/*=============================================================================

                            ConfigLib Module Sources

GENERAL DESCRIPTION
  This file defines ConfigLib api's to support initializing ConfigLib module
  and access a config item.

Copyright 2016,2017,2020-2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
01/11/23     yps      Fix name length issue
05/31/22     yps      Port DTBO Best Match algorithm from core.boot.6.1
03/28/22     tmt      Port pre-DTBO Best-Match algorithm from core.boot.6.1
11/11/21     tmt      Fix config_status_type config_create_platforminfo() encoding
09/28/21     tmt      Remove unused var (KW complaint)
09/08/21     tmt      Port to QDSP -> ConfigLib
06/25/21     tmt      Add DTB support: config_open_by_hwinfo, config_chipinfo, config_platforminfo
04/20/21     rrwt     added nullptr error check before free of cfg
10/16/20     rama     Added init mode to CONFIG_init.
10/16/17     kpa      Replace strcmp by strncmp
05/10/17     kpa      rename CONFIG_SIZE_OVERFLOW_ERR to CONFIG_OVERFLOW_ERR
05/03/17     kpa      update meta data buffer pointer used for validation.
03/15/17     kpa      fix memory leaks in error scenario, update get data api's
03/02/17     kpa      use heap instead of stack variable for xbl config cookie
02/14/17     kpa      code cleanup
02/10/17     kpa      Update error checks in cfg_load_meta_data
01/20/17     kpa      Updates to metadata header and config item parsing logic
10/14/16     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include <stdio.h>
#include "cfg_item_config.h"
#include "config_image_if.h"
#include "config_utils.h"


/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
#define EIGHT_BYTE_ALIGN_SIZE 0x8

/* ChipInfo & PlatformInfo Masks */
#define ChipVersionMask 0xFFFF0000
#define PlatformTypeMask 0xFF000000
#define PlatformSubTypeMask 0x00FF0000
#define PlatformVersionMask 0x0000FFFF

#define dtb_ext ".dtb"
#define dtbo_ext ".dtbo"


typedef struct cfg_item_list
{
  struct cfg_item_list * p_prev_item;
  struct cfg_item_list * p_next_item;
  uintnt index;
  /* pointer to start of entry in blob */
  cfg_metadata_table_entries_type *entry_ptr;
}cfg_item_list_type;

typedef struct cfg_sort_list
{
  cfg_item_list_type *p_dtb_list;
  cfg_item_list_type *p_soc_dtbo_list;
  cfg_item_list_type *p_platform_dtbo_list;
} cfg_sort_list_type;
typedef struct config_type
{
  void *cfg_metadata_buff;
  uintnt cfg_metadata_start_offset;

  /* List to manage variable length config entries */
  cfg_parsed_metadata_table_entry_type *config_entry_list;
  uintnt max_config_entries;

  /* Data structure to keep track of open config items */
  cfg_config_handle_type *cfg_handle_list;
  uint32 cfg_handle_max_count;
  uint32 cfg_handle_count;
  uint32 dtbo_initialized;
  cfg_sort_list_type *cfg_sort_table;
} config_type;

cfg_image_interface_type *cfg_image_interface = NULL;

static config_type *config_data = NULL;
extern boolean segment_loadable;
boolean segment_loadable __attribute__((weak));

#define INITIAL_CONFIG_HANDLES  5
#define SIZE_INCREASE_MULTIPLE 2

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/

/*===========================================================================
**  Function :  cfg_load_meta_data
** ==========================================================================
*/
/*!
*
* @brief
*   This function finds and loads ConfigLib meta data
*
* @param[out]
*   cfg_elf_metadata_buff_ptr      pointer to buffer loaded with meta data
*   cfg_metadata_start_offset_ptr  pointer to store meta data start offset
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

config_status_type cfg_load_meta_data(void)
{
  uint8 cfg_cookie_ptr[CFG_LOADER_MAGIC_COOKIE_SIZE];
  config_status_type status = CONFIG_INIT_ERR;
  uintnt max_logical_blocks = 0, index = 0, cookie_size = 0;
  uintnt blk_size = 0, blk_offset = 0;
  boolean meta_data_found = FALSE;
  segment_loadable = TRUE;

  do
  {
    status = cfg_image_interface->init();
    if(status != CONFIG_SUCCESS)
      break;

    status =  cfg_image_interface->get_max_logical_block_count(&max_logical_blocks);
    if(status != CONFIG_SUCCESS)
      break;

    /* Allocate temporary buffer for reading cookie */
    cookie_size = CFG_LOADER_MAGIC_COOKIE_SIZE;

    for(index = 0; index < max_logical_blocks; index++)
    {
      status = cfg_image_interface->get_block_info(index, &blk_size, &blk_offset);

      if(status != CONFIG_SUCCESS)
        break;

      /* Search for meta data in current block/segment */
      if(segment_loadable == TRUE  && blk_size > 0 && meta_data_found == FALSE)
      {
        /* Read first four bytes to check if its a ConfigLib data segment */
        status = cfg_image_interface->get_block_data(blk_offset, cookie_size, (void *)cfg_cookie_ptr, FALSE);
        /*Note: 'Block' is a generic term to denote fileformat's data items to be checked
          (which is used to contain ConfigLib blob. In case of elf file format its a segment */
        if(status != CONFIG_SUCCESS)
          break;

        if(
          cfg_cookie_ptr[CFG_LOADER_MAG0_INDEX] == CFG_LOADER_MAG0 &&
          cfg_cookie_ptr[CFG_LOADER_MAG1_INDEX] == CFG_LOADER_MAG1 &&
          cfg_cookie_ptr[CFG_LOADER_MAG2_INDEX] == CFG_LOADER_MAG2 &&
          cfg_cookie_ptr[CFG_LOADER_MAG3_INDEX] == CFG_LOADER_MAG3
        )
        {
          status = cfg_malloc(blk_size, (&config_data->cfg_metadata_buff));
          if(status != CONFIG_SUCCESS)
            break;


          /* Load the ConfigLib data segment */
          status = cfg_image_interface->get_block_data(blk_offset, blk_size, config_data->cfg_metadata_buff, TRUE);
          if(status != CONFIG_SUCCESS)
            break;

          /* Store the offset of meta data start. That shall later be needed to get individual item offsets */
          config_data->cfg_metadata_start_offset = blk_offset;

          if (status == CONFIG_SUCCESS)
            meta_data_found = TRUE;
        }
      }
    }

    if((config_data->cfg_metadata_buff == NULL) || (index > max_logical_blocks))
    {
      /* meta data was not found or all blocks were not processed */
      status = CONFIG_META_DATA_LOAD_ERR;
      break;
    }
    else if(status != CONFIG_SUCCESS)
    {
      break;
    }

    cfg_image_interface->reset();

  }
  while(0);

  /* Free malloced memory in case of error */
  if(status != CONFIG_SUCCESS)
  {
    /* Since this is memory leak cleanup after error, ignore
       the free api status and continue freeing all buffer's
    */
    cfg_free((void**)config_data->cfg_metadata_buff);
  }
  return status;
}

