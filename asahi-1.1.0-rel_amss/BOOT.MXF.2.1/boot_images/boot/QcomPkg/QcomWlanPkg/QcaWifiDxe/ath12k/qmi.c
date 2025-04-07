/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

// SPDX-License-Identifier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2021 The Linux Foundation. All rights reserved.
 * Copyright (c) 2021-2022 Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <qdf/firmware.h>
#include <qdf/cfg.h>
#include <qdf/dpp.h>
#include "qmi.h"
#include "core.h"
#include "debug.h"

#define SLEEP_CLOCK_SELECT_INTERNAL_BIT	0x02
#define HOST_CSTATE_BIT			0x04
#define PLATFORM_CAP_PCIE_GLOBAL_RESET	0x08
#define ATH12K_QMI_MAX_CHUNK_SIZE	2097152

#define BIN_BDF_FILE_NAME		    L"bdwlan.bin"
#define BIN_BDF_FILE_NAME_PREFIX	L"bdwlan.e"
#define BDF_FILE_NAME_PREFIX		L"bdwlan"
#define MAX_M3_FILE_NAME_LENGTH		13
#define DEFAULT_M3_FILE_NAME		L"m3.bin"
#define REGDB_FILE_NAME	            L"regdb.bin"

static struct qmi_elem_info qmi_wlfw_qdss_trace_config_download_req_msg_v01_ei[] = {
	{
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = offsetof(struct qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
					   total_size_valid),
	},
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x10,
		.offset         = offsetof(struct qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
					   total_size),
	},
	{
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = offsetof(struct qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
					   seg_id_valid),
	},
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u32),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x11,
		.offset         = offsetof(struct qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
					   seg_id),
	},
	{
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = offsetof(struct qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
					   data_valid),
	},
	{
		.data_type      = QMI_DATA_LEN,
		.elem_len       = 1,
		.elem_size      = sizeof(u16),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x12,
		.offset         = offsetof(struct
				qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
				data_len),
	},
	{
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLANFW_MAX_DATA_SIZE_V01,
		.elem_size      = sizeof(u8),
		.array_type     = VAR_LEN_ARRAY,
		.tlv_type       = 0x12,
		.offset         = offsetof(struct
				qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
				data),
	},
	{
		.data_type      = QMI_OPT_FLAG,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = offsetof(struct qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
					   end_valid),
	},
	{
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x13,
		.offset         = offsetof(struct qmi_wlanfw_qdss_trace_config_download_req_msg_v01,
					   end),
	},
	{
		.data_type      = QMI_EOTI,
		.array_type     = NO_ARRAY,
		.tlv_type       = QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_qdss_trace_config_download_resp_msg_v01_ei[] = {
	{
		.data_type      = QMI_STRUCT,
		.elem_len       = 1,
		.elem_size      = sizeof(struct qmi_response_type_v01),
		.array_type     = NO_ARRAY,
		.tlv_type       = 0x02,
		.offset         = offsetof(struct qmi_wlanfw_qdss_trace_config_download_resp_msg_v01,
					   resp),
		.ei_array       = qmi_response_type_v01_ei,
	},
	{
		.data_type      = QMI_EOTI,
		.array_type     = NO_ARRAY,
		.tlv_type       = QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info wlfw_host_mlo_chip_info_s_v01_ei[] = {
	{
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0,
		.offset         = offsetof(struct wlfw_host_mlo_chip_info_s_v01,
					   chip_id),
	},
	{
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = 1,
		.elem_size      = sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type       = 0,
		.offset         = offsetof(struct wlfw_host_mlo_chip_info_s_v01,
					   num_local_links),
	},
	{
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLFW_MAX_NUM_MLO_LINKS_PER_CHIP_V01,
		.elem_size      = sizeof(u8),
		.array_type     = STATIC_ARRAY,
		.tlv_type       = 0,
		.offset         = offsetof(struct wlfw_host_mlo_chip_info_s_v01,
					   hw_link_id),
	},
	{
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.elem_len       = QMI_WLFW_MAX_NUM_MLO_LINKS_PER_CHIP_V01,
		.elem_size      = sizeof(u8),
		.array_type     = STATIC_ARRAY,
		.tlv_type       = 0,
		.offset         = offsetof(struct wlfw_host_mlo_chip_info_s_v01,
					   valid_mlo_link_id),
	},
	{
		.data_type      = QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type       = QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_host_cap_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   num_clients_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   num_clients),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   wake_msi_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   wake_msi),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   gpios_valid),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   gpios_len),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= QMI_WLFW_MAX_NUM_GPIO_V01,
		.elem_size	= sizeof(u32),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   gpios),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   nm_modem_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   nm_modem),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   bdf_support_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   bdf_support),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   bdf_cache_support_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   bdf_cache_support),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   m3_support_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   m3_support),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   m3_cache_support_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   m3_cache_support),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   cal_filesys_support_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   cal_filesys_support),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   cal_cache_support_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   cal_cache_support),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   cal_done_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   cal_done),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mem_bucket_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mem_bucket),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1C,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mem_cfg_mode_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1C,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mem_cfg_mode),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1D,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   cal_duration_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1D,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   cal_duraiton),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1E,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   platform_name_valid),
	},
	{
		.data_type	= QMI_STRING,
		.elem_len	= QMI_WLANFW_MAX_PLATFORM_NAME_LEN_V01 + 1,
		.elem_size	= sizeof(char),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1E,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   platform_name),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1F,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   ddr_range_valid),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_HOST_DDR_RANGE_SIZE_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_host_ddr_range),
		.array_type	= STATIC_ARRAY,
		.tlv_type	= 0x1F,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   ddr_range),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x20,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   host_build_type_valid),
	},
	{
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= sizeof(enum qmi_wlanfw_host_build_type),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x20,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   host_build_type),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x21,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_capable_valid),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x21,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_capable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x22,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_chip_id_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x22,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_chip_id),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x23,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_group_id_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x23,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_group_id),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x24,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   max_mlo_peer_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x24,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   max_mlo_peer),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x25,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_num_chips_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x25,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_num_chips),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x26,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_chip_info_valid),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLFW_MAX_NUM_MLO_CHIPS_V01,
		.elem_size	= sizeof(struct wlfw_host_mlo_chip_info_s_v01),
		.array_type	= STATIC_ARRAY,
		.tlv_type	= 0x26,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   mlo_chip_info),
		.ei_array	= wlfw_host_mlo_chip_info_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x27,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   feature_list_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x27,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_req_msg_v01,
					   feature_list),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_host_cap_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_host_cap_resp_msg_v01, resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_ind_register_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   fw_ready_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   fw_ready_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   initiate_cal_download_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   initiate_cal_download_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   initiate_cal_update_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   initiate_cal_update_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   msa_ready_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   msa_ready_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   pin_connect_result_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   pin_connect_result_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   client_id_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   client_id),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   request_mem_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   request_mem_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   fw_mem_ready_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   fw_mem_ready_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   fw_init_done_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   fw_init_done_enable),
	},

	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   rejuvenate_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   rejuvenate_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   xo_cal_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   xo_cal_enable),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   cal_done_enable_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_req_msg_v01,
					   cal_done_enable),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_ind_register_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_resp_msg_v01,
					   fw_status_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_ind_register_resp_msg_v01,
					   fw_status),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_mem_cfg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_cfg_s_v01, offset),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_cfg_s_v01, size),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_cfg_s_v01, secure_flag),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_mem_seg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_seg_s_v01,
				  size),
	},
	{
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= sizeof(enum qmi_wlanfw_mem_type_enum_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_seg_s_v01, type),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_seg_s_v01, mem_cfg_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_MEM_CFG_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_mem_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_seg_s_v01, mem_cfg),
		.ei_array	= qmi_wlanfw_mem_cfg_s_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_request_mem_ind_msg_v01_ei[] = {
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= offsetof(struct qmi_wlanfw_request_mem_ind_msg_v01,
					   mem_seg_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= ATH12K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_mem_seg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x01,
		.offset		= offsetof(struct qmi_wlanfw_request_mem_ind_msg_v01,
					   mem_seg),
		.ei_array	= qmi_wlanfw_mem_seg_s_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_mem_seg_resp_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_seg_resp_s_v01, addr),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_seg_resp_s_v01, size),
	},
	{
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= sizeof(enum qmi_wlanfw_mem_type_enum_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_seg_resp_s_v01, type),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_mem_seg_resp_s_v01, restore),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_respond_mem_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= offsetof(struct qmi_wlanfw_respond_mem_req_msg_v01,
					   mem_seg_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= ATH12K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_mem_seg_resp_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x01,
		.offset		= offsetof(struct qmi_wlanfw_respond_mem_req_msg_v01,
					   mem_seg),
		.ei_array	= qmi_wlanfw_mem_seg_resp_s_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_respond_mem_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_respond_mem_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_cap_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_rf_chip_info_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_rf_chip_info_s_v01,
					   chip_id),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_rf_chip_info_s_v01,
					   chip_family),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_rf_board_info_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_rf_board_info_s_v01,
					   board_id),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_soc_info_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_soc_info_s_v01, soc_id),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_dev_mem_info_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_dev_mem_info_s_v01,
					   start),
	},
	{
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_dev_mem_info_s_v01,
					   size),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_fw_version_info_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_fw_version_info_s_v01,
					   fw_version),
	},
	{
		.data_type	= QMI_STRING,
		.elem_len	= ATH12K_QMI_WLANFW_MAX_TIMESTAMP_LEN_V01 + 1,
		.elem_size	= sizeof(char),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_fw_version_info_s_v01,
					   fw_build_timestamp),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_cap_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01, resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   chip_info_valid),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_wlanfw_rf_chip_info_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   chip_info),
		.ei_array	= qmi_wlanfw_rf_chip_info_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   board_info_valid),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_wlanfw_rf_board_info_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   board_info),
		.ei_array	= qmi_wlanfw_rf_board_info_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   soc_info_valid),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_wlanfw_soc_info_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   soc_info),
		.ei_array	= qmi_wlanfw_soc_info_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   fw_version_info_valid),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_wlanfw_fw_version_info_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   fw_version_info),
		.ei_array	= qmi_wlanfw_fw_version_info_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   fw_build_id_valid),
	},
	{
		.data_type	= QMI_STRING,
		.elem_len	= ATH12K_QMI_WLANFW_MAX_BUILD_ID_LEN_V01 + 1,
		.elem_size	= sizeof(char),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   fw_build_id),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   num_macs_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   num_macs),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   voltage_mv_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   voltage_mv),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   time_freq_hz_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   time_freq_hz),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   otp_version_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x18,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   otp_version),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   eeprom_caldata_read_timeout_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x19,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   eeprom_caldata_read_timeout),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   fw_caps_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1A,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01, fw_caps),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   rd_card_chain_cap_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1B,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   rd_card_chain_cap),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x1C,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01,
					   dev_mem_info_valid),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= ATH12K_QMI_WLFW_MAX_DEV_MEM_NUM_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_dev_mem_info_s_v01),
		.array_type	= STATIC_ARRAY,
		.tlv_type	= 0x1C,
		.offset		= offsetof(struct qmi_wlanfw_cap_resp_msg_v01, dev_mem),
		.ei_array	= qmi_wlanfw_dev_mem_info_s_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_bdf_download_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   valid),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   file_id_valid),
	},
	{
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= sizeof(enum qmi_wlanfw_cal_temp_id_enum_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   file_id),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   total_size_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   total_size),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   seg_id_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   seg_id),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   data_valid),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   data_len),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= QMI_WLANFW_MAX_DATA_SIZE_V01,
		.elem_size	= sizeof(u8),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   data),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   end_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   end),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   bdf_type_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_req_msg_v01,
					   bdf_type),
	},

	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_bdf_download_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_bdf_download_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_m3_info_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_8_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u64),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= offsetof(struct qmi_wlanfw_m3_info_req_msg_v01, addr),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_m3_info_req_msg_v01, size),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_m3_info_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_m3_info_resp_msg_v01, resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_ce_tgt_pipe_cfg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   pipe_num),
	},
	{
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= sizeof(enum qmi_wlanfw_pipedir_enum_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   pipe_dir),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   nentries),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   nbytes_max),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_ce_tgt_pipe_cfg_s_v01,
					   flags),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_ce_svc_pipe_cfg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_ce_svc_pipe_cfg_s_v01,
					   service_id),
	},
	{
		.data_type	= QMI_SIGNED_4_BYTE_ENUM,
		.elem_len	= 1,
		.elem_size	= sizeof(enum qmi_wlanfw_pipedir_enum_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_ce_svc_pipe_cfg_s_v01,
					   pipe_dir),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_ce_svc_pipe_cfg_s_v01,
					   pipe_num),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_shadow_reg_cfg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_shadow_reg_cfg_s_v01, id),
	},
	{
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_shadow_reg_cfg_s_v01,
					   offset),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_shadow_reg_v2_cfg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_shadow_reg_v2_cfg_s_v01,
					   addr),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_shadow_reg_v3_cfg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct qmi_wlanfw_shadow_reg_v3_cfg_s_v01,
					   addr),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_rri_over_ddr_cfg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct
					   qmi_wlanfw_rri_over_ddr_cfg_s_v01,
					   base_addr_low),
	},
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct
					   qmi_wlanfw_rri_over_ddr_cfg_s_v01,
					   base_addr_high),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_msi_cfg_s_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct
					   qmi_wlanfw_msi_cfg_s_v01,
					   ce_id),
	},
	{
		.data_type	= QMI_UNSIGNED_2_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u16),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0,
		.offset		= offsetof(struct
					   qmi_wlanfw_msi_cfg_s_v01,
					   msi_vector),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_wlan_mode_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_UNSIGNED_4_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u32),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x01,
		.offset		= offsetof(struct qmi_wlanfw_wlan_mode_req_msg_v01,
					   mode),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_wlan_mode_req_msg_v01,
					   hw_debug_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_wlan_mode_req_msg_v01,
					   hw_debug),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_wlan_mode_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_wlan_mode_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_wlan_cfg_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   host_version_valid),
	},
	{
		.data_type	= QMI_STRING,
		.elem_len	= QMI_WLANFW_MAX_STR_LEN_V01 + 1,
		.elem_size	= sizeof(char),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   host_version),
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   tgt_cfg_valid),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   tgt_cfg_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_CE_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_ce_tgt_pipe_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x11,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   tgt_cfg),
		.ei_array	= qmi_wlanfw_ce_tgt_pipe_cfg_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   svc_cfg_valid),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   svc_cfg_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_SVC_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_ce_svc_pipe_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x12,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   svc_cfg),
		.ei_array	= qmi_wlanfw_ce_svc_pipe_cfg_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type = NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg_valid),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type = NO_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_SHADOW_REG_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_shadow_reg_cfg_s_v01),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type	= 0x13,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg),
		.ei_array	= qmi_wlanfw_shadow_reg_cfg_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type = NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg_v2_valid),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type = NO_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg_v2_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_SHADOW_REG_V2_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_shadow_reg_v2_cfg_s_v01),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type	= 0x14,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg_v2),
		.ei_array	= qmi_wlanfw_shadow_reg_v2_cfg_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   rri_over_ddr_cfg_valid),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_wlanfw_rri_over_ddr_cfg_s_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x15,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   rri_over_ddr_cfg),
		.ei_array	= qmi_wlanfw_rri_over_ddr_cfg_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   msi_cfg_valid),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   msi_cfg_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_CE_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_msi_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x16,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   msi_cfg),
		.ei_array	= qmi_wlanfw_msi_cfg_s_v01_ei,
	},
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg_v3_valid),
	},
	{
		.data_type	= QMI_DATA_LEN,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg_v3_len),
	},
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= QMI_WLANFW_MAX_NUM_SHADOW_REG_V3_V01,
		.elem_size	= sizeof(struct qmi_wlanfw_shadow_reg_v3_cfg_s_v01),
		.array_type	= VAR_LEN_ARRAY,
		.tlv_type	= 0x17,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_req_msg_v01,
					   shadow_reg_v3),
		.ei_array	= qmi_wlanfw_shadow_reg_v3_cfg_s_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_wlan_cfg_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_wlan_cfg_resp_msg_v01, resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_mem_ready_ind_msg_v01_ei[] = {
	{
		.data_type = QMI_EOTI,
		.array_type = NO_ARRAY,
	},
};

