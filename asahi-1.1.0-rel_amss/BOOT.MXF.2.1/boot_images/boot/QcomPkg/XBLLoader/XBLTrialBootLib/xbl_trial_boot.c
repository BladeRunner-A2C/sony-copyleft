/**
 * @file xbl_trial_boot.c
 * @brief
 * Source file for bootloader configuration
 *
 * Copyright 2022 - 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
 *
 */

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when         who        what, where, why
--------     ---        ---------------------------------------------------------
02/22/23     suhas      Integrated BootPartitionLib
01/15/23     suhas      Included boot_partition_legacy.h
09/16/22     sp         Initial version

===========================================================================*/

/*==========================================================================
                             INCLUDE FILES
===========================================================================*/

#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_logger.h>
#include <TrialBootInfoLib.h>
#include <HALbootHWIO.h>
#include <HALhwio.h>
#include <xbl_trial_boot.h>
#include <trial_boot_info.h>
#include <boot_partition_legacy.h>
#include <boot_reset_if.h>
#include <pbl_sbl_shared.h>
#include <boot_partition.h>
#include <boot_media_interface_if.h>


/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/
bl_error_boot_type boot_sync_tbi_and_tcsr(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  trial_boot_status tbi_status = TBI_SUCCESS;
  boot_reset_if_type * reset_if = NULL;
  uint32 tcsr_trial_boot_enable = 0;
  uint32 tcsr_no_of_failed_boot_attempts = 0;
  uint32 tcsr_boot_max_attempts = 0;
  uint32 tbi_no_of_failed_boot_attempts = 0;
  uint32 tbi_boot_max_attempts = 0;
  uint32 tbi_image_set_to_boot = 0;
  uint32 tcsr_image_set_to_boot = 0;

  do
  {
    /* Read functional failure recovery feature enable bit and enable if not enabled*/
    tcsr_trial_boot_enable = HWIO_TCSR_TCSR_BOOT_INFO_IN & HWIO_TCSR_TCSR_BOOT_INFO_EARLY_FIRMWARE_FUNCTIONAL_FAILURE_RECOVERY_FEATURE_ENABLE_BMSK;

    if(tcsr_trial_boot_enable != TBI_ENABLE_TRIAL_BOOT)
    {
       HWIO_TCSR_TCSR_BOOT_INFO_OUTM(HWIO_TCSR_TCSR_BOOT_INFO_EARLY_FIRMWARE_FUNCTIONAL_FAILURE_RECOVERY_FEATURE_ENABLE_BMSK, TBI_ENABLE_TRIAL_BOOT);
    }

    /* Read Number of failed boot attempts from storage & TCSR and keep them in sync*/
    /* write storage value into tcsr*/
    tcsr_no_of_failed_boot_attempts = (HWIO_TCSR_TCSR_BOOT_INFO_IN & HWIO_TCSR_TCSR_BOOT_INFO_NUMBER_OF_FAILED_BOOT_ATTEMPTS_BMSK) >> HWIO_TCSR_TCSR_BOOT_INFO_NUMBER_OF_FAILED_BOOT_ATTEMPTS_SHFT;

    tbi_status = tbi_rw_curr_failed_attempts(&tbi_no_of_failed_boot_attempts, READ_TBI);
    if (tbi_status != TBI_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
      break;
    }
  
    if(tcsr_no_of_failed_boot_attempts < tbi_no_of_failed_boot_attempts)
    {
       HWIO_TCSR_TCSR_BOOT_INFO_OUTM(HWIO_TCSR_TCSR_BOOT_INFO_NUMBER_OF_FAILED_BOOT_ATTEMPTS_BMSK, tbi_no_of_failed_boot_attempts << HWIO_TCSR_TCSR_BOOT_INFO_NUMBER_OF_FAILED_BOOT_ATTEMPTS_SHFT);
    }
    else if(tcsr_no_of_failed_boot_attempts > tbi_no_of_failed_boot_attempts)
    {
      tbi_status = tbi_rw_curr_failed_attempts(&tcsr_no_of_failed_boot_attempts, WRITE_TBI);
      if (tbi_status != TBI_SUCCESS)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
        break;
      }
    }

    /* Read max number of boot attempts from storage & TCSR and keep them in sync*/
    tcsr_boot_max_attempts = (HWIO_TCSR_TCSR_BOOT_INFO_IN & HWIO_TCSR_TCSR_BOOT_INFO_NUMBER_OF_MAX_BOOT_ATTEMPTS_BMSK) >> HWIO_TCSR_TCSR_BOOT_INFO_NUMBER_OF_MAX_BOOT_ATTEMPTS_SHFT;
    tbi_status = tbi_get_max_boot_attempts(&tbi_boot_max_attempts);
    if (tbi_status != TBI_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
      break;
    }

    if(tcsr_boot_max_attempts != tbi_boot_max_attempts)
    {
      HWIO_TCSR_TCSR_BOOT_INFO_OUTM(HWIO_TCSR_TCSR_BOOT_INFO_NUMBER_OF_MAX_BOOT_ATTEMPTS_BMSK, tbi_boot_max_attempts << HWIO_TCSR_TCSR_BOOT_INFO_NUMBER_OF_MAX_BOOT_ATTEMPTS_SHFT);
    }

    /* check image_set from TCSR and storage, update tcsr if there is mismatch and perform warm reset*/
    tcsr_image_set_to_boot = (HWIO_TCSR_TCSR_BOOT_INFO_IN & HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_BMSK) >> HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_SHFT;

    tbi_status = tbi_get_image_set_to_boot (&tbi_image_set_to_boot);
    if (tbi_status != TBI_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
      break;
    }

    if (tcsr_image_set_to_boot != tbi_image_set_to_boot)
    {
      HWIO_TCSR_TCSR_BOOT_INFO_OUTM(HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_BMSK, tbi_image_set_to_boot << HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_SHFT);
      status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_RESET_INTERFACE, (void **)&reset_if);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = reset_if->hw_reset(BOOT_HARD_RESET_TYPE);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }

  }while(FALSE);


