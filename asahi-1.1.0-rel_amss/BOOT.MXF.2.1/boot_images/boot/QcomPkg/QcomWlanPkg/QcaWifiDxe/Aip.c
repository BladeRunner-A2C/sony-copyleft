/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 Copyright (c) 2015 - 2018, Intel Corporation. All rights reserved.<BR>
 This program and the accompanying materials
 are licensed and made available under the terms and conditions of the BSD License
 which accompanies this distribution.  The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php

 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN ""AS IS"" BASIS,
 WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 18/11/21  zxue     refine code
 6/9/21    zxue     fix parasoft issue
 14/7/21   zxue     add missing copyright
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/interrupt.h>
#include "Dev.h"
#include "Debug.h"
#include "Aip.h"
#include "QcaWlan.h"

 /**
   Returns the current state information for the adapter.

   This function returns information of type InformationType from the adapter.
   If an adapter does not support the requested informational type, then
   EFI_UNSUPPORTED is returned.

   @param[in]  This                   A pointer to the EFI_ADAPTER_INFORMATION_PROTOCOL instance.
   @param[in]  InformationType        A pointer to an EFI_GUID that defines the contents of InformationBlock.
   @param[out] InformationBlock       The service returns a pointer to the buffer with the InformationBlock
                                      structure which contains details about the data specific to InformationType.
   @param[out] InformationBlockSize   The driver returns the size of the InformationBlock in bytes.

   @retval EFI_SUCCESS                The InformationType information was retrieved.
   @retval EFI_UNSUPPORTED            The InformationType is not known.
   @retval EFI_DEVICE_ERROR           The device reported an error.
   @retval EFI_OUT_OF_RESOURCES       The request could not be completed due to a lack of resources.
   @retval EFI_INVALID_PARAMETER      This is NULL.
   @retval EFI_INVALID_PARAMETER      InformationBlock is NULL.
   @retval EFI_INVALID_PARAMETER      InformationBlockSize is NULL.

 **/
