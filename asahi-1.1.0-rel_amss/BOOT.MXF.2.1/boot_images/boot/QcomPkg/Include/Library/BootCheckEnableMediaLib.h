/** @file BootCheckEnableMediaLib.h

  Library to install UFSDXE if parition exists in SPINOR

  Copyright (c) 2023 by Qualcomm Technologies, Inc. All Rights Reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/20/23   vv      Initial revision.

=============================================================================*/

#ifndef __UFSINSTALLLIB_H__
#define __UFSINSTALLLIB_H__

#include <Uefi.h>
#include <Library/QcomLib.h>

#define EFI_SPINOR_UFS_FLAG_GUID \
 { \
    0xFDE4B5D4, 0xDEDD, 0x11ED, {0xB5, 0xEA, 0x02, 0x42, 0xAC, 0x12, 0x00, 0x02}\
 }


/** Check if empty partiion exists in spinor-ufs*/
BOOLEAN
EFIAPI CheckEnableMedia(VOID);


#endif /* __UFSINSTALLLIB_H__ */
