/*
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/* SPDX-License-Identifier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#ifndef ATH11K_HW_H
#define ATH11K_HW_H

#include "wmi.h"
#include "rx_desc.h"

/* Target configuration defines */

/* Num VDEVS per radio */
#define TARGET_NUM_VDEVS	(16 + 1)

#define TARGET_NUM_PEERS_PDEV	(512 + TARGET_NUM_VDEVS)

/* Num of peers for Single Radio mode */
#define TARGET_NUM_PEERS_SINGLE		(TARGET_NUM_PEERS_PDEV)

/* Num of peers for DBS */
#define TARGET_NUM_PEERS_DBS		(2 * TARGET_NUM_PEERS_PDEV)

/* Num of peers for DBS_SBS */
#define TARGET_NUM_PEERS_DBS_SBS	(3 * TARGET_NUM_PEERS_PDEV)

/* Max num of stations (per radio) */
#define TARGET_NUM_STATIONS	512

#define TARGET_NUM_PEERS(x)	TARGET_NUM_PEERS_##x
#define TARGET_NUM_PEER_KEYS	2
#define TARGET_NUM_TIDS(x)	(2 * TARGET_NUM_PEERS(x) + \
				 4 * TARGET_NUM_VDEVS + 8)

#define TARGET_AST_SKID_LIMIT	16
#define TARGET_NUM_OFFLD_PEERS	4
#define TARGET_NUM_OFFLD_REORDER_BUFFS 4

#define TARGET_TX_CHAIN_MASK	(BIT(0) | BIT(1) | BIT(2) | BIT(4))
#define TARGET_RX_CHAIN_MASK	(BIT(0) | BIT(1) | BIT(2) | BIT(4))
#define TARGET_RX_TIMEOUT_LO_PRI	100
#define TARGET_RX_TIMEOUT_HI_PRI	40

#define TARGET_DECAP_MODE_RAW		0
#define TARGET_DECAP_MODE_NATIVE_WIFI	1
#define TARGET_DECAP_MODE_ETH		2

#define TARGET_SCAN_MAX_PENDING_REQS	4
#define TARGET_BMISS_OFFLOAD_MAX_VDEV	3
#define TARGET_ROAM_OFFLOAD_MAX_VDEV	3
#define TARGET_ROAM_OFFLOAD_MAX_AP_PROFILES	8
#define TARGET_GTK_OFFLOAD_MAX_VDEV	3
#define TARGET_NUM_MCAST_GROUPS		12
#define TARGET_NUM_MCAST_TABLE_ELEMS	64
#define TARGET_MCAST2UCAST_MODE		2
#define TARGET_TX_DBG_LOG_SIZE		1024
#define TARGET_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK 1
#define TARGET_VOW_CONFIG		0
#define TARGET_NUM_MSDU_DESC		(2500)
#define TARGET_MAX_FRAG_ENTRIES		6
#define TARGET_MAX_BCN_OFFLD		16
#define TARGET_NUM_WDS_ENTRIES		32
#define TARGET_DMA_BURST_SIZE		1
#define TARGET_RX_BATCHMODE		1

#define ATH11K_HW_MAX_QUEUES		4

#define ATH11k_HW_RATECODE_CCK_SHORT_PREAM_MASK  0x4

#define ATH11K_FW_DIR			"ath11k"

/* IPQ8074 definitions */
#define IPQ8074_FW_DIR			"IPQ8074"
#define IPQ8074_MAX_BOARD_DATA_SZ	(256 * 1024)
#define IPQ8074_MAX_CAL_DATA_SZ		IPQ8074_MAX_BOARD_DATA_SZ

#define ATH11K_BOARD_MAGIC		"QCA-ATH11K-BOARD"
#define ATH11K_BOARD_API2_FILE		"board-2.bin"
#define ATH11K_DEFAULT_BOARD_FILE	"bdwlan.bin"
#define ATH11K_DEFAULT_CAL_FILE		"caldata.bin"

/* Save the Sram into sram.bin*/
#define ATH11K_SRAM_DUP_FILE_NAME	L"sram.bin"
#define FW_SRAM_START_QCA6390   0x01400000
#define FW_SRAM_END_QCA6390     0x0171ffff
#define FW_SRAM_START_QCA6490   0x01400000
#define FW_SRAM_END_QCA6490		0x0177ffff

#define MISC_CAPS_BAND_TO_MAC           BIT(0)
#define MISC_CAPS_HOST2FW_RXBUF_RING    BIT(1)
#define MISC_CAPS_V2_MAP                BIT(2)
#define MISC_CAPS_TCL_0_ONLY            BIT(3)
#define MISC_CAPS_IDLE_PS_SUPP          BIT(4)

enum ath11k_hw_rate_cck {
	ATH11K_HW_RATE_CCK_LP_11M = 0,
	ATH11K_HW_RATE_CCK_LP_5_5M,
	ATH11K_HW_RATE_CCK_LP_2M,
	ATH11K_HW_RATE_CCK_LP_1M,
	ATH11K_HW_RATE_CCK_SP_11M,
	ATH11K_HW_RATE_CCK_SP_5_5M,
	ATH11K_HW_RATE_CCK_SP_2M,
};

