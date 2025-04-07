/** @file FwUpdateInfoLib.c

This file contains functions which capture FwUpdate related info which 
can be utilized by other modules

Copyright (c) 2023 Qualcomm Technologies, Inc.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.

**/

/*=============================================================================
                              EDIT HISTORY


when         who       what, where, why
--------     ---       ----------------------------------------------------------- 
2023/03/10   gpavithr  Initial revision

=============================================================================*/

#include <FwUpdateInfoLib.h>
#include <Guid/GlobalVariable.h>
#include <Library/GenericBdsLib.h>

/**
    Function to check if there are any pending capsules.

    @retval  TRUE    Capsule pending.
    @retval  FALSE   No pending capsules.

**/
BOOLEAN
CheckIfCapsulePending (VOID)
{
    BOOLEAN                isCapsulePending                 = FALSE;
    UINTN                  bufferSize                       = 0;
    BOOLEAN               *isCapsulePendingInPersistedMedia = NULL;
    UINT64                *osIndications                    = NULL;

    isCapsulePendingInPersistedMedia = BdsLibGetVariableAndSize (
        L"IsCapsulePendingInPersistedMedia",
        &gEfiGlobalVariableGuid,
        &bufferSize
        );
    if ((isCapsulePendingInPersistedMedia != NULL) &&
        (*isCapsulePendingInPersistedMedia))
    {
        isCapsulePending = TRUE;
        goto Exit;
    }
    else
    {
        osIndications = BdsLibGetVariableAndSize (
            L"OsIndications",
            &gEfiGlobalVariableGuid,
            &bufferSize
            );
        if ((osIndications != NULL) &&
          (*osIndications & EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED))
        {
            isCapsulePending = TRUE;
            goto Exit;
        }
    }

Exit:
    DEBUG((EFI_D_WARN, "CheckIfCapsulePending: isCapsulePending:[%d]\n", isCapsulePending));
    return isCapsulePending;
}
  
