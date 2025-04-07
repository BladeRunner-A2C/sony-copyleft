/*=============================================================================

                            ConfigLib Module Sources

GENERAL DESCRIPTION
  This file defines ConfigLib Utility api's.   

Copyright 2017, 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
09/08/21     tmt      Port to QDSP -> ConfigLib
05/10/17     kpa      Added xcfg_malloc
04/05/17     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "cfg_item_config.h"
#include "config_utils.h"
#include "cfg_error_if.h"
#include "cfg_memory_mgr_if.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/


/*===========================================================================
**  Function :  cfg_malloc
** ==========================================================================
*/
/*!
* 
* @brief
*   This function is a wrapper for underlying system memory alloc api
* 
* @param[in] 
*   buff_size      Requested size of memory to be alloced
*   cfg_buff_ptr   Return parameter, callee will populate this to point to the
*                  block of alloced memory, valid only upon SUCCESS return
*                  code
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
config_status_type cfg_malloc(uintnt buff_size, void **cfg_buff_ptr)
{
  config_status_type status = CONFIG_MEMORY_ALLOCATION_ERR;  
  cfg_error_type return_status = CFG_ERR_NONE;
  
  do
  {
    if(cfg_buff_ptr == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
    
    if(buff_size > CFG_UINT32_MAX)
    {
      /* Limit buffer sizes to 32-bit to avoid port issues with 64-bit */
      status = CONFIG_OVERFLOW_ERR;
      break;
    }

    return_status = cfg_mem_if.malloc(buff_size, cfg_buff_ptr);

    if((return_status != CFG_ERR_NONE) || (cfg_buff_ptr == NULL))
    {
      status = CONFIG_MEMORY_ALLOCATION_ERR;
    }
    else 
    {
      status = CONFIG_SUCCESS;
    }
    
  } while(0);
  return status;  
}



/*===========================================================================
**  Function :  cfg_free
** ==========================================================================
*/
/*!
* 
* @brief
*   This function is a wrapper for underlying system memory free api
* 
* @param[in] 
*   cfg_buff_ptr            pointer to buffer being freed
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
config_status_type cfg_free
(
  void **cfg_buff_ptr
)
{
  config_status_type status = CONFIG_SUCCESS;  
  cfg_error_type return_status = CFG_ERR_NONE;

  do
  {
    if(cfg_buff_ptr == NULL)
    {
      status = CONFIG_NULL_PTR_ERR;
      break;
    }
     
    if(*cfg_buff_ptr != NULL)
    {

        return_status = cfg_mem_if.free(*cfg_buff_ptr);
        if(return_status != CFG_ERR_NONE)
        {
            status = CONFIG_MEMORY_FREE_ERR;
        }
        else
        {
            *cfg_buff_ptr = NULL;
            status = CONFIG_SUCCESS;
        }
    }
  } while(0);

  return status;  
}
