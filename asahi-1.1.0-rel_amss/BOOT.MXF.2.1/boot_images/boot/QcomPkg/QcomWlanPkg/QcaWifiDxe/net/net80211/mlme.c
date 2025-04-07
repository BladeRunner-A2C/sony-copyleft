/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 2/8/22    zxue     fix KW issue
 23/7/21   zxue     Fix the issue that deauth is wrong when PMF connection is fail at association process.
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/ndebug.h>
#include <net/net80211.h>
#include "net80211_i.h"
#include "chan.h"
#include "vif.h"
#include "sta.h"
#include "mlme.h"
#include "sme.h"

 /* NOTE: A LARGER TIMEOUT IS REQUIRED WHEN LOG IS ENABLED */
#define NET80211_AUTH_TIMEOUT		  (1 * 1000)
#define NET80211_AUTH_TIMEOUT_LONG	  (3 * 1000)
#define NET80211_AUTH_TIMEOUT_SAE	  (5 * 1000)
#define NET80211_AUTH_MAX_TRIES	      3

#define NET80211_ASSOC_TIMEOUT		  (3 * 1000)
#define NET80211_ASSOC_MAX_TRIES	  3

/* Spec says 8 but 6 in practice */
#define NET80211_COUNTRY_IE_MIN_LEN	6

static bool
net80211_find_80211h_power_constraint(struct net80211_vif *vif,
    struct ieee80211_channel *channel,
    const u8 *country_ie, u8 country_ie_len,
    const u8 *power_constraint_elem,
    s32 *chan_power, s32 *power_reduction)
{
	int chan = ieee80211_frequency_to_channel(channel->center_freq);
    int chan_increment = 0;
	bool have_chan_power = false;
    struct ieee80211_country_triplet *triplet;
    int i;

	/* Invalid country IE */
	if ((country_ie_len < NET80211_COUNTRY_IE_MIN_LEN) ||
        (country_ie_len % 2))
		return false;

    if (channel->band == NL80211_BAND_2GHZ || 
		channel->band == NL80211_BAND_60GHZ) {
        chan_increment = 1;
	}
    else if (channel->band == NL80211_BAND_5GHZ ||
        channel->band == NL80211_BAND_6GHZ) {
        chan_increment = 4;
	} else {
        WARN_ON_ONCE(1);
	}

    /* find channel */
    triplet = (void *)(country_ie + 3);
    country_ie_len -= 3;
	
	while (country_ie_len >= 3) {
		u8 first_chan = triplet->u.chans.first_chan;
        if (first_chan < IEEE80211_COUNTRY_EXTENSION_ID) {
            for (i = 0; i < triplet->u.chans.num_chans; i++) {
                if (first_chan + i * chan_increment == chan) {
                    have_chan_power = true;
                    *chan_power = triplet->u.chans.max_power;
                    break;
                }
            }
            if (have_chan_power)
                break;
        }

		triplet++;
		country_ie_len -= 3;
	}
    
    *power_reduction = (have_chan_power && power_constraint_elem) ? (*power_constraint_elem) : 0;

	return have_chan_power;
}

static u32
net80211_handle_power_constraint(struct net80211_vif *vif,
    struct ieee80211_channel *channel,
    struct ieee80211_mgmt *mgmt,
    const u8 *country_ie, u8 country_ie_len,
    const u8 *power_constraint_ie)
{
	bool has_80211h_power = false;
	s32 chan_power = 0;
	s32 power_reduction_80211h = 0;
	s32 power_level_80211h;
	__le16 capab_info = mgmt->u.probe_resp.capab_info;

	if (country_ie &&
        (capab_info & cpu_to_le16(WLAN_CAPABILITY_SPECTRUM_MGMT) ||
            capab_info & cpu_to_le16(WLAN_CAPABILITY_RADIO_MEASURE))) {
        has_80211h_power = net80211_find_80211h_power_constraint(
            vif, channel, country_ie, country_ie_len,
            power_constraint_ie, &chan_power, &power_reduction_80211h);
		
		power_level_80211h = max_t(s32, 0, chan_power - power_reduction_80211h);
	}

	if (!has_80211h_power)
		return 0;

	/* pick up the 802.11h power level. */
	if (vif->ap_power_level == power_level_80211h)
		return 0;

	net_dbg("Set ap power level to %d (%d - %d) dBm as advertised by %pM\n",
        power_level_80211h, chan_power, power_reduction_80211h,
        net80211_vif_get_bssid(vif));
	
	vif->ap_power_level = power_level_80211h;
	net80211_recalc_txpower(vif, true);

	return 0;
}

static inline bool
net80211_rx_our_beacon(const u8 *tx_bssid, u8 *bssid)
{
	return ether_addr_equal(tx_bssid, bssid);
}

static void
net80211_sta_rx_mgmt_beacon(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, u32 len,
    struct ieee80211_rx_status *rx_status)
{
	size_t baselen;
	struct ieee802_11_elems elems;
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct ieee80211_channel *chan;

	net_dbg("received beacon\n");

	/* Process beacon from the current BSS */
	baselen = (u8 *)mgmt->u.beacon.variable - (u8 *) mgmt;
	if (baselen > len)
	    return;

	chanctx_conf = rcu_dereference(vif->chanctx_conf);
	if (!chanctx_conf) {
		return;
	}

	if (rx_status->freq != chanctx_conf->def.chan->center_freq) {
		return;
	}
	
	chan = chanctx_conf->def.chan;

	if (!net80211_vif_get_associated(vif) ||
	    !net80211_rx_our_beacon(mgmt->bssid,  vif->bss_conf.bssid)) {
		return;
	}
	
	ieee802_11_parse_elems(mgmt->u.beacon.variable, len - baselen, &elems);
	/*
	 * TODOTODO:
	 * 1. TIM
	 * 2. TSF
	 * 3. WMM disable
	 * 4. DTIM
	 */
	net80211_handle_power_constraint(vif, chan, mgmt,
        elems.country_elem,
        elems.country_elem_len,
        elems.power_constraint_elem);
	
	net80211_vif_bss_conf_change_notify(vif);
}

static void
net80211_sta_rx_mgmt_probe_resp(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, u32 len,
    struct ieee80211_rx_status *rx_status)
{
    net_dbg("received probe response\n");
}

static void
net80211_sta_auth_challenge(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, size_t len)
{
    // TODOTODO: auth challenge
}

static bool
net80211_sta_mark_sta_auth(struct net80211_vif *vif,
    const u8 *bssid)
{
    struct net80211_sta *sta;
    bool result = true;

    net_dbg("authenticated\n");

    /* move station state to auth */
    sta = net80211_vif_get_sta(vif, bssid);
    if (!sta) {
        WARN(1, "%a: STA %pM not found", vif->name, bssid);
        result = false;
        goto out;
    }
    if (net80211_sta_move_state(sta, IEEE80211_STA_AUTH)) {
        net_warn("failed moving %pM to auth\n", bssid);
        result = false;
        goto out;
    }

out:
    return result;
}

static int
net80211_sta_send_sae_auth_response(
    struct net80211_vif *vif,
    struct net80211_auth_data *auth_data,
    const void *data,
    u32 data_len);

static void
net80211_sta_rx_mgmt_auth(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, u32 len)
{
    struct net80211_auth_data *auth_data;
    u8 bssid[ETH_ALEN];
    u16 status_code;
    u16 auth_algorithm, auth_transaction;

    net_dbg("sa: 0x%pM, length %d\n", mgmt->sa, len);

    if (len < 24 + 6)
        return;

    auth_data = net80211_sta_get_auth_data(vif);

    if (!auth_data)
        return;

    memcpy(bssid, auth_data->bss->bssid, ETH_ALEN);

    if (!ether_addr_equal(bssid, mgmt->bssid))
        return;

    auth_algorithm = le16_to_cpu(mgmt->u.auth.auth_algorithm);
    auth_transaction = le16_to_cpu(mgmt->u.auth.auth_transaction);
    status_code = le16_to_cpu(mgmt->u.auth.status_code);

    if ((auth_algorithm != auth_data->algorithm) ||
        (auth_algorithm != WLAN_AUTH_MODE_SAE &&
            auth_transaction != auth_data->expected_transaction) ||
        (auth_algorithm == WLAN_AUTH_MODE_SAE &&
            (auth_transaction < auth_data->expected_transaction || auth_transaction > 2))) {
        net_warn("%pM unexpected authentication state: algorithm %d (expected %d) transact %d (expected %d)\n",
            mgmt->sa, auth_algorithm, auth_data->algorithm,
            auth_transaction,
            auth_data->expected_transaction);

        return;
    }

    if (status_code != WLAN_STATUS_SUCCESS && 
		status_code != WLAN_STATUS_SAE_HASH_TO_ELEMENT) {
        net_warn("%pM denied authentication (status %d)\n",
            mgmt->sa, status_code);
        net80211_sta_sme_rx_mgmt(vif, (u8 *)mgmt, len);
        return;
    }

    if (WLAN_AUTH_MODE_SHARED_KEY == auth_data->algorithm) {
        if (auth_data->expected_transaction != 4) {
            net80211_sta_auth_challenge(vif, mgmt, len);
            /* need another frame */
            return;
        }
    }
    else if (WLAN_AUTH_MODE_SAE == auth_data->algorithm) {
        if (auth_data->expected_transaction != 2) {
            /* need another confirm frame */
            net80211_sta_send_sae_auth_response(vif, auth_data, mgmt, len);
            return;
        }

        net_dbg("SAE confirmed\n");
        net80211_sta_send_sae_auth_response(vif, auth_data, mgmt, len);
    }
    else if (WLAN_AUTH_MODE_OPEN != auth_data->algorithm) {
        WARN(1, "not supported auth algorithm %d", auth_data->algorithm);
        return;
    }

    if ((auth_data->algorithm != WLAN_AUTH_MODE_SAE) ||
        (auth_transaction == 2 &&
            auth_data->expected_transaction == 2)) {
        if (!net80211_sta_mark_sta_auth(vif, bssid))
            return; /* ignore frame -- wait for timeout */
    }

    net80211_sta_sme_rx_mgmt(vif, (u8 *)mgmt, len);
}

