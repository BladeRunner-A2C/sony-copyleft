/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

// SPDX-License-Identifier: BSD-3-Clause-Clear
/* Copyright (c) 2019 The Linux Foundation. All rights reserved. */

#include <mhi/mhi.h>
#include <qdf/pci.h>
#include <qdf/firmware.h>
#include "debug.h"

#define MHI_TIMEOUT_DEFAULT_MS	9000

static struct mhi_channel_config ath11k_mhi_channels[] = {
	{
		.num = 0,
		.name = "LOOPBACK",
		.num_elements = 32,
		.event_ring = 0,
		.dir = DMA_TO_DEVICE,
		.ee_mask = 0x4,
		.pollcfg = 0,
		.doorbell = MHI_DB_BRST_DISABLE,
		.lpm_notify = false,
		.offload_channel = false,
		.doorbell_mode_switch = false,
		.auto_queue = false,
		.auto_start = false,
	},
	{
		.num = 1,
		.name = "LOOPBACK",
		.num_elements = 32,
		.event_ring = 0,
		.dir = DMA_FROM_DEVICE,
		.ee_mask = 0x4,
		.pollcfg = 0,
		.doorbell = MHI_DB_BRST_DISABLE,
		.lpm_notify = false,
		.offload_channel = false,
		.doorbell_mode_switch = false,
		.auto_queue = false,
		.auto_start = false,
	},
    {
        .num = 4,
        .name = "DIAG",
        .num_elements = 64,
        .event_ring = 1,
        .dir = DMA_TO_DEVICE,
        .ee_mask = 0x14,
        .pollcfg = 0,
        .doorbell = MHI_DB_BRST_DISABLE,
        .lpm_notify = false,
        .offload_channel = false,
        .doorbell_mode_switch = false,
        .auto_queue = false,
        .auto_start = true,
    },
    {
        .num = 5,
        .name = "DIAG",
        .num_elements = 64,
        .event_ring = 1,
        .dir = DMA_FROM_DEVICE,
        .ee_mask = 0x14,
        .pollcfg = 0,
        .doorbell = MHI_DB_BRST_DISABLE,
        .lpm_notify = false,
        .offload_channel = false,
        .doorbell_mode_switch = false,
        .auto_queue = true,
        .auto_start = true,
    },
	{
		.num = 20,
		.name = "IPCR",
		.num_elements = 64,
		.event_ring = 1,
		.dir = DMA_TO_DEVICE,
		.ee_mask = 0x4,
		.pollcfg = 0,
		.doorbell = MHI_DB_BRST_DISABLE,
		.lpm_notify = false,
		.offload_channel = false,
		.doorbell_mode_switch = false,
		.auto_queue = false,
		.auto_start = true,
	},
	{
		.num = 21,
		.name = "IPCR",
		.num_elements = 64,
		.event_ring = 1,
		.dir = DMA_FROM_DEVICE,
		.ee_mask = 0x4,
		.pollcfg = 0,
		.doorbell = MHI_DB_BRST_DISABLE,
		.lpm_notify = false,
		.offload_channel = false,
		.doorbell_mode_switch = false,
		.auto_queue = true,
		.auto_start = true,
	},
};

static struct mhi_event_config ath11k_mhi_events[] = {
	{
		.num_elements = 32,
		.irq_moderation_ms = 0,
		.irq = 1,
		.mode = MHI_DB_BRST_DISABLE,
		.data_type = MHI_ER_CTRL,
		.hardware_event = false,
		.client_managed = false,
		.offload_channel = false,
	},
	{
		.num_elements = 256,
		.irq_moderation_ms = 1,
		.irq = 2,
		.mode = MHI_DB_BRST_DISABLE,
		.priority = 1,
		.hardware_event = false,
		.client_managed = false,
		.offload_channel = false,
	},
};

static struct mhi_controller_config ath11k_mhi_config = {
	.max_channels = 128,
	.timeout_ms = 2000,
	.use_bounce_buf = false,
	.buf_len = 4096,
	.num_channels = ARRAY_SIZE(ath11k_mhi_channels),
	.ch_cfg = ath11k_mhi_channels,
	.num_events = ARRAY_SIZE(ath11k_mhi_events),
	.event_cfg = ath11k_mhi_events,
};

