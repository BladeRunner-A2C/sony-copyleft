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

#include <net/mac80211.h>
#include <net/net80211.h>
#include <qdf/dpp.h>

#include "mac.h"
#include "core.h"
#include "debug.h"
#include "wmi.h"
#include "hw.h"
#include "dp_tx.h"
#include "dp_rx.h"
#include "peer.h"
#include "hif.h"

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

static const struct ieee80211_channel ath12k_2ghz_channels[] = {
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

static const struct ieee80211_channel ath12k_5ghz_channels[] = {
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
	CHAN5G(177, 5885, 0)
};

static const struct ieee80211_channel ath12k_6ghz_channels[] = {
	CHAN6G(1, 5955, 0),
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
	
	/* new addition in IEEE Std 802.11ax-2021 */
	CHAN6G(2, 5935, 0),
};

static struct ieee80211_rate ath12k_legacy_rates[] = {
	{ .bitrate = 10,
	  .hw_value = ATH12K_HW_RATE_CCK_LP_1M },
	{ .bitrate = 20,
	  .hw_value = ATH12K_HW_RATE_CCK_LP_2M,
	  .hw_value_short = ATH12K_HW_RATE_CCK_SP_2M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE },
	{ .bitrate = 55,
	  .hw_value = ATH12K_HW_RATE_CCK_LP_5_5M,
	  .hw_value_short = ATH12K_HW_RATE_CCK_SP_5_5M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE },
	{ .bitrate = 110,
	  .hw_value = ATH12K_HW_RATE_CCK_LP_11M,
	  .hw_value_short = ATH12K_HW_RATE_CCK_SP_11M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE },

	{ .bitrate = 60, .hw_value = ATH12K_HW_RATE_OFDM_6M },
	{ .bitrate = 90, .hw_value = ATH12K_HW_RATE_OFDM_9M },
	{ .bitrate = 120, .hw_value = ATH12K_HW_RATE_OFDM_12M },
	{ .bitrate = 180, .hw_value = ATH12K_HW_RATE_OFDM_18M },
	{ .bitrate = 240, .hw_value = ATH12K_HW_RATE_OFDM_24M },
	{ .bitrate = 360, .hw_value = ATH12K_HW_RATE_OFDM_36M },
	{ .bitrate = 480, .hw_value = ATH12K_HW_RATE_OFDM_48M },
	{ .bitrate = 540, .hw_value = ATH12K_HW_RATE_OFDM_54M },
};

static const int
ath12k_phymodes[NUM_NL80211_BANDS][ATH12K_CHAN_WIDTH_NUM] = {
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

const struct htt_rx_ring_tlv_filter ath12k_mac_mon_status_filter_default = {
	.rx_filter = HTT_RX_FILTER_TLV_FLAGS_MPDU_START |
		     HTT_RX_FILTER_TLV_FLAGS_PPDU_END |
		     HTT_RX_FILTER_TLV_FLAGS_PPDU_END_STATUS_DONE,
	.pkt_filter_flags0 = HTT_RX_FP_MGMT_FILTER_FLAGS0,
	.pkt_filter_flags1 = HTT_RX_FP_MGMT_FILTER_FLAGS1,
	.pkt_filter_flags2 = HTT_RX_FP_CTRL_FILTER_FLASG2,
	.pkt_filter_flags3 = HTT_RX_FP_DATA_FILTER_FLASG3 |
			     HTT_RX_FP_CTRL_FILTER_FLASG3
};

#define ATH12K_MAC_FIRST_OFDM_RATE_IDX 4
#define ath12k_g_rates ath12k_legacy_rates
#define ath12k_g_rates_size (ARRAY_SIZE(ath12k_legacy_rates))
#define ath12k_a_rates (ath12k_legacy_rates + 4)
#define ath12k_a_rates_size (ARRAY_SIZE(ath12k_legacy_rates) - 4)

#define ATH12K_MAC_SCAN_TIMEOUT_MSECS 200 /* in msecs */

static const u32 ath12k_smps_map[] = {
	[WLAN_HTCAP_SM_PS_STATIC] = WMI_PEER_SMPS_STATIC,
	[WLAN_HTCAP_SM_PS_DYNAMIC] = WMI_PEER_SMPS_DYNAMIC,
	[WLAN_HTCAP_SM_PS_INVALID] = WMI_PEER_SMPS_PS_NONE,
	[WLAN_HTCAP_SM_PS_DISABLED] = WMI_PEER_SMPS_PS_NONE,
};

static int ath12k_start_vdev_delay(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif);

static const char *ath12k_mac_phymode_str(enum wmi_phy_mode mode)
{
	switch (mode) {
	case MODE_11A:
		return "11a";
	case MODE_11G:
		return "11g";
	case MODE_11B:
		return "11b";
	case MODE_11GONLY:
		return "11gonly";
	case MODE_11NA_HT20:
		return "11na-ht20";
	case MODE_11NG_HT20:
		return "11ng-ht20";
	case MODE_11NA_HT40:
		return "11na-ht40";
	case MODE_11NG_HT40:
		return "11ng-ht40";
	case MODE_11AC_VHT20:
		return "11ac-vht20";
	case MODE_11AC_VHT40:
		return "11ac-vht40";
	case MODE_11AC_VHT80:
		return "11ac-vht80";
	case MODE_11AC_VHT160:
		return "11ac-vht160";
	case MODE_11AC_VHT80_80:
		return "11ac-vht80+80";
	case MODE_11AC_VHT20_2G:
		return "11ac-vht20-2g";
	case MODE_11AC_VHT40_2G:
		return "11ac-vht40-2g";
	case MODE_11AC_VHT80_2G:
		return "11ac-vht80-2g";
	case MODE_11AX_HE20:
		return "11ax-he20";
	case MODE_11AX_HE40:
		return "11ax-he40";
	case MODE_11AX_HE80:
		return "11ax-he80";
	case MODE_11AX_HE80_80:
		return "11ax-he80+80";
	case MODE_11AX_HE160:
		return "11ax-he160";
	case MODE_11AX_HE20_2G:
		return "11ax-he20-2g";
	case MODE_11AX_HE40_2G:
		return "11ax-he40-2g";
	case MODE_11AX_HE80_2G:
		return "11ax-he80-2g";
	case MODE_UNKNOWN:
		/* skip */
		break;

		/* no default handler to allow compiler to check that the
		 * enum is fully handled
		 */
	}

	return "<unknown>";
}

u8 ath12k_mac_bw_to_mac80211_bw(u8 bw)
{
	u8 ret = 0;

	switch (bw) {
	case ATH12K_BW_20:
		ret = IEEE80211_RATE_INFO_BW_20;
		break;
	case ATH12K_BW_40:
		ret = IEEE80211_RATE_INFO_BW_40;
		break;
	case ATH12K_BW_80:
		ret = IEEE80211_RATE_INFO_BW_80;
		break;
	case ATH12K_BW_160:
		ret = IEEE80211_RATE_INFO_BW_160;
		break;
	}

	return ret;
}

enum ath12k_supported_bw ath12k_mac_mac80211_bw_to_ath12k_bw(u8 bw)
{
	switch (bw) {
	case IEEE80211_RATE_INFO_BW_20:
		return ATH12K_BW_20;
	case IEEE80211_RATE_INFO_BW_40:
		return ATH12K_BW_40;
	case IEEE80211_RATE_INFO_BW_80:
		return ATH12K_BW_80;
	case IEEE80211_RATE_INFO_BW_160:
		return ATH12K_BW_160;
	default:
		return ATH12K_BW_20;
	}
}

int ath12k_mac_hw_ratecode_to_legacy_rate(u8 hw_rc, u8 preamble, u8 *rateidx,
					  u16 *rate)
{
	/* As default, it is OFDM rates */
	u8 i = ATH12K_MAC_FIRST_OFDM_RATE_IDX;
	u8 max_rates_idx = ath12k_g_rates_size;

	if (preamble == WMI_RATE_PREAMBLE_CCK) {
		hw_rc &= ~ATH12K_HW_RATECODE_CCK_SHORT_PREAM_MASK;
		i = 0;
		max_rates_idx = ATH12K_MAC_FIRST_OFDM_RATE_IDX;
	}

	while (i < max_rates_idx) {
		if (hw_rc == ath12k_legacy_rates[i].hw_value) {
			*rateidx = i;
			*rate = ath12k_legacy_rates[i].bitrate;
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

u8 ath12k_mac_bitrate_to_idx(const struct ieee80211_supported_band *sband,
			     u32 bitrate)
{
	u8 i;

	for (i = 0; i < (u8)sband->n_bitrates; i++)
		if (sband->bitrates[i].bitrate == bitrate)
			return i;

	return 0;
}

static u32
ath12k_mac_max_ht_nss(const u8 ht_mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
{
	int nss;

	for (nss = IEEE80211_HT_MCS_MASK_LEN - 1; nss >= 0; nss--)
		if (ht_mcs_mask[nss])
			return nss + 1;

	return 1;
}

static u32
ath12k_mac_max_vht_nss(const u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
{
	int nss;

	for (nss = NL80211_VHT_NSS_MAX - 1; nss >= 0; nss--)
		if (vht_mcs_mask[nss])
			return nss + 1;

	return 1;
}

static u8 ath12k_parse_mpdudensity(u8 mpdudensity)
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

static int ath12k_mac_vif_chan(struct ieee80211_vif *vif,
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

static bool ath12k_mac_bitrate_is_cck(int bitrate)
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

u8 ath12k_mac_hw_rate_to_idx(const struct ieee80211_supported_band *sband,
			     u8 hw_rate, bool cck)
{
	const struct ieee80211_rate *rate;
	u8 i;

	for (i = 0; i < (u8)sband->n_bitrates; i++) {
		rate = &sband->bitrates[i];

		if (ath12k_mac_bitrate_is_cck(rate->bitrate) != cck)
			continue;

		if (rate->hw_value == hw_rate)
			return i;
		else if (rate->flags & IEEE80211_RATE_SHORT_PREAMBLE &&
			 rate->hw_value_short == hw_rate)
			return i;
	}

	return 0;
}

static u8 ath12k_mac_bitrate_to_rate(int bitrate)
{
	return (u8)(DIV_ROUND_UP(bitrate, 5) |
		(ath12k_mac_bitrate_is_cck(bitrate) ? BIT(7) : 0));
}

static void ath12k_get_arvif_iter(void *data, const u8 *mac,
				  struct ieee80211_vif *vif)
{
	struct ath12k_vif_iter *arvif_iter = data;
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);

	if (arvif->vdev_id == arvif_iter->vdev_id)
		arvif_iter->arvif = arvif;
}

struct ath12k_vif *ath12k_mac_get_arvif(struct ath12k *ar, u32 vdev_id)
{
	struct ath12k_vif_iter arvif_iter = { 0,};
	u32 flags;

	arvif_iter.vdev_id = vdev_id;

	flags = 0;
	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   flags,
						   ath12k_get_arvif_iter,
						   &arvif_iter);
	if (!arvif_iter.arvif) {
		ath12k_warn(ar->ab, "No VIF found for vdev %d\n", vdev_id);
		return NULL;
	}

	return arvif_iter.arvif;
}

struct ath12k_vif *ath12k_mac_get_arvif_by_vdev_id(struct ath12k_base *ab,
						   u32 vdev_id)
{
	u8 i;
	struct ath12k_pdev *pdev;
	struct ath12k_vif *arvif;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = rcu_dereference(ab->pdevs_active[i]);
		if (pdev && pdev->ar) {
			arvif = ath12k_mac_get_arvif(pdev->ar, vdev_id);
			if (arvif)
				return arvif;
		}
	}

	return NULL;
}

struct ath12k *ath12k_mac_get_ar_by_vdev_id(struct ath12k_base *ab, u32 vdev_id)
{
	u8 i;
	struct ath12k_pdev *pdev;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = rcu_dereference(ab->pdevs_active[i]);
		if (pdev && pdev->ar) {
			if (pdev->ar->allocated_vdev_map & (1LL << vdev_id))
				return pdev->ar;
		}
	}

	return NULL;
}

struct ath12k *ath12k_mac_get_ar_by_pdev_id(struct ath12k_base *ab, u32 pdev_id)
{
	u8 i;
	struct ath12k_pdev *pdev;

	if (ab->hw_params->single_pdev_only) {
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

static void ath12k_pdev_caps_update(struct ath12k *ar)
{
	struct ath12k_base *ab = ar->ab;

	ar->max_tx_power = ab->target_caps.hw_max_tx_power;

	/* FIXME: Set min_tx_power to ab->target_caps.hw_min_tx_power.
	 * But since the received value in svcrdy is same as hw_max_tx_power,
	 * we can set ar->min_tx_power to 0 currently until
	 * this is fixed in firmware
	 */
	ar->min_tx_power = 0;

	ar->txpower_limit_2g = ar->max_tx_power;
	ar->txpower_limit_5g = ar->max_tx_power;
	ar->txpower_scale = WMI_HOST_TP_SCALE_MAX;
}

static int ath12k_mac_txpower_recalc(struct ath12k *ar)
{
	struct ath12k_pdev *pdev = ar->pdev;
	struct ath12k_vif *arvif;
	int ret, txpower = -1;
	u32 param;

	lockdep_assert_held(&ar->conf_mutex);

	list_for_each_entry(arvif, &ar->arvifs, struct ath12k_vif, list) {
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

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "txpower to set in hw %d\n",
		   txpower / 2);

	if ((pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP) &&
	    ar->txpower_limit_2g != (u32)txpower) {
		param = WMI_PDEV_PARAM_TXPOWER_LIMIT2G;
		ret = ath12k_wmi_pdev_set_param(ar, param,
			(u32)txpower, ar->pdev->pdev_id);
		if (ret)
			goto fail;
		ar->txpower_limit_2g = (u32)txpower;
	}

	if ((pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP) &&
	    ar->txpower_limit_5g != (u32)txpower) {
		param = WMI_PDEV_PARAM_TXPOWER_LIMIT5G;
		ret = ath12k_wmi_pdev_set_param(ar, param,
			(u32)txpower, ar->pdev->pdev_id);
		if (ret)
			goto fail;
		ar->txpower_limit_5g = (u32)txpower;
	}

	return 0;

fail:
	ath12k_warn(ar->ab, "failed to recalc txpower limit %d using pdev param %d: %d\n",
		    txpower / 2, param, ret);
	return ret;
}

static int ath12k_recalc_rtscts_prot(struct ath12k_vif *arvif)
{
	struct ath12k *ar = arvif->ar;
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

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac vdev %d recalc rts/cts prot %d\n",
		   arvif->vdev_id, rts_cts);

	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    vdev_param, rts_cts);
	if (ret)
		ath12k_warn(ar->ab, "failed to recalculate rts/cts prot for vdev %d: %d\n",
			    arvif->vdev_id, ret);

	return ret;
}

static int ath12k_mac_set_kickout(struct ath12k_vif *arvif)
{
	struct ath12k *ar = arvif->ar;
	u32 param;
	int ret;

	ret = ath12k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_STA_KICKOUT_TH,
					ATH12K_KICKOUT_THRESHOLD,
					ar->pdev->pdev_id);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set kickout threshold on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MIN_IDLE_INACTIVE_TIME_SECS;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, param,
					    ATH12K_KEEPALIVE_MIN_IDLE);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set keepalive minimum idle time on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MAX_IDLE_INACTIVE_TIME_SECS;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, param,
					    ATH12K_KEEPALIVE_MAX_IDLE);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set keepalive maximum idle time on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MAX_UNRESPONSIVE_TIME_SECS;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, param,
					    ATH12K_KEEPALIVE_MAX_UNRESPONSIVE);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set keepalive maximum unresponsive time on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}

void ath12k_mac_peer_cleanup_all(struct ath12k *ar)
{
	struct ath12k_peer *peer, *tmp;
	struct ath12k_base *ab = ar->ab;

	lockdep_assert_held(&ar->conf_mutex);

	spin_lock_bh(&ab->base_lock);
	list_for_each_entry_safe(peer, tmp, &ab->peers, struct ath12k_peer, list) {
		ath12k_dp_rx_peer_tid_cleanup(ar, peer);
		list_del(&peer->list);
		kfree(peer);
	}
	spin_unlock_bh(&ab->base_lock);

	ar->num_peers = 0;
	ar->num_stations = 0;
}

static int ath12k_mac_vdev_setup_sync(struct ath12k *ar)
{
	lockdep_assert_held(&ar->conf_mutex);

	if (test_bit(ATH12K_FLAG_CRASH_FLUSH, &ar->ab->dev_flags))
		return -ESHUTDOWN;
		
	if (!wait_for_completion_timeout(&ar->vdev_setup_done,
					 ATH12K_VDEV_SETUP_TIMEOUT_HZ)) 
		return -ETIMEDOUT;

	return ar->last_wmi_vdev_start_status ? -EINVAL : 0;
}

static int ath12k_monitor_vdev_up(struct ath12k *ar, int vdev_id)
{
	int ret = 0;

	ret = ath12k_wmi_vdev_up(ar, vdev_id, 0, ar->mac_addr);
	if (ret) {
		ath12k_warn(ar->ab, "failed to put up monitor vdev %i: %d\n",
			    vdev_id, ret);
		return ret;
	}

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac monitor vdev %i started\n",
		   vdev_id);
	return 0;
}

static int ath12k_mac_monitor_vdev_start(struct ath12k *ar, u32 vdev_id,
					 struct ieee80211_chan_def *chandef)
{
	struct ieee80211_channel *channel = NULL;
	struct wmi_vdev_start_req_arg arg = { 0, };
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	channel = chandef->chan;
	arg.vdev_id = vdev_id;
	arg.freq = channel->center_freq;
	arg.band_center_freq1 = chandef->center_freq1;
	arg.band_center_freq2 = chandef->center_freq2;
	arg.mode = ath12k_phymodes[chandef->chan->band][chandef->width];
	arg.chan_radar = !!(channel->flags & IEEE80211_CHAN_RADAR);

	arg.min_power = 0;
	arg.max_power = channel->max_power;
	arg.max_reg_power = channel->max_reg_power;
	arg.max_antenna_gain = channel->max_antenna_gain;

	arg.pref_tx_streams = ar->num_tx_chains;
	arg.pref_rx_streams = ar->num_rx_chains;

	arg.passive |= !!(chandef->chan->flags & IEEE80211_CHAN_NO_IR);

	reinit_completion(&ar->vdev_setup_done);
	reinit_completion(&ar->vdev_delete_done);

	ret = ath12k_wmi_vdev_start(ar, &arg, false);
	if (ret) {
		ath12k_warn(ar->ab, "failed to request monitor vdev %i start: %d\n",
			    vdev_id, ret);
		return ret;
	}

	ret = ath12k_mac_vdev_setup_sync(ar);
	if (ret) {
		ath12k_warn(ar->ab, "failed to synchronize setup for monitor vdev %i start: %d\n",
			    vdev_id, ret);
		return ret;
	}

	ret = ath12k_wmi_vdev_up(ar, vdev_id, 0, ar->mac_addr);
	if (ret) {
		ath12k_warn(ar->ab, "failed to put up monitor vdev %i: %d\n",
			    vdev_id, ret);
		goto vdev_stop;
	}

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac monitor vdev %i started\n",
		   vdev_id);
	return 0;

vdev_stop:
	ret = ath12k_wmi_vdev_stop(ar, vdev_id);
	if (ret)
		ath12k_warn(ar->ab, "failed to stop monitor vdev %i after start failure: %d\n",
			    vdev_id, ret);
	return ret;
}

static int ath12k_mac_monitor_vdev_stop(struct ath12k *ar)
{
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_done);

	ret = ath12k_wmi_vdev_stop(ar, ar->monitor_vdev_id);
	if (ret)
		ath12k_warn(ar->ab, "failed to request monitor vdev %i stop: %d\n",
			    ar->monitor_vdev_id, ret);

	ret = ath12k_mac_vdev_setup_sync(ar);
	if (ret)
		ath12k_warn(ar->ab, "failed to synchronize monitor vdev %i stop: %d\n",
			    ar->monitor_vdev_id, ret);

	ret = ath12k_wmi_vdev_down(ar, ar->monitor_vdev_id);
	if (ret)
		ath12k_warn(ar->ab, "failed to put down monitor vdev %i: %d\n",
			    ar->monitor_vdev_id, ret);

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac monitor vdev %i stopped\n",
		   ar->monitor_vdev_id);
	return ret;
}

static int ath12k_mac_monitor_vdev_create(struct ath12k *ar)
{
	struct ath12k_pdev *pdev = ar->pdev;
	struct ath12k_wmi_vdev_create_arg arg = { 0, };
	u32 bit;
	int ret = 0;
	u8 tmp_addr[6] = {0};
	u16 nss = 0;
	u16 nss_temp = 0;

	lockdep_assert_held(&ar->conf_mutex);

	if (ar->monitor_vdev_created)
		return 0;

	if (ar->ab->free_vdev_map == 0) {
		ath12k_warn(ar->ab, "failed to find free vdev id for monitor vdev\n");
		return -ENOMEM;
	}

	bit = (u32)__ffs64(ar->ab->free_vdev_map);

	ar->monitor_vdev_id = bit;

	arg.if_id = ar->monitor_vdev_id;
	arg.type = WMI_VDEV_TYPE_MONITOR;
	arg.subtype = WMI_VDEV_SUBTYPE_NONE;
	arg.pdev_id = pdev->pdev_id;
	arg.if_stats_id = ATH12K_INVAL_VDEV_STATS_ID;

	if (pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP) {
		arg.chains[NL80211_BAND_2GHZ].tx = ar->num_tx_chains;
		arg.chains[NL80211_BAND_2GHZ].rx = ar->num_rx_chains;
	}

	if (pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP) {
		arg.chains[NL80211_BAND_5GHZ].tx = ar->num_tx_chains;
		arg.chains[NL80211_BAND_5GHZ].rx = ar->num_rx_chains;
	}

	ret = ath12k_wmi_vdev_create(ar, tmp_addr, &arg);
	if (ret) {
		ath12k_warn(ar->ab, "failed to request monitor vdev %i creation: %d\n",
			    ar->monitor_vdev_id, ret);
		ar->monitor_vdev_id = (u32)-1;
		return ret;
	}

	nss = ((nss_temp = get_num_chains(ar->cfg_tx_chainmask)) ? nss_temp : 1);
	ret = ath12k_wmi_vdev_set_param_cmd(ar, ar->monitor_vdev_id,
					    WMI_VDEV_PARAM_NSS, nss);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set vdev %d chainmask 0x%x, nss %d :%d\n",
			    ar->monitor_vdev_id, ar->cfg_tx_chainmask, nss, ret);
		return ret;
	}

	ret = ath12k_mac_txpower_recalc(ar);
	if (ret)
		return ret;

	ar->allocated_vdev_map |= 1LL << ar->monitor_vdev_id;
	ar->ab->free_vdev_map &= ~(1LL << ar->monitor_vdev_id);
	ar->num_created_vdevs++;
	ar->monitor_vdev_created = true;
	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac monitor vdev %d created\n",
		   ar->monitor_vdev_id);

	return 0;
}

static int ath12k_mac_monitor_vdev_delete(struct ath12k *ar)
{
	int ret = 0;
	unsigned long time_left = 0;

	lockdep_assert_held(&ar->conf_mutex);

	if (!ar->monitor_vdev_created)
		return 0;

	reinit_completion(&ar->vdev_delete_done);

	ret = ath12k_wmi_vdev_delete(ar, ar->monitor_vdev_id);
	if (ret) {
		ath12k_warn(ar->ab, "failed to request wmi monitor vdev %i removal: %d\n",
			    ar->monitor_vdev_id, ret);
		return ret;
	}

	time_left = wait_for_completion_timeout(&ar->vdev_delete_done,
						ATH12K_VDEV_DELETE_TIMEOUT_HZ);
	if (time_left == 0) {
		ath12k_warn(ar->ab, "Timeout in receiving vdev delete response\n");
	} else {
		ar->allocated_vdev_map &= ~(1LL << ar->monitor_vdev_id);
		ar->ab->free_vdev_map |= 1LL << (ar->monitor_vdev_id);
		ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac monitor vdev %d deleted\n",
			   ar->monitor_vdev_id);
		ar->num_created_vdevs--;
		ar->monitor_vdev_id = (u32)-1;
		ar->monitor_vdev_created = false;
	}

	return ret;
}

static void
ath12k_mac_get_any_chandef_iter(struct ieee80211_hw *hw,
				struct ieee80211_chanctx_conf *conf,
				void *data)
{
	struct ieee80211_chan_def **def = data;

	*def = &conf->def;
}

static int ath12k_mac_monitor_start(struct ath12k *ar)
{
#if 0
	struct cfg80211_chan_def *chandef = NULL;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	if (ar->monitor_started)
		return 0;

	ieee80211_iter_chan_contexts_atomic(ar->hw,
					    ath12k_mac_get_any_chandef_iter,
					    &chandef);
	if (!chandef)
		return 0;

	ret = ath12k_mac_monitor_vdev_start(ar, ar->monitor_vdev_id, chandef);
	if (ret) {
		ath12k_warn(ar->ab, "failed to start monitor vdev: %d\n", ret);
		ath12k_mac_monitor_vdev_delete(ar);
		return ret;
	}

	ar->monitor_started = true;
	ar->num_started_vdevs++;
	ret = ath12k_dp_tx_htt_monitor_mode_ring_config(ar, false);
	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac monitor started ret %d\n", ret);

	return ret;
#endif
	return 0;
}

static int ath12k_mac_monitor_stop(struct ath12k *ar)
{
#if 0
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	if (!ar->monitor_started)
		return 0;

	ret = ath12k_mac_monitor_vdev_stop(ar);
	if (ret) {
		ath12k_warn(ar->ab, "failed to stop monitor vdev: %d\n", ret);
		return ret;
	}

	ar->monitor_started = false;
	ar->num_started_vdevs--;
	ret = ath12k_dp_tx_htt_monitor_mode_ring_config(ar, true);
	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac monitor stopped ret %d\n", ret);
	return ret;
#endif
	return 0;
}

static int ath12k_mac_op_config(struct ieee80211_hw *hw, u32 changed)
{
#if ATH12K_SUPPORT_MONITOR
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ieee80211_conf *conf = &hw->conf;
	int ret = 0;

	mutex_lock(&ar->conf_mutex);

	if (changed & IEEE80211_CONF_CHANGED_MONITOR) {
		//ar->monitor_conf_enabled = conf->flags & IEEE80211_CONF_MONITOR;
		if (ar->monitor_conf_enabled) {
			if (ar->monitor_vdev_created)
				goto exit;
			ret = ath12k_mac_monitor_vdev_create(ar);
			if (ret)
				goto exit;
			ret = ath12k_mac_monitor_start(ar);
			if (ret)
				goto err_mon_del;
		} else {
			if (!ar->monitor_vdev_created)
				goto exit;
			ret = ath12k_mac_monitor_stop(ar);
			if (ret)
				goto exit;
			ath12k_mac_monitor_vdev_delete(ar);
		}
	}

exit:
	mutex_unlock(&ar->conf_mutex);
	return ret;

err_mon_del:
	ath12k_mac_monitor_vdev_delete(ar);
	mutex_unlock(&ar->conf_mutex);
	return 0;
#endif
	return -ENOTSUPP;
}

