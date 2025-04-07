// SPDX-License-Identifier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#include "hw.h"
#include "core.h"
#include "hif.h"

static void ath11k_init_wmi_config_qca6x90(struct ath11k_base *ab,
					   struct target_resource_config *config)
{
	config->num_vdevs = 4;
	config->num_peers = 16;
	config->num_tids = 32;

	config->num_offload_peers = 3;
	config->num_offload_reorder_buffs = 3;
	config->num_peer_keys = TARGET_NUM_PEER_KEYS;
	config->ast_skid_limit = TARGET_AST_SKID_LIMIT;
	config->tx_chain_mask = (1 << ab->target_caps.num_rf_chains) - 1;
	config->rx_chain_mask = (1 << ab->target_caps.num_rf_chains) - 1;
	config->rx_timeout_pri[0] = TARGET_RX_TIMEOUT_LO_PRI;
	config->rx_timeout_pri[1] = TARGET_RX_TIMEOUT_LO_PRI;
	config->rx_timeout_pri[2] = TARGET_RX_TIMEOUT_LO_PRI;
	config->rx_timeout_pri[3] = TARGET_RX_TIMEOUT_HI_PRI;
	config->rx_decap_mode = TARGET_DECAP_MODE_ETH;
	config->scan_max_pending_req = TARGET_SCAN_MAX_PENDING_REQS;
	config->bmiss_offload_max_vdev = TARGET_BMISS_OFFLOAD_MAX_VDEV;
	config->roam_offload_max_vdev = TARGET_ROAM_OFFLOAD_MAX_VDEV;
	config->roam_offload_max_ap_profiles = TARGET_ROAM_OFFLOAD_MAX_AP_PROFILES;
	config->num_mcast_groups = 0;
	config->num_mcast_table_elems = 0;
	config->mcast2ucast_mode = 0;
	config->tx_dbg_log_size = TARGET_TX_DBG_LOG_SIZE;
	config->num_wds_entries = 0;
	config->dma_burst_size = 0;
	config->rx_skip_defrag_timeout_dup_detection_check = 0;
	config->vow_config = TARGET_VOW_CONFIG;
	config->gtk_offload_max_vdev = 2;
	config->num_msdu_desc = 0x400;
	config->beacon_tx_offload_max_vdev = 2;
	config->rx_batchmode = TARGET_RX_BATCHMODE;

	config->peer_map_unmap_v2_support = 0;
	config->use_pdev_id = 1;
	config->max_frag_entries = 0xa;
	config->num_tdls_vdevs = 0x1;
	config->num_tdls_conn_table_entries = 8;
	config->beacon_tx_offload_max_vdev = 0x2;
	config->num_multicast_filter_entries = 0x20;
	config->num_wow_filters = 0x16;
	config->num_keep_alive_pattern = 0x1;
	config->num_keep_alive_pattern = 0;
}

static u8 *ath11k_hw_rxdesc_80211_hdr_qca6390(struct hal_rx_desc *desc)
{
	return desc->u.qca6390.hdr_status;
}

static u8 *ath11k_hw_rxdesc_80211_hdr_qca6490(struct hal_rx_desc *desc)
{
	return desc->u.qca6490.hdr_status;
}

static enum hal_encrypt_type ath11k_hw_rxdesc_mpdu_start_enctype_qca6390(struct hal_rx_desc *desc)
{
	if (!(__le32_to_cpu(desc->u.qca6390.mpdu_start.info1) &
	    RX_MPDU_START_INFO1_ENCRYPT_INFO_VALID))
		return HAL_ENCRYPT_TYPE_OPEN;

	return FIELD_GET(RX_MPDU_START_INFO2_ENC_TYPE,
			 __le32_to_cpu(desc->u.qca6390.mpdu_start.info2));
}

static enum hal_encrypt_type ath11k_hw_rxdesc_mpdu_start_enctype_qca6490(struct hal_rx_desc *desc)
{
	if (!(__le32_to_cpu(desc->u.qca6490.mpdu_start.info1) &
	    RX_MPDU_START_INFO1_ENCRYPT_INFO_VALID))
		return HAL_ENCRYPT_TYPE_OPEN;

	return FIELD_GET(RX_MPDU_START_INFO2_ENC_TYPE,
			 __le32_to_cpu(desc->u.qca6490.mpdu_start.info2));
}

static u8 ath11k_hw_rxdesc_msdu_start_decap_type_qca6390(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO2_DECAP_FORMAT,
			 __le32_to_cpu(desc->u.qca6390.msdu_start.info2));
}

static u8 ath11k_hw_rxdesc_msdu_start_decap_type_qca6490(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO2_DECAP_FORMAT,
			 __le32_to_cpu(desc->u.qca6490.msdu_start.info2));
}

static u8 ath11k_hw_rxdesc_msdu_start_mesh_ctl_present_qca6390(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO2_MESH_CTRL_PRESENT,
			 __le32_to_cpu(desc->u.qca6390.msdu_start.info2));
}

static u8 ath11k_hw_rxdesc_msdu_start_mesh_ctl_present_qca6490(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO2_MESH_CTRL_PRESENT,
			 __le32_to_cpu(desc->u.qca6490.msdu_start.info2));
}

static bool ath11k_hw_rxdesc_mpdu_start_seq_ctrl_valid_qca6390(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_MPDU_START_INFO1_MPDU_SEQ_CTRL_VALID,
			   __le32_to_cpu(desc->u.qca6390.mpdu_start.info1));
}

static bool ath11k_hw_rxdesc_mpdu_start_seq_ctrl_valid_qca6490(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_MPDU_START_INFO1_MPDU_SEQ_CTRL_VALID,
			   __le32_to_cpu(desc->u.qca6490.mpdu_start.info1));
}

static bool ath11k_hw_rxdesc_mpdu_start_fc_valid_qca6390(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_MPDU_START_INFO1_MPDU_FCTRL_VALID,
			   __le32_to_cpu(desc->u.qca6390.mpdu_start.info1));
}

