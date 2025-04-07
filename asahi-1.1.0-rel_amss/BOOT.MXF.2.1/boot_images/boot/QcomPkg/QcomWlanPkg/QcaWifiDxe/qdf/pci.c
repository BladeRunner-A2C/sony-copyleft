/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 21/12/21  zxue     Add a mechanism to check the memory issue 
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include "pci.h"
#include <Config.h>
#include <qdf/list.h>

/* pci device probe */
extern struct pci_driver ath12k_pci_driver;

#if SUPPORT_DRIVER_ATH11K
extern struct pci_driver ath11k_pci_driver;
#endif

static struct pci_driver *pci_driver_list[] = {
	&ath12k_pci_driver,
#if SUPPORT_DRIVER_ATH11K
	&ath11k_pci_driver,
#endif
	NULL
};

static inline bool
pci_device_id_is_valid(const struct pci_device_id *id)
{
	if (!id)
		return false;

	if ((id->vendor != 0) ||
		(id->device != 0) ||
		(id->subsystem_vendor != 0) ||
		(id->subsystem_device != 0))
		return true;
	return false;
}

static s8 
pci_id_table_find_index(
	const struct pci_device_id *id_table,
	u16 vendor,
	u16 device,
	u16 subsystem_vendor,
	u16 subsystem_device)
{
	s8 i;

	if (!id_table)
		return -1;

	for (i = 0; pci_device_id_is_valid(&id_table[i]); i++) {
		if ((vendor == id_table[i].vendor) &&
			(device == id_table[i].device) &&
			((QCA_PCI_ANY_ID == id_table[i].subsystem_vendor) ||
				(subsystem_vendor != id_table[i].subsystem_vendor)) &&
			((QCA_PCI_ANY_ID == id_table[i].subsystem_device) ||
				(subsystem_device == id_table[i].subsystem_device))) {
			return i;
		}
	}

	return -1;
}

static s16
pci_driver_list_find_indexes(
	u16 vendor,
	u16 device,
	u16 subsystem_vendor,
	u16 subsystem_device)
{
	s8 i, j;

	for (i = 0; (pci_driver_list[i] != NULL); i++) {
		j = pci_id_table_find_index(pci_driver_list[i]->id_table,
				vendor, device, subsystem_vendor, subsystem_device);
		if (j >= 0)
			return ((i << 8) | j);
	}

	return -1;
}

const struct pci_device_id *pci_match(
	u16 vendor,
	u16 device,
	u16 subsystem_vendor,
	u16 subsystem_device)
{
	s16 indexes;
	struct pci_driver *driver;
	
	indexes = pci_driver_list_find_indexes(
		vendor, device, 
		subsystem_vendor, subsystem_device);
	if (indexes < 0)
		return NULL;

	driver = pci_driver_list[(indexes >> 8)];

	return &driver->id_table[(indexes & 0xFF)];
}

int pci_probe(pci_dev_handle dev)
{
	const struct pci_device_id *id;
	struct pci_driver *driver;
	s16 indexes;
	int ret;

	id = pci_get_hardware_id(dev);
	if (!id)
		return -EINVAL;

	indexes = pci_driver_list_find_indexes(
		id->vendor, id->device,
		id->subsystem_vendor, id->subsystem_device);

	driver = pci_driver_list[(indexes >> 8)];
	
	ret = driver->probe(dev);
	if (!ret)
		driver->probed = dev;

	return ret;
}

void pci_remove(pci_dev_handle dev)
{
	struct pci_driver **driver_next;

	driver_next = pci_driver_list;

	do {
		if (!(*driver_next))
			break;

		if ((*driver_next)->probed == dev) {
			(*driver_next)->probed = NULL;
			(*driver_next)->remove(dev);
		}
		driver_next++;
	} while (1);
}

/**********************************************************/
// DMA POOL

#define DMA_BUF_SZ_32K 	        0x8000
#define RESERVE32M_ADDR_32M 	0x2000000ul

struct dma_buf {
    dma_addr_t dma_addr;
    void *dma_mapping_addr;
    u32 alloc_size;
};

struct dma_buf_entry {
    list_entry_t node;
    struct dma_buf dma_desc;
};

void pci_request_dma_pool(
	pci_dev_handle dev,
	const char *name,
	dma_addr_t upper_addr,
	struct pci_dma_pool *dma_pool)
{
	u32 alloc_size = DMA_BUF_SZ_32K;
	dma_addr_t dma_addr;
	void *dma_mapping_addr;
	struct dma_buf_entry *dma_entry;

	dma_pool->name = name;
	dma_pool->dev = dev;
	dma_pool->count = 0;
	list_init_head(&dma_pool->free_list);

	BUILD_BUG_ON(DMA_BUF_SZ_32K < sizeof(struct dma_buf_entry));

	do {
		dma_entry = pci_dma_alloc_coherent(dev, alloc_size, &dma_addr, &dma_mapping_addr);
		if (!dma_entry) {
			pr_err("pci_dma_alloc_coherent alloc fail\n");
			return;
		}

		dma_entry->dma_desc.dma_addr = dma_addr;
		dma_entry->dma_desc.dma_mapping_addr = dma_mapping_addr;
		dma_entry->dma_desc.alloc_size = alloc_size;

		list_add_tail(&dma_entry->node, &dma_pool->free_list);
		dma_pool->count++;

		if (dma_entry->dma_desc.dma_addr > upper_addr) {
			pr_err("built dma pool %a: dev=0x%016llx, count=%d, "
				"last_dma_addr=0x%016llx, upper_addr=0x%016llx\n",
				dma_pool->name, dma_pool->dev,
				dma_pool->count,
				dma_entry->dma_desc.dma_addr,
				upper_addr);
			break;
		}
	} while (1);
}

void pci_free_dma_pool(struct pci_dma_pool *dma_pool)
{
	struct dma_buf_entry *dma_entry, *tmp;

	pr_err("free dma pool %a: dev=0x%016llx, count=%d\n",
		dma_pool->name, dma_pool->dev,
		dma_pool->count);

	list_for_each_entry_safe(dma_entry, tmp, &dma_pool->free_list, struct dma_buf_entry, node) {
		list_del(&dma_entry->node);
		dma_pool->count--;
		pci_dma_free_coherent(dma_pool->dev, dma_entry->dma_desc.alloc_size, dma_entry,
			dma_entry->dma_desc.dma_addr, dma_entry->dma_desc.dma_mapping_addr);
	}

	dma_pool->dev = NULL;
}