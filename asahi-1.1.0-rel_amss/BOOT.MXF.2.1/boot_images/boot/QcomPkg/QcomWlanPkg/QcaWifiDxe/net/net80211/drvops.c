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

#include <net/ndebug.h>
#include "net80211_i.h"
#include "drvops.h"

/* implementation */

int drv_add_interface(struct net80211_pdev *pdev,
    struct net80211_vif *vif)
{
    int ret;

    if (!pdev->drv_started) {
        ret = pdev->ops->ieee80211_start(
            net80211_pdev_to_ieee80211_hw(pdev));
        if (ret)
            goto err_exit;

        pdev->drv_started = true;
    }

    ret = pdev->ops->ieee80211_add_interface(
        net80211_pdev_to_ieee80211_hw(pdev), 
        net80211_vif_to_ieee80211_vif(vif));
    if (ret)
        goto err_stop;

    vif->drv_added = true;
    pdev->drv_interface_added++;

    return 0;

err_stop:
    if (!pdev->drv_interface_added) {
        pdev->ops->ieee80211_stop(
            net80211_pdev_to_ieee80211_hw(pdev));
        pdev->drv_started = false;
    }
 err_exit:
    return ret;
}

void drv_remove_interface(struct net80211_pdev *pdev,
    struct net80211_vif *vif)
{
    if (!vif->drv_added)
        return;

    pdev->ops->ieee80211_remove_interface(
        net80211_pdev_to_ieee80211_hw(pdev), 
        net80211_vif_to_ieee80211_vif(vif));
    vif->drv_added = false;
    pdev->drv_interface_added--;

    if (!pdev->drv_interface_added) {
        pdev->ops->ieee80211_stop(
            net80211_pdev_to_ieee80211_hw(pdev));
        pdev->drv_started = false;
    }
}

int drv_hw_scan(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_scan_request *req)
{
    return pdev->ops->ieee80211_hw_scan(
		net80211_pdev_to_ieee80211_hw(pdev), 
        net80211_vif_to_ieee80211_vif(vif), 
        (struct ieee80211_scan_request *)req);
}

void drv_cancel_hw_scan(struct net80211_pdev *pdev,
    struct net80211_vif *vif)
{
    pdev->ops->ieee80211_cancel_hw_scan(
        net80211_pdev_to_ieee80211_hw(pdev), 
        net80211_vif_to_ieee80211_vif(vif));
}

void drv_bss_info_changed(struct net80211_pdev *pdev,
    struct net80211_vif *vif)
{
    if (!pdev->ops->ieee80211_bss_info_changed)
        return;

    if (!vif->drv_added)
        return;

    if (!vif->bss_conf_changed)
        return;

    pdev->ops->ieee80211_bss_info_changed(
        net80211_pdev_to_ieee80211_hw(pdev),
        net80211_vif_to_ieee80211_vif(vif),
        (struct ieee80211_bss_conf *)&vif->bss_conf,
        vif->bss_conf_changed);
    vif->bss_conf_notified |= vif->bss_conf_changed;
    vif->bss_conf_changed = 0;
}

int drv_conf_tx(struct net80211_pdev *pdev,
    struct net80211_vif *vif, u16 ac,
    const struct ieee80211_tx_queue_params *params)
{
    if (!pdev->ops->ieee80211_conf_tx)
        return -EOPNOTSUPP;

    if (!vif->drv_added)
        return -EIO;

    if (params->cw_min == 0 || params->cw_min > params->cw_max)
        return -EINVAL;

     return pdev->ops->ieee80211_conf_tx(
         net80211_pdev_to_ieee80211_hw(pdev), 
         net80211_vif_to_ieee80211_vif(vif),
         ac, params);
}

int drv_sta_state(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_sta *sta,
    enum ieee80211_sta_state old_state,
    enum ieee80211_sta_state new_state)
{
    int ret = 0;

    if (pdev->ops->ieee80211_sta_state) {
        ret = pdev->ops->ieee80211_sta_state(
			net80211_pdev_to_ieee80211_hw(pdev), 
			net80211_vif_to_ieee80211_vif(vif), 
			net80211_sta_to_ieee80211_sta(sta),
            old_state, new_state);
    }
    return ret;
}

int drv_assign_vif_chanctx(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct ieee80211_chanctx *ctx)
{
    int ret = 0;

    if (!vif->drv_added)
        return -EIO;

    if (pdev->ops->ieee80211_assign_vif_chanctx) {
        WARN_ON_ONCE(!ctx->driver_present);
        ret = pdev->ops->ieee80211_assign_vif_chanctx(
			net80211_pdev_to_ieee80211_hw(pdev),
            net80211_vif_to_ieee80211_vif(vif),
            &ctx->conf);
    }

    return ret;
}

