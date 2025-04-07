/*===========================================================================

                       Recovery Boot Info data filed APIs

GENERAL DESCRIPTION
  This file contains functions to update Recovery Boot Info in Recovery Boot Info Partition

Copyright 2023 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
03/20/23   vk      Initial revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <string.h>
#include <RecoveryBootInfoLib.h>
#include <recovery_boot_info.h>


/*==============================================================================
**  Functions
**============================================================================*/


/*=========================================================================

**  Function :  rbi_mark_set_failed

** ==========================================================================
*/
/*!
*
* @brief
*   This api updates failed set to storage
*
*/
recovery_boot_status rbi_mark_set_failed (uint32 image_set)
{
  recovery_boot_status status = RBI_SUCCESS;

  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }


    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      if (image_set == BOOT_SET_A)
      {
        recovery_boot_info_ptr->image_set_status |= DONT_USE_SET_A;
      }
      else if (image_set == BOOT_SET_B)
      {
        recovery_boot_info_ptr->image_set_status |= DONT_USE_SET_B;
      }
    }
    else
    {
      status = RBI_ERR;
      break;
    }

    status = rbi_write_partition (recovery_boot_info_ptr);
    if ( status != RBI_SUCCESS)
    {
      break;
    }
  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  rbi_reset

** ==========================================================================
*/
/*!
*
* @brief
*   This api clears recovery boot info partition
*
*/
recovery_boot_status rbi_reset()
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    memset((void *)(recovery_boot_info_ptr), 0, sizeof(recovery_boot_info_type));

    status = rbi_write_partition (recovery_boot_info_ptr);
    if ( status != RBI_SUCCESS)
    {
      break;
    }
  } while (FALSE);

  return status;
}



/*=========================================================================

**  Function :  rbi_info_get_image_set_status

** ==========================================================================
*/
/*!
*
* @brief
*   This api returns image_set_status
*
*/
recovery_boot_status rbi_info_get_image_set_status (uint32 *image_set)
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    if (image_set == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    *image_set = 0;

    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      *image_set = recovery_boot_info_ptr->image_set_status;
    }
  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  rbi_is_image_set_attempted

** ==========================================================================
*/
/*!
*
* @brief
*   This api looks at image_set_status and returns if provded set is already attempted
*
*/
recovery_boot_status rbi_is_image_set_attempted (uint32 image_set_to_check, uint8* set_attempted)
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    if (set_attempted == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    if ((image_set_to_check != BOOT_SET_A) || (image_set_to_check != BOOT_SET_B))
    {
      status = RBI_ERR;
      break;
    }

    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    /* Set attempted by default */
    *set_attempted  = TRUE;

    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      switch (recovery_boot_info_ptr->image_set_status)
      {
      case SET_AB_USABLE:
        *set_attempted = FALSE;
        break;

      case DONT_USE_SET_A:
        if (image_set_to_check == BOOT_SET_B)
        {
          *set_attempted = FALSE;
        }
        break;

      case DONT_USE_SET_B:
        if (image_set_to_check == BOOT_SET_A)
        {
          *set_attempted = FALSE;
        }
        break;

      case DONT_USE_SET_AB:
      default:
        *set_attempted = TRUE;
        break;
      }
    }

  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  rbi_info_get_owner

** ==========================================================================
*/
/*!
*
* @brief
*   This api returns owner field
*
*/

recovery_boot_status rbi_info_get_owner (uint32 *owner)
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    if (owner == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      *owner = recovery_boot_info_ptr->owner;
    }
  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  rbi_info_set_owner

** ==========================================================================
*/
/*!
*
* @brief
*   This api sets owner field
*
*/

recovery_boot_status rbi_info_set_owner (uint32 owner)
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      recovery_boot_info_ptr->owner = owner;
    }

    status = rbi_write_partition (recovery_boot_info_ptr);
    if ( status != RBI_SUCCESS)
    {
      break;
    }

  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  rbi_is_boot_select_enabled

** ==========================================================================
*/
/*!
*
* @brief
*   This api returns status of boot_select field
*
*/

recovery_boot_status rbi_is_boot_select_enabled (uint8* is_boot_select_enabled)
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    if (is_boot_select_enabled == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    *is_boot_select_enabled = FALSE;

    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      if (recovery_boot_info_ptr->boot_set.magic == RBI_BOOT_SET_MAGIC)
      {
        *is_boot_select_enabled = TRUE;
      }
    }
  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  rbi_get_boot_select_set

