/**
@file BootRecoveryMethodCoreGpio.c

GENERAL DESCRIPTION
  This file contains functions to check if Boot recovery GPIO method is enabled and boot set to boot

Copyright 2023 Qualcomm Technologies Incorporated.  All Rights Reserved.
**/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
04/13/23   ac      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <Library/BootConfig.h>
#include <HALhwio.h>
#include <HALbootHWIO.h>

/*==============================================================================
**  Functions
**============================================================================*/

/*=========================================================================

**  Function :  RecoveryBootIsGpioMethodEnabled

** ==========================================================================
*/
/*!
*
* @brief
*   This api checks if GPIO method is enabled or not
*
*/

EFI_STATUS RecoveryBootIsGpioMethodEnabled (UINT8 *IsGpioMethodEnabled)
{
  UINT32 OemConfig0PblEnableABSel = 0;

  if (IsGpioMethodEnabled == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  /* Get fuse value to determine if GPIO base set selection is enabled */
  OemConfig0PblEnableABSel = (HWIO_OEM_CONFIG0_IN & HWIO_OEM_CONFIG0_PBL_ENABLE_AB_SEL_BMSK) >> HWIO_OEM_CONFIG0_PBL_ENABLE_AB_SEL_SHFT;
  if (OemConfig0PblEnableABSel)
  {
    *IsGpioMethodEnabled = TRUE;
  }
  else
  {
    *IsGpioMethodEnabled = FALSE;
  }
  
  return EFI_SUCCESS;
}

/*=========================================================================

**  Function :  RecoveryBootGpioBootSet

** ==========================================================================
*/
/*!
*
* @brief
*   This api gets the boot set if GPIO method is enabled
*
*/
EFI_STATUS RecoveryBootGetGpioBootSet (UINT32 *GpioBootSet)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = GetSharedImemBootSet(GpioBootSet);

  return Status;
}


