/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 9/21/22   zxue     fix fw crash when remove interface with AP connected
 19/10/21  zxue     refine code
 22/9/21   zxue     support beacon filter
 1/9/21    zxue     fix KW issue
 28/7/21   zxue     update the connection error code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/worker.h>
#include <net/ndebug.h>
#include "net80211_i.h"
#include "mlme.h"
#include "vif.h"
#include "sta.h"
#include "chan.h"
#include "sme.h"
#include "drvops.h"

struct net80211_sme_idle_params {
    u32 reason;
    bool from_ap;
    enum net80211_connect_stage stage;
};

struct net80211_sme_deauth_params {
    u8 bssid[ETH_ALEN];
    u16 reason_code;
    enum net80211_connect_stage stage;
};

static const struct ieee80211_ht_capabilities net80211_ht_capa_mod_mask = {
    .ht_capabilities_info = cpu_to_le16(
        IEEE80211_HTCAP_LDPC_CODING |
        IEEE80211_HTCAP_SUP_WIDTH_20_40 |
        IEEE80211_HTCAP_SGI_20 |
        IEEE80211_HTCAP_SGI_40 |
        IEEE80211_HTCAP_TX_STBC |
        IEEE80211_HTCAP_RX_STBC |
        IEEE80211_HTCAP_MAX_AMSDU |
        IEEE80211_HTCAP_40MHZ_INTOLERANT),
    .ampdu_params_info = (
        IEEE80211_HTCAP_AMPDU_PARM_FACTOR |
        IEEE80211_HTCAP_AMPDU_PARM_DENSITY),
    .mcs = {
        .rx_mask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, },
    },
};

static const struct ieee80211_vht_capabilities net80211_vht_capa_mod_mask = {
    .vht_capabilities_info = cpu_to_le32(
        IEEE80211_VHTCAP_RXLDPC |
        IEEE80211_VHTCAP_SHORT_GI_80 |
        IEEE80211_VHTCAP_SHORT_GI_160 |
        IEEE80211_VHTCAP_TXSTBC |
        IEEE80211_VHTCAP_RXSTBC_MASK |
        IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE |
        IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE |
        IEEE80211_VHTCAP_RX_ANTENNA_PATTERN |
        IEEE80211_VHTCAP_TX_ANTENNA_PATTERN |
        IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK),
    .supported_mcs_set = {
        .rx_mcs_map = 0xFFFF,
        .tx_mcs_map = 0xFFFF,
    },
};

 /* struct net80211_crypto_settings */
static bool
net80211_crypto_want_eapol(struct net80211_crypto_settings *crypto)
{
    static const u32 AKM_SUITES_WANT_EAPOL[] = {
        WLAN_RSN_AKM_SUITE_PSK,
        WLAN_RSN_AKM_SUITE_8021X,
        WLAN_RSN_AKM_SUITE_SAE,
        WLAN_RSN_AKM_SUITE_PSK_SHA256,
        WLAN_RSN_AKM_SUITE_8021X_SHA256,
        WLAN_RSN_AKM_SUITE_SUITE_B,
        WLAN_RSN_AKM_SUITE_SUITE_B_192,
    };

    u32 i, j;

    if (!crypto->n_akm_suites)
        return false;

    for (i = 0; i < crypto->n_akm_suites; i++) {
        for (j = 0; i < ARRAY_SIZE(AKM_SUITES_WANT_EAPOL); j++) {
            if (crypto->akm_suites[i] == AKM_SUITES_WANT_EAPOL[j])
                return true;
        }
    }

    return false;
}

static inline enum nl80211_auth_type
net80211_sta_auto_select_auth_type(
    struct net80211_crypto_settings *crypto)
{
    u16 i;

    for (i = 0; i < crypto->n_akm_suites; i++) {
        if (crypto->akm_suites[i] == WLAN_RSN_AKM_SUITE_SAE) {
            return NL80211_AUTHTYPE_SAE;
        }
    }

    return NL80211_AUTHTYPE_OPEN_SYSTEM;
}

static int
net80211_select_assoc_crypto_settings(
    struct net80211_supported_crypto_settings *scrypto,
    struct net80211_crypto_settings *crypto,
    struct net80211_crypto_settings *assoc_crypto)
{
    u32 i, j;
	u8 selected;

    assoc_crypto->wpa_type = crypto->wpa_type;
    assoc_crypto->wpa_versions = crypto->wpa_versions;
    assoc_crypto->cipher_group = crypto->cipher_group;
    assoc_crypto->mfp = crypto->mfp;

    /* select single pairwise cipher suite base on priority */
    if (crypto->n_ciphers_pairwise >= 1) {
	    selected = 0;
        assoc_crypto->n_ciphers_pairwise = 1;
        assoc_crypto->ciphers_pairwise[0] = crypto->ciphers_pairwise[0];

        for (i = 0; i < scrypto->n_cipher_suites && !selected; i++) {
            for (j = 0; j < crypto->n_ciphers_pairwise; j++) {
                if (scrypto->cipher_suites[i] == crypto->ciphers_pairwise[j]) {
                    assoc_crypto->ciphers_pairwise[0] = crypto->ciphers_pairwise[j];
					selected = 1;
                    break;
                }
            }
        }

        net_dbg("select pairwise cipher suite %08X from %d suites\n", 
            assoc_crypto->ciphers_pairwise[0], crypto->n_ciphers_pairwise);
    }

    /* select single akm suite base on priority */
	if (crypto->n_akm_suites >= 1) {
	    selected = 0;
        for (i = 0; i < scrypto->n_akm_suites && !selected; i++) {
            for (j = 0; j < crypto->n_akm_suites; j++) {
                if (scrypto->akm_suites[i] == crypto->akm_suites[j]) {
                    assoc_crypto->akm_suites[0] = crypto->akm_suites[j];
                    assoc_crypto->n_akm_suites = 1;
					selected = 1;
                    break;
                }
            }
        }

        if (selected) {
            net_dbg("select akm suite %08X from %d suites\n",
                assoc_crypto->akm_suites[0], crypto->n_akm_suites);
        }
        else {
            net_dbg("fail to select akm suite %08X from %d suites\n",
                assoc_crypto->akm_suites[0], crypto->n_akm_suites);
            return -ECONNABORTED;
        }
    }

