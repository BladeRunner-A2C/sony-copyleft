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
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __NET_MAC80211_H
#define __NET_MAC80211_H
#include <net/ieee80211.h>
#include <net/net80211.h>
#include <qdf/qbase.h>
#include <qdf/wait.h>
#include <qdf/pr_debug.h>
#include <net/net80211/net80211_i.h>
#include <net/net80211/vif.h>
#include <net/net80211/sta.h>

struct device;
struct ieee80211_hw;
struct ieee80211_vif;
struct ieee80211_sta;
struct ieee80211_bss_conf;
struct ieee80211_scan_request;
struct ieee80211_tx_control;
struct ieee80211_bss;

/* interface exposed to lower driver */
struct ieee80211_ops {
    void(*ieee80211_tx)(struct ieee80211_hw *hw,
        struct ieee80211_tx_control *control,
        struct sk_buff *skb);
	
	/* Add and remove the interface */
	int(*ieee80211_add_interface)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif);
    void(*ieee80211_remove_interface)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif);
	
	/* Start and stop the Hw */
    int(*ieee80211_start)(struct ieee80211_hw *hw);
    void(*ieee80211_stop)(struct ieee80211_hw *hw);

	/* Configure the Hw */
    int(*ieee80211_config)(struct ieee80211_hw *hw, u32 changed);

	/* Check the BSS info changed */
    void(*ieee80211_bss_info_changed)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif,
        struct ieee80211_bss_conf *info,
        u64 changed);

	/* Set key and set default unicast key */
    int(*ieee80211_set_key)(struct ieee80211_hw *hw, enum ieee80211_key_cmd cmd,
        struct ieee80211_vif *vif, struct ieee80211_sta *sta,
        struct ieee80211_key_conf *key);
    void(*ieee80211_set_default_unicast_key)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif, int idx);

	/* Hw scan and Cancel Hw scan */
    int(*ieee80211_hw_scan)(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
        struct ieee80211_scan_request *req);
    void(*ieee80211_cancel_hw_scan)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif);

	/* Set threshold for frag and rts */
    int(*ieee80211_set_frag_threshold)(struct ieee80211_hw *hw, u32 value);
    int(*ieee80211_set_rts_threshold)(struct ieee80211_hw *hw, u32 value);

	/* Set STA TX Power */
    int(*ieee80211_sta_set_txpwr)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif,
        struct ieee80211_sta *sta);

	/* Update the STA State */
    int(*ieee80211_sta_state)(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
        struct ieee80211_sta *sta,
        enum ieee80211_sta_state old_state,
        enum ieee80211_sta_state new_state);

	/* Update the STA RC */
    void(*ieee80211_sta_rc_update)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif,
        struct ieee80211_sta *sta,
        u32 changed);

	/* Configure the STA TX Parameters */
    int(*ieee80211_conf_tx)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif, u16 ac,
        const struct ieee80211_tx_queue_params *params);

	/* Configure the AMPDU Action */
    int(*ieee80211_ampdu_action)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif,
        struct ieee80211_ampdu_params *params);

	/* Set and Get the antenna */
    int(*ieee80211_set_antenna)(struct ieee80211_hw *hw, u32 tx_ant, u32 rx_ant);
    int(*ieee80211_get_antenna)(struct ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant);

	/* Add, Remove and Change the chan context */
    int(*ieee80211_add_chanctx)(struct ieee80211_hw *hw,
        struct ieee80211_chanctx_conf *ctx);
    void(*ieee80211_remove_chanctx)(struct ieee80211_hw *hw,
        struct ieee80211_chanctx_conf *ctx);
    void(*ieee80211_change_chanctx)(struct ieee80211_hw *hw,
        struct ieee80211_chanctx_conf *ctx,
        u32 changed);

	/* Assign, Unassign and Switch the chan context of the VIF*/
    int(*ieee80211_assign_vif_chanctx)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif,
        struct ieee80211_chanctx_conf *ctx);
    void(*ieee80211_unassign_vif_chanctx)(struct ieee80211_hw *hw,
        struct ieee80211_vif *vif,
        struct ieee80211_chanctx_conf *ctx);
    int(*ieee80211_switch_vif_chanctx)(struct ieee80211_hw *hw,
        struct ieee80211_vif_chanctx_switch *vifs,
        int n_vifs,
        enum ieee80211_chanctx_switch_mode mode);

	/* Set Beacon Filter */
    int(*ieee80211_set_beacon_filter)(struct ieee80211_hw *hw, struct ieee80211_vif *vif, const u32 *ies, u32 ies_cnt);

	/* User define the private Ops cmd */
	int(*ieee80211_priv_command)(struct ieee80211_hw *hw, struct ieee80211_priv_cmd *cmd);
};


