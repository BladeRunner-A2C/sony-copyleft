/* SPDX-License-Identifier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2020-2021 The Linux Foundation. All rights reserved.
 * Copyright (c) 2021-2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */
#ifndef _ATH12K_MHI_H
#define _ATH12K_MHI_H

#include "pci.h"

#define ATH12K_PCI_FW_FILE_NAME		L"amss.bin"

#ifdef qcn9244
#define ATH12K_PCI_FW_RDDM_SZ			0x600000
#else
#define ATH12K_PCI_FW_RDDM_SZ			0x780000
#endif

enum ath12k_mhi_state {
	ATH12K_MHI_INIT,
	ATH12K_MHI_DEINIT,
	ATH12K_MHI_POWER_ON,
	ATH12K_MHI_POWER_OFF,
	ATH12K_MHI_FORCE_POWER_OFF,
	ATH12K_MHI_SUSPEND,
	ATH12K_MHI_RESUME,
	ATH12K_MHI_TRIGGER_RDDM,
	ATH12K_MHI_RDDM,
	ATH12K_MHI_RDDM_DONE,
};

extern struct mhi_controller_config ath12k_mhi_config_qcn9274;
extern struct mhi_controller_config ath12k_mhi_config_wcn7850;

int ath12k_mhi_start(struct ath12k_pci *ar_pci);
void ath12k_mhi_stop(struct ath12k_pci *ar_pci);
int ath12k_mhi_register(struct ath12k_pci *ar_pci);
void ath12k_mhi_unregister(struct ath12k_pci *ar_pci);
void ath12k_mhi_set_mhictrl_reset(struct ath12k_base *ab);
void ath12k_mhi_clear_vector(struct ath12k_base *ab);

void ath12k_mhi_suspend(struct ath12k_pci *ar_pci);
void ath12k_mhi_resume(struct ath12k_pci *ar_pci);
int ath12k_mhi_force_rddm(struct ath12k_pci *ar_pci);

#endif
