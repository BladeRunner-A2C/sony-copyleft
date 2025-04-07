/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 28/9/22   zxue     fix the nss issue
 1/9/21    zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/net80211.h>
#include <net/ndebug.h>
#include "net80211_i.h"
#include "drvops.h"
#include "chan.h"
#include "sta.h"

struct net80211_sta *
net80211_sta_alloc(struct net80211_vif *vif, const u8 *addr)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_sta *sta;
    u32 band;

    sta = kzalloc(sizeof(*sta) + net80211_get_sta_data_size(pdev), GFP_KERNEL);
    if (!sta)
        return NULL;

    memcpy(sta->addr, addr, ETH_ALEN);
    sta->pdev = pdev;
    sta->vif = vif;
    sta->max_rx_aggregation_subframes = 
        net80211_get_max_rx_aggregation_subframes(pdev);
    sta->state = IEEE80211_STA_NONE;

    for (band = 0; band < NUM_NL80211_BANDS; band++) {
        sta->supp_rates[band] = net80211_get_band_supp_rates(pdev, band);
    }

    sta->smps_mode = IEEE80211_SMPS_NONE;
    sta->max_rc_amsdu_len = IEEE80211_MAX_MPDU_LEN_HT_BA;

    net_dbg("vif 0x%p, allocate sta 0x%p\n", vif, sta->addr);

    return sta;
}

void
net80211_sta_free(struct net80211_sta *sta)
{
    net_dbg("vif 0x%p, free sta 0x%p\n", sta->vif, sta->addr);

    kfree(sta);
}

int 
net80211_sta_move_state(struct net80211_sta *sta,
    enum ieee80211_sta_state new_state)
{
    int err;

    if (sta->state == new_state)
        return 0;

    /* validate the state */
    switch (new_state) {
    case IEEE80211_STA_NONE:
        if (sta->state != IEEE80211_STA_AUTH)
            return -EINVAL;
        break;
    case IEEE80211_STA_AUTH:
        if (sta->state != IEEE80211_STA_NONE &&
            sta->state != IEEE80211_STA_ASSOC)
            return -EINVAL;
        break;
    case IEEE80211_STA_ASSOC:
        if (sta->state != IEEE80211_STA_AUTH &&
            sta->state != IEEE80211_STA_AUTHORIZED)
            return -EINVAL;
        break;
    case IEEE80211_STA_AUTHORIZED:
        if (sta->state != IEEE80211_STA_ASSOC)
            return -EINVAL;
        break;
    default:
        WARN(1, "invalid state %d", new_state);
        return -EINVAL;
    }

    net_dbg("moving STA %pM to state %d\n",
        sta->addr, new_state);

    /* notify the driver before actual changes */
    err = drv_sta_state(sta->pdev, sta->vif, sta,
        sta->state, new_state);
    if (err)
        return err;

    /* update status */

    /* 2) AUTH -> ASSOC */
    if (new_state == IEEE80211_STA_ASSOC &&
        sta->state == IEEE80211_STA_AUTH) {
        sta->assoc_at = getwalltime_us();
        net80211_recalc_min_chandef(sta->vif);
    }
    /* 2) ASSOC -> AUTH */
    else if (new_state == IEEE80211_STA_AUTH &&
        sta->state == IEEE80211_STA_ASSOC) {
        net80211_recalc_min_chandef(sta->vif);
    }

    sta->state = new_state;

    return 0;
}

int
net80211_sta_destroy(struct net80211_sta *sta)
{
	struct net80211_pdev *pdev = sta->pdev;
    struct net80211_vif *vif = sta->vif;
    int ret = 0;

    /* part 1 */
    list_del(&sta->node);

    /* part 2 */
    while (sta->state == IEEE80211_STA_AUTHORIZED) {
        ret = net80211_sta_move_state(sta, IEEE80211_STA_ASSOC);
        WARN_ON_ONCE(ret);
    }

    while (sta->state > IEEE80211_STA_NONE) {
        ret = net80211_sta_move_state(sta, sta->state - 1);
        if (ret) {
            WARN_ON_ONCE(1);
            break;
        }
    }

    if (net80211_sta_is_uploaded(sta)) {
        ret = drv_sta_state(pdev, vif, sta, IEEE80211_STA_NONE,
            IEEE80211_STA_NOTEXIST);
        WARN_ON_ONCE(ret != 0);
    }

    net_dbg("Removed STA %pM\n", sta->addr);

    net80211_sta_free(sta);

    return ret;
}