static int ath12k_mac_setup_bcn_tmpl(struct ath12k_vif *arvif)
{
#if 0
	struct ath12k *ar = arvif->ar;
	struct ath12k_base *ab = ar->ab;
	struct ieee80211_hw *hw = ar->hw;
	struct ieee80211_vif *vif = arvif->vif;
	struct ieee80211_mutable_offsets offs = { 0, };
	struct sk_buff *bcn;
	struct ieee80211_mgmt *mgmt;
	u8 *ies;
	int ret;

	if (arvif->vdev_type != WMI_VDEV_TYPE_AP)
		return 0;

	bcn = ieee80211_beacon_get_template(hw, vif, &offs, 0);
	if (!bcn) {
		ath12k_warn(ab, "failed to get beacon template from mac80211\n");
		return -EPERM;
	}

	ies = bcn->data + ieee80211_get_hdrlen_from_skb(bcn);
	ies += sizeof(mgmt->u.beacon);

	if (cfg80211_find_ie(WLAN_EID_RSN, ies, (skb_tail_pointer(bcn) - ies)))
		arvif->rsnie_present = true;

	if (cfg80211_find_vendor_ie(WLAN_OUI_MICROSOFT,
				    WLAN_OUI_TYPE_MICROSOFT_WPA,
				    ies, (skb_tail_pointer(bcn) - ies)))
		arvif->wpaie_present = true;

	ret = ath12k_wmi_bcn_tmpl(ar, arvif->vdev_id, &offs, bcn);

	kfree_skb(bcn);

	if (ret)
		ath12k_warn(ab, "failed to submit beacon template command: %d\n",
			    ret);

	return ret;
#endif
	return 0;
}

static void ath12k_control_beaconing(struct ath12k_vif *arvif,
				     struct ieee80211_bss_conf *info)
{
#if 0
	struct ath12k *ar = arvif->ar;
	int ret = 0;

	lockdep_assert_held(&arvif->ar->conf_mutex);

	if (!info->enable_beacon) {
		ret = ath12k_wmi_vdev_down(ar, arvif->vdev_id);
		if (ret)
			ath12k_warn(ar->ab, "failed to down vdev_id %i: %d\n",
				    arvif->vdev_id, ret);

		arvif->is_up = false;
		return;
	}

	/* Install the beacon template to the FW */
	ret = ath12k_mac_setup_bcn_tmpl(arvif);
	if (ret) {
		ath12k_warn(ar->ab, "failed to update bcn tmpl during vdev up: %d\n",
			    ret);
		return;
	}

	arvif->tx_seq_no = 0x1000;

	arvif->aid = 0;

	ether_addr_copy(arvif->bssid, info->bssid);

	ret = ath12k_wmi_vdev_up(arvif->ar, arvif->vdev_id, arvif->aid,
				 arvif->bssid);
	if (ret) {
		ath12k_warn(ar->ab, "failed to bring up vdev %d: %i\n",
			    arvif->vdev_id, ret);
		return;
	}

	arvif->is_up = true;

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac vdev %d up\n", arvif->vdev_id);
#endif
}

static void ath12k_mac_handle_beacon_iter(void *data, const u8 *mac,
					  struct ieee80211_vif *vif)
{
	struct sk_buff *skb = data;
	struct ieee80211_mgmt *mgmt = (void *)skb->data;
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);

	if (ieee80211_vif_type(vif) != NL80211_IFTYPE_STATION)
		return;

	if (!ether_addr_equal(mgmt->bssid, ieee80211_vif_bss_conf_get_bssid(vif)))
		return;

	cancel_delayed_work(&arvif->connection_loss_work);
}

void ath12k_mac_handle_beacon(struct ath12k *ar, struct sk_buff *skb)
{
	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   IEEE80211_VIF_ITER_NORMAL,
						   ath12k_mac_handle_beacon_iter,
						   skb);
}

static void ath12k_mac_handle_beacon_miss_iter(void *data, const u8 *mac,
					       struct ieee80211_vif *vif)
{
	u32 *vdev_id = data;
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ath12k *ar = arvif->ar;
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
				     ATH12K_CONNECTION_LOSS_HZ);
}

void ath12k_mac_handle_beacon_miss(struct ath12k *ar, u32 vdev_id)
{
	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   IEEE80211_VIF_ITER_NORMAL,
						   ath12k_mac_handle_beacon_miss_iter,
						   &vdev_id);
}

static void ath12k_mac_vif_sta_connection_loss_work(void *context)
{
	struct ath12k_vif *arvif = context;
	struct ieee80211_vif *vif = arvif->vif;

	if (!arvif->is_up)
		return;

	ieee80211_connection_loss(vif);
}

static void ath12k_peer_assoc_h_basic(struct ath12k *ar,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta,
				      struct ath12k_wmi_peer_assoc_arg *arg)
{
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
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

static void ath12k_peer_assoc_h_crypto(struct ath12k *ar,
				       struct ieee80211_vif *vif,
				       struct ieee80211_sta *sta,
				       struct ath12k_wmi_peer_assoc_arg *arg)
{
	struct ieee80211_chan_def def;
	struct ieee80211_bss *bss;
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	const u8 *rsnie = NULL;
	const u8 *wpaie = NULL;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath12k_mac_vif_chan(vif, &def)))
		return;

	bss = ieee80211_get_bss(ar->hw, def.chan, 
        ieee80211_vif_bss_conf_get_bssid(vif), NULL, 0,
        IEEE80211_BSS_TYPE_ANY, IEEE80211_PRIVACY_ANY);

	if (arvif->rsnie_present || arvif->wpaie_present) {
		arg->need_ptk_4_way = true;
		if (arvif->wpaie_present)
			arg->need_gtk_2_way = true;
	} else if (bss) {
		rcu_read_lock();
		rsnie = ieee80211_bss_get_ie(bss, WLAN_EID_RSN);
		wpaie = ieee80211_bss_find_vendor_ie(bss, WLAN_OUI_MICROSOFT_WPA);
		rcu_read_unlock();
		ieee80211_put_bss(ar->hw, bss);
	}

	/* FIXME: base on RSN IE/WPA IE is a correct idea? */
	if (rsnie || wpaie) {
		ath12k_dbg(ar->ab, ATH12K_DBG_WMI, "rsn ie found\n");
		arg->need_ptk_4_way = true;
	}

	if (wpaie) {
		ath12k_dbg(ar->ab, ATH12K_DBG_WMI, "wpa ie found\n");
		arg->need_gtk_2_way = true;
	}

	if (ieee80211_sta_get_mfp(sta)) {
		/* TODO: Need to check if FW supports PMF? */
		arg->is_pmf_enabled = true;
	}

	/* TODO: safe_mode_enabled (bypass 4-way handshake) flag req? */
}

static void ath12k_peer_assoc_h_rates(struct ath12k *ar,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta,
				      struct ath12k_wmi_peer_assoc_arg *arg)
{
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct wmi_rate_set_arg *rateset = &arg->peer_legacy_rates;
	struct ieee80211_chan_def def;
	const struct ieee80211_supported_band *sband;
	const struct ieee80211_rate *rates;
	enum nl80211_band band;
	u32 ratemask;
	u8 rate;
	int i;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath12k_mac_vif_chan(vif, &def)))
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

		rate = ath12k_mac_bitrate_to_rate(rates->bitrate);
		rateset->rates[rateset->num_rates] = rate;
		rateset->num_rates++;
	}
}

static bool
ath12k_peer_assoc_h_ht_masked(const u8 ht_mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
{
	int nss;

	for (nss = 0; nss < IEEE80211_HT_MCS_MASK_LEN; nss++)
		if (ht_mcs_mask[nss])
			return false;

	return true;
}

static bool
ath12k_peer_assoc_h_vht_masked(const u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
{
	int nss;

	for (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++)
		if (vht_mcs_mask[nss])
			return false;

	return true;
}

static void ath12k_peer_assoc_h_ht(struct ath12k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta,
				   struct ath12k_wmi_peer_assoc_arg *arg)
{
	const struct ieee80211_sta_ht_cap *ht_cap = ieee80211_sta_get_ht_cap(sta);
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	u32 i, n;
	u8 max_nss;
	u32 stbc;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath12k_mac_vif_chan(vif, &def)))
		return;

	if (!ht_cap->ht_supported)
		return;

	band = def.chan->band;
	ht_mcs_mask = arvif->bitrate_mask.control[band].ht_mcs;

	if (ath12k_peer_assoc_h_ht_masked(ht_mcs_mask))
		return;

	arg->ht_flag = true;

	arg->peer_max_mpdu = (1 << (IEEE80211_HT_MAX_AMPDU_FACTOR +
				    ht_cap->ampdu_factor)) - 1;

	arg->peer_mpdu_density =
		ath12k_parse_mpdudensity(ht_cap->ampdu_density);

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
		for (i = 0; i < arg->peer_ht_rates.num_rates; i++)
			arg->peer_ht_rates.rates[i] = (u8)i;
	} else {
		arg->peer_ht_rates.num_rates = n;
		arg->peer_nss = min(ieee80211_sta_get_rx_nss(sta), max_nss);
	}
	
	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac ht peer %pM mcs cnt %d nss %d\n",
		   arg->peer_mac,
		   arg->peer_ht_rates.num_rates,
		   arg->peer_nss);
}

static int ath12k_mac_get_max_vht_mcs_map(u16 mcs_map, int nss)
{
	switch ((mcs_map >> (2 * nss)) & 0x3) {
	case IEEE80211_VHTCAP_MCS_SUPPORT_0_7: return BIT(8) - 1;
	case IEEE80211_VHTCAP_MCS_SUPPORT_0_8: return BIT(9) - 1;
	case IEEE80211_VHTCAP_MCS_SUPPORT_0_9: return BIT(10) - 1;
	}
	return 0;
}

static u16
ath12k_peer_assoc_h_vht_limit(u16 tx_mcs_set,
			      const u16 vht_mcs_limit[NL80211_VHT_NSS_MAX])
{
	int idx_limit;
	int nss;
	u16 mcs_map;
	u16 mcs;

	for (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++) {
		mcs_map = ath12k_mac_get_max_vht_mcs_map(tx_mcs_set, nss) &
			  vht_mcs_limit[nss];

		if (mcs_map)
			idx_limit = fls(mcs_map) - 1;
		else
			idx_limit = -1;

		switch (idx_limit) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
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
			//fallthrough;
		case -1:
			mcs = IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;
			break;
		}

		tx_mcs_set &= ~(0x3 << (nss * 2));
		tx_mcs_set |= mcs << (nss * 2);
	}

	return tx_mcs_set;
}

static void ath12k_peer_assoc_h_vht(struct ath12k *ar,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta,
				    struct ath12k_wmi_peer_assoc_arg *arg)
{
	const struct ieee80211_sta_vht_cap *vht_cap = ieee80211_sta_get_vht_cap(sta);
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	const u16 *vht_mcs_mask;
	u16 tx_mcs_map;
	u8 ampdu_factor;
	u8 max_nss, vht_mcs;
	u8 i;

	if (WARN_ON(ath12k_mac_vif_chan(vif, &def)))
		return;

	if (!vht_cap->vht_supported)
		return;

	band = def.chan->band;
	vht_mcs_mask = arvif->bitrate_mask.control[band].vht_mcs;

	if (ath12k_peer_assoc_h_vht_masked(vht_mcs_mask))
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
			max_nss = i + 1;
	}
	arg->peer_nss = min(ieee80211_sta_get_rx_nss(sta), max_nss);
	arg->rx_max_rate = __le16_to_cpu(vht_cap->vht_mcs.rx_highest);
	arg->rx_mcs_set = __le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map);
	arg->tx_max_rate = __le16_to_cpu(vht_cap->vht_mcs.tx_highest);

	tx_mcs_map = __le16_to_cpu(vht_cap->vht_mcs.tx_mcs_map);
	arg->tx_mcs_set = ath12k_peer_assoc_h_vht_limit(tx_mcs_map, vht_mcs_mask);

	/* In IPQ8074 platform, VHT mcs rate 10 and 11 is enabled by default.
	 * VHT mcs rate 10 and 11 is not suppoerted in 11ac standard.
	 * so explicitly disable the VHT MCS rate 10 and 11 in 11ac mode.
	 */
	arg->tx_mcs_set &= ~IEEE80211_VHT_MCS_SUPPORT_0_11_MASK;
	arg->tx_mcs_set |= IEEE80211_DISABLE_VHT_MCS_SUPPORT_0_11;

	if ((arg->tx_mcs_set & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED) ==
			IEEE80211_VHTCAP_MCS_NOT_SUPPORTED)
		arg->peer_vht_caps &= ~IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE;

	/* TODO:  Check */
	arg->tx_max_mcs_nss = 0xFF;

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac vht peer %pM max_mpdu %d flags 0x%x\n",
		   ieee80211_sta_addr(sta), arg->peer_max_mpdu, arg->peer_flags);

	/* TODO: rxnss_override */
}

static void ath12k_peer_assoc_h_he(struct ath12k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta,
				   struct ath12k_wmi_peer_assoc_arg *arg)
{
	const struct ieee80211_sta_he_cap *he_cap = ieee80211_sta_get_he_cap(sta);
	const struct ieee80211_sta_vht_cap *vht_cap = ieee80211_sta_get_vht_cap(sta);
	const struct ieee80211_sta_ht_cap *ht_cap = ieee80211_sta_get_ht_cap(sta);
	u8 i;
	u8 ampdu_factor, rx_mcs_80, rx_mcs_160, max_nss;
	u16 mcs_160_map, mcs_80_map;
	bool support_160;
	u16 v;
	struct ieee80211_bss_conf* bss_conf = ieee80211_vif_get_bss_conf(vif);

	if (!he_cap->he_supported)
		return;

	arg->he_flag = true;

	support_160 = !!(he_cap->he_capabilities.phy_cap_info[0] &
		  IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G);

	/* Supported HE-MCS and NSS Set of peer he_cap is intersection with self he_cp */
	mcs_160_map = le16_to_cpu(he_cap->he_mcs_nss_supp.he_rx_mcs_160);
	mcs_80_map = le16_to_cpu(he_cap->he_mcs_nss_supp.he_rx_mcs_80);

	if (support_160) {
		for (i = 7; i >= 0; i--) {
			u8 mcs_160 = (mcs_160_map >> (2 * i)) & 3;

			if (mcs_160 != IEEE80211_HECAP_MCS_NOT_SUPPORTED) {
				rx_mcs_160 = i + 1;
				break;
			}
		}
	}

	for (i = 7; i >= 0; i--) {
		u8 mcs_80 = (mcs_80_map >> (2 * i)) & 3;

		if (mcs_80 != IEEE80211_HECAP_MCS_NOT_SUPPORTED) {
			rx_mcs_80 = i + 1;
			break;
		}
	}

	if (support_160)
		max_nss = min(rx_mcs_80, rx_mcs_160);
	else
		max_nss = rx_mcs_80;

	arg->peer_nss = min(ieee80211_sta_get_rx_nss(sta), max_nss);

	memcpy(&arg->peer_he_cap_macinfo, he_cap->he_capabilities.mac_cap_info,
	       sizeof(arg->peer_he_cap_macinfo));
	memcpy(&arg->peer_he_cap_phyinfo, he_cap->he_capabilities.phy_cap_info,
	       sizeof(arg->peer_he_cap_phyinfo));
	memcpy(&arg->peer_he_ops, ieee80211_bss_conf_get_he_operation(bss_conf),
	       sizeof(arg->peer_he_ops));

	/* the top most byte is used to indicate BSS color info */
	arg->peer_he_ops &= 0xffffff;

	/* As per section 26.6.1 11ax Draft5.0, if the Max AMPDU Exponent Extension
	 * in HE cap is zero, use the arg->peer_max_mpdu as calculated while parsing
	 * VHT caps(if VHT caps is present) or HT caps (if VHT caps is not present).
	 *
	 * For non-zero value of Max AMPDU Extponent Extension in HE MAC caps,
	 * if a HE STA sends VHT cap and HE cap IE in assoc request then, use
	 * MAX_AMPDU_LEN_FACTOR as 20 to calculate max_ampdu length.
	 * If a HE STA that does not send VHT cap, but HE and HT cap in assoc
	 * request, then use MAX_AMPDU_LEN_FACTOR as 16 to calculate max_ampdu
	 * length.
	 */
	ampdu_factor = (he_cap->he_capabilities.mac_cap_info[3] &
			IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_MASK) >>
			IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_MASK;

	if (ampdu_factor) {
		if (vht_cap->vht_supported)
			arg->peer_max_mpdu = (1 << (IEEE80211_HE_VHT_MAX_AMPDU_FACTOR +
						    ampdu_factor)) - 1;
		else if (ht_cap->ht_supported)
			arg->peer_max_mpdu = (1 << (IEEE80211_HE_HT_MAX_AMPDU_FACTOR +
						    ampdu_factor)) - 1;
	}

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
		//fallthrough;

	default:
		v = le16_to_cpu(he_cap->he_mcs_nss_supp.he_rx_mcs_80);
		arg->peer_he_rx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80] = v;

		v = le16_to_cpu(he_cap->he_mcs_nss_supp.he_tx_mcs_80);
		arg->peer_he_tx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80] = v;

		arg->peer_he_mcs_count++;
		break;
	}
}


static void ath12k_peer_assoc_h_he_6ghz(struct ath12k *ar,
					struct ieee80211_vif *vif,
					struct ieee80211_sta *sta,
					struct ath12k_wmi_peer_assoc_arg *arg)
{
	const struct ieee80211_sta_he_cap *he_cap = ieee80211_sta_get_he_cap(sta);
	struct ieee80211_he_6ghz_cap  *sta_he_6ghz_cap = ieee80211_sta_get_6ghz_cap(sta);
	enum ieee80211_sta_rx_bandwidth sta_bandwidth = ieee80211_sta_get_bandwidth(sta);
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	u8  ampdu_factor;

	if (WARN_ON(ath12k_mac_vif_chan(vif, &def)))
		return;

	band = def.chan->band;

	if (!arg->he_flag || band != NL80211_BAND_6GHZ || !sta_he_6ghz_cap->cap)
		return;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_40)
		arg->bw_40 = true;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_80)
		arg->bw_80 = true;

	if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_160)
		arg->bw_160 = true;

	arg->peer_he_caps_6ghz = le16_to_cpu(sta_he_6ghz_cap->cap);

	arg->peer_mpdu_density = ath12k_parse_mpdudensity(
		FIELD_GET(IEEE80211_HE_6GHZCAP_MIN_MPDU_START, arg->peer_he_caps_6ghz));
	
	/* From IEEE Std 802.11ax-2021 - Section 10.12.2: An HE STA shall be capable of
	 * receiving A-MPDU where the A-MPDU pre-EOF padding length is up to the value
	 * indicated by the Maximum A-MPDU Length Exponent Extension field in the HE
	 * Capabilities element and the Maximum A-MPDU Length Exponent field in HE 6 GHz
	 * Band Capabilities element in the 6 GHz band.
	 *
	 * Here, we are extracting the Max A-MPDU Exponent Extension from HE caps and
	 * factor is the Maximum A-MPDU Length Exponent from HE 6 GHZ Band capability.
	 */
	ampdu_factor = FIELD_GET(IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_MASK,
				 he_cap->he_capabilities.mac_cap_info[3]) +
			FIELD_GET(IEEE80211_HE_6GHZCAP_MAX_AMPDU_LEN_EXP,
				  arg->peer_he_caps_6ghz);

	arg->peer_max_mpdu = (1u << (IEEE80211_HE_6GHZ_MAX_AMPDU_FACTOR +
				     ampdu_factor)) - 1;
}


static void ath12k_peer_assoc_h_smps(struct ieee80211_sta *sta,
				     struct ath12k_wmi_peer_assoc_arg *arg)
{
	const struct ieee80211_sta_ht_cap *ht_cap = ieee80211_sta_get_ht_cap(sta);
	struct ieee80211_he_6ghz_cap  *sta_he_6ghz_cap = ieee80211_sta_get_6ghz_cap(sta);
	int smps;

	if (!ht_cap->ht_supported && !sta_he_6ghz_cap->cap)
		return;

	if (ht_cap->ht_supported) {
		smps = ht_cap->cap & IEEE80211_HTCAP_SM_PS;
		smps >>= IEEE80211_HTCAP_SM_PS_SHIFT;
	} else {
		smps = FIELD_GET(IEEE80211_HE_6GHZCAP_SM_PS,
				 le16_to_cpu(sta_he_6ghz_cap->cap));
	}

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

static void ath12k_peer_assoc_h_qos(struct ath12k *ar,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta,
				    struct ath12k_wmi_peer_assoc_arg *arg)
{
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	bool sta_wme = false;
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

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac peer %pM qos %d\n",
		   ieee80211_sta_addr(sta), arg->qos_flag);
}

static int ath12k_peer_assoc_qos_ap(struct ath12k *ar,
				    struct ath12k_vif *arvif,
				    struct ieee80211_sta *sta)
{
	struct ath12k_wmi_ap_ps_arg arg;
	u8 *sta_addr;
	u8 sta_uapsd_queues, sta_max_sp;
	u32 max_sp;
	u32 uapsd;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	arg.vdev_id = arvif->vdev_id;
	sta_uapsd_queues = ieee80211_sta_get_uapsd_queues(sta);
    sta_max_sp = ieee80211_sta_get_max_sp(sta);
	
	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac uapsd_queues 0x%x max_sp %d\n",
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
	arg.param = WMI_AP_PS_PEER_PARAM_UAPSD;
	arg.value = uapsd;
	ret = ath12k_wmi_send_set_ap_ps_param_cmd(ar, sta_addr, &arg);
	if (ret)
		goto err;

	arg.param = WMI_AP_PS_PEER_PARAM_MAX_SP;
	arg.value = max_sp;
	ret = ath12k_wmi_send_set_ap_ps_param_cmd(ar, sta_addr, &arg);
	if (ret)
		goto err;

	/* TODO: revisit during testing */
	arg.param = WMI_AP_PS_PEER_PARAM_SIFS_RESP_FRMTYPE;
	arg.value = DISABLE_SIFS_RESPONSE_TRIGGER;
	ret = ath12k_wmi_send_set_ap_ps_param_cmd(ar, sta_addr, &arg);
	if (ret)
		goto err;

	arg.param = WMI_AP_PS_PEER_PARAM_SIFS_RESP_UAPSD;
	arg.value = DISABLE_SIFS_RESPONSE_TRIGGER;
	ret = ath12k_wmi_send_set_ap_ps_param_cmd(ar, sta_addr, &arg);
	if (ret)
		goto err;

	return 0;

err:
	ath12k_warn(ar->ab, "failed to set ap ps peer param %d for vdev %i: %d\n",
		    arg.param, arvif->vdev_id, ret);
	return ret;
}

static bool ath12k_mac_sta_has_ofdm_only(struct ieee80211_sta *sta)
{
	return !!(ieee80211_sta_get_supp_rates(sta, NL80211_BAND_2GHZ) >>
		ATH12K_MAC_FIRST_OFDM_RATE_IDX);
}

static enum wmi_phy_mode ath12k_mac_get_phymode_vht(struct ath12k *ar,
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

static enum wmi_phy_mode ath12k_mac_get_phymode_he(struct ath12k *ar,
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

static void ath12k_peer_assoc_h_phymode(struct ath12k *ar,
					struct ieee80211_vif *vif,
					struct ieee80211_sta *sta,
					struct ath12k_wmi_peer_assoc_arg *arg)
{
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ieee80211_sta_he_cap *sta_he_cap;
    struct ieee80211_sta_vht_cap *sta_vht_cap;
    struct ieee80211_sta_ht_cap *sta_ht_cap;
    enum ieee80211_sta_rx_bandwidth sta_bandwidth;
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	const u16 *vht_mcs_mask;
	enum wmi_phy_mode phymode = MODE_UNKNOWN;

	if (WARN_ON(ath12k_mac_vif_chan(vif, &def)))
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
		    !ath12k_peer_assoc_h_vht_masked(vht_mcs_mask)) {
			if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_40)
				phymode = MODE_11AC_VHT40;
			else
				phymode = MODE_11AC_VHT20;
		} else if (sta_ht_cap->ht_supported &&
			   !ath12k_peer_assoc_h_ht_masked(ht_mcs_mask)) {
			if (sta_bandwidth == IEEE80211_STA_RX_BANDWIDTH_40)
				phymode = MODE_11NG_HT40;
			else
				phymode = MODE_11NG_HT20;
		} else if (ath12k_mac_sta_has_ofdm_only(sta)) {
			phymode = MODE_11G;
		} else {
			phymode = MODE_11B;
		}
		break;
	case NL80211_BAND_5GHZ:
	case NL80211_BAND_6GHZ:
		/* Check HE first */
		if (sta_he_cap->he_supported) {
			phymode = ath12k_mac_get_phymode_he(ar, sta);
		} else if (sta_vht_cap->vht_supported &&
		    !ath12k_peer_assoc_h_vht_masked(vht_mcs_mask)) {
			phymode = ath12k_mac_get_phymode_vht(ar, sta);
		} else if (sta_ht_cap->ht_supported &&
			   !ath12k_peer_assoc_h_ht_masked(ht_mcs_mask)) {
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

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac peer %pM phymode %a\n",
		   ieee80211_sta_addr(sta), ath12k_mac_phymode_str(phymode));

	arg->peer_phymode = phymode;
	WARN_ON(phymode == MODE_UNKNOWN);
}

static void ath12k_peer_assoc_prepare(struct ath12k *ar,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta,
				      struct ath12k_wmi_peer_assoc_arg *arg,
				      bool reassoc)
{
	struct ath12k_sta *arsta;

	lockdep_assert_held(&ar->conf_mutex);

	arsta = ieee80211_sta_get_priv_data(sta);

	memset(arg, 0, sizeof(*arg));

	reinit_completion(&ar->peer_assoc_done);

	arg->peer_new_assoc = !reassoc;
	ath12k_peer_assoc_h_basic(ar, vif, sta, arg);
	ath12k_peer_assoc_h_crypto(ar, vif, sta, arg);
	ath12k_peer_assoc_h_rates(ar, vif, sta, arg);
	ath12k_peer_assoc_h_phymode(ar, vif, sta, arg);
	ath12k_peer_assoc_h_ht(ar, vif, sta, arg);
	ath12k_peer_assoc_h_vht(ar, vif, sta, arg);
	ath12k_peer_assoc_h_he(ar, vif, sta, arg);
	ath12k_peer_assoc_h_he_6ghz(ar, vif, sta, arg);
	//ath12k_peer_assoc_h_eht(ar, vif, sta, arg);
	ath12k_peer_assoc_h_qos(ar, vif, sta, arg);
	ath12k_peer_assoc_h_smps(sta, arg);

	arsta->peer_nss = arg->peer_nss;
	/* TODO: amsdu_disable req? */
}

static int ath12k_setup_peer_smps(struct ath12k *ar, struct ath12k_vif *arvif,
				  const u8 *addr,
				  const struct ieee80211_sta_ht_cap *ht_cap,
				  u16 he_6ghz_capa)
{
	int smps;

	if (!ht_cap->ht_supported && !he_6ghz_capa)
		return 0;

	if (ht_cap->ht_supported) {
		smps = ht_cap->cap & IEEE80211_HTCAP_SM_PS;
		smps >>= IEEE80211_HTCAP_SM_PS_SHIFT;
	} else {
		smps = FIELD_GET(IEEE80211_HE_6GHZCAP_SM_PS, he_6ghz_capa);
	}

	if (smps >= ARRAY_SIZE(ath12k_smps_map))
		return -EINVAL;

	return ath12k_wmi_set_peer_param(ar, addr, arvif->vdev_id,
					 WMI_PEER_MIMO_PS_STATE,
					 ath12k_smps_map[smps]);
}

static void ath12k_bss_assoc(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif,
			     struct ieee80211_bss_conf *bss_conf)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ieee80211_he_6ghz_cap *sta_6ghz_cap;
	struct ath12k_wmi_peer_assoc_arg peer_arg;
	struct ieee80211_sta *ap_sta;
#if 0
	struct ath12k_peer *peer;
	bool is_auth = false;
