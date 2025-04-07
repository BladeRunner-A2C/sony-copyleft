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
 18/11/21  zxue     refine code
 26/8/21   zxue     support HSP2.1
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <Protocol/PciIo.h>
#include "PciDev.h"
#include "Debug.h"

 /* BIT Defines */
#define BIT(nr)			((1UL) << (nr))

typedef struct {
    UINT32 Signature;
    UINT32 Size;
    VOID *Address;
    EFI_PHYSICAL_ADDRESS PhysicalAddress;
    VOID *MappingAddress;
} PCI_BUFFER_TAILER;

#define PCI_BUFFER_TAILER_SIGNATURE SIGNATURE_32('T', 'A', 'I', 'L')
#define PCI_BUFFER_TAILER_GET(_Address, _Offset) ((PCI_BUFFER_TAILER *)((UINT8 *)(_Address) + (_Offset)))

UINT16 PciGetHardwareDevID(
    IN  CONST QCA_PCI_DEVICE *Dev)
{
    return Dev->HardwareId.DeviceId;
}

CONST QCA_HARDWARE_ID *PciGetHardwareId(
    IN  CONST QCA_PCI_DEVICE *Dev)
{
    return &Dev->HardwareId;
}

EFI_STATUS PciReadConfigWord(
    IN  CONST QCA_PCI_DEVICE *Dev, 
    IN  UINT16               Config, 
    OUT UINT16               *Val)
{
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    PCI_TYPE00 Pci;

    if (Val == NULL)
        return EFI_INVALID_PARAMETER;

    PciIo = Dev->PciIo;

    switch (Config) {
    case PCI_DEVICE_ID:
        Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, 0,
            sizeof(Pci) / sizeof(UINT32),
            &Pci);
        *Val = Pci.Hdr.DeviceId;
        break;
    default:
        Status = EFI_INVALID_PARAMETER;
        break;
    }

    return Status;
}

EFI_STATUS PciReadConfigDword(
    IN  CONST QCA_PCI_DEVICE *Dev,
    IN  UINT16               Config,
    OUT UINT32               *Val)
{
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINT8 CapabilityPtr = 0;
    UINT16 CapabilityEntry;
    UINT8 CapabilityID;

    if (Val == NULL)
        return EFI_INVALID_PARAMETER;

    if (Config != PCI_MSI_ADDRESS_LO &&
        Config != PCI_MSI_ADDRESS_HI &&
        Config != PCI_MSI_DATA) {
        return EFI_UNSUPPORTED;
    }

    PciIo = Dev->PciIo;

    Status = PciIo->Pci.Read(PciIo,
        EfiPciIoWidthUint8,
        PCI_CAPBILITY_POINTER_OFFSET, 1, &CapabilityPtr);

    while ((CapabilityPtr >= 0x40) && ((CapabilityPtr & 0x03) == 0x00)) {
        Status = PciIo->Pci.Read(
            PciIo, 
            EfiPciIoWidthUint16, 
            CapabilityPtr, 1, &CapabilityEntry);

        CapabilityID = (UINT8)(CapabilityEntry & 0xFF);

        if (CapabilityID == EFI_PCI_CAPABILITY_ID_MSI) {
            UINT8 MsiCapabilities[14] = { 0 };
            UINT16 MsiControl;

            Status = PciIo->Pci.Read(
                PciIo,
                EfiPciIoWidthUint8,
                CapabilityPtr, sizeof(MsiCapabilities), 
                MsiCapabilities);

            if (EFI_ERROR(Status)) {
                DbgError("Fail to read MSI capability: %r\n", Status);
                break;
            }

            if (Config == PCI_MSI_ADDRESS_LO) {
                /* Skip Capability ID (1) + Next Pointer (1) + Message Control (2) */
                *Val = *(UINT32 *)(MsiCapabilities + 4);
                break;
            }
            MsiControl = *(UINT16 *)(MsiCapabilities + 2);
            if (Config == PCI_MSI_ADDRESS_HI) {
                if (MsiControl & BIT(7)) {
                    *Val = *(UINT32 *)(MsiCapabilities + 4 + 4);
                }
                else {
                    *Val = 0;
                }
                break;
            }
            if (Config == PCI_MSI_DATA) {
                if (MsiControl & BIT(7)) {
                    *Val = *(UINT16 *)(MsiCapabilities + 4 + 4 + 4);
                }
                else {
                    *Val = *(UINT16 *)(MsiCapabilities + 4 + 4);
                }
            }
            break;
        }

        //
        // Certain PCI device may incorrectly have capability pointing to itself,
        // break to avoid dead loop.
        //
        if (CapabilityPtr == (UINT8)(CapabilityEntry >> 8)) {
            break;
        }

        CapabilityPtr = (UINT8)(CapabilityEntry >> 8);

        DbgInfo("PCI NEXT Capability Pointer %d\n", CapabilityPtr);
    }

    return Status;
}

