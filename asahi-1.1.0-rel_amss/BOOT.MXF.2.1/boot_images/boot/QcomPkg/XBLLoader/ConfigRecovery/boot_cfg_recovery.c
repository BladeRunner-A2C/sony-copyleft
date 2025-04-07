/*=============================================================================

                            ConfigRecovery Module Sources

GENERAL DESCRIPTION
  This file defines XBL Config Recovery api's

Copyright 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
03/08/23     sp      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include <boot_error_if.h>
#include <boot_cfg_recovery.h>
#include <boot_recovery_lun.h>

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/
bl_error_boot_type cfg_image_error_handler_recovery()
{
  bl_error_boot_type status = BL_ERR_NONE;
  status = boot_recovery_load_recovery_lun(CONFIG_CONTEXT_CRT_HANDLE, NULL);
  return status;
}

bl_error_boot_type cfg_select_partition(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}

bl_error_boot_type cfg_item_add_partitioninfo_to_smem()
{
  bl_error_boot_type status = BL_ERR_NONE;
  return status;
}