#endif
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac vdev %d assoc bssid %pM aid %d\n",
		   arvif->vdev_id, arvif->bssid, arvif->aid);

	rcu_read_lock();

	ap_sta = ieee80211_find_sta(vif, ieee80211_bss_conf_get_bssid(bss_conf));
	if (!ap_sta) {
		ath12k_warn(ar->ab, "failed to find station entry for bss %pM vdev %i\n",
			    ieee80211_bss_conf_get_bssid(bss_conf), arvif->vdev_id);
		rcu_read_unlock();
		return;
	}

	ath12k_peer_assoc_prepare(ar, vif, ap_sta, &peer_arg, false);

	rcu_read_unlock();

	ret = ath12k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
	if (ret) {
		ath12k_warn(ar->ab, "failed to run peer assoc for %pM vdev %i: %d\n",
			    ieee80211_bss_conf_get_bssid(bss_conf), arvif->vdev_id, ret);
		return;
	}

	if (!wait_for_completion_timeout(&ar->peer_assoc_done, 1 * HZ)) {
		ath12k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %i\n",
			    ieee80211_bss_conf_get_bssid(bss_conf), arvif->vdev_id);
		return;
	}

	sta_6ghz_cap = ieee80211_sta_get_6ghz_cap(ap_sta);
	ret = ath12k_setup_peer_smps(ar, arvif, ieee80211_bss_conf_get_bssid(bss_conf),
				     ieee80211_sta_get_ht_cap(ap_sta), sta_6ghz_cap->cap);
	if (ret) {
		ath12k_warn(ar->ab, "failed to setup peer SMPS for vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return;
	}

	WARN_ON(arvif->is_up);

	arvif->aid = ieee80211_bss_conf_get_aid(bss_conf);
	ether_addr_copy(arvif->bssid, ieee80211_bss_conf_get_bssid(bss_conf));

	ret = ath12k_wmi_vdev_up(ar, arvif->vdev_id, arvif->aid, arvif->bssid);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set vdev %d up: %d\n",
			    arvif->vdev_id, ret);
		return;
	}

	arvif->is_up = true;

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
		   "mac vdev %d up (associated) bssid %pM aid %d\n",
		   arvif->vdev_id, ieee80211_bss_conf_get_bssid(bss_conf), 
		   ieee80211_bss_conf_get_aid(bss_conf));
	// TODOTODO: REVIEW THE PEER AUTH
#if 0
	spin_lock_bh(&ar->ab->base_lock);

	peer = ath12k_peer_find(ar->ab, arvif->vdev_id, arvif->bssid);
	if (peer && peer->is_authorized)
		is_auth = true;

	spin_unlock_bh(&ar->ab->base_lock);

	/* Authorize BSS Peer */
	if (is_auth) {
		ret = ath12k_wmi_set_peer_param(ar, arvif->bssid,
						arvif->vdev_id,
						WMI_PEER_AUTHORIZE,
						1);
		if (ret)
			ath12k_warn(ar->ab, "Unable to authorize BSS peer: %d\n", ret);
	}
#endif
	ret = ath12k_wmi_send_obss_spr_cmd(ar, arvif->vdev_id,
					   ieee80211_bss_conf_get_he_obss_pd(bss_conf));
	if (ret)
		ath12k_warn(ar->ab, "failed to set vdev %i OBSS PD parameters: %d\n",
			    arvif->vdev_id, ret);

	ath12k_mac_11d_scan_stop_all(ar->ab);
}

static void ath12k_bss_disassoc(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac vdev %i disassoc bssid %pM\n",
		   arvif->vdev_id, arvif->bssid);

	ret = ath12k_wmi_vdev_down(ar, arvif->vdev_id);
	if (ret)
		ath12k_warn(ar->ab, "failed to down vdev %i: %d\n",
			    arvif->vdev_id, ret);

	arvif->is_up = false;

	cancel_delayed_work_sync(&arvif->connection_loss_work);
}

static int ath12k_mac_get_rate_hw_value(int bitrate)
{
	u32 preamble;
	u16 hw_value;
	int rate;
	size_t i;

	if (ath12k_mac_bitrate_is_cck(bitrate))
		preamble = WMI_RATE_PREAMBLE_CCK;
	else
		preamble = WMI_RATE_PREAMBLE_OFDM;

	for (i = 0; i < ARRAY_SIZE(ath12k_legacy_rates); i++) {
		if (ath12k_legacy_rates[i].bitrate != bitrate)
			continue;

		hw_value = ath12k_legacy_rates[i].hw_value;
		rate = ATH12K_HW_RATE_CODE(hw_value, 0, preamble);

		return rate;
	}

	return -EINVAL;
}

static void ath12k_recalculate_mgmt_rate(struct ath12k *ar,
					 struct ieee80211_vif *vif,
					 struct ieee80211_chan_def *def)
{
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
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

	hw_rate_code = ath12k_mac_get_rate_hw_value(bitrate);
	if (hw_rate_code < 0) {
		ath12k_warn(ar->ab, "bitrate not supported %d\n", bitrate);
		return;
	}

	vdev_param = WMI_VDEV_PARAM_MGMT_RATE;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, vdev_param,
					    hw_rate_code);
	if (ret)
		ath12k_warn(ar->ab, "failed to set mgmt tx rate %d\n", ret);

	vdev_param = WMI_VDEV_PARAM_BEACON_RATE;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id, vdev_param,
					    hw_rate_code);
	if (ret)
		ath12k_warn(ar->ab, "failed to set beacon tx rate %d\n", ret);
}

static int ath12k_mac_fils_discovery(struct ath12k_vif *arvif,
				     struct ieee80211_bss_conf *info)
{
#if 0
	struct ath12k *ar = arvif->ar;
	struct sk_buff *tmpl;
	int ret;
	u32 interval;
	bool unsol_bcast_probe_resp_enabled = false;

	if (info->fils_discovery.max_interval) {
		interval = info->fils_discovery.max_interval;

		tmpl = ieee80211_get_fils_discovery_tmpl(ar->hw, arvif->vif);
		if (tmpl)
			ret = ath12k_wmi_fils_discovery_tmpl(ar, arvif->vdev_id,
							     tmpl);
	} else if (info->unsol_bcast_probe_resp_interval) {
		unsol_bcast_probe_resp_enabled = 1;
		interval = info->unsol_bcast_probe_resp_interval;

		tmpl = ieee80211_get_unsol_bcast_probe_resp_tmpl(ar->hw,
								 arvif->vif);
		if (tmpl)
			ret = ath12k_wmi_probe_resp_tmpl(ar, arvif->vdev_id,
							 tmpl);
	} else { /* Disable */
		return ath12k_wmi_fils_discovery(ar, arvif->vdev_id, 0, false);
	}

	if (!tmpl) {
		ath12k_warn(ar->ab,
			    "mac vdev %i failed to retrieve %s template\n",
			    arvif->vdev_id, (unsol_bcast_probe_resp_enabled ?
			    "unsolicited broadcast probe response" :
			    "FILS discovery"));
		return -EPERM;
	}
	kfree_skb(tmpl);

	if (!ret)
		ret = ath12k_wmi_fils_discovery(ar, arvif->vdev_id, interval,
						unsol_bcast_probe_resp_enabled);

	return ret;
#endif
	return 0;
}

static void ath12k_mac_op_bss_info_changed(struct ieee80211_hw *hw,
					   struct ieee80211_vif *vif,
					   struct ieee80211_bss_conf *info,
					   u64 changed)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ieee80211_chan_def def;
	u32 param_id, param_value;
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
		ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param_id,
						    arvif->beacon_interval);
		if (ret)
			ath12k_warn(ar->ab, "Failed to set beacon interval for VDEV: %d\n",
				    arvif->vdev_id);
		else
			ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
				   "Beacon interval: %d set for VDEV: %d\n",
				   arvif->beacon_interval, arvif->vdev_id);
	}

	if (changed & BSS_CHANGED_BEACON) {
		param_id = WMI_PDEV_PARAM_BEACON_TX_MODE;
		param_value = WMI_BEACON_STAGGERED_MODE;
		ret = ath12k_wmi_pdev_set_param(ar, param_id,
						param_value, ar->pdev->pdev_id);
		if (ret)
			ath12k_warn(ar->ab, "Failed to set beacon mode for VDEV: %d\n",
				    arvif->vdev_id);
		else
			ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
				   "Set staggered beacon mode for VDEV: %d\n",
				   arvif->vdev_id);

		ret = ath12k_mac_setup_bcn_tmpl(arvif);
		if (ret)
			ath12k_warn(ar->ab, "failed to update bcn template: %d\n",
				    ret);
	}

	if (changed & (BSS_CHANGED_BEACON_INFO | BSS_CHANGED_BEACON)) {
		arvif->dtim_period = ieee80211_bss_conf_get_dtim_period(info);

		param_id = WMI_VDEV_PARAM_DTIM_PERIOD;
		ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param_id,
						    arvif->dtim_period);

		if (ret)
			ath12k_warn(ar->ab, "Failed to set dtim period for VDEV %d: %d\n",
				    arvif->vdev_id, ret);
		else
			ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
				   "DTIM period: %d set for VDEV: %d\n",
				   arvif->dtim_period, arvif->vdev_id);
	}

#if 0
	if (changed & BSS_CHANGED_SSID &&
	    vif->type == NL80211_IFTYPE_AP) {
		arvif->u.ap.ssid_len = vif->cfg.ssid_len;
		if (vif->cfg.ssid_len)
			memcpy(arvif->u.ap.ssid, vif->cfg.ssid, vif->cfg.ssid_len);
		arvif->u.ap.hidden_ssid = info->hidden_ssid;
	}
#endif

	if (changed & BSS_CHANGED_BSSID && 
		!is_zero_ether_addr(ieee80211_bss_conf_get_bssid(info)))
		ether_addr_copy(arvif->bssid, ieee80211_bss_conf_get_bssid(info));

#if 0
	if (changed & BSS_CHANGED_BEACON_ENABLED) {
		ath12k_control_beaconing(arvif, info);

		if (arvif->is_up && vif->bss_conf.he_support &&
		    vif->bss_conf.he_oper.params) {
			/* TODO: Extend to support 1024 BA Bitmap size */
			ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
							    WMI_VDEV_PARAM_BA_MODE,
							    WMI_BA_MODE_BUFFER_SIZE_256);
			if (ret)
				ath12k_warn(ar->ab,
					    "failed to set BA BUFFER SIZE 256 for vdev: %d\n",
					    arvif->vdev_id);

			param_id = WMI_VDEV_PARAM_HEOPS_0_31;
			param_value = vif->bss_conf.he_oper.params;
			ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
							    param_id, param_value);
			ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
				   "he oper param: %x set for VDEV: %d\n",
				   param_value, arvif->vdev_id);

			if (ret)
				ath12k_warn(ar->ab, "Failed to set he oper params %x for VDEV %d: %i\n",
					    param_value, arvif->vdev_id, ret);
		}
	}
#endif
	
	if (changed & BSS_CHANGED_ERP_CTS_PROT) {
		u32 cts_prot;

		cts_prot = !!(ieee80211_bss_conf_get_erp_cts_port(info));
		param_id = WMI_VDEV_PARAM_PROTECTION_MODE;

		if (arvif->is_started) {
			ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
							    param_id, cts_prot);
			if (ret)
				ath12k_warn(ar->ab, "Failed to set CTS prot for VDEV: %d\n",
					    arvif->vdev_id);
			else
				ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "Set CTS prot: %d for VDEV: %d\n",
					   cts_prot, arvif->vdev_id);
		} else {
			ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "defer protection mode setup, vdev is not ready yet\n");
		}
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		u32 slottime;

		if (ieee80211_bss_conf_get_erp_short_slot(info))
			slottime = WMI_VDEV_SLOT_TIME_SHORT; /* 9us */

		else
			slottime = WMI_VDEV_SLOT_TIME_LONG; /* 20us */

		param_id = WMI_VDEV_PARAM_SLOT_TIME;
		ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param_id, slottime);
		if (ret)
			ath12k_warn(ar->ab, "Failed to set erp slot for VDEV: %d\n",
				    arvif->vdev_id);
		else
			ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
				   "Set slottime: %d for VDEV: %d\n",
				   slottime, arvif->vdev_id);
	}

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		if (ieee80211_bss_conf_get_erp_short_preamble(info))
			preamble = WMI_VDEV_PREAMBLE_SHORT;
		else
			preamble = WMI_VDEV_PREAMBLE_LONG;

		param_id = WMI_VDEV_PARAM_PREAMBLE;
		ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param_id, preamble);
		if (ret)
			ath12k_warn(ar->ab, "Failed to set preamble for VDEV: %d\n",
				    arvif->vdev_id);
		else
			ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
				   "Set preamble: %d for VDEV: %d\n",
				   preamble, arvif->vdev_id);
	}

	if (changed & BSS_CHANGED_ASSOC) {
		if (ieee80211_bss_conf_get_assoc(info))
			ath12k_bss_assoc(hw, vif, info);
		else
			ath12k_bss_disassoc(hw, vif);
	}

	if (changed & BSS_CHANGED_TXPOWER) {
		ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac vdev_id %d txpower %d\n",
			   arvif->vdev_id, ieee80211_bss_conf_get_txpower(info));

		arvif->txpower = ieee80211_bss_conf_get_txpower(info);
		ath12k_mac_txpower_recalc(ar);
	}

	if (changed & BSS_CHANGED_MCAST_RATE &&
	    !ath12k_mac_vif_chan(arvif->vif, &def)) {
		band = def.chan->band;
		mcast_rate = ieee80211_vif_bss_conf_get_mcast_rate(vif)[band];

		if (mcast_rate > 0)
			rateidx = (u8)(mcast_rate - 1);
		else
			rateidx = (u8)(ffs(ieee80211_vif_bss_conf_get_basic_rates(vif)) - 1);

		if (ar->pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP)
			rateidx += ATH12K_MAC_FIRST_OFDM_RATE_IDX;

		bitrate = ath12k_legacy_rates[rateidx].bitrate;
		hw_value = ath12k_legacy_rates[rateidx].hw_value;

		if (ath12k_mac_bitrate_is_cck(bitrate))
			preamble = WMI_RATE_PREAMBLE_CCK;
		else
			preamble = WMI_RATE_PREAMBLE_OFDM;

		rate = ATH12K_HW_RATE_CODE(hw_value, 0, preamble);

		ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
			   "mac vdev %d mcast_rate %x\n",
			   arvif->vdev_id, rate);

		vdev_param = WMI_VDEV_PARAM_MCAST_DATA_RATE;
		ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    vdev_param, rate);
		if (ret)
			ath12k_warn(ar->ab,
				    "failed to set mcast rate on vdev %i: %d\n",
				    arvif->vdev_id,  ret);

		vdev_param = WMI_VDEV_PARAM_BCAST_DATA_RATE;
		ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    vdev_param, rate);
		if (ret)
			ath12k_warn(ar->ab,
				    "failed to set bcast rate on vdev %i: %d\n",
				    arvif->vdev_id,  ret);
	}

	if (changed & BSS_CHANGED_BASIC_RATES &&
	    !ath12k_mac_vif_chan(arvif->vif, &def))
		ath12k_recalculate_mgmt_rate(ar, vif, &def);

	if (changed & BSS_CHANGED_TWT) {
		if (ieee80211_bss_conf_get_twt_requester(info) ||
            ieee80211_bss_conf_get_twt_responder(info))
			ath12k_wmi_send_twt_enable_cmd(ar, ar->pdev->pdev_id);
		else
			ath12k_wmi_send_twt_disable_cmd(ar, ar->pdev->pdev_id);
	}

	if (changed & BSS_CHANGED_HE_OBSS_PD)
		ath12k_wmi_send_obss_spr_cmd(ar, arvif->vdev_id,
					     ieee80211_bss_conf_get_he_obss_pd(info));

	if (changed & BSS_CHANGED_HE_BSS_COLOR) {
		if (ieee80211_vif_type(vif) == NL80211_IFTYPE_AP) {
#if 0
			ret = ath12k_wmi_obss_color_cfg_cmd(ar,
							    arvif->vdev_id,
							    info->he_bss_color.color,
							    ATH12K_BSS_COLOR_AP_PERIODS,
							    info->he_bss_color.enabled);
			if (ret)
				ath12k_warn(ar->ab, "failed to set bss color collision on vdev %i: %d\n",
					    arvif->vdev_id,  ret);
#endif
		} else if (ieee80211_vif_type(vif) == NL80211_IFTYPE_STATION) {
			ret = ath12k_wmi_send_bss_color_change_enable_cmd(ar,
									  arvif->vdev_id,
									  1);
			if (ret)
				ath12k_warn(ar->ab, "failed to enable bss color change on vdev %i: %d\n",
					    arvif->vdev_id,  ret);
			ret = ath12k_wmi_obss_color_cfg_cmd(ar,
							    arvif->vdev_id,
							    0,
							    ATH12K_BSS_COLOR_STA_PERIODS,
							    1);
			if (ret)
				ath12k_warn(ar->ab, "failed to set bss color collision on vdev %i: %d\n",
					    arvif->vdev_id,  ret);
		}
	}
	
#if 0
	if (changed & BSS_CHANGED_FILS_DISCOVERY ||
	    changed & BSS_CHANGED_UNSOL_BCAST_PROBE_RESP)
		ath12k_mac_fils_discovery(arvif, info);
#endif

	mutex_unlock(&ar->conf_mutex);
}

void __ath12k_mac_scan_finish(struct ath12k *ar)
{
	lockdep_assert_held(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH12K_SCAN_IDLE:
		break;
	case ATH12K_SCAN_RUNNING:
	case ATH12K_SCAN_ABORTING:
		if (!ar->scan.is_roc) {
			bool aborted = (ar->scan.state == ATH12K_SCAN_ABORTING);
			ieee80211_scan_completed(ar->hw, aborted);
		} 
#if 0
		else if (ar->scan.roc_notify) {
			ieee80211_remain_on_channel_expired(ar->hw);
		}
		fallthrough;
#endif
	case ATH12K_SCAN_STARTING:
		ar->scan.state = ATH12K_SCAN_IDLE;
		ar->scan_channel = NULL;
		ar->scan.roc_freq = 0;
		cancel_delayed_work(&ar->scan.timeout);
		complete_all(&ar->scan.completed);
		break;
	}
}

void ath12k_mac_scan_finish(struct ath12k *ar)
{
	spin_lock_bh(&ar->data_lock);
	__ath12k_mac_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);
}

static int ath12k_scan_stop(struct ath12k *ar)
{
	struct ath12k_wmi_scan_cancel_arg arg = {
		.req_type = WLAN_SCAN_CANCEL_SINGLE,
		.scan_id = ATH12K_SCAN_ID,
	};
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	/* TODO: Fill other STOP Params */
	arg.pdev_id = ar->pdev->pdev_id;

	ret = ath12k_wmi_send_scan_stop_cmd(ar, &arg);
	if (ret) {
		ath12k_warn(ar->ab, "failed to stop wmi scan: %d\n", ret);
		goto out;
	}

	ret = wait_for_completion_timeout(&ar->scan.completed, 3 * HZ);
	if (ret == 0) {
		ath12k_warn(ar->ab,
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
	if (ar->scan.state != ATH12K_SCAN_IDLE)
		__ath12k_mac_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);

	return ret;
}

static void ath12k_scan_abort(struct ath12k *ar)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH12K_SCAN_IDLE:
		/* This can happen if timeout worker kicked in and called
		 * abortion while scan completion was being processed.
		 */
		break;
	case ATH12K_SCAN_STARTING:
	case ATH12K_SCAN_ABORTING:
		ath12k_warn(ar->ab, "refusing scan abortion due to invalid scan state: %d\n",
			    ar->scan.state);
		break;
	case ATH12K_SCAN_RUNNING:
		ar->scan.state = ATH12K_SCAN_ABORTING;
		spin_unlock_bh(&ar->data_lock);

		ret = ath12k_scan_stop(ar);
		if (ret)
			ath12k_warn(ar->ab, "failed to abort scan: %d\n", ret);

		spin_lock_bh(&ar->data_lock);
		break;
	}

	spin_unlock_bh(&ar->data_lock);
}

static void ath12k_scan_timeout_work(void *context)
{
	struct ath12k *ar = context;

	mutex_lock(&ar->conf_mutex);
	ath12k_scan_abort(ar);
	mutex_unlock(&ar->conf_mutex);
}

static int ath12k_start_scan(struct ath12k *ar,
			     struct ath12k_wmi_scan_req_arg *arg)
{
	int ret;
	unsigned long time_left;
	unsigned long timeout = 5 * 1000;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath12k_wmi_send_scan_start_cmd(ar, arg);
	if (ret)
		return ret;

	// Add more 5 seconds timeout for 6G scan
    if (ar->supports_6ghz)
        timeout += 5 * 1000;
	
	time_left = wait_for_completion_timeout(&ar->scan.started, timeout);
	if (!time_left) {
		ret = ath12k_scan_stop(ar);
		if (ret)
			ath12k_warn(ar->ab, "failed to stop scan: %d\n", ret);

		return -ETIMEDOUT;
	}

	/* If we failed to start the scan, return error code at
	 * this point.  This is probably due to some issue in the
	 * firmware, but no need to wedge the driver due to that...
	 */
	spin_lock_bh(&ar->data_lock);
	if (ar->scan.state == ATH12K_SCAN_IDLE) {
		spin_unlock_bh(&ar->data_lock);
		return -EINVAL;
	}
	spin_unlock_bh(&ar->data_lock);

	return 0;
}

static int ath12k_mac_op_hw_scan(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_scan_request *hw_req)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ath12k_wmi_scan_req_arg arg = { 0, };
	struct ieee80211_ssid *ssids;
    struct ieee80211_channel **channels;
	int ret = 0;
	u32 i;

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	switch (ar->scan.state) {
	case ATH12K_SCAN_IDLE:
		reinit_completion(&ar->scan.started);
		reinit_completion(&ar->scan.completed);
		ar->scan.state = ATH12K_SCAN_STARTING;
		ar->scan.is_roc = false;
		ar->scan.vdev_id = arvif->vdev_id;
		ret = 0;
		break;
	case ATH12K_SCAN_STARTING:
	case ATH12K_SCAN_RUNNING:
	case ATH12K_SCAN_ABORTING:
		ret = -EBUSY;
		break;
	}
	spin_unlock_bh(&ar->data_lock);

	if (ret)
		goto exit;

	ath12k_wmi_start_scan_init(ar, &arg);
	arg.vdev_id = arvif->vdev_id;
	arg.scan_id = ATH12K_SCAN_ID;

	arg.extraie.len = ieee80211_scan_request_ies_len(hw_req);
	if (arg.extraie.len) {
		arg.extraie.ptr = kzalloc(arg.extraie.len, GFP_KERNEL);
		if (arg.extraie.ptr)
        	memcpy(arg.extraie.ptr, ieee80211_scan_request_ies(hw_req), arg.extraie.len);
	}

	arg.num_ssids = MIN(ieee80211_scan_request_num_ssids(hw_req), ARRAY_LENGTH(arg.ssid));
	if (arg.num_ssids) {
		ssids = ieee80211_scan_request_ssids(hw_req);
        for (i = 0; i < arg.num_ssids; i++) {
            arg.ssid[i].ssid_len = ssids[i].ssid_len;
            memcpy(arg.ssid[i].ssid, ssids[i].ssid, ssids[i].ssid_len);
        }
	} else {
		arg.u_scan_f.scan_flags |= WMI_SCAN_FLAG_PASSIVE;
	}

	arg.num_chan = MIN(ieee80211_scan_request_num_channels(hw_req), ARRAY_LENGTH(arg.chan_list));
	if (arg.num_chan) {
		channels = ieee80211_scan_request_channels(hw_req);
		for (i = 0; i < arg.num_chan; i++)
			arg.chan_list[i] = channels[i]->center_freq;

		ath12k_dbg_dump(ar->ab, ATH12K_DBG_WMI, "chan_list: ",
            arg.chan_list, arg.num_chan * sizeof(arg.chan_list[0]), 0);
	}

	ret = ath12k_start_scan(ar, &arg);
	if (ret) {
		ath12k_warn(ar->ab, "failed to start hw scan: %d\n", ret);
		spin_lock_bh(&ar->data_lock);
		ar->scan.state = ATH12K_SCAN_IDLE;
		spin_unlock_bh(&ar->data_lock);
	}

	/* Add a 200ms margin to account for event/command processing */
	ieee80211_queue_delayed_work(ar->hw, &ar->scan.timeout,
				     msecs_to_jiffies(arg.max_scan_time +
						      ATH12K_MAC_SCAN_TIMEOUT_MSECS));

exit:
	if (arg.extraie.len)
		kfree(arg.extraie.ptr);

	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static void ath12k_mac_op_cancel_hw_scan(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);

	mutex_lock(&ar->conf_mutex);
	ath12k_scan_abort(ar);
	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.timeout);
}

static int ath12k_install_key(struct ath12k_vif *arvif,
			      struct ieee80211_key_conf *key,
			      enum ieee80211_key_cmd cmd,
			      const u8 *macaddr, u32 flags)
{
	int ret;
	struct ath12k *ar = arvif->ar;
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

	if (test_bit(ATH12K_FLAG_HW_CRYPTO_DISABLED, &ar->ab->dev_flags))
		return 0;

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
		ath12k_warn(ar->ab, "cipher %x is not supported\n", key->cipher);
		return -EOPNOTSUPP;
	}

	if (test_bit(ATH12K_FLAG_RAW_MODE, &ar->ab->dev_flags))
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV |
			      IEEE80211_KEY_FLAG_RESERVE_TAILROOM;

install:
	ret = ath12k_wmi_vdev_install_key(arvif->ar, &arg);

	if (ret)
		return ret;

	if (!wait_for_completion_timeout(&ar->install_key_done, 1 * HZ))
		return -ETIMEDOUT;

	if (ether_addr_equal(macaddr, ieee80211_vif_addr(arvif->vif)))
		arvif->key_cipher = key->cipher;

	return ar->install_key_status ? -EINVAL : 0;
}

static int ath12k_clear_peer_keys(struct ath12k_vif *arvif,
				  const u8 *addr)
{
	struct ath12k *ar = arvif->ar;
	struct ath12k_base *ab = ar->ab;
	struct ath12k_peer *peer;
	int first_errno = 0;
	int ret;
	int i;
	u32 flags = 0;

	lockdep_assert_held(&ar->conf_mutex);

	spin_lock_bh(&ab->base_lock);
	peer = ath12k_peer_find(ab, arvif->vdev_id, addr);
	spin_unlock_bh(&ab->base_lock);

	if (!peer)
		return -ENOENT;

	for (i = 0; i < ARRAY_SIZE(peer->keys); i++) {
		if (!peer->keys[i])
			continue;

		/* key flags are not required to delete the key */
		ret = ath12k_install_key(arvif, peer->keys[i],
					 IEEE80211_DISABLE_KEY, addr, flags);
		if (ret < 0 && first_errno == 0)
			first_errno = ret;

		if (ret < 0)
			ath12k_warn(ab, "failed to remove peer key %d: %d\n",
				    i, ret);

		spin_lock_bh(&ab->base_lock);
		peer->keys[i] = NULL;
		spin_unlock_bh(&ab->base_lock);
	}

	return first_errno;
}

static int ath12k_mac_op_set_key(struct ieee80211_hw *hw, enum ieee80211_key_cmd cmd,
				 struct ieee80211_vif *vif, struct ieee80211_sta *sta,
				 struct ieee80211_key_conf *key)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ath12k_peer *peer;
	struct ath12k_sta *arsta;
	const u8 *peer_addr;
	int ret = 0;
	u32 flags = 0;

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "key cipher = %x keyidx = %d\n", 
		key->cipher, key->key_idx);

#if 0	
	/* BIP needs to be done in software */
	if (key->cipher == WLAN_RSN_CIPHER_SUITE_AES_CMAC ||
	    key->cipher == WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128 ||
	    key->cipher == WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256 ||
	    key->cipher == WLAN_RSN_CIPHER_SUITE_BIP_CMAC_256)
		return 1;
