#ifndef RAMDUMP_MEM_MAP_H
#define RAMDUMP_MEM_MAP_H

/*===========================================================================

                        Boot memory map header

GENERAL DESCRIPTION
  This header file contains the definitions of RAMDUMP memory mapping APIs

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
**  Function :  ramdump_populate_mem_map
** ==========================================================================
*/
/*!
*
* @brief
*   populate the existing pbl page table with Ramdump memory mapping
*
* @param[in] bl_shared_data Pointer to shared data
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
bl_error_boot_type ramdump_populate_mem_map(boot_handle config_context_handle);


#endif /* RAMDUMP_MEM_MAP_H */

