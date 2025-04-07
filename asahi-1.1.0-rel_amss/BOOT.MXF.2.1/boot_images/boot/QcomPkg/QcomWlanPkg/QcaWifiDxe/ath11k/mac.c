/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

// SPDX-License-Identifier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#include <net/mac80211.h>
#include <net/net80211.h>
#include "mac.h"
#include "core.h"
#include "debug.h"
#include "wmi.h"
#include "hw.h"
#include "dp_tx.h"
#include "dp_rx.h"
#include "testmode.h"
#include "peer.h"
#include "hif.h"
#include "reg.h"

#define CHAN2G(_channel, _freq, _flags) { \
	.band                   = NL80211_BAND_2GHZ, \
	.hw_value               = (_channel), \
	.center_freq            = (_freq), \
	.flags                  = (_flags), \
	.max_antenna_gain       = 0, \
	.max_power              = 30, \
}

#define CHAN5G(_channel, _freq, _flags) { \
	.band                   = NL80211_BAND_5GHZ, \
	.hw_value               = (_channel), \
	.center_freq            = (_freq), \
	.flags                  = (_flags), \
	.max_antenna_gain       = 0, \
	.max_power              = 30, \
}

#define CHAN6G(_channel, _freq, _flags) { \
	.band                   = NL80211_BAND_6GHZ, \
	.hw_value               = (_channel), \
	.center_freq            = (_freq), \
	.flags                  = (_flags), \
	.max_antenna_gain       = 0, \
	.max_power              = 30, \
}

static const struct ieee80211_channel ath11k_2ghz_channels[] = {
	CHAN2G(1, 2412, 0),
	CHAN2G(2, 2417, 0),
	CHAN2G(3, 2422, 0),
	CHAN2G(4, 2427, 0),
	CHAN2G(5, 2432, 0),
	CHAN2G(6, 2437, 0),
	CHAN2G(7, 2442, 0),
	CHAN2G(8, 2447, 0),
	CHAN2G(9, 2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
};

static const struct ieee80211_channel ath11k_5ghz_channels[] = {
	CHAN5G(36, 5180, 0),
	CHAN5G(40, 5200, 0),
	CHAN5G(44, 5220, 0),
	CHAN5G(48, 5240, 0),
	CHAN5G(52, 5260, 0),
	CHAN5G(56, 5280, 0),
	CHAN5G(60, 5300, 0),
	CHAN5G(64, 5320, 0),
	CHAN5G(100, 5500, 0),
	CHAN5G(104, 5520, 0),
	CHAN5G(108, 5540, 0),
	CHAN5G(112, 5560, 0),
	CHAN5G(116, 5580, 0),
	CHAN5G(120, 5600, 0),
	CHAN5G(124, 5620, 0),
	CHAN5G(128, 5640, 0),
	CHAN5G(132, 5660, 0),
	CHAN5G(136, 5680, 0),
	CHAN5G(140, 5700, 0),
	CHAN5G(144, 5720, 0),
	CHAN5G(149, 5745, 0),
	CHAN5G(153, 5765, 0),
	CHAN5G(157, 5785, 0),
	CHAN5G(161, 5805, 0),
	CHAN5G(165, 5825, 0),
	CHAN5G(169, 5845, 0),
	CHAN5G(173, 5865, 0),
};

static const struct ieee80211_channel ath11k_6ghz_channels[] = {
	CHAN6G(1, 5955, 0),
	CHAN6G(2, 5935, 0), /* op_class = 136 */
	CHAN6G(5, 5975, 0),
	CHAN6G(9, 5995, 0),
	CHAN6G(13, 6015, 0),
	CHAN6G(17, 6035, 0),
	CHAN6G(21, 6055, 0),
	CHAN6G(25, 6075, 0),
	CHAN6G(29, 6095, 0),
	CHAN6G(33, 6115, 0),
	CHAN6G(37, 6135, 0),
	CHAN6G(41, 6155, 0),
	CHAN6G(45, 6175, 0),
	CHAN6G(49, 6195, 0),
	CHAN6G(53, 6215, 0),
	CHAN6G(57, 6235, 0),
	CHAN6G(61, 6255, 0),
	CHAN6G(65, 6275, 0),
	CHAN6G(69, 6295, 0),
	CHAN6G(73, 6315, 0),
	CHAN6G(77, 6335, 0),
	CHAN6G(81, 6355, 0),
	CHAN6G(85, 6375, 0),
	CHAN6G(89, 6395, 0),
	CHAN6G(93, 6415, 0),
	CHAN6G(97, 6435, 0),
	CHAN6G(101, 6455, 0),
	CHAN6G(105, 6475, 0),
	CHAN6G(109, 6495, 0),
	CHAN6G(113, 6515, 0),
	CHAN6G(117, 6535, 0),
	CHAN6G(121, 6555, 0),
	CHAN6G(125, 6575, 0),
	CHAN6G(129, 6595, 0),
	CHAN6G(133, 6615, 0),
	CHAN6G(137, 6635, 0),
	CHAN6G(141, 6655, 0),
	CHAN6G(145, 6675, 0),
	CHAN6G(149, 6695, 0),
	CHAN6G(153, 6715, 0),
	CHAN6G(157, 6735, 0),
	CHAN6G(161, 6755, 0),
	CHAN6G(165, 6775, 0),
	CHAN6G(169, 6795, 0),
	CHAN6G(173, 6815, 0),
	CHAN6G(177, 6835, 0),
	CHAN6G(181, 6855, 0),
	CHAN6G(185, 6875, 0),
	CHAN6G(189, 6895, 0),
	CHAN6G(193, 6915, 0),
	CHAN6G(197, 6935, 0),
	CHAN6G(201, 6955, 0),
	CHAN6G(205, 6975, 0),
	CHAN6G(209, 6995, 0),
	CHAN6G(213, 7015, 0),
	CHAN6G(217, 7035, 0),
	CHAN6G(221, 7055, 0),
	CHAN6G(225, 7075, 0),
	CHAN6G(229, 7095, 0),
	CHAN6G(233, 7115, 0),
};

static struct ieee80211_rate ath11k_legacy_rates[] = {
	{ .bitrate = 10,
	  .hw_value = ATH11K_HW_RATE_CCK_LP_1M },
	{ .bitrate = 20,
	  .hw_value = ATH11K_HW_RATE_CCK_LP_2M,
	  .hw_value_short = ATH11K_HW_RATE_CCK_SP_2M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE },
	{ .bitrate = 55,
	  .hw_value = ATH11K_HW_RATE_CCK_LP_5_5M,
	  .hw_value_short = ATH11K_HW_RATE_CCK_SP_5_5M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE },
	{ .bitrate = 110,
	  .hw_value = ATH11K_HW_RATE_CCK_LP_11M,
	  .hw_value_short = ATH11K_HW_RATE_CCK_SP_11M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE },

	{ .bitrate = 60, .hw_value = ATH11K_HW_RATE_OFDM_6M },
	{ .bitrate = 90, .hw_value = ATH11K_HW_RATE_OFDM_9M },
	{ .bitrate = 120, .hw_value = ATH11K_HW_RATE_OFDM_12M },
	{ .bitrate = 180, .hw_value = ATH11K_HW_RATE_OFDM_18M },
	{ .bitrate = 240, .hw_value = ATH11K_HW_RATE_OFDM_24M },
	{ .bitrate = 360, .hw_value = ATH11K_HW_RATE_OFDM_36M },
	{ .bitrate = 480, .hw_value = ATH11K_HW_RATE_OFDM_48M },
	{ .bitrate = 540, .hw_value = ATH11K_HW_RATE_OFDM_54M },
};

static const int
ath11k_phymodes[NUM_NL80211_BANDS][ATH11K_CHAN_WIDTH_NUM] = {
	[NL80211_BAND_2GHZ] = {
			[NL80211_CHAN_WIDTH_5] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_10] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_20_NOHT] = MODE_11AX_HE20_2G,
			[NL80211_CHAN_WIDTH_20] = MODE_11AX_HE20_2G,
			[NL80211_CHAN_WIDTH_40] = MODE_11AX_HE40_2G,
			[NL80211_CHAN_WIDTH_80] = MODE_11AX_HE80_2G,
			[NL80211_CHAN_WIDTH_80P80] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_160] = MODE_UNKNOWN,
	},
	[NL80211_BAND_5GHZ] = {
			[NL80211_CHAN_WIDTH_5] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_10] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_20_NOHT] = MODE_11AX_HE20,
			[NL80211_CHAN_WIDTH_20] = MODE_11AX_HE20,
			[NL80211_CHAN_WIDTH_40] = MODE_11AX_HE40,
			[NL80211_CHAN_WIDTH_80] = MODE_11AX_HE80,
			[NL80211_CHAN_WIDTH_160] = MODE_11AX_HE160,
			[NL80211_CHAN_WIDTH_80P80] = MODE_11AX_HE80_80,
	},
	[NL80211_BAND_6GHZ] = {
			[NL80211_CHAN_WIDTH_5] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_10] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_20_NOHT] = MODE_11AX_HE20,
			[NL80211_CHAN_WIDTH_20] = MODE_11AX_HE20,
			[NL80211_CHAN_WIDTH_40] = MODE_11AX_HE40,
			[NL80211_CHAN_WIDTH_80] = MODE_11AX_HE80,
			[NL80211_CHAN_WIDTH_160] = MODE_11AX_HE160,
			[NL80211_CHAN_WIDTH_80P80] = MODE_11AX_HE80_80,
	},

};

const struct htt_rx_ring_tlv_filter ath11k_mac_mon_status_filter_default = {
	.rx_filter = HTT_RX_FILTER_TLV_FLAGS_MPDU_START |
		     HTT_RX_FILTER_TLV_FLAGS_PPDU_END |
		     HTT_RX_FILTER_TLV_FLAGS_PPDU_END_STATUS_DONE,
	.pkt_filter_flags0 = HTT_RX_FP_MGMT_FILTER_FLAGS0,
	.pkt_filter_flags1 = HTT_RX_FP_MGMT_FILTER_FLAGS1,
	.pkt_filter_flags2 = HTT_RX_FP_CTRL_FILTER_FLASG2,
	.pkt_filter_flags3 = HTT_RX_FP_DATA_FILTER_FLASG3 |
			     HTT_RX_FP_CTRL_FILTER_FLASG3
};

#define ATH11K_MAC_FIRST_OFDM_RATE_IDX 4
#define ath11k_g_rates ath11k_legacy_rates
#define ath11k_g_rates_size (ARRAY_SIZE(ath11k_legacy_rates))
#define ath11k_a_rates (ath11k_legacy_rates + 4)
#define ath11k_a_rates_size (ARRAY_SIZE(ath11k_legacy_rates) - 4)

#define ATH11K_MAC_SCAN_TIMEOUT_MSECS 200 /* in msecs */

static const u32 ath11k_smps_map[] = {
	[WLAN_HTCAP_SM_PS_STATIC] = WMI_PEER_SMPS_STATIC,
	[WLAN_HTCAP_SM_PS_DYNAMIC] = WMI_PEER_SMPS_DYNAMIC,
	[WLAN_HTCAP_SM_PS_INVALID] = WMI_PEER_SMPS_PS_NONE,
	[WLAN_HTCAP_SM_PS_DISABLED] = WMI_PEER_SMPS_PS_NONE,
};

static int
ath11k_start_vdev_delay(struct ieee80211_hw *hw,
			struct ieee80211_vif *vif);

u8 ath11k_mac_bw_to_mac80211_bw(u8 bw)
{
	u8 ret = 0;

	switch (bw) {
	case ATH11K_BW_20:
		ret = IEEE80211_RATE_INFO_BW_20;
		break;
	case ATH11K_BW_40:
		ret = IEEE80211_RATE_INFO_BW_40;
		break;
	case ATH11K_BW_80:
		ret = IEEE80211_RATE_INFO_BW_80;
		break;
	case ATH11K_BW_160:
		ret = IEEE80211_RATE_INFO_BW_160;
		break;
	}

	return ret;
}

int ath11k_mac_hw_ratecode_to_legacy_rate(u8 hw_rc, u8 preamble, u8 *rateidx,
					  u16 *rate)
{
	/* As default, it is OFDM rates */
	u8 i = ATH11K_MAC_FIRST_OFDM_RATE_IDX;
	u8 max_rates_idx = ath11k_g_rates_size;

	if (preamble == WMI_RATE_PREAMBLE_CCK) {
		hw_rc &= ~ATH11k_HW_RATECODE_CCK_SHORT_PREAM_MASK;
		i = 0;
		max_rates_idx = ATH11K_MAC_FIRST_OFDM_RATE_IDX;
	}

	while (i < max_rates_idx) {
		if (hw_rc == ath11k_legacy_rates[i].hw_value) {
			*rateidx = i;
			*rate = ath11k_legacy_rates[i].bitrate;
			return 0;
		}
		i++;
	}

	return -EINVAL;
}

static u8 get_num_chains(u32 mask)
{
	u8 num_chains = 0;

	while (mask) {
		if (mask & BIT(0))
			num_chains++;
		mask >>= 1;
	}

	return num_chains;
}

u8 ath11k_mac_bitrate_to_idx(const struct ieee80211_supported_band *sband,
			     u32 bitrate)
{
	u32 i;

	for (i = 0; i < sband->n_bitrates; i++)
		if (sband->bitrates[i].bitrate == bitrate)
			return (u8)i;

	return 0;
}

static u32
ath11k_mac_max_ht_nss(const u8 ht_mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
{
	int nss;

	for (nss = IEEE80211_HT_MCS_MASK_LEN - 1; nss >= 0; nss--)
		if (ht_mcs_mask[nss])
			return nss + 1;

	return 1;
}

static u32
ath11k_mac_max_vht_nss(const u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
{
	int nss;

	for (nss = NL80211_VHT_NSS_MAX - 1; nss >= 0; nss--)
		if (vht_mcs_mask[nss])
			return nss + 1;

	return 1;
}

static u8 ath11k_parse_mpdudensity(u8 mpdudensity)
{
/* 802.11n D2.0 defined values for "Minimum MPDU Start Spacing":
 *   0 for no restriction
 *   1 for 1/4 us
 *   2 for 1/2 us
 *   3 for 1 us
 *   4 for 2 us
 *   5 for 4 us
 *   6 for 8 us
 *   7 for 16 us
 */
	switch (mpdudensity) {
	case 0:
		return 0;
	case 1:
	case 2:
	case 3:
	/* Our lower layer calculations limit our precision to
	 * 1 microsecond
	 */
		return 1;
	case 4:
		return 2;
	case 5:
		return 4;
	case 6:
		return 8;
	case 7:
		return 16;
	default:
		return 0;
	}
}

static int ath11k_mac_vif_chan(struct ieee80211_vif *vif,
			       struct ieee80211_chan_def *def)
{
	struct ieee80211_chanctx_conf *conf;

	rcu_read_lock();
	conf = ieee80211_vif_get_chanctx_conf(vif);
	if (!conf) {
		rcu_read_unlock();
		return -ENOENT;
	}

	*def = conf->def;
	rcu_read_unlock();

	return 0;
}

static bool ath11k_mac_bitrate_is_cck(int bitrate)
{
	switch (bitrate) {
	case 10:
	case 20:
	case 55:
	case 110:
		return true;
	}

	return false;
}

u8 ath11k_mac_hw_rate_to_idx(const struct ieee80211_supported_band *sband,
			     u8 hw_rate, bool cck)
{
	const struct ieee80211_rate *rate;
	u32 i;

	for (i = 0; i < sband->n_bitrates; i++) {
		rate = &sband->bitrates[i];

		if (ath11k_mac_bitrate_is_cck(rate->bitrate) != cck)
			continue;

		if (rate->hw_value == hw_rate)
			return (u8)i;
		else if (rate->flags & IEEE80211_RATE_SHORT_PREAMBLE &&
			 rate->hw_value_short == hw_rate)
			return (u8)i;
	}

	return 0;
}

static u8 ath11k_mac_bitrate_to_rate(int bitrate)
{
	return (u8)(DIV_ROUND_UP(bitrate, 5) |
	       (ath11k_mac_bitrate_is_cck(bitrate) ? BIT(7) : 0));
}

static void ath11k_get_arvif_iter(void *data, const u8 *mac,
				  struct ieee80211_vif *vif)
{
	struct ath11k_vif_iter *arvif_iter = data;
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);

	if (arvif->vdev_id == arvif_iter->vdev_id)
		arvif_iter->arvif = arvif;
}

struct ath11k_vif *ath11k_mac_get_arvif(struct ath11k *ar, u32 vdev_id)
{
	struct ath11k_vif_iter arvif_iter;
	u32 flags;

	memset(&arvif_iter, 0, sizeof(struct ath11k_vif_iter));
	arvif_iter.vdev_id = vdev_id;

	flags = 0;
	ieee80211_iterate_interfaces(ar->hw,
						   flags,
						   ath11k_get_arvif_iter,
						   &arvif_iter);
	if (!arvif_iter.arvif) {
		ath11k_warn(ar->ab, "No VIF found for vdev %d\n", vdev_id);
		return NULL;
	}

	return arvif_iter.arvif;
}

struct ath11k_vif *ath11k_mac_get_arvif_by_vdev_id(struct ath11k_base *ab,
						   u32 vdev_id)
{
	u32 i;
	struct ath11k_pdev *pdev;
	struct ath11k_vif *arvif;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = rcu_dereference(ab->pdevs_active[i]);
		if (pdev && pdev->ar) {
			arvif = ath11k_mac_get_arvif(pdev->ar, vdev_id);
			if (arvif)
				return arvif;
		}
	}

	return NULL;
}

struct ath11k *ath11k_mac_get_ar_by_vdev_id(struct ath11k_base *ab, u32 vdev_id)
{
	u32 i;
	struct ath11k_pdev *pdev;
	struct ath11k_vif *arvif;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = rcu_dereference(ab->pdevs_active[i]);
		if (pdev && pdev->ar) {
			arvif = ath11k_mac_get_arvif(pdev->ar, vdev_id);
			if (arvif)
				return arvif->ar;
		}
	}

	return NULL;
}

struct ath11k_vif *ath11k_mac_get_deleting_arvif(struct ath11k *ar, u32 vdev_id)
{
    struct ath11k_vif_iter arvif_iter;
    u32 flags;

    memset(&arvif_iter, 0, sizeof(struct ath11k_vif_iter));
    arvif_iter.vdev_id = vdev_id;

    flags = IEEE80211_VIF_ITER_INACTIVE;
    ieee80211_iterate_interfaces(ar->hw,
        flags,
        ath11k_get_arvif_iter,
        &arvif_iter);
    if (!arvif_iter.arvif) {
        ath11k_warn(ar->ab, "No VIF found for vdev %d\n", vdev_id);
        return NULL;
    }

    return arvif_iter.arvif;
}

struct ath11k *ath11k_mac_get_ar_vdev_delete_status(struct ath11k_base *ab, u32 vdev_id)
{
    u32 i;
    struct ath11k_pdev *pdev;
    struct ath11k_vif *arvif;

    for (i = 0; i < ab->num_radios; i++) {
        pdev = rcu_dereference(ab->pdevs_active[i]);
        if (pdev && pdev->ar) {
            arvif = ath11k_mac_get_deleting_arvif(pdev->ar, vdev_id);
            if (arvif)
                return arvif->ar;
        }
    }

    return NULL;
}

struct ath11k *ath11k_mac_get_ar_by_pdev_id(struct ath11k_base *ab, u32 pdev_id)
{
    u32 i;
    struct ath11k_pdev *pdev;

    if (ab->hw_params.single_pdev_only) {
        pdev = rcu_dereference(ab->pdevs_active[0]);
        return pdev ? pdev->ar : NULL;
    }

    if (WARN_ON(pdev_id > ab->num_radios))
        return NULL;

    for (i = 0; i < ab->num_radios; i++) {
        pdev = rcu_dereference(ab->pdevs_active[i]);

        if (pdev && pdev->pdev_id == pdev_id)
            return (pdev->ar ? pdev->ar : NULL);
    }

    return NULL;
}

struct ath11k *ath11k_mac_get_ar_vdev_stop_status(struct ath11k_base *ab,
						  u32 vdev_id)
{
	u32 i;
	struct ath11k_pdev *pdev;
	struct ath11k *ar;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = rcu_dereference(ab->pdevs_active[i]);
		if (pdev && pdev->ar) {
			ar = pdev->ar;

			spin_lock_bh(&ar->data_lock);
			if (ar->vdev_stop_status.stop_in_progress &&
			    ar->vdev_stop_status.vdev_id == vdev_id) {
				ar->vdev_stop_status.stop_in_progress = false;
				spin_unlock_bh(&ar->data_lock);
				return ar;
			}
			spin_unlock_bh(&ar->data_lock);
		}
	}
	return NULL;
}

static void ath11k_pdev_caps_update(struct ath11k *ar)
{
	struct ath11k_base *ab = ar->ab;

	ar->max_tx_power = ab->target_caps.hw_max_tx_power;

	/* FIXME Set min_tx_power to ab->target_caps.hw_min_tx_power.
	 * But since the received value in svcrdy is same as hw_max_tx_power,
	 * we can set ar->min_tx_power to 0 currently until
	 * this is fixed in firmware
	 */
	ar->min_tx_power = 0;

	ar->txpower_limit_2g = ar->max_tx_power;
	ar->txpower_limit_5g = ar->max_tx_power;
	ar->txpower_scale = WMI_HOST_TP_SCALE_MAX;
}

static int ath11k_mac_txpower_recalc(struct ath11k *ar)
{
	struct ath11k_pdev *pdev = ar->pdev;
	struct ath11k_vif *arvif;
	int ret, txpower = -1;
	u32 param;

	lockdep_assert_held(&ar->conf_mutex);

	list_for_each_entry(arvif, &ar->arvifs, struct ath11k_vif, list) {
		if (arvif->txpower <= 0)
			continue;

		if (txpower == -1)
			txpower = arvif->txpower;
		else
			txpower = min(txpower, arvif->txpower);
	}

	if (txpower == -1)
		return 0;

	/* txpwr is set as 2 units per dBm in FW*/
	txpower = min_t(u32, max_t(u32, ar->min_tx_power, txpower),
			ar->max_tx_power) * 2;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "txpower to set in hw %d\n",
		   txpower / 2);

	if ((pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP) &&
	    ar->txpower_limit_2g != (u32)txpower) {
		param = WMI_PDEV_PARAM_TXPOWER_LIMIT2G;
		ret = ath11k_wmi_pdev_set_param(ar, param,
						txpower, ar->pdev->pdev_id);
		if (ret)
			goto fail;
		ar->txpower_limit_2g = txpower;
	}

	if ((pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP) &&
	    ar->txpower_limit_5g != (u32)txpower) {
		param = WMI_PDEV_PARAM_TXPOWER_LIMIT5G;
		ret = ath11k_wmi_pdev_set_param(ar, param,
						txpower, ar->pdev->pdev_id);
		if (ret)
			goto fail;
		ar->txpower_limit_5g = txpower;
	}

	return 0;

fail:
	ath11k_warn(ar->ab, "failed to recalc txpower limit %d using pdev param %d: %d\n",
		    txpower / 2, param, ret);
	return ret;
}

static int ath11k_recalc_rtscts_prot(struct ath11k_vif *arvif)
{
	struct ath11k *ar = arvif->ar;
	u32 vdev_param, rts_cts = 0;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	vdev_param = WMI_VDEV_PARAM_ENABLE_RTSCTS;

	/* Enable RTS/CTS protection for sw retries (when legacy stations
	 * are in BSS) or by default only for second rate series.
	 * TODO: Check if we need to enable CTS 2 Self in any case
	 */
	rts_cts = WMI_USE_RTS_CTS;

	if (arvif->num_legacy_stations > 0)
		rts_cts |= WMI_RTSCTS_ACROSS_SW_RETRIES << 4;
	else
		rts_cts |= WMI_RTSCTS_FOR_SECOND_RATESERIES << 4;

	/* Need not send duplicate param value to firmware */
	if (arvif->rtscts_prot_mode == rts_cts)
		return 0;

	arvif->rtscts_prot_mode = rts_cts;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %d recalc rts/cts prot %d\n",
		   arvif->vdev_id, rts_cts);

	ret =  ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					     vdev_param, rts_cts);
	if (ret)
		ath11k_warn(ar->ab, "failed to recalculate rts/cts prot for vdev %d: %d\n",
			    arvif->vdev_id, ret);

	return ret;
}

static int ath11k_mac_set_kickout(struct ath11k_vif *arvif)
{
	struct ath11k *ar = arvif->ar;
	u32 param;
	int ret;

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_STA_KICKOUT_TH,
					ATH11K_KICKOUT_THRESHOLD,
					ar->pdev->pdev_id);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set kickout threshold on vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MIN_IDLE_INACTIVE_TIME_SECS;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, param,
					    ATH11K_KEEPALIVE_MIN_IDLE);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set keepalive minimum idle time on vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MAX_IDLE_INACTIVE_TIME_SECS;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, param,
					    ATH11K_KEEPALIVE_MAX_IDLE);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set keepalive maximum idle time on vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MAX_UNRESPONSIVE_TIME_SECS;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, param,
					    ATH11K_KEEPALIVE_MAX_UNRESPONSIVE);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set keepalive maximum unresponsive time on vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}

void ath11k_mac_peer_cleanup_all(struct ath11k *ar)
{
	struct ath11k_peer *peer, *tmp;
	struct ath11k_base *ab = ar->ab;

	lockdep_assert_held(&ar->conf_mutex);

	spin_lock_bh(&ab->base_lock);
	list_for_each_entry_safe(peer, tmp, &ab->peers, struct ath11k_peer, list) {
		ath11k_peer_rx_tid_cleanup(ar, peer);
		list_del(&peer->list);
		kfree(peer);
	}
	spin_unlock_bh(&ab->base_lock);

	ar->num_peers = 0;
	ar->num_stations = 0;
}

static int ath11k_monitor_vdev_up(struct ath11k *ar, int vdev_id)
{
	int ret = 0;

	ret = ath11k_wmi_vdev_up(ar, vdev_id, 0, ar->mac_addr);
	if (ret) {
		ath11k_warn(ar->ab, "failed to put up monitor vdev %d: %d\n",
			    vdev_id, ret);
		return ret;
	}

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac monitor vdev %d started\n",
		   vdev_id);
	return 0;
}

static int ath11k_mac_vif_setup_ps(struct ath11k_vif *arvif)
{
	struct ath11k *ar = arvif->ar;
	struct ieee80211_vif *vif = arvif->vif;
	enum wmi_sta_powersave_param param;
	enum wmi_sta_ps_mode psmode;
	int ret;
	int ps_timeout;
	bool enable_ps;

	lockdep_assert_held(&arvif->ar->conf_mutex);

	if (ieee80211_vif_type(arvif->vif) != NL80211_IFTYPE_STATION)
		return 0;

	enable_ps = arvif->ps;

	/* need to check if multiple vdev ps setting is supported */

	if (!arvif->is_started) {
		/* mac80211 can update vif powersave state while disconnected.
		 * Firmware doesn't behave nicely and consumes more power than
		 * necessary if PS is disabled on a non-started vdev. Hence
		 * force-enable PS for non-running vdevs.
		 */
		psmode = WMI_STA_PS_MODE_ENABLED;
	} else if (enable_ps) {
		psmode = WMI_STA_PS_MODE_ENABLED;
		param = WMI_STA_PS_PARAM_INACTIVITY_TIME;

		ps_timeout = ieee80211_hw_get_dynamic_ps_timeout(ar->hw);
		if (ps_timeout == 0) {
			/* Firmware doesn't like 0 */
			ps_timeout = ieee80211_tu_to_usec (
                ieee80211_vif_bss_conf_get_beacon_interval(vif)) / 1000;
		}

		ret = ath11k_wmi_set_sta_ps_param(ar, arvif->vdev_id, param,
						  ps_timeout);
		if (ret) {
			ath11k_warn(ar->ab, "failed to set inactivity time for vdev %d: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}
	} else {
		psmode = WMI_STA_PS_MODE_DISABLED;
	}

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %d psmode %a\n",
		   arvif->vdev_id, psmode ? "enable" : "disable");
	ret = ath11k_wmi_set_psmode(ar, arvif->vdev_id, psmode);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set PS Mode %d for vdev %d: %d\n",
			    psmode, arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}

static int ath11k_config_ps(struct ath11k *ar)
{
	struct ath11k_vif *arvif;
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	list_for_each_entry(arvif, &ar->arvifs, struct ath11k_vif, list) {
		ret = ath11k_mac_vif_setup_ps(arvif);
		if (ret) {
			ath11k_warn(ar->ab, "failed to setup powersave: %d\n", ret);
			break;
		}
	}

	return ret;
}

static int ath11k_mac_op_config(struct ieee80211_hw *hw, u32 changed)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	int ret = 0;

	/* mac80211 requires this op to be present and that's why
	 * there's an empty function, this can be extended when
	 * required.
	 */

	mutex_lock(&ar->conf_mutex);
	if (changed & IEEE80211_CONF_CHANGED_PS)
		ath11k_config_ps(ar);
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

#if 0
static int ath11k_mac_setup_bcn_tmpl(struct ath11k_vif *arvif)
{
	struct ath11k *ar = arvif->ar;
	struct ath11k_base *ab = ar->ab;
	struct ieee80211_hw *hw = ar->hw;
	struct ieee80211_vif *vif = arvif->vif;
	struct ieee80211_mutable_offsets offs = { 0 };
	struct sk_buff *bcn;
	int ret;

	if (arvif->vdev_type != WMI_VDEV_TYPE_AP)
		return 0;

	bcn = ieee80211_beacon_get_template(hw, vif, &offs);
	if (!bcn) {
		ath11k_warn(ab, "failed to get beacon template from mac80211\n");
		return -EPERM;
	}

	ret = ath11k_wmi_bcn_tmpl(ar, arvif->vdev_id, &offs, bcn);

	kfree_skb(bcn);

	if (ret)
		ath11k_warn(ab, "failed to submit beacon template command: %d\n",
			    ret);

	return ret;
}

static void ath11k_control_beaconing(struct ath11k_vif *arvif,
				     struct ieee80211_bss_conf *info)
{
	struct ath11k *ar = arvif->ar;
	int ret = 0;

	lockdep_assert_held(&arvif->ar->conf_mutex);

	if (!info->enable_beacon) {
		ret = ath11k_wmi_vdev_down(ar, arvif->vdev_id);
		if (ret)
			ath11k_warn(ar->ab, "failed to down vdev_id %d: %d\n",
				    arvif->vdev_id, ret);

		arvif->is_up = false;
		return;
	}

	/* Install the beacon template to the FW */
	ret = ath11k_mac_setup_bcn_tmpl(arvif);
	if (ret) {
		ath11k_warn(ar->ab, "failed to update bcn tmpl during vdev up: %d\n",
			    ret);
		return;
	}

	arvif->tx_seq_no = 0x1000;

	arvif->aid = 0;

	ether_addr_copy(arvif->bssid, info->bssid);

	ret = ath11k_wmi_vdev_up(arvif->ar, arvif->vdev_id, arvif->aid,
				 arvif->bssid);
	if (ret) {
		ath11k_warn(ar->ab, "failed to bring up vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return;
	}

	arvif->is_up = true;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %d up\n", arvif->vdev_id);
}

#endif

static void ath11k_mac_handle_beacon_iter(void *data, const u8 *mac,
					  struct ieee80211_vif *vif)
{
	struct sk_buff *skb = data;
	struct ieee80211_mgmt *mgmt = (void *)skb->data;
    struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);

	if (ieee80211_vif_type(vif) != NL80211_IFTYPE_STATION)
		return;

	if (!ether_addr_equal(mgmt->bssid, ieee80211_vif_bss_conf_get_bssid(vif)))
		return;

	cancel_delayed_work(&arvif->connection_loss_work);
}

void ath11k_mac_handle_beacon(struct ath11k *ar, struct sk_buff *skb)
{
	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   IEEE80211_VIF_ITER_NORMAL,
						   ath11k_mac_handle_beacon_iter,
						   skb);
}

