/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
// SPDX-License-Identifier: BSD-3-Clause-Clear
/**
 * Copyright (c) 2021 The Linux Foundation. All rights reserved.
 */

#include "mhi.h"
#include <mhi/mhi.h>
#include <qdf/file.h>
#include "core.h"
#include "coredump.h"
#include "pci.h"
#include "debug.h"

static size_t ath12k_get_paging_buf_len(struct mhi_controller *mhi_cntrl)
{
	struct image_info *img = mhi_cntrl->fbc_image;
	u32 i = 0;
	size_t len = 0;
	u32 entries = img->entries;
	size_t seg_size = mhi_cntrl->seg_len;

	for (i = 0; i < entries; ++i) {
		size_t vec_size = seg_size;

		if (i == entries - 1)
			vec_size = sizeof(struct ath12k_vec_entry) * i;
		len += vec_size;
	}

	return len;
}

int ath12k_coredump_fw_paging_dump(struct ath12k_pci *ab_pci, struct mhi_controller *mhi_cntrl)
{
	struct image_info *img = mhi_cntrl->fbc_image;
	struct ath12k_mhi_fw_crash_data *crash_data = &ab_pci->mhi_fw_crash_data;
	u8 *buf = NULL;
	unsigned int size = 0;
	u32 seg = 0;
	u32 offset = 0;
	u32 fw_vec_entry_num = img->entries - 1;
	size_t paging_dump_buf_len = ath12k_get_paging_buf_len(mhi_cntrl);

	crash_data->paging_dump_buf_len = paging_dump_buf_len;
	ath12k_info(ab_pci->ab, "FW paging dump buffer len=\n", paging_dump_buf_len);
	
	crash_data->paging_dump_buf = vzalloc(paging_dump_buf_len);
	if (!crash_data->paging_dump_buf)
		return -ENOMEM;

	for (seg = 0; seg < fw_vec_entry_num; seg++) {
		buf = img->mhi_buf[seg].aligned_buf;
		size = img->mhi_buf[seg].len;
		memcpy(crash_data->paging_dump_buf + offset, buf, size);
		offset += size;
	}

	buf = crash_data->paging_dump_buf + offset;
	size = img->mhi_buf[img->entries - 1].len;
	ath12k_info(ab_pci->ab, "to write last block: mem: 0x%p, size: 0x%x\n",
		    buf, size);
	memcpy(buf, img->mhi_buf[img->entries - 1].aligned_buf, size);

	fdump(L"paging.bin", crash_data->paging_dump_buf, &crash_data->paging_dump_buf_len);

	return 0;
}

int ath12k_coredump_fw_rddm_dump(struct ath12k_pci *ab_pci, struct mhi_controller *mhi_cntrl)
{
	struct ath12k_mhi_fw_crash_data *crash_data = &ab_pci->mhi_fw_crash_data;
	struct image_info *img = mhi_cntrl->rddm_image;
	u8 *buf = NULL;
	unsigned int size = 0;
	u32 seg = 0;
	u32 offset = 0;
	u32 rddm_vec_entry_num;
	u32 entries = mhi_cntrl->rddm_image->entries;
	
	rddm_vec_entry_num = DIV_ROUND_UP(ATH12K_PCI_FW_RDDM_SZ,
					  mhi_cntrl->seg_len);
	crash_data->ramdump_buf_len = (entries - 1) * mhi_cntrl->seg_len +
				      rddm_vec_entry_num * sizeof(struct ath12k_vec_entry);

	ath12k_info(ab_pci->ab, "rddm_vec_entry_num=%d entries=%d\n",
		    rddm_vec_entry_num, img->entries);
	
	crash_data->ramdump_buf = vzalloc(crash_data->ramdump_buf_len);
	if (!crash_data->ramdump_buf)
		return -ENOMEM;

	for (seg = 0; seg < rddm_vec_entry_num; seg++) {
		buf = img->mhi_buf[seg].aligned_buf;
		size = img->mhi_buf[seg].len;
		ath12k_info(ab_pci->ab,
			    "write rddm memory: mem: 0x%p, size: 0x%x\n",
			    buf, size);
		memcpy(crash_data->ramdump_buf + offset, buf, size);
		offset += size;
	}
		
	buf = crash_data->ramdump_buf + offset;
	size = img->mhi_buf[img->entries - 1].len;
	ath12k_info(ab_pci->ab,
		    "to write vector table block: mem: 0x%p, size: 0x%x\n",
		    buf, size);
	memcpy(buf, img->mhi_buf[img->entries - 1].aligned_buf, size);
	
	fdump(L"fwsramfull.bin", crash_data->ramdump_buf, &crash_data->ramdump_buf_len);
	
	return 0;
}

