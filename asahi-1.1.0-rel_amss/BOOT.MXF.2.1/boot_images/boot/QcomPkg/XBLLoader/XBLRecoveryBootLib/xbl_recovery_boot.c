/**
# @file xbl_boot_recovery.c
#
#  Boot Recovery APIs - interface to XBL_SC
#
#  Copyright 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
#
#**/

/*==============================================================================
#                              EDIT HISTORY
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 02/20/23   vk      Initial Revision
#
#==============================================================================*/

#include <string.h>
#include <stdio.h>

#include <HALhwio.h>
#include <HALbootHWIO.h>
#include <boot_config_context.h>
#include <boot_partition.h>
#include <boot_error_if.h>
#include <boot_logger.h>
#include <xbl_recovery_boot.h>
#include <boot_recovery_method.h>
#include <RecoveryBootInfoLib.h>
#include <recovery_boot_info.h>
#include <boot_media_interface_if.h>
#include <boot_reset_if.h>
#include <busywait.h>
#include <boot_crashdump.h>

#define UART_FLUSH_DELAY 3000

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/*=============================================================================
                              LOCAL FUNCTION DECLARATIONS
=============================================================================*/
static bl_error_boot_type xbl_recovery_boot_info_log (recovery_boot_info_type *recoveryinfo_p);
static bl_error_boot_type xbl_recovery_validate_recoveryinfo_data_support (void);
static bl_error_boot_type xbl_recovery_validate_current_pbl_boot_set (boot_image_set_t *pbl_boot_set, boolean* reset_required);

uint32 recoveryinfo_partition_support = FALSE;

/*=============================================================================
                              LOCAL FUNCTION DEFINITIONS
=============================================================================*/

/*=========================================================================

**  Function :  boot_recovery_info_log

** ==========================================================================
*/
/*!
*
* @brief
*   This api dumps recoveryinfo partition data.
*   If NULL param is passed does not access partition
*/
bl_error_boot_type xbl_recovery_boot_info_log (recovery_boot_info_type *rinfo_p)
{
  bl_error_boot_type bl_status = BL_ERR_NONE;
  boot_image_set_t actual_set_to_boot = 0;
  boot_image_set_t set_expected = 0;
  char dbg_info[80];

  bl_status = boot_recovery_method_get_pbl_boot_set (&actual_set_to_boot, &set_expected);
  if (bl_status != BL_ERR_NONE)
  {
    bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_BOOT_SET_UNAVAILABLE);
    goto exit;
  }

  if (actual_set_to_boot == BOOT_SET_A)
  {
    boot_log_message("TCSR_SET: BOOT_SET_A");
  }
  else if (actual_set_to_boot == BOOT_SET_B)
  {
    boot_log_message("TCSR_SET: BOOT_SET_B");
  }

  if (set_expected== BOOT_SET_A)
  {
    boot_log_message("PBLS_SET: BOOT_SET_A");
  }
  else if (set_expected == BOOT_SET_B)
  {
    boot_log_message("PBLS_SET: BOOT_SET_B");
  }

  if (rinfo_p == NULL)
  {
    bl_status = BL_ERR_NONE;
    goto exit;
  }

  snprintf (dbg_info, sizeof(dbg_info), "magic_cookie       0x%x", rinfo_p->magic_cookie);
  boot_log_message(dbg_info);
  snprintf (dbg_info, sizeof(dbg_info), "version            0x%x", rinfo_p->version);
  boot_log_message(dbg_info);
  snprintf (dbg_info, sizeof(dbg_info), "image_set_status   0x%x", rinfo_p->image_set_status);
  boot_log_message(dbg_info);
  snprintf (dbg_info, sizeof(dbg_info), "owner              0x%x", rinfo_p->owner);
  boot_log_message(dbg_info);
  snprintf (dbg_info, sizeof(dbg_info), "magic              0x%x", rinfo_p->boot_set.magic);
  boot_log_message(dbg_info);
  snprintf (dbg_info, sizeof(dbg_info), "selected_set       0x%x", rinfo_p->boot_set.selected_set);
  boot_log_message(dbg_info);
  snprintf (dbg_info, sizeof(dbg_info), "r_crc              0x%x", rinfo_p->recovery_boot_info_crc);
  boot_log_message(dbg_info);
  snprintf (dbg_info, sizeof(dbg_info), "r_crc_enable_magic 0x%x", rinfo_p->recovery_boot_info_crc_enable_magic );
  boot_log_message(dbg_info);