static void
net80211_sta_set_disassoc(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    const u8 *bssid = net80211_vif_get_bssid(vif);

    net_dbg("associated 0x%p\n", mlme_conf->associated);

    if (!mlme_conf->associated) {
        /* clean up when not associated */
        net80211_vif_destroy_sta(vif, bssid);
        net80211_vif_bss_conf_set_bssid(vif, NULL);
        net80211_vif_bss_conf_change_notify(vif);
        mlme_conf->flags = 0;
        net80211_vif_release_channel(vif);
        return;
    }

    net80211_put_bss(pdev, mlme_conf->associated);
    mlme_conf->associated = NULL;
    
    net80211_vif_reset_ap_power_level(vif);
    net80211_vif_recalc_powersave(vif);

    /* delete PTK/GTK key before remove peers */
    net80211_vif_del_key(vif, bssid);

    /* clear bssid only after building the needed mgmt frames */
    net80211_vif_bss_conf_set_bssid(vif, NULL);

    /* remove peers */
    net80211_vif_flush_stations(vif);

    /* finally reset all BSS / config parameters */
    net80211_vif_bss_conf_set_erp_cts_prot(vif, false);
    net80211_vif_bss_conf_set_erp_short_preamble(vif, false);
    net80211_vif_bss_conf_set_erp_short_slot(vif, false);

    net80211_vif_bss_conf_set_assoc(vif, false);

    /* on the next assoc, re-program HT/VHT parameters */
    memset(&mlme_conf->ht_capa, 0, sizeof(mlme_conf->ht_capa));
    memset(&mlme_conf->ht_capa_mask, 0, sizeof(mlme_conf->ht_capa_mask));
    memset(&mlme_conf->vht_capa, 0, sizeof(mlme_conf->vht_capa));
    memset(&mlme_conf->vht_capa_mask, 0, sizeof(mlme_conf->vht_capa_mask));

    // TODOTODO: reset MU-MIMO ownership and group data

    // TODOTODO: Disable ARP filtering */

    net80211_vif_bss_conf_set_qos(vif, false);

    net80211_vif_bss_conf_change_notify(vif);

    /* disassociated - set to defaults now */
    net80211_vif_set_wmm_default(vif, false, false);

    net80211_vif_bss_conf_set_dtim_period(vif, 0);
    net80211_vif_bss_conf_set_beacon_rate(vif, 0);

    mlme_conf->flags = 0;
    net80211_vif_release_channel(vif);
}


static void
net80211_sta_rx_mgmt_deauth(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, u32 len)
{
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct net80211_assoc_data *assoc_data;

    u16 reason_code;
    const u8 *bssid;

    /* corrupted deauth frame */
    if (len < 24 + 2)
        return;

    reason_code = le16_to_cpu(mgmt->u.deauth.reason_code);

    DEBUG_PARAMETER(reason_code);
    DEBUG_PARAMETER(bssid);

    if (mlme_conf->associated &&
        ether_addr_equal(mgmt->bssid, mlme_conf->associated->bssid)) {
        bssid = mlme_conf->associated->bssid;

        DEBUG_PARAMETER(bssid);
        net_dbg("deauthenticated from %pM (Reason: %u=%a)\n",
            bssid, reason_code,
            ieee80211_get_reason_code_string(reason_code));

        net80211_sta_set_disassoc(vif);

        net80211_sta_sme_rx_mgmt(vif, (u8 *)mgmt, len);
        return;
    }

    assoc_data = net80211_sta_get_assoc_data(vif);
    if (assoc_data &&
        ether_addr_equal(mgmt->bssid, assoc_data->bss->bssid)) {
        bssid = assoc_data->bss->bssid;

        net_dbg("deauthenticated from %pM while associating (Reason: %u=%a)\n",
            bssid, reason_code,
            ieee80211_get_reason_code_string(reason_code));
        net80211_sta_sme_rx_mgmt(vif, (u8 *)mgmt, len);
        return;
    }
}

static void
net80211_sta_rx_mgmt_disassoc(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, u32 len)
{
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    u16 reason_code;

    DEBUG_PARAMETER(reason_code);

    if (len < 24 + 2)
        return;

    if (!mlme_conf->associated ||
        !ether_addr_equal(mgmt->bssid, mlme_conf->associated->bssid))
        return;

    reason_code = le16_to_cpu(mgmt->u.disassoc.reason_code);

    net_dbg("disassociated from %pM (Reason: %u=%a)\n",
        mgmt->sa, reason_code,
        ieee80211_get_reason_code_string(reason_code));

    net80211_sta_set_disassoc(vif);
    net80211_sta_sme_rx_mgmt(vif, (u8 *)mgmt, len);
}

static void
net80211_sta_update_erp_info(struct net80211_vif *vif,
    u16 capab, bool erp_valid, u8 erp)
{
    const struct ieee80211_supported_band *sband;
    bool use_protection;
    bool use_short_preamble;
    bool use_short_slot;

    sband = net80211_vif_get_sband(vif);
    if (!sband)
        return;

    if (erp_valid) {
        use_protection = (erp & WLAN_ERP_USE_PROTECTION) != 0;
        use_short_preamble = (erp & WLAN_ERP_BARKER_PREAMBLE) == 0;
    }
    else {
        use_protection = false;
        use_short_preamble = !!(capab & WLAN_CAPABILITY_SHORT_PREAMBLE);
    }

    use_short_slot = !!(capab & WLAN_CAPABILITY_SHORT_SLOT_TIME);
    if (sband->band == NL80211_BAND_5GHZ || sband->band == NL80211_BAND_6GHZ)
        use_short_slot = true;

    net80211_vif_bss_conf_set_erp_cts_prot(vif, use_protection);
    net80211_vif_bss_conf_set_erp_short_preamble(vif, use_short_preamble);
    net80211_vif_bss_conf_set_erp_short_slot(vif, use_short_slot);
}

static void
net80211_sta_set_associated(struct net80211_vif *vif,
    struct net80211_bss *bss)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);

    u8 dtim_count, dtim_period;

    net80211_sta_update_erp_info(vif,
        net80211_vif_bss_conf_get_assoc_capability(vif), 
        bss->data.erp_valid, bss->data.erp_value);

    mlme_conf->associated = net80211_ref_bss(pdev, bss);

    // TODOTODO: Review the code for rate?

    mlme_conf->flags |= NET80211_MLME_RESET_SIGNAL_AVE;

    if (net80211_bss_get_dtim(bss, &dtim_count, &dtim_period)) {
        net80211_vif_bss_conf_set_dtim_period(vif, dtim_period);
        net80211_vif_bss_conf_set_beacon_rate(vif, bss->data.beacon_rate);
    }

    net80211_vif_bss_conf_set_assoc(vif, true);
    net80211_vif_bss_conf_change_notify(vif);

    net80211_vif_recalc_smps(vif);
    net80211_vif_recalc_powersave(vif);
}

