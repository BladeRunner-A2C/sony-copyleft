/*
 * Copyright (c) 2020-2021, 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 8/2/22    zxue     fix the kw issue
 26/9/21   zxue     correct the print message format
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/ndebug.h>
#include <net/mac80211.h>
#include "net80211_i.h"
#include "drvops.h"

void net80211_send_delba(struct net80211_vif *vif,
    const u8 *da, u16 tid,
    bool initiator, u16 reason_code)
{
    struct net80211_pdev *pdev = vif->pdev;
	struct sk_buff *skb;
	struct ieee80211_mgmt *mgmt;
	u16 params;

	skb = dev_alloc_skb(pdev->dev, sizeof(*mgmt));
	if (!skb)
		return;

	mgmt = skb_put_zero(skb, 24);
	if (!mgmt)
		return;
	
	memcpy(mgmt->da, da, ETH_ALEN);
	memcpy(mgmt->sa, vif->addr, ETH_ALEN);
	if (vif->type == NL80211_IFTYPE_STATION)
		memcpy(mgmt->bssid, vif->bss_conf.bssid, ETH_ALEN);

	mgmt->frame_control = IEEE80211_FC_TYPE(IEEE80211_FC0_TYPE_MGT, 
        IEEE80211_FC0_SUBTYPE_ACTION);

	skb_put(skb, 1 + sizeof(mgmt->u.action.u.delba));

	mgmt->u.action.category = WLAN_ACTION_BLOCK_ACK;
	mgmt->u.action.u.delba.action_code = WLAN_ACTION_DELBA;
	params = (u16)(initiator << 11);	/* bit 11 initiator */
	params |= (u16)(tid << 12); 		/* bit 15:12 TID number */

	mgmt->u.action.u.delba.params = cpu_to_le16(params);
	mgmt->u.action.u.delba.reason_code = cpu_to_le16(reason_code);

	net80211_tx_skb(vif, skb);
}

void net80211_stop_rx_ba_session(struct net80211_sta *sta, u16 tid,
    bool initiator, u16 reason, bool tx)
{
	struct net80211_pdev *pdev = sta->pdev;
	struct ieee80211_ampdu_params params = { 0 };

	params.sta = (void*)(sta);
	params.action = IEEE80211_AMPDU_RX_STOP;
	params.tid = tid;
	params.amsdu = false;
	params.timeout = 0;
	params.ssn = 0;

	if (!test_bit(tid, sta->ampdu_mlme.agg_session_valid))
		return;

	clear_bit(tid, sta->ampdu_mlme.agg_session_valid);
	net_dbg("Rx BA session stop requested for %p tid %u %a reason: %d\n",
		   sta->addr, tid,
		   !initiator ? "recipient" : "initiator",
		   (int)reason);

	if (drv_ampdu_action(pdev, sta->vif, &params))
		net_warn("HW problem - can not stop rx aggregation for %p tid %d\n",
			   sta->addr, tid);

	/* check whether this is a self generated aggregation halt */
	if (!initiator && tx)
		net80211_send_delba(sta->vif, sta->addr,
					 tid, false, reason);
}

static void net80211_add_addbaext(struct net80211_vif *vif,
    struct sk_buff *skb,
    const struct ieee80211_addba_extension *req)
{
	const struct ieee80211_supported_band *sband = NULL;
	struct ieee80211_addba_extension *resp;
	const struct ieee80211_sta_he_cap *sta_he_cap;
	u8 frag_level, cap_frag_level;
	u8 *pos;
	struct ieee80211_chanctx_conf *chanctx_conf = vif->chanctx_conf;
    enum nl80211_band band;

	if (chanctx_conf) {
		band = chanctx_conf->def.chan->band;
	    sband = net80211_get_sband(vif->pdev, band);
	}

	if (!sband)
		return;
	sta_he_cap = ieee80211_get_iftype_he_cap(sband, vif->type);
	if (!sta_he_cap)
		return;

	pos = skb_put_zero(skb, 2 + sizeof(struct ieee80211_addba_extension));
	if (!pos)
		return;
	*pos++ = WLAN_EID_ADDBA_EXTENSION;
	*pos++ = sizeof(struct ieee80211_addba_extension);
	resp = (struct ieee80211_addba_extension *)pos;
	resp->data = req->data & IEEE80211_ADDBA_EXT_NO_FRAG;

	frag_level = (u8)u32_get_bits(req->data,
				  IEEE80211_ADDBA_EXT_FRAG_LEVEL_MASK);
	cap_frag_level = (u8)u32_get_bits(sta_he_cap->he_capabilities.mac_cap_info[0],
				      IEEE80211_HEMAC_CAP0_DYNAMIC_FRAG_MASK);
	if (frag_level > cap_frag_level)
		frag_level = cap_frag_level;
	resp->data |= u8_encode_bits(frag_level,
				     IEEE80211_ADDBA_EXT_FRAG_LEVEL_MASK);
}