/*===========================================================================
**  Function :  cfg_populate_config_item_list
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes the data structure that maintains config item
*   list.
*
* @param[in]
*  cfg_parsed_metadata_table_entry_type    Pointer to config entry list
*  cfg_metadata_header_type                Pointer to meta data header
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static config_status_type cfg_populate_config_item_list
(
  cfg_parsed_metadata_table_entry_type *config_entry_list,
  cfg_metadata_header_type *cfg_header
)
{
  config_status_type status = CONFIG_INIT_ERR;
  uintnt index =0, extended_bytes = 0, entry_ptr_val = 0;

  cfg_metadata_table_entries_type *item_entry_ptr;
  do
  {
    if (config_entry_list == NULL || cfg_header == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    item_entry_ptr = (cfg_metadata_table_entries_type *)
                     ((uintnt)cfg_header + sizeof(cfg_metadata_header_type));

    // Populate the config item meta list with pointers to each entry
    for(index = 0; index < config_data->max_config_entries; index++)
    {
      config_entry_list[index].entry_ptr = item_entry_ptr;

      extended_bytes = (uintnt)item_entry_ptr->config_name_len % EIGHT_BYTE_ALIGN_SIZE;
      if (extended_bytes != 0)
      {
        // name length is not a multiple of byte size
        extended_bytes = EIGHT_BYTE_ALIGN_SIZE - extended_bytes;
      }

      // Point to next entry in the meta data blob
      entry_ptr_val = (uintnt) item_entry_ptr
                      + sizeof(cfg_metadata_table_entries_type)
                      + (uintnt)item_entry_ptr->config_name_len
                      + extended_bytes
                      - 0x1 ;/* substract size of first byte that is included
                              in cfg_metadata_table_entries_type */

      if(entry_ptr_val < (uintnt)item_entry_ptr)
      {
        status = CONFIG_OVERFLOW_ERR;
        break;
      }

      item_entry_ptr = (cfg_metadata_table_entries_type *)entry_ptr_val;
    }
    status = CONFIG_SUCCESS;

  }
  while(0);

  return status;
}

/*===========================================================================
**  Function :  cfg_handle_init
** ==========================================================================
*/
/*!
*
* @brief
*  Function to initialize data structure maintaining open handles.
*  Everytime this api is called, if handle list is running out of space
*  it shall double its size.
*
* @param[out]
*  cfg_config_handle_type **cfg_handle_ptr       Pointer to config handle list
*  uint32 *handle_max_count_ptr                  Pointer to max handle count
*  uint32 *handle_count_ptr                      Pointer to count of handles in use
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static config_status_type cfg_handle_init
(
  cfg_config_handle_type **cfg_handle_ptr,
  uint32 *handle_max_count_ptr,
  uint32 *handle_count_ptr
)
{
  config_status_type status = CONFIG_HANDLE_ERR;
  cfg_config_handle_type *cfg_handle_temp_ptr = NULL;
  uint32 handle_list_size =0;
  boolean handle_init_flag = FALSE;
  do
  {
    if( handle_max_count_ptr == NULL || handle_count_ptr == NULL ||
        cfg_handle_ptr == NULL )
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    if(*handle_max_count_ptr != 0)
    {
      if(*cfg_handle_ptr == NULL)
      {
        // Null pointer for handle list but max handle count being
        // non-zero, it should have been initialized earlier.
        // looks incorrect.
        status = CONFIG_NULL_PTR_ERR;
        break;
      }

      if(*handle_count_ptr == *handle_max_count_ptr)
      {
        // Overflow check. at this point (*handle_max_count_ptr) is not 0
        if(sizeof(cfg_config_handle_type) > (CFG_UINT32_MAX / (*handle_max_count_ptr)))
        {
          status = CONFIG_OVERFLOW_ERR;
          break;
        }

        handle_list_size = (*handle_max_count_ptr) * sizeof(cfg_config_handle_type);

        // List of handles exhausted hence double the allocated memory for list
        if(handle_list_size > (CFG_UINT32_MAX / SIZE_INCREASE_MULTIPLE))
        {
          status = CONFIG_OVERFLOW_ERR;
          break;
        }

        status = cfg_malloc((handle_list_size * SIZE_INCREASE_MULTIPLE), (void **)&cfg_handle_temp_ptr);
        if(status != CONFIG_SUCCESS)
        {
          break;
        }

        memset((void *)cfg_handle_temp_ptr, 0x0, (handle_list_size * SIZE_INCREASE_MULTIPLE));

        //relocate list to new memory region
        memcpy((void *)cfg_handle_temp_ptr, (void *)*cfg_handle_ptr,
                handle_list_size);

        status = cfg_free((void**)cfg_handle_ptr);
        if(status != CONFIG_SUCCESS)
        {
          break;
        }
        *cfg_handle_ptr = cfg_handle_temp_ptr;
        *handle_max_count_ptr = *handle_max_count_ptr * 2;
        status = CONFIG_SUCCESS;
      }
    }
    else
    {
      //Since max handle count is zero, this is first time init
      if(*cfg_handle_ptr != NULL)
        break;

      *handle_max_count_ptr = INITIAL_CONFIG_HANDLES;
      handle_list_size = (*handle_max_count_ptr) * sizeof(cfg_config_handle_type);

      status = cfg_malloc(handle_list_size,(void **)cfg_handle_ptr);
      if(status != CONFIG_SUCCESS)
      {
        break;
      }

      memset((void *)*cfg_handle_ptr, 0x0, handle_list_size);
      *handle_count_ptr = 0;
      handle_init_flag = TRUE;
      status = CONFIG_SUCCESS;
    }

  }
  while(0);

  /* Free malloced memory in case of error */
  if(status != CONFIG_SUCCESS)
  {
    cfg_free((void**)&cfg_handle_temp_ptr);

    if(cfg_handle_ptr != NULL)
    {
      if(*cfg_handle_ptr != NULL && handle_init_flag == TRUE)
      {
        /* cfg_handle_ptr was malloced in this invocation of api */
        cfg_free((void**)cfg_handle_ptr);
      }
    }
  }

  return status;
}

