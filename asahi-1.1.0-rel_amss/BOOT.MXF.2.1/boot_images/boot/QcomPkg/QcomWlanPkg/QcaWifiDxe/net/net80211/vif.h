/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
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

#ifndef __NET_NET80211_VIF_H
#define __NET_NET80211_VIF_H

#include <qdf/qbase.h>
#include "net80211_i.h"

static inline const u8 *
net80211_vif_addr(struct net80211_vif *vif)
{
    return vif->addr;
}

static inline enum nl80211_iftype
net80211_vif_type(struct net80211_vif *vif)
{
    return vif->type;
}

static inline void
net80211_set_vif_set_offload_flag(struct net80211_vif *vif, u32 flag)
{
    vif->offload_flag |= flag;
}

static inline void *
net80211_vif_get_priv_data(struct net80211_vif *vif)
{
    return vif->drv_priv;
}

static inline const u8 *
net80211_vif_get_bssid(struct net80211_vif *vif)
{
    return vif->bss_conf.bssid;
}

static inline void
net80211_vif_drv_conf_set_uapsd(struct net80211_vif *vif, bool enable)
{
    vif->drv_conf.supports_uapsd = enable;
}

static inline bool
net80211_vif_drv_conf_get_uapsd(struct net80211_vif *vif)
{
    return vif->drv_conf.supports_uapsd;
}

static inline void net80211_vif_assign_hw_queue(struct net80211_vif *vif, u32 vid)
{
    u32 i;

    vif->cab_queue = vid % (IEEE80211_NUM_OF_ACS - 1);

    for (i = 0; i < IEEE80211_NUM_OF_ACS; i++) {
        vif->hw_queue[i] = i % (IEEE80211_NUM_OF_ACS - 1);
    }
}

static inline struct net80211_bss_conf *
net80211_vif_get_bss_conf(struct net80211_vif *vif)
{
    return &vif->bss_conf;
}

static inline struct ieee80211_chanctx_conf *
net80211_vif_get_chanctx_conf(struct net80211_vif *vif)
{
    return vif->chanctx_conf;
}

static inline const struct ieee80211_supported_band *
net80211_vif_get_sband(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct ieee80211_chanctx_conf *chanctx_conf;
    enum nl80211_band band;

    chanctx_conf = net80211_vif_get_chanctx_conf(vif);

    if (WARN_ON_ONCE(!chanctx_conf)) {
        return NULL;
    }

    band = chanctx_conf->def.chan->band;

    return net80211_get_sband(pdev, band);
}

static inline void 
net80211_vif_reset_ap_power_level(struct net80211_vif *vif)
{
    vif->ap_power_level = NET80211_UNSET_POWER_LEVEL;
}

