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
#include "sta.h"
#include "vif.h"
#include "mlme.h"

u8
ieee80211_mcs_info_get_chains(const struct ieee80211_mcs_info *mcs)
{
    if (!mcs)
        return 1;

    if (mcs->rx_mask[3])
        return 4;
    if (mcs->rx_mask[2])
        return 3;
    if (mcs->rx_mask[1])
        return 2;
    return 1;
}

static void
__htcap_check_disable(
    const struct ieee80211_ht_capabilities *ht_capa,
    const struct ieee80211_ht_capabilities *ht_capa_mask,
    struct ieee80211_sta_ht_cap *sta_ht_cap,
    u16 flag)
{
    __le16 le_flag = cpu_to_le16(flag);
    if (ht_capa_mask->ht_capabilities_info & le_flag) {
        if (!(ht_capa->ht_capabilities_info & le_flag))
            sta_ht_cap->cap &= ~flag;
    }
}

static void
__htcap_check_enable(
    const struct ieee80211_ht_capabilities *ht_capa,
    const struct ieee80211_ht_capabilities *ht_capa_mask,
    struct ieee80211_sta_ht_cap *sta_ht_cap,
    u16 flag)
{
    __le16 le_flag = cpu_to_le16(flag);

    if ((ht_capa_mask->ht_capabilities_info & le_flag) &&
        (ht_capa->ht_capabilities_info & le_flag))
        sta_ht_cap->cap |= flag;
}

u8 *
ieee80211_ie_build_ht_cap(u8 *pos, 
    const struct ieee80211_sta_ht_cap *sta_ht_cap, u16 cap)
{
    __le16 tmp_cap;

    *pos++ = WLAN_EID_HT_CAP;
    *pos++ = sizeof(struct ieee80211_ht_capabilities);
    memset(pos, 0, sizeof(struct ieee80211_ht_capabilities));

    /* Add capability */
    tmp_cap = cpu_to_le16(cap);
    memcpy(pos, &tmp_cap, sizeof(u16));
    pos += sizeof(u16);

    /* Add AMPDU parameters */
    *pos++ = (sta_ht_cap->ampdu_factor | 
        (sta_ht_cap->ampdu_density << IEEE80211_HTCAP_AMPDU_PARM_DENSITY_SHIFT));

    /* Add MCS set */
    memcpy(pos, &sta_ht_cap->mcs, sizeof(sta_ht_cap->mcs));
    pos += sizeof(sta_ht_cap->mcs);

    /* Add extended capabilities */
    pos += sizeof(__le16);

    /* Add BF capabilities */
    pos += sizeof(__le32);

    /* Add Antenna selection */
    pos += sizeof(u8);

    return pos;
}

void
net80211_vif_apply_htcap_overrides(struct net80211_vif *vif,
    struct ieee80211_sta_ht_cap *sta_ht_cap)
{
    static const u16 htcap_check_disable_flags[] = {
        IEEE80211_HTCAP_SUP_WIDTH_20_40,
        IEEE80211_HTCAP_SGI_40,
        IEEE80211_HTCAP_SGI_20,
        IEEE80211_HTCAP_MAX_AMSDU,
        IEEE80211_HTCAP_LDPC_CODING,
    };
    static const u16 htcap_check_enable_flags[] = {
        IEEE80211_HTCAP_40MHZ_INTOLERANT,
        IEEE80211_HTCAP_TX_STBC,
        IEEE80211_HTCAP_RX_STBC,
    };

    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct ieee80211_ht_capabilities *ht_capa;
    struct ieee80211_ht_capabilities *ht_capa_mask;

    u8 *scaps, *smask;
    u32 i;

    if (!sta_ht_cap->ht_supported)
        return;

    ht_capa = &mlme_conf->ht_capa;
    ht_capa_mask = &mlme_conf->ht_capa_mask;

    /* MCS */
    scaps = (u8 *)(&ht_capa->mcs.rx_mask);
    smask = (u8 *)(&ht_capa_mask->mcs.rx_mask);