/*===========================================================================
**  Function :  cfg_handle_allocate
** ==========================================================================
*/
/*!
*
* @brief
*  Function to initialize data structure maintaining open handles.
*  Everytime this api is called, if handle list is running out of space
*  it shall double its size.
*
* @param[in]
*  cfg_config_handle_type **cfg_handle_ptr  pointer to handle list
*  uint32 *handle_max_count                 Pointer to count of max
*                                           handles available
*
* @param[out]
*  uint32 *handle_count                 Pointer to current open handle count
*  uint32 *free_handle_index            Pointer filled with available handle
*                                       index
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static config_status_type cfg_handle_allocate
(
  cfg_config_handle_type **cfg_handle_ptr,
  uint32 *handle_max_count,
  uint32 *handle_count_ptr,
  uint32 *free_handle_index
)
{
  config_status_type status = CONFIG_HANDLE_ERR;
  uintnt index;
  do
  {
    if( (*handle_count_ptr) >= (*handle_max_count))
    {
      // no more space to allocate handle
      status = cfg_handle_init(cfg_handle_ptr, handle_max_count,
                                handle_count_ptr);

      if(status != CONFIG_SUCCESS || ((*handle_count_ptr) >= (*handle_max_count)))
        break;
    }
    //allocate handle from list. Find first free entry.
    for(index =0; index < (*handle_max_count) ; index++)
    {
      if((*cfg_handle_ptr)[index].is_valid == FALSE)
      {
        (*cfg_handle_ptr)[index].is_valid = TRUE;
        break;
      }
    }
    if(index < (*handle_max_count))
    {
      *free_handle_index = index;
      status = CONFIG_SUCCESS;
    }
    else
    {
      status = CONFIG_HANDLE_ERR;
    }

  }
  while(0);
  return status;
}

/*===========================================================================
**  Function :  cfg_item_config_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function initializes config module
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   config_status_type CONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_item_config_init(config_init_mode_type mode_type)
{
  config_status_type status = CONFIG_INIT_ERR;
  /* ConfigLib header structure */
  cfg_metadata_header_type *cfg_header;

  do
  {
    if(config_data != NULL)
    {
      status = CONFIG_SUCCESS;
      break;
    }

    /* Point ConfigLib image interface to cl ram function table */
    if(mode_type == CONFIG_INIT_FROM_FLASH)
    {
      cfg_image_interface = &cfg_storage_addr_image_interface;
    }
    else
    {
      cfg_image_interface = &cfg_ram_addr_image_interface;
    }

    status = cfg_malloc(sizeof(config_type), (void **)&config_data);
    if( (status != CONFIG_SUCCESS) || (config_data == NULL) )
    {
      break;
    }

    config_data->cfg_metadata_buff = NULL;
    config_data->cfg_metadata_start_offset = 0;

    config_data->config_entry_list = NULL;
    config_data->max_config_entries = 0;

    config_data->cfg_handle_list = NULL;
    config_data->cfg_handle_max_count = 0;
    config_data->cfg_handle_count = 0;
    config_data->dtbo_initialized = 0;
    config_data->cfg_sort_table = NULL;


    /*Initialize module for validating buffers to which data can be loaded
      from storage, example those from heap
    */

      //Load and authenticate ConfigLib hash table and get meta data blob
      status = cfg_load_meta_data();
      if(status != CONFIG_SUCCESS)
      {
        break;
      }

    //Validate meta data header
    cfg_header = (cfg_metadata_header_type *)config_data->cfg_metadata_buff;
    if (cfg_header == NULL)
      break;

    if(cfg_header->major_version != CFG_CONFIG_MAJOR_VERSION &&
        cfg_header->minor_version != CFG_CONFIG_MINOR_VERSION)
    {
      // unsupported meta data format.
      break;
    }

    config_data->max_config_entries = cfg_header->number_of_entries;

    // Parse the meta data to index the entries.
    status = cfg_malloc((config_data->max_config_entries * sizeof(cfg_parsed_metadata_table_entry_type)),
                         (void **)&config_data->config_entry_list);
    if(status != CONFIG_SUCCESS)
    {
      break;
    }

    status = cfg_populate_config_item_list(config_data->config_entry_list, cfg_header);
    if(status != CONFIG_SUCCESS)
      break;

    //Initialize list for open handles
    status = cfg_handle_init(&config_data->cfg_handle_list, &config_data->cfg_handle_max_count,
                              &config_data->cfg_handle_count);
    if(status != CONFIG_SUCCESS)
      break;

  }
  while(0);

  /* Free malloced memory in case of error */
  if(status != CONFIG_SUCCESS)
  {
    if(config_data->config_entry_list != NULL)
    {
      cfg_free((void**)&config_data->config_entry_list);
    }

    if(cfg_image_interface->cfg_error_handler != NULL )
    {
      status = cfg_image_interface->cfg_error_handler((uint32)status);
    }
  }

  return status;
} /* cfg_item_config_init */


