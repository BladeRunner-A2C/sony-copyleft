/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 22/9/21   zxue     support beacon filter
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/ndebug.h>
#include <net/netdevice.h>
#include "net80211_i.h"
#include "drvops.h"
#include "vif.h"

#define NET80211_SCAN_RESULT_EXPIRE_US	  (120 * 1000 * 1000)
#define NET80211_TPUT_THRESHOLD_NO_SCAN   2000

struct net80211_internal_bss {
    list_entry_t node;

    unsigned long refcount;

    struct net80211_bss pub;
};

/* utils */
static bool
ieee80211_elements_is_uapsd_supported(struct ieee802_11_elems *elems)
{
    u8 qos_info = 0;

    if (elems->wmm_info && elems->wmm_info_len == 7 && elems->wmm_info[5] == 1) {
		/*check wmm info*/
        qos_info = elems->wmm_info[6];
    } else if (elems->wmm_param && elems->wmm_param_len == 24 && elems->wmm_param[5] == 1) {
        /*check wmm para*/
        qos_info = elems->wmm_param[6];
    } else {
        return false;
    }

    return qos_info & IEEE80211_WMM_IE_AP_UAPSD;
}

static bool
ieee80211_bss_type_match(u16 capability,
    enum nl80211_band band,
    enum ieee80211_bss_type bss_type)
{
    static const u16 type_caps[] = {
        [IEEE80211_BSS_TYPE_ESS] = WLAN_CAPABILITY_ESS,
        [IEEE80211_BSS_TYPE_IBSS] = WLAN_CAPABILITY_IBSS,
        [IEEE80211_BSS_TYPE_MBSS] = 0,
        [IEEE80211_BSS_TYPE_PBSS] = 0xff
    };

    u16 mask, val;

    if (bss_type == IEEE80211_BSS_TYPE_ANY)
        return true;

    mask = WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS;
    val = (bss_type < ARRAY_LENGTH(type_caps)) ? type_caps[bss_type] : 0xff;

    return ((capability & mask) == val);
}

static int ieee802_11_parse_vendor_specific(const u8 *pos, u8 elen,
    struct ieee802_11_elems *elems)
{
    u32 oui;

    if (elen < 4) {
        net_dbg("short vendor specific information element ignored (len=%lu)", elen);
        return -1;
    }

    oui = __cpu_to_be32(*(u32 *)pos);
    switch (oui) {
    case WLAN_OUI_MICROSOFT_WPA:
        break;
    case WLAN_OUI_MICROSOFT_WMM:
        if (elen < 5) {
            net_dbg("short WMM information element ignored (len=%lu)", elen);
            return -1;
        }

        /* OUI Type 2 - WMM IE */
        if (pos[4] == 0) {
            elems->wmm_info = pos;
            elems->wmm_info_len = elen;
        }
        else if (pos[4] == 1) {
            elems->wmm_param = pos;
            elems->wmm_param_len = elen;
        }
        break;
    case WLAN_OUI_MICROSOFT_WPS:
        break;
    default:
        return -1;

    }
 
    return 0;
}
/*
 * ieee80211_he_spr_size - calculate 802.11ax HE Spatial Reuse IE size
 */
static inline u8
ieee80211_he_spr_size(const u8* he_spr_ie)
{
    struct ieee80211_he_spr* he_spr = (void*)he_spr_ie;
    u8 spr_len = sizeof(struct ieee80211_he_spr);
    u8 he_spr_params;

    /* Make sure he_spr_ie is valid */
    if (!he_spr_ie)
        return 0;

    /* Calc the required len */
    he_spr_params = he_spr->he_sr_control;
    if (he_spr_params & IEEE80211_HESPR_NON_SRG_OFFSET_PRESENT)
        spr_len++;
    if (he_spr_params & IEEE80211_HESPR_SRG_INFORMATION_PRESENT)
        spr_len += 18;

    /* Add the first byte (extension ID) */
    spr_len++;

    return spr_len;
}

static int
ieee802_11_parse_extension(
    const u8 *pos, u8 elen,
    struct ieee802_11_elems *elems)
{
    u8 len = elen - 1;
    const void *data = pos + 1;