    /* select group mgmt cipher suite */
    if (crypto->mfp) {
        switch (assoc_crypto->akm_suites[0]) {
        case WLAN_RSN_AKM_SUITE_SAE:
            assoc_crypto->group_mgmt_cipher_suite = WLAN_RSN_CIPHER_SUITE_AES_CMAC;
            break;
        case WLAN_RSN_AKM_SUITE_8021X:
        case WLAN_RSN_AKM_SUITE_8021X_SHA256:
            assoc_crypto->group_mgmt_cipher_suite = WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128;
            break;
        case WLAN_RSN_AKM_SUITE_SUITE_B:
        case WLAN_RSN_AKM_SUITE_SUITE_B_192:
            assoc_crypto->group_mgmt_cipher_suite = WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256;
            break;
		case WLAN_RSN_AKM_SUITE_PSK:
		case WLAN_RSN_AKM_SUITE_PSK_SHA256:
			/* don't specify the group mgmt cipher suite */
			break;
        default:
            net_err("unsupported akm_suite: %08X\n", assoc_crypto->akm_suites[0]);
        }

        net_dbg("select group mgmt cipher suite %08X\n", assoc_crypto->group_mgmt_cipher_suite);
    }

    if (crypto->rsnxe_cap & IEEE80211_RSNXE_CAP_SAE_H2E) {
        switch (assoc_crypto->akm_suites[0]) {
        case WLAN_RSN_AKM_SUITE_SAE:
            assoc_crypto->rsnxe_cap |= (crypto->rsnxe_cap & IEEE80211_RSNXE_CAP_SAE_H2E);
            break;
        default:
            net_err("SAE H2E is not supported for akm_suite: %08x\n", assoc_crypto->akm_suites[0]);
        }

        net_dbg("select rsnxe capability 0x%x\n", assoc_crypto->rsnxe_cap);
    }

    return 0;
}

static int
net80211_get_assoc_crypto_settings(
    struct net80211_supported_crypto_settings *scrypto,
    struct net80211_bss *bss,
    struct net80211_crypto_settings *assoc_crypto)
{
    struct net80211_crypto_settings crypto = { 0 };
    const u8 *wpa_ie, *rsn_ie, *rsnxe_ie;
    int err = 0;

    rsn_ie = net80211_bss_find_ie(bss, WLAN_EID_RSN);
    if (rsn_ie) {
        err = ieee80211_parse_rsn_ie(rsn_ie, &crypto);
    }

    if (!rsn_ie || err) {
        wpa_ie = net80211_bss_find_vendor_ie(bss, WLAN_OUI_MICROSOFT_WPA);
        if (wpa_ie) {
            err = ieee80211_parse_wpa_ie(wpa_ie, &crypto);
        }
    }

    if (crypto.wpa_type == IEEE80211_WPA_TYPE_RSN) {
        rsnxe_ie = net80211_bss_find_ie(bss, WLAN_EID_RSNX);
        if (rsnxe_ie) {
            ieee80211_parse_rsnxe_ie(rsnxe_ie, &crypto);
        }
    }

    if (crypto.wpa_type != IEEE80211_WPA_TYPE_NONE)
        err = net80211_select_assoc_crypto_settings(scrypto, &crypto, assoc_crypto);

    return err;
}

/* struct net80211_sme */

struct net80211_state_info {
    const char *name;
    void(*state_entry)(void *ctx, void *params);
    void(*state_exit)(void *ctx);
    bool(*state_event)(void *ctx, u16 event_type, u16 event_data_len, void *event_data);
};

enum net80211_sme_state {
    NET80211_SME_STATE_IDLE,
    NET80211_SME_STATE_AUTH,
    NET80211_SME_STATE_ASSOC,
    NET80211_SME_STATE_RUN,
    NET80211_SME_STATE_DEAUTH,
};

#define NET80211_SME_STATE_NUM (NET80211_SME_STATE_DEAUTH + 1)

enum net80211_sme_event {
    NET80211_SME_EVENT_CONNECT_REQUEST,
    NET80211_SME_EVENT_DISCONNECT_REQUEST,
    NET80211_SME_EVENT_AUTH_SUCCESS,
    NET80211_SME_EVENT_AUTH_FAIL,
    NET80211_SME_EVENT_ASSOC_SUCCESS,
    NET80211_SME_EVENT_ASSOC_FAIL,
    NET80211_SME_EVENT_DISASSOC,
    NET80211_SME_EVENT_DEAUTH,
    NET80211_SME_EVENT_DEAUTH_CONFIRM,
    NET80211_SME_EVENT_DISASSOC_CONFIRM,
    NET80211_SME_EVENT_TIMEOUT,
    NET80211_SME_EVENT_ABORT,
};

static const char *net80211_sme_event_names[] = {
    [NET80211_SME_EVENT_CONNECT_REQUEST ] = "CONNECT_REQUEST",
    [NET80211_SME_EVENT_DISCONNECT_REQUEST] = "DISCONNECT_REQUEST",
    [NET80211_SME_EVENT_AUTH_SUCCESS] = "AUTH_SUCCESS",
    [NET80211_SME_EVENT_AUTH_FAIL] = "AUTH_FAIL",
    [NET80211_SME_EVENT_ASSOC_SUCCESS] = "ASSOC_SUCCESS",
    [NET80211_SME_EVENT_ASSOC_FAIL] = "ASSOC_FAIL",
    [NET80211_SME_EVENT_DISASSOC] = "DISASSOC",
    [NET80211_SME_EVENT_DEAUTH] = "DEAUTH",
    [NET80211_SME_EVENT_DEAUTH_CONFIRM] = "DEAUTH_CONFIRM",
    [NET80211_SME_EVENT_DISASSOC_CONFIRM] = "DISASSOC_CONFIRM",
    [NET80211_SME_EVENT_TIMEOUT] = "TIMEOUT",
    [NET80211_SME_EVENT_ABORT] = "ABORT",
};

struct net80211_conn
{
    struct net80211_connect_params params;
    struct net80211_bss *bss;
    u8 bssid[ETH_ALEN];
    bool auto_auth;
};

static void
net80211_conn_select_auth_type(
    struct net80211_conn *conn,
    struct net80211_crypto_settings *auth_crypto)
{
    if (conn->params.auth_type != NL80211_AUTHTYPE_AUTOMATIC)
        return;

    conn->auto_auth = true;
    conn->params.auth_type =
        net80211_sta_auto_select_auth_type(auth_crypto);
}

struct net80211_sme {
    struct net80211_pdev *pdev;
    struct net80211_vif *vif;

    /* connecting */
    struct net80211_conn *conn;

    /* state machine */
    enum net80211_sme_state state;
    const struct net80211_state_info *state_info;
    void *state_data[NET80211_SME_STATE_NUM];

	/* the state machine is on idle or not */
	struct completion on_idle;

    const char **event_names;   /* for debug printing */
    u32 n_event_names;

    /* conf */
    struct net80211_mlme_conf conf;
};

static void
net80211_sme_transition_to(struct net80211_sme *sme, u8 next_state, void *params)
{
    const struct net80211_state_info *state_info = sme->state_info;
    u8 state = sme->state;

    if (next_state == state) {
        net_warn("SME: invalid transition from %d to %d\n", state, next_state);
        return;
    }

    net_dbg("SME: transition %a => %a\n",
        state_info[state].name, state_info[next_state].name);

    /* exit current state */
    if (state_info[state].state_exit) {
        state_info[state].state_exit(sme);
    }

    /* entry next state */
    sme->state = next_state;
    if (state_info[next_state].state_entry) {
        state_info[next_state].state_entry(sme, params);
    }
}

