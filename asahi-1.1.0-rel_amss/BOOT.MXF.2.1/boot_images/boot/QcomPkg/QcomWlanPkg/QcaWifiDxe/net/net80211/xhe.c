/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 28/9/22   zxue     fix the nss value
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/ndebug.h>
#include "net80211_i.h"
#include "sta.h"
#include "vif.h"
#include "chan.h"

static void
ieee80211_update_from_he_6ghz_capa(
    const struct ieee80211_he_6ghz_cap *he_6ghz_cap,
    struct net80211_sta *sta)
{
    static const u16 ieee80211_vht_max_amsdu_len_map[] = {
        [IEEE80211_VHTCAP_MAX_MPDU_LENGTH_3895] = 3895,
        [IEEE80211_VHTCAP_MAX_MPDU_LENGTH_7991] = 7991,
        [IEEE80211_VHTCAP_MAX_MPDU_LENGTH_11454] = 11454,
    };

    u16 max_mpdu_len_idx;

    /* smps_mode: only STA mode is support here */
    sta->smps_mode = IEEE80211_SMPS_NONE;

    /* max_mpdu_len */
    max_mpdu_len_idx = le16_get_bits(he_6ghz_cap->cap,
        IEEE80211_HE_6GHZCAP_MAX_MPDU_LEN);
    if (max_mpdu_len_idx >= (u16)ARRAY_LENGTH(ieee80211_vht_max_amsdu_len_map))
        max_mpdu_len_idx = 0;
    sta->max_amsdu_len = ieee80211_vht_max_amsdu_len_map[max_mpdu_len_idx];
    
    /* he_6ghz_cap */
	sta->he_6ghz_cap = *he_6ghz_cap;
}

u8 *
ieee80211_ie_build_he_cap(u8 *pos,
    const struct ieee80211_sta_he_cap *sta_he_cap,
    u8 *end)
{
    u8 *original_pos = pos;
    u8 size;
    u8 ie_len;

    if (!sta_he_cap)
        return original_pos;

    size = ieee80211_he_mcs_nss_size(&sta_he_cap->he_capabilities);
    ie_len = 2 + 1 + size +
        sizeof(sta_he_cap->he_capabilities) +
        ieee80211_he_ppe_size(sta_he_cap->ppe_thres[0],
            sta_he_cap->he_capabilities.phy_cap_info);

    if ((end - pos) < ie_len)
        return original_pos;

    *pos++ = WLAN_EID_EXTENSION;
    pos++; /* Will set the size later*/
    *pos++ = WLAN_EID_EXT_HE_CAPABILITIES;

    /* Copy the he_capabilities */
    memcpy(pos, &sta_he_cap->he_capabilities, sizeof(sta_he_cap->he_capabilities));
    pos += sizeof(sta_he_cap->he_capabilities);

    /* Copy the he_mcs_nss_supp */
    memcpy(pos, &sta_he_cap->he_mcs_nss_supp, size);
    pos += size;

    /* Check if need to present the PPE Threshold*/
    if ((sta_he_cap->he_capabilities.phy_cap_info[6] & IEEE80211_HEPHY_CAP6_PPE_THRESHOLD_PRESENT) == 0)
        goto end;

    /*
     * Check how many PPET16/PPET8 pairs.
     * Algorithm: (NSS_M1 + 1) x (num of 1 bits in RU_INDEX_BITMASK)
     */
    size = (u8)hweight8(sta_he_cap->ppe_thres[0] & IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_MASK);
    size *= (1 + ((sta_he_cap->ppe_thres[0] & IEEE80211_HE_PPE_THRES_NSS_MASK) >>
        IEEE80211_HE_PPE_THRES_NSS_POS));

    /* Each pair is 6 bits, add the another 7 bits "header" to the total size.*/
    size = (size * IEEE80211_HE_PPE_THRES_INFO_PPET_SIZE * 2) + 7;
    size = DIV_ROUND_UP(size, 8);

    /* Copy the PPE Thresholds */
    memcpy(pos, &sta_he_cap->ppe_thres, size);
    pos += size;

end:
    /* update the size */
    original_pos[1] = (u8)((pos - original_pos) - 2);

    return pos;
}