static struct qmi_elem_info qmi_wlanfw_fw_ready_ind_msg_v01_ei[] = {
	{
		.data_type = QMI_EOTI,
		.array_type = NO_ARRAY,
	},
};

static struct qmi_elem_info qmi_wlanfw_wlan_ini_req_msg_v01_ei[] = {
	{
		.data_type	= QMI_OPT_FLAG,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_wlan_ini_req_msg_v01,
					   enablefwlog_valid),
	},
	{
		.data_type	= QMI_UNSIGNED_1_BYTE,
		.elem_len	= 1,
		.elem_size	= sizeof(u8),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x10,
		.offset		= offsetof(struct qmi_wlanfw_wlan_ini_req_msg_v01,
					   enablefwlog),
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static struct qmi_elem_info qmi_wlanfw_wlan_ini_resp_msg_v01_ei[] = {
	{
		.data_type	= QMI_STRUCT,
		.elem_len	= 1,
		.elem_size	= sizeof(struct qmi_response_type_v01),
		.array_type	= NO_ARRAY,
		.tlv_type	= 0x02,
		.offset		= offsetof(struct qmi_wlanfw_wlan_ini_resp_msg_v01,
					   resp),
		.ei_array	= qmi_response_type_v01_ei,
	},
	{
		.data_type	= QMI_EOTI,
		.array_type	= NO_ARRAY,
		.tlv_type	= QMI_COMMON_TLV_TYPE,
	},
};

static int ath12k_qmi_send_qdss_trace_config_download_req(struct ath12k_base *ab,
							  const u8 *buffer,
							  unsigned int buffer_len)
{
	int ret = 0;
	struct qmi_wlanfw_qdss_trace_config_download_req_msg_v01 *req;
	struct qmi_wlanfw_qdss_trace_config_download_resp_msg_v01 resp;
	struct qmi_txn txn;
	const u8 *temp = buffer;
	int  max_len = QMI_WLANFW_QDSS_TRACE_CONFIG_DOWNLOAD_REQ_MSG_V01_MAX_LEN;
	unsigned int  remaining;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	remaining = buffer_len;
	while (remaining) {
		memset(&resp, 0, sizeof(resp));
		req->total_size_valid = 1;
		req->total_size = buffer_len;
		req->seg_id_valid = 1;
		req->data_valid = 1;
		req->end_valid = 1;

		if (remaining > QMI_WLANFW_MAX_DATA_SIZE_V01) {
			req->data_len = QMI_WLANFW_MAX_DATA_SIZE_V01;
		} else {
			req->data_len = remaining;
			req->end = 1;
		}
		memcpy(req->data, temp, req->data_len);

		ret = qmi_txn_init(&ab->qmi.handle, &txn,
				   qmi_wlanfw_qdss_trace_config_download_resp_msg_v01_ei,
				   &resp);
		if (ret < 0)
			goto out;

		ret = qmi_send_request(&ab->qmi.handle, &txn,
				       QMI_WLANFW_QDSS_TRACE_CONFIG_DOWNLOAD_REQ_V01,
				       max_len,
				       qmi_wlfw_qdss_trace_config_download_req_msg_v01_ei,
				       req);
		if (ret < 0) {
			ath12k_warn(ab, "Failed to send QDSS config download request = %d\n",
				    ret);
			qmi_txn_cancel(&txn);
			goto out;
		}

		ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
		if (ret < 0)
			goto out;

		if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
			ath12k_warn(ab, "QDSS config download request failed, result: %d, err: %d\n",
				    resp.resp.result, resp.resp.error);
			ret = -EINVAL;
			goto out;
		}
		remaining -= req->data_len;
		temp += req->data_len;
		req->seg_id++;
	}

out:
	kfree(req);
	return ret;
}