static inline struct net80211_pdev *
ieee80211_hw_to_net80211_pdev(struct ieee80211_hw *hw)
{
    return (struct net80211_pdev *)(hw);
}

static inline struct ieee80211_hw *
ieee80211_alloc_hw(size_t priv_data_len, const struct ieee80211_ops *ops)
{
    return (struct ieee80211_hw *)net80211_pdev_alloc(priv_data_len, ops);
}

static inline void
ieee80211_free_hw(struct ieee80211_hw *hw)
{
    net80211_pdev_free(ieee80211_hw_to_net80211_pdev(hw));
}

static inline int
ieee80211_register_hw(struct ieee80211_hw *hw)
{
    return net80211_pdev_register(ieee80211_hw_to_net80211_pdev(hw));
}

static inline void
ieee80211_unregister_hw(struct ieee80211_hw *hw)
{
    net80211_pdev_unregister(ieee80211_hw_to_net80211_pdev(hw));
}

static inline void *
ieee80211_hw_to_priv_data(struct ieee80211_hw *hw)
{
    return net80211_to_priv_data(ieee80211_hw_to_net80211_pdev(hw));
}

static inline void
ieee80211_hw_set_queues(
    struct ieee80211_hw *hw, u16 queues)
{
    net80211_set_hw_queues(
        ieee80211_hw_to_net80211_pdev(hw),
        queues);
}

static inline void
ieee80211_hw_set_vif_data_size(
    struct ieee80211_hw *hw, u16 vif_data_size)
{
    net80211_set_vif_data_size(
        ieee80211_hw_to_net80211_pdev(hw),
        vif_data_size);
}

static inline void
ieee80211_hw_set_sta_data_size(
    struct ieee80211_hw *hw, u16 sta_data_size)
{
    net80211_set_sta_data_size(
        ieee80211_hw_to_net80211_pdev(hw), sta_data_size);
}

static inline void
ieee80211_set_dev(struct ieee80211_hw *hw, struct device *dev)
{
    net80211_set_dev(ieee80211_hw_to_net80211_pdev(hw), dev);
}

static inline void
ieee80211_set_perm_addr(
    struct ieee80211_hw *hw, const u8 *addr)
{
    net80211_set_perm_addr(ieee80211_hw_to_net80211_pdev(hw), addr);
}

static inline void
ieee80211_hw_set_available_chains(
    struct ieee80211_hw *hw, u8 rx_chains, u8 tx_chains)
{
    net80211_set_available_chains(ieee80211_hw_to_net80211_pdev(hw),
        rx_chains, tx_chains);
}

static inline u32
ieee80211_hw_get_rts_threshold(struct ieee80211_hw *hw)
{
    return net80211_get_rts_threshold(ieee80211_hw_to_net80211_pdev(hw));
}

static inline void
ieee80211_hw_set_supported_cipher_suites(struct ieee80211_hw *hw, 
    const u32 *cipher_suites, u32 n_cipher_suites)
{
    net80211_set_supported_cipher_suites(
        ieee80211_hw_to_net80211_pdev(hw),
        cipher_suites, n_cipher_suites);
}

static inline void
ieee80211_hw_set_supported_akm_suites(struct ieee80211_hw *hw, 
    const u32 *akm_suites, u32 n_akm_suites)
{
    net80211_set_supported_akm_suites(
        ieee80211_hw_to_net80211_pdev(hw),
        akm_suites, n_akm_suites);
}

static inline void
ieee80211_hw_set_max_scan_ssids(struct ieee80211_hw *hw, 
    u16 max_scan_ssids)
{
    net80211_set_max_scan_ssids(
        ieee80211_hw_to_net80211_pdev(hw), 
        max_scan_ssids);
}

static inline void
ieee80211_hw_set_max_scan_ie_len(struct ieee80211_hw *hw, 
    u16 max_scan_ie_len)
{
    net80211_set_max_scan_ie_len(
        ieee80211_hw_to_net80211_pdev(hw), 
        max_scan_ie_len);
}

