/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
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

#ifndef __QDF_PCI_H
#define __QDF_PCI_H

#include <qdf/base_type.h>
#include <qdf/pr_debug.h>
#include <qdf/list.h>

#if SUPPORT_DEBUG_PRINT
#define SUPPORT_PCI_MEMORY_DEBUG_PRINT 1
#endif

/* types */
typedef void *pci_dev_handle;

enum dma_data_direction {
    DMA_BIDIRECTIONAL = 0,
    DMA_TO_DEVICE = 1,
    DMA_FROM_DEVICE = 2,
    DMA_NONE = 3,
};

struct pci_device_id {
    u16 vendor;
    u16 device;
    u16 subsystem_vendor;
    u16 subsystem_device;
    u32 firmware_attributes;
};

/* platform implementation */
#include <PciDev.h>

static inline u32 pci_read_config_word(pci_dev_handle dev, u16 config, u16 *val)
{
    return (u32)PciReadConfigWord((QCA_PCI_DEVICE*)dev, config, val);
}

static inline u32 pci_read_config_dword(pci_dev_handle dev, u16 config, u32 *val)
{
    return (u32)PciReadConfigDword((QCA_PCI_DEVICE*)dev, config, val);
}

static inline u32 pci_assign_resource(pci_dev_handle dev, u8 bar_index)
{
    return (u32)PciAssignResource((QCA_PCI_DEVICE*)dev, bar_index);
}

static inline u32 pci_enable_device(pci_dev_handle dev)
{
    return (u32)PciEnableDevice((QCA_PCI_DEVICE*)dev);
}

static inline void pci_disable_device(pci_dev_handle dev)
{
    PciDisableDevice((QCA_PCI_DEVICE*)dev);
}

static inline bool pci_is_enabled(pci_dev_handle dev)
{
    return (bool)PciIsEnabled((QCA_PCI_DEVICE*)dev);
}

static inline u16 pci_get_hardware_dev_id(pci_dev_handle dev)
{
    return (u16)PciGetHardwareDevID((QCA_PCI_DEVICE*)dev);
}

static inline const struct pci_device_id *pci_get_hardware_id(pci_dev_handle dev)
{
    BUILD_BUG_ON(sizeof(struct pci_device_id) != sizeof(QCA_HARDWARE_ID));
    return (const struct pci_device_id *)PciGetHardwareId((QCA_PCI_DEVICE*)dev);
}

static inline u32 pci_read32(pci_dev_handle dev, u32 offset)
{
    return (u32)PciRead32((QCA_PCI_DEVICE*)dev, offset);
}

static inline void pci_write8(pci_dev_handle dev, u32 offset, u8 val)
{
    PciWrite8((QCA_PCI_DEVICE*)dev, offset, val);
}

static inline void pci_write32(pci_dev_handle dev, u32 offset, u32 val)
{
    PciWrite32((QCA_PCI_DEVICE*)dev, offset, val);
}

static inline u32 pci_dma_map_single(pci_dev_handle dev,
    void *ptr, u32 size, enum dma_data_direction dir,
    dma_addr_t *paddr, void **paddr_mapping_addr)
{
    return (u32)PciDmaMap((QCA_PCI_DEVICE*)dev,
        ptr, size, (QCA_DMA_DIRECTION)dir,
        (EFI_PHYSICAL_ADDRESS *)paddr, (VOID **)paddr_mapping_addr);
}

static inline void pci_dma_unmap_single(pci_dev_handle dev,
    dma_addr_t paddr, void *paddr_mapping_addr,
    u32 size, enum dma_data_direction dir)
{
    PciDmaUnmap((QCA_PCI_DEVICE*)dev, paddr_mapping_addr);
}

static inline void pci_set_drvdata(pci_dev_handle dev, void *drv)
{
    PciSetDriverData((QCA_PCI_DEVICE*)dev, drv);
}

static inline void *pci_get_drvdata(pci_dev_handle dev)
{
    return PciGetDriverData((QCA_PCI_DEVICE*)dev);
}

#if !SUPPORT_PCI_MEMORY_DEBUG_PRINT

