/**
# @file boot_recovery_lun.c
#
#  Boot Recovery LUN handling
#
#  Copyright 2021, 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
#
#**/

/*==============================================================================
#                              EDIT HISTORY
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 02/19/23   suhas   Integrated BootPartitionLib
# 05/24/21   vk      Initial Revision
#
#==============================================================================*/
#include <string.h>
#include <boot_config_context.h>
#include <boot_recovery_partition.h>
#include <boot_error_if.h>
#include <boot_coldplug_if.h>
#include <boot_media_interface_if.h>
#include <boot_media_types.h>
#include <boot_memory_mgr_if.h>
#include <boot_ramdump_if.h>
#include <boot_config.h>
#include <boot_logger.h>
#include <boot_reset_if.h>
#include <boot_block_dev.h>
#include <coldplug_api.h>
#include <busywait.h>
#include <boot_recovery_lun.h>
#include <boot_partition.h>

extern boot_configuration_table_entry sbl1_config_table[];

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define UART_FLUSH_DELAY     (3000)
typedef enum recovery_info_acces_mode_type {RECOVERY_INFO_READ, RECOVERY_INFO_WRITE, RECOVERY_INFO_READ_WITHOUT_INIT} recovery_info_acces_mode_type;

/*=============================================================================
                              LOCAL FUNCTION DECLARATIONS
=============================================================================*/
static bl_error_boot_type boot_recovery_access_recovery_info (boot_handle config_context_handle, bl_recovery_info_type *recovery_info_buffer, recovery_info_acces_mode_type access_mode);
static bl_error_boot_type boot_recovery_get_bank_status      (boot_handle config_context_handle, uint32 *bank_status, recovery_info_acces_mode_type recovery_info_acces_mode);
static bl_error_boot_type boot_recovery_update_lun_attempted (boot_handle config_context_handle, uint32 bank_status);
static bl_error_boot_type boot_recovery_process_bank_status  (boot_handle config_context_handle, uint8 current_boot_lun, uint8 bank_status);
static bl_error_boot_type boot_recovery_swap_boot_lun        (boot_handle config_context_handle, uint32 switch_to_lun);


/*=============================================================================
                              LOCAL FUNCTION DEFINITIONS
=============================================================================*/

