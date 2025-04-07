/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/ndebug.h>
#include "net80211_i.h"
#include "vif.h"
#include "sta.h"
#include "mlme.h"

u8 ieee80211_vht_mcs_info_get_nss(const struct ieee80211_vht_mcs_info *mcs)
{
    u8 nss;
    u16 tx_mcs_map;

    tx_mcs_map = le16_to_cpu(mcs->tx_mcs_map);
    for (nss = 8; nss > 0; nss--) {
        if (((tx_mcs_map >> (2 * (nss - 1))) & 3) != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED)
            break;
    }

    return nss;
}

u8 *ieee80211_ie_build_vht_cap(u8 *pos, 
    const struct ieee80211_sta_vht_cap *sta_vht_cap, u32 cap)
{
    __le32 le_cap;

    /* Initialize */
    *pos++ = WLAN_EID_VHT_CAP;
    *pos++ = sizeof(struct ieee80211_vht_capabilities);
    memset(pos, 0, sizeof(struct ieee80211_vht_capabilities));

    /* Set capability flags */
    le_cap = cpu_to_le32(cap);
    memcpy(pos, &le_cap, sizeof(u32));
    pos += sizeof(u32);

    /* Set VHT MCS*/
    memcpy(pos, &sta_vht_cap->vht_mcs, sizeof(sta_vht_cap->vht_mcs));
    pos += sizeof(sta_vht_cap->vht_mcs);

    return pos;
}

static inline void
__vhtcap_check_disable(
    const struct ieee80211_vht_capabilities *vht_capa,
    const struct ieee80211_vht_capabilities *vht_capa_mask,
    struct ieee80211_sta_vht_cap *sta_vht_cap,
    u32 flag)
{
    __le32 le_flag = cpu_to_le32(flag);

    if ((vht_capa_mask->vht_capabilities_info & le_flag) &&
        !(vht_capa->vht_capabilities_info & le_flag))
        sta_vht_cap->cap &= ~flag;
}

void
net80211_vif_apply_vhtcap_overrides(struct net80211_vif *vif,
    struct ieee80211_sta_vht_cap *sta_vht_cap)
{
    static const u32 vhtcap_check_disable_flags[] = {
        IEEE80211_VHTCAP_RXLDPC,
        IEEE80211_VHTCAP_SHORT_GI_80,
        IEEE80211_VHTCAP_SHORT_GI_160,
        IEEE80211_VHTCAP_TXSTBC,
        IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE,
        IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE,
        IEEE80211_VHTCAP_RX_ANTENNA_PATTERN,
        IEEE80211_VHTCAP_TX_ANTENNA_PATTERN,
    };

    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct ieee80211_vht_capabilities *vht_capa = &mlme_conf->vht_capa;
    struct ieee80211_vht_capabilities *vht_capa_mask = &mlme_conf->vht_capa_mask;

    u8 i;
    u16 rxmcs_mask, rxmcs_cap, rxmcs_val;
    u16 txmcs_mask, txmcs_cap, txmcs_val;

    if (!sta_vht_cap->vht_supported)
        return;

    for (i = 0; i < ARRAY_LENGTH(vhtcap_check_disable_flags); i++) {
        __vhtcap_check_disable(vht_capa, vht_capa_mask,
            sta_vht_cap, vhtcap_check_disable_flags[i]);
    }

    /* Allow user to decrease AMPDU length exponent */
    if (vht_capa_mask->vht_capabilities_info &
        cpu_to_le32(IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK)) {
        u32 cap, val;

        val = le32_to_cpu(vht_capa->vht_capabilities_info) &
            IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
        val >>= IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;
        cap = sta_vht_cap->cap & IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
        cap >>= IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;

        if (val < cap) {
            sta_vht_cap->cap &=
                ~IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
            sta_vht_cap->cap |=
                val << IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;
        }
    }

    /* Allow the user to decrease MCSes */
    rxmcs_mask =
        le16_to_cpu(vht_capa_mask->supported_mcs_set.rx_mcs_map);
    rxmcs_val = le16_to_cpu(vht_capa->supported_mcs_set.rx_mcs_map);
    rxmcs_val &= rxmcs_mask;
    rxmcs_cap = le16_to_cpu(sta_vht_cap->vht_mcs.rx_mcs_map);