static int ath11k_pci_get_mhi_msi(struct ath11k_pci *ar_pci)
{
	u32 user_base_data, base_vector;
	int ret, num_vectors, i;
	int *irq = NULL;

	ret = ath11k_pci_get_user_msi_assignment(ar_pci,
						 "MHI", &num_vectors,
						 &user_base_data, &base_vector);
	if (ret)
		return ret;

    ath11k_info(ar_pci->ab, "Number of assigned MSI for MHI is %d, base vector is %d\n",
		   num_vectors, base_vector);

	irq = kcalloc(num_vectors, sizeof(int), GFP_KERNEL);
	if (!irq)
		return -ENOMEM;

	for (i = 0; i < num_vectors; i++)
		irq[i] = ath11k_pci_get_msi_irq(ar_pci->pdev,
						base_vector + i);

	ar_pci->mhi_ctrl->irq = irq;
	ar_pci->mhi_ctrl->nr_irqs = num_vectors;

	return 0;
}

static int ath11k_mhi_link_status(struct mhi_controller *mhi_ctrl)
{
	return 0;
}

static void ath11k_mhi_notify_status(struct mhi_controller *mhi_ctrl,
				     enum mhi_callback reason)
{
	struct ath11k_pci *ar_pci = mhi_ctrl->priv_data;
	struct ath11k_base *ab = ar_pci->ab;
	
	mhi_dbg("reason %u\n", reason);

    if (reason == MHI_CB_EE_RDDM) {
        ath11k_err(ab, "schedule to do RDDM\n");
		set_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags);
        schedule_work(&ar_pci->rddm_worker);
    }
}

static int ath11k_mhi_pm_runtime_get(struct mhi_controller *mhi_ctrl)
{
	return 0;
}

static void ath11k_mhi_pm_runtime_put_noidle(struct mhi_controller *mhi_ctrl)
{
}

extern int ipcr_init(void *cntrl_dev);
extern void ipcr_fini(void);

int ath11k_pci_register_mhi(struct ath11k_pci *ar_pci)
{
	//struct pci_dev *pci_dev = ar_pci->pdev;
	struct ath11k_base *ab = ar_pci->ab;
	struct mhi_controller *mhi_ctrl = NULL;
	int ret;

	mhi_ctrl = kzalloc(sizeof(*mhi_ctrl), GFP_KERNEL);
	if (!mhi_ctrl) {
		ath11k_err(ab, "failed to alloc mhi_ctrl\n");
		return -ENOMEM;
	}
	
	ar_pci->mhi_ctrl = mhi_ctrl;
    mhi_ctrl->priv_data = ar_pci;
    mhi_ctrl->cntrl_dev = ar_pci->pdev;
	mhi_ctrl->fw_image = ATH11K_PCI_FW_FILE_NAME;
	mhi_ctrl->regs = ar_pci->mem;
    mhi_ctrl->rddm_size = ab->hw_params.rddm_size;
	ret = ath11k_pci_get_mhi_msi(ar_pci);
	if (ret) {
        ath11k_err(ab, "failed to get msi for mhi\n");
		return ret;
	}

	mhi_ctrl->iova_start = 0x0;
	mhi_ctrl->iova_stop = 0xffffffff;

	mhi_ctrl->link_status = ath11k_mhi_link_status;
	mhi_ctrl->status_cb = ath11k_mhi_notify_status;
	mhi_ctrl->runtime_get = ath11k_mhi_pm_runtime_get;
	mhi_ctrl->runtime_put = ath11k_mhi_pm_runtime_put_noidle;

	mhi_ctrl->sbl_size = SZ_512K;
	mhi_ctrl->seg_len = SZ_512K;
	mhi_ctrl->fbc_download = true;

	ret = mhi_register_controller(mhi_ctrl, &ath11k_mhi_config);
	if (ret) {
        ath11k_err(ab, "failed to register to mhi bus, err = %d\n", ret);
		kfree(mhi_ctrl);
		
		return ret;
	}

    ipcr_init(mhi_ctrl->cntrl_dev);

	return 0;
}

void ath11k_pci_unregister_mhi(struct ath11k_pci *ar_pci)
{
	struct mhi_controller *mhi_ctrl = ar_pci->mhi_ctrl;

    ipcr_fini();
	
	mhi_unregister_controller(mhi_ctrl);
	kfree(mhi_ctrl->irq);
}