u8 *
ieee80211_ie_build_he_6ghz_cap(u8 *pos, __le16 cap, u8 *end)
{
	if ((end - pos) < 5)
		return pos;

	*pos++ = WLAN_EID_EXTENSION;
	*pos++ = 1 + sizeof(cap);
	*pos++ = WLAN_EID_EXT_HE_6GHZ_BAND_CAP;
	memcpy(pos, &cap, sizeof(cap));

	return pos + sizeof(cap);
}

void 
net80211_vif_build_he_6ghz_cap(struct net80211_vif *vif,
    struct sk_buff *skb)
{
	struct ieee80211_supported_band *sband;
	const struct ieee80211_sband_iftype_data *iftd;
	enum nl80211_iftype iftype = NL80211_IFTYPE_STATION;   //Only support STA mode
	u8 *pos;
	u16 cap;

    struct ieee80211_chanctx_conf *chanctx_conf = vif->chanctx_conf;
    enum nl80211_band band = chanctx_conf->def.chan->band;
	sband = net80211_get_sband(vif->pdev, band);
	if (!sband)
		return;

	iftd = ieee80211_get_sband_iftype_data(sband, iftype);
	if (WARN_ON(!iftd))
		return;

	/* Check for device HE 6 GHz capability before adding element */
	if (!iftd->he_6ghz_cap.cap)
		return;

	cap = le16_to_cpu(iftd->he_6ghz_cap.cap);
	cap &= ~IEEE80211_HE_6GHZCAP_SM_PS;

	switch (vif->smps_mode) {
	case IEEE80211_SMPS_AUTOMATIC:
	case IEEE80211_SMPS_NUM_MODES:
		WARN_ON(1);
		//fallthrough;
	case IEEE80211_SMPS_NONE:
		cap |= u16_encode_bits(WLAN_HTCAP_SM_PS_DISABLED,
				       IEEE80211_HE_6GHZCAP_SM_PS);
		break;
	case IEEE80211_SMPS_STATIC:
		cap |= u16_encode_bits(WLAN_HTCAP_SM_PS_STATIC,
				       IEEE80211_HE_6GHZCAP_SM_PS);
		break;
	case IEEE80211_SMPS_DYNAMIC:
		cap |= u16_encode_bits(WLAN_HTCAP_SM_PS_DYNAMIC,
				       IEEE80211_HE_6GHZCAP_SM_PS);
		break;
	}

	pos = skb_put(skb, 2 + 1 + sizeof(cap));
	ieee80211_ie_build_he_6ghz_cap(pos, cpu_to_le16(cap),
				    pos + 2 + 1 + sizeof(cap));
}

bool
net80211_chandef_he_6ghz_oper(struct net80211_vif *vif,
    const struct ieee80211_he_operation *he_oper,
    struct ieee80211_chan_def *chandef)
{
	const struct ieee80211_supported_band *sband;
	enum nl80211_iftype iftype = NL80211_IFTYPE_STATION;   //Only support STA mode
	const struct ieee80211_sta_he_cap *he_cap;
	struct ieee80211_chan_def he_chandef = *chandef;
	const struct ieee80211_he_6ghz_oper *he_6ghz_oper;
	bool support_80_80, support_160;
	u8 he_phy_cap;
	u32 freq;

	if (chandef->chan->band != NL80211_BAND_6GHZ)
		return true;

	sband = net80211_get_sband(vif->pdev, chandef->chan->band);

	he_cap = ieee80211_get_iftype_he_cap(sband, iftype);
	if (!he_cap) {
		net_warn("Missing iftype sband data/HE cap");
		return false;
	}

	he_phy_cap = he_cap->he_capabilities.phy_cap_info[0];
	support_160 =
		he_phy_cap &
		IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;
	support_80_80 =
		he_phy_cap &
		IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;

	if (!he_oper) {
		net_warn("HE is not advertised on (on %d MHz), expect issues\n", chandef->chan->center_freq);
		return false;
	}

	he_6ghz_oper = ieee80211_he_6ghz_operation(he_oper);

	if (!he_6ghz_oper) {
		net_warn("HE 6GHz operation missing (on %d MHz), expect issues\n", chandef->chan->center_freq);
		return false;
	}

	freq = ieee80211_channel_to_frequency(he_6ghz_oper->primary_chan,
					      NL80211_BAND_6GHZ);
	he_chandef.chan = net80211_get_channel(vif->pdev, freq);