    txmcs_mask =
        le16_to_cpu(vht_capa_mask->supported_mcs_set.tx_mcs_map);
    txmcs_val = le16_to_cpu(vht_capa->supported_mcs_set.tx_mcs_map);
    txmcs_val &= txmcs_mask;
    txmcs_cap = le16_to_cpu(sta_vht_cap->vht_mcs.tx_mcs_map);
    for (i = 0; i < 8; i++) {
        u8 mask, val, cap;

        /* TODOTODO: REVIEW THE CODE */
        mask = (rxmcs_mask >> 2 * i) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;
        val = (rxmcs_val >> 2 * i) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;
        cap = (rxmcs_cap >> 2 * i) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;

        if (mask && ((cap != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED && val < cap) ||
            val == IEEE80211_VHTCAP_MCS_NOT_SUPPORTED)) {
            rxmcs_cap &= ~(3 << 2 * i);
            rxmcs_cap |= (rxmcs_val & (3 << 2 * i));
        }

        mask = (txmcs_mask >> 2 * i) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;
        val = (txmcs_val >> 2 * i) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;
        cap = (txmcs_cap >> 2 * i) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;

        if (mask && ((cap != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED && val < cap) ||
            val == IEEE80211_VHTCAP_MCS_NOT_SUPPORTED)) {
            txmcs_cap &= ~(3 << 2 * i);
            txmcs_cap |= (txmcs_val & (3 << 2 * i));
        }
    }
    sta_vht_cap->vht_mcs.rx_mcs_map = cpu_to_le16(rxmcs_cap);
    sta_vht_cap->vht_mcs.tx_mcs_map = cpu_to_le16(txmcs_cap);
}

void
net80211_vif_vht_cap_to_sta_vht_cap(struct net80211_vif *vif,
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_vht_capabilities *vht_cap,
    struct net80211_sta *sta)
{
    struct ieee80211_sta_vht_cap *sta_vht_cap = &sta->vht_cap;
    struct ieee80211_sta_vht_cap own_vht_cap;
    u32 cap_info, i;
    enum ieee80211_sta_rx_bandwidth max_bandwidth;

    if (!sta->ht_cap.ht_supported)
        return;

    if (!vht_cap || !sband->vht_cap.vht_supported)
        return;
	
    memset(sta_vht_cap, 0, sizeof(*sta_vht_cap));

    /* 80MHz is required for VHT */
    if (!ieee80211_sband_supports_80mhz(sband))
        return;

    sta_vht_cap->vht_supported = true;

    own_vht_cap = sband->vht_cap;

    if (net80211_vif_type(vif) == NL80211_IFTYPE_STATION)
        net80211_vif_apply_vhtcap_overrides(vif, &own_vht_cap);

    /* Set capabilities */
    cap_info = le32_to_cpu(vht_cap->vht_capabilities_info);
    sta_vht_cap->cap = cap_info;
    sta_vht_cap->cap &= (IEEE80211_VHTCAP_MAX_MPDU_LENGTH_3895 |
        IEEE80211_VHTCAP_MAX_MPDU_LENGTH_7991 |
        IEEE80211_VHTCAP_MAX_MPDU_LENGTH_11454 |
        IEEE80211_VHTCAP_RXLDPC |
        IEEE80211_VHTCAP_VHT_TXOP_PS |
        IEEE80211_VHTCAP_HTC_VHT |
        IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK |
        IEEE80211_VHTCAP_VHT_LINK_ADAPTATION_VHT_UNSOL_MFB |
        IEEE80211_VHTCAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB |
        IEEE80211_VHTCAP_RX_ANTENNA_PATTERN |
        IEEE80211_VHTCAP_TX_ANTENNA_PATTERN);

    /* and some based on our own capabilities */
    switch (own_vht_cap.cap & IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK) {
    case IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ:
        sta_vht_cap->cap |= cap_info &
            IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ;
        break;
    case IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ:
        sta_vht_cap->cap |= cap_info &
            IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK;
        break;
    default:
        /* nothing */
        break;
    }

    /* short gi capabilities */
    sta_vht_cap->cap |= cap_info & own_vht_cap.cap &
        (IEEE80211_VHTCAP_SHORT_GI_80 | IEEE80211_VHTCAP_SHORT_GI_160);

    /* Set beamformee & beamformer */
    if (own_vht_cap.cap & IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE)
        sta_vht_cap->cap |= cap_info &
        (IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE | IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK);

    if (own_vht_cap.cap & IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE)
        sta_vht_cap->cap |= cap_info &
        (IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE | IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK);

    if (own_vht_cap.cap & IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE)
        sta_vht_cap->cap |= cap_info &
        IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE;

    if (own_vht_cap.cap & IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE)
        sta_vht_cap->cap |= cap_info &
        IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE;

    /* Set stbc */
    if (own_vht_cap.cap & IEEE80211_VHTCAP_TXSTBC)
        sta_vht_cap->cap |= cap_info & IEEE80211_VHTCAP_RXSTBC_MASK;

    if (own_vht_cap.cap & IEEE80211_VHTCAP_RXSTBC_MASK)
        sta_vht_cap->cap |= cap_info & IEEE80211_VHTCAP_TXSTBC;

    /* Copy peer MCS info */
    memcpy(&sta_vht_cap->vht_mcs, &vht_cap->supported_mcs_set,
        sizeof(struct ieee80211_vht_mcs_info));

    /* Check EXT_NSS_BW */
    if (net80211_hw_check(vif->pdev, IEEE80211_HW_SUPPORTS_VHT_EXT_NSS_BW))
        sta_vht_cap->cap |= (cap_info & IEEE80211_VHTCAP_EXT_NSS_BW_MASK);
    else
        sta_vht_cap->vht_mcs.tx_highest &=
        ~cpu_to_le16(IEEE80211_VHTCAP_EXT_NSS_BW_CAPABLE);