#endif

	if (test_bit(ATH12K_FLAG_HW_CRYPTO_DISABLED, &ar->ab->dev_flags))
		return 1;

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

	/* the peer should not disappear in mid-way (unless FW goes awry) since
	 * we already hold conf_mutex. we just make sure its there now.
	 */
	spin_lock_bh(&ab->base_lock);
	peer = ath12k_peer_find(ab, arvif->vdev_id, peer_addr);
	if (peer && cmd == IEEE80211_SET_KEY) {
		ath12k_warn(ab, "flush the fragments cache during key (re)install to ensure all frags in the new frag list belong to the same key.\n");
		ath12k_peer_frags_flush(ar, peer);
	}
	spin_unlock_bh(&ab->base_lock);

	if (!peer) {
		if (cmd == IEEE80211_SET_KEY) {
			ath12k_warn(ab, "cannot install key for non-existent peer %pM\n",
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

	ret = ath12k_install_key(arvif, key, cmd, peer_addr, flags);
	if (ret) {
		ath12k_warn(ab, "ath12k_install_key failed (%d)\n", ret);
		goto exit;
	}

	ret = ath12k_dp_rx_peer_pn_replay_config(arvif, peer_addr, cmd, key);
	if (ret) {
		ath12k_warn(ab, "failed to offload PN replay detection %d\n", ret);
		goto exit;
	}

	spin_lock_bh(&ab->base_lock);
	peer = ath12k_peer_find(ab, arvif->vdev_id, peer_addr);
	if (peer && cmd == IEEE80211_SET_KEY) {
		peer->keys[key->key_idx] = key;
		if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) {
			peer->ucast_keyidx = key->key_idx;
			peer->sec_type = ath12k_dp_tx_get_encrypt_type(key->cipher);
		} else {
			peer->mcast_keyidx = key->key_idx;
			peer->sec_type_grp = ath12k_dp_tx_get_encrypt_type(key->cipher);
		}
	} else if (peer && cmd == IEEE80211_DISABLE_KEY) {
		peer->keys[key->key_idx] = NULL;
		if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
			peer->ucast_keyidx = 0;
		else
			peer->mcast_keyidx = 0;
	} else if (!peer)
		/* impossible unless FW goes crazy */
		ath12k_warn(ab, "peer %pM disappeared!\n", peer_addr);

	if (sta) {
		arsta = ieee80211_sta_get_priv_data(sta);

		switch (key->cipher) {
		case WLAN_RSN_CIPHER_SUITE_TKIP:
		case WLAN_RSN_CIPHER_SUITE_CCMP:
		case WLAN_RSN_CIPHER_SUITE_CCMP_256:
		case WLAN_RSN_CIPHER_SUITE_GCMP:
		case WLAN_RSN_CIPHER_SUITE_GCMP_256:
			if (cmd == IEEE80211_SET_KEY)
				arsta->pn_type = HAL_PN_TYPE_WPA;
			else
				arsta->pn_type = HAL_PN_TYPE_NONE;
			break;
		default:
			arsta->pn_type = HAL_PN_TYPE_NONE;
			break;
		}
	}

	spin_unlock_bh(&ab->base_lock);

exit:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static u8
ath12k_mac_bitrate_mask_num_vht_rates(struct ath12k *ar,
				      enum nl80211_band band,
				      const struct ieee80211_bitrate_mask *mask)
{
	u8 num_rates = 0;
	u8 i;

	for (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++)
		num_rates += (u8)hweight16(mask->control[band].vht_mcs[i]);

	return num_rates;
}

static int
ath12k_mac_set_peer_vht_fixed_rate(struct ath12k_vif *arvif,
				   struct ieee80211_sta *sta,
				   const struct ieee80211_bitrate_mask *mask,
				   enum nl80211_band band)
{
	struct ath12k *ar = arvif->ar;
	u8 vht_rate, nss;
	u32 rate_code;
	int ret;
	u8 i;

	lockdep_assert_held(&ar->conf_mutex);

	nss = 0;

	for (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) {
		if (hweight16(mask->control[band].vht_mcs[i]) == 1) {
			nss = i + 1;
			vht_rate = (u8)(ffs(mask->control[band].vht_mcs[i]) - 1);
		}
	}

	if (!nss) {
		ath12k_warn(ar->ab, "No single VHT Fixed rate found to set for %pM",
			    ieee80211_sta_addr(sta));
		return -EINVAL;
	}

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
		   "Setting Fixed VHT Rate for peer %pM. Device will not switch to any other selected rates",
		   ieee80211_sta_addr(sta));

	rate_code = ATH12K_HW_RATE_CODE(vht_rate, nss - 1,
					WMI_RATE_PREAMBLE_VHT);
	ret = ath12k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta),
					arvif->vdev_id,
					WMI_PEER_PARAM_FIXED_RATE,
					rate_code);
	if (ret)
		ath12k_warn(ar->ab,
			    "failed to update STA %pM Fixed Rate %d: %d\n",
			     ieee80211_sta_addr(sta), rate_code, ret);

	return ret;
}

static int ath12k_station_assoc(struct ath12k *ar,
				struct ieee80211_vif *vif,
				struct ieee80211_sta *sta,
				bool reassoc)
{
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ieee80211_he_6ghz_cap *sta_6ghz_cap;
	struct ath12k_wmi_peer_assoc_arg peer_arg;
	int ret = 0;
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	struct ieee80211_bitrate_mask *mask;
	u8 num_vht_rates;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath12k_mac_vif_chan(vif, &def)))
		return -EPERM;

	band = def.chan->band;
	mask = &arvif->bitrate_mask;

	ath12k_peer_assoc_prepare(ar, vif, sta, &peer_arg, reassoc);

	ret = ath12k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
	if (ret) {
		ath12k_warn(ar->ab, "failed to run peer assoc for STA %pM vdev %i: %d\n",
			    ieee80211_sta_addr(sta), arvif->vdev_id, ret);
		return ret;
	}

	if (!wait_for_completion_timeout(&ar->peer_assoc_done, 1 * HZ)) {
		ath12k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %i\n",
			    ieee80211_sta_addr(sta), arvif->vdev_id);
		return -ETIMEDOUT;
	}

	num_vht_rates = ath12k_mac_bitrate_mask_num_vht_rates(ar, band, mask);

	/* If single VHT rate is configured (by set_bitrate_mask()),
	 * peer_assoc will disable VHT. This is now enabled by a peer specific
	 * fixed param.
	 * Note that all other rates and NSS will be disabled for this peer.
	 */
	if (ieee80211_sta_get_vht_cap(sta)->vht_supported && num_vht_rates == 1) {
		ret = ath12k_mac_set_peer_vht_fixed_rate(arvif, sta, mask,
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
	ret = ath12k_setup_peer_smps(ar, arvif, ieee80211_sta_addr(sta),
				     ieee80211_sta_get_ht_cap(sta), sta_6ghz_cap->cap);
	if (ret) {
		ath12k_warn(ar->ab, "failed to setup peer SMPS for vdev %d: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	if (!ieee80211_sta_get_wme(sta)) {
		arvif->num_legacy_stations++;
		ret = ath12k_recalc_rtscts_prot(arvif);
		if (ret)
			return ret;
	}

	if (ieee80211_sta_get_wme(sta) &&
        ieee80211_sta_get_uapsd_queues(sta)) {
		ret = ath12k_peer_assoc_qos_ap(ar, arvif, sta);
		if (ret) {
			ath12k_warn(ar->ab, "failed to set qos params for STA %pM for vdev %i: %d\n",
				    ieee80211_sta_addr(sta), arvif->vdev_id, ret);
			return ret;
		}
	}

	return 0;
}

static int ath12k_station_disassoc(struct ath12k *ar,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta)
{
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	if (!ieee80211_sta_get_wme(sta)) {
		arvif->num_legacy_stations--;
		ret = ath12k_recalc_rtscts_prot(arvif);
		if (ret)
			return ret;
	}

	ret = ath12k_clear_peer_keys(arvif, ieee80211_sta_addr(sta));
	if (ret) {
		ath12k_warn(ar->ab, "failed to clear all peer keys for vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}
	return 0;
}

static void ath12k_sta_rc_update_wk(void *context)
{
	struct ath12k *ar;
	struct ath12k_vif *arvif;
	struct ath12k_sta *arsta;
	struct ieee80211_sta *sta;
	struct ieee80211_chan_def def;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	const u16 *vht_mcs_mask;
	u32 changed, bw, nss, smps;
	int err, num_vht_rates;
	const struct ieee80211_bitrate_mask *mask;
	struct ath12k_wmi_peer_assoc_arg peer_arg;

	arsta = context;
	sta = ieee80211_sta_from_drv_priv(arsta);
	arvif = arsta->arvif;
	ar = arvif->ar;

	if (WARN_ON(ath12k_mac_vif_chan(arvif->vif, &def)))
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
	nss = min(nss, max(ath12k_mac_max_ht_nss(ht_mcs_mask),
			   ath12k_mac_max_vht_nss(vht_mcs_mask)));

	if (changed & IEEE80211_RC_CHANGED_BW) {
		err = ath12k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta), arvif->vdev_id,
						WMI_PEER_CHWIDTH, bw);
		if (err)
			ath12k_warn(ar->ab, "failed to update STA %pM peer bw %d: %d\n",
				    ieee80211_sta_addr(sta), bw, err);
	}

	if (changed & IEEE80211_RC_CHANGED_NSS) {
		ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac update sta %pM nss %d\n",
			   ieee80211_sta_addr(sta), nss);

		err = ath12k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta), arvif->vdev_id,
						WMI_PEER_NSS, nss);
		if (err)
			ath12k_warn(ar->ab, "failed to update STA %pM nss %d: %d\n",
				    ieee80211_sta_addr(sta), nss, err);
	}

	if (changed & IEEE80211_RC_CHANGED_SMPS) {
		ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac update sta %pM smps %d\n",
			   ieee80211_sta_addr(sta), smps);

		err = ath12k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta), arvif->vdev_id,
						WMI_PEER_MIMO_PS_STATE, smps);
		if (err)
			ath12k_warn(ar->ab, "failed to update STA %pM smps %d: %d\n",
				    ieee80211_sta_addr(sta), smps, err);
	}

	if (changed & IEEE80211_RC_CHANGED_SUPP_RATES) {
		mask = &arvif->bitrate_mask;
		num_vht_rates = ath12k_mac_bitrate_mask_num_vht_rates(ar, band,
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
			ath12k_mac_set_peer_vht_fixed_rate(arvif, sta, mask,
							   band);
		} else {
			/* If the peer is non-VHT or no fixed VHT rate
			 * is provided in the new bitrate mask we set the
			 * other rates using peer_assoc command.
			 */
			ath12k_peer_assoc_prepare(ar, arvif->vif, sta,
						  &peer_arg, true);

			err = ath12k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
			if (err)
				ath12k_warn(ar->ab, "failed to run peer assoc for STA %pM vdev %i: %d\n",
					    ieee80211_sta_addr(sta), arvif->vdev_id, err);

			if (!wait_for_completion_timeout(&ar->peer_assoc_done, 1 * HZ))
				ath12k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %i\n",
					    ieee80211_sta_addr(sta), arvif->vdev_id);
		}
	}

	mutex_unlock(&ar->conf_mutex);
}

static int ath12k_mac_inc_num_stations(struct ath12k_vif *arvif,
				       struct ieee80211_sta *sta)
{
	struct ath12k *ar = arvif->ar;

	lockdep_assert_held(&ar->conf_mutex);

	if (arvif->vdev_type == WMI_VDEV_TYPE_STA && !ieee80211_sta_get_tdls(sta))
		return 0;

	if (ar->num_stations >= ar->max_num_stations)
		return -ENOBUFS;

	ar->num_stations++;

	return 0;
}

static void ath12k_mac_dec_num_stations(struct ath12k_vif *arvif,
					struct ieee80211_sta *sta)
{
	struct ath12k *ar = arvif->ar;

	lockdep_assert_held(&ar->conf_mutex);

	if (arvif->vdev_type == WMI_VDEV_TYPE_STA && !ieee80211_sta_get_tdls(sta))
		return;

	ar->num_stations--;
}

static int ath12k_mac_station_add(struct ath12k *ar,
				  struct ieee80211_vif *vif,
				  struct ieee80211_sta *sta)
{
	struct ath12k_base *ab = ar->ab;
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ath12k_sta *arsta = ieee80211_sta_get_priv_data(sta);
	struct ath12k_wmi_peer_create_arg peer_param;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath12k_mac_inc_num_stations(arvif, sta);
	if (ret) {
		ath12k_warn(ab, "refusing to associate station: too many connected already (%d)\n",
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

	ret = ath12k_peer_create(ar, arvif, sta, &peer_param);
	if (ret) {
		ath12k_warn(ab, "Failed to add peer: %pM for VDEV: %d\n",
			    ieee80211_sta_addr(sta), arvif->vdev_id);
		goto free_peer;
	}

	ath12k_dbg(ab, ATH12K_DBG_MAC, "Added peer: %pM for VDEV: %d\n",
		   ieee80211_sta_addr(sta), arvif->vdev_id);

#if 0
	if (ieee80211_vif_is_mesh(vif)) {
		ret = ath12k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta),
						arvif->vdev_id,
						WMI_PEER_USE_4ADDR, 1);
		if (ret) {
			ath12k_warn(ab, "failed to STA %pM 4addr capability: %d\n",
				    ieee80211_sta_addr(sta), ret);
			goto free_peer;
		}
	}
#endif
	
	ret = ath12k_dp_peer_setup(ar, arvif->vdev_id, ieee80211_sta_addr(sta));
	if (ret) {
		ath12k_warn(ab, "failed to setup dp for peer %pM on vdev %i (%d)\n",
			    ieee80211_sta_addr(sta), arvif->vdev_id, ret);
		goto free_peer;
	}

	if (ab->hw_params->vdev_start_delay &&
	    !arvif->is_started &&
	    arvif->vdev_type != WMI_VDEV_TYPE_AP) {
		ret = ath12k_start_vdev_delay(ar->hw, vif);
		if (ret) {
			ath12k_warn(ab, "failed to delay vdev start: %d\n", ret);
			goto free_peer;
		}
	}

	return 0;

free_peer:
	ath12k_peer_delete(ar, arvif->vdev_id, ieee80211_sta_addr(sta));
dec_num_station:
	ath12k_mac_dec_num_stations(arvif, sta);
exit:
	return ret;
}

static int ath12k_mac_op_sta_state(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta,
				   enum ieee80211_sta_state old_state,
				   enum ieee80211_sta_state new_state)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ath12k_sta *arsta = ieee80211_sta_get_priv_data(sta);
	struct ath12k_peer *peer;
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
		init_work(&arsta->update_wk, ath12k_sta_rc_update_wk, ar);

		ret = ath12k_mac_station_add(ar, vif, sta);
		if (ret)
			ath12k_warn(ar->ab, "Failed to add station: %pM for VDEV: %d\n",
				    ieee80211_sta_addr(sta), arvif->vdev_id);
	} else if ((old_state == IEEE80211_STA_NONE &&
		    new_state == IEEE80211_STA_NOTEXIST)) {
		bool skip_peer_delete = ar->ab->hw_params->vdev_start_delay &&
			ieee80211_vif_type(vif) == NL80211_IFTYPE_STATION;
		
		ath12k_dp_peer_cleanup(ar, arvif->vdev_id, ieee80211_sta_addr(sta));

		if (!skip_peer_delete) {
			ret = ath12k_peer_delete(ar, arvif->vdev_id, ieee80211_sta_addr(sta));
			if (ret)
				ath12k_warn(ar->ab, "Failed to delete peer: %pM for VDEV: %d\n",
					    ieee80211_sta_addr(sta), arvif->vdev_id);
			else
				ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "Removed peer: %pM for VDEV: %d\n",
					   ieee80211_sta_addr(sta), arvif->vdev_id);
		}

		ath12k_mac_dec_num_stations(arvif, sta);
		spin_lock_bh(&ar->ab->base_lock);
		peer = ath12k_peer_find(ar->ab, arvif->vdev_id, ieee80211_sta_addr(sta));
		if (skip_peer_delete && peer) {
			peer->sta = NULL;
		} else if (peer && peer->sta == sta) {
			ath12k_warn(ar->ab, "Found peer entry %pM n vdev %i after it was supposedly removed\n",
				    ieee80211_vif_addr(vif), arvif->vdev_id);
			peer->sta = NULL;
			list_del(&peer->list);
			kfree(peer);
			ar->num_peers--;
		}
		spin_unlock_bh(&ar->ab->base_lock);

		kfree(arsta->rx_stats);
		arsta->rx_stats = NULL;
	} else if (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC &&
		   (ieee80211_vif_type(vif) == NL80211_IFTYPE_AP ||
		    ieee80211_vif_type(vif) == NL80211_IFTYPE_MESH_POINT ||
		    ieee80211_vif_type(vif) == NL80211_IFTYPE_ADHOC)) {
		ret = ath12k_station_assoc(ar, vif, sta, false);
		if (ret)
			ath12k_warn(ar->ab, "Failed to associate station: %pM\n",
				    ieee80211_sta_addr(sta));
	} else if (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTHORIZED) {
		spin_lock_bh(&ar->ab->base_lock);

		peer = ath12k_peer_find(ar->ab, arvif->vdev_id, ieee80211_sta_addr(sta));
		if (peer)
			peer->is_authorized = true;

		spin_unlock_bh(&ar->ab->base_lock);

		if (ieee80211_vif_type(vif) == NL80211_IFTYPE_STATION && arvif->is_up) {
			ret = ath12k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta),
							arvif->vdev_id,
							WMI_PEER_AUTHORIZE,
							1);
			if (ret)
				ath12k_warn(ar->ab, "Unable to authorize peer %pM vdev %d: %d\n",
					    ieee80211_sta_addr(sta), arvif->vdev_id, ret);
		}
	} else if (old_state == IEEE80211_STA_AUTHORIZED &&
		   new_state == IEEE80211_STA_ASSOC) {
		spin_lock_bh(&ar->ab->base_lock);

		peer = ath12k_peer_find(ar->ab, arvif->vdev_id, ieee80211_sta_addr(sta));
		if (peer)
			peer->is_authorized = false;

		spin_unlock_bh(&ar->ab->base_lock);
	} else if (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTH &&
		   (ieee80211_vif_type(vif) == NL80211_IFTYPE_AP ||
		    ieee80211_vif_type(vif) == NL80211_IFTYPE_MESH_POINT ||
		    ieee80211_vif_type(vif) == NL80211_IFTYPE_ADHOC)) {
		ret = ath12k_station_disassoc(ar, vif, sta);
		if (ret)
			ath12k_warn(ar->ab, "Failed to disassociate station: %pM\n",
				    ieee80211_sta_addr(sta));
	}

	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static int ath12k_mac_op_sta_set_txpwr(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif,
				       struct ieee80211_sta *sta)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
    struct ieee80211_sta_txpwr *sta_txpwr = ieee80211_sta_get_txpwr(sta);
	int ret = 0;
	s16 txpwr;

	if (sta_txpwr->type == NL80211_TX_POWER_AUTOMATIC) {
		txpwr = 0;
	} else {
		txpwr = sta_txpwr->type;
		if (!txpwr)
			return -EINVAL;
	}

	if (txpwr > ATH12K_TX_POWER_MAX_VAL || txpwr < ATH12K_TX_POWER_MIN_VAL)
		return -EINVAL;

	mutex_lock(&ar->conf_mutex);

	ret = ath12k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta), arvif->vdev_id,
					WMI_PEER_USE_FIXED_PWR, txpwr);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set tx power for station ret: %d\n",
			    ret);
		goto out;
	}

out:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static void ath12k_mac_op_sta_rc_update(struct ieee80211_hw *hw,
					struct ieee80211_vif *vif,
					struct ieee80211_sta *sta,
					u32 changed)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_sta *arsta = ieee80211_sta_get_priv_data(sta);
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ath12k_peer *peer;
	u32 bw, smps;

	spin_lock_bh(&ar->ab->base_lock);

	peer = ath12k_peer_find(ar->ab, arvif->vdev_id, ieee80211_sta_addr(sta));
	if (!peer) {
		spin_unlock_bh(&ar->ab->base_lock);
		ath12k_warn(ar->ab, "mac sta rc update failed to find peer %pM on vdev %i\n",
			    ieee80211_sta_addr(sta), arvif->vdev_id);
		return;
	}

	spin_unlock_bh(&ar->ab->base_lock);
	
	ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
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
			ath12k_warn(ar->ab, "Invalid bandwidth %d in rc update for %pM\n",
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
			ath12k_warn(ar->ab, "Invalid smps %d in sta rc update for %pM\n",
				    ieee80211_sta_get_smps_mode(sta), ieee80211_sta_addr(sta));
			smps = WMI_PEER_SMPS_PS_NONE;
			break;
		}

		arsta->smps = smps;
	}

	arsta->changed |= changed;

	spin_unlock_bh(&ar->data_lock);

	ieee80211_queue_work(hw, &arsta->update_wk);
}

static int ath12k_conf_tx_uapsd(struct ath12k *ar, struct ieee80211_vif *vif,
				u16 ac, bool enable)
{
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
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

	ret = ath12k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
					  WMI_STA_PS_PARAM_UAPSD,
					  arvif->u.sta.uapsd);
	if (ret) {
		ath12k_warn(ar->ab, "could not set uapsd params %d\n", ret);
		goto exit;
	}

	if (arvif->u.sta.uapsd)
		value = WMI_STA_PS_RX_WAKE_POLICY_POLL_UAPSD;
	else
		value = WMI_STA_PS_RX_WAKE_POLICY_WAKE;

	ret = ath12k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
					  WMI_STA_PS_PARAM_RX_WAKE_POLICY,
					  value);
	if (ret)
		ath12k_warn(ar->ab, "could not set rx wake param %d\n", ret);

exit:
	return ret;
}

static int ath12k_mac_op_conf_tx(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif, u16 ac,
				 const struct ieee80211_tx_queue_params *params)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
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

	ret = ath12k_wmi_send_wmm_update_cmd(ar, arvif->vdev_id,
					     &arvif->wmm_params);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set wmm params: %d\n", ret);
		goto exit;
	}

	ret = ath12k_conf_tx_uapsd(ar, vif, ac, params->uapsd);

	if (ret)
		ath12k_warn(ar->ab, "failed to set sta uapsd: %d\n", ret);

exit:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static struct ieee80211_sta_ht_cap
ath12k_create_ht_cap(struct ath12k *ar, u32 ar_ht_cap, u32 rate_cap_rx_chainmask)
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

static int ath12k_mac_set_txbf_conf(struct ath12k_vif *arvif)
{
	u32 value = 0;
	struct ath12k *ar = arvif->ar;
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

	return ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					     vdev_param, value);
}

static void ath12k_set_vht_txbf_cap(struct ath12k *ar, u32 *vht_cap)
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
		sound_dim &= IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK;
		*vht_cap |= sound_dim;
	}

	/* Use the STS advertised by FW unless SU Beamformee is not supported*/
	if (!subfee)
		*vht_cap &= ~(IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK);
}

static struct ieee80211_sta_vht_cap
ath12k_create_vht_cap(struct ath12k *ar, u32 rate_cap_tx_chainmask,
		      u32 rate_cap_rx_chainmask)
{
	struct ieee80211_sta_vht_cap vht_cap = {0};
	u16 txmcs_map, rxmcs_map;
	int i;

	vht_cap.vht_supported = 1;
	vht_cap.cap = ar->pdev->cap.vht_cap;

	ath12k_set_vht_txbf_cap(ar, &vht_cap.cap);

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

static void ath12k_mac_setup_ht_vht_cap(struct ath12k *ar,
					struct ath12k_pdev_cap *cap,
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
		band->ht_cap = ath12k_create_ht_cap(ar, ht_cap,
						    rate_cap_rx_chainmask);
	}

	if (cap->supported_bands & WMI_HOST_WLAN_5G_CAP &&
	    (ar->ab->hw_params->single_pdev_only ||
	     !ar->supports_6ghz)) {
		band = &ar->mac.sbands[NL80211_BAND_5GHZ];
		ht_cap = cap->band[NL80211_BAND_5GHZ].ht_cap_info;
		if (ht_cap_info)
			*ht_cap_info = ht_cap;
		band->ht_cap = ath12k_create_ht_cap(ar, ht_cap,
						    rate_cap_rx_chainmask);
		band->vht_cap = ath12k_create_vht_cap(ar, rate_cap_tx_chainmask,
						      rate_cap_rx_chainmask);
	}
}

static int ath12k_check_chain_mask(struct ath12k *ar, u32 ant, bool is_tx_ant)
{
	/* TODO: Check the request chainmask against the supported
	 * chainmask table which is advertised in extented_service_ready event
	 */

	return 0;
}

