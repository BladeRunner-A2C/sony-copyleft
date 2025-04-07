/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
// SPDX-License-Identifier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2019 The Linux Foundation. All rights reserved.
 */


#include <Uefi.h>
#include <Protocol/PciIo.h>
#include <IndustryStandard/Pci22.h>
#include <qdf/qbase.h>
#include <mhi/mhi.h>
#include <mhi/internal.h>
#include "core.h"
#include "hif.h"
#include "pci.h"
#include "debug.h"
#include "coredump.h"
#include "htc.h"
#include <qdf/file.h>

#define TCSR_SOC_HW_VERSION		0x0224
#define TCSR_SOC_HW_VERSION_MAJOR_MASK	GENMASK(16, 8)
#define TCSR_SOC_HW_VERSION_MINOR_MASK	GENMASK(7, 0)


 /* EFI access offset directly */
#define PCI_BASE_OFFSET(B) (u32)((u8*)(B) - (u8*)0)

const char *irq_name[ATH11K_IRQ_NUM_MAX] = {
	"bhi",
	"mhi-er0",
	"mhi-er1",
	"ce0",
	"ce1",
	"ce2",
	"ce3",
	"ce4",
	"ce5",
	"ce6",
	"ce7",
	"ce8",
	"ce9",
	"ce10",
	"ce11",
	"host2wbm-desc-feed",
	"host2reo-re-injection",
	"host2reo-command",
	"host2rxdma-monitor-ring3",
	"host2rxdma-monitor-ring2",
	"host2rxdma-monitor-ring1",
	"reo2ost-exception",
	"wbm2host-rx-release",
	"reo2host-status",
	"reo2host-destination-ring4",
	"reo2host-destination-ring3",
	"reo2host-destination-ring2",
	"reo2host-destination-ring1",
	"rxdma2host-monitor-destination-mac3",
	"rxdma2host-monitor-destination-mac2",
	"rxdma2host-monitor-destination-mac1",
	"ppdu-end-interrupts-mac3",
	"ppdu-end-interrupts-mac2",
	"ppdu-end-interrupts-mac1",
	"rxdma2host-monitor-status-ring-mac3",
	"rxdma2host-monitor-status-ring-mac2",
	"rxdma2host-monitor-status-ring-mac1",
	"host2rxdma-host-buf-ring-mac3",
	"host2rxdma-host-buf-ring-mac2",
	"host2rxdma-host-buf-ring-mac1",
	"rxdma2host-destination-ring-mac3",
	"rxdma2host-destination-ring-mac2",
	"rxdma2host-destination-ring-mac1",
	"host2tcl-input-ring4",
	"host2tcl-input-ring3",
	"host2tcl-input-ring2",
	"host2tcl-input-ring1",
	"wbm2host-tx-completions-ring3",
	"wbm2host-tx-completions-ring2",
	"wbm2host-tx-completions-ring1",
	"tcl2host-status-ring",
};

static const u8 ath11k_tx_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    ATH11K_TX_RING_MASK_0,
    ATH11K_TX_RING_MASK_1,
    ATH11K_TX_RING_MASK_2,
};

#if ATH11K_SUPPORT_MONITOR
static const u8 ath11k_rx_mon_status_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    0, 0, 0, 0,
    ATH11K_RX_MON_STATUS_RING_MASK_0,
    ATH11K_RX_MON_STATUS_RING_MASK_1,
    ATH11K_RX_MON_STATUS_RING_MASK_2,
};
#endif

static const u8 ath11k_rx_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    0, 0, 0, 0, 0, 0, 0,
    ATH11K_RX_RING_MASK_0,
    ATH11K_RX_RING_MASK_1,
    ATH11K_RX_RING_MASK_2,
    ATH11K_RX_RING_MASK_3,
};

static const u8 ath11k_rx_err_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    ATH11K_RX_ERR_RING_MASK_0,
};

static const u8 ath11k_rx_wbm_rel_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    ATH11K_RX_WBM_REL_RING_MASK_0,
};

static const u8 ath11k_reo_status_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    ATH11K_REO_STATUS_RING_MASK_0,
};

#ifdef CONFIG_ATH11K_AHB
static const u8 ath11k_rxdma2host_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    ATH11K_RXDMA2HOST_RING_MASK_0,
    ATH11K_RXDMA2HOST_RING_MASK_1,
    ATH11K_RXDMA2HOST_RING_MASK_2,
};

static const u8 ath11k_host2rxdma_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    ATH11K_HOST2RXDMA_RING_MASK_0,
    ATH11K_HOST2RXDMA_RING_MASK_1,
    ATH11K_HOST2RXDMA_RING_MASK_2,
};
#else
static const u8 ath11k_rxdma2host_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    ATH11K_RXDMA2HOST_RING_MASK_0,
    ATH11K_RXDMA2HOST_RING_MASK_1,
    ATH11K_RXDMA2HOST_RING_MASK_2
};

static const u8 ath11k_host2rxdma_ring_mask[ATH11K_EXT_IRQ_GRP_NUM_MAX] = {
    0, 0, 0,
};
#endif

static const struct pci_device_id ath11k_pci_id_table[] = {
	{ QCA6490_VENDOR_ID, QCA6490_DEVICE_ID, QCA_PCI_ANY_ID, QCA_PCI_ANY_ID,
	  QCA_FIRMWARE_SUPPORT_WMI_DIAG },
	{ 0 }
};

static struct ath11k_msi_config global_msi_config = {
	.total_vectors = 32,
	.total_users = 4,
	.users = (struct ath11k_msi_user[]) {
		{ .name = "MHI", .num_vectors = 3, .base_vector = 0 },
		{ .name = "CE", .num_vectors = 10, .base_vector = 3 },
		{ .name = "WAKE", .num_vectors = 1, .base_vector = 13 },
		{ .name = "DP", .num_vectors = 18, .base_vector = 14 },
	},
};

static inline void ath11k_pci_select_window(struct ath11k_pci *ar_pci, u32 offset)
{
	u32 window = (offset >> WINDOW_SHIFT) & WINDOW_VALUE_MASK;

	if (window != ar_pci->register_window) {
		pci_write32(ar_pci->pdev, PCI_BASE_OFFSET(ar_pci->mem) + WINDOW_REG_ADDRESS,
            WINDOW_ENABLE_BIT | window);
		pci_read32(ar_pci->pdev, PCI_BASE_OFFSET(ar_pci->mem) + WINDOW_REG_ADDRESS);
		ar_pci->register_window = window;
	}
}

static inline struct ath11k_pci *ath11k_pci_priv(struct ath11k_base *ab)
{
	return (struct ath11k_pci *)ab->drv_priv;
}

