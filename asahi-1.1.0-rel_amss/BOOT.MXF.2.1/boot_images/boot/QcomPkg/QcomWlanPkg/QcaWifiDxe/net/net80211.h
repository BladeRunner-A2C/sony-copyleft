/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 28/7/21   zxue     update the connection error code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __NET_NET_80211_H
#define __NET_NET_80211_H

#include <net/nl80211.h>
#include <net/ieee80211.h>
#include <net/ether.h>
#include <net/netdevice.h>

#define NET80211_MAX_NR_CIPHER_SUITES       5
#define NET80211_MAX_NR_AKM_SUITES          2

#define NET80211_MAX_CHAINS	4
#define NET80211_WLAN_SCAN_MAX_IE_LEN  512

enum net80211_event_type {
    NET80211_EVENT_INVALID,
    NET80211_EVENT_EXTERNAL_AUTH_REQUEST,
    NET80211_EVENT_EXTERNAL_AUTH_RESPONSE,
    NET80211_EVENT_SCAN_COMPLETE,
    NET80211_EVENT_CONNECT_COMPLETE,
    NET80211_EVENT_DISCONNECT_COMPLETE
};

struct net80211_dev_event {
    enum net80211_event_type type;
    struct net80211_vif *vif;
    u8 data[128];
    u32 data_len;
};

struct net80211_pdev;

struct net80211_notifier {
    void *ctx;
    void(*dev_registered)(struct net80211_pdev *pdev, void *ctx);
    void(*dev_unregistered)(struct net80211_pdev *pdev, void *ctx);
    void(*dev_notify)(struct net80211_pdev *pdev, struct net80211_dev_event *devt, void *ctx);
};

struct net80211_crypto_settings {
    u16 wpa_type;
    u16 wpa_versions;
    u32 cipher_group;
    u16 n_ciphers_pairwise;
    u32 ciphers_pairwise[NET80211_MAX_NR_CIPHER_SUITES];
    u16 n_akm_suites;
    u32 akm_suites[NET80211_MAX_NR_AKM_SUITES];
    u8 mfp;
    u32 group_mgmt_cipher_suite;
    /* rsn extension capability */
    u8 rsnxe_cap;
};

/**
 * enum net80211_bss_scan_width - control channel width for a BSS
 * 20 MHz wide or compatible / control channel is 10 MHz wide / control channel is 5 MHz wide
 */
enum net80211_bss_scan_width {
	NET80211_BSS_CHAN_WIDTH_20,
	NET80211_BSS_CHAN_WIDTH_10,
	NET80211_BSS_CHAN_WIDTH_5,
};

struct net80211_bss {
    /* timestamp in us */
	u64 ts;
    /* channel information */
	struct ieee80211_channel *channel;
	enum net80211_bss_scan_width scan_width;

    /* basic information */
	s8 signal;
	u16 beacon_interval;
	u16 capability;
	u8 bssid[ETH_ALEN];
	u8 chains;
	s8 chain_signal[NET80211_MAX_CHAINS];

    /* elelments */
    const struct net80211_bss_ies *ies;

    /* data used at association time */
    struct {
        u8 erp_value;
        bool wmm_used;
        bool uapsd_supported;

#define IEEE80211_MAX_SUPP_RATES 32
        u8 supp_rates[IEEE80211_MAX_SUPP_RATES];
        u8 supp_rates_len;
        struct ieee80211_rate *beacon_rate;

        u8 rates_valid : 1;
        u8 wmm_valid : 1;
        u8 erp_valid : 1;

        u8 corrupt;
    } data;

	u8 priv[0];
};

struct net80211_scan_ies {
    const u8* ies[NUM_NL80211_BANDS];
    size_t len[NUM_NL80211_BANDS];
    const u8* common_ies;
    size_t common_ie_len;
};

struct net80211_scan_6ghz_params {
	u32 short_ssid;			/* short ssid to scan for */
	u32 channel_idx;		/* idx of the channel in the channel array in the scan request which the above info relvant to*/
	u8 bssid[ETH_ALEN];
	bool unsolicited_probe; /* the AP transmits unsolicited probe response every 20 TU */
	bool short_ssid_valid;  /* short_ssid is valid and can be used */
	bool psc_no_listen;		/* when set, and the channel is a PSC channel, no need to wait 20 TUs before starting to send probe requests.*/
};

