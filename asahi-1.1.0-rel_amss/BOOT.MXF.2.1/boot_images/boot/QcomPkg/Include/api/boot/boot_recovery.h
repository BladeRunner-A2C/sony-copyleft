#ifndef _BOOT_RECOVERY_H_
#define _BOOT_RECOVERY_H_

/*===========================================================================
                                Boot Recovery Public Interface

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
#include <recoveryinfo_partition.h>
#include <boot_partition.h>

typedef enum
{
  RECOVERY_SELECT_NONE = 0,
  RECOVERY_SELECT_TCSR = 1,          /* Use TCSR */
  RECOVERY_SELECT_HW_PARTITION = 2,  /* Use HW partition information - eMMC BOOT, USER partition, UFS: WLUN1, WLUN2 */
  RECOVERY_SELECT_MAX
}recovery_selection_method_t;

typedef enum
{
  RECOVERY_SET_NOT_ATTEMPTED = 0,
  RECOVERY_SET_ATTEMPTED = 1,
  RECOVERY_SET_MAX,
} recovery_set_attempted_t;

/*=============================================================================
            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.
=============================================================================*/

bl_error_boot_type boot_recovery_init2 (boolean *reset_required);
bl_error_boot_type recovery_boot_get_boot_set (boot_image_set_t *image_set_to_boot);
bl_error_boot_type recovery_boot_mark_set_failed (boot_image_set_t failed_image_set);
bl_error_boot_type recovery_boot_get_selection_method (recovery_selection_method_t *selection_method);
bl_error_boot_type recovery_boot_check_set_attempted (boot_image_set_t check_image_set, recovery_set_attempted_t *set_status);

#endif /* _BOOT_RECOVERY_H_ */