	switch (u8_get_bits(he_6ghz_oper->control,
        IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH)) {
	case IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH_20MHZ:
		he_chandef.width = NL80211_CHAN_WIDTH_20;
		break;
	case IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH_40MHZ:
		he_chandef.width = NL80211_CHAN_WIDTH_40;
		break;
	case IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH_80MHZ:
		he_chandef.width = NL80211_CHAN_WIDTH_80;
		break;
	case IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH_160MHZ:
		he_chandef.width = NL80211_CHAN_WIDTH_80;
		if (!he_6ghz_oper->center_freq_seg1)
			break;
		if (abs(he_6ghz_oper->center_freq_seg1 - he_6ghz_oper->center_freq_seg0) == 8) {
			if (support_160)
				he_chandef.width = NL80211_CHAN_WIDTH_160;
		} else {
			if (support_80_80)
				he_chandef.width = NL80211_CHAN_WIDTH_80P80;
		}
		break;
	}

	if (he_chandef.width == NL80211_CHAN_WIDTH_160) {
		he_chandef.center_freq1 =
			ieee80211_channel_to_frequency(he_6ghz_oper->center_freq_seg1,
						       NL80211_BAND_6GHZ);
	} else {
		he_chandef.center_freq1 =
			ieee80211_channel_to_frequency(he_6ghz_oper->center_freq_seg0,
						       NL80211_BAND_6GHZ);
		if (support_80_80 || support_160)
			he_chandef.center_freq2 =
				ieee80211_channel_to_frequency(he_6ghz_oper->center_freq_seg1,
							       NL80211_BAND_6GHZ);
	}

	if (!ieee80211_chandef_valid(&he_chandef)) {
		net_warn("HE 6GHz operation resulted in invalid chandef: %d MHz/%d/%d MHz/%d MHz\n",
			   he_chandef.chan ? he_chandef.chan->center_freq : 0,
			   he_chandef.width,
			   he_chandef.center_freq1,
			   he_chandef.center_freq2);
		return false;
	}

	*chandef = he_chandef;

	return true;
}

bool
net80211_verify_sta_he_mcs_support(
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_he_operation *he_operation)
{
    const struct ieee80211_sta_he_cap *sta_he_cap =
        ieee80211_get_sta_he_cap(sband);
    bool verified = false;
    u16 ap_min_req_set;
    int i;

    if (!sta_he_cap || !he_operation)
        return verified;

    ap_min_req_set = le16_to_cpu(he_operation->he_mcs_nss_set);

    /* Check 80MHz/160MHz for 80P80MHz */
    for (i = 0; i < 3; i++) {
        const struct ieee80211_he_mcs_nss_supp *sta_mcs_nss_supp = &sta_he_cap->he_mcs_nss_supp;
        u16 sta_mcs_map_tx = le16_to_cpu(((le16 *)sta_mcs_nss_supp)[2 * i + 1]);
        u16 sta_mcs_map_rx = le16_to_cpu(((le16 *)sta_mcs_nss_supp)[2 * i]);
        u8 nss;
        verified = true;

        for (nss = 8; nss > 0; nss--) {
            u8 ap_val = (ap_min_req_set >> (2 * (nss - 1))) & 3;
            u8 sta_tx_val = (sta_mcs_map_tx >> (2 * (nss - 1))) & 3;
            u8 sta_rx_val = (sta_mcs_map_rx >> (2 * (nss - 1))) & 3;

            if (ap_val == IEEE80211_HECAP_MCS_NOT_SUPPORTED)
                continue;

            if (sta_rx_val == IEEE80211_HECAP_MCS_NOT_SUPPORTED ||
                sta_tx_val == IEEE80211_HECAP_MCS_NOT_SUPPORTED ||
                (ap_val > sta_tx_val) || (ap_val > sta_rx_val)) {
                verified = false;
                break;
            }
        }
    }

    return verified;
}

static void net80211_he_mcs_disable(__le16 *he_mcs)
{
	u32 i;

	for (i = 0; i < 8; i++)
		*he_mcs |= cpu_to_le16(IEEE80211_HECAP_MCS_NOT_SUPPORTED << i * 2);
}