EFI_STATUS PciEnableDevice(
    IN QCA_PCI_DEVICE *Dev)
{
    EFI_STATUS Status;
    UINT64 Supported;

    WARN_ON(Dev == NULL);

    if (Dev->EnabledPciAttributes != 0) {
        DbgWarn("Enabled already\n");
        return EFI_SUCCESS;
    }
    
    // Get original PCI attributes
    Status = Dev->PciIo->Attributes(Dev->PciIo,
        EfiPciIoAttributeOperationGet,
        0,
        &Dev->OriginalPciAttributes);

    if (EFI_ERROR(Status)) {
        DbgError("Failed getting pci attributes\n");
        return Status;
    }

    // Get the PCI Command options that are supported by this controller.
    Status = Dev->PciIo->Attributes(Dev->PciIo,
        EfiPciIoAttributeOperationSupported,
        0,
        &Supported);
    if (EFI_ERROR(Status)) {
        DbgError("Failed getting supported attributes\n");
        return Status;
    }

    DbgInfo("Original Attributes: 0x%x, Supported attributes: 0x%x\n",
        Dev->OriginalPciAttributes, Supported);

    // Set the PCI Command options to enable device memory mapped IO,
    // port IO, and bus mastering.
    Supported &= (UINT64)(EFI_PCI_DEVICE_ENABLE);

    Status = Dev->PciIo->Attributes(
        Dev->PciIo,
        EfiPciIoAttributeOperationEnable,
        Supported,
        NULL);

    if (EFI_ERROR(Status)) {
        DbgError("Enabling pci attributes failed: %d\n", Status);
        return Status;
    }

    Dev->EnabledPciAttributes = Supported;

    DbgInfo("New attributes:  0x%x\n", Supported);
    return Status;
}

VOID PciDisableDevice(
    IN QCA_PCI_DEVICE *Dev)
{
    EFI_STATUS Status;

    if (Dev->EnabledPciAttributes == 0)
        return;

    // Restore original PCI attributes
    Status = Dev->PciIo->Attributes(Dev->PciIo,
        EfiPciIoAttributeOperationSet,
        Dev->OriginalPciAttributes,
        NULL);
    if (EFI_ERROR(Status)) {
        DbgError("ERROR STATUS: %r\n", Status);
    }

    Dev->EnabledPciAttributes = 0;
}

BOOLEAN PciIsEnabled(
    IN QCA_PCI_DEVICE *Dev)
{
    return (Dev->EnabledPciAttributes != 0);
}

EFI_STATUS PciAssignResource(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT8          BarIndex)
{
    Dev->BarIndex = BarIndex;

    return EFI_SUCCESS;
}

UINT32 PciRead32(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Offset)
{
    EFI_STATUS Status;
    UINT32 Value;

    Status = Dev->PciIo->Mem.Read(Dev->PciIo,
        EfiPciIoWidthUint32,
        Dev->BarIndex,
        Offset,
        1,
        (VOID *)&Value);
    if (EFI_ERROR(Status)) {
        DbgError("Read address 0x%x failed: %r\n", Offset, Status);
        return PCI_READ_ERROR_VAL;
    }

    return Value;
}

VOID PciWrite8(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Offset,
    IN UINT8          Value)
{
    EFI_STATUS Status;

    Status = Dev->PciIo->Mem.Write(Dev->PciIo,
        EfiPciIoWidthUint8,
        Dev->BarIndex,
        Offset,
        1,
        (VOID *)(&Value));
    if (EFI_ERROR(Status)) {
        DbgError("Write address 0x%x failed: %d\n", Offset, Status);
    }
}

VOID PciWrite32(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Offset,
    IN UINT32         Value)
{
    EFI_STATUS Status;

    Status = Dev->PciIo->Mem.Write(Dev->PciIo,
        EfiPciIoWidthUint32,
        Dev->BarIndex,
        Offset,
        1,
        (VOID *)(&Value));
    if (EFI_ERROR(Status)) {
        DbgError("Write address 0x%x failed: %d\n", Offset, Status);
    }
}

