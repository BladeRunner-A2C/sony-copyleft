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
 18/11/21  zxue     refine code
 19/8/21   zxue     fix KW issue
 3/8/21    zxue     Update the error code when interface is not available
 23/7/21   zxue     add missing copyright
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/ether.h>
#include <net/net80211.h>
#include <net/netdevice.h>
#include <qdf/interrupt.h>
#include "Debug.h"
#include "Dev.h"
#include "QcaWlan.h"
#include "QcaTxRx.h"

VOID
EFIAPI
QcWlanSnpIsPacketAvailable(
    IN  EFI_EVENT Event,
    IN  VOID      *Context
)
{
}

EFI_STATUS
EFIAPI
QcWlanSnpStart(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This
)
{
	EFI_QCWLAN_DEVICE_CONTEXT *Dev;
	EFI_TPL OldTpl;
	EFI_STATUS Status;

	if (This == NULL)
	    return EFI_INVALID_PARAMETER;

	Dev = QCWLAN_DEV_FROM_SNP(This);
	OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

	if (Dev->Snm.State != EfiSimpleNetworkStopped) {
		Status = EFI_ALREADY_STARTED;
		goto Out;
	}

	Dev->Snm.State = EfiSimpleNetworkStarted;

	Status = EFI_SUCCESS;

Out:
	gBS->RestoreTPL(OldTpl);
	return Status;
}

EFI_STATUS
EFIAPI
QcWlanSnpStop(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This
)
{
	EFI_QCWLAN_DEVICE_CONTEXT *Dev;
	EFI_TPL OldTpl;
	EFI_STATUS Status;

	if (This == NULL)
        return EFI_INVALID_PARAMETER;

	Dev = QCWLAN_DEV_FROM_SNP (This);
	OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

	switch (Dev->Snm.State) {
	case EfiSimpleNetworkStarted:
	case EfiSimpleNetworkInitialized:
		Dev->Snm.State = EfiSimpleNetworkStopped;
	  	break;
	default:
	  	Status = EFI_DEVICE_ERROR;
	  	goto Out;
	}

    QcWlanUninitializeNic(Dev);
    Status = EFI_SUCCESS;
Out:
	gBS->RestoreTPL(OldTpl);
    DbgFlush();
	return Status;
}

EFI_STATUS
EFIAPI
QcWlanSnpInitialize(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN UINTN                       ExtraRxBufferSize,
  IN UINTN                       ExtraTxBufferSize
)
{
	EFI_QCWLAN_DEVICE_CONTEXT *Dev;
	EFI_TPL OldTpl;
	EFI_STATUS Status = EFI_SUCCESS;

	if (This == NULL)
	return EFI_INVALID_PARAMETER;

	Dev = QCWLAN_DEV_FROM_SNP(This);
	OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

	if (Dev->Snm.State == EfiSimpleNetworkInitialized) {
		Status = EFI_SUCCESS;
		goto Out;
	} else if (Dev->Snm.State == EfiSimpleNetworkStopped) {
		Status = EFI_NOT_STARTED;
		goto Out;
	}

    Status = QcWlanInitializeNic(Dev);
	if (Status != EFI_SUCCESS)
		goto Out;

    QcWlanApplyNicConfiguration(Dev);

	Dev->Snm.State = EfiSimpleNetworkInitialized;
	Status = EFI_SUCCESS;

Out:
	gBS->RestoreTPL(OldTpl);
	return Status;
}


EFI_STATUS
EFIAPI
QcWlanSnpReset(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN BOOLEAN                     ExtendedVerification)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
QcWlanSnpShutdown(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This
)
{
	EFI_QCWLAN_DEVICE_CONTEXT *Dev;
	EFI_TPL OldTpl;
	EFI_STATUS Status;

	if (This == NULL)
		return EFI_INVALID_PARAMETER;

	Dev = QCWLAN_DEV_FROM_SNP (This);
	OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

	if (Dev->Snm.State == EfiSimpleNetworkStarted) {
		Status = EFI_DEVICE_ERROR;
		goto Out;
	} else if (Dev->Snm.State == EfiSimpleNetworkStopped) {
		Status = EFI_NOT_STARTED;
		goto Out;
	}

    QcWlanUninitializeNic(Dev);
	Dev->Snm.State = EfiSimpleNetworkStarted;
	Status = EFI_SUCCESS;

Out:
	gBS->RestoreTPL(OldTpl);
    DbgFlush();
	return Status;
}