static void ath11k_mac_handle_beacon_miss_iter(void *data, const u8 *mac,
					       struct ieee80211_vif *vif)
{
	u32 *vdev_id = data;
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ath11k *ar = arvif->ar;
	struct ieee80211_hw *hw = ar->hw;

	if (arvif->vdev_id != *vdev_id)
		return;

	if (!arvif->is_up)
		return;

	ieee80211_beacon_loss(vif);

	/* Firmware doesn't report beacon loss events repeatedly. If AP probe
	 * (done by mac80211) succeeds but beacons do not resume then it
	 * doesn't make sense to continue operation. Queue connection loss work
	 * which can be cancelled when beacon is received.
	 */
	ieee80211_queue_delayed_work(hw, &arvif->connection_loss_work,
				     ATH11K_CONNECTION_LOSS_HZ);
}

void ath11k_mac_handle_beacon_miss(struct ath11k *ar, u32 vdev_id)
{
	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   IEEE80211_VIF_ITER_NORMAL,
						   ath11k_mac_handle_beacon_miss_iter,
						   &vdev_id);
}

static void ath11k_mac_vif_sta_connection_loss_work(void *context)
{
	struct ath11k_vif *arvif = context;
	struct ieee80211_vif *vif = arvif->vif;

	if (!arvif->is_up)
		return;

	ieee80211_connection_loss(vif);
}

static void ath11k_peer_assoc_h_basic(struct ath11k *ar,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta,
				      struct peer_assoc_params *arg)
{
    struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	u32 aid;

	lockdep_assert_held(&ar->conf_mutex);

    if (ieee80211_vif_type(vif) == NL80211_IFTYPE_STATION)
        aid = ieee80211_vif_bss_conf_get_aid(vif);
    else
        aid = ieee80211_sta_get_aid(sta);

	ether_addr_copy(arg->peer_mac, ieee80211_sta_addr(sta));
	arg->vdev_id = arvif->vdev_id;
	arg->peer_associd = aid;
	arg->auth_flag = true;
	/* TODO: STA WAR in ath10k for listen interval required? */
	arg->peer_listen_intval = ieee80211_hw_get_listen_interval(ar->hw);
	arg->peer_nss = 1;
	arg->peer_caps = ieee80211_vif_bss_conf_get_assoc_capability(vif);
}

static void ath11k_peer_assoc_h_crypto(struct ath11k *ar,
				       struct ieee80211_vif *vif,
				       struct ieee80211_sta *sta,
				       struct peer_assoc_params *arg)
{
	struct ieee80211_chan_def def;
	struct ieee80211_bss *bss;
	const u8 *rsnie = NULL;
	const u8 *wpaie = NULL;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath11k_mac_vif_chan(vif, &def)))
		return;

	bss = ieee80211_get_bss(ar->hw, def.chan, 
        ieee80211_vif_bss_conf_get_bssid(vif), NULL, 0,
        IEEE80211_BSS_TYPE_ANY, IEEE80211_PRIVACY_ANY);
	if (bss) {
		rcu_read_lock();
		rsnie = ieee80211_bss_get_ie(bss, WLAN_EID_RSN);

		wpaie = ieee80211_bss_find_vendor_ie(bss, WLAN_OUI_MICROSOFT_WPA);
		rcu_read_unlock();
		ieee80211_put_bss(ar->hw, bss);
	}

	/* FIXME: base on RSN IE/WPA IE is a correct idea? */
	if (rsnie || wpaie) {
		ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "rsn ie found\n", __func__);
		arg->need_ptk_4_way = true;
	}

	if (wpaie) {
		ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "wpa ie found\n");
		arg->need_gtk_2_way = true;
	}

	if (ieee80211_sta_get_mfp(sta)) {
		/* TODO: Need to check if FW supports PMF? */
		arg->is_pmf_enabled = true;
	}

	/* TODO: safe_mode_enabled (bypass 4-way handshake) flag req? */
}

static void ath11k_peer_assoc_h_rates(struct ath11k *ar,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta,
				      struct peer_assoc_params *arg)
{
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct wmi_rate_set_arg *rateset = &arg->peer_legacy_rates;
	struct ieee80211_chan_def def;
	const struct ieee80211_supported_band *sband;
	const struct ieee80211_rate *rates;
	enum nl80211_band band;
	u32 ratemask;
	u8 rate;
	int i;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath11k_mac_vif_chan(vif, &def)))
		return;

	band = def.chan->band;
	sband = ieee80211_hw_get_sband(ar->hw, band);
	if (sband == NULL)
		return;

	ratemask = ieee80211_sta_get_supp_rates(sta, band);
	ratemask &= arvif->bitrate_mask.control[band].legacy;
	rates = sband->bitrates;

	rateset->num_rates = 0;

	for (i = 0; i < 32; i++, ratemask >>= 1, rates++) {
		if (!(ratemask & 1))
			continue;

		rate = ath11k_mac_bitrate_to_rate(rates->bitrate);
		rateset->rates[rateset->num_rates] = rate;
		rateset->num_rates++;
	}
}

static bool
ath11k_peer_assoc_h_ht_masked(const u8 ht_mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
{
	int nss;

	for (nss = 0; nss < IEEE80211_HT_MCS_MASK_LEN; nss++)
		if (ht_mcs_mask[nss])
			return false;

	return true;
}

static bool
ath11k_peer_assoc_h_vht_masked(const u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
{
	int nss;

	for (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++)
		if (vht_mcs_mask[nss])
			return false;

	return true;
}

static void ath11k_peer_assoc_h_ht(struct ath11k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta,
				   struct peer_assoc_params *arg)
{
	const struct ieee80211_sta_ht_cap *ht_cap = ieee80211_sta_get_ht_cap(sta);
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	int i, n;
	u8 max_nss;
	u32 stbc;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath11k_mac_vif_chan(vif, &def)))
		return;

	if (!ht_cap->ht_supported)
		return;

	band = def.chan->band;
	ht_mcs_mask = arvif->bitrate_mask.control[band].ht_mcs;

	if (ath11k_peer_assoc_h_ht_masked(ht_mcs_mask))
		return;

	arg->ht_flag = true;

	arg->peer_max_mpdu = (1 << (IEEE80211_HT_MAX_AMPDU_FACTOR +
				    ht_cap->ampdu_factor)) - 1;

	arg->peer_mpdu_density =
		ath11k_parse_mpdudensity(ht_cap->ampdu_density);

	arg->peer_ht_caps = ht_cap->cap;
	arg->peer_rate_caps |= WMI_HOST_RC_HT_FLAG;

	if (ht_cap->cap & IEEE80211_HTCAP_LDPC_CODING)
		arg->ldpc_flag = true;

	if (ieee80211_sta_get_bandwidth(sta) >= IEEE80211_STA_RX_BANDWIDTH_40) {
		arg->bw_40 = true;
		arg->peer_rate_caps |= WMI_HOST_RC_CW40_FLAG;
	}

	if (arvif->bitrate_mask.control[band].gi != NL80211_TXRATE_FORCE_LGI) {
		if (ht_cap->cap & (IEEE80211_HTCAP_SGI_20 |
		    IEEE80211_HTCAP_SGI_40))
			arg->peer_rate_caps |= WMI_HOST_RC_SGI_FLAG;
	}

	if (ht_cap->cap & IEEE80211_HTCAP_TX_STBC) {
		arg->peer_rate_caps |= WMI_HOST_RC_TX_STBC_FLAG;
		arg->stbc_flag = true;
	}

	if (ht_cap->cap & IEEE80211_HTCAP_RX_STBC) {
		stbc = ht_cap->cap & IEEE80211_HTCAP_RX_STBC;
		stbc = stbc >> IEEE80211_HTCAP_RX_STBC_SHIFT;
		stbc = stbc << WMI_HOST_RC_RX_STBC_FLAG_S;
		arg->peer_rate_caps |= stbc;
		arg->stbc_flag = true;
	}

	if (ht_cap->mcs.rx_mask[1] && ht_cap->mcs.rx_mask[2])
		arg->peer_rate_caps |= WMI_HOST_RC_TS_FLAG;
	else if (ht_cap->mcs.rx_mask[1])
		arg->peer_rate_caps |= WMI_HOST_RC_DS_FLAG;

	for (i = 0, n = 0, max_nss = 0; i < IEEE80211_HT_MCS_MASK_LEN * 8; i++)
		if ((ht_cap->mcs.rx_mask[i / 8] & BIT(i % 8)) &&
		    (ht_mcs_mask[i / 8] & BIT(i % 8))) {
			max_nss = (u8)((i / 8) + 1);
			arg->peer_ht_rates.rates[n++] = (u8)i;
		}

	/* This is a workaround for HT-enabled STAs which break the spec
	 * and have no HT capabilities RX mask (no HT RX MCS map).
	 *
	 * As per spec, in section 20.3.5 Modulation and coding scheme (MCS),
	 * MCS 0 through 7 are mandatory in 20MHz with 800 ns GI at all STAs.
	 *
	 * Firmware asserts if such situation occurs.
	 */
	if (n == 0) {
		arg->peer_ht_rates.num_rates = 8;
		for (i = 0; i < (int)arg->peer_ht_rates.num_rates; i++)
			arg->peer_ht_rates.rates[i] = (u8)i;
	} else {
		arg->peer_ht_rates.num_rates = n;
		arg->peer_nss = min(ieee80211_sta_get_rx_nss(sta), max_nss);
	}

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac ht peer %pM mcs cnt %d nss %d\n",
		   arg->peer_mac,
		   arg->peer_ht_rates.num_rates,
		   arg->peer_nss);
}

static int ath11k_mac_get_max_vht_mcs_map(u16 mcs_map, int nss)
{
	switch ((mcs_map >> (2 * nss)) & 0x3) {
	case IEEE80211_VHTCAP_MCS_SUPPORT_0_7: return BIT(8) - 1;
	case IEEE80211_VHTCAP_MCS_SUPPORT_0_8: return BIT(9) - 1;
	case IEEE80211_VHTCAP_MCS_SUPPORT_0_9: return BIT(10) - 1;
	}
	return 0;
}

static u16
ath11k_peer_assoc_h_vht_limit(u16 tx_mcs_set,
			      const u16 vht_mcs_limit[NL80211_VHT_NSS_MAX])
{
	int idx_limit;
	int nss;
	u16 mcs_map;
	u16 mcs;

	for (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++) {
		mcs_map = ath11k_mac_get_max_vht_mcs_map(tx_mcs_set, nss) &
			  vht_mcs_limit[nss];

		if (mcs_map)
			idx_limit = fls(mcs_map) - 1;
		else
			idx_limit = -1;

		switch (idx_limit) {
		case 0: /* fall through */
		case 1: /* fall through */
		case 2: /* fall through */
		case 3: /* fall through */
		case 4: /* fall through */
		case 5: /* fall through */
		case 6: /* fall through */
		case 7:
			mcs = IEEE80211_VHTCAP_MCS_SUPPORT_0_7;
			break;
		case 8:
			mcs = IEEE80211_VHTCAP_MCS_SUPPORT_0_8;
			break;
		case 9:
			mcs = IEEE80211_VHTCAP_MCS_SUPPORT_0_9;
			break;
		default:
			WARN_ON(1);
			/* fall through */
		case -1:
			mcs = IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;
			break;
		}

		tx_mcs_set &= ~(0x3 << (nss * 2));
		tx_mcs_set |= mcs << (nss * 2);
	}

	return tx_mcs_set;
}

static void ath11k_peer_assoc_h_vht(struct ath11k *ar,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta,
				    struct peer_assoc_params *arg)
{
	const struct ieee80211_sta_vht_cap *vht_cap = ieee80211_sta_get_vht_cap(sta);
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	const u16 *vht_mcs_mask;
	u8 ampdu_factor;
	u8 max_nss, vht_mcs;
	int i;

	if (WARN_ON(ath11k_mac_vif_chan(vif, &def)))
		return;

	if (!vht_cap->vht_supported)
		return;

	band = def.chan->band;
	vht_mcs_mask = arvif->bitrate_mask.control[band].vht_mcs;

	if (ath11k_peer_assoc_h_vht_masked(vht_mcs_mask))
		return;

	arg->vht_flag = true;

	/* TODO: similar flags required? */
	arg->vht_capable = true;

	if (def.chan->band == NL80211_BAND_2GHZ)
		arg->vht_ng_flag = true;

	arg->peer_vht_caps = vht_cap->cap;

	ampdu_factor = (u8)((vht_cap->cap &
			IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK) >>
		       IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT);

	/* Workaround: Some Netgear/Linksys 11ac APs set Rx A-MPDU factor to
	 * zero in VHT IE. Using it would result in degraded throughput.
	 * arg->peer_max_mpdu at this point contains HT max_mpdu so keep
	 * it if VHT max_mpdu is smaller.
	 */
	arg->peer_max_mpdu = max(arg->peer_max_mpdu,
				 (1U << (IEEE80211_HT_MAX_AMPDU_FACTOR +
					ampdu_factor)) - 1);

	if (ieee80211_sta_get_bandwidth(sta) == IEEE80211_STA_RX_BANDWIDTH_80)
		arg->bw_80 = true;

	if (ieee80211_sta_get_bandwidth(sta) == IEEE80211_STA_RX_BANDWIDTH_160)
		arg->bw_160 = true;

	/* Calculate peer NSS capability from VHT capabilities if STA
	 * supports VHT.
	 */
	for (i = 0, max_nss = 0, vht_mcs = 0; i < NL80211_VHT_NSS_MAX; i++) {
		vht_mcs = __le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map) >>
			  (2 * i) & 3;

		if (vht_mcs != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED &&
		    vht_mcs_mask[i])
			max_nss = (u8)(i + 1);
	}
	arg->peer_nss = min(ieee80211_sta_get_rx_nss(sta), max_nss);
	arg->rx_max_rate = __le16_to_cpu(vht_cap->vht_mcs.rx_highest);
	arg->rx_mcs_set = __le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map);
	arg->tx_max_rate = __le16_to_cpu(vht_cap->vht_mcs.tx_highest);
	arg->tx_mcs_set = ath11k_peer_assoc_h_vht_limit(
		__le16_to_cpu(vht_cap->vht_mcs.tx_mcs_map), vht_mcs_mask);

	/* In IPQ8074 platform, VHT mcs rate 10 and 11 is enabled by default.
	 * VHT mcs rate 10 and 11 is not suppoerted in 11ac standard.
	 * so explicitly disable the VHT MCS rate 10 and 11 in 11ac mode.
	 */
	arg->tx_mcs_set &= ~IEEE80211_VHT_MCS_SUPPORT_0_11_MASK;
	arg->tx_mcs_set |= IEEE80211_DISABLE_VHT_MCS_SUPPORT_0_11;

	/* TODO:  Check */
	arg->tx_max_mcs_nss = 0xFF;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vht peer %pM max_mpdu %d flags 0x%x\n",
        ieee80211_sta_addr(sta), arg->peer_max_mpdu, arg->peer_flags);

	/* TODO: rxnss_override */
}


static void ath11k_peer_assoc_h_he(struct ath11k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta,
				   struct peer_assoc_params *arg)
{
#if ATH11K_SUPPORT_HE
	const struct ieee80211_sta_he_cap *he_cap = ieee80211_sta_get_he_cap(sta);
	u16 v;
	struct ieee80211_bss_conf* bss_conf = ieee80211_vif_get_bss_conf(vif);
	if (!he_cap->he_supported)
		return;

	arg->he_flag = true;

	memcpy(&arg->peer_he_cap_macinfo, he_cap->he_capabilities.mac_cap_info,
	       sizeof(arg->peer_he_cap_macinfo));
	memcpy(&arg->peer_he_cap_phyinfo, he_cap->he_capabilities.phy_cap_info,
	       sizeof(arg->peer_he_cap_phyinfo));
	memcpy(&arg->peer_he_ops, ieee80211_bss_conf_get_he_operation(bss_conf),
	       sizeof(arg->peer_he_ops));

	/* the top most byte is used to indicate BSS color info */
	arg->peer_he_ops &= 0xffffff;

	if (he_cap->he_capabilities.phy_cap_info[6] &
	    IEEE80211_HEPHY_CAP6_PPE_THRESHOLD_PRESENT) {
		int bit = 7;
		u32 nss, ru;

		arg->peer_ppet.numss_m1 = he_cap->ppe_thres[0] &
					  IEEE80211_HE_PPE_THRES_NSS_MASK;
		arg->peer_ppet.ru_bit_mask =
			(he_cap->ppe_thres[0] &
			 IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_MASK) >>
			IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_POS;

		for (nss = 0; nss <= arg->peer_ppet.numss_m1; nss++) {
			for (ru = 0; ru < 4; ru++) {
				u32 val = 0;
				int i;

				if ((arg->peer_ppet.ru_bit_mask & BIT(ru)) == 0)
					continue;
				for (i = 0; i < 6; i++) {
					val >>= 1;
					val |= ((he_cap->ppe_thres[bit / 8] >>
						 (bit % 8)) & 0x1) << 5;
					bit++;
				}
				arg->peer_ppet.ppet16_ppet8_ru3_ru0[nss] |=
								val << (ru * 6);
			}
		}
	}

	if (he_cap->he_capabilities.mac_cap_info[0] & IEEE80211_HEMAC_CAP0_TWT_RES)
		arg->twt_responder = true;
	if (he_cap->he_capabilities.mac_cap_info[0] & IEEE80211_HEMAC_CAP0_TWT_REQ)
		arg->twt_requester = true;

	switch (ieee80211_sta_get_bandwidth(sta)) {
	case IEEE80211_STA_RX_BANDWIDTH_160:
		if (he_cap->he_capabilities.phy_cap_info[0] &
		    IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G) {
			v = le16_to_cpu(he_cap->he_mcs_nss_supp.he_rx_mcs_80p80);
			arg->peer_he_rx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80_80] = v;

			v = le16_to_cpu(he_cap->he_mcs_nss_supp.he_tx_mcs_80p80);
			arg->peer_he_tx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80_80] = v;

			arg->peer_he_mcs_count++;
		}
		v = le16_to_cpu(he_cap->he_mcs_nss_supp.he_rx_mcs_160);
		arg->peer_he_rx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_160] = v;

		v = le16_to_cpu(he_cap->he_mcs_nss_supp.he_tx_mcs_160);
		arg->peer_he_tx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_160] = v;

		arg->peer_he_mcs_count++;
		/* fall through */

	default:
		v = le16_to_cpu(he_cap->he_mcs_nss_supp.he_rx_mcs_80);
		arg->peer_he_rx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80] = v;

		v = le16_to_cpu(he_cap->he_mcs_nss_supp.he_tx_mcs_80);
		arg->peer_he_tx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80] = v;

		arg->peer_he_mcs_count++;
		break;
	}
#endif // !ATH11K_SUPPORT_HE
}

static void ath11k_peer_assoc_h_he_6ghz(struct ath11k *ar,
					struct ieee80211_vif *vif,
					struct ieee80211_sta *sta,
					struct peer_assoc_params *arg)
{
	const struct ieee80211_sta_he_cap *he_cap = ieee80211_sta_get_he_cap(sta);
	struct ieee80211_he_6ghz_cap  *sta_he_6ghz_cap = ieee80211_sta_get_6ghz_cap(sta);
	enum ieee80211_sta_rx_bandwidth sta_bandwidth = ieee80211_sta_get_bandwidth(sta);
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	u8  ampdu_factor;

	if (WARN_ON(ath11k_mac_vif_chan(vif, &def)))
		return;

	band = def.chan->band;

	if (!arg->he_flag || band != NL80211_BAND_6GHZ || !sta_he_6ghz_cap->cap)
		return;

	if (sta_bandwidth >= IEEE80211_STA_RX_BANDWIDTH_40)
		arg->bw_40 = true;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_80)
		arg->bw_80 = true;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_160)
		arg->bw_160 = true;

	arg->peer_he_caps_6ghz = le16_to_cpu(sta_he_6ghz_cap->cap);

	arg->peer_mpdu_density = ath11k_parse_mpdudensity(
		FIELD_GET(IEEE80211_HE_6GHZCAP_MIN_MPDU_START, arg->peer_he_caps_6ghz));

	/* From IEEE P802.11ax/D6.1: An HE STA shall be capable of receiving A-MPDU
	 * where the A-MPDU pre-EOF padding length is up to the value indicated by the
	 * Maximum A-MPDU Length Exponent Extension field in the HE Capabilities element
	 * and the Maximum A-MPDU Length Exponent field in HE 6 GHz Band Capabilities
	 * element in the 6 GHz band.
	 *
	 * Here, we are extracting the Max AMPDU Exponent Extension from HE caps and
	 * ampdu factor is Maximum A-MPDU Length Exponent from HE 6GHZ Band capability.
	 */
	arg->peer_max_mpdu = (he_cap->he_capabilities.mac_cap_info[3] &
			IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_MASK) >>
			IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_SHIFT;

	ampdu_factor = FIELD_GET(IEEE80211_HE_6GHZCAP_MAX_AMPDU_LEN_EXP,
				 arg->peer_he_caps_6ghz);

	arg->peer_max_mpdu = (1u << (IEEE80211_HE_6GHZ_MAX_AMPDU_FACTOR + ampdu_factor +
			      arg->peer_max_mpdu)) - 1;
}

static void ath11k_peer_assoc_h_smps(struct ieee80211_sta *sta,
				     struct peer_assoc_params *arg)
{
	const struct ieee80211_sta_ht_cap *ht_cap = ieee80211_sta_get_ht_cap(sta);
	struct ieee80211_he_6ghz_cap  *sta_he_6ghz_cap = ieee80211_sta_get_6ghz_cap(sta);
	int smps;

	if (!ht_cap->ht_supported && !sta_he_6ghz_cap->cap)
		return;

	if (ht_cap->ht_supported) {
		smps = ht_cap->cap & IEEE80211_HTCAP_SM_PS;
		smps >>= IEEE80211_HTCAP_SM_PS_SHIFT;
	}

	if (sta_he_6ghz_cap->cap)
		smps = FIELD_GET(IEEE80211_HE_6GHZCAP_SM_PS, 
		         le16_to_cpu(sta_he_6ghz_cap->cap));

	switch (smps) {
	case WLAN_HTCAP_SM_PS_STATIC:
		arg->static_mimops_flag = true;
		break;
	case WLAN_HTCAP_SM_PS_DYNAMIC:
		arg->dynamic_mimops_flag = true;
		break;
	case WLAN_HTCAP_SM_PS_DISABLED:
		arg->spatial_mux_flag = true;
		break;
	default:
		break;
	}
}

static void ath11k_peer_assoc_h_qos(struct ath11k *ar,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta,
				    struct peer_assoc_params *arg)
{
    struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
    bool sta_wme;
    u8 sta_uapsd_queues;

	switch (arvif->vdev_type) {
	case WMI_VDEV_TYPE_AP:
        sta_wme = ieee80211_sta_get_wme(sta);
        sta_uapsd_queues = ieee80211_sta_get_uapsd_queues(sta);
		if (sta_wme) {
			/* TODO: Check WME vs QoS */
			arg->is_wme_set = true;
			arg->qos_flag = true;
		}

		if (sta_wme && sta_uapsd_queues) {
			/* TODO: Check WME vs QoS */
			arg->is_wme_set = true;
			arg->apsd_flag = true;
			arg->peer_rate_caps |= WMI_HOST_RC_UAPSD_FLAG;
		}
		break;
	case WMI_VDEV_TYPE_STA:
        sta_wme = ieee80211_sta_get_wme(sta);
		if (sta_wme) {
			arg->is_wme_set = true;
			arg->qos_flag = true;
		}
		break;
	default:
		break;
	}

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac peer %pM qos %d\n",
        ieee80211_sta_addr(sta), arg->qos_flag);
}

static int ath11k_peer_assoc_qos_ap(struct ath11k *ar,
				    struct ath11k_vif *arvif,
				    struct ieee80211_sta *sta)
{
	struct ap_ps_params params;
    const u8 *sta_addr;
    u8 sta_uapsd_queues, sta_max_sp;
	u32 max_sp;
	u32 uapsd;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	params.vdev_id = arvif->vdev_id;

    sta_uapsd_queues = ieee80211_sta_get_uapsd_queues(sta);
    sta_max_sp = ieee80211_sta_get_max_sp(sta);
	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac uapsd_queues 0x%x max_sp %d\n",
		   sta_uapsd_queues, sta_max_sp);

	uapsd = 0;
	if (sta_uapsd_queues & IEEE80211_WMM_IE_STA_UAPSD_VO)
		uapsd |= WMI_AP_PS_UAPSD_AC3_DELIVERY_EN |
			 WMI_AP_PS_UAPSD_AC3_TRIGGER_EN;
	if (sta_uapsd_queues & IEEE80211_WMM_IE_STA_UAPSD_VI)
		uapsd |= WMI_AP_PS_UAPSD_AC2_DELIVERY_EN |
			 WMI_AP_PS_UAPSD_AC2_TRIGGER_EN;
	if (sta_uapsd_queues & IEEE80211_WMM_IE_STA_UAPSD_BK)
		uapsd |= WMI_AP_PS_UAPSD_AC1_DELIVERY_EN |
			 WMI_AP_PS_UAPSD_AC1_TRIGGER_EN;
	if (sta_uapsd_queues & IEEE80211_WMM_IE_STA_UAPSD_BE)
		uapsd |= WMI_AP_PS_UAPSD_AC0_DELIVERY_EN |
			 WMI_AP_PS_UAPSD_AC0_TRIGGER_EN;

	max_sp = 0;
	if (sta_max_sp < MAX_WMI_AP_PS_PEER_PARAM_MAX_SP)
		max_sp = sta_max_sp;

    sta_addr = ieee80211_sta_addr(sta);

	params.param = WMI_AP_PS_PEER_PARAM_UAPSD;
	params.value = uapsd;
	ret = ath11k_wmi_send_set_ap_ps_param_cmd(ar, sta_addr, &params);
	if (ret)
		goto err;

	params.param = WMI_AP_PS_PEER_PARAM_MAX_SP;
	params.value = max_sp;
	ret = ath11k_wmi_send_set_ap_ps_param_cmd(ar, sta_addr, &params);
	if (ret)
		goto err;

	/* TODO revisit during testing */
	params.param = WMI_AP_PS_PEER_PARAM_SIFS_RESP_FRMTYPE;
	params.value = DISABLE_SIFS_RESPONSE_TRIGGER;
	ret = ath11k_wmi_send_set_ap_ps_param_cmd(ar, sta_addr, &params);
	if (ret)
		goto err;

	params.param = WMI_AP_PS_PEER_PARAM_SIFS_RESP_UAPSD;
	params.value = DISABLE_SIFS_RESPONSE_TRIGGER;
	ret = ath11k_wmi_send_set_ap_ps_param_cmd(ar, sta_addr, &params);
	if (ret)
		goto err;

	return 0;