    for (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++) {
        u8 m = smask[i];
        sta_ht_cap->mcs.rx_mask[i] &= ~m;
        sta_ht_cap->mcs.rx_mask[i] |= (m & scaps[i]);
    }

    /* Allow the user to disable capabilities */
    for (i = 0; i < ARRAY_LENGTH(htcap_check_disable_flags); i++) {
        __htcap_check_disable(ht_capa, ht_capa_mask, sta_ht_cap,
            htcap_check_disable_flags[i]);
    }

    /* Allow the user to enable capabilities */
    for (i = 0; i < ARRAY_LENGTH(htcap_check_enable_flags); i++) {
        __htcap_check_enable(ht_capa, ht_capa_mask, sta_ht_cap,
            htcap_check_enable_flags[i]);
    }

    /* Allow user to decrease AMPDU factor */
    if (1) {
        u8 ampdu_factor = ht_capa->ampdu_params_info & IEEE80211_HTCAP_AMPDU_PARM_FACTOR;
        if (ampdu_factor && (ampdu_factor < sta_ht_cap->ampdu_factor))
            sta_ht_cap->ampdu_factor = ampdu_factor;
    }

    /* Allow the user to increase AMPDU density. */
    if (1) {
        u8 ampdu_density = (ht_capa->ampdu_params_info &
            IEEE80211_HTCAP_AMPDU_PARM_DENSITY)
            >> IEEE80211_HTCAP_AMPDU_PARM_DENSITY_SHIFT;
        if (ampdu_density > sta_ht_cap->ampdu_density)
            sta_ht_cap->ampdu_density = ampdu_density;
    }
}

bool
net80211_vif_ht_cap_to_sta_ht_cap(struct net80211_vif *vif,
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_ht_capabilities *ht_cap,
    struct net80211_sta *sta)
{
    struct ieee80211_sta_ht_cap sta_ht_cap, own_ht_cap;
    u8 ampdu_info, tx_mcs_set_cap;
    int i, max_tx_streams;
    bool changed;
    enum ieee80211_sta_rx_bandwidth bw;
    enum nl80211_chan_width cw;

    memset(&sta_ht_cap, 0, sizeof(sta_ht_cap));

    if (!ht_cap || !sband->ht_cap.ht_supported)
        goto apply;

    sta_ht_cap.ht_supported = true;

    own_ht_cap = sband->ht_cap;

    if (net80211_vif_type(vif) == NL80211_IFTYPE_STATION)
        net80211_vif_apply_htcap_overrides(vif, &own_ht_cap);

    sta_ht_cap.cap = le16_to_cpu(ht_cap->ht_capabilities_info) &
        (own_ht_cap.cap | ~(IEEE80211_HTCAP_LDPC_CODING |
            IEEE80211_HTCAP_SUP_WIDTH_20_40 |
            IEEE80211_HTCAP_GRN_FLD |
            IEEE80211_HTCAP_SGI_20 |
            IEEE80211_HTCAP_SGI_40 |
            IEEE80211_HTCAP_DSSSCCK40));

    if (!(own_ht_cap.cap & IEEE80211_HTCAP_TX_STBC))
        sta_ht_cap.cap &= ~IEEE80211_HTCAP_RX_STBC;
    if (!(own_ht_cap.cap & IEEE80211_HTCAP_RX_STBC))
        sta_ht_cap.cap &= ~IEEE80211_HTCAP_TX_STBC;

    ampdu_info = ht_cap->ampdu_params_info;
    sta_ht_cap.ampdu_factor =
        ampdu_info & IEEE80211_HTCAP_AMPDU_PARM_FACTOR;
    sta_ht_cap.ampdu_density =
        (ampdu_info & IEEE80211_HTCAP_AMPDU_PARM_DENSITY) 
        >> IEEE80211_HTCAP_AMPDU_PARM_DENSITY_SHIFT;

    /* Set own MCS TX capabilities */
    tx_mcs_set_cap = own_ht_cap.mcs.tx_params;

    /* Set peer MCS TX parameters*/
    sta_ht_cap.mcs.tx_params = ht_cap->mcs.tx_params;