static bool ath11k_hw_rxdesc_mpdu_start_fc_valid_qca6490(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_MPDU_START_INFO1_MPDU_FCTRL_VALID,
			   __le32_to_cpu(desc->u.qca6490.mpdu_start.info1));
}

static u16 ath11k_hw_rxdesc_mpdu_start_seq_no_qca6390(struct hal_rx_desc *desc)
{
	return (u16)FIELD_GET(RX_MPDU_START_INFO1_MPDU_SEQ_NUM,
			 __le32_to_cpu(desc->u.qca6390.mpdu_start.info1));
}

static u16 ath11k_hw_rxdesc_mpdu_start_seq_no_qca6490(struct hal_rx_desc *desc)
{
	return (u16)FIELD_GET(RX_MPDU_START_INFO1_MPDU_SEQ_NUM,
			 __le32_to_cpu(desc->u.qca6490.mpdu_start.info1));
}

static u8 *ath11k_hw_rxdesc_mpdu_start_addr2_qca6390(struct hal_rx_desc *desc) 
{	
	if (!desc ||
	    !(desc->u.qca6390.mpdu_start.info1 & RX_MPDU_START_INFO1_MAC_ADDR2_VALID)) {
		return NULL;
	}

	return desc->u.qca6390.mpdu_start.addr2;
}

static u8 *ath11k_hw_rxdesc_mpdu_start_addr2_qca6490(struct hal_rx_desc *desc) 
{	
	if (!desc ||
	    !(desc->u.qca6490.mpdu_start.info1 & RX_MPDU_START_INFO1_MAC_ADDR2_VALID)) {
		return NULL;
	}

	return desc->u.qca6490.mpdu_start.addr2;
}

static bool ath11k_hw_rxdesc_attn_msdu_done_qca6390(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_ATTENTION_INFO2_MSDU_DONE,
			   __le32_to_cpu(desc->u.qca6390.attention.info2));
}

static bool ath11k_hw_rxdesc_attn_msdu_done_qca6490(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_ATTENTION_INFO2_MSDU_DONE,
			   __le32_to_cpu(desc->u.qca6490.attention.info2));
}

static bool ath11k_hw_rxdesc_attn_l4_cksum_fail_qca6390(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_ATTENTION_INFO1_TCP_UDP_CKSUM_FAIL,
			   __le32_to_cpu(desc->u.qca6390.attention.info1));
}

static bool ath11k_hw_rxdesc_attn_l4_cksum_fail_qca6490(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_ATTENTION_INFO1_TCP_UDP_CKSUM_FAIL,
			   __le32_to_cpu(desc->u.qca6490.attention.info1));
}

static bool ath11k_hw_rxdesc_attn_ip_cksum_fail_qca6390(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_ATTENTION_INFO1_IP_CKSUM_FAIL,
			   __le32_to_cpu(desc->u.qca6390.attention.info1));
}

static bool ath11k_hw_rxdesc_attn_ip_cksum_fail_qca6490(struct hal_rx_desc *desc)
{
	return !!FIELD_GET(RX_ATTENTION_INFO1_IP_CKSUM_FAIL,
			   __le32_to_cpu(desc->u.qca6490.attention.info1));
}

static bool ath11k_hw_rxdesc_attn_is_decrypted_qca6390(struct hal_rx_desc *desc)
{
	return (FIELD_GET(RX_ATTENTION_INFO2_DCRYPT_STATUS_CODE,
			  __le32_to_cpu(desc->u.qca6390.attention.info2)) ==
		RX_DESC_DECRYPT_STATUS_CODE_OK);
}

static bool ath11k_hw_rxdesc_attn_is_decrypted_qca6490(struct hal_rx_desc *desc)
{
	return (FIELD_GET(RX_ATTENTION_INFO2_DCRYPT_STATUS_CODE,
			  __le32_to_cpu(desc->u.qca6490.attention.info2)) ==
		RX_DESC_DECRYPT_STATUS_CODE_OK);
}

static struct rx_attention *ath11k_hw_rxdesc_get_attn_qca6390(struct hal_rx_desc *desc)
{
	return &desc->u.qca6390.attention;
}

static struct rx_attention *ath11k_hw_rxdesc_get_attn_qca6490(struct hal_rx_desc *desc)
{
	return &desc->u.qca6490.attention;
}

static u16 ath11k_hw_rxdesc_msdu_start_msdu_len_qca6390(struct hal_rx_desc *desc)
{
	return FIELD_GET(RX_MSDU_START_INFO1_MSDU_LENGTH,
			 __le32_to_cpu(desc->u.qca6390.msdu_start.info1));
}

static u16 ath11k_hw_rxdesc_msdu_start_msdu_len_qca6490(struct hal_rx_desc *desc)
{
	return FIELD_GET(RX_MSDU_START_INFO1_MSDU_LENGTH,
			 __le32_to_cpu(desc->u.qca6490.msdu_start.info1));
}