static int ath12k_qmi_send_qdss_config(struct ath12k_base *ab)
{
	unsigned int config_len;
	const char *config;
	int ret;

	config = ab->hw_params->qdss_config;
	if (!config)
		/* this hw doesn't need qdss config */
		return 0;

	config_len = ab->hw_params->qdss_config_len;

	ret = ath12k_qmi_send_qdss_trace_config_download_req(ab,
							     (const u8 *)config,
							     config_len);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to load QDSS config to FW: %d\n", ret);
		return ret;
	}

	return 0;
}

static void ath12k_host_cap_parse_mlo(struct qmi_wlanfw_host_cap_req_msg_v01 *req)
{
	req->mlo_capable_valid = 1;
	req->mlo_capable = 1;
	req->mlo_chip_id_valid = 1;
	req->mlo_chip_id = 0;
	req->mlo_group_id_valid = 1;
	req->mlo_group_id = 0;
	req->max_mlo_peer_valid = 1;
	/* Max peer number generally won't change for the same device
	 * but needs to be synced with host driver.
	 */
	req->max_mlo_peer = 32;
	req->mlo_num_chips_valid = 1;
	req->mlo_num_chips = 1;
	req->mlo_chip_info_valid = 1;
	req->mlo_chip_info[0].chip_id = 0;
	req->mlo_chip_info[0].num_local_links = 2;
	req->mlo_chip_info[0].hw_link_id[0] = 0;
	req->mlo_chip_info[0].hw_link_id[1] = 1;
	req->mlo_chip_info[0].valid_mlo_link_id[0] = 1;
	req->mlo_chip_info[0].valid_mlo_link_id[1] = 1;
}

static int ath12k_qmi_host_cap_send(struct ath12k_base *ab)
{
	struct qmi_wlanfw_host_cap_req_msg_v01 req;
	struct qmi_wlanfw_host_cap_resp_msg_v01 resp;
	struct qmi_txn txn = { 0, };
	int ret = 0;

	memset(&req, 0, sizeof(req));
	memset(&resp, 0, sizeof(resp));

	req.num_clients_valid = 1;
	req.num_clients = 1;
	req.mem_cfg_mode = (u8)ab->qmi.target_mem_mode;
	req.mem_cfg_mode_valid = 1;
	req.bdf_support_valid = 1;
	req.bdf_support = 1;

	req.m3_support_valid = 1;
	req.m3_support = 1;
	req.m3_cache_support_valid = 1;
	req.m3_cache_support = 1;

	req.cal_done_valid = 1;
	req.cal_done = ab->qmi.cal_done;

	/* BRINGUP: here we are piggybacking a lot of stuff using
	 * internal_sleep_clock, should it be split?
	 */
	if (ab->hw_params->internal_sleep_clock) {
		req.nm_modem_valid = 1;

		/* Notify firmware that this is non-qualcomm platform. */
		req.nm_modem |= HOST_CSTATE_BIT;

		/* Notify firmware about the sleep clock selection,
		 * nm_modem_bit[1] is used for this purpose. Host driver on
		 * non-qualcomm platforms should select internal sleep
		 * clock.
		 */
		req.nm_modem |= SLEEP_CLOCK_SELECT_INTERNAL_BIT;
		req.nm_modem |= PLATFORM_CAP_PCIE_GLOBAL_RESET;

		ath12k_host_cap_parse_mlo(&req);
	}

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_host_cap_resp_msg_v01_ei, &resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&ab->qmi.handle, &txn,
			       QMI_WLANFW_HOST_CAP_REQ_V01,
			       QMI_WLANFW_HOST_CAP_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_host_cap_req_msg_v01_ei, &req);
	if (ret < 0) {
		ath12k_warn(ab, "Failed to send host capability request,err = %d\n", ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
	if (ret < 0)
		goto out;

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath12k_warn(ab, "Host capability request failed, result: %d, err: %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		goto out;
	}

out:
	return ret;
}

static int ath12k_qmi_fw_ind_register_send(struct ath12k_base *ab)
{
	struct qmi_wlanfw_ind_register_req_msg_v01 *req;
	struct qmi_wlanfw_ind_register_resp_msg_v01 *resp;
	struct qmi_handle *handle = &ab->qmi.handle;
	struct qmi_txn txn;
	int ret;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	resp = kzalloc(sizeof(*resp), GFP_KERNEL);
	if (!resp) {
		ret = -ENOMEM;
		goto resp_out;
	}

	req->client_id_valid = 1;
	req->client_id = QMI_WLANFW_CLIENT_ID;
	req->fw_ready_enable_valid = 1;
	req->fw_ready_enable = 1;
	req->request_mem_enable_valid = 1;
	req->request_mem_enable = 1;
	req->fw_mem_ready_enable_valid = 1;
	req->fw_mem_ready_enable = 1;
	req->cal_done_enable_valid = 1;
	req->cal_done_enable = 1;
	req->fw_init_done_enable_valid = 1;
	req->fw_init_done_enable = 1;

	req->pin_connect_result_enable_valid = 0;
	req->pin_connect_result_enable = 0;

	ret = qmi_txn_init(handle, &txn,
			   qmi_wlanfw_ind_register_resp_msg_v01_ei, resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&ab->qmi.handle, &txn,
			       QMI_WLANFW_IND_REGISTER_REQ_V01,
			       QMI_WLANFW_IND_REGISTER_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_ind_register_req_msg_v01_ei, req);
	if (ret < 0) {
		ath12k_warn(ab, "Failed to send indication register request, err = %d\n",
			    ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
	if (ret < 0) {
		ath12k_warn(ab, "failed to register fw indication %d\n", ret);
		goto out;
	}

	if (resp->resp.result != QMI_RESULT_SUCCESS_V01) {
		ath12k_warn(ab, "FW Ind register request failed, result: %d, err: %d\n",
			    resp->resp.result, resp->resp.error);
		ret = -EINVAL;
		goto out;
	}

out:
	kfree(resp);
resp_out:
	kfree(req);
	return ret;
}

static int ath12k_qmi_respond_fw_mem_request(struct ath12k_base *ab)
{
	struct qmi_wlanfw_respond_mem_req_msg_v01 *req;
	struct qmi_wlanfw_respond_mem_resp_msg_v01 resp;
	struct qmi_txn txn = { 0, };
	int ret = 0;
	u32 i;
	bool delayed;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	memset(&resp, 0, sizeof(resp));

	/* Some targets by default request a block of big contiguous
	 * DMA memory, it's hard to allocate from kernel. So host returns
	 * failure to firmware and firmware then request multiple blocks of
	 * small chunk size memory.
	 */
	if (ab->qmi.target_mem_delayed) {
		delayed = true;
		ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi delays mem_request %d\n",
			   ab->qmi.mem_seg_count);
		memset(req, 0, sizeof(*req));
	} else {
		delayed = false;
		req->mem_seg_len = ab->qmi.mem_seg_count;
		for (i = 0; i < req->mem_seg_len; i++) {
			req->mem_seg[i].addr = ab->qmi.target_mem[i].aligned_paddr;
			req->mem_seg[i].size = ab->qmi.target_mem[i].size;
			req->mem_seg[i].type = ab->qmi.target_mem[i].type;
			ath12k_dbg(ab, ATH12K_DBG_QMI,
				   "qmi req mem_seg[%d] %pad %u %u\n", i,
				   ab->qmi.target_mem[i].aligned_paddr,
				   ab->qmi.target_mem[i].size,
				   ab->qmi.target_mem[i].type);
		}
	}

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_respond_mem_resp_msg_v01_ei, &resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&ab->qmi.handle, &txn,
			       QMI_WLANFW_RESPOND_MEM_REQ_V01,
			       QMI_WLANFW_RESPOND_MEM_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_respond_mem_req_msg_v01_ei, req);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to respond memory request, err = %d\n",
			    ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed memory request, err = %d\n", ret);
		goto out;
	}

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		/* the error response is expected when
		 * target_mem_delayed is true.
		 */
		if (delayed && resp.resp.error == 0)
			goto out;

		ath12k_warn(ab, "Respond mem req failed, result: %d, err: %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		goto out;
	}
out:
	kfree(req);
	return ret;
}

