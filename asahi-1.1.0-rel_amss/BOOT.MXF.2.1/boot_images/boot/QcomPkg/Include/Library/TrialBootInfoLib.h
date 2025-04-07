#ifndef TBI_BOOT_INFO_H
#define TBI_BOOT_INFO_H

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
05/27/22   sp      Initial Revision
=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <com_dtypes.h>

#define PARTITION_TABLE_RESTORE_INPROGRESS 0x1
#define PARTITION_TABLE_RESTORE_COMPLETE 0x2

/*===========================================================================
                      DATA DECLARATIONS
===========================================================================*/
#define ENABLE_PARTITION_TABLE_RESTORE 0x1

typedef enum
{
  TBI_SUCCESS                = 0x0000,
  TBI_READ_ERR               = 0x0001,
  TBI_WRITE_ERR              = 0x0002,
  TBI_NULL_PTR               = 0x0003,
  TBI_MAX_ATTEMPTS_REACHED   = 0x0004,
  TBI_ERR                    = 0x7FFF
} trial_boot_status;

typedef enum
{
  READ_TBI,
  WRITE_TBI
} tbi_rw_type;

/*===========================================================================

                      FUNCTION DECLARATIONS

===========================================================================*/

trial_boot_status tbi_init(void);

trial_boot_status tbi_enable_trial_boot(uint8 enable_partition_table_restore);

trial_boot_status tbi_is_trial_boot_enabled (uint8 *is_trial_boot_enabled);

trial_boot_status tbi_is_trial_boot_failed(uint8 *is_trial_boot_failed);

trial_boot_status tbi_rw_curr_failed_attempts(uint32 *trial_boot_failed_attempts, tbi_rw_type rw_type);

trial_boot_status tbi_increment_failed_boot_attempts(void);

trial_boot_status tbi_induce_trial_boot_failure(void);

trial_boot_status tbi_get_max_boot_attempts(uint32 *trial_boot_max_attempts);

trial_boot_status tbi_is_partition_table_restore_enabled (uint32 *is_recovery_partition_restore_enabled);

trial_boot_status tbi_get_partition_table_restore_status (uint32 *restore_status);

trial_boot_status tbi_update_partition_table_restore_status(uint32 restore_status);

trial_boot_status tbi_get_image_set_to_boot (uint32 *image_set);

trial_boot_status tbi_clear_partition(void);


#endif