exit:  
  return bl_status;
}

/*=============================================================================

**  Function : xbl_recovery_validate_recoveryinfo_data_support 

** ============================================================================
*/
/*!
*
* @brief
*   This api checks if we have non volatile stoorage support for recoveryinfo data
*/
static bl_error_boot_type xbl_recovery_validate_recoveryinfo_data_support (void)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_media_interface_if_type *media_if = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_handle media_handle = NULL;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;
  const uint8 * recoveryinfo_partition_id = NULL;
  uint8 recoveryinfo_partition_id_size = 0;
  boot_media_type boot_device = NO_FLASH;
  boot_image_set_t current_image_set = IMAGE_SET_MAX;

  do
  {
    status = boot_config_context_get_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
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

    /* Get boot device from config table */
    status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get the current image set */
    status = boot_config_context_get_value (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_CURRENT_IMAGE_SET, (void *)&current_image_set);
    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get the media family */
    status = get_boot_media_family(boot_device, &media_family);
    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get the BootPartitionLib interface pointer */
    status = boot_config_context_get_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_INTERFACE, (void **)&partition_if);
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
    status = partition_if->get_partition_id_by_partition(media_family, current_image_set, RECOVERY_BOOT_INFO_PARTITION, &recoveryinfo_partition_id, &recoveryinfo_partition_id_size);
    if (status != BL_ERR_NONE)
    {
      /* If error is returned then a partition does not exist.
        Clear the error and set the  partition id to null. */
      CLEAR_ERROR_CODE;
      recoveryinfo_partition_id = NULL;
      status = BL_ERR_NONE;
    }

    status = boot_config_context_set_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, (void *)recoveryinfo_partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_media_get_interface (CONFIG_CONTEXT_CRT_HANDLE, media_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (media_if == NULL)
    {
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = media_if->open (CONFIG_CONTEXT_CRT_HANDLE, &media_handle);
    if (status != BL_ERR_NONE)
    {
      boot_log_message ("RBOOT: media open fail");
      status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_FEATURE_UNSUPPORTED);
      break;
    }
    else
    {
      recoveryinfo_partition_support = TRUE;
    }

    status = media_if->close (media_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_set_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, (void *)NULL);
    if (status != BL_ERR_NONE)
    {
      break;
    }
  } while (FALSE);

  if (media_if != NULL)
  {
    mem_if->free(media_if);
    media_if = NULL;
  }

  return status;
}

/*=========================================================================

**  Function :  xbl_recovery_validate_current_pbl_boot_set

** ==========================================================================
*/

static bl_error_boot_type xbl_recovery_validate_current_pbl_boot_set (boot_image_set_t *pbl_boot_set, boolean* reset_required)
{
  bl_error_boot_type bl_status = BL_ERR_NONE;
  recovery_boot_status rstatus = RBI_SUCCESS;
  boot_image_set_t actual_set_to_boot = BOOT_SET_INVALID;
  boot_image_set_t set_expected = BOOT_SET_INVALID;

  /* Check boot set status information from PBL */
  bl_status = boot_recovery_method_get_pbl_boot_set (&actual_set_to_boot, &set_expected);
  if (bl_status != BL_ERR_NONE)
  {
    /* Unable to determine PBL boot set - return error and loader to handle */
    bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY,BL_ERR_PBL_BOOT_SET_ERROR);
    goto exit;
  }

  if (actual_set_to_boot == set_expected)
  {
    boot_log_message ("RBOOT: TCSR in Sync");
    *pbl_boot_set = actual_set_to_boot;
    reset_required = FALSE;
    goto exit;
  }
  else
  {
    boot_log_message ("RBOOT: TCSR not in Sync");
    rstatus = rbi_mark_set_failed (set_expected);
    if (rstatus != RBI_SUCCESS)
    {
      /* Fatal error */
      boot_log_message ("RBOOT: rbi_mark_set_failure");
      bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED);
      reset_required = FALSE;
      goto exit;
    }

    rstatus = rbi_get_boot_set (&actual_set_to_boot);
    if (rstatus != RBI_SUCCESS)
    {
      /* Fatal error */
      boot_log_message ("RBOOT: rbi_get_boot_set failure");
      bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED);
      reset_required = FALSE;
      goto exit;
    }

    if (actual_set_to_boot == BOOT_SET_INVALID)
    {
      /* EDL */
      *reset_required = TRUE;
      bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_BOOT_SET_UNAVAILABLE);
      goto exit;
    }
  }