static bool
net80211_sta_assoc_success(struct net80211_vif *vif,
    struct net80211_bss *bss,
    struct ieee80211_mgmt *mgmt, size_t len,
    struct ieee802_11_elems *elems)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_assoc_data *assoc_data = net80211_sta_get_assoc_data(vif);
	bool is_6ghz = bss->channel->band == NL80211_BAND_6GHZ;
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct net80211_sta *sta;
    const struct ieee80211_supported_band *sband;
    u16 capab_info, aid;
    struct net80211_bss_ies *bss_ies = NULL;
    int err;
    bool ret;

    /* AssocResp and ReassocResp have identical structure */

    aid = le16_to_cpu(mgmt->u.assoc_resp.aid);
    capab_info = le16_to_cpu(mgmt->u.assoc_resp.capab_info);

    /* The 5 MSB of the AID field are reserved */
    aid &= 0x7ff;

    if (!elems->supp_rates) {
        net_warn("no SuppRates element in AssocResp\n");
        return false;
    }

    /*
     * Some APs are erroneously not including some information in their
     * (re)association response frames. Try to recover by using the data
     * from the beacon or probe response. 
     */
    if (!is_6ghz &&
		((assoc_data->wmm && !elems->wmm_param) ||
         (!(mlme_conf->flags & NET80211_MLME_DISABLE_HT) &&
         (!elems->ht_capabilities || !elems->ht_operation)) ||
         (!(mlme_conf->flags & NET80211_MLME_DISABLE_VHT) &&
         (!elems->vht_capabilities || !elems->vht_operation)))) {
        const struct net80211_bss_ies *ies;
        struct ieee802_11_elems bss_elems;
        ies = bss->ies;
        if (ies)
            bss_ies = kmemdup(ies, sizeof(*ies) + ies->len, GFP_ATOMIC);
        if (!bss_ies)
            return false;

        ieee802_11_parse_elems(bss_ies->data, bss_ies->len,
             &bss_elems);
        if (assoc_data->wmm &&
            !elems->wmm_param && bss_elems.wmm_param) {
            elems->wmm_param = bss_elems.wmm_param;
            net_warn("AP bug: WMM param missing from AssocResp\n");
        }

        /*
         * Also check if we requested HT/VHT, otherwise the AP doesn't
         * have to include the IEs in the (re)association response.
         */
        if (!elems->ht_capabilities && bss_elems.ht_capabilities &&
            !(mlme_conf->flags & NET80211_MLME_DISABLE_HT)) {
            elems->ht_capabilities = bss_elems.ht_capabilities;
            net_warn("AP bug: HT capability missing from AssocResp\n");
        }
        if (!elems->ht_operation && bss_elems.ht_operation &&
            !(mlme_conf->flags & NET80211_MLME_DISABLE_HT)) {
            elems->ht_operation = bss_elems.ht_operation;
            net_warn("AP bug: HT operation missing from AssocResp\n");
        }
        if (!elems->vht_capabilities && bss_elems.vht_capabilities &&
            !(mlme_conf->flags & NET80211_MLME_DISABLE_VHT)) {
            elems->vht_capabilities = bss_elems.vht_capabilities;
            net_dbg("AP bug: VHT capa missing from AssocResp\n");
        }
        if (!elems->vht_operation && bss_elems.vht_operation &&
            !(mlme_conf->flags & NET80211_MLME_DISABLE_VHT)) {
            elems->vht_operation = bss_elems.vht_operation;
            net_warn("AP bug: VHT operation missing from AssocResp\n");
        }
    }

    if (!is_6ghz && !(mlme_conf->flags & NET80211_MLME_DISABLE_HT) &&
        (!elems->wmm_param || !elems->ht_capabilities || !elems->ht_operation)) {
        net_warn("HT AP is missing WMM params or HT capability/operation\n");
        ret = false;
        goto out;
    }

    if (!is_6ghz && !(mlme_conf->flags & NET80211_MLME_DISABLE_VHT) &&
        (!elems->vht_capabilities || !elems->vht_operation)) {
        net_warn("VHT AP is missing VHT capability/operation\n");
        ret = false;
        goto out;
    }

	if (is_6ghz && !(mlme_conf->flags & NET80211_MLME_DISABLE_HE) &&
	    !elems->he_6ghz_cap) {
		net_warn("HE 6 GHz AP is missing HE 6 GHz band capability\n");
		ret = false;
		goto out;
	}

    /* station info should exists already */
    sta = net80211_vif_get_sta(vif, bss->bssid);
    if (WARN_ON(!sta)) {
        ret = false;
        goto out;
    }

    sband = net80211_vif_get_sband(vif);
    if (!sband) {
        ret = false;
        goto out;
    }

    if (!(mlme_conf->flags & NET80211_MLME_DISABLE_HE) &&
        (!elems->he_cap || !elems->he_operation)) {
        net_warn("HE AP is missing HE capability/operation\n");
        ret = false;
        goto out;
    }

    /* Set up internal HT/VHT capabilities */
    if (elems->ht_capabilities && !(mlme_conf->flags & NET80211_MLME_DISABLE_HT))
        net80211_vif_ht_cap_to_sta_ht_cap(vif, sband,
            elems->ht_capabilities, sta);

    if (elems->vht_capabilities && !(mlme_conf->flags & NET80211_MLME_DISABLE_VHT))
        net80211_vif_vht_cap_to_sta_vht_cap(vif, sband,
            elems->vht_capabilities, sta);

    if (elems->he_operation && !(mlme_conf->flags & NET80211_MLME_DISABLE_HE) &&
        elems->he_cap) {
        net80211_vif_he_cap_ie_to_sta_he_cap(vif, sband,
            elems->he_cap,
            elems->he_cap_len,
            (void *)elems->he_6ghz_cap,
            sta);

        net80211_vif_bss_conf_set_he_support(vif, sta->he_cap.he_supported);
#if 0
        changed |= ieee80211_recalc_twt_req(sdata, sta, elems);
#endif
    }
    else {
        net80211_vif_bss_conf_set_he_support(vif, false);
        net80211_vif_bss_conf_set_twt_requester(vif, false);
    }

    if (net80211_vif_bss_conf_get_he_support(vif)) {
        net80211_vif_bss_conf_set_he_bss_color(vif, elems->he_operation->he_operation_params);
        
        /* TODOTODO: To review if it is need for HE?
        net80211_vif_bss_conf_set_he_htc_trig_based_pkt_ext(vif, elems->he_operation->he_operation_params);
        net80211_vif_bss_conf_set_he_frame_time_rts_th(vif, elems->he_operation->he_operation_params);
        net80211_vif_bss_conf_set_he_multi_sta_back(vif, elems->he_operation->he_operation_params);
        net80211_vif_bss_conf_set_he_ack_enabled(vif, elems->he_operation->he_operation_params);
        net80211_vif_bss_conf_set_he_uora_exists(vif, elems);
        */

        net80211_vif_he_op_ie_to_bss_conf(vif, elems->he_operation);
        net80211_vif_he_spr_ie_to_bss_conf(vif, elems->he_spr);
	}

    // TODOTODO: MBSSID Support

    if (elems->opmode_notif &&
        !(*elems->opmode_notif & IEEE80211_OPMODE_RX_NSS_TYPE_BF)) {
        u8 nss;

        nss = *elems->opmode_notif & IEEE80211_OPMODE_RX_NSS_MASK;
        nss >>= IEEE80211_OPMODE_RX_NSS_SHIFT;
        nss += 1;
        sta->rx_nss = nss;
    }

    net80211_sta_update_rx_nss(sta);

    sta->mfp = !!(mlme_conf->flags & NET80211_MLME_MFP_ENABLED);

    sta->wme = elems->wmm_param && 
        (net80211_get_hw_queues(pdev) >= IEEE80211_NUM_OF_ACS);

    err = net80211_sta_move_state(sta, IEEE80211_STA_ASSOC);
    if (!err && !(mlme_conf->flags & NET80211_MLME_CONTROL_PORT))
        err = net80211_sta_move_state(sta, IEEE80211_STA_AUTHORIZED);
    if (err) {
        net_warn("failed to move station %pM to desired state\n",
            sta->addr);
        WARN_ON(net80211_sta_destroy(sta));
        ret = false;
        goto out;
    }

    /* Always update WMM once after association */
    mlme_conf->wmm_param_last_set = -1;
    mlme_conf->mu_edca_param_last_set = -1;

    if (mlme_conf->flags & NET80211_MLME_DISABLE_WMM) {
        net80211_vif_set_wmm_default(vif, false, false);
    }
    else if (!net80211_vif_set_wmm_params(vif, elems->wmm_param,
        elems->wmm_param_len,
        elems->mu_edca_param_set)) {
        /* still enable QoS since we might have HT/VHT */
        net80211_vif_set_wmm_default(vif, false, true);
        mlme_conf->flags |= NET80211_MLME_DISABLE_WMM;
    }

    if (elems->bss_max_idle_period) {
        net80211_vif_bss_conf_set_max_idle_period(vif,
            le16_to_cpu(elems->bss_max_idle_period->max_idle_period));
        net80211_vif_bss_conf_set_protected_keep_alive(vif, 
            !!(elems->bss_max_idle_period->idle_options & WLAN_IDLE_OPTIONS_PROTECTED_KEEP_ALIVE));
    }
    else {
        net80211_vif_bss_conf_set_max_idle_period(vif, 0);
        net80211_vif_bss_conf_set_protected_keep_alive(vif, false);
    }

    /* set aid and assoc capability */
    net80211_vif_bss_conf_set_aid(vif, aid);
    net80211_vif_bss_conf_set_assoc_capability(vif, capab_info);

    /* set the remaining bss conf and notify */
    net80211_sta_set_associated(vif, bss);

    // TODOTODO: Do we need the connection monitor?

    ret = true;
out:
    kfree(bss_ies);
    return ret;
}

static void
net80211_sta_rx_mgmt_assoc_resp(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, u32 len)
{
    struct net80211_assoc_data *assoc_data = net80211_sta_get_assoc_data(vif);
    u16 capab_info, status_code, aid;
    struct ieee802_11_elems elems;
    u8 *pos;
    bool reassoc;
    struct net80211_bss *bss;

    DEBUG_PARAMETER(capab_info);
    DEBUG_PARAMETER(aid);
    DEBUG_PARAMETER(reassoc);

    if (!assoc_data)
        return;

    /* corrupted assoc response */
    if (len < 24 + 6)
        return;

    bss = assoc_data->bss;
    if (!ether_addr_equal(mgmt->bssid, bss->bssid)) {
        net_warn("unexpected assoc response received\n");
        return;
    }

    reassoc = ieee80211_is_reassoc_resp(mgmt->frame_control);
    capab_info = le16_to_cpu(mgmt->u.assoc_resp.capab_info);
    status_code = le16_to_cpu(mgmt->u.assoc_resp.status_code);
    aid = le16_to_cpu(mgmt->u.assoc_resp.aid);

    net_dbg("RX %assocResp from %pM (capab=0x%x status=%d aid=%d)\n",
        reassoc ? "Rea" : "A", mgmt->sa,
        capab_info, status_code, (u16)(aid & ~(BIT(15) | BIT(14))));

    pos = mgmt->u.assoc_resp.variable;
    ieee802_11_parse_elems(pos, len - (pos - (u8 *)mgmt), &elems);

    if (status_code == WLAN_STATUS_ASSOC_REJECTED_TEMPORARILY &&
        elems.timeout_int &&
        elems.timeout_int->type == WLAN_TIMEOUT_ASSOC_COMEBACK) {
        u32 tu, ms;
        tu = le32_to_cpu(elems.timeout_int->value);
        ms = tu * 1024 / 1000;
        net_warn("%pM rejected association temporarily; comeback duration %u TU (%u ms)\n",
            mgmt->sa, tu, ms);
        if (ms > NET80211_ASSOC_TIMEOUT)
            queue_delayed_work(&assoc_data->run_again, ms);
        return;
    }

    if (status_code != WLAN_STATUS_SUCCESS) {
        net_warn("%pM denied association (code=%d)\n",
            mgmt->sa, status_code);
        net80211_sta_sme_rx_assoc_resp(vif, status_code, true);
    }
    else {
        if (!net80211_sta_assoc_success(vif, bss, mgmt, len, &elems)) {
            /* internal error */
            net80211_sta_sme_rx_assoc_resp(vif, status_code, true);
            return;
        }
        net_warn("associated\n");
        net80211_sta_sme_rx_assoc_resp(vif, status_code, false);
    }
}

void
net80211_sta_rx_mgmt(
    struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, u32 len, 
    struct ieee80211_rx_status *rx_status)
{
    u8 fc0 = (u8)le16_to_cpu(mgmt->frame_control);

    switch (fc0 & IEEE80211_FC0_SUBTYPE_MASK) {
    case IEEE80211_FC0_SUBTYPE_BEACON:
        net80211_sta_rx_mgmt_beacon(vif, mgmt, len, rx_status);
        break;
    case IEEE80211_FC0_SUBTYPE_PROBE_RESP:
        net80211_sta_rx_mgmt_probe_resp(vif, mgmt, len, rx_status);
        break;
    case IEEE80211_FC0_SUBTYPE_AUTH:
        net80211_sta_rx_mgmt_auth(vif, mgmt, len);
        break;
    case IEEE80211_FC0_SUBTYPE_DEAUTH:
        net80211_sta_rx_mgmt_deauth(vif, mgmt, len);
        break;
    case IEEE80211_FC0_SUBTYPE_DISASSOC:
        net80211_sta_rx_mgmt_disassoc(vif, mgmt, len);
        break;
    case IEEE80211_FC0_SUBTYPE_ASSOC_RESP:
    case IEEE80211_FC0_SUBTYPE_REASSOC_RESP:
        net80211_sta_rx_mgmt_assoc_resp(vif, mgmt, len);
        break;
    case IEEE80211_FC0_SUBTYPE_ACTION:
        net_warn("action category %u not handled\n", mgmt->u.action.category);
        break;
    }
}

