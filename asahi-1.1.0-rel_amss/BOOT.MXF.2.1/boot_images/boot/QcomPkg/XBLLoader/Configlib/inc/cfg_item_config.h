#ifndef CFG_ITEM_CONFIG_H
#define CFG_ITEM_CONFIG_H

/*=============================================================================

                            ConfigLib Module Sources

GENERAL DESCRIPTION
  This file defines ConfigLib api's to support initializing ConfigLib module
  and access a config item.

Copyright 2016, 2017, 2020-2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
05/31/22     yps      Port DTBO Best Match algorithm from core.boot.6.1
03/28/22     tmt      Port pre-DTBO Best-Match algorithm from core.boot.6.1
12/20/21     yps      Add chipinfo and platforminfo hierarchy structures
11/11/21     tmt      Fix config_status_type config_create_platforminfo() encoding
09/08/21     tmt      Port to QDSP -> ConfigLib (Config.h -> cfg_item_config.h)
06/25/21     tmt      Add DTB support: config_open_by_hwinfo, config_chipinfo, config_platforminfo
10/16/20     rama     Added initialization mode to config_init
05/10/17     kpa      rename CONFIG_SIZE_OVERFLOW_ERR to CONFIG_OVERFLOW_ERR
03/10/17     kpa      Added error codes, update config_read parameters
03/03/17     kpa      Added error type and XCFG_LOADER_MAGIC_COOKIE_SIZE
02/14/17     kpa      Rename CONFIG_ERR_NONE to CONFIG_SUCCESS
01/20/17     kpa      Update magic cookie
10/14/16     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "cfg_comdef.h"


/*===========================================================================
                      DATA DECLARATIONS
===========================================================================*/

#define CFG_LOADER_MAGIC_COOKIE_SIZE  4

/*  Define ConfigLib loader magic number "CFGL" */
#define CFG_LOADER_MAG0_INDEX    0      /* Header identification byte 0 index */
#define CFG_LOADER_MAG0         'C'     /* Magic number byte 0              */

#define CFG_LOADER_MAG1_INDEX    1      /* Header identification byte 1 index */
#define CFG_LOADER_MAG1         'F'     /* Magic number byte 1              */

#define CFG_LOADER_MAG2_INDEX    2     /* Header identification byte 2 index */
#define CFG_LOADER_MAG2         'G'    /* Magic number byte 2              */

#define CFG_LOADER_MAG3_INDEX    3     /* Header identification byte 3 index */
#define CFG_LOADER_MAG3         'L'    /* Magic number byte 3              */


/*  Define ConfigLib Core magic number "CFGU" */
#define CFG_CORE_MAG0_INDEX    0      /* Header identification byte 0 index */
#define CFG_CORE_MAG0         'C'     /* Magic number byte 0              */

#define CFG_CORE_MAG1_INDEX    1      /* Header identification byte 1 index */
#define CFG_CORE_MAG1         'F'     /* Magic number byte 1              */

#define CFG_CORE_MAG2_INDEX    2     /* Header identification byte 2 index */
#define CFG_CORE_MAG2         'G'    /* Magic number byte 2              */

#define CFG_CORE_MAG3_INDEX    3     /* Header identification byte 3 index */
#define CFG_CORE_MAG3         'U'    /* Magic number byte 3              */


#define CFG_CONFIG_MAJOR_VERSION          0X2
#define CFG_CONFIG_MINOR_VERSION          0X0

#define CFG_CONFIG_MAX_NUM_ENTRIES        0X9
#define CFG_CONFIG_MAX_HANDLES            0X5

/* boot_boolean data type used for boolean variables shared with pbl*/
typedef  unsigned int       boot_boolean;     /* uint32 Boolean value type. */
typedef struct cfg_metadata_header_type
{
  uint32 cfg_type;
  uint8 major_version; 
  uint8 minor_version; 
  uint16 number_of_entries; 
  uint32 config_meta_size;
} cfg_metadata_header_type;


typedef struct cfg_metadata_table_entries_type
{
  uint32 attributes;
  uint32 offset_from_meta_start; 
  uint32 size;
  uint64 chipinfo;
  uint64 platforminfo;
  uint32 config_name_len; 
  char   config_name_start;
} __attribute__ ((packed)) cfg_metadata_table_entries_type;


typedef struct cfg_parsed_metadata_table_entry_type
{
  /* pointer to start of entry in blob */
  cfg_metadata_table_entries_type *entry_ptr;

}cfg_parsed_metadata_table_entry_type;

typedef struct cfg_config_handle_type
{
  uintnt config_entry_index;
  boolean is_valid;
}cfg_config_handle_type;

typedef struct chipinfo_hierarchy
{
  uint16 reserved; 
  uint8  Minor_version;
  uint8  Major_version;
  uint16 ChipId;
  uint16 ChipFamily;
} __attribute__ ((packed)) chipinfo_hierarchy_type;