exit:  
  return bl_status;
}
/*=============================================================================

**  Function :  xbl_recovery_validate_recoveryinfo_boot_set

** ============================================================================
*/

static bl_error_boot_type xbl_recovery_validate_recoveryinfo_boot_set (boot_image_set_t pbl_boot_set, uint8 *reset_required)
{
  bl_error_boot_type bl_status = BL_ERR_NONE;
  recovery_boot_status rstatus = RBI_SUCCESS;
  boot_image_set_t rbi_set_to_boot = BOOT_SET_INVALID;

  rstatus = rbi_get_boot_set (&rbi_set_to_boot);
  if (rstatus != RBI_SUCCESS)
  {
    bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NOT_INITIALIZED);
    goto exit;
  }

  if (rbi_set_to_boot == BOOT_SET_INVALID)
  {
    *reset_required = TRUE;
    bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_BOOT_SET_UNAVAILABLE);
    goto exit;
  }

  if (rbi_set_to_boot == pbl_boot_set)
  {
    /* Continue to boot */
    *reset_required = FALSE;
  }
  else
  {
    bl_status = boot_recovery_method_set_pbl_boot_set (rbi_set_to_boot);
    *reset_required = TRUE;
  }

exit:
  return bl_status;
}


/*=============================================================================
                              PUBLIC FUNCTION DEFINITIONS
=============================================================================*/

/*===========================================================================
**  Function :  xbl_recovery_boot_is_enabled
** ==========================================================================
*/
/*!
*
* @brief
*   This function return TRUE if recovery boot is enabled
* @param[out] recovery boot enabled
*
* @par Dependencies
*   None
*
*/
bl_error_boot_type xbl_recovery_boot_is_enabled (boolean *recovery_boot_enabled_flag)
{
  if (recovery_boot_enabled_flag == NULL)
  {
    return GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
  }

  *recovery_boot_enabled_flag = TRUE; 
  return BL_ERR_NONE;
}

