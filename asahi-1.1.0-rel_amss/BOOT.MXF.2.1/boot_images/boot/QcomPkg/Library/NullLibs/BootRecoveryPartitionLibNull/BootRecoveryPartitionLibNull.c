/**
# @file BootRecoveryPartitionLibNull.c
#
#  BootRecoveryPartitionLibNull
#
#  Copyright 2021, 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
#
#**/

/*==============================================================================
#                              EDIT HISTORY
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 02/20/23   suhas   Updating file for BootPartitionLib
# 01/25/21   sp      Initial Revision
#
#==============================================================================*/

#include <boot_config_context.h>
#include <boot_recovery_partition.h>
#include <boot_error_if.h>
#include <boot_logger_if.h>

bl_error_boot_type boot_recovery_init(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}

boolean boot_recovery_is_recovery_enabled(void)
{
  return FALSE;
}

boolean boot_recovery_is_booting_from_recovery_partition(uint8 *partition_id, uint8 *recovery_partition_id)
{
  return FALSE;
}

bl_error_boot_type boot_recovery_partitions_info_smem_init(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}

bl_error_boot_type boot_recovery_add_recovery_info_internal(uint8 *partition_id, uint8 *recovery_partition_id, uint64 error_code, uint32 flags)
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}

bl_error_boot_type boot_recovery_partitions_info_imem_init(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}

bl_error_boot_type boot_load_recovery_image(boot_handle config_context_handle, uint8 *recovery_partition_id)
{
  bl_error_boot_type status = GET_ERROR_INFO;
  return status;
}

bl_error_boot_type boot_recovery_load_recovery_lun(boot_handle config_context_handle, uint8 *recovery_partition_id)
{
  bl_error_boot_type status = GET_ERROR_INFO;
  return status;
}

bl_error_boot_type boot_recovery_select_boot_partitions (boot_handle config_context_handle)
{
  return BL_ERR_NONE;
}

bl_error_boot_type boot_recovery_update_corrupt_patition_id (boot_handle config_context_handle, uint8 *partition_id)
{
  return BL_ERR_NONE;
}

bl_error_boot_type boot_recovery_is_partition_valid(boot_handle config_context_handle, uint8 *partition_id)
{
  return BL_ERR_NONE;
}
