#ifndef TRIAL_BOOT_INFO_H
#define TRIAL_BOOT_INFO_H

/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file defines Trial Boot Info api's to support read or write trial_boot_info to storage

Copyright 2022 Qualcomm Technologies Incorporated.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
05/27/21   sp      Initial Revision
=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

/*===========================================================================
                      DATA DECLARATIONS
===========================================================================*/
#define TBI_MAGIC_COOKIE      0x74726269
#define TBI_VERSION           0x1
#define TBI_MAX_ATTEMPTS      6+1 /* 6: Total number of trial boots, +1: as boot count starts from 1 */
#define TBI_ENABLE_TRIAL_BOOT 0x1
#define TBI_ENABLE_PARTITION_TABLE_RESTORE 0x1

typedef struct {
  uint32 magic_cookie;
  uint32 version;
  uint32 trial_boot_enable;
  uint32 trial_boot_max_attempts;
  uint32 trial_boot_failed_attempts;
  uint32 partition_table_restore_enable;
  uint32 partition_table_restore_status;
  uint32 image_set_to_boot;
}trial_boot_info_type;

trial_boot_status tbi_get_trial_boot_info(trial_boot_info_type **trial_boot_info_ptr);

trial_boot_status tbi_write_partition(trial_boot_info_type *trial_boot_info_ptr);


#endif