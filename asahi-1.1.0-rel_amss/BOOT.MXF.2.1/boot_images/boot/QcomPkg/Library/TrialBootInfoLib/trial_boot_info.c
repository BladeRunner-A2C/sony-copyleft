/*===========================================================================

                       Trial Boot Info Source File

GENERAL DESCRIPTION
  This file contains functions to update Trial Boot Info in Trial Boot Info Partition

Copyright 2022 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/27/21   sp      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <string.h>
#include <TrialBootInfoLib.h>
#include <trial_boot_info.h>


/*==============================================================================
**  Functions
**============================================================================*/

/*=========================================================================

**  Function :  tbi_enable_trial_boot

** ==========================================================================
*/
/*!
*
* @brief
*   This api sets trial boot enable bit and writes into storage
*   @param[in]           TRUE to enable partition table restore
*
*/
trial_boot_status tbi_enable_trial_boot(uint8 enable_partition_table_restore)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    trial_boot_info_ptr->trial_boot_enable = TBI_ENABLE_TRIAL_BOOT;
    if (enable_partition_table_restore == TRUE)
    {
      trial_boot_info_ptr->partition_table_restore_enable = ENABLE_PARTITION_TABLE_RESTORE;
    }

    status = tbi_write_partition (trial_boot_info_ptr);
    if ( status != TBI_SUCCESS)
    {
      break;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_is_trial_boot_enabled

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and check whether trial boot is enabled or not
*
*   @param[in] pointer to hold trial_boot_enabled value
*              0 - Trial boot is not enabled
*              1 - Trial boot is enabled
*/
trial_boot_status tbi_is_trial_boot_enabled (uint8 *is_trial_boot_enabled)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    if (is_trial_boot_enabled == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }
	
    *is_trial_boot_enabled = 0;
  
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      *is_trial_boot_enabled = 0x1;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_is_trial_boot_failed

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and check whether max boot attempts of trial boots reached
*
*   @param[in] pointer to hold max_attempts_reached value
*              0 - Max attempts not reached
*              1 - Max attempts reached
*/
trial_boot_status tbi_is_trial_boot_failed(uint8 *is_trial_boot_failed)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    if (is_trial_boot_failed == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    *is_trial_boot_failed = 0;

    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && 
        trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT && 
        trial_boot_info_ptr->trial_boot_failed_attempts >= trial_boot_info_ptr->trial_boot_max_attempts)
    {
      *is_trial_boot_failed = 0x1;
    }
  }while(FALSE);

  return status; 
}


/*=========================================================================

**  Function :  tbi_rw_curr_failed_attempts

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and updates current number of failed boot attempts
*
*   @param[in] pointer to hold current failed attempts
*/
trial_boot_status tbi_rw_curr_failed_attempts(uint32 *trial_boot_failed_attempts, tbi_rw_type rw_type)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    if (trial_boot_failed_attempts == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    *trial_boot_failed_attempts = 0;

    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      if (rw_type == READ_TBI)
      {
        *trial_boot_failed_attempts = trial_boot_info_ptr->trial_boot_failed_attempts;
      }
      else if ( rw_type == WRITE_TBI)
      {
        trial_boot_info_ptr->trial_boot_failed_attempts = *trial_boot_failed_attempts;
        status = tbi_write_partition (trial_boot_info_ptr);
        if ( status != TBI_SUCCESS)
        {
          break;
        }
      }
    }
   }while(FALSE);

  return status; 
}

/*=========================================================================

**  Function :  tbi_increment_failed_boot_attempts

** ==========================================================================
*/
/*!
*
* @brief
*   This api writes current number of failed boot attempts to storage
*
*/
trial_boot_status tbi_increment_failed_boot_attempts()
{
  trial_boot_status status = TBI_SUCCESS;

  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT && 
        trial_boot_info_ptr->trial_boot_failed_attempts < trial_boot_info_ptr->trial_boot_max_attempts)
    {
      trial_boot_info_ptr->trial_boot_failed_attempts++;
    }
    else
    {
      status = TBI_MAX_ATTEMPTS_REACHED;
      break;
    }

    status = tbi_write_partition (trial_boot_info_ptr);
    if ( status != TBI_SUCCESS)
    {
      break;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_induce_trial_boot_failure

** ==========================================================================
*/
/*!
*
* @brief
*   This api writes the current_boot_failed_attempts as max_attempts  
*
*/
trial_boot_status  tbi_induce_trial_boot_failure()
{ 
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      trial_boot_info_ptr->trial_boot_failed_attempts = TBI_MAX_ATTEMPTS;
      trial_boot_info_ptr->trial_boot_max_attempts = TBI_MAX_ATTEMPTS;
      status = tbi_write_partition (trial_boot_info_ptr);
      if ( status != TBI_SUCCESS)
      {
        break;
      }
    }

  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_get_max_boot_attempts

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and returns max boot attempts
*
*   @param[in] pointer to hold max boot attempts
*/
trial_boot_status  tbi_get_max_boot_attempts(uint32 *trial_boot_max_attempts)
{ 
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      *trial_boot_max_attempts = trial_boot_info_ptr->trial_boot_max_attempts;
    }

  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_is_partition_table_restore_enabled

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and check whether recovery partition restore is enabled or not
*
*   @param[in] pointer to hold partition_table_restore_enabled value
*/
trial_boot_status tbi_is_partition_table_restore_enabled (uint32 *is_partition_table_restore_enabled)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    if (is_partition_table_restore_enabled == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    *is_partition_table_restore_enabled = 0;

    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      *is_partition_table_restore_enabled = trial_boot_info_ptr -> partition_table_restore_enable;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_get_partition_table_restore_status

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and returns recovery partition table restore status
*
*   @param[in] pointer to hold partition_table_restore_status value
*/
trial_boot_status tbi_get_partition_table_restore_status (uint32 *restore_status)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    if (restore_status == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    *restore_status = 0;

    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      *restore_status = trial_boot_info_ptr -> partition_table_restore_status;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_get_image_set_to_boot

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage and gets image set to boot from
*
*   @param[in] pointer to hold image set A/B
*/
trial_boot_status tbi_get_image_set_to_boot (uint32 *image_set)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    if (image_set == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    *image_set = 0;

    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      *image_set = trial_boot_info_ptr->image_set_to_boot;
    }
  }while(FALSE);

  return status;
}

trial_boot_status tbi_update_partition_table_restore_status(uint32 restore_status)
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    if (trial_boot_info_ptr->magic_cookie == TBI_MAGIC_COOKIE && trial_boot_info_ptr->trial_boot_enable == TBI_ENABLE_TRIAL_BOOT)
    {
      trial_boot_info_ptr->partition_table_restore_status = restore_status;
    }

    status = tbi_write_partition (trial_boot_info_ptr);
    if ( status != TBI_SUCCESS)
    {
      break;
    }

  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_clear_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api clears trial boot info partition
*
*/
trial_boot_status tbi_clear_partition()
{
  trial_boot_status status = TBI_SUCCESS;
  trial_boot_info_type *trial_boot_info_ptr = NULL;

  do
  {
    status = tbi_get_trial_boot_info (&trial_boot_info_ptr);
    if (status != TBI_SUCCESS)
    {
      break;
    }

    if (trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    memset((void *)(trial_boot_info_ptr), 0, sizeof(trial_boot_info_type));

    status = tbi_write_partition (trial_boot_info_ptr);
  }while(FALSE);

  return status;
}