static int 
net80211_sta_add_check(struct net80211_sta *sta)
{
    struct net80211_vif *vif = sta->vif;

    if (WARN_ON(ether_addr_equal(sta->addr, vif->addr) ||
        is_multicast_ether_addr(sta->addr)))
        return -EINVAL;

    if (net80211_hw_check(sta->pdev, IEEE80211_HW_NEEDS_UNIQUE_STA_ADDR) &&
        net80211_vif_get_sta(vif, sta->addr)) {
        return -ENOTUNIQ;
    }

    return 0;
}

static int 
net80211_sta_add_drv_state(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_sta *sta)
{
    enum ieee80211_sta_state state;
    int err = 0;

    for (state = IEEE80211_STA_NOTEXIST; state < sta->state; state++) {
        err = drv_sta_state(pdev, vif, sta, state, state + 1);
        if (err)
            break;
    }

    if (!err) {
        return 0;
    }

    /* unwind on error */
    for (; state > IEEE80211_STA_NOTEXIST; state--)
        WARN_ON(drv_sta_state(pdev, vif, sta, state, state - 1));

    return err;
}

static int 
net80211_sta_add_complete(struct net80211_sta *sta)
{
    struct net80211_pdev *pdev = sta->pdev;
    struct net80211_vif *vif = sta->vif;
    int err = 0;

    /* check if STA exists already */
    if (net80211_vif_get_sta(vif, sta->addr)) {
        err = -EEXIST;
        goto err_exist;
    }

	list_add_tail(&sta->node, &pdev->sta_list);

    /* notify driver */
    err = net80211_sta_add_drv_state(pdev, vif, sta);
    if (err)
        goto err_state;

    if (sta->state >= IEEE80211_STA_ASSOC) {
        net80211_recalc_min_chandef(sta->vif);
    }

    net_dbg("Inserted STA %pM\n", sta->addr);
    return 0;

err_state:
    list_del(&sta->node);
err_exist:
    return err;
}

int 
net80211_sta_add(struct net80211_sta *sta)
{
    int err;
	
    err = net80211_sta_add_check(sta);
    if (err) {
        goto err_add;
    }

    err = net80211_sta_add_complete(sta);
    if (err)
        goto err_add;

    return 0;

err_add:
    net80211_sta_free(sta);
    return err;
}

void net80211_sta_update_rx_nss(struct net80211_sta *sta)
{
    u8 ht_rx_nss = 0, vht_rx_nss = 0, he_rx_nss = 0;
	bool support_160;
    u8 rx_nss;

    /* already have a valid value */
    if (sta->rx_nss)
        return;

    if (sta->he_cap.he_supported) {
        int i;
        u8 rx_mcs_80 = 0, rx_mcs_160 = 0;
        const struct ieee80211_sta_he_cap *he_cap = &sta->he_cap;
        u16 mcs_160_map =
            le16_to_cpu(he_cap->he_mcs_nss_supp.he_rx_mcs_160);
        u16 mcs_80_map = le16_to_cpu(he_cap->he_mcs_nss_supp.he_rx_mcs_80);

        for (i = 7; i >= 0; i--) {
            u8 mcs_160 = (mcs_160_map >> (2 * i)) & 3;

            if (mcs_160 != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED) {
                rx_mcs_160 = (u8)(i + 1);
                break;
            }
        }
        for (i = 7; i >= 0; i--) {
            u8 mcs_80 = (mcs_80_map >> (2 * i)) & 3;

            if (mcs_80 != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED) {
                rx_mcs_80 = (u8)(i + 1);
                break;
            }
        }

        he_rx_nss = min(rx_mcs_80, rx_mcs_160);
		support_160 = he_cap->he_capabilities.phy_cap_info[0] &
			      IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;

		if (support_160)
			he_rx_nss = min(rx_mcs_80, rx_mcs_160);
		else
			he_rx_nss = rx_mcs_80;
    }

    if (sta->ht_cap.ht_supported) {
        if (sta->ht_cap.mcs.rx_mask[0])
            ht_rx_nss++;
        if (sta->ht_cap.mcs.rx_mask[1])
            ht_rx_nss++;
        if (sta->ht_cap.mcs.rx_mask[2])
            ht_rx_nss++;
        if (sta->ht_cap.mcs.rx_mask[3])
            ht_rx_nss++;
        /* FIXME: consider rx_highest? */
    }

    if (sta->vht_cap.vht_supported) {
        int i;
        u16 rx_mcs_map;

        rx_mcs_map = le16_to_cpu(sta->vht_cap.vht_mcs.rx_mcs_map);

        for (i = 7; i >= 0; i--) {
            u8 mcs = (rx_mcs_map >> (2 * i)) & 3;

            if (mcs != IEEE80211_VHTCAP_MCS_NOT_SUPPORTED) {
                vht_rx_nss = (u8)(i + 1);
                break;
            }
        }
        /* FIXME: consider rx_highest? */
    }

    rx_nss = max(vht_rx_nss, ht_rx_nss);
    rx_nss = max(he_rx_nss, rx_nss);
    sta->rx_nss = max_t(u8, 1, rx_nss);
}