    /* Check if can we TX with MCS rates? */
    if (!(tx_mcs_set_cap & IEEE80211_HTCAP_MCS_TX_DEFINED))
        goto apply;

    /* Counting from 0, therefore +1 */
    if (tx_mcs_set_cap & IEEE80211_HTCAP_MCS_TX_RX_DIFF)
        max_tx_streams =
        ((tx_mcs_set_cap & IEEE80211_HTCAP_MCS_TX_MAX_STREAMS_MASK)
            >> IEEE80211_HTCAP_MCS_TX_MAX_STREAMS_SHIFT) + 1;
    else
        max_tx_streams = IEEE80211_HTCAP_MCS_TX_MAX_STREAMS;

    /*
     * 802.11n-2009 20.3.5 / 20.6:
     * -- indices 0 to 7 and 32 are single spatial stream
     * -- 8 to 31 are multiple spatial streams using equal modulation
     *    [8..15 for two streams, 16..23 for three and 24..31 for four]
     * -- remainder are multiple spatial streams using unequal modulation
     */
    for (i = 0; i < max_tx_streams; i++)
        sta_ht_cap.mcs.rx_mask[i] =
        own_ht_cap.mcs.rx_mask[i] & ht_cap->mcs.rx_mask[i];

    if (tx_mcs_set_cap & IEEE80211_HTCAP_MCS_TX_UNEQUAL_MODULATION)
        for (i = IEEE80211_HTCAP_MCS_UNEQUAL_MODULATION_START_BYTE;
            i < IEEE80211_HT_MCS_MASK_LEN; i++)
            sta_ht_cap.mcs.rx_mask[i] =
            own_ht_cap.mcs.rx_mask[i] &
            ht_cap->mcs.rx_mask[i];

    /* MCS rate 32 also */
    if (own_ht_cap.mcs.rx_mask[32 / 8] & ht_cap->mcs.rx_mask[32 / 8] & 1)
        sta_ht_cap.mcs.rx_mask[32 / 8] |= 1;

    /* set Rx highest rate */
    sta_ht_cap.mcs.rx_highest = ht_cap->mcs.rx_highest;

    if (sta_ht_cap.cap & IEEE80211_HTCAP_MAX_AMSDU)
        net80211_sta_set_max_amsdu_len(sta, IEEE80211_HTCAP_MAX_MPDU_LEN_7935);
    else
        net80211_sta_set_max_amsdu_len(sta, IEEE80211_HTCAP_MAX_MPDU_LEN_3839);

apply:
    changed = (memcmp(&sta->ht_cap, &sta_ht_cap, sizeof(sta_ht_cap)) != 0);

    memcpy(&sta->ht_cap, &sta_ht_cap, sizeof(sta_ht_cap));

    cw = net80211_vif_bss_conf_get_chandef(vif)->width;
    if (cw == NL80211_CHAN_WIDTH_20_NOHT ||
		cw == NL80211_CHAN_WIDTH_20) {
        bw = IEEE80211_STA_RX_BANDWIDTH_20;
	} else if (cw == NL80211_CHAN_WIDTH_40 ||
	           cw == NL80211_CHAN_WIDTH_80 ||
	           cw == NL80211_CHAN_WIDTH_80P80 ||
	           cw == NL80211_CHAN_WIDTH_160) {
        bw = sta_ht_cap.cap & IEEE80211_HTCAP_SUP_WIDTH_20_40 ?
             IEEE80211_STA_RX_BANDWIDTH_40 : IEEE80211_STA_RX_BANDWIDTH_20;
	} else {
        WARN_ON_ONCE(1);
        bw = IEEE80211_STA_RX_BANDWIDTH_20;
	}

    sta->bandwidth = bw;
    sta->cur_max_bandwidth =
        sta_ht_cap.cap & IEEE80211_HTCAP_SUP_WIDTH_20_40 ?
        IEEE80211_STA_RX_BANDWIDTH_40 : IEEE80211_STA_RX_BANDWIDTH_20;
    sta->smps_mode = IEEE80211_SMPS_NONE;

    return changed;
}