/*===========================================================================
**  Function :  cfg_item_config_open
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses ConfigLib meta data to locate config item and
*   returns a config handle if found, along with its size
*
* @param[in]    config_name       Null terminated config item name string
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*
* @par Dependencies
*   Config module should have been initialized via config_init
*   before calling config_open
*
* @retval
*   config_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_item_config_open
(
  const char *config_name,
  uint32 *config_handle,
  uint32 *config_item_size
)
{
  cfg_metadata_table_entries_type *item_entry_ptr;
  config_status_type status = CONFIG_OPEN_ERR;
  uintnt index;

  do
  {
    if( config_name == NULL || config_handle == NULL ||
        config_item_size == NULL )
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    if(config_data == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    //Parse config table entries to locate item.
    for(index = 0; index < config_data->max_config_entries; index++)
    {
      item_entry_ptr = config_data->config_entry_list[index].entry_ptr;
      if(strncmp(config_name, &item_entry_ptr->config_name_start, strlen(&item_entry_ptr->config_name_start)) == 0)
      {
        //Config entry is found. Allocate handle
        status =  cfg_handle_allocate(&config_data->cfg_handle_list, &config_data->cfg_handle_max_count,
                                       &config_data->cfg_handle_count, config_handle);
        if(status != CONFIG_SUCCESS)
          break;

        //Update handle with config data info
        config_data->cfg_handle_list[(*config_handle)].config_entry_index = index;
        *config_item_size = item_entry_ptr->size;
        config_data->cfg_handle_count++;
        break;
      }
    }
    if(index == config_data->max_config_entries)
    {
      status = CONFIG_OPEN_ERR;
    }
  }
  while(0);

  return status;
}/* cfg_item_config_open */

/*===========================================================================
**  Function :  cfg_item_config_create_chipinfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the chipinfo value as used by config_open_by_hwinfo
*   Per ConfigLib v2.0 spec, chipinfo parameter (uint64) is created thusly...
*     [63..48] Chip_Family
*     [47..32] Chip_ID
*     [31..24] Major_Version
*     [23..16] Minor_Version
*     [15..0]  Reserved
*
* @param[in]         cFamily                  16-bit Chip_Family
*                    cId                      16-bit Chip_ID
*                    cVersion                 16-bit Major_Minor_Version
*
* @param[out]        chipinfo                 64-bit chip code
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
config_status_type cfg_item_config_create_chipinfo
(
  uint16   cFamily,
  uint16   cID,
  uint16   cVersion,
  uint64  *chipinfo
)
{
    uint64 hWord;
    uint32 lWord;

    if (NULL == chipinfo)
        return CONFIG_NULL_PTR_ERR;

    hWord = (cFamily<<16)  | cID;
    lWord = (cVersion<<16) & ChipVersionMask;

    *chipinfo = (hWord<<32)|lWord;

    return CONFIG_SUCCESS;
}

/*===========================================================================
**  Function :  cfg_item_config_create_platforminfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the platforminfo value as used by config_open_by_hwinfo
*   Per ConfigLib v2.0 spec, platforminfo parameter (uint64) is created thusly...
*     [63..56] Platform_Type    
*     [55..48] Platform_SubType
*     [47..40] Major_Version
*     [39..32] Minor_Version
*     [31..0]  Reserved
*
* @param[in]         pType                        8-bit platform Type
*                    pVersion                     16-bit Platform Version
*                    pSubtype                     8-bit Platform SubType
*
* @param[out]        platforminfo                 64-bit platform code
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
config_status_type cfg_item_config_create_platforminfo
(
  uint8    pType,
  uint16   pVersion,
  uint8    pSubtype,
  uint8    pOemVariant,
  uint64  *platforminfo
)
{
    uint64 hWord;
    uint32 lWord = 0;

    if (NULL == platforminfo)
        return CONFIG_NULL_PTR_ERR;

    hWord = ((pType<<24) & PlatformTypeMask) |
             ((pSubtype<<16) & PlatformSubTypeMask) |
             (pVersion & PlatformVersionMask);

    lWord = (pOemVariant<<24);

    *platforminfo = (hWord<<32)|lWord;

    return CONFIG_SUCCESS;
}

/*===========================================================================
**  Function :  config_match_chipinfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the comparative result of chipinfo base on the best
*   match algorithm 
*
* @param[in]         prequested_chipinfo          address of device's chipinfo  
*                    pentry_chipinfo              address of current entry chipinfo
*                   
*
* @par Dependencies
*   None
*
* @retval
*      boolean       TRUE                         chipinfo match successfully  
*                    FALSE                        chipinfo match failure
*
* @par Side Effects
*   None
*
*/

