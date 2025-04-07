/**
# @file BootRecoverySmemLibNull.c
#
#  BootRecoverySmemLibNull
#
#  Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
#
#**/

/*==============================================================================
#                              EDIT HISTORY
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 06/28/21   sp  Initial Revision
#
#==============================================================================*/

#include <boot_recovery_partition.h>

boot_recovery_status boot_recovery_add_recovery_info(uint8 *partition_id, uint8 *recovery_partition_id, uint64 last_reported_errorcode, uint32 flags)
{
  return BOOT_RECOVERY_ERROR_NONE;
}