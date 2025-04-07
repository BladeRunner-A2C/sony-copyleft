/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file defines XBL config api's that interface with XBLLoader's elf image
  load module.

Copyright 2016 - 2021, 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
10/14/16     yps      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include "boot_loader_if.h"
#include "boot_seclib_if.h"
#include "boot_elf_loader.h"
#include "cfg_item_config.h"
#include "config_utils.h"
#include "config_image_if.h"
#include <boot_recovery_partition.h>
#include <boot_cfg_recovery.h>
#define PARTIAL_HASH_BUFF_SIZE (1024)
/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
typedef struct cfg_segment_info_type
{
  uintnt offset;
  uintnt size;
} cfg_segment_info_type;


typedef struct cfg_info_type
{
  cfg_segment_info_type *segment_info_ptr;
  uint32 num_segments;
  boot_handle loader_handle;
  boot_loader_if_type *loader_if;
} cfg_info_type;


/* XBLConfig elf info structure containing pointer to
hash buffer and segment info */
static cfg_info_type *cfg_info = NULL;

/*Define whitelist for validating load addresses */
#ifndef BOOT_RAMDUMP_ENABLE
extern uintnt * boot_internal_cached_heap_base;
extern uintnt boot_internal_cached_heap_size;
#endif

extern uintnt * boot_external_cached_heap_base;
extern uintnt boot_external_cached_heap_size;
/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/
/*===========================================================================
**  Function :  xcfg_load_addr_validation_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes load address validation module
*  (such as whitelist checks)
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
*   xblconfig_status_type. CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
whitelst_tbl_entry_type xblconfig_img_whitelist[4];
config_status_type cfg_load_addr_validation_init(boot_handle config_context_handle)
{
  config_status_type status = CONFIG_BUFFER_VALIDATION_ERR;
  bl_error_boot_type return_status = BL_ERR_NONE;
#ifndef BOOT_RAMDUMP_ENABLE
  xblconfig_img_whitelist[0].start_addr = (uint64)boot_internal_cached_heap_base;
  xblconfig_img_whitelist[0].size = boot_internal_cached_heap_size;

  xblconfig_img_whitelist[1].start_addr = (uint64)boot_external_cached_heap_base;
  xblconfig_img_whitelist[1].size = boot_external_cached_heap_size;

  xblconfig_img_whitelist[2].start_addr = SCL_SBL1_DDR_DSF_CFG_BUF_BASE;
  xblconfig_img_whitelist[2].size = SCL_SBL1_DDR_DSF_CFG_BUF_SIZE;

  xblconfig_img_whitelist[3].start_addr = SCL_SBL1_DDR_SHRM_STRUCT_BASE;
  xblconfig_img_whitelist[3].size = SCL_SBL1_DDR_SHRM_STRUCT_SIZE;
#else
  xblconfig_img_whitelist[0].start_addr = (uint64 )boot_external_cached_heap_base;
  xblconfig_img_whitelist[0].size = boot_external_cached_heap_size;

  xblconfig_img_whitelist[1].start_addr = SCL_SBL1_DDR_DSF_CFG_BUF_BASE;
  xblconfig_img_whitelist[1].size = SCL_SBL1_DDR_DSF_CFG_BUF_SIZE;

  xblconfig_img_whitelist[2].start_addr = SCL_SBL1_DDR_SHRM_STRUCT_BASE;
  xblconfig_img_whitelist[2].size = SCL_SBL1_DDR_SHRM_STRUCT_SIZE;
#endif

  /* Set the image whitelist for whitelist based image loading */
//  if( TRUE == boot_set_active_img_whitelist_table(&xblconfig_img_whitelist[0]))
//    status = CONFIG_SUCCESS;

  do
  {
    return_status = boot_config_context_set_value(config_context_handle, CONFIG_CONTEXT_WHITELIST_NUM_ENTRIES, sizeof(xblconfig_img_whitelist)/sizeof(whitelst_tbl_entry_type));
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_IMAGE_WHITELIST, xblconfig_img_whitelist);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    status = CONFIG_SUCCESS;

  } while (FALSE);

  return status;
}