    switch (pos[0]) {
    case WLAN_EID_EXT_HE_CAPABILITIES:
        elems->he_cap = data;
        elems->he_cap_len = len;
        break;
    case WLAN_EID_EXT_HE_OPERATION:
        elems->he_operation = data;
        elems->he_operation_len = len;
        break;
    case WLAN_EID_EXT_UORA:
        if (len == 1)
            elems->uora_element = data;
        break;
    case WLAN_EID_EXT_HE_MU_EDCA_PARAMS: 
        if (len == sizeof(*elems->mu_edca_param_set))
            elems->mu_edca_param_set = data;
        break;
    case WLAN_EID_EXT_MAX_CHANNEL_SWITCH_TIME:
        if (len == 3)
            elems->max_channel_switch_time = data;
        break;
    case WLAN_EID_EXT_MULTIPLE_BSSID_CONFIGURATION:
        if (len == sizeof(*elems->mbssid_config))
            elems->mbssid_config = data;
        break;
	case WLAN_EID_EXT_HE_6GHZ_BAND_CAP:
		if (len == sizeof(*elems->he_6ghz_cap))
			elems->he_6ghz_cap = data;
		break;
    case WLAN_EID_EXT_SPATIAL_REUSE:
        if (len >= sizeof(*elems->he_spr) &&
            len >= ieee80211_he_spr_size(data))
            elems->he_spr = data;
        break;
    }
    
    return 0;
}

int ieee802_11_parse_elems(const u8 *start, size_t len,
    struct ieee802_11_elems *elems)
{
    const struct element *elem;
    u32 unknown = 0;

    memset(elems, 0, sizeof(*elems));

    if (!start)
        return 0;