err:
	ath11k_warn(ar->ab, "failed to set ap ps peer param %d for vdev %d: %d\n",
		    params.param, arvif->vdev_id, ret);
	return ret;
}

static bool ath11k_mac_sta_has_ofdm_only(struct ieee80211_sta *sta)
{
	return (bool)(ieee80211_sta_get_supp_rates(sta, NL80211_BAND_2GHZ) >>
	       ATH11K_MAC_FIRST_OFDM_RATE_IDX);
}

static enum wmi_phy_mode ath11k_mac_get_phymode_vht(struct ath11k *ar,
						    struct ieee80211_sta *sta)
{
    enum ieee80211_sta_rx_bandwidth sta_bandwidth = ieee80211_sta_get_bandwidth(sta);
    struct ieee80211_sta_vht_cap *sta_vht_cap = ieee80211_sta_get_vht_cap(sta);

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_160) {
		switch (sta_vht_cap->cap &
			IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK) {
		case IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ:
			return MODE_11AC_VHT160;
		case IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ:
			return MODE_11AC_VHT80_80;
		default:
			/* not sure if this is a valid case? */
			return MODE_11AC_VHT160;
		}
	}

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_80)
		return MODE_11AC_VHT80;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_40)
		return MODE_11AC_VHT40;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_20)
		return MODE_11AC_VHT20;

	return MODE_UNKNOWN;
}

static enum wmi_phy_mode ath11k_mac_get_phymode_he(struct ath11k *ar,
						   struct ieee80211_sta *sta)
{
    enum ieee80211_sta_rx_bandwidth sta_bandwidth = ieee80211_sta_get_bandwidth(sta);
    struct ieee80211_sta_he_cap *sta_he_cap = ieee80211_sta_get_he_cap(sta);

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_160) {
		if (sta_he_cap->he_capabilities.phy_cap_info[0] &
		     IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G)
			return MODE_11AX_HE160;
		else if (sta_he_cap->he_capabilities.phy_cap_info[0] &
		     IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G)
			return MODE_11AX_HE80_80;
		/* not sure if this is a valid case? */
		return MODE_11AX_HE160;
	}

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_80)
		return MODE_11AX_HE80;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_40)
		return MODE_11AX_HE40;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_20)
		return MODE_11AX_HE20;

	return MODE_UNKNOWN;
}

static void ath11k_peer_assoc_h_phymode(struct ath11k *ar,
					struct ieee80211_vif *vif,
					struct ieee80211_sta *sta,
					struct peer_assoc_params *arg)
{
    struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
    struct ieee80211_sta_he_cap *sta_he_cap;
    struct ieee80211_sta_vht_cap *sta_vht_cap;
    struct ieee80211_sta_ht_cap *sta_ht_cap;
    enum ieee80211_sta_rx_bandwidth sta_bandwidth;
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	const u16 *vht_mcs_mask;
	enum wmi_phy_mode phymode = MODE_UNKNOWN;

	if (WARN_ON(ath11k_mac_vif_chan(vif, &def)))
		return;

	band = def.chan->band;
	ht_mcs_mask = arvif->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvif->bitrate_mask.control[band].vht_mcs;

    sta_bandwidth = ieee80211_sta_get_bandwidth(sta);
    sta_he_cap = ieee80211_sta_get_he_cap(sta);
    sta_vht_cap = ieee80211_sta_get_vht_cap(sta);
    sta_ht_cap = ieee80211_sta_get_ht_cap(sta);

	switch (band) {
	case NL80211_BAND_2GHZ:
		if (sta_he_cap->he_supported) {
			if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_80)
				phymode = MODE_11AX_HE80_2G;
			else if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_40)
				phymode = MODE_11AX_HE40_2G;
			else
				phymode = MODE_11AX_HE20_2G;
		} else if (sta_vht_cap->vht_supported &&
		    !ath11k_peer_assoc_h_vht_masked(vht_mcs_mask)) {
			if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_40)
				phymode = MODE_11AC_VHT40;
			else
				phymode = MODE_11AC_VHT20;
		} else if (sta_ht_cap->ht_supported &&
			   !ath11k_peer_assoc_h_ht_masked(ht_mcs_mask)) {
			if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_40)
				phymode = MODE_11NG_HT40;
			else
				phymode = MODE_11NG_HT20;
		} else if (ath11k_mac_sta_has_ofdm_only(sta)) {
			phymode = MODE_11G;
		} else {
			phymode = MODE_11B;
		}
		break;
	case NL80211_BAND_5GHZ:
	case NL80211_BAND_6GHZ:
		/* Check HE first */
		if (sta_he_cap->he_supported) {
			phymode = ath11k_mac_get_phymode_he(ar, sta);
		} else if (sta_vht_cap->vht_supported &&
		    !ath11k_peer_assoc_h_vht_masked(vht_mcs_mask)) {
			phymode = ath11k_mac_get_phymode_vht(ar, sta);
		} else if (sta_ht_cap->ht_supported &&
			   !ath11k_peer_assoc_h_ht_masked(ht_mcs_mask)) {
			if (sta_bandwidth >= IEEE80211_STA_RX_BANDWIDTH_40)
				phymode = MODE_11NA_HT40;
			else
				phymode = MODE_11NA_HT20;
		} else {
			phymode = MODE_11A;
		}
		break;
	default:
		break;
	}

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac peer %pM phymode %a\n",
		   ieee80211_sta_addr(sta), ath11k_wmi_phymode_str(phymode));

	arg->peer_phymode = phymode;
	WARN_ON(phymode == MODE_UNKNOWN);
}

static void ath11k_peer_assoc_prepare(struct ath11k *ar,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta,
				      struct peer_assoc_params *arg,
				      bool reassoc)
{
	lockdep_assert_held(&ar->conf_mutex);

	memset(arg, 0, sizeof(*arg));

	reinit_completion(&ar->peer_assoc_done);

	arg->peer_new_assoc = !reassoc;
	ath11k_peer_assoc_h_basic(ar, vif, sta, arg);
	ath11k_peer_assoc_h_crypto(ar, vif, sta, arg);
	ath11k_peer_assoc_h_rates(ar, vif, sta, arg);
	ath11k_peer_assoc_h_ht(ar, vif, sta, arg);
	ath11k_peer_assoc_h_vht(ar, vif, sta, arg);
	ath11k_peer_assoc_h_he(ar, vif, sta, arg);
	ath11k_peer_assoc_h_he_6ghz(ar, vif, sta, arg);
	ath11k_peer_assoc_h_qos(ar, vif, sta, arg);
	ath11k_peer_assoc_h_phymode(ar, vif, sta, arg);
	ath11k_peer_assoc_h_smps(sta, arg);

	/* TODO: amsdu_disable req? */
}

static int ath11k_setup_peer_smps(struct ath11k *ar, struct ath11k_vif *arvif,
				  const u8 *addr,
				  const struct ieee80211_sta_ht_cap *ht_cap,
				  u16 he_6ghz_capa)
{
	int smps;

	if (ht_cap == NULL)
		return -EINVAL;

	if (!(ht_cap && ht_cap->ht_supported) && !ar->supports_6ghz)
		return 0;

	
	if (ht_cap->ht_supported) {
		smps = ht_cap->cap & IEEE80211_HTCAP_SM_PS;
		smps >>= IEEE80211_HTCAP_SM_PS_SHIFT;
	} else {
		smps = FIELD_GET(IEEE80211_HE_6GHZCAP_SM_PS, he_6ghz_capa);
	}


	if (smps >= ARRAY_SIZE(ath11k_smps_map))
		return -EINVAL;

	return ath11k_wmi_set_peer_param(ar, addr, arvif->vdev_id,
					 WMI_PEER_MIMO_PS_STATE,
					 ath11k_smps_map[smps]);
}

static void ath11k_bss_assoc(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif,
			     struct ieee80211_bss_conf *bss_conf)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
    struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ieee80211_he_6ghz_cap *sta_6ghz_cap;
	struct peer_assoc_params peer_arg;
	struct ieee80211_sta *ap_sta;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %d assoc bssid %pM aid %d\n",
		   arvif->vdev_id, arvif->bssid, arvif->aid);

	rcu_read_lock();

	ap_sta = ieee80211_find_sta(vif, ieee80211_bss_conf_get_bssid(bss_conf));
	if (!ap_sta) {
		ath11k_warn(ar->ab, "failed to find station entry for bss %pM vdev %u\n",
            ieee80211_bss_conf_get_bssid(bss_conf), arvif->vdev_id);
		rcu_read_unlock();
		return;
	}

	ath11k_peer_assoc_prepare(ar, vif, ap_sta, &peer_arg, false);

	rcu_read_unlock();

	ret = ath11k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
	if (ret) {
		ath11k_warn(ar->ab, "failed to run peer assoc for %pM vdev %d: %d\n",
            ieee80211_bss_conf_get_bssid(bss_conf), arvif->vdev_id, ret);
		return;
	}

	if (!wait_for_completion_timeout(&ar->peer_assoc_done, 1 * HZ)) {
		ath11k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %d\n",
            ieee80211_bss_conf_get_bssid(bss_conf), arvif->vdev_id);
		return;
	}

    sta_6ghz_cap = ieee80211_sta_get_6ghz_cap(ap_sta);
	ret = ath11k_setup_peer_smps(ar, arvif, 
        ieee80211_bss_conf_get_bssid(bss_conf),
        ieee80211_sta_get_ht_cap(ap_sta),
        sta_6ghz_cap->cap);
	if (ret) {
		ath11k_warn(ar->ab, "failed to setup peer SMPS for vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return;
	}

	WARN_ON(arvif->is_up);

	arvif->aid = ieee80211_bss_conf_get_aid(bss_conf);
	ether_addr_copy(arvif->bssid, ieee80211_bss_conf_get_bssid(bss_conf));

	ret = ath11k_wmi_vdev_up(ar, arvif->vdev_id, arvif->aid, arvif->bssid);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set vdev %d up: %d\n",
			    arvif->vdev_id, ret);
		return;
	}

	arvif->is_up = true;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
        "mac vdev %d up (associated) bssid %pM aid %d\n",
        arvif->vdev_id, 
        ieee80211_bss_conf_get_bssid(bss_conf), 
        ieee80211_bss_conf_get_aid(bss_conf));

	/* Authorize BSS Peer */
	ret = ath11k_wmi_set_peer_param(ar, arvif->bssid,
					arvif->vdev_id,
					WMI_PEER_AUTHORIZE,
					1);
	if (ret)
		ath11k_warn(ar->ab, "Unable to authorize BSS peer: %d\n", ret);

#if ATH11K_SUPPORT_HE
	ret = ath11k_wmi_send_obss_spr_cmd(ar, arvif->vdev_id,
		ieee80211_bss_conf_get_he_obss_pd(bss_conf));
	if (ret)
		ath11k_warn(ar->ab, "failed to set vdev %d OBSS PD parameters: %d\n",
			    arvif->vdev_id, ret);
#endif

    ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    WMI_VDEV_PARAM_DTIM_POLICY,
					    STICK_DTIM);
	if (ret)
		ath11k_warn(ar->ab, "failed to set vdev %d dtim policy: %d\n",
			    arvif->vdev_id, ret);

	ath11k_mac_11d_scan_stop_all(ar->ab);
}

static void ath11k_bss_disassoc(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %d disassoc bssid %pM\n",
		   arvif->vdev_id, arvif->bssid);

	ret = ath11k_wmi_vdev_down(ar, arvif->vdev_id);
	if (ret)
		ath11k_warn(ar->ab, "failed to down vdev %d: %d\n",
			    arvif->vdev_id, ret);

	arvif->def_wep_key_idx = -1;
	arvif->is_up = false;

	cancel_delayed_work_sync(&arvif->connection_loss_work);
}

static u32 ath11k_mac_get_rate_hw_value(int bitrate)
{
	u32 preamble;
	u16 hw_value;
	int rate;
	size_t i;

	if (ath11k_mac_bitrate_is_cck(bitrate))
		preamble = WMI_RATE_PREAMBLE_CCK;
	else
		preamble = WMI_RATE_PREAMBLE_OFDM;

	for (i = 0; i < ARRAY_SIZE(ath11k_legacy_rates); i++) {
		if (ath11k_legacy_rates[i].bitrate != bitrate)
			continue;

		hw_value = ath11k_legacy_rates[i].hw_value;
		rate = ATH11K_HW_RATE_CODE(hw_value, 0, preamble);

		return rate;
	}

	return (u32)-EINVAL;
}

static void ath11k_recalculate_mgmt_rate(struct ath11k *ar,
					 struct ieee80211_vif *vif,
					 struct ieee80211_chan_def *def)
{
    struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	const struct ieee80211_supported_band *sband;
	u8 basic_rate_idx;
	int hw_rate_code;
	u32 vdev_param;
	u16 bitrate;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

    sband = ieee80211_hw_get_sband(ar->hw, def->chan->band);
	if (sband == NULL)
		return;

	basic_rate_idx = (u8)(ffs(ieee80211_vif_bss_conf_get_basic_rates(vif)) - 1);
	bitrate = sband->bitrates[basic_rate_idx].bitrate;

	hw_rate_code = ath11k_mac_get_rate_hw_value(bitrate);
	if (hw_rate_code < 0) {
		ath11k_warn(ar->ab, "bitrate not supported %d\n", bitrate);
		return;
	}

	vdev_param = WMI_VDEV_PARAM_MGMT_RATE;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, vdev_param,
					    hw_rate_code);
	if (ret)
		ath11k_warn(ar->ab, "failed to set mgmt tx rate %d\n", ret);

	vdev_param = WMI_VDEV_PARAM_BEACON_RATE;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, vdev_param,
					    hw_rate_code);
	if (ret)
		ath11k_warn(ar->ab, "failed to set beacon tx rate %d\n", ret);
}

static void ath11k_mac_op_bss_info_changed(struct ieee80211_hw *hw,
					   struct ieee80211_vif *vif,
					   struct ieee80211_bss_conf *info,
					   u64 changed)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct ieee80211_chan_def def;
    u32 param_id;
    //u32 param_value;
	enum nl80211_band band;
	u32 vdev_param;
	int mcast_rate;
	u32 preamble;
	u16 hw_value;
	u16 bitrate;
	int ret = 0;
	u8 rateidx;
	u32 rate;

	mutex_lock(&ar->conf_mutex);

	if (changed & BSS_CHANGED_BEACON_INT) {
		arvif->beacon_interval = ieee80211_bss_conf_get_beacon_interval(info);

		param_id = WMI_VDEV_PARAM_BEACON_INTERVAL;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param_id,
						    arvif->beacon_interval);
		if (ret)
			ath11k_warn(ar->ab, "Failed to set beacon interval for VDEV: %d\n",
				    arvif->vdev_id);
		else
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "Beacon interval: %d set for VDEV: %d\n",
				   arvif->beacon_interval, arvif->vdev_id);
	}

#if 0 // TODOTODO: SAP or P2PGO
	if (changed & BSS_CHANGED_BEACON) {
		param_id = WMI_PDEV_PARAM_BEACON_TX_MODE;
		param_value = WMI_BEACON_STAGGERED_MODE;
		ret = ath11k_wmi_pdev_set_param(ar, param_id,
						param_value, ar->pdev->pdev_id);
		if (ret)
			ath11k_warn(ar->ab, "Failed to set beacon mode for VDEV: %d\n",
				    arvif->vdev_id);
		else
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "Set staggered beacon mode for VDEV: %d\n",
				   arvif->vdev_id);

		ret = ath11k_mac_setup_bcn_tmpl(arvif);
		if (ret)
			ath11k_warn(ar->ab, "failed to update bcn template: %d\n",
				    ret);

		if (ieee80211_vif_bss_conf_get_he_support(vif)) {
			ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
							    WMI_VDEV_PARAM_BA_MODE,
							    WMI_BA_MODE_BUFFER_SIZE_256);
			if (ret)
				ath11k_warn(ar->ab,
					    "failed to set BA BUFFER SIZE 256 for vdev: %d\n",
					    arvif->vdev_id);
			else
				ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
					   "Set BA BUFFER SIZE 256 for VDEV: %d\n",
					   arvif->vdev_id);
		}
	}
#endif

	if (changed & (BSS_CHANGED_BEACON_INFO | BSS_CHANGED_BEACON)) {
		arvif->dtim_period = ieee80211_bss_conf_get_dtim_period(info);

		param_id = WMI_VDEV_PARAM_DTIM_PERIOD;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param_id,
						    arvif->dtim_period);

		if (ret)
			ath11k_warn(ar->ab, "Failed to set dtim period for VDEV %d: %d\n",
				    arvif->vdev_id, ret);
		else
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "DTIM period: %d set for VDEV: %d\n",
				   arvif->dtim_period, arvif->vdev_id);
	}

#if 0
	if (changed & BSS_CHANGED_SSID &&
	    vif->type == NL80211_IFTYPE_AP) {
		arvif->u.ap.ssid_len = info->ssid_len;
		if (info->ssid_len)
			memcpy(arvif->u.ap.ssid, info->ssid, info->ssid_len);
		arvif->u.ap.hidden_ssid = info->hidden_ssid;
	}

#endif /* */

    if (changed & BSS_CHANGED_BSSID && 
        !is_zero_ether_addr(ieee80211_bss_conf_get_bssid(info)))
        ether_addr_copy(arvif->bssid, ieee80211_bss_conf_get_bssid(info));

#if 0 /* TODOTODO */
	if (changed & BSS_CHANGED_BEACON_ENABLED)
		ath11k_control_beaconing(arvif, info);
#endif
	if (changed & BSS_CHANGED_ERP_CTS_PROT) {
		u32 cts_prot;

		cts_prot = !!(ieee80211_bss_conf_get_erp_cts_port(info));
		param_id = WMI_VDEV_PARAM_PROTECTION_MODE;

		if (arvif->is_started) {
			ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
							    param_id, cts_prot);
			if (ret)
				ath11k_warn(ar->ab, "Failed to set CTS prot for VDEV: %d\n",
					    arvif->vdev_id);
			else
				ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "Set CTS prot: %d for VDEV: %d\n",
					   cts_prot, arvif->vdev_id);
		} else {
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "defer protection mode setup, vdev is not ready yet\n");
		}
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		u32 slottime;

		if (ieee80211_bss_conf_get_erp_short_slot(info))
			slottime = WMI_VDEV_SLOT_TIME_SHORT; /* 9us */

		else
			slottime = WMI_VDEV_SLOT_TIME_LONG; /* 20us */

		param_id = WMI_VDEV_PARAM_SLOT_TIME;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param_id, slottime);
		if (ret)
			ath11k_warn(ar->ab, "Failed to set erp slot for VDEV: %d\n",
				    arvif->vdev_id);
		else
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "Set slottime: %d for VDEV: %d\n",
				   slottime, arvif->vdev_id);
	}

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {

		if (ieee80211_bss_conf_get_erp_short_preamble(info))
			preamble = WMI_VDEV_PREAMBLE_SHORT;
		else
			preamble = WMI_VDEV_PREAMBLE_LONG;

		param_id = WMI_VDEV_PARAM_PREAMBLE;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param_id, preamble);
		if (ret)
			ath11k_warn(ar->ab, "Failed to set preamble for VDEV: %d\n",
				    arvif->vdev_id);
		else
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "Set preamble: %d for VDEV: %d\n",
				   preamble, arvif->vdev_id);
	}

	if (changed & BSS_CHANGED_ASSOC) {
		if (ieee80211_bss_conf_get_assoc(info))
			ath11k_bss_assoc(hw, vif, info);
		else
			ath11k_bss_disassoc(hw, vif);
	}

	if (changed & BSS_CHANGED_TXPOWER) {
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev_id %d txpower %d\n",
            arvif->vdev_id, 
            ieee80211_bss_conf_get_txpower(info));

        arvif->txpower = ieee80211_bss_conf_get_txpower(info);
		ath11k_mac_txpower_recalc(ar);
	}

	if (changed & BSS_CHANGED_PS) {
		arvif->ps = ieee80211_bss_conf_get_powersave(info);

		ret = ath11k_config_ps(ar);
		if (ret)
			ath11k_warn(ar->ab, "failed to setup ps on vdev %d: %d\n",
				    arvif->vdev_id, ret);
	}

	if (changed & BSS_CHANGED_MCAST_RATE &&
	    !ath11k_mac_vif_chan(arvif->vif, &def)) {
		band = def.chan->band;
		mcast_rate = ieee80211_vif_bss_conf_get_mcast_rate(vif)[band];

		if (mcast_rate > 0)
			rateidx = (u8)(mcast_rate - 1);
		else
			rateidx = (u8)(ffs(ieee80211_vif_bss_conf_get_basic_rates(vif)) - 1);

		if (ar->pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP)
			rateidx += ATH11K_MAC_FIRST_OFDM_RATE_IDX;

		bitrate = ath11k_legacy_rates[rateidx].bitrate;
		hw_value = ath11k_legacy_rates[rateidx].hw_value;

		if (ath11k_mac_bitrate_is_cck(bitrate))
			preamble = WMI_RATE_PREAMBLE_CCK;
		else
			preamble = WMI_RATE_PREAMBLE_OFDM;

		rate = ATH11K_HW_RATE_CODE(hw_value, 0, preamble);

		ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
			   "mac vdev %d mcast_rate 0x%x\n",
			   arvif->vdev_id, rate);

		vdev_param = WMI_VDEV_PARAM_MCAST_DATA_RATE;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    vdev_param, rate);
		if (ret)
			ath11k_warn(ar->ab,
				    "failed to set mcast rate on vdev %d: %d\n",
				    arvif->vdev_id,  ret);

		vdev_param = WMI_VDEV_PARAM_BCAST_DATA_RATE;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    vdev_param, rate);
		if (ret)
			ath11k_warn(ar->ab,
				    "failed to set bcast rate on vdev %d: %d\n",
				    arvif->vdev_id,  ret);
	}

	if (changed & BSS_CHANGED_BASIC_RATES &&
	    !ath11k_mac_vif_chan(arvif->vif, &def))
		ath11k_recalculate_mgmt_rate(ar, vif, &def);

	if (changed & BSS_CHANGED_TWT) {
		if (ieee80211_bss_conf_get_twt_requester(info) ||
            ieee80211_bss_conf_get_twt_responder(info))
			ath11k_wmi_send_twt_enable_cmd(ar, ar->pdev->pdev_id);
		else
			ath11k_wmi_send_twt_disable_cmd(ar, ar->pdev->pdev_id);
	}

#if ATH11K_SUPPORT_HE
	if (changed & BSS_CHANGED_HE_OBSS_PD)
		ath11k_wmi_send_obss_spr_cmd(ar, arvif->vdev_id,
			ieee80211_bss_conf_get_he_obss_pd(info));

	if (changed & BSS_CHANGED_HE_BSS_COLOR) {
		if (ieee80211_vif_type(vif) == NL80211_IFTYPE_STATION) {
			ret = ath11k_wmi_send_bss_color_change_enable_cmd(ar,
				arvif->vdev_id,
				1);
			if (ret)
				ath11k_warn(ar->ab, "failed to enable bss color change on vdev %i: %d\n",
					arvif->vdev_id, ret);
			ret = ath11k_wmi_send_obss_color_collision_cfg_cmd(
				ar, arvif->vdev_id, 0,
				ATH11K_BSS_COLOR_COLLISION_DETECTION_STA_PERIOD_MS, 1);
			if (ret)
				ath11k_warn(ar->ab, "failed to set bss color collision on vdev %i: %d\n",
					arvif->vdev_id, ret);
		}
	}
#endif

	mutex_unlock(&ar->conf_mutex);
}

void __ath11k_mac_scan_finish(struct ath11k *ar)
{
    /* drain mgmt rx */
    poll_irqs(16);

	lockdep_assert_held(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH11K_SCAN_IDLE:
		break;
	case ATH11K_SCAN_RUNNING:
	case ATH11K_SCAN_ABORTING:
		if (!ar->scan.is_roc) {
            bool aborted = (ar->scan.state == ATH11K_SCAN_ABORTING);
			ieee80211_scan_completed(ar->hw, aborted);
#if 0  // TODOTODO: Remain on channel
		} else if (ar->scan.roc_notify) {
			ieee80211_remain_on_channel_expired(ar->hw);
#endif
		}

		/* fall through */
	case ATH11K_SCAN_STARTING:
		ar->scan.state = ATH11K_SCAN_IDLE;
		ar->scan_channel = NULL;
		ar->scan.roc_freq = 0;
		cancel_delayed_work(&ar->scan.timeout);
		complete(&ar->scan.completed);
		break;
	}
}

void ath11k_mac_scan_finish(struct ath11k *ar)
{
	spin_lock_bh(&ar->data_lock);
	__ath11k_mac_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);
}

static int ath11k_scan_stop(struct ath11k *ar)
{
	struct scan_cancel_param arg = {
		.req_type = WLAN_SCAN_CANCEL_SINGLE,
		.scan_id = ATH11K_SCAN_ID,
	};
	int ret;
	unsigned long time_left;

	lockdep_assert_held(&ar->conf_mutex);

	/* TODO: Fill other STOP Params */
	arg.pdev_id = ar->pdev->pdev_id;

	ret = ath11k_wmi_send_scan_stop_cmd(ar, &arg);
	if (ret) {
		ath11k_warn(ar->ab, "failed to stop wmi scan: %d\n", ret);
		goto out;
	}

	time_left = wait_for_completion_timeout(&ar->scan.completed, 3 * HZ);
	if (!time_left) {
		ath11k_warn(ar->ab,
			    "failed to receive scan abort comple: timed out\n");
		ret = -ETIMEDOUT;
	} else if (ret > 0) {
		ret = 0;
	}

out:
	/* Scan state should be updated upon scan completion but in case
	 * firmware fails to deliver the event (for whatever reason) it is
	 * desired to clean up scan state anyway. Firmware may have just
	 * dropped the scan completion event delivery due to transport pipe
	 * being overflown with data and/or it can recover on its own before
	 * next scan request is submitted.
	 */
	spin_lock_bh(&ar->data_lock);
	if (ar->scan.state != ATH11K_SCAN_IDLE)
		__ath11k_mac_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);

	return ret;
}

static void ath11k_scan_abort(struct ath11k *ar)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH11K_SCAN_IDLE:
		/* This can happen if timeout worker kicked in and called
		 * abortion while scan completion was being processed.
		 */
		break;
	case ATH11K_SCAN_STARTING:
	case ATH11K_SCAN_ABORTING:
		ath11k_warn(ar->ab, "refusing scan abortion due to invalid scan state: %d\n",
			    ar->scan.state);
		break;
	case ATH11K_SCAN_RUNNING:
		ar->scan.state = ATH11K_SCAN_ABORTING;
		spin_unlock_bh(&ar->data_lock);

		ret = ath11k_scan_stop(ar);
		if (ret)
			ath11k_warn(ar->ab, "failed to abort scan: %d\n", ret);

		spin_lock_bh(&ar->data_lock);
		break;
	}

	spin_unlock_bh(&ar->data_lock);
}

static void ath11k_scan_timeout_work(void *context)
{
    struct ath11k *ar = context;

	mutex_lock(&ar->conf_mutex);
	ath11k_scan_abort(ar);
	mutex_unlock(&ar->conf_mutex);
}

static int ath11k_start_scan(struct ath11k *ar,
			     struct scan_req_params *arg)
{
	int ret;
	unsigned long time_left;
	unsigned long timeout = 5 * 1000;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath11k_wmi_send_scan_start_cmd(ar, arg);
	if (ret)
		return ret;

	// Add more 5 seconds timeout for 6G scan
    if (ar->supports_6ghz)
        timeout += 5 * 1000;
	
	time_left = wait_for_completion_timeout(&ar->scan.started, timeout);
	if (!time_left) {
		ret = ath11k_scan_stop(ar);
		if (ret)
			ath11k_warn(ar->ab, "failed to stop scan: %d\n", ret);

		return -ETIMEDOUT;
	}

	/* If we failed to start the scan, return error code at
	 * this point.  This is probably due to some issue in the
	 * firmware, but no need to wedge the driver due to that...
	 */
	spin_lock_bh(&ar->data_lock);
	if (ar->scan.state == ATH11K_SCAN_IDLE && 
        !completion_done(&ar->scan.completed)) {
		spin_unlock_bh(&ar->data_lock);
		return -EINVAL;
	}
	spin_unlock_bh(&ar->data_lock);

	return 0;
}