static void net80211_send_addba_resp(struct net80211_sta *sta, u8 *da, u16 tid,
				      u8 dialog_token, u16 status, u16 policy,
				      u16 buf_size, u16 timeout,
				      const struct ieee80211_addba_extension *addbaext)
{
	struct net80211_vif *vif = sta->vif;
	struct net80211_pdev *pdev = vif->pdev;
	struct sk_buff *skb;
	struct ieee80211_mgmt *mgmt;
	bool amsdu = ieee80211_hw_check((void*)pdev, SUPPORTS_AMSDU_IN_AMPDU);
	u16 capab;

	skb = dev_alloc_skb(pdev->dev, sizeof(*mgmt) +
		    2 + sizeof(struct ieee80211_addba_extension));
	if (!skb)
		return;

	mgmt = skb_put_zero(skb, 24);
	if (!mgmt)
		return;
	
	memcpy(mgmt->da, da, ETH_ALEN);
	memcpy(mgmt->sa, vif->addr, ETH_ALEN);
	if (vif->type == NL80211_IFTYPE_STATION)
		memcpy(mgmt->bssid, vif->bss_conf.bssid, ETH_ALEN);

	mgmt->frame_control = IEEE80211_FC_TYPE(IEEE80211_FC0_TYPE_MGT, 
        IEEE80211_FC0_SUBTYPE_ACTION);

	skb_put(skb, 1 + sizeof(mgmt->u.action.u.addba_resp)); /*add the addba_resp*/
	mgmt->u.action.category = WLAN_ACTION_BLOCK_ACK;
	mgmt->u.action.u.addba_resp.action_code = WLAN_ACTION_ADDBA_RESPONSE;
	mgmt->u.action.u.addba_resp.dialog_token = dialog_token;

    /* build the capab:
     * 1. bit 0 A-MSDU support
	 * 2. bit 1 aggregation policy
	 * 3. bit 2 bit 5:2 TID number
	 * 4. bit 3 bit 15:6 max size of aggregation
	 */
	capab = (u16)(amsdu << 0);
	capab |= (u16)(policy << 1);
	capab |= (u16)(tid << 2);
	capab |= (u16)(buf_size << 6);
	mgmt->u.action.u.addba_resp.capab = cpu_to_le16(capab);
	
	mgmt->u.action.u.addba_resp.timeout = cpu_to_le16(timeout);
	mgmt->u.action.u.addba_resp.status = cpu_to_le16(status);

	if (sta->he_cap.he_supported && addbaext)
		net80211_add_addbaext(vif, skb, addbaext);

	net80211_tx_skb(vif, skb);
}

static void net80211_start_rx_ba_session(struct net80211_sta *sta,
					    u8 dialog_token, u16 timeout,
					    u16 start_seq_num, u16 ba_policy,
					    u16 tid, u16 buf_size, bool tx,
					    bool auto_seq,
					    const struct ieee80211_addba_extension *addbaext)
{
	struct net80211_pdev *pdev = sta->pdev;
	struct ieee80211_ampdu_params params = { 0 };
	int ret = -EOPNOTSUPP;
	u16 status = WLAN_STATUS_REQUEST_DECLINED;
	u16 max_buf_size;

	if (tid >= IEEE80211_FIRST_TSPEC_TSID) {
		net_dbg("STA %pM requests BA session on unsupported tid %d\n",
			   sta->addr, tid);
		goto end;
	}

	if (!sta->ht_cap.ht_supported &&
		sta->vif->bss_conf.chandef.chan->band != NL80211_BAND_6GHZ) {
		net_dbg("STA %pM erroneously requests BA session on tid %d w/o QoS\n",
			   sta->addr, tid);
		/* send a response anyway, this is an error case if we get here */
		goto end;
	}
	
	params.sta = (void*)sta;
	params.action = IEEE80211_AMPDU_RX_START;
	params.tid = tid;
	params.amsdu = false;
	params.timeout = timeout;
	params.ssn = start_seq_num;

	if (sta->he_cap.he_supported)
		max_buf_size = IEEE80211_AMPDU_MAX_BUF;
	else
		max_buf_size = IEEE80211_AMPDU_MAX_BUF_HT;

	/* sanity check for incoming parameters */
	if (((ba_policy != 1) &&
		 (!(sta->ht_cap.cap & IEEE80211_HTCAP_DELAY_BA))) ||
		(buf_size > max_buf_size)) {
		status = WLAN_STATUS_INVALID_PARAMETERS;
		net_dbg("AddBA Req with bad params from %pM on tid %u. policy %d, buffer size %d\n",
			sta->addr, tid, ba_policy, buf_size);
		goto end;
	}
	/* determine the default buffer size */
	if (buf_size == 0)
		buf_size = max_buf_size;

	/* make sure the size doesn't exceed the maximum supported by the hw */
	if (buf_size > sta->max_rx_aggregation_subframes)
		buf_size = sta->max_rx_aggregation_subframes;
	params.buf_size = buf_size;

	net_dbg("AddBA Req buf_size=%d for %pM\n",
		   buf_size, sta->addr);

	if (test_bit(tid, sta->ampdu_mlme.agg_session_valid)) {
		if (sta->ampdu_mlme.tid_rx_token[tid] == dialog_token) {
			status = WLAN_STATUS_REQUEST_DECLINED;
			goto end;
		}

		net_dbg("unexpected AddBA Req from %pM on tid %u\n",
			sta->addr, tid);

		/* delete existing Rx BA session on the same tid */
		net80211_stop_rx_ba_session(sta, tid, false,
						WLAN_STATUS_UNSPECIFIED_QOS_FAILURE,
						false);
	}

	if (ieee80211_hw_check((void*)pdev, SUPPORTS_REORDERING_BUFFER)) {
		ret = drv_ampdu_action(pdev, sta->vif, &params);
		net_dbg("Rx A-MPDU request on %pM tid %d result %d\n",
			   sta->addr, tid, ret);
		if (!ret)
			status = WLAN_STATUS_SUCCESS;
		goto end;
	}

end:
	if (status == WLAN_STATUS_SUCCESS) {
		set_bit(tid, sta->ampdu_mlme.agg_session_valid);
		sta->ampdu_mlme.tid_rx_token[tid] = dialog_token;
	}

	if (tx)
		net80211_send_addba_resp(sta, sta->addr, tid,
					  dialog_token, status, 1, buf_size,
					  timeout, addbaext);
}