    for_each_element(elem, start, len) {
        u32 elem_parse_failed = 0;
        u8 id = elem->id, elen = elem->datalen;
        const u8 *pos = elem->data;

        switch (id) {
        case WLAN_EID_SSID:
			/*parse ssid*/
            if (elen > IEEE80211_MAX_SSID_LEN) {
                elem_parse_failed++;
                break;
            }

            elems->ssid = pos;
            elems->ssid_len = elen;
            break;
        case WLAN_EID_SUPP_RATES:
			/*parse supported rates*/
            elems->supp_rates = pos;
            elems->supp_rates_len = elen;
            break;
        case WLAN_EID_DS_PARAMS:
			/*parse DS parameters*/
            if (elen < 1)
                elem_parse_failed++;
            else
                elems->ds_params = pos;
            break;
        case WLAN_EID_CF_PARAMS:
            break;
        case WLAN_EID_TIM:
            if (elen < sizeof(struct ieee80211_tim)) {
                elem_parse_failed++;
            }
            else {
                elems->tim = (void *)pos;
                elems->tim_len = elen;
            }
            break;
        case WLAN_EID_COUNTRY:
            elems->country_elem = pos;
            elems->country_elem_len = elen;
            break;
        case WLAN_EID_CHALLENGE:
            elems->challenge = pos;
            elems->challenge_len = elen;
            break;
        case WLAN_EID_PWR_CONSTRAINT:
            if (elen != 1)
                elem_parse_failed++;
            else
                elems->power_constraint_elem = pos;
            break;
        case WLAN_EID_ERP_INFO:
            if (elen < 1)
                elem_parse_failed++;
            else
                elems->erp_info = pos;
            break;
        case WLAN_EID_EXT_SUPP_RATES:
            elems->ext_supp_rates = pos;
            elems->ext_supp_rates_len = elen;
            break;
        case WLAN_EID_VENDOR_SPECIFIC:
            if (ieee802_11_parse_vendor_specific(pos, elen, elems))
                unknown++;
            break;
        case WLAN_EID_RSN:
            elems->rsn = pos;
            elems->rsn_len = elen;
            break;
        case WLAN_EID_CHANNEL_SWITCH:
            if (elen != sizeof(struct ieee80211_chan_switch))
                elem_parse_failed++;
            else
                elems->chan_switch = (void *)pos;
            break;
        case WLAN_EID_EXT_CHANSWITCH_ANN:
            if (elen != sizeof(struct ieee80211_extended_chan_switch))
                elem_parse_failed++;
            else
                elems->extended_chan_switch = (void *)pos;
            break;
        case WLAN_EID_TIMEOUT_INTERVAL:
            if (elen < sizeof(struct ieee80211_timeout_interval))
                elem_parse_failed++;
            else
                elems->timeout_int = (void *)pos;
            break;
        case WLAN_EID_SECONDARY_CHANNEL_OFFSET:
            if (elen != sizeof(struct ieee80211_sec_chan_offset))
                elem_parse_failed++;
            else
                elems->sec_chan_offset = (void *)pos;
            break;
        case WLAN_EID_HT_CAP:
            if (elen < sizeof(struct ieee80211_ht_capabilities))
                elem_parse_failed++;
            else
                elems->ht_capabilities = (void *)pos;
            break;
        case WLAN_EID_HT_OPERATION:
            if (elen < sizeof(struct ieee80211_ht_operation))
                elem_parse_failed++;
            else
                elems->ht_operation = (void *)pos;
            break;
        case WLAN_EID_CHANNEL_SWITCH_TIMING:
            if (elen != sizeof(struct ieee80211_ch_switch_timing))
                elem_parse_failed++;
            else
                elems->ch_sw_timing = (void *)pos;
            break;
        case WLAN_EID_MESH_ID:
            elems->mesh_id = pos;
            elems->mesh_id_len = elen;
            break;
        case WLAN_EID_PEER_MGMT:
            elems->peering = pos;
            elems->peering_len = elen;
            break;
        case WLAN_EID_VHT_CAP:
            if (elen < sizeof(struct ieee80211_vht_capabilities))
                elem_parse_failed++;
            else
                elems->vht_capabilities = (void *)pos;
            break;
        case WLAN_EID_VHT_OPERATION:
            if (elen < sizeof(struct ieee80211_vht_operation))
                elem_parse_failed++;
            else
                elems->vht_operation = (void *)pos;
            break;
        case WLAN_EID_EXT_CAPAB:
            elems->ext_capab = pos;
            elems->ext_capab_len = elen;
            break;
        case WLAN_EID_BSS_MAX_IDLE_PERIOD:
            if (elen < 3)
                elem_parse_failed++;
            else
                elems->bss_max_idle_period = (void *)pos;
            break;
        case WLAN_EID_ADDBA_EXTENSION:
            if (elen != sizeof(struct ieee80211_addba_extension))
                elem_parse_failed++;
            else
                elems->addba_extension = (void *)pos;
            break;
        case WLAN_EID_VHT_WIDE_BW_CHSWITCH:
            if (elen != sizeof(*elems->wide_bw_chansw))
                elem_parse_failed++;
            else
                elems->wide_bw_chansw = (void *)pos;
            break;
        case WLAN_EID_VHT_OPERATING_MODE_NOTIFICATION:
            if (elen == 0)
                elem_parse_failed++;
            else
                elems->opmode_notif = pos;
            break;
        case WLAN_EID_RSNX:
            elems->rsnx = pos;
            elems->rsnx_len = elen;
            break;
        case WLAN_EID_EXTENSION:
            if (ieee802_11_parse_extension(pos, elen, elems))
                unknown++;
            break;
        default:
            unknown++;
            net_dbg("IEEE 802.11 element parse ignored unknown element (id=%d elen=%d)\n",
                id, elen);
            break;
        }

        if(elem_parse_failed)
            elems->parse_error = true;
    }

    if (!for_each_element_completed(elem, start, len)) {
        elems->parse_error = true;
    }

    return unknown ? -E2BIG : 0;
}

/* struct net80211_internal_bss */
static void
net80211_internal_bss_free(struct net80211_internal_bss *bss)
{
    void *ies = (void *)bss->pub.ies;

    if (ies)
        kfree(ies);
    kfree(bss);
}

static inline void
net80211_internal_bss_ref_get(struct net80211_internal_bss *bss)
{
    bss->refcount++;
}

static inline void
net80211_internal_bss_ref_put(struct net80211_internal_bss *bss)
{
    bss->refcount--;
    if (bss->refcount == 0)
        net80211_internal_bss_free(bss);
}

static bool
net80211_bss_match(struct net80211_bss *bss, 
    const u8 *bssid,
    const u8 *ssid, u32 ssid_len)
{
    const struct element *ssidie;

    if (bssid && !ether_addr_equal(bss->bssid, bssid))
        return false;

    if (!ssid)
        return true;

    ssidie = net80211_bss_find_element(bss, WLAN_EID_SSID);
    if (!ssidie)
        return false;
    if (ssidie->datalen != ssid_len)
        return false;
    return memcmp(ssidie->data, ssid, ssid_len) == 0;
}