static void ath12k_qmi_free_target_mem_chunk(struct ath12k_base *ab)
{
	u32 i;

	for (i = 0; i < ab->qmi.mem_seg_count; i++) {
		if (!ab->qmi.target_mem[i].vaddr)
			continue;
		dma_free_coherent(ab->dev,
            ab->qmi.target_mem[i].alloc_size,
            ab->qmi.target_mem[i].vaddr,
            ab->qmi.target_mem[i].paddr,
            ab->qmi.target_mem[i].p_dma_mapping_addr);
		ab->qmi.target_mem[i].vaddr = NULL;
        ab->qmi.target_mem[i].aligned_vaddr = NULL;
	}
}

static void ath12k_qmi_set_remote_mem(struct fw_remote_mem *fw_mem,
				      void *vaddr, size_t size,
				      uint32_t segnum)
{
	fw_mem[segnum].vaddr = vaddr;
	fw_mem[segnum].size = size;
}

static int ath12k_qmi_alloc_target_mem_chunk(struct ath12k_base *ab)
{
	u32 i;
	struct target_mem_chunk *chunk;

	ab->qmi.target_mem_delayed = false;

	for (i = 0; i < ab->qmi.mem_seg_count; i++) {
		chunk = &ab->qmi.target_mem[i];

		WARN_ON(chunk->vaddr != NULL);

		/* Allocate memory for the region and the functionality supported
		 * on the host. For the non-supported memory region, host does not
		 * allocate memory, assigns NULL and FW will handle this without crashing.
		 */
		switch (chunk->type) {
		case HOST_DDR_REGION_TYPE:
		case M3_DUMP_REGION_TYPE:
		case PAGEABLE_MEM_REGION_TYPE:
		case CALDB_MEM_REGION_TYPE:
			if (chunk->size > ATH12K_QMI_MAX_CHUNK_SIZE) {
				ab->qmi.target_mem_delayed = true;
 				ath12k_warn(ab, "will try later with small size\n", chunk->size, chunk->type);
				return 0;
			}
			
			chunk->alloc_size = chunk->size + 
            ATH12K_QMI_WLFW_MM_DEFAULT_ALIGNMENT - 1;
			chunk->vaddr = dma_alloc_coherent(ab->dev,
							   chunk->alloc_size,
							   &chunk->paddr, 
							   &chunk->p_dma_mapping_addr);
			if (!chunk->vaddr) {
				ath12k_warn(ab, "memory allocation failure for %u size: %d\n",
					    chunk->type, chunk->size);
				return -ENOMEM;
			}
			
			chunk->aligned_paddr = 
            ALIGN(chunk->paddr, ATH12K_QMI_WLFW_MM_DEFAULT_ALIGNMENT);
        	chunk->aligned_vaddr = (u8*)chunk->vaddr + (chunk->aligned_paddr - chunk->paddr);
	        ath12k_info(ab, "qmi mem seg type %d size %d, aligned_vaddr=0x%p, aligned_paddr=0x%x, p_dma_mapping_addr=0x%p\n", 
	            chunk->type, ab->qmi.target_mem[i].size,
	            chunk->aligned_vaddr,
	            chunk->aligned_paddr,
	            chunk->p_dma_mapping_addr);
			
			if (chunk->type == QMI_WLANFW_MEM_TYPE_DDR_V01) {
	            ath12k_qmi_set_remote_mem(ab->remote_mem,
	                chunk->aligned_vaddr,
	                chunk->size,
	                i);
				ath12k_info(ab, "vaddr=0x%p size=0x%x\n", chunk->aligned_vaddr, chunk->size);
        	}
			
			break;
		default:
			ath12k_warn(ab, "memory type %u not supported\n", chunk->type);
			chunk->paddr = 0;
			chunk->vaddr = NULL;
			break;
		}
	}
	return 0;
}

int ath12k_qmi_wlanfw_wlan_ini_send(struct ath12k_base *ab, bool enable)
{
	int ret;
	struct qmi_txn txn = { 0, };
	struct qmi_wlanfw_wlan_ini_req_msg_v01 req;
	struct qmi_wlanfw_wlan_ini_resp_msg_v01 resp;

	memset(&req, 0, sizeof(req));
	memset(&resp, 0, sizeof(resp));

	req.enablefwlog_valid = true;
	req.enablefwlog = enable ? 1 : 0;

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_wlan_ini_resp_msg_v01_ei, &resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&ab->qmi.handle, &txn,
			       ATH12K_QMI_WLANFW_WLAN_INI_REQ_V01,
			       QMI_WLANFW_WLAN_INI_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_wlan_ini_req_msg_v01_ei, &req);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send wlan ini request, err = %d\n",
			    ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed wlan ini request, err = %d\n", ret);
		goto out;
	}

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath12k_warn(ab, "qmi wlan ini request failed, result: %d, err: %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		goto out;
	}

out:
	return ret;
}