enum ath11k_hw_rate_ofdm {
	ATH11K_HW_RATE_OFDM_48M = 0,
	ATH11K_HW_RATE_OFDM_24M,
	ATH11K_HW_RATE_OFDM_12M,
	ATH11K_HW_RATE_OFDM_6M,
	ATH11K_HW_RATE_OFDM_54M,
	ATH11K_HW_RATE_OFDM_36M,
	ATH11K_HW_RATE_OFDM_18M,
	ATH11K_HW_RATE_OFDM_9M,
};

enum ath11k_bus {
	ATH11K_BUS_AHB,
	ATH11K_BUS_PCI,
};

struct ath11k_hw_srng_params {
	u32 tcl_data_ring_size;
	u32 tx_comp_ring_size;
	u32 reo_dst_ring_size;
	u32 num_clients_max;
	u32 scaler;
};

struct ath11k_hw_misc_regs {
	u32 gcc_pcie_hot_rst;
	u32 gcc_pcie_hot_rst_val;
};

struct ath11k_hw_params {
	const char *name;
	u16 dev_id;
	struct {
		const char *dir;
		size_t board_size;
		size_t cal_size;
	} fw;
	bool single_pdev_only;
	const struct ath11k_hw_ops *hw_ops;
	
	const struct ath11k_hw_regs *regs;
	const struct ce_attr *host_ce_config;
	u32 ce_count;
	const struct ce_pipe_config *target_ce_config;
	u32 target_ce_count;
	const struct service_to_pipe *svc_to_ce_map;
	u32 svc_to_ce_map_len;
	const struct ath11k_hw_values *hw_values;
	
	const struct ath11k_hw_srng_params *srng_params;
	const struct ath11k_hw_misc_regs *misc_regs;
	bool vdev_start_delay;
	bool disable_pktlog;
	bool channel_num_war;
	bool band_2g_fake;
	bool v2_map_support;
	bool host2fw_rxbuf_ring;
	u32 misc_caps;
	bool rxdma1_enable;
	//int num_rxmda_per_pdev;
	bool cut_off_power;
	u32  hal_desc_sz;
	u32  ring_hmap;
	bool fw_wmi_diag_event;
	u32 fw_sram_start;
	u32 fw_sram_end;
	u32 rddm_size;
};

/* Defines needed for Rx descriptor abstraction */
struct ath11k_hw_ops {
	u8 (*get_hw_mac_from_pdev_id)(int pdev_id);
	void (*wmi_init_config)(struct ath11k_base *ab, struct target_resource_config *config);
	int (*mac_id_to_pdev_id)(struct ath11k_hw_params *hw, int mac_id);
	int (*mac_id_to_srng_id)(struct ath11k_hw_params *hw, int mac_id);
	u8* (*rxdesc_80211_hdr)(struct hal_rx_desc *desc);
	enum hal_encrypt_type (*rxdesc_mpdu_start_enctype)(struct hal_rx_desc *desc);
	u8 (*rxdesc_msdu_start_decap_type)(struct hal_rx_desc *desc);
	u8 (*rxdesc_msdu_start_mesh_ctl_present)(struct hal_rx_desc *desc);
	bool (*rxdesc_mpdu_start_seq_ctrl_valid)(struct hal_rx_desc *desc);
	bool (*rxdesc_mpdu_start_fc_valid)(struct hal_rx_desc *desc);
	u16 (*rxdesc_mpdu_start_seq_no)(struct hal_rx_desc *desc);
	u8* (*rxdesc_mpdu_start_addr2)(struct hal_rx_desc *desc);
	bool (*rxdesc_attn_msdu_done)(struct hal_rx_desc *desc);
	bool (*rxdesc_attn_l4_cksum_fail)(struct hal_rx_desc *desc);
	bool (*rxdesc_attn_ip_cksum_fail)(struct hal_rx_desc *desc);
	bool (*rxdesc_attn_is_decrypted)(struct hal_rx_desc *desc);
	struct rx_attention* (*rxdesc_get_attn)(struct hal_rx_desc *desc);
	u16 (*rxdesc_msdu_start_msdu_len)(struct hal_rx_desc *desc);
	u8 (*rxdesc_msdu_start_sgi)(struct hal_rx_desc *desc);
	u8 (*rxdesc_msdu_start_rate_mcs)(struct hal_rx_desc *desc);
	u8 (*rxdesc_msdu_start_rx_bw)(struct hal_rx_desc *desc);
	u32 (*rxdesc_msdu_start_freq)(struct hal_rx_desc *desc);
	u8 (*rxdesc_msdu_start_pkt_type)(struct hal_rx_desc *desc);
	u8 (*rxdesc_msdu_start_nss)(struct hal_rx_desc *desc);
	u8 (*rxdesc_mpdu_start_tid)(struct hal_rx_desc *desc);
	u16 (*rxdesc_mpdu_start_peer_id)(struct hal_rx_desc *desc);
	u8 (*rxdesc_msdu_end_l3pad)(struct hal_rx_desc *desc);
	bool (*rxdesc_msdu_end_first_msdu)(struct hal_rx_desc *desv);
	bool (*rxdesc_msdu_end_last_msdu)(struct hal_rx_desc *desv);
	void (*rxdesc_end_tlv_copy)(struct hal_rx_desc *fdesc, struct hal_rx_desc *ldesc);
	u32 (*rxdesc_get_mpdulen_err)(struct hal_rx_desc *desc);
	u32 (*rxdesc_get_decap_format)(struct hal_rx_desc *desc);
	u8* (*rxdesc_get_80211hdr)(struct hal_rx_desc *desc);
	bool (*rxdesc_mpdu_valid)(struct hal_rx_desc *desc);
	u32 (*rxdesc_get_ppduid)(struct hal_rx_desc *desc);
	u32* (*rxdesc_msdu_start_msdu_len_offset)(struct hal_rx_desc *desc);
	void (*reo_setup)(struct ath11k_base *ab, u32 hmap);
	u16 (*mpdu_info_get_peerid)(u8 *tlv_data);
};