static void
net80211_sme_dispatch(struct net80211_sme *sme, u16 event_type,
    u16 event_data_len, void *event_data)
{
    const struct net80211_state_info *state_info;

    state_info = &sme->state_info[sme->state];

    net_dbg("SME: state %a event %a(%d)\n",
        state_info->name, 
        (sme->event_names && (event_type < sme->n_event_names)) ?
        sme->event_names[event_type] : "UNKOWN", event_type);

    if (state_info->state_event) {
        state_info->state_event(sme, event_type, event_data_len, event_data);
    }
}

static void
net80211_sme_free(struct net80211_sme *sme)
{
    if (!sme->conn)
        return;

    if (sme->conn->bss) {
        net80211_put_bss(sme->pdev, sme->conn->bss);
    }

    kfree(sme->conn);
    sme->conn = NULL;
}

static void
net80211_sme_timeout(void *ctx)
{
    struct net80211_sme *sme = ctx;
    net80211_sme_dispatch(sme, NET80211_SME_EVENT_TIMEOUT, 0, ERR_PTR(-ECONNABORTED));
}

static void
net80211_sme_state_idle_entry(void *ctx, void *params)
{
    struct net80211_sme *sme = ctx;
    struct net80211_sme_idle_params *idle_params = params;

    if (!idle_params)
        return;

    if (sme->conn) {
        /* notify */
        struct net80211_connect_result cr = { 0 };
        cr.status = 1;
        cr.reason = idle_params->reason;
        cr.stage = idle_params->stage;
        cr.want_eapol = sme->conn->params.want_eapol;
        memcpy(cr.bssid, sme->conn->bss->bssid, sizeof(cr.bssid));

        net80211_sta_sme_connect_done(sme->vif, &cr);

        /* clean */
        net80211_sme_free(sme);
    }
    else {
        struct net80211_disconnect_result dr = { 0 };
        dr.reason = idle_params->reason;
        dr.from_ap = idle_params->from_ap;

        net80211_sta_sme_send_disconnected(sme->vif, &dr);
    }
	
	complete(&sme->on_idle);
}

static void
net80211_sme_state_idle_exit(void *ctx)
{
    struct net80211_sme *sme = ctx;
	
	reinit_completion(&sme->on_idle);
    WARN_ON(sme->conn == NULL);
}

static bool
net80211_sme_state_idle_event(void *ctx,
    u16 event_type, u16 event_data_len, void *event_data)
{
    struct net80211_sme *sme = ctx;
    bool unhandled = false;

    switch (event_type) {
    case NET80211_SME_EVENT_CONNECT_REQUEST:
        net80211_sme_transition_to(sme, NET80211_SME_STATE_AUTH, NULL);
        break;
    default:
        unhandled = true;
        break;
    }

    return !unhandled;
}

static void
net80211_sme_state_auth_entry(void *ctx, void *params)
{
    struct net80211_sme *sme = ctx;
    struct net80211_pdev *pdev = sme->pdev;
    struct net80211_vif *vif = sme->vif;
    struct net80211_conn *conn = sme->conn;
    struct net80211_auth_data *auth_data;
    const u8 *ssidie;
    int err;

    /* allocate auth data */
    auth_data = kzalloc(sizeof(*auth_data), GFP_KERNEL);
    if (!auth_data) {
		err = -ENOMEM;
        goto err_auth;
    }

    sme->state_data[sme->state] = auth_data;

    /* initialize the auth data */
    
    /* 1) bss */
    auth_data->bss = net80211_ref_bss(pdev, conn->bss);
	if (auth_data->bss == NULL) {
		err = -ENOMEM;
        goto err_auth;
    }

    /* 2) ssid */
    ssidie = net80211_bss_find_ie(conn->bss, WLAN_EID_SSID);
    if (!ssidie || ssidie[1] > sizeof(auth_data->ssid)) {
		err = -EINVAL;
        goto err_auth;
    }
    memcpy(auth_data->ssid, ssidie + 2, ssidie[1]);
    auth_data->ssid_len = ssidie[1];

    /* 3) crypto settings */
	err = net80211_get_assoc_crypto_settings(&pdev->scrypto, conn->bss, &auth_data->crypto);
    if (err) {
		net_err("failed to get assoc crypto settings: %d\n", err);
        goto err_auth;
    }

    /* 4) select auth type */
    net80211_conn_select_auth_type(conn, &auth_data->crypto);

    /* NOTE: key data? */

    auth_data->algorithm = ieee80211_auth_type_to_auth_algorithm(conn->params.auth_type);
    init_delayed_work(&auth_data->run_again, net80211_sme_timeout, sme);

    /* auth preparation */
    net_dbg("authenticate with %02X:%02X:%02X:%02X:%02X:%02X\n",
        auth_data->bss->bssid[0], auth_data->bss->bssid[1],
        auth_data->bss->bssid[2], auth_data->bss->bssid[3],
        auth_data->bss->bssid[4], auth_data->bss->bssid[5]);

    err = net80211_prep_connection(vif, auth_data->bss, false, false);
    if (err) {
        net_err("failed to prepare connection: %d\n", err);
        goto err_auth;
    }

    /* auth */
    err = net80211_sta_auth_request(vif);
    if (err) {
        net80211_vif_destroy_sta(vif, auth_data->bss->bssid);
        goto err_auth;
    }

    return;

err_auth:
    net80211_sme_dispatch(sme, NET80211_SME_EVENT_ABORT, 0, ERR_PTR(err));
}

static void
net80211_sme_state_auth_exit(void *ctx)
{
    struct net80211_sme *sme = ctx;
    struct net80211_vif *vif = sme->vif;
    struct net80211_pdev *pdev = sme->pdev;
    struct net80211_auth_data *auth_data = sme->state_data[sme->state];

    cancel_delayed_work(&auth_data->run_again);

    if (!auth_data->assoc) {
        net80211_vif_destroy_sta(vif, auth_data->bss->bssid);
        net80211_vif_bss_conf_set_bssid(vif, NULL);
        net80211_vif_bss_conf_change_notify(vif);
        net80211_vif_release_channel(vif);
    }

    net80211_put_bss(pdev, auth_data->bss);
    kfree(auth_data);
    sme->state_data[sme->state] = NULL;
}