static char *ath11k_mhi_state_to_str(enum ath11k_mhi_state mhi_state)
{
	switch (mhi_state) {
	case ATH11K_MHI_INIT:
		return "INIT";
	case ATH11K_MHI_DEINIT:
		return "DEINIT";
	case ATH11K_MHI_POWER_ON:
		return "POWER_ON";
	case ATH11K_MHI_POWER_OFF:
		return "POWER_OFF";
	case ATH11K_MHI_FORCE_POWER_OFF:
		return "FORCE_POWER_OFF";
	case ATH11K_MHI_SUSPEND:
		return "SUSPEND";
	case ATH11K_MHI_RESUME:
		return "RESUME";
	case ATH11K_MHI_TRIGGER_RDDM:
		return "TRIGGER_RDDM";
	case ATH11K_MHI_RDDM_DONE:
		return "RDDM_DONE";
	default:
		return "UNKNOWN";
	}
};

static void ath11k_pci_set_mhi_state_bit(struct ath11k_pci *ar_pci,
					 enum ath11k_mhi_state mhi_state)
{
	struct ath11k_base *ab = ar_pci->ab;

	switch (mhi_state) {
	case ATH11K_MHI_INIT:
		set_bit(ATH11K_MHI_INIT, &ar_pci->mhi_state);
		break;
	case ATH11K_MHI_DEINIT:
		clear_bit(ATH11K_MHI_INIT, &ar_pci->mhi_state);
		break;
	case ATH11K_MHI_POWER_ON:
		set_bit(ATH11K_MHI_POWER_ON, &ar_pci->mhi_state);
		break;
	case ATH11K_MHI_POWER_OFF:
	case ATH11K_MHI_FORCE_POWER_OFF:
		clear_bit(ATH11K_MHI_POWER_ON, &ar_pci->mhi_state);
		clear_bit(ATH11K_MHI_TRIGGER_RDDM, &ar_pci->mhi_state);
		clear_bit(ATH11K_MHI_RDDM_DONE, &ar_pci->mhi_state);
		break;
	case ATH11K_MHI_SUSPEND:
		set_bit(ATH11K_MHI_SUSPEND, &ar_pci->mhi_state);
		break;
	case ATH11K_MHI_RESUME:
		clear_bit(ATH11K_MHI_SUSPEND, &ar_pci->mhi_state);
		break;
	case ATH11K_MHI_TRIGGER_RDDM:
		set_bit(ATH11K_MHI_TRIGGER_RDDM, &ar_pci->mhi_state);
		break;
	case ATH11K_MHI_RDDM_DONE:
		set_bit(ATH11K_MHI_RDDM_DONE, &ar_pci->mhi_state);
		break;
	default:
		ath11k_err(ab, "unhandled mhi state (%d)\n", mhi_state);
		break;
	}
}

static int ath11k_pci_check_mhi_state_bit(struct ath11k_pci *ar_pci,
					  enum ath11k_mhi_state mhi_state)
{
	struct ath11k_base *ab = ar_pci->ab;

	switch (mhi_state) {
	case ATH11K_MHI_INIT:
		if (!test_bit(ATH11K_MHI_INIT, &ar_pci->mhi_state))
			return 0;
		break;
	case ATH11K_MHI_DEINIT:
	case ATH11K_MHI_POWER_ON:
		if (test_bit(ATH11K_MHI_INIT, &ar_pci->mhi_state) &&
		    !test_bit(ATH11K_MHI_POWER_ON, &ar_pci->mhi_state))
			return 0;
		break;
	case ATH11K_MHI_FORCE_POWER_OFF:
		if (test_bit(ATH11K_MHI_POWER_ON, &ar_pci->mhi_state))
			return 0;
		break;
	case ATH11K_MHI_POWER_OFF:
	case ATH11K_MHI_SUSPEND:
		if (test_bit(ATH11K_MHI_POWER_ON, &ar_pci->mhi_state) &&
		    !test_bit(ATH11K_MHI_SUSPEND, &ar_pci->mhi_state))
			return 0;
		break;
	case ATH11K_MHI_RESUME:
		if (test_bit(ATH11K_MHI_SUSPEND, &ar_pci->mhi_state))
			return 0;
		break;
	case ATH11K_MHI_TRIGGER_RDDM:
		if (test_bit(ATH11K_MHI_POWER_ON, &ar_pci->mhi_state) &&
		    !test_bit(ATH11K_MHI_TRIGGER_RDDM, &ar_pci->mhi_state))
			return 0;
		break;
	case ATH11K_MHI_RDDM_DONE:
		return 0;
	default:
		ath11k_err(ab, "unhandled mhi state: %a(%d)\n",
			   ath11k_mhi_state_to_str(mhi_state), mhi_state);
		break;
	}
	