static int
net80211_bss_compare(struct net80211_bss *a, struct net80211_bss *b)
{
    const struct element *ie1 = NULL, *ie2 = NULL;
    int r;

    /* BSSID */
    r = memcmp(a->bssid, b->bssid, sizeof(a->bssid));
    if (r)
        return r;

    /* SSID */
    ie1 = net80211_bss_find_element(a, WLAN_EID_SSID);
    ie2 = net80211_bss_find_element(b, WLAN_EID_SSID);

    if (!ie1 && !ie2)
        return 0;

    /* TODOTODO: support hidden ssid */

    if (!ie1)
        return -1;
    if (!ie2)
        return 1;

    /* length */
    if (ie1->datalen != ie2->datalen)
        return ie2->datalen - ie1->datalen;
    return memcmp(ie1->data, ie2->data, ie1->datalen);
}

static void
net80211_unlink_bss(struct net80211_pdev *pdev,
    struct net80211_internal_bss *bss)
{
    list_del(&bss->node);
    pdev->bss_entries--;

    net80211_internal_bss_ref_put(bss);
}

void net80211_bss_iterate(struct net80211_pdev *pdev,
    void(*iterate)(struct net80211_pdev *pdev, struct net80211_bss *bss, void *data),
    void *iterate_data)
{
    struct net80211_internal_bss *bss;
	
	list_for_each_entry(bss, &pdev->bss_list, 
		struct net80211_internal_bss, node) {
		iterate(pdev, &bss->pub, iterate_data);
	}
}

static void
net80211_bss_expire(struct net80211_pdev *pdev)
{
    struct net80211_internal_bss *bss, *tmp;
    u64 now = getwalltime_us();
    u64 expire_time = (now > NET80211_SCAN_RESULT_EXPIRE_US) ? 
        (now - NET80211_SCAN_RESULT_EXPIRE_US) : 0;

    list_for_each_entry_safe(bss, tmp, &pdev->bss_list, 
        struct net80211_internal_bss, node) {
        if (expire_time <= bss->pub.ts)
            continue;

        net_dbg("Unlink expired bss: 0x%x, bssid=%02X:%02X:%02X:%02X:%02X:%02X, ts=%llu(expired %llu)\n", 
            bss, bss->pub.bssid[0], bss->pub.bssid[1],
            bss->pub.bssid[2], bss->pub.bssid[3],
            bss->pub.bssid[4], bss->pub.bssid[5], bss->pub.ts, expire_time);
        net80211_unlink_bss(pdev, bss);
    }
}

static struct net80211_internal_bss *
net80211_find_bss(struct net80211_pdev *pdev,
    struct net80211_internal_bss *res)
{
    struct net80211_internal_bss *bss;
    int r;

    list_for_each_entry(bss, &pdev->bss_list, struct net80211_internal_bss, node) {
        r = net80211_bss_compare(&res->pub, &bss->pub);
        if (r == 0)
            return bss;
    }

    return NULL;
}

static void
net80211_assign_known_bss(struct net80211_pdev *pdev,
    struct net80211_internal_bss *nbss_known,
    struct net80211_internal_bss *nbss_new)
{
    const struct net80211_bss_ies *old_ies;

    old_ies = rcu_access_pointer(nbss_known->pub.ies);
    rcu_assign_pointer(nbss_known->pub.ies, nbss_new->pub.ies);
    rcu_assign_pointer(nbss_new->pub.ies, NULL);
    if (old_ies) {
        kfree((void *)old_ies);
    }

    nbss_known->pub.channel = nbss_new->pub.channel;
    nbss_known->pub.signal = nbss_new->pub.signal;
    nbss_known->pub.beacon_interval = nbss_new->pub.beacon_interval;
    nbss_known->pub.capability = nbss_new->pub.capability;
    nbss_known->pub.chains = nbss_new->pub.chains;
    memcpy(nbss_known->pub.chain_signal, nbss_new->pub.chain_signal, IEEE80211_MAX_CHAINS);
    nbss_known->pub.ts = nbss_new->pub.ts;

    kfree(nbss_new);
}

