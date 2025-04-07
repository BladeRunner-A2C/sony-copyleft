/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/* SPDX-License-Identifier: BSD-3-Clause-Clear */
/**
 * Copyright (c) 2021 The Linux Foundation. All rights reserved.
 */

#ifndef _COREDUMP_H_
#define _COREDUMP_H_

#define ATH12K_FW_CRASH_DUMP_VERSION 1

enum ath12k_fw_crash_dump_type {
	ATH12K_FW_CRASH_PAGING_DATA,
	ATH12K_FW_CRASH_RDDM_DATA,
	ATH12K_FW_REMOTE_MEM_DATA,
	ATH12K_FW_REGISTER_DATA,
	ATH12K_FW_REGISTER_RDDM_DATA,
	ATH12K_FW_QDSS_DATA,
	ATH12K_FW_CRASH_DUMP_MAX,
};

struct ath12k_dump_segment {
	unsigned long addr;
	void *vaddr;
	unsigned int len;
	unsigned int type;
};

#pragma pack(1)
struct ath12k_dump_file_data {
	/* "ATH12K-FW-DUMP" */
	char df_magic[16];
	__le32 len;
	/* file dump version */
	__le32 version;
	//guid_t guid;
	/* time-of-day stamp */
	__le64 tv_sec;
	/* time-of-day stamp, nano-seconds */
	__le64 tv_nsec;
	/* room for growth w/out changing binary format */
	u8 unused[8];
	/* struct ath12k_tlv_dump_data + more */
	u8 data[0];
} __packed;
#pragma pack()

struct ath12k_coredump_state {
	struct ath12k_dump_file_data *header;
	struct ath12k_dump_segment *segments;
	struct completion dump_done;
	u32 num_seg;
};

#pragma pack(1)
struct ath12k_tlv_dump_data {
	/* see ath12k_fw_crash_dump_type above */
	__le32 type;
	/* in bytes */
	__le32 tlv_len;
	/* pad to 32-bit boundaries as needed */
	u8 tlv_data[];
} __packed;
#pragma pack()

void ath12k_mhi_pm_rddm_worker(void *context);

void ath12k_coredump_download_rddm(struct ath12k_base *ab);

#endif