    /* update MCSes */
    for (i = 0; i < 8; i++) {
        u16 own_rx_mcs, own_tx_mcs;
        u16 peer_rx_mcs, peer_tx_mcs;

        own_rx_mcs = le16_to_cpu(own_vht_cap.vht_mcs.rx_mcs_map);
        own_rx_mcs = (own_rx_mcs >> i * 2) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;

        own_tx_mcs = le16_to_cpu(own_vht_cap.vht_mcs.tx_mcs_map);
        own_tx_mcs = (own_tx_mcs >> i * 2) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;

        peer_rx_mcs = le16_to_cpu(sta_vht_cap->vht_mcs.rx_mcs_map);
        peer_rx_mcs = (peer_rx_mcs >> i * 2) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;

        peer_tx_mcs = le16_to_cpu(sta_vht_cap->vht_mcs.tx_mcs_map);
        peer_tx_mcs = (peer_tx_mcs >> i * 2) & IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;

        if (peer_tx_mcs != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED) {
            if (own_rx_mcs == IEEE80211_VHTCAP_MCS_NOT_SUPPORTED)
                peer_tx_mcs = IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;
            else if (own_rx_mcs < peer_tx_mcs)
                peer_tx_mcs = own_rx_mcs;
        }

        if (peer_rx_mcs != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED) {
            if (own_tx_mcs == IEEE80211_VHTCAP_MCS_NOT_SUPPORTED)
                peer_rx_mcs = IEEE80211_VHTCAP_MCS_NOT_SUPPORTED;
            else if (own_tx_mcs < peer_rx_mcs)
                peer_rx_mcs = own_tx_mcs;
        }

        sta_vht_cap->vht_mcs.rx_mcs_map &=
            ~cpu_to_le16(IEEE80211_VHTCAP_MCS_NOT_SUPPORTED << i * 2);
        sta_vht_cap->vht_mcs.rx_mcs_map |= cpu_to_le16(peer_rx_mcs << i * 2);

        sta_vht_cap->vht_mcs.tx_mcs_map &=
            ~cpu_to_le16(IEEE80211_VHTCAP_MCS_NOT_SUPPORTED << i * 2);
        sta_vht_cap->vht_mcs.tx_mcs_map |= cpu_to_le16(peer_tx_mcs << i * 2);
    }

    /*
     * WORKAROUND: Some VHT-enabled STAs do NOT follow the spec and have the 
     * VHT-MCS Rx map filled in with value 3 for all eightspacial streams, 
     *
     * From spec in section 22.1.1:
     * A VHT STA shall support at least single spactial stream VHT-MCSs
     * 0 to 7 (transmit and receive) in all supported channel widths.
     */
    if (sta_vht_cap->vht_mcs.rx_mcs_map == cpu_to_le16(0xFFFF)) {
        sta_vht_cap->vht_supported = false;
        net_dbg("Ignoring VHT IE from %pM due to invalid rx_mcs_map\n", net80211_sta_addr(sta));
        return;
    }

    /* Set up the bandwidth */
    switch (sta_vht_cap->cap & IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK) {
    case IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ:
    case IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ:
        max_bandwidth = IEEE80211_STA_RX_BANDWIDTH_160;
        break;
    default:
        max_bandwidth = IEEE80211_STA_RX_BANDWIDTH_80;

        if (!(sta_vht_cap->vht_mcs.tx_highest &
            cpu_to_le16(IEEE80211_VHTCAP_EXT_NSS_BW_CAPABLE)))
            break;

        if (cap_info & IEEE80211_VHTCAP_EXT_NSS_BW_MASK)
            max_bandwidth = IEEE80211_STA_RX_BANDWIDTH_160;
    }

    net80211_sta_update_max_bandwidth(sta, max_bandwidth, false);

    /* Do NOT update the size if HT IE reported 3839 bytes only */
    if (net80211_sta_get_max_amsdu_len(sta) == IEEE80211_HTCAP_MAX_MPDU_LEN_3839)
        return;

    /* vht_cap_max_mpdu */
    if (1) {
		u16 vht_max_mpdu_len_idx = (sta_vht_cap->cap & IEEE80211_VHTCAP_MAX_MPDU_MASK);
        static const u16 ieee80211_vht_max_amsdu_len_map[] = {
            [IEEE80211_VHTCAP_MAX_MPDU_LENGTH_3895] = 3895,
            [IEEE80211_VHTCAP_MAX_MPDU_LENGTH_7991] = 7991,
            [IEEE80211_VHTCAP_MAX_MPDU_LENGTH_11454] = 11454,
        };
        
        if (vht_max_mpdu_len_idx >= (u16)ARRAY_LENGTH(ieee80211_vht_max_amsdu_len_map))
            vht_max_mpdu_len_idx = 0;

        net80211_sta_set_max_amsdu_len(sta, 
            ieee80211_vht_max_amsdu_len_map[vht_max_mpdu_len_idx]);
    }
}