/** @file FvUtilsEnhanced.c

Implementation for Qualcomm FV Utils protocol.

Copyright (c) 2022 Qualcomm Technologies, Inc. All rights
reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/18/22   jj      Initial revision.  

=============================================================================*/

#include <Library/GuidedFvLib.h>

/**
FV PROTOCOL interfaces
*/
#include <Protocol/EFIFVUtils.h>

BOOLEAN
CheckIfFvMounted (IN EFI_FV_PROTOCOL *This,
                  EFI_GUID           *FvGuid)
{
    DEBUG((EFI_D_INFO, "[FVUtilsProtocol]: GuidedFvIsMounted Invoked\n"));
    return GuidedFvIsMounted(FvGuid);
}

EFI_STATUS
LoadFileFromFv (IN EFI_FV_PROTOCOL *This,
                EFI_GUID           *FvGuid,
				CHAR8      		   *FileName,
				OUT UINT8 		   **FileBuffer,
                OUT UINTN  		   *FileSize)
{
    DEBUG((EFI_D_INFO, "[FVUtilsProtocol]: LoadFileFromGuidedFv Invoked\n"));
    return LoadFileFromGuidedFv(FvGuid, FileName, FileBuffer, FileSize);
}
