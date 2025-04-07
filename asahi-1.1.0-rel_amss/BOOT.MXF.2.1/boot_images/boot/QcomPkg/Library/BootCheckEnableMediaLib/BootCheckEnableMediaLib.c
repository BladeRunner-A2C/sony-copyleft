/*********************************************************************
 * @file BootCheckEnableMediaLib.c
 *
 * @brief Library to enable UFSDXE if parition exits in  Spinor
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
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN ElfSize = 0;
  UINT8* ElfBuffer = NULL;
  CHAR16  *LabelStr = NULL ;
  BOOLEAN ReturnVal;
  static BOOLEAN printonce = TRUE;

  EFI_GUID PartiGuid = EFI_SPINOR_UFS_FLAG_GUID;

  Status = ReadFromPartition (&PartiGuid, LabelStr, (VOID**)&ElfBuffer, &ElfSize, 0);
  if (Status == EFI_SUCCESS){
     ReturnVal = FALSE;
   }
   else {
     ReturnVal = TRUE;
  }

  if(printonce) {
     if (ReturnVal == FALSE) {
       DEBUG ((EFI_D_WARN, "Partition to control UFS enable/disable is present\n"));
     }
     else {
       DEBUG ((EFI_D_WARN, "Partition to control UFS enable/disable not present\n"));
    }
    printonce = FALSE;
  }

  return ReturnVal;
}

