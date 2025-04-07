/**
# @file boot_recovery_method_wlun.c
#
#  Boot Recovery External Interface APIs - interface to get boot info from external sources
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
#include <xbl_recovery_boot.h>
#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_config.h>
#include <boot_logger.h>
#include <boot_reset_if.h>
#include <busywait.h>


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
bl_error_boot_type boot_recovery_get_pbl_boot_set (boot_image_set_t *actual_set_to_boot, boot_image_set_t *set_expected)
{
  //media_if_ioctl
  return BL_ERR_NONE;
}

bl_error_boot_type boot_recovery_set_pbl_boot_set (boot_image_set_t image_set_to_boot)
{
  return BL_ERR_NONE;
}

bl_error_boot_type boot_recovery_method_get_selection_method (recovery_selection_method_t *recovery_selection_method)
{
  *recovery_selection_method = RECOVERY_SELECT_HW_PARTITION;
  return BL_ERR_NONE;
}

