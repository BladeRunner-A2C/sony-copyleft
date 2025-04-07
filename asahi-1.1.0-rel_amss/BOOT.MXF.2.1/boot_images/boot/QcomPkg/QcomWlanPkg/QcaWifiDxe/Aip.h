/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __AIP_H
#define __AIP_H

#include <Uefi.h>

EFI_STATUS
EFIAPI
QcWlanAipGetInfo(
    IN   EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    IN   EFI_GUID                         *InformationType,
    OUT  VOID                             **InformationBlock,
    OUT  UINTN                            *InformationBlockSize
);

EFI_STATUS
EFIAPI
QcWlanAipSetInfo(
    IN   EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    IN   EFI_GUID                         *InformationType,
    IN   VOID                             *InformationBlock,
    IN   UINTN                            InformationBlockSize
);

EFI_STATUS
EFIAPI
QcWlanAipGetSupportedTypes(
    IN    EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    OUT   EFI_GUID                         **InfoTypesBuffer,
    OUT   UINTN                            *InfoTypesBufferCount
);

#endif // !__AIP_H