static int ath12k_qmi_request_target_cap(struct ath12k_base *ab)
{
	struct qmi_wlanfw_cap_req_msg_v01 req;
	struct qmi_wlanfw_cap_resp_msg_v01 resp;
	struct qmi_txn txn = { 0, };
	unsigned int board_id = ATH12K_BOARD_ID_DEFAULT;
	int ret = 0;
	int i;

	memset(&req, 0, sizeof(req));
	memset(&resp, 0, sizeof(resp));

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_cap_resp_msg_v01_ei, &resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&ab->qmi.handle, &txn,
			       QMI_WLANFW_CAP_REQ_V01,
			       QMI_WLANFW_CAP_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_cap_req_msg_v01_ei, &req);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send target cap request, err = %d\n",
			    ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed target cap request %d\n", ret);
		goto out;
	}

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath12k_warn(ab, "qmi targetcap req failed, result: %d, err: %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		goto out;
	}

	if (resp.chip_info_valid) {
		ab->qmi.target.chip_id = resp.chip_info.chip_id;
		ab->qmi.target.chip_family = resp.chip_info.chip_family;
	}

	if (resp.board_info_valid)
		ab->qmi.target.board_id = resp.board_info.board_id;
	else
		ab->qmi.target.board_id = board_id;

	if (resp.soc_info_valid)
		ab->qmi.target.soc_id = resp.soc_info.soc_id;

	if (resp.fw_version_info_valid) {
		ab->qmi.target.fw_version = resp.fw_version_info.fw_version;
		strlcpy(ab->qmi.target.fw_build_timestamp,
			resp.fw_version_info.fw_build_timestamp,
			sizeof(ab->qmi.target.fw_build_timestamp));
	}

	if (resp.fw_build_id_valid)
		strlcpy(ab->qmi.target.fw_build_id, resp.fw_build_id,
			sizeof(ab->qmi.target.fw_build_id));

	if (resp.dev_mem_info_valid) {
		for (i = 0; i < ATH12K_QMI_WLFW_MAX_DEV_MEM_NUM_V01; i++) {
			ab->qmi.dev_mem[i].start =
				resp.dev_mem[i].start;
			ab->qmi.dev_mem[i].size =
				resp.dev_mem[i].size;
			ath12k_dbg(ab, ATH12K_DBG_QMI,
				   "devmem [%d] start ox%llx size %llu\n", i,
				   ab->qmi.dev_mem[i].start,
				   ab->qmi.dev_mem[i].size);
		}
	}

	if (resp.eeprom_caldata_read_timeout_valid) {
		ab->qmi.target.eeprom_caldata = resp.eeprom_caldata_read_timeout;
		ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi cal data supported from eeprom\n");
	}

	ath12k_info(ab, "chip_id 0x%x chip_family 0x%x board_id 0x%x soc_id 0x%x\n",
		    ab->qmi.target.chip_id, ab->qmi.target.chip_family,
		    ab->qmi.target.board_id, ab->qmi.target.soc_id);

	ath12k_info(ab, "fw_version 0x%x fw_build_timestamp %s fw_build_id %s",
		    ab->qmi.target.fw_version,
		    ab->qmi.target.fw_build_timestamp,
		    ab->qmi.target.fw_build_id);

out:
	return ret;
}

static int ath12k_qmi_load_file_target_mem(struct ath12k_base *ab,
					   const u8 *data, u32 len, u8 type)
{
	struct qmi_wlanfw_bdf_download_req_msg_v01 *req;
	struct qmi_wlanfw_bdf_download_resp_msg_v01 resp;
	struct qmi_txn txn = { 0, };
	const u8 *temp = data;
	int ret;
	u32 remaining = len;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;
	memset(&resp, 0, sizeof(resp));

	while (remaining) {
		req->valid = 1;
		req->file_id_valid = 1;
		req->file_id = ab->qmi.target.board_id;
		req->total_size_valid = 1;
		req->total_size = remaining;
		req->seg_id_valid = 1;
		req->data_valid = 1;
		req->bdf_type = type;
		req->bdf_type_valid = 1;
		req->end_valid = 1;
		req->end = 0;

		if (remaining > QMI_WLANFW_MAX_DATA_SIZE_V01) {
			req->data_len = QMI_WLANFW_MAX_DATA_SIZE_V01;
		} else {
			req->data_len = remaining;
			req->end = 1;
		}

		if (type == ATH12K_QMI_FILE_TYPE_EEPROM) {
			req->data_valid = 0;
			req->end = 1;
			req->data_len = ATH12K_QMI_MAX_BDF_FILE_NAME_SIZE;
		} else {
			memcpy(req->data, temp, req->data_len);
		}

		ret = qmi_txn_init(&ab->qmi.handle, &txn,
				   qmi_wlanfw_bdf_download_resp_msg_v01_ei,
				   &resp);
		if (ret < 0)
			goto out;

		ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi bdf download req fixed addr type %d\n",
			   type);

		ret = qmi_send_request(&ab->qmi.handle, &txn,
				       QMI_WLANFW_BDF_DOWNLOAD_REQ_V01,
				       QMI_WLANFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_LEN,
				       qmi_wlanfw_bdf_download_req_msg_v01_ei, req);
		if (ret < 0) {
			qmi_txn_cancel(&txn);
			goto out;
		}

		ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
		if (ret < 0)
			goto out;

		if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
			ath12k_warn(ab, "qmi BDF download failed, result: %d, err: %d\n",
				    resp.resp.result, resp.resp.error);
			ret = -EINVAL;
			goto out;
		}

		remaining -= req->data_len;
		temp += req->data_len;
		req->seg_id++;
		ath12k_dbg(ab, ATH12K_DBG_QMI,
			   "qmi bdf download request remaining %i\n",
			   remaining);
	}

out:
	kfree(req);
	return ret;
}

static int ath12k_target_match_expression(struct ath12k_base *ab, struct expression_iterator *it)
{
    const struct pci_device_id *device_id;
    const struct target_info *target_info;
    u32 count;
    int ret;

	device_id = pci_get_hardware_id(ab->dev);
    if (!device_id) {
        ath12k_err(ab, "failed to get hardware id\n");
        return -ENODEV;
    }
    target_info = &ab->qmi.target;

    count = 0;
    ret = 0;

    while (expression_iterator_next(it) == 0) {
        count++;
        if (strcmp("bus", it->key) == 0) {
            if (strcmp(it->value, "pci") != 0) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("vendor", it->key) == 0) {
            if (strhextou64(it->value) != device_id->vendor) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("device", it->key) == 0) {
            if (strhextou64(it->value) != device_id->device) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("subsystem-vendor", it->key) == 0) {
            if (strhextou64(it->value) != device_id->subsystem_vendor) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("subsystem-device", it->key) == 0) {
            if (strhextou64(it->value) != device_id->subsystem_device) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("qmi-board-id", it->key) == 0) {
            if (strhextou64(it->value) != target_info->board_id) {
                ret = -EBADF;
                break;
            }
        }
        else if (strcmp("qmi-chip-id", it->key) == 0) {
            if (strhextou64(it->value) != target_info->chip_id) {
                ret = -EBADF;
                break;
            }
        }
        else {
            ath12k_warn(ab, "unsupported expression: %a=%a\n", it->key, it->value);
            ret = -EBADF;
        }
    }

    if (!count) /* expression is invalid */
        ret = -EBADF;

    return ret;
}

static int ath12k_firmware_metadata_match_target(const u8 *name, struct firmware_metadata *metadata, void *ctx)
{
    struct ath12k_base *ab = ctx;
    struct description_iterator it;
    int ret;

    if (!name || !metadata || !ab)
        return -EINVAL;

    /* match target if no description is specified */
    if (!metadata->description) {
        ath12k_info(ab, "match firmware %a(no description): 0\n", name);
        return 0;
    }

    ret = 0;
    description_iterator_init(&it, metadata->description, metadata->description_len);
    
    while (description_iterator_next(&it) == 0) {
        ret = ath12k_target_match_expression(ab, &it.expression_it);
        if (!ret)
            break;
    }

    if (SUPPORT_DEBUG_PRINT) {
        u8 description[384] = { 0 };
        memcpy(description, metadata->description, MIN(metadata->description_len, sizeof(description) - 1));
        ath12k_info(ab, "match firmware %a(description: %a): %d\n", name, description, ret);
    }

    return ret;
}

int ath12k_get_bdf_from_dpp(struct ath12k_base *ab, struct firmware *fw)
{
    const struct target_info *target_info =  &ab->qmi.target;
    return dpp_get_wlan_bdf(fw, target_info->board_id, target_info->chip_id);
}

int ath12k_get_bdf(struct ath12k_base *ab, struct firmware *fw_entry)
{
    int ret;

#if SUPPORT_QCOM_DPP
	ath12k_info(ab, "First try get bdf from dpp\n");
	ret = ath12k_get_bdf_from_dpp(ab, fw_entry);
	if (!ret) {
		ath12k_info(ab, "Get bdf from dpp succ\n");
		return ret;
	}
#endif

    ath12k_info(ab, "try to get matched bdf from firmware\n");
    ret = request_firmware_fancily(fw_entry, BIN_BDF_FILE_NAME, ath12k_firmware_metadata_match_target, ab);
    if (ret) {
        ath12k_err(ab, "failed to load a matched bdf: %d\n", ret);
    }

    return ret;
}

int ath12k_get_regdb(struct ath12k_base *ab, struct firmware *fw_entry)
{
    int ret;

    ret = request_firmware_fancily(fw_entry, REGDB_FILE_NAME, ath12k_firmware_metadata_match_target, ab);
    if (ret) {
        ath12k_warn(ab, "qmi failed to load regdb: %d\n", ret);
    }

    return ret;
}

