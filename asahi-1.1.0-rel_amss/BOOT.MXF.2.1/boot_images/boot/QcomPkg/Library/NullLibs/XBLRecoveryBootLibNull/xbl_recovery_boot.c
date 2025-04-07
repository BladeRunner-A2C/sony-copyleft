/**
# @file xbl_recovery_boot.c
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
#include <stdio.h>
#include <string.h>
#include <boot_config_context.h>
#include <boot_partition.h>
#include <boot_error_if.h>
#include <boot_logger.h>
#include <boot_shared_imem_cookie.h>

#include <xbl_recovery_boot.h>
#include <boot_recovery_method.h>
#include <RecoveryBootInfoLib.h>
#include <recovery_boot_info.h>
/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/*=============================================================================
                              LOCAL FUNCTION DECLARATIONS
=============================================================================*/

/*=============================================================================
                              LOCAL FUNCTION DEFINITIONS
=============================================================================*/



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

  *recovery_boot_enabled_flag = FALSE; 

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
*     -- Storage errors after recoveryinfo is read
*     -- Alternate set not available while trying to keep recoveryinfo  in sync (EDL).
* @param[out] reset required
*
* @par Dependencies
*   None
*
*/
bl_error_boot_type xbl_recovery_boot_init (boolean *reset_required)
{
  return BL_ERR_NONE;
}

/*===========================================================================
**  Function :  xbl_recovery_boot_get_boot_set
** ==========================================================================
*/
/*!
*
* @brief
*   This function provides a bootable set.
*   Returns error in following cases:
*     -- Storage errors after recoveryinfo is read
*
* @param[out] image set to boot
*
* @par Dependencies
*   None
*
*/

bl_error_boot_type xbl_recovery_boot_get_boot_set (boot_image_set_t *image_set_to_boot)
{
  if (image_set_to_boot == NULL)
  {
    return GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
  }

  *image_set_to_boot = BOOT_SET_A;

  /* Update Shared IMEM with final boot set */
  if (boot_shared_imem_cookie_ptr != NULL)
  {
    boot_shared_imem_cookie_ptr->boot_set_type = (uint16)BOOT_SET_A;
  }

  return BL_ERR_NONE;
}
/*===========================================================================
**  Function :  recovery_boot_mark_set_failed
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
  return BL_ERR_NONE;
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
  return BL_ERR_NONE;  
}

/*===========================================================================
**  Function :  xbl_recovery_boot_boot_media_early_init
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

bl_error_boot_type  __attribute__ ((weak)) xbl_recovery_boot_boot_media_early_init(boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}

bl_error_boot_type xbl_recovery_boot_get_current_boot_set (boot_image_set_t *current_boot_set)
{
  return BL_ERR_NONE;  
}

bl_error_boot_type xbl_recovery_boot_handle_load_failure (boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}  