static u8 ath11k_hw_rxdesc_msdu_start_sgi_qca6390(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_SGI,
			 __le32_to_cpu(desc->u.qca6390.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_msdu_start_sgi_qca6490(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_SGI,
			 __le32_to_cpu(desc->u.qca6490.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_msdu_start_rate_mcs_qca6390(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_RATE_MCS,
			 __le32_to_cpu(desc->u.qca6390.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_msdu_start_rate_mcs_qca6490(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_RATE_MCS,
			 __le32_to_cpu(desc->u.qca6490.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_msdu_start_rx_bw_qca6390(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_RECV_BW,
			 __le32_to_cpu(desc->u.qca6390.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_msdu_start_rx_bw_qca6490(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_RECV_BW,
			 __le32_to_cpu(desc->u.qca6490.msdu_start.info3));
}

static u32 ath11k_hw_rxdesc_msdu_start_freq_qca6390(struct hal_rx_desc *desc)
{
	return __le32_to_cpu(desc->u.qca6390.msdu_start.phy_meta_data);
}

static u32 ath11k_hw_rxdesc_msdu_start_freq_qca6490(struct hal_rx_desc *desc)
{
	return __le32_to_cpu(desc->u.qca6490.msdu_start.phy_meta_data);
}

static u8 ath11k_hw_rxdesc_msdu_start_pkt_type_qca6390(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_PKT_TYPE,
			 __le32_to_cpu(desc->u.qca6390.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_msdu_start_pkt_type_qca6490(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_PKT_TYPE,
			 __le32_to_cpu(desc->u.qca6490.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_msdu_start_nss_qca6390(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_MIMO_SS_BITMAP,
			 __le32_to_cpu(desc->u.qca6390.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_msdu_start_nss_qca6490(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_START_INFO3_MIMO_SS_BITMAP,
			  __le32_to_cpu(desc->u.qca6490.msdu_start.info3));
}

static u8 ath11k_hw_rxdesc_mpdu_start_tid_qca6390(struct hal_rx_desc *desc)
{
#ifdef RX_MPDU_START_INFO2_TID
#undef RX_MPDU_START_INFO2_TID
#endif
#define RX_MPDU_START_INFO2_TID	GENMASK(17, 14)

	return (u8)FIELD_GET(RX_MPDU_START_INFO2_TID,
			 __le32_to_cpu(desc->u.qca6390.mpdu_start.info2));
}

static u8 ath11k_hw_rxdesc_mpdu_start_tid_qca6490(struct hal_rx_desc *desc)
{
#ifdef RX_MPDU_START_INFO2_TID
#undef RX_MPDU_START_INFO2_TID
#endif
#define RX_MPDU_START_INFO2_TID	GENMASK(18, 15)

	return (u8)FIELD_GET(RX_MPDU_START_INFO2_TID,
			 __le32_to_cpu(desc->u.qca6490.mpdu_start.info2));
}

static u16 ath11k_hw_rxdesc_mpdu_start_peer_id_qca6390(struct hal_rx_desc *desc)
{
	return __le16_to_cpu(desc->u.qca6390.mpdu_start.sw_peer_id);
}

static u16 ath11k_hw_rxdesc_mpdu_start_peer_id_qca6490(struct hal_rx_desc *desc)
{
	return __le16_to_cpu(desc->u.qca6490.mpdu_start.sw_peer_id);
}

static u8 ath11k_hw_rxdesc_msdu_end_l3pad_qca6390(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_END_INFO2_L3_HDR_PADDING,
			 __le32_to_cpu(desc->u.qca6390.msdu_end.info2));
}

static u8 ath11k_hw_rxdesc_msdu_end_l3pad_qca6490(struct hal_rx_desc *desc)
{
	return (u8)FIELD_GET(RX_MSDU_END_INFO2_L3_HDR_PADDING,
			 __le32_to_cpu(desc->u.qca6490.msdu_end.info2));
}

static bool ath11k_hw_rxdesc_msdu_end_first_msdu_qca6390(struct hal_rx_desc *desc)
{
#ifdef RX_MSDU_END_INFO2_FIRST_MSDU
#undef RX_MSDU_END_INFO2_FIRST_MSDU
#endif
#define RX_MSDU_END_INFO2_FIRST_MSDU BIT(14)

	return !!FIELD_GET(RX_MSDU_END_INFO2_FIRST_MSDU,
			__le32_to_cpu(desc->u.qca6390.msdu_end.info2));
}

static bool ath11k_hw_rxdesc_msdu_end_first_msdu_qca6490(struct hal_rx_desc *desc)
{
#ifdef RX_MSDU_END_INFO2_FIRST_MSDU
#undef RX_MSDU_END_INFO2_FIRST_MSDU
#endif
#define RX_MSDU_END_INFO2_FIRST_MSDU BIT(28)

	return !!FIELD_GET(RX_MSDU_END_INFO2_FIRST_MSDU,
			__le32_to_cpu(desc->u.qca6490.msdu_end.info2));
}

static bool ath11k_hw_rxdesc_msdu_end_last_msdu_qca6390(struct hal_rx_desc *desc)
{
#ifdef RX_MSDU_END_INFO2_LAST_MSDU
#undef RX_MSDU_END_INFO2_LAST_MSDU
#endif
#define RX_MSDU_END_INFO2_LAST_MSDU BIT(15)

	return !!FIELD_GET(RX_MSDU_END_INFO2_LAST_MSDU,
			__le32_to_cpu(desc->u.qca6390.msdu_end.info2));
}

static bool ath11k_hw_rxdesc_msdu_end_last_msdu_qca6490(struct hal_rx_desc *desc)
{
#ifdef RX_MSDU_END_INFO2_LAST_MSDU
#undef RX_MSDU_END_INFO2_LAST_MSDU
#endif
#define RX_MSDU_END_INFO2_LAST_MSDU BIT(29)

	return !!FIELD_GET(RX_MSDU_END_INFO2_LAST_MSDU,
			__le32_to_cpu(desc->u.qca6490.msdu_end.info2));
}

static void ath11k_hw_rxdesc_end_tlv_copy_qca6390(struct hal_rx_desc *fdesc,
						  struct hal_rx_desc *ldesc)
{
	memcpy((u8 *)&fdesc->u.qca6390.msdu_end, (u8 *)&ldesc->u.qca6390.msdu_end,
	       sizeof(struct rx_msdu_end_qca6390));
	memcpy((u8 *)&fdesc->u.qca6390.attention, (u8 *)&ldesc->u.qca6390.attention,
	       sizeof(struct rx_attention));
	memcpy((u8 *)&fdesc->u.qca6390.mpdu_end, (u8 *)&ldesc->u.qca6390.mpdu_end,
	       sizeof(struct rx_mpdu_end));
}

static void ath11k_hw_rxdesc_end_tlv_copy_qca6490(struct hal_rx_desc *fdesc,
						  struct hal_rx_desc *ldesc)
{
	memcpy((u8 *)&fdesc->u.qca6490.msdu_end, (u8 *)&ldesc->u.qca6490.msdu_end,
	       sizeof(struct rx_msdu_end_qca6490));
	memcpy((u8 *)&fdesc->u.qca6490.attention, (u8 *)&ldesc->u.qca6490.attention,
	       sizeof(struct rx_attention));
	memcpy((u8 *)&fdesc->u.qca6490.mpdu_end, (u8 *)&ldesc->u.qca6490.mpdu_end,
	       sizeof(struct rx_mpdu_end));
}

static u32 ath11k_hw_rxdesc_get_mpdulen_err_qca6390(struct hal_rx_desc *desc)
{
	return FIELD_GET(RX_ATTENTION_INFO1_MPDU_LEN_ERR,
			__le32_to_cpu(desc->u.qca6390.attention.info1));
}

static u32 ath11k_hw_rxdesc_get_mpdulen_err_qca6490(struct hal_rx_desc *desc)
{
	return FIELD_GET(RX_ATTENTION_INFO1_MPDU_LEN_ERR,
			__le32_to_cpu(desc->u.qca6490.attention.info1));
}

static u32 ath11k_hw_rxdesc_get_decap_format_qca6390(struct hal_rx_desc *desc)
{
	return FIELD_GET(RX_MSDU_START_INFO2_DECAP_FORMAT,
			__le32_to_cpu(desc->u.qca6390.msdu_start.info2));
}

static u32 ath11k_hw_rxdesc_get_decap_format_qca6490(struct hal_rx_desc *desc)
{
	return FIELD_GET(RX_MSDU_START_INFO2_DECAP_FORMAT,
			__le32_to_cpu(desc->u.qca6490.msdu_start.info2));
}

static u8 *ath11k_hw_rxdesc_get_80211hdr_qca6390(struct hal_rx_desc *desc)
{
	u8 *rx_pkt_hdr;

	rx_pkt_hdr = &desc->u.qca6390.msdu_payload[0];

	return rx_pkt_hdr;
}

static u8 *ath11k_hw_rxdesc_get_80211hdr_qca6490(struct hal_rx_desc *desc)
{
	u8 *rx_pkt_hdr;

	rx_pkt_hdr = &desc->u.qca6490.msdu_payload[0];

	return rx_pkt_hdr;
}

static bool ath11k_hw_rxdesc_mpdu_valid_qca6390(struct hal_rx_desc *desc)
{
	u32 tlv_tag;

	tlv_tag = FIELD_GET(HAL_TLV_HDR_TAG,
			    __le32_to_cpu(desc->u.qca6390.mpdu_start_tag));

	return tlv_tag == HAL_RX_MPDU_START;
}

static bool ath11k_hw_rxdesc_mpdu_valid_qca6490(struct hal_rx_desc *desc)
{
	u32 tlv_tag;

	tlv_tag = FIELD_GET(HAL_TLV_HDR_TAG,
			    __le32_to_cpu(desc->u.qca6490.mpdu_start_tag));

	return tlv_tag == HAL_RX_MPDU_START;
}

static u32 ath11k_hw_rxdesc_get_ppduid_qca6390(struct hal_rx_desc *desc)
{
	return __le16_to_cpu(desc->u.qca6390.mpdu_start.phy_ppdu_id);
}

static u32 ath11k_hw_rxdesc_get_ppduid_qca6490(struct hal_rx_desc *desc)
{
	return __le16_to_cpu(desc->u.qca6490.mpdu_start.phy_ppdu_id);
}

static u32 *ath11k_hw_rxdesc_msdu_start_msdu_len_offset_qca6390(struct hal_rx_desc *desc)
{
	return (u32 *)&desc->u.qca6390.msdu_start;
}

static u32 *ath11k_hw_rxdesc_msdu_start_msdu_len_offset_qca6490(struct hal_rx_desc *desc)
{
	return (u32 *)&desc->u.qca6490.msdu_start;
}

static void ath11k_hw_reo_setup_qca6390(struct ath11k_base *ab, u32 ring_hash_map)
{
	u32 reo_base = HAL_SEQ_WCSS_UMAC_REO_REG;
	u32 val;

	val = ath11k_hif_read32(ab, reo_base + HAL_REO1_GEN_ENABLE);

	val &= ~HAL_REO1_GEN_ENABLE_FRAG_DST_RING;
	val |= FIELD_PREP(HAL_REO1_GEN_ENABLE_FRAG_DST_RING,
			HAL_SRNG_RING_ID_REO2SW1) |
		FIELD_PREP(HAL_REO1_GEN_ENABLE_AGING_LIST_ENABLE, 1) |
		FIELD_PREP(HAL_REO1_GEN_ENABLE_AGING_FLUSH_ENABLE, 1);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_GEN_ENABLE, val);

	ath11k_hif_write32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_0(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_1(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_2(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_3(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);

	ath11k_hif_write32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_0,
			   FIELD_PREP(HAL_REO_DEST_RING_CTRL_HASH_RING_MAP,
				      ring_hash_map));
	ath11k_hif_write32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_1,
			   FIELD_PREP(HAL_REO_DEST_RING_CTRL_HASH_RING_MAP,
				      ring_hash_map));
	ath11k_hif_write32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_2,
			   FIELD_PREP(HAL_REO_DEST_RING_CTRL_HASH_RING_MAP,
				      ring_hash_map));
	ath11k_hif_write32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_3,
			   FIELD_PREP(HAL_REO_DEST_RING_CTRL_HASH_RING_MAP,
				      ring_hash_map));
}

static void ath11k_hw_reo_setup_qca6490(struct ath11k_base *ab, u32 ring_hash_map)
{
	u32 reo_base = HAL_SEQ_WCSS_UMAC_REO_REG;
	u32 val;

	val = ath11k_hif_read32(ab, reo_base + HAL_REO1_GEN_ENABLE);
	val |= FIELD_PREP(HAL_REO1_GEN_ENABLE_AGING_LIST_ENABLE, 1) |
		FIELD_PREP(HAL_REO1_GEN_ENABLE_AGING_FLUSH_ENABLE, 1);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_GEN_ENABLE, val);

	val = ath11k_hif_read32(ab, reo_base + HAL_REO1_MISC_CTL);
	val &= ~HAL_REO1_MISC_CTL_FRAGMENT_DST_RING;
	val |= FIELD_PREP(HAL_REO1_MISC_CTL_FRAGMENT_DST_RING, HAL_SRNG_RING_ID_REO2SW1);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_MISC_CTL, val);

	ath11k_hif_write32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_0(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_1(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_2(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_AGING_THRESH_IX_3(ab),
			   HAL_DEFAULT_REO_TIMEOUT_USEC);

	ath11k_hif_write32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_2,
			   ring_hash_map);
	ath11k_hif_write32(ab, reo_base + HAL_REO1_DEST_RING_CTRL_IX_3,
			   ring_hash_map);
}

static u16 ath11k_hw_mpdu_info_get_peerid_qca6390(u8 *tlv_data)
{
	u16 peer_id = 0;

	struct hal_rx_mpdu_info_qca6390 *mpdu_info =
		(struct hal_rx_mpdu_info_qca6390 *)tlv_data;
#ifdef HAL_RX_MPDU_INFO_INFO0_PEERID
#undef HAL_RX_MPDU_INFO_INFO0_PEERID
#endif
#define HAL_RX_MPDU_INFO_INFO0_PEERID GENMASK(31, 16)

	peer_id = (u16)FIELD_GET(HAL_RX_MPDU_INFO_INFO0_PEERID,
			    __le32_to_cpu(mpdu_info->info0));

	return peer_id;
}

static u16 ath11k_hw_mpdu_info_get_peerid_qca6490(u8 *tlv_data)
{
	u16 peer_id = 0;

	struct hal_rx_mpdu_info_qca6490 *mpdu_info =
		(struct hal_rx_mpdu_info_qca6490 *)tlv_data;
#ifdef HAL_RX_MPDU_INFO_INFO0_PEERID
#undef HAL_RX_MPDU_INFO_INFO0_PEERID
#endif
#define HAL_RX_MPDU_INFO_INFO0_PEERID GENMASK(15, 0)

	peer_id = FIELD_GET(HAL_RX_MPDU_INFO_INFO0_PEERID,
			    __le32_to_cpu(mpdu_info->info0));
	return peer_id;
}

const struct ath11k_hw_ops qca6390_ops = {
	.get_hw_mac_from_pdev_id = NULL,
	.wmi_init_config = ath11k_init_wmi_config_qca6x90,
	.mac_id_to_pdev_id = NULL,
	.mac_id_to_srng_id = NULL,
	.rxdesc_80211_hdr = ath11k_hw_rxdesc_80211_hdr_qca6390,
	.rxdesc_mpdu_start_enctype = ath11k_hw_rxdesc_mpdu_start_enctype_qca6390,
	.rxdesc_msdu_start_decap_type = ath11k_hw_rxdesc_msdu_start_decap_type_qca6390,
	.rxdesc_msdu_start_mesh_ctl_present = ath11k_hw_rxdesc_msdu_start_mesh_ctl_present_qca6390,
	.rxdesc_mpdu_start_seq_ctrl_valid = ath11k_hw_rxdesc_mpdu_start_seq_ctrl_valid_qca6390,
	.rxdesc_mpdu_start_fc_valid = ath11k_hw_rxdesc_mpdu_start_fc_valid_qca6390,
	.rxdesc_mpdu_start_seq_no = ath11k_hw_rxdesc_mpdu_start_seq_no_qca6390,
	.rxdesc_mpdu_start_addr2 = ath11k_hw_rxdesc_mpdu_start_addr2_qca6390,
	.rxdesc_attn_msdu_done = ath11k_hw_rxdesc_attn_msdu_done_qca6390,
	.rxdesc_attn_l4_cksum_fail = ath11k_hw_rxdesc_attn_l4_cksum_fail_qca6390,
	.rxdesc_attn_ip_cksum_fail = ath11k_hw_rxdesc_attn_ip_cksum_fail_qca6390,
	.rxdesc_attn_is_decrypted = ath11k_hw_rxdesc_attn_is_decrypted_qca6390,
	.rxdesc_get_attn = ath11k_hw_rxdesc_get_attn_qca6390,
	.rxdesc_msdu_start_msdu_len = ath11k_hw_rxdesc_msdu_start_msdu_len_qca6390,
	.rxdesc_msdu_start_sgi = ath11k_hw_rxdesc_msdu_start_sgi_qca6390,
	.rxdesc_msdu_start_rate_mcs = ath11k_hw_rxdesc_msdu_start_rate_mcs_qca6390,
	.rxdesc_msdu_start_rx_bw = ath11k_hw_rxdesc_msdu_start_rx_bw_qca6390,
	.rxdesc_msdu_start_freq = ath11k_hw_rxdesc_msdu_start_freq_qca6390,
	.rxdesc_msdu_start_pkt_type = ath11k_hw_rxdesc_msdu_start_pkt_type_qca6390,
	.rxdesc_msdu_start_nss = ath11k_hw_rxdesc_msdu_start_nss_qca6390,
	.rxdesc_mpdu_start_tid = ath11k_hw_rxdesc_mpdu_start_tid_qca6390,
	.rxdesc_mpdu_start_peer_id = ath11k_hw_rxdesc_mpdu_start_peer_id_qca6390,
	.rxdesc_msdu_end_l3pad = ath11k_hw_rxdesc_msdu_end_l3pad_qca6390,
	.rxdesc_msdu_end_first_msdu = ath11k_hw_rxdesc_msdu_end_first_msdu_qca6390,
	.rxdesc_msdu_end_last_msdu = ath11k_hw_rxdesc_msdu_end_last_msdu_qca6390,
	.rxdesc_end_tlv_copy = ath11k_hw_rxdesc_end_tlv_copy_qca6390,
	.rxdesc_get_mpdulen_err = ath11k_hw_rxdesc_get_mpdulen_err_qca6390,
	.rxdesc_get_decap_format = ath11k_hw_rxdesc_get_decap_format_qca6390,
	.rxdesc_get_80211hdr = ath11k_hw_rxdesc_get_80211hdr_qca6390,
	.rxdesc_mpdu_valid = ath11k_hw_rxdesc_mpdu_valid_qca6390,
	.rxdesc_get_ppduid = ath11k_hw_rxdesc_get_ppduid_qca6390,
	.rxdesc_msdu_start_msdu_len_offset = ath11k_hw_rxdesc_msdu_start_msdu_len_offset_qca6390,
	.reo_setup = ath11k_hw_reo_setup_qca6390,
	.mpdu_info_get_peerid = ath11k_hw_mpdu_info_get_peerid_qca6390,
};

const struct ath11k_hw_ops qca6490_ops = {
	.get_hw_mac_from_pdev_id = NULL,
	.wmi_init_config = ath11k_init_wmi_config_qca6x90,
	.mac_id_to_pdev_id = NULL,
	.mac_id_to_srng_id = NULL,
	.rxdesc_80211_hdr = ath11k_hw_rxdesc_80211_hdr_qca6490,
	.rxdesc_mpdu_start_enctype = ath11k_hw_rxdesc_mpdu_start_enctype_qca6490,
	.rxdesc_msdu_start_decap_type = ath11k_hw_rxdesc_msdu_start_decap_type_qca6490,
	.rxdesc_msdu_start_mesh_ctl_present = ath11k_hw_rxdesc_msdu_start_mesh_ctl_present_qca6490,
	.rxdesc_mpdu_start_seq_ctrl_valid = ath11k_hw_rxdesc_mpdu_start_seq_ctrl_valid_qca6490,
	.rxdesc_mpdu_start_fc_valid = ath11k_hw_rxdesc_mpdu_start_fc_valid_qca6490,
	.rxdesc_mpdu_start_seq_no = ath11k_hw_rxdesc_mpdu_start_seq_no_qca6490,
	.rxdesc_mpdu_start_addr2 = ath11k_hw_rxdesc_mpdu_start_addr2_qca6490,
	.rxdesc_attn_msdu_done = ath11k_hw_rxdesc_attn_msdu_done_qca6490,
	.rxdesc_attn_l4_cksum_fail = ath11k_hw_rxdesc_attn_l4_cksum_fail_qca6490,
	.rxdesc_attn_ip_cksum_fail = ath11k_hw_rxdesc_attn_ip_cksum_fail_qca6490,
	.rxdesc_attn_is_decrypted = ath11k_hw_rxdesc_attn_is_decrypted_qca6490,
	.rxdesc_get_attn = ath11k_hw_rxdesc_get_attn_qca6490,
	.rxdesc_msdu_start_msdu_len = ath11k_hw_rxdesc_msdu_start_msdu_len_qca6490,
	.rxdesc_msdu_start_sgi = ath11k_hw_rxdesc_msdu_start_sgi_qca6490,
	.rxdesc_msdu_start_rate_mcs = ath11k_hw_rxdesc_msdu_start_rate_mcs_qca6490,
	.rxdesc_msdu_start_rx_bw = ath11k_hw_rxdesc_msdu_start_rx_bw_qca6490,
	.rxdesc_msdu_start_freq = ath11k_hw_rxdesc_msdu_start_freq_qca6490,
	.rxdesc_msdu_start_pkt_type = ath11k_hw_rxdesc_msdu_start_pkt_type_qca6490,
	.rxdesc_msdu_start_nss = ath11k_hw_rxdesc_msdu_start_nss_qca6490,
	.rxdesc_mpdu_start_tid = ath11k_hw_rxdesc_mpdu_start_tid_qca6490,
	.rxdesc_mpdu_start_peer_id = ath11k_hw_rxdesc_mpdu_start_peer_id_qca6490,
	.rxdesc_msdu_end_l3pad = ath11k_hw_rxdesc_msdu_end_l3pad_qca6490,
	.rxdesc_msdu_end_first_msdu = ath11k_hw_rxdesc_msdu_end_first_msdu_qca6490,
	.rxdesc_msdu_end_last_msdu = ath11k_hw_rxdesc_msdu_end_last_msdu_qca6490,
	.rxdesc_end_tlv_copy = ath11k_hw_rxdesc_end_tlv_copy_qca6490,
	.rxdesc_get_mpdulen_err = ath11k_hw_rxdesc_get_mpdulen_err_qca6490,
	.rxdesc_get_decap_format = ath11k_hw_rxdesc_get_decap_format_qca6490,
	.rxdesc_get_80211hdr = ath11k_hw_rxdesc_get_80211hdr_qca6490,
	.rxdesc_mpdu_valid = ath11k_hw_rxdesc_mpdu_valid_qca6490,
	.rxdesc_get_ppduid = ath11k_hw_rxdesc_get_ppduid_qca6490,
	.rxdesc_msdu_start_msdu_len_offset = ath11k_hw_rxdesc_msdu_start_msdu_len_offset_qca6490,
	.reo_setup = ath11k_hw_reo_setup_qca6490,
	.mpdu_info_get_peerid = ath11k_hw_mpdu_info_get_peerid_qca6490,
};


/* Target firmware's Copy Engine configuration. */
const struct ce_pipe_config ath11k_target_ce_config_wlan_qca6x90[] = {
	/* CE0: host->target HTC control and raw streams */
	{
		.pipenum = __cpu_to_le32(0),
		.pipedir = __cpu_to_le32(PIPEDIR_OUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	},

	/* CE1: target->host HTT + HTC control */
	{
		.pipenum = __cpu_to_le32(1),
		.pipedir = __cpu_to_le32(PIPEDIR_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	},

	/* CE2: target->host WMI */
	{
		.pipenum = __cpu_to_le32(2),
		.pipedir = __cpu_to_le32(PIPEDIR_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	},

	/* CE3: host->target WMI */
	{
		.pipenum = __cpu_to_le32(3),
		.pipedir = __cpu_to_le32(PIPEDIR_OUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	},

	/* CE4: host->target HTT */
	{
		.pipenum = __cpu_to_le32(4),
		.pipedir = __cpu_to_le32(PIPEDIR_OUT),
		.nentries = __cpu_to_le32(256),
		.nbytes_max = __cpu_to_le32(256),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS | CE_ATTR_DIS_INTR),
		.reserved = __cpu_to_le32(0),
	},

	/* CE5: target->host Pktlog */
	{
		.pipenum = __cpu_to_le32(5),
		.pipedir = __cpu_to_le32(PIPEDIR_IN),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(2048),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	},

	/* CE6: Reserved for target autonomous hif_memcpy */
	{
		.pipenum = __cpu_to_le32(6),
		.pipedir = __cpu_to_le32(PIPEDIR_INOUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(16384),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	},

	/* CE7 used only by Host */
	{
		.pipenum = __cpu_to_le32(7),
		.pipedir = __cpu_to_le32(PIPEDIR_INOUT_H2H),
		.nentries = __cpu_to_le32(0),
		.nbytes_max = __cpu_to_le32(0),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS | CE_ATTR_DIS_INTR),
		.reserved = __cpu_to_le32(0),
	},

	/* CE8 target->host used only by IPA */
	{
		.pipenum = __cpu_to_le32(8),
		.pipedir = __cpu_to_le32(PIPEDIR_INOUT),
		.nentries = __cpu_to_le32(32),
		.nbytes_max = __cpu_to_le32(16384),
		.flags = __cpu_to_le32(CE_ATTR_FLAGS),
		.reserved = __cpu_to_le32(0),
	},
	/* CE 9, 10, 11 are used by MHI driver */
};

/* Map from service/endpoint to Copy Engine.
 * This table is derived from the CE_PCI TABLE, above.
 * It is passed to the Target at startup for use by firmware.
 */
const struct service_to_pipe ath11k_target_service_to_ce_map_wlan_qca6x90[] = {
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_DATA_VO),
		__cpu_to_le32(PIPEDIR_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_DATA_VO),
		__cpu_to_le32(PIPEDIR_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_DATA_BK),
		__cpu_to_le32(PIPEDIR_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_DATA_BK),
		__cpu_to_le32(PIPEDIR_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_DATA_BE),
		__cpu_to_le32(PIPEDIR_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_DATA_BE),
		__cpu_to_le32(PIPEDIR_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_DATA_VI),
		__cpu_to_le32(PIPEDIR_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_DATA_VI),
		__cpu_to_le32(PIPEDIR_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_CONTROL),
		__cpu_to_le32(PIPEDIR_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(3),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_WMI_CONTROL),
		__cpu_to_le32(PIPEDIR_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_RSVD_CTRL),
		__cpu_to_le32(PIPEDIR_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(0),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_RSVD_CTRL),
		__cpu_to_le32(PIPEDIR_IN),	/* in = DL = target -> host */
		__cpu_to_le32(2),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_HTT_DATA_MSG),
		__cpu_to_le32(PIPEDIR_OUT),	/* out = UL = host -> target */
		__cpu_to_le32(4),
	},
	{
		__cpu_to_le32(ATH11K_HTC_SVC_ID_HTT_DATA_MSG),
		__cpu_to_le32(PIPEDIR_IN),	/* in = DL = target -> host */
		__cpu_to_le32(1),
	},

	/* (Additions here) */

	{ /* must be last */
		__cpu_to_le32(0),
		__cpu_to_le32(0),
		__cpu_to_le32(0),
	},
};

const struct ath11k_hw_values qca6x90_values = {
	.rfkill_pin			= 48,
	.rfkill_cfg			= 0,
	.rfkill_on_level	= 1,
};

const struct ath11k_hw_regs qca6390_regs = {
	/* SW2TCL(x) R0 ring configuration address */
	.hal_tcl1_ring_base_lsb = 0x00000684,
	.hal_tcl1_ring_base_msb = 0x00000688,
	.hal_tcl1_ring_id = 0x0000068c,
	.hal_tcl1_ring_misc = 0x00000694,
	.hal_tcl1_ring_tp_addr_lsb = 0x000006a0,
	.hal_tcl1_ring_tp_addr_msb = 0x000006a4,
	.hal_tcl1_ring_consumer_int_setup_ix0 = 0x000006b4,
	.hal_tcl1_ring_consumer_int_setup_ix1 = 0x000006b8,
	.hal_tcl1_ring_msi1_base_lsb = 0x000006cc,
	.hal_tcl1_ring_msi1_base_msb = 0x000006d0,
	.hal_tcl1_ring_msi1_data = 0x000006d4,
	.hal_tcl2_ring_base_lsb = 0x000006dc,
	.hal_tcl_ring_base_lsb = 0x0000078c,

	/* TCL STATUS ring address */
	.hal_tcl_status_ring_base_lsb = 0x00000894,

	/* REO2SW(x) R0 ring configuration address */
	.hal_reo1_ring_base_lsb = 0x00000244,
	.hal_reo1_ring_base_msb = 0x00000248,
	.hal_reo1_ring_id = 0x0000024c,
	.hal_reo1_ring_misc = 0x00000254,
	.hal_reo1_ring_hp_addr_lsb = 0x00000258,
	.hal_reo1_ring_hp_addr_msb = 0x0000025c,
	.hal_reo1_ring_producer_int_setup = 0x00000268,
	.hal_reo1_ring_msi1_base_lsb = 0x0000028c,
	.hal_reo1_ring_msi1_base_msb = 0x00000290,
	.hal_reo1_ring_msi1_data = 0x00000294,
	.hal_reo2_ring_base_lsb = 0x0000029c,
	.hal_reo1_aging_thresh_ix_0 = 0x0000050c,
	.hal_reo1_aging_thresh_ix_1 = 0x00000510,
	.hal_reo1_aging_thresh_ix_2 = 0x00000514,
	.hal_reo1_aging_thresh_ix_3 = 0x00000518,

	/* REO2SW(x) R2 ring pointers (head/tail) address */
	.hal_reo1_ring_hp = 0x00003030,
	.hal_reo1_ring_tp = 0x00003034,
	.hal_reo2_ring_hp = 0x00003038,

	/* REO2TCL R0 ring configuration address */
	.hal_reo_tcl_ring_base_lsb = 0x000003a4,
	.hal_reo_tcl_ring_hp = 0x00003050,

	/* REO status address */
	.hal_reo_status_ring_base_lsb = 0x000004ac,
	.hal_reo_status_hp = 0x00003068,

	/* WCSS CE register base*/
	.hal_ce0_src_reg_base = 0x00a00000,
	.hal_ce0_dst_reg_base = 0x00a01000,
	.hal_ce1_src_reg_base = 0x00a02000,
	.hal_ce1_dst_reg_base = 0x00a03000,

	.hal_ce_host_ie = 0x00a1803c,
	.hal_ce_host_ie2 = 0x00a18040,

	/*WBM Idle R0 address*/
	.hal_wbm_idle_link_ring_base_lsb = 0x00000860,
	.hal_wbm_idle_link_ring_misc_addr = 0x00000870,

	/*SW2WBM R0 release address*/
	.hal_wbm_release_ring_base_lsb = 0x000001d8,

	/*WBM2SW R0 release address*/
	.hal_wbm0_release_ring_base_lsb = 0x00000910,
	.hal_wbm1_release_ring_base_lsb = 0x00000968,
};

const struct ath11k_hw_regs qca6490_regs = {
	/* SW2TCL(x) R0 ring configuration address */
	.hal_tcl1_ring_base_lsb = 0x00000690,
	.hal_tcl1_ring_base_msb = 0x00000694,
	.hal_tcl1_ring_id = 0x00000698,
	.hal_tcl1_ring_misc = 0x000006a0,
	.hal_tcl1_ring_tp_addr_lsb = 0x000006ac,
	.hal_tcl1_ring_tp_addr_msb = 0x000006b0,
	.hal_tcl1_ring_consumer_int_setup_ix0 = 0x000006c0,
	.hal_tcl1_ring_consumer_int_setup_ix1 = 0x000006c4,
	.hal_tcl1_ring_msi1_base_lsb = 0x000006d8,
	.hal_tcl1_ring_msi1_base_msb = 0x000006dc,
	.hal_tcl1_ring_msi1_data = 0x000006e0,
	.hal_tcl2_ring_base_lsb = 0x000006e8,
	.hal_tcl_ring_base_lsb = 0x00000798,

	/* TCL STATUS ring address */
	.hal_tcl_status_ring_base_lsb = 0x000008a0,

	/* REO2SW(x) R0 ring configuration address */
	.hal_reo1_ring_base_lsb = 0x00000244,
	.hal_reo1_ring_base_msb = 0x00000248,
	.hal_reo1_ring_id = 0x0000024c,
	.hal_reo1_ring_misc = 0x00000254,
	.hal_reo1_ring_hp_addr_lsb = 0x00000258,
	.hal_reo1_ring_hp_addr_msb = 0x0000025c,
	.hal_reo1_ring_producer_int_setup = 0x00000268,
	.hal_reo1_ring_msi1_base_lsb = 0x0000028c,
	.hal_reo1_ring_msi1_base_msb = 0x00000290,
	.hal_reo1_ring_msi1_data = 0x00000294,
	.hal_reo2_ring_base_lsb = 0x0000029c,
	.hal_reo1_aging_thresh_ix_0 = 0x000005bc,
	.hal_reo1_aging_thresh_ix_1 = 0x000005c0,
	.hal_reo1_aging_thresh_ix_2 = 0x000005c4,
	.hal_reo1_aging_thresh_ix_3 = 0x000005c8,

	/* REO2SW(x) R2 ring pointers (head/tail) address */
	.hal_reo1_ring_hp = 0x00003030,
	.hal_reo1_ring_tp = 0x00003034,
	.hal_reo2_ring_hp = 0x00003038,

	/* REO2TCL R0 ring configuration address */
	.hal_reo_tcl_ring_base_lsb = 0x00000454,
	.hal_reo_tcl_ring_hp = 0x00003060,

	/* REO status address */
	.hal_reo_status_ring_base_lsb = 0x0000055c,
	.hal_reo_status_hp = 0x00003078,

	/* WCSS CE register base*/
	.hal_ce0_src_reg_base = 0x1b80000,
	.hal_ce0_dst_reg_base = 0x1b81000,
	.hal_ce1_src_reg_base = 0x1b82000,
	.hal_ce1_dst_reg_base = 0x1b83000,

	.hal_ce_host_ie = 0x01b9804c,
	.hal_ce_host_ie2 = 0x01b98050,

	/*WBM Idle R0 address*/
	.hal_wbm_idle_link_ring_base_lsb = 0x00000870,
	.hal_wbm_idle_link_ring_misc_addr = 0x00000880,

	/*SW2WBM R0 release address*/
	.hal_wbm_release_ring_base_lsb = 0x000001e8,

	/*WBM2SW R0 release address*/
	.hal_wbm0_release_ring_base_lsb = 0x00000920,
	.hal_wbm1_release_ring_base_lsb = 0x00000978,
};

const struct ath11k_hw_srng_params ath11k_hw_srng_qca6x90 = {
	.tcl_data_ring_size = 4096,
	.tx_comp_ring_size = 8192,
	.reo_dst_ring_size = 2048,
	.num_clients_max = 64,
	.scaler = 0,
};

const struct ath11k_hw_misc_regs qca6390_misc_regs = {
	.gcc_pcie_hot_rst = 0x1E402BC,
	.gcc_pcie_hot_rst_val = 0x10,
};

const struct ath11k_hw_misc_regs qca6490_misc_regs = {
	.gcc_pcie_hot_rst = 0x01E40304,
	.gcc_pcie_hot_rst_val = 0x5,
};

