#ifndef BOOT_COMMON_MAP_H
#define BOOT_COMMON_MAP_H

/*===========================================================================

                        Boot memory map header

GENERAL DESCRIPTION
  This header file contains the definitions of COMMON memory mapping APIs

Copyright 2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/08/22   rama    Initial revision.

============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "common_mem_map.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS
                      
===========================================================================*/



/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/
/*===========================================================================
**  Function :  xbl_uncached_memmap_init
** ==========================================================================
*/
/*!
*
* @brief
*   Map uncached region
*
* @param[in]
*   boot_handle   Handle passed by caller
*   uintnt        base address of uncached region to be mapped
*   uintnt        size of uncached region to be mapped
*
* @par Dependencies
*   None
*
* @retval
*   BL_ERR_NONE on success
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type xbl_uncached_memmap_init(boot_handle config_context,
                                            uintnt base,
                                            uintnt size);

#endif /* BOOT_COMMON_MAP_H */