EFI_STATUS
EFIAPI
QcWlanSnpReceiveFilters(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN UINT32                      Enable,
  IN UINT32                      Disable,
  IN BOOLEAN                     ResetMCastFilter,
  IN UINTN                       MCastFilterCnt  OPTIONAL,
  IN EFI_MAC_ADDRESS             *MCastFilter    OPTIONAL
)
{
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
QcWlanSnpStationAddress(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN BOOLEAN                     Reset,
  IN EFI_MAC_ADDRESS             *New OPTIONAL
)
{
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
QcWlanSnpStatistics(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN BOOLEAN                     Reset,
  IN OUT UINTN                   *StatisticsSize   OPTIONAL,
  OUT EFI_NETWORK_STATISTICS     *StatisticsTable  OPTIONAL
)
{
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
QcWlanSnpMcastIpToMac(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN BOOLEAN                     IPv6,
  IN EFI_IP_ADDRESS              *Ip,
  OUT EFI_MAC_ADDRESS            *Mac
)
{
    // See VirtioNet
	return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
QcWlanSnpNvData(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN BOOLEAN                     ReadWrite,
  IN UINTN                       Offset,
  IN UINTN                       BufferSize,
  IN OUT VOID                    *Buffer
)
{
    // See VirtioNet
	return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
QcWlanSnpGetStatus(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  OUT UINT32                     *InterruptStatus,
  OUT VOID                       **TxBuf
)
{
	EFI_QCWLAN_DEVICE_CONTEXT *Dev;
	EFI_TPL OldTpl;
	EFI_STATUS Status = EFI_SUCCESS;
	NET80211_CONTEXT *Context;
	struct net_device* dev;

	if (This == NULL)
		return EFI_INVALID_PARAMETER;

	Dev = QCWLAN_DEV_FROM_SNP (This);
	Context = &Dev->WiFi;
	if (Context->NetIf == NULL) {
        return EFI_NOT_READY;
	}

	OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

	switch (Dev->Snm.State) {
	case EfiSimpleNetworkStopped:
		Status = EFI_NOT_STARTED;
		goto Out;
	case EfiSimpleNetworkStarted:
		Status = EFI_DEVICE_ERROR;
		goto Out;
	default:
		break;
	}

    dev = net80211_get_data_device(Context->NetIf);
	if (dev == NULL) {
        goto Out;
	}
	
    poll_irqs(MAX_INT32);

	if (InterruptStatus != NULL) {
		*InterruptStatus = 0;

		if (!skb_queue_empty(&dev->rxq))
		    *InterruptStatus |= EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT;

		if (!skb_queue_empty(&dev->txq_recycle))
		    *InterruptStatus |= EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT;
	}

	if (TxBuf != NULL) {
        struct sk_buff *skb = skb_dequeue(&dev->txq_recycle);
        if (skb) {
            *TxBuf = skb_get_data_meta(skb);
            DbgTxRxInfo("Recycling buffer 0x%x from skb 0x%p(%d)\n", *TxBuf, skb, skb->len);

            kfree_skb(skb);
        }
        else {
		    *TxBuf = NULL;
		}
	}

	Status = EFI_SUCCESS;

Out:
	gBS->RestoreTPL(OldTpl);
	return Status;
}

EFI_STATUS
EFIAPI
QcWlanSnpTransmit(
  IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
  IN UINTN                       HeaderSize,
  IN UINTN                       BufferSize,
  IN /* +OUT! */ VOID            *Buffer,
  IN EFI_MAC_ADDRESS             *SrcAddr ,
  IN EFI_MAC_ADDRESS             *DestAddr,
  IN UINT16                      *Protocol
)
{
	EFI_QCWLAN_DEVICE_CONTEXT *Dev;
	EFI_TPL OldTpl;
	EFI_STATUS Status = EFI_SUCCESS;
	UINT16 LocalProtocol;
	struct sk_buff *skb = NULL;

	if (This == NULL || BufferSize == 0 || Buffer == NULL)
		return EFI_INVALID_PARAMETER;

	Dev = QCWLAN_DEV_FROM_SNP(This);
	OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

	switch (Dev->Snm.State) {
	case EfiSimpleNetworkStopped:
		Status = EFI_NOT_STARTED;
		goto Exit;
	case EfiSimpleNetworkStarted:
		Status = EFI_DEVICE_ERROR;
		goto Exit;
	default:
		break;
	}

	if (!Dev->Snm.MediaPresent) {
		Status = EFI_NOT_STARTED;
		goto Exit;
	}

	if (BufferSize < Dev->Snm.MediaHeaderSize) {
		Status = EFI_BUFFER_TOO_SMALL;
		goto Exit;
	}

	if (BufferSize > Dev->Snm.MediaHeaderSize + Dev->Snm.MaxPacketSize) {
		Status = EFI_INVALID_PARAMETER;
		goto Exit;
	}

	if (!SrcAddr)
		SrcAddr = (VOID *)&Dev->Snm.CurrentAddress;

	if (HeaderSize) {
		UINT8 *Ptr = Buffer;

		if (HeaderSize != Dev->Snm.MediaHeaderSize) {
		    Status = EFI_INVALID_PARAMETER;
		    goto Exit;
		}

		if (!DestAddr || !Protocol) {
		    Status = EFI_INVALID_PARAMETER;
		    goto Exit;
		}

		CopyMem(Ptr, DestAddr, ETH_ALEN);
		Ptr += ETH_ALEN;
		CopyMem(Ptr, SrcAddr, ETH_ALEN);
		Ptr += ETH_ALEN;

		*Ptr++ = (UINT8) (*Protocol >> 8);
		*Ptr++ = (UINT8) *Protocol;
	}

	if (!DestAddr)
		DestAddr = Buffer;

	if (!Protocol || !*Protocol) {
		LocalProtocol = SwapBytes16(*(UINT16 *)((UINT8 *)Buffer + 2 * ETH_ALEN));
		Protocol = &LocalProtocol;
	}

	if (0 != CompareMem((UINT8 *)Buffer + ETH_ALEN, (VOID *)SrcAddr, ETH_ALEN)) {
		Status = EFI_INVALID_PARAMETER;
		goto Exit;
	}

    skb = sk_buff_pool_alloc_skb(&Dev->tx_skb_pool, 4);
	if (skb == NULL) {
		Status = EFI_OUT_OF_RESOURCES;
		goto Exit;
	}
	
    skb_put_data(skb, Buffer, (u32)BufferSize);
    skb_set_data_meta(skb, Buffer);

	Status = QcWlanTxPacket(Dev, skb);
	if (Status != EFI_SUCCESS)
		goto Exit;

Exit:
	gBS->RestoreTPL(OldTpl);
	return Status;
}

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
)
{
	EFI_QCWLAN_DEVICE_CONTEXT *Dev;
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_TPL OldTpl;
	BOOLEAN ValidRxPacket = FALSE;
	UINT8 *Ptr;
	NET80211_CONTEXT *Context;
	struct net_device* dev;

	if (This == NULL || BufferSize == NULL || Buffer == NULL)
		return EFI_INVALID_PARAMETER;

	Dev = QCWLAN_DEV_FROM_SNP(This);
	Context = &Dev->WiFi;
	if (Context->NetIf == NULL) {
        return EFI_NOT_READY;
	}
	
	OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

	switch (Dev->Snm.State) {
    case EfiSimpleNetworkStopped:
		Status = EFI_NOT_STARTED;
		goto Exit;
	case EfiSimpleNetworkStarted:
		Status = EFI_DEVICE_ERROR;
		goto Exit;
	default:
		break;
	}

    dev = net80211_get_data_device(Context->NetIf);
	if (dev == NULL) {
        goto Exit;
	}
	
    poll_irqs(MAX_INT32);
	
	if (*BufferSize < Dev->Snm.MediaHeaderSize + Dev->Snm.MaxPacketSize) {
		Status = EFI_INVALID_PARAMETER;
		goto Exit;
	}

	if (dev) {
        if (skb_queue_empty(&dev->rxq)) {
            poll_irqs(MAX_INT32);
            if (skb_queue_empty(&dev->rxq)) {
                Status = EFI_NOT_READY;
                goto Exit;
            }
        }

		do {
			// Will process the rxq
			struct sk_buff *skb = skb_dequeue(&dev->rxq);
			if (skb) {
				ValidRxPacket = QcWlanProcessRxPacket(Dev, skb, Buffer, BufferSize);
            	consume_skb(skb);
			}
		} while (!ValidRxPacket && !skb_queue_empty(&dev->rxq));

		if (!ValidRxPacket) {
			Status = EFI_NOT_READY;
			goto Exit;
		}

		if (HeaderSize != NULL)
			*HeaderSize = Dev->Snm.MediaHeaderSize;

		Ptr = Buffer;
		if (DestAddr)
			CopyMem(DestAddr, Ptr, ETH_ALEN);
			Ptr += ETH_ALEN;
		if (SrcAddr)
			CopyMem(SrcAddr, Ptr, ETH_ALEN);
			Ptr += ETH_ALEN;
		if (Protocol)
			*Protocol = SwapBytes16(*(UINT16 *)Ptr);
	}
	
	Status = EFI_SUCCESS;
Exit:
	gBS->RestoreTPL(OldTpl);
	return Status;
}