/*===========================================================================
**  Function :  cfg_loader_image_get_max_logical_block_count
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
*  config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_loader_image_get_max_logical_block_count
(
  uintnt *max_logical_blk_ptr
)
{
  config_status_type status = CONFIG_META_DATA_LOAD_ERR;
  do
  {
    if( max_logical_blk_ptr == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    *max_logical_blk_ptr = cfg_info->num_segments;
    status = CONFIG_SUCCESS;

  }while(0);

  return status;
}

/*===========================================================================
**  Function :  cfg_loader_image_get_block_info
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns info for requested logical block
*
*   Note: A logical block for elf file type is a segment
*
* @param[in]
*    index        index pointing to desired logical block.
*
* @param[out]
*   blk_size_ptr        pointer to block size
*   is_blk_loadable_ptr pointer to flag indicating loadable block
*   blk_offset_ptr      pointer to block offset on storage device
*
* @par Dependencies
*   None
*
* @retval
*  config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_loader_image_get_block_info
(
  uintnt index,
  uintnt *blk_size_ptr,
  uintnt *blk_offset_ptr
)
{
 config_status_type status = CONFIG_META_DATA_LOAD_ERR;
  bl_error_boot_type result_status = BL_ERR_NONE;
  boot_loader_segment_info_type segment_info;

  do
  {
    if( blk_size_ptr == NULL || blk_offset_ptr == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }

    result_status = cfg_info->loader_if->get(cfg_info->loader_handle, BOOT_LOADER_SEGMENT_INFO, &segment_info, &index);
    if(result_status != BL_ERR_NONE)
    {
      status = CONFIG_META_DATA_LOAD_ERR;
      break;
    }

    /*while searching for meta data also keep track of segment offset and size */
    cfg_info->segment_info_ptr[index].offset = segment_info.source_offset;
    cfg_info->segment_info_ptr[index].size = segment_info.source_size;

    *blk_size_ptr = segment_info.source_size;
    *blk_offset_ptr = segment_info.source_offset;

    status = CONFIG_SUCCESS;

  } while(0);

  return status;
}


/*===========================================================================
**  Function :  cfg_loader_get_config_segment_index
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses program header table and locates segment cointaining
* data at given offset.
*
* @param[in]
*    config_item_start_offset location of requested item data within partition
*    config_item_size         size of data
*
* @param[out]
*   segment_index             pointer to segment index
*   segment_offset            pointer to segment offset
*   segment_size              pointer to segment size
*
* @par Dependencies
*   None
*
* @retval
*  config_status_type.   CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static config_status_type cfg_loader_get_config_segment_index
(
  uintnt config_item_start_offset,
  uintnt config_item_size,
  uintnt *segment_index,
  uintnt *segment_offset,
  uintnt *segment_size
)
{
  config_status_type status = CONFIG_VERIFY_ERR;
  bl_error_boot_type return_status = BL_ERR_NONE;
  uintnt index =0, entry_end_offset =0;
  cfg_segment_info_type *cfg_segment_info_ptr;
  uint32 num_segments = 0;

  do
  {
    if( cfg_info == NULL || segment_index == NULL ||
        segment_offset == NULL || segment_size == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }

    if( cfg_info->segment_info_ptr == NULL)
    {
      status = CONFIG_INIT_ERR;
      break;
    }


    if (cfg_info->loader_if == NULL)
    {
      status = CONFIG_INIT_ERR;
      break;
    }

    return_status = cfg_info->loader_if->get(cfg_info->loader_handle, BOOT_LOADER_NUM_SEGMENTS, &num_segments, NULL);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_META_DATA_LOAD_ERR;
      break;
    }

    cfg_segment_info_ptr  = cfg_info->segment_info_ptr;
    for(index =0;index < num_segments; index++)
    {
      entry_end_offset = (cfg_segment_info_ptr[index].offset + cfg_segment_info_ptr[index].size);
      if(entry_end_offset < cfg_segment_info_ptr[index].offset )
      {
        status = CONFIG_OVERFLOW_ERR;
        break;
      }

      if( (cfg_segment_info_ptr[index].offset <= config_item_start_offset) &&
          (cfg_segment_info_ptr[index].size >= config_item_size) &&
          (entry_end_offset > config_item_start_offset) )
      {
        /* Config data fully contained within segment*/
        *segment_index = index;
        *segment_offset = cfg_segment_info_ptr[index].offset;
        *segment_size = cfg_segment_info_ptr[index].size;
        status = CONFIG_SUCCESS;
        break;
      }
    }
  }while(0);
  return status;
}

