/*=============================================================================

                            ConfigLib Module Sources

GENERAL DESCRIPTION
  This file defines ConfigLib api's that interface with ConfigLib RamLib's
  start address load module.

Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
09/08/21     tmt     Port to QDSP -> ConfigLib
10/16/20     rama    Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include <string.h>
#include "cfg_item_config.h"
#include "config_utils.h"
#include "config_image_if.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define CFG_RAM_MAX_LOGICAL_BLOCK_COUNT 1

typedef struct cfg_ram_info_type{
    cfg_metadata_header_type *cfg_metadata_ptr;
    uint32 cfg_metadata_size;
    uintnt max_logical_block_count;
}cfg_ram_info_type;

cfg_ram_info_type *cfg_ram_info_table = NULL;
boolean segment_loadable = FALSE;

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/

/*===========================================================================
**  Function :  cfg_ram_image_get_max_logical_block_count
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the max number of image logical blocks
*  (segments in case of elf image)
*
* @param[out]
*   max_logical_blk_ptr      pointer to max logical blocks
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_ram_image_get_max_logical_block_count
(
  uintnt *max_logical_blk_ptr
)
{
  config_status_type status = CONFIG_META_DATA_LOAD_ERR;
  do
  {
    if( max_logical_blk_ptr == NULL || cfg_ram_info_table == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    *max_logical_blk_ptr = cfg_ram_info_table->max_logical_block_count;
    status = CONFIG_SUCCESS;

  }
  while(0);

  return status;
}

/*===========================================================================
**  Function :  cfg_ram_image_get_block_info
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the block size and offset for a given index
*  (info of metadata header in case of init from start address)
*
* @param[in]
*   index                index of the block info to be retrieved
* @param[out]
*   blk_size_ptr         pointer to store the block size
*   blk_offset_ptr       pointer to store the block offset
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_ram_image_get_block_info
(
  uintnt index,
  uintnt *blk_size_ptr,
  uintnt *blk_offset_ptr
)
{
  config_status_type status = CONFIG_SUCCESS;
  
  do
  {
    if( blk_size_ptr == NULL || blk_offset_ptr == NULL || cfg_ram_info_table == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;      
    }

    if(index > 0)
    {
      status = CONFIG_META_DATA_LOAD_ERR;
      break;
    }
    
    *blk_offset_ptr = 0;
    *blk_size_ptr = cfg_ram_info_table->cfg_metadata_size;
    segment_loadable = TRUE;
  }while(0);

  return status;  
}

/*===========================================================================
**  Function :  cfg_ram_get_data
** ==========================================================================
*/
/*!
* 
* @brief
*   This function loads data from ConfigLib segment in ram to destinition buffer
* 
* @param[in] 
*  uintnt file_offset          - Start of data to be loaded 
*                                
*  uintnt file_size            - Size of data to be loaded.
*
* @param[out] 
*  void *buffer                - pointer to buffer, loaded with data
* 
*       
* @par Dependencies
*  ConfigLib data segment is assumed to be loaded before calling the api
*   
* @retval
*   config_status_type.   CONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
config_status_type cfg_ram_get_data( uintnt file_offset, uintnt file_size, void *buffer)
{
  config_status_type status = CONFIG_SUCCESS;
  uintnt phy_addr;
  
  do
  {
    if(buffer == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;      
    }
    if( file_size == 0)
    {
      status = CONFIG_INVALID_SIZE;
      break;      
    }
    if(file_size > CFG_UINT32_MAX)
    {
      status = CONFIG_OVERFLOW_ERR;
      break;
    }
    
    phy_addr = (uintnt)(cfg_ram_info_table->cfg_metadata_ptr) + file_offset;
    
    memcpy( buffer, (void *)phy_addr, (uint32) file_size);

  }while(0);

  return status;
}  

/*===========================================================================
**  Function :  cfg_ram_get_block_data
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns ConfigLib data at input offset
*  (segments in case of elf image)
*
* @param[in]
*  uintnt block_offset         - Start of data to be loaded in partition from
*                                storge device
*  uintnt block_size           - Size of data to be loaded.
*
* @param[out]
*  void *buffer                - pointer to buffer, loaded with data
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/

config_status_type cfg_ram_get_block_data
(
  uintnt block_offset,
  uintnt block_size,
  void *buffer,
  boot_boolean validate
)
{
 return cfg_ram_get_data(block_offset, block_size, buffer);
}

/*===========================================================================
**  Function :  cfg_ram_image_interface_reset
** ==========================================================================
*/
/*!
*
* @brief
*   This function resets ConfigLib image loading interface
*
* @param[out]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_ram_image_interface_reset (void)
{
  config_status_type status = CONFIG_SUCCESS;
  do
  {
    if(cfg_ram_info_table == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }
  }
  while(FALSE);

  return status;
}

/*===========================================================================
**  Function :  cfg_ram_image_interface_deinit
** ==========================================================================
*/
/*!
*
* @brief
*   This function deinitializes ConfigLib image loading interface
*   It free's up structures allocated by image loading interface
*
* @param[out]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_ram_image_interface_deinit (void)
{
  config_status_type status = CONFIG_DEINIT_ERR;
  do
  {
    if(cfg_ram_info_table == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    status = cfg_free((void**)&(cfg_ram_info_table));

    /* if any buffer freeing failed, indicate it to caller */
    if(status != CONFIG_SUCCESS)
    {
      break;
    }

    status = CONFIG_SUCCESS;

  }
  while(0);

  return status;
}