static void net80211_he_mcs_intersection(__le16 *he_own_rx, __le16 *he_peer_rx,
					  __le16 *he_own_tx, __le16 *he_peer_tx)
{
	u32 i;
	u16 own_rx, own_tx, peer_rx, peer_tx;

	for (i = 0; i < 8; i++) {
		own_rx = le16_to_cpu(*he_own_rx);
		own_rx = (own_rx >> i * 2) & IEEE80211_HECAP_MCS_NOT_SUPPORTED;

		own_tx = le16_to_cpu(*he_own_tx);
		own_tx = (own_tx >> i * 2) & IEEE80211_HECAP_MCS_NOT_SUPPORTED;

		peer_rx = le16_to_cpu(*he_peer_rx);
		peer_rx = (peer_rx >> i * 2) & IEEE80211_HECAP_MCS_NOT_SUPPORTED;

		peer_tx = le16_to_cpu(*he_peer_tx);
		peer_tx = (peer_tx >> i * 2) & IEEE80211_HECAP_MCS_NOT_SUPPORTED;

		if (peer_tx != IEEE80211_HECAP_MCS_NOT_SUPPORTED) {
			if (own_rx == IEEE80211_HECAP_MCS_NOT_SUPPORTED)
				peer_tx = IEEE80211_HECAP_MCS_NOT_SUPPORTED;
			else if (own_rx < peer_tx)
				peer_tx = own_rx;
		}

		if (peer_rx != IEEE80211_HECAP_MCS_NOT_SUPPORTED) {
			if (own_tx == IEEE80211_HECAP_MCS_NOT_SUPPORTED)
				peer_rx = IEEE80211_HECAP_MCS_NOT_SUPPORTED;
			else if (own_tx < peer_rx)
				peer_rx = own_tx;
		}

		*he_peer_rx &=
			~cpu_to_le16(IEEE80211_HECAP_MCS_NOT_SUPPORTED << i * 2);
		*he_peer_rx |= cpu_to_le16(peer_rx << i * 2);

		*he_peer_tx &=
			~cpu_to_le16(IEEE80211_HECAP_MCS_NOT_SUPPORTED << i * 2);
		*he_peer_tx |= cpu_to_le16(peer_tx << i * 2);
	}
}

void
net80211_vif_he_cap_ie_to_sta_he_cap(struct net80211_vif *vif,
    const struct ieee80211_supported_band *sband,
    const u8 *he_cap_ie, u8 he_cap_len,
    const struct ieee80211_he_6ghz_cap *he_6ghz_cap,
    struct net80211_sta *sta)
{
    struct ieee80211_sta_he_cap *sta_he_cap = &sta->he_cap;
	struct ieee80211_sta_he_cap own_he_cap = sband->iftype_data->he_cap;
    struct ieee80211_he_capabilities *he_capabilities = (void *)he_cap_ie;
    u8 he_ppe_size;
    u8 mcs_nss_size;
    u8 he_total_size;
	bool own_160, peer_160, own_80p80, peer_80p80;

    if (!he_cap_ie || !ieee80211_get_sta_he_cap(sband))
        return;

	memset(sta_he_cap, 0, sizeof(*sta_he_cap));

    /* Make sure size is OK */
    mcs_nss_size = ieee80211_he_mcs_nss_size(he_capabilities);
    he_ppe_size = ieee80211_he_ppe_size(he_cap_ie[sizeof(sta_he_cap->he_capabilities) + mcs_nss_size],
        he_capabilities->phy_cap_info);
    he_total_size = sizeof(sta_he_cap->he_capabilities) + mcs_nss_size + he_ppe_size;
	
    if (he_cap_len < he_total_size)
        return;

    /* Copy the he_cap_ie*/
    memcpy(&sta_he_cap->he_capabilities, he_cap_ie, sizeof(sta_he_cap->he_capabilities));

    /* Copy HE Tx/Rx HE MCS NSS Support Field */
    memcpy(&sta_he_cap->he_mcs_nss_supp, &he_cap_ie[sizeof(sta_he_cap->he_capabilities)], mcs_nss_size);

    /* Check if has PPE Thresholds (optional)*/
    if (sta_he_cap->he_capabilities.phy_cap_info[6] & IEEE80211_HEPHY_CAP6_PPE_THRESHOLD_PRESENT)
        memcpy(sta_he_cap->ppe_thres, &he_cap_ie[sizeof(sta_he_cap->he_capabilities) + mcs_nss_size], he_ppe_size);