EFI_STATUS PciDmaMap(
    IN  QCA_PCI_DEVICE        *Dev,
    IN  VOID                  *Address,
    IN  UINT32                Size,
    IN  QCA_DMA_DIRECTION     Direction,
    OUT EFI_PHYSICAL_ADDRESS *PciAddress,
    OUT VOID                  **MappingAddress)
{
    UINTN MapSize = Size;
    EFI_PCI_IO_PROTOCOL_OPERATION Operation;

    switch (Direction) {
    case QCA_DMA_TO_DEVICE:
        Operation = EfiPciIoOperationBusMasterRead;
        break;
    case QCA_DMA_FROM_DEVICE:
        Operation = EfiPciIoOperationBusMasterWrite;
        break;
    case QCA_DMA_BIDIRECTIONAL:
        Operation = EfiPciIoOperationBusMasterCommonBuffer;
        break;
    default:
        DbgError("Invalid DMA direction\n");
        return EFI_INVALID_PARAMETER;
    }

    return Dev->PciIo->Map(Dev->PciIo, 
        Operation,
        Address,
        &MapSize,
        PciAddress,
        MappingAddress);
}

VOID PciDmaUnmap(
    IN QCA_PCI_DEVICE *Dev,
    IN VOID           *MappingAddress)
{
    Dev->PciIo->Unmap(Dev->PciIo, MappingAddress);
}

VOID *PciMemoryAllocate(
    IN  QCA_PCI_DEVICE       *Dev,
    IN  UINT32               Size)
{
    EFI_STATUS Status;
    VOID *AddressOut = NULL;

    // Limit allocation to 4G?
    Status = Dev->PciIo->AllocateBuffer(Dev->PciIo,
        AllocateAnyPages,
        EfiBootServicesData,
        EFI_SIZE_TO_PAGES(Size),
        &AddressOut, 0);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to allocate DMA pages for size %d: %r\n", Size, Status);
        return AddressOut;
    }

    ZeroMem(AddressOut, Size);

    return AddressOut;
}

VOID PciMemoryFree(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN VOID           *Address)
{
    if (Address == NULL)
        return;
    Dev->PciIo->FreeBuffer(Dev->PciIo, EFI_SIZE_TO_PAGES(Size), Address);
}

VOID *PciDmaMemoryAllocate(
    IN  QCA_PCI_DEVICE       *Dev,
    IN  UINT32               Size,
    OUT EFI_PHYSICAL_ADDRESS *PciAddress,
    OUT VOID                 **MappingAddress)
{
    EFI_STATUS Status;
    EFI_PHYSICAL_ADDRESS PhysicalAddressOut = 0;
    VOID *AddressOut = NULL, *MappingAddressOut = NULL;

    *PciAddress = 0;
    *MappingAddress = 0;

    // Limit allocation to 4G?
    Status = Dev->PciIo->AllocateBuffer(Dev->PciIo,
        AllocateAnyPages,
        EfiBootServicesData,
        EFI_SIZE_TO_PAGES(Size),
        &AddressOut, 0);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to allocate DMA pages for size %d: %r\n", Size, Status);
        return AddressOut;
    }

    ZeroMem(AddressOut, Size);

    Status = PciDmaMap(Dev, AddressOut, Size, QCA_DMA_BIDIRECTIONAL, 
        &PhysicalAddressOut, &MappingAddressOut);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to map DMA pages: %r\n", Status);
        Dev->PciIo->FreeBuffer(Dev->PciIo, EFI_SIZE_TO_PAGES(Size), (VOID *)AddressOut);
        return AddressOut;
    }

    *PciAddress = PhysicalAddressOut;
    *MappingAddress = MappingAddressOut;
    return AddressOut;
}

VOID PciDmaMemoryFree(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN VOID           *Address,
    IN VOID           *MappingAddress)
{
    if (Address == NULL)
        return;

    if (MappingAddress)
        PciDmaUnmap(Dev, MappingAddress);

    Dev->PciIo->FreeBuffer(Dev->PciIo, EFI_SIZE_TO_PAGES(Size), Address);
}

VOID *PciMemoryAllocateDebug(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN CONST CHAR8    *Func,
    IN UINT32         Line)
{
    PCI_BUFFER_TAILER *BufferTailer;
    VOID *Address;

    Address = PciMemoryAllocate(Dev, Size + sizeof(PCI_BUFFER_TAILER));
    if (Address) {
        BufferTailer = PCI_BUFFER_TAILER_GET(Address, Size);
        BufferTailer->Signature = PCI_BUFFER_TAILER_SIGNATURE;
        BufferTailer->Address = Address;
        BufferTailer->Size = Size;

        DbgRaw(WLAN_LOG_LEVEL_INFO, "%a(%d): pci memory allocated 0x%p(%d)\n", Func, Line, Address, Size);
    };

    return Address;
}

