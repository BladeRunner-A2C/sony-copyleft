/*=============================================================================

                            Module Entry Point

GENERAL DESCRIPTION
  This file contains CPU Info APIs.

Copyright 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
04/10/23   ak      Get Boot Core and Cluster APIs
=============================================================================*/


/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include <boot_cpu_info.h>
#include <boot_error_if.h>
/*=============================================================================

                              DEFINITIONS

=============================================================================*/
#define MPIDR_AFFINITY_MASK    0xFFFF
#define AFF1_BIT_SHIFT         0x8
#define AFF2_BIT_SHIFT         0x16

/*===========================================================================

**  Function : GetTargetBootCore

** ==========================================================================
*/
/*!
*
* @brief
*   Get Boot Core value.
*
* @par Dependencies
*   uint32 *core
*
* @retval
*   bl_error_boot_type
*
* @par Side Effects
*   None
*/

bl_error_boot_type GetTargetBootCore (uint32 *core)
{
  uint64 Mpidr = 0;
  
  if(core != NULL)
  {
    __asm__ __volatile__("mrs %0, MPIDR_EL1":"=r"(Mpidr));
    /* Aff1 shows the bootcore */
    *core = ((Mpidr & (MPIDR_AFFINITY_MASK))>> AFF1_BIT_SHIFT);
  }
  return BL_ERR_NONE;
}


/*===========================================================================

**  Function : GetTargetBootCluster

** ==========================================================================
*/
/*!
*
* @brief
*   Get Boot Cluster value.
*
* @par Dependencies
*   uint32 *cluster
*
* @retval
*   bl_error_boot_type
*
* @par Side Effects
*   None
*/

bl_error_boot_type GetTargetBootCluster (uint32 *cluster)
{
  uint64 Mpidr = 0;
  if(cluster != NULL)
  {
    __asm__ __volatile__("mrs %0, MPIDR_EL1":"=r"(Mpidr));
    
    /* Aff2 shows the boot cluster */
    *cluster = ((Mpidr & (MPIDR_AFFINITY_MASK))>> AFF2_BIT_SHIFT);
  }
  return BL_ERR_NONE;
}