static void ath11k_pci_write32(struct ath11k_base *ab, u32 offset, u32 value)
{
	struct ath11k_pci *ab_pci = ath11k_pci_priv(ab);

	/* for offset beyond BAR + 4K - 32, may
	 * need to wakeup MHI to access.
	 */
	if (test_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags) &&
	    offset >= ACCESS_ALWAYS_OFF)
		mhi_device_get_sync(ab_pci->mhi_ctrl->mhi_dev);

	if (!ab->use_register_windowing ||
	    offset < MAX_UNWINDOWED_ADDRESS)
	    pci_write32(ab_pci->pdev, PCI_BASE_OFFSET(ab_pci->mem) + offset, value);
	else {
		spin_lock_bh(&ab_pci->window_lock);
		ath11k_pci_select_window(ab_pci, offset);
		pci_write32(ab_pci->pdev, 
	            PCI_BASE_OFFSET(ab_pci->mem) + WINDOW_START + (offset & WINDOW_RANGE_MASK), value);
		spin_unlock_bh(&ab_pci->window_lock);
	}

	if (test_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags) &&
	    offset >= ACCESS_ALWAYS_OFF)
		mhi_device_put(ab_pci->mhi_ctrl->mhi_dev);
}

static u32 ath11k_pci_read32(struct ath11k_base *ab, u32 offset)
{
	struct ath11k_pci *ab_pci = ath11k_pci_priv(ab);
	u32 val;

	/* for offset beyond BAR + 4K - 32, may
	 * need to wakeup MHI to access.
	 */
	if (test_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags) &&
	    offset >= ACCESS_ALWAYS_OFF)
		mhi_device_get_sync(ab_pci->mhi_ctrl->mhi_dev);

	if (!ab->use_register_windowing ||
	    offset < MAX_UNWINDOWED_ADDRESS)
		val = pci_read32(ab_pci->pdev, PCI_BASE_OFFSET(ab_pci->mem) + offset);
	else {
		spin_lock_bh(&ab_pci->window_lock);
		ath11k_pci_select_window(ab_pci, offset);
		val = pci_read32(ab_pci->pdev, 
	            PCI_BASE_OFFSET(ab_pci->mem) + WINDOW_START + (offset & WINDOW_RANGE_MASK));
		spin_unlock_bh(&ab_pci->window_lock);
	}

	if (test_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags) &&
	    offset >= ACCESS_ALWAYS_OFF)
		mhi_device_put(ab_pci->mhi_ctrl->mhi_dev);

	return val;
}

int ath11k_pci_get_msi_irq(void *dev, unsigned int vector)
{
#if 0
	struct pci_dev *pci_dev = to_pci_dev(dev);
	int irq_num;

	irq_num = pci_irq_vector(pci_dev, vector);

	return irq_num;
#endif
	return vector;
}

void ath11k_pci_set_mhictrl_reset(struct ath11k_base *ab)
{
	u32 val;

	DEBUG_PARAMETER(val);

	val = ath11k_pci_read32(ab, MHISTATUS);

	ath11k_dbg(ab, ATH11K_DBG_PCI, "MHISTATUS 0x%x\n", val);

	/* Observed on Hastings that after SOC_GLOBAL_RESET, MHISTATUS
	 * has SYSERR bit set and thus need to set MHICTRL_RESET
	 * to clear SYSERR.
	 */
	ath11k_pci_write32(ab, MHICTRL, MHICTRL_RESET_MASK);

	mdelay(10);
}

static void ath11k_pci_reset_txvecdb(struct ath11k_base *ab)
{
	ath11k_pci_write32(ab, PCIE_TXVECDB, 0);
}

static void ath11k_pci_reset_txvecstatus(struct ath11k_base *ab)
{
	ath11k_pci_write32(ab, PCIE_TXVECSTATUS, 0);
}

static void ath11k_pci_reset_rxvecdb(struct ath11k_base *ab)
{
	ath11k_pci_write32(ab, PCIE_RXVECDB, 0);
}

static void ath11k_pci_reset_rxvecstatus(struct ath11k_base *ab)
{
	ath11k_pci_write32(ab, PCIE_RXVECSTATUS, 0);
}

void ath11k_mhi_clear_vector(struct ath11k_base *ab)
{
	ath11k_pci_reset_txvecdb(ab);
	ath11k_pci_reset_txvecstatus(ab);
	ath11k_pci_reset_rxvecdb(ab);
	ath11k_pci_reset_rxvecstatus(ab);
}


void ath11k_pci_enable_LTSSM(struct ath11k_base *ab)
{
	u32 val;
	int count = 5;

	val = ath11k_pci_read32(ab, PCIE_PCIE_PARF_LTSSM);

	/* PCIE link seems very unstable after the Hot Reset*/
	while (val != PARM_LTSSM_VALUE && count--) {
		if (val == 0xffffffff)
			mdelay(5);
		ath11k_pci_write32(ab, PCIE_PCIE_PARF_LTSSM, PARM_LTSSM_VALUE);

		val = ath11k_pci_read32(ab, PCIE_PCIE_PARF_LTSSM);
	}

	ath11k_dbg(ab, ATH11K_DBG_PCI, "read parf_ltssm:0x%x\n", val);

	val = ath11k_pci_read32(ab, GCC_GCC_PCIE_HOT_RST);

	val |= GCC_GCC_PCIE_HOT_RST_VAL | 0x10;

	ath11k_pci_write32(ab, GCC_GCC_PCIE_HOT_RST, val);

	val = ath11k_pci_read32(ab, GCC_GCC_PCIE_HOT_RST);

	ath11k_dbg(ab, ATH11K_DBG_PCI,
		   "after set, read GCC_GCC_PCIE_HOT_RST 0x%x\n", val);

	mdelay(5);
}

static void ath11k_pci_clear_all_intrs(struct ath11k_base *ab)
{
	/* This is a WAR for PCIE Hotreset.
	 * When target receive Hotreset, but will set the interrupt.
	 * So when download SBL again, SBL will open Interrupt and
	 * receive it, and crash immediately.
	 */
	ath11k_pci_write32(ab, PCIE_PCIE_INT_ALL_CLEAR, PCIE_INT_CLEAR_ALL);
}

static void ath11k_pci_set_wlaon_pwr_ctrl(struct ath11k_base *ab, bool set_vdd4blow)
{
	u32 val;

	/* control FW otp write privilege.
	 * Disable the write prvilige to protect otp from
	 * overwritten by unknown electric signals. This issue
	 * is seen in stress test.
	 */
	val = ath11k_pci_read32(ab, WLAON_QFPROM_PWR_CTRL_REG);

	if (set_vdd4blow)
		val |= QFPROM_PWR_CTRL_VDD4BLOW_MASK;
	else
		val &= ~QFPROM_PWR_CTRL_VDD4BLOW_MASK;

	ath11k_pci_write32(ab, WLAON_QFPROM_PWR_CTRL_REG, val);
}