static int ath11k_mac_op_hw_scan(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_scan_request *hw_req)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct scan_req_params arg = {0};
    struct ieee80211_ssid *ssids;
    struct ieee80211_channel **channels;
    u32 i;
	int ret = 0;

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	switch (ar->scan.state) {
	case ATH11K_SCAN_IDLE:
		reinit_completion(&ar->scan.started);
		reinit_completion(&ar->scan.completed);
		ar->scan.state = ATH11K_SCAN_STARTING;
		ar->scan.is_roc = false;
		ar->scan.vdev_id = arvif->vdev_id;
		ret = 0;
		break;
	case ATH11K_SCAN_STARTING:
	case ATH11K_SCAN_RUNNING:
	case ATH11K_SCAN_ABORTING:
		ret = -EBUSY;
		break;
	}
	spin_unlock_bh(&ar->data_lock);

	if (ret)
		goto exit;

	if (ar->pending_11d) {
		long time_left;

		DEBUG_PARAMETER(time_left);

		time_left = wait_for_completion_timeout(&ar->finish_11d_ch_list, 3 * HZ);
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
			   "mac wait 11d channel list time left %ld\n", time_left);
	}

	ath11k_wmi_start_scan_init(ar, &arg);
	arg.vdev_id = arvif->vdev_id;
	arg.scan_id = ATH11K_SCAN_ID;

    arg.extraie.len = ieee80211_scan_request_ies_len(hw_req);
	if (arg.extraie.len) {
		arg.extraie.ptr = kzalloc(arg.extraie.len, GFP_KERNEL);
		if (arg.extraie.ptr)
        	memcpy(arg.extraie.ptr, ieee80211_scan_request_ies(hw_req), arg.extraie.len);
	}

	arg.num_ssids = MIN(ieee80211_scan_request_num_ssids(hw_req),
        ARRAY_LENGTH(arg.ssid));
    if (arg.num_ssids) {
        ssids = ieee80211_scan_request_ssids(hw_req);
        for (i = 0; i < arg.num_ssids; i++) {
            arg.ssid[i].length = ssids[i].ssid_len;
            memcpy(arg.ssid[i].ssid, ssids[i].ssid, ssids[i].ssid_len);
        }
    }
    else {
		arg.u_scan_f.scan_flags |= WMI_SCAN_FLAG_PASSIVE;
	}

    arg.num_chan = MIN(ieee80211_scan_request_num_channels(hw_req), 
        ARRAY_LENGTH(arg.chan_list));
	if (arg.num_chan) {
        channels = ieee80211_scan_request_channels(hw_req);
		for (i = 0; i < arg.num_chan; i++)
			arg.chan_list[i] = channels[i]->center_freq;

        ath11k_dbg_dump(ar->ab, ATH11K_DBG_WMI, "chan_list: ",
            arg.chan_list, arg.num_chan * sizeof(arg.chan_list[0]), 0);
	}

	ret = ath11k_start_scan(ar, &arg);
	if (ret) {
		ath11k_warn(ar->ab, "failed to start hw scan: %d\n", ret);
		spin_lock_bh(&ar->data_lock);
		ar->scan.state = ATH11K_SCAN_IDLE;
		spin_unlock_bh(&ar->data_lock);
	}

	/* Add a 200ms margin to account for event/command processing */
	ieee80211_queue_delayed_work(ar->hw, &ar->scan.timeout,
				     msecs_to_jiffies(arg.max_scan_time +
						      ATH11K_MAC_SCAN_TIMEOUT_MSECS));

exit:
	if (arg.extraie.len)
		kfree(arg.extraie.ptr);

	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static void ath11k_mac_op_cancel_hw_scan(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);

	mutex_lock(&ar->conf_mutex);
	ath11k_scan_abort(ar);
	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.timeout);
}

static int ath11k_install_key(struct ath11k_vif *arvif,
			      struct ieee80211_key_conf *key,
			      enum ieee80211_key_cmd cmd,
			      const u8 *macaddr, u32 flags)
{
	int ret;
	struct ath11k *ar = arvif->ar;
	struct wmi_vdev_install_key_arg arg = { 0 };

    arg.vdev_id = arvif->vdev_id; 
    arg.key_idx = key->key_idx;
    arg.key_len = key->key_len;
    arg.key_data = key->key;
    arg.key_flags = flags;
    arg.macaddr = macaddr;

	DbgInfo("cmd/vid/key_idx/key_len/key_flags: %d-%d-%d-%d-%d \n", 
        cmd, arg.vdev_id, arg.key_idx, arg.key_len, arg.key_flags);
    DbgInfo("Mac: %x-%x-%x-%x-%x-%x \n", arg.macaddr[0], arg.macaddr[1], arg.macaddr[2], 
        arg.macaddr[3], arg.macaddr[4], arg.macaddr[5]);
    DbgDump("Key:", arg.key_data, arg.key_len, 256);
		
	lockdep_assert_held(&arvif->ar->conf_mutex);

	reinit_completion(&ar->install_key_done);

	if (cmd == IEEE80211_DISABLE_KEY) {
		/* TODO: Check if FW expects  value other than NONE for del */
		/* arg.key_cipher = WMI_CIPHER_NONE; */
		arg.key_len = 0;
		arg.key_data = NULL;
		goto install;
	}

	switch (key->cipher) {
	case WLAN_RSN_CIPHER_SUITE_CCMP:
		arg.key_cipher = WMI_CIPHER_AES_CCM;
#if 0
		/* TODO: Re-check if flag is valid */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV_MGMT;
#endif
		break;
	case WLAN_RSN_CIPHER_SUITE_TKIP:
		arg.key_cipher = WMI_CIPHER_TKIP;
		arg.key_txmic_len = 8;
		arg.key_rxmic_len = 8;
		break;
	case WLAN_RSN_CIPHER_SUITE_WEP40:
	case WLAN_RSN_CIPHER_SUITE_WEP104:
		arg.key_cipher = WMI_CIPHER_WEP;
		break;
	case WLAN_RSN_CIPHER_SUITE_CCMP_256:
		arg.key_cipher = WMI_CIPHER_AES_CCM;
		break;
	case WLAN_RSN_CIPHER_SUITE_GCMP:
	case WLAN_RSN_CIPHER_SUITE_GCMP_256:
		arg.key_cipher = WMI_CIPHER_AES_GCM;
		break;
	case WLAN_RSN_CIPHER_SUITE_AES_CMAC:
	case WLAN_RSN_CIPHER_SUITE_BIP_CMAC_256:
		arg.key_cipher = WMI_CIPHER_AES_CMAC;
		break;
	case WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256:
		arg.key_cipher = WMI_CIPHER_AES_GMAC;
		break;
	default:
		ath11k_warn(ar->ab, "cipher %x is not supported\n", key->cipher);
		return -EOPNOTSUPP;
	}

install:
	ret = ath11k_wmi_vdev_install_key(arvif->ar, &arg);
	if (ret)
		return ret;

	if (!wait_for_completion_timeout(&ar->install_key_done, 1 * HZ))
		return -ETIMEDOUT;

	return ar->install_key_status ? -EINVAL : 0;
}

static int ath11k_install_peer_wep_keys(struct ath11k_vif *arvif,
					const u8 *addr)
{
	struct ath11k *ar = arvif->ar;
	struct ath11k_peer *peer;
	int ret;
	int i;
	u32 flags;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ieee80211_vif_type(arvif->vif) != NL80211_IFTYPE_AP &&
        ieee80211_vif_type(arvif->vif) != NL80211_IFTYPE_ADHOC &&
        ieee80211_vif_type(arvif->vif) != NL80211_IFTYPE_MESH_POINT))
		return -EINVAL;

	spin_lock_bh(&ar->data_lock);
	peer = ath11k_peer_find(ar->ab, arvif->vdev_id, addr);
	spin_unlock_bh(&ar->data_lock);

	if (!peer)
		return -ENOENT;

	for (i = 0; i < ARRAY_SIZE(arvif->wep_keys); i++) {
		if (!arvif->wep_keys[i])
			continue;

		switch (ieee80211_vif_type(arvif->vif)) {
		case NL80211_IFTYPE_AP:
			flags = WMI_KEY_PAIRWISE;

			if (arvif->def_wep_key_idx == i)
				flags |= WMI_KEY_TX_USAGE;

			ret = ath11k_install_key(arvif, arvif->wep_keys[i],
						 IEEE80211_SET_KEY, addr, flags);
			if (ret < 0)
				return ret;
			break;
		case NL80211_IFTYPE_ADHOC:
			ret = ath11k_install_key(arvif, arvif->wep_keys[i],
						 IEEE80211_SET_KEY, addr,
						 WMI_KEY_PAIRWISE);
			if (ret < 0)
				return ret;

			ret = ath11k_install_key(arvif, arvif->wep_keys[i],
						 IEEE80211_SET_KEY, addr, WMI_KEY_GROUP);
			if (ret < 0)
				return ret;
			break;
		default:
			WARN_ON(1);
			return -EINVAL;
		}

		spin_lock_bh(&ar->data_lock);
		peer->keys[i] = arvif->wep_keys[i];
		spin_unlock_bh(&ar->data_lock);
	}

	/* In some cases (notably with static WEP IBSS with multiple keys)
	 * multicast Tx becomes broken. Both pairwise and groupwise keys are
	 * installed already. Using WMI_KEY_TX_USAGE in different combinations
	 * didn't seem help. Using def_keyid vdev parameter seems to be
	 * effective so use that.
	 *
	 * FIXME: Revisit. Perhaps this can be done in a less hacky way.
	 */
	if (ieee80211_vif_type(arvif->vif) != NL80211_IFTYPE_ADHOC)
		return 0;

	if (arvif->def_wep_key_idx == -1)
		return 0;

	ret = ath11k_wmi_vdev_set_param_cmd(arvif->ar,
					    arvif->vdev_id,
					WMI_VDEV_PARAM_DEF_KEYID,
					arvif->def_wep_key_idx);
	if (ret) {
		ath11k_warn(ar->ab, "failed to re-set def wpa key idxon vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}

static int ath11k_clear_peer_keys(struct ath11k_vif *arvif,
				  const u8 *addr)
{
	struct ath11k *ar = arvif->ar;
	struct ath11k_base *ab = ar->ab;
	struct ath11k_peer *peer;
	int first_errno = 0;
	int ret;
	int i;
	u32 flags = 0;

	lockdep_assert_held(&ar->conf_mutex);

	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find(ab, arvif->vdev_id, addr);
	spin_unlock_bh(&ab->base_lock);

	if (!peer)
		return -ENOENT;

	for (i = 0; i < ARRAY_SIZE(peer->keys); i++) {
		if (!peer->keys[i])
			continue;

		/* key flags are not required to delete the key */
		ret = ath11k_install_key(arvif, peer->keys[i],
					 IEEE80211_DISABLE_KEY, addr, flags);
		if (ret < 0 && first_errno == 0)
			first_errno = ret;

		if (ret < 0)
			ath11k_warn(ab, "failed to remove peer key %d: %d\n",
				    i, ret);

		spin_lock_bh(&ab->base_lock);
		peer->keys[i] = NULL;
		spin_unlock_bh(&ab->base_lock);
	}

	return first_errno;
}

static int ath11k_clear_vdev_key(struct ath11k_vif *arvif,
				 struct ieee80211_key_conf *key)
{
	struct ath11k *ar = arvif->ar;
	struct ath11k_peer *peer;
	u8 addr[ETH_ALEN];
	int first_errno = 0;
	int ret;
	int i;
	u32 flags = 0;

	lockdep_assert_held(&ar->conf_mutex);

	for (;;) {
		/* since ath11k_install_key we can't hold data_lock all the
		 * time, so we try to remove the keys incrementally
		 */
		spin_lock_bh(&ar->data_lock);
		i = 0;
		list_for_each_entry(peer, &ar->ab->peers, struct ath11k_peer, list) {
			for (i = 0; i < ARRAY_SIZE(peer->keys); i++) {
				if (peer->keys[i] == key) {
					ether_addr_copy(addr, peer->addr);
					peer->keys[i] = NULL;
					break;
				}
			}

			if (i < ARRAY_SIZE(peer->keys))
				break;
		}
		spin_unlock_bh(&ar->data_lock);

		if (i == ARRAY_SIZE(peer->keys))
			break;
		/* key flags are not required to delete the key */
		ret = ath11k_install_key(arvif, key, IEEE80211_DISABLE_KEY, addr, flags);
		if (ret < 0 && first_errno == 0)
			first_errno = ret;

		if (ret)
			ath11k_warn(ar->ab, "failed to remove key for %pM: %d\n",
				    addr, ret);
	}

	return first_errno;
}

static int ath11k_mac_vif_update_wep_key(struct ath11k_vif *arvif,
					 struct ieee80211_key_conf *key)
{
	struct ath11k *ar = arvif->ar;
	struct ath11k_peer *peer;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	list_for_each_entry(peer, &ar->ab->peers, struct ath11k_peer, list) {
		if (ether_addr_equal(peer->addr, ieee80211_vif_addr(arvif->vif)))
			continue;

		if (ether_addr_equal(peer->addr, arvif->bssid))
			continue;

		if (peer->keys[key->key_idx] == key)
			continue;

		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vif vdev %d update key %d needs update\n",
			   arvif->vdev_id, key->key_idx);

		ret = ath11k_install_peer_wep_keys(arvif, peer->addr);
		if (ret) {
			ath11k_warn(ar->ab, "failed to update wep keys on vdev %d for peer %pM: %d\n",
				    arvif->vdev_id, peer->addr, ret);
			return ret;
		}
	}

	return 0;
}

static int ath11k_mac_op_set_key(struct ieee80211_hw *hw, enum ieee80211_key_cmd cmd,
				 struct ieee80211_vif *vif, struct ieee80211_sta *sta,
				 struct ieee80211_key_conf *key)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct ath11k_peer *peer;
	const u8 *peer_addr;
	bool is_wep = key->cipher == WLAN_RSN_CIPHER_SUITE_WEP40 ||
		      key->cipher == WLAN_RSN_CIPHER_SUITE_WEP104;
	int ret = 0, ret2 = 0;
	u32 flags = 0, flags2 = 0;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "key cipher = %x keyidx = %d\n", 
		key->cipher, key->key_idx);
#if __TODO__
	/* BIP needs to be done in software */
	if (key->cipher == WLAN_RSN_CIPHER_SUITE_AES_CMAC ||
	    key->cipher == WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128 ||
	    key->cipher == WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256 ||
	    key->cipher == WLAN_RSN_CIPHER_SUITE_BIP_CMAC_256)
		return 1;
#endif

	if (key->key_idx > WMI_MAX_KEY_INDEX)
		return -ENOSPC;

	mutex_lock(&ar->conf_mutex);

	if (sta)
		peer_addr = ieee80211_sta_addr(sta);
	else if (arvif->vdev_type == WMI_VDEV_TYPE_STA)
		peer_addr = ieee80211_vif_bss_conf_get_bssid(vif);
	else
		peer_addr = ieee80211_vif_addr(arvif->vif);

	key->hw_key_idx = key->key_idx;

	if (is_wep) {
		if (cmd == IEEE80211_SET_KEY)
			arvif->wep_keys[key->key_idx] = key;
		else
			arvif->wep_keys[key->key_idx] = NULL;
	}

	/* the peer should not disappear in mid-way (unless FW goes awry) since
	 * we already hold conf_mutex. we just make sure its there now.
	 */
	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find(ab, arvif->vdev_id, peer_addr);

	if (peer && cmd == IEEE80211_SET_KEY) {
		ath11k_warn(ab, "flush the fragments cache during key (re)install to ensure all frags in the new frag list belong to the same key.\n");
		ath11k_peer_frags_flush(ar, peer);
	}

	spin_unlock_bh(&ab->base_lock);

	if (!peer) {
		if (cmd == IEEE80211_SET_KEY) {
			ath11k_warn(ab, "cannot install key for non-existent peer %pM\n",
				    peer_addr);
			ret = -EOPNOTSUPP;
			goto exit;
		} else {
			/* if the peer doesn't exist there is no key to disable
			 * anymore
			 */
			goto exit;
		}
	}

	if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		flags |= WMI_KEY_PAIRWISE;
	else
		flags |= WMI_KEY_GROUP;

	if (is_wep) {
		if (cmd == IEEE80211_DISABLE_KEY)
			ath11k_clear_vdev_key(arvif, key);

		/* When WEP keys are uploaded it's possible that there are
		 * stations associated already (e.g. when merging) without any
		 * keys. Static WEP needs an explicit per-peer key upload.
		 */
		if (ieee80211_vif_type(vif) == NL80211_IFTYPE_ADHOC &&
		    cmd == IEEE80211_SET_KEY)
			ath11k_mac_vif_update_wep_key(arvif, key);

		/* 802.1x never sets the def_wep_key_idx so each set_key()
		 * call changes default tx key.
		 *
		 * Static WEP sets def_wep_key_idx via .set_default_unicast_key
		 * after first set_key().
		 */
		if (cmd == IEEE80211_SET_KEY && arvif->def_wep_key_idx == -1)
			flags |= WMI_KEY_TX_USAGE;
	}

	ret = ath11k_install_key(arvif, key, cmd, peer_addr, flags);
	if (ret) {
		ath11k_warn(ab, "ath11k_install_key failed (%d)\n", ret);
		goto exit;
	}

	/* mac80211 sets static WEP keys as groupwise while firmware requires
	 * them to be installed twice as both pairwise and groupwise.
	 */
	if (is_wep && !sta && ieee80211_vif_type(vif) == NL80211_IFTYPE_STATION) {
		flags2 = flags;
		flags2 &= ~WMI_KEY_GROUP;
		flags2 |= WMI_KEY_PAIRWISE;

		ret = ath11k_install_key(arvif, key, cmd, peer_addr, flags2);
		if (ret) {
			WARN_ON(ret > 0);
			ath11k_warn(ar->ab, "failed to install (ucast) key for vdev %d peer %pM: %d\n",
				    arvif->vdev_id, peer_addr, ret);
			ret2 = ath11k_install_key(arvif, key, IEEE80211_DISABLE_KEY,
						  peer_addr, flags);
			if (ret2) {
				WARN_ON(ret2 > 0);
				ath11k_warn(ar->ab, "failed to disable (mcast) key for vdev %d peer %pM: %d\n",
					    arvif->vdev_id, peer_addr, ret2);
			}
			goto exit;
		}
	}

	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find(ab, arvif->vdev_id, peer_addr);
    if (peer && cmd == IEEE80211_SET_KEY) {
        peer->keys[key->key_idx] = key;
        if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) {
            peer->ucast_keyidx = key->key_idx;
            peer->sec_type = ath11k_dp_tx_get_encrypt_type(key->cipher);
        }
        else {
            peer->mcast_keyidx = key->key_idx;
            peer->sec_type_grp = ath11k_dp_tx_get_encrypt_type(key->cipher);
        }
    }
    else if (peer && cmd == IEEE80211_DISABLE_KEY) {
        peer->keys[key->key_idx] = NULL;
        if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
            peer->ucast_keyidx = 0;
        else
            peer->mcast_keyidx = 0;
    }
	else if (!peer)
		/* impossible unless FW goes crazy */
		ath11k_warn(ab, "peer %pM disappeared!\n", peer_addr);
	spin_unlock_bh(&ab->base_lock);

exit:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static void ath11k_mac_op_set_default_unicast_key(struct ieee80211_hw *hw,
						  struct ieee80211_vif *vif,
						  int key_idx)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;

	mutex_lock(&arvif->ar->conf_mutex);

	if (arvif->ar->state != ATH11K_STATE_ON)
		goto unlock;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %d set keyidx %d\n",
		   arvif->vdev_id, key_idx);

	ret = ath11k_wmi_vdev_set_param_cmd(arvif->ar,
					    arvif->vdev_id,
					    WMI_VDEV_PARAM_DEF_KEYID,
					    key_idx);

	if (ret) {
		ath11k_warn(ar->ab, "failed to update wep key index for vdev %d: %d\n",
			    arvif->vdev_id,
			    ret);
		goto unlock;
	}

	arvif->def_wep_key_idx = (s8)key_idx;

unlock:
	mutex_unlock(&arvif->ar->conf_mutex);
}

static int
ath11k_mac_bitrate_mask_num_vht_rates(struct ath11k *ar,
				      enum nl80211_band band,
				      const struct ieee80211_bitrate_mask *mask)
{
	int num_rates = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++)
		num_rates += hweight16(mask->control[band].vht_mcs[i]);

	return num_rates;
}

static int
ath11k_mac_set_peer_vht_fixed_rate(struct ath11k_vif *arvif,
				   struct ieee80211_sta *sta,
				   const struct ieee80211_bitrate_mask *mask,
				   enum nl80211_band band)
{
	struct ath11k *ar = arvif->ar;
	u8 vht_rate, nss;
	u32 rate_code;
	int ret, i;

	lockdep_assert_held(&ar->conf_mutex);

	nss = 0;

	for (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) {
		if (hweight16(mask->control[band].vht_mcs[i]) == 1) {
			nss = (u8)(i + 1);
			vht_rate = (u8)(ffs(mask->control[band].vht_mcs[i]) - 1);
		}
	}

	if (!nss) {
		ath11k_warn(ar->ab, "No single VHT Fixed rate found to set for %pM",
            ieee80211_sta_addr(sta));
		return -EINVAL;
	}

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
        "Setting Fixed VHT Rate for peer %pM. Device will not switch to any other selected rates",
        ieee80211_sta_addr(sta));

	rate_code = ATH11K_HW_RATE_CODE(vht_rate, nss - 1,
					WMI_RATE_PREAMBLE_VHT);
	ret = ath11k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta),
					arvif->vdev_id,
					WMI_PEER_PARAM_FIXED_RATE,
					rate_code);
	if (ret)
		ath11k_warn(ar->ab,
            "failed to update STA %pM Fixed Rate %d: %d\n",
            ieee80211_sta_addr(sta), rate_code, ret);

	return ret;
}

static int ath11k_station_assoc(struct ath11k *ar,
				struct ieee80211_vif *vif,
				struct ieee80211_sta *sta,
				bool reassoc)
{
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct ieee80211_he_6ghz_cap *sta_6ghz_cap;
	struct peer_assoc_params peer_arg;
	int ret = 0;
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	struct ieee80211_bitrate_mask *mask;
	u8 num_vht_rates;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath11k_mac_vif_chan(vif, &def)))
		return -EPERM;

	band = def.chan->band;
	mask = &arvif->bitrate_mask;

	ath11k_peer_assoc_prepare(ar, vif, sta, &peer_arg, reassoc);

	ret = ath11k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
	if (ret) {
		ath11k_warn(ar->ab, "failed to run peer assoc for STA %pM vdev %d: %d\n",
            ieee80211_sta_addr(sta), arvif->vdev_id, ret);
		return ret;
	}

	if (!wait_for_completion_timeout(&ar->peer_assoc_done, 1 * HZ)) {
		ath11k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %d\n",
            ieee80211_sta_addr(sta), arvif->vdev_id);
		return -ETIMEDOUT;
	}

	num_vht_rates = (u8)ath11k_mac_bitrate_mask_num_vht_rates(ar, band, mask);

	/* If single VHT rate is configured (by set_bitrate_mask()),
	 * peer_assoc will disable VHT. This is now enabled by a peer specific
	 * fixed param.
	 * Note that all other rates and NSS will be disabled for this peer.
	 */
	if (ieee80211_sta_get_vht_cap(sta)->vht_supported && num_vht_rates == 1) {
		ret = ath11k_mac_set_peer_vht_fixed_rate(arvif, sta, mask,
							 band);
		if (ret)
			return ret;
	}

	/* Re-assoc is run only to update supported rates for given station. It
	 * doesn't make much sense to reconfigure the peer completely.
	 */
	if (reassoc)
		return 0;

    sta_6ghz_cap = ieee80211_sta_get_6ghz_cap(sta);
	ret = ath11k_setup_peer_smps(ar, arvif, ieee80211_sta_addr(sta),
				     ieee80211_sta_get_ht_cap(sta), sta_6ghz_cap->cap);
	if (ret) {
		ath11k_warn(ar->ab, "failed to setup peer SMPS for vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	if (!ieee80211_sta_get_wme(sta)) {
		arvif->num_legacy_stations++;
		ret = ath11k_recalc_rtscts_prot(arvif);
		if (ret)
			return ret;
	}

	if (ieee80211_sta_get_wme(sta) &&
        ieee80211_sta_get_uapsd_queues(sta)) {
		ret = ath11k_peer_assoc_qos_ap(ar, arvif, sta);
		if (ret) {
			ath11k_warn(ar->ab, "failed to set qos params for STA %pM for vdev %d: %d\n",
                ieee80211_sta_addr(sta), arvif->vdev_id, ret);
			return ret;
		}
	}

	/* Plumb cached keys only for static WEP */
	if ((arvif->def_wep_key_idx != -1) &&!ieee80211_sta_get_tdls(sta)) {
		ret = ath11k_install_peer_wep_keys(arvif, ieee80211_sta_addr(sta));
		if (ret) {
			ath11k_warn(ar->ab, "failed to install peer wep keys for vdev %d: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}
	}

	return 0;
}

static int ath11k_station_disassoc(struct ath11k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta)
{
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	if (!ieee80211_sta_get_wme(sta)) {
		arvif->num_legacy_stations--;
		ret = ath11k_recalc_rtscts_prot(arvif);
		if (ret)
			return ret;
	}

	ret = ath11k_clear_peer_keys(arvif, ieee80211_sta_addr(sta));
	if (ret) {
		ath11k_warn(ar->ab, "failed to clear all peer keys for vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}
	return 0;
}

static void ath11k_sta_rc_update_wk(void *context)
{
	struct ath11k *ar;
	struct ath11k_vif *arvif;
	struct ath11k_sta *arsta;
	struct ieee80211_sta *sta;
    const u8 *sta_addr;
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	const u16 *vht_mcs_mask;
	u32 changed, bw, nss, smps;
	int err, num_vht_rates;
	const struct ieee80211_bitrate_mask *mask;
	struct peer_assoc_params peer_arg;

    arsta = context;
	sta = ieee80211_sta_from_drv_priv(arsta);
    sta_addr = ieee80211_sta_addr(sta);

	arvif = arsta->arvif;
	ar = arvif->ar;

	if (WARN_ON(ath11k_mac_vif_chan(arvif->vif, &def)))
		return;

	band = def.chan->band;
	ht_mcs_mask = arvif->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvif->bitrate_mask.control[band].vht_mcs;

	spin_lock_bh(&ar->data_lock);

	changed = arsta->changed;
	arsta->changed = 0;

	bw = arsta->bw;
	nss = arsta->nss;
	smps = arsta->smps;

	spin_unlock_bh(&ar->data_lock);

	mutex_lock(&ar->conf_mutex);

	nss = max_t(u32, 1, nss);
	nss = min(nss, max(ath11k_mac_max_ht_nss(ht_mcs_mask),
			   ath11k_mac_max_vht_nss(vht_mcs_mask)));

	if (changed & IEEE80211_RC_CHANGED_BW) {
		err = ath11k_wmi_set_peer_param(ar, sta_addr, arvif->vdev_id,
						WMI_PEER_CHWIDTH, bw);
		if (err)
			ath11k_warn(ar->ab, "failed to update STA %pM peer bw %d: %d\n",
                sta_addr, bw, err);
	}

	if (changed & IEEE80211_RC_CHANGED_NSS) {
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac update sta %pM nss %d\n",
            sta_addr, nss);

		err = ath11k_wmi_set_peer_param(ar, sta_addr, arvif->vdev_id,
						WMI_PEER_NSS, nss);
		if (err)
			ath11k_warn(ar->ab, "failed to update STA %pM nss %d: %d\n",
                sta_addr, nss, err);
	}

	if (changed & IEEE80211_RC_CHANGED_SMPS) {
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac update sta %pM smps %d\n",
            sta_addr, smps);

		err = ath11k_wmi_set_peer_param(ar, sta_addr, arvif->vdev_id,
						WMI_PEER_MIMO_PS_STATE, smps);
		if (err)
			ath11k_warn(ar->ab, "failed to update STA %pM smps %d: %d\n",
                sta_addr, smps, err);
	}

	if (changed & IEEE80211_RC_CHANGED_SUPP_RATES) {
		mask = &arvif->bitrate_mask;
		num_vht_rates = ath11k_mac_bitrate_mask_num_vht_rates(ar, band,
								      mask);

		/* Peer_assoc_prepare will reject vht rates in
		 * bitrate_mask if its not available in range format and
		 * sets vht tx_rateset as unsupported. So multiple VHT MCS
		 * setting(eg. MCS 4,5,6) per peer is not supported here.
		 * But, Single rate in VHT mask can be set as per-peer
		 * fixed rate. But even if any HT rates are configured in
		 * the bitrate mask, device will not switch to those rates
		 * when per-peer Fixed rate is set.
		 * TODO: Check RATEMASK_CMDID to support auto rates selection
		 * across HT/VHT and for multiple VHT MCS support.
		 */
		if (ieee80211_sta_get_vht_cap(sta)->vht_supported && num_vht_rates == 1) {
			ath11k_mac_set_peer_vht_fixed_rate(arvif, sta, mask,
							   band);
		} else {
			/* If the peer is non-VHT or no fixed VHT rate
			 * is provided in the new bitrate mask we set the
			 * other rates using peer_assoc command.
			 */
			ath11k_peer_assoc_prepare(ar, arvif->vif, sta,
						  &peer_arg, true);

			err = ath11k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
			if (err)
				ath11k_warn(ar->ab, "failed to run peer assoc for STA %pM vdev %d: %d\n",
                    ieee80211_sta_addr(sta), arvif->vdev_id, err);

			if (!wait_for_completion_timeout(&ar->peer_assoc_done, 1 * HZ))
				ath11k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %d\n",
                    ieee80211_sta_addr(sta), arvif->vdev_id);
		}
	}

	mutex_unlock(&ar->conf_mutex);
}

static int ath11k_mac_inc_num_stations(struct ath11k_vif *arvif,
				       struct ieee80211_sta *sta)
{
	struct ath11k *ar = arvif->ar;

	lockdep_assert_held(&ar->conf_mutex);

	if (arvif->vdev_type == WMI_VDEV_TYPE_STA && !ieee80211_sta_get_tdls(sta))
		return 0;

	if (ar->num_stations >= ar->max_num_stations)
		return -ENOBUFS;

	ar->num_stations++;

	return 0;
}

static void ath11k_mac_dec_num_stations(struct ath11k_vif *arvif,
					struct ieee80211_sta *sta)
{
	struct ath11k *ar = arvif->ar;

	lockdep_assert_held(&ar->conf_mutex);

	if (arvif->vdev_type == WMI_VDEV_TYPE_STA && !ieee80211_sta_get_tdls(sta))
		return;

	ar->num_stations--;
}

static int ath11k_mac_station_add(struct ath11k *ar,
				  struct ieee80211_vif *vif,
				  struct ieee80211_sta *sta)
{
	struct ath11k_base *ab = ar->ab;
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct ath11k_sta *arsta = ieee80211_sta_get_priv_data(sta);
	struct peer_create_params peer_param;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath11k_mac_inc_num_stations(arvif, sta);
	if (ret) {
		ath11k_warn(ab, "refusing to associate station: too many connected already (%d)\n",
			    ar->max_num_stations);
		goto exit;
	}

	arsta->rx_stats = kzalloc(sizeof(*arsta->rx_stats), GFP_KERNEL);
	if (!arsta->rx_stats) {
		ret = -ENOMEM;
		goto dec_num_station;
	}

	peer_param.vdev_id = arvif->vdev_id;
	peer_param.peer_addr = ieee80211_sta_addr(sta);
	peer_param.peer_type = WMI_PEER_TYPE_DEFAULT;

	ret = ath11k_peer_create(ar, arvif, sta, &peer_param);
	if (ret) {
		ath11k_warn(ab, "Failed to add peer: %pM for VDEV: %d\n",
            ieee80211_sta_addr(sta), arvif->vdev_id);
		goto free_rx_stats;
	}

	ath11k_dbg(ab, ATH11K_DBG_MAC, "Added peer: %pM for VDEV: %d\n",
        ieee80211_sta_addr(sta), arvif->vdev_id);

	if (ath11k_debug_is_extd_tx_stats_enabled(ar)) {
		arsta->tx_stats = kzalloc(sizeof(*arsta->tx_stats), GFP_KERNEL);
		if (!arsta->tx_stats) {
			ret = -ENOMEM;
			goto free_peer;
		}
	}

#if ATH11k_UNUSED
	if (ieee80211_vif_is_mesh(vif)) {
		ret = ath11k_wmi_set_peer_param(ar, sta->addr,
						arvif->vdev_id,
						WMI_PEER_USE_4ADDR, 1);
		if (ret) {
			ath11k_warn(ab, "failed to STA %pM 4addr capability: %d\n",
				    sta->addr, ret);
			goto free_tx_stats;
		}
	}
#endif // !ATH11K_UNUSED

	ret = ath11k_dp_peer_setup(ar, arvif->vdev_id, ieee80211_sta_addr(sta));
	if (ret) {
		ath11k_warn(ab, "failed to setup dp for peer %pM on vdev %d (%d)\n",
            ieee80211_sta_addr(sta), arvif->vdev_id, ret);
		goto free_tx_stats;
	}

	if (ab->hw_params.vdev_start_delay)
		ret = ath11k_start_vdev_delay(ar->hw, vif);

	return 0;

free_tx_stats:
	kfree(arsta->tx_stats);
	arsta->tx_stats = NULL;
free_peer:
	ath11k_peer_delete(ar, arvif->vdev_id, ieee80211_sta_addr(sta));
free_rx_stats:
	kfree(arsta->rx_stats);
	arsta->rx_stats = NULL;
dec_num_station:
	ath11k_mac_dec_num_stations(arvif, sta);
exit:
	return ret;
}

static int ath11k_mac_op_sta_state(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta,
				   enum ieee80211_sta_state old_state,
				   enum ieee80211_sta_state new_state)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct ath11k_sta *arsta = ieee80211_sta_get_priv_data(sta);
	int ret = 0;

	/* cancel must be done outside the mutex to avoid deadlock */
	if ((old_state == IEEE80211_STA_NONE &&
	     new_state == IEEE80211_STA_NOTEXIST))
		cancel_work_sync(&arsta->update_wk);

	mutex_lock(&ar->conf_mutex);

	if (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) {
		memset(arsta, 0, sizeof(*arsta));
		arsta->arvif = arvif;
		init_work(&arsta->update_wk, ath11k_sta_rc_update_wk, arsta);

		ret = ath11k_mac_station_add(ar, vif, sta);
		if (ret)
			ath11k_warn(ar->ab, "Failed to add station: %pM for VDEV: %d\n",
                ieee80211_sta_addr(sta), arvif->vdev_id);
	} else if ((old_state == IEEE80211_STA_NONE &&
		    new_state == IEEE80211_STA_NOTEXIST)) {
		ath11k_dp_peer_cleanup(ar, arvif->vdev_id, ieee80211_sta_addr(sta));

		ret = ath11k_peer_delete(ar, arvif->vdev_id, ieee80211_sta_addr(sta));
		if (ret)
			ath11k_warn(ar->ab, "Failed to delete peer: %pM for VDEV: %d\n",
                ieee80211_sta_addr(sta), arvif->vdev_id);
		else
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "Removed peer: %pM for VDEV: %d\n",
                ieee80211_sta_addr(sta), arvif->vdev_id);

		ath11k_mac_dec_num_stations(arvif, sta);

		kfree(arsta->tx_stats);
		arsta->tx_stats = NULL;

		kfree(arsta->rx_stats);
		arsta->rx_stats = NULL;
	} else if (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC &&
		   (ieee80211_vif_type(vif) == NL80211_IFTYPE_AP ||
               ieee80211_vif_type(vif) == NL80211_IFTYPE_MESH_POINT ||
               ieee80211_vif_type(vif) == NL80211_IFTYPE_ADHOC)) {
		ret = ath11k_station_assoc(ar, vif, sta, false);
		if (ret)
			ath11k_warn(ar->ab, "Failed to associate station: %pM\n",
                ieee80211_sta_addr(sta));
		else
			ath11k_info(ar->ab,
                "Station %pM moved to assoc state\n",
                ieee80211_sta_addr(sta));
	} else if (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTH &&
		   (ieee80211_vif_type(vif) == NL80211_IFTYPE_AP ||
               ieee80211_vif_type(vif) == NL80211_IFTYPE_MESH_POINT ||
               ieee80211_vif_type(vif) == NL80211_IFTYPE_ADHOC)) {
		ret = ath11k_station_disassoc(ar, vif, sta);
		if (ret)
			ath11k_warn(ar->ab, "Failed to disassociate station: %pM\n",
                ieee80211_sta_addr(sta));
		else
			ath11k_info(ar->ab,
                "Station %pM moved to disassociated state\n",
                ieee80211_sta_addr(sta));
	}

	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static int ath11k_mac_op_sta_set_txpwr(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif,
				       struct ieee80211_sta *sta)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
    struct ieee80211_sta_txpwr *sta_txpwr = ieee80211_sta_get_txpwr(sta);
    s16 txpwr;
    int ret = 0;

	if (sta_txpwr->type == NL80211_TX_POWER_AUTOMATIC) {
		txpwr = 0;
	} else {
		txpwr = sta_txpwr->power;
		if (!txpwr)
			return -EINVAL;
	}

	if (txpwr > ATH11K_TX_POWER_MAX_VAL || txpwr < ATH11K_TX_POWER_MIN_VAL)
		return -EINVAL;

	mutex_lock(&ar->conf_mutex);

	ret = ath11k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta), arvif->vdev_id,
					WMI_PEER_USE_FIXED_PWR, txpwr);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set tx power for station ret: %d\n",
			    ret);
		goto out;
	}

out:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static void ath11k_mac_op_sta_rc_update(struct ieee80211_hw *hw,
					struct ieee80211_vif *vif,
					struct ieee80211_sta *sta,
					u32 changed)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_sta *arsta = ieee80211_sta_get_priv_data(sta);
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ath11k_peer *peer;
	u32 bw, smps;

	spin_lock_bh(&ar->ab->base_lock);

	peer = ath11k_peer_find(ar->ab, arvif->vdev_id, ieee80211_sta_addr(sta));
	if (!peer) {
		spin_unlock_bh(&ar->ab->base_lock);
		ath11k_warn(ar->ab, "mac sta rc update failed to find peer %pM on vdev %d\n",
            ieee80211_sta_addr(sta), arvif->vdev_id);
		return;
	}

	spin_unlock_bh(&ar->ab->base_lock);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
        "mac sta rc update for %pM changed %08x bw %d nss %d smps %d\n",
        ieee80211_sta_addr(sta), changed, 
        ieee80211_sta_get_bandwidth(sta), 
        ieee80211_sta_get_rx_nss(sta),
		ieee80211_sta_get_smps_mode(sta));

	spin_lock_bh(&ar->data_lock);

	if (changed & IEEE80211_RC_CHANGED_BW) {
		bw = WMI_PEER_CHWIDTH_20MHZ;

		switch (ieee80211_sta_get_bandwidth(sta)) {
		case IEEE80211_STA_RX_BANDWIDTH_20:
			bw = WMI_PEER_CHWIDTH_20MHZ;
			break;
		case IEEE80211_STA_RX_BANDWIDTH_40:
			bw = WMI_PEER_CHWIDTH_40MHZ;
			break;
		case IEEE80211_STA_RX_BANDWIDTH_80:
			bw = WMI_PEER_CHWIDTH_80MHZ;
			break;
		case IEEE80211_STA_RX_BANDWIDTH_160:
			bw = WMI_PEER_CHWIDTH_160MHZ;
			break;
		default:
			ath11k_warn(ar->ab, "Invalid bandwidth %d in rc update for %pM\n",
                ieee80211_sta_get_bandwidth(sta),
                ieee80211_sta_addr(sta));
			bw = WMI_PEER_CHWIDTH_20MHZ;
			break;
		}

		arsta->bw = bw;
	}

    if (changed & IEEE80211_RC_CHANGED_NSS)
        arsta->nss = ieee80211_sta_get_rx_nss(sta);

	if (changed & IEEE80211_RC_CHANGED_SMPS) {
		smps = WMI_PEER_SMPS_PS_NONE;

		switch (ieee80211_sta_get_smps_mode(sta)) {
		case IEEE80211_SMPS_AUTOMATIC:
		case IEEE80211_SMPS_NONE:
			smps = WMI_PEER_SMPS_PS_NONE;
			break;
		case IEEE80211_SMPS_STATIC:
			smps = WMI_PEER_SMPS_STATIC;
			break;
		case IEEE80211_SMPS_DYNAMIC:
			smps = WMI_PEER_SMPS_DYNAMIC;
			break;
		default:
			ath11k_warn(ar->ab, "Invalid smps %d in sta rc update for %pM\n",
                ieee80211_sta_get_smps_mode(sta),
                ieee80211_sta_addr(sta));
			smps = WMI_PEER_SMPS_PS_NONE;
			break;
		}

		arsta->smps = smps;
	}

	arsta->changed |= changed;

	spin_unlock_bh(&ar->data_lock);

	ieee80211_queue_work(hw, &arsta->update_wk);
}

static int ath11k_conf_tx_uapsd(struct ath11k *ar, struct ieee80211_vif *vif,
				u16 ac, bool enable)
{
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	u32 value = 0;
	int ret = 0;

	if (arvif->vdev_type != WMI_VDEV_TYPE_STA)
		return 0;

	switch (ac) {
	case IEEE80211_AC_VO:
		value = WMI_STA_PS_UAPSD_AC3_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC3_TRIGGER_EN;
		break;
	case IEEE80211_AC_VI:
		value = WMI_STA_PS_UAPSD_AC2_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC2_TRIGGER_EN;
		break;
	case IEEE80211_AC_BE:
		value = WMI_STA_PS_UAPSD_AC1_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC1_TRIGGER_EN;
		break;
	case IEEE80211_AC_BK:
		value = WMI_STA_PS_UAPSD_AC0_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC0_TRIGGER_EN;
		break;
	}

	if (enable)
		arvif->u.sta.uapsd |= value;
	else
		arvif->u.sta.uapsd &= ~value;

	ret = ath11k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
					  WMI_STA_PS_PARAM_UAPSD,
					  arvif->u.sta.uapsd);
	if (ret) {
		ath11k_warn(ar->ab, "could not set uapsd params %d\n", ret);
		goto exit;
	}

	if (arvif->u.sta.uapsd)
		value = WMI_STA_PS_RX_WAKE_POLICY_POLL_UAPSD;
	else
		value = WMI_STA_PS_RX_WAKE_POLICY_WAKE;

	ret = ath11k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
					  WMI_STA_PS_PARAM_RX_WAKE_POLICY,
					  value);
	if (ret)
		ath11k_warn(ar->ab, "could not set rx wake param %d\n", ret);

exit:
	return ret;
}

static int ath11k_mac_op_conf_tx(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif, u16 ac,
				 const struct ieee80211_tx_queue_params *params)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct wmi_wmm_params_arg *p = NULL;
	int ret;

	mutex_lock(&ar->conf_mutex);

	switch (ac) {
	case IEEE80211_AC_VO:
		p = &arvif->wmm_params.ac_vo;
		break;
	case IEEE80211_AC_VI:
		p = &arvif->wmm_params.ac_vi;
		break;
	case IEEE80211_AC_BE:
		p = &arvif->wmm_params.ac_be;
		break;
	case IEEE80211_AC_BK:
		p = &arvif->wmm_params.ac_bk;
		break;
	}

	if (WARN_ON(!p)) {
		ret = -EINVAL;
		goto exit;
	}

	p->cwmin = params->cw_min;
	p->cwmax = params->cw_max;
	p->aifs = params->aifs;
	p->txop = params->txop;

	ret = ath11k_wmi_send_wmm_update_cmd_tlv(ar, arvif->vdev_id,
						 &arvif->wmm_params);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set wmm params: %d\n", ret);
		goto exit;
	}

	ret = ath11k_conf_tx_uapsd(ar, vif, ac, params->uapsd);

	if (ret)
		ath11k_warn(ar->ab, "failed to set sta uapsd: %d\n", ret);

exit:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static struct ieee80211_sta_ht_cap
ath11k_create_ht_cap(struct ath11k *ar, u32 ar_ht_cap, u32 rate_cap_rx_chainmask)
{
	int i;
	struct ieee80211_sta_ht_cap ht_cap = {0};
	u32 ar_vht_cap = ar->pdev->cap.vht_cap;

	if (!(ar_ht_cap & WMI_HT_CAP_ENABLED))
		return ht_cap;

	ht_cap.ht_supported = 1;
	ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap.ampdu_density = IEEE80211_HTCAP_MPDU_DENSITY_NONE;
	ht_cap.cap |= IEEE80211_HTCAP_SUP_WIDTH_20_40;
	ht_cap.cap |= IEEE80211_HTCAP_DSSSCCK40;
	ht_cap.cap |= WLAN_HTCAP_SM_PS_STATIC << IEEE80211_HTCAP_SM_PS_SHIFT;

	if (ar_ht_cap & WMI_HT_CAP_HT20_SGI)
		ht_cap.cap |= IEEE80211_HTCAP_SGI_20;

	if (ar_ht_cap & WMI_HT_CAP_HT40_SGI)
		ht_cap.cap |= IEEE80211_HTCAP_SGI_40;

	if (ar_ht_cap & WMI_HT_CAP_DYNAMIC_SMPS) {
		u32 smps;

		smps   = WLAN_HTCAP_SM_PS_DYNAMIC;
		smps <<= IEEE80211_HTCAP_SM_PS_SHIFT;

		ht_cap.cap |= smps;
	}

	if (ar_ht_cap & WMI_HT_CAP_TX_STBC)
		ht_cap.cap |= IEEE80211_HTCAP_TX_STBC;

	if (ar_ht_cap & WMI_HT_CAP_RX_STBC) {
		u32 stbc;

		stbc   = ar_ht_cap;
		stbc  &= WMI_HT_CAP_RX_STBC;
		stbc >>= WMI_HT_CAP_RX_STBC_MASK_SHIFT;
		stbc <<= IEEE80211_HTCAP_RX_STBC_SHIFT;
		stbc  &= IEEE80211_HTCAP_RX_STBC;

		ht_cap.cap |= stbc;
	}

	if (ar_ht_cap & WMI_HT_CAP_RX_LDPC)
		ht_cap.cap |= IEEE80211_HTCAP_LDPC_CODING;

	if (ar_ht_cap & WMI_HT_CAP_L_SIG_TXOP_PROT)
		ht_cap.cap |= IEEE80211_HTCAP_LSIG_TXOP_PROT;

	if (ar_vht_cap & WMI_VHT_CAP_MAX_MPDU_LEN_MASK)
		ht_cap.cap |= IEEE80211_HTCAP_MAX_AMSDU;

	for (i = 0; i < ar->num_rx_chains; i++) {
		if (rate_cap_rx_chainmask & BIT(i))
			ht_cap.mcs.rx_mask[i] = 0xFF;
	}

	ht_cap.mcs.tx_params |= IEEE80211_HTCAP_MCS_TX_DEFINED;

	return ht_cap;
}

static int ath11k_mac_set_txbf_conf(struct ath11k_vif *arvif)
{
	u32 value = 0;
	struct ath11k *ar = arvif->ar;
	int nsts;
	int sound_dim;
	u32 vht_cap = ar->pdev->cap.vht_cap;
	u32 vdev_param = WMI_VDEV_PARAM_TXBF;

	if (vht_cap & (IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE)) {
		nsts = vht_cap & IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK;
		nsts >>= IEEE80211_VHTCAP_BEAMFORMEE_STS_SHIFT;
		value |= SM(nsts, WMI_TXBF_STS_CAP_OFFSET);
	}

	if (vht_cap & (IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE)) {
		sound_dim = vht_cap &
			    IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK;
		sound_dim >>= IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_SHIFT;
		if (sound_dim > (ar->num_tx_chains - 1))
			sound_dim = ar->num_tx_chains - 1;
		value |= SM(sound_dim, WMI_BF_SOUND_DIM_OFFSET);
	}

	if (!value)
		return 0;

	if (vht_cap & IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE) {
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFER;

		if ((vht_cap & IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE) &&
		    arvif->vdev_type == WMI_VDEV_TYPE_AP)
			value |= WMI_VDEV_PARAM_TXBF_MU_TX_BFER;
	}

	/* TODO: SUBFEE not validated in HK, disable here until validated? */

	if (vht_cap & IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE) {
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFEE;

		if ((vht_cap & IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE) &&
		    arvif->vdev_type == WMI_VDEV_TYPE_STA)
			value |= WMI_VDEV_PARAM_TXBF_MU_TX_BFEE;
	}

	return ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					     vdev_param, value);
}

static void ath11k_set_vht_txbf_cap(struct ath11k *ar, u32 *vht_cap)
{
	bool subfer, subfee;
	int sound_dim = 0;

	subfer = !!(*vht_cap & (IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE));
	subfee = !!(*vht_cap & (IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE));

	if (ar->num_tx_chains < 2) {
		*vht_cap &= ~(IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE);
		subfer = false;
	}

	/* If SU Beaformer is not set, then disable MU Beamformer Capability */
	if (!subfer)
		*vht_cap &= ~(IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE);

	/* If SU Beaformee is not set, then disable MU Beamformee Capability */
	if (!subfee)
		*vht_cap &= ~(IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE);

	sound_dim = (*vht_cap & IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK);
	sound_dim >>= IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_SHIFT;
	*vht_cap &= ~IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK;

	/* TODO: Need to check invalid STS and Sound_dim values set by FW? */

	/* Enable Sounding Dimension Field only if SU BF is enabled */
	if (subfer) {
		if (sound_dim > (ar->num_tx_chains - 1))
			sound_dim = ar->num_tx_chains - 1;

		sound_dim <<= IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_SHIFT;
		sound_dim &=  IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK;
		*vht_cap |= sound_dim;
	}

	/* Use the STS advertised by FW unless SU Beamformee is not supported*/
	if (!subfee)
		*vht_cap &= ~(IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK);
}

static struct ieee80211_sta_vht_cap
ath11k_create_vht_cap(struct ath11k *ar, u32 rate_cap_tx_chainmask,
		      u32 rate_cap_rx_chainmask)
{
	struct ieee80211_sta_vht_cap vht_cap = {0};
	u16 txmcs_map, rxmcs_map;
	int i;

	vht_cap.vht_supported = 1;
	vht_cap.cap = ar->pdev->cap.vht_cap;

	ath11k_set_vht_txbf_cap(ar, &vht_cap.cap);

	/* TODO: Enable back VHT160 mode once association issues are fixed */
	/* Disabling VHT160 and VHT80+80 modes */
	vht_cap.cap &= ~IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK;
	vht_cap.cap &= ~IEEE80211_VHTCAP_SHORT_GI_160;

	rxmcs_map = 0;
	txmcs_map = 0;
	for (i = 0; i < 8; i++) {
		if (i < ar->num_tx_chains && rate_cap_tx_chainmask & BIT(i))
			txmcs_map |= IEEE80211_VHTCAP_MCS_SUPPORT_0_9 << (i * 2);
		else
			txmcs_map |= IEEE80211_VHTCAP_MCS_NOT_SUPPORTED << (i * 2);

		if (i < ar->num_rx_chains && rate_cap_rx_chainmask & BIT(i))
			rxmcs_map |= IEEE80211_VHTCAP_MCS_SUPPORT_0_9 << (i * 2);
		else
			rxmcs_map |= IEEE80211_VHTCAP_MCS_NOT_SUPPORTED << (i * 2);
	}

	if (rate_cap_tx_chainmask <= 1)
		vht_cap.cap &= ~IEEE80211_VHTCAP_TXSTBC;

	vht_cap.vht_mcs.rx_mcs_map = cpu_to_le16(rxmcs_map);
	vht_cap.vht_mcs.tx_mcs_map = cpu_to_le16(txmcs_map);

	return vht_cap;
}

static void ath11k_mac_setup_ht_vht_cap(struct ath11k *ar,
					struct ath11k_pdev_cap *cap,
					u32 *ht_cap_info)
{
	struct ieee80211_supported_band *band;
	u32 rate_cap_tx_chainmask;
	u32 rate_cap_rx_chainmask;
	u32 ht_cap;

	rate_cap_tx_chainmask = ar->cfg_tx_chainmask >> cap->tx_chain_mask_shift;
	rate_cap_rx_chainmask = ar->cfg_rx_chainmask >> cap->rx_chain_mask_shift;

	if (cap->supported_bands & WMI_HOST_WLAN_2G_CAP) {
		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		ht_cap = cap->band[NL80211_BAND_2GHZ].ht_cap_info;
		if (ht_cap_info)
			*ht_cap_info = ht_cap;
		band->ht_cap = ath11k_create_ht_cap(ar, ht_cap,
						    rate_cap_rx_chainmask);
        ath11k_info(ar->ab, "BAND 2G ht_cap: ht_supported=%u, cap=0x%x\n",
            band->ht_cap.ht_supported, band->ht_cap.cap);
	}

	if (cap->supported_bands & WMI_HOST_WLAN_5G_CAP &&
	    (ar->ab->hw_params.single_pdev_only ||
	    !ar->supports_6ghz)) {
		band = &ar->mac.sbands[NL80211_BAND_5GHZ];
		ht_cap = cap->band[NL80211_BAND_5GHZ].ht_cap_info;
		if (ht_cap_info)
			*ht_cap_info = ht_cap;
		band->ht_cap = ath11k_create_ht_cap(ar, ht_cap,
						    rate_cap_rx_chainmask);
		band->vht_cap = ath11k_create_vht_cap(ar, rate_cap_tx_chainmask,
						      rate_cap_rx_chainmask);

        ath11k_info(ar->ab, "BAND 5G ht_cap: ht_supported=%u, cap=0x%x\n",
            band->ht_cap.ht_supported, band->ht_cap.cap);
        ath11k_info(ar->ab, "BAND 5G vht_cap: vht_supported=%u, cap=0x%x\n",
            band->vht_cap.vht_supported, band->vht_cap.cap);
	}
}

static int ath11k_check_chain_mask(struct ath11k *ar, u32 ant, bool is_tx_ant)
{
	/* TODO: Check the request chainmask against the supported
	 * chainmask table which is advertised in extented_service_ready event
	 */

	return 0;
}

static void ath11k_gen_ppe_thresh(struct ath11k_ppe_threshold *fw_ppet,
				  u8 *he_ppet)
{
	int nss, ru;
	u8 bit = 7;

	he_ppet[0] = fw_ppet->numss_m1 & IEEE80211_HE_PPE_THRES_NSS_MASK;
	he_ppet[0] |= (fw_ppet->ru_bit_mask <<
		       IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_POS) &
		      IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_MASK;
	for (nss = 0; nss <= (int)fw_ppet->numss_m1; nss++) {
		for (ru = 0; ru < 4; ru++) {
			u8 val;
			int i;

			if ((fw_ppet->ru_bit_mask & BIT(ru)) == 0)
				continue;
			val = (fw_ppet->ppet16_ppet8_ru3_ru0[nss] >> (ru * 6)) &
			       0x3f;
			val = ((val >> 3) & 0x7) | ((val & 0x7) << 3);
			for (i = 5; i >= 0; i--) {
				he_ppet[bit / 8] |=
					((val >> i) & 0x1) << ((bit % 8));
				bit++;
			}
		}
	}
}

static void
ath11k_mac_filter_he_cap_mesh(struct ieee80211_he_capabilities *he_capabilities)
{
	u8 m;

	m = IEEE80211_HEMAC_CAP0_TWT_RES |
	    IEEE80211_HEMAC_CAP0_TWT_REQ;
	he_capabilities->mac_cap_info[0] &= ~m;

	m = IEEE80211_HEMAC_CAP2_TRS |
	    IEEE80211_HEMAC_CAP2_BCAST_TWT |
	    IEEE80211_HEMAC_CAP2_MU_CASCADING;
	he_capabilities->mac_cap_info[2] &= ~m;

	m = IEEE80211_HEMAC_CAP3_FLEX_TWT_SCHED |
	    IEEE80211_HEMAC_CAP2_BCAST_TWT |
	    IEEE80211_HEMAC_CAP2_MU_CASCADING;
	he_capabilities->mac_cap_info[3] &= ~m;

	m = IEEE80211_HEMAC_CAP4_BSRP_BQRP_A_MPDU_AGG |
	    IEEE80211_HEMAC_CAP4_BQR;
	he_capabilities->mac_cap_info[4] &= ~m;

	m = IEEE80211_HEMAC_CAP5_SUBCHAN_SELECTIVE_TRANSMISSION |
	    IEEE80211_HEMAC_CAP5_UL_2x996_TONE_RU |
	    IEEE80211_HEMAC_CAP5_PUNCTURED_SOUNDING |
	    IEEE80211_HEMAC_CAP5_HT_VHT_TRIG_FRAME_RX;
	he_capabilities->mac_cap_info[5] &= ~m;

	m = IEEE80211_HEPHY_CAP2_UL_MU_FULL_MU_MIMO |
	    IEEE80211_HEPHY_CAP2_UL_MU_PARTIAL_MU_MIMO;
	he_capabilities->phy_cap_info[2] &= ~m;

	m = IEEE80211_HEPHY_CAP3_RX_HE_MU_PPDU_FROM_NON_AP_STA |
	    IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_TX_MASK |
	    IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_RX_MASK;
	he_capabilities->phy_cap_info[3] &= ~m;

	m = IEEE80211_HEPHY_CAP4_MU_BEAMFORMER;
	he_capabilities->phy_cap_info[4] &= ~m;

	m = IEEE80211_HEPHY_CAP5_NG16_MU_FEEDBACK;
	he_capabilities->phy_cap_info[5] &= ~m;

	m = IEEE80211_HEPHY_CAP6_CODEBOOK_SIZE_75_MU |
	    IEEE80211_HEPHY_CAP6_TRIG_MU_BEAMFORMER_FB |
	    IEEE80211_HEPHY_CAP6_TRIG_CQI_FB |
	    IEEE80211_HEPHY_CAP6_PARTIAL_BANDWIDTH_DL_MUMIMO;
	he_capabilities->phy_cap_info[6] &= ~m;

	m = IEEE80211_HEPHY_CAP7_SRP_BASED_SR |
	    IEEE80211_HEPHY_CAP7_POWER_BOOST_FACTOR_AR |
	    IEEE80211_HEPHY_CAP7_STBC_TX_ABOVE_80MHZ |
	    IEEE80211_HEPHY_CAP7_STBC_RX_ABOVE_80MHZ;
	he_capabilities->phy_cap_info[7] &= ~m;

	m = IEEE80211_HEPHY_CAP8_HE_ER_SU_PPDU_4XLTF_AND_08_US_GI |
	    IEEE80211_HEPHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
	    IEEE80211_HEPHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
	    IEEE80211_HEPHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU;
	he_capabilities->phy_cap_info[8] &= ~m;

	m = IEEE80211_HEPHY_CAP9_LONGER_THAN_16_SIGB_OFDM_SYM |
	    IEEE80211_HEPHY_CAP9_NON_TRIGGERED_CQI_FEEDBACK |
	    IEEE80211_HEPHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU |
	    IEEE80211_HEPHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU |
	    IEEE80211_HEPHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_COMP_SIGB |
	    IEEE80211_HEPHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_NON_COMP_SIGB;
	he_capabilities->phy_cap_info[9] &= ~m;
}

static __le16 ath11k_mac_setup_he_6ghz_cap(struct ath11k_pdev_cap *pcap,
					   struct ath11k_band_cap *bcap)
{
	u8 val;