static void ath12k_gen_ppe_thresh(struct ath12k_wmi_ppe_threshold_arg *fw_ppet,
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
ath12k_mac_filter_he_cap_mesh(struct ieee80211_he_capabilities *he_cap_elem)
{
	u8 m;

	m = IEEE80211_HEMAC_CAP0_TWT_RES |
	    IEEE80211_HEMAC_CAP0_TWT_REQ;
	he_cap_elem->mac_cap_info[0] &= ~m;

	m = IEEE80211_HEMAC_CAP2_TRS |
	    IEEE80211_HEMAC_CAP2_BCAST_TWT |
	    IEEE80211_HEMAC_CAP2_MU_CASCADING;
	he_cap_elem->mac_cap_info[2] &= ~m;

	m = IEEE80211_HEMAC_CAP3_FLEX_TWT_SCHED |
	    IEEE80211_HEMAC_CAP2_BCAST_TWT |
	    IEEE80211_HEMAC_CAP2_MU_CASCADING;
	he_cap_elem->mac_cap_info[3] &= ~m;

	m = IEEE80211_HEMAC_CAP4_BSRP_BQRP_A_MPDU_AGG |
	    IEEE80211_HEMAC_CAP4_BQR;
	he_cap_elem->mac_cap_info[4] &= ~m;
	
	m = IEEE80211_HEMAC_CAP5_SUBCHAN_SELECTIVE_TRANSMISSION |
	    IEEE80211_HEMAC_CAP5_UL_2x996_TONE_RU |
	    IEEE80211_HEMAC_CAP5_PUNCTURED_SOUNDING |
	    IEEE80211_HEMAC_CAP5_HT_VHT_TRIG_FRAME_RX;
	he_cap_elem->mac_cap_info[5] &= ~m;

	m = IEEE80211_HEPHY_CAP2_UL_MU_FULL_MU_MIMO |
	    IEEE80211_HEPHY_CAP2_UL_MU_PARTIAL_MU_MIMO;
	he_cap_elem->phy_cap_info[2] &= ~m;

	m = IEEE80211_HEPHY_CAP3_RX_HE_MU_PPDU_FROM_NON_AP_STA |
	    IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_TX_MASK |
	    IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_RX_MASK;
	he_cap_elem->phy_cap_info[3] &= ~m;

	m = IEEE80211_HEPHY_CAP4_MU_BEAMFORMER;
	he_cap_elem->phy_cap_info[4] &= ~m;

	m = IEEE80211_HEPHY_CAP5_NG16_MU_FEEDBACK;
	he_cap_elem->phy_cap_info[5] &= ~m;

	m = IEEE80211_HEPHY_CAP6_CODEBOOK_SIZE_75_MU |
	    IEEE80211_HEPHY_CAP6_TRIG_MU_BEAMFORMER_FB |
	    IEEE80211_HEPHY_CAP6_TRIG_CQI_FB |
	    IEEE80211_HEPHY_CAP6_PARTIAL_BANDWIDTH_DL_MUMIMO;
	he_cap_elem->phy_cap_info[6] &= ~m;

	m = IEEE80211_HEPHY_CAP7_SRP_BASED_SR |
	    IEEE80211_HEPHY_CAP7_POWER_BOOST_FACTOR_AR |
	    IEEE80211_HEPHY_CAP7_STBC_TX_ABOVE_80MHZ |
	    IEEE80211_HEPHY_CAP7_STBC_RX_ABOVE_80MHZ;
	he_cap_elem->phy_cap_info[7] &= ~m;

	m = IEEE80211_HEPHY_CAP8_HE_ER_SU_PPDU_4XLTF_AND_08_US_GI |
	    IEEE80211_HEPHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
	    IEEE80211_HEPHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
	    IEEE80211_HEPHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU;
	he_cap_elem->phy_cap_info[8] &= ~m;

	m = IEEE80211_HEPHY_CAP9_LONGER_THAN_16_SIGB_OFDM_SYM |
	    IEEE80211_HEPHY_CAP9_NON_TRIGGERED_CQI_FEEDBACK |
	    IEEE80211_HEPHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU |
	    IEEE80211_HEPHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU |
	    IEEE80211_HEPHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_COMP_SIGB |
	    IEEE80211_HEPHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_NON_COMP_SIGB;
	he_cap_elem->phy_cap_info[9] &= ~m;
}

static __le16 ath12k_mac_setup_he_6ghz_cap(struct ath12k_pdev_cap *pcap,
					   struct ath12k_band_cap *bcap)
{
	u8 val;

	bcap->he_6ghz_capa = IEEE80211_HTCAP_MPDU_DENSITY_NONE;
	if (bcap->ht_cap_info & WMI_HT_CAP_DYNAMIC_SMPS)
		bcap->he_6ghz_capa |=
			u32_encode_bits(WLAN_HTCAP_SM_PS_DYNAMIC,
					IEEE80211_HE_6GHZCAP_SM_PS);
	else
		bcap->he_6ghz_capa |=
			u32_encode_bits(WLAN_HTCAP_SM_PS_DISABLED,
					IEEE80211_HE_6GHZCAP_SM_PS);
	val = (u8)u32_get_bits(pcap->vht_cap,
			   IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK);
	bcap->he_6ghz_capa |=
		u32_encode_bits(val, IEEE80211_HE_6GHZCAP_MAX_AMPDU_LEN_EXP);
	val = (u8)u32_get_bits(pcap->vht_cap,
			   IEEE80211_VHTCAP_MAX_MPDU_MASK);
	bcap->he_6ghz_capa |=
		u32_encode_bits(val, IEEE80211_HE_6GHZCAP_MAX_MPDU_LEN);
	if (pcap->vht_cap & IEEE80211_VHTCAP_RX_ANTENNA_PATTERN)
		bcap->he_6ghz_capa |= IEEE80211_HE_6GHZCAP_RX_ANTPAT_CONS;
	if (pcap->vht_cap & IEEE80211_VHTCAP_TX_ANTENNA_PATTERN)
		bcap->he_6ghz_capa |= IEEE80211_HE_6GHZCAP_TX_ANTPAT_CONS;

	return cpu_to_le16(bcap->he_6ghz_capa);
}

static u16 ath12k_mac_copy_he_cap(struct ath12k *ar,
				  struct ath12k_pdev_cap *cap,
				  struct ieee80211_sband_iftype_data *data,
				  int band)
{
	u16 i, idx = 0;

	for (i = 0; i < NUM_NL80211_IFTYPES; i++) {
		struct ieee80211_sta_he_cap *he_cap = &data[idx].he_cap;
		struct ath12k_band_cap *band_cap = &cap->band[band];
		struct ieee80211_he_capabilities *he_cap_elem =
				&he_cap->he_capabilities;

		switch (i) {
		case NL80211_IFTYPE_STATION:
		case NL80211_IFTYPE_AP:
		case NL80211_IFTYPE_MESH_POINT:
			break;

		default:
			continue;
		}

		data[idx].types_mask = BIT(i);
		he_cap->he_supported = true;
		memcpy(he_cap_elem->mac_cap_info, band_cap->he_cap_info,
		       sizeof(he_cap_elem->mac_cap_info));
		memcpy(he_cap_elem->phy_cap_info, band_cap->he_cap_phy_info,
		       sizeof(he_cap_elem->phy_cap_info));

		he_cap_elem->mac_cap_info[1] &=
			IEEE80211_HEMAC_CAP1_TF_MAC_PAD_DUR_MASK;

		he_cap_elem->phy_cap_info[5] &=
			~IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_MASK;
		he_cap_elem->phy_cap_info[5] &=
			~IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK;
		he_cap_elem->phy_cap_info[5] |= ar->num_tx_chains - 1;

		switch (i) {
		case NL80211_IFTYPE_AP:
			he_cap_elem->phy_cap_info[3] &=
				~IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_TX_MASK;
			he_cap_elem->phy_cap_info[9] |=
				IEEE80211_HEPHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU;
			break;
		case NL80211_IFTYPE_STATION:
			he_cap_elem->mac_cap_info[0] &=
				~IEEE80211_HEMAC_CAP0_TWT_RES;
			he_cap_elem->mac_cap_info[0] |=
				IEEE80211_HEMAC_CAP0_TWT_REQ;
			he_cap_elem->phy_cap_info[9] |=
				IEEE80211_HEPHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU;
			break;
		case NL80211_IFTYPE_MESH_POINT:
			ath12k_mac_filter_he_cap_mesh(he_cap_elem);
			break;
		}

		he_cap->he_mcs_nss_supp.he_rx_mcs_80 =
			cpu_to_le16(band_cap->he_mcs & 0xffff);
		he_cap->he_mcs_nss_supp.he_tx_mcs_80 =
			cpu_to_le16(band_cap->he_mcs & 0xffff);
		he_cap->he_mcs_nss_supp.he_rx_mcs_160 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
		he_cap->he_mcs_nss_supp.he_tx_mcs_160 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
		he_cap->he_mcs_nss_supp.he_rx_mcs_80p80 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
		he_cap->he_mcs_nss_supp.he_tx_mcs_80p80 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);

		memset(he_cap->ppe_thres, 0, sizeof(he_cap->ppe_thres));
		if (he_cap_elem->phy_cap_info[6] &
		    IEEE80211_HEPHY_CAP6_PPE_THRESHOLD_PRESENT)
			ath12k_gen_ppe_thresh(&band_cap->he_ppet,
					      he_cap->ppe_thres);

		if (band == NL80211_BAND_6GHZ) {
			data[idx].he_6ghz_cap.cap =
				ath12k_mac_setup_he_6ghz_cap(cap, band_cap);
		}
		idx++;
	}

	return idx;
}

static void ath12k_mac_setup_he_cap(struct ath12k *ar,
				    struct ath12k_pdev_cap *cap)
{
	struct ieee80211_supported_band *band;
	u16 count;

	if (cap->supported_bands & WMI_HOST_WLAN_2G_CAP) {
		count = ath12k_mac_copy_he_cap(ar, cap,
					       ar->mac.iftype[NL80211_BAND_2GHZ],
					       NL80211_BAND_2GHZ);
		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		band->iftype_data = ar->mac.iftype[NL80211_BAND_2GHZ];
		band->n_iftype_data = count;
	}

	if (cap->supported_bands & WMI_HOST_WLAN_5G_CAP) {
		count = ath12k_mac_copy_he_cap(ar, cap,
					       ar->mac.iftype[NL80211_BAND_5GHZ],
					       NL80211_BAND_5GHZ);
		band = &ar->mac.sbands[NL80211_BAND_5GHZ];
		band->iftype_data = ar->mac.iftype[NL80211_BAND_5GHZ];
		band->n_iftype_data = count;
	}

	if (cap->supported_bands & WMI_HOST_WLAN_5G_CAP &&
	    ar->supports_6ghz) {
		count = ath12k_mac_copy_he_cap(ar, cap,
					       ar->mac.iftype[NL80211_BAND_6GHZ],
					       NL80211_BAND_6GHZ);
		band = &ar->mac.sbands[NL80211_BAND_6GHZ];
		band->iftype_data = ar->mac.iftype[NL80211_BAND_6GHZ];
		band->n_iftype_data = count;
	}
}

static int __ath12k_set_antenna(struct ath12k *ar, u32 tx_ant, u32 rx_ant)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	if (ath12k_check_chain_mask(ar, tx_ant, true))
		return -EINVAL;

	if (ath12k_check_chain_mask(ar, rx_ant, false))
		return -EINVAL;

	ar->cfg_tx_chainmask = (u8)tx_ant;
	ar->cfg_rx_chainmask = (u8)rx_ant;

	if (ar->state != ATH12K_STATE_ON &&
	    ar->state != ATH12K_STATE_RESTARTED)
		return 0;

	ret = ath12k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_TX_CHAIN_MASK,
					tx_ant, ar->pdev->pdev_id);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set tx-chainmask: %d, req 0x%x\n",
			    ret, tx_ant);
		return ret;
	}

	ar->num_tx_chains = get_num_chains(tx_ant);

	ret = ath12k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_RX_CHAIN_MASK,
					rx_ant, ar->pdev->pdev_id);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set rx-chainmask: %d, req 0x%x\n",
			    ret, rx_ant);
		return ret;
	}

	ar->num_rx_chains = get_num_chains(rx_ant);

	/* Reload HT/VHT/HE capability */
	ath12k_mac_setup_ht_vht_cap(ar, &ar->pdev->cap, NULL);
	ath12k_mac_setup_he_cap(ar, &ar->pdev->cap);

	return 0;
}

int ath12k_mac_tx_mgmt_pending_free(int buf_id, void *skb, void *ctx)
{
	struct sk_buff *msdu = skb;
	struct ieee80211_tx_info *info;
	struct ath12k *ar = ctx;
	struct ath12k_base *ab = ar->ab;

	spin_lock_bh(&ar->txmgmt_idr_lock);
	idr_remove(&ar->txmgmt_idr, buf_id);
	spin_unlock_bh(&ar->txmgmt_idr_lock);
	dma_unmap_single(ab->dev, ATH12K_SKB_CB(msdu)->paddr, ATH12K_SKB_CB(msdu)->paddr_mapping_addr,
		msdu->len, DMA_TO_DEVICE);

	info = IEEE80211_SKB_CB(msdu);
	memset(&info->u.status, 0, sizeof(info->u.status));

	ieee80211_free_txskb(ar->hw, msdu);

	return 0;
}

static int ath12k_mac_vif_txmgmt_idr_remove(int buf_id, void *skb, void *ctx)
{
	struct ieee80211_vif *vif = ctx;
	struct ath12k_skb_cb *skb_cb = ATH12K_SKB_CB((struct sk_buff *)skb);
	struct sk_buff *msdu = skb;
	struct ath12k *ar = skb_cb->ar;
	struct ath12k_base *ab = ar->ab;

	if (skb_cb->vif == vif) {
		spin_lock_bh(&ar->txmgmt_idr_lock);
		idr_remove(&ar->txmgmt_idr, buf_id);
		spin_unlock_bh(&ar->txmgmt_idr_lock);
		dma_unmap_single(ab->dev, skb_cb->paddr, skb_cb->paddr_mapping_addr,
			msdu->len, DMA_TO_DEVICE);
	}

	return 0;
}

static int ath12k_mac_mgmt_tx_wmi(struct ath12k *ar, struct ath12k_vif *arvif,
				  struct sk_buff *skb)
{
	struct ath12k_base *ab = ar->ab;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_tx_info *info;
	dma_addr_t paddr;
	void *paddr_mapping_addr;
	int buf_id;
	int ret;

	spin_lock_bh(&ar->txmgmt_idr_lock);
	buf_id = idr_alloc(&ar->txmgmt_idr, skb, 0,
			   ATH12K_TX_MGMT_NUM_PENDING_MAX);
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
		ath12k_warn(ab, "failed to DMA map mgmt Tx buffer\n");
		ret = -EIO;
		goto err_free_idr;
	}

	ATH12K_SKB_CB(skb)->ar = ar;
	ATH12K_SKB_CB(skb)->paddr = paddr;
	ATH12K_SKB_CB(skb)->paddr_mapping_addr = paddr_mapping_addr;
	
	ret = ath12k_wmi_mgmt_send(ar, arvif->vdev_id, buf_id, skb);
	if (ret) {
		ath12k_warn(ar->ab, "failed to send mgmt frame: %d\n", ret);
		goto err_unmap_buf;
	}

	return 0;

err_unmap_buf:
	dma_unmap_single(ab->dev, ATH12K_SKB_CB(skb)->paddr,
			 ATH12K_SKB_CB(skb)->paddr_mapping_addr, skb->len, DMA_TO_DEVICE);
err_free_idr:
	spin_lock_bh(&ar->txmgmt_idr_lock);
	idr_remove(&ar->txmgmt_idr, buf_id);
	spin_unlock_bh(&ar->txmgmt_idr_lock);

	return ret;
}

static void ath12k_mgmt_over_wmi_tx_purge(struct ath12k *ar)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&ar->wmi_mgmt_tx_queue)) != NULL)
		ieee80211_free_txskb(ar->hw, skb);
}

static void ath12k_mgmt_over_wmi_tx_work(void *context)
{
	struct ath12k *ar = context;
	struct ath12k_skb_cb *skb_cb;
	struct ath12k_vif *arvif;
	struct sk_buff *skb;
	int ret;

	while ((skb = skb_dequeue(&ar->wmi_mgmt_tx_queue)) != NULL) {
		skb_cb = ATH12K_SKB_CB(skb);
		if (!skb_cb->vif) {
			ath12k_warn(ar->ab, "no vif found for mgmt frame\n");
			ieee80211_free_txskb(ar->hw, skb);
			continue;
		}

		arvif = ath12k_vif_to_arvif(skb_cb->vif);
		if (ar->allocated_vdev_map & (1LL << arvif->vdev_id) &&
		    arvif->is_started) {
			ret = ath12k_mac_mgmt_tx_wmi(ar, arvif, skb);
			if (ret) {
				ath12k_warn(ar->ab, "failed to tx mgmt frame, vdev_id %d :%d\n",
					    arvif->vdev_id, ret);
				ieee80211_free_txskb(ar->hw, skb);
			} else {
				atomic_inc(&ar->num_pending_mgmt_tx);
			}
		} else {
			ath12k_warn(ar->ab,
				    "dropping mgmt frame for vdev %d, is_started %d\n",
				    arvif->vdev_id,
				    arvif->is_started);
			ieee80211_free_txskb(ar->hw, skb);
		}
	}
}

static int ath12k_mac_mgmt_tx(struct ath12k *ar, struct sk_buff *skb,
			      bool is_prb_rsp)
{
	struct sk_buff_head *q = &ar->wmi_mgmt_tx_queue;

	if (test_bit(ATH12K_FLAG_CRASH_FLUSH, &ar->ab->dev_flags))
		return -ESHUTDOWN;

	/* Drop probe response packets when the pending management tx
	 * count has reached a certain threshold, so as to prioritize
	 * other mgmt packets like auth and assoc to be sent on time
	 * for establishing successful connections.
	 */
	if (is_prb_rsp &&
	    atomic_read(&ar->num_pending_mgmt_tx) > ATH12K_PRB_RSP_DROP_THRESHOLD) {
		ath12k_warn(ar->ab,
			    "dropping probe response as pending queue is almost full\n");
		return -ENOSPC;
	}

	if (skb_queue_len(q) == ATH12K_TX_MGMT_NUM_PENDING_MAX) {
		ath12k_warn(ar->ab, "mgmt tx queue is full\n");
		return -ENOSPC;
	}

	skb_queue_tail(q, skb);
	ieee80211_queue_work(ar->hw, &ar->wmi_mgmt_tx_work);

	return 0;
}

static void ath12k_mac_op_tx(struct ieee80211_hw *hw,
			     struct ieee80211_tx_control *control,
			     struct sk_buff *skb)
{
	struct ath12k_skb_cb *skb_cb = ATH12K_SKB_CB(skb);
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_vif *vif = info->u.control.vif;
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_key_conf *key = info->u.control.hw_key;
	u32 info_flags = info->flags;
	bool is_prb_rsp;
	int ret;

	memset(skb_cb, 0, sizeof(*skb_cb));
	skb_cb->vif = vif;

	if (key) {
		skb_cb->cipher = key->cipher;
		skb_cb->flags |= ATH12K_SKB_CIPHER_SET;
	}
	
	if (info_flags & IEEE80211_TX_CTRL_HW_80211_ENCAP) {
		skb_cb->flags |= ATH12K_SKB_HW_80211_ENCAP;
	} else if (ieee80211_is_mgmt(hdr->frame_control)) {
		ath12k_dbg_dump(ar->ab, ATH12K_DBG_PKT, "mgmt ", skb->data, skb->len, 0);
		
		is_prb_rsp = ieee80211_is_probe_resp(hdr->frame_control);
		ret = ath12k_mac_mgmt_tx(ar, skb, is_prb_rsp);
		if (ret) {
			ath12k_warn(ar->ab, "failed to queue management frame %d\n",
				    ret);
			ieee80211_tx_status(ar->hw, skb);
		}
		return;
	}

	ath12k_dbg_dump(ar->ab, ATH12K_DBG_PKT, "data ", skb->data, skb->len, 0);
	ret = ath12k_dp_tx(ar, arvif, skb);
	if (ret) {
		ath12k_warn(ar->ab, "failed to transmit frame %d\n", ret);
		ieee80211_tx_status(ar->hw, skb);
	}
}

void ath12k_mac_drain_tx(struct ath12k *ar)
{
	/* make sure rcu-protected mac80211 tx path itself is drained */
	synchronize_net();

	cancel_work_sync(&ar->wmi_mgmt_tx_work);
	ath12k_mgmt_over_wmi_tx_purge(ar);
}

static int ath12k_mac_config_mon_status_default(struct ath12k *ar, bool enable)
{
	return -ENOTSUPP;
	/* TODO: Need to support new monitor mode */
}

static void ath12k_mac_wait_reconfigure(struct ath12k_base *ab)
{
	int recovery_start_count;

	if (!ab->is_reset)
		return;

	recovery_start_count = atomic_inc_return(&ab->recovery_start_count);

	ath12k_dbg(ab, ATH12K_DBG_MAC, "recovery start count %d\n", recovery_start_count);

	if (recovery_start_count == (int)ab->num_radios) {
		complete(&ab->recovery_start);
		ath12k_dbg(ab, ATH12K_DBG_MAC, "recovery started success\n");
	}

	ath12k_dbg(ab, ATH12K_DBG_MAC, "waiting reconfigure...\n");

	wait_for_completion_timeout(&ab->reconfigure_complete,
				    ATH12K_RECONFIGURE_TIMEOUT_HZ);
}

static int ath12k_mac_op_start(struct ieee80211_hw *hw)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;
	struct ath12k_pdev *pdev = ar->pdev;
	int ret;

	ath12k_mac_drain_tx(ar);
	mutex_lock(&ar->conf_mutex);

	switch (ar->state) {
	case ATH12K_STATE_OFF:
		ar->state = ATH12K_STATE_ON;
		break;
	case ATH12K_STATE_RESTARTING:
		ar->state = ATH12K_STATE_RESTARTED;
		ath12k_mac_wait_reconfigure(ab);
		break;
	case ATH12K_STATE_RESTARTED:
	case ATH12K_STATE_WEDGED:
	case ATH12K_STATE_ON:
		WARN_ON(1);
		ret = -EINVAL;
		goto err;
	}

	ret = ath12k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_PMF_QOS,
					1, pdev->pdev_id);

	if (ret) {
		ath12k_err(ar->ab, "failed to enable PMF QOS: (%d\n", ret);
		goto err;
	}

	ret = ath12k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_DYNAMIC_BW, 1,
					pdev->pdev_id);
	if (ret) {
		ath12k_err(ar->ab, "failed to enable dynamic bw: %d\n", ret);
		goto err;
	}

	ret = ath12k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_ARP_AC_OVERRIDE,
					0, pdev->pdev_id);
	if (ret) {
		ath12k_err(ab, "failed to set ac override for ARP: %d\n",
			   ret);
		goto err;
	}

	ret = ath12k_wmi_send_dfs_phyerr_offload_enable_cmd(ar, pdev->pdev_id);
	if (ret) {
		ath12k_err(ab, "failed to offload radar detection: %d\n",
			   ret);
		goto err;
	}

	ret = ath12k_dp_tx_htt_h2t_ppdu_stats_req(ar,
						  HTT_PPDU_STATS_TAG_DEFAULT);
	if (ret) {
		ath12k_err(ab, "failed to req ppdu stats: %d\n", ret);
		goto err;
	}

	ret = ath12k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_MESH_MCAST_ENABLE,
					1, pdev->pdev_id);

	if (ret) {
		ath12k_err(ar->ab, "failed to enable MESH MCAST ENABLE: (%d\n", ret);
		goto err;
	}

	__ath12k_set_antenna(ar, ar->cfg_tx_chainmask, ar->cfg_rx_chainmask);

	/* TODO: Do we need to enable ANI? */

	ath12k_reg_update_chan_list(ar, false);

	ar->num_started_vdevs = 0;
	ar->num_created_vdevs = 0;
	ar->num_peers = 0;
	ar->allocated_vdev_map = 0;

	/* Configure monitor status ring with default rx_filter to get rx status
	 * such as rssi, rx_duration.
	 */
	ret = ath12k_mac_config_mon_status_default(ar, true);
	if (ret && (ret != -ENOTSUPP)) {
		ath12k_err(ab, "failed to configure monitor status ring with default rx_filter: (%d)\n",
			   ret);
		goto err;
	}

	if (ret == -ENOTSUPP)
		ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
			   "monitor status config is not yet supported");

	/* Configure the hash seed for hash based reo dest ring selection */
	ath12k_wmi_pdev_lro_cfg(ar, ar->pdev->pdev_id);

	/* allow device to enter IMPS */
	if (ab->hw_params->idle_ps) {
		ret = ath12k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_IDLE_PS_CONFIG,
						1, pdev->pdev_id);
		if (ret) {
			ath12k_err(ab, "failed to enable idle ps: %d\n", ret);
			goto err;
		}
	}

	mutex_unlock(&ar->conf_mutex);

	rcu_assign_pointer(ab->pdevs_active[ar->pdev_idx],
			   &ab->pdevs[ar->pdev_idx]);

	return 0;

err:
	ar->state = ATH12K_STATE_OFF;
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static void ath12k_mac_op_stop(struct ieee80211_hw *hw)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct htt_ppdu_stats_info *ppdu_stats, *tmp;
	int ret;

	ath12k_mac_drain_tx(ar);

	mutex_lock(&ar->conf_mutex);
	ret = ath12k_mac_config_mon_status_default(ar, false);
	if (ret && (ret != -ENOTSUPP))
		ath12k_err(ar->ab, "failed to clear rx_filter for monitor status ring: (%d)\n",
			   ret);

	clear_bit(ATH12K_CAC_RUNNING, &ar->dev_flags);
	ar->state = ATH12K_STATE_OFF;
	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.timeout);
	cancel_work_sync(&ar->regd_update_work);
	cancel_work_sync(&ar->ab->update_11d_work);
	ar->state_11d = ATH12K_11D_IDLE;
	complete(&ar->completed_11d_scan);

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

static u8
ath12k_mac_get_vdev_stats_id(struct ath12k_vif *arvif)
{
	struct ath12k_base *ab = arvif->ar->ab;
	u8 vdev_stats_id = 0;

	do {
		if (ab->free_vdev_stats_id_map & (1LL << vdev_stats_id)) {
			vdev_stats_id++;
			if (vdev_stats_id <= ATH12K_INVAL_VDEV_STATS_ID) {
				vdev_stats_id = ATH12K_INVAL_VDEV_STATS_ID;
				break;
			}
		} else {
			ab->free_vdev_stats_id_map |= (1LL << vdev_stats_id);
			break;
		}
	} while (vdev_stats_id);

	arvif->vdev_stats_id = vdev_stats_id;
	return vdev_stats_id;
}

static void ath12k_mac_setup_vdev_create_arg(struct ath12k_vif *arvif,
					     struct ath12k_wmi_vdev_create_arg *arg)
{
	struct ath12k *ar = arvif->ar;
	struct ath12k_pdev *pdev = ar->pdev;

	arg->if_id = arvif->vdev_id;
	arg->type = arvif->vdev_type;
	arg->subtype = arvif->vdev_subtype;
	arg->pdev_id = pdev->pdev_id;

	if (pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP) {
		arg->chains[NL80211_BAND_2GHZ].tx = ar->num_tx_chains;
		arg->chains[NL80211_BAND_2GHZ].rx = ar->num_rx_chains;
	}
	if (pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP) {
		arg->chains[NL80211_BAND_5GHZ].tx = ar->num_tx_chains;
		arg->chains[NL80211_BAND_5GHZ].rx = ar->num_rx_chains;
	}
	if (pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP &&
	    ar->supports_6ghz) {
		arg->chains[NL80211_BAND_6GHZ].tx = ar->num_tx_chains;
		arg->chains[NL80211_BAND_6GHZ].rx = ar->num_rx_chains;
	}

	arg->if_stats_id = ath12k_mac_get_vdev_stats_id(arvif);
}

static u32
ath12k_mac_prepare_he_mode(struct ath12k_pdev *pdev, u32 viftype)
{
	struct ath12k_pdev_cap *pdev_cap = &pdev->cap;
	struct ath12k_band_cap *cap_band = NULL;
	u32 *hecap_phy_ptr = NULL;
	u32 hemode = 0;

	if (pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP)
		cap_band = &pdev_cap->band[NL80211_BAND_2GHZ];
	else
		cap_band = &pdev_cap->band[NL80211_BAND_5GHZ];

	hecap_phy_ptr = &cap_band->he_cap_phy_info[0];

	hemode = u32_encode_bits(HE_SU_BFEE_ENABLE, HE_MODE_SU_TX_BFEE) |
		 u32_encode_bits(HECAP_PHY_SUBFMR_GET(hecap_phy_ptr),
				 HE_MODE_SU_TX_BFER) |
		 u32_encode_bits(HECAP_PHY_ULMUMIMO_GET(hecap_phy_ptr),
				 HE_MODE_UL_MUMIMO);

	/* TODO: WDS and other modes */
	if (viftype == NL80211_IFTYPE_AP) {
		hemode |= u32_encode_bits(HECAP_PHY_MUBFMR_GET(hecap_phy_ptr),
					  HE_MODE_MU_TX_BFER) |
			  u32_encode_bits(HE_DL_MUOFDMA_ENABLE, HE_MODE_DL_OFDMA) |
			  u32_encode_bits(HE_UL_MUOFDMA_ENABLE, HE_MODE_UL_OFDMA);
	} else {
		hemode |= u32_encode_bits(HE_MU_BFEE_ENABLE, HE_MODE_MU_TX_BFEE);
	}

	return hemode;
}

static int ath12k_set_he_mu_sounding_mode(struct ath12k *ar,
					  struct ath12k_vif *arvif)
{
	u32 param_id, param_value;
	struct ath12k_base *ab = ar->ab;
	int ret = 0;