** ==========================================================================
*/
/*!
*
* @brief
*   This api returns status of boot_select field
*
*/
recovery_boot_status rbi_get_boot_select_set (uint32 *selected_set)
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    if (selected_set == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      if (recovery_boot_info_ptr->boot_set.magic == RBI_BOOT_SET_MAGIC)
      {
        *selected_set = recovery_boot_info_ptr->boot_set.selected_set;
      }
      else
      {
        status = RBI_ERR;
      }
    }
  } while (FALSE);

  return status;
}

recovery_boot_status rbi_get_boot_set (uint32 *boot_set)
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {
    if (boot_set == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }
    

    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      if (recovery_boot_info_ptr->image_set_status == DONT_USE_SET_AB)
      {
        *boot_set = BOOT_SET_INVALID;
        goto exit;
      }

      if (recovery_boot_info_ptr->boot_set.magic == RBI_BOOT_SET_MAGIC)
      {
        if ((recovery_boot_info_ptr->boot_set.selected_set == BOOT_SET_A) &&
            (recovery_boot_info_ptr->image_set_status != DONT_USE_SET_A))
        {
          *boot_set = BOOT_SET_A;
        }
        else if ((recovery_boot_info_ptr->boot_set.selected_set == BOOT_SET_A) &&
                 (recovery_boot_info_ptr->image_set_status == DONT_USE_SET_A))
        {
          rbi_log_message ("RBOOT: ignore BS A. not usable");
          *boot_set = BOOT_SET_B;
        }
        else if ((recovery_boot_info_ptr->boot_set.selected_set == BOOT_SET_B) &&
                 (recovery_boot_info_ptr->image_set_status != DONT_USE_SET_B))
        {
          *boot_set = BOOT_SET_B;
        }
        else if ((recovery_boot_info_ptr->boot_set.selected_set == BOOT_SET_B) &&
                 (recovery_boot_info_ptr->image_set_status == DONT_USE_SET_B))
        {
          rbi_log_message ("RBOOT: ignore BS B. not usable");
          *boot_set = BOOT_SET_A;
        }
        else
        {
          *boot_set = BOOT_SET_INVALID;
        }
      }
      else
      {
        if (recovery_boot_info_ptr->image_set_status == SET_AB_USABLE)
        {
          *boot_set = BOOT_SET_A;
        }
        else if (recovery_boot_info_ptr->image_set_status == DONT_USE_SET_B)
        {
          *boot_set = BOOT_SET_A;
        }
        else if (recovery_boot_info_ptr->image_set_status == DONT_USE_SET_A)
        {
          *boot_set = BOOT_SET_B;
        }
        else
        {
          *boot_set = BOOT_SET_INVALID;
        }
      }
    }
  } while (FALSE);

exit:  
  return status;
}

/*=========================================================================

**  Function :  rbi_set_boot_select_set

** ==========================================================================
*/
/*!
*
* @brief
*   This api sets boot_select field and adds magic
*
*/
recovery_boot_status rbi_set_boot_select_set (uint32 selected_boot_set)
{
  recovery_boot_status status = RBI_SUCCESS;
  recovery_boot_info_type *recovery_boot_info_ptr = NULL;

  do
  {

    if ((selected_boot_set != BOOT_SET_A) || (selected_boot_set != BOOT_SET_B))
    {
      status = RBI_ERR;
      break;
    }

    status = rbi_get_recovery_boot_info (&recovery_boot_info_ptr);
    if (status != RBI_SUCCESS)
    {
      break;
    }

    if (recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    if (recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE)
    {
      recovery_boot_info_ptr->boot_set.magic = RBI_BOOT_SET_MAGIC;
      recovery_boot_info_ptr->boot_set.selected_set = selected_boot_set;
    }

    status = rbi_write_partition (recovery_boot_info_ptr);
    if ( status != RBI_SUCCESS)
    {
      break;
    }

  } while (FALSE);

  return status;
}

/*=========================================================================

**  Function :  recoveryinfo_partition_present

** ==========================================================================
*/
/*!
*
* @brief
*   This api returns in partition is present
*
*/

recovery_boot_status recoveryinfo_partition_present (uint8* parition_exists)
{
  *parition_exists = TRUE;
  return RBI_ERR;
}