/*===========================================================================
**  Function :  cfg_ram_image_interface_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes ConfigLib image loading interface
*   
*
* @param[out]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_ram_image_interface_init(void)
{
  config_status_type status = CONFIG_RAM_ELF_INFO_INIT_ERR;
  cfg_metadata_header_type *cfg_metadata_ptr = NULL;
  do
  {

    if(cfg_ram_info_table == NULL)
    {
      /*Ramlib data structs are expected to be set before interface init. 
        In case of ramlib the data is already available
        since ConfigLib is part of ConfigLib elf.  */
      status = CONFIG_RAM_ELF_INFO_INIT_ERR;
      break;
    }  
    cfg_metadata_ptr = cfg_ram_info_table->cfg_metadata_ptr;
    if(cfg_metadata_ptr == NULL)
    {
      status = CONFIG_RAM_ELF_INFO_INIT_ERR;
      break;
    }
    /* Populate cfg_ram_info_table */
    cfg_ram_info_table->cfg_metadata_size = cfg_metadata_ptr->config_meta_size;
    cfg_ram_info_table->max_logical_block_count = CFG_RAM_MAX_LOGICAL_BLOCK_COUNT;
    
    status = CONFIG_SUCCESS;
    
  }while(0);

  /* Free malloced memory in case of error */
  if(status != CONFIG_SUCCESS)  
  {
    cfg_free((void**)&(cfg_ram_info_table));    
  }
  
  return status;
  
} /* cfg_ram_image_interface_init */

/*===========================================================================
**  Function :  config_ramlib_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function sets elf meta info consumed by ConfigLib ramlib
*
* @param[in]
*  cfg_ram_start_address   Start address of ConfigLib
*
* @param[out]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type config_ramlib_init
(
  uintnt *cfg_ram_start_address
)
{
  config_status_type status = CONFIG_INIT_ERR;
  
  do
  {
      if(cfg_ram_info_table != NULL)
      {
        status = CONFIG_SUCCESS;
        break;
      }
      
      if(cfg_ram_start_address == NULL)
      {
        break;
      }
      
      status = cfg_malloc(sizeof(cfg_ram_info_type), (void **)&cfg_ram_info_table);
      if(status != CONFIG_SUCCESS)
      {
        break;
      }
      
      cfg_ram_info_table->cfg_metadata_ptr = (cfg_metadata_header_type *)cfg_ram_start_address;
      status = CONFIG_SUCCESS;
  }
  while(FALSE);
  return status;
}

cfg_image_interface_type cfg_ram_addr_image_interface = {
    cfg_ram_image_interface_init,
    cfg_ram_image_get_max_logical_block_count,
    cfg_ram_image_get_block_info,
    cfg_ram_get_block_data,
    cfg_ram_image_interface_deinit,
    cfg_ram_image_interface_reset
};
