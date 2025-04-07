/** @file SPSSDxe.c

  Implements the Qualcomm's driver that loads SPSS

  Copyright (c) 2019 - 2022,  Qualcomm Technologies Inc. All 
  rights reserved. 

**/

/*=============================================================================
                              EDIT HISTORY


 when         who     what, where, why
 --------     ---     -----------------------------------------------------------
 12/05/22     gn      Merge Hamoa and Lanai SPSS drivers to use SPSSLib
 11/24/22     eb      Add Support for sharing Keymint info with SPU
 08/11/22     ll      Update SPSS PIL loading address for Lanai per ipcat
 07/31/22     nl      Fix: Init pEfiChipInfoProtocol before using it
 07/07/22     me      Update SPSS PIL loading address for Halliday per ipcat and 
                      Update chipFamily check to check for Halliday
 05/27/22     bxr     Change file coded format to be UTF-8
 04/07/22     ll      Update SPSS PIL loading address for Kailua per ipcat
 02/14/22     nl      Remove the WA, set SP_CNOC_SP_SCSR_RMB_GPm
 02/07/22     vp      Temporary WA, to avoid setting SP_CNOC_SP_SCSR_RMB_GPm
 02/05/22     nl      Fix a bug in reading SPSS configuration
 09/30/21     nl      Updates for Kailua support removing Waipio support
 06/29/21     av      Add support for 1.5MB image size
 06/29/21     sg      Add WA to consider SPSS config_mode b'11 as PROD type
 01/20/20     ll      Updates for Waipio support removing Lahaina support
 10/29/20     mm      Updated Lahaina power alarm GPIO as b7
 06/17/20     av      Write to a GP register if SPSS load attempt fails
 06/05/20     av      Replace chipID check with chipFamily,load 1t/p images on R2
 05/20/20     av      Update chipID check to include all Lahaina variants
 01/23/20     kv      Updates for Lahaina support
 06/21/19     as      Add IAR support
 06/18/19     av      Read SECURITY CONTROL CORE register for image type
 06/05/19     av      Initial revision - introduce driver that loads SPSS
 
=============================================================================*/
#include <Uefi.h>
#include <Library/SPSSLib.h>
/**
File Logging Dependencies
*/
#include "ULogFront.h"
#include "ULogUEFI.h"

/*===========================================================================*/
/*                  FUNCTIONS DEFINITIONS                                    */
/*===========================================================================*/

/**
*  SPSSDxe_Generic_Entry ()
*
* @brief  Initialize SPSS from the SPSSLib
*
* @return EFI_SUCCESS or error code
*/
EFI_STATUS SPSSDxe_Generic_Entry
(
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
)
{
  EFI_STATUS Status   = EFI_LOAD_ERROR;

  Status = SPSSLib_Entry(ImageHandle, SystemTable);

  return Status;
}