static inline void
ieee80211_hw_set_max_listen_interval(struct ieee80211_hw *hw,
    u16 max_listen_interval)
{
    net80211_set_max_listen_interval(
        ieee80211_hw_to_net80211_pdev(hw), 
        max_listen_interval);
}

static inline u16
ieee80211_hw_get_listen_interval(struct ieee80211_hw *hw)
{
    return net80211_get_listen_interval(ieee80211_hw_to_net80211_pdev(hw));
}

static inline void
ieee80211_hw_set_max_rx_aggregation_subframes(struct ieee80211_hw *hw,
    u16 max_rx_aggregation_subframes)
{
    net80211_set_max_rx_aggregation_subframes(
        ieee80211_hw_to_net80211_pdev(hw),
        max_rx_aggregation_subframes);
}

static inline u16
ieee80211_hw_get_max_rx_aggregation_subframes(struct ieee80211_hw *hw)
{
    return net80211_get_max_rx_aggregation_subframes(
        ieee80211_hw_to_net80211_pdev(hw));
}

static inline u32
ieee80211_hw_get_dynamic_ps_timeout(
    struct ieee80211_hw *hw)
{
    return net80211_get_dynamic_ps_timeout(ieee80211_hw_to_net80211_pdev(hw));
}

static inline struct ieee80211_supported_band **
ieee80211_hw_get_sbands(struct ieee80211_hw *hw)
{
    return net80211_get_sbands(ieee80211_hw_to_net80211_pdev(hw));
}

static inline const struct ieee80211_supported_band *
ieee80211_hw_get_sband(struct ieee80211_hw *hw, enum nl80211_band band)
{
    return net80211_get_sband(ieee80211_hw_to_net80211_pdev(hw), band);
}

static inline void ieee80211_hw_set_sband(
    struct ieee80211_hw *hw,
    enum nl80211_band band, 
    struct ieee80211_supported_band *sband)
{
    net80211_set_sband(ieee80211_hw_to_net80211_pdev(hw), band, sband);
}

static inline const struct ieee80211_regdomain *
ieee80211_hw_get_regdomain(struct ieee80211_hw *hw)
{
    return net80211_regulatory_get_regdomain(ieee80211_hw_to_net80211_pdev(hw));
}

static inline int ieee80211_hw_set_regdomain(struct ieee80211_hw *hw, 
    struct ieee80211_regdomain *regd)
{
    return net80211_regulatory_set_regdomain(ieee80211_hw_to_net80211_pdev(hw), regd);
}

