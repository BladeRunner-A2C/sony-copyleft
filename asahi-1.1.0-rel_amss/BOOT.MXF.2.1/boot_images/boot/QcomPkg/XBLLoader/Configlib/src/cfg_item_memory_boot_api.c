/*=============================================================================

                            ConfigLib Module Sources

GENERAL DESCRIPTION
  This file defines ConfigLib api's to provide wrappers around system memory functions.
  The entry-points in this file are expected to change when ConfigLib is ported.

Copyright 2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
09/08/21     tmt      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <stdlib.h>
#include "cfg_memory_mgr_if.h"
#include "cfg_item_config.h"
#include "boot_config_context.h"
#include "boot_memory_mgr_if.h"
#include "config_utils.h"
/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

static cfg_error_type cfg_sys_malloc(uint32 dwSize, void **ppMem);
static cfg_error_type cfg_sys_memalign(uint32 dwSize, uint32 alignment, void **ppMem);
static cfg_error_type cfg_sys_free(void *pmem);

cfg_memory_mgr_if_type cfg_mem_if = {
    cfg_sys_malloc,
    NULL,
    cfg_sys_free
};

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/


/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/


/*===========================================================================
**  Function :  xcfg_malloc
** ==========================================================================
*/
/*!
*
* @brief
*   This function is a wrapper for underlying DAL memory alloc api
*
* @param[in]
*   buff_size      Requested size of memory to be alloced
*   xcfg_buff_ptr  Return parameter, callee will populate this to point to the
*                  block of alloced memory, valid only upon DAL_SUCCESS return
*                  code
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static cfg_error_type cfg_sys_malloc(uint32 dwSize, void **ppMem)
{
  cfg_error_type status = CFG_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (ppMem == NULL)
    {
      status = CFG_ERR_NULL_PTR_PASSED;
      break;
    }


    return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (return_status != BL_ERR_NONE)
    {
      status = CFG_ERR_MEMORY_ALLOC_FAIL;
      break;
    }

    return_status = mem_if->malloc(dwSize, ppMem);

    if ((return_status != BL_ERR_NONE) || (ppMem == NULL))
    {
      status = CFG_ERR_MEMORY_ALLOC_FAIL;
    }
    else
    {
      status = CFG_ERR_NONE;
    }

  } while (0);
  return status;
}



/*===========================================================================
**  Function :  xcfg_free
** ==========================================================================
*/
/*!
*
* @brief
*   This function is a wrapper for underlying DAL memory free api
*
* @param[in]
*   xcfg_buff_ptr            pointer to buffer being freed
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type.   XBLCONFIG_SUCCESS if no error else error value
*
* @par Side Effects
*   None
*
*/
static cfg_error_type cfg_sys_free
(
  void *pmem
)
{
  cfg_error_type status = CFG_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type return_status = BL_ERR_NONE;

  do
  {
    if (pmem == NULL)
    {
      status = CFG_ERR_NULL_PTR_PASSED;
      break;
    }

    if (pmem != NULL)
    {
      return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
      if (return_status != BL_ERR_NONE)
      {
        break;
      }

      return_status = mem_if->free(pmem);
      if (return_status != BL_ERR_NONE)
      {
        status = CFG_ERR_MEMORY_FREE_FAIL;
      }
      else
      {
        status = CFG_ERR_NONE;
      }
    }
  } while (0);

  return status;
}