static bl_error_boot_type boot_recovery_access_recovery_info(boot_handle config_context_handle, bl_recovery_info_type *recovery_info_data, recovery_info_acces_mode_type access_mode)
{
  bl_error_boot_type status = BL_ERR_NONE;
  bl_error_boot_type temp_status = BL_ERR_NONE;
  boot_media_interface_if_type *media_if = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_coldplug_if_type *coldplug_if = NULL;
  boot_handle media_handle = NULL;
  struct coldplug_guid *previous_guid_ptr = NULL;
  enum coldplug_result coldplug_status = COLDPLUG_RESULT_UNKNOWN;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;
  const uint8 * recoveryinfo_partition_id = NULL;
  uint8 recoveryinfo_partition_id_size = 0;
  boot_media_type boot_device = NO_FLASH;
  boot_image_set_t current_image_set = IMAGE_SET_MAX;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_COLDPLUG_INTERFACE, (void **)&coldplug_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Malloc memory for media interface */
    status = mem_if->malloc(sizeof(boot_media_interface_if_type), (void *)&media_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (media_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }


    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_PARTITION_ID, (void **)&previous_guid_ptr);
    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get boot device from config table */
    status = boot_config_context_get_value(config_context_handle,
                                           CONFIG_CONTEXT_BOOT_DEVICE,
                                           (void *)&boot_device);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get the current image set */
    status = boot_config_context_get_value(config_context_handle,
                                           CONFIG_CONTEXT_CURRENT_IMAGE_SET,
                                           (void *)&current_image_set);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get the media family */
    status = get_boot_media_family(boot_device,
                                   &media_family);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get the BootPartitionLib interface pointer */
    status = boot_config_context_get_ptr(config_context_handle, 
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


    /* Get recoveryinfo partition id */
    status = partition_if->get_partition_id_by_partition(media_family,
                                                         current_image_set,
                                                         RECOVERY_INFO_PARTITION,
                                                         &recoveryinfo_partition_id,
                                                         &recoveryinfo_partition_id_size);
    
    if (status != BL_ERR_NONE)
    {
      /* If error is returned then a partition does not exist.
        Clear the error and set the  partition id to null. */
      CLEAR_ERROR_CODE;
      recoveryinfo_partition_id = NULL;
      status = BL_ERR_NONE;
    }


    status = boot_config_context_set_ptr (config_context_handle, 
                                          CONFIG_CONTEXT_PARTITION_ID, 
                                          (void *)recoveryinfo_partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_media_get_interface(config_context_handle, media_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (media_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Open media, if open failed , retry after performing full UFS init */
    status = media_if->open(config_context_handle, &media_handle);
    if (status != BL_ERR_NONE)
    {
      if (access_mode == RECOVERY_INFO_READ_WITHOUT_INIT)
      {
        boot_log_message ("Recovery: media open skip");
        status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED);
        break;
      }

      /* Try after full device init */
      coldplug_status = coldplug_if->background_init_start (COLDPLUG_DEVICE_UFS, TRUE, 0);
      if (coldplug_status != COLDPLUG_RESULT_SUCCESS)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_BACKGRND_INIT_START_FAILURE);
        break;
      }

      coldplug_status = coldplug_if->background_init_finish (COLDPLUG_DEVICE_UFS, TRUE, 0);
      if (coldplug_status != COLDPLUG_RESULT_SUCCESS)
      {
        status =  GET_ERROR_CODE (BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_BACKGRND_INIT_FINISH_FAILURE);
        break;
      }

      coldplug_status = coldplug_if->open_device (COLDPLUG_DEVICE_UFS, TRUE);
      if (coldplug_status != COLDPLUG_RESULT_SUCCESS)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_BLOCKDEV, BL_ERR_COLDPLUG_OPEN_DEV_FAILURE);
        break;
      }

      status = media_if->open(config_context_handle, &media_handle);
      if (status != BL_ERR_NONE)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERROR_OPEN_GPT_PARTITION_FAIL);
        break;
      }
    }

    if ( (access_mode == RECOVERY_INFO_READ) || (access_mode == RECOVERY_INFO_READ_WITHOUT_INIT) )
    {
      status = media_if->read (media_handle, (uint8*)recovery_info_data, 0, sizeof(bl_recovery_info_type));
      if (status != BL_ERR_NONE)
      {
        boot_log_message ("Recovery: Read failed");
        if (status == GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED)) 
        {
          boot_log_message ("Recovery: Read failed not init");
          status = BL_ERR_NONE;
        }
      }
    }
    else if (access_mode == RECOVERY_INFO_WRITE)
    {
      status = media_if->write (media_handle, (uint8*)recovery_info_data, 0, sizeof(bl_recovery_info_type));
      if (status != BL_ERR_NONE)
      {
        boot_log_message ("Recovery: Write failed");
      }
    }
    else
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, 0);
    }

    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = media_if->close (media_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }
  } while (FALSE);

  if (previous_guid_ptr != NULL)
  {
    temp_status = boot_config_context_set_ptr (config_context_handle, CONFIG_CONTEXT_PARTITION_ID, previous_guid_ptr);
    if (temp_status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERROR_RESTORE_PARTITION_GUID_FAIL);
    }
  }

  if (media_if != NULL)
  {
    mem_if->free(media_if);
    media_if = NULL;
  }

  return status;
}