#define ieee80211_hw_check(hw, flg)	\
    net80211_hw_check(ieee80211_hw_to_net80211_pdev(hw), IEEE80211_HW_##flg)
#define ieee80211_hw_set(hw, flg)	\
    net80211_hw_set(ieee80211_hw_to_net80211_pdev(hw), IEEE80211_HW_##flg)

/*utils interfaces*/ 
static inline void
ieee80211_queue_work(struct ieee80211_hw *hw, struct work_struct *work)
{
    net80211_queue_work(ieee80211_hw_to_net80211_pdev(hw), work);
}

static inline void
ieee80211_queue_delayed_work(struct ieee80211_hw *hw,
    struct delayed_work *dwork, u32 delay)
{
    queue_delayed_work(dwork, delay);
}

static inline struct ieee80211_channel *
ieee80211_get_channel(struct ieee80211_hw *hw, u32 freq)
{
    return net80211_get_channel(ieee80211_hw_to_net80211_pdev(hw), freq);
}

static inline void
ieee80211_scan_rx(struct ieee80211_hw *hw, struct sk_buff *skb)
{
    net80211_scan_rx(ieee80211_hw_to_net80211_pdev(hw), skb);
}

static inline void
ieee80211_scan_completed(struct ieee80211_hw *hw, bool aborted)
{
    net80211_scan_completed(ieee80211_hw_to_net80211_pdev(hw), aborted);
}

static inline struct net80211_bss *
ieee80211_bss_to_net80211_bss(struct ieee80211_bss *bss)
{
    return  (struct net80211_bss *)bss;
}

static inline const u8 *
ieee80211_bss_get_ie(struct ieee80211_bss *bss, u8 id)
{
    return (u8 *)net80211_bss_find_element(
        ieee80211_bss_to_net80211_bss(bss), id);
}

static inline const u8 *
ieee80211_bss_find_vendor_ie(struct ieee80211_bss *bss, u32 oui)
{
    return (u8 *)net80211_bss_find_vendor_element(
        ieee80211_bss_to_net80211_bss(bss),
        oui);
}

static inline struct ieee80211_bss *
ieee80211_get_bss(struct ieee80211_hw *hw,
    struct ieee80211_channel *channel,
    const u8 *bssid,
    const u8 *ssid, u32 ssid_len,
    enum ieee80211_bss_type bss_type,
    enum ieee80211_privacy privacy)
{
    return (struct ieee80211_bss *)net80211_get_bss(
        ieee80211_hw_to_net80211_pdev(hw),
        channel, bssid, ssid, ssid_len,
        bss_type, privacy);
}

static inline void
ieee80211_put_bss(struct ieee80211_hw *hw, struct ieee80211_bss *bss)
{
    net80211_put_bss(ieee80211_hw_to_net80211_pdev(hw),
        ieee80211_bss_to_net80211_bss(bss));
}

static inline struct net80211_vif *
ieee80211_vif_to_net80211_vif(struct ieee80211_vif *vif)
{
    return (struct net80211_vif *)(vif);
}

static inline const u8 *
ieee80211_vif_addr(struct ieee80211_vif *vif)
{
    return net80211_vif_addr(ieee80211_vif_to_net80211_vif(vif));
}

static inline void *
ieee80211_vif_get_priv_data(struct ieee80211_vif *vif)
{
    return net80211_vif_get_priv_data(ieee80211_vif_to_net80211_vif(vif));
}

static inline enum nl80211_iftype
ieee80211_vif_type(struct ieee80211_vif *vif)
{
    return net80211_vif_type(ieee80211_vif_to_net80211_vif(vif));
}

static inline void
ieee80211_vif_set_offload_flag(
	struct ieee80211_vif *vif, u32 offload_flag_value)
{
	net80211_set_vif_set_offload_flag(
		ieee80211_vif_to_net80211_vif(vif),
		offload_flag_value);
}

static inline void
ieee80211_vif_drv_conf_set_uapsd(struct ieee80211_vif *vif, bool enable)
{
    net80211_vif_drv_conf_set_uapsd(ieee80211_vif_to_net80211_vif(vif), enable);
}

static inline void
ieee80211_vif_assign_hw_queue(struct ieee80211_vif *vif, u32 vid)
{
    net80211_vif_assign_hw_queue(ieee80211_vif_to_net80211_vif(vif), vid);
}

static inline struct ieee80211_chanctx_conf *
ieee80211_vif_get_chanctx_conf(struct ieee80211_vif *vif)
{
    return net80211_vif_get_chanctx_conf(ieee80211_vif_to_net80211_vif(vif));
}

static inline const u8 *
ieee80211_vif_bss_conf_get_bssid(struct ieee80211_vif *vif)
{
    struct net80211_bss_conf *bss_conf =
        net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
    return net80211_bss_conf_get_bssid(bss_conf);
}

static inline u32
ieee80211_vif_bss_conf_get_basic_rates(struct ieee80211_vif *vif)
{
    struct net80211_bss_conf *bss_conf =
        net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
    return net80211_bss_conf_get_basic_rates(bss_conf);
}

static inline u16
ieee80211_vif_bss_conf_get_beacon_interval(struct ieee80211_vif *vif)
{
    struct net80211_bss_conf *bss_conf =
        net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
    return net80211_bss_conf_get_beacon_interval(bss_conf);
}

static inline u16
ieee80211_vif_bss_conf_get_aid(struct ieee80211_vif *vif)
{
    struct net80211_bss_conf *bss_conf =
        net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
    return net80211_bss_conf_get_aid(bss_conf);
}

static inline u16
ieee80211_vif_bss_conf_get_assoc_capability(struct ieee80211_vif *vif)
{
    struct net80211_bss_conf *bss_conf =
        net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
    return net80211_bss_conf_get_assoc_capability(bss_conf);
}

static inline s32 *
ieee80211_vif_bss_conf_get_mcast_rate(struct ieee80211_vif *vif)
{
    struct net80211_bss_conf *bss_conf =
        net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
    return net80211_bss_conf_get_mcast_rate(bss_conf);
}

static inline int
ieee80211_vif_bss_conf_get_txpower(struct ieee80211_vif *vif)
{
    struct net80211_bss_conf *bss_conf =
        net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
    return net80211_bss_conf_get_txpower(bss_conf);
}

static inline bool
ieee80211_vif_bss_conf_get_he_support(struct ieee80211_vif *vif)
{
    struct net80211_bss_conf *bss_conf =
        net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
    return net80211_bss_conf_get_he_support(bss_conf);
}

static inline void
ieee80211_iterate_interfaces(struct ieee80211_hw *hw, u32 iter_flags,
    void(*iterator)(void *data, const u8 *mac, struct ieee80211_vif *vif),
    void *data)
{
    net80211_iterate_interfaces(
        ieee80211_hw_to_net80211_pdev(hw), 
        iter_flags, 
        (void (*)(void *, const u8*, struct net80211_vif *))iterator, 
        data);
}

static inline void
ieee80211_iterate_active_interfaces(struct ieee80211_hw *hw, u32 iter_flags,
    void(*iterator)(void *data, const u8 *mac,
        struct ieee80211_vif *vif),
    void *data)
{
    ieee80211_iterate_interfaces(hw,
        iter_flags | IEEE80211_VIF_ITER_ACTIVE,
        iterator, data);
}

static inline void
ieee80211_iterate_active_interfaces_atomic(struct ieee80211_hw *hw, u32 iter_flags,
    void(*iterator)(void *data, const u8 *mac,
        struct ieee80211_vif *vif),
    void *data)
{
    ieee80211_iterate_interfaces(hw,
        iter_flags | IEEE80211_VIF_ITER_ACTIVE,
        iterator, data);
}

static inline void
ieee80211_beacon_loss(struct ieee80211_vif *vif)
{
    net80211_vif_beacon_loss(ieee80211_vif_to_net80211_vif(vif));
}

static inline void
ieee80211_connection_loss(struct ieee80211_vif *vif)
{
    net80211_vif_connection_loss(ieee80211_vif_to_net80211_vif(vif));
}

static inline struct net80211_sta *
ieee80211_sta_to_net80211_sta(struct ieee80211_sta *sta)
{
    return (struct net80211_sta *)(sta);
}

static inline struct ieee80211_sta *
ieee80211_sta_from_drv_priv(void *priv)
{
    return (void *)net80211_sta_from_priv_data(priv);
}

static inline void *
ieee80211_sta_get_priv_data(struct ieee80211_sta *sta)
{
    return net80211_sta_get_priv_data(ieee80211_sta_to_net80211_sta(sta));
}

static inline u8 *
ieee80211_sta_addr(struct ieee80211_sta *sta)
{
    return net80211_sta_addr(ieee80211_sta_to_net80211_sta(sta));
}

static inline u16
ieee80211_sta_get_aid(struct ieee80211_sta *sta)
{
    return net80211_sta_get_aid(ieee80211_sta_to_net80211_sta(sta));
}

static inline enum ieee80211_sta_rx_bandwidth
ieee80211_sta_get_bandwidth(struct ieee80211_sta *sta)
{
    return net80211_sta_get_bandwidth(ieee80211_sta_to_net80211_sta(sta));
}

static inline u32
ieee80211_sta_get_supp_rates(
    struct ieee80211_sta *sta, enum nl80211_band band)
{
    return net80211_sta_get_supp_rates(
        ieee80211_sta_to_net80211_sta(sta), band);
}

static inline struct ieee80211_sta_ht_cap *
ieee80211_sta_get_ht_cap(struct ieee80211_sta *sta)
{
    return net80211_sta_get_ht_cap(ieee80211_sta_to_net80211_sta(sta));
}

static inline struct ieee80211_sta_vht_cap *
ieee80211_sta_get_vht_cap(struct ieee80211_sta *sta)
{
    return net80211_sta_get_vht_cap(ieee80211_sta_to_net80211_sta(sta));
}

static inline struct ieee80211_sta_he_cap *
ieee80211_sta_get_he_cap(struct ieee80211_sta *sta)
{
    return net80211_sta_get_he_cap(ieee80211_sta_to_net80211_sta(sta));
}

static inline struct ieee80211_he_6ghz_cap *
ieee80211_sta_get_6ghz_cap(struct ieee80211_sta *sta)
{
    return net80211_sta_get_6ghz_cap(ieee80211_sta_to_net80211_sta(sta));
}

static inline u8
ieee80211_sta_get_rx_nss(struct ieee80211_sta *sta)
{
    return net80211_sta_get_rx_nss(ieee80211_sta_to_net80211_sta(sta));
}

static inline enum ieee80211_smps_mode
ieee80211_sta_get_smps_mode(struct ieee80211_sta *sta)
{
    return net80211_sta_get_smps_mode(ieee80211_sta_to_net80211_sta(sta));
}

static inline bool
ieee80211_sta_get_tdls(struct ieee80211_sta *sta)
{
    return net80211_sta_get_tdls(ieee80211_sta_to_net80211_sta(sta));
}

static inline bool
ieee80211_sta_get_wme(struct ieee80211_sta *sta)
{
    return net80211_sta_get_wme(ieee80211_sta_to_net80211_sta(sta));
}

static inline u8
ieee80211_sta_get_uapsd_queues(struct ieee80211_sta *sta)
{
    return net80211_sta_get_uapsd_queues(ieee80211_sta_to_net80211_sta(sta));
}

static inline u8
ieee80211_sta_get_max_sp(struct ieee80211_sta *sta)
{
    return net80211_sta_get_max_sp(ieee80211_sta_to_net80211_sta(sta));
}

static inline bool
ieee80211_sta_get_mfp(struct ieee80211_sta *sta)
{
    return net80211_sta_get_mfp(ieee80211_sta_to_net80211_sta(sta));
}

static inline struct ieee80211_sta_txpwr *
ieee80211_sta_get_txpwr(struct ieee80211_sta *sta)
{
    return net80211_sta_get_txpwr(ieee80211_sta_to_net80211_sta(sta));
}

static inline void
ieee80211_report_low_ack(struct ieee80211_sta *sta, u32 num_packets)
{
    net80211_sta_report_low_ack(
        ieee80211_sta_to_net80211_sta(sta), num_packets);
}

static inline struct ieee80211_sta *
ieee80211_find_sta(struct ieee80211_vif *vif,
    const u8 *addr)
{
    return (struct ieee80211_sta *)net80211_vif_find_sta(
        ieee80211_vif_to_net80211_vif(vif),
        addr);
}

static inline void
ieee80211_iterate_stations_atomic(struct ieee80211_hw *hw,
    void(*iterator)(void *data, struct ieee80211_sta *sta),
    void *data)
{
    net80211_iterate_stations(
        ieee80211_hw_to_net80211_pdev(hw),
        (void(*)(void *, struct net80211_sta *))iterator,
        data);
}

static inline struct net80211_scan_request *
ieee80211_scanreq_to_net80211_scanreq(struct ieee80211_scan_request *hw_req)
{
    return (struct net80211_scan_request *)(hw_req);
}

static inline u32
ieee80211_scan_request_ies_len(struct ieee80211_scan_request *hw_req)
{
    return net80211_scan_request_ies_len(ieee80211_scanreq_to_net80211_scanreq(hw_req));
}

static inline const u8 *
ieee80211_scan_request_ies(struct ieee80211_scan_request *hw_req)
{
    return net80211_scan_request_ies(ieee80211_scanreq_to_net80211_scanreq(hw_req));
}

static inline u32
ieee80211_scan_request_num_ssids(struct ieee80211_scan_request *hw_req)
{
    return net80211_scan_request_num_ssids(ieee80211_scanreq_to_net80211_scanreq(hw_req));
}

static inline struct ieee80211_ssid *
ieee80211_scan_request_ssids(struct ieee80211_scan_request *hw_req)
{
    return net80211_scan_request_ssids(ieee80211_scanreq_to_net80211_scanreq(hw_req));
}

static inline u32
ieee80211_scan_request_num_channels(struct ieee80211_scan_request *hw_req)
{
    return net80211_scan_request_num_channels(ieee80211_scanreq_to_net80211_scanreq(hw_req));
}

static inline struct ieee80211_channel **
ieee80211_scan_request_channels(struct ieee80211_scan_request *hw_req)
{
    return net80211_scan_request_channels(ieee80211_scanreq_to_net80211_scanreq(hw_req));
}

static inline struct ieee80211_bss_conf*
ieee80211_vif_get_bss_conf(struct ieee80211_vif* vif)
{
    return (struct ieee80211_bss_conf*)net80211_vif_get_bss_conf(ieee80211_vif_to_net80211_vif(vif));
}

static inline struct net80211_bss_conf *
ieee80211_bss_conf_to_net80211_bss_conf(struct ieee80211_bss_conf *bss_conf)
{
    return (struct net80211_bss_conf *)(bss_conf);
}

static inline u8 *
ieee80211_bss_conf_get_bssid(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_bssid(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline u16
ieee80211_bss_conf_get_aid(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_aid(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline bool
ieee80211_bss_conf_get_assoc(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_assoc(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline u16
ieee80211_bss_conf_get_beacon_interval(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_beacon_interval(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline u8
ieee80211_bss_conf_get_dtim_period(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_dtim_period(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline bool
ieee80211_bss_conf_get_twt_requester(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_twt_requester(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline bool
ieee80211_bss_conf_get_twt_responder(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_twt_responder(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline int
ieee80211_bss_conf_get_txpower(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_txpower(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline bool
ieee80211_bss_conf_get_erp_cts_port(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_erp_cts_port(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline bool
ieee80211_bss_conf_get_erp_short_preamble(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_erp_short_preamble(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline bool
ieee80211_bss_conf_get_erp_short_slot(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_erp_short_slot(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline bool
ieee80211_bss_conf_get_powersave(struct ieee80211_bss_conf *bss_conf)
{
    return net80211_bss_conf_get_powersave(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline bool
ieee80211_bss_conf_get_he_support(struct ieee80211_bss_conf* bss_conf)
{
    return net80211_bss_conf_get_he_support(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline void*
ieee80211_bss_conf_get_he_obss_pd(struct ieee80211_bss_conf* bss_conf)
{
    return net80211_bss_conf_get_he_obss_pd(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

static inline void*
ieee80211_bss_conf_get_he_operation(struct ieee80211_bss_conf* bss_conf)
{
    return net80211_bss_conf_get_he_operation(
        ieee80211_bss_conf_to_net80211_bss_conf(bss_conf));
}

/* tx/rx */
static inline void
ieee80211_rx_napi(struct ieee80211_hw *hw, 
    struct ieee80211_sta *sta, struct sk_buff *skb)
{
    net80211_rx_napi(ieee80211_hw_to_net80211_pdev(hw),
        ieee80211_sta_to_net80211_sta(sta), 
        skb);
}

static inline void
ieee80211_rx_8023(struct ieee80211_hw *hw, 
    struct ieee80211_sta *sta, struct sk_buff *skb,
    struct napi_struct *napi)
{
    net80211_rx_8023(ieee80211_hw_to_net80211_pdev(hw),
        ieee80211_sta_to_net80211_sta(sta),
        skb, napi);
}

static inline void
ieee80211_rx(struct ieee80211_hw *hw, struct sk_buff *skb)
{
    net80211_rx_napi(ieee80211_hw_to_net80211_pdev(hw),
        NULL, skb);
}

static inline void
ieee80211_rx_ni(struct ieee80211_hw *hw,
    struct sk_buff *skb)
{
    net80211_rx_napi(ieee80211_hw_to_net80211_pdev(hw),
        NULL, skb);
}

static inline void
ieee80211_free_txskb(struct ieee80211_hw *hw, struct sk_buff *skb)
{
    net80211_dev_free_txskb(ieee80211_hw_to_net80211_pdev(hw), skb);
}

static inline void
ieee80211_tx_status(struct ieee80211_hw *hw,
    struct sk_buff *skb)
{
    net80211_tx_status(ieee80211_hw_to_net80211_pdev(hw), skb);
}

static inline void
ieee80211_tx_status_irqsafe(struct ieee80211_hw *hw,
    struct sk_buff *skb)
{
    net80211_tx_status(ieee80211_hw_to_net80211_pdev(hw), skb);
}

/* +++ crypto null implementation +++ */

struct crypto_shash {
    u8 name[16];
};

static inline void crypto_free_shash(struct crypto_shash *shash) {
    kfree(shash);
}

/* -- crypto null implmentation --- */

#endif // !__NET_MAC80211_H
