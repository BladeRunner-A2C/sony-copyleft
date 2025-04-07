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

#include <net/net80211.h>
#include <net/ndebug.h>
#include "net80211_i.h"
#include "vif.h"
#include "sta.h"
#include "drvops.h"

/* defines */
enum net80211_tx_result
{
    NET80211_TX_CONTINUE = 0,
    NET80211_TX_DROP = 1,
    NET80211_TX_QUEUED = 2
};

/* helpers */
static inline u16
net80211_ac_from_tid(int tid)
{
    // Default mapping in classifier to the default queue settings.
    static const int net802_1d_to_ac[8] = {
        IEEE80211_AC_BE,
        IEEE80211_AC_BK,
        IEEE80211_AC_BK,
        IEEE80211_AC_BE,
        IEEE80211_AC_VI,
        IEEE80211_AC_VI,
        IEEE80211_AC_VO,
        IEEE80211_AC_VO
    };

    return (u16)net802_1d_to_ac[tid & 7];
}

static int 
net80211_lookup_ra_sta(struct net80211_vif *vif,
				   struct sk_buff *skb,
				   struct net80211_sta **sta_out)
{
	struct net80211_sta *sta = NULL;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		sta = net80211_vif_get_sta(vif, vif->bss_conf.bssid);
		if (!sta)
			return -ENOLINK;
		break;
	default:
		return -EINVAL;
	}

	*sta_out = sta ? sta: ERR_PTR(-ENOENT);
	return 0;
}

static struct net80211_vif *
net80211_vif_from_skb(struct net80211_pdev *pdev, struct sk_buff *skb)
{
    struct net80211_vif *vif;

    if (skb->dev) {
        list_for_each_entry(vif, &pdev->interfaces, 
            struct net80211_vif, node) {
            if (skb->dev == &vif->dev)
                return vif;
        }
    }

    return NULL;
}

static void 
net80211_vif_free_tx_skb( struct net80211_vif *vif, struct sk_buff *skb)
{
    struct net_device *dev = &vif->dev;

    if (!skb->pre_alloc) {
        dev_kfree_skb_any(skb);
    }
    else {
        skb_queue_tail(&dev->txq_recycle, skb);
    }
}

void net80211_update_tx_stats(struct net_device *dev, struct sk_buff *skb)
{
    struct net_device_stats *stats = &dev->stats;
    struct net_bytes_record *record0, *record1;
    u64 now;

    now = getwalltime_us();
    stats->tx_bytes += skb->len;
    record1 = &stats->tx_bytes_history.records[(stats->tx_bytes_history.next + 1) & 0x1];
    if ((now - record1->timestamp) >= NETDEV_TPUT_CALCULATE_INTERVAL) {
        record0 = &stats->tx_bytes_history.records[stats->tx_bytes_history.next & 0x1];
        record0->timestamp = now;
        record0->bytes = stats->tx_bytes;
        stats->tx_bytes_history.next = (stats->tx_bytes_history.next + 1) & 0x1;
    }
}

void 
net80211_dev_free_txskb(struct net80211_pdev *pdev, struct sk_buff *skb)
{
	struct net80211_vif *vif;
	struct net_device *dev;
   
	if (!skb->pre_alloc) {
		dev_kfree_skb_any(skb);
	}
	else {
		vif = net80211_vif_from_skb(pdev, skb);
		dev = &vif->dev;

		net_txrx_dbg("recycle skb 0x%p\n", skb);

		/* remove the skb from the txq, and insert it to the recycle-q */
		__skb_unlink(skb, &dev->txq);
		skb_queue_tail(&dev->txq_recycle, skb);

		/* stats */
		net80211_update_tx_stats(dev, skb);
	}
}

void net80211_tx_status(struct net80211_pdev *pdev,
    struct sk_buff *skb)
{
    struct net80211_vif *vif;
    struct ieee80211_tx_info *tx_info;
    bool acked;
    bool noack_success;
    
    vif = net80211_vif_from_skb(pdev, skb);
    if (!vif) {
        net_warn("drop skb 0x%p for unknown interface\n", skb);
        net80211_dev_free_txskb(pdev, skb);
        return;
    }

    tx_info = IEEE80211_SKB_CB(skb);
    acked = !!(tx_info->flags & IEEE80211_TX_STATUS_ACK);
    noack_success = !!(tx_info->flags & IEEE80211_TX_STATUS_NOACK_TRANSMITTED);

