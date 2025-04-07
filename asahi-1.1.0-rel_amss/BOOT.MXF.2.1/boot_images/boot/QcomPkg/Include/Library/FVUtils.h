/** @file FVUtils.h

  API declarations for FVUtils.h

  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when        who      what, where, why
 --------    ---      ----------------------------------------------------------
 03/09/2023  da       Initial revision
=============================================================================*/
#ifndef __FVUTILS_H__
#define __FVUTILS_H__

#include <Protocol/EFIFVUtils.h>

BOOLEAN
CheckIfFvMounted (IN EFI_FV_PROTOCOL *This,
                  EFI_GUID           *FvGuid);

EFI_STATUS
LoadFileFromFv (IN EFI_FV_PROTOCOL *This,
                EFI_GUID           *FvGuid,
                CHAR8              *FileName,
                OUT UINT8          **FileBuffer,
                OUT UINTN          *FileSize);

#endif  /* __FVUTILS_H__*/

