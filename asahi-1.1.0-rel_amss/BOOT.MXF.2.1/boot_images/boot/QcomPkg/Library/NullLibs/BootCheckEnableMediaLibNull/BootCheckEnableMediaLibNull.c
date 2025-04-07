/*********************************************************************
 * @file BootCheckEnableMediaNull.c
 *
 * @brief  Library to install UFSDXE if parition exists in Spinor
 *
 * Copyright (c) 2023 by Qualcomm Technologies, Inc. All Rights Reserved.
 *
 *********************************************************************/
/*=======================================================================
                        Edit History

 when       who     what, where, why
 --------   ----    ---------------------------------------------------
 04/20/23   vv      Initial revision.

========================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/SerialPortShLib.h>
#include <Library/BootCheckEnableMediaLib.h>


BOOLEAN
EFIAPI CheckEnableMedia(VOID){
  BOOLEAN Status = TRUE;

  return Status;
}