static void ath12k_coredump_buf_release(struct ath12k_pci *ab_pci)
{
	struct fw_remote_crash_data *remote = &ab_pci->ab->remote_crash_data;
	struct ath12k_mhi_fw_crash_data *mhi = &ab_pci->mhi_fw_crash_data;
	struct register_crash_data *reg = &ab_pci->reg_data;

	if (remote->remote_buf) {
		vfree(remote->remote_buf);
		remote->remote_buf = NULL;
	}

	if (mhi->ramdump_buf) {
		vfree(mhi->ramdump_buf);
		mhi->ramdump_buf = NULL;
	}

	if (mhi->paging_dump_buf) {
		vfree(mhi->paging_dump_buf);
		mhi->paging_dump_buf = NULL;
	}

	if (reg->reg_buf) {
		vfree(reg->reg_buf);
		reg->reg_buf = NULL;
	}

	if (reg->reg_rddm_buf) {
		vfree(reg->reg_rddm_buf);
		reg->reg_rddm_buf = NULL;
	}
}

static size_t ath12k_qmi_get_remote_buf_len(struct fw_remote_mem *fw_mem)
{
	unsigned int i;
	size_t len = 0;

	for (i = 0; i < ATH12K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01; i++) {
		if (fw_mem[i].vaddr && fw_mem[i].size)
			len += fw_mem[i].size;
	}
	return len;
}

int ath12k_qmi_remote_dump(struct ath12k_base *ab)
{
	struct fw_remote_crash_data *crash_data = &ab->remote_crash_data;
	struct fw_remote_mem *fw_mem = ab->remote_mem;
	u8 i;
	size_t offset = 0;

	crash_data->remote_buf_len = ath12k_qmi_get_remote_buf_len(fw_mem);
	ath12k_info(ab, "%s remote buffer len=%lu\n", __func__, crash_data->remote_buf_len);
	crash_data->remote_buf = vzalloc(crash_data->remote_buf_len);
	if (!crash_data->remote_buf)
		return -ENOMEM;

	for (i = 0; i < ATH12K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01; i++) {
		if (fw_mem[i].vaddr && fw_mem[i].size) {
			ath12k_info(ab, "remote mem: 0x%p, size: 0x%lx\n", fw_mem[i].vaddr,
				    fw_mem[i].size);
			memcpy(crash_data->remote_buf + offset, fw_mem[i].vaddr, fw_mem[i].size);
			offset += fw_mem[i].size;
		}
	}

	fdump(L"remote.bin", crash_data->remote_buf, &crash_data->remote_buf_len);
	return 0;
}

