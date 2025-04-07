/*
* Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 2/8/22    zxue     fix KW issue
 20/7/21   zxue     remove useless code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/net80211.h>
#include <net/ndebug.h>
#include "net80211_i.h"
#include "vif.h"
#include "sta.h"

/* See IEEE 802.1H for LLC/SNAP encapsulation/decapsulation */
/* Ethernet-II snap header (RFC1042 for most EtherTypes) */
const char rfc1042_header[] = {
	0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00 };

/* Bridge-Tunnel header (for EtherTypes ETH_P_AARP and ETH_P_IPX) */
const char bridge_tunnel_header[] = {
	0xaa, 0xaa, 0x03, 0x00, 0x00, 0xf8 };

/* internal  */
struct net80211_rx_data {
    struct sk_buff *skb;
    struct net80211_pdev *pdev;
    struct net80211_vif *vif;
    struct net80211_sta *sta;
};

enum net80211_rx_result
{
    NET80211_RX_CONTINUE = 0,
    NET80211_RX_DROP = 1,
    NET80211_RX_QUEUED = 2,
};

/* utils */
static u8 *ieee80211_get_bssid(struct ieee80211_hdr *hdr, u32 len,
	enum nl80211_iftype type)
{
    if (ieee80211_is_mgmt(hdr->frame_control)) {
        if (len < 24)
            return NULL;
        return hdr->addr3;
    }
	
    if (ieee80211_is_data(hdr->frame_control)) {
        if (len < 24)
			return NULL;
		if (ieee80211_has_a4(hdr->frame_control))
			return NULL;
		if (ieee80211_has_tods(hdr->frame_control))
			return hdr->addr1;
		if (ieee80211_has_fromds(hdr->frame_control))
			return hdr->addr2;
		return hdr->addr3;
	} 
    
    if (ieee80211_is_ctl(hdr->frame_control)) {
		if (ieee80211_is_pspoll(hdr->frame_control))
			return hdr->addr1;
		if (ieee80211_is_back_req(hdr->frame_control)) {
            if (type == NL80211_IFTYPE_STATION) {
                return hdr->addr2;
			} 
            if (type == NL80211_IFTYPE_AP ||
                type == NL80211_IFTYPE_AP_VLAN) {
                return hdr->addr1;
			}
		}
	}
	
	return NULL;
}

static enum net80211_rx_result
net80211_rx_h_mgmt(struct net80211_rx_data *rx)
{
    struct net80211_pdev *pdev = rx->pdev;
	struct net80211_vif *vif = rx->vif;
	struct ieee80211_mgmt *mgmt = (void *)rx->skb->data;
	__le16 stype;

	DEBUG_PARAMETER(stype);

	stype = IEEE80211_GET_FC_STYPE(mgmt->frame_control);

	net_dbg("stype=0x%x\n", stype);

	/* queue up frame and kick off work to process it */
	skb_queue_tail(&vif->skb_queue, rx->skb);
	net80211_queue_work(pdev, &vif->work);

	return NET80211_RX_QUEUED;
}

void
net80211_process_sa_query_req(struct net80211_vif *vif,
    struct ieee80211_mgmt *mgmt,
	size_t len)
{
    struct net80211_pdev *pdev = vif->pdev;
	struct sk_buff *skb;
	struct ieee80211_mgmt *resp;

    // Not to own unicast address
	if (!ether_addr_equal(mgmt->da, vif->addr)) {
		return;
	}
    
    // Not from the current AP or not associated yet.
	if (!ether_addr_equal(mgmt->sa, net80211_vif_get_bssid(vif)) ||
		!ether_addr_equal(mgmt->bssid, net80211_vif_get_bssid(vif))) {
		return;
	}

    // The SA Query request frame is too short
	if (len < 24 + 1 + sizeof(resp->u.action.u.sa_query)) {
		return;
	}

	skb = dev_alloc_skb(pdev->dev, sizeof(*resp));
	if (skb == NULL)
		return;

	resp = skb_put_zero(skb, 24);
	if (!resp)
		return;
	
    /* build the response packet */
	memcpy(resp->da, mgmt->sa, ETH_ALEN);
	memcpy(resp->sa, net80211_vif_addr(vif), ETH_ALEN);
	memcpy(resp->bssid, net80211_vif_get_bssid(vif), ETH_ALEN);
	resp->frame_control = IEEE80211_FC_TYPE(IEEE80211_FC0_TYPE_MGT, 
        IEEE80211_FC0_SUBTYPE_ACTION);

	/* add the sa part */
	skb_put(skb, 1 + sizeof(resp->u.action.u.sa_query));
	resp->u.action.category = WLAN_ACTION_SA_QUERY;
	resp->u.action.u.sa_query.action = WLAN_ACTION_SA_QUERY_RESPONSE;
	memcpy(resp->u.action.u.sa_query.trans_id,
		mgmt->u.action.u.sa_query.trans_id,
		WLAN_SA_QUERY_TR_ID_LEN);

	net80211_tx_skb(vif, skb);
}