/*===========================================================================
**  Function :  xbl_recovery_boot_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function handles recovery feature init.
*   Init ensures recoveryinfo partition data and TCSR or HWPARTITION
*   selection methods are in sync.
*   Returns error in follwing cases:
*     -- Storage errors after recoveryinfo is present but not writable
*     -- Alternate set not available while trying to keep recoveryinfo  in sync (EDL).
* @param[out] reset required
*
* @par Dependencies
*   None
*
*/
bl_error_boot_type xbl_recovery_boot_init (boolean *reset_required)
{
  bl_error_boot_type bl_status = BL_ERR_NONE;
  recovery_boot_status rstatus = RBI_SUCCESS;
  recovery_boot_info_type *rinfo_part_p = NULL;
  boot_image_set_t pbl_boot_set = BOOT_SET_INVALID;
  uint8 gpio_selection_enabled = FALSE;
  boot_image_set_t set_expected = BOOT_SET_INVALID;
  boot_image_set_t final_image_set_to_boot = BOOT_SET_INVALID;

  /* Check GPIO first */
  bl_status =  boot_recovery_method_is_gpio_method_enabled (&gpio_selection_enabled);
  if (bl_status == BL_ERR_NONE)
  {
    if (gpio_selection_enabled)
    {
      bl_status = boot_recovery_method_get_pbl_boot_set_gpio (&final_image_set_to_boot, &set_expected);
      if (bl_status != BL_ERR_NONE)
      {
        /* Recovery error handle by loader */
        goto exit;
      }
      
      if (final_image_set_to_boot == BOOT_SET_A)
        boot_log_message("RBOOT: GPIO method - SET_A");
      else
        boot_log_message("RBOOT: GPIO method - SET_B");

      /* Update TCSR for init processing to get current set */
      bl_status = boot_recovery_method_set_pbl_boot_set (final_image_set_to_boot);
      if (bl_status != BL_ERR_NONE)
      {
        /* Unable to determine PBL boot set - return error and loader to handle */
        bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY,BL_ERR_PBL_BOOT_SET_ERROR);
        goto exit;
      }

      reset_required = FALSE;
      goto exit;
    }
  }

  /* Log PBL info */
  xbl_recovery_boot_info_log (NULL);

  /* Initial media for recoveryinfo access */
  bl_status =  xbl_recovery_boot_boot_media_early_init(CONFIG_CONTEXT_CRT_HANDLE);
  if (bl_status != BL_ERR_NONE)
  {
    goto exit;
  }


  /* Set default set as BOOT_SET_A - required for getting recoveryinfo ID
   * Once we have parition access this will be set to actual - if there is no partition default to BOOT_SET_A */

  bl_status = boot_config_context_set_value(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_CURRENT_IMAGE_SET, IMAGE_SET_A);
  if (bl_status != BL_ERR_NONE)
  {
    goto exit;
  }

  bl_status = xbl_recovery_validate_recoveryinfo_data_support ();
  if (bl_status != BL_ERR_NONE)
  {
    bl_status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_FEATURE_UNSUPPORTED);
    boot_log_message ("RBOOT: recoveryinfo unavailable");
    goto exit;
  }
  
  rstatus = rbi_get_recovery_boot_info (&rinfo_part_p);
  if ((rstatus == RBI_SUCCESS) && (rinfo_part_p != NULL))
  {
    xbl_recovery_boot_info_log (rinfo_part_p);
  }

  bl_status = xbl_recovery_validate_current_pbl_boot_set (&pbl_boot_set, reset_required);
  if (bl_status != BL_ERR_NONE)
  {
    goto exit;
  }

  bl_status = xbl_recovery_validate_recoveryinfo_boot_set (pbl_boot_set, reset_required);
  if (bl_status != BL_ERR_NONE)
  {
    goto exit;
  }

exit:
  return bl_status;
}

/*===========================================================================
**  Function :  xbl_recovery_boot_mark_set_failed
** ==========================================================================
*/
/*!
*
* @brief
*   This function updates recovery info with failed set
*   Returns error in following cases:
*     -- Storage errors after recoveryinfo is read
*
* @param[in] failed image set to be added in recovery partition
*
* @par Dependencies
*   None
*
*/


bl_error_boot_type xbl_recovery_boot_mark_set_failed (boot_image_set_t failed_image_set)
{
  bl_error_boot_type bl_status = BL_ERR_NONE;
  recovery_boot_status rstatus = RBI_SUCCESS;
  recovery_boot_info_type *rinfo_part_p = NULL;

  if (failed_image_set == BOOT_SET_A)
  {
    boot_log_message ("RBOOT: Mark A Failed");
  }
  else if (failed_image_set == BOOT_SET_B)
  {
    boot_log_message ("RBOOT: Mark B Failed");
  }

  /* Get recoveyinfo data */
  rstatus = rbi_get_recovery_boot_info (&rinfo_part_p);
  if (rstatus != RBI_SUCCESS)
  {
    /* Partition exist, but write failure */
    bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_RECOVERYINFO_WRITE_ERR);
    goto exit;
  }

  rstatus = rbi_mark_set_failed (failed_image_set);
  if (rstatus != RBI_SUCCESS)
  {
    /* Partition exist, but write failure */
    bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_RECOVERYINFO_WRITE_ERR);
    goto exit;
  }

exit:
  return bl_status;
}


/*===========================================================================
**  Function :  xbl_recovery_boot_get_selection_method
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns selection method. Implemented in abstract library.
*   Returns error in following cases:
*     -- Storage errors after recoveryinfo is read
*
* @param[in] failed image set to be added in recovery partition
*
* @par Dependencies
*   None
*
*/

bl_error_boot_type xbl_recovery_boot_get_selection_method (recovery_selection_method_t *selection_method)
{
  if (selection_method == NULL)
  {
    return BL_ERR_NULL_PTR_PASSED;
  }

  return boot_recovery_method_get_selection_method (selection_method);
}

