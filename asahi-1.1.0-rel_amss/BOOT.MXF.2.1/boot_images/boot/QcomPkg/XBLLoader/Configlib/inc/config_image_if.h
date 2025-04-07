#ifndef CONFIG_IMAGE_IF_H
#define CONFIG_IMAGE_IF_H
/*=============================================================================

                      ConfigLib Image Interface Module Sources

GENERAL DESCRIPTION
  This file defines ConfigLib api's that interface with Elf image
  load module.

Copyright 2016, 2017, 2020-2021, 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
04/13/23     yps      Added cfg_ram_addr_image_interface and cfg_storage_addr_image_interface
09/08/21     tmt      Port to QDSP -> ConfigLib
10/16/20     rama     Added xcfg_image_interface table.
03/27/17     kpa      Added xcfg_image_interface_reset
03/03/17     kpa      Added xcfg_load_addr_validation_init, deinit
02/14/17     kpa      Rename XBLCONFIG_ERR_NONE to XBLCONFIG_SUCCESS
                      added xcfg_validate_data
10/14/16     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "cfg_item_config.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/


/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/
typedef struct cfg_image_interface_type{
    config_status_type (*init)(void);
    config_status_type (*get_max_logical_block_count)(uintnt *);
    config_status_type (*get_block_info)(uintnt, uintnt *, uintnt *);
    config_status_type (*get_block_data)(uintnt, uintnt, void *, boot_boolean);
    config_status_type (*deinit)(void);
    config_status_type (*reset)(void);
    config_status_type (*get_metadata_size)(uint32 *);
  config_status_type (*cfg_error_handler)(uint32);
}cfg_image_interface_type;
extern cfg_image_interface_type cfg_ram_addr_image_interface;
extern cfg_image_interface_type cfg_storage_addr_image_interface;

/*===========================================================================
**  Function :  cfg_validate_data
** ==========================================================================
*/
/*!
* 
* @brief
*   This function verifies the loaded ConfigLib item.
*   It is an intermediate api to add image meta data (eg segment info) 
*   needed by authentication api's which do the actual validation.
* 
* @param[in]    
*     start_offset      location of requested item data within partition
*     config_item_size  Pointer to size of data to be verified
*     buffer            Pointer to data to be verified
*
* @param[out] 
*  None
*        
* @par Dependencies
*   buffer is assumed to be populated with data to be verified
*   
* @retval
*   config_status_type. CONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
config_status_type cfg_validate_data
(
  uintnt start_offset,
  uintnt config_item_size,
  void *buffer  
);

/*===========================================================================
**  Function :  cfg_verified_config_data_read
** ==========================================================================
*/
/*!
* 
* @brief
*   This function reads ConfigLib item and later proceeds to validate it
*   (eg verify its hash in context of elf image).
*
* @param[in]    
*     start_offset      location of requested item data within partition
*     config_item_size  size of data to be verified
*     buffer            Pointer to data to be verified
*
* @param[out] 
*  None
*        
* @par Dependencies
*   buffer is assumed to be big enough for data to be read and verified
*   
* @retval
*   config_status_type. CONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
config_status_type cfg_verified_config_data_read
(
  uintnt start_offset,
  uintnt config_item_size,
  void *buffer
);

#endif /* CONFIG_IMAGE_IF_H */