static void
net80211_process_addba_request(struct net80211_pdev *pdev,
    struct net80211_sta *sta,
    struct ieee80211_mgmt *mgmt, u32 len)
{
	u8 dialog_token;
	u16 timeout, start_seq_num, capab, ba_policy, tid, buf_size;
	struct ieee802_11_elems elems = { 0 };
	int ies_len;

	/* extract session parameters from addba request frame */
	// Get the dialog_token
	dialog_token = mgmt->u.action.u.addba_req.dialog_token;

	// Get the timeout value
	timeout = le16_to_cpu(mgmt->u.action.u.addba_req.timeout);

	// Get the start_seq_num
	start_seq_num = le16_to_cpu(mgmt->u.action.u.addba_req.start_seq_num) >> 4;

	// Get the capab
	capab = le16_to_cpu(mgmt->u.action.u.addba_req.capab);

	// Get the ba_policy
	ba_policy = (capab & IEEE80211_ADDBA_PARAMETER_POLICY_MASK) >> 1;

	// Get the tid value
	tid = (capab & IEEE80211_ADDBA_PARAMETER_TID_MASK) >> 2;

	// Get the buf_size
	buf_size = (capab & IEEE80211_ADDBA_PARAMETER_BUF_SIZE_MASK) >> 6;

	// Get the ies_len
	ies_len = len - offsetof(struct ieee80211_mgmt, u.action.u.addba_req.variable);
	if (ies_len) {
		ieee802_11_parse_elems(mgmt->u.action.u.addba_req.variable,
								ies_len, &elems);
		if (elems.parse_error)
			return;
	}

	net80211_start_rx_ba_session(sta, dialog_token, timeout,
					start_seq_num, ba_policy, tid,
					buf_size, true, false,
					elems.addba_extension);
}

void net80211_process_addba_resp(struct net80211_pdev *pdev,
    struct net80211_sta *sta,
    struct ieee80211_mgmt *mgmt, u32 len)

{
    net_err("WLAN_ACTION_ADDBA_RESP NOT HANDLED YET\n");
}

void net80211_process_delba(struct net80211_pdev *pdev,
    struct net80211_sta *sta,
    struct ieee80211_mgmt *mgmt, u32 len)
{
    net_err("WLAN_ACTION_DELBA NOT HANDLED YET\n");
}

bool 
net80211_process_action_back(struct net80211_pdev *pdev,
    struct net80211_sta *sta,
    struct ieee80211_mgmt *mgmt, u32 len)
{
    u8 acode = mgmt->u.action.u.addba_req.action_code;
    if (WLAN_ACTION_ADDBA_REQUEST == acode) {
        net80211_process_addba_request(pdev, sta, mgmt, len);
        return true;
    }
    
    if (WLAN_ACTION_ADDBA_RESPONSE == acode) {
        net80211_process_addba_resp(pdev, sta, mgmt, len);
        return true;
    }

    if (WLAN_ACTION_DELBA == acode) {
        net80211_process_delba(pdev, sta, mgmt, len);
        return true;
    }

    return true;
}