    sta_he_cap->he_supported = true;
    net80211_sta_update_max_bandwidth(sta, net80211_sta_cap_rx_bw(sta), false);

	if (sband->band == NL80211_BAND_6GHZ && he_6ghz_cap)
		ieee80211_update_from_he_6ghz_capa(he_6ghz_cap, sta);


	net80211_he_mcs_intersection(&own_he_cap.he_mcs_nss_supp.he_rx_mcs_80,
				      &sta_he_cap->he_mcs_nss_supp.he_rx_mcs_80,
				      &own_he_cap.he_mcs_nss_supp.he_tx_mcs_80,
				      &sta_he_cap->he_mcs_nss_supp.he_tx_mcs_80);

	own_160 = own_he_cap.he_capabilities.phy_cap_info[0] &
		  IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;
	peer_160 = sta_he_cap->he_capabilities.phy_cap_info[0] &
		   IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;

	if (peer_160 && own_160) {
		net80211_he_mcs_intersection(&own_he_cap.he_mcs_nss_supp.he_rx_mcs_160,
					      &sta_he_cap->he_mcs_nss_supp.he_rx_mcs_160,
					      &own_he_cap.he_mcs_nss_supp.he_tx_mcs_160,
					      &sta_he_cap->he_mcs_nss_supp.he_tx_mcs_160);
	} else if (peer_160 && !own_160) {
		net80211_he_mcs_disable(&sta_he_cap->he_mcs_nss_supp.he_rx_mcs_160);
		net80211_he_mcs_disable(&sta_he_cap->he_mcs_nss_supp.he_tx_mcs_160);
		sta_he_cap->he_capabilities.phy_cap_info[0] &=
			~IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;
	}

	own_80p80 = own_he_cap.he_capabilities.phy_cap_info[0] &
		    IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;
	peer_80p80 = sta_he_cap->he_capabilities.phy_cap_info[0] &
		     IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;

	if (peer_80p80 && own_80p80) {
		net80211_he_mcs_intersection(&own_he_cap.he_mcs_nss_supp.he_rx_mcs_80p80,
					      &sta_he_cap->he_mcs_nss_supp.he_rx_mcs_80p80,
					      &own_he_cap.he_mcs_nss_supp.he_tx_mcs_80p80,
					      &sta_he_cap->he_mcs_nss_supp.he_tx_mcs_80p80);
	} else if (peer_80p80 && !own_80p80) {
		net80211_he_mcs_disable(&sta_he_cap->he_mcs_nss_supp.he_rx_mcs_80p80);
		net80211_he_mcs_disable(&sta_he_cap->he_mcs_nss_supp.he_tx_mcs_80p80);
		sta_he_cap->he_capabilities.phy_cap_info[0] &=
			~IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;
	}
}

void
net80211_vif_he_op_ie_to_bss_conf(struct net80211_vif* vif,
    const struct ieee80211_he_operation* he_op_ie)
{
    memset(&vif->bss_conf.he_operation, 0, sizeof(vif->bss_conf.he_operation));
    if (!he_op_ie)
        return;

    vif->bss_conf.he_operation.he_operation_params = __le32_to_cpu(he_op_ie->he_operation_params);
    vif->bss_conf.he_operation.he_mcs_nss_set = __le16_to_cpu(he_op_ie->he_mcs_nss_set);
}

void
net80211_vif_he_spr_ie_to_bss_conf(struct net80211_vif* vif,
    const struct ieee80211_he_spr* he_spr_ie_elem)
{
    struct ieee80211_he_obss_pd* he_obss_pd = &vif->bss_conf.he_obss_pd;
    const u8* data;

    memset(he_obss_pd, 0, sizeof(*he_obss_pd));

	/* Check the SPR IE NULL or not*/
    if (!he_spr_ie_elem)
        return;
    data = he_spr_ie_elem->optional;

	/* Check SPR NON_SRG OFFSET */
    if (he_spr_ie_elem->he_sr_control &
        IEEE80211_HESPR_NON_SRG_OFFSET_PRESENT)
        data++;

	/* Check SPR SRG INFORMATION OFFSET */
    if (he_spr_ie_elem->he_sr_control &
        IEEE80211_HESPR_SRG_INFORMATION_PRESENT) {
        he_obss_pd->max_offset = *data++;
        he_obss_pd->min_offset = *data++;
        he_obss_pd->enable = true;
    }
}