enum ieee80211_sta_rx_bandwidth
net80211_sta_cap_rx_bw(struct net80211_sta *sta)
{
    struct ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
    struct ieee80211_sta_he_cap *he_cap = &sta->he_cap;
    u32 cap_width;

    if (he_cap->he_supported) {
        u8 info = he_cap->he_capabilities.phy_cap_info[0];
        struct ieee80211_chan_def *chandef = net80211_vif_bss_conf_get_chandef(sta->vif);

        if (chandef->chan->band == NL80211_BAND_2GHZ) {
            if (info & IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G)
                return IEEE80211_STA_RX_BANDWIDTH_40;
            else
                return IEEE80211_STA_RX_BANDWIDTH_20;
        }

        if (info & IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G ||
            info & IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G)
            return IEEE80211_STA_RX_BANDWIDTH_160;
        else if (info & IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G)
            return IEEE80211_STA_RX_BANDWIDTH_80;

        return IEEE80211_STA_RX_BANDWIDTH_20;
    }

    if (!vht_cap->vht_supported)
        return sta->ht_cap.cap & IEEE80211_HTCAP_SUP_WIDTH_20_40 ?
        IEEE80211_STA_RX_BANDWIDTH_40 : IEEE80211_STA_RX_BANDWIDTH_20;

    cap_width = vht_cap->cap & IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK;

    if (cap_width == IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ ||
        cap_width == IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ)
        return IEEE80211_STA_RX_BANDWIDTH_160;

    /*
     * If this is non-zero, then it does support 160 MHz after all,
     * in one form or the other. We don't distinguish here (or even
     * above) between 160 and 80+80 yet.
     */
    if (vht_cap->cap & IEEE80211_VHTCAP_EXT_NSS_BW_MASK)
        return IEEE80211_STA_RX_BANDWIDTH_160;

    return IEEE80211_STA_RX_BANDWIDTH_80;
}

static enum ieee80211_sta_rx_bandwidth
ieee80211_chan_width_to_sta_rx_bw(enum nl80211_chan_width width)
{
    static const enum ieee80211_sta_rx_bandwidth chan_width_to_sta_rx_bw_map[] = {
        [NL80211_CHAN_WIDTH_20_NOHT] = IEEE80211_STA_RX_BANDWIDTH_20,
        [NL80211_CHAN_WIDTH_20] = IEEE80211_STA_RX_BANDWIDTH_20,
        [NL80211_CHAN_WIDTH_40] = IEEE80211_STA_RX_BANDWIDTH_40,
        [NL80211_CHAN_WIDTH_80] = IEEE80211_STA_RX_BANDWIDTH_80,
        [NL80211_CHAN_WIDTH_80P80] = IEEE80211_STA_RX_BANDWIDTH_160,
        [NL80211_CHAN_WIDTH_160] = IEEE80211_STA_RX_BANDWIDTH_160,
    };

    if (width >= ARRAY_LENGTH(chan_width_to_sta_rx_bw_map)) {
        WARN_ON_ONCE(1);
        return IEEE80211_STA_RX_BANDWIDTH_20;
    }

    return chan_width_to_sta_rx_bw_map[width];
}

