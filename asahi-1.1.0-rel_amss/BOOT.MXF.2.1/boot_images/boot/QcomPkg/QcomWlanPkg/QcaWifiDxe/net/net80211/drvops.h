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

#ifndef __NET_NET80211_DRVOPS_H
#define __NET_NET80211_DRVOPS_H

#include <net/mac80211.h>
#include "net80211_i.h"

 /* helpers */
static inline struct ieee80211_hw *
net80211_pdev_to_ieee80211_hw(struct net80211_pdev *pdev)
{
    return (void *)pdev;
}

static inline struct ieee80211_vif *
net80211_vif_to_ieee80211_vif(struct net80211_vif *vif)
{
    return (void *)vif;
}

static inline struct ieee80211_sta *
net80211_sta_to_ieee80211_sta(struct net80211_sta *sta)
{
    return (void *)sta;
}

/* interface */
int drv_add_interface(struct net80211_pdev *pdev,
    struct net80211_vif *vif);

void drv_remove_interface(struct net80211_pdev *pdev,
    struct net80211_vif *vif);

int drv_hw_scan(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_scan_request *req);

void drv_cancel_hw_scan(struct net80211_pdev *pdev, struct net80211_vif *vif);

void drv_bss_info_changed(struct net80211_pdev *pdev,
    struct net80211_vif *vif);

int drv_conf_tx(struct net80211_pdev *pdev,
    struct net80211_vif *vif, u16 ac,
    const struct ieee80211_tx_queue_params *params);

int drv_sta_state(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_sta *sta,
    enum ieee80211_sta_state old_state,
    enum ieee80211_sta_state new_state);

int drv_assign_vif_chanctx(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct ieee80211_chanctx *ctx);

void drv_unassign_vif_chanctx(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct ieee80211_chanctx *ctx);

void drv_update_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx,
    u32 changed);

int drv_add_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx);

void drv_remove_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx);

int drv_config(struct net80211_pdev *pdev, u32 changed);

int drv_set_key(struct net80211_pdev *pdev,
    enum ieee80211_key_cmd cmd,
    struct net80211_vif *vif,
    struct net80211_sta *sta,
    struct ieee80211_key_conf *key);

void drv_sta_rc_update(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_sta *sta);

int drv_ampdu_action(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct ieee80211_ampdu_params *params);

int drv_set_bcn_filter(struct net80211_pdev *pdev, struct net80211_vif *vif, const u32 *ies, u32 ies_cnt);

int drv_priv_command(struct net80211_pdev *pdev,
    struct ieee80211_priv_cmd *cmd);

/* inline for optimization */
static inline void
drv_tx(struct net80211_pdev *pdev,
    struct ieee80211_tx_control *control,
    struct sk_buff *skb)
{
    pdev->ops->ieee80211_tx(net80211_pdev_to_ieee80211_hw(pdev),
        control, skb);
}

#endif // !__NET_NET80211_DRVOPS_H