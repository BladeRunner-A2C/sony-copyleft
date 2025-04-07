/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __NET_NET80211_MLME_H
#define __NET_NET80211_MLME_H

#include <net/net80211.h>
#include "net80211_i.h"

enum net80211_mlme_flags {
    NET80211_MLME_CONTROL_PORT = BIT(2),
    NET80211_MLME_DISABLE_HT = BIT(4),
    NET80211_MLME_MFP_REQUIRED = BIT(5),
    NET80211_MLME_MFP_ENABLED = BIT(6),
    NET80211_MLME_UAPSD_ENABLED = BIT(7),
    NET80211_MLME_RESET_SIGNAL_AVE = BIT(9),
    NET80211_MLME_DISABLE_40MHZ = BIT(10),
    NET80211_MLME_DISABLE_VHT = BIT(11),
    NET80211_MLME_DISABLE_80P80MHZ = BIT(12),
    NET80211_MLME_DISABLE_160MHZ = BIT(13),
    NET80211_MLME_DISABLE_WMM = BIT(14),
    NET80211_MLME_ENABLE_RRM = BIT(15),
    NET80211_MLME_DISABLE_HE = BIT(16),
};

struct net80211_mlme_conf {
    u32 flags;

    bool powersave;
    u8 uapsd_queues;
    unsigned int uapsd_max_sp_len;

    int wmm_param_last_set;
    int mu_edca_param_last_set;

    struct ieee80211_ht_capabilities ht_capa;
    struct ieee80211_ht_capabilities ht_capa_mask;
    struct ieee80211_vht_capabilities vht_capa;
    struct ieee80211_vht_capabilities vht_capa_mask;

    struct net80211_bss *associated;
};

struct net80211_auth_data {
    struct net80211_bss *bss;

    u16 algorithm;
    u16 expected_transaction;

    u8 key[WLAN_KEY_LEN_WEP104];
    u8 key_len, key_idx;

    bool done;
    u16 sae_trans, sae_status;

    u8 ssid[IEEE80211_MAX_SSID_LEN];
    u8 ssid_len;
    struct net80211_crypto_settings crypto;

    u16 tries;
    bool assoc;
    struct delayed_work run_again;

    u32 data_len;
    u8 data[];
};

struct net80211_assoc_data {
    struct net80211_bss *bss;
    const u8 *supp_rates;

    u16 capability;
    u8 prev_bssid[ETH_ALEN];
    u8 ssid[IEEE80211_MAX_SSID_LEN];
    u8 ssid_len;
    u8 supp_rates_len;
    bool wmm;
    bool uapsd;

    u8 bss_ht_param;
    struct ieee80211_vht_capabilities bss_vht_cap;

    struct net80211_crypto_settings crypto;

    u16 tries;
    bool assoc;
    struct delayed_work run_again;

    u32 ie_len;
    u8 ie[];
};

struct net80211_deauth_data {
    u8 bssid[ETH_ALEN];
    u16 reason_code;
    enum net80211_connect_stage stage;
};

struct net80211_mlme_conf *
net80211_sta_get_mlme_conf(struct net80211_vif *vif);

struct net80211_auth_data *
net80211_sta_get_auth_data(struct net80211_vif *vif);

struct net80211_assoc_data *
net80211_sta_get_assoc_data(struct net80211_vif *vif);

struct net80211_deauth_data *
net80211_sta_get_deauth_data(struct net80211_vif *vif);

/* helpers */
static inline u16
ieee80211_auth_type_to_auth_algorithm(enum nl80211_auth_type auth_type)
{
    u16 auth_algorithm = WLAN_AUTH_MODE_OPEN;

    switch (auth_type) {
    case NL80211_AUTHTYPE_OPEN_SYSTEM:
        auth_algorithm = WLAN_AUTH_MODE_OPEN;
        break;
    case NL80211_AUTHTYPE_SHARED_KEY:
        auth_algorithm = WLAN_AUTH_MODE_SHARED_KEY;
        break;
    case NL80211_AUTHTYPE_FT:
        auth_algorithm = WLAN_AUTH_MODE_FT;
        break;
    case NL80211_AUTHTYPE_NETWORK_EAP:
        auth_algorithm = WLAN_AUTH_MODE_LEAP;
        break;
    case NL80211_AUTHTYPE_SAE:
        auth_algorithm = WLAN_AUTH_MODE_SAE;
        break;
    case NL80211_AUTHTYPE_FILS_SK:
        auth_algorithm = WLAN_AUTH_MODE_FILS_SK;
        break;
    case NL80211_AUTHTYPE_FILS_SK_PFS:
        auth_algorithm = WLAN_AUTH_MODE_FILS_SK_PFS;
        break;
    case NL80211_AUTHTYPE_FILS_PK:
        auth_algorithm = WLAN_AUTH_MODE_FILS_PK;
        break;
    default:
        break;
    }

    return auth_algorithm;
}

int
net80211_prep_connection(struct net80211_vif *vif,
    struct net80211_bss *bss, bool assoc,
    bool foverride);

/* public - TX */
int
net80211_sta_auth_request(struct net80211_vif *vif);

int
net80211_sta_assoc_request(struct net80211_vif *vif);

int
net80211_sta_deauth_request(struct net80211_vif *vif);


/* public RX */
bool
net80211_process_action_back(struct net80211_pdev *pdev,
    struct net80211_sta *sta,
    struct ieee80211_mgmt *mgmt, u32 len);

void
net80211_sta_rx_mgmt(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt, u32 len,
    struct ieee80211_rx_status *rx_status);

#endif // !__NET_NET80211_MLME_H