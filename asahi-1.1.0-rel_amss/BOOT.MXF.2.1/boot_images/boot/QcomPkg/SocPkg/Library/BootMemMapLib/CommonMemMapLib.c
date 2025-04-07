/*===========================================================================

GENERAL DESCRIPTION
  This module contains the common BootMemMapLib functions.

  Copyright (c) 2022-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

 ==============================================================================*/
/*=============================================================================
                          EDIT HISTORY

when       who     what, where, why
--------   ---     -----------------------------------------------------------
02/15/23   ck      Renamed edk2 interfaces
12/08/22   rama    Added common_mem_map.h
02/08/22   ck      Initial revision

=============================================================================*/

#include <boot_error_if.h>
#include <boot_config_context.h>
#include <boot_mmu_if.h>
#include <common_mem_map.h>

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
                                            uintnt size)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_mmu_if_type * mmu_if = NULL;


  ARM_MEMORY_REGION_DESCRIPTOR current_entry[] =
  {
    { base, base, size, EFI_ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED_XN},
    {    0,    0,    0, 0}  /* Last Region Marker */
  };


  /* Obtain MMU interface */
  status = boot_config_context_get_ptr(config_context,
                                       CONFIG_CONTEXT_MMU_INTERFACE,
                                       (void **)&mmu_if);
  if (status != BL_ERR_NONE)
  {
    goto exit;
  }

  if (mmu_if == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_HANDLE);
    goto exit;
  }


  /* Set memory region as uncached */
  if (mmu_if->ArmSetMemoryAttributes(current_entry->PhysicalBase,
                                     current_entry->Length,
                                     current_entry->Attributes) != EFI_SUCCESS)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_MMU, BL_ERR_MMU_PGTBL_MAPPING_FAIL);
    goto exit;
  }


 exit:
  return status;
}