EFI_STATUS
EFIAPI
QcWlanAipGetInfo(
    IN   EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    IN   EFI_GUID                         *InformationType,
    OUT  VOID                             **InformationBlock,
    OUT  UINTN                            *InformationBlockSize
)
{
    EFI_QCWLAN_DEVICE_CONTEXT *Dev;

    if (This == NULL || InformationBlock == NULL || InformationBlockSize == NULL ||
        InformationType == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    Dev = QCWLAN_DEV_FROM_AIP(This);

    // Poll to drive the net80211/pci_driver to run
    poll_irqs(16);

    if (CompareGuid(InformationType, &gEfiAdapterInfoMediaStateGuid)) {
        EFI_ADAPTER_INFO_MEDIA_STATE *MediaState;

        *InformationBlockSize = sizeof(*MediaState);
        *InformationBlock = AllocateZeroPool(*InformationBlockSize);
        if (*InformationBlock == NULL) {
            return EFI_OUT_OF_RESOURCES;
        }

        MediaState = (EFI_ADAPTER_INFO_MEDIA_STATE *)(*InformationBlock);

        if (Dev->Snm.MediaPresent) {
            MediaState->MediaState = EFI_SUCCESS;
        }
        else {
            if (Dev->ConnectNetworkToken || (Dev->GetNetworksToken))
                MediaState->MediaState = EFI_NOT_READY;
            else
                MediaState->MediaState = EFI_NO_MEDIA;

        }
    }
    else if (CompareGuid(InformationType, &gEfiAdapterInfoUndiIpv6SupportGuid)) {
        EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT    *UndiIpv6Support;

        *InformationBlockSize = sizeof(EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT);
        *InformationBlock = AllocateZeroPool(*InformationBlockSize);
        if (*InformationBlock == NULL) {
            return EFI_OUT_OF_RESOURCES;
        }

        UndiIpv6Support = (EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT *)(*InformationBlock);
        UndiIpv6Support->Ipv6Support = TRUE;
    }
    else {
        return EFI_UNSUPPORTED;
    }

    return EFI_SUCCESS;
}

/**
  Sets state information for an adapter.

  This function sends information of type InformationType for an adapter.
  If an adapter does not support the requested information type, then EFI_UNSUPPORTED
  is returned.

  @param[in]  This                   A pointer to the EFI_ADAPTER_INFORMATION_PROTOCOL instance.
  @param[in]  InformationType        A pointer to an EFI_GUID that defines the contents of InformationBlock.
  @param[in]  InformationBlock       A pointer to the InformationBlock structure which contains details
                                     about the data specific to InformationType.
  @param[in]  InformationBlockSize   The size of the InformationBlock in bytes.

  @retval EFI_SUCCESS                The information was received and interpreted successfully.
  @retval EFI_UNSUPPORTED            The InformationType is not known.
  @retval EFI_DEVICE_ERROR           The device reported an error.
  @retval EFI_INVALID_PARAMETER      This is NULL.
  @retval EFI_INVALID_PARAMETER      InformationBlock is NULL.
  @retval EFI_WRITE_PROTECTED        The InformationType cannot be modified using EFI_ADAPTER_INFO_SET_INFO().

**/
EFI_STATUS
EFIAPI
QcWlanAipSetInfo(
    IN   EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    IN   EFI_GUID                         *InformationType,
    IN   VOID                             *InformationBlock,
    IN   UINTN                            InformationBlockSize
)
{
    if (This == NULL || InformationType == NULL || InformationBlock == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (CompareGuid(InformationType, &gEfiAdapterInfoMediaStateGuid) ||
        CompareGuid(InformationType, &gEfiAdapterInfoUndiIpv6SupportGuid)) {
        return EFI_WRITE_PROTECTED;
    }

    return EFI_UNSUPPORTED;
}

/**
  Get a list of supported information types for this instance of the protocol.

  This function returns a list of InformationType GUIDs that are supported on an
  adapter with this instance of EFI_ADAPTER_INFORMATION_PROTOCOL. The list is returned
  in InfoTypesBuffer, and the number of GUID pointers in InfoTypesBuffer is returned in
  InfoTypesBufferCount.

  @param[in]  This                  A pointer to the EFI_ADAPTER_INFORMATION_PROTOCOL instance.
  @param[out] InfoTypesBuffer       A pointer to the list of InformationType GUID pointers that are supported
                                    by This.
  @param[out] InfoTypesBufferCount  A pointer to the number of GUID pointers present in InfoTypesBuffer.

  @retval EFI_SUCCESS               The list of information type GUIDs that are supported on this adapter was
                                    returned in InfoTypesBuffer. The number of information type GUIDs was
                                    returned in InfoTypesBufferCount.
  @retval EFI_INVALID_PARAMETER     This is NULL.
  @retval EFI_INVALID_PARAMETER     InfoTypesBuffer is NULL.
  @retval EFI_INVALID_PARAMETER     InfoTypesBufferCount is NULL.
  @retval EFI_OUT_OF_RESOURCES      There is not enough pool memory to store the results.

**/
EFI_STATUS
EFIAPI
QcWlanAipGetSupportedTypes(
    IN    EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    OUT   EFI_GUID                         **InfoTypesBuffer,
    OUT   UINTN                            *InfoTypesBufferCount
)
{
    EFI_GUID SupportedGuids[2] = {0};

    if (This == NULL || InfoTypesBuffer == NULL || InfoTypesBufferCount == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    CopyMem(&SupportedGuids[0], &gEfiAdapterInfoMediaStateGuid,
        sizeof(EFI_GUID));
    CopyMem(&SupportedGuids[1], &gEfiAdapterInfoUndiIpv6SupportGuid,
        sizeof(EFI_GUID));
    *InfoTypesBufferCount = 2;
    *InfoTypesBuffer = AllocateCopyPool(sizeof(SupportedGuids), SupportedGuids);
    if (InfoTypesBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    return EFI_SUCCESS;
}
