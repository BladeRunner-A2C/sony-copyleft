// SPDX-License-Identifier: BSD-3-Clause-Clear
/**
 * Copyright (c) 2010 The Linux Foundation. All rights reserved.
 */

#include <mhi/mhi.h>
#include <qdf/file.h>
#include "core.h"
#include "coredump.h"
#include "pci.h"
#include "debug.h"

static int ath11k_coredump_remote_dump(struct ath11k_base *ab)
{
	struct fw_remote_mem *fw_mem = ab->remote_mem;
    struct segment segments[ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01 + 1] = { 0 };
    u8 count = 0;
	u8 i;

	for (i = 0; i < ATH11K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01; i++) {
		if (fw_mem[i].vaddr && fw_mem[i].size) {
            segments[count].size = fw_mem[i].size;
            segments[count].buffer = fw_mem[i].vaddr;
			ath11k_info(ab, "remote memory: 0x%p, size: 0x%lx\n",
                segments[count].buffer, segments[count].size);
            count++;
		}
	}

    fdump_segments(L"remote.bin", segments);

	return 0;
}

static int ath11k_coredump_fw_rddm_dump(struct mhi_controller *mhi_cntrl)
{
	struct image_info *img = mhi_cntrl->rddm_image;
    struct ath11k_pci *ar_pci = mhi_cntrl->priv_data;
    struct segment segments[16] = { 0 };
    u32 seg;

    ath11k_info(ar_pci->ab, "entries=%d\n", img->entries);

    if (img->entries > (ARRAY_LENGTH(segments) - 1)) {
        ath11k_err(ar_pci->ab,
            "ERROR: no enough segments resvered\n");
        return -ENOSPC;
    }

	for (seg = 0; seg < img->entries; seg++) {
        segments[seg].size = img->mhi_buf[seg].len;
        segments[seg].buffer = img->mhi_buf[seg].aligned_buf;
		ath11k_info(ar_pci->ab,
            "rddm memory: 0x%p, size: 0x%x\n",
            segments[seg].buffer, segments[seg].size);
	}

    fdump_segments(L"fwsram.bin", segments);

	return 0;
}

static int ath11k_coredump_fw_paging_dump(struct mhi_controller *mhi_cntrl)
{
	struct image_info *img = mhi_cntrl->fbc_image;
    struct ath11k_pci *ar_pci = mhi_cntrl->priv_data;
    struct segment segments[16] = { 0 };
	u32 seg;

	ath11k_info(ar_pci->ab, "entries=%d\n", img->entries);

    if (img->entries > (ARRAY_LENGTH(segments) - 1)) {
        ath11k_err(ar_pci->ab,
            "ERROR: no enough segments resvered\n");
        return -ENOSPC;
    }

    for (seg = 0; seg < img->entries; seg++) {
        segments[seg].size = img->mhi_buf[seg].len;
        segments[seg].buffer = img->mhi_buf[seg].aligned_buf;
        ath11k_info(ar_pci->ab,
            "firmware paging memory: 0x%p, size: 0x%x\n",
            segments[seg].buffer, segments[seg].size);
    }

    fdump_segments(L"paging.bin", segments);

	return 0;
}

void ath11k_mhi_pm_rddm_worker(void *context)
{
	struct ath11k_pci *ar_pci = (struct ath11k_pci *)context;

	mhi_download_rddm_img(ar_pci->mhi_ctrl, false);

	ath11k_coredump_fw_rddm_dump(ar_pci->mhi_ctrl);
	ath11k_coredump_fw_paging_dump(ar_pci->mhi_ctrl);
	ath11k_coredump_remote_dump(ar_pci->ab);
}