static u32
net80211_determine_chantype(struct net80211_vif *vif,
    const struct ieee80211_supported_band *sband,
    struct ieee80211_channel *channel,
    const struct ieee80211_ht_operation *htop,
    const struct ieee80211_vht_operation *vhtop,
    const struct ieee80211_he_operation *heop,
    struct ieee80211_chan_def *chandef, bool tracking)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct ieee80211_chan_def vht_chandef;
    struct ieee80211_sta_ht_cap sta_ht_cap;
    u32 ht_cfreq;
    u32 ret;

    net_dbg("sband=0x%p, channel=%u, htop=0x%p, vhtop=0x%p, "
        "heop=0x%p, chandef=0x%p, tracking=%u\n",
        sband, channel ? channel->center_freq : 0,
        htop, vhtop, heop, chandef, tracking);

    memset(chandef, 0, sizeof(struct ieee80211_chan_def));
    chandef->chan = channel;
    chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
    chandef->center_freq1 = channel->center_freq;
    chandef->freq1_offset = channel->freq_offset;

	if (channel->band == NL80211_BAND_6GHZ) {
		if (!net80211_chandef_he_6ghz_oper(vif, heop, chandef)) {
			ret = NET80211_MLME_DISABLE_HT |
		      	  NET80211_MLME_DISABLE_VHT |
		      	  NET80211_MLME_DISABLE_HE;
		}
        else {
            ret = 0;
        }
		vht_chandef = *chandef;
		goto out;
	}

	memcpy(&sta_ht_cap, &sband->ht_cap, sizeof(sta_ht_cap));
	net80211_vif_apply_htcap_overrides(vif, &sta_ht_cap);

	if (!htop || !sta_ht_cap.ht_supported) {
		ret = NET80211_MLME_DISABLE_HT |
		      NET80211_MLME_DISABLE_VHT |
		      NET80211_MLME_DISABLE_HE;
		goto out;
	}

    chandef->width = NL80211_CHAN_WIDTH_20;

    ht_cfreq = ieee80211_channel_to_frequency(htop->primary_chan,
        channel->band);
    /* check that channel matches the right operating channel */
    if (!tracking && channel->center_freq != ht_cfreq) {
        net_warn("Wrong control channel: center-freq: %d ht-cfreq: %d ht->primary_chan: %d band: %d - Disabling HT\n",
            channel->center_freq, ht_cfreq,
            htop->primary_chan, channel->band);
        ret = NET80211_MLME_DISABLE_HT |
            NET80211_MLME_DISABLE_VHT |
            NET80211_MLME_DISABLE_HE;
        goto out;
    }

    /* check 40 MHz support, if we have it */
    if (sta_ht_cap.cap & IEEE80211_HTCAP_SUP_WIDTH_20_40) {
        ieee80211_chandef_ht_operation(htop, chandef);
    }
    else {
        /* 40 MHz (and 80 MHz) must be supported for VHT */
        ret = NET80211_MLME_DISABLE_VHT;
        /* also mark 40 MHz disabled */
        ret |= NET80211_MLME_DISABLE_40MHZ;
        goto out;
    }

    if (!vhtop || !sband->vht_cap.vht_supported) {
        ret = NET80211_MLME_DISABLE_VHT;
        goto out;
    }

    vht_chandef = *chandef;
    if (!(mlme_conf->flags & NET80211_MLME_DISABLE_HE) && heop &&
        (le32_to_cpu(heop->he_operation_params) &
            IEEE80211_HEOP_VHT_OPER_INFO)) {
        struct ieee80211_vht_operation heop_vhtop = { 0 };

        /* only copy first 3 bytes */
        memcpy(&heop_vhtop, heop->optional, 3);
        heop_vhtop.basic_mcs_set = cpu_to_le16(0);

        if (!ieee80211_chandef_vht_operation(sband,
            &heop_vhtop, htop,
            net80211_hw_check(pdev, IEEE80211_HW_SUPPORTS_VHT_EXT_NSS_BW),
            &vht_chandef)) {
            if (!(mlme_conf->flags & NET80211_MLME_DISABLE_HE))
                net_dbg("HE AP VHT information is invalid, disable HE\n");
            ret = NET80211_MLME_DISABLE_HE;
            goto out;
        }
    }
    else if (!ieee80211_chandef_vht_operation(sband, 
        vhtop, htop,
        net80211_hw_check(pdev, IEEE80211_HW_SUPPORTS_VHT_EXT_NSS_BW),
        &vht_chandef)) {
        if (!(mlme_conf->flags & NET80211_MLME_DISABLE_VHT))
            net_dbg("AP VHT information is invalid, disable VHT\n");
        ret = NET80211_MLME_DISABLE_VHT;
        goto out;
    }

    if (!ieee80211_chandef_valid(&vht_chandef)) {
        if (!(mlme_conf->flags & NET80211_MLME_DISABLE_VHT))
            net_dbg("AP VHT information is invalid, disable VHT\n");
        ret = NET80211_MLME_DISABLE_VHT;
        goto out;
    }

    if (ieee80211_chandef_identical(chandef, &vht_chandef)) {
        ret = 0;
        goto out;
    }

    if (!ieee80211_chandef_compatible(chandef, &vht_chandef)) {
        if (!(mlme_conf->flags & NET80211_MLME_DISABLE_VHT))
            net_dbg("AP VHT information doesn't match HT, disable VHT\n");
        ret = NET80211_MLME_DISABLE_VHT;
        goto out;
    }

    *chandef = vht_chandef;

    ret = 0;

out:
    if (tracking &&
        ieee80211_chandef_identical(chandef, net80211_vif_bss_conf_get_chandef(vif)))
        return ret;

    /* don't print the message below for VHT mismatch if VHT is disabled */
    if (ret & NET80211_MLME_DISABLE_VHT)
        vht_chandef = *chandef;

    while (!net80211_chandef_usable(pdev, chandef, 
        tracking ? 0 : IEEE80211_CHAN_DISABLED)) {
        if (WARN_ON(chandef->width == NL80211_CHAN_WIDTH_20_NOHT)) {
            ret = NET80211_MLME_DISABLE_HT |
                NET80211_MLME_DISABLE_VHT |
                NET80211_MLME_DISABLE_HE;
            break;
        }

        ret |= ieee80211_chandef_downgrade(chandef);
    }

    if (!heop || !net80211_chandef_usable(pdev, chandef,
        IEEE80211_CHAN_NO_HE))
        ret |= NET80211_MLME_DISABLE_HE;

    if (chandef->width != vht_chandef.width && !tracking)
        net_dbg("capabilities/regulatory prevented using AP HT/VHT configuration, downgraded\n");

    WARN_ON_ONCE(!ieee80211_chandef_valid(chandef));
    return ret;
}

static int
net80211_prep_channel(struct net80211_vif *vif,
    struct net80211_bss *bss)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);

    const struct ieee80211_ht_capabilities *ht_cap = NULL;
    const struct ieee80211_ht_operation *ht_operation = NULL;
    const struct ieee80211_vht_capabilities *vht_cap = NULL;
    const struct ieee80211_vht_operation *vht_operation = NULL;
    const struct ieee80211_he_operation *he_operation = NULL;
    const struct ieee80211_supported_band *sband;
	bool is_6ghz = bss->channel->band == NL80211_BAND_6GHZ;
	bool is_5ghz = bss->channel->band == NL80211_BAND_5GHZ;
    struct ieee80211_chan_def chandef;
    int ret;

    net_dbg("vif=0x%p, bss=0x%p\n", vif, bss);

    sband = net80211_get_sband(pdev, bss->channel->band);
	if (sband == NULL)
		return -EINVAL;

    mlme_conf->flags &= ~NET80211_MLME_DISABLE_40MHZ;
    mlme_conf->flags &= ~NET80211_MLME_DISABLE_80P80MHZ;
    mlme_conf->flags &= ~NET80211_MLME_DISABLE_160MHZ;

    if (!sband->ht_cap.ht_supported && !is_6ghz) {
        mlme_conf->flags |= NET80211_MLME_DISABLE_HT;
        mlme_conf->flags |= NET80211_MLME_DISABLE_VHT;
        mlme_conf->flags |= NET80211_MLME_DISABLE_HE;
    }

    if (!sband->vht_cap.vht_supported && is_5ghz) {
		mlme_conf->flags |= NET80211_MLME_DISABLE_VHT;
		mlme_conf->flags |= NET80211_MLME_DISABLE_HE;
	}
	
    if (!ieee80211_get_sta_he_cap(sband))
        mlme_conf->flags |= NET80211_MLME_DISABLE_HE;

    net_dbg("ht_supported %u, vht_supported %u, he_sta_cap %u\n",
        sband->ht_cap.ht_supported, sband->vht_cap.vht_supported,
        ieee80211_get_sta_he_cap(sband));

    if (!(mlme_conf->flags & NET80211_MLME_DISABLE_HT) && !is_6ghz) {
        const u8 *ht_operation_ie, *ht_cap_ie;

        ht_operation_ie = net80211_bss_find_ie(bss, WLAN_EID_HT_OPERATION);
        if (ht_operation_ie && ht_operation_ie[1] >= sizeof(*ht_operation))
            ht_operation = (void *)(ht_operation_ie + 2);

        ht_cap_ie = net80211_bss_find_ie(bss, WLAN_EID_HT_CAP);
        if (ht_cap_ie && ht_cap_ie[1] >= sizeof(*ht_cap))
            ht_cap = (void *)(ht_cap_ie + 2);

        if (!ht_cap) {
            mlme_conf->flags |= NET80211_MLME_DISABLE_HT;
            ht_operation = NULL;
        }
    }

    if (!(mlme_conf->flags & NET80211_MLME_DISABLE_VHT) && !is_6ghz) {
        const u8 *vht_operation_ie, *vht_cap_ie;

        vht_operation_ie = net80211_bss_find_ie(bss, WLAN_EID_VHT_OPERATION);
        if (vht_operation_ie && vht_operation_ie[1] >= sizeof(*vht_operation))
            vht_operation = (void *)(vht_operation_ie + 2);
        if (vht_operation && !ht_operation) {
            vht_operation = NULL;
            net_dbg("Disabling HT/VHT/HE as AP advertised VHT without HT\n");
            mlme_conf->flags |= NET80211_MLME_DISABLE_HT;
            mlme_conf->flags |= NET80211_MLME_DISABLE_VHT;
            mlme_conf->flags |= NET80211_MLME_DISABLE_HE;
        }

        vht_cap_ie = net80211_bss_find_ie(bss, WLAN_EID_VHT_CAP);
        if (vht_cap_ie && vht_cap_ie[1] >= sizeof(*vht_cap))
            vht_cap = (void *)(void *)(vht_cap_ie + 2);

        if (!vht_cap) {
            mlme_conf->flags |= NET80211_MLME_DISABLE_VHT;
            vht_operation = NULL;
        }
    }

    if (!(mlme_conf->flags & NET80211_MLME_DISABLE_HE)) {
        const u8 *he_operation_ie;
        he_operation_ie = net80211_bss_find_extension_ie(bss, WLAN_EID_EXT_HE_OPERATION);
        if (he_operation_ie &&
            he_operation_ie[1] == ieee80211_he_operation_size(&he_operation_ie[3]))
            he_operation = (void *)(he_operation_ie + 3);
        else
            he_operation = NULL;

        if (!net80211_verify_sta_he_mcs_support(sband, he_operation))
            mlme_conf->flags |= NET80211_MLME_DISABLE_HE;
    }

    mlme_conf->flags |= net80211_determine_chantype(vif, sband,
        bss->channel,
        ht_operation, vht_operation, he_operation,
        &chandef, false);

    net_dbg("ifmgd->flags=0x%x\n", mlme_conf->flags);

    vif->needed_rx_chains = ieee80211_get_rx_chains(sband, ht_cap, vht_cap);
    vif->smps_mode = IEEE80211_SMPS_NONE;

    ret = net80211_vif_use_channel(vif, &chandef);

    if (chandef.width == NL80211_CHAN_WIDTH_5 ||
        chandef.width == NL80211_CHAN_WIDTH_10) {
        goto out;
    }

    while (ret && chandef.width != NL80211_CHAN_WIDTH_20_NOHT) {
        mlme_conf->flags |= ieee80211_chandef_downgrade(&chandef);
        ret = net80211_vif_use_channel(vif, &chandef);
    }