static bl_error_boot_type boot_recovery_get_bank_status (boot_handle config_context_handle, uint32 *bank_status, recovery_info_acces_mode_type access_mode)
{
  bl_error_boot_type status = BL_ERR_NONE;
  bl_recovery_info_type *recovery_info_data = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;

  do
  {
    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Malloc memory for media interface */
    status = mem_if->malloc(sizeof(bl_recovery_info_type), (void *)&recovery_info_data);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (recovery_info_data == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Read the recovery misc and meta data */
    status = boot_recovery_access_recovery_info (config_context_handle, recovery_info_data, access_mode);
    if (status != BL_ERR_NONE)
    {
      if (status == GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED))
      {
        status = BL_ERR_NONE;
      }
      break;
    }

    if (recovery_info_data->magic == RECOVERY_INFO_MAGIC)
    {
      *bank_status = recovery_info_data->bank_status;
    }
    else
    {
      boot_log_message ("Recovery: partition magic not set");
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED);
      break;
    }

  } while (FALSE);

  if (recovery_info_data != NULL)
  {
    mem_if->free(recovery_info_data);
    recovery_info_data = NULL;
  }

  return status;
}

bl_error_boot_type boot_recovery_update_lun_attempted (boot_handle config_context_handle, uint32 bank_status)
{
  bl_error_boot_type status = BL_ERR_NONE;
  bl_recovery_info_type *recovery_info_data = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;

  do
  {
    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Malloc memory for media interface */
    status = mem_if->malloc(sizeof(bl_recovery_info_type), (void *)&recovery_info_data);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (recovery_info_data == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Read the recovery misc and meta data */
    status = boot_recovery_access_recovery_info (config_context_handle, recovery_info_data, RECOVERY_INFO_READ);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* MISC data does not exist, create it */
    if (recovery_info_data->magic != RECOVERY_INFO_MAGIC)
    {
      recovery_info_data->magic         = RECOVERY_INFO_MAGIC;
      recovery_info_data->version       = 1U;
      recovery_info_data->bank_status   = bank_status;
      recovery_info_data->owner         = OWNER_XBL;
      recovery_info_data->reserved0     = 0;
      recovery_info_data->reserved1     = 0;
    }
    else
    {
      recovery_info_data->bank_status  |= bank_status;
      recovery_info_data->owner         = OWNER_XBL;
    }

    status = boot_recovery_access_recovery_info (config_context_handle, recovery_info_data, RECOVERY_INFO_WRITE);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (recovery_info_data != NULL)
    {
      mem_if->free(recovery_info_data);
      recovery_info_data = NULL;
    }
  } while (FALSE);

  return status;
}

static bl_error_boot_type boot_recovery_swap_boot_lun(boot_handle config_context_handle, uint32 switch_to_lun)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_coldplug_if_type *coldplug_if = NULL;
  boot_reset_if_type * reset_if = NULL;
  int coldplug_status = 0;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_COLDPLUG_INTERFACE, (void **)&coldplug_if);
    if (status != BL_ERR_NONE)
    {
      return status;
    }
    if (coldplug_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_RESET_INTERFACE, (void **)&reset_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (reset_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    coldplug_status = coldplug_if->set_bootable_partition (COLDPLUG_DEVICE_UFS, TRUE, switch_to_lun);
    if (coldplug_status != 0)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY,  0);
      break;
    }

    status = reset_if->hw_reset(BOOT_HARD_RESET_TYPE);
    if (status != BL_ERR_NONE)
    {
      break;
    }
  } while (FALSE);

  return status;
}