static int ath12k_qmi_load_bdf_qmi(struct ath12k_base *ab, enum ath12k_qmi_bdf_type type)
{
	struct qmi_wlanfw_bdf_download_req_msg_v01 *req;
	struct qmi_wlanfw_bdf_download_resp_msg_v01 resp;
	struct firmware fw_entry = { 0 };
	unsigned int remaining;
	struct qmi_txn txn = { 0 };
	int ret = 0;
	const u8 *temp;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;
	memset(&resp, 0, sizeof(resp));

    if (type == ATH12K_QMI_BDF_TYPE_ELF) {
        ret = ath12k_get_bdf(ab, &fw_entry);
        if (ret) {
            ath12k_err(ab, "qmi failed to load bdf\n");
            goto out;
        }
    }
    else if (type == ATH12K_QMI_BDF_TYPE_REGDB) {
        ret = ath12k_get_regdb(ab, &fw_entry);
        if (ret) {
            ath12k_err(ab, "qmi failed to load regdb\n");
            goto out;
        }
    }
    else {
        ret = -EINVAL;
        ath12k_err(ab, "unsupported bdf type %d\n", type);
        goto out;
    }
    ath12k_info(ab, "qmi BDF type %d downloading\n", type);
	
	temp = fw_entry.data;
	remaining = fw_entry.size;

	while (remaining) {
		req->valid = 1;
		req->file_id_valid = 1;
		req->file_id = ab->qmi.target.board_id;
		req->total_size_valid = 1;
		req->total_size = fw_entry.size;
		req->seg_id_valid = 1;
		req->data_valid = 1;
		req->bdf_type = type;
		req->bdf_type_valid = 1;
		req->end_valid = 1;
		req->end = 0;

		if (remaining > QMI_WLANFW_MAX_DATA_SIZE_V01) {
			req->data_len = QMI_WLANFW_MAX_DATA_SIZE_V01;
		} else {
			req->data_len = remaining;
			req->end = 1;
		}

		memcpy(req->data, temp, req->data_len);

		ret = qmi_txn_init(&ab->qmi.handle, &txn,
				   qmi_wlanfw_bdf_download_resp_msg_v01_ei,
				   &resp);
		if (ret < 0)
			goto out_qmi_bdf;

		ret = (int)qmi_send_request(&ab->qmi.handle, &txn,
				       QMI_WLANFW_BDF_DOWNLOAD_REQ_V01,
				       QMI_WLANFW_BDF_DOWNLOAD_REQ_MSG_V01_MAX_LEN,
				       qmi_wlanfw_bdf_download_req_msg_v01_ei, req);
		if (ret < 0) {
			qmi_txn_cancel(&txn);
			goto out_qmi_bdf;
		}
	
		ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
		if (ret < 0)
			goto out_qmi_bdf;

        ath12k_info(ab, "seg id %d len %d result %d error %d\n",
			    req->seg_id, req->data_len,
			    resp.resp.result, resp.resp.error);
		
		if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
			ath12k_warn(ab, "qmi BDF download failed, result: %d, err: %d\n",
				    resp.resp.result, resp.resp.error);
			if (resp.resp.error == QMI_ERR_AUTHENTICATION_FAILED_V01) {
				ret = -EAUTH;
			} else {
				ret = -EINVAL;
			}
			goto out_qmi_bdf;
		}
		remaining -= req->data_len;
		temp += req->data_len;
		req->seg_id++;
	}
	ath12k_info(ab, "qmi BDF type %d downloaded\n", type);

out_qmi_bdf:
	release_firmware(&fw_entry);
out:
	kfree(req);
	return ret;
}

static int ath12k_qmi_m3_load(struct ath12k_base *ab)
{
	struct m3_mem_region *m3_mem = &ab->qmi.m3_mem;
	const u16 *filename = DEFAULT_M3_FILE_NAME;
	struct firmware fw_entry;
	int ret;

	ret = request_firmware_fancily(&fw_entry, filename, ath12k_firmware_metadata_match_target, ab);
	if (ret) {
		ath12k_err(ab, "Failed to load M3 image: %s\n", filename);
		return ret;
	}

	m3_mem->vaddr = dma_alloc_coherent(ab->dev,
					fw_entry.size, &m3_mem->paddr,
					&m3_mem->p_dma_mapping_addr);
	if (!m3_mem->vaddr) {
		ath12k_err(ab, "Failed to allocate memory for M3, size: 0x%x\n",
			    fw_entry.size);
		release_firmware(&fw_entry);
		return -ENOMEM;
	}

	ath12k_info(ab, "memory for M3, size: 0x%x\n", fw_entry.size);
	
	memcpy(m3_mem->vaddr, fw_entry.data, fw_entry.size);
	m3_mem->size = fw_entry.size;
	release_firmware(&fw_entry);

	return 0;
}

static void ath12k_qmi_m3_free(struct ath12k_base *ab)
{
	struct m3_mem_region *m3_mem = &ab->qmi.m3_mem;

	if (!m3_mem->vaddr)
		return;

	dma_free_coherent(ab->dev, m3_mem->size,
			  m3_mem->vaddr, m3_mem->paddr, m3_mem->p_dma_mapping_addr);
	m3_mem->vaddr = NULL;
	m3_mem->size = 0;
}

static int ath12k_qmi_wlanfw_m3_info_send(struct ath12k_base *ab)
{
	struct m3_mem_region *m3_mem = &ab->qmi.m3_mem;
	struct qmi_wlanfw_m3_info_req_msg_v01 req;
	struct qmi_wlanfw_m3_info_resp_msg_v01 resp;
	struct qmi_txn txn = { 0, };
	int ret = 0;

	memset(&req, 0, sizeof(req));
	memset(&resp, 0, sizeof(resp));

	ret = ath12k_qmi_m3_load(ab);
	if (ret) {
		ath12k_err(ab, "failed to load m3 firmware: %d", ret);
		return ret;
	}

	req.addr = m3_mem->paddr;
	req.size = m3_mem->size;

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_m3_info_resp_msg_v01_ei, &resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&ab->qmi.handle, &txn,
			       QMI_WLANFW_M3_INFO_REQ_V01,
			       QMI_WLANFW_M3_INFO_REQ_MSG_V01_MAX_MSG_LEN,
			       qmi_wlanfw_m3_info_req_msg_v01_ei, &req);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send M3 information request, err = %d\n",
			    ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed M3 information request %d\n", ret);
		goto out;
	}

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath12k_warn(ab, "qmi M3 info request failed, result: %d, err: %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		goto out;
	}
out:
	return ret;
}

static int ath12k_qmi_wlanfw_mode_send(struct ath12k_base *ab,
				       u32 mode)
{
	struct qmi_wlanfw_wlan_mode_req_msg_v01 req;
	struct qmi_wlanfw_wlan_mode_resp_msg_v01 resp;
	struct qmi_txn txn = { 0, };
	int ret = 0;

	memset(&req, 0, sizeof(req));
	memset(&resp, 0, sizeof(resp));

	req.mode = mode;
	req.hw_debug_valid = 1;
	req.hw_debug = 0;

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_wlan_mode_resp_msg_v01_ei, &resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&ab->qmi.handle, &txn,
			       QMI_WLANFW_WLAN_MODE_REQ_V01,
			       QMI_WLANFW_WLAN_MODE_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_wlan_mode_req_msg_v01_ei, &req);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send mode request, mode: %d, err = %d\n",
			    mode, ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
	if (ret < 0) {
		if (mode == ATH12K_FIRMWARE_MODE_OFF && ret == -ENETRESET) {
			ath12k_warn(ab, "WLFW service is dis-connected\n");
			return 0;
		}
		ath12k_warn(ab, "qmi failed set mode request, mode: %d, err = %d\n",
			    mode, ret);
		goto out;
	}

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath12k_warn(ab, "Mode request failed, mode: %d, result: %d err: %d\n",
			    mode, resp.resp.result, resp.resp.error);
		if (resp.resp.error == QMI_ERR_AUTHENTICATION_FAILED_V01) {
			ret = -EAUTH;
		} else {
			ret = -EINVAL;
		}
		goto out;
	}

out:
	return ret;
}