out:
    return ret;
}

int net80211_prep_connection(struct net80211_vif *vif,
    struct net80211_bss *bss, bool assoc,
    bool foverride)
{
    struct net80211_pdev *pdev = vif->pdev;
    const struct ieee80211_supported_band *sband;
    struct net80211_sta *new_sta = NULL;
    bool have_sta = false;
    int err;

    if (!bss->channel || bss->channel->band >= NUM_NL80211_BANDS)
		return -EINVAL;
	
    sband = net80211_get_sband(pdev, bss->channel->band);
	if (sband == NULL)
		return -EINVAL;

    if (assoc) {
        have_sta = (net80211_vif_get_sta(vif, bss->bssid) != NULL);
    }

    if (!have_sta) {
        new_sta = net80211_sta_alloc(vif, bss->bssid);
        if (!new_sta)
            return -ENOMEM;
    }

    if (new_sta) {
        u32 rates = 0;
        u32 basic_rates = 0;
        bool have_rate_higher_than_11mbit;
        int shift = net80211_vif_get_channel_shift(vif);

        ieee80211_get_rates(sband, bss->data.supp_rates,
            bss->data.supp_rates_len, shift,
            &rates, &basic_rates,
            &have_rate_higher_than_11mbit);

        if (rates)
            new_sta->supp_rates[bss->channel->band] = rates;
        else
            net_warn("No rates found, keeping mandatory only\n");

        vif->only_g_mode = (bss->channel->band == NL80211_BAND_2GHZ &&
            have_rate_higher_than_11mbit);

        net80211_vif_bss_conf_set_basic_rates(vif, basic_rates);
        net80211_vif_bss_conf_set_bssid(vif, bss->bssid);
        net80211_vif_bss_conf_set_beacon_interval(vif, bss->beacon_interval);
    }

    net_dbg("new_sta=0x%p\n", new_sta);

    if (new_sta || foverride) {
        err = net80211_prep_channel(vif, bss);
        if (err) {
            if (new_sta)
                net80211_sta_free(new_sta);
            return -EINVAL;
        }
    }

    if (new_sta) {
        net80211_vif_bss_conf_change_notify(vif);

        if (assoc)
            net80211_sta_move_state(new_sta, IEEE80211_STA_AUTH);

        err = net80211_sta_add(new_sta);
        new_sta = NULL;
        if (err) {
            net_err("failed to insert STA entry for the AP: %d\n", err);
            return err;
        }
    }
    else {
        WARN_ON_ONCE(!ether_addr_equal(net80211_vif_get_bssid(vif), bss->bssid));
    }
    return 0;
}

/* auth */

static void
net80211_sta_send_auth_complete(struct sk_buff *skb,
    void *arg, bool acked)
{
    struct net80211_vif *vif = arg;
    struct net80211_auth_data *auth_data = net80211_sta_get_auth_data(vif);

    if (auth_data && !acked) {
        queue_delayed_work(&auth_data->run_again, 0);
    }
}

static void
net80211_sta_send_auth(
    struct net80211_vif *vif,
    u16 transaction, u16 auth_algorithm, u16 status,
    const u8 *extra, u32 extra_len, const u8 *da,
    const u8 *bssid, const u8 *key, u8 key_len, u8 key_idx,
    u32 tx_flags,
    ieee80211_tx_complete_handler tx_complete_handler,
    void *tx_complete_arg)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct sk_buff *skb;
    struct ieee80211_mgmt *mgmt;

    /* 24 + 6 = header + auth_algo + auth_transaction + status_code */
    skb = dev_alloc_skb(pdev->dev, IEEE80211_WEP_IV_LENGTH +
        24 + 6 + extra_len + IEEE80211_WEP_ICV_LENGTH);
    if (!skb)
        return;

    skb_reserve(skb, IEEE80211_WEP_IV_LENGTH);

    mgmt = skb_put_zero(skb, 24 + 6);
	if (!mgmt)
		return;
	
    mgmt->frame_control = IEEE80211_FC_TYPE(IEEE80211_FC0_TYPE_MGT, IEEE80211_FC0_SUBTYPE_AUTH);
    memcpy(mgmt->da, da, ETH_ALEN);
    memcpy(mgmt->sa, net80211_vif_addr(vif), ETH_ALEN);
    memcpy(mgmt->bssid, bssid, ETH_ALEN);
    mgmt->u.auth.auth_algorithm = cpu_to_le16(auth_algorithm);
    mgmt->u.auth.auth_transaction = cpu_to_le16(transaction);
    mgmt->u.auth.status_code = cpu_to_le16(status);
    if (extra)
        skb_put_data(skb, extra, extra_len);

    net_dbg("da %02X:%02X:%02X:%02X:%02X:%02X, sa %02X:%02X:%02X:%02X:%02X:%02X\n",
        mgmt->da[0], mgmt->da[1], mgmt->da[2],
        mgmt->da[3], mgmt->da[4], mgmt->da[5],
        mgmt->sa[0], mgmt->sa[1], mgmt->sa[2],
        mgmt->sa[3], mgmt->sa[4], mgmt->sa[5]);

    // TODOTODO: To support the WEP?

    IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTERNAL_DONT_ENCRYPT |
        tx_flags;
    IEEE80211_SKB_CB(skb)->tx_complete_handler = tx_complete_handler;
    IEEE80211_SKB_CB(skb)->tx_complete_arg = tx_complete_arg;

    net80211_tx_skb(vif, skb);
}

static void
net80211_sta_send_auth_frame(
    struct net80211_vif *vif,
    const u8 *buf, u32 buf_len)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct sk_buff* skb;
    struct ieee80211_mgmt* mgmt;

    skb = dev_alloc_skb(pdev->dev, IEEE80211_WEP_IV_LENGTH + buf_len + IEEE80211_WEP_ICV_LENGTH);
    if (!skb)
        return;

    skb_reserve(skb, IEEE80211_WEP_IV_LENGTH);
    mgmt = skb_put_zero(skb, buf_len);
	if (!mgmt)
		return;
	
    memcpy(mgmt, buf, buf_len);
    net_dbg("frame_len %d, da %02X:%02X:%02X:%02X:%02X:%02X, sa %02X:%02X:%02X:%02X:%02X:%02X\n", buf_len,
        mgmt->da[0], mgmt->da[1], mgmt->da[2],
        mgmt->da[3], mgmt->da[4], mgmt->da[5],
        mgmt->sa[0], mgmt->sa[1], mgmt->sa[2],
        mgmt->sa[3], mgmt->sa[4], mgmt->sa[5]);

    net_dbg("auth_algorithm %d, auth_transaction %d, status_code %d\n",
        mgmt->u.auth.auth_algorithm,
        mgmt->u.auth.auth_transaction, mgmt->u.auth.status_code);

    IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTERNAL_DONT_ENCRYPT;
    IEEE80211_SKB_CB(skb)->tx_complete_handler = net80211_sta_send_auth_complete;
    IEEE80211_SKB_CB(skb)->tx_complete_arg = vif;

    net80211_tx_skb(vif, skb);
}

static int
net80211_sta_send_sae_auth_request(
    struct net80211_vif *vif,
    struct net80211_auth_data *auth_data)
{
    struct net80211_auth_frame_desc desc = { 0 };
    struct net80211_auth_request_query query = { 0 };
    const struct ieee80211_mgmt *mgmt = (void *)desc.data;

    /* initialize the query */
    memcpy(query.ctx.bssid, auth_data->bss->bssid, ETH_ALEN);
    memcpy(query.ctx.ssid, auth_data->ssid, sizeof(auth_data->ssid));
    query.ctx.ssid_len = auth_data->ssid_len;
    memcpy(&query.ctx.crypto, &auth_data->crypto, sizeof(auth_data->crypto));
    query.desc = &desc;

    /* send query */
    net80211_sta_sme_external_auth_request(vif, &query);
    if (desc.err) {
        net_err("failed to query external auth request: %d\n", desc.err);
        return desc.err;
    }

    if (!desc.data_len) {
        net_warn("invalid auth request\n");
        return -ENODATA;
    }

    /* send auth frame */
    net80211_sta_send_auth_frame(vif, desc.data, desc.data_len);
    