/*=============================================================================
**  Function :  xbl_recovery_boot_get_current_boot_set
** ============================================================================
*/
/*!
*
* @brief
*   This function returns the current active boot set
*
* @param[out] current image set
*
* @par Dependencies
*   None
*
*/

bl_error_boot_type xbl_recovery_boot_get_current_boot_set (boot_image_set_t *current_boot_set)
{
  bl_error_boot_type bl_status = BL_ERR_NONE;
  boot_image_set_t current_image_set = BOOT_SET_INVALID;
  boot_image_set_t expected_set = BOOT_SET_INVALID;

  if (current_boot_set == NULL)
  {
    bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  bl_status = boot_recovery_method_get_pbl_boot_set (&current_image_set, &expected_set);
  if ((bl_status != BL_ERR_NONE))
  {
    bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_PBL_BOOT_GET_ERROR);
    *current_boot_set = BOOT_SET_INVALID;
    goto exit;
  }

  *current_boot_set = current_image_set;

exit:
  return bl_status;
}

/*=============================================================================
**  Function :  xbl_recovery_boot_handle_load_failure
** ============================================================================
*/
/*!
*
* @brief
*   This function handles image load failures
*
* @par Dependencies
*   None
*
*/

bl_error_boot_type xbl_recovery_boot_handle_load_failure (boot_handle config_context_handle)
{
  bl_error_boot_type bl_status = BL_ERR_NONE;
  boot_image_set_t current_image_set = BOOT_SET_INVALID;
  recovery_selection_method_t selection_method = 0;
  uint8 gpio_selection_method = FALSE;

  bl_status = boot_recovery_method_is_gpio_method_enabled (&gpio_selection_method);
  if (bl_status != BL_ERR_NONE)
  {
    /* Storage error - handle in upper layer */
    bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_GPIO_ERR);
    goto exit;
  }

  /* If GPIO ased selction, do not process recoveryinfo data */
  if (gpio_selection_method == TRUE)
  {
    selection_method = RECOVERY_SELECT_GPIO;
  }
  else if (gpio_selection_method == FALSE)
  {
    if (recoveryinfo_partition_support == FALSE)
    {
      goto exit;
    }

    bl_status = xbl_recovery_boot_get_current_boot_set (&current_image_set);
    if (bl_status != BL_ERR_NONE)
    {
      /* Storage error - handle in upper layer */
      bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_PBL_BOOT_GET_ERROR);
      goto exit;
    }

    bl_status = xbl_recovery_boot_mark_set_failed (current_image_set);
    if (bl_status != BL_ERR_NONE)
    {
      /* Storage error - handle in upper layer */
      bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_SET_SELECTION_ERROR);
      goto exit;
    }
 
    bl_status = xbl_recovery_boot_get_selection_method (&selection_method);
    if (bl_status != BL_ERR_NONE)
    {
      /* Unable to determine selection method - handle in upper layer */
      bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_INTERFACE_FAILURE);
      goto exit;
    }
  }

  if (selection_method == RECOVERY_SELECT_TCSR)
  {
    /* Can be handled by HARD reset because we have set information in non voaltile memory */
    boot_log_message ("RBOOT: HARD RESET");
    busywait (UART_FLUSH_DELAY);
    boot_hw_reset (BOOT_HARD_RESET_TYPE);
  }
  else if (selection_method == RECOVERY_SELECT_HW_PARTITION)
  {
    boot_log_message ("RBOOT: HARD RESET");
    busywait (UART_FLUSH_DELAY);
    boot_hw_reset (BOOT_HARD_RESET_TYPE);
  }
  else if (selection_method == RECOVERY_SELECT_GPIO)
  {
    boot_log_message ("RBOOT: EDL");
    busywait (UART_FLUSH_DELAY);
   
    boot_dload_transition_pbl_forced_dload (config_context_handle);
  }

exit:
  return bl_status;
}

/*===========================================================================
**  Function :  xbl_recovery_boot_boot_media_early_init
** ==========================================================================
*/
/*!
*
* @brief
*   This is a weak function used to initialize boot_media init required for recoveryinfo access
*
* @par Dependencies
*   None
*
*/

bl_error_boot_type  __attribute__ ((weak)) xbl_recovery_boot_boot_media_early_init(boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}