static int ath12k_qmi_wlanfw_wlan_cfg_send(struct ath12k_base *ab)
{
	struct qmi_wlanfw_wlan_cfg_req_msg_v01 *req;
	struct qmi_wlanfw_wlan_cfg_resp_msg_v01 resp;
	struct ce_pipe_config *ce_cfg;
	struct service_to_pipe *svc_cfg;
	struct qmi_txn txn = { 0, };
	int ret = 0;
	u32 pipe_num;

	ce_cfg	= (struct ce_pipe_config *)ab->qmi.ce_cfg.tgt_ce;
	svc_cfg	= (struct service_to_pipe *)ab->qmi.ce_cfg.svc_to_ce_map;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	memset(&resp, 0, sizeof(resp));

	req->host_version_valid = 1;
	strlcpy(req->host_version, ATH12K_HOST_VERSION_STRING,
		sizeof(req->host_version));

	req->tgt_cfg_valid = 1;
	/* This is number of CE configs */
	req->tgt_cfg_len = ab->qmi.ce_cfg.tgt_ce_len;
	for (pipe_num = 0; pipe_num < req->tgt_cfg_len ; pipe_num++) {
		req->tgt_cfg[pipe_num].pipe_num = ce_cfg[pipe_num].pipenum;
		req->tgt_cfg[pipe_num].pipe_dir = ce_cfg[pipe_num].pipedir;
		req->tgt_cfg[pipe_num].nentries = ce_cfg[pipe_num].nentries;
		req->tgt_cfg[pipe_num].nbytes_max = ce_cfg[pipe_num].nbytes_max;
		req->tgt_cfg[pipe_num].flags = ce_cfg[pipe_num].flags;
	}

	req->svc_cfg_valid = 1;
	/* This is number of Service/CE configs */
	req->svc_cfg_len = ab->qmi.ce_cfg.svc_to_ce_map_len;
	for (pipe_num = 0; pipe_num < req->svc_cfg_len; pipe_num++) {
		req->svc_cfg[pipe_num].service_id = svc_cfg[pipe_num].service_id;
		req->svc_cfg[pipe_num].pipe_dir = svc_cfg[pipe_num].pipedir;
		req->svc_cfg[pipe_num].pipe_num = svc_cfg[pipe_num].pipenum;
	}

	/* set shadow v3 configuration */
	if (ab->hw_params->supports_shadow_regs) {
		req->shadow_reg_v3_valid = 1;
		req->shadow_reg_v3_len = min_t(u32,
					       ab->qmi.ce_cfg.shadow_reg_v3_len,
					       QMI_WLANFW_MAX_NUM_SHADOW_REG_V3_V01);
		memcpy(&req->shadow_reg_v3, ab->qmi.ce_cfg.shadow_reg_v3,
		       sizeof(u32) * req->shadow_reg_v3_len);
	} else {
		req->shadow_reg_v3_valid = 0;
	}

	ret = qmi_txn_init(&ab->qmi.handle, &txn,
			   qmi_wlanfw_wlan_cfg_resp_msg_v01_ei, &resp);
	if (ret < 0)
		goto out;

	ret = qmi_send_request(&ab->qmi.handle, &txn,
			       QMI_WLANFW_WLAN_CFG_REQ_V01,
			       QMI_WLANFW_WLAN_CFG_REQ_MSG_V01_MAX_LEN,
			       qmi_wlanfw_wlan_cfg_req_msg_v01_ei, req);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send wlan config request, err = %d\n",
			    ret);
		goto out;
	}

	ret = qmi_txn_wait(&txn, msecs_to_jiffies(ATH12K_QMI_WLANFW_TIMEOUT_MS));
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed wlan config request, err = %d\n", ret);
		goto out;
	}

	if (resp.resp.result != QMI_RESULT_SUCCESS_V01) {
		ath12k_warn(ab, "qmi wlan config request failed, result: %d, err: %d\n",
			    resp.resp.result, resp.resp.error);
		ret = -EINVAL;
		goto out;
	}

out:
	kfree(req);
	return ret;
}

void ath12k_qmi_firmware_stop(struct ath12k_base *ab)
{
	int ret;

	ret = ath12k_qmi_wlanfw_mode_send(ab, ATH12K_FIRMWARE_MODE_OFF);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send wlan mode off\n");
		return;
	}
}

int ath12k_qmi_firmware_start(struct ath12k_base *ab,
			      u32 mode)
{
	int ret;
	
	ret = ath12k_qmi_wlanfw_wlan_ini_send(ab, true);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send wlan fw ini:%d\n", ret);
		return ret;
	}

	ret = ath12k_qmi_wlanfw_wlan_cfg_send(ab);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send wlan cfg:%d\n", ret);
		return ret;
	}

	ret = ath12k_qmi_wlanfw_mode_send(ab, mode);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send wlan fw mode:%d\n", ret);
		return ret;
	}

	return 0;
}

static int
ath12k_qmi_driver_event_post(struct ath12k_qmi *qmi,
			     enum ath12k_qmi_event_type type,
			     void *data)
{
	struct ath12k_qmi_driver_event *event;

	event = kzalloc(sizeof(*event), GFP_ATOMIC);
	if (!event)
		return -ENOMEM;

	event->type = type;
	event->data = data;

	spin_lock(&qmi->event_lock);
	list_add_tail(&event->list, &qmi->event_list);
	spin_unlock(&qmi->event_lock);

	//queue_work(qmi->event_wq, &qmi->event_work);
	schedule_work(&qmi->event_work);

	return 0;
}

static int ath12k_qmi_event_server_arrive(struct ath12k_qmi *qmi)
{
	struct ath12k_base *ab = qmi->ab;
	int ret;

	ret = ath12k_qmi_fw_ind_register_send(ab);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send FW indication QMI:%d\n", ret);
		return ret;
	}

	ret = ath12k_qmi_host_cap_send(ab);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send host cap QMI:%d\n", ret);
		return ret;
	}

	return ret;
}

static int ath12k_qmi_event_mem_request(struct ath12k_qmi *qmi)
{
	struct ath12k_base *ab = qmi->ab;
	int ret;

	ret = ath12k_qmi_respond_fw_mem_request(ab);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to respond fw mem req:%d\n", ret);
		return ret;
	}

	return ret;
}

static int ath12k_qmi_event_load_bdf(struct ath12k_qmi *qmi)
{
	struct ath12k_base *ab = qmi->ab;
	int ret;

	ret = ath12k_qmi_request_target_cap(ab);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to req target capabilities:%d\n", ret);
		return ret;
	}

	ret = ath12k_qmi_load_bdf_qmi(ab, ATH12K_QMI_BDF_TYPE_REGDB);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to load regdb file:%d\n", ret);
		return ret;
	}

	ret = ath12k_qmi_load_bdf_qmi(ab, ATH12K_QMI_BDF_TYPE_ELF);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to load board data file:%d\n", ret);
		return ret;
	}

	ret = ath12k_qmi_wlanfw_m3_info_send(ab);
	if (ret < 0) {
		ath12k_warn(ab, "qmi failed to send m3 info req:%d\n", ret);
		return ret;
	}

	/* TODO: QDSS should be removed after WCN7850 firmware is fixed */
	ret = ath12k_qmi_send_qdss_config(ab);
	if (ret < 0) {
		ath12k_warn(ab, "Failed to download QDSS config to FW: %d\n", ret);
		return ret;
	}

	return 0;
}

static void ath12k_qmi_msg_mem_request_cb(struct qmi_handle *qmi_hdl,
					  struct qmi_txn *txn,
					  const void *data)
{
	struct ath12k_qmi *qmi = container_of(qmi_hdl, struct ath12k_qmi, handle);
	struct ath12k_base *ab = qmi->ab;
	const struct qmi_wlanfw_request_mem_ind_msg_v01 *msg = data;
	u32 i;
	int ret;

	ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi firmware request memory request\n");

	if (msg->mem_seg_len == 0 ||
	    msg->mem_seg_len > ATH12K_QMI_WLANFW_MAX_NUM_MEM_SEG_V01)
		ath12k_warn(ab, "Invalid memory segment length: %u\n",
			    msg->mem_seg_len);

	ab->qmi.mem_seg_count = msg->mem_seg_len;

	for (i = 0; i < qmi->mem_seg_count ; i++) {
		ab->qmi.target_mem[i].type = msg->mem_seg[i].type;
		ab->qmi.target_mem[i].size = msg->mem_seg[i].size;
		ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi mem seg type %d size %d\n",
			   msg->mem_seg[i].type, msg->mem_seg[i].size);
	}

	ret = ath12k_qmi_alloc_target_mem_chunk(ab);
	if (ret) {
		ath12k_warn(ab, "qmi failed to alloc target memory: %d\n",
			    ret);
		return;
	}

	ath12k_qmi_driver_event_post(qmi, ATH12K_QMI_EVENT_REQUEST_MEM, NULL);
}

static void ath12k_qmi_msg_mem_ready_cb(struct qmi_handle *qmi_hdl,
					struct qmi_txn *txn,
					const void *decoded)
{
	struct ath12k_qmi *qmi = container_of(qmi_hdl, struct ath12k_qmi, handle);
	struct ath12k_base *ab = qmi->ab;

	ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi firmware memory ready indication\n");
	ath12k_qmi_driver_event_post(qmi, ATH12K_QMI_EVENT_FW_MEM_READY, NULL);
}

