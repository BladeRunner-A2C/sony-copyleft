/**
# @file boot_recovery_method_gpio.c
#
#  Boot Recovery Method GPIO APIs
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
#include <HALhwio.h>
#include <HALbootHWIO.h>
#include <HALOcimemTcsrHWIO.h>
#include <xbl_recovery_boot.h>
#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_config.h>
#include <boot_logger.h>
#include <pbl_sbl_shared.h>

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
**  Function :  boot_recovery_method_is_gpio_method_enabled
** ==========================================================================
*/
/*!
* 
* @brief
*   This function is used to query if GPIO based set selection is enabled.
*
* @par Dependencies
*   None
*
*/ 
bl_error_boot_type boot_recovery_method_is_gpio_method_enabled (uint8 *gpio_boot_select_enabled_flag)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint32 oem_config0_pbl_enable_ab_sel = 0;

  if (gpio_boot_select_enabled_flag == NULL)
  {
    status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  /* Get fuse value to determine if GPIO base set selection is enabled */
  oem_config0_pbl_enable_ab_sel = (HWIO_OEM_CONFIG0_IN & HWIO_OEM_CONFIG0_PBL_ENABLE_AB_SEL_BMSK) >> HWIO_OEM_CONFIG0_PBL_ENABLE_AB_SEL_SHFT;
  if (oem_config0_pbl_enable_ab_sel)
  {
    *gpio_boot_select_enabled_flag = TRUE;
  }
  else
  {
    *gpio_boot_select_enabled_flag = FALSE;
  }
  
exit:
  return status;
}


/*===========================================================================
**  Function :  boot_recovery_method_get_pbl_boot_set_gpio
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the boot set as indicated by GPIO
*
* @par Dependencies
*   None
*
*/ 
bl_error_boot_type boot_recovery_method_get_pbl_boot_set_gpio (boot_image_set_t *actual_set_to_boot, boot_image_set_t *set_expected)
{

  bl_error_boot_type status = BL_ERR_NONE;
  boot_pbl_shared_data_if_type * pbl_shared_data_if = NULL;
  uintnt is_xbl_booted_from_set_a_or_b = 0;

  if ((actual_set_to_boot == NULL) || (set_expected == NULL))
  {
    status = GET_ERROR_CODE (BL_ERROR_GROUP_BOOT_RECOVERY, BL_ERR_NULL_PTR_PASSED);
    goto exit;
  }

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PBL_SHARED_DATA_INTERFACE, (void **)&pbl_shared_data_if);
  if (status != BL_ERR_NONE || pbl_shared_data_if == NULL)
  {
    goto exit;
  }

  /* Get boot set from PBL shared data value does not match */
  status = pbl_shared_data_if->get_value(PBL_APPS_XBL_SHARED_DATA_PARAM_ID_CURRENT_IMAGE_SET, (uintnt *)&is_xbl_booted_from_set_a_or_b);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }
 
  *actual_set_to_boot = (boot_image_set_t)is_xbl_booted_from_set_a_or_b; 
  *set_expected = (boot_image_set_t)is_xbl_booted_from_set_a_or_b;

  exit:
    return status;
}