static bool
net80211_sme_state_auth_event(void *ctx,
    u16 event_type, u16 event_data_len, void *event_data)
{
    struct net80211_sme *sme = ctx;
    struct net80211_auth_data *auth_data = sme->state_data[sme->state];
    bool unhandled = false;

    switch (event_type) {
    case NET80211_SME_EVENT_AUTH_FAIL:
        auth_data->algorithm = 
            ieee80211_auth_type_to_auth_algorithm(sme->conn->params.auth_type);
    case NET80211_SME_EVENT_TIMEOUT:
        if (!net80211_sta_auth_request(sme->vif))
            break;
        /* fall through */
    case NET80211_SME_EVENT_ABORT:
        if (1) {
            struct net80211_sme_idle_params params = { 0 };
            params.reason = PTR_ERR(event_data);
            params.stage = NET80211_CONNECT_STAGE_AUTH;
            params.from_ap = (PTR_ERR(event_data) > 1);

            net80211_sme_transition_to(sme, NET80211_SME_STATE_IDLE, &params);
        }
        break;
    case NET80211_SME_EVENT_AUTH_SUCCESS:
        auth_data->assoc = true;
        net80211_sme_transition_to(sme, NET80211_SME_STATE_ASSOC, NULL);
        break;
    default:
        unhandled = true;
        break;
    }

    return !unhandled;
}

static void
net80211_sme_state_assoc_entry(void *ctx, void *parmas)
{
    struct net80211_sme *sme = ctx;
    struct net80211_pdev *pdev = sme->pdev;
    struct net80211_vif *vif = sme->vif;
    struct net80211_bss *bss = sme->conn->bss;
    struct net80211_mlme_conf *mlme_conf = &sme->conf;
    struct net80211_assoc_data *assoc_data;
    struct ieee80211_supported_band *sband;
	bool is_6ghz = bss->channel->band == NL80211_BAND_6GHZ;
    const u8 *ssidie, *ht_ie, *vht_ie;
    bool foverride = false;
    int err;

    assoc_data = kzalloc(sizeof(*assoc_data), GFP_KERNEL);
    if (!assoc_data) {
		err = -ENOMEM;
        goto err_assoc;
    }

    sme->state_data[sme->state] = assoc_data;

    /* prepare assoc data */

    /* 1) ssid */
    ssidie = net80211_bss_find_ie(bss, WLAN_EID_SSID);
    if (!ssidie || ssidie[1] > sizeof(assoc_data->ssid)) {
		err = -EINVAL;
        goto err_assoc;
    }
    memcpy(assoc_data->ssid, ssidie + 2, ssidie[1]);
    assoc_data->ssid_len = ssidie[1];

    /* 2) WMM */
    assoc_data->wmm = bss->data.wmm_used &&
        (net80211_get_hw_queues(pdev) >= IEEE80211_NUM_OF_ACS);

    /* 3) crypto settings */
   err = net80211_get_assoc_crypto_settings(&pdev->scrypto, bss, &assoc_data->crypto);
   if (err) {
   	   net_err("failed to get assoc crypto settings: %d\n", err);
       goto err_assoc;
   }

    /* 4) bss */
    assoc_data->bss = net80211_ref_bss(pdev, bss);

    assoc_data->capability = bss->capability;
    assoc_data->supp_rates = bss->data.supp_rates;
    assoc_data->supp_rates_len = bss->data.supp_rates_len;

    /* configurate smps */
    if (mlme_conf->powersave)
        vif->smps_mode = IEEE80211_SMPS_DYNAMIC;
    else
        vif->smps_mode = IEEE80211_SMPS_NONE;

    sband = net80211_get_sband(pdev, bss->channel->band);
	if (sband == NULL)
		goto err_assoc;

    /* also disable HT/VHT/HE if the AP doesn't use WMM */
    if (!bss->data.wmm_used) {
        mlme_conf->flags |= NET80211_MLME_DISABLE_HT;
        mlme_conf->flags |= NET80211_MLME_DISABLE_VHT;
        mlme_conf->flags |= NET80211_MLME_DISABLE_HE;
        net_dbg("disabling HT/VHT/HE as WMM/QoS is not supported by the AP\n");
    }

    /* re-initialize mlme ht and vht capabilities */
    memcpy(&mlme_conf->ht_capa, &net80211_ht_capa_mod_mask,
        sizeof(mlme_conf->ht_capa));
    memset(&mlme_conf->ht_capa_mask, 0, sizeof(mlme_conf->ht_capa_mask));

    memcpy(&mlme_conf->vht_capa, &net80211_vht_capa_mod_mask,
        sizeof(mlme_conf->vht_capa));
    memset(&mlme_conf->vht_capa_mask, 0, sizeof(mlme_conf->vht_capa_mask));

    /* HT */
    ht_ie = net80211_bss_find_ie(bss, WLAN_EID_HT_OPERATION);
    if (ht_ie && ht_ie[1] >= sizeof(struct ieee80211_ht_operation))
        assoc_data->bss_ht_param =
        ((struct ieee80211_ht_operation *)(ht_ie + 2))->ht_param;
    else if (!is_6ghz)
        mlme_conf->flags |= NET80211_MLME_DISABLE_HT;

    /* VHT */
    vht_ie = net80211_bss_find_ie(bss, WLAN_EID_VHT_CAP);
    if (vht_ie && vht_ie[1] >= sizeof(struct ieee80211_vht_capabilities))
        memcpy(&assoc_data->bss_vht_cap, vht_ie + 2,
            sizeof(struct ieee80211_vht_capabilities));
    else if (!is_6ghz)
        mlme_conf->flags |= NET80211_MLME_DISABLE_VHT;

    if (bss->data.wmm_used && bss->data.uapsd_supported &&
        net80211_vif_drv_conf_get_uapsd(vif)) {
        assoc_data->uapsd = true;
        mlme_conf->flags |= NET80211_MLME_UAPSD_ENABLED;
    }
    else {
        assoc_data->uapsd = false;
        mlme_conf->flags &= ~NET80211_MLME_UAPSD_ENABLED;
    }

    /* MFP disabled by default */
    mlme_conf->flags &= ~NET80211_MLME_MFP_ENABLED;

    if (assoc_data->crypto.mfp & IEEE80211_RSN_CAP_MFP_ENABLED) {
        mlme_conf->flags |= NET80211_MLME_MFP_ENABLED;
    }

    // TODOTODO: Is Radio Resource Managment needed?

    /* kick off associate process */

    /* override HT/VHT configuration only if the AP and we support it */
    if (!(mlme_conf->flags & NET80211_MLME_DISABLE_HT)) {
        struct ieee80211_sta_ht_cap sta_ht_cap;

        memcpy(&sta_ht_cap, &sband->ht_cap, sizeof(sta_ht_cap));
        net80211_vif_apply_htcap_overrides(vif, &sta_ht_cap);

        /* check for 40 MHz disable override */
        if (!(mlme_conf->flags & NET80211_MLME_DISABLE_40MHZ) &&
            sband->ht_cap.cap & IEEE80211_HTCAP_SUP_WIDTH_20_40 &&
            !(sta_ht_cap.cap & IEEE80211_HTCAP_SUP_WIDTH_20_40))
            foverride = true;
    }

    err = net80211_prep_connection(vif, bss, true, foverride);
    if (err)
        goto err_assoc;

    // TODOTODO: Is code for NEED_DTIM_BEFORE_ASSOC needed ?
    // TODOTODO: to support MBSSID

    /* prepare to run again */
    init_delayed_work(&assoc_data->run_again, net80211_sme_timeout, sme);

    err = net80211_sta_assoc_request(vif);
    if (err)
        goto err_assoc;

    if (bss->data.corrupt) {
        net_dbg("associating with AP with corrupt %a\n", 
            bss->ies->from_beacon ? "beacon" : "probe response");
    }

    return;

err_assoc:
    net80211_sme_dispatch(sme, NET80211_SME_EVENT_ABORT, 0, ERR_PTR(err));
}

