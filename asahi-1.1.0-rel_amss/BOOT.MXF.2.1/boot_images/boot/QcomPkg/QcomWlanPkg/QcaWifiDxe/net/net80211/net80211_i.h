/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 22/9/21   zxue     support beacon filter
 23/7/21   zxue     Disable 6G when supplicant doesnt support WPA3 (SAE or SUITE B)
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __NET_NET80211_I_H
#define __NET_NET80211_I_H

#include <qdf/qbase.h>
#include <qdf/worker.h>
#include <qdf/interrupt.h>
#include <net/ieee80211.h>
#include <net/net80211.h>
#include <net/netdevice.h>

 /* interface exposed for mac80211 */

struct net80211_hw_conf {
    u8 perm_addr[ETH_ALEN];

    u8 available_tx_chains;
    u8 available_rx_chains;

    u16 queues;

    u16 max_tx_aggregation_subframes;
    u16 max_rx_aggregation_subframes;

    s8 max_signal;
	
    u16 max_scan_ssids;
    u16 max_scan_ie_len;

    u16 max_listen_interval;

    u32 rts_threshold;
    u32 dynamic_ps_timeout;

    u32 n_cipher_suites;
    const u32 *cipher_suites;
    u32 n_akm_suites;
    const u32 *akm_suites;

    u16 vif_data_size;
    u16 sta_data_size;
	u16 chanctx_data_size;
};

struct net80211_supported_crypto_settings {
    u32 n_cipher_suites;
    u32 cipher_suites[16];
    u32 n_akm_suites;
    u32 akm_suites[16];
};

struct net80211_pdev {
    struct device *dev;
    struct net80211_hw_conf conf;

    /* supported bands*/
    struct ieee80211_supported_band *sbands[NUM_NL80211_BANDS];
    /* regulatory */
    const struct ieee80211_regdomain *regd;
    const struct ieee80211_ops *ops;

    /* supported crypto settings */
    struct net80211_supported_crypto_settings scrypto;

    /* channel contexts */
    list_entry_t chanctx_list;
	
    /* interfaces */
    bool drv_started;
    u16 drv_interface_added;

    list_entry_t interfaces;
	unsigned long flags[BITS_TO_LONGS(NUM_IEEE80211_HW_FLAGS)];

    /* scan */
	struct net80211_scan_request *scan_req;
	struct net80211_vif *scan_vif;

	list_entry_t bss_list;
    u32 bss_entries;

    /* station list */
    list_entry_t sta_list;

    u8 *drv_priv[0];
};

struct net80211_he_bss_color {
    u8 color;
    bool disabled;
    bool partial;
};

struct net80211_bss_conf {
    u8 bssid[ETH_ALEN];
    u16 beacon_interval;
    u8 dtim_period;
    struct ieee80211_rate *beacon_rate;

    s32 mcast_rate[NUM_NL80211_BANDS];
    u32 basic_rates;

    struct {
        u8 cts_prot : 1;
        u8 short_preamble : 1;
        u8 short_slot : 1;
    } erp;

    struct {
        u8 requester : 1;
        u8 responder : 1;
    } twt;

    struct ieee80211_chan_def chandef;

    bool idle;
    bool assoc;
    u16 aid;
    u16 assoc_capability;
    s32 txpower;
    bool powersave;
    bool qos;

    u16 max_idle_period;
    bool protected_keep_alive;

    /* HE */
    bool he_support;
    struct ieee80211_he_operation he_operation;
    struct ieee80211_he_obss_pd he_obss_pd;
    struct net80211_he_bss_color he_bss_color;
    u8 htc_trig_based_pkt_ext;
    u16 frame_time_rts_th;
    bool multi_sta_back_32bit;
    bool ack_enabled;
    bool uora_exists;
    u8 uora_ocw_range;
};

struct net80211_bcn_filter_conf {
    void *deactivaters[2];
    bool enabled;
    bool added;
    u32  ies_cnt;
    const u32 *ies;
};

struct net80211_key {
    /* references */
    struct net80211_pdev *pdev;
    struct net80211_vif *vif;
    struct net80211_sta *sta;

    /* status */
    u8 uploaded : 1;

    /* configuration */
    struct ieee80211_key_conf conf;
};

struct net80211_vif {
    struct net80211_pdev *pdev;
    enum nl80211_iftype type;

    list_entry_t node;

    u8 name[16];
    u8 addr[ETH_ALEN];

    /* status */
    bool drv_added;
    bool is_running;