static boolean config_match_chipinfo
(
  uint64 *prequested_chipinfo,
  uint64 *pentry_chipinfo)
{
  chipinfo_hierarchy_type *requested_chipinfo_ptr = (chipinfo_hierarchy_type *)prequested_chipinfo;
  chipinfo_hierarchy_type *entry_chipinfo_ptr = (chipinfo_hierarchy_type *)pentry_chipinfo;
  if( pentry_chipinfo == NULL || (uint64)*pentry_chipinfo == 0xFFFFFFFFFFFFFFFF)
    goto next_entry;
  
  if (requested_chipinfo_ptr->ChipFamily == entry_chipinfo_ptr->ChipFamily)
  {
    if(requested_chipinfo_ptr->ChipId == entry_chipinfo_ptr->ChipId ||
       entry_chipinfo_ptr->ChipId == 0)
    {
      if(requested_chipinfo_ptr->Major_version == entry_chipinfo_ptr->Major_version)
      {
        if(requested_chipinfo_ptr->Minor_version >= entry_chipinfo_ptr->Minor_version)
            goto check_platforminfo;
        else
            goto next_entry;
      }
      else
      {
        if(requested_chipinfo_ptr->Major_version > entry_chipinfo_ptr->Major_version)
            goto check_platforminfo;
        else
            goto next_entry;
      }
    }
  }
  next_entry:
    return FALSE;
  check_platforminfo:
    return TRUE;
}

  /*===========================================================================
  **  Function :  config_match_platforminfo
  ** ==========================================================================
  */
  /*!
  *
  * @brief
  *   This function returns the comparative result of platforminfo base on the best
  *   match algorithm 
  *
  * @param[in]         prequested_platforminfo          address of device's platforminfo  
  *                    pentry_platforminfo              address of current entry platforminfo
  *                   
  *
  * @par Dependencies
  *   None
  *
  * @retval
  *      boolean       TRUE                         platforminfo match successfully  
  *                    FALSE                        platforminfo match failure
  *
  * @par Side Effects
  *   None
  *
  */

static boolean config_match_platforminfo
(
 uint64 *prequested_platforminfo,
 uint64 *pentry_platforminfo)
{
 platfrominfo_hierarchy_type *requested_platforminfo_ptr = (platfrominfo_hierarchy_type *)prequested_platforminfo;
 platfrominfo_hierarchy_type *entry_platforminfo_ptr = (platfrominfo_hierarchy_type *)pentry_platforminfo;

 if(pentry_platforminfo == NULL || (uint64)*pentry_platforminfo == 0xFFFFFFFFFFFFFFFF)
    goto next_entry;
 
 if(requested_platforminfo_ptr->Platformtype == entry_platforminfo_ptr->Platformtype)
 {
   if(requested_platforminfo_ptr->PlatformSubtype == entry_platforminfo_ptr->PlatformSubtype ||
      entry_platforminfo_ptr->PlatformSubtype == 0)
   {
     if(requested_platforminfo_ptr->Major_version == entry_platforminfo_ptr->Major_version)
     {
       if(requested_platforminfo_ptr->Minor_version >= entry_platforminfo_ptr->Minor_version)
       {
          goto check_oem_flavor_id;
       }
       else
       {
          goto next_entry;
       }
     }
     else 
     {
        if(requested_platforminfo_ptr->Major_version > entry_platforminfo_ptr->Major_version)
          goto check_oem_flavor_id;
        else
          goto next_entry;
     }
   }
   else
   {
     goto next_entry;
   }
 }
 else
 {
   if(entry_platforminfo_ptr->Platformtype == 0)
     goto check_oem_flavor_id;
   else
     goto next_entry;
 }
 check_oem_flavor_id:
  /*If oem flavor id can't be matched exactly, choose cfg item whose Oem_flaver_id is 0 */
  if( requested_platforminfo_ptr->Oem_flavor_id == entry_platforminfo_ptr->Oem_flavor_id ||
      entry_platforminfo_ptr->Oem_flavor_id == 0)
    goto bingo;

 next_entry:
   return FALSE;
 bingo:
   return TRUE;
}