	bcap->he_6ghz_capa = IEEE80211_HTCAP_MPDU_DENSITY_NONE;
	if (bcap->ht_cap_info & WMI_HT_CAP_DYNAMIC_SMPS)
		bcap->he_6ghz_capa |=
			FIELD_PREP(IEEE80211_HE_6GHZCAP_SM_PS,
				   WLAN_HTCAP_SM_PS_DYNAMIC);
	else
		bcap->he_6ghz_capa |=
			FIELD_PREP(IEEE80211_HE_6GHZCAP_SM_PS,
				   WLAN_HTCAP_SM_PS_DISABLED);
	val = (u8)FIELD_GET(IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK,
			pcap->vht_cap);
	bcap->he_6ghz_capa |=
		FIELD_PREP(IEEE80211_HE_6GHZCAP_MAX_AMPDU_LEN_EXP, val);
	val = (u8)FIELD_GET(IEEE80211_VHTCAP_MAX_MPDU_MASK, pcap->vht_cap);
	bcap->he_6ghz_capa |=
		FIELD_PREP(IEEE80211_HE_6GHZCAP_MAX_MPDU_LEN, val);
	if (pcap->vht_cap & IEEE80211_VHTCAP_RX_ANTENNA_PATTERN)
		bcap->he_6ghz_capa |= IEEE80211_HE_6GHZCAP_RX_ANTPAT_CONS;
	if (pcap->vht_cap & IEEE80211_VHTCAP_TX_ANTENNA_PATTERN)
		bcap->he_6ghz_capa |= IEEE80211_HE_6GHZCAP_TX_ANTPAT_CONS;

	return cpu_to_le16(bcap->he_6ghz_capa);
}

static int ath11k_mac_copy_he_cap(struct ath11k *ar,
				  struct ath11k_pdev_cap *cap,
				  struct ieee80211_sband_iftype_data *data,
				  int band)
{
	int i, idx = 0;

	for (i = 0; i < NUM_NL80211_IFTYPES; i++) {
		struct ieee80211_sta_he_cap *sta_he_cap = &data[idx].he_cap;
		struct ath11k_band_cap *band_cap = &cap->band[band];
		struct ieee80211_he_capabilities *he_capabilities =
				&sta_he_cap->he_capabilities;

		switch (i) {
		case NL80211_IFTYPE_STATION:
		case NL80211_IFTYPE_AP:
		case NL80211_IFTYPE_MESH_POINT:
			break;

		default:
			continue;
		}

		data[idx].types_mask = BIT(i);
        sta_he_cap->he_supported = true;
		memcpy(he_capabilities->mac_cap_info, band_cap->he_cap_info,
		       sizeof(he_capabilities->mac_cap_info));
		memcpy(he_capabilities->phy_cap_info, band_cap->he_cap_phy_info,
		       sizeof(he_capabilities->phy_cap_info));

		he_capabilities->mac_cap_info[1] &=
			IEEE80211_HEMAC_CAP1_TF_MAC_PAD_DUR_MASK;
		he_capabilities->phy_cap_info[4] &=
			~IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_MASK;
		he_capabilities->phy_cap_info[4] &=
			~IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_MASK;
		he_capabilities->phy_cap_info[4] |= (ar->num_tx_chains - 1) << 2;

		he_capabilities->phy_cap_info[5] &=
			~IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_MASK;
		he_capabilities->phy_cap_info[5] &=
			~IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK;
		he_capabilities->phy_cap_info[5] |= ar->num_tx_chains - 1;

		switch (i) {
		case NL80211_IFTYPE_AP:
			he_capabilities->phy_cap_info[9] |=
				IEEE80211_HEPHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU;
			break;
		case NL80211_IFTYPE_STATION:
			he_capabilities->mac_cap_info[0] &=
				~IEEE80211_HEMAC_CAP0_TWT_RES;
			he_capabilities->mac_cap_info[0] |=
				IEEE80211_HEMAC_CAP0_TWT_REQ;
			he_capabilities->phy_cap_info[9] |=
				IEEE80211_HEPHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU;
			break;
		case NL80211_IFTYPE_MESH_POINT:
			ath11k_mac_filter_he_cap_mesh(he_capabilities);
			break;
		}

        sta_he_cap->he_mcs_nss_supp.he_rx_mcs_80 =
			cpu_to_le16(band_cap->he_mcs & 0xffff);
        sta_he_cap->he_mcs_nss_supp.he_tx_mcs_80 =
			cpu_to_le16(band_cap->he_mcs & 0xffff);
        sta_he_cap->he_mcs_nss_supp.he_rx_mcs_160 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
        sta_he_cap->he_mcs_nss_supp.he_tx_mcs_160 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
        sta_he_cap->he_mcs_nss_supp.he_rx_mcs_80p80 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
        sta_he_cap->he_mcs_nss_supp.he_tx_mcs_80p80 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);

		memset(sta_he_cap->ppe_thres, 0, sizeof(sta_he_cap->ppe_thres));
		if (he_capabilities->phy_cap_info[6] &
		    IEEE80211_HEPHY_CAP6_PPE_THRESHOLD_PRESENT)
			ath11k_gen_ppe_thresh(&band_cap->he_ppet,
                sta_he_cap->ppe_thres);
				
		if (band == NL80211_BAND_6GHZ) {
			data[idx].he_6ghz_cap.cap =
				ath11k_mac_setup_he_6ghz_cap(cap, band_cap);
		}
		idx++;
	}

	return idx;
}

static void ath11k_mac_setup_he_cap(struct ath11k *ar,
				    struct ath11k_pdev_cap *cap)
{
#if ATH11K_SUPPORT_HE
	struct ieee80211_supported_band *band;
	int count;

	if (cap->supported_bands & WMI_HOST_WLAN_2G_CAP) {
		count = ath11k_mac_copy_he_cap(ar, cap,
					       ar->mac.iftype[NL80211_BAND_2GHZ],
					       NL80211_BAND_2GHZ);
		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		band->iftype_data = ar->mac.iftype[NL80211_BAND_2GHZ];
		band->n_iftype_data = (u16)count;
	}

	if (cap->supported_bands & WMI_HOST_WLAN_5G_CAP) {
		count = ath11k_mac_copy_he_cap(ar, cap,
					       ar->mac.iftype[NL80211_BAND_5GHZ],
					       NL80211_BAND_5GHZ);
		band = &ar->mac.sbands[NL80211_BAND_5GHZ];
		band->iftype_data = ar->mac.iftype[NL80211_BAND_5GHZ];
		band->n_iftype_data = (u16)count;
	}

	if (cap->supported_bands & WMI_HOST_WLAN_5G_CAP &&
	    ar->supports_6ghz) {
		count = ath11k_mac_copy_he_cap(ar, cap,
					       ar->mac.iftype[NL80211_BAND_6GHZ],
					       NL80211_BAND_6GHZ);
		band = &ar->mac.sbands[NL80211_BAND_6GHZ];
		band->iftype_data = ar->mac.iftype[NL80211_BAND_6GHZ];
		band->n_iftype_data = (u16)count;
	}
#endif
}

static int __ath11k_set_antenna(struct ath11k *ar, u32 tx_ant, u32 rx_ant)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	if (ath11k_check_chain_mask(ar, tx_ant, true))
		return -EINVAL;

	if (ath11k_check_chain_mask(ar, rx_ant, false))
		return -EINVAL;

	ar->cfg_tx_chainmask = (u8)tx_ant;
	ar->cfg_rx_chainmask = (u8)rx_ant;

	if (ar->state != ATH11K_STATE_ON &&
	    ar->state != ATH11K_STATE_RESTARTED)
		return 0;

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_TX_CHAIN_MASK,
					tx_ant, ar->pdev->pdev_id);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set tx-chainmask: %d, req 0x%x\n",
			    ret, tx_ant);
		return ret;
	}

	ar->num_tx_chains = get_num_chains(tx_ant);

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_RX_CHAIN_MASK,
					rx_ant, ar->pdev->pdev_id);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set rx-chainmask: %d, req 0x%x\n",
			    ret, rx_ant);
		return ret;
	}

	ar->num_rx_chains = get_num_chains(rx_ant);

	/* Reload HT/VHT/HE capability */
	ath11k_mac_setup_ht_vht_cap(ar, &ar->pdev->cap, NULL);
	ath11k_mac_setup_he_cap(ar, &ar->pdev->cap);

	return 0;
}

int ath11k_mac_tx_mgmt_pending_free(int buf_id, void *skb, void *ctx)
{
	struct ath11k *ar = ctx;
	struct ath11k_base *ab = ar->ab;
	struct sk_buff *msdu = skb;
	struct ieee80211_tx_info *info;

	spin_lock_bh(&ar->txmgmt_idr_lock);
	idr_remove(&ar->txmgmt_idr, buf_id);
	spin_unlock_bh(&ar->txmgmt_idr_lock);
	dma_unmap_single(ab->dev, ATH11K_SKB_CB(msdu)->paddr, 
        ATH11K_SKB_CB(msdu)->paddr_mapping_addr, msdu->len, DMA_TO_DEVICE);

	info = IEEE80211_SKB_CB(msdu);
	memset(&info->u.status, 0, sizeof(info->u.status));

	ieee80211_free_txskb(ar->hw, msdu);

	return 0;
}

static int ath11k_mac_vif_txmgmt_idr_remove(int buf_id, void *skb, void *ctx)
{
	struct ieee80211_vif *vif = ctx;
	struct ath11k_skb_cb *skb_cb = ATH11K_SKB_CB((struct sk_buff *)skb);
	struct sk_buff *msdu = skb;
	struct ath11k *ar = skb_cb->ar;
	struct ath11k_base *ab = ar->ab;

	if (skb_cb->vif == vif) {
		spin_lock_bh(&ar->txmgmt_idr_lock);
		idr_remove(&ar->txmgmt_idr, buf_id);
		spin_unlock_bh(&ar->txmgmt_idr_lock);
		dma_unmap_single(ab->dev, skb_cb->paddr, skb_cb->paddr_mapping_addr,
            msdu->len, DMA_TO_DEVICE);
	}

	return 0;
}

static int ath11k_mac_mgmt_tx_wmi(struct ath11k *ar, struct ath11k_vif *arvif,
				  struct sk_buff *skb)
{
	struct ath11k_base *ab = ar->ab;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_tx_info *info;
	dma_addr_t paddr;
    void *paddr_mapping_addr;
	int buf_id;
	int ret;

	spin_lock_bh(&ar->txmgmt_idr_lock);
	buf_id = idr_alloc(&ar->txmgmt_idr, skb, 0,
			   ATH11K_TX_MGMT_NUM_PENDING_MAX);
	spin_unlock_bh(&ar->txmgmt_idr_lock);
	if (buf_id < 0)
		return -ENOSPC;

	info = IEEE80211_SKB_CB(skb);
	if (!(info->flags & IEEE80211_TX_CTRL_HW_80211_ENCAP)) {
		if ((ieee80211_is_action(hdr->frame_control) ||
		     ieee80211_is_deauth(hdr->frame_control) ||
		     ieee80211_is_disassoc(hdr->frame_control)) &&
		     ieee80211_has_protected(hdr->frame_control)) {
			skb_put(skb, IEEE80211_CCMP_MIC_LENGTH);
		}
	}

	ret = dma_map_single(ab->dev, skb->data, skb->len, DMA_TO_DEVICE, 
         &paddr, &paddr_mapping_addr);
	if (ret) {
		ath11k_warn(ab, "failed to DMA map mgmt Tx buffer\n");
		ret = -EIO;
		goto err_free_idr;
	}

	ATH11K_SKB_CB(skb)->ar = ar;
	ATH11K_SKB_CB(skb)->paddr = paddr;
    ATH11K_SKB_CB(skb)->paddr_mapping_addr = paddr_mapping_addr;

	ret = ath11k_wmi_mgmt_send(ar, arvif->vdev_id, buf_id, skb);
	if (ret) {
		ath11k_warn(ar->ab, "failed to send mgmt frame: %d\n", ret);
		goto err_unmap_buf;
	}

	return 0;

err_unmap_buf:
	dma_unmap_single(ab->dev, ATH11K_SKB_CB(skb)->paddr,
        ATH11K_SKB_CB(skb)->paddr_mapping_addr, skb->len, DMA_TO_DEVICE);

err_free_idr:
	spin_lock_bh(&ar->txmgmt_idr_lock);
	idr_remove(&ar->txmgmt_idr, buf_id);
	spin_unlock_bh(&ar->txmgmt_idr_lock);

	return ret;
}

static void ath11k_mgmt_over_wmi_tx_purge(struct ath11k *ar)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&ar->wmi_mgmt_tx_queue)) != NULL)
		ieee80211_free_txskb(ar->hw, skb);
}

static void ath11k_mgmt_over_wmi_tx_work(void *context)
{
	struct ath11k *ar = context;
	struct ath11k_skb_cb *skb_cb;
	struct ath11k_vif *arvif;
	struct sk_buff *skb;
	int ret;

    ath11k_info(ar->ab, "tx queue length is %u\n", 
        skb_queue_len(&ar->wmi_mgmt_tx_queue));

	while ((skb = skb_dequeue(&ar->wmi_mgmt_tx_queue)) != NULL) {
		skb_cb = ATH11K_SKB_CB(skb);
		if (!skb_cb->vif) {
			ath11k_warn(ar->ab, "no vif found for mgmt frame\n");
			ieee80211_free_txskb(ar->hw, skb);
			continue;
		}
		
		arvif = ath11k_vif_to_arvif(skb_cb->vif);

		ret = ath11k_mac_mgmt_tx_wmi(ar, arvif, skb);
		if (ret) {
			ath11k_warn(ar->ab, "failed to transmit management frame %d\n",
				    ret);
			ieee80211_free_txskb(ar->hw, skb);
		} else {
			atomic_inc(&ar->num_pending_mgmt_tx);
		}
	}
}

static int ath11k_mac_mgmt_tx(struct ath11k *ar, struct sk_buff *skb,
			      bool is_prb_rsp)
{
    struct ath11k_base *ab = ar->ab;
	struct sk_buff_head *q = &ar->wmi_mgmt_tx_queue;

	if (test_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags))
		return -ESHUTDOWN;

	/* Drop probe response packets when the pending management tx
	 * count has reached a certain threshold, so as to prioritize
	 * other mgmt packets like auth and assoc to be sent on time
	 * for establishing successful connections.
	 */
	if (is_prb_rsp &&
	    atomic_read(&ar->num_pending_mgmt_tx) > ATH11K_PRB_RSP_DROP_THRESHOLD) {
		ath11k_warn(ab,
			    "dropping probe response as pending queue is almost full\n");
		return -ENOSPC;
	}

	if (skb_queue_len(q) == ATH11K_TX_MGMT_NUM_PENDING_MAX) {
		ath11k_warn(ab, "mgmt tx queue is full\n");
		return -ENOSPC;
	}

    ath11k_info(ab, "queue skb 0x%p\n", skb);

	skb_queue_tail(q, skb);
	ieee80211_queue_work(ar->hw, &ar->wmi_mgmt_tx_work);

	return 0;
}

static void ath11k_mac_op_tx(struct ieee80211_hw *hw,
			     struct ieee80211_tx_control *control,
			     struct sk_buff *skb)
{
    struct ath11k_skb_cb *skb_cb = ATH11K_SKB_CB((struct sk_buff *)skb);
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_vif *vif = info->u.control.vif;
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_key_conf *key = info->u.control.hw_key;
	u32 info_flags = info->flags;
	bool is_prb_rsp;
	int ret;

	memset(skb_cb, 0, sizeof(*skb_cb));
	skb_cb->vif = vif;
	
	if (key) {
		skb_cb->cipher = key->cipher;
		skb_cb->flags |= ATH11K_SKB_CIPHER_SET;
	}
	
	if (info_flags & IEEE80211_TX_CTRL_HW_80211_ENCAP) {
			skb_cb->flags |= ATH11K_SKB_HW_80211_ENCAP;
	} else if (ieee80211_is_mgmt(hdr->frame_control)) {
        ath11k_dbg_dump(ar->ab, ATH11K_DBG_PKT, "mgmt ", skb->data, skb->len, 0);
		is_prb_rsp = ieee80211_is_probe_resp(hdr->frame_control);
		ret = ath11k_mac_mgmt_tx(ar, skb, is_prb_rsp);
		if (ret) {
			ath11k_warn(ar->ab, "failed to queue management frame %d\n",
				    ret);
            ieee80211_tx_status(ar->hw, skb);
		}
		return;
	}

    ath11k_dbg_dump(ar->ab, ATH11K_DBG_PKT, "data ", skb->data, skb->len, 0);
	ret = ath11k_dp_tx(ar, arvif, skb);
	if (ret) {
		ath11k_warn(ar->ab, "failed to transmit frame %d\n", ret);
        ieee80211_tx_status(ar->hw, skb);
	}
}

void ath11k_mac_drain_tx(struct ath11k *ar)
{
	/* make sure rcu-protected mac80211 tx path itself is drained */
	synchronize_net();

	cancel_work_sync(&ar->wmi_mgmt_tx_work);
	ath11k_mgmt_over_wmi_tx_purge(ar);
}

#if ATH11K_SUPPORT_MONITOR
static int ath11k_mac_config_mon_status_default(struct ath11k *ar, bool enable)
{
	struct htt_rx_ring_tlv_filter tlv_filter = {0};
	u32 ring_id;
	int i, ret = 0;

	if (enable)
		tlv_filter = ath11k_mac_mon_status_filter_default;

	for (i = 0; i < MAX_MACS_PER_PDEV; i++) {
		ring_id = ar->dp.rx_mon_status_refill_ring[i].refill_buf_ring.ring_id;

		ret = ath11k_dp_tx_htt_rx_filter_setup(ar->ab, ring_id, ar->dp.mac_id + i,
							HAL_RXDMA_MONITOR_STATUS,
							DP_RX_BUFFER_SIZE, &tlv_filter);
	}
	return ret;
}
#endif // !ATH11K_SUPPORT_MONITOR

static int ath11k_mac_op_start(struct ieee80211_hw *hw)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;
	struct ath11k_pdev *pdev = ar->pdev;
	int ret;

    ath11k_info(ar->ab, "hw 0x%p\n", hw);

	ath11k_mac_drain_tx(ar);
	mutex_lock(&ar->conf_mutex);

	switch (ar->state) {
	case ATH11K_STATE_OFF:
		/* if mac_op_stop was called, then needs to download
		 * firmware again for pci device in non-wow scenario.
		 */
		if (test_bit(ATH11K_FLAG_MAC_STOPPED, &ab->dev_flags)) {
			set_bit(ATH11K_FLAG_MAC_STARTING, &ab->dev_flags);
			init_completion(&ab->fw_mac_restart);
			ath11k_hif_power_up(ab);

			if (!wait_for_completion_timeout(&ab->fw_mac_restart,
							 ATH11K_MAC_START_TIMEOUT)) {
				ath11k_err(ab, "wait mac start timeout\n");
				ret = -ETIMEDOUT;
				goto err;
			}
			clear_bit(ATH11K_FLAG_MAC_STARTING, &ab->dev_flags);
			clear_bit(ATH11K_FLAG_MAC_STOPPED, &ab->dev_flags);
		}
		ar->state = ATH11K_STATE_ON;
		break;
	case ATH11K_STATE_RESTARTING:
		ar->state = ATH11K_STATE_RESTARTED;
		break;
	case ATH11K_STATE_RESTARTED:
	case ATH11K_STATE_WEDGED:
	case ATH11K_STATE_ON:
	case ATH11K_STATE_TM:
		WARN_ON(1);
		ret = -EINVAL;
		goto err;
	}

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_PMF_QOS,
					1, pdev->pdev_id);

	if (ret) {
		ath11k_err(ar->ab, "failed to enable PMF QOS: (%d\n", ret);
		goto err;
	}

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_DYNAMIC_BW, 1,
					pdev->pdev_id);
	if (ret) {
		ath11k_err(ar->ab, "failed to enable dynamic bw: %d\n", ret);
		goto err;
	}

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_ARP_AC_OVERRIDE,
					0, pdev->pdev_id);
	if (ret) {
		ath11k_err(ab, "failed to set ac override for ARP: %d\n",
			   ret);
		goto err;
	}

	ret = ath11k_wmi_send_dfs_phyerr_offload_enable_cmd(ar, pdev->pdev_id);
	if (ret) {
		ath11k_err(ab, "failed to offload radar detection: %d\n",
			   ret);
		goto err;
	}

	ret = ath11k_dp_tx_htt_h2t_ppdu_stats_req(ar,
						  0x1fff);
	if (ret) {
		ath11k_err(ab, "failed to req ppdu stats: %d\n", ret);
		goto err;
	}

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_MESH_MCAST_ENABLE,
					1, pdev->pdev_id);

	if (ret) {
		ath11k_err(ar->ab, "failed to enable MESH MCAST ENABLE: (%d\n", ret);
		goto err;
	}

	__ath11k_set_antenna(ar, ar->cfg_tx_chainmask, ar->cfg_rx_chainmask);

	/* TODO: Do we need to enable ANI? */

	ath11k_reg_update_chan_list(ar);

	ar->num_started_vdevs = 0;
	ar->num_created_vdevs = 0;
	ar->num_peers = 0;

#if ath11k_dp_tx_htt_monitor_mode_ring_config
	/* Configure monitor status ring with default rx_filter to get rx status
	 * such as rssi, rx_duration.
	 */
	ret = ath11k_mac_config_mon_status_default(ar, true);
	if (ret) {
		ath11k_err(ab, "failed to configure monitor status ring with default rx_filter: (%d)\n",
			   ret);
		goto err;
	}
#endif

	mutex_unlock(&ar->conf_mutex);

	rcu_assign_pointer(ab->pdevs_active[ar->pdev_idx],
			   &ab->pdevs[ar->pdev_idx]);

	return 0;

err:
	ar->state = ATH11K_STATE_OFF;
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static void ath11k_mac_op_stop(struct ieee80211_hw *hw)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct htt_ppdu_stats_info *ppdu_stats, *tmp;
#if ATH11K_SUPPORT_MONITOR
	int ret;
#endif

    ath11k_info(ar->ab, "hw 0x%p\n", hw);

	ath11k_mac_drain_tx(ar);

	mutex_lock(&ar->conf_mutex);
#if ATH11K_SUPPORT_MONITOR
	ret = ath11k_mac_config_mon_status_default(ar, false);
	if (ret)
		ath11k_err(ar->ab, "failed to clear rx_filter for monitor status ring: (%d)\n",
			   ret);
#endif //!ATH11K_SUPPORT_MONITOR
	clear_bit(ATH11K_CAC_RUNNING, &ar->dev_flags);
	ar->state = ATH11K_STATE_OFF;
	mutex_unlock(&ar->conf_mutex);

	/* for pci device, need to power down target */
	if (ar->ab->hw_params.cut_off_power &&
	    !test_bit(ATH11K_FLAG_MAC_STOPPED, &ar->ab->dev_flags) &&
	    !test_bit(ATH11K_FLAG_UNREGISTERING, &ar->ab->dev_flags)) {
		set_bit(ATH11K_FLAG_MAC_STOPPED, &ar->ab->dev_flags);
		ath11k_core_stop(ar->ab);
		ath11k_hif_power_down(ar->ab);
		ath11k_hif_irq_disable(ar->ab);
	}

	cancel_delayed_work_sync(&ar->scan.timeout);
	cancel_work_sync(&ar->regd_update_work);

	spin_lock_bh(&ar->data_lock);
	list_for_each_entry_safe(ppdu_stats, tmp, &ar->ppdu_stats_info, struct htt_ppdu_stats_info, list) {
		list_del(&ppdu_stats->list);
		kfree(ppdu_stats);
	}
	spin_unlock_bh(&ar->data_lock);

	rcu_assign_pointer(ar->ab->pdevs_active[ar->pdev_idx], NULL);

	synchronize_rcu();

	atomic_set(&ar->num_pending_mgmt_tx, 0);
}

static void
ath11k_mac_setup_vdev_create_params(struct ath11k_vif *arvif,
				    struct vdev_create_params *params)
{
	struct ath11k *ar = arvif->ar;
	struct ath11k_pdev *pdev = ar->pdev;

	params->if_id = (u8)arvif->vdev_id;
	params->type = arvif->vdev_type;
	params->subtype = arvif->vdev_subtype;
	params->pdev_id = pdev->pdev_id;

	if (pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP) {
		params->chains[NL80211_BAND_2GHZ].tx = ar->num_tx_chains;
		params->chains[NL80211_BAND_2GHZ].rx = ar->num_rx_chains;
	}
	if (pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP) {
		params->chains[NL80211_BAND_5GHZ].tx = ar->num_tx_chains;
		params->chains[NL80211_BAND_5GHZ].rx = ar->num_rx_chains;
	}
	if (pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP &&
	    ar->supports_6ghz) {
		params->chains[NL80211_BAND_6GHZ].tx = ar->num_tx_chains;
		params->chains[NL80211_BAND_6GHZ].rx = ar->num_rx_chains;
	}
}

static u32
ath11k_mac_prepare_he_mode(struct ath11k_pdev *pdev, u32 viftype)
{
	struct ath11k_pdev_cap *pdev_cap = &pdev->cap;
	struct ath11k_band_cap *cap_band = NULL;
	u32 *hecap_phy_ptr = NULL;
	u32 hemode = 0;

	if (pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP)
		cap_band = &pdev_cap->band[NL80211_BAND_2GHZ];
	else
		cap_band = &pdev_cap->band[NL80211_BAND_5GHZ];

	hecap_phy_ptr = &cap_band->he_cap_phy_info[0];

	hemode = FIELD_PREP(HE_MODE_SU_TX_BFEE, HE_SU_BFEE_ENABLE) |
		 FIELD_PREP(HE_MODE_SU_TX_BFER, HECAP_PHY_SUBFMR_GET(hecap_phy_ptr)) |
		 FIELD_PREP(HE_MODE_UL_MUMIMO, HECAP_PHY_ULMUMIMO_GET(hecap_phy_ptr));

	/* TODO WDS and other modes */
	if (viftype == NL80211_IFTYPE_AP) {
		hemode |= FIELD_PREP(HE_MODE_MU_TX_BFER,
			  HECAP_PHY_MUBFMR_GET(hecap_phy_ptr)) |
			  FIELD_PREP(HE_MODE_DL_OFDMA, HE_DL_MUOFDMA_ENABLE) |
			  FIELD_PREP(HE_MODE_UL_OFDMA, HE_UL_MUOFDMA_ENABLE);
	} else {
		hemode |= FIELD_PREP(HE_MODE_MU_TX_BFEE, HE_MU_BFEE_ENABLE);
	}

	return hemode;
}

static int ath11k_set_he_mu_sounding_mode(struct ath11k *ar,
					  struct ath11k_vif *arvif)
{
	u32 param_id, param_value = 0;
	struct ath11k_base *ab = ar->ab;
	int ret = 0;

	param_id = WMI_VDEV_PARAM_SET_HEMU_MODE;
	param_value = ath11k_mac_prepare_he_mode(ar->pdev, ieee80211_vif_type(arvif->vif));
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, param_value);
	if (ret) {
		ath11k_warn(ab, "failed to set vdev %d HE MU mode: %d param_value %x\n",
			    arvif->vdev_id, ret, param_value);
		return ret;
	}
	param_id = WMI_VDEV_PARAM_SET_HE_SOUNDING_MODE;
	param_value =
		FIELD_PREP(HE_VHT_SOUNDING_MODE, HE_VHT_SOUNDING_MODE_ENABLE) |
		FIELD_PREP(HE_TRIG_NONTRIG_SOUNDING_MODE,
			   HE_TRIG_NONTRIG_SOUNDING_MODE_ENABLE);
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, param_value);
	if (ret) {
		ath11k_warn(ab, "failed to set vdev %d HE MU mode: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}
	return ret;
}

static bool ath11k_mac_has_ap_up(struct ath11k_base *ab)
{
	struct ath11k *ar;
	struct ath11k_pdev *pdev;
	struct ath11k_vif *arvif;
	int i;

	for (i = 0; i < (int)ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		list_for_each_entry(arvif, &ar->arvifs, struct ath11k_vif, list) {
			if (arvif->is_up && arvif->vdev_type == WMI_VDEV_TYPE_AP)
				return true;
		}
	}
	return false;
}

void ath11k_mac_11d_scan_start(struct ath11k *ar, u32 vdev_id, bool wait)
{
	int ret;

	mutex_lock(&ar->ab->vdev_id_11d_lock);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev id for 11d scan %d\n",
		   ar->vdev_id_11d_scan);

	if (ar->vdev_id_11d_scan != ATH11K_11D_INV_VDEV_ID)
		goto fin;
	
	if (test_bit(WMI_TLV_SERVICE_11D_OFFLOAD, ar->ab->wmi_ab.svc_map) &&
	    !(ath11k_mac_has_ap_up(ar->ab))) {
		struct wmi_11d_scan_start_params param;

		param.vdev_id = vdev_id;
		param.start_interval_msec = wait ? 0 : ATH11K_SCAN_11D_START_INTERVAL;
		param.scan_period_msec = ATH11K_SCAN_11D_INTERVAL;

		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac start 11d scan\n");

		ret = ath11k_wmi_send_11d_scan_start_cmd(ar, &param);
		if (ret) {
			ath11k_warn(ar->ab, "failed to start 11d scan vdev %d ret: %d\n",
				    vdev_id, ret);
		} else {
			ar->vdev_id_11d_scan = vdev_id;
			if (wait) {
				reinit_completion(&ar->finish_11d_scan);
				ar->pending_11d = true;
				ret = wait_for_completion_timeout(&ar->finish_11d_scan,
								  5 * HZ);
				ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
					   "mac 11d scan left time %d\n", ret);

				if (!ret)
					ar->pending_11d = false;
			}
		}
	}