static bl_error_boot_type boot_recovery_process_bank_status (boot_handle config_context_handle, uint8 current_boot_lun, uint8 bank_status)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_ramdump_if_type *ramdump_if = NULL;

  status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_INTERFACE, (void **)&ramdump_if);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  switch (bank_status)
  {
    {
    case BANK_AB_USABLE:
      /* No errors found */
      boot_log_message ("Recovery: Set AB usable");
      status = BL_ERR_NONE;
      break;

    case DONT_USE_BANK_A:
      /* Booting from LUN 1 that is already marked unusable - swap boot lun and reset */
      if (current_boot_lun == BOOT_LUN_1)
      {
        boot_log_message ("Recovery: Swap to BOOT_LUN2");
        busywait(UART_FLUSH_DELAY);
        status = boot_recovery_swap_boot_lun (config_context_handle, BOOT_LUN_2);
      }
      break;

    case DONT_USE_BANK_B:
      /* Booting from LUN 2 that is already marked unusable - swap boot lun and reset */
      if (current_boot_lun == BOOT_LUN_2)
      {
        boot_log_message ("Recovery: Swap to BOOT_LUN1");
        busywait(UART_FLUSH_DELAY);
        status = boot_recovery_swap_boot_lun (config_context_handle, BOOT_LUN_1);
      }
      break;

    case DONT_USE_BANK_AB:
      /* Enter EDL */
      boot_log_message ("Recovery: Set AB corrupt - EDL");
      busywait(UART_FLUSH_DELAY);
      status = ramdump_if->transition_pbl_forced_dload (config_context_handle);
      break;
    }
  }

exit:  
  return status;
}


/*=============================================================================
                              PUBLIC FUNCTION DEFINITIONS
=============================================================================*/


bl_error_boot_type boot_recovery_select_boot_partitions (boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_coldplug_if_type *coldplug_if = NULL;
  boot_media_type boot_device = NO_FLASH;
  uint32 current_boot_lun =0xFFFF;
  enum coldplug_result coldplug_status = COLDPLUG_RESULT_UNKNOWN;
  int i = 0;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;
  const uint8 * recovery_img_partition_id = NULL;
  uint8 recovery_img_partition_id_size = 0;


  /* Get boot device from the context table */
  status = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
  if (status != BL_ERR_NONE)
  {
    return status;
  }

  if ((boot_device != UFS_FLASH))
  {
    return status;
  }

  status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_COLDPLUG_INTERFACE, (void **)&coldplug_if);
  if (status != BL_ERR_NONE)
  {
    return status;
  }

  coldplug_status = coldplug_if->get_bootable_partition(COLDPLUG_DEVICE_UFS, TRUE, &current_boot_lun);
  if (coldplug_status != 0)
  {
    boot_log_message ("get_bootable_partition fail");
  }

  if (current_boot_lun == BOOT_LUN_2)
  {
    boot_log_message ("BOOT_LUN_2");
  }
  else if (current_boot_lun == BOOT_LUN_1)
  {
    boot_log_message ("BOOT_LUN_1");
  }
  else
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_INVALID_LUN);
    return status;
  }

  /* Check if current lun is bootable */
  status = boot_recovery_is_current_boot_partition_valid (config_context_handle);
  if (status != BL_ERR_NONE)
  {
    if (status == GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED))
    {
      status = BL_ERR_NONE;
    }
    else 
    {
      return status;
    }
  }


  /* Set the current_image_set to image_set_b for recovery partition */
  status = boot_config_context_set_value(config_context_handle,
                                         CONFIG_CONTEXT_CURRENT_IMAGE_SET,
                                         IMAGE_SET_B);

  if (status != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Get the media family */
  status = get_boot_media_family(boot_device,
                                 &media_family);

  if (status != BL_ERR_NONE)
  {
    goto exit;
  }


  status = boot_config_context_get_ptr(config_context_handle, 
                                       CONFIG_CONTEXT_PARTITION_INTERFACE, 
                                       (void **)&partition_if);
  
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  /* Check for null pointer */
  if (partition_if == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }
  
  
  do
  {
    status = partition_if->get_partition_id_by_partition(media_family,
                                                         IMAGE_SET_B,
                                                         sbl1_config_table[i].boot_partition_type,
                                                         &recovery_img_partition_id,
                                                         &recovery_img_partition_id_size);

    /* If error is returned then the partition does not exist.
       Clear the error and set the partition id to NULL. */
    if (status != BL_ERR_NONE)
    {
      CLEAR_ERROR_CODE;
      recovery_img_partition_id = NULL;
      status = BL_ERR_NONE;
    }


    /* Set the recovery partition id  pointer */
    status = boot_config_context_set_ptr(config_context_handle,
                                         CONFIG_CONTEXT_RECOVERY_PARTITION_ID,
                                         (void *)recovery_img_partition_id);

    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_INITIALIZATION_ERROR);
      break;
    }

    i++;

  } while (sbl1_config_table[i].media_type != MEDIA_TYPE_MAX);


 exit:
  return status;
}