	param_id = WMI_VDEV_PARAM_SET_HEMU_MODE;
	param_value = ath12k_mac_prepare_he_mode(ar->pdev, ieee80211_vif_type(arvif->vif));
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, param_value);
	if (ret) {
		ath12k_warn(ab, "failed to set vdev %d HE MU mode: %d param_value %x\n",
			    arvif->vdev_id, ret, param_value);
		return ret;
	}
	param_id = WMI_VDEV_PARAM_SET_HE_SOUNDING_MODE;
	param_value =
		u32_encode_bits(HE_VHT_SOUNDING_MODE_ENABLE, HE_VHT_SOUNDING_MODE) |
		u32_encode_bits(HE_TRIG_NONTRIG_SOUNDING_MODE_ENABLE,
				HE_TRIG_NONTRIG_SOUNDING_MODE);
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, param_value);
	if (ret) {
		ath12k_warn(ab, "failed to set vdev %d HE MU mode: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}
	return ret;
}

static void ath12k_mac_op_update_vif_offload(struct ieee80211_hw *hw,
					     struct ieee80211_vif *vif)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	u32 param_id, param_value;
	int ret;
	u32 flag_value = 0;

	/*uefi use 802.3 pkt for both tx and rx*/
	param_id = WMI_VDEV_PARAM_TX_ENCAP_TYPE;
	flag_value = IEEE80211_OFFLOAD_ENCAP_ENABLED|IEEE80211_OFFLOAD_DECAP_ENABLED;
		
	if (ieee80211_vif_type(vif) != NL80211_IFTYPE_STATION &&
	    ieee80211_vif_type(vif) != NL80211_IFTYPE_AP) {
		flag_value &= ~(IEEE80211_OFFLOAD_ENCAP_ENABLED |
					IEEE80211_OFFLOAD_DECAP_ENABLED);
		ieee80211_vif_set_offload_flag(vif, flag_value);
	}

	if (flag_value & IEEE80211_OFFLOAD_ENCAP_ENABLED)
		arvif->tx_encap_type = ATH12K_HW_TXRX_ETHERNET;
	else if (test_bit(ATH12K_FLAG_RAW_MODE, &ab->dev_flags))
		arvif->tx_encap_type = ATH12K_HW_TXRX_RAW;
	else
		arvif->tx_encap_type = ATH12K_HW_TXRX_NATIVE_WIFI;

	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, arvif->tx_encap_type);
	if (ret) {
		ath12k_warn(ab, "failed to set vdev %d tx encap mode: %d\n",
			    arvif->vdev_id, ret);
		flag_value &= ~IEEE80211_OFFLOAD_ENCAP_ENABLED;
		ieee80211_vif_set_offload_flag(vif, flag_value);
	}

	param_id = WMI_VDEV_PARAM_RX_DECAP_TYPE;
	if (flag_value & IEEE80211_OFFLOAD_DECAP_ENABLED)
		param_value = ATH12K_HW_TXRX_ETHERNET;
	else if (test_bit(ATH12K_FLAG_RAW_MODE, &ab->dev_flags))
		param_value = ATH12K_HW_TXRX_RAW;
	else
		param_value = ATH12K_HW_TXRX_NATIVE_WIFI;

	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, param_value);
	if (ret) {
		ath12k_warn(ab, "failed to set vdev %d rx decap mode: %d\n",
			    arvif->vdev_id, ret);
		flag_value &= ~IEEE80211_OFFLOAD_DECAP_ENABLED;
		ieee80211_vif_set_offload_flag(vif, flag_value);
	}
}

static bool ath12k_mac_vif_ap_active_any(struct ath12k_base *ab)
{
	struct ath12k *ar;
	struct ath12k_pdev *pdev;
	struct ath12k_vif *arvif;
	u8 i;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		list_for_each_entry(arvif, &ar->arvifs, struct ath12k_vif, list) {
			if (arvif->is_up && arvif->vdev_type == WMI_VDEV_TYPE_AP)
				return true;
		}
	}
	return false;
}

void ath12k_mac_11d_scan_start(struct ath12k *ar, u32 vdev_id, bool wait)
{
	struct wmi_11d_scan_start_params param;
	int ret;

	mutex_lock(&ar->ab->vdev_id_11d_lock);

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac vdev id for 11d scan %d\n",
		   ar->vdev_id_11d_scan);

	if (ar->regdom_set_by_user)
		goto fin;

	if (ar->vdev_id_11d_scan != ATH12K_11D_INVALID_VDEV_ID)
		goto fin;

	if (!test_bit(WMI_TLV_SERVICE_11D_OFFLOAD, ar->ab->wmi_ab.svc_map))
		goto fin;

	if (ath12k_mac_vif_ap_active_any(ar->ab))
		goto fin;

	param.vdev_id = vdev_id;
	param.start_interval_msec = wait ? 0 : ATH12K_SCAN_11D_START_INTERVAL;
	param.scan_period_msec = ATH12K_SCAN_11D_INTERVAL;

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac start 11d scan\n");

	ret = ath12k_wmi_send_11d_scan_start_cmd(ar, &param);
	if (ret) {
		ath12k_warn(ar->ab, "failed to start 11d scan vdev %d ret: %d\n",
			    vdev_id, ret);
	} else {
		ar->vdev_id_11d_scan = vdev_id;
		if (ar->state_11d == ATH12K_11D_PREPARING)
			ar->state_11d = ATH12K_11D_RUNNING;
	}

fin:
	if (ar->state_11d == ATH12K_11D_PREPARING) {
		ar->state_11d = ATH12K_11D_IDLE;
		complete(&ar->completed_11d_scan);
	}

	mutex_unlock(&ar->ab->vdev_id_11d_lock);
}

void ath12k_mac_11d_scan_stop(struct ath12k *ar)
{
	int ret;
	u32 vdev_id;

	if (!test_bit(WMI_TLV_SERVICE_11D_OFFLOAD, ar->ab->wmi_ab.svc_map))
		return;

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac stop 11d scan\n");

	mutex_lock(&ar->ab->vdev_id_11d_lock);

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac stop 11d vdev id %d\n",
		   ar->vdev_id_11d_scan);

	if (ar->state_11d == ATH12K_11D_PREPARING) {
		ar->state_11d = ATH12K_11D_IDLE;
		complete(&ar->completed_11d_scan);
	}

	if (ar->vdev_id_11d_scan != ATH12K_11D_INVALID_VDEV_ID) {
		vdev_id = ar->vdev_id_11d_scan;

		ret = ath12k_wmi_send_11d_scan_stop_cmd(ar, vdev_id);
		if (ret) {
			ath12k_warn(ar->ab,
				    "failed to stopt 11d scan vdev %d ret: %d\n",
				    vdev_id, ret);
		} else {
			ar->vdev_id_11d_scan = ATH12K_11D_INVALID_VDEV_ID;
			ar->state_11d = ATH12K_11D_IDLE;
			complete(&ar->completed_11d_scan);
		}
	}
	mutex_unlock(&ar->ab->vdev_id_11d_lock);
}

void ath12k_mac_11d_scan_stop_all(struct ath12k_base *ab)
{
	struct ath12k *ar;
	struct ath12k_pdev *pdev;
	u8 i;

	ath12k_dbg(ab, ATH12K_DBG_MAC, "mac stop soc 11d scan\n");

	for (i = 0; i < ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;

		ath12k_mac_11d_scan_stop(ar);
	}
}

static int ath12k_mac_op_add_interface(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ath12k_wmi_vdev_create_arg vdev_arg = {0};
	struct ath12k_wmi_peer_create_arg peer_param;
	u32 param_id, param_value;
	u16 nss;
	u16 nss_temp = 0;
	int i;
	int ret;
	u32 bit;

	ieee80211_vif_drv_conf_set_uapsd(vif, true);

	mutex_lock(&ar->conf_mutex);

	if (ieee80211_vif_type(vif) == NL80211_IFTYPE_AP &&
	    ar->num_peers > (ar->max_num_peers - 1)) {
		ath12k_warn(ab, "failed to create vdev due to insufficient peer entry resource in firmware\n");
		ret = -ENOBUFS;
		goto err;
	}

	if (ar->num_created_vdevs > (TARGET_NUM_VDEVS - 1)) {
		ath12k_warn(ab, "failed to create vdev, reached max vdev limit %d\n",
			    TARGET_NUM_VDEVS);
		ret = -EBUSY;
		goto err;
	}

	memset(arvif, 0, sizeof(*arvif));

	arvif->ar = ar;
	arvif->vif = vif;

	list_init_head(&arvif->list);

	init_delayed_work(&arvif->connection_loss_work,
			  ath12k_mac_vif_sta_connection_loss_work, arvif);

	for (i = 0; i < ARRAY_SIZE(arvif->bitrate_mask.control); i++) {
		arvif->bitrate_mask.control[i].legacy = 0xffffffff;
		memset(arvif->bitrate_mask.control[i].ht_mcs, 0xff,
		       sizeof(arvif->bitrate_mask.control[i].ht_mcs));
		memset(arvif->bitrate_mask.control[i].vht_mcs, 0xff,
		       sizeof(arvif->bitrate_mask.control[i].vht_mcs));
	}

	bit = (u32)__ffs64(ab->free_vdev_map);

	arvif->vdev_id = bit;
	arvif->vdev_subtype = WMI_VDEV_SUBTYPE_NONE;

	switch (ieee80211_vif_type(vif)) {
	case NL80211_IFTYPE_UNSPECIFIED:
	case NL80211_IFTYPE_STATION:
		arvif->vdev_type = WMI_VDEV_TYPE_STA;
		break;
	case NL80211_IFTYPE_MESH_POINT:
		arvif->vdev_subtype = WMI_VDEV_SUBTYPE_MESH_11S;
		//fallthrough;
	case NL80211_IFTYPE_AP:
		arvif->vdev_type = WMI_VDEV_TYPE_AP;
		break;
	case NL80211_IFTYPE_MONITOR:
		arvif->vdev_type = WMI_VDEV_TYPE_MONITOR;
		ar->monitor_vdev_id = bit;
		break;
	default:
		WARN_ON(1);
		break;
	}

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac add interface id %d type %d subtype %d map %llx\n",
		   arvif->vdev_id, arvif->vdev_type, arvif->vdev_subtype,
		   ab->free_vdev_map);

	ieee80211_vif_assign_hw_queue(vif, arvif->vdev_id);

	ath12k_mac_setup_vdev_create_arg(arvif, &vdev_arg);

	ret = ath12k_wmi_vdev_create(ar, ieee80211_vif_addr(vif), &vdev_arg);
	if (ret) {
		ath12k_warn(ab, "failed to create WMI vdev %d: %d\n",
			    arvif->vdev_id, ret);
		goto err;
	}

	ar->num_created_vdevs++;
	ath12k_dbg(ab, ATH12K_DBG_MAC, "vdev %pM created, vdev_id %d\n",
		   ieee80211_vif_addr(vif), arvif->vdev_id);
	ar->allocated_vdev_map |= 1LL << arvif->vdev_id;
	ab->free_vdev_map &= ~(1LL << arvif->vdev_id);

	spin_lock_bh(&ar->data_lock);
	list_add_tail(&arvif->list, &ar->arvifs);
	spin_unlock_bh(&ar->data_lock);

	ath12k_mac_op_update_vif_offload(hw, vif);

	nss = ((nss_temp = get_num_chains(ar->cfg_tx_chainmask)) ? nss_temp : 1);
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    WMI_VDEV_PARAM_NSS, nss);
	if (ret) {
		ath12k_warn(ab, "failed to set vdev %d chainmask 0x%x, nss %d :%d\n",
			    arvif->vdev_id, ar->cfg_tx_chainmask, nss, ret);
		goto err_vdev_del;
	}

	switch (arvif->vdev_type) {
	case WMI_VDEV_TYPE_AP:
		peer_param.vdev_id = arvif->vdev_id;
		peer_param.peer_addr = ieee80211_vif_addr(vif);
		peer_param.peer_type = WMI_PEER_TYPE_DEFAULT;
		ret = ath12k_peer_create(ar, arvif, NULL, &peer_param);
		if (ret) {
			ath12k_warn(ab, "failed to vdev %d create peer for AP: %d\n",
				    arvif->vdev_id, ret);
			goto err_vdev_del;
		}

		ret = ath12k_mac_set_kickout(arvif);
		if (ret) {
			ath12k_warn(ar->ab, "failed to set vdev %i kickout parameters: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}
		ath12k_mac_11d_scan_stop_all(ar->ab);
		break;
	case WMI_VDEV_TYPE_STA:
		param_id = WMI_STA_PS_PARAM_RX_WAKE_POLICY;
		param_value = WMI_STA_PS_RX_WAKE_POLICY_WAKE;
		ret = ath12k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
						  param_id, param_value);
		if (ret) {
			ath12k_warn(ar->ab, "failed to set vdev %d RX wake policy: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}

		param_id = WMI_STA_PS_PARAM_TX_WAKE_THRESHOLD;
		param_value = WMI_STA_PS_TX_WAKE_THRESHOLD_ALWAYS;
		ret = ath12k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
						  param_id, param_value);
		if (ret) {
			ath12k_warn(ar->ab, "failed to set vdev %d TX wake threshold: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}

		param_id = WMI_STA_PS_PARAM_PSPOLL_COUNT;
		param_value = WMI_STA_PS_PSPOLL_COUNT_NO_MAX;
		ret = ath12k_wmi_set_sta_ps_param(ar, arvif->vdev_id,
						  param_id, param_value);
		if (ret) {
			ath12k_warn(ar->ab, "failed to set vdev %d pspoll count: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}

		ret = ath12k_wmi_pdev_set_ps_mode(ar, arvif->vdev_id, false);
		if (ret) {
			ath12k_warn(ar->ab, "failed to disable vdev %d ps mode: %d\n",
				    arvif->vdev_id, ret);
			goto err_peer_del;
		}
		
		if (test_bit(WMI_TLV_SERVICE_11D_OFFLOAD, ab->wmi_ab.svc_map)) {
			reinit_completion(&ar->completed_11d_scan);
			ar->state_11d = ATH12K_11D_PREPARING;

			ath12k_mac_11d_scan_start(ar, arvif->vdev_id, false);
		}
		break;
	default:
		break;
	}

	arvif->txpower = ieee80211_vif_bss_conf_get_txpower(vif);
	ret = ath12k_mac_txpower_recalc(ar);
	if (ret)
		goto err_peer_del;

	param_id = WMI_VDEV_PARAM_RTS_THRESHOLD;
	param_value = ieee80211_hw_get_rts_threshold(ar->hw);
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    param_id, param_value);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set rts threshold for vdev %d: %d\n",
			    arvif->vdev_id, ret);
	}

	ath12k_dp_vdev_tx_attach(ar, arvif);

	if (ieee80211_vif_type(vif) != NL80211_IFTYPE_MONITOR && ar->monitor_conf_enabled)
		ath12k_mac_monitor_vdev_create(ar);

	mutex_unlock(&ar->conf_mutex);

	return ret;

err_peer_del:
	if (arvif->vdev_type == WMI_VDEV_TYPE_AP) {
		reinit_completion(&ar->peer_delete_done);

		ret = ath12k_wmi_send_peer_delete_cmd(ar, ieee80211_vif_addr(vif),
						      arvif->vdev_id);
		if (ret) {
			ath12k_warn(ar->ab, "failed to delete peer vdev_id %d addr %pM\n",
				    arvif->vdev_id, ieee80211_vif_addr(vif));
			goto err;
		}

		ret = ath12k_wait_for_peer_delete_done(ar, arvif->vdev_id,
						       ieee80211_vif_addr(vif));
		if (ret)
			goto err;

		ar->num_peers--;
	}

err_vdev_del:
	ath12k_wmi_vdev_delete(ar, arvif->vdev_id);
	ar->num_created_vdevs--;
	ar->allocated_vdev_map &= ~(1LL << arvif->vdev_id);
	ab->free_vdev_map |= 1LL << arvif->vdev_id;
	ab->free_vdev_stats_id_map &= ~(1LL << arvif->vdev_stats_id);
	spin_lock_bh(&ar->data_lock);
	list_del(&arvif->list);
	spin_unlock_bh(&ar->data_lock);

err:
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static void ath12k_mac_vif_unref(struct ath12k_dp *dp, struct ieee80211_vif *vif)
{
	struct ath12k_tx_desc_info *tx_desc_info, *tmp1;
	struct ath12k_skb_cb *skb_cb;
	struct sk_buff *skb;
	int i;

	for (i = 0; i < ATH12K_HW_MAX_QUEUES; i++) {
		spin_lock_bh(&dp->tx_desc_lock[i]);

		list_for_each_entry_safe(tx_desc_info, tmp1, &dp->tx_desc_used_list[i],
					 struct ath12k_tx_desc_info, list) {
			skb = tx_desc_info->skb;
			if (!skb)
				continue;

			skb_cb = ATH12K_SKB_CB(skb);
			if (skb_cb->vif == vif)
				skb_cb->vif = NULL;
		}

		spin_unlock_bh(&dp->tx_desc_lock[i]);
	}
}

static void ath12k_mac_op_remove_interface(struct ieee80211_hw *hw,
					   struct ieee80211_vif *vif)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ath12k_vif_to_arvif(vif);
	struct ath12k_base *ab = ar->ab;
	unsigned long time_left;
	int ret;

	mutex_lock(&ar->conf_mutex);

	ath12k_dbg(ab, ATH12K_DBG_MAC, "mac remove interface (vdev %d)\n",
		   arvif->vdev_id);

	cancel_delayed_work_sync(&arvif->connection_loss_work);

	if (arvif->vdev_type == WMI_VDEV_TYPE_STA)
		ath12k_mac_11d_scan_stop(ar);
	
	if (arvif->vdev_type == WMI_VDEV_TYPE_AP) {
		ret = ath12k_peer_delete(ar, arvif->vdev_id, ieee80211_vif_addr(vif));
		if (ret)
			ath12k_warn(ab, "failed to submit AP self-peer removal on vdev %d: %d\n",
				    arvif->vdev_id, ret);
	}

	reinit_completion(&ar->vdev_delete_done);

	ret = ath12k_wmi_vdev_delete(ar, arvif->vdev_id);
	if (ret) {
		ath12k_warn(ab, "failed to delete WMI vdev %d: %d\n",
			    arvif->vdev_id, ret);
		goto err_vdev_del;
	}

	time_left = wait_for_completion_timeout(&ar->vdev_delete_done,
						ATH12K_VDEV_DELETE_TIMEOUT_HZ);
	if (time_left == 0) {
		ath12k_warn(ab, "Timeout in receiving vdev delete response\n");
		goto err_vdev_del;
	}

	if (arvif->vdev_type == WMI_VDEV_TYPE_MONITOR) {
		ar->monitor_vdev_id = (u32)-1;
		ar->monitor_vdev_created = false;
	} else if (ar->monitor_vdev_created && !ar->monitor_started) {
		ret = ath12k_mac_monitor_vdev_delete(ar);
	}

	ab->free_vdev_map |= 1LL << (arvif->vdev_id);
	ar->allocated_vdev_map &= ~(1LL << arvif->vdev_id);
	ab->free_vdev_stats_id_map &= ~(1LL << arvif->vdev_stats_id);
	ar->num_created_vdevs--;

	ath12k_dbg(ab, ATH12K_DBG_MAC, "vdev %pM deleted, vdev_id %d\n",
		   ieee80211_vif_addr(vif), arvif->vdev_id);

err_vdev_del:
	spin_lock_bh(&ar->data_lock);
	list_del(&arvif->list);
	spin_unlock_bh(&ar->data_lock);

	ath12k_peer_cleanup(ar, arvif->vdev_id);

	idr_for_each(&ar->txmgmt_idr,
		     ath12k_mac_vif_txmgmt_idr_remove, vif);

	ath12k_mac_vif_unref(&ab->dp, vif);
	ath12k_dp_tx_put_bank_profile(&ab->dp, (u8)arvif->bank_id);

	/* Recalc txpower for remaining vdev */
	ath12k_mac_txpower_recalc(ar);
	clear_bit(ATH12K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);

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

static void ath12k_mac_op_configure_filter(struct ieee80211_hw *hw,
					   unsigned int changed_flags,
					   unsigned int *total_flags,
					   u64 multicast)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	bool reset_flag = false;
	int ret = 0;

	mutex_lock(&ar->conf_mutex);

	changed_flags &= SUPPORTED_FILTERS;
	*total_flags &= SUPPORTED_FILTERS;
	ar->filter_flags = *total_flags;

	/* For monitor mode */
	reset_flag = !(ar->filter_flags & IEEE80211_FIF_BCN_PRBRESP_PROMISC);

	ret = ath12k_dp_tx_htt_monitor_mode_ring_config(ar, reset_flag);
	if (!ret) {
		if (!reset_flag)
			set_bit(ATH12K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
		else
			clear_bit(ATH12K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
	} else {
		ath12k_warn(ar->ab,
			    "fail to set monitor filter: %d\n", ret);
	}
	ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
		   "changed_flags:0x%x, total_flags:0x%x, reset_flag:%d\n",
		   changed_flags, *total_flags, reset_flag);

	mutex_unlock(&ar->conf_mutex);
}

static int ath12k_mac_op_get_antenna(struct ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);

	mutex_lock(&ar->conf_mutex);

	*tx_ant = ar->cfg_tx_chainmask;
	*rx_ant = ar->cfg_rx_chainmask;

	mutex_unlock(&ar->conf_mutex);

	return 0;
}

static int ath12k_mac_op_set_antenna(struct ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	int ret;

	mutex_lock(&ar->conf_mutex);
	ret = __ath12k_set_antenna(ar, tx_ant, rx_ant);
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static int ath12k_mac_op_ampdu_action(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      struct ieee80211_ampdu_params *params)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	int ret = -EINVAL;

	mutex_lock(&ar->conf_mutex);

	switch (params->action) {
	case IEEE80211_AMPDU_RX_START:
		ret = ath12k_dp_rx_ampdu_start(ar, params);
		break;
	case IEEE80211_AMPDU_RX_STOP:
		ret = ath12k_dp_rx_ampdu_stop(ar, params);
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

static int ath12k_mac_op_add_chanctx(struct ieee80211_hw *hw,
				     struct ieee80211_chanctx_conf *ctx)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;

	ath12k_dbg(ab, ATH12K_DBG_MAC,
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

static void ath12k_mac_op_remove_chanctx(struct ieee80211_hw *hw,
					 struct ieee80211_chanctx_conf *ctx)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;

	ath12k_dbg(ab, ATH12K_DBG_MAC,
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

static int
ath12k_mac_vdev_start_restart(struct ath12k_vif *arvif,
			      const struct ieee80211_chan_def *chandef,
			      bool restart)
{
	struct ath12k *ar = arvif->ar;
	struct ath12k_base *ab = ar->ab;
	struct wmi_vdev_start_req_arg arg = { 0,};
	int he_support = ieee80211_vif_bss_conf_get_he_support(arvif->vif);
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_done);

	arg.vdev_id = arvif->vdev_id;
	arg.dtim_period = arvif->dtim_period;
	arg.bcn_intval = arvif->beacon_interval;

	arg.freq = chandef->chan->center_freq;
	arg.band_center_freq1 = chandef->center_freq1;
	arg.band_center_freq2 = chandef->center_freq2;
	if (chandef->chan->band >= NUM_NL80211_BANDS || chandef->width >= ATH12K_CHAN_WIDTH_NUM) {
		ath12k_warn(ar->ab, "Invalid chandef, band = %d, width = %d\n",
					    chandef->chan->band, chandef->width);
		return 0;
	}

	arg.mode = ath12k_phymodes[chandef->chan->band][chandef->width];

	arg.min_power = 0;
	arg.max_power = chandef->chan->max_power;
	arg.max_reg_power = chandef->chan->max_reg_power;
	arg.max_antenna_gain = chandef->chan->max_antenna_gain;

	arg.pref_tx_streams = ar->num_tx_chains;
	arg.pref_rx_streams = ar->num_rx_chains;

	if (arvif->vdev_type == WMI_VDEV_TYPE_AP) {
		arg.ssid = arvif->u.ap.ssid;
		arg.ssid_len = arvif->u.ap.ssid_len;
		arg.hidden_ssid = arvif->u.ap.hidden_ssid;

		/* For now allow DFS for AP mode */
		arg.chan_radar = !!(chandef->chan->flags & IEEE80211_CHAN_RADAR);

		arg.passive = arg.chan_radar;

		spin_lock_bh(&ab->base_lock);
		arg.regdomain = ar->ab->dfs_region;
		spin_unlock_bh(&ab->base_lock);

		/* TODO: Notify if secondary 80Mhz also needs radar detection */
		if (he_support) {
			ret = ath12k_set_he_mu_sounding_mode(ar, arvif);
			if (ret) {
				ath12k_warn(ar->ab, "failed to set he mode vdev %i\n",
					    arg.vdev_id);
				return ret;
			}
		}
	}

	arg.passive |= !!(chandef->chan->flags & IEEE80211_CHAN_NO_IR);

	ath12k_dbg(ab, ATH12K_DBG_MAC,
		   "mac vdev %d start center_freq %d phymode %s\n",
		   arg.vdev_id, arg.freq,
		   ath12k_mac_phymode_str(arg.mode));

	ret = ath12k_wmi_vdev_start(ar, &arg, restart);
	if (ret) {
		ath12k_warn(ar->ab, "failed to %s WMI vdev %i\n",
			    restart ? "restart" : "start", arg.vdev_id);
		return ret;
	}

	ret = ath12k_mac_vdev_setup_sync(ar);
	if (ret) {
		ath12k_warn(ab, "failed to synchronize setup for vdev %d %s: %d\n",
			    arg.vdev_id, restart ? "restart" : "start", ret);
		return ret;
	}

	ar->num_started_vdevs++;
	ath12k_dbg(ab, ATH12K_DBG_MAC,  "vdev %pM started, vdev_id %d\n",
		   ieee80211_vif_addr(arvif->vif), arvif->vdev_id);
#if 0
	/* Enable CAC Flag in the driver by checking the channel DFS cac time,
	 * i.e dfs_cac_ms value which will be valid only for radar channels
	 * and state as NL80211_DFS_USABLE which indicates CAC needs to be
	 * done before channel usage. This flags is used to drop rx packets.
	 * during CAC.
	 */
	/* TODO: Set the flag for other interface types as required */
	if (arvif->vdev_type == WMI_VDEV_TYPE_AP &&
	    chandef->chan->dfs_cac_ms &&
	    chandef->chan->dfs_state == NL80211_DFS_USABLE) {
		set_bit(ATH12K_CAC_RUNNING, &ar->dev_flags);
		ath12k_dbg(ab, ATH12K_DBG_MAC,
			   "CAC Started in chan_freq %d for vdev %d\n",
			   arg.freq, arg.vdev_id);
	}
#endif
	
	ret = ath12k_mac_set_txbf_conf(arvif);
	if (ret)
		ath12k_warn(ab, "failed to set txbf conf for vdev %d: %d\n",
			    arvif->vdev_id, ret);

	return 0;
}

static int ath12k_mac_vdev_stop(struct ath12k_vif *arvif)
{
	struct ath12k *ar = arvif->ar;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_done);

	ret = ath12k_wmi_vdev_stop(ar, arvif->vdev_id);
	if (ret) {
		ath12k_warn(ar->ab, "failed to stop WMI vdev %i: %d\n",
			    arvif->vdev_id, ret);
		goto err;
	}

	ret = ath12k_mac_vdev_setup_sync(ar);
	if (ret) {
		ath12k_warn(ar->ab, "failed to synchronize setup for vdev %i: %d\n",
			    arvif->vdev_id, ret);
		goto err;
	}

	WARN_ON(ar->num_started_vdevs == 0);

	ar->num_started_vdevs--;
	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "vdev %pM stopped, vdev_id %d\n",
		   ieee80211_vif_addr(arvif->vif), arvif->vdev_id);

	if (test_bit(ATH12K_CAC_RUNNING, &ar->dev_flags)) {
		clear_bit(ATH12K_CAC_RUNNING, &ar->dev_flags);
		ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "CAC Stopped for vdev %d\n",
			   arvif->vdev_id);
	}

	return 0;
err:
	return ret;
}

static int ath12k_mac_vdev_start(struct ath12k_vif *arvif,
				 const struct ieee80211_chan_def *chandef)
{
	return ath12k_mac_vdev_start_restart(arvif, chandef, false);
}

static int ath12k_mac_vdev_restart(struct ath12k_vif *arvif,
				   const struct ieee80211_chan_def *chandef)
{
	return ath12k_mac_vdev_start_restart(arvif, chandef, true);
}

struct ath12k_mac_change_chanctx_arg {
	struct ieee80211_chanctx_conf *ctx;
	struct ieee80211_vif_chanctx_switch *vifs;
	int n_vifs;
	int next_vif;
};

static void
ath12k_mac_change_chanctx_cnt_iter(void *data, const u8 *mac,
				   struct ieee80211_vif *vif)
{
	struct ath12k_mac_change_chanctx_arg *arg = data;

	if (ieee80211_vif_get_chanctx_conf(vif) != arg->ctx)
		return;

	arg->n_vifs++;
}

static void
ath12k_mac_change_chanctx_fill_iter(void *data, const u8 *mac,
				    struct ieee80211_vif *vif)
{
	struct ath12k_mac_change_chanctx_arg *arg = data;
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
ath12k_mac_update_vif_chan(struct ath12k *ar,
			   struct ieee80211_vif_chanctx_switch *vifs,
			   int n_vifs)
{
	struct ath12k_base *ab = ar->ab;
	struct ath12k_vif *arvif;
	int ret;
	int i;
	bool monitor_vif = false;

	lockdep_assert_held(&ar->conf_mutex);

	for (i = 0; i < n_vifs; i++) {
		arvif = ieee80211_vif_get_priv_data(vifs[i].vif);

		if (ieee80211_vif_type(vifs[i].vif) == NL80211_IFTYPE_MONITOR)
			monitor_vif = true;

		ath12k_dbg(ab, ATH12K_DBG_MAC,
			   "mac chanctx switch vdev_id %i freq %u->%u width %d->%d\n",
			   arvif->vdev_id,
			   vifs[i].old_ctx->def.chan->center_freq,
			   vifs[i].new_ctx->def.chan->center_freq,
			   vifs[i].old_ctx->def.width,
			   vifs[i].new_ctx->def.width);

		if (WARN_ON(!arvif->is_started))
			continue;

		if (WARN_ON(!arvif->is_up))
			continue;

		ret = ath12k_wmi_vdev_down(ar, arvif->vdev_id);
		if (ret) {
			ath12k_warn(ab, "failed to down vdev %d: %d\n",
				    arvif->vdev_id, ret);
			continue;
		}
	}

	/* All relevant vdevs are downed and associated channel resources
	 * should be available for the channel switch now.
	 */

	/* TODO: Update ar->rx_channel */

	for (i = 0; i < n_vifs; i++) {
		arvif = ieee80211_vif_get_priv_data(vifs[i].vif);

		if (WARN_ON(!arvif->is_started))
			continue;

		if (WARN_ON(!arvif->is_up))
			continue;

		ret = ath12k_mac_vdev_restart(arvif, &vifs[i].new_ctx->def);
		if (ret) {
			ath12k_warn(ab, "failed to restart vdev %d: %d\n",
				    arvif->vdev_id, ret);
			continue;
		}

		ret = ath12k_mac_setup_bcn_tmpl(arvif);
		if (ret)
			ath12k_warn(ab, "failed to update bcn tmpl during csa: %d\n",
				    ret);

		ret = ath12k_wmi_vdev_up(arvif->ar, arvif->vdev_id, arvif->aid,
					 arvif->bssid);
		if (ret) {
			ath12k_warn(ab, "failed to bring vdev up %d: %d\n",
				    arvif->vdev_id, ret);
			continue;
		}
	}

	/* Restart the internal monitor vdev on new channel */
	if (!monitor_vif && ar->monitor_vdev_created) {
		if (!ath12k_mac_monitor_stop(ar))
			ath12k_mac_monitor_start(ar);
	}
}

static void
ath12k_mac_update_active_vif_chan(struct ath12k *ar,
				  struct ieee80211_chanctx_conf *ctx)
{
	struct ath12k_mac_change_chanctx_arg arg = { 0 };

    arg.ctx = ctx;

	lockdep_assert_held(&ar->conf_mutex);

	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   IEEE80211_VIF_ITER_NORMAL,
						   ath12k_mac_change_chanctx_cnt_iter,
						   &arg);
	if (arg.n_vifs == 0)
		return;

	arg.vifs = kcalloc(arg.n_vifs, sizeof(arg.vifs[0]), GFP_KERNEL);
	if (!arg.vifs)
		return;

	ieee80211_iterate_active_interfaces_atomic(ar->hw,
						   IEEE80211_VIF_ITER_NORMAL,
						   ath12k_mac_change_chanctx_fill_iter,
						   &arg);

	ath12k_mac_update_vif_chan(ar, arg.vifs, arg.n_vifs);

	kfree(arg.vifs);
}

static void ath12k_mac_op_change_chanctx(struct ieee80211_hw *hw,
					 struct ieee80211_chanctx_conf *ctx,
					 u32 changed)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;

	mutex_lock(&ar->conf_mutex);

	ath12k_dbg(ab, ATH12K_DBG_MAC,
		   "mac chanctx change freq %u width %d ptr %pK changed %x\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx, changed);

	/* This shouldn't really happen because channel switching should use
	 * switch_vif_chanctx().
	 */
	if (WARN_ON(changed & IEEE80211_CHANCTX_CHANGE_CHANNEL))
		goto unlock;

	if (changed & IEEE80211_CHANCTX_CHANGE_WIDTH)
		ath12k_mac_update_active_vif_chan(ar, ctx);

	/* TODO: Recalc radar detection */

unlock:
	mutex_unlock(&ar->conf_mutex);
}

static int ath12k_start_vdev_delay(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;

	if (WARN_ON(arvif->is_started))
		return -EBUSY;

	ret = ath12k_mac_vdev_start(arvif, &arvif->chanctx.def);
	if (ret) {
		ath12k_warn(ab, "failed to start vdev %d addr %pM on freq %d: %d\n",
			    arvif->vdev_id, ieee80211_vif_addr(vif),
			    arvif->chanctx.def.chan->center_freq, ret);
		return ret;
	}

	if (arvif->vdev_type == WMI_VDEV_TYPE_MONITOR) {
		ret = ath12k_monitor_vdev_up(ar, arvif->vdev_id);
		if (ret) {
			ath12k_warn(ab, "failed put monitor up: %d\n", ret);
			return ret;
		}
	}

	arvif->is_started = true;

	/* TODO: Setup ps and cts/rts protection */
	return 0;
}

static int
ath12k_mac_op_assign_vif_chanctx(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_chanctx_conf *ctx)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;
	struct ath12k_wmi_peer_create_arg param;

	mutex_lock(&ar->conf_mutex);

	ath12k_dbg(ab, ATH12K_DBG_MAC,
		   "mac chanctx assign ptr %pK vdev_id %i\n",
		   ctx, arvif->vdev_id);

	/* for some targets bss peer must be created before vdev_start */
	if (ab->hw_params->vdev_start_delay &&
	    arvif->vdev_type != WMI_VDEV_TYPE_AP &&
	    arvif->vdev_type != WMI_VDEV_TYPE_MONITOR &&
	    !ath12k_peer_find_by_vdev_id(ab, arvif->vdev_id)) {
		memcpy(&arvif->chanctx, ctx, sizeof(*ctx));
		ret = 0;
		goto out;
	}

	if (WARN_ON(arvif->is_started)) {
		ret = -EBUSY;
		goto out;
	}

	if (ab->hw_params->vdev_start_delay &&
	    (arvif->vdev_type == WMI_VDEV_TYPE_AP ||
	    arvif->vdev_type == WMI_VDEV_TYPE_MONITOR)) {
		param.vdev_id = arvif->vdev_id;
		param.peer_type = WMI_PEER_TYPE_DEFAULT;
		param.peer_addr = ar->mac_addr;

		ret = ath12k_peer_create(ar, arvif, NULL, &param);
		if (ret) {
			ath12k_warn(ab, "failed to create peer after vdev start delay: %d",
				    ret);
			goto out;
		}
	}

	if (arvif->vdev_type == WMI_VDEV_TYPE_MONITOR) {
		ret = ath12k_mac_monitor_start(ar);
		if (ret)
			goto out;
		arvif->is_started = true;
		goto out;
	}

	ret = ath12k_mac_vdev_start(arvif, &ctx->def);
	if (ret) {
		ath12k_warn(ab, "failed to start vdev %i addr %pM on freq %d: %d\n",
			    arvif->vdev_id, ieee80211_vif_addr(vif),
			    ctx->def.chan->center_freq, ret);
		goto out;
	}

	if (arvif->vdev_type != WMI_VDEV_TYPE_MONITOR && ar->monitor_vdev_created)
		ath12k_mac_monitor_start(ar);

	arvif->is_started = true;

	/* TODO: Setup ps and cts/rts protection */

	ret = 0;

out:
	mutex_unlock(&ar->conf_mutex);

	return ret;
}

static void
ath12k_mac_op_unassign_vif_chanctx(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_chanctx_conf *ctx)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_base *ab = ar->ab;
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	int ret;

	mutex_lock(&ar->conf_mutex);

	ath12k_dbg(ab, ATH12K_DBG_MAC,
		   "mac chanctx unassign ptr %pK vdev_id %i\n",
		   ctx, arvif->vdev_id);

	WARN_ON(!arvif->is_started);

	if (ab->hw_params->vdev_start_delay &&
	    arvif->vdev_type == WMI_VDEV_TYPE_MONITOR &&
	    ath12k_peer_find_by_addr(ab, ar->mac_addr))
		ath12k_peer_delete(ar, arvif->vdev_id, ar->mac_addr);

	if (arvif->vdev_type == WMI_VDEV_TYPE_MONITOR) {
		ret = ath12k_mac_monitor_stop(ar);
		if (ret) {
			mutex_unlock(&ar->conf_mutex);
			return;
		}

		arvif->is_started = false;
		mutex_unlock(&ar->conf_mutex);
	}

	ret = ath12k_mac_vdev_stop(arvif);
	if (ret)
		ath12k_warn(ab, "failed to stop vdev %i: %d\n",
			    arvif->vdev_id, ret);

	arvif->is_started = false;

	if (ab->hw_params->vdev_start_delay &&
	    arvif->vdev_type == WMI_VDEV_TYPE_STA) {
		ret = ath12k_peer_delete(ar, arvif->vdev_id, arvif->bssid);
		if (ret)
			ath12k_warn(ar->ab,
				    "failed to delete peer %pM for vdev %d: %d\n",
				    arvif->bssid, arvif->vdev_id, ret);
		else
			ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
				   "mac removed peer %pM  vdev %d after vdev stop\n",
				   arvif->bssid, arvif->vdev_id);
	}
	
	if (ab->hw_params->vdev_start_delay &&
	    arvif->vdev_type == WMI_VDEV_TYPE_MONITOR)
		ath12k_wmi_vdev_down(ar, arvif->vdev_id);

	if (arvif->vdev_type != WMI_VDEV_TYPE_MONITOR &&
	    ar->num_started_vdevs == 1 && ar->monitor_vdev_created)
		ath12k_mac_monitor_stop(ar);
	
	if (arvif->vdev_type == WMI_VDEV_TYPE_STA)
		ath12k_mac_11d_scan_start(ar, arvif->vdev_id, false);

	mutex_unlock(&ar->conf_mutex);
}