static void
net80211_sme_state_assoc_exit(void *ctx)
{
    struct net80211_sme *sme = ctx;
    struct net80211_vif *vif = sme->vif;
    struct net80211_pdev *pdev = sme->pdev;
    struct net80211_assoc_data *assoc_data = sme->state_data[sme->state];

    cancel_delayed_work(&assoc_data->run_again);

    if (!assoc_data->assoc) {

        net80211_vif_destroy_sta(vif, assoc_data->bss->bssid);

        net80211_vif_bss_conf_set_bssid(vif, NULL);
        net80211_vif_bss_conf_change_notify(vif);

        sme->conf.flags = 0;

        net80211_vif_release_channel(vif);
    }
    else {
        /* copy the crypto used */
        sme->conn->params.crypto = assoc_data->crypto;
    }

    net80211_put_bss(pdev, assoc_data->bss);

    kfree(assoc_data);
    sme->state_data[sme->state] = NULL;
}

static bool
net80211_sme_state_assoc_event(void *ctx,
    u16 event_type, u16 event_data_len, void *event_data)
{
    struct net80211_sme *sme = ctx;
    struct net80211_assoc_data *assoc_data = sme->state_data[sme->state];
    bool unhandled = false;

    switch (event_type) {
    case NET80211_SME_EVENT_ASSOC_FAIL:
    case NET80211_SME_EVENT_TIMEOUT:
        if (!net80211_sta_assoc_request(sme->vif))
            break;
        /* fall through */
    case NET80211_SME_EVENT_ABORT:
        if (!PTR_ERR(event_data)) {
            /* abortion is not come from ap, deauth firstly. */
            struct net80211_sme_deauth_params params = { 0 };
            params.reason_code = WLAN_REASON_DEAUTH_LEAVING;
            params.stage = NET80211_CONNECT_STAGE_ASSOC;
            memcpy(params.bssid, assoc_data->bss->bssid, sizeof(params.bssid));

            assoc_data->assoc = true;
            net80211_sme_transition_to(sme, NET80211_SME_STATE_DEAUTH, &params);
        }
        else {
            struct net80211_sme_idle_params params = { 0 };
            params.reason = PTR_ERR(event_data);
            params.stage = NET80211_CONNECT_STAGE_ASSOC;
            params.from_ap = true;

            net80211_sme_transition_to(sme, NET80211_SME_STATE_IDLE, &params);
        }
        break;
    case NET80211_SME_EVENT_ASSOC_SUCCESS:
        assoc_data->assoc = true;
        net80211_sme_transition_to(sme, NET80211_SME_STATE_RUN, NULL);
        break;

    case NET80211_SME_EVENT_DEAUTH:
    case NET80211_SME_EVENT_DISASSOC:
        if (1) {
            struct net80211_sme_idle_params params = { 0 };
            params.reason = PTR_ERR(event_data);
            params.stage = NET80211_CONNECT_STAGE_ASSOC;
            params.from_ap = true;

            net80211_sme_transition_to(sme, NET80211_SME_STATE_IDLE, &params);
        }
        break;
    default:
        unhandled = true;
        break;
    }

    return !unhandled;
}

static void
net80211_sme_state_run_entry(void *ctx, void *params)
{
    struct net80211_sme *sme = ctx;
    struct net80211_connect_result cr = { 0 };
    const struct element *ssid_ie;

    if (WARN_ON(!sme->conn))
        return;

    /* notify */
    cr.stage = NET80211_CONNECT_STAGE_RUN;
    cr.want_eapol = sme->conn->params.want_eapol;
    if (sme->conf.associated) {
        cr.status = 0;
        memcpy(cr.bssid, sme->conf.associated->bssid, sizeof(cr.bssid));
        ssid_ie = net80211_bss_find_element(sme->conn->bss, WLAN_EID_SSID);
        if (ssid_ie) {
            cr.ssid_len = ssid_ie->datalen;
            memcpy(cr.ssid, ssid_ie->data, ssid_ie->datalen);
        }
        cr.crypto = sme->conn->params.crypto;
    }
    else {
        cr.status = 1;
    }

    net80211_sta_sme_connect_done(sme->vif, &cr);
    net80211_sme_free(sme);
}

static void
net80211_sme_state_run_exit(void *ctx)
{

}

static bool
net80211_sme_state_run_event(void *ctx,
    u16 event_type, u16 event_data_len, void *event_data)
{
    struct net80211_sme *sme = ctx;
    bool unhandled = false;

    switch (event_type) {
    case NET80211_SME_EVENT_DEAUTH:
    case NET80211_SME_EVENT_DISASSOC:
        if (1) {
            struct net80211_sme_idle_params params = { 0 };
            params.reason = PTR_ERR(event_data);
            params.stage = NET80211_CONNECT_STAGE_RUN;
            params.from_ap = true;
            
            net80211_sme_transition_to(sme, NET80211_SME_STATE_IDLE, &params);
        }
        break;
    case NET80211_SME_EVENT_DISCONNECT_REQUEST:
    case NET80211_SME_EVENT_ABORT:
        if (sme->conf.associated) {
            struct net80211_sme_deauth_params params = { 0 };
            params.reason_code = event_data ? (u16)PTR_ERR(event_data) : WLAN_REASON_DEAUTH_LEAVING;
            params.stage = NET80211_CONNECT_STAGE_RUN;
            memcpy(params.bssid, sme->conf.associated->bssid, sizeof(params.bssid));

            net80211_sme_transition_to(sme, NET80211_SME_STATE_DEAUTH, &params);
        }
        break;
    default:
        unhandled = true;
        break;
    }

    return !unhandled;
}