VOID PciMemoryFreeDebug(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN VOID           *Address,
    IN CONST CHAR8    *Func,
    IN UINT32         Line)
{
    PCI_BUFFER_TAILER *BufferTailer;

    if (Address == NULL) {
        DbgRaw(WLAN_LOG_LEVEL_WARN, "%a(%d): pci memory free 0x%p(%d)\n", 
            Func, Line, Address, Size);
        return;
    }

    BufferTailer = PCI_BUFFER_TAILER_GET(Address, Size);

    if ((BufferTailer->Signature != PCI_BUFFER_TAILER_SIGNATURE) ||
        (BufferTailer->Address != Address) ||
        (BufferTailer->Size != Size)) {
        DbgRaw(WLAN_LOG_LEVEL_ERROR, 
            "%a(%d): ERROR: pci memory free 0x%p(%d) with tailer: signature=0x%08X, address=0x%p, size=%d\n",
            Func, Line, Address, Size, 
            BufferTailer->Signature, BufferTailer->Address, BufferTailer->Size);
    }
    else {
        DbgRaw(WLAN_LOG_LEVEL_INFO, "%a(%d): pci memory free 0x%p(%d)\n", Func, Line, Address, Size);
    }

    PciMemoryFree(Dev, Size + sizeof(PCI_BUFFER_TAILER), Address);
}

VOID *PciDmaMemoryAllocateDebug(
    IN  QCA_PCI_DEVICE       *Dev,
    IN  UINT32               Size,
    OUT EFI_PHYSICAL_ADDRESS *PciAddress,
    OUT VOID                 **MappingAddress,
    IN CONST CHAR8           *Func, 
    IN UINT32                Line)
{
    PCI_BUFFER_TAILER *BufferTailer;
    VOID *Address;
    VOID *PciMappingAddress;
    EFI_PHYSICAL_ADDRESS PhysicalAddress;

    Address = PciDmaMemoryAllocate(Dev, Size + sizeof(PCI_BUFFER_TAILER), &PhysicalAddress, &PciMappingAddress);
    if (Address) {
        BufferTailer = PCI_BUFFER_TAILER_GET(Address, Size);
        BufferTailer->Signature = PCI_BUFFER_TAILER_SIGNATURE;
        BufferTailer->Size = Size;
        BufferTailer->Address = Address;
        BufferTailer->PhysicalAddress = PhysicalAddress;
        BufferTailer->MappingAddress = PciMappingAddress;

        *PciAddress = PhysicalAddress;
        *MappingAddress = BufferTailer;

        DbgRaw(WLAN_LOG_LEVEL_INFO,
            "%a(%d): pci dma memory allocated 0x%p(%d), physical_address=0x%p, mapping_address=0x%p\n",
            Func, Line, Address, Size,
            BufferTailer->PhysicalAddress, BufferTailer->MappingAddress);
    }

    return Address;
}

VOID PciDmaMemoryFreeDebug(
    IN QCA_PCI_DEVICE *Dev,
    IN UINT32         Size,
    IN VOID           *Address,
    IN VOID           *MappingAddress,
    IN CONST CHAR8    *Func,
    IN UINT32          Line)
{
    PCI_BUFFER_TAILER *BufferTailer;

    if ((Address == NULL) || (MappingAddress == NULL)) {
        DbgRaw(WLAN_LOG_LEVEL_WARN, "%a(%d): pci dma memory free 0x%p(%d), mapping_address=0x%p\n", 
            Func, Line, Address, Size, MappingAddress);
        return;
    }

    BufferTailer = MappingAddress;
    if ((BufferTailer->Signature != PCI_BUFFER_TAILER_SIGNATURE) ||
        (BufferTailer->Address != Address) ||
        (BufferTailer->Size != Size)) {
        DbgRaw(WLAN_LOG_LEVEL_ERROR,
            "%a(%d): ERROR: pci dma memory free 0x%p(%d) with tailer: signature=0x%08X, address=0x%p, size=%d, "
            "physical_address=0x%p, mapping_address=0x%p\n",
            Func, Line, Address, Size,
            BufferTailer->Signature, BufferTailer->Address, BufferTailer->Size,
            BufferTailer->PhysicalAddress, BufferTailer->MappingAddress);
    }
    else {
        DbgRaw(WLAN_LOG_LEVEL_INFO,
            "%a(%d): pci dma memory free 0x%p(%d), physical_address=0x%p, mapping_address=0x%p\n",
            Func, Line, Address, Size,
            BufferTailer->PhysicalAddress, BufferTailer->MappingAddress);
    }

    PciDmaMemoryFree(Dev, Size + sizeof(PCI_BUFFER_TAILER), Address, BufferTailer->MappingAddress);
}

VOID PciSetDriverData(
    IN QCA_PCI_DEVICE *Dev,
    IN VOID           *DriverData)
{
    Dev->DriverData = DriverData;
}

VOID *PciGetDriverData(
    IN QCA_PCI_DEVICE *Dev)
{
    return  Dev->DriverData;
}

