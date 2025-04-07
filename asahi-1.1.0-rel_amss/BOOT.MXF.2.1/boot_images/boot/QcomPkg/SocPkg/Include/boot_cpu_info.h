#ifndef BOOT_CPU_INFO_H
#define BOOT_CPU_INFO_H
/*=============================================================================

                            CPU Info

GENERAL DESCRIPTION
  Internal header for Boot CPU Info.

Copyright 2023 by Qualcomm Technologies, Inc. All rights reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who          what, where, why
--------   ---          ----------------------------------------------------------
04/10/23   ak           Initial revision.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES
               
===========================================================================*/
#include <boot_error_if.h>

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

bl_error_boot_type GetTargetBootCore (uint32 *core);


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

bl_error_boot_type GetTargetBootCluster (uint32 *cluster);


#endif  /* BOOT_CPU_INFO_H */