static void
net80211_sme_state_deauth_entry(void *ctx, void *params)
{
    struct net80211_sme *sme = ctx;
    struct net80211_sme_deauth_params *deauth_params = params;
    struct net80211_deauth_data *deauth_data;
    int err;

    if (!deauth_params) {
        err = -EINVAL;
		goto err_deauth;
    }

    deauth_data = kzalloc(sizeof(*deauth_data), GFP_KERNEL);
    if (!deauth_data) {
		err = -ENOMEM;
        goto err_deauth;
    }

    sme->state_data[sme->state] = deauth_data;

    /* prepare the deauth data */
    memcpy(deauth_data->bssid, deauth_params->bssid, ETH_ALEN);
    deauth_data->reason_code = deauth_params->reason_code;
    deauth_data->stage = deauth_params->stage;

    err = net80211_sta_deauth_request(sme->vif);
    if (err)
        goto err_deauth;

    return;

err_deauth:
    net80211_sme_dispatch(sme, NET80211_SME_EVENT_ABORT, 0, ERR_PTR(err));
}

static void
net80211_sme_state_deauth_exit(void *ctx)
{
    struct net80211_sme *sme = ctx;
    struct net80211_deauth_data *deauth_data;

    deauth_data = sme->state_data[sme->state];

    kfree(deauth_data);
    sme->state_data[sme->state] = NULL;
}

static bool
net80211_sme_state_deauth_event(void *ctx,
    u16 event_type, u16 event_data_len, void *event_data)
{
    struct net80211_sme *sme = ctx;
    bool unhandled = false;

    switch (event_type) {
    case NET80211_SME_EVENT_ABORT:
        net_warn("aborting unexpectedly\n");
        /* fall through */
    case NET80211_SME_EVENT_DEAUTH_CONFIRM:
    case NET80211_SME_EVENT_DEAUTH:
    case NET80211_SME_EVENT_DISASSOC:
        if (1) {
            struct net80211_sme_idle_params params = { 0 };
            params.reason = PTR_ERR(event_data);
            params.stage = NET80211_CONNECT_STAGE_UNSPECIFIED;
            params.from_ap = true;
            net80211_sme_transition_to(sme, NET80211_SME_STATE_IDLE, &params);
        }
        break;
    default:
        unhandled = true;
        break;
    }

    return !unhandled;
}

struct net80211_state_info net80211_sme_state_info[] = {
    [NET80211_SME_STATE_IDLE] = {
        "IDLE",
        net80211_sme_state_idle_entry,
        net80211_sme_state_idle_exit,
        net80211_sme_state_idle_event
    },
    [NET80211_SME_STATE_AUTH] = {
        "AUTH",
        net80211_sme_state_auth_entry,
        net80211_sme_state_auth_exit,
        net80211_sme_state_auth_event
    },
    [NET80211_SME_STATE_ASSOC] = {
        "ASSOC",
        net80211_sme_state_assoc_entry,
        net80211_sme_state_assoc_exit,
        net80211_sme_state_assoc_event
    },
    [NET80211_SME_STATE_RUN] = {
        "RUN",
        net80211_sme_state_run_entry,
        net80211_sme_state_run_exit,
        net80211_sme_state_run_event
    },
    [NET80211_SME_STATE_DEAUTH] = {
        "DEAUTH",
        net80211_sme_state_deauth_entry,
        net80211_sme_state_deauth_exit,
        net80211_sme_state_deauth_event
    },
};

static int
net80211_sme_connect_request(struct net80211_sme *sme)
{
    if (!sme->conn)
        return -EINVAL;

    if (sme->state != NET80211_SME_STATE_IDLE) {
        return -EINPROGRESS;
    }

    net80211_sme_dispatch(sme, 
        NET80211_SME_EVENT_CONNECT_REQUEST, 0, NULL);

    return 0;
}

static int
net80211_sme_disconnect_request(struct net80211_sme *sme, u16 reason)
{
    if (!sme->conf.associated)
        return 0;

    if (sme->state != NET80211_SME_STATE_RUN) {
        return -ENOTCONN;
    }

    net80211_sme_dispatch(sme,
        NET80211_SME_EVENT_DISCONNECT_REQUEST, 0, ERR_PTR(reason));

    return 0;
}

int net80211_sme_wait_idle(struct net80211_sme *sme)
{
	unsigned long time_left;

	time_left = wait_for_completion_timeout(&sme->on_idle, 3000);
	if (!time_left)
		return -ETIMEDOUT;

	return 0;
}

static void
net80211_sme_stop(struct net80211_sme *sme)
{
    net80211_sme_dispatch(sme, NET80211_SME_EVENT_ABORT, 0, ERR_PTR(0));

    net80211_sme_wait_idle(sme);
}

void
net80211_sta_sme_init(struct net80211_vif *vif)
{
    struct net80211_sme *sme;
    struct net80211_mlme_conf *mlme_conf;

    /* Use the below code to get size of struct net80211_sme on compiler time */
    //char(*__kaboom)[sizeof(struct net80211_sme)] = 1;
    BUILD_BUG_ON(sizeof(vif->sme) < sizeof(struct net80211_sme));

    sme = (void *)vif->sme;

    sme->pdev = vif->pdev;
    sme->vif = vif;
    sme->state_info = net80211_sme_state_info;
    sme->event_names = net80211_sme_event_names;
    sme->n_event_names = ARRAY_LENGTH(net80211_sme_event_names);

    /* initialize the mlme configuration */
    mlme_conf = &sme->conf;
    mlme_conf->flags = 0;
    mlme_conf->powersave = 0; /* no power save by default */
    mlme_conf->uapsd_queues = 0;
    mlme_conf->uapsd_max_sp_len = 0;

	/* Default is the Idle state. */
	init_completion(&sme->on_idle);
	complete(&sme->on_idle);
}

void
net80211_sta_sme_exit(struct net80211_vif *vif)
{
}

void
net80211_sta_sme_rx_assoc_resp(struct net80211_vif *vif,
    u16 status_code, bool abort)
{
    struct net80211_sme *sme = (void *)vif->sme;

    if (abort) {
        net80211_sme_dispatch(sme, NET80211_SME_EVENT_ABORT, 0, ERR_PTR(status_code));
        return;
    }

    if (status_code != WLAN_STATUS_SUCCESS) {
        net80211_sme_dispatch(sme, NET80211_SME_EVENT_ASSOC_FAIL, 0, ERR_PTR(status_code));
    }
    else {
        net80211_sme_dispatch(sme, NET80211_SME_EVENT_ASSOC_SUCCESS, 0, ERR_PTR(status_code));
    }
}