/*===========================================================================
 **  Function :  add_cfg_item_to_list
 ** ==========================================================================
 */
 /*!
 *
 * @brief
 *   This function insterts config item to sort list table
 *
 * @param[in]        plist_header             pointer of sort list table
 *                   item_entry_ptr           pointer of config item entry
 *                   index                    the config index in metadate table
 *
 * @param[out]   
 *
 * @par Dependencies
 *   config module should have been initialized via CONFIG_init
 *   before calling CONFIG_open
 *
 * @retval
 *   config_status_type   Status of operation
 *
 * @par Side Effects
 *   None
 *
 */
 config_status_type add_cfg_item_to_list(cfg_item_list_type **plist_header,cfg_metadata_table_entries_type *item_entry_ptr, uintnt index)
 {
   config_status_type status = CONFIG_ADD_SORT_LIST_FAILED;
   cfg_item_list_type *p_curr_cfg_item = NULL, *p_cfg_item = NULL;
   do
   {
      status = cfg_malloc(sizeof(cfg_item_list_type), (void **)&p_curr_cfg_item);
      if(status != CONFIG_SUCCESS)
      {
        break;
      }
      p_curr_cfg_item->entry_ptr = item_entry_ptr;
      p_curr_cfg_item->index = index;
      p_curr_cfg_item->p_next_item = NULL;
      p_curr_cfg_item->p_prev_item = NULL;
      if(*plist_header == NULL)
      {
        *plist_header = p_curr_cfg_item;
        p_curr_cfg_item->p_prev_item = NULL;
        status = CONFIG_SUCCESS;
        break;
      }
      else
      {
        for(p_cfg_item = *plist_header; p_cfg_item!=NULL;p_cfg_item=p_cfg_item->p_next_item)
        {
            /*if chipinfo is greater than the currect chipinfo,  or chipinfo is equal current chipinfo 
             * and platforminfo is greater than the current platforminfo, the item will come first   */
            if ((p_curr_cfg_item->entry_ptr->chipinfo > p_cfg_item->entry_ptr->chipinfo)||
                ((p_curr_cfg_item->entry_ptr->chipinfo || p_cfg_item->entry_ptr->chipinfo)&&
                 (p_curr_cfg_item->entry_ptr->platforminfo > p_cfg_item->entry_ptr->platforminfo)))
            {
                if(p_cfg_item == *plist_header)
                {
                  /*if it is the first elment in link, update header point*/
                    *plist_header = p_curr_cfg_item;
                    p_curr_cfg_item->p_next_item = p_cfg_item;
                    p_cfg_item->p_prev_item = p_curr_cfg_item;
                }
                else
                {
                  p_cfg_item->p_prev_item->p_next_item = p_curr_cfg_item;
                  p_curr_cfg_item->p_next_item = p_cfg_item;
                }
                status = CONFIG_SUCCESS;
                break;
            }
            else
            {
              if(p_cfg_item->p_next_item == NULL)
              {
                p_cfg_item->p_next_item = p_curr_cfg_item;
                status = CONFIG_SUCCESS;
                break;
              }
            }
        }    
      }
   } while (FALSE);
   return status;

 } /*===========================================================================
 **  Function :  create_cfg_sort_list
 ** ==========================================================================
 */
 /*!
 *
 * @brief
 *   This function parses xbl config meta data to locate config item and
 *   Create three sorts list table for dtb, soc dtbo and platform dtbo.
 *
 * @param[in]        
 *
 * @param[out]  
 *
 * @par Dependencies
 *   config module should have been initialized via CONFIG_init
 *   before calling CONFIG_open
 *
 * @retval
 *   config_status_type   Status of operation
 *
 * @par Side Effects
 *   None
 *
 */
 config_status_type create_cfg_sort_list(void)
 {
   cfg_metadata_table_entries_type *item_entry_ptr;
   config_status_type status = CONFIG_OPEN_ERR;
   chipinfo_hierarchy_type *entry_chipinfo_ptr = NULL;
   cfg_metadata_header_type *cfg_header;
   uintnt index;
   uint8 ext_max_length = 0;
   uint8 dtb_ext_length = strlen(dtb_ext);
   uint8 dtbo_ext_length = strlen(dtbo_ext);
   uint8 config_name_length = 0;

   do
  {

    if(config_data == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    } else if (config_data->dtbo_initialized)
        return CONFIG_SUCCESS;

    if(config_data->cfg_sort_table == NULL)
    {
       status = cfg_malloc(sizeof(cfg_sort_list_type), (void **)&config_data->cfg_sort_table);
        if(status != CONFIG_SUCCESS)
        {
          break;
        }
        config_data->cfg_sort_table->p_dtb_list = NULL;
        config_data->cfg_sort_table->p_soc_dtbo_list = NULL;
        config_data->cfg_sort_table->p_platform_dtbo_list = NULL; 
    }
    cfg_header = (cfg_metadata_header_type *)config_data->cfg_metadata_buff;
    ext_max_length = dtb_ext_length > dtbo_ext_length?dtb_ext_length:dtbo_ext_length;
    //Parse config table entries to locate item.
    for(index = 0; index < config_data->max_config_entries; index++)
    {
      item_entry_ptr = config_data->config_entry_list[index].entry_ptr;
        if((cfg_header->major_version * 10 + cfg_header->minor_version) > 20)
          config_name_length = strlen(&item_entry_ptr->config_name_start);
        else
          config_name_length = item_entry_ptr->config_name_len;
        if(item_entry_ptr!=NULL && (char*)&item_entry_ptr->config_name_start != NULL && config_name_length > ext_max_length )
          {
         
            if(strncmp(((char *)&item_entry_ptr->config_name_start+(config_name_length-dtb_ext_length)),dtb_ext, dtb_ext_length)==0 && item_entry_ptr->platforminfo==0)
              {
              status = add_cfg_item_to_list(&config_data->cfg_sort_table->p_dtb_list,item_entry_ptr,index);
            }
            else 
            {
              /* sort dtbo table*/
              if(strncmp(((char *)&item_entry_ptr->config_name_start+(config_name_length-dtbo_ext_length)),dtbo_ext, dtbo_ext_length)==0 )
              {
                entry_chipinfo_ptr = (chipinfo_hierarchy_type *)&item_entry_ptr->chipinfo;
                /*if platforminfo is 0x0 and chip version is not 0x0, it is soc dtbo*/
                if(item_entry_ptr->platforminfo==0x0 && (entry_chipinfo_ptr->Major_version<<8|entry_chipinfo_ptr->Minor_version) != 0x0)
                  status = add_cfg_item_to_list(&config_data->cfg_sort_table->p_soc_dtbo_list,item_entry_ptr,index);
                else
                  status = add_cfg_item_to_list(&config_data->cfg_sort_table->p_platform_dtbo_list,item_entry_ptr,index);
                  
              } 
            }
            if(status != CONFIG_SUCCESS)
                break;
          
      }
    }
  }while(FALSE);
  if (status == CONFIG_SUCCESS)
    config_data->dtbo_initialized = 1;
  return status;
 }

 /*===========================================================================
**  Function :  cfg_item_config_open_first_dtb
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses ConfigLib meta data to locate config item and
*   returns a config handle if found, along with its size
*
* @param[in]        chipinfo                 64-bit chip code
*                   platforminfo             64-bit platform code
*                   config_name_starts_with  Null terminated config item [partial] name string
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*
* @par Dependencies
*   Config module should have been initialized via config_init
*   before calling config_open
*
* @retval
*   config_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/

config_status_type cfg_item_config_open_first_dtb
(
  uint64  chipinfo,
  uint64  platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size
)
{
  cfg_metadata_table_entries_type *item_entry_ptr;
  config_status_type status = CONFIG_OPEN_ERR;
  uintnt index;
  cfg_item_list_type *p_dtb_node;
  do
  {
    if( config_handle == NULL || config_item_size == NULL )
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    if(config_data == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }
    status = create_cfg_sort_list();
    if (status != CONFIG_SUCCESS)
      break;
    //Parse config table entries to locate item.
    for (p_dtb_node = config_data->cfg_sort_table->p_dtb_list; p_dtb_node!=NULL; p_dtb_node=p_dtb_node->p_next_item)
    {
      item_entry_ptr = p_dtb_node->entry_ptr;

      if (config_match_chipinfo(&chipinfo, (void *)&item_entry_ptr->chipinfo)!= TRUE)
      {
        continue;
      }

      if (config_name_starts_with != NULL)
      {
        if (strncmp(config_name_starts_with, (char *)&item_entry_ptr->config_name_start, strlen(config_name_starts_with)) != 0)
          continue;
      }

      index = p_dtb_node->index;
      break; /*bingo the chipfamily dtb has been found*/
    }
    if (p_dtb_node == NULL)
    {
      status = CONFIG_ITEM_NOT_FOUND;
      break;
    }
    else
    {

      //Config entry is found. Allocate handle
      status =  cfg_handle_allocate(&config_data->cfg_handle_list, &config_data->cfg_handle_max_count,
                                     &config_data->cfg_handle_count, config_handle);
      if (status != CONFIG_SUCCESS)
        break;

      //Update handle with config data info
      config_data->cfg_handle_list[(*config_handle)].config_entry_index = index;
      *config_item_size = item_entry_ptr->size;
      config_data->cfg_handle_count++;
    }
  } while (0);

  return status;
}/* cfg_itme_config_open_first_dtb */

