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

#ifndef __NET_NET80211_STA_H
#define __NET_NET80211_STA_H

#include <qdf/qbase.h>
#include "net80211_i.h"

static inline u8 *
net80211_sta_addr(struct net80211_sta *sta)
{
    return sta->addr;
}

static inline struct net80211_vif *
net80211_sta_vif(struct net80211_sta *sta)
{
    return sta->vif;
}

static inline bool
net80211_sta_is_uploaded(struct net80211_sta *sta)
{
    return (sta->state > IEEE80211_STA_NOTEXIST);
}

static inline bool
net80211_sta_is_authorized(struct net80211_sta *sta)
{
    return (sta->state == IEEE80211_STA_AUTHORIZED);
}

static inline struct net80211_sta *
net80211_sta_from_priv_data(void *priv)
{
    return container_of(priv, struct net80211_sta, drv_priv);
}

static inline void *
net80211_sta_get_priv_data(struct net80211_sta *sta)
{
    return (void *)sta->drv_priv;
}

static inline u16
net80211_sta_get_aid(struct net80211_sta *sta)
{
    return sta->aid;
}

static inline enum ieee80211_sta_rx_bandwidth
net80211_sta_get_bandwidth(struct net80211_sta *sta)
{
    return sta->bandwidth;
}

static inline u32
net80211_sta_get_supp_rates(struct net80211_sta *sta, enum nl80211_band band)
{
    return sta->supp_rates[band];
}

static inline struct ieee80211_sta_ht_cap *
net80211_sta_get_ht_cap(struct net80211_sta *sta)
{
    return &sta->ht_cap;
}

static inline struct ieee80211_sta_vht_cap *
net80211_sta_get_vht_cap(struct net80211_sta *sta)
{
    return &sta->vht_cap;
}

static inline struct ieee80211_sta_he_cap *
net80211_sta_get_he_cap(struct net80211_sta *sta)
{
    return &sta->he_cap;
}

static inline struct ieee80211_he_6ghz_cap *
net80211_sta_get_6ghz_cap(struct net80211_sta *sta)
{
    return &sta->he_6ghz_cap;
}

static inline u8 
net80211_sta_get_rx_nss(struct net80211_sta *sta)
{
    return sta->rx_nss;
}

static inline enum ieee80211_smps_mode
net80211_sta_get_smps_mode(struct net80211_sta *sta)
{
    return sta->smps_mode;
}

static inline bool
net80211_sta_get_tdls(struct net80211_sta *sta)
{
    return false;
}

static inline bool
net80211_sta_get_wme(struct net80211_sta *sta)
{
    return sta->wme;
}

static inline u8
net80211_sta_get_uapsd_queues(struct net80211_sta *sta)
{
    return sta->uapsd_queues;
}

static inline bool
net80211_sta_get_mfp(struct net80211_sta *sta)
{
    return sta->mfp;
}

static inline u8
net80211_sta_get_max_sp(struct net80211_sta *sta)
{
    return sta->max_sp;
}

static inline struct ieee80211_sta_txpwr *
net80211_sta_get_txpwr(struct net80211_sta *sta)
{
    return &sta->txpwr;
}

static inline u16
net80211_sta_get_max_amsdu_len(struct net80211_sta *sta)
{
    return sta->max_amsdu_len;
}

static inline bool
net80211_sta_set_max_amsdu_len(struct net80211_sta *sta,
    u16 max_amsdu_len)
{
    sta->max_amsdu_len = max_amsdu_len;
    return true;
}

/* helpers */
struct net80211_sta *
net80211_sta_alloc(struct net80211_vif *vif, const u8 *addr);

void
net80211_sta_free(struct net80211_sta *sta);

int
net80211_sta_destroy(struct net80211_sta *sta);

int
net80211_sta_move_state(struct net80211_sta *sta,
    enum ieee80211_sta_state new_state);

int
net80211_sta_add(struct net80211_sta *sta);

void net80211_sta_update_rx_nss(struct net80211_sta *sta);

enum ieee80211_sta_rx_bandwidth
net80211_sta_cur_vht_bw(struct net80211_sta *sta);

enum ieee80211_sta_rx_bandwidth
net80211_sta_cap_rx_bw(struct net80211_sta *sta);

bool
net80211_sta_update_max_bandwidth(struct net80211_sta *sta,
    enum ieee80211_sta_rx_bandwidth max_bw, bool notify);

void
net80211_sta_report_low_ack(struct net80211_sta *sta, 
    u32 num_packets);

/* vif */

struct net80211_sta *
net80211_vif_get_sta(struct net80211_vif *vif, const u8 *addr);

struct net80211_sta *
net80211_vif_find_sta(struct net80211_vif *vif, const u8 *addr);

int
net80211_vif_destroy_sta(struct net80211_vif *vif, const u8 *addr);

int
net80211_vif_flush_stations(struct net80211_vif *vif);

/* pdev */
void net80211_iterate_stations(struct net80211_pdev *pdev,
    void(*iterator)(void *data, struct net80211_sta *sta),
    void *data);

#endif // !__NET_NET80211_STA_H