/*===========================================================================
**  Function :  cfg_loader_get_data
** ==========================================================================
*/
/*!
*
* @brief
*   This function loades xbl config data of a given size from a given offset
*
* @param[in]
*    file_offset              offset into xbl config data to start loading
*    file_size                size of data to be loaded.
*
* @param[out]
*   buffer                    pointer to loaded data
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
static config_status_type cfg_loader_get_data(uintnt file_offset, uintnt file_size, void *buffer)
{
  config_status_type status = CONFIG_CONFIG_DATA_LOAD_ERR;
  bl_error_boot_type return_status = BL_ERR_NONE;

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

    if( (file_offset > CFG_UINT32_MAX) ||
        (file_size > CFG_UINT32_MAX))
    {
      status = CONFIG_OVERFLOW_ERR;
      break;
    }

    if(cfg_info->loader_if == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }

    return_status = cfg_info->loader_if->load_buffer(cfg_info->loader_handle, file_offset, file_size, buffer);
    if(return_status != BL_ERR_NONE)
    {
      /* Could not get max prog header count from elf header */
      status = CONFIG_META_DATA_LOAD_ERR;
      break;
    }

    status = CONFIG_SUCCESS;

  } while(0);

  return status;
}

/*===========================================================================
**  Function :  cfg_loader_verify_transient_data
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds data to running hash.
* 
* @param[in]    
*     seg_start_offset  location of segment data within partition
*     seg_end_offset    end offset of segment data chunk
*     hash_buffer       Pointer to xbl config hash buffer
*     hash_buffer_size  Size of hash buffer
*     segment_index     index of segment containing data to be verified
*     segment_size      size of segment containing data to be verified
*
* @param[out] 
*  None
*        
* @par Dependencies
*   None
*   
* @retval
*   config_status_type. CONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
static config_status_type cfg_loader_verify_transient_data
(
  uintnt seg_start_offset,
  uintnt seg_end_offset,
  void *hash_buffer,
  uintnt hash_buffer_size,
  uintnt segment_index,
  uintnt segment_size
)
{
  volatile config_status_type status = CONFIG_SUCCESS, free_status = CONFIG_SUCCESS;
  void *partial_hash_data_buff = NULL;
  uintnt segment_chunk_size, data_size;
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_seclib_if_type *seclib_if = NULL;

  do
  {
    if( seg_start_offset > seg_end_offset)
    {
      status = CONFIG_INVALID_SIZE;
      break;
    }
    if(hash_buffer == NULL || hash_buffer_size == 0)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }

    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_SECLIB_INTERFACE, (void **)&seclib_if);
    if(return_status != BL_ERR_NONE || seclib_if == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }
    
    /* Allocate buffer for streaming hash compute */
    status = cfg_malloc(PARTIAL_HASH_BUFF_SIZE, (void **)&partial_hash_data_buff);
    if(status != CONFIG_SUCCESS)
    {
      break;
    }

    if(partial_hash_data_buff == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
     
    segment_chunk_size = seg_end_offset - seg_start_offset;
    data_size = PARTIAL_HASH_BUFF_SIZE;
    while(segment_chunk_size > data_size)
    {
      /* Load segment data into buffer */
      if(CONFIG_SUCCESS != cfg_loader_get_data( seg_start_offset, data_size, partial_hash_data_buff))
      {
        status = CONFIG_VERIFY_ERR;
        break;
      }

      return_status = seclib_if->auth_partial_hash_update (hash_buffer, hash_buffer_size, partial_hash_data_buff, data_size, segment_index);
      if(return_status != BL_ERR_NONE)
      {
        status = CONFIG_VERIFY_ERR;
        break;
      }

      segment_chunk_size = segment_chunk_size - data_size;
      seg_start_offset = seg_start_offset + data_size;
    }
    
    if(segment_chunk_size > 0 && status == CONFIG_SUCCESS)
    {
      /*segment_chunk_size has to be less than data size at this point */
      /* Load segment data into buffer */
      if(CONFIG_SUCCESS != cfg_loader_get_data( seg_start_offset, segment_chunk_size, partial_hash_data_buff))
      {
        status = CONFIG_VERIFY_ERR;
        break;
      }

      return_status = seclib_if->auth_partial_hash_update (hash_buffer, hash_buffer_size, partial_hash_data_buff, segment_chunk_size, segment_index);
      if(return_status != BL_ERR_NONE)
      {
        status = CONFIG_VERIFY_ERR;
        break;
      }
    }
    
  }while(0);
  
  /*In all cases success or failure, free the buffer if memory is allocated */
  free_status = cfg_free((void**)&partial_hash_data_buff);
  if(status == CONFIG_SUCCESS)
  {
    /* Overwrite main logic status with cleanup status only if no error in main logic */
    status = free_status;
  }
  
  return status;
}