    /* update the sae status */
    auth_data->expected_transaction = le16_to_cpu(mgmt->u.auth.auth_transaction);
    auth_data->sae_status = le16_to_cpu(mgmt->u.auth.status_code);

    return 0;
}

static int
net80211_sta_send_sae_auth_response(
    struct net80211_vif *vif, 
    struct net80211_auth_data *auth_data,
    const void *data,
    u32 data_len)
{
    struct net80211_auth_frame_desc desc = { 0 };
    struct net80211_auth_response_query query = { 0 };
    struct ieee80211_mgmt *mgmt = (void *)desc.data;

    /* initialize the query */
    query.rx.data = data;
    query.rx.data_len = data_len;
    query.desc = &desc;

    /* send query */
    net80211_sta_sme_external_auth_response(vif, &query);
    if (desc.err) {
        net_err("failed to query external auth response: %d\n", desc.err);
        return desc.err;
    }
    if (!desc.data_len) {
        net_warn("no further auth response\n");
        return 0;
    }

    /* send auth frame */
    net80211_sta_send_auth_frame(vif, desc.data, desc.data_len);

    /* update the sae status */
    auth_data->expected_transaction = le16_to_cpu(mgmt->u.auth.auth_transaction);
    auth_data->sae_status = le16_to_cpu(mgmt->u.auth.status_code);

    return 0;
}

int
net80211_sta_auth_request(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_auth_data *auth_data = net80211_sta_get_auth_data(vif);
    u32 tx_flags = 0;
    u16 transaction = 1;
    u16 status = 0;
    u32 auth_timeout = NET80211_AUTH_TIMEOUT;

    if (WARN_ON_ONCE(!auth_data))
        return -EINVAL;

    auth_data->tries++;
    if (auth_data->tries > NET80211_AUTH_MAX_TRIES) {
        net_dbg("authentication with %02X:%02X:%02X:%02X:%02X:%02X timed out\n", 
            auth_data->bss->bssid[0], auth_data->bss->bssid[1],
            auth_data->bss->bssid[2], auth_data->bss->bssid[3],
            auth_data->bss->bssid[4], auth_data->bss->bssid[5]);
        return -ETIMEDOUT;
    }

    net_dbg("send auth to %02X:%02X:%02X:%02X:%02X:%02X (try %d/%d)\n",
        auth_data->bss->bssid[0], auth_data->bss->bssid[1],
        auth_data->bss->bssid[2], auth_data->bss->bssid[3],
        auth_data->bss->bssid[4], auth_data->bss->bssid[5],
        auth_data->tries, NET80211_AUTH_MAX_TRIES);

    auth_data->expected_transaction = 2;

    if (net80211_hw_check(pdev, IEEE80211_HW_REPORTS_TX_ACK_STATUS))
        tx_flags = IEEE80211_TX_CTL_REQUEST_TX_STATUS | IEEE80211_TX_INTERNAL_MLME_TX;

    if (auth_data->algorithm == WLAN_AUTH_MODE_SAE) {
        /* send external auth request */
        auth_timeout = NET80211_AUTH_TIMEOUT_SAE;
        net80211_sta_send_sae_auth_request(vif, auth_data);
    }
    else {
        net80211_sta_send_auth(vif,
            transaction, auth_data->algorithm, status,
            auth_data->data, auth_data->data_len,
            auth_data->bss->bssid,
            auth_data->bss->bssid, NULL, 0, 0,
            tx_flags, net80211_sta_send_auth_complete, vif);
    }
    
    queue_delayed_work(&auth_data->run_again, auth_timeout);

    return 0;
}

/* assoc */

static void
net80211_add_ht_ie(struct net80211_vif *vif,
    struct sk_buff *skb, u8 bss_ht_param,
    const struct ieee80211_supported_band *sband,
    struct ieee80211_channel *channel,
    enum ieee80211_smps_mode smps)
{
    static const u8 smps_to_ht_cap_map[] = {
        [IEEE80211_SMPS_AUTOMATIC] = WLAN_HTCAP_SM_PS_DISABLED,
        [IEEE80211_SMPS_NONE] = WLAN_HTCAP_SM_PS_DISABLED,
        [IEEE80211_SMPS_STATIC] = WLAN_HTCAP_SM_PS_STATIC,
        [IEEE80211_SMPS_DYNAMIC] = WLAN_HTCAP_SM_PS_DYNAMIC,
    };

    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    u32 flags = channel->flags;
    struct ieee80211_sta_ht_cap ht_cap = sband->ht_cap;
    u8 *pos;
    u16 cap;
    u8 secondary_channel_offset;

    net80211_vif_apply_htcap_overrides(vif, &ht_cap);

    /* prepare the capability flags */
    cap = ht_cap.cap;

    secondary_channel_offset =
        (bss_ht_param & IEEE80211_HT_PARAM_SEC_CHA_OFFSET);
    if (IEEE80211_HT_PARAM_SEC_CHA_ABOVE == secondary_channel_offset) {
        if (flags & IEEE80211_CHAN_NO_HT40PLUS) {
            cap &= ~IEEE80211_HTCAP_SGI_40;
            cap &= ~IEEE80211_HTCAP_SUP_WIDTH_20_40;
        }
    }
    else if (IEEE80211_HT_PARAM_SEC_CHA_BELOW == secondary_channel_offset) {
        if (flags & IEEE80211_CHAN_NO_HT40MINUS) {
            cap &= ~IEEE80211_HTCAP_SGI_40;
            cap &= ~IEEE80211_HTCAP_SUP_WIDTH_20_40;
        }
    }

    if (mlme_conf->flags & NET80211_MLME_DISABLE_40MHZ) {
        cap &= ~IEEE80211_HTCAP_SGI_40;
        cap &= ~IEEE80211_HTCAP_SUP_WIDTH_20_40;
    }

    /* SMPS mode */
    cap &= ~IEEE80211_HTCAP_SM_PS;
    if (smps < ARRAY_LENGTH(smps_to_ht_cap_map)) {
        cap |= (smps_to_ht_cap_map[smps] << IEEE80211_HTCAP_SM_PS_SHIFT);
    }

    /* reserve and fill ht capability IE */
    pos = skb_put(skb, sizeof(struct ieee80211_ht_capabilities) + 2);
    ieee80211_ie_build_ht_cap(pos, &ht_cap, cap);
}

static void
net80211_add_vht_ie(struct net80211_vif *vif,
    struct sk_buff *skb,
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_vht_capabilities *bss_vht_cap)
{
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct ieee80211_sta_vht_cap vht_cap = sband->vht_cap;
    u8 *pos;
    u32 cap;
    u32 bss_bf_sts, our_bf_sts;

    net80211_vif_apply_vhtcap_overrides(vif, &vht_cap);

    /* prepare the capability flags */
    cap = vht_cap.cap;

    if (mlme_conf->flags & NET80211_MLME_DISABLE_80P80MHZ) {
        u32 cap_width = cap & IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK;

        cap &= ~IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK;
        if (cap_width == IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ ||
            cap_width == IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ)
            cap |= IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ;
    }

    if (mlme_conf->flags & NET80211_MLME_DISABLE_160MHZ) {
        cap &= ~IEEE80211_VHTCAP_SHORT_GI_160;
        cap &= ~IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK;
    }

    /* set the beamformer/beamformee capabilities based on bss capabilities */
    if (!(bss_vht_cap->vht_capabilities_info &
        cpu_to_le32(IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE))) {
        cap &= ~(IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE |
            IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE);
    }
    else if (!(bss_vht_cap->vht_capabilities_info &
        cpu_to_le32(IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE))) {
        cap &= ~IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE;
    }

    bss_bf_sts = le32_to_cpu(bss_vht_cap->vht_capabilities_info) & 
        IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK;
    our_bf_sts = cap & IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK;

    if (bss_bf_sts < our_bf_sts) {
        cap &= ~IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK;
        cap |= bss_bf_sts;
    }

    /* reserve and fill VHT capability IE */
    pos = skb_put(skb, sizeof(struct ieee80211_vht_capabilities) + 2);
    ieee80211_ie_build_vht_cap(pos, &vht_cap, cap);
}

static void
net80211_add_he_ie(struct net80211_vif *vif,
    struct sk_buff *skb,
    const struct ieee80211_supported_band *sband)
{
    struct net80211_pdev *pdev = vif->pdev;
    const struct ieee80211_sta_he_cap *he_cap = NULL;
    struct ieee80211_chanctx_conf *chanctx_conf;
    u8 he_cap_size;
    u8 *pos;

    chanctx_conf = net80211_vif_get_chanctx_conf(vif);
    if (WARN_ON_ONCE(!chanctx_conf) ||
        !net80211_chandef_usable(pdev, &chanctx_conf->def, IEEE80211_CHAN_NO_HE))
        return;

    he_cap = ieee80211_get_sta_he_cap(sband);
    if (!he_cap)
        return;

    /* he capability ie is an extension ie */
    he_cap_size = 2 + 1 + sizeof(he_cap->he_capabilities);
    he_cap_size += ieee80211_he_mcs_nss_size(&he_cap->he_capabilities);
    he_cap_size += ieee80211_he_ppe_size(he_cap->ppe_thres[0],
        he_cap->he_capabilities.phy_cap_info);
    pos = skb_put(skb, he_cap_size);
    ieee80211_ie_build_he_cap(pos, he_cap, pos + he_cap_size);

	net80211_vif_build_he_6ghz_cap(vif, skb);
}

static void
net80211_add_wpa_ie(struct net80211_vif *vif,
    struct sk_buff *skb,
    struct net80211_crypto_settings *crypto)
{
    u8 *pos;
    u32 wpa_size;

    net_dbg("add wpa ie\n");

    wpa_size = 2 + 4 +
        2 + /* version */
        4 + /* multicast/group cipher */
        2 + 4 * crypto->n_ciphers_pairwise + /* unicast ciphers */
        2 + 4 * crypto->n_akm_suites + /* key management algorithms */
        2; /* capability */

    pos = skb_put(skb, wpa_size);

    /* build */
    ieee80211_ie_build_wpa(pos, crypto);
}

static void
net80211_add_rsn_ie(struct net80211_vif *vif,
    struct sk_buff *skb,
    struct net80211_crypto_settings *crypto)
{
    u8 *pos;
    u32 rsn_size;
    u32 ext_len;

    net_dbg("add rsn ie\n");

