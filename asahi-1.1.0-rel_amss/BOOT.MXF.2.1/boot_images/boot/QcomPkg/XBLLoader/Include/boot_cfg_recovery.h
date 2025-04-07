#ifndef BOOT_CFG_RECOVERY_H
#define BOOT_CFG_RECOVERY_H

/*=============================================================================

GENERAL DESCRIPTION
  This file defines ConfigRecovery api's.

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

#include <boot_error_if.h>
#include <boot_config_context.h>

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/
/*===========================================================================
**  Function :  cfg_image_error_handler_recovery
** ==========================================================================
*/
/*!
*
* @brief
*   This function clears first 4 bytes in the storage partition upon failure and does hard reset.
*   So on the next boot loader loads the image from secondary partition by calling cfg_select_partition api
*
* @param[in]
*  None
*
* @param[out]
*  None
*
* @par Dependencies
*   None
*
* @retval
*   status = BL_ERR_NONE if no error, else error value
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type cfg_image_error_handler_recovery();

/*===========================================================================
**  Function :  cfg_select_partition
** ==========================================================================
*/
/*!
*
* @brief
*   This function selects the xbl config primary/secondary partition by reading the first 4 bytes from storage partition and checking the elf value
*
* @param[in]
*  config_context_handle
*
* @param[out]
*  None
*
* @par Dependencies
*   None
*
* @retval
*   status = BL_ERR_NONE if no error, else error value
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type cfg_select_partition(boot_handle config_context_handle);

/*===========================================================================
**  Function :  cfg_item_add_partitioninfo_to_smem
** ==========================================================================
*/
/*!
*
* @brief
*   This function copies good and corrupted partition ids to smem
*
* @retval
*   config_status_type   Status of operation
*
*/
bl_error_boot_type cfg_item_add_partitioninfo_to_smem();

#endif /* BOOT_CFG_RECOVERY_H */