static enum net80211_rx_result
net80211_rx_h_action(struct net80211_rx_data *rx)
{
    struct net80211_pdev *pdev = rx->pdev;
	struct net80211_vif *vif = rx->vif;
	struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)rx->skb->data;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	u32 len = rx->skb->len;

	if (!ieee80211_is_action(mgmt->frame_control))
		return NET80211_RX_CONTINUE;

	if (len < IEEE80211_ACTION_MIN_SIZE)
		return NET80211_RX_DROP;

	if (!rx->sta &&
        mgmt->u.action.category != WLAN_ACTION_PUBLIC &&
		mgmt->u.action.category != WLAN_ACTION_SELF_PROTECTED &&
		mgmt->u.action.category != WLAN_ACTION_SPECTRUM_MGMT)
		return NET80211_RX_DROP;

	switch (mgmt->u.action.category) {
		case WLAN_ACTION_HT:
			// if the sta not support HT, reject the pkt
			if (!rx->sta || !rx->sta->ht_cap.ht_supported)
				goto invalid;

			if (net80211_vif_type(vif) != NL80211_IFTYPE_STATION)
				break;

			if (len < IEEE80211_ACTION_MIN_SIZE + 2)
				goto invalid;

			switch (mgmt->u.action.u.ht_smps.action) {
				case WLAN_HT_ACTION_SMPS: {
					net_dbg("WLAN_HT_ACTION_SMPS DROPPED\n");
					goto handled;
				}
				case WLAN_HT_ACTION_NOTIFY_CHANWIDTH: {
					u8 chanwidth = mgmt->u.action.u.ht_notify_cw.chanwidth;
					enum ieee80211_sta_rx_bandwidth max_bw;

					/* not support 40 MHz, goto handled */
					if (!(rx->sta->ht_cap.cap & IEEE80211_HTCAP_SUP_WIDTH_20_40))
						goto handled;

					if (chanwidth == IEEE80211_HT_CHANWIDTH_20MHZ)
						max_bw = IEEE80211_STA_RX_BANDWIDTH_20;
					else {
						max_bw = net80211_sta_cap_rx_bw(rx->sta);
					}

                    net80211_sta_update_max_bandwidth(rx->sta, max_bw, true);
					goto handled;
				}
				default:
					goto invalid;
			}

			break;
		case WLAN_ACTION_PUBLIC:
			if ((len < IEEE80211_ACTION_MIN_SIZE + 1) ||
			    (len < offsetof(struct ieee80211_mgmt, u.action.u.ext_chan_switch.variable))) {
                goto invalid;
			}

            if (!rx->sta || net80211_vif_type(vif) != NL80211_IFTYPE_STATION || 
			    !ether_addr_equal(mgmt->bssid, net80211_vif_get_bssid(vif)) ||
			    mgmt->u.action.u.ext_chan_switch.action_code !=
				WLAN_PUB_ACTION_EXT_CHANSW_ANN) {
                break;
			}
			goto queue;
		case WLAN_ACTION_VHT:
			if (net80211_vif_type(vif) != NL80211_IFTYPE_STATION)
				break;
			
			if (len < IEEE80211_ACTION_MIN_SIZE + 1)
				goto invalid;

			switch (mgmt->u.action.u.vht_opmode_notif.action_code) {
				case WLAN_VHT_ACTION_OPMODE_NOTIF: {
					if (len < IEEE80211_ACTION_MIN_SIZE + 2)
						goto invalid;

                    // TODOTODO: VHT action operation mode notification
					goto queue;
				}
				case WLAN_VHT_ACTION_GROUPID_MGMT: {
					if (len < IEEE80211_ACTION_MIN_SIZE + 25)
						goto invalid;
					
					/*queue the skb*/
					goto queue;
				}
				default:
					break;
			}
			break;
		case WLAN_ACTION_BLOCK_ACK:
			if (net80211_vif_type(vif) != NL80211_IFTYPE_STATION)
				break;

			if (len < IEEE80211_ACTION_MIN_SIZE + 1)
				break;

            if (mgmt->u.action.u.addba_req.action_code == WLAN_ACTION_ADDBA_REQUEST) {
                if (len < (IEEE80211_ACTION_MIN_SIZE + sizeof(mgmt->u.action.u.addba_req)))
					goto invalid;
			} else if (mgmt->u.action.u.addba_req.action_code == WLAN_ACTION_ADDBA_RESPONSE) {
                if (len < (IEEE80211_ACTION_MIN_SIZE + sizeof(mgmt->u.action.u.addba_resp)))
					goto invalid;
			} else if (mgmt->u.action.u.addba_req.action_code == WLAN_ACTION_DELBA) {
                if (len < (IEEE80211_ACTION_MIN_SIZE + sizeof(mgmt->u.action.u.delba)))
					goto invalid;
			} else {
                goto invalid;
			}

			goto queue;
		case WLAN_ACTION_SPECTRUM_MGMT:
			if (len < IEEE80211_ACTION_MIN_SIZE + 1)
				break;

            if (mgmt->u.action.u.measurement.action_code == WLAN_ACTION_SPCT_MSR_REQ) {
                if (status->band != NL80211_BAND_5GHZ)
					break;

				if (len < (IEEE80211_ACTION_MIN_SIZE + sizeof(mgmt->u.action.u.measurement)))
					break;

				if (vif->type != NL80211_IFTYPE_STATION)
					break;

				net_dbg("WLAN_ACTION_SPCT_MSR_REQ DROPPED\n");
				goto handled;
			} else if (mgmt->u.action.u.measurement.action_code == WLAN_ACTION_SPCT_CHL_SWITCH) {
                const u8 *bssid = NULL;
				if (len < (IEEE80211_ACTION_MIN_SIZE + sizeof(mgmt->u.action.u.chan_switch)))
					break;

				if (vif->type != NL80211_IFTYPE_STATION)
					break;

				if (vif->type == NL80211_IFTYPE_STATION)
					bssid = net80211_vif_get_bssid(vif);
				else
					break;

				if (!ether_addr_equal(mgmt->bssid, bssid))
					break;

				goto queue;
			}
			
			break;
		case WLAN_ACTION_SA_QUERY:
			if (len < (IEEE80211_ACTION_MIN_SIZE + sizeof(mgmt->u.action.u.sa_query)))
				break;

            if (mgmt->u.action.u.sa_query.action == WLAN_ACTION_SA_QUERY_REQUEST) {
                net_dbg("check WLAN_ACTION_SA_QUERY_REQUEST\n");
				if (net80211_vif_type(vif) != NL80211_IFTYPE_STATION)
					break;
				net80211_process_sa_query_req(vif, mgmt, len);
				goto handled;
			}
			
			break;
		case WLAN_ACTION_SELF_PROTECTED:
		case WLAN_ACTION_MESH:
			net_dbg("WLAN_ACTION_SPCT_MSR_REQ DROPPED\n");
			goto handled;
	}

	return NET80211_RX_CONTINUE;

