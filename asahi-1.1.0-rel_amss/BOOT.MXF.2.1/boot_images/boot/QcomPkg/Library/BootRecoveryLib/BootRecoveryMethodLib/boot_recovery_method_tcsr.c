/**
# @file boot_recovery_method_tcsr.c
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
**  Function :  boot_recovery_method_get_pbl_boot_set
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the actual set PBL booted from shared via PBL 
*   shared data and also returns the TCSR value inidicating the set PBL
*   was asked to boot form. 
*   Returns error in following cases:
*     -- Storage errors after recoveryinfo is read
*
* @param[in] actual_set_to_boot - PBL Shared data
*            set_expected - TCSR value of boot set  
*
* @par Dependencies
*   None
*
*/ 
bl_error_boot_type boot_recovery_method_get_pbl_boot_set (boot_image_set_t *actual_set_to_boot, boot_image_set_t *set_expected)
{
  #define HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_BMSK 0x80000000
  #define HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_SHFT 31

  bl_error_boot_type status = BL_ERR_NONE;
  boot_pbl_shared_data_if_type * pbl_shared_data_if = NULL;
  uintnt is_xbl_booted_from_set_a_or_b = 0;
  uint32 tcsr_image_set_to_boot = BOOT_SET_INVALID;

  if ((actual_set_to_boot == NULL) || (set_expected == NULL))
  {
    status = BL_ERR_INVALID_PARAMETER;
    goto exit;
  }

  /* Get image_set from TCSR */
  tcsr_image_set_to_boot = (HWIO_TCSR_TCSR_BOOT_INFO_IN & HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_BMSK) >> HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_SHFT;
  *actual_set_to_boot = tcsr_image_set_to_boot;

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
  
  *set_expected = (boot_image_set_t)is_xbl_booted_from_set_a_or_b;

exit:
  return status;
}


/*===========================================================================
**  Function :  boot_recovery_method_set_pbl_boot_set
** ==========================================================================
*/
/*!
* 
* @brief
*   This function sets tcsr cookie for PBL to select boot set
*
* @param[in] IMAGE_SET PBL shoudl boot from
*
* @par Dependencies
*   None
*
*/ 

bl_error_boot_type boot_recovery_method_set_pbl_boot_set (boot_image_set_t image_set_to_boot)
{
/* For targerts that use cookie in OCIMEM instead of TCSR */
#ifdef BOOT_RECOVERY_USE_OCIMEM_COOKIE   
#define PBL_MAGIC_DO_NOT_CLEAR_OCIMEM_AB_VALUE 0x3CA5965A
#define PBL_MAGIC_DO_NOT_CLEAR_OCIMEM_AB_ADDR  0x146ABFF8 

  /* PBL required magic to not clean the set at PBL exit */
  out_dword(PBL_MAGIC_DO_NOT_CLEAR_OCIMEM_AB_ADDR, PBL_MAGIC_DO_NOT_CLEAR_OCIMEM_AB_VALUE);
#endif  

  /* Update TCSR with image set */
  HWIO_TCSR_TCSR_BOOT_INFO_OUTM(HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_BMSK, image_set_to_boot << HWIO_TCSR_TCSR_BOOT_INFO_IMAGE_SET_TO_BOOT_SHFT);
  
  return BL_ERR_NONE;
}

/*===========================================================================
**  Function :  boot_recovery_method_get_selection_method
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns selection method
*
* @par Dependencies
*   None
*
*/
bl_error_boot_type boot_recovery_method_get_selection_method (recovery_selection_method_t *recovery_selection_method)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if (recovery_selection_method == NULL)
  {
    status = BL_ERR_INVALID_PARAMETER;
    goto exit;
  }

  *recovery_selection_method = RECOVERY_SELECT_TCSR;

exit:  
  return status;
}