    struct {
        u8 supports_uapsd : 1;
    } drv_conf;

	u32 offload_flag;
    /* handle received management packets */
    struct work_struct work;
    struct sk_buff_head skb_queue;

	s32 ap_power_level; /* in dBm */

    /* bss configuration */
    struct net80211_bss_conf bss_conf;
    u32 bss_conf_changed;
    u32 bss_conf_notified;
    
    /* hw queue configuration */
    u8 cab_queue;
	u8 hw_queue[IEEE80211_NUM_OF_ACS];

    /* common configuration */
    u16 sequence_number;
    u8 needed_rx_chains;
    enum ieee80211_smps_mode smps_mode;
    bool only_g_mode;   /* operating in G-only mode */

    /* chanctx */
    struct ieee80211_chanctx_conf *chanctx_conf;
    list_entry_t assigned_chanctx_list;

    /* keys */
    struct net80211_key *ptk_key;
    struct net80211_key *gtk_key;
    struct net80211_key* igtk_key;
	
    /* tx configuration */
    struct ieee80211_tx_queue_params tx_conf[IEEE80211_NUM_OF_ACS];

    /* opaque opamanagment entity */
    u8 sme[256];

	/* beacon filter configuration */
    struct net80211_bcn_filter_conf bcn_filter_conf;

    /* for data path */
    struct net_device dev;

    u8 drv_priv[0];
};

struct net80211_sta_ampdu_mlme {
    /* rx */
    u8 tid_rx_token[IEEE80211_NUM_TIDS];
    unsigned long agg_session_valid[BITS_TO_LONGS(IEEE80211_NUM_TIDS)];
    /* tx */
    /* not supported yet */
};

struct net80211_sta {
    u8 addr[ETH_ALEN];

    list_entry_t node;

    /* references */
    struct net80211_pdev *pdev;
    struct net80211_vif *vif;

    /* status */
    enum ieee80211_sta_state state;
    enum ieee80211_sta_rx_bandwidth cur_max_bandwidth;
    u64 assoc_at;
	u16 tid_seq[IEEE80211_QOS_TID_MASK + 1];

    /* aggregation information */
    struct net80211_sta_ampdu_mlme ampdu_mlme;

    /* info */
    u32 supp_rates[NUM_NL80211_BANDS];
    struct ieee80211_sta_ht_cap ht_cap;
    struct ieee80211_sta_vht_cap vht_cap;
    struct ieee80211_sta_he_cap he_cap;
	struct ieee80211_he_6ghz_cap he_6ghz_cap;
    u16 aid;
    u16 max_rx_aggregation_subframes;
    bool wme;
    u8 uapsd_queues;
    u8 max_sp;
    u8 rx_nss;
    enum ieee80211_sta_rx_bandwidth bandwidth;
    enum ieee80211_smps_mode smps_mode;
    bool mfp;

    u16 max_amsdu_len;
    u16 max_rc_amsdu_len;
    u16 max_tid_amsdu_len[IEEE80211_NUM_TIDS];
    struct ieee80211_sta_txpwr txpwr;

    /* rate control changed*/
    u32 rc_changed;

    u8 drv_priv[0];
};

struct net80211_pdev *net80211_pdev_alloc(
    size_t priv_data_len,
    const struct ieee80211_ops *ops);

void net80211_pdev_free(struct net80211_pdev *pdev);

int net80211_pdev_register(struct net80211_pdev *pdev);
void net80211_pdev_unregister(struct net80211_pdev *pdev);

static inline void *
net80211_to_priv_data(struct net80211_pdev *pdev)
{
    return pdev->drv_priv;
}

static inline void
net80211_set_dev(struct net80211_pdev *pdev,
    struct device *dev)
{
    pdev->dev = dev;
}

static inline void
net80211_set_vif_data_size(struct net80211_pdev *pdev,
    u16 vif_data_size)
{
    pdev->conf.vif_data_size = vif_data_size;
}

static inline u16
net80211_get_vif_data_size(struct net80211_pdev *pdev)
{
    return pdev->conf.vif_data_size;
}

static inline void
net80211_set_sta_data_size(struct net80211_pdev *pdev,
    u16 sta_data_size)
{
    pdev->conf.sta_data_size = sta_data_size;
}

static inline u16
net80211_get_sta_data_size(struct net80211_pdev *pdev)
{
    return pdev->conf.sta_data_size;
}

static inline u16
net80211_get_hw_queues(struct net80211_pdev *pdev)
{
    return pdev->conf.queues;
}