bl_error_boot_type boot_recovery_load_recovery_lun(boot_handle config_context_handle, uint8 *recovery_partition_id)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_coldplug_if_type *coldplug_if = NULL;
  boot_ramdump_if_type *ramdump_if = NULL;
  boot_media_type boot_device = NO_FLASH;
  uint32 current_boot_lun = 0;
  uint32 bank_status = 0;
  enum coldplug_result coldplug_status = COLDPLUG_RESULT_UNKNOWN;

  status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_INTERFACE, (void **)&ramdump_if);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  /* Get boot device from the context table */
  status = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  if ((boot_device != UFS_FLASH))
  {
    status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_FEATURE_UNSUPPORTED);
    goto exit;
  }

  status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_COLDPLUG_INTERFACE, (void **)&coldplug_if);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  coldplug_status = coldplug_if->get_bootable_partition (COLDPLUG_DEVICE_UFS, TRUE, &current_boot_lun);
  if (coldplug_status != 0)
  {
    status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY,  BL_ERR_INVALID_LUN);
    goto exit;
  }

    /* Update bank status in recovery_info partition */
    status = boot_recovery_update_lun_attempted (config_context_handle, current_boot_lun);
    if (status != BL_ERR_NONE)
    {
      goto exit;
  }

  status = boot_recovery_get_bank_status (config_context_handle, &bank_status, RECOVERY_INFO_READ);
  if (status != BL_ERR_NONE)
  {
    if (status == GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED))
    {
      boot_log_message ("Recovery: Info missing");
      bank_status = BANK_AB_USABLE;
      status = BL_ERR_NONE;
    }
    else
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_INVALID_LUN);
      return status;
    }
  }

  status = boot_recovery_process_bank_status (config_context_handle, current_boot_lun, bank_status);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

exit:
  return status;
}

bl_error_boot_type boot_recovery_is_current_boot_partition_valid (boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_coldplug_if_type *coldplug_if = NULL;
  boot_media_type boot_device = NO_FLASH;
  uint32 current_boot_lun = 0;
  uint32 bank_status = 0;
  enum coldplug_result coldplug_status = COLDPLUG_RESULT_UNKNOWN;

  /* Get boot device from the context table */
  status = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  if ((boot_device != UFS_FLASH))
  {
    status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_FEATURE_UNSUPPORTED);
    goto exit;
  }

  status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_COLDPLUG_INTERFACE, (void **)&coldplug_if);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  coldplug_status = coldplug_if->get_bootable_partition (COLDPLUG_DEVICE_UFS, TRUE, &current_boot_lun);
  if (coldplug_status != 0)
  {
    status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY,  BL_ERR_INVALID_LUN);
    goto exit;
  }

  status = boot_recovery_get_bank_status (config_context_handle, &bank_status, RECOVERY_INFO_READ_WITHOUT_INIT);
  if (status != BL_ERR_NONE)
  {
    if (status == GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED))
    {
      boot_log_message ("Recovery: Info missing");
      bank_status = BANK_AB_USABLE;
    }
    else
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_INVALID_LUN);
      goto exit;
    }
  }

  if (status != GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED))
  {
    status = boot_recovery_process_bank_status (config_context_handle, current_boot_lun, bank_status);
    if (status != BL_ERR_NONE)
    {
      return status;
    }
  }

exit:
  return status;
}