static void
net80211_sme_rx_auth(struct net80211_sme *sme, const u8 *buf, u32 len)
{
    struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)buf;
    u16 status_code = le16_to_cpu(mgmt->u.auth.status_code);

    if (!sme->conn)
        return;

    if (status_code == WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG &&
        sme->conn->auto_auth &&
        sme->conn->params.auth_type != NL80211_AUTHTYPE_NETWORK_EAP) {
        switch (sme->conn->params.auth_type) {
        case NL80211_AUTHTYPE_OPEN_SYSTEM:
            sme->conn->params.auth_type =
                NL80211_AUTHTYPE_NETWORK_EAP;
            break;
        case NL80211_AUTHTYPE_SHARED_KEY:
            sme->conn->params.auth_type =
                NL80211_AUTHTYPE_NETWORK_EAP;
            break;
        default:
            sme->conn->params.auth_type =
                NL80211_AUTHTYPE_OPEN_SYSTEM;
            break;
        }
        net80211_sme_dispatch(sme, NET80211_SME_EVENT_AUTH_FAIL, 0, ERR_PTR(-ENOTSUPP));
    }
    else if (status_code != WLAN_STATUS_SUCCESS && status_code != WLAN_STATUS_SAE_HASH_TO_ELEMENT) {
        net80211_sme_dispatch(sme, NET80211_SME_EVENT_ABORT, 0, ERR_PTR(status_code));
    }
    else {
        net80211_sme_dispatch(sme, NET80211_SME_EVENT_AUTH_SUCCESS, 0, NULL);
    }
}

static void
net80211_sme_rx_deauth(struct net80211_sme *sme, const u8 *buf, u32 len)
{
    struct ieee80211_mgmt *mgmt = (void *)buf;
    u16 reason_code = le16_to_cpu(mgmt->u.deauth.reason_code);

    net80211_sme_dispatch(sme, NET80211_SME_EVENT_DEAUTH, 0, ERR_PTR(reason_code));
}

static void
net80211_sme_rx_disassoc(struct net80211_sme *sme, const u8 *buf, u32 len)
{
    struct ieee80211_mgmt *mgmt = (void *)buf;
    u16 reason_code = le16_to_cpu(mgmt->u.disassoc.reason_code);

    net80211_sme_dispatch(sme, NET80211_SME_EVENT_DISASSOC, 0, ERR_PTR(reason_code));
}

static void
net80211_sme_deauth_confirm(struct net80211_sme *sme, const u8 *buf, u32 len)
{
    struct ieee80211_mgmt *mgmt = (void *)buf;
    u16 reason_code = le16_to_cpu(mgmt->u.deauth.reason_code);

    net80211_sme_dispatch(sme, NET80211_SME_EVENT_DEAUTH_CONFIRM, 0, ERR_PTR(reason_code));
}

static void
net80211_sme_disassoc_confirm(struct net80211_sme *sme, const u8 *buf, u32 len)
{
    struct ieee80211_mgmt *mgmt = (void *)buf;
    u16 reason_code = le16_to_cpu(mgmt->u.disassoc.reason_code);

    net80211_sme_dispatch(sme, NET80211_SME_EVENT_DISASSOC_CONFIRM, 0, ERR_PTR(reason_code));
}

struct net80211_mlme_conf *
net80211_sta_get_mlme_conf(struct net80211_vif *vif)
{
    struct net80211_sme *sme = (void *)vif->sme;
    return &sme->conf;
}

struct net80211_auth_data *
net80211_sta_get_auth_data(struct net80211_vif *vif)
{
    struct net80211_sme *sme = (void *)vif->sme;
    return sme->state_data[NET80211_SME_STATE_AUTH];
}

struct net80211_assoc_data *
net80211_sta_get_assoc_data(struct net80211_vif *vif)
{
    struct net80211_sme *sme = (void *)vif->sme;
    return sme->state_data[NET80211_SME_STATE_ASSOC];
}

struct net80211_deauth_data *
net80211_sta_get_deauth_data(struct net80211_vif *vif)
{
    struct net80211_sme *sme = (void *)vif->sme;
    return sme->state_data[NET80211_SME_STATE_DEAUTH];
}

static struct net80211_bss *
net80211_get_conn_bss(struct net80211_pdev *pdev, 
    struct net80211_conn *conn)
{
    struct net80211_bss *bss;

    bss = net80211_get_bss(pdev,
        conn->params.channel,
        conn->params.bssid,
        conn->params.ssid,
        conn->params.ssid_len,
        conn->params.bss_type,
        IEEE80211_PRIVACY(conn->params.privacy));
    if (!bss)
        return NULL;

    memcpy(conn->bssid, bss->bssid, ETH_ALEN);
    conn->params.bssid = conn->bssid;
    conn->params.channel = bss->channel;
    conn->params.want_eapol = net80211_crypto_want_eapol(&conn->params.crypto);
    conn->bss = bss;

    return bss;
}

int net80211_sta_sme_connect(struct net80211_vif *vif, 
    struct net80211_connect_params *connect)
{
    struct net80211_sme *sme = (void *)vif->sme;
    struct net80211_bss *bss;
    int err;

    if (WARN_ON(sme->conf.associated))
        return -EALREADY;

    if (WARN_ON(sme->conn))
        return -EINPROGRESS;

    sme->conn = kzalloc(sizeof(*sme->conn), GFP_KERNEL);
    if (!sme->conn)
        return -ENOMEM;

    /* build connect parameters */
    memcpy(&sme->conn->params, connect, sizeof(*connect));
    if (connect->bssid) {
        sme->conn->params.bssid = sme->conn->bssid;
        memcpy(sme->conn->bssid, connect->bssid, ETH_ALEN);
    }

    sme->conn->params.auth_type = connect->auth_type;
    sme->conn->params.privacy = (connect->crypto.n_ciphers_pairwise > 0);

    /* candiate bss */
    bss = net80211_get_conn_bss(sme->pdev, sme->conn);
    if (!bss) {
        // TODOTODO: TO support scan when cannot find a matching ap?
        net_err("cannot find a matching bss with ssid: %a\n", connect->ssid);
        err = -ENOTSUPP;
        goto done;
    }

    err = net80211_sme_connect_request(sme);

done:
    if (err)
        net80211_sme_free(sme);
    return err;
}

int net80211_sta_sme_disconnect(struct net80211_vif *vif)
{
    return net80211_sme_disconnect_request((void *)vif->sme, 0);
}

void net80211_sta_sme_stop(struct net80211_vif *vif)
{
    net80211_sme_stop((void *)vif->sme);
}

void
net80211_sta_sme_connect_done(struct net80211_vif *vif,
    struct net80211_connect_result *result)
{
    struct net80211_dev_event devt = { 0 };

    /* update the beacon filter */
    net80211_sta_recalc_bcn_filter(vif);

    /* deliver the event */
    devt.type = NET80211_EVENT_CONNECT_COMPLETE;
    devt.vif = vif;

    BUILD_BUG_ON(sizeof(devt.data) < sizeof(*result));
    memcpy(devt.data, result, sizeof(*result));

    net80211_dev_notify(vif->pdev, &devt);
}

void
net80211_sta_sme_send_disconnected(struct net80211_vif *vif,
    struct net80211_disconnect_result *result)
{
    struct net80211_dev_event devt = { 0 };