static inline void
net80211_set_hw_queues(
    struct net80211_pdev *pdev, u16 queues)
{
    pdev->conf.queues = queues;
}

static inline void
net80211_set_perm_addr(struct net80211_pdev *pdev, const u8 *addr)
{
    memcpy(pdev->conf.perm_addr, addr, ETH_ALEN);
}

static inline void
net80211_set_available_chains(struct net80211_pdev *pdev,
    u8 rx_chains, u8 tx_chains)
{
    pdev->conf.available_rx_chains = rx_chains;
    pdev->conf.available_tx_chains = tx_chains;
}

static inline void
net80211_set_max_rx_aggregation_subframes(struct net80211_pdev *pdev,
    u16 max_rx_aggregation_subframes)
{
    pdev->conf.max_rx_aggregation_subframes = max_rx_aggregation_subframes;
}

static inline u16
net80211_get_max_rx_aggregation_subframes(struct net80211_pdev *pdev)
{
    return pdev->conf.max_rx_aggregation_subframes;
}

static inline u32
net80211_get_rts_threshold(struct net80211_pdev *pdev)
{
    return pdev->conf.rts_threshold;
}

static inline void
net80211_set_supported_cipher_suites(struct net80211_pdev *pdev,
    const u32 *cipher_suites, u32 n_cipher_suites)
{
    pdev->conf.cipher_suites = cipher_suites;
    pdev->conf.n_cipher_suites = n_cipher_suites;
}

static inline void
net80211_set_supported_akm_suites(struct net80211_pdev *pdev,
    const u32 *akm_suites, u32 n_akm_suites)
{
    pdev->conf.akm_suites = akm_suites;
    pdev->conf.n_akm_suites = n_akm_suites;
}

static inline void
net80211_set_max_scan_ssids(struct net80211_pdev *pdev,
    u16 max_scan_ssids)
{
    pdev->conf.max_scan_ssids = max_scan_ssids;
}

static inline void
net80211_set_max_scan_ie_len(struct net80211_pdev *pdev,
    u16 max_scan_ie_len)
{
    pdev->conf.max_scan_ie_len = max_scan_ie_len;
}

static inline void
net80211_set_max_listen_interval(struct net80211_pdev *pdev,
    u16 max_listen_interval)
{
    pdev->conf.max_listen_interval = max_listen_interval;
}

static inline u16
net80211_get_listen_interval(struct net80211_pdev *pdev)
{
    return pdev->conf.max_listen_interval;
}

static inline u32
net80211_get_dynamic_ps_timeout(struct net80211_pdev *pdev)
{
    return pdev->conf.dynamic_ps_timeout;
}

static inline bool
net80211_pdev_is_started(struct net80211_pdev *pdev)
{
    return pdev->drv_started;
}

static inline struct ieee80211_supported_band **
net80211_get_sbands(struct net80211_pdev *pdev)
{
    return pdev->sbands;
}

static inline struct ieee80211_supported_band *
net80211_get_sband(struct net80211_pdev *pdev, enum nl80211_band band)
{
    if (band >= NUM_NL80211_BANDS)
        return NULL;
    return pdev->sbands[band];
}

static inline void
net80211_set_sband(struct net80211_pdev *pdev,
    enum nl80211_band band, struct ieee80211_supported_band *sband)
{
    pdev->sbands[band] = sband;
}

static inline struct ieee80211_rate *
net80211_get_band_rate(struct net80211_pdev *pdev,
    enum nl80211_band band, u32 index)
{
    struct ieee80211_supported_band *sband = pdev->sbands[band];
    if (index < sband->n_bitrates)
        return &sband->bitrates[index];
    return NULL;
}

u32
net80211_get_band_supp_rates(struct net80211_pdev *pdev,
    enum nl80211_band band);

const struct ieee80211_regdomain *
net80211_regulatory_get_regdomain(struct net80211_pdev *pdev);

int
net80211_regulatory_set_regdomain(struct net80211_pdev *pdev,
    struct ieee80211_regdomain *regd);

static inline bool
net80211_hw_check(struct net80211_pdev *pdev,
    enum ieee80211_hw_flags flag)
{
    return test_bit(flag, pdev->flags);
}

static inline void
net80211_hw_set(struct net80211_pdev *pdev,
    enum ieee80211_hw_flags flag)
{
    set_bit(flag, pdev->flags);
}