struct net80211_scan_request {
    struct ieee80211_ssid *ssids;
    u32 n_ssids;
    u32 n_channels;
    enum net80211_bss_scan_width scan_width;
    u16 duration;
    bool duration_mandatory;
    u32 flags;
    u32 rates[NUM_NL80211_BANDS];
    u8 bssid[ETH_ALEN];
    enum nl80211_band scan_band;

    /* scan ies */
    struct net80211_scan_ies scan_ies;
    u8 ie[NET80211_WLAN_SCAN_MAX_IE_LEN];
    u32 ie_len;

    /* target */
    struct net80211_vif *vif;

    bool scan_6ghz;
	u32 n_6ghz_params;
	struct net80211_scan_6ghz_params *scan_6ghz_params;
	
    /* keep last */
    struct ieee80211_channel *channels[0];
};

struct net80211_connect_params
{
    struct net80211_vif *vif;

    u32 ssid_len;
    u8 ssid[32];
    enum nl80211_auth_type auth_type;
    enum ieee80211_bss_type bss_type;

    struct net80211_crypto_settings crypto;

    struct ieee80211_channel *channel;
    const u8 *bssid;
    bool privacy;
    bool want_eapol;
};

struct net80211_bss_ies {
    bool from_beacon;
    u64 tsf;
    u32 len;
    u8 data[];
};

enum net80211_connect_stage {
    NET80211_CONNECT_STAGE_UNSPECIFIED,
    NET80211_CONNECT_STAGE_SCAN,
    NET80211_CONNECT_STAGE_AUTH,
    NET80211_CONNECT_STAGE_ASSOC,
    NET80211_CONNECT_STAGE_RUN,
};

struct net80211_auth_frame_desc {
    int err;
    u32 data_len;
    u8 data[256];    /* the max size of auth is 256 */
};

struct net80211_auth_request_query {
    struct {
        u8 bssid[ETH_ALEN];
        u8 ssid[IEEE80211_MAX_SSID_LEN];
        u8 ssid_len;
        struct net80211_crypto_settings crypto;
    } ctx;

    struct net80211_auth_frame_desc *desc;
};

struct net80211_auth_response_query {
    struct {
        const void *data;
        u32 data_len;
    } rx;

    struct net80211_auth_frame_desc *desc;
};

struct net80211_connect_result {
    int status;
    u8 bssid[ETH_ALEN];
    u32 reason;
    enum net80211_connect_stage stage;
    u8 ssid_len;
    u8 ssid[32];
    bool want_eapol;
    struct net80211_crypto_settings crypto;
};

struct net80211_disconnect_result {
    u32 reason;
    bool from_ap;
};

struct net80211_scan_result {
    bool aborted;
};

struct net80211_priv_cmd {
    u32 id;
    u32 len;
    u8 data[0];
};

/* Copy from EFI_80211_SUITE_SELECTOR */
struct net80211_suite_selector {
	u8    oui[3];     /* As defined in IEEE 802.11 standard, usually set to 00-0F-AC.*/
	u8    suite_type; /* Suites types, as defined in IEEE 802.11 standard*/
};

#define WLAN_SUITE_SELECTOR(_ss) SUITE_SELECTOR((_ss)->oui[0], (_ss)->oui[1], (_ss)->oui[2], (_ss)->suite_type)

/* Use to get ptk/gtk from supp */
struct net80211_key_set {
	u8 key[64];
	u8 key_len;
	u8 key_id;
	int key_type;
	u8 mac_addr[ETH_ALEN];
	u8 rsc[8];
	u8 rsc_len;
	bool is_authenticator;
	struct net80211_suite_selector cipher_suite;
	u32 direction;
};

int net80211_init(struct net80211_notifier *notifier);
void net80211_deinit(struct net80211_notifier *notifier);

