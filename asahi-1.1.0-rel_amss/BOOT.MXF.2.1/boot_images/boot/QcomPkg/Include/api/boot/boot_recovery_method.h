#ifndef _BOOT_RECOVERY_METHOD_H_
#define _BOOT_RECOVERY_METHOD_H_

/*===========================================================================
Boot Recovery method interface functions

GENERAL DESCRIPTION

Copyright 2023 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================
                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   --------     ------------------------------------------------------
02/20/23   vk           Initial Revision
============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <boot_error_if.h>
#include <boot_partition.h>
#include <RecoveryBootInfoLib.h>
#include <xbl_recovery_boot.h>

/*=============================================================================
            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/

bl_error_boot_type boot_recovery_method_get_pbl_boot_set (boot_image_set_t *actual_set_to_boot, boot_image_set_t *set_expected);
bl_error_boot_type boot_recovery_method_set_pbl_boot_set (boot_image_set_t image_set_to_boot);
bl_error_boot_type boot_recovery_method_get_selection_method (recovery_selection_method_t *recovery_selection_method);

bl_error_boot_type boot_recovery_method_get_pbl_boot_set_gpio (boot_image_set_t *actual_set_to_boot, boot_image_set_t *set_expected);
bl_error_boot_type boot_recovery_method_is_gpio_method_enabled (uint8 *gpio_method_enabled);

#endif /* _BOOT_RECOVERY_METHOD_H_ */