bool
net80211_is_sae_suiteb_supported(struct net80211_pdev *pdev);
/*---------------------------*/
/* net80211_pdev helpers */
void net80211_notify_dev_registered(struct net80211_pdev *pdev);
void net80211_notify_dev_unregistered(struct net80211_pdev *pdev);

void net80211_interfaces_init(struct net80211_pdev *pdev);
void net80211_interfaces_remove(struct net80211_pdev *pdev);

void net80211_scan_init(struct net80211_pdev *pdev);
void net80211_scan_remove(struct net80211_pdev *pdev);

void net80211_stations_init(struct net80211_pdev *pdev);
void net80211_stations_remove(struct net80211_pdev *pdev);

void net80211_chanctx_init(struct net80211_pdev *pdev);
void net80211_chanctx_remove(struct net80211_pdev *pdev);

/*---------------------------*/
/* utils */
const char *
ieee80211_get_reason_code_string(u16 reason_code);

static inline int
ieee80211_chandef_get_shift(struct ieee80211_chan_def *chandef)
{
    if (NL80211_CHAN_WIDTH_5 == chandef->width)
        return 2;
    if (NL80211_CHAN_WIDTH_10 == chandef->width)
        return 1;

    return 0;
}

bool
ieee80211_sband_supports_80mhz(const struct ieee80211_supported_band *sband);

void
ieee80211_get_rates(const struct ieee80211_supported_band *sband,
    u8 *supp_rates, u32 supp_rates_len,
    int shift,
    u32 *rates, u32 *basic_rates,
    bool *have_rate_higher_than_11mbit);

int
ieee802_11_parse_elems(const u8 *start, size_t len,
    struct ieee802_11_elems *elems);

u32
ieee80211_parse_bitrates(struct ieee80211_chan_def *chandef,
    const struct ieee80211_supported_band *sband,
    const u8 *supp_rates, u32 supp_rates_len, u32 *rates);

int
ieee80211_parse_wpa_ie(const u8 *ie, struct net80211_crypto_settings *crypto);
u8*
ieee80211_ie_build_wpa(u8 *pos, struct net80211_crypto_settings *crypto);

int
ieee80211_parse_rsn_ie(const u8 *ie, struct net80211_crypto_settings *crypto);
u8*
ieee80211_ie_build_rsn(u8 *pos, struct net80211_crypto_settings *crypto);

int
ieee80211_parse_rsnxe_ie(const u8 *ie, struct net80211_crypto_settings *crypto);
u8*
ieee80211_ie_build_rsnxe(u8 *pos, struct net80211_crypto_settings *crypto);

u8
ieee80211_get_rx_chains(
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_ht_capabilities *ht_cap,
    const struct ieee80211_vht_capabilities *vht_cap);

u8 *ieee80211_add_wmm_info_ie(u8 *buf, u8 qosinfo);

u8 ieee80211_ac_to_qos_mask(u8 ac);

int net80211_vif_build_preq_ies(struct net80211_vif* vif,
    u8* buffer,
    u32 buffer_len,
    struct net80211_scan_ies* ie_desc,
    const u8* ie, u32 ie_len,
    u8 bands_used, u32* rate_masks,
    struct ieee80211_chan_def* chandef,
    u32 flags);

/* ht */
u8 ieee80211_mcs_info_get_chains(const struct ieee80211_mcs_info *mcs);

u8 *ieee80211_ie_build_ht_cap(u8 *pos, 
    const struct ieee80211_sta_ht_cap *sta_ht_cap, u16 cap);

void net80211_vif_apply_htcap_overrides(
    struct net80211_vif *vif,
    struct ieee80211_sta_ht_cap *sta_ht_cap);

bool
net80211_vif_ht_cap_to_sta_ht_cap(struct net80211_vif *vif,
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_ht_capabilities *ht_cap,
    struct net80211_sta *sta);

/* vht */
u8 ieee80211_vht_mcs_info_get_nss(const struct ieee80211_vht_mcs_info *mcs);

u8 *ieee80211_ie_build_vht_cap(u8 *pos, 
    const struct ieee80211_sta_vht_cap *sta_vht_cap, u32 cap);

void
net80211_vif_apply_vhtcap_overrides(struct net80211_vif *vif,
    struct ieee80211_sta_vht_cap *sta_vht_cap);

void
net80211_vif_vht_cap_to_sta_vht_cap(struct net80211_vif *vif,
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_vht_capabilities *vht_cap,
    struct net80211_sta *sta);