static void ath12k_qmi_msg_fw_ready_cb(struct qmi_handle *qmi_hdl,
				       struct qmi_txn *txn,
				       const void *decoded)
{
	struct ath12k_qmi *qmi = container_of(qmi_hdl, struct ath12k_qmi, handle);
	struct ath12k_base *ab = qmi->ab;

	ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi firmware ready\n");
	ath12k_qmi_driver_event_post(qmi, ATH12K_QMI_EVENT_FW_READY, NULL);
}

static const struct qmi_msg_handler ath12k_qmi_msg_handlers[] = {
	{
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_REQUEST_MEM_IND_V01,
		.ei = qmi_wlanfw_request_mem_ind_msg_v01_ei,
		.decoded_size = sizeof(struct qmi_wlanfw_request_mem_ind_msg_v01),
		.fn = ath12k_qmi_msg_mem_request_cb,
	},
	{
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_FW_MEM_READY_IND_V01,
		.ei = qmi_wlanfw_mem_ready_ind_msg_v01_ei,
		.decoded_size = sizeof(struct qmi_wlanfw_fw_mem_ready_ind_msg_v01),
		.fn = ath12k_qmi_msg_mem_ready_cb,
	},
	{
		.type = QMI_INDICATION,
		.msg_id = QMI_WLFW_FW_READY_IND_V01,
		.ei = qmi_wlanfw_fw_ready_ind_msg_v01_ei,
		.decoded_size = sizeof(struct qmi_wlanfw_fw_ready_ind_msg_v01),
		.fn = ath12k_qmi_msg_fw_ready_cb,
	},
};

static int ath12k_qmi_ops_new_server(struct qmi_handle *qmi_hdl,
				     struct qmi_service *service)
{
	struct ath12k_qmi *qmi = container_of(qmi_hdl, struct ath12k_qmi, handle);
	struct ath12k_base *ab = qmi->ab;
	
	if((service->service != ATH12K_QMI_WLFW_SERVICE_ID_V01) ||
		(service->version != ATH12K_QMI_WLFW_SERVICE_VERS_V01)) {
		ath12k_info(ab, "qmi wifi fw service not match: fw service: %u, version: %u,\
				expected service: %u, version: %u\n", service->service, service->version,
				ATH12K_QMI_WLFW_SERVICE_ID_V01, ATH12K_QMI_WLFW_SERVICE_VERS_V01);
		return 0;
	}

	qmi->handle.server.addr.proc_id = service->node;
	qmi->handle.server.addr.port_id = service->port;

	ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi wifi fw qmi service connected\n");
	ath12k_qmi_driver_event_post(qmi, ATH12K_QMI_EVENT_SERVER_ARRIVE, NULL);

	return 0;
}

static void ath12k_qmi_ops_del_server(struct qmi_handle *qmi_hdl,
				      struct qmi_service *service)
{
	struct ath12k_qmi *qmi = container_of(qmi_hdl, struct ath12k_qmi, handle);
	struct ath12k_base *ab = qmi->ab;

	ath12k_dbg(ab, ATH12K_DBG_QMI, "qmi wifi fw del server\n");
	ath12k_qmi_driver_event_post(qmi, ATH12K_QMI_EVENT_SERVER_EXIT, NULL);
}

static const struct qmi_ops ath12k_qmi_ops = {
	.new_server = ath12k_qmi_ops_new_server,
	.del_server = ath12k_qmi_ops_del_server,
};

static void ath12k_qmi_driver_event_work(void *context)
{
	struct ath12k_qmi *qmi = (struct ath12k_qmi *)context;
	struct ath12k_qmi_driver_event *event;
	struct ath12k_base *ab = qmi->ab;
	int ret;

	spin_lock(&qmi->event_lock);
	while (!list_is_empty(&qmi->event_list)) {
		event = BASE_CR(list_first_entry(&qmi->event_list),
					 struct ath12k_qmi_driver_event, list);
		
		list_del(&event->list);
		spin_unlock(&qmi->event_lock);

		if (test_bit(ATH12K_FLAG_UNREGISTERING, &ab->dev_flags))
			return;
		switch (event->type) {
		case ATH12K_QMI_EVENT_SERVER_ARRIVE:
			ret = ath12k_qmi_event_server_arrive(qmi);
			if (ret < 0)
				set_bit(ATH12K_FLAG_QMI_FAIL, &ab->dev_flags);
			break;
		case ATH12K_QMI_EVENT_SERVER_EXIT:
			set_bit(ATH12K_FLAG_CRASH_FLUSH, &ab->dev_flags);
			set_bit(ATH12K_FLAG_RECOVERY, &ab->dev_flags);
			break;
		case ATH12K_QMI_EVENT_REQUEST_MEM:
			ret = ath12k_qmi_event_mem_request(qmi);
			if (ret < 0)
				set_bit(ATH12K_FLAG_QMI_FAIL, &ab->dev_flags);
			break;
		case ATH12K_QMI_EVENT_FW_MEM_READY:
			ret = ath12k_qmi_event_load_bdf(qmi);
			if (ret < 0) {
				set_bit(ATH12K_FLAG_QMI_FAIL, &ab->dev_flags);
#if SUPPORT_SECURITY_BOOT
				ath12k_err(ab, "Bdf/Regdb load fail, will try to reload again");
				schedule_work(&ab->reset_work);
#endif
			}
			break;
		case ATH12K_QMI_EVENT_FW_READY:
			clear_bit(ATH12K_FLAG_QMI_FAIL, &ab->dev_flags);
			#if 0
			if (test_bit(ATH12K_FLAG_REGISTERED, &ab->dev_flags)) {
				ath12k_hal_dump_srng_stats(ab);
				schedule_work(&ab->restart_work);
				break;
			}
			#endif
			clear_bit(ATH12K_FLAG_CRASH_FLUSH, &ab->dev_flags);
			clear_bit(ATH12K_FLAG_RECOVERY, &ab->dev_flags);
			ret = ath12k_core_qmi_firmware_ready(ab);
			if (ret < 0) {
				set_bit(ATH12K_FLAG_QMI_FAIL, &ab->dev_flags);
#if SUPPORT_SECURITY_BOOT
				ath12k_err(ab, "M3 load fail, will try to reload again");
				schedule_work(&ab->reset_work);
#endif
			}
			//set_bit(ATH12K_FLAG_REGISTERED, &ab->dev_flags);
			break;
		default:
			ath12k_warn(ab, "invalid event type: %d", event->type);
			break;
		}
		kfree(event);
		spin_lock(&qmi->event_lock);
	}
	spin_unlock(&qmi->event_lock);

}

int ath12k_qmi_init_service(struct ath12k_base *ab)
{
	int ret;

	memset(&ab->qmi.target, 0, sizeof(struct target_info));
	memset(&ab->qmi.target_mem, 0, sizeof(struct target_mem_chunk));
	ab->qmi.ab = ab;

	ab->qmi.target_mem_mode = ATH12K_QMI_TARGET_MEM_MODE_DEFAULT;
	ret = qmi_handle_init(&ab->qmi.handle, ATH12K_QMI_RESP_LEN_MAX,
			      &ath12k_qmi_ops, ath12k_qmi_msg_handlers);
	if (ret < 0) {
		ath12k_warn(ab, "failed to initialize qmi handle\n");
		return ret;
	}

#if 0
	ab->qmi.event_wq = alloc_workqueue("ath12k_qmi_driver_event",
					   WQ_UNBOUND, 1);
	if (!ab->qmi.event_wq) {
		ath12k_err(ab, "failed to allocate workqueue\n");
		return -EFAULT;
	}
#endif
	
	list_init_head(&ab->qmi.event_list);	
	spin_lock_init(&ab->qmi.event_lock);
	init_work(&ab->qmi.event_work, ath12k_qmi_driver_event_work, &ab->qmi);

	ret = qmi_add_lookup(&ab->qmi.handle, ATH12K_QMI_WLFW_SERVICE_ID_V01,
			     ATH12K_QMI_WLFW_SERVICE_VERS_V01,
			     ab->qmi.service_ins_id);
	if (ret < 0) {
		ath12k_warn(ab, "failed to add qmi lookup\n");
		//destroy_workqueue(ab->qmi.event_wq);
		return ret;
	}

	return ret;
}

void ath12k_qmi_deinit_service(struct ath12k_base *ab)
{
	qmi_handle_release(&ab->qmi.handle);
	cancel_work_sync(&ab->qmi.event_work);
	//destroy_workqueue(ab->qmi.event_wq);
	ath12k_qmi_m3_free(ab);
	ath12k_qmi_free_target_mem_chunk(ab);
}

void ath12k_qmi_free_resource(struct ath12k_base *ab)
{
	ath12k_qmi_free_target_mem_chunk(ab);
	ath12k_qmi_m3_free(ab);
}