void drv_unassign_vif_chanctx(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct ieee80211_chanctx *ctx)
{
    if (!vif->drv_added)
        return;

    if (pdev->ops->ieee80211_unassign_vif_chanctx) {
        WARN_ON_ONCE(!ctx->driver_present);
        pdev->ops->ieee80211_unassign_vif_chanctx(
			net80211_pdev_to_ieee80211_hw(pdev),
            net80211_vif_to_ieee80211_vif(vif),
            &ctx->conf);
    }
}

void drv_update_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx,
    u32 changed)
{
    if (pdev->ops->ieee80211_change_chanctx) {
        WARN_ON_ONCE(!ctx->driver_present);
        pdev->ops->ieee80211_change_chanctx(
			net80211_pdev_to_ieee80211_hw(pdev), 
			&ctx->conf, changed);
    }
}

int drv_add_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx)
{
    int ret = -EOPNOTSUPP;

    if (pdev->ops->ieee80211_add_chanctx)
        ret = pdev->ops->ieee80211_add_chanctx(
        	net80211_pdev_to_ieee80211_hw(pdev), 
        	&ctx->conf);
	
    if (!ret)
        ctx->driver_present = true;

    return ret;
}

void drv_remove_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx)
{
    if (WARN_ON(!ctx->driver_present))
        return;

    if (pdev->ops->ieee80211_remove_chanctx)
        pdev->ops->ieee80211_remove_chanctx(
        	net80211_pdev_to_ieee80211_hw(pdev), 
       		&ctx->conf);
    ctx->driver_present = false;
}

int drv_config(struct net80211_pdev *pdev, u32 changed)
{
    int ret;
    ret = pdev->ops->ieee80211_config(
			net80211_pdev_to_ieee80211_hw(pdev), 
			changed);
    return ret;
}

int drv_set_key(struct net80211_pdev *pdev,
    enum ieee80211_key_cmd cmd,
    struct net80211_vif *vif,
    struct net80211_sta *sta,
    struct ieee80211_key_conf *key)
{
    int ret;

    if (!vif->drv_added)
        return -EIO;

    ret = pdev->ops->ieee80211_set_key(net80211_pdev_to_ieee80211_hw(pdev), 
        cmd, 
        net80211_vif_to_ieee80211_vif(vif), 
        net80211_sta_to_ieee80211_sta(sta), 
        key);
    return ret;
}

void drv_sta_rc_update(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_sta *sta)
{
    if (!vif->drv_added)
        return;

    if (!sta->rc_changed)
        return;

    if (pdev->ops->ieee80211_sta_rc_update)
        pdev->ops->ieee80211_sta_rc_update(net80211_pdev_to_ieee80211_hw(pdev),
            net80211_vif_to_ieee80211_vif(vif),
            net80211_sta_to_ieee80211_sta(sta),
            sta->rc_changed);
    sta->rc_changed = 0;
}

int drv_ampdu_action(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct ieee80211_ampdu_params *params)
{
    int ret = -EOPNOTSUPP;

    if (!vif->drv_added)
        return -EIO;

    if (pdev->ops->ieee80211_ampdu_action)
        ret = pdev->ops->ieee80211_ampdu_action(
        	net80211_pdev_to_ieee80211_hw(pdev), 
        	net80211_vif_to_ieee80211_vif(vif), 
        	params);

    return ret;
}

int drv_set_bcn_filter(struct net80211_pdev *pdev, struct net80211_vif *vif, const u32 *ies, u32 ies_cnt)
{
	int ret = -EOPNOTSUPP;

	if (pdev->ops->ieee80211_set_beacon_filter)
        ret = pdev->ops->ieee80211_set_beacon_filter(
        	net80211_pdev_to_ieee80211_hw(pdev), 
        	net80211_vif_to_ieee80211_vif(vif), 
        	ies,
        	ies_cnt);
	return ret;
}

int drv_priv_command(struct net80211_pdev *pdev,
    struct ieee80211_priv_cmd *cmd)
{
    int ret = -EOPNOTSUPP;

    if (pdev->ops->ieee80211_priv_command) 
        ret = pdev->ops->ieee80211_priv_command(
            net80211_pdev_to_ieee80211_hw(pdev), cmd);

    return ret;
}