static bool ath11k_pci_set_link_reg(struct ath11k_base *ab,
				    u32 offset, u32 value, u32 mask)
{
	u32 ret;
	int count = 10;

	ret = ath11k_pci_read32(ab, offset);
	if ((ret & mask) == value)
		return true;

	while (count > 0) {
		ath11k_pci_write32(ab, offset, (ret & ~mask) | value);
		ret = ath11k_pci_read32(ab, offset);
		if ((ret & mask) == value)
			return true;

		mdelay(2);
		count--;
	}

	ath11k_err(ab, "Failed to set Pcie Link Register 0x%08x to 0x%08x\n", offset, ret);
	return false;
}


void ath11k_pci_fix_l1ss(struct ath11k_base *ab)
{
	if (!ath11k_pci_set_link_reg(ab,
				     PCIE_QSERDES_COM_SYSCLK_EN_SEL_REG,
				     PCIE_QSERDES_COM_SYSCLK_EN_SEL_VAL,
				     PCIE_QSERDES_COM_SYSCLK_EN_SEL_MSK)) {
		ath11k_err(ab, "set sysclk error\n");
		return;
	}

	if (!ath11k_pci_set_link_reg(ab,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG1_REG,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG1_VAL,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG_MSK)) {
		ath11k_err(ab, "set dtct_config1 error\n");
		return;
	}

	if (!ath11k_pci_set_link_reg(ab,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG2_REG,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG2_VAL,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG_MSK)) {
		ath11k_err(ab, "set dtct_config2 error\n");
		return;
	}

	if (!ath11k_pci_set_link_reg(ab,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG4_REG,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG4_VAL,
				     PCIE_USB3_PCS_MISC_OSC_DTCT_CONFIG_MSK))
		ath11k_err(ab, "set dtct_config4 error\n");
}

void ath11k_pci_soc_global_reset(struct ath11k_base *ab)
{
	u32 val;
	u32 delay;

	val = ath11k_pci_read32(ab, PCIE_SOC_GLOBAL_RESET);

	val |= PCIE_SOC_GLOBAL_RESET_V;

	ath11k_pci_write32(ab, PCIE_SOC_GLOBAL_RESET, val);

	/* TODO: exact time to sleep is uncertain */
	delay = 10;
	mdelay(delay);

	/* Need to toggle V bit back otherwise stuck in reset status */
	val &= ~PCIE_SOC_GLOBAL_RESET_V;

	ath11k_pci_write32(ab, PCIE_SOC_GLOBAL_RESET, val);

	mdelay(delay);

	val = ath11k_pci_read32(ab, PCIE_SOC_GLOBAL_RESET);
	if (val == 0xffffffff)
		ath11k_err(ab, "link down error\n");
}

void ath11k_pci_clear_dbg_registers(struct ath11k_base *ab)
{
	u32 val;

	DEBUG_PARAMETER(val);

	/* read cookie */
	val = ath11k_pci_read32(ab, PCIE_Q6_COOKIE_ADDR);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "cookie:0x%x\n", val);

	val = ath11k_pci_read32(ab, WLAON_WARM_SW_ENTRY);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "WLAON_WARM_SW_ENTRY 0x%x\n", val);

	/* TODO: exact time to sleep is uncertain */
	mdelay(10);

	/* write 0 to WLAON_WARM_SW_ENTRY to prevent Q6 from
	 * continuing warm path and entering dead loop.
	 */
	ath11k_pci_write32(ab, WLAON_WARM_SW_ENTRY, 0);
	mdelay(10);

	val = ath11k_pci_read32(ab, WLAON_WARM_SW_ENTRY);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "WLAON_WARM_SW_ENTRY 0x%x\n", val);

	/* A read clear register. clear the register to prevent
	 * Q6 from entering wrong code path.
	 */
	val = ath11k_pci_read32(ab, WLAON_SOC_RESET_CAUSE_REG);
	ath11k_dbg(ab, ATH11K_DBG_PCI, "soc reset cause:%d\n", val);
}


void ath11k_pci_force_wake(struct ath11k_base *ab)
{
	ath11k_pci_write32(ab, PCIE_SOC_WAKE_PCIE_LOCAL_REG, 1);
	mdelay(5);
}

void ath11k_pci_reset_wake(struct ath11k_base *ab)
{
    ath11k_pci_write32(ab, PCIE_WRAP_INTR_STATUS_SOC_PCIE_REG, 1);
}

static void ath11k_pci_gpio_reset(struct ath11k_base *ab)
{
    int old_val, new_val;

	DEBUG_PARAMETER(new_val);

    old_val = ath11k_pci_read32(ab, PCIE_GPIO_CFG_REG);
    if (old_val == PCI_READ_ERROR_VAL) {
        ath11k_dbg(ab, ATH11K_DBG_PCI,
            "failed to read the gpio 0x%08x cfg: 0x%x\n", PCIE_GPIO_CFG_REG, old_val);
        return;
    }
    if (old_val == PCIE_GPIO_RESET_VAL) {
        ath11k_dbg(ab, ATH11K_DBG_PCI, 
            "gpio 0x%08x cfg is already expected: 0x%x\n", PCIE_GPIO_CFG_REG, old_val);
        return;
    }
    
    ath11k_pci_write32(ab, PCIE_GPIO_CFG_REG, PCIE_GPIO_RESET_VAL);
    mdelay(10);
    new_val = ath11k_pci_read32(ab, PCIE_GPIO_CFG_REG);
    ath11k_dbg(ab, ATH11K_DBG_PCI, 
        "update gpio 0x%08x cfg: 0x%x -> 0x%x (expect 0x%x)\n", 
        PCIE_GPIO_CFG_REG, old_val, new_val, PCIE_GPIO_RESET_VAL);
}

void ath11k_pci_sw_reset(struct ath11k_base *ab, bool power_on)
{
	if (power_on) {
		ath11k_pci_enable_LTSSM(ab);
		ath11k_pci_clear_all_intrs(ab);
		ath11k_pci_set_wlaon_pwr_ctrl(ab, false);
		ath11k_pci_fix_l1ss(ab);
	}

	ath11k_mhi_clear_vector(ab);
    ath11k_pci_clear_dbg_registers(ab);
	ath11k_pci_soc_global_reset(ab);
	ath11k_pci_set_mhictrl_reset(ab);
}

void ath11k_pci_get_msi_address(struct ath11k_base *ab, u32 *msi_addr_lo,
				u32 *msi_addr_hi)
{
#if 0
    pci_dev_handle *pci_dev = ab->pdev;

	pci_read_config_dword(pci_dev, PCI_MSI_ADDRESS_LO, msi_addr_lo);

	pci_read_config_dword(pci_dev, PCI_MSI_ADDRESS_HI, msi_addr_hi);

#endif
    /* UEFI doesn't support interrupt, use the dummy msi */
    struct ath11k_pci *ar_pci = ath11k_pci_priv(ab);

    *msi_addr_lo = (u32)(ar_pci->dummy_msi.paddr & 0xFFFFFFFF);
    *msi_addr_hi = (u32)(ar_pci->dummy_msi.paddr >> 32);

}