static int
ath12k_mac_op_switch_vif_chanctx(struct ieee80211_hw *hw,
				 struct ieee80211_vif_chanctx_switch *vifs,
				 int n_vifs,
				 enum ieee80211_chanctx_switch_mode mode)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);

	mutex_lock(&ar->conf_mutex);

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
		   "mac chanctx switch n_vifs %d mode %d\n",
		   n_vifs, mode);
	ath12k_mac_update_vif_chan(ar, vifs, n_vifs);

	mutex_unlock(&ar->conf_mutex);

	return 0;
}

static int
ath12k_set_vdev_param_to_all_vifs(struct ath12k *ar, int param, u32 value)
{
	struct ath12k_vif *arvif;
	int ret = 0;

	mutex_lock(&ar->conf_mutex);
	list_for_each_entry(arvif, &ar->arvifs, struct ath12k_vif, list) {
		ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "setting mac vdev %d param %d value %d\n",
			   param, arvif->vdev_id, value);

		ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
						    param, value);
		if (ret) {
			ath12k_warn(ar->ab, "failed to set param %d for vdev %d: %d\n",
				    param, arvif->vdev_id, ret);
			break;
		}
	}
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

/* mac80211 stores device specific RTS/Fragmentation threshold value,
 * this is set interface specific to firmware from ath12k driver
 */
static int ath12k_mac_op_set_rts_threshold(struct ieee80211_hw *hw, u32 value)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	int param_id = WMI_VDEV_PARAM_RTS_THRESHOLD;

	return ath12k_set_vdev_param_to_all_vifs(ar, param_id, value);
}

static int ath12k_mac_op_set_frag_threshold(struct ieee80211_hw *hw, u32 value)
{
	/* Even though there's a WMI vdev param for fragmentation threshold no
	 * known firmware actually implements it. Moreover it is not possible to
	 * rely frame fragmentation to mac80211 because firmware clears the
	 * "more fragments" bit in frame control making it impossible for remote
	 * devices to reassemble frames.
	 *
	 * Hence implement a dummy callback just to say fragmentation isn't
	 * supported. This effectively prevents mac80211 from doing frame
	 * fragmentation in software.
	 */
	return -EOPNOTSUPP;
}

static void ath12k_mac_op_flush(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
				u32 queues, bool drop)
{
	struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	long time_left;

	if (drop)
		return;
	
	wait_event_timeout(ar->dp.tx_empty_waitq,
			       (atomic_read(&ar->dp.num_tx_pending) == 0),
			       ATH12K_FLUSH_TIMEOUT, time_left);
	if (time_left == 0)
		ath12k_warn(ar->ab, "failed to flush transmit queue %ld\n", time_left);
}

static int
ath12k_mac_bitrate_mask_num_ht_rates(struct ath12k *ar,
				     enum nl80211_band band,
				     const struct ieee80211_bitrate_mask *mask)
{
	int num_rates = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++)
		num_rates += hweight16(mask->control[band].ht_mcs[i]);

	return num_rates;
}

static bool
ath12k_mac_has_single_legacy_rate(struct ath12k *ar,
				  enum nl80211_band band,
				  const struct ieee80211_bitrate_mask *mask)
{
	int num_rates = 0;

	num_rates = hweight32(mask->control[band].legacy);

	if (ath12k_mac_bitrate_mask_num_ht_rates(ar, band, mask))
		return false;

	if (ath12k_mac_bitrate_mask_num_vht_rates(ar, band, mask))
		return false;

	return num_rates == 1;
}

static bool
ath12k_mac_bitrate_mask_get_single_nss(struct ath12k *ar,
				       enum nl80211_band band,
				       const struct ieee80211_bitrate_mask *mask,
				       int *nss)
{
	struct ieee80211_supported_band *sband = &ar->mac.sbands[band];
	u16 vht_mcs_map = le16_to_cpu(sband->vht_cap.vht_mcs.tx_mcs_map);
	u8 ht_nss_mask = 0;
	u8 vht_nss_mask = 0;
	int i;

	/* No need to consider legacy here. Basic rates are always present
	 * in bitrate mask
	 */

	for (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++) {
		if (mask->control[band].ht_mcs[i] == 0)
			continue;
		else if (mask->control[band].ht_mcs[i] ==
			 sband->ht_cap.mcs.rx_mask[i])
			ht_nss_mask |= BIT(i);
		else
			return false;
	}

	for (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) {
		if (mask->control[band].vht_mcs[i] == 0)
			continue;
		else if (mask->control[band].vht_mcs[i] ==
			 ath12k_mac_get_max_vht_mcs_map(vht_mcs_map, i))
			vht_nss_mask |= BIT(i);
		else
			return false;
	}

	if (ht_nss_mask != vht_nss_mask)
		return false;

	if (ht_nss_mask == 0)
		return false;

	if (BIT(fls(ht_nss_mask)) - 1 != ht_nss_mask)
		return false;

	*nss = fls(ht_nss_mask);

	return true;
}

static int
ath12k_mac_get_single_legacy_rate(struct ath12k *ar,
				  enum nl80211_band band,
				  const struct ieee80211_bitrate_mask *mask,
				  u32 *rate, u8 *nss)
{
	int rate_idx;
	u16 bitrate;
	u8 preamble;
	u16 hw_rate;

	if (hweight32(mask->control[band].legacy) != 1)
		return -EINVAL;

	rate_idx = ffs(mask->control[band].legacy) - 1;

	if (band == NL80211_BAND_5GHZ || band == NL80211_BAND_6GHZ)
		rate_idx += ATH12K_MAC_FIRST_OFDM_RATE_IDX;

	hw_rate = ath12k_legacy_rates[rate_idx].hw_value;
	bitrate = ath12k_legacy_rates[rate_idx].bitrate;

	if (ath12k_mac_bitrate_is_cck(bitrate))
		preamble = WMI_RATE_PREAMBLE_CCK;
	else
		preamble = WMI_RATE_PREAMBLE_OFDM;

	*nss = 1;
	*rate = ATH12K_HW_RATE_CODE(hw_rate, 0, preamble);

	return 0;
}

static int ath12k_mac_set_fixed_rate_params(struct ath12k_vif *arvif,
					    u32 rate, u8 nss, u8 sgi, u8 ldpc)
{
	struct ath12k *ar = arvif->ar;
	u32 vdev_param;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ath12k_dbg(ar->ab, ATH12K_DBG_MAC, "mac set fixed rate params vdev %i rate 0x%02x nss %u sgi %u\n",
		   arvif->vdev_id, rate, nss, sgi);

	vdev_param = WMI_VDEV_PARAM_FIXED_RATE;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    vdev_param, rate);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set fixed rate param 0x%02x: %d\n",
			    rate, ret);
		return ret;
	}

	vdev_param = WMI_VDEV_PARAM_NSS;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    vdev_param, nss);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set nss param %d: %d\n",
			    nss, ret);
		return ret;
	}

	vdev_param = WMI_VDEV_PARAM_SGI;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    vdev_param, sgi);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set sgi param %d: %d\n",
			    sgi, ret);
		return ret;
	}

	vdev_param = WMI_VDEV_PARAM_LDPC;
	ret = ath12k_wmi_vdev_set_param_cmd(ar, arvif->vdev_id,
					    vdev_param, ldpc);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set ldpc param %d: %d\n",
			    ldpc, ret);
		return ret;
	}

	return 0;
}

static bool
ath12k_mac_vht_mcs_range_present(struct ath12k *ar,
				 enum nl80211_band band,
				 const struct ieee80211_bitrate_mask *mask)
{
	int i;
	u16 vht_mcs;

	for (i = 0; i < NL80211_VHT_NSS_MAX; i++) {
		vht_mcs = mask->control[band].vht_mcs[i];

		switch (vht_mcs) {
		case 0:
		case BIT(8) - 1:
		case BIT(9) - 1:
		case BIT(10) - 1:
			break;
		default:
			return false;
		}
	}

	return true;
}

static void ath12k_mac_set_bitrate_mask_iter(void *data,
					     struct ieee80211_sta *sta)
{
	struct ath12k_vif *arvif = data;
	struct ath12k_sta *arsta = ieee80211_sta_get_priv_data(sta);
	struct ath12k *ar = arvif->ar;

	spin_lock_bh(&ar->data_lock);
	arsta->changed |= IEEE80211_RC_CHANGED_SUPP_RATES;
	spin_unlock_bh(&ar->data_lock);

	ieee80211_queue_work(ar->hw, &arsta->update_wk);
}

static void ath12k_mac_disable_peer_fixed_rate(void *data,
					       struct ieee80211_sta *sta)
{
	struct ath12k_vif *arvif = data;
	struct ath12k *ar = arvif->ar;
	int ret;

	ret = ath12k_wmi_set_peer_param(ar, ieee80211_sta_addr(sta),
					arvif->vdev_id,
					WMI_PEER_PARAM_FIXED_RATE,
					WMI_FIXED_RATE_NONE);
	if (ret)
		ath12k_warn(ar->ab,
			    "failed to disable peer fixed rate for STA %pM ret %d\n",
			    ieee80211_sta_addr(sta), ret);
}

static int
ath12k_mac_op_set_bitrate_mask(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif,
			       const struct ieee80211_bitrate_mask *mask)
{
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
	struct ieee80211_chan_def def;
	struct ath12k *ar = arvif->ar;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	const u16 *vht_mcs_mask;
	u32 rate;
	u8 nss;
	u8 sgi;
	u8 ldpc;
	int single_nss;
	int ret;
	int num_rates;

	if (ath12k_mac_vif_chan(vif, &def))
		return -EPERM;

	band = def.chan->band;
	ht_mcs_mask = mask->control[band].ht_mcs;
	vht_mcs_mask = mask->control[band].vht_mcs;
	ldpc = !!(ar->ht_cap_info & WMI_HT_CAP_LDPC);

	sgi = mask->control[band].gi;
	if (sgi == NL80211_TXRATE_FORCE_LGI)
		return -EINVAL;

	/* mac80211 doesn't support sending a fixed HT/VHT MCS alone, rather it
	 * requires passing at least one of used basic rates along with them.
	 * Fixed rate setting across different preambles(legacy, HT, VHT) is
	 * not supported by the FW. Hence use of FIXED_RATE vdev param is not
	 * suitable for setting single HT/VHT rates.
	 * But, there could be a single basic rate passed from userspace which
	 * can be done through the FIXED_RATE param.
	 */
	if (ath12k_mac_has_single_legacy_rate(ar, band, mask)) {
		ret = ath12k_mac_get_single_legacy_rate(ar, band, mask, &rate,
							&nss);
		if (ret) {
			ath12k_warn(ar->ab, "failed to get single legacy rate for vdev %i: %d\n",
				    arvif->vdev_id, ret);
			return ret;
		}
		ieee80211_iterate_stations_atomic(ar->hw,
						  ath12k_mac_disable_peer_fixed_rate,
						  arvif);
	} else if (ath12k_mac_bitrate_mask_get_single_nss(ar, band, mask,
							  &single_nss)) {
		rate = WMI_FIXED_RATE_NONE;
		nss = (u8)single_nss;
	} else {
		rate = WMI_FIXED_RATE_NONE;
		nss = (u8)min_t(u32, ar->num_tx_chains,
			    max(ath12k_mac_max_ht_nss(ht_mcs_mask),
				ath12k_mac_max_vht_nss(vht_mcs_mask)));

		/* If multiple rates across different preambles are given
		 * we can reconfigure this info with all peers using PEER_ASSOC
		 * command with the below exception cases.
		 * - Single VHT Rate : peer_assoc command accommodates only MCS
		 * range values i.e 0-7, 0-8, 0-9 for VHT. Though mac80211
		 * mandates passing basic rates along with HT/VHT rates, FW
		 * doesn't allow switching from VHT to Legacy. Hence instead of
		 * setting legacy and VHT rates using RATEMASK_CMD vdev cmd,
		 * we could set this VHT rate as peer fixed rate param, which
		 * will override FIXED rate and FW rate control algorithm.
		 * If single VHT rate is passed along with HT rates, we select
		 * the VHT rate as fixed rate for vht peers.
		 * - Multiple VHT Rates : When Multiple VHT rates are given,this
		 * can be set using RATEMASK CMD which uses FW rate-ctl alg.
		 * TODO: Setting multiple VHT MCS and replacing peer_assoc with
		 * RATEMASK_CMDID can cover all use cases of setting rates
		 * across multiple preambles and rates within same type.
		 * But requires more validation of the command at this point.
		 */

		num_rates = ath12k_mac_bitrate_mask_num_vht_rates(ar, band,
								  mask);

		if (!ath12k_mac_vht_mcs_range_present(ar, band, mask) &&
		    num_rates > 1) {
			/* TODO: Handle multiple VHT MCS values setting using
			 * RATEMASK CMD
			 */
			ath12k_warn(ar->ab,
				    "Setting more than one MCS Value in bitrate mask not supported\n");
			return -EINVAL;
		}

		ieee80211_iterate_stations_atomic(ar->hw,
						  ath12k_mac_disable_peer_fixed_rate,
						  arvif);

		mutex_lock(&ar->conf_mutex);

		arvif->bitrate_mask = *mask;
		ieee80211_iterate_stations_atomic(ar->hw,
						  ath12k_mac_set_bitrate_mask_iter,
						  arvif);

		mutex_unlock(&ar->conf_mutex);
	}

	mutex_lock(&ar->conf_mutex);

	ret = ath12k_mac_set_fixed_rate_params(arvif, rate, nss, sgi, ldpc);
	if (ret) {
		ath12k_warn(ar->ab, "failed to set fixed rate params on vdev %i: %d\n",
			    arvif->vdev_id, ret);
	}

	mutex_unlock(&ar->conf_mutex);

	return ret;
}

#if 0
static void
ath12k_mac_op_reconfig_complete(struct ieee80211_hw *hw,
				enum ieee80211_reconfig_type reconfig_type)
{
	struct ath12k *ar = hw->priv;
	struct ath12k_base *ab = ar->ab;
	int recovery_count;

	if (reconfig_type != IEEE80211_RECONFIG_TYPE_RESTART)
		return;

	mutex_lock(&ar->conf_mutex);

	if (ar->state == ATH12K_STATE_RESTARTED) {
		ath12k_warn(ar->ab, "pdev %d successfully recovered\n",
			    ar->pdev->pdev_id);
		ar->state = ATH12K_STATE_ON;
		ieee80211_wake_queues(ar->hw);

		if (ab->is_reset) {
			recovery_count = atomic_inc_return(&ab->recovery_count);
			ath12k_dbg(ab, ATH12K_DBG_BOOT, "recovery count %d\n",
				   recovery_count);
			/* When there are multiple radios in an SOC,
			 * the recovery has to be done for each radio
			 */
			if (recovery_count == ab->num_radios) {
				atomic_dec(&ab->reset_count);
				complete(&ab->reset_complete);
				ab->is_reset = false;
				atomic_set(&ab->fail_cont_count, 0);
				ath12k_dbg(ab, ATH12K_DBG_BOOT, "reset success\n");
			}
		}
	}

	mutex_unlock(&ar->conf_mutex);
}
#endif

#if 0
static void
ath12k_mac_update_bss_chan_survey(struct ath12k *ar,
				  struct ieee80211_channel *channel)
{
	int ret;
	enum wmi_bss_chan_info_req_type type = WMI_BSS_SURVEY_REQ_TYPE_READ;

	lockdep_assert_held(&ar->conf_mutex);

	if (!test_bit(WMI_TLV_SERVICE_BSS_CHANNEL_INFO_64, ar->ab->wmi_ab.svc_map) ||
	    ar->rx_channel != channel)
		return;

	if (ar->scan.state != ATH12K_SCAN_IDLE) {
		ath12k_dbg(ar->ab, ATH12K_DBG_MAC,
			   "ignoring bss chan info req while scanning..\n");
		return;
	}

	reinit_completion(&ar->bss_survey_done);

	ret = ath12k_wmi_pdev_bss_chan_info_request(ar, type);
	if (ret) {
		ath12k_warn(ar->ab, "failed to send pdev bss chan info request\n");
		return;
	}

	ret = wait_for_completion_timeout(&ar->bss_survey_done, 3 * HZ);
	if (ret == 0)
		ath12k_warn(ar->ab, "bss channel survey timed out\n");
}

static int ath12k_mac_op_get_survey(struct ieee80211_hw *hw, int idx,
				    struct survey_info *survey)
{
	struct ath12k *ar = hw->priv;
	struct ieee80211_supported_band *sband;
	struct survey_info *ar_survey;
	int ret = 0;

	if (idx >= ATH12K_NUM_CHANS)
		return -ENOENT;

	ar_survey = &ar->survey[idx];

	mutex_lock(&ar->conf_mutex);

	sband = hw->wiphy->bands[NL80211_BAND_2GHZ];
	if (sband && idx >= sband->n_channels) {
		idx -= sband->n_channels;
		sband = NULL;
	}

	if (!sband)
		sband = hw->wiphy->bands[NL80211_BAND_5GHZ];