static inline void *pci_dma_alloc_coherent(pci_dev_handle dev,
    size_t size, dma_addr_t *dma_handle, void **dma_mapping_addr)
{
    return PciDmaMemoryAllocate((QCA_PCI_DEVICE*)dev, (UINT32)size,
        (EFI_PHYSICAL_ADDRESS *)dma_handle, (VOID **)dma_mapping_addr);
}

static inline void pci_dma_free_coherent(pci_dev_handle dev,
    size_t size, void *vaddr, dma_addr_t dma_handle, void *dma_mapping_addr)
{
    PciDmaMemoryFree((QCA_PCI_DEVICE*)dev, (UINT32)size, vaddr, dma_mapping_addr);
}

static inline void *pci_mem_alloc(pci_dev_handle dev, size_t size)
{
    return PciMemoryAllocate((QCA_PCI_DEVICE*)dev, (UINT32)size);
}

static inline void pci_mem_free(pci_dev_handle dev, size_t size, void *vaddr)
{
    PciMemoryFree((QCA_PCI_DEVICE*)dev, (UINT32)size, vaddr);
}

#else /* SUPPORT_PCI_MEMORY_DEBUG_PRINT */

#define pci_dma_alloc_coherent(_dev, _size, _dma_handle, _dma_mapping_addr) \
    PciDmaMemoryAllocateDebug((QCA_PCI_DEVICE*)(_dev), (UINT32)(_size), (EFI_PHYSICAL_ADDRESS *)(_dma_handle), (VOID **)(_dma_mapping_addr), __FUNCTION__, __LINE__)

#define pci_dma_free_coherent(_dev, _size, _vaddr, _dma_handle, _dma_mapping_addr) \
    PciDmaMemoryFreeDebug((QCA_PCI_DEVICE*)(_dev), (UINT32)(_size), (_vaddr), (_dma_mapping_addr), __FUNCTION__, __LINE__)

#define pci_mem_alloc(_dev, _size) \
    PciMemoryAllocateDebug((QCA_PCI_DEVICE*)(_dev), (UINT32)(_size), __FUNCTION__, __LINE__)

#define pci_mem_free(_dev, _size, _vaddr) \
    PciMemoryFreeDebug((QCA_PCI_DEVICE*)(_dev), (UINT32)(_size), (_vaddr), __FUNCTION__, __LINE__)

#endif /* SUPPORT_PCI_MEMORY_DEBUG_PRINT */

/* DMA APIs */
#define dma_alloc_coherent(_dev, _size, _dma_handle, _dma_mapping_addr) \
    pci_dma_alloc_coherent(_dev, _size, _dma_handle, _dma_mapping_addr)

#define dma_free_coherent(_dev, _size, _cpu_addr, _dma_handle, _dma_mapping_addr) \
    pci_dma_free_coherent(_dev, _size, _cpu_addr, _dma_handle, _dma_mapping_addr)

#define dma_map_single(dev,ptr,size,dir,paddr,paddr_mapping_addr) \
    pci_dma_map_single(dev,ptr,size,dir,paddr,paddr_mapping_addr)

#define dma_unmap_single(dev,paddr,paddr_mapping_addr,size,dir) \
    pci_dma_unmap_single(dev,paddr,paddr_mapping_addr,size,dir)

/********************************************************/
/* pci driver */
/*******************************************************/

struct pci_driver {
    const char *name;
    const struct pci_device_id *id_table;
    int(*probe)(pci_dev_handle dev);
    void(*remove)(pci_dev_handle dev);
    void *probed;
};

const struct pci_device_id *pci_match(
    u16 vendor,
    u16 device,
    u16 subsystem_vendor,
    u16 subsystem_device);

int pci_probe(pci_dev_handle dev);

void pci_remove(pci_dev_handle dev);

/* pci dma pool */

struct pci_dma_pool {
    const char *name;
    void *dev;
    u32 count;
    list_entry_t free_list;
};

void pci_request_dma_pool(
    pci_dev_handle dev,
    const char *name,
    dma_addr_t upper_addr,
    struct pci_dma_pool *dma_pool);

void pci_free_dma_pool(struct pci_dma_pool *dma_pool);

#endif // !__QDF_PCI_H