int ath11k_pci_get_user_msi_assignment(struct ath11k_pci *ar_pci, char *user_name,
				       int *num_vectors, u32 *user_base_data,
				       u32 *base_vector)
{
	struct ath11k_msi_config *msi_config;
	int idx;

	msi_config = ar_pci->msi_config;
	if (!msi_config) {
		ath11k_err(ar_pci->ab, "MSI configuration is missing\n");
		return -EINVAL;
	}

	for (idx = 0; idx < msi_config->total_users; idx++) {
		if (strcmp(user_name, msi_config->users[idx].name) == 0) {
			*num_vectors = msi_config->users[idx].num_vectors;
			*user_base_data = msi_config->users[idx].base_vector
				+ ar_pci->msi_ep_base_data;
			*base_vector = msi_config->users[idx].base_vector;
			
            ath11k_info(ar_pci->ab, 
                "Assign MSI to user: %a, num_vectors: %d, user_base_data: %u, base_vector: %u\n",
                user_name, *num_vectors, *user_base_data, *base_vector);

			return 0;
		}
	}

    ath11k_err(ar_pci->ab, "Failed to find MSI assignment for %s!\n", user_name);

	return -EINVAL;
}

int ath11k_get_user_msi_assignment(struct ath11k_base *ab, char *user_name,
				   int *num_vectors, u32 *user_base_data,
				   u32 *base_vector)
{
	struct ath11k_pci *ab_pci = ath11k_pci_priv(ab);

	return ath11k_pci_get_user_msi_assignment(ab_pci, user_name, num_vectors, user_base_data,
						 base_vector);
}

static void ath11k_pci_free_ext_irq(struct ath11k_base *ab)
{
	u32 i, j;

	for (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) {
		struct ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		for (j = 0; j < irq_grp->num_irq; j++)
			free_irq(ab->irq_num[irq_grp->irqs[j]], irq_grp);

		//netif_napi_del(&irq_grp->napi);
	}
}