/* he */
bool net80211_chandef_he_6ghz_oper(struct net80211_vif *vif,
    const struct ieee80211_he_operation *he_oper,
    struct ieee80211_chan_def *chandef);

u8 *ieee80211_ie_build_he_cap(u8 *pos,
    const struct ieee80211_sta_he_cap *sta_he_cap, u8 *end);

u8 *ieee80211_ie_build_he_6ghz_cap(u8 *pos, __le16 cap, u8 *end);

void net80211_vif_build_he_6ghz_cap(struct net80211_vif *vif,
    struct sk_buff *skb);

bool
net80211_verify_sta_he_mcs_support(
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_he_operation *he_operation);

void
net80211_vif_he_cap_ie_to_sta_he_cap(struct net80211_vif *vif,
    const struct ieee80211_supported_band *sband,
    const u8 *he_cap_ie, u8 he_cap_len,
    const struct ieee80211_he_6ghz_cap *he_6ghz_cap,
    struct net80211_sta *sta);

void
net80211_vif_he_spr_ie_to_bss_conf(struct net80211_vif* vif,
    const struct ieee80211_he_spr* he_spr_ie_elem);

void
net80211_vif_he_op_ie_to_bss_conf(struct net80211_vif* vif,
    const struct ieee80211_he_operation* he_op_ie_elem);

/* pdev */
void
net80211_queue_work(struct net80211_pdev *pdev, struct work_struct *work);

/*---------------------------*/
/* struct net80211_scan_request */
static inline u32
net80211_scan_request_ies_len(struct net80211_scan_request *scan_req)
{
    return scan_req->ie_len;
}

static inline const u8 *
net80211_scan_request_ies(struct net80211_scan_request *scan_req)
{
    return scan_req->ie;
}

static inline u32
net80211_scan_request_num_ssids(struct net80211_scan_request *scan_req)
{
    return scan_req->n_ssids;
}

static inline struct ieee80211_ssid *
net80211_scan_request_ssids(struct net80211_scan_request *scan_req)
{
    return scan_req->ssids;
}

static inline u32
net80211_scan_request_num_channels(struct net80211_scan_request *scan_req)
{
    return scan_req->n_channels;
}

static inline struct ieee80211_channel **
net80211_scan_request_channels(struct net80211_scan_request *scan_req)
{
    return scan_req->channels;
}

/*---------------------------*/
/* scan helpers */
void net80211_scan_rx(struct net80211_pdev *pdev, struct sk_buff *skb);
void net80211_scan_completed(struct net80211_pdev *pdev, bool aborted);
void net80211_scan_cancel(struct net80211_pdev *pdev);

/* struct net80211_bss */
struct net80211_bss *net80211_get_bss(struct net80211_pdev *pdev,
    struct ieee80211_channel *channel,
    const u8 *bssid,
    const u8 *ssid, u32 ssid_len,
    enum ieee80211_bss_type bss_type,
    enum ieee80211_privacy privacy);

struct net80211_bss *net80211_ref_bss(struct net80211_pdev *pdev, struct net80211_bss *pub);
void net80211_put_bss(struct net80211_pdev *pdev, struct net80211_bss *pub);

bool
net80211_bss_get_dtim(struct net80211_bss *bss,
    u8 *dtim_count, u8 *dtim_period);

/* power level not configured */
#define NET80211_UNSET_POWER_LEVEL	INT_MIN

/* key */
int net80211_vif_add_key(struct net80211_vif *vif, struct net80211_key_set *key);
int net80211_vif_del_key(struct net80211_vif *vif, const u8 *mac_addr);

/* tx/rx */
void net80211_rx_napi(struct net80211_pdev *pdev,
    struct net80211_sta *sta,
    struct sk_buff *skb);

void net80211_rx_8023(struct net80211_pdev *pdev,
    struct net80211_sta *sta,
    struct sk_buff *skb, struct napi_struct *napi);

void net80211_tx_skb_tid(struct net80211_vif *vif,
    struct sk_buff *skb, int tid);

static inline void
net80211_tx_skb(struct net80211_vif *vif,
    struct sk_buff *skb)
{
    /* Set TID to 7 for managment packets. */
    net80211_tx_skb_tid(vif, skb, 7);
}

void net80211_dev_free_txskb(struct net80211_pdev *pdev,
    struct sk_buff *skb);

void net80211_tx_status(struct net80211_pdev *pdev,
    struct sk_buff *skb);


#endif // !__NET_NET80211_I_H
