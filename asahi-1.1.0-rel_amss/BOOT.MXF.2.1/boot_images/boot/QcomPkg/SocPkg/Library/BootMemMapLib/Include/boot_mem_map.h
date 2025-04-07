#ifndef BOOT_MEM_MAP_H
#define BOOT_MEM_MAP_H

/*===========================================================================

                        Boot memory map header

GENERAL DESCRIPTION
  This header file contains the definitions of BOOT memory mapping APIs

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
**  Function :  xbl_populate_initial_mem_map
** ==========================================================================
*/
/*!
*
* @brief
*   populate the existing pbl page table with SBL memory mapping
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
bl_error_boot_type xbl_populate_initial_mem_map(boot_handle config_context_handle);

/*===========================================================================
**  Function :  xbl_populate_additional_mem_map
** ==========================================================================
*/
/*!
*
* @brief
*   This function populates additional memory maps after DDR init 
*
* @param[in] boot_handle
*
* @par Dependencies
*   DDR must be initialized before calling this API
*
* @retval
*   BL_ERR_NONE  on success
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type xbl_populate_additional_mem_map(boot_handle config_context_handle);

/*===========================================================================
**  Function :  xbl_map_postinit_ddr
** ==========================================================================
*/
/*!
*
* @brief
*   Updated the DDR range mapping after DDR is initialized
*
* @param[in] 
*   boot_handle   handle passed by caller
*   uint64        base address of DDR range to be mapped
*   uint64        size of DDR range to be mapped
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
bl_error_boot_type xbl_map_postinit_ddr(boot_handle config_context_handle, uint64 base, uint64 size);

/*===========================================================================
**  Function :  xbl_map_preinit_ddr
** ==========================================================================
*/
/*!
*
* @brief
*   Map DDR range to device shared before DDR init
*
* @param[in] boot_handle
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
bl_error_boot_type xbl_map_preinit_ddr(boot_handle config_context_handle);

/*===========================================================================
**  Function :  xbl_map_smem
** ==========================================================================
*/
/*!
*
* @brief
*   Update smem range mapping
*
* @param[in] boot_handle
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
bl_error_boot_type xbl_map_smem(boot_handle config_context_handle);

#endif /* BOOT_MEM_MAP_H */

