/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/* SPDX-License-Identifier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2019 The Linux Foundation. All rights reserved.
 */
#ifndef _ATH11K_PCI_H
#define _ATH11K_PCI_H

#include <qdf/qbase.h>
#include <qdf/pci.h>
#include <qdf/worker.h>

#define QCA6290_VENDOR_ID		0x17CB
#define QCA6290_DEVICE_ID		0x1100
#define QCA6390_VENDOR_ID		0x17CB
#define QCA6390_DEVICE_ID		0x1101
#define QCA6490_VENDOR_ID		0x17CB
#define QCA6490_DEVICE_ID		0x1103
#define PCI_BAR_NUM			    0
#define PCI_DMA_MASK_64_BIT		64
#define PCI_DMA_MASK_32_BIT		32

#define MAX_UNWINDOWED_ADDRESS 0x80000
#define WINDOW_ENABLE_BIT 0x40000000
#define WINDOW_REG_ADDRESS 0x310C
#define WINDOW_SHIFT 19
#define WINDOW_VALUE_MASK 0x3F
#define WINDOW_START MAX_UNWINDOWED_ADDRESS
#define WINDOW_RANGE_MASK 0x7FFFF

#define ATH11K_IRQ_CE0_OFFSET 3

#define PCIE_SOC_GLOBAL_RESET (0x3008)
#define PCIE_SOC_GLOBAL_RESET_V 1

#define WLAON_WARM_SW_ENTRY (0x1f80504)
#define WLAON_RESET_DBG_SW_ENTRY    (0x01F80508)
#define WLAON_SOC_RESET_CAUSE_REG   (0x01f8060c)

#define PCIE_Q6_COOKIE_ADDR         (0x01F80500)
#define PCIE_Q6_COOKIE_DATA         (0xC0000000)

#define HOST_RESET_REG                    0x1E40314

#define GCC_PRE_ARES_DEBUG_TIMER_VAL      0x01E40270
#define HOST_RESET_ADDR                   0xB0
#define HOST_RESET_PATTERN                0XFFFFFFFF


#define PCIE_PCIE_PARF_LTSSM              0X1E081B0
#define PARM_LTSSM_VALUE                  0x111

#define GCC_GCC_PCIE_HOT_RST              0X1E402BC
#define GCC_GCC_PCIE_HOT_RST_VAL          0x10

#define PCIE_PCIE_INT_ALL_CLEAR           0X1E08228
#define PCIE_SMLH_REQ_RST_LINK_DOWN       0x2
#define PCIE_INT_CLEAR_ALL                0xFFFFFFFF

#define WLAON_QFPROM_PWR_CTRL_REG         0x01F8031C
#define QFPROM_PWR_CTRL_VDD4BLOW_MASK     0x4
#define QFPROM_PWR_CTRL_SHUTDOWN_MASK     0x1

#define PCIE_GPIO_CFG_REG                 0x0180e000
#define PCIE_GPIO_RESET_VAL               0xC5

#define PCIE_QSERDES_COM_SYSCLK_EN_SEL_REG      0x01E0C0AC
#define PCIE_QSERDES_COM_SYSCLK_EN_SEL_VAL      0x10
#define PCIE_QSERDES_COM_SYSCLK_EN_SEL_MSK      0xFFFFFFFF
#define PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG1_REG 0x01E0C628
#define PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG1_VAL 0x02
#define PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG2_REG 0x01E0C62C
#define PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG2_VAL 0x52
#define PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG4_REG 0x01E0C634
#define PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG4_VAL 0xFF
#define PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG_MSK  0x000000FF



/* Register to wake the UMAC from power collapse */
#define PCIE_SCRATCH_0_SOC_PCIE_REG 0x4040
/* Register used for handshake mechanism to validate UMAC is awake */
#define PCIE_SOC_WAKE_PCIE_LOCAL_REG 0x3004
/* Register to clear PCIE_SOC_WAKE_PCIE_LOCAL_REG */
#define PCIE_WRAP_INTR_STATUS_SOC_PCIE_REG 0x4058

enum ath11k_pci_flags {
	ATH11K_PCI_FLAG_INIT_DONE,
};
#define ACCESS_ALWAYS_OFF 0xFE0

struct ath11k_msi_user {
	char *name;
	int num_vectors;
	u32 base_vector;
};

struct ath11k_msi_config {
	int total_vectors;
	int total_users;
	struct ath11k_msi_user *users;
};

struct ath11k_pci {
	void *pdev;
	//struct device *dev;
	struct ath11k_base *ab;
	void __iomem *mem;
	u32 mem_len;
	u16 dev_id;
	u32 chip_id;
	struct ath11k_msi_config *msi_config;
	u32 msi_ep_base_data;
	struct mhi_controller *mhi_ctrl;
	unsigned long mhi_state;
	u32 register_window;
	spinlock_t window_lock;
	struct work_struct rddm_worker;
	
	/* enum ath11k_pci_flags */
	unsigned long flags;

    struct {
        void *vaddr;
        dma_addr_t paddr;
        void *paddr_mapping_addr;
    } dummy_msi;

	/* a dma pool to be reserved to avoid dma address < 8K being used */
	struct pci_dma_pool reserved_dma_pool;
};

int ath11k_pci_get_user_msi_assignment(struct ath11k_pci *ar_pci, char *user_name,
				       int *num_vectors, u32 *user_base_data,
				       u32 *base_vector);

int ath11k_pci_get_msi_irq(void* dev, unsigned int vector);


/* mhi.h in ath11k */
#define ATH11K_PCI_FW_FILE_NAME		L"amss.bin"

enum ath11k_mhi_state {
    ATH11K_MHI_INIT,
    ATH11K_MHI_DEINIT,
    ATH11K_MHI_POWER_ON,
    ATH11K_MHI_POWER_OFF,
    ATH11K_MHI_FORCE_POWER_OFF,
    ATH11K_MHI_SUSPEND,
    ATH11K_MHI_RESUME,
    ATH11K_MHI_TRIGGER_RDDM,
    ATH11K_MHI_RDDM,
    ATH11K_MHI_RDDM_DONE,
};

int ath11k_pci_start_mhi(struct ath11k_pci *ar_pci);
void ath11k_pci_stop_mhi(struct ath11k_pci *ar_pci);
int ath11k_pci_register_mhi(struct ath11k_pci *ar_pci);
void ath11k_pci_unregister_mhi(struct ath11k_pci *ar_pci);
int ath11k_pci_rddm_mhi(struct ath11k_pci *ar_pci);

u32 ath11k_probe(pci_dev_handle pdev);

#endif