/*---------------------------*/
/* interface for vif->bss_conf */
static inline bool
net80211_vif_bss_conf_set_erp_cts_prot(struct net80211_vif *vif, bool cts_prot)
{
    if ((cts_prot == vif->bss_conf.erp.cts_prot) &&
        (vif->bss_conf_notified & BSS_CHANGED_ERP_CTS_PROT))
        return false;
    vif->bss_conf.erp.cts_prot = cts_prot;
    vif->bss_conf_changed |= BSS_CHANGED_ERP_CTS_PROT;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_erp_short_preamble(struct net80211_vif *vif, bool short_preamble)
{
    if ((short_preamble == vif->bss_conf.erp.short_preamble) ||
        (vif->bss_conf_notified & BSS_CHANGED_ERP_PREAMBLE))
        return false;
    vif->bss_conf.erp.short_preamble = short_preamble;
    vif->bss_conf_changed |= BSS_CHANGED_ERP_PREAMBLE;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_erp_short_slot(struct net80211_vif *vif, bool short_slot)
{
    if ((short_slot == vif->bss_conf.erp.short_slot) &&
        (vif->bss_conf_notified & BSS_CHANGED_ERP_SLOT))
        return false;
    vif->bss_conf.erp.short_slot = short_slot;
    vif->bss_conf_changed |= BSS_CHANGED_ERP_SLOT;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_basic_rates(struct net80211_vif *vif, u32 basic_rates)
{
    if ((basic_rates == vif->bss_conf.basic_rates) &&
        (vif->bss_conf_notified & BSS_CHANGED_BASIC_RATES))
        return false;
    vif->bss_conf.basic_rates = basic_rates;
    vif->bss_conf_changed |= BSS_CHANGED_BASIC_RATES;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_bssid(struct net80211_vif *vif, u8 *bssid)
{
    if (bssid) {
        if ((memcmp(vif->bss_conf.bssid, bssid, ETH_ALEN) == 0) &&
            (vif->bss_conf_notified & BSS_CHANGED_BSSID)) {
            return false;
        }
        memcpy(vif->bss_conf.bssid, bssid, ETH_ALEN);
     }   
    else {
        if (is_zero_ether_addr(vif->bss_conf.bssid) &&
            (vif->bss_conf_notified & BSS_CHANGED_BSSID)) {
            return false;
        }
        eth_zero_addr(vif->bss_conf.bssid);
    }
    
    vif->bss_conf_changed |= BSS_CHANGED_BSSID;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_beacon_interval(struct net80211_vif *vif, u16 beacon_interval)
{
    if ((beacon_interval == vif->bss_conf.beacon_interval) &&
        (vif->bss_conf_notified & BSS_CHANGED_BEACON_INT))
        return false;
    vif->bss_conf.beacon_interval = beacon_interval;
    vif->bss_conf_changed |= BSS_CHANGED_BEACON_INT;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_qos(struct net80211_vif *vif, bool enable)
{
    if ((enable == vif->bss_conf.qos) &&
        (vif->bss_conf_notified & BSS_CHANGED_QOS))
        return false;
    vif->bss_conf.qos = enable;
    vif->bss_conf_changed |= BSS_CHANGED_QOS;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_txpower(struct net80211_vif *vif, s32 txpower)
{
    if ((txpower == vif->bss_conf.txpower) &&
        (vif->bss_conf_notified & BSS_CHANGED_TXPOWER))
        return false;
    vif->bss_conf.txpower= txpower;
    vif->bss_conf_changed |= BSS_CHANGED_TXPOWER;
	return true;
}

static inline bool
net80211_vif_bss_conf_set_assoc(struct net80211_vif *vif, bool assoc)
{
    if ((assoc == vif->bss_conf.assoc) &&
        (vif->bss_conf_notified & BSS_CHANGED_ASSOC))
        return false;
    vif->bss_conf.assoc = assoc;
    vif->bss_conf_changed |= BSS_CHANGED_ASSOC;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_dtim_period(struct net80211_vif *vif, u8 dtim_period)
{
    if (dtim_period == 0)
        dtim_period = 1;
    if ((dtim_period == vif->bss_conf.dtim_period) &&
        (vif->bss_conf_notified & BSS_CHANGED_BEACON_INFO))
        return false;
    vif->bss_conf.dtim_period = dtim_period;
    vif->bss_conf_changed |= BSS_CHANGED_BEACON_INFO;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_beacon_rate(struct net80211_vif *vif,
    struct ieee80211_rate *beacon_rate)
{
    vif->bss_conf.beacon_rate = beacon_rate;
    vif->bss_conf_changed |= BSS_CHANGED_BEACON_INFO;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_aid(struct net80211_vif *vif, u16 aid)
{
    vif->bss_conf.aid = aid;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_assoc_capability(struct net80211_vif *vif, u16 assoc_capability)
{
    vif->bss_conf.assoc_capability = assoc_capability;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_powersave(struct net80211_vif *vif, bool powersave)
{
    if ((powersave == vif->bss_conf.powersave) &&
        (vif->bss_conf_notified & BSS_CHANGED_PS))
        return false;
    vif->bss_conf.powersave = powersave;
    vif->bss_conf_changed |= BSS_CHANGED_PS;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_twt_requester(struct net80211_vif *vif, bool twt_requester)
{
    if ((twt_requester == vif->bss_conf.twt.requester) &&
        (vif->bss_conf_notified & BSS_CHANGED_TWT))
        return false;
    vif->bss_conf.twt.requester = twt_requester;
    vif->bss_conf_changed |= BSS_CHANGED_TWT;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_twt_responder(struct net80211_vif *vif, bool twt_responder)
{
    if ((twt_responder == vif->bss_conf.twt.responder) &&
        (vif->bss_conf_notified & BSS_CHANGED_TWT))
        return false;
    vif->bss_conf.twt.responder = twt_responder;
    vif->bss_conf_changed |= BSS_CHANGED_TWT;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_max_idle_period(struct net80211_vif *vif, u16 max_idle_period)
{
    if (max_idle_period == vif->bss_conf.max_idle_period)
        return false;
    vif->bss_conf.max_idle_period = max_idle_period;
    vif->bss_conf_changed |= BSS_CHANGED_KEEP_ALIVE;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_protected_keep_alive(struct net80211_vif *vif, bool protected_keep_alive)
{
    if (protected_keep_alive == vif->bss_conf.protected_keep_alive)
        return false;
    vif->bss_conf.protected_keep_alive = protected_keep_alive;
    vif->bss_conf_changed |= BSS_CHANGED_KEEP_ALIVE;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_he_support(struct net80211_vif *vif, bool he_support)
{
    if (he_support == vif->bss_conf.he_support)
        return false;
    vif->bss_conf.he_support = he_support;
    return true;
}

static inline bool
net80211_vif_bss_conf_set_he_bss_color(struct net80211_vif* vif, u32 he_operation_params)
{

    vif->bss_conf.he_bss_color.color =
        (u8)le32_get_bits(he_operation_params, IEEE80211_HEOP_BSS_COLOR_MASK);

    vif->bss_conf.he_bss_color.partial =
        (bool)le32_get_bits(he_operation_params, IEEE80211_HEOP_PARTIAL_BSS_COLOR);
    vif->bss_conf.he_bss_color.disabled =
        (bool)le32_get_bits(he_operation_params, IEEE80211_HEOP_BSS_COLOR_DISABLED);
    vif->bss_conf_changed |= BSS_CHANGED_HE_BSS_COLOR;

    return true;
}

static inline bool
net80211_vif_bss_conf_set_he_htc_trig_based_pkt_ext(struct net80211_vif* vif, u32 he_operation_params)
{
    vif->bss_conf.htc_trig_based_pkt_ext =
        (u8)u32_get_bits(he_operation_params, IEEE80211_HEOP_DFLT_PE_DURATION_MASK);
    return true;
}

static inline bool
net80211_vif_bss_conf_set_he_frame_time_rts_th(struct net80211_vif* vif, u32 he_operation_params)
{
    vif->bss_conf.frame_time_rts_th =
        (u16)u32_get_bits(he_operation_params, IEEE80211_HEOP_RTS_THRESHOLD_MASK);
    return true;
}

static inline bool
net80211_vif_bss_conf_set_he_multi_sta_back(struct net80211_vif* vif, u32 he_operation_params)
{
    vif->bss_conf.multi_sta_back_32bit =
        (bool)u32_get_bits(he_operation_params, IEEE80211_HEMAC_CAP2_32BIT_BA_BITMAP);
    return true;
}

static inline bool
net80211_vif_bss_conf_set_he_ack_enabled(struct net80211_vif* vif, u32 he_operation_params)
{
    vif->bss_conf.ack_enabled =
        (bool)u32_get_bits(he_operation_params, IEEE80211_HEMAC_CAP2_ACK_EN);
    return true;
}

static inline bool
net80211_vif_bss_conf_set_he_uora_exists(struct net80211_vif* vif, struct ieee802_11_elems* elems)
{

    vif->bss_conf.uora_exists = !!elems->uora_element;
    if (!elems->uora_element)
        return false;
    vif->bss_conf.uora_ocw_range = elems->uora_element[0];
    return true;
}

void net80211_vif_bss_conf_change_notify(struct net80211_vif *vif);

static inline const u8 *
net80211_vif_bss_conf_get_bssid(struct net80211_vif *vif)
{
    return vif->bss_conf.bssid;
}

static inline struct ieee80211_chan_def *
net80211_vif_bss_conf_get_chandef(struct net80211_vif *vif)
{
    return &vif->bss_conf.chandef;
}

static inline u16
net80211_vif_bss_conf_get_assoc_capability(struct net80211_vif *vif)
{
    return vif->bss_conf.assoc_capability;
}

static inline bool
net80211_vif_bss_conf_get_powersave(struct net80211_vif *vif)
{
    return vif->bss_conf.powersave;
}

static inline bool
net80211_vif_bss_conf_get_he_support(struct net80211_vif *vif)
{
    return vif->bss_conf.he_support;
}

/* net80211_bss_conf */

static inline u8 *
net80211_bss_conf_get_bssid(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->bssid;
}

static inline u16
net80211_bss_conf_get_aid(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->aid;
}

static inline u16
net80211_bss_conf_get_beacon_interval(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->beacon_interval;
}

static inline u8
net80211_bss_conf_get_dtim_period(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->dtim_period;
}

static inline bool
net80211_bss_conf_get_twt_requester(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->twt.requester;
}

static inline bool
net80211_bss_conf_get_twt_responder(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->twt.responder;
}

static inline int
net80211_bss_conf_get_txpower(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->txpower;
}

static inline bool
net80211_bss_conf_get_erp_cts_port(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->erp.cts_prot;
}

static inline bool
net80211_bss_conf_get_erp_short_preamble(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->erp.short_preamble;
}

static inline bool
net80211_bss_conf_get_erp_short_slot(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->erp.short_slot;
}

static inline bool
net80211_bss_conf_get_powersave(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->powersave;
}

static inline bool
net80211_bss_conf_get_he_support(struct net80211_bss_conf* bss_conf)
{
    return bss_conf->he_support;
}

static inline void*
net80211_bss_conf_get_he_obss_pd(struct net80211_bss_conf* bss_conf)
{
    return &bss_conf->he_obss_pd;
}

static inline void*
net80211_bss_conf_get_he_operation(struct net80211_bss_conf* bss_conf)
{
    return &bss_conf->he_operation;
}

static inline void*
net80211_bss_conf_get_he_bss_color_color(struct net80211_bss_conf* bss_conf)
{
    return &bss_conf->he_bss_color.color;
}

static inline void*
net80211_bss_conf_get_he_bss_color_partial(struct net80211_bss_conf* bss_conf)
{
    return &bss_conf->he_bss_color.partial;
}

static inline void*
net80211_bss_conf_get_he_bss_color_disabled(struct net80211_bss_conf* bss_conf)
{
    return &bss_conf->he_bss_color.disabled;
}

static inline s32 *
net80211_bss_conf_get_mcast_rate(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->mcast_rate;
}

static inline u32
net80211_bss_conf_get_basic_rates(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->basic_rates;
}

static inline u16
net80211_bss_conf_get_assoc_capability(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->assoc_capability;
}

static inline bool
net80211_bss_conf_get_assoc(struct net80211_bss_conf *bss_conf)
{
    return bss_conf->assoc;
}

static inline struct ieee80211_chan_def *
net80211_bss_conf_get_chandef(struct net80211_bss_conf *bss_conf)
{
    return &bss_conf->chandef;
}

/* helpers */
void
net80211_iterate_interfaces(
    struct net80211_pdev *pdev, u32 iter_flags,
    void(*iterator)(void *data, const u8 *mac, struct net80211_vif *vif),
    void *data);

/* utils */
void
net80211_vif_set_wmm_default(struct net80211_vif *vif, 
    bool bss_notify, bool enable_qos);

bool
net80211_vif_set_wmm_params(
    struct net80211_vif *vif,
    const u8 *wmm_param, u8 wmm_param_len,
    const struct ieee80211_he_mu_edca_param_set *mu_edca);

bool
net80211_vif_get_associated(struct net80211_vif *vif);

bool
net80211_vif_get_powersave(struct net80211_vif *vif);

void
net80211_vif_recalc_smps(struct net80211_vif *vif);

void
net80211_vif_recalc_powersave(struct net80211_vif *vif);

void
net80211_vif_beacon_loss(struct net80211_vif *vif);

void
net80211_vif_connection_loss(struct net80211_vif *vif);

/* beacon filter */
void
net80211_vif_deactivate_beacon_filter(struct net80211_vif *vif,
    void *deactivater, u8 deactivate);

#endif // !__NET_NET80211_VIF_H