static struct cnss_pci_reg register_rddm_fail_debug[] = {
	{"PCIE_BHI_VERSION_LOWER", HWIO_PCIE_PCIE_BHI_VERSION_LOWER_ADDR, 0},
	{"PCIE_BHI_VERSION_UPPER", HWIO_PCIE_PCIE_BHI_VERSION_UPPER_ADDR, 0},
	{"PCIE_BHI_IMGADDR_LOWER", HWIO_PCIE_PCIE_BHI_IMGADDR_LOWER_ADDR, 0},
	{"PCIE_BHI_IMGADDR_UPPER", HWIO_PCIE_PCIE_BHI_IMGADDR_UPPER_ADDR, 0},
	{"PCIE_BHI_IMGSIZE", HWIO_PCIE_PCIE_BHI_IMGSIZE_ADDR, 0},
	{"PCIE_BHI_IMGTXDB", HWIO_PCIE_PCIE_BHI_IMGTXDB_ADDR, 0},
	{"PCIE_BHI_INTVEC", HWIO_PCIE_PCIE_BHI_INTVEC_ADDR, 0},
	{"PCIE_BHI_EXECENV", HWIO_PCIE_PCIE_BHI_EXECENV_ADDR, 0},
	{"PCIE_BHI_STATUS", HWIO_PCIE_PCIE_BHI_STATUS_ADDR, 0},
	{"PCIE_BHI_ERRCODE", HWIO_PCIE_PCIE_BHI_ERRCODE_ADDR, 0},
	{"PCIE_BHI_ERRDBG1", HWIO_PCIE_PCIE_BHI_ERRDBG1_ADDR, 0},
	{"PCIE_BHI_ERRDBG2", HWIO_PCIE_PCIE_BHI_ERRDBG2_ADDR, 0},
	{"PCIE_BHI_ERRDBG3", HWIO_PCIE_PCIE_BHI_ERRDBG3_ADDR, 0},
	{"PCIE_BHI_SERIALNUM", HWIO_PCIE_PCIE_BHI_SERIALNUM_ADDR, 0},
	{"PCIE_BHI_SBLANTIROLLVER", HWIO_PCIE_PCIE_BHI_SBLANTIROLLVER_ADDR, 0},
	{"PCIE_BHI_NUMSEG", HWIO_PCIE_PCIE_BHI_NUMSEG_ADDR, 0},
	{"PCIE_BHI_MSMHWID_0", HWIO_PCIE_PCIE_BHI_MSMHWID_0_ADDR, 0},
	{"PCIE_BHI_MSMHWID_1", HWIO_PCIE_PCIE_BHI_MSMHWID_1_ADDR, 0},
	{"PCIE_BHI_MSMHWID_2", HWIO_PCIE_PCIE_BHI_MSMHWID_2_ADDR, 0},
	{"PCIE_BHI_MSMHWID_3", HWIO_PCIE_PCIE_BHI_MSMHWID_3_ADDR, 0},
	{"PCIE_BHI_MSMHWID_4", HWIO_PCIE_PCIE_BHI_MSMHWID_4_ADDR, 0},
	{"PCIE_BHI_MSMHWID_5", HWIO_PCIE_PCIE_BHI_MSMHWID_5_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_0", HWIO_PCIE_PCIE_BHI_OEMPKHASH_0_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_1", HWIO_PCIE_PCIE_BHI_OEMPKHASH_1_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_2", HWIO_PCIE_PCIE_BHI_OEMPKHASH_2_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_3", HWIO_PCIE_PCIE_BHI_OEMPKHASH_3_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_4", HWIO_PCIE_PCIE_BHI_OEMPKHASH_4_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_5", HWIO_PCIE_PCIE_BHI_OEMPKHASH_5_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_6", HWIO_PCIE_PCIE_BHI_OEMPKHASH_6_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_7", HWIO_PCIE_PCIE_BHI_OEMPKHASH_7_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_8", HWIO_PCIE_PCIE_BHI_OEMPKHASH_8_ADDR, 0},
	{"PCIE_BHI_OEMPKHASH_9", HWIO_PCIE_PCIE_BHI_OEMPKHASH_9_ADDR, 0},
	{"PCIE_BHI_TXVECDB", HWIO_PCIE_PCIE_BHI_TXVECDB_ADDR, 0},
	{"PCIE_BHI_TXVECSTATUS", HWIO_PCIE_PCIE_BHI_TXVECSTATUS_ADDR, 0},
	{"PCIE_BHI_RXVECDB", HWIO_PCIE_PCIE_BHI_RXVECDB_ADDR, 0},
	{"PCIE_BHI_RXVECSTATUS", HWIO_PCIE_PCIE_BHI_RXVECSTATUS_ADDR, 0},
	/* After dump this register, recovery will fail for QCA6490 */
	//{"PCIE_WLAON_RESET_DBG_SW_ENTRY", WLAON_RESET_DBG_SW_ENTRY, 0},
	{NULL},
};

static struct cnss_pci_reg register_to_dump[] = {
	{"QDSS_APB_DEC_CS_QDSSCSR_ETRIRQCTRL", QDSS_APB_DEC_CS_QDSSCSR_ETRIRQCTRL, 0},
	{"QDSS_APB_DEC_CS_QDSSCSR_PRESERVEETF", QDSS_APB_DEC_CS_QDSSCSR_PRESERVEETF, 0},
	{"QDSS_APB_DEC_CS_QDSSCSR_PRESERVEETR0", QDSS_APB_DEC_CS_QDSSCSR_PRESERVEETR0, 0},
	{"QDSS_APB_DEC_CS_QDSSCSR_PRESERVEETR1", QDSS_APB_DEC_CS_QDSSCSR_PRESERVEETR1, 0},
	{"Q6SS_PRIVCSR_QDSP6SS_QTMR_V1_CNTP_CTL_0", Q6SS_PRIVCSR_QDSP6SS_QTMR_V1_CNTP_CTL_0, 0},
	{"Q6SS_PRIVCSR_QDSP6SS_QTMR_V1_CNTP_CTL_1", Q6SS_PRIVCSR_QDSP6SS_QTMR_V1_CNTP_CTL_1, 0},
	{"Q6SS_PRIVCSR_QDSP6SS_QTMR_V1_CNTP_CTL_2", Q6SS_PRIVCSR_QDSP6SS_QTMR_V1_CNTP_CTL_2, 0},
	{NULL},
};

#define LINE_LEN_MAX 80

static int ath12k_register_dump(struct ath12k_base *ab,
				u8 **buf,
				size_t *buf_len,
				struct cnss_pci_reg *regs,
				size_t num)
{
	u32 i;
	size_t offset = 0;
	size_t line_len;
	ssize_t len;
	char (*line_ptr)[LINE_LEN_MAX];

	*buf_len = 0;

	line_ptr = (char (*)[LINE_LEN_MAX])vzalloc(num * LINE_LEN_MAX);
	if (!line_ptr)
		return -ENOMEM;

	for (i = 0; regs[i].name; i++) {
		regs[i].value = ath12k_pci_read32(ab, regs[i].offset);
		ath12k_info(ab, "%s[0x%x] = 0x%x\n",
			    regs[i].name, regs[i].offset, regs[i].value);
		len = snprintf(line_ptr[i], LINE_LEN_MAX, "%s[0x%x] = 0x%x\n",
			       regs[i].name, regs[i].offset, regs[i].value);
		*buf_len += len;
	}

	ath12k_info(ab, "%s buf len=%lu\n", __func__, *buf_len);
	*buf = vzalloc(*buf_len);
	if (!*buf)
		return -ENOMEM;

	for (i = 0; i < num; ++i) {
		line_len = strlen(line_ptr[i]);
		memcpy(*buf + offset, line_ptr[i], line_len);
		offset += line_len;
	}

	vfree(line_ptr);

	return 0;
}

void ath12k_pci_register_dump(struct ath12k_pci *ab_pci)
{
	size_t num;
	struct register_crash_data *crash_data = &ab_pci->reg_data;

	num = sizeof(register_to_dump) / sizeof(struct cnss_pci_reg) - 1;
	ath12k_register_dump(ab_pci->ab,
			     &crash_data->reg_buf,
			     &crash_data->reg_buf_len,
			     register_to_dump,
			     num);
	fdump(L"reg_buf.bin", crash_data->reg_buf, &crash_data->reg_buf_len);
	
	num = sizeof(register_rddm_fail_debug) / sizeof(struct cnss_pci_reg) - 1;
	ath12k_register_dump(ab_pci->ab,
			     &crash_data->reg_rddm_buf,
			     &crash_data->reg_rddm_buf_len,
			     register_rddm_fail_debug,
			     num);
	fdump(L"reg_rddm_buf.bin", crash_data->reg_rddm_buf, &crash_data->reg_rddm_buf_len);
}


void ath12k_mhi_pm_rddm_worker(void *context)
{
	struct ath12k_pci *ab_pci = (struct ath12k_pci *)context;
	
	mhi_download_rddm_img(ab_pci->mhi_ctrl, false);
	ath12k_coredump_fw_rddm_dump(ab_pci, ab_pci->mhi_ctrl);
	ath12k_coredump_fw_paging_dump(ab_pci, ab_pci->mhi_ctrl);
	ath12k_qmi_remote_dump(ab_pci->ab);
	ath12k_pci_register_dump(ab_pci);
	ath12k_coredump_buf_release(ab_pci);
}