    if (crypto->group_mgmt_cipher_suite) {
        net_dbg("add pmkid and gmc suite ie\n");
        ext_len = 2 + /* pmkid count & list*/
            4; /* group mgmt cipher suite*/
    }
    else
        ext_len = 0;

    rsn_size = 2 +
        2 + /* version */
        4 + /* multicast/group cipher */
        2 + 4 * crypto->n_ciphers_pairwise + /* unicast ciphers */
        2 + 4 * crypto->n_akm_suites + /* key management algorithms */
        2 + /* capability */
        ext_len;

    pos = skb_put(skb, rsn_size);

    /* build */
    ieee80211_ie_build_rsn(pos, crypto);
}

static void
net80211_add_rsnxe_ie(struct net80211_vif *vif,
    struct sk_buff *skb,
    struct net80211_crypto_settings *crypto)
{
    u8 *pos;
    u32 rsnxe_size;

    net_dbg("add rsnxe ie\n");

    rsnxe_size = 2 + 1 /* extension capability */;
    pos = skb_put(skb, rsnxe_size);

    /* build */
    ieee80211_ie_build_rsnxe(pos, crypto);
}

static void
net80211_add_wmm_info_ie(struct net80211_vif *vif, struct sk_buff *skb, bool uapsd)
{
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    u8 qos_info;
	void *ptr = NULL;

    if (uapsd) {
        qos_info = mlme_conf->uapsd_queues;
        qos_info |= (mlme_conf->uapsd_max_sp_len << IEEE80211_WMM_IE_STA_UAPSD_SP_SHIFT);
    }
    else {
        qos_info = 0;
    }

    if (skb) {
        ptr = skb_put(skb, 9);
		if (ptr)
			ieee80211_add_wmm_info_ie(ptr, qos_info);
	}	
}

static void
net80211_sta_send_assoc_complete(struct sk_buff *skb,
    void *arg, bool acked)
{
    struct net80211_vif *vif = arg;
    struct net80211_assoc_data *assoc_data = net80211_sta_get_assoc_data(vif);
    if (assoc_data && !acked) {
        queue_delayed_work(&assoc_data->run_again, 0);
    }
}

static void
net80211_sta_send_assoc(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_assoc_data *assoc_data = net80211_sta_get_assoc_data(vif);
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct sk_buff *skb;
    struct ieee80211_mgmt *mgmt;
    u8 *pos;
    u32 offset = 0, noffset;
    int shift;
    u32 basic_rates_len, rates_len;
    u8 supp_rates_len;
    u16 cap;
    u32 n;

    const struct ieee80211_supported_band *sband;
    struct ieee80211_chanctx_conf *chanctx_conf;
    struct ieee80211_channel *chan;
    u32 rates = 0;
    struct element *ext_capa = NULL;

    if (assoc_data->ie_len) {
        ext_capa = (void *)ieee80211_find_element(
            assoc_data->ie, assoc_data->ie_len, 
            WLAN_EID_EXT_CAPAB);
    }

    chanctx_conf = net80211_vif_get_chanctx_conf(vif);
    if (WARN_ON(!chanctx_conf)) {
        return;
    }

    chan = chanctx_conf->def.chan;
    sband = net80211_get_sband(pdev, chan->band);
	if (sband == NULL)
		return;

    shift = net80211_vif_get_channel_shift(vif);

    /* get all supported rates */
    rates_len = ieee80211_parse_bitrates(&chanctx_conf->def, sband,
        assoc_data->supp_rates,
        assoc_data->supp_rates_len,
        &rates);

    skb = dev_alloc_skb(pdev->dev, sizeof(*mgmt) + /* header */
        2 + assoc_data->ssid_len + /* SSID */
        4 + rates_len + /* supported rates */
        4 + /* power capability */
        2 + 2 * sband->n_channels + /* supported channels */
        128 + /* max RSN or WPA information */
        2 + sizeof(struct ieee80211_ht_capabilities) + /* HT capabilities */
        2 + sizeof(struct ieee80211_vht_capabilities) + /* VHT capabilities */
        2 + 1 + sizeof(struct ieee80211_he_capabilities) + /* HE capabilities */
        sizeof(struct ieee80211_he_mcs_nss_supp) +
        IEEE80211_HE_PPE_THRES_MAX_LEN +
        2 + 1 + sizeof(struct ieee80211_he_6ghz_cap) +
        assoc_data->ie_len + /* addtional IEs */
        sizeof(struct ieee80211_wmm_ie) /* WMM */);
    if (!skb)
        return;

    cap = WLAN_CAPABILITY_ESS;

    if (sband->band == NL80211_BAND_2GHZ) {
        cap |= WLAN_CAPABILITY_SHORT_PREAMBLE;
        cap |= WLAN_CAPABILITY_SHORT_SLOT_TIME;
    }

    if (assoc_data->capability & WLAN_CAPABILITY_PRIVACY)
        cap |= WLAN_CAPABILITY_PRIVACY;

    if ((assoc_data->capability & WLAN_CAPABILITY_SPECTRUM_MGMT) &&
        net80211_hw_check(pdev, IEEE80211_HW_SPECTRUM_MGMT))
        cap |= WLAN_CAPABILITY_SPECTRUM_MGMT;

    if (mlme_conf->flags & NET80211_MLME_ENABLE_RRM)
        cap |= WLAN_CAPABILITY_RADIO_MEASURE;

    mgmt = skb_put_zero(skb, 24);
	if (!mgmt)
		return;
	
    memcpy(mgmt->da, assoc_data->bss->bssid, ETH_ALEN);
    memcpy(mgmt->sa, net80211_vif_addr(vif), ETH_ALEN);
    memcpy(mgmt->bssid, assoc_data->bss->bssid, ETH_ALEN);

    if (!is_zero_ether_addr(assoc_data->prev_bssid)) {
        skb_put(skb, 10);
        mgmt->frame_control = IEEE80211_FC_TYPE(IEEE80211_FC0_TYPE_MGT, IEEE80211_FC0_SUBTYPE_REASSOC_REQ);
        mgmt->u.reassoc_req.capab_info = cpu_to_le16(cap);
        mgmt->u.reassoc_req.listen_interval =
            cpu_to_le16(net80211_get_listen_interval(pdev));
        memcpy(mgmt->u.reassoc_req.current_ap, assoc_data->prev_bssid,
            ETH_ALEN);
    }
    else {
        skb_put(skb, 4);
        mgmt->frame_control = IEEE80211_FC_TYPE(IEEE80211_FC0_TYPE_MGT, IEEE80211_FC0_SUBTYPE_ASSOC_REQ);
        mgmt->u.assoc_req.capab_info = cpu_to_le16(cap);
        mgmt->u.assoc_req.listen_interval =
            cpu_to_le16(net80211_get_listen_interval(pdev));
    }

    net_dbg("capab_info=0x%x, listen_interval=%u\n", mgmt->u.assoc_req.capab_info,
        mgmt->u.assoc_req.listen_interval);

    /* SSID */
    pos = skb_put(skb, 2 + assoc_data->ssid_len);
    *pos++ = WLAN_EID_SSID;
    *pos++ = assoc_data->ssid_len;
    memcpy(pos, assoc_data->ssid, assoc_data->ssid_len);

    /* Supported Rates */
    supp_rates_len = (u8)min(rates_len, 8);

    pos = skb_put(skb, 2 + supp_rates_len);
    *pos++ = WLAN_EID_SUPP_RATES;
    *pos++ = supp_rates_len;

    basic_rates_len = 0;
    for (n = 0; n < sband->n_bitrates; n++) {
        if (BIT(n) & rates) {
            int rate = DIV_ROUND_UP(sband->bitrates[n].bitrate,
                5 * (1 << shift));
            *pos++ = (u8)rate;
            if (++basic_rates_len == 8)
                break;
        }
    }

    /* Extended Supported Rates */
    if (rates_len > basic_rates_len) {
        pos = skb_put(skb, 2 + rates_len - basic_rates_len);
        *pos++ = WLAN_EID_EXT_SUPP_RATES;
        *pos++ = (u8)(rates_len - basic_rates_len);

        for (n++; n < sband->n_bitrates; n++) {
            if (BIT(n) & rates) {
                int rate;
                rate = DIV_ROUND_UP(sband->bitrates[n].bitrate,
                    5 * (1 << shift));
                *pos++ = (u8)rate;
            }
        }
    }

    /* Power Capability */
    if (cap & WLAN_CAPABILITY_SPECTRUM_MGMT ||
        cap & WLAN_CAPABILITY_RADIO_MEASURE) {
        pos = skb_put(skb, 4);
        *pos++ = WLAN_EID_PWR_CAPABILITY;
        *pos++ = 2;
        *pos++ = 0; /* min tx power */
         /* max tx power */
        *pos++ = (u8)ieee80211_chandef_max_power(&chanctx_conf->def);
    }

    if (cap & WLAN_CAPABILITY_SPECTRUM_MGMT &&
        (sband->band != NL80211_BAND_6GHZ ||
            !ext_capa || ext_capa->datalen < 1 ||
            !(ext_capa->data[0] & WLAN_EXT_CAPA1_EXT_CHAN_SWITCHING))) {
        /* TODO: get this in reg domain format */
        pos = skb_put(skb, 2 * sband->n_channels + 2);
        *pos++ = WLAN_EID_SUPPORTED_CHANNELS;
        *pos++ = (u8)(2 * sband->n_channels);
        for (n = 0; n < sband->n_channels; n++) {
            *pos++ = (u8)ieee80211_frequency_to_channel(
                sband->channels[n].center_freq);
            *pos++ = 1; /* one channel in the subband*/
        }
    }

    /* RSN */
    if (assoc_data->crypto.wpa_type & IEEE80211_WPA_TYPE_RSN) {
        net80211_add_rsn_ie(vif, skb, &assoc_data->crypto);
    }

    /* add any custom IEs that go before HT */
    if (assoc_data->ie_len) {
        // TODOTODO: add custom ies
    }

    /* HT capability */
    if (sband->band != NL80211_BAND_6GHZ &&
		!(mlme_conf->flags & NET80211_MLME_DISABLE_HT))
        net80211_add_ht_ie(vif, skb, assoc_data->bss_ht_param,
            sband, chan, vif->smps_mode);

    /* Extended capability */
    if (net80211_hw_check(pdev, IEEE80211_HW_SUPPORTS_ONLY_HE_MULTI_BSSID) &&
        !(mlme_conf->flags & NET80211_MLME_DISABLE_HE) && assoc_data->ie_len &&
        ext_capa && ext_capa->datalen >= 3)
        ext_capa->data[2] |= WLAN_EXT_CAPA3_MULTIPLE_BSSID_SUPPORT;

    /* add any custom IEs that go before VHT */
    if (assoc_data->ie_len) {
        // TODOTODO: add custom ies
    }

    /* VHT Capability */
    if (WARN_ON_ONCE((mlme_conf->flags & NET80211_MLME_DISABLE_HT) &&
        !(mlme_conf->flags & NET80211_MLME_DISABLE_VHT)))
        mlme_conf->flags |= NET80211_MLME_DISABLE_VHT;

    if (sband->band != NL80211_BAND_6GHZ &&
		!(mlme_conf->flags & NET80211_MLME_DISABLE_VHT))
        net80211_add_vht_ie(vif, skb, sband, &assoc_data->bss_vht_cap);

    /* add any custom IEs that go before HE */
    if (assoc_data->ie_len) {
        // TODOTODO: add custom ies
    }

    if ((assoc_data->crypto.wpa_type & IEEE80211_WPA_TYPE_RSN) && 
        (assoc_data->crypto.rsnxe_cap != 0)) {
        net80211_add_rsnxe_ie(vif, skb, &assoc_data->crypto);
    }

    /* HE Capability */
    if (mlme_conf->flags & NET80211_MLME_DISABLE_HT ||
        (sband->band == NL80211_BAND_5GHZ && mlme_conf->flags & NET80211_MLME_DISABLE_VHT))
        mlme_conf->flags |= NET80211_MLME_DISABLE_HE;

    if (!(mlme_conf->flags & NET80211_MLME_DISABLE_HE))
        net80211_add_he_ie(vif, skb, sband);

    /* if present, add any custom non-vendor IEs that go after HE */
    if (assoc_data->ie_len) {
        // TODOTODO: add custom non-vendor ies
    }

    if (assoc_data->crypto.wpa_type & IEEE80211_WPA_TYPE_WPA) {
        net80211_add_wpa_ie(vif, skb, &assoc_data->crypto);
    }

    if (assoc_data->wmm) {
        net80211_add_wmm_info_ie(vif, skb, assoc_data->uapsd);
    }

    /* add any remaining custom (i.e. vendor specific here) IEs */
    if (assoc_data->ie_len) {
        noffset = assoc_data->ie_len;
        skb_put_data(skb, assoc_data->ie + offset, noffset - offset);
    }

    IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTERNAL_DONT_ENCRYPT;
    if (net80211_hw_check(pdev, IEEE80211_HW_REPORTS_TX_ACK_STATUS))
        IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_REQUEST_TX_STATUS |
        IEEE80211_TX_INTERNAL_MLME_TX;
    IEEE80211_SKB_CB(skb)->tx_complete_handler = net80211_sta_send_assoc_complete;
    IEEE80211_SKB_CB(skb)->tx_complete_arg = vif;

    net80211_tx_skb(vif, skb);
}