    /* update the beacon filter */
    net80211_sta_recalc_bcn_filter(vif);

    /* deliver the event */
    devt.type = NET80211_EVENT_DISCONNECT_COMPLETE;
    devt.vif = vif;

    BUILD_BUG_ON(sizeof(devt.data) < sizeof(*result));
    memcpy(devt.data, result, sizeof(*result));

    net80211_dev_notify(vif->pdev, &devt);
}

void
net80211_sta_sme_external_auth_request(struct net80211_vif* vif,
    struct net80211_auth_request_query* query)
{
    struct net80211_dev_event devt = { 0 };

    /* build the event */
    devt.type = NET80211_EVENT_EXTERNAL_AUTH_REQUEST;
    devt.vif = vif;

    BUILD_BUG_ON(sizeof(devt.data) < sizeof(*query));
    memcpy(devt.data, query, sizeof(*query));

    /* query the data */
    net80211_dev_notify(vif->pdev, &devt);
}

void
net80211_sta_sme_external_auth_response(struct net80211_vif* vif,
    struct net80211_auth_response_query* query)
{
    struct net80211_dev_event devt = { 0 };

    /* build the event */
    devt.type = NET80211_EVENT_EXTERNAL_AUTH_RESPONSE;
    devt.vif = vif;

    BUILD_BUG_ON(sizeof(devt.data) < sizeof(*query));
    memcpy(devt.data, query, sizeof(*query));

    /* query the data */
    net80211_dev_notify(vif->pdev, &devt);
}

void
net80211_sta_sme_rx_mgmt(struct net80211_vif *vif, const u8 *buf, u32 len)
{
    struct net80211_sme *sme = (void *)vif->sme;
    struct ieee80211_mgmt *mgmt = (void *)buf;

    if (WARN_ON(len < 2))
        return;

    if (ieee80211_is_auth(mgmt->frame_control))
        net80211_sme_rx_auth(sme, buf, len);
    else if (ieee80211_is_deauth(mgmt->frame_control))
        net80211_sme_rx_deauth(sme, buf, len);
    else if (ieee80211_is_disassoc(mgmt->frame_control))
        net80211_sme_rx_disassoc(sme, buf, len);
}

void net80211_sta_sme_tx_mgmt(struct net80211_vif *vif, const u8 *buf, u32 len)
{
    struct net80211_sme *sme = (void *)vif->sme;
    struct ieee80211_mgmt *mgmt = (void *)buf;

    if (WARN_ON(len < 2))
        return;

    if (ieee80211_is_deauth(mgmt->frame_control))
        net80211_sme_deauth_confirm(sme, buf, len);
    else
        net80211_sme_disassoc_confirm(sme, buf, len);
}

bool
net80211_vif_get_associated(struct net80211_vif *vif)
{
    struct net80211_sme *sme = (void *)vif->sme;

    return (sme->conf.associated != NULL);
}

bool
net80211_vif_get_powersave(struct net80211_vif *vif)
{
    struct net80211_sme *sme = (void *)vif->sme;

    return sme->conf.powersave;
}

void
net80211_vif_connection_loss(struct net80211_vif *vif)
{
    struct net80211_sme *sme = (void *)vif->sme;

    net80211_sme_disconnect_request(sme, 
        WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY);
}

void
net80211_vif_beacon_loss(struct net80211_vif *vif)
{
    net_warn("ignored. wait firmware to trigger connection loss\n");
}

/* becaon filter */
void
net80211_sta_bcn_filter_init(struct net80211_vif *vif)
{
    static const u32 ies_default[] = {
		WLAN_EID_DS_PARAMS,
		WLAN_EID_EDCA_PARAM_SET,
        WLAN_EID_CHANNEL_SWITCH,
        WLAN_EID_QUIET,
        WLAN_EID_ERP_INFO,
        WLAN_EID_QOS,
        WLAN_EID_EXT_CHANSWITCH_ANN,
        WLAN_EID_HT_OPERATION,
    };

    struct net80211_bcn_filter_conf *conf = &vif->bcn_filter_conf;

    conf->ies = ies_default;
    conf->ies_cnt = ARRAY_SIZE(ies_default);
}

static int
net80211_sta_apply_bcn_filter(struct net80211_vif *vif)
{
    struct net80211_bcn_filter_conf *conf = &vif->bcn_filter_conf;
    u8 add = conf->enabled;
    u8 i;

    /* calculate */
    if (add) {
        for (i = 0; i < ARRAY_SIZE(conf->deactivaters); i++) {
            if (conf->deactivaters[i]) {
                add = 0;
                break;
            }
        }
    }

    /* no change */
    if (add == conf->added)
        return 0;

    /* apply new */
    if (add)
        conf->added = (drv_set_bcn_filter(vif->pdev, vif, conf->ies, conf->ies_cnt) == 0);
    else
        conf->added = (bool)drv_set_bcn_filter(vif->pdev, vif, NULL, 0);

    return 0;
}

static void
net80211_sta_deactivate_bcn_filter(struct net80211_vif *vif, 
    void *deactivater, u8 deactivate)
{
    struct net80211_bcn_filter_conf *conf = &vif->bcn_filter_conf;
    u8 i, free = 0xFF, found = 0xFF, updates = 0;

    for (i = 0; i < ARRAY_SIZE(conf->deactivaters); i++) {
        if (free == 0xFF && !conf->deactivaters[i]) {
            free = i;
        }
        else if (conf->deactivaters[i] == deactivater) {
            found = i;
            break;
        }
    }

    do {
        if (found < ARRAY_SIZE(conf->deactivaters)) {
            if (!deactivate) {
                conf->deactivaters[found] = NULL;
                pr_debug("remove deactivater 0x%p\n", deactivater);
                updates++;
            }
            break;
        }

        if (deactivate) {
            if (free < ARRAY_SIZE(conf->deactivaters)) {
                conf->deactivaters[free] = deactivater;
                pr_debug("add deactivater 0x%p\n", deactivater);
                updates++;
            }
            else {
                pr_debug("no free space for deactivater 0x%p\n", deactivater);
            }
        }
    } while (0);

    if (updates) {
        net80211_sta_apply_bcn_filter(vif);
    }
}

int
net80211_sta_recalc_bcn_filter(struct net80211_vif *vif) 
{
    struct net80211_bcn_filter_conf *conf = &vif->bcn_filter_conf;
    bool associated = net80211_vif_get_associated(vif);

    if (conf->enabled == associated)
        return -EALREADY;
    conf->enabled = associated;

    return net80211_sta_apply_bcn_filter(vif);
}

void
net80211_vif_deactivate_beacon_filter(struct net80211_vif *vif, 
    void *deactivater, u8 deactivate)
{
    if (vif->type != NL80211_IFTYPE_STATION)
        return;

    net80211_sta_deactivate_bcn_filter(vif, deactivater, deactivate);
}