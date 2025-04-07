#ifndef RECOVERY_BOOT_INFO_H
#define RECOVERY_BOOT_INFO_H

/*=============================================================================

                           Recover Boot Info 

GENERAL DESCRIPTION
  This file defines Recovery Boot Info api's to support read or write recovery_boot_info to storage

Copyright 2023 Qualcomm Technologies Incorporated.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
03/19/23   vk      Initial revision
=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

/*===========================================================================
                      DATA DECLARATIONS
===========================================================================*/

#define RBI_MAGIC_COOKIE                  (0x72637279UL) /* 'rcry' */
#define RBI_CURRENT_VERSION               (2)

#define RBI_BOOT_SET_MAGIC                (0x6D62U)      /* 'mb' */

#define RBI_PARTITION_ID_MAX_SIZE         16

#define RBI_CRC32_DEFAULT_SEED            0xFFFFFFFFUL
#define RBI_CRC_MAGIC                     0x72637263UL   /* 'rcrc' */


typedef struct  __attribute__((packed)) _boot_set
{
  uint16 magic;
  uint16 selected_set;
} recovery_boot_boot_set_type;

typedef struct  __attribute__((packed)) _recovery_boot_info
{
  uint32 magic_cookie;
  uint32 version;
  uint32 image_set_status;
  uint32 owner;
  recovery_boot_boot_set_type boot_set;    /* uint32 */
  uint32 reserved1;
  uint8  corrupt_id_1 [RBI_PARTITION_ID_MAX_SIZE];
  uint8  corrupt_id_2 [RBI_PARTITION_ID_MAX_SIZE];
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

} recovery_boot_info_type;

recovery_boot_status rbi_get_recovery_boot_info (recovery_boot_info_type **recovery_boot_info_ptr);

recovery_boot_status rbi_write_partition(recovery_boot_info_type *recovery_boot_info_ptr);
recovery_boot_status rbi_log_message (char * message);

#endif