struct ath11k_fw_ie {
	__le32 id;
	__le32 len;
	u8 data[0];
};

enum ath11k_bd_ie_board_type {
	ATH11K_BD_IE_BOARD_NAME = 0,
	ATH11K_BD_IE_BOARD_DATA = 1,
};

enum ath11k_bd_ie_type {
	/* contains sub IEs of enum ath11k_bd_ie_board_type */
	ATH11K_BD_IE_BOARD = 0,
	ATH11K_BD_IE_BOARD_EXT = 1,
};

struct ath11k_hw_regs {
	u32 hal_tcl1_ring_base_lsb;
	u32 hal_tcl1_ring_base_msb;
	u32 hal_tcl1_ring_id;
	u32 hal_tcl1_ring_misc;
	u32 hal_tcl1_ring_tp_addr_lsb;
	u32 hal_tcl1_ring_tp_addr_msb;
	u32 hal_tcl1_ring_consumer_int_setup_ix0;
	u32 hal_tcl1_ring_consumer_int_setup_ix1;
	u32 hal_tcl1_ring_msi1_base_lsb;
	u32 hal_tcl1_ring_msi1_base_msb;
	u32 hal_tcl1_ring_msi1_data;
	u32 hal_tcl2_ring_base_lsb;
	u32 hal_tcl_ring_base_lsb;

	u32 hal_tcl_status_ring_base_lsb;

	u32 hal_reo1_ring_base_lsb;
	u32 hal_reo1_ring_base_msb;
	u32 hal_reo1_ring_id;
	u32 hal_reo1_ring_misc;
	u32 hal_reo1_ring_hp_addr_lsb;
	u32 hal_reo1_ring_hp_addr_msb;
	u32 hal_reo1_ring_producer_int_setup;
	u32 hal_reo1_ring_msi1_base_lsb;
	u32 hal_reo1_ring_msi1_base_msb;
	u32 hal_reo1_ring_msi1_data;
	u32 hal_reo2_ring_base_lsb;
	u32 hal_reo1_aging_thresh_ix_0;
	u32 hal_reo1_aging_thresh_ix_1;
	u32 hal_reo1_aging_thresh_ix_2;
	u32 hal_reo1_aging_thresh_ix_3;

	u32 hal_reo1_ring_hp;
	u32 hal_reo1_ring_tp;
	u32 hal_reo2_ring_hp;

	u32 hal_reo_tcl_ring_base_lsb;
	u32 hal_reo_tcl_ring_hp;

	u32 hal_reo_status_ring_base_lsb;
	u32 hal_reo_status_hp;

	u32 hal_ce0_src_reg_base;
	u32 hal_ce1_src_reg_base;
	u32 hal_ce0_dst_reg_base;
	u32 hal_ce1_dst_reg_base;

	u32 hal_ce_host_ie;
	u32 hal_ce_host_ie2;

	u32 hal_wbm_idle_link_ring_base_lsb;
	u32 hal_wbm_idle_link_ring_misc_addr;

	u32 hal_wbm_release_ring_base_lsb;
	u32 hal_wbm0_release_ring_base_lsb;
	u32 hal_wbm1_release_ring_base_lsb;
};

extern const struct ath11k_hw_regs ipa8074_regs;
extern const struct ath11k_hw_regs qca6x90_regs;

extern const struct ath11k_hw_ops qca6390_ops;
extern const struct ath11k_hw_ops qca6490_ops;

extern const struct ath11k_hw_regs qca6390_regs;
extern const struct ath11k_hw_regs qca6490_regs;
extern const struct ath11k_hw_values qca6x90_values;

extern const struct ath11k_hw_srng_params ath11k_hw_srng_qca6x90;
extern const struct ath11k_hw_misc_regs qca6390_misc_regs;
extern const struct ath11k_hw_misc_regs qca6490_misc_regs;

struct ath11k_hw_values {
	u32 rfkill_pin;
	u32 rfkill_cfg;
	bool rfkill_on_level;
};

extern const struct ath11k_hw_srng_params ath11k_hw_srng_qca6x90;

#endif