/* utils */
bool net80211_channel_is_psc(const struct ieee80211_channel *chan);

/* device information */
struct ieee80211_channel *net80211_get_channel(struct net80211_pdev *pdev, u32 freq);
u32 net80211_get_scan_channel_num(struct net80211_pdev *pdev);
u32 net80211_get_scan_channels(struct net80211_pdev *pdev, 
    struct ieee80211_channel **channels, u32 nchannels);

int net80211_get_mac_address(struct net80211_pdev *pdev, u8 *mac_address);
void net80211_dev_notify(struct net80211_pdev *pdev, struct net80211_dev_event *devt);

int net80211_set_supplicant_supported_akm_suites(struct net80211_pdev *pdev,
    const struct net80211_suite_selector *akm_suites, u32 n_akm_suites);
int net80211_set_supplicant_supported_cipher_suites(struct net80211_pdev *pdev,
    const struct net80211_suite_selector *cipher_suites, u32 n_cipher_suites);

/* interface api */
struct net80211_vif* net80211_add_interface(struct net80211_pdev *pdev);
int net80211_remove_interface(struct net80211_pdev *pdev, struct net80211_vif *vif);
int net80211_install_key(struct net80211_pdev *pdev,
    struct net80211_vif *vif, struct net80211_key_set *key_set);

/* scan */
int net80211_scan(struct net80211_pdev *pdev, struct net80211_scan_request *request);
void net80211_bss_iterate(struct net80211_pdev *pdev,
    void(*iterate)(struct net80211_pdev *pdev, struct net80211_bss *bss_entry, void *data),
    void *iterate_data);

/* connect */
int net80211_connect(
    struct net80211_pdev *pdev, struct net80211_vif *vif,
    struct net80211_connect_params *request);

int net80211_disconnect(
    struct net80211_pdev *pdev, struct net80211_vif *vif);

/* tx & rx */
int net80211_transmit_pkt(struct net80211_pdev *pdev, 
    struct net80211_vif *vif, struct sk_buff *skb);

struct net_device *net80211_get_data_device(struct net80211_vif *vif);

netdev_tx_t net80211_vif_start_xmit_8023(struct sk_buff *skb,
    struct net_device *dev);

/* priv */
int net80211_priv_command(struct net80211_pdev *pdev, struct net80211_priv_cmd *cmd);


/* struct net80211_bss */
static inline const struct element *
net80211_bss_find_element(struct net80211_bss *bss, u8 eid)
{
    const struct net80211_bss_ies *ies = bss->ies;

    if (!ies)
        return NULL;
    return ieee80211_find_element(ies->data, ies->len, eid);
}

static inline const struct element *
net80211_bss_find_vendor_element(struct net80211_bss *bss, u32 oui)
{
    const struct net80211_bss_ies *ies = bss->ies;

    if (!ies)
        return NULL;
    return ieee80211_find_vendor_element(ies->data, ies->len, oui);
}

static inline const struct element *
net80211_bss_find_extension_element(struct net80211_bss *bss, u8 eeid)
{
    const struct net80211_bss_ies *ies = bss->ies;

    if (!ies)
        return NULL;

    return ieee80211_find_extension_element(ies->data, ies->len, eeid);
}

const struct element *
net80211_bss_find_element(struct net80211_bss *bss, u8 eid);

static inline const u8 *
net80211_bss_find_ie(struct net80211_bss *bss, u8 eid)
{
    return (void *)net80211_bss_find_element(bss, eid);
}

const struct element *
net80211_bss_find_vendor_element(struct net80211_bss *bss, u32 oui);

static inline const u8 *
net80211_bss_find_vendor_ie(struct net80211_bss *bss, u32 oui)
{
    return (void *)net80211_bss_find_vendor_element(bss, oui);
}

const struct element *
net80211_bss_find_extension_element(struct net80211_bss *bss, u8 eeid);

static inline const u8 *
net80211_bss_find_extension_ie(struct net80211_bss *bss, u8 eeid)
{
    return (void *)net80211_bss_find_extension_element(bss, eeid);
}

#endif //!__NET_NET_80211_H