bl_error_boot_type boot_recovery_update_corrupt_patition_id (boot_handle config_context_handle, uint8 *partition_id)
{
  bl_error_boot_type status = BL_ERR_NONE;
  bl_recovery_info_type *recovery_info_data = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_reset_if_type * reset_if = NULL;
  uint32 copy_size = 0;
  uint8 *recovery_partition_id = NULL;
  boot_ramdump_if_type *ramdump_if = NULL;

  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_INTERFACE, (void **)&ramdump_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_XBLCFG_RECOVERY_PARTITION_ID, (void **)&recovery_partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Malloc memory for media interface */
    status = mem_if->malloc(sizeof(bl_recovery_info_type), (void *)&recovery_info_data);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (recovery_info_data == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Read the recovery misc and meta data */
    status = boot_recovery_access_recovery_info (config_context_handle, recovery_info_data, RECOVERY_INFO_READ);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* MISC data does not exist, create it */
    if (recovery_info_data->magic != RECOVERY_INFO_MAGIC)
    {
      recovery_info_data->magic         = RECOVERY_INFO_MAGIC;
      recovery_info_data->version       = 1U;
      recovery_info_data->owner         = OWNER_XBL;
      recovery_info_data->reserved0     = 0;
      recovery_info_data->reserved1     = 0;
      copy_size = memscpy(recovery_info_data->corrupt_guid_bank_a, sizeof(recovery_info_data->corrupt_guid_bank_a), partition_id, PARTITION_ID_MAX_SIZE);
      if(copy_size < PARTITION_ID_MAX_SIZE)
      {
        break;
      }
    }

    status = boot_recovery_access_recovery_info (config_context_handle, recovery_info_data, RECOVERY_INFO_WRITE);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (recovery_info_data != NULL)
    {
      mem_if->free(recovery_info_data);
      recovery_info_data = NULL;
    }

    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_RESET_INTERFACE, (void **)&reset_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (reset_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    if(boot_recovery_is_booting_from_recovery_partition(partition_id, recovery_partition_id) == TRUE)
    {
      /* Enter EDL */
      boot_log_message ("Recovery: Set AB corrupt - EDL");
      busywait(UART_FLUSH_DELAY);
      status = ramdump_if->transition_pbl_forced_dload (config_context_handle);
    }
    else
    {
      status = reset_if->hw_reset(BOOT_HARD_RESET_TYPE);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }

  } while (FALSE);

  return status;
}


bl_error_boot_type boot_recovery_is_partition_valid (boot_handle config_context_handle, uint8 *partition_id)
{
  bl_error_boot_type status = BL_ERR_NONE;
  bl_recovery_info_type *recovery_info_data = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  uint8 *recovery_partition_id = NULL;

  do
  {
    status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Malloc memory for media interface */
    status = mem_if->malloc(sizeof(bl_recovery_info_type), (void *)&recovery_info_data);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (recovery_info_data == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Read the recovery misc and meta data */
    status = boot_recovery_access_recovery_info (config_context_handle, recovery_info_data, RECOVERY_INFO_READ);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED);
      break;
    }

    if (recovery_info_data->magic == RECOVERY_INFO_MAGIC)
    {
      /* compare corrupted_guid_bank_a with primary partition, if true set primary with recovery partition id */
      if (memcmp(recovery_info_data->corrupt_guid_bank_a, partition_id, PARTITION_ID_MAX_SIZE) == 0)
      {
        status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_XBLCFG_RECOVERY_PARTITION_ID, (void **)&recovery_partition_id);
        if (status != BL_ERR_NONE)
        {
          break;
        }
        status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_PARTITION_ID, recovery_partition_id);
        if (status != BL_ERR_NONE)
        {
          break;
        }
        status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_XBLCFG_PARTITION_ID, recovery_partition_id);
        if (status != BL_ERR_NONE)
        {
          break;
        }

        boot_log_message ("Load from recovery partition");
      }

      memset(recovery_info_data, 0, sizeof(bl_recovery_info_type));

      status = boot_recovery_access_recovery_info (config_context_handle, recovery_info_data, RECOVERY_INFO_WRITE);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }
  
  } while (FALSE);

  if (recovery_info_data != NULL)
  {
    mem_if->free(recovery_info_data);
    recovery_info_data = NULL;
  }

  return status;
}