fin:
	mutex_unlock(&ar->ab->vdev_id_11d_lock);
}

void ath11k_mac_11d_scan_stop(struct ath11k *ar)
{
	int ret;
	u32 vdev_id;

	if (test_bit(WMI_TLV_SERVICE_11D_OFFLOAD, ar->ab->wmi_ab.svc_map)) {
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac stop 11d scan\n");

		mutex_lock(&ar->ab->vdev_id_11d_lock);

		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac stop 11d vdev id %d\n",
			   ar->vdev_id_11d_scan);

		if (ar->vdev_id_11d_scan != ATH11K_11D_INV_VDEV_ID) {
			vdev_id = ar->vdev_id_11d_scan;

			ret = ath11k_wmi_send_11d_scan_stop_cmd(ar, vdev_id);
			if (ret)
				ath11k_warn(ar->ab,
					    "failed to stopt 11d scan vdev %d ret: %d\n",
					    vdev_id, ret);
			else
				ar->vdev_id_11d_scan = ATH11K_11D_INV_VDEV_ID;
		}
		mutex_unlock(&ar->ab->vdev_id_11d_lock);
	}
}

void ath11k_mac_11d_scan_stop_all(struct ath11k_base *ab)
{
	struct ath11k *ar;
	struct ath11k_pdev *pdev;
	int i;

	ath11k_dbg(ab, ATH11K_DBG_MAC, "mac stop soc 11d scan\n");

	for (i = 0; i < (int)ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;

		ath11k_mac_11d_scan_stop(ar);
	}
}

static int ath11k_mac_op_add_interface(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct vdev_create_params vdev_param = {0};
	struct peer_create_params peer_param;
	u32 param_id, param_value;
	u16 nss;
	u16 nss_temp = 0;
	u32 i;
	int ret;
	int bit;

    ieee80211_vif_drv_conf_set_uapsd(vif, true);

	mutex_lock(&ar->conf_mutex);

	if (ieee80211_vif_type(vif) == NL80211_IFTYPE_AP &&
	    ar->num_peers > (ar->max_num_peers - 1)) {
		ath11k_warn(ab, "failed to create vdev due to insufficient peer entry resource in firmware\n");
		ret = -ENOBUFS;
		goto err;
	}

	if (ar->num_created_vdevs > (TARGET_NUM_VDEVS - 1)) {
		ath11k_warn(ab, "failed to create vdev, reached max vdev limit %d\n",
			    TARGET_NUM_VDEVS);
		ret = -EBUSY;
		goto err;
	}

	memset(arvif, 0, sizeof(*arvif));

	arvif->ar = ar;
	arvif->vif = vif;

	list_init_head(&arvif->list);

	init_delayed_work(&arvif->connection_loss_work,
			  ath11k_mac_vif_sta_connection_loss_work, arvif);

	for (i = 0; i < ARRAY_SIZE(arvif->bitrate_mask.control); i++) {
		arvif->bitrate_mask.control[i].legacy = 0xffffffff;
		memset(arvif->bitrate_mask.control[i].ht_mcs, 0xff,
		       sizeof(arvif->bitrate_mask.control[i].ht_mcs));
		memset(arvif->bitrate_mask.control[i].vht_mcs, 0xff,
		       sizeof(arvif->bitrate_mask.control[i].vht_mcs));
	}

	bit = __ffs64(ab->free_vdev_map);

	arvif->vdev_id = bit;
	arvif->vdev_subtype = WMI_VDEV_SUBTYPE_NONE;

	switch (ieee80211_vif_type(vif)) {
	case NL80211_IFTYPE_UNSPECIFIED:
	case NL80211_IFTYPE_STATION:
		arvif->vdev_type = WMI_VDEV_TYPE_STA;
		break;
	case NL80211_IFTYPE_MESH_POINT:
		arvif->vdev_subtype = WMI_VDEV_SUBTYPE_MESH_11S;
		/* fall through */
	case NL80211_IFTYPE_AP:
		arvif->vdev_type = WMI_VDEV_TYPE_AP;
		break;
	case NL80211_IFTYPE_MONITOR:
		arvif->vdev_type = WMI_VDEV_TYPE_MONITOR;
		break;
	default:
		WARN_ON(1);
		break;
	}

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac add interface id %d type %d subtype %d map %llx\n",
		   arvif->vdev_id, arvif->vdev_type, arvif->vdev_subtype,
		   ab->free_vdev_map);

    ieee80211_vif_assign_hw_queue(vif, arvif->vdev_id);

	ath11k_mac_setup_vdev_create_params(arvif, &vdev_param);

	ret = ath11k_wmi_vdev_create(ar, ieee80211_vif_addr(vif), &vdev_param);
	if (ret) {
		ath11k_warn(ab, "failed to create WMI vdev %d: %d\n",
			    arvif->vdev_id, ret);
		goto err;
	}

	ar->num_created_vdevs++;
	ath11k_dbg(ab, ATH11K_DBG_MAC, "vdev %pM created, vdev_id %d\n",
        ieee80211_vif_addr(vif), arvif->vdev_id);
	ab->free_vdev_map &= ~(1LL << arvif->vdev_id);
	spin_lock_bh(&ar->data_lock);
	list_add_tail(&arvif->list, &ar->arvifs);
	spin_unlock_bh(&ar->data_lock);

	arvif->def_wep_key_idx = -1;

	param_id = WMI_VDEV_PARAM_TX_ENCAP_TYPE;
	param_value = ATH11K_HW_TXRX_ETHERNET;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, param_value);
	if (ret) {
		ath11k_warn(ab, "failed to set vdev %d tx encap mode: %d\n",
			    arvif->vdev_id, ret);
		goto err_vdev_del;
	}

	/* Do not enable ethernet mode for mesh vifs, packets in mesh network
	 * can be forwarded to other mesh nodes and mac80211 expects the packet
	 * in 802.11 format. Also, please note that ethernet mode shall not be
	 * used on interface where 4addr mode is enabled as we might not have
	 * 4addr related config during add_interface().
	 */
	if (ieee80211_vif_type(vif) != NL80211_IFTYPE_MESH_POINT) {
		param_id = WMI_VDEV_PARAM_RX_DECAP_TYPE;
		param_value = ATH11K_HW_TXRX_ETHERNET;

		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
							param_id, param_value);
		if (ret) {
			ath11k_warn(ab, "failed to set vdev %d tx encap mode: %d\n",
					arvif->vdev_id, ret);
			goto err_vdev_del;
		}
	}
	
	nss = ((nss_temp = get_num_chains(ar->cfg_tx_chainmask)) ? nss_temp : 1);
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    WMI_VDEV_PARAM_NSS, nss);
	if (ret) {
		ath11k_warn(ab, "failed to set vdev %d chainmask 0x%x, nss %d :%d\n",
			    arvif->vdev_id, ar->cfg_tx_chainmask, nss, ret);
		goto err_vdev_del;
	}

	switch (arvif->vdev_type) {
	case WMI_VDEV_TYPE_AP:
		peer_param.vdev_id = arvif->vdev_id;
		peer_param.peer_addr = ieee80211_vif_addr(vif);
		peer_param.peer_type = WMI_PEER_TYPE_DEFAULT;
		ret = ath11k_peer_create(ar, arvif, NULL, &peer_param);
		if (ret) {
			ath11k_warn(ab, "failed to vdev %d create peer for AP: %d\n",
				    arvif->vdev_id, ret);
			goto err_vdev_del;
		}

		ret = ath11k_mac_set_kickout(arvif);
		if (ret) {
			ath11k_warn(ar->ab, "failed to set vdev %d kickout parameters: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}
		break;
	case WMI_VDEV_TYPE_STA:
		param_id = WMI_STA_PS_PARAM_RX_WAKE_POLICY;
		param_value = WMI_STA_PS_RX_WAKE_POLICY_WAKE;
		ret = ath11k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
						  param_id, param_value);
		if (ret) {
			ath11k_warn(ar->ab, "failed to set vdev %d RX wake policy: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}

		param_id = WMI_STA_PS_PARAM_TX_WAKE_THRESHOLD;
		param_value = WMI_STA_PS_TX_WAKE_THRESHOLD_ALWAYS;
		ret = ath11k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
						  param_id, param_value);
		if (ret) {
			ath11k_warn(ar->ab, "failed to set vdev %d TX wake threshold: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}

		param_id = WMI_STA_PS_PARAM_PSPOLL_COUNT;
		param_value = WMI_STA_PS_PSPOLL_COUNT_NO_MAX;
		ret = ath11k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
						  param_id, param_value);
		if (ret) {
			ath11k_warn(ar->ab, "failed to set vdev %d pspoll count: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}

		ret = ath11k_wmi_pdev_set_ps_mode(ar, arvif->vdev_id, false);
		if (ret) {
			ath11k_warn(ar->ab, "failed to disable vdev %d ps mode: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}

		ath11k_mac_11d_scan_start(ar, arvif->vdev_id, false);
		break;
	default:
		break;
	}

	arvif->txpower = ieee80211_vif_bss_conf_get_txpower(vif);
	ret = ath11k_mac_txpower_recalc(ar);
	if (ret)
		goto err_peer_del;

	param_id = WMI_VDEV_PARAM_RTS_THRESHOLD;
	param_value = ieee80211_hw_get_rts_threshold(ar->hw);
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, param_value);
	if (ret) {
		ath11k_warn(ar->ab, "failed to set rts threshold for vdev %d: %d\n",
			    arvif->vdev_id, ret);
	}

	ath11k_dp_vdev_tx_attach(ar, arvif);

	mutex_unlock(&ar->conf_mutex);

	return 0;

err_peer_del:
	if (arvif->vdev_type == WMI_VDEV_TYPE_AP) {
		ar->num_peers--;
		ath11k_wmi_send_peer_delete_cmd(ar, 
            ieee80211_vif_addr(vif), arvif->vdev_id);
	}

err_vdev_del:
	ath11k_wmi_vdev_delete(ar, arvif->vdev_id);
	ar->num_created_vdevs--;
	ab->free_vdev_map |= 1LL << arvif->vdev_id;
	spin_lock_bh(&ar->data_lock);
	list_del(&arvif->list);
	spin_unlock_bh(&ar->data_lock);

err:
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static int ath11k_mac_vif_unref(int buf_id, void *skb, void *ctx)
{
	struct ieee80211_vif *vif = (struct ieee80211_vif *)ctx;
	struct ath11k_skb_cb *skb_cb = ATH11K_SKB_CB((struct sk_buff *)skb);

	if (skb_cb->vif == vif)
		skb_cb->vif = NULL;

	return 0;
}

static void ath11k_mac_op_remove_interface(struct ieee80211_hw *hw,
					   struct ieee80211_vif *vif)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ath11k_vif_to_arvif(vif);
	struct ath11k_base *ab = ar->ab;
	int ret;
	int i;

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ab, ATH11K_DBG_MAC, "mac remove interface (vdev %d)\n",
		   arvif->vdev_id);

	cancel_delayed_work_sync(&arvif->connection_loss_work);

	ab->free_vdev_map |= 1LL << (arvif->vdev_id);
	spin_lock_bh(&ar->data_lock);
	list_del(&arvif->list);
	spin_unlock_bh(&ar->data_lock);

	if (arvif->vdev_type == WMI_VDEV_TYPE_STA)
		ath11k_mac_11d_scan_stop(ar);

	if (arvif->vdev_type == WMI_VDEV_TYPE_AP) {
		ret = ath11k_peer_delete(ar, arvif->vdev_id, ieee80211_vif_addr(vif));
		if (ret)
			ath11k_warn(ab, "failed to submit AP self-peer removal on vdev %d: %d\n",
				    arvif->vdev_id, ret);
	}

    reinit_completion(&ar->vdev_delete_done);

	ret = ath11k_wmi_vdev_delete(ar, arvif->vdev_id);
	if (ret) {
		ath11k_warn(ab, "failed to delete WMI vdev %d: %d\n",
			    arvif->vdev_id, ret);
	}
	else {
		if (!wait_for_completion_timeout(&ar->vdev_delete_done,
	        ATH11K_VDEV_DELETE_TIMEOUT_HZ)) {
	        ath11k_warn(ab, "failed to wait vdev %d delete done\n",
	            arvif->vdev_id);
		}
    }

	ar->num_created_vdevs--;

	ath11k_peer_cleanup(ar, arvif->vdev_id);
	idr_for_each(&ar->txmgmt_idr,
		     ath11k_mac_vif_txmgmt_idr_remove, vif);

	for (i = 0; i < DP_TCL_NUM_RING_MAX; i++) {
		spin_lock_bh(&ab->dp.tx_ring[i].tx_idr_lock);
		idr_for_each(&ab->dp.tx_ring[i].txbuf_idr,
			     ath11k_mac_vif_unref, vif);
		spin_unlock_bh(&ab->dp.tx_ring[i].tx_idr_lock);
	}

	/* Recalc txpower for remaining vdev */
	ath11k_mac_txpower_recalc(ar);
	clear_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);

	/* TODO: recal traffic pause state based on the available vdevs */

	mutex_unlock(&ar->conf_mutex);
}

/* FIXME: Has to be verified. */
#define SUPPORTED_FILTERS			\
	(IEEE80211_FIF_ALLMULTI |				\
	IEEE80211_FIF_CONTROL |				\
	IEEE80211_FIF_PSPOLL |				\
	IEEE80211_FIF_OTHER_BSS |				\
	IEEE80211_FIF_BCN_PRBRESP_PROMISC |		\
	IEEE80211_FIF_PROBE_REQ |				\
	IEEE80211_FIF_FCSFAIL)

static void ath11k_mac_op_configure_filter(struct ieee80211_hw *hw,
					   unsigned int changed_flags,
					   unsigned int *total_flags,
					   u64 multicast)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	bool reset_flag = false;
#if ATH11K_SUPPORT_MONITOR
	int ret = 0;
#else
    DEBUG_PARAMETER(reset_flag);
#endif

	mutex_lock(&ar->conf_mutex);

	changed_flags &= SUPPORTED_FILTERS;
	*total_flags &= SUPPORTED_FILTERS;
	ar->filter_flags = *total_flags;

#if ATH11K_SUPPORT_MONITOR
	/* For monitor mode */
	reset_flag = !(ar->filter_flags & IEEE80211_FIF_BCN_PRBRESP_PROMISC);

	ret = ath11k_dp_tx_htt_monitor_mode_ring_config(ar, reset_flag);
	if (!ret) {
		if (!reset_flag)
			set_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
		else
			clear_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
	} else {
		ath11k_warn(ar->ab,
			    "fail to set monitor filter: %d\n", ret);
	}
#endif // !ATH11K_SUPPORT_MONITOR
	ath11k_info(ar->ab, "changed_flags:0x%x, total_flags:0x%x, reset_flag:%d\n",
		    changed_flags, *total_flags, reset_flag);

	mutex_unlock(&ar->conf_mutex);
}

static int ath11k_mac_op_get_antenna(struct ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);

	mutex_lock(&ar->conf_mutex);

	*tx_ant = ar->cfg_tx_chainmask;
	*rx_ant = ar->cfg_rx_chainmask;

	mutex_unlock(&ar->conf_mutex);

	return 0;
}

static int ath11k_mac_op_set_antenna(struct ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	int ret;

	mutex_lock(&ar->conf_mutex);
	ret = __ath11k_set_antenna(ar, tx_ant, rx_ant);
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static int ath11k_mac_op_ampdu_action(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_ampdu_params *params)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	int ret = -EINVAL;

	mutex_lock(&ar->conf_mutex);

	switch (params->action) {
	case IEEE80211_AMPDU_RX_START:
		ret = ath11k_dp_rx_ampdu_start(ar, params);
		break;
	case IEEE80211_AMPDU_RX_STOP:
		ret = ath11k_dp_rx_ampdu_stop(ar, params);
		break;
	case IEEE80211_AMPDU_TX_START:
	case IEEE80211_AMPDU_TX_STOP_CONT:
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		/* Tx A-MPDU aggregation offloaded to hw/fw so deny mac80211
		 * Tx aggregation requests.
		 */
		ret = -EOPNOTSUPP;
		break;
	}

	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static int ath11k_mac_op_add_chanctx(struct ieee80211_hw *hw,
				     struct ieee80211_chanctx_conf *ctx)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx add freq %u width %d ptr %pK\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx);

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	/* TODO: In case of multiple channel context, populate rx_channel from
	 * Rx PPDU desc information.
	 */
	ar->rx_channel = ctx->def.chan;
	spin_unlock_bh(&ar->data_lock);

	mutex_unlock(&ar->conf_mutex);

	return 0;
}

static void ath11k_mac_op_remove_chanctx(struct ieee80211_hw *hw,
					 struct ieee80211_chanctx_conf *ctx)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx remove freq %u width %d ptr %pK\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx);

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	/* TODO: In case of there is one more channel context left, populate
	 * rx_channel with the channel of that remaining channel context.
	 */
	ar->rx_channel = NULL;
	spin_unlock_bh(&ar->data_lock);

	mutex_unlock(&ar->conf_mutex);
}

static inline int ath11k_mac_vdev_setup_sync(struct ath11k *ar)
{
	lockdep_assert_held(&ar->conf_mutex);

	if (test_bit(ATH11K_FLAG_CRASH_FLUSH, &ar->ab->dev_flags))
		return -ESHUTDOWN;

	if (!wait_for_completion_timeout(&ar->vdev_setup_done,
					 ATH11K_VDEV_SETUP_TIMEOUT_HZ))
		return -ETIMEDOUT;

	return ar->last_wmi_vdev_start_status ? -EINVAL : 0;
}

static int
ath11k_mac_vdev_start_restart(struct ath11k_vif *arvif,
			      const struct ieee80211_chan_def *chandef,
			      bool restart)
{
	struct ath11k *ar = arvif->ar;
	struct ath11k_base *ab = ar->ab;
	struct wmi_vdev_start_req_arg arg = { 0 };
	bool he_support = ieee80211_vif_bss_conf_get_he_support(arvif->vif);
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_done);

	arg.vdev_id = arvif->vdev_id;
	arg.dtim_period = arvif->dtim_period;
	arg.bcn_intval = arvif->beacon_interval;

	arg.channel.freq = chandef->chan->center_freq;
	arg.channel.band_center_freq1 = chandef->center_freq1;
	arg.channel.band_center_freq2 = chandef->center_freq2;

	if (chandef->chan->band >= NUM_NL80211_BANDS || chandef->width >= ATH11K_CHAN_WIDTH_NUM) {
		ath11k_warn(ar->ab, "Invalid chandef, band = %d, width = %d\n",
					    chandef->chan->band, chandef->width);
		return 0;
	}
	arg.channel.mode =
		ath11k_phymodes[chandef->chan->band][chandef->width];

	arg.channel.min_power = 0;
	arg.channel.max_power = chandef->chan->max_power;
	arg.channel.max_reg_power = chandef->chan->max_reg_power;
	arg.channel.max_antenna_gain = chandef->chan->max_antenna_gain;

	arg.pref_tx_streams = ar->num_tx_chains;
	arg.pref_rx_streams = ar->num_rx_chains;

	if (arvif->vdev_type == WMI_VDEV_TYPE_AP) {
		arg.ssid = arvif->u.ap.ssid;
		arg.ssid_len = arvif->u.ap.ssid_len;
		arg.hidden_ssid = arvif->u.ap.hidden_ssid;

		/* For now allow DFS for AP mode */
		arg.channel.chan_radar =
			!!(chandef->chan->flags & IEEE80211_CHAN_RADAR);

		arg.channel.passive = arg.channel.chan_radar;

		spin_lock_bh(&ab->base_lock);
		arg.regdomain = ar->ab->dfs_region;
		spin_unlock_bh(&ab->base_lock);

		/* TODO: Notify if secondary 80Mhz also needs radar detection */
		if (he_support) {
			ret = ath11k_set_he_mu_sounding_mode(ar, arvif);
			if (ret) {
				ath11k_warn(ar->ab, "failed to set he mode vdev %d\n",
					    arg.vdev_id);
				return ret;
			}
		}
	}

	arg.channel.passive |= !!(chandef->chan->flags & IEEE80211_CHAN_NO_IR);

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac vdev %d start center_freq %d phymode %a\n",
		   arg.vdev_id, arg.channel.freq,
		   ath11k_wmi_phymode_str(arg.channel.mode));

	ret = ath11k_wmi_vdev_start(ar, &arg, restart);
	if (ret) {
		ath11k_warn(ar->ab, "failed to %a WMI vdev %d\n",
			    restart ? "restart" : "start", arg.vdev_id);
		return ret;
	}

	ret = ath11k_mac_vdev_setup_sync(ar);
	if (ret) {
		ath11k_warn(ab, "failed to synchronize setup for vdev %d %a: %d\n",
			    arg.vdev_id, restart ? "restart" : "start", ret);
		return ret;
	}

	ar->num_started_vdevs++;

#if ATH11K_UNUSED
	/* Enable CAC Flag in the driver by checking the channel DFS cac time,
	 * i.e dfs_cac_ms value which will be valid only for radar channels
	 * and state as NL80211_DFS_USABLE which indicates CAC needs to be
	 * done before channel usage. This flags is used to drop rx packets.
	 * during CAC.
	 */
	/* TODO Set the flag for other interface types as required */
	if (arvif->vdev_type == WMI_VDEV_TYPE_AP &&
	    chandef->chan->dfs_cac_ms &&
	    chandef->chan->dfs_state == NL80211_DFS_USABLE) {
		set_bit(ATH11K_CAC_RUNNING, &ar->dev_flags);
		ath11k_dbg(ab, ATH11K_DBG_MAC,
			   "CAC Started in chan_freq %d for vdev %d\n",
			   arg.channel.freq, arg.vdev_id);
	}
#endif // !ATH11K_UNUSED

	ret = ath11k_mac_set_txbf_conf(arvif);
	if (ret)
		ath11k_warn(ab, "failed to set txbf conf for vdev %d: %d\n",
			    arvif->vdev_id, ret);

	return 0;
}

static int ath11k_mac_vdev_stop(struct ath11k_vif *arvif)
{
	struct ath11k *ar = arvif->ar;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_done);

	spin_lock_bh(&ar->data_lock);

	ar->vdev_stop_status.stop_in_progress = true;
	ar->vdev_stop_status.vdev_id = arvif->vdev_id;

	spin_unlock_bh(&ar->data_lock);

	ret = ath11k_wmi_vdev_stop(ar, arvif->vdev_id);
	if (ret) {
		ath11k_warn(ar->ab, "failed to stop WMI vdev %d: %d\n",
			    arvif->vdev_id, ret);
		goto err;
	}

	ret = ath11k_mac_vdev_setup_sync(ar);
	if (ret) {
		ath11k_warn(ar->ab, "failed to synchronize setup for vdev %d: %d\n",
			    arvif->vdev_id, ret);
		goto err;
	}

	WARN_ON(ar->num_started_vdevs == 0);

	ar->num_started_vdevs--;

	if (test_bit(ATH11K_CAC_RUNNING, &ar->dev_flags)) {
		clear_bit(ATH11K_CAC_RUNNING, &ar->dev_flags);
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "CAC Stopped for vdev %d\n",
			   arvif->vdev_id);
	}

	return 0;
err:
	spin_lock_bh(&ar->data_lock);
	ar->vdev_stop_status.stop_in_progress = false;
	spin_unlock_bh(&ar->data_lock);

	return ret;
}

static int ath11k_mac_vdev_start(struct ath11k_vif *arvif,
				 const struct ieee80211_chan_def *chandef)
{
	return ath11k_mac_vdev_start_restart(arvif, chandef, false);
}

static int ath11k_mac_vdev_restart(struct ath11k_vif *arvif,
				   const struct ieee80211_chan_def *chandef)
{
	return ath11k_mac_vdev_start_restart(arvif, chandef, true);
}

struct ath11k_mac_change_chanctx_arg {
	struct ieee80211_chanctx_conf *ctx;
	struct ieee80211_vif_chanctx_switch *vifs;
	int n_vifs;
	int next_vif;
};

static void
ath11k_mac_change_chanctx_cnt_iter(void *data, const u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct ath11k_mac_change_chanctx_arg *arg = data;

	if (ieee80211_vif_get_chanctx_conf(vif) != arg->ctx)
		return;

	arg->n_vifs++;
}

static void
ath11k_mac_change_chanctx_fill_iter(void *data, const u8 *mac,
				    struct ieee80211_vif *vif)
{
	struct ath11k_mac_change_chanctx_arg *arg = data;
	struct ieee80211_chanctx_conf *ctx;

	ctx = ieee80211_vif_get_chanctx_conf(vif);
	if (ctx != arg->ctx)
		return;

	if (WARN_ON(arg->next_vif == arg->n_vifs))
		return;

	arg->vifs[arg->next_vif].vif = vif;
	arg->vifs[arg->next_vif].old_ctx = ctx;
	arg->vifs[arg->next_vif].new_ctx = ctx;
	arg->next_vif++;
}

static void
ath11k_mac_update_vif_chan(struct ath11k *ar,
			   struct ieee80211_vif_chanctx_switch *vifs,
			   int n_vifs)
{
	struct ath11k_base *ab = ar->ab;
	struct ath11k_vif *arvif;
	int ret;
	int i;

	lockdep_assert_held(&ar->conf_mutex);

	/* All relevant vdevs are downed and associated channel resources
	 * should be available for the channel switch now.
	 */

	/* TODO: Update ar->rx_channel */

	for (i = 0; i < n_vifs; i++) {
		arvif = ieee80211_vif_get_priv_data(vifs[i].vif);

		ath11k_dbg(ab, ATH11K_DBG_MAC,
			   "mac chanctx switch vdev_id %d freq %hu->%hu width %d->%d\n",
			   arvif->vdev_id,
			   vifs[i].old_ctx->def.chan->center_freq,
			   vifs[i].new_ctx->def.chan->center_freq,
			   vifs[i].old_ctx->def.width,
			   vifs[i].new_ctx->def.width);

		if (WARN_ON(!arvif->is_started))
			continue;

		if (WARN_ON(!arvif->is_up))
			continue;

#if 0 // TODOTODO: SAP or P2PGO
		ret = ath11k_mac_setup_bcn_tmpl(arvif);
		if (ret)
			ath11k_warn(ab, "failed to update bcn tmpl during csa: %d\n",
				    ret);
#endif

		ret = ath11k_mac_vdev_restart(arvif, &vifs[i].new_ctx->def);
		if (ret) {
			ath11k_warn(ab, "failed to restart vdev %d: %d\n",
				    arvif->vdev_id, ret);
			continue;
		}

		ret = ath11k_wmi_vdev_up(arvif->ar, arvif->vdev_id, arvif->aid,
					 arvif->bssid);
		if (ret) {
			ath11k_warn(ab, "failed to bring vdev up %d: %d\n",
				    arvif->vdev_id, ret);
			continue;
		}
	}
}

static void
ath11k_mac_update_active_vif_chan(struct ath11k *ar,
				  struct ieee80211_chanctx_conf *ctx)
{
	struct ath11k_mac_change_chanctx_arg arg = { 0 };

    arg.ctx = ctx;

	lockdep_assert_held(&ar->conf_mutex);

	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   IEEE80211_VIF_ITER_NORMAL,
						   ath11k_mac_change_chanctx_cnt_iter,
						   &arg);
	if (arg.n_vifs == 0)
		return;

	arg.vifs = kcalloc(arg.n_vifs, sizeof(arg.vifs[0]), GFP_KERNEL);
	if (!arg.vifs)
		return;

	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   IEEE80211_VIF_ITER_NORMAL,
						   ath11k_mac_change_chanctx_fill_iter,
						   &arg);

	ath11k_mac_update_vif_chan(ar, arg.vifs, arg.n_vifs);

	kfree(arg.vifs);
}

static void ath11k_mac_op_change_chanctx(struct ieee80211_hw *hw,
					 struct ieee80211_chanctx_conf *ctx,
					 u32 changed)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx change freq %u width %d ptr %pK changed %x\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx, changed);

	/* This shouldn't really happen because channel switching should use
	 * switch_vif_chanctx().
	 */
	if (WARN_ON(changed & IEEE80211_CHANCTX_CHANGE_CHANNEL))
		goto unlock;

	if (changed & IEEE80211_CHANCTX_CHANGE_WIDTH)
		ath11k_mac_update_active_vif_chan(ar, ctx);

	/* TODO: Recalc radar detection */

unlock:
	mutex_unlock(&ar->conf_mutex);
}

static int
ath11k_start_vdev_delay(struct ieee80211_hw *hw,
			struct ieee80211_vif *vif)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;

	if (WARN_ON(arvif->is_started)) {
		mutex_unlock(&ar->conf_mutex);
		return -EBUSY;
	}

	ret = ath11k_mac_vdev_start(arvif, &arvif->chanctx.def);
	if (ret) {
		ath11k_warn(ab, "failed to start vdev %d addr %pM on freq %d: %d\n",
			    arvif->vdev_id, ieee80211_vif_addr(vif),
			    arvif->chanctx.def.chan->center_freq, ret);
		goto err;
	}
	if (arvif->vdev_type == WMI_VDEV_TYPE_MONITOR) {
		ret = ath11k_monitor_vdev_up(ar, arvif->vdev_id);
		if (ret)
			goto err;
	}

	arvif->is_started = true;
    ath11k_info(ab, "vdev %d: is_started %d\n",
        arvif->vdev_id, arvif->is_started);

	/* TODO: Setup ps and cts/rts protection */
	return 0;

err:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static int
ath11k_mac_op_assign_vif_chanctx(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_chanctx_conf *ctx)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;
	struct peer_create_params param;

	mutex_lock(&ar->conf_mutex);

	// For QCA6390, bss peer must be created before vdev_start.
	if (ab->hw_params.vdev_start_delay &&
	    arvif->vdev_type != WMI_VDEV_TYPE_MONITOR) {
		memcpy(&arvif->chanctx, ctx, sizeof(*ctx));
		mutex_unlock(&ar->conf_mutex);
		return 0;
	}

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx assign ptr %pK vdev_id %d\n",
		   ctx, arvif->vdev_id);

	if (WARN_ON(arvif->is_started)) {
		mutex_unlock(&ar->conf_mutex);
		return -EBUSY;
	}

	param.vdev_id = arvif->vdev_id;
	param.peer_type = WMI_PEER_TYPE_DEFAULT;
	param.peer_addr = ar->mac_addr;
	ret = ath11k_peer_create(ar, arvif, NULL, &param);

	ret = ath11k_mac_vdev_start(arvif, &ctx->def);
	if (ret) {
		ath11k_warn(ab, "failed to start vdev %d addr %pM on freq %d: %d\n",
			    arvif->vdev_id, ieee80211_vif_addr(vif),
			    ctx->def.chan->center_freq, ret);
		goto err;
	}
	if (arvif->vdev_type == WMI_VDEV_TYPE_MONITOR) {
		ret = ath11k_monitor_vdev_up(ar, arvif->vdev_id);
		if (ret)
			goto err;
	}

	arvif->is_started = true;
    ath11k_info(ab, "vdev %d: is_started %d\n",
        arvif->vdev_id, arvif->is_started);

	/* TODO: Setup ps and cts/rts protection */

	mutex_unlock(&ar->conf_mutex);

	return 0;

err:
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static void
ath11k_mac_op_unassign_vif_chanctx(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_chanctx_conf *ctx)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_base *ab = ar->ab;
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx unassign ptr %pK vdev_id %u\n",
		   ctx, arvif->vdev_id);

	WARN_ON(!arvif->is_started);

	if (ab->hw_params.vdev_start_delay &&
	    arvif->vdev_type == WMI_VDEV_TYPE_MONITOR &&
	    ath11k_peer_find_by_addr(ab, ar->mac_addr))
		ath11k_peer_delete(ar, arvif->vdev_id, ar->mac_addr);

	ret = ath11k_mac_vdev_stop(arvif);
	if (ret)
		ath11k_warn(ab, "failed to stop vdev %d: %d\n",
			    arvif->vdev_id, ret);

	arvif->is_started = false;
    ath11k_info(ab, "vdev %d: is_started %d\n",
        arvif->vdev_id, arvif->is_started);

    if (arvif->vdev_type == WMI_VDEV_TYPE_STA)
		ath11k_mac_11d_scan_start(ar, arvif->vdev_id, false);

	mutex_unlock(&ar->conf_mutex);
}

static int
ath11k_mac_op_switch_vif_chanctx(struct ieee80211_hw *hw,
				 struct ieee80211_vif_chanctx_switch *vifs,
				 int n_vifs,
				 enum ieee80211_chanctx_switch_mode mode)
{
	struct ath11k *ar = ieee80211_hw_to_priv_data(hw);

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
		   "mac chanctx switch n_vifs %d mode %d\n",
		   n_vifs, mode);
	ath11k_mac_update_vif_chan(ar, vifs, n_vifs);

	mutex_unlock(&ar->conf_mutex);

	return 0;
}

static int
ath11k_mac_set_country_code(struct ath11k *ar, u8 *ccode)
{
    int ret = 0;
	struct wmi_set_current_country_params param;

	if ( !ccode || ccode[0] == '\0' || ccode[1] == '\0') {
        return -EINVAL; 
	}

	param.alpha2[0] = ccode[0];
	param.alpha2[1] = ccode[1];

    ret = ath11k_wmi_send_set_current_country_cmd(ar, &param);
	return ret;
}

static int 
ath11k_mac_set_beacon_filter(struct ieee80211_hw *hw, struct ieee80211_vif *vif, const u32 *ies, u32 ies_cnt)
{
    struct ath11k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath11k_vif *arvif = ieee80211_vif_get_priv_data(vif);
    int ret = 0;

	ret = ath11k_wmi_set_beacon_filter(ar, arvif->vdev_id, ies, ies_cnt);
	return ret;
}

static int ath11k_mac_op_priv_command(struct ieee80211_hw *hw, 
    struct ieee80211_priv_cmd *cmd)
{
    struct ath11k *ar = ieee80211_hw_to_priv_data(hw);

    if (!cmd)
        return -EINVAL;

    switch (cmd->id) {
    case IEEE80211_PRIV_CMD_RDDM:
        return ath11k_hif_dump_target(ar->ab);
	case IEEE80211_PRIV_CMD_CCODE:
		if (cmd->len != 2)
			return -EINVAL;
		return ath11k_mac_set_country_code(ar, cmd->data);
    default:
        ath11k_warn(ar->ab, "priv command %d is not supported\n", cmd->id);
        break;
    }

    return -ENOPARAM;
}

static const struct ieee80211_ops ath11k_ops = {
	.ieee80211_tx				        = ath11k_mac_op_tx,
	.ieee80211_start                    = ath11k_mac_op_start,
	.ieee80211_stop                     = ath11k_mac_op_stop,
	//.ieee80211_reconfig_complete      = ath11k_mac_op_reconfig_complete,
	.ieee80211_add_interface            = ath11k_mac_op_add_interface,
	.ieee80211_remove_interface		    = ath11k_mac_op_remove_interface,
	.ieee80211_config                   = ath11k_mac_op_config,
	.ieee80211_bss_info_changed         = ath11k_mac_op_bss_info_changed,
	//.ieee80211_configure_filter	    = ath11k_mac_op_configure_filter,
	.ieee80211_hw_scan                  = ath11k_mac_op_hw_scan,
	.ieee80211_cancel_hw_scan           = ath11k_mac_op_cancel_hw_scan,
	.ieee80211_set_key                  = ath11k_mac_op_set_key,
	.ieee80211_set_default_unicast_key  = ath11k_mac_op_set_default_unicast_key,
	.ieee80211_sta_state                = ath11k_mac_op_sta_state,
	.ieee80211_sta_set_txpwr			= ath11k_mac_op_sta_set_txpwr,
	.ieee80211_sta_rc_update			= ath11k_mac_op_sta_rc_update,
	.ieee80211_conf_tx                  = ath11k_mac_op_conf_tx,
#if 0
	.ieee80211_set_antenna			    = ath11k_mac_op_set_antenna,
	.ieee80211_get_antenna			    = ath11k_mac_op_get_antenna,
#endif
	.ieee80211_ampdu_action			    = ath11k_mac_op_ampdu_action,
	.ieee80211_add_chanctx			    = ath11k_mac_op_add_chanctx,
	.ieee80211_remove_chanctx			= ath11k_mac_op_remove_chanctx,
	.ieee80211_change_chanctx			= ath11k_mac_op_change_chanctx,
	.ieee80211_assign_vif_chanctx		= ath11k_mac_op_assign_vif_chanctx,
	.ieee80211_unassign_vif_chanctx		= ath11k_mac_op_unassign_vif_chanctx,
	.ieee80211_switch_vif_chanctx		= ath11k_mac_op_switch_vif_chanctx,
#if 0
	.ieee80211_set_rts_threshold	    = ath11k_mac_op_set_rts_threshold,
	.ieee80211_set_frag_threshold		= ath11k_mac_op_set_frag_threshold,
	.ieee80211_set_bitrate_mask		    = ath11k_mac_op_set_bitrate_mask,
	.ieee80211_get_survey			    = ath11k_mac_op_get_survey,
	.ieee80211_flush				    = ath11k_mac_op_flush,
	.ieee80211_sta_statistics			= ath11k_mac_op_sta_statistics,
	CFG80211_TESTMODE_CMD(ath11k_tm_cmd)
#ifdef CONFIG_ATH11K_DEBUGFS
	.ieee80211_sta_add_debugfs		    = ath11k_sta_add_debugfs,
#endif
#endif
    .ieee80211_set_beacon_filter        = ath11k_mac_set_beacon_filter,
    .ieee80211_priv_command             = ath11k_mac_op_priv_command,
};

#if ATH11K_UNUSED

static const struct ieee80211_iface_limit ath11k_if_limits[] = {
	{
		.max = 1,
		.types = BIT(NL80211_IFTYPE_STATION),
	},
	{
		.max    = 16,
		.types  = BIT(NL80211_IFTYPE_AP)
#ifdef CONFIG_MAC80211_MESH
			| BIT(NL80211_IFTYPE_MESH_POINT)
#endif
	},
};

static const struct ieee80211_iface_combination ath11k_if_comb[] = {
	{
		.limits = ath11k_if_limits,
		.n_limits = ARRAY_SIZE(ath11k_if_limits),
		.max_interfaces = 16,
		.num_different_channels = 1,
		.beacon_int_infra_match = true,
		.beacon_int_min_gcd = 100,
		.radar_detect_widths =	BIT(NL80211_CHAN_WIDTH_20_NOHT) |
					BIT(NL80211_CHAN_WIDTH_20) |
					BIT(NL80211_CHAN_WIDTH_40) |
					BIT(NL80211_CHAN_WIDTH_80),
	},
};

#endif //!ATH11K_UNUSED

static void ath11k_mac_update_ch_list(struct ath11k *ar,
				      struct ieee80211_supported_band *band,
				      u32 freq_low, u32 freq_high)
{
	u32 i;

	if (!(freq_low && freq_high))
		return;

	for (i = 0; i < band->n_channels; i++) {
		if (band->channels[i].center_freq < freq_low ||
		    band->channels[i].center_freq > freq_high)
			band->channels[i].flags |= IEEE80211_CHAN_DISABLED;
	}
}

static u32 ath11k_get_phy_id(struct ath11k *ar, u32 band)
{
    struct ath11k_pdev *pdev = ar->pdev;
    struct ath11k_pdev_cap *pdev_cap = &pdev->cap;

    if (band == WMI_HOST_WLAN_2G_CAP)
        return pdev_cap->band[NL80211_BAND_2GHZ].phy_id;

    if (band == WMI_HOST_WLAN_5G_CAP)
        return pdev_cap->band[NL80211_BAND_5GHZ].phy_id;

    ath11k_warn(ar->ab, "unsupported phy cap:%d\n", band);

    return 0;
}

static int ath11k_mac_setup_channels_rates(struct ath11k *ar,
    u32 supported_bands)
{
    struct ieee80211_supported_band *band;
    struct ath11k_hal_reg_capabilities_ext *reg_cap, *temp_reg_cap;
    void *channels;
    u32 phy_id;

    BUILD_BUG_ON((ARRAY_SIZE(ath11k_2ghz_channels) +
		      ARRAY_SIZE(ath11k_5ghz_channels) +
		      ARRAY_SIZE(ath11k_6ghz_channels)) !=
		     ATH11K_NUM_CHANS);

    reg_cap = &ar->ab->hal_reg_cap[ar->pdev_idx];
	temp_reg_cap = reg_cap;

    if (supported_bands & WMI_HOST_WLAN_2G_CAP) {
        channels = kmemdup(ath11k_2ghz_channels,
            sizeof(ath11k_2ghz_channels),
            GFP_KERNEL);
        if (!channels)
            return -ENOMEM;

        band = &ar->mac.sbands[NL80211_BAND_2GHZ];
        band->band = NL80211_BAND_2GHZ;
        band->n_channels = ARRAY_SIZE(ath11k_2ghz_channels);
        band->channels = channels;
        band->n_bitrates = ath11k_g_rates_size;
        band->bitrates = ath11k_g_rates;
        ieee80211_hw_set_sband(ar->hw, NL80211_BAND_2GHZ, band);

		if (ar->ab->hw_params.single_pdev_only) {
			phy_id = ath11k_get_phy_id(ar, WMI_HOST_WLAN_2G_CAP);
			temp_reg_cap = &ar->ab->hal_reg_cap[phy_id];
		}
		ath11k_mac_update_ch_list(ar, band,
					  temp_reg_cap->low_2ghz_chan,
					  temp_reg_cap->high_2ghz_chan);
	}

	if (supported_bands & WMI_HOST_WLAN_5G_CAP) {
		if (reg_cap->high_5ghz_chan >= ATH11K_MAX_6G_FREQ && !cfg_is_ath_6G_disabled()) {
			channels = kmemdup(ath11k_6ghz_channels,
					   sizeof(ath11k_6ghz_channels), GFP_KERNEL);
			if (!channels) {
				kfree(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
				return -ENOMEM;
			}

			ar->supports_6ghz = true;
			band = &ar->mac.sbands[NL80211_BAND_6GHZ];
			band->band = NL80211_BAND_6GHZ;
			band->n_channels = ARRAY_SIZE(ath11k_6ghz_channels);
			band->channels = channels;
			band->n_bitrates = ath11k_a_rates_size;
			band->bitrates = ath11k_a_rates;
			ieee80211_hw_set_sband(ar->hw, NL80211_BAND_6GHZ, band);

			if (ar->ab->hw_params.single_pdev_only) {
				phy_id = ath11k_get_phy_id(ar, WMI_HOST_WLAN_5G_CAP);
				temp_reg_cap = &ar->ab->hal_reg_cap[phy_id];
			}

			ath11k_mac_update_ch_list(ar, band,
						  temp_reg_cap->low_5ghz_chan,
						  temp_reg_cap->high_5ghz_chan);
		}

		if (reg_cap->low_5ghz_chan < ATH11K_MIN_6G_FREQ) {
			channels = kmemdup(ath11k_5ghz_channels,
					   sizeof(ath11k_5ghz_channels),
					   GFP_KERNEL);
			if (!channels) {
				kfree(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
				kfree(ar->mac.sbands[NL80211_BAND_6GHZ].channels);
				return -ENOMEM;
			}

        band = &ar->mac.sbands[NL80211_BAND_5GHZ];
        band->band = NL80211_BAND_5GHZ;
        band->n_channels = ARRAY_SIZE(ath11k_5ghz_channels);
        band->channels = channels;
        band->n_bitrates = ath11k_a_rates_size;
        band->bitrates = ath11k_a_rates;
        ieee80211_hw_set_sband(ar->hw, NL80211_BAND_5GHZ, band);

		if (ar->ab->hw_params.single_pdev_only) {
			phy_id = ath11k_get_phy_id(ar, WMI_HOST_WLAN_5G_CAP);
			temp_reg_cap = &ar->ab->hal_reg_cap[phy_id];
		}

		ath11k_mac_update_ch_list(ar, band,
					  temp_reg_cap->low_5ghz_chan,
					  temp_reg_cap->high_5ghz_chan);
		}
	}

    return 0;
}

#if ATH11K_UNUSED
static const u8 ath11k_if_types_ext_capa[] = {
	[0] = WLAN_EXT_CAPA1_EXT_CHAN_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
};

static const u8 ath11k_if_types_ext_capa_sta[] = {
	[0] = WLAN_EXT_CAPA1_EXT_CHAN_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
	[9] = WLAN_EXT_CAPA10_TWT_REQUESTER_SUPPORT,
};

static const u8 ath11k_if_types_ext_capa_ap[] = {
	[0] = WLAN_EXT_CAPA1_EXT_CHAN_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
	[9] = WLAN_EXT_CAPA10_TWT_RESPONDER_SUPPORT,
};

static const struct wiphy_iftype_ext_capab ath11k_iftypes_ext_capa[] = {
	{
		.extended_capabilities = ath11k_if_types_ext_capa,
		.extended_capabilities_mask = ath11k_if_types_ext_capa,
		.extended_capabilities_len = sizeof(ath11k_if_types_ext_capa),
	}, {
		.iftype = NL80211_IFTYPE_STATION,
		.extended_capabilities = ath11k_if_types_ext_capa_sta,
		.extended_capabilities_mask = ath11k_if_types_ext_capa_sta,
		.extended_capabilities_len =
				sizeof(ath11k_if_types_ext_capa_sta),
	}, {
		.iftype = NL80211_IFTYPE_AP,
		.extended_capabilities = ath11k_if_types_ext_capa_ap,
		.extended_capabilities_mask = ath11k_if_types_ext_capa_ap,
		.extended_capabilities_len =
				sizeof(ath11k_if_types_ext_capa_ap),
	},
};

#endif // !ATH11K_UNUSED

static void __ath11k_mac_unregister(struct ath11k *ar)
{
	cancel_work_sync(&ar->regd_update_work);

	ieee80211_unregister_hw(ar->hw);

	idr_for_each(&ar->txmgmt_idr, ath11k_mac_tx_mgmt_pending_free, ar);
	idr_destroy(&ar->txmgmt_idr);

	kfree(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
	kfree(ar->mac.sbands[NL80211_BAND_5GHZ].channels);
	kfree(ar->mac.sbands[NL80211_BAND_6GHZ].channels);

	ieee80211_set_dev(ar->hw, NULL);
}

void ath11k_mac_unregister(struct ath11k_base *ab)
{
	struct ath11k *ar;
	struct ath11k_pdev *pdev;
	int i;

	for (i = 0; i < (int)ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		if (!ar)
			continue;

		__ath11k_mac_unregister(ar);
	}
}

static int __ath11k_mac_register(struct ath11k *ar)
{
	struct ath11k_base *ab = ar->ab;
	struct ath11k_pdev_cap *cap = &ar->pdev->cap;
	static const u32 cipher_suites[] = {
		WLAN_RSN_CIPHER_SUITE_WEP40,
		WLAN_RSN_CIPHER_SUITE_WEP104,
		WLAN_RSN_CIPHER_SUITE_TKIP,
		WLAN_RSN_CIPHER_SUITE_CCMP,
		WLAN_RSN_CIPHER_SUITE_AES_CMAC,
		WLAN_RSN_CIPHER_SUITE_BIP_CMAC_256,
		WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128,
		WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256,
		WLAN_RSN_CIPHER_SUITE_GCMP,
		WLAN_RSN_CIPHER_SUITE_GCMP_256,
		WLAN_RSN_CIPHER_SUITE_CCMP_256,
	};
	int ret;
	u32 ht_cap = 0;

	ath11k_pdev_caps_update(ar);

	ieee80211_set_perm_addr(ar->hw, ar->mac_addr);

	ieee80211_set_dev(ar->hw, ab->dev);

	if (ab->hw_params.band_2g_fake)
		cap->supported_bands = WMI_HOST_WLAN_2G_CAP | WMI_HOST_WLAN_5G_CAP;

	ret = ath11k_mac_setup_channels_rates(ar,
					      cap->supported_bands);
	if (ret)
		goto err_free;

	ath11k_mac_setup_ht_vht_cap(ar, cap, &ht_cap);
	ath11k_mac_setup_he_cap(ar, cap);

    ieee80211_hw_set_available_chains(ar->hw, 
        (u8)cap->rx_chain_mask, (u8)cap->tx_chain_mask);

#if ATH11K_UNUSED
	ar->hw->wiphy->available_antennas_rx = cap->rx_chain_mask;
	ar->hw->wiphy->available_antennas_tx = cap->tx_chain_mask;

	ar->hw->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
					 BIT(NL80211_IFTYPE_AP) |
					 BIT(NL80211_IFTYPE_MESH_POINT);
#endif
	ieee80211_hw_set(ar->hw, SIGNAL_DBM);
	ieee80211_hw_set(ar->hw, SUPPORTS_PS);
	ieee80211_hw_set(ar->hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(ar->hw, MFP_CAPABLE);
	ieee80211_hw_set(ar->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(ar->hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(ar->hw, AP_LINK_PS);
	ieee80211_hw_set(ar->hw, SPECTRUM_MGMT);
	ieee80211_hw_set(ar->hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(ar->hw, CONNECTION_MONITOR);
	ieee80211_hw_set(ar->hw, SUPPORTS_PER_STA_GTK);
	ieee80211_hw_set(ar->hw, WANT_MONITOR_VIF);
	ieee80211_hw_set(ar->hw, CHANCTX_STA_CSA);
	ieee80211_hw_set(ar->hw, QUEUE_CONTROL);
	ieee80211_hw_set(ar->hw, SUPPORTS_TX_FRAG);
	ieee80211_hw_set(ar->hw, REPORTS_LOW_ACK);
	ieee80211_hw_set(ar->hw, SINGLE_SCAN_ON_ALL_BANDS);
	if (ht_cap & WMI_HT_CAP_ENABLED || ar->supports_6ghz) {
		ieee80211_hw_set(ar->hw, AMPDU_AGGREGATION);
		ieee80211_hw_set(ar->hw, TX_AMPDU_SETUP_IN_HW);
		ieee80211_hw_set(ar->hw, SUPPORTS_REORDERING_BUFFER);
		ieee80211_hw_set(ar->hw, SUPPORTS_AMSDU_IN_AMPDU);
	}
#if ATH11K_UNUSED
	ar->hw->wiphy->features |= NL80211_FEATURE_STATIC_SMPS;
	ar->hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	/* TODO: Check if HT capability advertised from firmware is different
	 * for each band for a dual band capable radio. It will be tricky to
	 * handle it when the ht capability different for each band.
	 */
	if (ht_cap & WMI_HT_CAP_DYNAMIC_SMPS || ar->supports_6ghz)
		ar->hw->wiphy->features |= NL80211_FEATURE_DYNAMIC_SMPS;
#endif // !ATH11K_UNUSED

    ieee80211_hw_set_max_scan_ssids(ar->hw, WLAN_SCAN_PARAMS_MAX_SSID);
    ieee80211_hw_set_max_scan_ie_len(ar->hw, WLAN_SCAN_PARAMS_MAX_IE_LEN);
    ieee80211_hw_set_max_listen_interval(ar->hw, ATH11K_MAX_HW_LISTEN_INTERVAL);
    ieee80211_hw_set_max_rx_aggregation_subframes(ar->hw, IEEE80211_AMPDU_MAX_BUF);

#if ATH11K_UNUSED
	ar->hw->wiphy->max_scan_ssids = WLAN_SCAN_PARAMS_MAX_SSID;
	ar->hw->wiphy->max_scan_ie_len = WLAN_SCAN_PARAMS_MAX_IE_LEN;

	ar->hw->max_listen_interval = ATH11K_MAX_HW_LISTEN_INTERVAL;

	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;
	ar->hw->wiphy->max_remain_on_channel_duration = 5000;

	ar->hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;
	ar->hw->wiphy->features |= NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE |
				   NL80211_FEATURE_AP_SCAN;
#endif // !ATH11K_UNUSED

	ar->max_num_stations = TARGET_NUM_STATIONS;
	ar->max_num_peers = TARGET_NUM_PEERS_PDEV;
#if ATH11K_UNUSED
	ar->hw->wiphy->max_ap_assoc_sta = (u16)ar->max_num_stations;

	ar->hw->queues = ATH11K_HW_MAX_QUEUES;
	ar->hw->offchannel_tx_hw_queue = ATH11K_HW_MAX_QUEUES - 1;
	ar->hw->max_rx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF;

	ar->hw->vif_data_size = sizeof(struct ath11k_vif);
	ar->hw->sta_data_size = sizeof(struct ath11k_sta);

#endif // !ATH11K_UNUSED
    ieee80211_hw_set_queues(ar->hw, ATH11K_HW_MAX_QUEUES);

    ieee80211_hw_set_vif_data_size(ar->hw, sizeof(struct ath11k_vif));
    ieee80211_hw_set_sta_data_size(ar->hw, sizeof(struct ath11k_sta));

    ieee80211_hw_set_supported_cipher_suites(
        ar->hw, cipher_suites, ARRAY_SIZE(cipher_suites));

#if ATH11K_UNUSED
	ar->hw->wiphy->iface_combinations = ath11k_if_comb;
	ar->hw->wiphy->n_iface_combinations = ARRAY_SIZE(ath11k_if_comb);

	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_STA_TX_PWR);

	ar->hw->wiphy->cipher_suites = cipher_suites;
	ar->hw->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

#endif //!ATH11K_UNUSED

	ath11k_reg_init(ar);

	/* advertise HW checksum offload capabilities */
	//ar->hw->netdev_features = NETIF_F_HW_CSUM;

	ret = ieee80211_register_hw(ar->hw);
	if (ret) {
		ath11k_err(ar->ab, "ieee80211 registration failed: %d\n", ret);
		goto err_free;
	}

	/* Apply the regd received during initialization */
	ret = ath11k_regd_update(ar, true);
	if (ret) {
		ath11k_err(ar->ab, "ath11k regd update failed: %d\n", ret);
		goto err_free;
	}

	ret = ath11k_debug_register(ar);
	if (ret) {
		ath11k_err(ar->ab, "debugfs registration failed: %d\n", ret);
		goto err_free;
	}

	return 0;

err_free:
	kfree(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
	kfree(ar->mac.sbands[NL80211_BAND_5GHZ].channels);
	kfree(ar->mac.sbands[NL80211_BAND_6GHZ].channels);

	ieee80211_set_dev(ar->hw, NULL);
	return ret;
}

int ath11k_mac_register(struct ath11k_base *ab)
{
	struct ath11k *ar;
	struct ath11k_pdev *pdev;
	int i;
	int ret;

	if (test_bit(ATH11K_FLAG_REGISTERED, &ab->dev_flags))
		return 0;

	for (i = 0; i < (int)ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		if (ab->pdevs_macaddr_valid) {
			ether_addr_copy(ar->mac_addr, pdev->mac_addr);
		} else {
			ether_addr_copy(ar->mac_addr, ab->mac_addr);
			ar->mac_addr[4] += (u8)i;
		}

		ret = __ath11k_mac_register(ar);
		if (ret)
			goto err_cleanup;

		idr_init(&ar->txmgmt_idr);
		spin_lock_init(&ar->txmgmt_idr_lock);
	}

	/* Initialize channel counters frequency value in hertz */
	ab->cc_freq_hz = IPQ8074_CC_FREQ_HERTZ;
	ab->free_vdev_map = (1LL << (ab->num_radios * TARGET_NUM_VDEVS)) - 1;

	return 0;

err_cleanup:
	for (i = i - 1; i >= 0; i--) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		__ath11k_mac_unregister(ar);
	}

	return ret;
}

int ath11k_mac_allocate(struct ath11k_base *ab)
{
	struct ieee80211_hw *hw;
	struct ath11k *ar;
	struct ath11k_pdev *pdev;
	int ret;
	int i;

	if (test_bit(ATH11K_FLAG_REGISTERED, &ab->dev_flags))
		return 0;

    ath11k_info(ab, "prepare the struct ieee80211_hw\n");

	for (i = 0; i < (int)ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		hw = ieee80211_alloc_hw(sizeof(struct ath11k), &ath11k_ops);
		if (!hw) {
			ath11k_warn(ab, "failed to allocate mac80211 hw device\n");
			ret = -ENOMEM;
			goto err_free_mac;
		}

		ar = ieee80211_hw_to_priv_data(hw);
		ar->hw = hw;
		ar->ab = ab;
		ar->pdev = pdev;
		ar->pdev_idx = (u8)i;
		ar->lmac_id = ath11k_core_get_hw_mac_id(ab, i);

		ar->ops = &ath11k_ops;

		ar->wmi = &ab->wmi_ab.wmi[i];
		/* FIXME wmi[0] is already initialized during attach,
		 * Should we do this again?
		 */
		ath11k_wmi_pdev_attach(ab, (u8)i);

		ar->cfg_tx_chainmask = (u8)pdev->cap.tx_chain_mask;
		ar->cfg_rx_chainmask = (u8)pdev->cap.rx_chain_mask;
		ar->num_tx_chains = get_num_chains(pdev->cap.tx_chain_mask);
		ar->num_rx_chains = get_num_chains(pdev->cap.rx_chain_mask);

		pdev->ar = ar;
		spin_lock_init(&ar->data_lock);
		list_init_head(&ar->arvifs);
		list_init_head(&ar->ppdu_stats_info);
		mutex_init(&ar->conf_mutex);
		init_completion(&ar->vdev_setup_done);
		init_completion(&ar->peer_assoc_done);
		init_completion(&ar->install_key_done);
		init_completion(&ar->bss_survey_done);
		init_completion(&ar->scan.started);
		init_completion(&ar->scan.completed);
		init_delayed_work(&ar->scan.timeout, ath11k_scan_timeout_work, ar);
		init_work(&ar->regd_update_work, ath11k_regd_update_work, ar);

		init_work(&ar->wmi_mgmt_tx_work, ath11k_mgmt_over_wmi_tx_work, ar);
		skb_queue_head_init(&ar->wmi_mgmt_tx_queue);
		clear_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
		ar->vdev_id_11d_scan = ATH11K_11D_INV_VDEV_ID;
		init_completion(&ar->finish_11d_scan);
		init_completion(&ar->finish_11d_ch_list);
	}

	return 0;

err_free_mac:
	ath11k_mac_destroy(ab);

	return ret;
}

void ath11k_mac_destroy(struct ath11k_base *ab)
{
	struct ath11k *ar;
	struct ath11k_pdev *pdev;
	int i;

	for (i = 0; i < (int)ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		if (!ar)
			continue;

		ieee80211_free_hw(ar->hw);
		pdev->ar = NULL;
	}
}

