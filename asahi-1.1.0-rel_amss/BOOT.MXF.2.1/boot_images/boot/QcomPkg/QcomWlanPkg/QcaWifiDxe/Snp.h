/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
  Copyright (C) 2013, Red Hat, Inc.
  Copyright (c) 2017, AMD Inc, All rights reserved.<BR>

  This program and the accompanying materials are licensed and made available
  under the terms and conditions of the BSD License which accompanies this
  distribution. The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS, WITHOUT
  WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 23/7/21   zxue     add missing copyright
 14/7/21   zxue     branch for core boot

=============================================================================*/

/* See VirtioNet */

#ifndef __SNP_H
#define __SNP_H

#include <Uefi.h>

VOID
EFIAPI
QcWlanSnpIsPacketAvailable(
    IN  EFI_EVENT Event,
    IN  VOID      *Context
);

EFI_STATUS
EFIAPI
QcWlanSnpStart(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This
);

EFI_STATUS
EFIAPI
QcWlanSnpStop(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This
);

EFI_STATUS
EFIAPI
QcWlanSnpInitialize(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN UINTN                       ExtraRxBufferSize,
    IN UINTN                       ExtraTxBufferSize
);

EFI_STATUS
EFIAPI
QcWlanSnpReset(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN BOOLEAN                     ExtendedVerification
);

EFI_STATUS
EFIAPI
QcWlanSnpShutdown(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This
);

EFI_STATUS
EFIAPI
QcWlanSnpReceiveFilters(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN UINT32                      Enable,
    IN UINT32                      Disable,
    IN BOOLEAN                     ResetMCastFilter,
    IN UINTN                       MCastFilterCnt    OPTIONAL,
    IN EFI_MAC_ADDRESS             *MCastFilter      OPTIONAL
);

EFI_STATUS
EFIAPI
QcWlanSnpStationAddress(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN BOOLEAN                     Reset,
    IN EFI_MAC_ADDRESS             *New OPTIONAL
);

EFI_STATUS
EFIAPI
QcWlanSnpStatistics(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN BOOLEAN                     Reset,
    IN OUT UINTN                   *StatisticsSize   OPTIONAL,
    OUT EFI_NETWORK_STATISTICS     *StatisticsTable  OPTIONAL
);

EFI_STATUS
EFIAPI
QcWlanSnpMcastIpToMac(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN BOOLEAN                     IPv6,
    IN EFI_IP_ADDRESS              *Ip,
    OUT EFI_MAC_ADDRESS            *Mac
);

EFI_STATUS
EFIAPI
QcWlanSnpNvData(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN BOOLEAN                     ReadWrite,
    IN UINTN                       Offset,
    IN UINTN                       BufferSize,
    IN OUT VOID                    *Buffer
);

EFI_STATUS
EFIAPI
QcWlanSnpGetStatus(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    OUT UINT32                     *InterruptStatus,
    OUT VOID                       **TxBuf
);

EFI_STATUS
EFIAPI
QcWlanSnpTransmit(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN UINTN                       HeaderSize,
    IN UINTN                       BufferSize,
    IN /* +OUT! */ VOID            *Buffer,
    IN EFI_MAC_ADDRESS             *SrcAddr,
    IN EFI_MAC_ADDRESS             *DestAddr,
    IN UINT16                      *Protocol
);

EFI_STATUS
EFIAPI
QcWlanSnpReceive(
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    OUT UINTN                      *HeaderSize,
    IN OUT UINTN                   *BufferSize,
    OUT VOID                       *Buffer,
    OUT EFI_MAC_ADDRESS            *SrcAddr,
    OUT EFI_MAC_ADDRESS            *DestAddr,
    OUT UINT16                     *Protocol
);


#endif // !__SNP_H