static void ath11k_pci_free_irq(struct ath11k_base *ab)
{
	int irq_idx;
	u32 i;

	for (i = 0; i < CE_COUNT; i++) {
		if (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			continue;
		irq_idx = ATH11K_IRQ_CE0_OFFSET + i;
		free_irq(ab->irq_num[irq_idx], &ab->ce.ce_pipe[i]);
	}

	ath11k_pci_free_ext_irq(ab);
}

static void ath11k_pci_ce_irq_enable(struct ath11k_base *ab, u16 ce_id)
{
	u32 irq_idx;

	irq_idx = ATH11K_IRQ_CE0_OFFSET + ce_id;
	enable_irq(ab->irq_num[irq_idx]);
}

static void ath11k_pci_ce_irq_disable(struct ath11k_base *ab, u16 ce_id)
{
	u32 irq_idx;

	irq_idx = ATH11K_IRQ_CE0_OFFSET + ce_id;
	disable_irq_nosync(ab->irq_num[irq_idx]);
}

static void ath11k_pci_ce_irqs_disable(struct ath11k_base *ab)
{
	u32 i;

	for (i = 0; i < CE_COUNT; i++) {
		if (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			continue;
		ath11k_pci_ce_irq_disable(ab, (u16)i);
	}
}

static void ath11k_pci_sync_ce_irqs(struct ath11k_base *ab)
{
	u32 i;
	int irq_idx;

	for (i = 0; i < CE_COUNT; i++) {
		if (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			continue;

		irq_idx = ATH11K_IRQ_CE0_OFFSET + i;
		synchronize_irq(ab->irq_num[irq_idx]);
	}
}

#if 0
static void ath11k_pci_ce_tasklet(unsigned long data)
{
	struct ath11k_ce_pipe *ce_pipe = (struct ath11k_ce_pipe *)data;

	ath11k_ce_per_engine_service(ce_pipe->ab, ce_pipe->pipe_num);

	ath11k_pci_ce_irq_enable(ce_pipe->ab, ce_pipe->pipe_num);
}
#endif

static int ath11k_pci_ce_interrupt_handler(int irq, int budget, void *arg)
{
	struct ath11k_ce_pipe *ce_pipe = (struct ath11k_ce_pipe *)arg;
    int handled;

	//ath11k_pci_ce_irq_disable(ce_pipe->ab, ce_pipe->pipe_num);
	//tasklet_schedule(&ce_pipe->intr_tq);

    handled = ath11k_ce_per_engine_service(ce_pipe->ab, ce_pipe->pipe_num);

	return handled ? 1 : 0;
}

static void ath11k_pci_init_qmi_ce_config(struct ath11k_base *ab)
{
	struct ath11k_qmi_ce_cfg *cfg = &ab->qmi.ce_cfg;

	cfg->tgt_ce = ab->hw_params.target_ce_config;
	cfg->tgt_ce_len = ab->hw_params.target_ce_count;

	cfg->svc_to_ce_map = ab->hw_params.svc_to_ce_map;
	cfg->svc_to_ce_map_len = ab->hw_params.svc_to_ce_map_len;
	ab->qmi.service_ins_id = ATH11K_QMI_WLFW_SERVICE_INS_ID_V01_QCA6x90;
}

static void ath11k_pci_ce_irqs_enable(struct ath11k_base *ab)
{
	u32 i;

	for (i = 0; i < CE_COUNT; i++) {
		if (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			continue;
		ath11k_pci_ce_irq_enable(ab, (u16)i);
	}
}

int ath11k_pci_qca6x90_powerup(struct ath11k_pci *ar_pci)
{
    ath11k_pci_sw_reset(ar_pci->ab, true);
	return ath11k_pci_start_mhi(ar_pci);
}

void ath11k_pci_qca6x90_powerdown(struct ath11k_pci *ar_pci)
{
	ath11k_pci_stop_mhi(ar_pci);
	//ath11k_pci_force_wake(ar_pci->ab);
	ath11k_pci_sw_reset(ar_pci->ab, false);
}

int ath11k_pci_target_dump(struct ath11k_pci *ar_pci)
{
    return ath11k_pci_rddm_mhi(ar_pci);
}

static int ath11k_pci_get_msi_assignment(struct ath11k_pci *ar_pci)
{
	ar_pci->msi_config = &global_msi_config;

	return 0;
}

static void ath11k_pci_ext_grp_disable(struct ath11k_ext_irq_grp *irq_grp)
{
	u32 i;

	for (i = 0; i < irq_grp->num_irq; i++)
		disable_irq_nosync(irq_grp->ab->irq_num[irq_grp->irqs[i]]);
}

static void __ath11k_pci_ext_irq_disable(struct ath11k_base *sc)
{
	struct sk_buff *skb;
	u32 i;

	for (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) {
		struct ath11k_ext_irq_grp *irq_grp = &sc->ext_irq_grp[i];

		ath11k_pci_ext_grp_disable(irq_grp);

        // TODOTODO: NAPI
		//napi_synchronize(&irq_grp->napi);
		//napi_disable(&irq_grp->napi);

		while ((skb = __skb_dequeue(&irq_grp->pending_q)) != NULL)
			dev_kfree_skb_any(skb);
	}
}

static void ath11k_pci_ext_grp_enable(struct ath11k_ext_irq_grp *irq_grp)
{
	u32 i;

	for (i = 0; i < irq_grp->num_irq; i++)
		enable_irq(irq_grp->ab->irq_num[irq_grp->irqs[i]]);
}

static void ath11k_pci_ext_irq_enable(struct ath11k_base *ab)
{
	int i;

	for (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) {
		struct ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

        // TODOTODO: NAPI
		//napi_enable(&irq_grp->napi);
		ath11k_pci_ext_grp_enable(irq_grp);
	}
}

static void ath11k_pci_sync_ext_irqs(struct ath11k_base *ab)
{
	u32 i, j;
	int irq_idx;

	for (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) {
		struct ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];

		for (j = 0; j < irq_grp->num_irq; j++) {
			irq_idx = irq_grp->irqs[j];

			synchronize_irq(ab->irq_num[irq_idx]);
		}
	}
}

static void ath11k_pci_ext_irq_disable(struct ath11k_base *ab)
{
	__ath11k_pci_ext_irq_disable(ab);
	ath11k_pci_sync_ext_irqs(ab);
}

static int ath11k_pci_ext_grp_napi_poll(struct napi_struct *napi, int budget)
{
	struct ath11k_ext_irq_grp *irq_grp = container_of(napi,
						struct ath11k_ext_irq_grp,
						napi);
	struct ath11k_base *ab = irq_grp->ab;
	int work_done;

	work_done = ath11k_dp_service_srng(ab, irq_grp, budget);
#if 0  // TODOTODO: NAPI
	if (work_done < budget) {
		napi_complete_done(napi, work_done);
		ath11k_pci_ext_grp_enable(irq_grp);
	}
#endif

	if (work_done > budget)
		work_done = budget;

	return work_done;
}

static int ath11k_pci_ext_interrupt_handler(int irq, int budget, void *arg)
{
	struct ath11k_ext_irq_grp *irq_grp = arg;
    int work_done;

	//ath11k_info(irq_grp->ab, "ext irq:%d\n", irq);

	//ath11k_pci_ext_grp_disable(irq_grp);
    //ath11k_info(irq_grp->ab, "napi_schedule\n");
	//napi_schedule(&irq_grp->napi);

    work_done = ath11k_pci_ext_grp_napi_poll(&irq_grp->napi, budget);

    return work_done;
}

static void ath11k_pci_ext_ring_mask_config(struct ath11k_base *ab)
{
	int i;

	for (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) {
		ab->ring_mask.tx_ring_mask[i] = ath11k_tx_ring_mask[i];
#if ATH11K_SUPPORT_MONITOR
		ab->ring_mask.rx_mon_status_ring_mask[i] =
			ath11k_rx_mon_status_ring_mask[i];
#endif
		ab->ring_mask.rx_ring_mask[i] = ath11k_rx_ring_mask[i];
		ab->ring_mask.rx_err_ring_mask[i] = ath11k_rx_err_ring_mask[i];
		ab->ring_mask.rx_wbm_rel_ring_mask[i] = ath11k_rx_wbm_rel_ring_mask[i];
		ab->ring_mask.reo_status_ring_mask[i] = ath11k_reo_status_ring_mask[i];
		ab->ring_mask.rxdma2host_ring_mask[i] = ath11k_rxdma2host_ring_mask[i];
		ab->ring_mask.host2rxdma_ring_mask[i] = ath11k_host2rxdma_ring_mask[i];
	}
}

static int ath11k_pci_ext_irq_config(struct ath11k_base *ab)
{
	u32 i, j;
	int ret;
	int num_vectors = 0;
	u32 user_base_data = 0, base_vector = 0;
	
	ath11k_pci_ext_ring_mask_config(ab);
	
	ath11k_pci_get_user_msi_assignment(ath11k_pci_priv(ab), "DP",
					   &num_vectors, &user_base_data,
					   &base_vector);

	for (i = 0; i < ATH11K_EXT_IRQ_GRP_NUM_MAX; i++) {
		struct ath11k_ext_irq_grp *irq_grp = &ab->ext_irq_grp[i];
		u32 num_irq = 0;

		irq_grp->ab = ab;
		irq_grp->grp_id = i;

        // TODOTODO
		//init_dummy_netdev(&irq_grp->napi_ndev);
		//netif_napi_add(&irq_grp->napi_ndev, &irq_grp->napi,
		//	       ath11k_pci_ext_grp_napi_poll, NAPI_POLL_WEIGHT);
		__skb_queue_head_init(&irq_grp->pending_q);

		if (ath11k_tx_ring_mask[i] || ath11k_rx_ring_mask[i] ||
		    ath11k_rx_err_ring_mask[i] || ath11k_rx_wbm_rel_ring_mask[i] ||
		    ath11k_reo_status_ring_mask[i] || ath11k_rxdma2host_ring_mask[i] ||
		    ath11k_host2rxdma_ring_mask[i] 
#if ATH11K_SUPPORT_MONITOR
            || ath11k_rx_mon_status_ring_mask[i]
#endif
            ) {
			num_irq = 1;
		}

		irq_grp->num_irq = num_irq;
		irq_grp->irqs[0] = base_vector + i;

		for (j = 0; j < irq_grp->num_irq; j++) {
			int irq_idx = irq_grp->irqs[j];
			int vector = (i % num_vectors) + base_vector;
			int irq = ath11k_pci_get_msi_irq(ab->dev, vector);

			ab->irq_num[irq_idx] = irq;

			ath11k_info(ab, "irq:%d group:%d\n", irq, i);
			ret = request_irq(irq, ath11k_pci_ext_interrupt_handler,
					  "DP_EXT_IRQ", irq_grp);
			if (ret) {
				ath11k_err(ab, "failed request_irq for %d\n",
					   vector);
			}
			// balance irq_enable
			disable_irq_nosync(ab->irq_num[irq_idx]);
		}
	}

	return 0;
}

static int ath11k_pci_config_irq(struct ath11k_base *ab)
{
	struct ath11k_ce_pipe *ce_pipe = NULL;
	u32 msi_data_start = 0;
	int msi_data_count = 0;
	u32 msi_irq_start  = 0;
	unsigned int msi_data;
	int irq, ret, irq_idx;
    u32 i;

	ret = ath11k_pci_get_user_msi_assignment(ath11k_pci_priv(ab),
						 "CE", &msi_data_count,
						 &msi_data_start, &msi_irq_start);

	/* Configure CE irqs */
	for (i = 0; i < CE_COUNT; i++) {
		msi_data = (i % msi_data_count) + msi_irq_start;
		irq = ath11k_pci_get_msi_irq(ab->dev, msi_data);
		ce_pipe = &ab->ce.ce_pipe[i];

		if (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			continue;

		irq_idx = ATH11K_IRQ_CE0_OFFSET + i;

		ath11k_info(ab, "irq:%d, irq_idx:%d\n", irq, irq_idx);

		//tasklet_init(&ce_pipe->intr_tq, ath11k_pci_ce_tasklet,
		//	     (unsigned long)ce_pipe);

		ret = request_irq(irq, ath11k_pci_ce_interrupt_handler,
				  irq_name[irq_idx], ce_pipe);
		if (ret)
			return ret;
		ab->irq_num[irq_idx] = irq;
		ath11k_pci_ce_irq_disable(ab, (u16)i);
	}

	/* To Do Configure external interrupts */
	ath11k_pci_ext_irq_config(ab);

	return ret;
}

#if 0
static int ath11k_pci_enable_msi(struct ath11k_pci *ar_pci)
{
	struct ath11k_base *ab = ar_pci->ab;
	struct ath11k_msi_config *msi_config;
	struct msi_desc *msi_desc;
	int num_vectors;
	int ret;

	ret = ath11k_pci_get_msi_assignment(ar_pci);
	if (ret) {
		ath11k_err(ab, "failed to get MSI assignment, err = %d\n", ret);
		goto out;
	}

	msi_config = ar_pci->msi_config;
	if (!msi_config) {
		ath11k_err(ab, "msi_config is NULL!\n");
		ret = -EINVAL;
		goto out;
	}

	num_vectors = pci_alloc_irq_vectors(ar_pci->pdev,
					    msi_config->total_vectors,
					    msi_config->total_vectors,
					    PCI_IRQ_MSI);
	if (num_vectors != msi_config->total_vectors) {
		ath11k_err(ab, "failed to get enough MSI vectors (%d), available vectors = %d",
			   msi_config->total_vectors, num_vectors);
		if (num_vectors >= 0)
			ret = -EINVAL;
		goto reset_msi_config;
	}

	msi_desc = irq_get_msi_desc(ar_pci->pdev->irq);
	if (!msi_desc) {
		ath11k_err(ab, "msi_desc is NULL!\n");
		ret = -EINVAL;
		goto free_msi_vector;
	}

	ar_pci->msi_ep_base_data = msi_desc->msg.data;

	ath11k_dbg(ab, ATH11K_DBG_PCI, "msi base data is %d\n", ar_pci->msi_ep_base_data);

	return 0;

free_msi_vector:
	pci_free_irq_vectors(ar_pci->pdev);
reset_msi_config:
	ar_pci->msi_config = NULL;
out:
	return ret;
}

static void ath11k_pci_disable_msi(struct ath11k_pci *ar_pci)
{
	pci_free_irq_vectors(ar_pci->pdev);
}

#endif

static int ath11k_pci_enable_msi(struct ath11k_pci *ar_pci)
{
    struct ath11k_base *ab = ar_pci->ab;
    struct ath11k_msi_config *msi_config;
    int ret;

    ret = ath11k_pci_get_msi_assignment(ar_pci);
    if (ret) {
        ath11k_err(ab, "failed to get MSI assignment, err = %d\n", ret);
        goto out;
    }

    msi_config = ar_pci->msi_config;
    if (!msi_config) {
        ath11k_err(ab, "msi_config is NULL!\n");
        ret = -EINVAL;
        goto out;
    }

    pci_read_config_dword(ar_pci->pdev, PCI_MSI_DATA, &ar_pci->msi_ep_base_data);
    ath11k_dbg(ab, ATH11K_DBG_PCI, "msi base data is %d\n", ar_pci->msi_ep_base_data);

    /* uefi doesn't support interrupt, allocate a dummy msi */
    ar_pci->dummy_msi.vaddr = pci_dma_alloc_coherent(ar_pci->pdev, sizeof(u32),
        &ar_pci->dummy_msi.paddr, &ar_pci->dummy_msi.paddr_mapping_addr);
out:
    return ret;
}

static void ath11k_pci_disable_msi(struct ath11k_pci *ar_pci)
{
    /* free dummy msi */
    if (ar_pci->dummy_msi.vaddr) {
        pci_dma_free_coherent(ar_pci->pdev, sizeof(u32),
            ar_pci->dummy_msi.vaddr, 
            ar_pci->dummy_msi.paddr, ar_pci->dummy_msi.paddr_mapping_addr);
        ar_pci->dummy_msi.vaddr = NULL;
    }
}

static int ath11k_pci_claim(struct ath11k_pci *ar_pci, pci_dev_handle pdev)
{
    struct ath11k_base *ab = ar_pci->ab;
    int ret = 0;

    ath11k_info(ab, "pci_assign_resource\n");
    ret = pci_assign_resource(pdev, PCI_BAR_NUM);
    if (ret) {
        ath11k_err(ab, "failed to assign pci resource, err = %d\n", ret);
        goto out;
    }

    ret = pci_enable_device(pdev);
    ath11k_info(ab, "pci_enable_device\n");
    if (ret) {
        ath11k_err(ab, "failed to enable pci device, err = %d\n", ret);
        goto out;
    }
    
    /* base address 0 in efi */
    ar_pci->mem_len = 0;
    ar_pci->mem = 0;

	/* request a reserved dma pool to avoid dma address < 8K being used */
	pci_request_dma_pool(pdev, "ath11k_pci_reserved_8k", SZ_8K,
		&ar_pci->reserved_dma_pool);

out:
    return ret;
}

static void ath11k_pci_free_region(struct ath11k_pci *ar_pci)
{
    pci_dev_handle pci_dev = ar_pci->pdev;

	pci_free_dma_pool(&ar_pci->reserved_dma_pool);

    if (pci_is_enabled(pci_dev))
        pci_disable_device(pci_dev);
}

#if 0
static int ath11k_pci_claim(struct ath11k_pci *ar_pci, struct pci_dev *pdev)
{
	u32 pci_dma_mask = PCI_DMA_MASK_32_BIT;
	struct ath11k_base *ab = ar_pci->ab;
	u16 device_id;
	int ret = 0;

	pci_read_config_word(pdev, PCI_DEVICE_ID, &device_id);
	if (device_id != ar_pci->dev_id)  {
		ath11k_err(ab, "pci device id mismatch, config ID: 0x%x, probe ID: 0x%x\n",
			   device_id, ar_pci->dev_id);
		ret = -EIO;
		goto out;
	}

	ret = pci_assign_resource(pdev, PCI_BAR_NUM);
	if (ret) {
		ath11k_err(ab, "failed to assign pci resource, err = %d\n", ret);
		goto out;
	}

	ret = pci_enable_device(pdev);
	if (ret) {
		ath11k_err(ab, "failed to enable pci device, err = %d\n", ret);
		goto out;
	}

	ret = pci_request_region(pdev, PCI_BAR_NUM, "ath11k_pci");
	if (ret) {
		ath11k_err(ab, "failed to request pci region, err = %d\n", ret);
		goto disable_device;
	}

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(pci_dma_mask));
	if (ret) {
		ath11k_err(ab, "failed to set pci dma mask (%d), err = %d\n",
			   ret, pci_dma_mask);
		goto release_region;
	}

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(pci_dma_mask));
	if (ret) {
		ath11k_err(ab, "failed to set pci consistent dma mask (%d), err = %d\n",
			   ret, pci_dma_mask);
		goto release_region;
	}

	pci_set_master(pdev);

	ar_pci->mem_len = pci_resource_len(pdev, PCI_BAR_NUM);
	ar_pci->mem = pci_iomap(pdev, PCI_BAR_NUM, 0);
	if (!ar_pci->mem) {
		ath11k_err(ab, "failed to map pci bar, bar = %d\n", PCI_BAR_NUM);
		ret = -EIO;
		goto clear_master;
	}

	ath11k_dbg(ab, ATH11K_DBG_BOOT, "boot pci_mem 0x%pK\n", ar_pci->mem);
	return 0;

clear_master:
	pci_clear_master(pdev);
release_region:
	pci_release_region(pdev, PCI_BAR_NUM);
disable_device:
	pci_disable_device(pdev);
out:
	return ret;
}

static void ath11k_pci_free_region(struct ath11k_pci *ar_pci)
{
	struct pci_dev *pci_dev = ar_pci->pdev;

	pci_iounmap(pci_dev, ar_pci->mem);
	ar_pci->mem = NULL;
	pci_clear_master(pci_dev);
	pci_release_region(pci_dev, PCI_BAR_NUM);
	if (pci_is_enabled(pci_dev))
		pci_disable_device(pci_dev);
}

#endif

static int ath11k_pci_power_up(struct ath11k_base *ab)
{
	struct ath11k_pci *ar_pci;
	int ret;

	ar_pci = ath11k_pci_priv(ab);
	ar_pci->register_window = 0;
	clear_bit(ATH11K_PCI_FLAG_INIT_DONE, &ar_pci->flags);

	ret = ath11k_pci_qca6x90_powerup(ar_pci);
	if (ret)
		ath11k_err(ab, "failed to power on mhi: %d\n", ret);

	return ret;
}

static void ath11k_pci_power_down(struct ath11k_base *ab)
{
	struct ath11k_pci *ar_pci;

	ar_pci = ath11k_pci_priv(ab);
	ath11k_pci_qca6x90_powerdown(ar_pci);
	clear_bit(ATH11K_PCI_FLAG_INIT_DONE, &ar_pci->flags);
}

#if 0
static void ath11k_pci_kill_tasklets(struct ath11k_base *ab)
{
	int i;

	for (i = 0; i < CE_COUNT; i++) {
		struct ath11k_ce_pipe *ce_pipe = &ab->ce.ce_pipe[i];

		if (ath11k_ce_get_attr_flags(ab, i) & CE_ATTR_DIS_INTR)
			continue;

		tasklet_kill(&ce_pipe->intr_tq);
	}
}
#endif

static void ath11k_pci_stop(struct ath11k_base *ab)
{
    ath11k_err(ab, "disable ce\n");
	ath11k_pci_ce_irqs_disable(ab);
	ath11k_pci_sync_ce_irqs(ab);
	//ath11k_pci_kill_tasklets(ab);  // no tasklets on uefi
	ath11k_ce_cleanup_pipes(ab);
	/* Shutdown other components as appropriate */
}

static int ath11k_pci_start(struct ath11k_base *ab)
{
    struct ath11k_pci *ab_pci = ath11k_pci_priv(ab);
	
	set_bit(ATH11K_PCI_FLAG_INIT_DONE, &ab_pci->flags);

	ath11k_err(ab, "enable ce\n");
	ath11k_pci_ce_irqs_enable(ab);
	ath11k_ce_rx_post_buf(ab);
	/* Bring up other components as appropriate */

	return 0;
}

static int ath11k_pci_map_service_to_pipe(struct ath11k_base *ab, u16 service_id,
					  u8 *ul_pipe, u8 *dl_pipe)
{
	const struct service_to_pipe *entry;
	bool ul_set = false, dl_set = false;
	u32 i;

	for (i = 0; i < ab->hw_params.svc_to_ce_map_len; i++) {
		entry = &ab->hw_params.svc_to_ce_map[i];

		if (__le32_to_cpu(entry->service_id) != service_id)
			continue;

		switch (__le32_to_cpu(entry->pipedir)) {
		case PIPEDIR_NONE:
			break;
		case PIPEDIR_IN:
			WARN_ON(dl_set);
			*dl_pipe = (u8)__le32_to_cpu(entry->pipenum);
			dl_set = true;
			break;
		case PIPEDIR_OUT:
			WARN_ON(ul_set);
			*ul_pipe = (u8)__le32_to_cpu(entry->pipenum);
			ul_set = true;
			break;
		case PIPEDIR_INOUT:
			WARN_ON(dl_set);
			WARN_ON(ul_set);
			*dl_pipe = (u8)__le32_to_cpu(entry->pipenum);
			*ul_pipe = (u8)__le32_to_cpu(entry->pipenum);
			dl_set = true;
			ul_set = true;
			break;
		}
	}

	if (WARN_ON(!ul_set || !dl_set))
		return -ENOENT;

	return 0;
}

static int ath11k_pci_dump(struct ath11k_base *ab)
{
    int ret;
    struct ath11k_pci *ar_pci;

    ar_pci = ath11k_pci_priv(ab);

    ret = ath11k_pci_target_dump(ar_pci);

    return ret;
}

/* Provide an interface to dump the SRAM*/
int ath11k_sram_dump(struct ath11k_base *ab)
{
	u32 i, start, end;
	u8 *buf, *ptr;
	int data;
	u64 data_len;
	const u16 *file = ATH11K_SRAM_DUP_FILE_NAME;

    start = ab->hw_params.fw_sram_start;
	end = ab->hw_params.fw_sram_end;
	data_len = (end - start + 1);

	buf = kmalloc(data_len, GFP_ATOMIC);
	if (!buf)
		return -ENOMEM;

    ptr = buf;
	
	for (i = start; i < end; i += 4) {
		data = ath11k_hif_read32(ab, i);
		memcpy(ptr, &data, 4);
		ptr += 4;
	}
	
	fdump(file, buf, &data_len);
	kfree(buf);

	return 0;
}

static const struct ath11k_hif_ops ath11k_pci_hif_ops = {
    .start = ath11k_pci_start,
    .stop = ath11k_pci_stop,
    .read32 = ath11k_pci_read32,
    .write32 = ath11k_pci_write32,
    .power_down = ath11k_pci_power_down,
    .power_up = ath11k_pci_power_up,
    .irq_enable = ath11k_pci_ext_irq_enable,
    .irq_disable = ath11k_pci_ext_irq_disable,
    .get_msi_address = ath11k_pci_get_msi_address,
    .get_user_msi_vector = ath11k_get_user_msi_assignment,
    .map_service_to_pipe = ath11k_pci_map_service_to_pipe,
    .dump = ath11k_pci_dump,
    .dump_sram = ath11k_sram_dump,
};

static int ath11k_pci_probe(pci_dev_handle pdev)
{
	struct ath11k_base *ab;
	struct ath11k_pci *ar_pci;
	u16 dev_id;
	u32 soc_hw_version;
	int ret = 0;

    pr_debug("ath11k_core_alloc\n");
	ab = ath11k_core_alloc(pdev, sizeof(*ar_pci));
	if (!ab) {
        ath11k_info(ab, "failed to allocate ath11k base\n");
		return -ENOMEM;
	}

    ab->pdev = pdev;
	ab->fw_mode = ATH11K_FIRMWARE_MODE_NORMAL;
	ar_pci = ath11k_pci_priv(ab);
	ar_pci->ab = ab;
    ar_pci->pdev = pdev;
	ab->hif.ops = &ath11k_pci_hif_ops;
	ab->m3_fw_support = true;
	ab->mhi_support = true;
	ab->use_register_windowing = true;

	pr_debug("get device id and hw_revision\n");
	dev_id = pci_get_hardware_dev_id(pdev);

	pci_set_drvdata(pdev, ab);
	spin_lock_init(&ar_pci->window_lock);

    /*
     * ath11k_pci_claim & ath11k_pci_enable_msi
	 */
	ret = ath11k_pci_claim(ar_pci, pdev);
	if (ret) {
		ath11k_err(ab, "failed to claim device: %d\n", ret);
		goto err_free_core;
	}

	ab->mem = ar_pci->mem;
	ab->mem_len = ar_pci->mem_len;

	switch (dev_id) {
#if SUPPORT_HARDWARE_HST6390
	case QCA6390_DEVICE_ID:
		ab->hw_rev = ATH11K_HW_QCA6390;
		break;
#endif
	case QCA6490_DEVICE_ID:
		soc_hw_version = ath11k_pci_read32(ab, TCSR_SOC_HW_VERSION);
		ath11k_dbg(ab, ATH11K_DBG_PCI, "tcsr_soc_hw_version 0x%x\n", soc_hw_version);
		if (FIELD_GET(TCSR_SOC_HW_VERSION_MAJOR_MASK, soc_hw_version) == 1) {
			ab->hw_rev = ATH11K_HW_QCA6490_HW11;
		}
		else {
			ab->hw_rev = ATH11K_HW_QCA6490_HW20;
			break;
		}
		
		ab->hw_rev = ATH11K_HW_QCA6490_HW11;
		break;
	default:
		ath11k_err(ab, "Unknown PCI device found: 0x%x\n", dev_id);
		return -ENODEV;
	}

	ret = ath11k_pci_enable_msi(ar_pci);
	if (ret) {
		ath11k_err(ab, "failed to enable  msi: %d\n", ret);
		goto err_pci_free_region;
	}

	ret = ath11k_core_pre_init(ab);
	if (ret) {
		goto err_pci_disable_msi;
	}
	
	ret = ath11k_pci_register_mhi(ar_pci);
	if (ret) {
		ath11k_err(ab, "failed to register  mhi: %d\n", ret);
		goto err_pci_disable_msi;
	}

    /* TODOTODO: Move to a correct place */
	init_work(&ar_pci->rddm_worker, ath11k_mhi_pm_rddm_worker, ar_pci);

	ret = ath11k_core_pre_init(ab);
	if (ret)
		goto err_pci_unregister_mhi;

	ret = ath11k_hal_srng_init(ab);
	if (ret)
		goto err_pci_unregister_mhi;

	ret = ath11k_ce_alloc_pipes(ab);
	if (ret) {
		ath11k_err(ab, "failed to allocate ce pipes: %d\n", ret);
		goto err_hal_srng_deinit;
	}

	ath11k_pci_init_qmi_ce_config(ab);

	ret = ath11k_pci_config_irq(ab);
	if (ret) {
		ath11k_err(ab, "failed to config irq: %d\n", ret);
		goto err_ce_free;
	}

	ret = ath11k_core_init(ab);
	if (ret) {
		ath11k_err(ab, "failed to init core: %d\n", ret);
		goto err_free_irq;
	}
	return 0;

err_free_irq:
	ath11k_pci_free_irq(ab);

err_ce_free:
	ath11k_ce_free_pipes(ab);

err_hal_srng_deinit:
	ath11k_hal_srng_deinit(ab);

err_pci_unregister_mhi:
	ath11k_pci_unregister_mhi(ar_pci);

err_pci_disable_msi:
	ath11k_pci_disable_msi(ar_pci);

err_pci_free_region:
	ath11k_pci_free_region(ar_pci);

err_free_core:
	ath11k_core_free(ab);

	return ret;
}

static void ath11k_pci_remove(pci_dev_handle pdev)
{
    struct ath11k_base *ab = pci_get_drvdata(pdev);
	struct ath11k_pci *ar_pci = ath11k_pci_priv(ab);

	set_bit(ATH11K_FLAG_UNREGISTERING, &ab->dev_flags);
	cancel_work_sync(&ab->update_11d_work);
	ath11k_core_deinit(ab);

	ath11k_pci_unregister_mhi(ar_pci);
	ath11k_pci_free_irq(ab);
	ath11k_pci_disable_msi(ar_pci);
	ath11k_pci_free_region(ar_pci);

	ath11k_hal_srng_deinit(ab);
	ath11k_ce_free_pipes(ab);

#if ATH11K_SUPPORT_MONITOR
	//del_timer_sync(&ab->mon_reap_timer);
	cancel_delayed_work_sync(&ab->mon_reap_work);
#endif
	ath11k_core_free(ab);
}

struct pci_driver ath11k_pci_driver = {
    .name = "ath11k_pci",
	.id_table = ath11k_pci_id_table,
    .probe = ath11k_pci_probe,
    .remove = ath11k_pci_remove,
};

