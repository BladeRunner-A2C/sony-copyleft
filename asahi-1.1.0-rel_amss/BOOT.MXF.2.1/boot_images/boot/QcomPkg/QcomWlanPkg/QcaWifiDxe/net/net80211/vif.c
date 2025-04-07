/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
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

#include <net/net80211.h>
#include <net/ndebug.h>
#include "net80211_i.h"
#include "drvops.h"
#include "chan.h"
#include "vif.h"
#include "mlme.h"
#include "sme.h"

static void 
net80211_assign_perm_addr(struct net80211_pdev *pdev,
    u8 *perm_addr, enum nl80211_iftype type)
{
    /* always copy the permanent address */
    memcpy(perm_addr, pdev->conf.perm_addr, ETH_ALEN);
}

void
net80211_vif_bss_conf_change_notify(struct net80211_vif *vif)
{
    drv_bss_info_changed(vif->pdev, vif);
}

static void
net80211_vif_reset_bss_erp_conf(struct net80211_vif *vif)
{
    net80211_vif_bss_conf_set_erp_cts_prot(vif, false);
    net80211_vif_bss_conf_set_erp_short_preamble(vif, false);
    net80211_vif_bss_conf_set_erp_short_slot(vif, false);

    net80211_vif_bss_conf_change_notify(vif);
}

static int
net80211_vif_open(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    int ret;

    net_dbg("vif: 0x%p\n", vif);

    ret = drv_add_interface(pdev, vif);
    if (ret) {
        net_dbg("failed to add drvier interface: %u\n", ret);
        goto err_exit;
    }

    net80211_vif_reset_bss_erp_conf(vif);
    net80211_vif_set_wmm_default(vif, true,
        vif->type != NL80211_IFTYPE_STATION);

    vif->is_running = true;

    return 0;

err_exit:
    return ret;
}

static void
net80211_vif_close(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    bool cancel_scan;
    int flushed;

    DEBUG_PARAMETER(flushed);

    net_dbg("vif: 0x%p\n", vif);

    /* Stop any tx */
    // TODOTODO:

    /* Cancel any scan */
    cancel_scan = (pdev->scan_vif == vif);
    if (cancel_scan)
        net80211_scan_cancel(pdev);
	
    /* Cancel any connection */
    if (net80211_vif_type(vif) == NL80211_IFTYPE_STATION) {
        net80211_sta_sme_stop(vif);
    }

    /* Remove all stations */
    flushed = net80211_vif_flush_stations(vif);
    net_dbg("%d stations flushed\n", flushed);

    /* Purge any pending managment packets */
    cancel_work_sync(&vif->work);
    skb_queue_purge(&vif->skb_queue);

    vif->is_running = false;

    drv_remove_interface(pdev, vif);
}

static void
net80211_vif_work(void *context)
{
    struct net80211_vif *vif = context;
    struct net80211_pdev *pdev = vif->pdev;
    struct sk_buff *skb;
    struct net80211_sta *sta;

    /* first process frames */
    while ((skb = skb_dequeue(&vif->skb_queue)) != NULL) {
        struct ieee80211_mgmt *mgmt = (void *)skb->data;
        u32 len = skb->len;
        bool handled = false;

        if (ieee80211_is_action(mgmt->frame_control)) {
            if (WLAN_ACTION_BLOCK_ACK == mgmt->u.action.category) {
                sta = net80211_vif_get_sta(vif, mgmt->sa);
                if (sta) {
                    net80211_process_action_back(pdev, sta, mgmt, len);
                }
                handled = true;
            }
        }

        if (!handled) {
            if (vif->type == NL80211_IFTYPE_STATION) {
                net80211_sta_rx_mgmt(vif, mgmt, len, IEEE80211_SKB_RXCB(skb));
            }
            else {
                net_err("interface %u is not supported\n", vif->type);
            }
        }
        
        kfree_skb(skb);
    }
}

static void
net80211_vif_setup(struct net80211_vif *vif)
{
    /* chanctx */
    list_init_head(&vif->assigned_chanctx_list);

    /* queue */
    skb_queue_head_init(&vif->skb_queue);
    init_work(&vif->work, net80211_vif_work, vif);

    if (vif->type == NL80211_IFTYPE_STATION) {
        net80211_sta_sme_init(vif);
		net80211_sta_bcn_filter_init(vif);
    }
}

static void
net80211_vif_teardown(struct net80211_vif *vif)
{
    net80211_sta_sme_exit(vif);

    /* flush works */
    flush_work(&vif->work);
}