int
net80211_sta_assoc_request(struct net80211_vif *vif)
{
    struct net80211_assoc_data *assoc_data = net80211_sta_get_assoc_data(vif);

    if (WARN_ON_ONCE(!assoc_data))
        return -EINVAL;

    assoc_data->tries++;
    if (assoc_data->tries > NET80211_ASSOC_MAX_TRIES) {
        net_dbg("association with %02X:%02X:%02X:%02X:%02X:%02X timed out\n",
            assoc_data->bss->bssid[0], assoc_data->bss->bssid[1],
            assoc_data->bss->bssid[2], assoc_data->bss->bssid[3],
            assoc_data->bss->bssid[4], assoc_data->bss->bssid[5]);
        return -ETIMEDOUT;
    }

    net_dbg("associate with %02X:%02X:%02X:%02X:%02X:%02X (try %d/%d)\n",
        assoc_data->bss->bssid[0], assoc_data->bss->bssid[1],
        assoc_data->bss->bssid[2], assoc_data->bss->bssid[3],
        assoc_data->bss->bssid[4], assoc_data->bss->bssid[5],
        assoc_data->tries, NET80211_ASSOC_MAX_TRIES);

    net80211_sta_send_assoc(vif);

    queue_delayed_work(&assoc_data->run_again, NET80211_ASSOC_TIMEOUT);

    return 0;
}

/* deauth */

static void
net80211_sta_send_deauth_complete(struct sk_buff *skb,
    void *arg, bool acked)
{
    struct net80211_vif *vif = arg;
    struct net80211_deauth_data *deauth_data = net80211_sta_get_deauth_data(vif);
    if (deauth_data) {
        net80211_sta_set_disassoc(vif);
    }

    net80211_sta_sme_tx_mgmt(vif, skb->data, skb->len);
}

static inline 
int
net80211_sta_key_get_iv(struct net80211_vif* vif)
{
    int iv_size = 0;
    net_dbg("cipher is %d\n", vif->ptk_key->conf.cipher);
    if (!vif->ptk_key)
        return 0;

    switch (vif->ptk_key->conf.cipher) {
    case WLAN_RSN_CIPHER_SUITE_CCMP:
    case WLAN_RSN_CIPHER_SUITE_AES_CMAC:
    case WLAN_RSN_CIPHER_SUITE_GCMP:
    case WLAN_RSN_CIPHER_SUITE_GCMP_256:
    case WLAN_RSN_CIPHER_SUITE_CCMP_256:
    case WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128:
    case WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256:
    case WLAN_RSN_CIPHER_SUITE_BIP_CMAC_256:
        iv_size = 8;
        break;
    case WLAN_RSN_CIPHER_SUITE_WEP40:
    case WLAN_RSN_CIPHER_SUITE_WEP104:
        iv_size = 4;
        break;
    default:
        break;
    }
    net_dbg("iv_size is %d\n", iv_size);
    return iv_size;

}

static inline
int
net80211_sta_key_get_mic(struct net80211_vif* vif)
{
    int mic_size = 0;
    net_dbg("cipher is %d\n", vif->ptk_key->conf.cipher);
    net_dbg("cipher key len is %d\n", vif->ptk_key->conf.key_len);
    if (!vif->ptk_key)
        return 0;

    switch (vif->ptk_key->conf.cipher) {
    case WLAN_RSN_CIPHER_SUITE_CCMP:
    case WLAN_RSN_CIPHER_SUITE_AES_CMAC:
    case WLAN_RSN_CIPHER_SUITE_GCMP:
    case WLAN_RSN_CIPHER_SUITE_GCMP_256:
    case WLAN_RSN_CIPHER_SUITE_CCMP_256:
    case WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128:
    case WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256:
    case WLAN_RSN_CIPHER_SUITE_BIP_CMAC_256:
        if (vif->ptk_key->conf.key_len == 16)
            mic_size = 8; /* 8 byte MIC */
        else if (vif->ptk_key->conf.key_len == 32)
            mic_size = 16; /* 16 byte MIC */
        break;
    case WLAN_RSN_CIPHER_SUITE_WEP40:
    case WLAN_RSN_CIPHER_SUITE_WEP104:
        mic_size = 4; /* 4 byte ICV */
    case WLAN_RSN_CIPHER_SUITE_TKIP:
        mic_size = 12; /* 8 byte MIC + 4 byte ICV */
        break;
    default:
        break;
    }
    net_dbg("mic_size is %d\n", mic_size);
    return mic_size;
}

int
net80211_sta_send_deauth_disassoc(struct net80211_vif *vif,
    const u8 *da, const u8 *bssid,
    u16 stype, u16 reason,
    ieee80211_tx_complete_handler tx_complete_handler,
    void *tx_complete_arg)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct sk_buff *skb;
    struct ieee80211_mgmt *mgmt;

    skb = dev_alloc_skb(pdev->dev, IEEE80211_DEAUTH_FRAME_LEN);
    if (!skb)
        return -ENOMEM;

    /* build frame */

    mgmt = skb_put_zero(skb, IEEE80211_FRAME_HEADER_LEN);
	if (!mgmt)
		return -EFAULT;
	
    mgmt->frame_control = IEEE80211_FC_TYPE(IEEE80211_FC0_TYPE_MGT, stype);
    mgmt->duration = 0; /* initialize only */
    mgmt->seq_ctrl = 0; /* initialize only */
    memcpy(mgmt->da, da, ETH_ALEN);
    memcpy(mgmt->sa, net80211_vif_addr(vif), ETH_ALEN);
    memcpy(mgmt->bssid, bssid, ETH_ALEN);
    if ((mlme_conf->flags & NET80211_MLME_MFP_ENABLED) &&
        vif->ptk_key) {
        mgmt->frame_control |= IEEE80211_FC_WEP;
        mgmt = skb_put_zero(skb, net80211_sta_key_get_iv(vif));
        skb_put_data(skb, &reason, 2);
        skb_put(skb, net80211_sta_key_get_mic(vif));
    }
    else {
        skb_put_data(skb, &reason, 2);
        IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTERNAL_DONT_ENCRYPT;
    }

    if (net80211_hw_check(pdev, IEEE80211_HW_REPORTS_TX_ACK_STATUS))
        IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_REQUEST_TX_STATUS |
        IEEE80211_TX_INTERNAL_MLME_TX;

    IEEE80211_SKB_CB(skb)->tx_complete_handler = tx_complete_handler;
    IEEE80211_SKB_CB(skb)->tx_complete_arg = tx_complete_arg;

    net80211_tx_skb(vif, skb);

    return 0;
}

int
net80211_sta_deauth_request(struct net80211_vif *vif)
{
    struct net80211_deauth_data *deauth_data = net80211_sta_get_deauth_data(vif);

    if (WARN_ON_ONCE(!deauth_data))
        return -EINVAL;

    net_dbg("deauthenticating from %pM by local choice (Reason: %u=%a)\n",
        deauth_data->bssid, deauth_data->reason_code,
        ieee80211_get_reason_code_string(deauth_data->reason_code));

    return net80211_sta_send_deauth_disassoc(vif,
        deauth_data->bssid, deauth_data->bssid,
        IEEE80211_FC0_SUBTYPE_DEAUTH, deauth_data->reason_code,
        net80211_sta_send_deauth_complete,
        vif);
}