    /* report tx status */
    if ((tx_info->flags & IEEE80211_TX_INTERNAL_MLME_TX) &&
        tx_info->tx_complete_handler) {
        tx_info->tx_complete_handler(skb, tx_info->tx_complete_arg, acked || noack_success);
    }
	
    net80211_dev_free_txskb(pdev, skb);
}

void net80211_set_qos_hdr(struct net80211_vif *vif,
    struct sk_buff *skb)
{
    struct ieee80211_hdr *hdr = (void *)skb->data;
    struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
    u8 tid = skb->priority & IEEE80211_QOS_TAG1D_MASK;
    u8 flags;
    u8 *p;

    if (!ieee80211_is_data_qos(hdr->frame_control))
        return;

    p = ieee80211_get_qos_ctl(hdr);

    // set up the first byte

    // set TID and ACK policy
    flags = *p & ~(IEEE80211_QOS_TID_MASK |
        IEEE80211_QOS_ACK_POLICY_MASK);

    if (is_multicast_ether_addr(hdr->addr1) /* ||
        sdata->noack_map & BIT(tid) */) {
        flags |= IEEE80211_QOS_ACK_POLICY_NOACK;
        info->flags |= IEEE80211_TX_CTL_NO_ACK;
    }

    *p = flags | tid;

    // set up the 2th byte
    p++;
    *p = 0;
}

static __le16 net80211_tx_next_seq(struct net80211_sta *sta, int tid)
{
    u16 *seq = &sta->tid_seq[tid];
    __le16 ret = cpu_to_le16(*seq);

    /* Increase the sequence number. */
    *seq = (*seq + 0x10) & IEEE80211_SEQ_SEQ_MASK;

    return ret;
}

static enum net80211_tx_result 
net80211_tx_h_sequence(struct net80211_pdev *pdev, 
    struct net80211_vif *vif,
    struct net80211_sta *sta,
    struct sk_buff *skb,
    u32 txdata_flags)
{
    struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
    struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
    int tid;

    if (ieee80211_hdrlen(hdr->frame_control) < 24)
        return NET80211_TX_CONTINUE;
	
    if (ieee80211_is_ctl(hdr->frame_control))
        return NET80211_TX_CONTINUE;

    if (ieee80211_is_qos_nullfunc(hdr->frame_control))
        return NET80211_TX_CONTINUE;

    // set up the seq-num for non-Qos && QoS-multicast from the global counter
    if (!ieee80211_is_data_qos(hdr->frame_control) ||
        is_multicast_ether_addr(hdr->addr1)) {
        // driver should assign seq-num
        info->flags |= IEEE80211_TX_CTL_ASSIGN_SN;
        hdr->seq_ctrl = cpu_to_le16(vif->sequence_number);
        vif->sequence_number += 0x10;
        return NET80211_TX_CONTINUE;
    }

    // Here should be true to inject/management frames
    if (!sta)
        return NET80211_TX_CONTINUE;

    // also check the per-STA, per-TID sequence counter
    tid = ieee80211_get_tid(hdr);
    hdr->seq_ctrl = net80211_tx_next_seq(sta, tid);

    return NET80211_TX_CONTINUE;
}

static bool net80211_tx_prepare(struct net80211_pdev *pdev,
    struct net80211_vif *vif,
    struct net80211_sta *sta,
    struct sk_buff *skb, 
    u32 txdata_flags)
{
    enum net80211_tx_result result;

    result = net80211_tx_h_sequence(pdev, vif, sta, skb, txdata_flags);

    if (unlikely(result == NET80211_TX_DROP)) {
        return false;
    }
    else if (unlikely(result == NET80211_TX_QUEUED)) {
        return true;
    }

    return true;
}

/*
 * Returns false if the frame couldn't be transmitted but was queued instead.
 */
static bool net80211_tx(struct net80211_vif *vif,
    struct net80211_sta *sta, struct sk_buff *skb,
    bool txpending, u32 txdata_flags)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct ieee80211_tx_control control = { 0 };

    net_dbg("sta=0x%p, skb=0x%p(%u), txpending=%u, txdata_flags=0x%x\n", 
        sta, skb, skb->len, txpending, txdata_flags);

    if (unlikely(skb->len < 10)) {
        dev_kfree_skb(skb);
        return true;
    }

    if (net80211_tx_prepare(pdev, vif, sta, skb, txdata_flags)) {
        control.sta = sta ? (void*)sta : NULL;
        drv_tx(pdev, &control, skb);
    }
    else {
        dev_kfree_skb(skb);
    }
    
    return true;
}