int 
net80211_vif_add(
    struct net80211_pdev *pdev, 
    const char *name, enum nl80211_iftype type,
    struct net80211_vif **new_vif)
{
    struct net80211_vif *vif = NULL;
    struct net_device *ndev = NULL;
    int ret;

    net_dbg("name %a, type %u\n", name, type);

    vif = kzalloc(sizeof(*vif) + net80211_get_vif_data_size(pdev), GFP_KERNEL);
    if (!vif)
        return -ENOMEM;

    vif->pdev = pdev;
    vif->type = type;

    strlcpy((char *)vif->name, name, ARRAY_LENGTH(vif->name));
    net80211_assign_perm_addr(pdev, vif->addr, type);
    vif->ap_power_level = NET80211_UNSET_POWER_LEVEL;
    
    /* initialize the net_device */
    ndev = &vif->dev;
    net80211_assign_perm_addr(pdev, ndev->perm_addr, type);
    ndev->net80211_ptr = vif;
    netdev_setup(ndev);

    ret = net80211_vif_open(vif);
    if (ret)
        goto err_open_dev;

    /* setup */
    net80211_vif_setup(vif);

	list_add_tail(&vif->node, &pdev->interfaces);

    if (new_vif)
        *new_vif = vif;

    net_dbg("vif: 0x%p, ndev: %p\n", vif, ndev);

    return ret;

err_open_dev:
    netdev_teardown(ndev);
    return ret;
}

void
net80211_vif_remove(struct net80211_vif *vif)
{
    net_dbg("name %a, type %u\n", vif->name, vif->type);

    net80211_vif_teardown(vif);

    net80211_vif_close(vif);

    netdev_teardown(&vif->dev);

    /* remove from list */
    list_del(&vif->node);

    net_dbg("removed %a\n", vif->name);

    kfree(vif);
}

/* utils */
static bool
net80211_vif_powersave_allowed(struct net80211_vif *vif)
{
    struct net80211_sta *sta = NULL;
    bool authorized = false;

    if (!net80211_vif_get_powersave(vif))
        return false;

    if (!net80211_vif_get_associated(vif))
        return false;

    sta = net80211_vif_get_sta(vif, net80211_vif_get_bssid(vif));
    if (sta)
        authorized = net80211_sta_is_authorized(sta);

    return authorized;
}

void
net80211_vif_recalc_smps(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct ieee80211_chanctx_conf *chanctx_conf;
    struct ieee80211_chanctx *chanctx;

    chanctx_conf = net80211_vif_get_chanctx_conf(vif);
    if (!chanctx_conf)
        return;

    chanctx = container_of(chanctx_conf, struct ieee80211_chanctx, conf);
    net80211_recalc_smps_chanctx(pdev, chanctx);
}

void
net80211_vif_recalc_powersave(struct net80211_vif *vif)
{
    bool powersave = net80211_vif_powersave_allowed(vif);
    if (net80211_vif_bss_conf_set_powersave(vif, powersave))
        net80211_vif_bss_conf_change_notify(vif);
}

/* pdev */

void net80211_iterate_interfaces(
    struct net80211_pdev *pdev, u32 iter_flags,
    void(*iterator)(void *data, const u8 *mac, struct net80211_vif *vif),
    void *data)
{

    struct net80211_vif *vif;
    bool iter_inactive = iter_flags & IEEE80211_VIF_ITER_INACTIVE;
    bool iter_active = iter_flags & IEEE80211_VIF_ITER_ACTIVE;

    list_for_each_entry(vif, &pdev->interfaces, struct net80211_vif, node) {

        if (iter_inactive && vif->is_running)
            continue;
        if (iter_active && !vif->is_running)
            continue;
        iterator(data, net80211_vif_addr(vif), vif);
    }
}

void
net80211_interfaces_init(struct net80211_pdev *pdev)
{
    list_init_head(&pdev->interfaces);
}

void
net80211_interfaces_remove(struct net80211_pdev *pdev)
{
    struct net80211_vif *vif, *tmp;

    net_dbg("drv_interface_added %d\n", pdev->drv_interface_added);

    list_for_each_entry_safe(vif, tmp, &pdev->interfaces,
        struct net80211_vif, node) {
        net80211_vif_remove(vif);
    }

    WARN(pdev->drv_interface_added, "remaining drv_interface_added %d\n", pdev->drv_interface_added);
}