struct net80211_bss *
net80211_ref_bss(struct net80211_pdev *pdev, struct net80211_bss *pub)
{
    struct net80211_internal_bss *bss;

    if (!pub)
        return NULL;

    bss = container_of(pub, struct net80211_internal_bss, pub);
    net80211_internal_bss_ref_get(bss);

    return &bss->pub;
}

void
net80211_put_bss(struct net80211_pdev *pdev, struct net80211_bss *pub)
{
    struct net80211_internal_bss *bss;

    if (!pub)
        return;

    bss = container_of(pub, struct net80211_internal_bss, pub);
    net80211_internal_bss_ref_put(bss);
}

struct net80211_bss *
net80211_get_bss(struct net80211_pdev *pdev,
    struct ieee80211_channel *channel,
    const u8 *bssid,
    const u8 *ssid, u32 ssid_len,
    enum ieee80211_bss_type bss_type,
    enum ieee80211_privacy privacy)
{
    struct net80211_internal_bss *bss, *res = NULL;
    int bss_privacy;
    u64 now = getwalltime_us();

    list_for_each_entry(bss, &pdev->bss_list, 
        struct net80211_internal_bss, node) {
        if (!ieee80211_bss_type_match(bss->pub.capability, bss->pub.channel->band, bss_type))
            continue;

        if ((!is_valid_ether_addr(bss->pub.bssid)) || 
			 (channel && bss->pub.channel != channel))
            continue;
		
        bss_privacy = (bss->pub.capability & WLAN_CAPABILITY_PRIVACY);
        if ((privacy == IEEE80211_PRIVACY_ON && !bss_privacy) ||
            (privacy == IEEE80211_PRIVACY_OFF && bss_privacy))
            continue;

        /* bypass expired bss */
        if (now > (bss->pub.ts + NET80211_SCAN_RESULT_EXPIRE_US))
            continue;
        if (net80211_bss_match(&bss->pub, bssid, ssid, ssid_len)) {
            res = bss;
            net80211_internal_bss_ref_get(res);
            break;
        }
    }

    return res ? &res->pub : NULL;
}

struct net80211_bss *
net80211_inform_bss_frame_data(
    struct net80211_pdev *pdev, s8 signal,
    enum net80211_bss_scan_width scan_width,
    struct ieee80211_mgmt *mgmt, size_t len,
    struct ieee80211_channel *channel)
{
    struct net80211_internal_bss *bss_new, *bss;
    struct net80211_bss_ies *ies;
    u32 ielen = (u32)(len - offsetof(struct ieee80211_mgmt,
        u.probe_resp.variable));

    bss_new = kzalloc(sizeof(*bss_new), GFP_KERNEL);
    if (!bss_new) {
        return NULL;
    }
    bss_new->refcount++;
    bss_new->pub.ts = getwalltime_us();

    /* bssid */
    memcpy(bss_new->pub.bssid, mgmt->bssid, ETH_ALEN);

    /* channel & scan_width */
    bss_new->pub.channel = channel;
    bss_new->pub.scan_width = scan_width;

    bss_new->pub.beacon_interval = le16_to_cpu(mgmt->u.probe_resp.beacon_int);
    bss_new->pub.capability = le16_to_cpu(mgmt->u.probe_resp.capab_info);

    /* update the signal */
    bss_new->pub.signal = signal;

    /* build the ies */
    ies = kzalloc(sizeof(*ies) + ielen, GFP_KERNEL);
    if (!ies) {
        kfree(bss_new);
        return NULL;
    }
    ies->from_beacon = ieee80211_is_beacon(mgmt->frame_control);
    ies->tsf = le64_to_cpu(mgmt->u.probe_resp.timestamp);
    ies->len = ielen;
    memcpy(ies->data, mgmt->u.probe_resp.variable, ielen);
    rcu_assign_pointer(bss_new->pub.ies, ies);

