/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 21/12/21  zxue     Add a mechanism to check the memory issue 
 26/8/21   zxue     support HSP2.1
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __PCI_DEV_H
#define __PCI_DEV_H

#include "Dev.h"

#define PCI_READ_ERROR_VAL 0xFFFFFFFF

enum PCI_CONFIG
{
    PCI_DEVICE_ID,
    PCI_MSI_ADDRESS_LO,
    PCI_MSI_ADDRESS_HI,
    PCI_MSI_DATA
};

UINT16 PciGetHardwareDevID(
    IN  CONST QCA_PCI_DEVICE *Dev);

const QCA_HARDWARE_ID *PciGetHardwareId(
    IN  CONST QCA_PCI_DEVICE *Dev);

EFI_STATUS PciReadConfigWord(
    IN  CONST QCA_PCI_DEVICE *Dev,
    IN  UINT16               Config,
    OUT UINT16               *Val);

EFI_STATUS PciReadConfigDword(
    IN  CONST QCA_PCI_DEVICE *Dev,
    IN  UINT16               Config,
    OUT UINT32               *Val);

EFI_STATUS PciAssignResource(
    IN  QCA_PCI_DEVICE *Dev,
    IN  UINT8          BarIndex);

EFI_STATUS PciEnableDevice(
    IN  QCA_PCI_DEVICE *Dev);

VOID PciDisableDevice(
    IN  QCA_PCI_DEVICE *Dev);

BOOLEAN PciIsEnabled(
    IN QCA_PCI_DEVICE *Dev);

UINT32 PciRead32(
    IN  QCA_PCI_DEVICE *Dev,
    IN  UINT32         Offset);

VOID PciWrite8(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Offset,
    IN UINT8          Value);

VOID PciWrite32(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Offset,
    IN UINT32         Value);

EFI_STATUS PciDmaMap(
    IN  QCA_PCI_DEVICE        *Dev,
    IN  VOID                  *Address,
    IN  UINT32                Size,
    IN  QCA_DMA_DIRECTION     Direction,
    OUT EFI_PHYSICAL_ADDRESS *PciAddress,
    OUT VOID                  **MappingAddress);

VOID PciDmaUnmap(
    IN QCA_PCI_DEVICE *Dev,
    IN VOID           *MappingAddress);

VOID *PciMemoryAllocate(
    IN  QCA_PCI_DEVICE *Dev,
    IN  UINT32        Size);

VOID PciMemoryFree(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN VOID           *Address);

VOID *PciDmaMemoryAllocate(
    IN  QCA_PCI_DEVICE       *Dev,
    IN  UINT32               Size,
    OUT EFI_PHYSICAL_ADDRESS *PciAddress,
    OUT VOID                 **MappingAddress);

VOID PciDmaMemoryFree(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN VOID           *Address,
    IN VOID           *MappingAddress);

VOID *PciMemoryAllocateDebug(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32        Size,
    IN CONST CHAR8   *Func,
    IN UINT32        Line);

VOID PciMemoryFreeDebug(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN VOID           *Address,
    IN CONST CHAR8   *Func,
    IN UINT32        Line);

VOID *PciDmaMemoryAllocateDebug(
    IN  QCA_PCI_DEVICE       *Dev,
    IN  UINT32               Size,
    OUT EFI_PHYSICAL_ADDRESS *PciAddress,
    OUT VOID                 **MappingAddress,
    IN  CONST CHAR8          *Func,
    IN  UINT32               Line);

VOID PciDmaMemoryFreeDebug(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN VOID           *Address,
    IN VOID           *MappingAddress,
    IN CONST CHAR8    *Func,
    IN UINT32         Line);

VOID PciSetDriverData(
    IN QCA_PCI_DEVICE *Dev,
    IN VOID           *Drv);

VOID *PciGetDriverData(
    IN QCA_PCI_DEVICE *Dev);

#endif // __PCI_DEV_H