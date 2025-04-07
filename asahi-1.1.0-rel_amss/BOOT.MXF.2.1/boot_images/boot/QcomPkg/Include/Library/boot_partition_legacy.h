#ifndef BOOT_PARTITION_LEGACY_H
#define BOOT_PARTITION_LEGACY_H

/*=============================================================================

                            XBL TRIALBOOT Module Sources

GENERAL DESCRIPTION
  This file defines Boot patition Lib api's.

Copyright 2022 - 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
02/15/23     suhas   Removed boot_set_partition_ids and boot_set_recovery_partition_ids_to_null
01/10/23     suhas   Renamed the file to boot_partition_legacy.h
11/21/22     sp      Initial version
===========================================================================*/

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/

#include <boot_error_if.h>
#include <boot_config_context.h>

typedef enum
{
  /* Partition IDs */
  TRIALBOOTINFO_PARTITION_ID,
  /* Only add partition ids before this point */
  /* Partition IDs for Partition table restore */
  PARTITION_TABLE_RESTORE_PARTITION_ID,
  PARTITION_TABLE_RESTORE_MAX,
  BOOT_PARTITION_ID_MAX = 0x7FFF,
} boot_partition_id;

typedef enum
{
  SET_A,
  SET_B,
}boot_partition_set;

typedef struct partition_table_restore_ioctl_params
{
  void *handle;
  uint8 *restore_partition_id;
}partition_table_restore_ioctl_params;

bl_error_boot_type boot_media_restore_partition_table(boot_handle config_context_handle);

#endif