enum ieee80211_sta_rx_bandwidth
net80211_sta_cur_vht_bw(struct net80211_sta *sta)
{
    struct ieee80211_chan_def *chandef =
        net80211_vif_bss_conf_get_chandef(sta->vif);
    enum ieee80211_sta_rx_bandwidth bw;

    bw = net80211_sta_cap_rx_bw(sta);
    bw = min(bw, sta->cur_max_bandwidth);

    bw = min(bw, ieee80211_chan_width_to_sta_rx_bw(chandef->width));

    return bw;
}

bool
net80211_sta_update_max_bandwidth(struct net80211_sta *sta,
    enum ieee80211_sta_rx_bandwidth max_bw,
    bool notify)
{
    enum ieee80211_sta_rx_bandwidth new_bw = IEEE80211_STA_RX_BANDWIDTH_20;

    sta->cur_max_bandwidth = max_bw;

    /*  recalc sta bw */
    new_bw = net80211_sta_cur_vht_bw(sta);

    if (sta->bandwidth == new_bw)
        return false;

    sta->bandwidth = new_bw;
    sta->rc_changed |= IEEE80211_RC_CHANGED_BW;
    if (notify) {
        drv_sta_rc_update(sta->pdev, sta->vif, sta);
    }

    return true;
}

void
net80211_sta_report_low_ack(struct net80211_sta *sta,
    u32 num_packets)
{
    net80211_vif_connection_loss(sta->vif);
}

/* vif */
struct net80211_sta *
net80211_vif_get_sta(struct net80211_vif *vif, const u8 *addr)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_sta *sta;

    list_for_each_entry(sta, &pdev->sta_list, struct net80211_sta, node) {
        if (ether_addr_equal(net80211_sta_addr(sta), addr)) {
            if (net80211_sta_vif(sta) == vif) {
                return sta;
            }
        }
    }

    return NULL;
}

struct net80211_sta *
net80211_vif_find_sta(struct net80211_vif *vif, const u8 *addr)
{
    struct net80211_sta *sta;

    if (!vif)
        return NULL;

    sta = net80211_vif_get_sta(vif, addr);
    if (!sta) {
        net_dbg("unable to find sta %02X:%02X:%02X:%02X:%02X:%02X\n",
            addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
        return NULL;
    }

    if (!net80211_sta_is_uploaded(sta))
        return NULL;

    return sta;
}

int
net80211_vif_destroy_sta(struct net80211_vif *vif, const u8 *addr)
{
    struct net80211_sta *sta = net80211_vif_get_sta(vif, addr);
    if (!sta)
        return -EINVAL;

    return net80211_sta_destroy(sta);
}

int
net80211_vif_flush_stations(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_sta *sta, *tmp;
    int ret = 0;

    list_for_each_entry_safe(sta, tmp, 
        &pdev->sta_list, struct net80211_sta, node) {
        if (vif == sta->vif) {
            net80211_sta_destroy(sta);
            ret++;
        }
    }

    return ret;
}

void net80211_iterate_stations(struct net80211_pdev *pdev,
    void(*iterator)(void *data, struct net80211_sta *sta),
    void *data)
{
    struct net80211_sta *sta;

    list_for_each_entry(sta, &pdev->sta_list, struct net80211_sta, node) {
        iterator(data, sta);
    }
}

/* pdev */
void
net80211_stations_init(struct net80211_pdev *pdev)
{
    list_init_head(&pdev->sta_list);
}

void
net80211_stations_remove(struct net80211_pdev *pdev)
{
    struct net80211_sta *sta, *tmp;

    list_for_each_entry_safe(sta, tmp, &pdev->sta_list,
        struct net80211_sta, node) {
        net80211_sta_destroy(sta);
    }
}