    bss = net80211_find_bss(pdev, bss_new);
    if (!bss) {
        net_dbg("Add new bss: 0x%x, bssid=%02X:%02X:%02X:%02X:%02X:%02X, ts=%llu, freq=%d\n", 
            bss_new, 
            bss_new->pub.bssid[0], bss_new->pub.bssid[1],
            bss_new->pub.bssid[2], bss_new->pub.bssid[3],
            bss_new->pub.bssid[4], bss_new->pub.bssid[5], bss_new->pub.ts, bss_new->pub.channel->center_freq);
		list_add_tail(&bss_new->node, &pdev->bss_list);
        pdev->bss_entries++;
        bss = bss_new;
    }
    else {
        net80211_assign_known_bss(pdev, bss, bss_new);
        net_dbg("Update known bss: 0x%x, bssid=%02X:%02X:%02X:%02X:%02X:%02X, ts=%llu, freq=%d\n", 
            bss, bss->pub.bssid[0], bss->pub.bssid[1],
            bss->pub.bssid[2], bss->pub.bssid[3],
            bss->pub.bssid[4], bss->pub.bssid[5], bss->pub.ts, bss->pub.channel->center_freq);
    }
    
    return &bss->pub;
}

static void
net80211_update_bss_data_from_elems(struct net80211_pdev *pdev,
    struct net80211_bss *bss,
    struct ieee802_11_elems *elems,
    struct ieee80211_rx_status *rx_status,
    bool beacon)
{
    int clen, srlen;

    bss->data.corrupt = elems->parse_error;

    if (elems->erp_info && 
        (!elems->parse_error || !bss->data.erp_valid)) {
        bss->data.erp_value = elems->erp_info[0];
        bss->data.erp_valid = 1;
    }

    /* overwrite old supported rates if we get new values */
    if (!elems->parse_error || !bss->data.rates_valid) {
        srlen = 0;
        if (elems->supp_rates) {
            clen = IEEE80211_MAX_SUPP_RATES;
            if (clen > elems->supp_rates_len)
                clen = elems->supp_rates_len;
            memcpy(bss->data.supp_rates, elems->supp_rates, clen);
            srlen += clen;
        }
        if (elems->ext_supp_rates) {
            clen = IEEE80211_MAX_SUPP_RATES - srlen;
            if (clen > elems->ext_supp_rates_len)
                clen = elems->ext_supp_rates_len;
            memcpy(bss->data.supp_rates + srlen, elems->ext_supp_rates,
                clen);
            srlen += clen;
        }
        if (srlen) {
            bss->data.supp_rates_len = (u8)srlen;
            if (!elems->parse_error)
                bss->data.rates_valid = 1;
        }
    }

    if (!elems->parse_error || !bss->data.wmm_valid) {
        bss->data.wmm_used = (elems->wmm_param || elems->wmm_info);
        bss->data.uapsd_supported = ieee80211_elements_is_uapsd_supported(elems);
        if (!elems->parse_error)
            bss->data.wmm_valid = 1;
    }

    bss->chains = rx_status->chains;
	memcpy(bss->chain_signal, rx_status->chain_signal, sizeof(bss->chain_signal));
    if (beacon) {
        if (!(rx_status->encoding == RX_ENC_HT) &&
            !(rx_status->encoding == RX_ENC_VHT)) {
            bss->data.beacon_rate = net80211_get_band_rate(pdev,
                rx_status->band, rx_status->rate_idx);
        }
    }
}

static void
net80211_update_bss_channel_from_elems(struct net80211_pdev *pdev,
    struct net80211_bss *bss,
    struct ieee802_11_elems *elems)
{
    struct ieee80211_channel *bss_channel = bss->channel;
    struct ieee80211_channel *channel;
    u32 freq = 0;

    if (!bss_channel)
        return;

    /* 11AX BSS may support duplicated beacon */
    if (elems->he_operation && elems->ht_operation) {
        enum nl80211_band band = bss_channel->band;
        u8 primary_chan = elems->ht_operation->primary_chan;
        freq = ieee80211_channel_to_frequency(primary_chan, band);
    }

    /* TODO6G: Get primary channel from HE operation IE for 6G */

    if (freq && (freq != bss_channel->center_freq)) {
        net_dbg("freq = %d channel->center_freq = %d\n", freq, bss_channel->center_freq);
        channel = net80211_get_channel(pdev, freq);
        if (channel)
            bss->channel = channel;
    }
}