/*===========================================================================
**  Function :  cfg_item_config_open_next_dtbo
** ==========================================================================
*/
/*!
*
* @brief
*   This function parses config items to get best match DTBO binary
* @param[in]        chipinfo                 64-bit chip code
*                   platforminfo             64-bit platform code
*                   config_name_starts_with  Null terminated config item [partial] name string
*                   state                    which DTBO to get.
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*               state             current match states.
*
* @par Dependencies
*   CONFIG module should have been initialized via CONFIG_init
*   before calling CONFIG_open
*
* @retval
*   config_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_item_config_open_next_dtbo
(
  uint64  chipinfo,
  uint64  platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size,
  cfg_dtbo_state_type *state
)
{
  cfg_metadata_table_entries_type *item_entry_ptr;
  config_status_type status = CONFIG_SUCCESS;
  uintnt index;
  cfg_item_list_type *p_dtbo_node, *p_dtbo_list;
  uint64 cplatforminfo;

  /*Check input parameters*/
  do
  {
    if ( config_handle == NULL || config_item_size == NULL || state == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    if (config_data == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }
    if (*state > CFG_GET_MAX_DTBO)
    {
      status = CONFIG_INVALID_DTBO_STATE;
      break;
    }
  } while (0);

  if (status != CONFIG_SUCCESS)
    return status;


  do
  {
    if ( *state == CFG_GET_MAX_DTBO)
    {
      status = CONFIG_DTBO_NOTFOUND;
      break;
    }

    /*If it is SOC dtbo, go to search in soc dtbo list, otherwise goto search in platform list */
    if (*state==CFG_GET_SOC_DTBO)
    {
      p_dtbo_list = config_data->cfg_sort_table->p_soc_dtbo_list;
      cplatforminfo = 0;
    }
    else
    {
      p_dtbo_list = config_data->cfg_sort_table->p_platform_dtbo_list;
      cplatforminfo = platforminfo;
    }

    //Parse config table entries to locate item.
    for (p_dtbo_node = p_dtbo_list; p_dtbo_node!=NULL; p_dtbo_node=p_dtbo_node->p_next_item)
    {
      item_entry_ptr = p_dtbo_node->entry_ptr;

      if (config_match_chipinfo(&chipinfo, (void *)&item_entry_ptr->chipinfo)!= TRUE)
        continue;

      if (config_match_platforminfo(&cplatforminfo, (void *)&item_entry_ptr->platforminfo) != TRUE)
        continue;

      /* if config name provide and it is not the second match in first enter, do config name matching.*/
      if (config_name_starts_with != NULL)
      {
        if (strncmp(config_name_starts_with, (char *)&item_entry_ptr->config_name_start, strlen(config_name_starts_with)) != 0)
          continue;
      }

      index = p_dtbo_node->index;
      break; /*bingo the dtbo has been found*/

    }

    if (p_dtbo_node == NULL)
    {
      /*if DTBO was not found in currect list , bump state and continue to search next dtbo list */
      *state=*state+1;
      continue;
    }
    else
    {
      /*DTBO is found. Allocate handle*/
      status =  cfg_handle_allocate(&config_data->cfg_handle_list, &config_data->cfg_handle_max_count,
                                     &config_data->cfg_handle_count, config_handle);
      if (status != CONFIG_SUCCESS)
        break;
      /*Update handle with config data info*/
      config_data->cfg_handle_list[(*config_handle)].config_entry_index = index;
      *config_item_size = item_entry_ptr->size;
      config_data->cfg_handle_count++;
      /*Bump the state and return to client side*/
      *state=*state+1;
      break;
    }

  } while (1);

  return status;
}/* cfg_item_config_open_next_dtbo */