/*===========================================================================
**  Function :  cfg_loader_verify_data
** ==========================================================================
*/
/*!
* 
* @brief
*   This function verifies input data.
* 
* @param[in]    
*     start_offset      location of requested item data within partition
*     config_item_size  size of data to be verified
*     segment_index     index of segment containing data to be verified
*     segment_offset    offset of segment containing data to be verified
*     segment_size      size of segment containing data to be verified
*     buffer            Pointer to data to be verified
*     hash_buffer       Pointer to xbl config hash buffer
*     hash_buffer_size  Size of hash buffer
*
* @param[out] 
*  None
*        
* @par Dependencies
*   None
*   
* @retval
*   config_status_type. CONFIG_SUCCESS if no error else error value
* 
* @par Side Effects
*   None
* 
*/
static config_status_type cfg_loader_verify_data
(
  uintnt config_item_offset,
  uintnt config_item_size,
  uintnt segment_index,
  uintnt segment_offset,
  uintnt segment_size,
  void *buffer,
  void *hash_buffer,
  uintnt hash_buffer_size
)
{
  config_status_type status = CONFIG_SUCCESS;
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_seclib_if_type *seclib_if = NULL;

  do
  {
    if( buffer == NULL || hash_buffer == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }

    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_SECLIB_INTERFACE, (void **)&seclib_if);
    if(return_status != BL_ERR_NONE || seclib_if == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    return_status = seclib_if->auth_partial_hash_init (hash_buffer, hash_buffer_size, buffer, config_item_size, segment_index);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_VERIFY_ERR;
      break;
    }
    
    /* Compute hash for intial data if applicable */
    if(segment_offset < config_item_offset)
    {
      
      status = cfg_loader_verify_transient_data(segment_offset, config_item_offset,
                  hash_buffer, hash_buffer_size, segment_index, segment_size);
                  
      if(status != CONFIG_SUCCESS )
      {
        break;
      }
    }

    return_status = seclib_if->auth_partial_hash_update (hash_buffer, hash_buffer_size, buffer, config_item_size, segment_index);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_VERIFY_ERR;
      break;
    }

    /* check for overflow */
    if(
       ((config_item_offset + config_item_size) < config_item_offset) ||
       ((segment_offset + segment_size) < segment_offset)
      )
    {
      status = CONFIG_OVERFLOW_ERR;
      break;
    }
    
    /* Compute hash for remaining segment data if applicable */
    if((config_item_offset + config_item_size) < 
       (segment_offset + segment_size)
      )
    {
      status = cfg_loader_verify_transient_data(
                (config_item_offset + config_item_size),
                (segment_offset + segment_size),
                hash_buffer, hash_buffer_size, segment_index, segment_size );
                
      if(status != CONFIG_SUCCESS )
      {
        break;
      }
    }    

    return_status = seclib_if->auth_partial_hash_finalize (hash_buffer, hash_buffer_size, buffer, config_item_size, segment_index);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_VERIFY_ERR;
      break;
    }
     
  }while(0);
  return status;  
}  

