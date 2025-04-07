#ifndef CONFIG_UTILS_H
#define CONFIG_UTILS_H
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
05/10/17     kpa      Added xcfg_malloc wrapper
04/05/17     kpa      Initial version
===========================================================================*/
 

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include <stdint.h>
#include "cfg_item_config.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

#define CFG_UINT32_MAX     UINT32_MAX

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
config_status_type cfg_malloc
(
  uintnt buff_size,
  void **cfg_buff_ptr
);

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
);

#endif /* CONFIG_UTILS_H */