typedef struct platfrominfo_hierarchy
{
  uint8  reserved[3];
  uint8  Oem_flavor_id;
  uint8  Minor_version;
  uint8  Major_version;
  uint8  PlatformSubtype; 
  uint8  Platformtype;
} __attribute__ ((packed)) platfrominfo_hierarchy_type;

/*---------------------------------------------------------------------------
 ENUMS FOR INITIALIZING CONFIGLIB FROM LOADER,RAM ELF AND RAM ADDRESS
 ---------------------------------------------------------------------------*/
typedef enum
{
  CONFIG_INIT_FROM_FLASH = 0,
  CONFIG_INIT_FROM_RAM_ADDRESS
}config_init_mode_type;

/*---------------------------------------------------------------------------
 ERRORS FROM CONFIGLIB
 ---------------------------------------------------------------------------*/
typedef enum
{
  CONFIG_SUCCESS                            = 0X0000,
  CONFIG_ITEM_NOT_FOUND                     = 0X0001,
  CONFIG_INVALID_SIZE                       = 0X0002,
  CONFIG_META_DATA_LOAD_ERR                 = 0X0003,  
  CONFIG_CONFIG_DATA_LOAD_ERR               = 0X0004,  
  CONFIG_INIT_ERR                           = 0X0005,
  CONFIG_OPEN_ERR                           = 0X0006,
  CONFIG_READ_ERR                           = 0X0007,
  CONFIG_CLOSE_ERR                          = 0X0008,
  CONFIG_MEMORY_ALLOCATION_ERR              = 0X0009,
  CONFIG_HASH_SEG_ERR                       = 0X000A,
  CONFIG_NULL_PTR_ERR                       = 0X000B,  
  CONFIG_HANDLE_ERR                         = 0X000C,  
  CONFIG_VERIFY_ERR                         = 0X000D,  
  CONFIG_UNINITIALIZED                      = 0X000E,  
  CONFIG_BUFFER_VALIDATION_ERR              = 0X000F,  
  CONFIG_RAM_ELF_INFO_INIT_ERR              = 0X0010,
  CONFIG_MEMORY_FREE_ERR                    = 0X0011,
  CONFIG_DEINIT_ERR                         = 0X0012,  
  CONFIG_OVERFLOW_ERR                       = 0X0013,  
  CONFIG_INVALID_NAME                       = 0X0014,
  CONFIG_CHIPFAMILY_DTB_NOTFOUND            = 0X0015,
  CONFIG_DTBO_NOTFOUND                      = 0X0016,
  CONFIG_DTBO_MERGE_FAILED                  = 0X0017,
  CONFIG_ADD_SORT_LIST_FAILED               = 0X0018,
  CONFIG_INVALID_DTBO_STATE                 = 0X0019,
  CONFIG_RECOVERY_ERR                       = 0X0020,
  CONFIG_INVALID_PARAMETER                  = 0X0021,
  CONFIG_ERR_MAX                            = 0x7FFF
} config_status_type;



typedef enum
{
  CFG_GET_INITIALIZED                        = 0X0000,
  CFG_GET_SOC_DTBO                           = CFG_GET_INITIALIZED,
  CFG_GET_PLAT_DTBO                          ,
  CFG_GET_MAX_DTBO                                                             
} cfg_dtbo_state_type;
/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/


/*===========================================================================
**  Function :  cfg_item_config_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes ConfigLib module
* 
* @param[in] 
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/

config_status_type cfg_item_config_init(config_init_mode_type mode_type);

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
*   ConfigLib module should have been initialized via config_init()
*   before calling config_open()
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
);

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
);


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
*     [55..48] Platform_Type
*     [47..40] Major_Version
*     [39..32] Minor_Version
*     [31..0]  Reserved
*
* @param[in]         pType                        8-bit platform Type
*                    pVersion                     16-bit Platform Version
*                    pSubtype                     8-bit Platform SubType
*                    pOemVariant                  8-bit OEM Variant Id
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
  uint8     pType,
  uint16   pVersion,
  uint8    pSubtype,
  uint8    pOemVariant,
  uint64  *platforminfo
);

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
config_status_type cfg_item_config_open_next_dtbo
(
  uint64  chipinfo,
  uint64  platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size,
  cfg_dtbo_state_type *state
);
 /*===========================================================================
 **  Function :  cfg_item_config_open_first_dtb
 ** ==========================================================================
 */
 /*!
 *
 * @brief
 *   This function parses  config meta data to locate config item and
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
 *   config module should have been initialized via config_init
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
);
/*===========================================================================
**  Function :  cfg_item_config_read
** ==========================================================================
*/
/*!
* 
* @brief
*   This function copies ConfigLib item data equal to input "size" from read offset
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
);

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
config_status_type cfg_item_config_close (uint32 config_handle);

/*===========================================================================
**  Function :  cfg_item_config_deinit
** ==========================================================================
*/
/*!
* 
* @brief
*   This function deinitializes ConfigLib module. Free's all internal allocated
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
config_status_type cfg_item_config_deinit(void);
config_status_type config_ramlib_init
(
  uintnt *cfg_ram_start_address
);


#endif /* CFG_ITEM_CONFIG_H */