/*===========================================================================
**  Function :  cfg_loader_get_block_data
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns xbl config data at input offset
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
config_status_type cfg_loader_get_block_data
(
  uintnt block_offset,
  uintnt block_size,
  void *buffer,
  boot_boolean validate
)
{
  config_status_type status = CONFIG_READ_ERR;
  bl_error_boot_type return_status = BL_ERR_NONE;
  uintnt segment_index = 0;
  uintnt segment_offset = 0;
  uintnt segment_size = 0;
  void *hash_buffer = NULL;
  uintnt hash_buffer_size = 0;

  do
  {
    if( buffer == NULL )
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }

    if( block_size == 0 )
    {
      status = CONFIG_INVALID_SIZE;
      break;
    }

    if(cfg_info == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    if (cfg_info->loader_if == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    return_status = cfg_info->loader_if->load_buffer(cfg_info->loader_handle, block_offset, block_size, buffer);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    if (validate == FALSE)
    {
      status = CONFIG_SUCCESS;
      break;
    }

    return_status = cfg_info->loader_if->get(cfg_info->loader_handle, BOOT_ELF_LOADER_HASH_SEGMENT_BUFFER, &hash_buffer, NULL);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    if (hash_buffer == NULL)
    {
      break;
    }

    return_status = cfg_info->loader_if->get(cfg_info->loader_handle, BOOT_ELF_LOADER_HASH_SEGMENT_SIZE, &hash_buffer_size, NULL);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    status = cfg_loader_get_config_segment_index (block_offset, block_size, &segment_index, &segment_offset, &segment_size);
    if(status != BL_ERR_NONE)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    status = cfg_loader_verify_data(block_offset, block_size, segment_index, segment_offset, segment_size, buffer, hash_buffer, hash_buffer_size);
    if(status != CONFIG_SUCCESS)
    {
      break;
    }

    status = CONFIG_SUCCESS;

  }while(0);
  return status;
}

/*===========================================================================
**  Function :  cfg_loader_image_interface_reset
** ==========================================================================
*/
/*!
*
* @brief
*   This function resets xbl config image loading interface
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
config_status_type cfg_loader_image_interface_reset (void)
{
  config_status_type status = CONFIG_SUCCESS;
  do
  {
    /* Close the image partition and release the flash translation interface */
  }while(0);

  return status;
}

/*===========================================================================
**  Function :  cfg_loader_image_interface_deinit
** ==========================================================================
*/
/*!
*
* @brief
*   This function deinitializes xbl config image loading interface
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
config_status_type cfg_loader_image_interface_deinit (void)
{
  config_status_type status = CONFIG_DEINIT_ERR;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if(cfg_info == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    /* If recovery boot is enabled, copy primary and recovery partition id to smem */
    if (boot_recovery_is_recovery_enabled() == TRUE)
    {
      return_status = cfg_item_add_partitioninfo_to_smem();
      if(return_status != BL_ERR_NONE)
      {
        status = CONFIG_DEINIT_ERR;
        break;
      }
    }

    status = cfg_free((void**)&(cfg_info->segment_info_ptr));
    if(status != CONFIG_SUCCESS)
      break;

    if (cfg_info->loader_if == NULL)
    {
      status = CONFIG_DEINIT_ERR;
      break;
    }

    return_status = cfg_info->loader_if->close(cfg_info->loader_handle);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_DEINIT_ERR;
      break;
    }

    status = cfg_free((void**)&cfg_info);
    if(status != CONFIG_SUCCESS)
      break;

    cfg_info = NULL;

  } while(FALSE);

  return status;
}
/*===========================================================================
**  Function :  config_errorhandler
** ==========================================================================
*/
/*!
*
* @brief
*   This function handles xblcfg_init and xblcfg_read errors
*   and loading recovery image
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_loader_image_error_handler(uint32 cfg_err_status)
{
  bl_error_boot_type status = BL_ERR_NONE;
  config_status_type cfg_status = CONFIG_SUCCESS;



    /* NOTE: Error handler is common for lun switch or partition swap in case of recovery
             Handles following cases :
             Case 1: Recovery feature is disabled, it returns error i.e., cfg_err_status
             Case 2: Recovery feature is enabled: It can be LUN Switch or GUID Swap
                     CASE 2.1: LUN SWITCH: If recovery partition id is null
                                           (i) Does LUN Switch and then hard reset
                                           (ii) If primary and recovery LUNS are corrupted goes into EDL
                     CASE 2.2: GUID SWAP: If recovery partion id is not null
                                           (i) If booting from primary, updates corrupted partition id in recoveryinfo partition and does hard reset to boot from recovery
                                           (ii) If booting from recovery, updates corrupted partition id in recoveryinfo partition and goes into EDL*/

    /* CASE 1: Recovery boot is not enabled, return xbl_cfg status */
    if (boot_recovery_is_recovery_enabled() == FALSE)
    {
      cfg_status =(config_status_type) cfg_err_status;
    return cfg_status;
    }

    /* CASE 2: Recovery boot is enabled */
  status = cfg_image_error_handler_recovery ();
      /* CASE 2.1: recovery_partition_id is NULL, if LUN switch is enabled switch boot LUN */
        /* lun switch and hard reset */
        if (status != BL_ERR_NONE)
        {
          cfg_status = CONFIG_RECOVERY_ERR;
        }

      /* CASE 2.2: recovery_partition_id is not NULL, try loading from recovery partition */
          /* Update corrupt partition id in recoveryinfo partition and do a hard reset */
          /* Update recovery partition id in recoveryinfo partition and enter EDL*/


  
  return cfg_status;
} /* cfg_loader_image_error_handler */