	ath11k_err(ab, "failed to set mhi state %a(%d) in current mhi state (0x%lx)\n",
		   ath11k_mhi_state_to_str(mhi_state), mhi_state,
		   ar_pci->mhi_state);

	return -EINVAL;
}

int ath11k_pci_set_mhi_state(struct ath11k_pci *ar_pci,
			     enum ath11k_mhi_state mhi_state)
{
	struct ath11k_base *ab = ar_pci->ab;
	int ret;

	ret = ath11k_pci_check_mhi_state_bit(ar_pci, mhi_state);
	if (ret)
		goto out;

    ath11k_info(ab, "setting mhi state: %a(%d)\n",
		   ath11k_mhi_state_to_str(mhi_state), mhi_state);

	switch (mhi_state) {
	case ATH11K_MHI_INIT:
		ret = mhi_prepare_for_power_up(ar_pci->mhi_ctrl);
		break;
	case ATH11K_MHI_DEINIT:
		mhi_unprepare_after_power_down(ar_pci->mhi_ctrl);
		ret = 0;
		break;
	case ATH11K_MHI_POWER_ON:
        ret = mhi_sync_power_up(ar_pci->mhi_ctrl);
		if (ret) {
			ath11k_err(ab, "failed to power up ret = 0x%x\n", ret);
			mhi_power_down(ar_pci->mhi_ctrl, false);
		}
		break;
	case ATH11K_MHI_POWER_OFF:
		mhi_power_down(ar_pci->mhi_ctrl, true);
		ret = 0;
		break;
	case ATH11K_MHI_FORCE_POWER_OFF:
		mhi_power_down(ar_pci->mhi_ctrl, false);
		ret = 0;
		break;
	case ATH11K_MHI_SUSPEND:
		break;
	case ATH11K_MHI_RESUME:
		break;
	case ATH11K_MHI_TRIGGER_RDDM:
		ret = mhi_force_rddm_mode(ar_pci->mhi_ctrl);
		break;
	case ATH11K_MHI_RDDM_DONE:
		break;
	default:
		ath11k_err(ab, "unhandled MHI state (%d)\n", mhi_state);
		ret = -EINVAL;
	}

	if (ret)
		goto out;

	ath11k_pci_set_mhi_state_bit(ar_pci, mhi_state);

	return 0;

out:
    ath11k_err(ab, "failed to set mhi state: %a(%d)\n",
		   ath11k_mhi_state_to_str(mhi_state), mhi_state);
	return ret;
}

int ath11k_pci_start_mhi(struct ath11k_pci *ar_pci)
{
	int ret;
	struct ath11k_base *ab = ar_pci->ab;

	ar_pci->mhi_ctrl->timeout_ms = MHI_TIMEOUT_DEFAULT_MS;

	ret = ath11k_pci_set_mhi_state(ar_pci, ATH11K_MHI_INIT);
	if (ret)
		goto out;

	ret = ath11k_pci_set_mhi_state(ar_pci, ATH11K_MHI_POWER_ON);
	if (ret) {
#if SUPPORT_SECURITY_BOOT
		ath11k_err(ab, "power on fail and try again.\n");

		/* clean up the fw cache */
    	flush_firmware_cache();
		
		/* Fw load fail, try to power on again.*/
		ret = ath11k_pci_set_mhi_state(ar_pci, ATH11K_MHI_POWER_ON);
#else
		ath11k_err(ab, "power on fail ret = 0x%x.\n", ret);
		goto out;
#endif
	}

	return 0;

out:
	return ret;
}

void ath11k_pci_stop_mhi(struct ath11k_pci *ar_pci)
{
	ath11k_pci_set_mhi_state(ar_pci, ATH11K_MHI_POWER_OFF);
	ath11k_pci_set_mhi_state(ar_pci, ATH11K_MHI_DEINIT);
}

int ath11k_pci_rddm_mhi(struct ath11k_pci *ar_pci)
{
    return ath11k_pci_set_mhi_state(ar_pci, ATH11K_MHI_TRIGGER_RDDM);
}