invalid:
	status->rx_flags |= IEEE80211_RX_MALFORMED_ACTION_FRM;
	return NET80211_RX_CONTINUE;

handled:
	dev_kfree_skb(rx->skb);
	return NET80211_RX_QUEUED;

queue:
	skb_queue_tail(&vif->skb_queue, rx->skb);
	net80211_queue_work(pdev, &vif->work);
	return NET80211_RX_QUEUED;
}

static bool
net80211_accept_frame(struct net80211_rx_data *rx)
{
	struct net80211_vif *vif = rx->vif;
	struct sk_buff *skb = rx->skb;
	struct ieee80211_hdr *hdr = (void *)skb->data;
	u8 *bssid = ieee80211_get_bssid(hdr, skb->len, vif->type);
	bool multicast = is_multicast_ether_addr(hdr->addr1);

	switch (net80211_vif_type(vif)) {
		case NL80211_IFTYPE_STATION:
			if (!bssid)
				return false;
			if (ieee80211_is_robust_mgmt_frame(skb) && !rx->sta)
				return false;
			if (multicast)
				return true;
			return ether_addr_equal(vif->addr, hdr->addr1);
		default:
			break;
	}

	WARN_ON_ONCE(1);
	return false;
}

static void
net80211_update_rx_stats(struct net_device *dev, struct sk_buff *skb)
{
	struct net_device_stats *stats = &dev->stats;
	struct net_bytes_record *record0, *record1;
	u64 now;

	now = getwalltime_us();
	stats->rx_bytes += skb->len;
	record1 = &stats->rx_bytes_history.records[(stats->rx_bytes_history.next + 1) & 0x1];
	if ((now - record1->timestamp) >= NETDEV_TPUT_CALCULATE_INTERVAL) {
		record0 = &stats->rx_bytes_history.records[stats->rx_bytes_history.next & 0x1];
		record0->timestamp = now;
		record0->bytes = stats->rx_bytes;
		stats->rx_bytes_history.next = (stats->rx_bytes_history.next + 1) & 0x1;
	}
}