/*===========================================================================
**  Function :  cfg_loader_image_interface_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes image interface and performs steps necessary
*  prior to data access such as image authentication
*
* @param[out]
*  None
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
config_status_type cfg_loader_image_interface_init(void)
{
  config_status_type status = CONFIG_META_DATA_LOAD_ERR;
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint32 num_segments = 0;

  do
  {
    if(cfg_info != NULL)
    {
      status = CONFIG_SUCCESS;
      break;
    }

    status = cfg_malloc(sizeof(cfg_info_type), (void **)&cfg_info);
    if(status != CONFIG_SUCCESS)
    {
      break;
    }

    if (cfg_info == NULL)
    {
      status = CONFIG_MEMORY_ALLOCATION_ERR;
      break;
    }
    status = cfg_load_addr_validation_init(CONFIG_CONTEXT_CRT_HANDLE);
    if(status != CONFIG_SUCCESS)
    {
      break;
    }
    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_LOADER_INTERFACE, (void **)&(cfg_info->loader_if));
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    if(cfg_info->loader_if == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      return_status = BL_ERR_SUBSYS_BOOT_FAIL;
      break;
    }

    return_status = cfg_info->loader_if->open(CONFIG_CONTEXT_CRT_HANDLE, &cfg_info->loader_handle);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_OPEN_ERR;
      break;
    }

    return_status = cfg_info->loader_if->load_metadata(cfg_info->loader_handle);
    if(return_status != BL_ERR_NONE)
    {
      status = CONFIG_META_DATA_LOAD_ERR;
      break;
    }

    return_status = cfg_info->loader_if->get(cfg_info->loader_handle, BOOT_LOADER_NUM_SEGMENTS, &num_segments, NULL);
    if(return_status != BL_ERR_NONE)
    {
      /* Could not get max prog header count from elf header */
      status = CONFIG_META_DATA_LOAD_ERR;
      break;
    }

    /*overflow check */
    if(sizeof(cfg_segment_info_type) > (CFG_UINT32_MAX / num_segments))
    {
      status = CONFIG_OVERFLOW_ERR;
      break;
    }

    /* Prepare segment info data struct, keeping track of all segment
       offset and sizes */
    status = cfg_malloc(num_segments * sizeof(cfg_segment_info_type),
                         (void **)&(cfg_info->segment_info_ptr));
    if(status != CONFIG_SUCCESS)
    {
      break;
    }

    if (cfg_info->segment_info_ptr == NULL)
    {
      status = CONFIG_MEMORY_ALLOCATION_ERR;
      break;
    }

    memset( (void *)(cfg_info->segment_info_ptr), 0x0,
             (uint32)(num_segments * sizeof(cfg_segment_info_type)));

    cfg_info->num_segments = num_segments;

    status = CONFIG_SUCCESS;

  }while(0);

  /* Free malloced memory in case of error */
  if(status != CONFIG_SUCCESS)
  {
    /* Since this is memory leak cleanup after error, ignore
       the status and continue freeing other buffers
    */
    if (cfg_info != NULL)
    {
      cfg_free((void**)&(cfg_info->segment_info_ptr));
      cfg_info->segment_info_ptr = NULL;
    }
  }

  return status;

} /* cfg_loader_image_interface_init */

cfg_image_interface_type cfg_storage_addr_image_interface = {
  cfg_loader_image_interface_init,
  cfg_loader_image_get_max_logical_block_count,
  cfg_loader_image_get_block_info,
  cfg_loader_get_block_data,
  cfg_loader_image_interface_deinit,
  cfg_loader_image_interface_reset,
  NULL,
  cfg_loader_image_error_handler,
};
