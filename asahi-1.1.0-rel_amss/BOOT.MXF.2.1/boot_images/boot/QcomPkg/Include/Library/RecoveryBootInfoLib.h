/**
# @file RecoveryBootInfoLib.h
#
#  Boot recoveryinfo partition structure
#  Recovery info and trial boot info structure layout in recoveryinfo partition
#
#  Copyright 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
#
#**/

/*==============================================================================
#                              EDIT HISTORY
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 03/17/23   vk      Initial Revision
#
#==============================================================================*/

#ifndef __RECOVERY_BOOT_INFO_LIB_H__
#define __RECOVERY_BOOT_INFO_LIB_H__

#include <com_dtypes.h>

/* -------------------------- Recovery Boot -------------------------------- */

typedef enum
{
  RBI_SUCCESS                = 0x0000,
  RBI_READ_ERR               = 0x0001,
  RBI_WRITE_ERR              = 0x0002,
  RBI_NULL_PTR               = 0x0003,
  RBI_MAGIC_READ_FAIL        = 0x0004,
  RBI_PARTITION_CRC_FAIL     = 0x0005,
  RBI_PARTITION_NOT_PRESENT  = 0x0006,
  RBI_ERR                    = 0x7FFF
} recovery_boot_status;

/* image_set_status*/
#define SET_AB_USABLE       (0x0UL)
#define DONT_USE_SET_A      (0x1UL)
#define DONT_USE_SET_B      (0x2UL)
#define DONT_USE_SET_AB     (0x3UL)

/* owner */
#define OWNER_XBL           (1)
#define OWNER_HLOS          (2)
#define OWNER_UEFI          (3)
#define OWNER_ABL           (4)

/* boot_select_set */
#define BOOT_SET_INVALID    (0xFFFF)
#define BOOT_SET_A          (0x0U)
#define BOOT_SET_B          (0x1U)

/* -------- RecoveryInfo Info Access APIs ------------------------- */
recovery_boot_status recoveryinfo_partition_present (uint8* parition_exists);
recovery_boot_status rbi_reset (void);

recovery_boot_status rbi_info_get_image_set_status (uint32 *boot_set_status);
recovery_boot_status rbi_is_image_set_attempted (uint32 boot_set, uint8* set_attempted);

recovery_boot_status rbi_info_get_owner (uint32 *boot_set);
recovery_boot_status rbi_info_set_owner (uint32 boot_set);

recovery_boot_status rbi_is_boot_select_enabled (uint8* is_boot_select_enabled);
recovery_boot_status rbi_get_boot_select_set (uint32 *selected_set);
recovery_boot_status rbi_set_boot_select_set (uint32 selected_set);

recovery_boot_status rbi_get_boot_set (uint32 *boot_set);
recovery_boot_status rbi_mark_set_failed (uint32 failed_image_set);

#endif