return status;
}


/*===========================================================================
**  Function :  boot_handle_trial_boot
** ==========================================================================
*/
/*!
* 
* @brief
*   This function handles trial boot. Checks for feature enable bit & number of failed attempts 
*   and switches to set B once max attempts reached. And keeps storage partition and tcsr values in sync
*
* @param[in] boot_handle
*
* @par Dependencies
*   None
*
*/ 
bl_error_boot_type boot_handle_trial_boot(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  trial_boot_status tbi_status = TBI_SUCCESS;
  boot_pbl_shared_data_if_type * pbl_shared_data_if = NULL;
  boot_reset_if_type * reset_if = NULL;
  uintnt is_xbl_booted_from_set_a_or_b = 0;
  uint32 is_partition_table_restore_enabled = 0;
  uint32 restore_status = 0;
  uint32 tbi_image_set = 0;
  uint8 is_trial_boot_enabled = 0;
  uint8 is_trial_boot_failed = 0;
  boot_media_type boot_device = NO_FLASH;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;

  do
  {
    tbi_status = tbi_is_trial_boot_enabled(&is_trial_boot_enabled);
    if (tbi_status != TBI_SUCCESS)
    {
      break;
    }

    if (is_trial_boot_enabled == 1)
    {
      /*Increment Trial Boot count and write to storage*/
      tbi_status = tbi_increment_failed_boot_attempts();
      if (tbi_status != TBI_SUCCESS)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
        break;
      }

      status = boot_sync_tbi_and_tcsr(config_context_handle);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      /* Check Image set from tbi and pbl shared data. If pbl booted from inverse, induce trial boot failure */
      status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_PBL_SHARED_DATA_INTERFACE, (void **)&pbl_shared_data_if);
      if (status != BL_ERR_NONE || pbl_shared_data_if == NULL)
      {
        return status;
      }

      status = pbl_shared_data_if->get_value(PBL_APPS_XBL_SHARED_DATA_PARAM_ID_CURRENT_IMAGE_SET, (uintnt *)&is_xbl_booted_from_set_a_or_b);
      if (status != BL_ERR_NONE)
      {
        if(status == (BL_ERROR_GROUP_PBL_SHARED_DATA|BL_ERR_INVALID_PARAMETER))
        {
          status = BL_ERR_NONE;
        }
      }

      tbi_status = tbi_get_image_set_to_boot (&tbi_image_set);
      if (tbi_status != TBI_SUCCESS)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
        break;
      }

      if (is_xbl_booted_from_set_a_or_b != tbi_image_set)
      {
        /* Induce trial boot failure by writing max attempts to storage */
        tbi_status = tbi_induce_trial_boot_failure();
        if (tbi_status != TBI_SUCCESS)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
          break;
        }
      }

      tbi_status = tbi_is_trial_boot_failed(&is_trial_boot_failed);
      if (tbi_status != TBI_SUCCESS)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
        break;
      }

      if (is_trial_boot_failed == 1)
      {
        tbi_status = tbi_is_partition_table_restore_enabled(&is_partition_table_restore_enabled);
        if (tbi_status != TBI_SUCCESS)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
          break;
        }

        tbi_status = tbi_get_partition_table_restore_status(&restore_status);
        if (tbi_status != TBI_SUCCESS)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
          break;
        }

        if ((is_partition_table_restore_enabled == TBI_ENABLE_PARTITION_TABLE_RESTORE) && (restore_status != PARTITION_TABLE_RESTORE_COMPLETE))
        {
          status = boot_media_restore_partition_table(config_context_handle);
          if (status == BL_ERR_NONE)
          {
            restore_status = PARTITION_TABLE_RESTORE_COMPLETE;
            tbi_status = tbi_update_partition_table_restore_status(restore_status);
            if (tbi_status != TBI_SUCCESS)
            {
              status = GET_ERROR_CODE(BL_ERROR_GROUP_TRIAL_BOOT, tbi_status);
              break;
            }
          }
          else
          {
            break;
          }

          status = boot_config_context_get_ptr (config_context_handle, CONFIG_CONTEXT_RESET_INTERFACE, (void **)&reset_if);
          if (status != BL_ERR_NONE)
          {
            break;
          }
          /* hard reset */
          status = reset_if->hw_reset(BOOT_HARD_RESET_TYPE);
          if (status != BL_ERR_NONE)
          {
            break;
          }
        }
        else if(is_partition_table_restore_enabled != TBI_ENABLE_PARTITION_TABLE_RESTORE)
        {
          if (tbi_image_set == SET_A) /* with trial boot failed */
          {
            status = boot_config_context_set_value (config_context_handle,
                                                    CONFIG_CONTEXT_CURRENT_IMAGE_SET,
                                                    IMAGE_SET_B);
            if (status != BL_ERR_NONE)
            {
              break;
            }
          }
        } /* Partition table restore not enabled case*/
      } /* Trial boot failed case */

      /* Get boot device */
      status = boot_config_context_get_value(config_context_handle,
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
      status = boot_config_context_get_ptr(config_context_handle,
                                           CONFIG_CONTEXT_PARTITION_INTERFACE,
                                           (void *)&partition_if);

      if (status != BL_ERR_NONE)
      {
        break;
      }

      /* Check for null pointer */
      if (partition_if == NULL)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION,
                                BL_ERR_NULL_PTR_PASSED);
        break;
      }


      /* set recovery partition ids to null to disable corruption recovery feature when trial boot is enabled*/
      status = partition_if->boot_partition_disable_all_image_sets(media_family);

      if (status != BL_ERR_NONE)
      {
        break;
      }
    } 
    else
    {
      /* clear TCSR */ 
      HWIO_TCSR_TCSR_BOOT_INFO_OUT(0);
    }

  }while(FALSE);

  return status;
}