struct net80211_bss *
net80211_bss_info_update(struct net80211_pdev *pdev,
    struct ieee80211_rx_status *rx_status,
    struct ieee80211_mgmt *mgmt, size_t len,
    struct ieee80211_channel *channel)
{
    struct net80211_bss *bss;
    s8 signal = 0;
    enum net80211_bss_scan_width scan_width;
    bool beacon = ieee80211_is_beacon(mgmt->frame_control);
    struct ieee802_11_elems elems;
    u32 baselen;
    u8 *elements;

    if (rx_status->flag & IEEE80211_RX_FLAG_NO_SIGNAL_VAL)
        signal = 0;
    else
        signal = rx_status->signal;

    if (rx_status->bw == IEEE80211_RATE_INFO_BW_5)
        scan_width = NET80211_BSS_CHAN_WIDTH_5;
    else if (rx_status->bw == IEEE80211_RATE_INFO_BW_10)
        scan_width = NET80211_BSS_CHAN_WIDTH_10;
    else
        scan_width = NET80211_BSS_CHAN_WIDTH_20;

    bss = net80211_inform_bss_frame_data(
        pdev, signal, scan_width, mgmt, len, channel);
	
    if (!bss) {
		net_dbg("bss NULL!\n");
        return NULL;
    }

    if (ieee80211_is_probe_resp(mgmt->frame_control)) {
        elements = mgmt->u.probe_resp.variable;
        baselen = offsetof(struct ieee80211_mgmt, u.probe_resp.variable);
    }
    else {
        baselen = offsetof(struct ieee80211_mgmt, u.beacon.variable);
        elements = mgmt->u.beacon.variable;
    }

    if (baselen > len) {
		net_dbg("Length invalid!\n");
        return NULL;
    }

    ieee802_11_parse_elems(elements, len - baselen, &elems);

    net80211_update_bss_data_from_elems(pdev, bss, &elems, rx_status, beacon);

    net80211_update_bss_channel_from_elems(pdev, bss, &elems);

    return bss;
}

static void
net80211_prepare_scan_chandef(struct ieee80211_chan_def* chandef,
    enum net80211_bss_scan_width scan_width)
{
    memset(chandef, 0, sizeof(*chandef));
    switch (scan_width) {
    case NET80211_BSS_CHAN_WIDTH_5:
        chandef->width = NL80211_CHAN_WIDTH_5;
        break;
    case NET80211_BSS_CHAN_WIDTH_10:
        chandef->width = NL80211_CHAN_WIDTH_10;
        break;
    default:
        chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
        break;
    }
}

/* return false if no more work */
static bool net80211_prep_hw_scan(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_scan_request *req)
{
    struct ieee80211_chan_def chandef;
    u8 bands_used = 0;
    int ielen, n_chans;
    u32 flags = 0;
    int hw_scan_ie_len = pdev->conf.max_scan_ie_len;
    u32 i;

    if (net80211_hw_check(pdev, IEEE80211_HW_SINGLE_SCAN_ON_ALL_BANDS)) {
        for (i = 0; i < req->n_channels; i++) {
            bands_used |= BIT(req->channels[i]->band);
        }
        n_chans = req->n_channels;
    }
    else {
        do {
            n_chans = 0;
            if (!req->n_channels)
                break;
            for (i = 0; i < req->n_channels; i++) {
                n_chans++;
                bands_used |= BIT(req->channels[i]->band);
            }
        } while (!n_chans);
    }

    req->n_channels = n_chans;
    net80211_prepare_scan_chandef(&chandef, req->scan_width);

    ielen = net80211_vif_build_preq_ies(vif,
        (u8*)req->ie,
        hw_scan_ie_len,
        &req->scan_ies,
        req->ie, req->ie_len,
        bands_used, req->rates, &chandef,
        flags);

    req->ie_len = ielen;
    return true;
}


void
net80211_scan_done(struct net80211_scan_request *scan_req,
    bool aborted)
{
    struct net80211_pdev *pdev = scan_req->vif->pdev;
    struct net80211_dev_event devt = { 0 };
    struct net80211_scan_result *result;

    /* clean up expired bss */
    net80211_bss_expire(pdev);

    devt.type = NET80211_EVENT_SCAN_COMPLETE;
    devt.vif = scan_req->vif;

    /* event data */
    BUILD_BUG_ON(sizeof(devt.data) < sizeof(*result));
    result = (struct net80211_scan_result *)devt.data;
    result->aborted = aborted;

    net80211_dev_notify(pdev, &devt);

    kfree(scan_req);
}