	if (!sband || idx >= sband->n_channels) {
		ret = -ENOENT;
		goto exit;
	}

	ath12k_mac_update_bss_chan_survey(ar, &sband->channels[idx]);

	spin_lock_bh(&ar->data_lock);
	memcpy(survey, ar_survey, sizeof(*survey));
	spin_unlock_bh(&ar->data_lock);

	survey->channel = &sband->channels[idx];

	if (ar->rx_channel == survey->channel)
		survey->filled |= SURVEY_INFO_IN_USE;

exit:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}

static void ath12k_mac_op_sta_statistics(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif,
					 struct ieee80211_sta *sta,
					 struct station_info *sinfo)
{
	struct ath12k_sta *arsta = ieee80211_sta_from_drv_priv(sta);

	sinfo->rx_duration = arsta->rx_duration;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_DURATION);

	sinfo->tx_duration = arsta->tx_duration;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_DURATION);

	if (!arsta->txrate.legacy && !arsta->txrate.nss)
		return;

	if (arsta->txrate.legacy) {
		sinfo->txrate.legacy = arsta->txrate.legacy;
	} else {
		sinfo->txrate.mcs = arsta->txrate.mcs;
		sinfo->txrate.nss = arsta->txrate.nss;
		sinfo->txrate.bw = arsta->txrate.bw;
		sinfo->txrate.he_gi = arsta->txrate.he_gi;
		sinfo->txrate.he_dcm = arsta->txrate.he_dcm;
		sinfo->txrate.he_ru_alloc = arsta->txrate.he_ru_alloc;
	}
	sinfo->txrate.flags = arsta->txrate.flags;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);

	/* TODO: Use real NF instead of default one. */
	sinfo->signal = arsta->rssi_comb + ATH12K_DEFAULT_NOISE_FLOOR;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
}
#endif

static int
ath12k_mac_set_country_code(struct ath12k *ar, u8 *ccode)
{
    int ret = 0;
	struct wmi_set_current_country_params param;

	if ( !ccode || ccode[0] == '\0' || ccode[1] == '\0') {
        return -EINVAL; 
	}

	param.alpha2[0] = ccode[0];
	param.alpha2[1] = ccode[1];

    ret = ath12k_wmi_send_set_current_country_cmd(ar, &param);
	return ret;
}

static int 
ath12k_mac_set_beacon_filter(struct ieee80211_hw *hw, struct ieee80211_vif *vif, const u32 *ies, u32 ies_cnt)
{
    struct ath12k *ar = ieee80211_hw_to_priv_data(hw);
	struct ath12k_vif *arvif = ieee80211_vif_get_priv_data(vif);
    int ret = 0;

	ret = ath12k_wmi_set_beacon_filter(ar, arvif->vdev_id, ies, ies_cnt);
	return ret;
}

static int ath12k_mac_op_priv_command(struct ieee80211_hw *hw, 
    struct ieee80211_priv_cmd *cmd)
{
    struct ath12k *ar = ieee80211_hw_to_priv_data(hw);

    if (!cmd)
        return -EINVAL;

    switch (cmd->id) {
    case IEEE80211_PRIV_CMD_RDDM:
        return ath12k_hif_dump_target(ar->ab);
	case IEEE80211_PRIV_CMD_CCODE:
		if (cmd->len != 2)
			return -EINVAL;
		return ath12k_mac_set_country_code(ar, cmd->data);
    default:
        ath12k_warn(ar->ab, "priv command %d is not supported\n", cmd->id);
        break;
    }

    return -ENOPARAM;
}

static const struct ieee80211_ops ath12k_ops = {
	.ieee80211_tx				= ath12k_mac_op_tx,
	.ieee80211_start            = ath12k_mac_op_start,
	.ieee80211_stop             = ath12k_mac_op_stop,
	//.reconfig_complete              	= ath12k_mac_op_reconfig_complete,
	.ieee80211_add_interface    = ath12k_mac_op_add_interface,
	.ieee80211_remove_interface	= ath12k_mac_op_remove_interface,
	//.update_vif_offload			= ath12k_mac_op_update_vif_offload,
	.ieee80211_config           = ath12k_mac_op_config,
	.ieee80211_bss_info_changed = ath12k_mac_op_bss_info_changed,
	//.configure_filter				= ath12k_mac_op_configure_filter,
	.ieee80211_hw_scan          = ath12k_mac_op_hw_scan,
	.ieee80211_cancel_hw_scan   = ath12k_mac_op_cancel_hw_scan,
	.ieee80211_set_key          = ath12k_mac_op_set_key,
	.ieee80211_sta_state        = ath12k_mac_op_sta_state,
	.ieee80211_sta_set_txpwr	= ath12k_mac_op_sta_set_txpwr,
	.ieee80211_sta_rc_update	= ath12k_mac_op_sta_rc_update,
	.ieee80211_conf_tx          = ath12k_mac_op_conf_tx,
	.ieee80211_set_antenna			= ath12k_mac_op_set_antenna,
	.ieee80211_get_antenna			= ath12k_mac_op_get_antenna,
	.ieee80211_ampdu_action			= ath12k_mac_op_ampdu_action,
	.ieee80211_add_chanctx			= ath12k_mac_op_add_chanctx,
	.ieee80211_remove_chanctx		= ath12k_mac_op_remove_chanctx,
	.ieee80211_change_chanctx		= ath12k_mac_op_change_chanctx,
	.ieee80211_assign_vif_chanctx	= ath12k_mac_op_assign_vif_chanctx,
	.ieee80211_unassign_vif_chanctx	= ath12k_mac_op_unassign_vif_chanctx,
	.ieee80211_switch_vif_chanctx	= ath12k_mac_op_switch_vif_chanctx,
	.ieee80211_set_rts_threshold	= ath12k_mac_op_set_rts_threshold,
	.ieee80211_set_frag_threshold	= ath12k_mac_op_set_frag_threshold,
	//.set_bitrate_mask				= ath12k_mac_op_set_bitrate_mask,
	//.get_survey						= ath12k_mac_op_get_survey,
	//.flush							= ath12k_mac_op_flush,
	//.sta_statistics					= ath12k_mac_op_sta_statistics,
	.ieee80211_set_beacon_filter    = ath12k_mac_set_beacon_filter,
	.ieee80211_priv_command         = ath12k_mac_op_priv_command,
};

static void ath12k_mac_update_ch_list(struct ath12k *ar,
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

static u32 ath12k_get_phy_id(struct ath12k *ar, u32 band)
{
	struct ath12k_pdev *pdev = ar->pdev;
	struct ath12k_pdev_cap *pdev_cap = &pdev->cap;

	if (band == WMI_HOST_WLAN_2G_CAP)
		return pdev_cap->band[NL80211_BAND_2GHZ].phy_id;

	if (band == WMI_HOST_WLAN_5G_CAP)
		return pdev_cap->band[NL80211_BAND_5GHZ].phy_id;

	ath12k_warn(ar->ab, "unsupported phy cap:%d\n", band);

	return 0;
}

static int ath12k_mac_setup_channels_rates(struct ath12k *ar,
					   u32 supported_bands)
{
	struct ieee80211_supported_band *band;
	struct ath12k_wmi_hal_reg_capabilities_ext_arg *reg_cap, *temp_reg_cap;
	void *channels;
	u32 phy_id;

	BUILD_BUG_ON((ARRAY_SIZE(ath12k_2ghz_channels) +
		      ARRAY_SIZE(ath12k_5ghz_channels) +
		      ARRAY_SIZE(ath12k_6ghz_channels)) !=
		     ATH12K_NUM_CHANS);

	reg_cap = &ar->ab->hal_reg_cap[ar->pdev_idx];
	temp_reg_cap = reg_cap;

	if (supported_bands & WMI_HOST_WLAN_2G_CAP) {
		channels = kmemdup(ath12k_2ghz_channels,
				   sizeof(ath12k_2ghz_channels),
				   GFP_KERNEL);
		if (!channels)
			return -ENOMEM;

		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		band->band = NL80211_BAND_2GHZ;
		band->n_channels = ARRAY_SIZE(ath12k_2ghz_channels);
		band->channels = channels;
		band->n_bitrates = ath12k_g_rates_size;
		band->bitrates = ath12k_g_rates;
		ieee80211_hw_set_sband(ar->hw, NL80211_BAND_2GHZ, band);

		if (ar->ab->hw_params->single_pdev_only) {
			phy_id = ath12k_get_phy_id(ar, WMI_HOST_WLAN_2G_CAP);
			temp_reg_cap = &ar->ab->hal_reg_cap[phy_id];
		}
		ath12k_mac_update_ch_list(ar, band,
					  temp_reg_cap->low_2ghz_chan,
					  temp_reg_cap->high_2ghz_chan);
	}

	if (supported_bands & WMI_HOST_WLAN_5G_CAP) {
		if (reg_cap->high_5ghz_chan >= ATH12K_MAX_6G_FREQ && !cfg_is_ath_6G_disabled()) {
			channels = kmemdup(ath12k_6ghz_channels,
					   sizeof(ath12k_6ghz_channels), GFP_KERNEL);
			if (!channels) {
				kfree(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
				return -ENOMEM;
			}

			ar->supports_6ghz = true;
			band = &ar->mac.sbands[NL80211_BAND_6GHZ];
			band->band = NL80211_BAND_6GHZ;
			band->n_channels = ARRAY_SIZE(ath12k_6ghz_channels);
			band->channels = channels;
			band->n_bitrates = ath12k_a_rates_size;
			band->bitrates = ath12k_a_rates;
			ieee80211_hw_set_sband(ar->hw, NL80211_BAND_6GHZ, band);
			
			if (ar->ab->hw_params->single_pdev_only) {
				phy_id = ath12k_get_phy_id(ar, WMI_HOST_WLAN_5G_CAP);
				temp_reg_cap = &ar->ab->hal_reg_cap[phy_id];
			}
			ath12k_mac_update_ch_list(ar, band,
						  temp_reg_cap->low_5ghz_chan,
						  temp_reg_cap->high_5ghz_chan);
		}

		if (reg_cap->low_5ghz_chan < ATH12K_MIN_6G_FREQ) {
			channels = kmemdup(ath12k_5ghz_channels,
					   sizeof(ath12k_5ghz_channels),
					   GFP_KERNEL);
			if (!channels) {
				kfree(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
				kfree(ar->mac.sbands[NL80211_BAND_6GHZ].channels);
				return -ENOMEM;
			}

			band = &ar->mac.sbands[NL80211_BAND_5GHZ];
			band->band = NL80211_BAND_5GHZ;
			band->n_channels = ARRAY_SIZE(ath12k_5ghz_channels);
			band->channels = channels;
			band->n_bitrates = ath12k_a_rates_size;
			band->bitrates = ath12k_a_rates;
			ieee80211_hw_set_sband(ar->hw, NL80211_BAND_5GHZ, band);

			if (ar->ab->hw_params->single_pdev_only) {
				phy_id = ath12k_get_phy_id(ar, WMI_HOST_WLAN_5G_CAP);
				temp_reg_cap = &ar->ab->hal_reg_cap[phy_id];
			}

			ath12k_mac_update_ch_list(ar, band,
						  temp_reg_cap->low_5ghz_chan,
						  temp_reg_cap->high_5ghz_chan);
		}
	}

	return 0;
}

static int ath12k_mac_setup_iface_combinations(struct ath12k *ar)
{
#if 0
	struct ath12k_base *ab = ar->ab;
	struct ieee80211_iface_combination *combinations;
	struct ieee80211_iface_limit *limits;
	int n_limits, max_interfaces;
	bool ap, mesh;

	ap = ab->hw_params->interface_modes & BIT(NL80211_IFTYPE_AP);

	mesh = IS_ENABLED(CONFIG_MAC80211_MESH) &&
		ab->hw_params->interface_modes & BIT(NL80211_IFTYPE_MESH_POINT);

	combinations = kzalloc(sizeof(*combinations), GFP_KERNEL);
	if (!combinations)
		return -ENOMEM;

	if (ap || mesh) {
		n_limits = 2;
		max_interfaces = 16;
	} else {
		n_limits = 1;
		max_interfaces = 1;
	}

	limits = kcalloc(n_limits, sizeof(*limits), GFP_KERNEL);
	if (!limits) {
		kfree(combinations);
		return -ENOMEM;
	}

	limits[0].max = 1;
	limits[0].types |= BIT(NL80211_IFTYPE_STATION);

	if (ap) {
		limits[1].max = max_interfaces;
		limits[1].types |= BIT(NL80211_IFTYPE_AP);
	}

	if (mesh)
		limits[1].types |= BIT(NL80211_IFTYPE_MESH_POINT);

	combinations[0].limits = limits;
	combinations[0].n_limits = n_limits;
	combinations[0].max_interfaces = max_interfaces;
	combinations[0].num_different_channels = 1;
	combinations[0].beacon_int_infra_match = true;
	combinations[0].beacon_int_min_gcd = 100;
	combinations[0].radar_detect_widths = BIT(NL80211_CHAN_WIDTH_20_NOHT) |
						BIT(NL80211_CHAN_WIDTH_20) |
						BIT(NL80211_CHAN_WIDTH_40) |
						BIT(NL80211_CHAN_WIDTH_80);

	ar->hw->wiphy->iface_combinations = combinations;
	ar->hw->wiphy->n_iface_combinations = 1;

	return 0;
#endif
	return 0;
}

#if 0
static const u8 ath12k_if_types_ext_capa[] = {
	[0] = WLAN_EXT_CAPA1_EXT_CHAN_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
};

static const u8 ath12k_if_types_ext_capa_sta[] = {
	[0] = WLAN_EXT_CAPA1_EXT_CHAN_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
	[9] = WLAN_EXT_CAPA10_TWT_REQUESTER_SUPPORT,
};

static const u8 ath12k_if_types_ext_capa_ap[] = {
	[0] = WLAN_EXT_CAPA1_EXT_CHAN_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
	[9] = WLAN_EXT_CAPA10_TWT_RESPONDER_SUPPORT,
};

static const struct wiphy_iftype_ext_capab ath12k_iftypes_ext_capa[] = {
	{
		.extended_capabilities = ath12k_if_types_ext_capa,
		.extended_capabilities_mask = ath12k_if_types_ext_capa,
		.extended_capabilities_len = sizeof(ath12k_if_types_ext_capa),
	}, {
		.iftype = NL80211_IFTYPE_STATION,
		.extended_capabilities = ath12k_if_types_ext_capa_sta,
		.extended_capabilities_mask = ath12k_if_types_ext_capa_sta,
		.extended_capabilities_len =
				sizeof(ath12k_if_types_ext_capa_sta),
	}, {
		.iftype = NL80211_IFTYPE_AP,
		.extended_capabilities = ath12k_if_types_ext_capa_ap,
		.extended_capabilities_mask = ath12k_if_types_ext_capa_ap,
		.extended_capabilities_len =
				sizeof(ath12k_if_types_ext_capa_ap),
	},
};
#endif

static void __ath12k_mac_unregister(struct ath12k *ar)
{
	cancel_work_sync(&ar->regd_update_work);

	ieee80211_unregister_hw(ar->hw);

	idr_for_each(&ar->txmgmt_idr, ath12k_mac_tx_mgmt_pending_free, ar);
	idr_destroy(&ar->txmgmt_idr);

	kfree(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
	kfree(ar->mac.sbands[NL80211_BAND_5GHZ].channels);
	kfree(ar->mac.sbands[NL80211_BAND_6GHZ].channels);

	//kfree(ar->hw->wiphy->iface_combinations[0].limits);
	//kfree(ar->hw->wiphy->iface_combinations);

	ieee80211_set_dev(ar->hw, NULL);
}

void ath12k_mac_unregister(struct ath12k_base *ab)
{
	struct ath12k *ar;
	struct ath12k_pdev *pdev;
	u8 i;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		if (!ar)
			continue;

		__ath12k_mac_unregister(ar);
	}
}

static int __ath12k_mac_register(struct ath12k *ar)
{
	struct ath12k_base *ab = ar->ab;
	struct ath12k_pdev_cap *cap = &ar->pdev->cap;
	static const u32 cipher_suites[] = {
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

	ath12k_pdev_caps_update(ar);

	ieee80211_set_perm_addr(ar->hw, ar->mac_addr);

	ieee80211_set_dev(ar->hw, ab->dev);

	ret = ath12k_mac_setup_channels_rates(ar,
					      cap->supported_bands);
	if (ret)
		goto err_free;

	ath12k_mac_setup_ht_vht_cap(ar, cap, &ht_cap);
	ath12k_mac_setup_he_cap(ar, cap);

#if 0
	ret = ath12k_mac_setup_iface_combinations(ar);
	if (ret) {
		ath12k_err(ar->ab, "failed to setup interface combinations: %d\n", ret);
		goto err_free_channels;
	}
#endif

	ieee80211_hw_set_available_chains(ar->hw, (u8)cap->rx_chain_mask, (u8)cap->tx_chain_mask);
	//ar->hw->wiphy->available_antennas_rx = cap->rx_chain_mask;
	//ar->hw->wiphy->available_antennas_tx = cap->tx_chain_mask;

	//ar->hw->wiphy->interface_modes = ab->hw_params->interface_modes;

	if (ab->hw_params->single_pdev_only && ar->supports_6ghz)
		ieee80211_hw_set(ar->hw, SINGLE_SCAN_ON_ALL_BANDS);
	
	ieee80211_hw_set(ar->hw, SIGNAL_DBM);
	ieee80211_hw_set(ar->hw, SUPPORTS_PS);
	ieee80211_hw_set(ar->hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(ar->hw, MFP_CAPABLE);
	ieee80211_hw_set(ar->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(ar->hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(ar->hw, AP_LINK_PS);
	ieee80211_hw_set(ar->hw, SPECTRUM_MGMT);
	ieee80211_hw_set(ar->hw, CONNECTION_MONITOR);
	ieee80211_hw_set(ar->hw, SUPPORTS_PER_STA_GTK);
	ieee80211_hw_set(ar->hw, CHANCTX_STA_CSA);
	ieee80211_hw_set(ar->hw, QUEUE_CONTROL);
	ieee80211_hw_set(ar->hw, SUPPORTS_TX_FRAG);
	ieee80211_hw_set(ar->hw, REPORTS_LOW_ACK);

	//Set Ethernet mode
	ieee80211_hw_set(ar->hw, SUPPORTS_TX_ENCAP_OFFLOAD);
	ieee80211_hw_set(ar->hw, SUPPORTS_RX_DECAP_OFFLOAD);

	if (ht_cap & WMI_HT_CAP_ENABLED || ar->supports_6ghz) {
		ieee80211_hw_set(ar->hw, AMPDU_AGGREGATION);
		ieee80211_hw_set(ar->hw, TX_AMPDU_SETUP_IN_HW);
		ieee80211_hw_set(ar->hw, SUPPORTS_REORDERING_BUFFER);
		ieee80211_hw_set(ar->hw, SUPPORTS_AMSDU_IN_AMPDU);
		ieee80211_hw_set(ar->hw, USES_RSS);
	}

#if 0
	ar->hw->wiphy->features |= NL80211_FEATURE_STATIC_SMPS;
	ar->hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	/* TODO: Check if HT capability advertised from firmware is different
	 * for each band for a dual band capable radio. It will be tricky to
	 * handle it when the ht capability different for each band.
	 */
	if (ht_cap & WMI_HT_CAP_DYNAMIC_SMPS || ar->supports_6ghz)
		ar->hw->wiphy->features |= NL80211_FEATURE_DYNAMIC_SMPS;
#endif

#if 0
	ar->hw->wiphy->max_scan_ssids = WLAN_SCAN_PARAMS_MAX_SSID;
	ar->hw->wiphy->max_scan_ie_len = WLAN_SCAN_PARAMS_MAX_IE_LEN;

	ar->hw->max_listen_interval = ATH12K_MAX_HW_LISTEN_INTERVAL;

	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;
	ar->hw->wiphy->max_remain_on_channel_duration = 5000;

	ar->hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;
	ar->hw->wiphy->features |= NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE |
				   NL80211_FEATURE_AP_SCAN;
#endif
	ieee80211_hw_set_max_scan_ssids(ar->hw, WLAN_SCAN_PARAMS_MAX_SSID);
    ieee80211_hw_set_max_scan_ie_len(ar->hw, WLAN_SCAN_PARAMS_MAX_IE_LEN);
    ieee80211_hw_set_max_listen_interval(ar->hw, ATH12K_MAX_HW_LISTEN_INTERVAL);
    ieee80211_hw_set_max_rx_aggregation_subframes(ar->hw, IEEE80211_AMPDU_MAX_BUF);
	
	ar->max_num_stations = TARGET_NUM_STATIONS;
	ar->max_num_peers = TARGET_NUM_PEERS_PDEV;

#if 0
	ar->hw->wiphy->max_ap_assoc_sta = ar->max_num_stations;

	ar->hw->queues = ATH12K_HW_MAX_QUEUES;
	ar->hw->wiphy->tx_queue_len = ATH12K_QUEUE_LEN;
	ar->hw->offchannel_tx_hw_queue = ATH12K_HW_MAX_QUEUES - 1;
	ar->hw->max_rx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF_HE;

	ar->hw->vif_data_size = sizeof(struct ath12k_vif);
	ar->hw->sta_data_size = sizeof(struct ath12k_sta);
#endif
	ieee80211_hw_set_queues(ar->hw, ATH12K_HW_MAX_QUEUES);

    ieee80211_hw_set_vif_data_size(ar->hw, sizeof(struct ath12k_vif));
    ieee80211_hw_set_sta_data_size(ar->hw, sizeof(struct ath12k_sta));

    ieee80211_hw_set_supported_cipher_suites(
        ar->hw, cipher_suites, ARRAY_SIZE(cipher_suites));

#if 0	
	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_STA_TX_PWR);

	ar->hw->wiphy->cipher_suites = cipher_suites;
	ar->hw->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

	ar->hw->wiphy->iftype_ext_capab = ath12k_iftypes_ext_capa;
	ar->hw->wiphy->num_iftype_ext_capab =
		ARRAY_SIZE(ath12k_iftypes_ext_capa);
#endif

#if 0
	if (ar->supports_6ghz) {
		wiphy_ext_feature_set(ar->hw->wiphy,
				      NL80211_EXT_FEATURE_FILS_DISCOVERY);
		wiphy_ext_feature_set(ar->hw->wiphy,
				      NL80211_EXT_FEATURE_UNSOL_BCAST_PROBE_RESP);
	}
#endif
	
	ath12k_reg_init(ar);

#if 0
	if (!test_bit(ATH12K_FLAG_RAW_MODE, &ab->dev_flags)) {
		ar->hw->netdev_features = NETIF_F_HW_CSUM;
		ieee80211_hw_set(ar->hw, SW_CRYPTO_CONTROL);
		ieee80211_hw_set(ar->hw, SUPPORT_FAST_XMIT);
	}
#endif
	
	ret = ieee80211_register_hw(ar->hw);
	if (ret) {
		ath12k_err(ar->ab, "ieee80211 registration failed: %d\n", ret);
		goto err_free;
	}

#if 0
	if (!ab->hw_params->supports_monitor)
		/* There's a race between calling ieee80211_register_hw()
		 * and here where the monitor mode is enabled for a little
		 * while. But that time is so short and in practise it make
		 * a difference in real life.
		 */
		ar->hw->wiphy->interface_modes &= ~BIT(NL80211_IFTYPE_MONITOR);
#endif
	
	/* Apply the regd received during initialization */
	ret = ath12k_regd_update(ar, true);
	if (ret) {
		ath12k_err(ar->ab, "ath12k regd update failed: %d\n", ret);
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

u8 ath12k_get_wlan_mac_from_dpp(u8 *mac_addr)
{
    return dpp_get_wlan_mac_address(mac_addr);
}

int ath12k_mac_register(struct ath12k_base *ab)
{
	struct ath12k *ar;
	struct ath12k_pdev *pdev;
	u8 i;
	int ret;

	if (test_bit(ATH12K_FLAG_REGISTERED, &ab->dev_flags))
		return 0;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;

#if SUPPORT_QCOM_DPP
		/* For Hamoa UEFI, will first try to use the MAC address from DPP file.*/
		if (ath12k_get_wlan_mac_from_dpp(ar->mac_addr)) {
            ath12k_info(ab, "Get mac from DPP: 0x%02x-0x%02x-0x%02x-0x%02x-0x%02x-0x%02x", 
				ar->mac_addr[0], ar->mac_addr[1], ar->mac_addr[2], 
				ar->mac_addr[3], ar->mac_addr[4], ar->mac_addr[5]);
		} else
#endif
		{
			/* Get MAC address on X86 UEFI. */
			if (ab->pdevs_macaddr_valid) {
				ether_addr_copy(ar->mac_addr, pdev->mac_addr);
			} else {
				ether_addr_copy(ar->mac_addr, ab->mac_addr);
				ar->mac_addr[4] += i;
			}
		}

		ret = __ath12k_mac_register(ar);
		if (ret)
			goto err_cleanup;

		idr_init(&ar->txmgmt_idr);
		spin_lock_init(&ar->txmgmt_idr_lock);
	}

	/* Initialize channel counters frequency value in hertz */
	ab->cc_freq_hz = 320000;
	ab->free_vdev_map = (1LL << (ab->num_radios * TARGET_NUM_VDEVS)) - 1;

	return 0;

err_cleanup:
	for (i = i - 1; i >= 0; i--) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		__ath12k_mac_unregister(ar);
	}

	return ret;
}

int ath12k_mac_allocate(struct ath12k_base *ab)
{
	struct ieee80211_hw *hw;
	struct ath12k *ar;
	struct ath12k_pdev *pdev;
	int ret;
	u8 i;

	if (test_bit(ATH12K_FLAG_REGISTERED, &ab->dev_flags))
		return 0;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		hw = ieee80211_alloc_hw(sizeof(struct ath12k), &ath12k_ops);
		if (!hw) {
			ath12k_warn(ab, "failed to allocate mac80211 hw device\n");
			ret = -ENOMEM;
			goto err_free_mac;
		}

		ar = ieee80211_hw_to_priv_data(hw);
		ar->hw = hw;
		ar->ab = ab;
		ar->pdev = pdev;
		ar->pdev_idx = i;
		ar->lmac_id = ath12k_hw_get_mac_from_pdev_id(ab->hw_params, i);

		ar->wmi = &ab->wmi_ab.wmi[i];
		/* FIXME: wmi[0] is already initialized during attach,
		 * Should we do this again?
		 */
		ath12k_wmi_pdev_attach(ab, i);

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
		init_completion(&ar->vdev_delete_done);
		init_completion(&ar->peer_assoc_done);
		init_completion(&ar->peer_delete_done);
		init_completion(&ar->install_key_done);
		init_completion(&ar->bss_survey_done);
		init_completion(&ar->scan.started);
		init_completion(&ar->scan.completed);

		init_delayed_work(&ar->scan.timeout, ath12k_scan_timeout_work, ar);
		init_work(&ar->regd_update_work, ath12k_regd_update_work, ar);

		init_work(&ar->wmi_mgmt_tx_work, ath12k_mgmt_over_wmi_tx_work, ar);
		skb_queue_head_init(&ar->wmi_mgmt_tx_queue);
		clear_bit(ATH12K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
		ar->vdev_id_11d_scan = ATH12K_11D_INVALID_VDEV_ID;
		init_completion(&ar->completed_11d_scan);
	}

	return 0;

err_free_mac:
	ath12k_mac_destroy(ab);

	return ret;
}

void ath12k_mac_destroy(struct ath12k_base *ab)
{
	struct ath12k *ar;
	struct ath12k_pdev *pdev;
	u8 i;

	for (i = 0; i < ab->num_radios; i++) {
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		if (!ar)
			continue;

		ieee80211_free_hw(ar->hw);
		pdev->ar = NULL;
	}
}