static enum net80211_rx_result
net80211_rx_h_data(struct net80211_rx_data *rx)
{
	struct net80211_vif* vif = rx->vif;
	struct net_device *dev = &vif->dev;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)rx->skb->data;

	if (unlikely(!ieee80211_is_data(hdr->frame_control)))
		return NET80211_RX_CONTINUE;

	/* queue up data frame */
	skb_queue_tail(&dev->rxq, rx->skb);

	/* stats */
	net80211_update_rx_stats(dev, rx->skb);

	return NET80211_RX_QUEUED;
}

static enum net80211_rx_result
net80211_rx_h_data_8023(struct net80211_rx_data *rx)
{
    struct net80211_vif* vif = rx->vif;
    struct net_device *dev = &vif->dev;

    /* queue up data frame */
    skb_queue_tail(&dev->rxq, rx->skb);

    /* stats */
    net80211_update_rx_stats(dev, rx->skb);

    return NET80211_RX_QUEUED;
}

static bool __net80211_invoke_rx_mgmt_handle(struct net80211_rx_data *rx)
{
	enum net80211_rx_result res;

	if (!net80211_accept_frame(rx))
		return false;

	do {
		if ((res = net80211_rx_h_action(rx)) != NET80211_RX_CONTINUE)
			break;
		if ((res = net80211_rx_h_mgmt(rx)) != NET80211_RX_CONTINUE)
			break;
	} while (0);

	return (res == NET80211_RX_QUEUED);
}

static bool net80211_data_to_8023(struct sk_buff *skb, const u8*addr,
	enum nl80211_iftype iftype)
{
	struct ethhdr* ehdr = NULL;
	struct ieee80211_hdr* hdr = (struct ieee80211_hdr*)skb->data;
	struct {
		u8 hdr[ETH_ALEN] __aligned(2);
		__be16 proto;
	} payload;
	struct ethhdr tmp;
	u32 hdrlen;
	u8 fc_mask;

	if (unlikely(!ieee80211_is_data_present(hdr->frame_control)))
		return false;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	if (skb->len < hdrlen + 8)
		return false;

    /* Convert IEEE 802.11 header + possible LLC headers into Ethernet header */
	memcpy(tmp.h_source, ieee80211_get_sa(hdr), ETH_ALEN);
	memcpy(tmp.h_dest, ieee80211_get_da(hdr), ETH_ALEN);

	fc_mask = (u8)(hdr->frame_control >> 8) & (IEEE80211_FC1_DIR_TODS | IEEE80211_FC1_DIR_FROMDS);
	switch (fc_mask) {
	case IEEE80211_FC1_DIR_TODS:  //Not support ToDS currently
		if (unlikely(iftype != NL80211_IFTYPE_AP &&
			iftype != NL80211_IFTYPE_AP_VLAN &&
			iftype != NL80211_IFTYPE_P2P_GO))
			return false;
		break;
	case (IEEE80211_FC1_DIR_TODS | IEEE80211_FC1_DIR_FROMDS):
		if (unlikely(iftype != NL80211_IFTYPE_MESH_POINT &&
			iftype != NL80211_IFTYPE_AP_VLAN &&
			iftype != NL80211_IFTYPE_STATION))
			return false;
		if (iftype == NL80211_IFTYPE_MESH_POINT) {
			 net_dbg("Do NOT Support Mesh Point\n");
		}
		break;
	case IEEE80211_FC1_DIR_FROMDS:
		if ((iftype != NL80211_IFTYPE_MESH_POINT &&
			iftype != NL80211_IFTYPE_STATION &&
			iftype != NL80211_IFTYPE_P2P_CLIENT) ||
			(ether_addr_equal(tmp.h_source, addr) &&
				is_multicast_ether_addr(tmp.h_dest)))
			return false;
		if (iftype == NL80211_IFTYPE_MESH_POINT) {
            net_dbg("Do NOT Support Mesh Point\n");
		}
		break;
	case 0:
		if (iftype != NL80211_IFTYPE_ADHOC &&
			iftype != NL80211_IFTYPE_STATION &&
			iftype != NL80211_IFTYPE_OCB)
			return false;
		break;
	}