/*===========================================================================
**  Function :  cfg_item_config_read
** ==========================================================================
*/
/*!
*
* @brief
*   This function copies config item data equal to input "size" from read offset
*   into provided buffer
*
* @param[in]    config_handle   Handle to identify config item to be read
*               read_offset     Offset within config item to start read
*               size            Size of data to be read
*
* @param[out]   buffer          Data buffer provided by callee for reading data
*
* @par Dependencies
*   NOTE:   The user of config_read api has to allocate memory and
*           point it via buffer for loading data.
*
* @retval
*   config_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_item_config_read
(
  const uint32 config_handle,
  uint32 read_offset,
  uint32 size,
  void *buffer
)
{
  config_status_type status = CONFIG_READ_ERR;
  cfg_metadata_table_entries_type *item_entry_ptr;
  uintnt parsed_entry_index = 0, total_offset = 0;
  uint32 config_item_start = 0, test_size = 0;
  do
  {
    if(config_data == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    if(buffer == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    if(size == 0)
    {
      status = CONFIG_INVALID_SIZE;
      break;
    }
    if((config_handle >= config_data->cfg_handle_max_count) ||
        config_data->cfg_handle_list[config_handle].is_valid == FALSE)
    {
      break;
    }

    /* check for overflow */
    test_size = read_offset + size;
    if(test_size < size)
    {
      status = CONFIG_OVERFLOW_ERR;
      break;
    }

    parsed_entry_index = config_data->cfg_handle_list[config_handle].config_entry_index;
    item_entry_ptr = config_data->config_entry_list[parsed_entry_index].entry_ptr;
    config_item_start = item_entry_ptr->offset_from_meta_start;

    /* ensure data to be read is within bounds. read offset + requested size
       will not exceed max config item size
    */
    if(read_offset > item_entry_ptr->size ||
        (read_offset + size) > item_entry_ptr->size)
    {
      status = CONFIG_INVALID_SIZE;
      break;
    }

    total_offset =  config_data->cfg_metadata_start_offset + config_item_start + read_offset;
    if(total_offset < config_data->cfg_metadata_start_offset)
    {
      status = CONFIG_OVERFLOW_ERR;
      break;
    }

    status = cfg_image_interface->get_block_data(total_offset, (uintnt)size, buffer, TRUE);

    if(status != CONFIG_SUCCESS)
      break;

  }
  while(0);
  if(status != CONFIG_SUCCESS && cfg_image_interface->cfg_error_handler != NULL )
  {
    status = cfg_image_interface->cfg_error_handler((uint32)status);
  }
  return status;
}/* cfg_item_config_read */

/*===========================================================================
**  Function :  cfg_item_config_close
** ==========================================================================
*/
/*!
*
* @brief
*   This function free's config handle to be closed(sets to 0)
*
* @param[in]  config_handle   Handle to be closed
*   None
*
* @par Dependencies
*   NOTE:   The user of config_close api has to free memory
*           used for reads associated with the handle to be closed.
*
* @retval
*   config_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
config_status_type cfg_item_config_close (uint32 config_handle)
{
  config_status_type status = CONFIG_CLOSE_ERR;

  do
  {
    if(config_data == NULL)
    {
      status = CONFIG_UNINITIALIZED;
      break;
    }

    if((config_handle >= config_data->cfg_handle_max_count) ||
        config_data->cfg_handle_count == 0)
    {
      break;
    }

    if(config_data->cfg_handle_list[config_handle].is_valid != FALSE)
    {
      /*Ensure handle is not already freed to avoid handle count
        underrun across multiple api invocations for same handle
      */
      config_data->cfg_handle_list[config_handle].config_entry_index = 0;
      config_data->cfg_handle_list[config_handle].is_valid = FALSE;
      config_data->cfg_handle_count--;
      status = CONFIG_SUCCESS;
    }
  }
  while(0);

  return status;
} /* cfg_item_config_close */

/*===========================================================================
**  Function :  cfg_item_config_deinit
** ==========================================================================
*/
/*!
*
* @brief
*   This function deinitializes config module. Free's all internal allocated
*   buffers
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
config_status_type cfg_item_config_deinit(void)
{
  config_status_type status = CONFIG_DEINIT_ERR;

  do
  {

    /* Free all allocated buffers */
    status = cfg_free((void**)&config_data->cfg_metadata_buff);
    if(status != CONFIG_SUCCESS)
      break;

    status = cfg_free((void**)&config_data->config_entry_list);
    if(status != CONFIG_SUCCESS)
      break;

    status = cfg_free((void**)&config_data->cfg_handle_list);
    if(status != CONFIG_SUCCESS)
      break;

    status = cfg_free((void**)&config_data->cfg_sort_table);
    if (status != CONFIG_SUCCESS)
      break;

    status = cfg_image_interface->deinit();
    if (status != CONFIG_SUCCESS)
      break;

    /* reset config item handle counts*/
    config_data->cfg_handle_max_count = 0;
    config_data->cfg_handle_count = 0;

    config_data->max_config_entries = 0;

    status = cfg_free((void**)&config_data);
    if(status != CONFIG_SUCCESS)
      break;

    status = CONFIG_SUCCESS;

  }
  while(FALSE);

  return status;
} /* cfg_item_config_deinit */

