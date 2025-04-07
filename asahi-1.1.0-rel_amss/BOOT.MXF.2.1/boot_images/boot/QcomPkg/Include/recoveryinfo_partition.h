/**
# @file recoveryinfo.h
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
# 02/20/23   vk      Initial Revision
#
#==============================================================================*/

#ifndef __RECOVERYINFO_H_
#define __RECOVERYINFO_H_

#include <boot_error_if.h>

/* -------------------------- Recovery Boot -------------------------------- */
#define RECOVERY_INFO_MAGIC           (0x72637279UL) /* 'rcry' */
#define RECOVERY_INFO_CURRENT_VERSION (2)

#define SET_AB_USABLE                 (0x0UL)
#define DONT_USE_SET_A                (0x1UL)
#define DONT_USE_SET_B                (0x2UL)
#define DONT_USE_SET_AB               (0x3UL)

#define OWNER_XBL                     (1)
#define BOOT_SET_MAGIC                (0x6D62U)      /* 'mb' */

#define PARTITION_ID_MAX_SIZE         16

typedef struct  __attribute__((packed)) _bl_boot_set
{
  uint16 magic;
  uint16 boot_set;
} bl_recovery_boot_boot_set_type;


typedef struct  __attribute__((packed)) _bl_recovery_boot_info
{
  uint32 magic;
  uint32 version;
  uint32 bank_status;
  uint32 owner;
  bl_recovery_boot_boot_set_type boot_set;     /* uint32 */
  uint32 reserved1;
  uint8  corrupt_id_1 [PARTITION_ID_MAX_SIZE];
  uint8  corrupt_id_2 [PARTITION_ID_MAX_SIZE];
  uint32 reserved2;
  uint32 reserved3;
  uint32 reserved4;
  uint32 reserved5;
  uint32 reserved6;
  uint32 reserved7;
  uint32 reserved8;
  uint32 reserved9;
  
  /* CRC fields for fields above */
  uint32 recovery_boot_info_crc;
  uint32 recovery_boot_info_crc_enable_magic;  /* rcrc */
  
} bl_recovery_boot_info_type;


/* -------------------------- Trial Boot -------------------------------- */
#define TBI_MAGIC_COOKIE      0x74726269
#define TBI_VERSION           0x1
#define TBI_MAX_ATTEMPTS      6+1 /* 6: Total number of trial boots, +1: as boot count starts from 1 */
#define TBI_ENABLE_TRIAL_BOOT 0x1
#define TBI_ENABLE_PARTITION_TABLE_RESTORE 0x1

typedef struct __attribute__((packed)) _bl_trial_boot_info
{
  uint32 magic_cookie;
  uint32 version;
  uint32 trial_boot_enable;
  uint32 trial_boot_max_attempts;
  uint32 trial_boot_failed_attempts;
  uint32 partition_table_restore_enable;
  uint32 partition_table_restore_status;
  uint32 image_set_to_boot;
  uint32 trial_boot_info_crc;
  uint32 trial_boot_info_crc_enable_magic;          /* tcrc */
}bl_trial_boot_info_type;


/* ----------------- RecoveryInfo Partition Layout ------------------------- */
typedef struct __attribute__((packed)) _recoveryinfo_
{
  bl_recovery_boot_info_type recovery_boot_info;
  bl_trial_boot_info_type    trial_boot_info;
} bl_recoveryinfo_partition_t;


/* ----------------- RecoveryInfo Info Access APIs ------------------------- */
bl_error_boot_type recoveryinfo_get_recoveryinfo (bl_recovery_boot_info_type **recovery_boot_info_ptr);
bl_error_boot_type recoveryinfo_set_recoveryinfo (bl_recovery_boot_info_type *recovery_boot_info_ptr);

bl_error_boot_type recoveryinfo_get_trialbootinfo (bl_trial_boot_info_type **trialbootinfo_boot_info_ptr);
bl_error_boot_type recoveryinfo_set_trialbootinfo (bl_trial_boot_info_type *trialbootinfo_boot_info_ptr);
#endif