void
net80211_scan_completed(struct net80211_pdev *pdev, bool aborted)
{
    struct net80211_vif *vif;
    struct net80211_scan_request *scan_req;

    vif = pdev->scan_vif;
    scan_req = pdev->scan_req;

    /* Indicates to upper layer */
    if (scan_req) {
        pdev->scan_vif = NULL;
        pdev->scan_req = NULL;

		/* rollback the bcn filter */
        net80211_vif_deactivate_beacon_filter(vif, scan_req, 0);

        net_dbg("vif 0x%p, scan_req 0x%p %a\n", 
            vif, scan_req, aborted ? "aborted" : "completed");
        net80211_scan_done(scan_req, aborted);
    }
}

static int
net80211_request_scan(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_scan_request *req)
{
    int ret;

    if (pdev->scan_req)
        return -EBUSY;

    pdev->scan_req = req;
    pdev->scan_vif = vif;

    if (!net80211_prep_hw_scan(pdev, vif, req)) {
        net_dbg("net80211_prep_hw_scan failed\n");
        return -ENOMEM;
    }
        
	/* deactivate the bcn filter */
	net80211_vif_deactivate_beacon_filter(vif, req, 1);
		
    ret = drv_hw_scan(pdev, vif, req);
	if (ret) {
		net80211_vif_deactivate_beacon_filter(vif, req, 0);
	}

    return ret;
}

void
net80211_scan_cancel(struct net80211_pdev *pdev)
{
    if (!pdev->scan_req)
        return;

    if (pdev->ops->ieee80211_cancel_hw_scan) {
        drv_cancel_hw_scan(pdev, pdev->scan_vif);
    }
}

int 
net80211_scan(struct net80211_pdev *pdev, 
    struct net80211_scan_request *request)
{
    struct net80211_vif *vif = request->vif;
    u64 tx_tput, rx_tput;

    /* cancle scan when tput is high */
    if (net80211_vif_get_associated(vif)) {
        tx_tput = netdev_get_tx_tput(&vif->dev);
        if (tx_tput > NET80211_TPUT_THRESHOLD_NO_SCAN) {
            net_dbg("cancel scan as tx tput %d (>%d)\n", 
                tx_tput, NET80211_TPUT_THRESHOLD_NO_SCAN);
            return -EBUSY;
        }

        rx_tput = netdev_get_rx_tput(&vif->dev);
        if (rx_tput > NET80211_TPUT_THRESHOLD_NO_SCAN) {
            net_dbg("cancel scan as rx tput %d (>%d)\n", 
                rx_tput, NET80211_TPUT_THRESHOLD_NO_SCAN);
            return -EBUSY;
        }
    }

    return net80211_request_scan(pdev, vif, request);
}

void
net80211_scan_rx(struct net80211_pdev *pdev, struct sk_buff *skb)
{
    struct ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
    struct ieee80211_mgmt *mgmt = (void *)skb->data;
    struct ieee80211_channel *channel;

    struct net80211_vif *vif;
    struct net80211_scan_request *scan_req;

    DEBUG_PARAMETER(vif);
    DEBUG_PARAMETER(scan_req);

    if (skb->len < 24)
        return;

	channel = net80211_get_channel(pdev, rx_status->freq);
    if (!channel || channel->flags & IEEE80211_CHAN_DISABLED) {
        return;
    }

    if (!ieee80211_is_probe_resp(mgmt->frame_control) &&
        !ieee80211_is_beacon(mgmt->frame_control))
        return;

    vif = pdev->scan_vif;
    scan_req = pdev->scan_req;
	
    net_verb("skb 0x%p (rx_status 0x%p), vif 0x%p, scan_req 0x%p\n",
        skb, rx_status, vif, scan_req);

    net80211_bss_info_update(pdev, rx_status, mgmt, skb->len, channel);
}

void
net80211_scan_init(struct net80211_pdev *pdev)
{
    list_init_head(&pdev->bss_list);
}

void
net80211_scan_remove(struct net80211_pdev *pdev)
{
    struct net80211_internal_bss *bss, *tmp;

    list_for_each_entry_safe(bss, tmp, &pdev->bss_list,
        struct net80211_internal_bss, node) {
        net80211_put_bss(pdev, &bss->pub);
    }
}