void net80211_xmit(struct net80211_vif *vif,
    struct net80211_sta *sta, struct sk_buff *skb,
    u32 txdata_flags)
{
    struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

    info->u.control.vif = (void*)vif;

    net80211_set_qos_hdr(vif, skb);
    net80211_tx(vif, sta, skb, false, txdata_flags);
}

static void inline
net80211_tx_skb_tid_band(struct net80211_vif *vif,
    struct sk_buff *skb, int tid,
    enum nl80211_band band, u32 txdata_flags)
{
	u16 ac = net80211_ac_from_tid(tid);

	//skb_reset_mac_header(skb);
	skb_set_queue_mapping(skb, ac);

	skb->priority = tid;
	skb->dev = &vif->dev;

	IEEE80211_SKB_CB(skb)->band = band;
	net80211_xmit(vif, NULL, skb, txdata_flags);
}

void
net80211_tx_skb_tid(struct net80211_vif *vif,
    struct sk_buff *skb, int tid)
{
    struct ieee80211_chanctx_conf *chanctx_conf;

    net_dbg("skb=0x%p, tid=%u\n", skb, tid);

    chanctx_conf = net80211_vif_get_chanctx_conf(vif);
    if (WARN_ON(!chanctx_conf)) {
        kfree_skb(skb);
        return;
    }

    net80211_tx_skb_tid_band(vif, skb, tid,
        chanctx_conf->def.chan->band, 0);
}

static bool net80211_tx_8023(struct net80211_vif *vif,
			      struct sk_buff *skb, int led_len,
			      struct net80211_sta *sta,
			      bool txpending)
{
    struct net_device *dev = &vif->dev;
	struct net80211_pdev *pdev = vif->pdev;

	struct ieee80211_tx_control control = { 0 };
    struct net80211_sta *pubsta = NULL;

    /* link the device */
    skb->dev = dev;

    /* only queue the skb need recycle */
    if (skb->pre_alloc) {
        skb_queue_tail(&dev->txq, skb);
        net_txrx_dbg("queued skb 0x%p\n", skb);
    }

    if (sta && net80211_sta_is_uploaded(sta))
        pubsta = sta;

    control.sta = (void*)pubsta;

	drv_tx(pdev, &control, skb);

	return true;
}

static void net80211_8023_xmit(struct net80211_vif *vif,
				struct net_device *dev, struct net80211_sta *sta,
				struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ethhdr *ehdr = (struct ethhdr *)skb->data;
	bool multicast;
    bool authorized;
	const u8 *ra = ehdr->h_dest;

    if (IS_ERR(sta) || (sta && !net80211_sta_is_uploaded(sta)))
        sta = NULL;

	if (vif->type == NL80211_IFTYPE_STATION)
		ra = net80211_vif_bss_conf_get_bssid(vif);

	if (!is_valid_ether_addr(ra))
		goto out_free;

	multicast = is_multicast_ether_addr(ra);
    authorized = sta ? net80211_sta_is_authorized(sta) : false;

	if (!multicast && !authorized &&
	    !ether_addr_equal(vif->addr, ehdr->h_source))
		goto out_free;

	memset(info, 0, sizeof(*info));

	if (multicast)
		info->flags |= IEEE80211_TX_CTL_NO_ACK;

	info->hw_queue = vif->hw_queue[skb_get_queue_mapping(skb)];

	info->flags |= IEEE80211_TX_CTRL_HW_80211_ENCAP;
	info->u.control.vif = (void*)vif;

	net80211_tx_8023(vif, skb, skb->len, sta, false);

	return;

out_free:
    net80211_vif_free_tx_skb(vif, skb);
}

netdev_tx_t net80211_vif_start_xmit_8023(struct sk_buff *skb,
					    struct net_device *dev)
{
	struct net80211_vif *vif = dev->net80211_ptr;
    struct net80211_sta *sta;
	
	if (unlikely(skb->len < ETH_HLEN)) {
        net80211_vif_free_tx_skb(vif, skb);
		return NETDEV_TX_OK;
	}

	if (net80211_lookup_ra_sta(vif, skb, &sta))
        net80211_vif_free_tx_skb(vif, skb);
	else
		net80211_8023_xmit(vif, dev, sta, skb);

	return NETDEV_TX_OK;
}