	skb_copy_bits(skb, hdrlen, &payload, sizeof(payload));
	tmp.h_proto = payload.proto;

	if (likely((ether_addr_equal(payload.hdr, (const u8 *)rfc1042_header) &&
		tmp.h_proto != __cpu_to_be16(ETH_P_AARP) &&
		tmp.h_proto != __cpu_to_be16(ETH_P_IPX)) ||
		ether_addr_equal(payload.hdr, (const u8 *)bridge_tunnel_header)))
		/* remove RFC1042 or Bridge-Tunnel encapsulation and
		 * replace EtherType */
		hdrlen += ETH_ALEN + 2;
	else
		tmp.h_proto = __cpu_to_be16((u16)(skb->len - hdrlen));

	skb_pull(skb, hdrlen);

	ehdr = skb_push(skb, sizeof(struct ethhdr));
	memcpy(ehdr, &tmp, sizeof(tmp));

	return true;
}
static void
__net80211_rx_handle_packet(struct net80211_pdev *pdev,
    struct net80211_sta *pubsta, 
    struct sk_buff *skb)
{
	struct net80211_vif *vif;
	struct ieee80211_hdr *hdr;
	__le16 fc;
	struct net80211_rx_data rx = { 0 };

	hdr = (struct ieee80211_hdr *)skb->data;
	fc = hdr->frame_control;

	rx.skb = skb;
	rx.pdev = pdev;

	if (ieee80211_is_mgmt(fc)) {
		/* drop frame if too short for header */
		if (skb->len < ieee80211_hdrlen(fc)) {
			goto out;
		}

		if (unlikely(ieee80211_is_probe_resp(hdr->frame_control) ||
			ieee80211_is_beacon(hdr->frame_control))) {
			net80211_scan_rx(pdev, skb);
		}

		list_for_each_entry(vif, &pdev->interfaces, struct net80211_vif, node) {
			if (!vif->is_running)
				continue;

			rx.sta = net80211_vif_get_sta(vif, hdr->addr2);
			rx.vif = vif;

			if (__net80211_invoke_rx_mgmt_handle(&rx))
				return;
		}
	}
	else if (ieee80211_is_data(fc)) {
		struct net80211_sta *sta = pubsta;

		if (!sta) {
			list_for_each_entry(vif, &pdev->interfaces,
			struct net80211_vif, node) {
				if (!vif->is_running)
					continue;

				sta = net80211_vif_find_sta(vif, hdr->addr2);
				break;
			}
		}

		if (sta) {
			rx.sta = sta;
			rx.vif = sta->vif;

			/*convert an 802.11 data frame to 802.3 */
			if (net80211_data_to_8023(rx.skb, rx.vif->addr, rx.vif->type)) {
				if (net80211_rx_h_data_8023(&rx) != NET80211_RX_CONTINUE)
					return;
			}
			else {
				if (net80211_rx_h_data(&rx) != NET80211_RX_CONTINUE)
					return;
			}
		}
	}

out:
	dev_kfree_skb(skb);
}

void net80211_rx_napi(struct net80211_pdev *pdev, 
    struct net80211_sta *sta,
    struct sk_buff *skb)
{
    if (!net80211_pdev_is_started(pdev))
        goto drop;

    __net80211_rx_handle_packet(pdev, sta, skb);

    return;
drop:
    kfree_skb(skb);
}

void net80211_rx_8023(struct net80211_pdev *pdev, 
    struct net80211_sta *sta,
    struct sk_buff *skb, struct napi_struct *napi)
{
    struct net80211_rx_data rx = { 0 };

    if (!net80211_pdev_is_started(pdev))
        goto drop;

    rx.skb = skb;
    rx.pdev = pdev;

    if (sta) {
        rx.sta = sta;
        rx.vif = sta->vif;

        if (net80211_rx_h_data_8023(&rx) != NET80211_RX_CONTINUE)
            return;
    }
    else {
        net_dbg("sta is NULL.\n");
    }

drop:
    kfree_skb(skb);
}
