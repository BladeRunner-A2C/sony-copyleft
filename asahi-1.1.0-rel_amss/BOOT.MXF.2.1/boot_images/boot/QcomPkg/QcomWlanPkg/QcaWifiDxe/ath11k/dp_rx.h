/* SPDX-License-Identifier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#ifndef ATH11K_DP_RX_H
#define ATH11K_DP_RX_H

#include "core.h"
#include "rx_desc.h"
#include "debug.h"

#define DP_MAX_NWIFI_HDR_LEN	30
#define DP_RX_FCS_LEN 4

#define DP_RX_MPDU_ERR_FCS			    BIT(0)
#define DP_RX_MPDU_ERR_DECRYPT			BIT(1)
#define DP_RX_MPDU_ERR_TKIP_MIC			BIT(2)
#define DP_RX_MPDU_ERR_AMSDU_ERR		BIT(3)
#define DP_RX_MPDU_ERR_OVERFLOW			BIT(4)
#define DP_RX_MPDU_ERR_MSDU_LEN			BIT(5)
#define DP_RX_MPDU_ERR_MPDU_LEN			BIT(6)
#define DP_RX_MPDU_ERR_UNENCRYPTED_FRAME	BIT(7)

enum dp_rx_decap_type {
	DP_RX_DECAP_TYPE_RAW,
	DP_RX_DECAP_TYPE_NATIVE_WIFI,
	DP_RX_DECAP_TYPE_ETHERNET2_DIX,
	DP_RX_DECAP_TYPE_8023,
};

#pragma pack(1)
struct ath11k_dp_amsdu_subframe_hdr {
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	__be16 len;
} __packed;

struct ath11k_dp_rfc1042_hdr {
	u8 llc_dsap;
	u8 llc_ssap;
	u8 llc_ctrl;
	u8 snap_oui[3];
	__be16 snap_type;
} __packed;

struct dp_rx_ops {
	u8* (*h_80211_hdr)(void *);
	enum hal_encrypt_type (*h_mpdu_start_enctype)(void *);
	u8 (*h_msdu_start_decap_type)(void *);
	u8 (*h_msdu_start_mesh_ctl_present)(void *);
	bool (*h_mpdu_start_seq_ctrl_valid)(void *);
	bool (*h_mpdu_start_fc_valid)(void *);
	bool (*h_mpdu_start_more_frags)(struct sk_buff *);
	u16 (*h_mpdu_start_frag_no)(struct sk_buff *);
	u16 (*h_mpdu_start_seq_no)(void *);
	bool (*h_attn_msdu_done)(void *);
	bool (*h_attn_l4_cksum_fail)(void *);
	bool (*h_attn_ip_cksum_fail)(void *);
	bool (*h_attn_is_decrypted)(void *);
	u32 (*h_attn_mpdu_err)(void *);
	u16 (*h_msdu_start_msdu_len)(void *);
	u8 (*h_msdu_start_sgi)(void *);
	u8 (*h_msdu_start_rate_mcs)(void *);
	u8 (*h_msdu_start_rx_bw)(void *);
	u32 (*h_msdu_start_freq)(void *);
	u8 (*h_msdu_start_pkt_type)(void *);
	u8 (*h_msdu_start_nss)(void *);
	u8 (*h_mpdu_start_tid)(void *);
	u16 (*h_mpdu_start_peer_id)(void *);
	u8 (*h_msdu_end_l3pad)(void *);
	bool (*h_msdu_end_first_msdu)(void*);
	bool (*h_msdu_end_last_msdu)(void*);
	void (*rxdesc_end_tlv_copy)(void *fbuf, void *lbuf);
	u32 (*rxdesc_get_mpdulen_err)(void *);
	u32 (*rxdesc_get_decap_format)(void *);
	u8* (*rxdesc_get_80211hdr)(void *);
	bool (*rxdesc_mpdu_valid)(void *);
	u32 (*rxdesc_get_ppduid)(void *);
	bool (*h_attn_is_mcbc)(void *);
	u8* (*h_mpdu_start_addr2)(void *);
	u32* (*h_msdu_start_msdu_len_offset)(void *);
	size_t (*rxdesc_get_desc_size)(void);
}__packed;

#pragma pack()

int ath11k_dp_rx_ampdu_start(struct ath11k *ar,
			     struct ieee80211_ampdu_params *params);
int ath11k_dp_rx_ampdu_stop(struct ath11k *ar,
			    struct ieee80211_ampdu_params *params);
int ath11k_dp_peer_rx_pn_replay_config(struct ath11k_vif *arvif,
				       const u8 *peer_addr,
				       enum ieee80211_key_cmd key_cmd,
				       struct ieee80211_key_conf *key);
void ath11k_peer_frags_flush(struct ath11k *ar, struct ath11k_peer *peer);
void ath11k_peer_rx_tid_cleanup(struct ath11k *ar, struct ath11k_peer *peer);
void ath11k_peer_rx_tid_delete(struct ath11k *ar,
			       struct ath11k_peer *peer, u8 tid);
int ath11k_peer_rx_tid_setup(struct ath11k *ar, const u8 *peer_mac, int vdev_id,
			     u8 tid, u16 ba_win_sz, u16 ssn,
			     enum hal_pn_type pn_type);
void ath11k_dp_htt_htc_t2h_msg_handler(struct ath11k_base *ab,
				       struct sk_buff *skb);

int ath11k_dp_pdev_reo_setup(struct ath11k_base *ab);
void ath11k_dp_pdev_reo_cleanup(struct ath11k_base *ab);
int ath11k_dp_rx_pdev_alloc(struct ath11k_base *ab, int pdev_idx);
void ath11k_dp_rx_pdev_free(struct ath11k_base *ab, int pdev_idx);
void ath11k_dp_reo_cmd_list_cleanup(struct ath11k_base *ab);
void ath11k_dp_process_reo_status(struct ath11k_base *ab);
int ath11k_dp_process_rxdma_err(struct ath11k_base *ab, int mac_id, int budget);
int ath11k_dp_rx_process_wbm_err(struct ath11k_base *ab,
				 struct napi_struct *napi, int budget);
int ath11k_dp_process_rx_err(struct ath11k_base *ab, struct napi_struct *napi,
			     int budget);
int ath11k_dp_process_rx(struct ath11k_base *ab, int mac_id,
			 struct napi_struct *napi,
			 int budget);
int ath11k_dp_rxbufs_replenish(struct ath11k_base *ab, int mac_id,
			       struct dp_rxdma_ring *rx_ring,
			       int req_entries,
			       enum hal_rx_buf_return_buf_manager mgr,
			       gfp_t gfp);
int ath11k_dp_htt_tlv_iter(struct ath11k_base *ab, const void *ptr, size_t len,
			   int (*iter)(struct ath11k_base *ar, u16 tag, u16 len,
				       const void *ptr, void *data),
			   void *data);
#if ATH11K_SUPPORT_MONITOR
int ath11k_dp_rx_process_mon_rings(struct ath11k_base *ab, int mac_id,
				   struct napi_struct *napi, int budget);
int ath11k_dp_rx_process_mon_status(struct ath11k_base *ab, int mac_id,
				    struct napi_struct *napi, int budget);
int ath11k_dp_rx_mon_status_bufs_replenish(struct ath11k_base *ab, int mac_id,
					   struct dp_rxdma_ring *rx_ring,
					   int req_entries,
					   enum hal_rx_buf_return_buf_manager mgr,
					   gfp_t gfp);
int ath11k_dp_rx_pdev_mon_detach(struct ath11k *ar);
int ath11k_dp_rx_pdev_mon_attach(struct ath11k *ar);
#endif // !ATH11K_SUPPORT_MONITOR
int ath11k_peer_rx_frag_setup(struct ath11k *ar, const u8 *peer_mac, int vdev_id);
int ath11k_dp_purge_mon_ring(struct ath11k_base *ab);
int ath11k_dp_rx_ops_init(struct ath11k_base *ab);
#endif /* ATH11K_DP_RX_H */
