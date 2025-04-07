/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*
 * IEEE 802.11 Frame type definitions
 * Copyright (c) 2002-2019, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2007-2008 Intel Corporation
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 20/7/21   zxue     remove useless code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __IEEE80211_H
#define __IEEE80211_H

#include <qdf/qbase.h>
#include <qdf/sk_buff.h>
#include <net/nl80211.h>

#define IEEE80211_FC0_VERSION_MASK          0x03
#define IEEE80211_FC0_VERSION_SHIFT         0
#define IEEE80211_FC0_VERSION_0             0x00
#define IEEE80211_FC0_TYPE_MASK             0x0c
#define IEEE80211_FC0_TYPE_SHIFT            2
#define IEEE80211_FC0_SUBTYPE_MASK          0xf0
#define IEEE80211_FC0_SUBTYPE_SHIFT         4

#define IEEE80211_FC1_DIR_MASK              0x03
#define IEEE80211_FC1_DIR_NODS              0x00    /* STA->STA */
#define IEEE80211_FC1_DIR_TODS              0x01    /* STA->AP  */
#define IEEE80211_FC1_DIR_FROMDS            0x02    /* AP ->STA */
#define IEEE80211_FC1_DIR_DSTODS            0x03    /* AP ->AP  */

#define IEEE80211_FC1_MORE_FRAG             0x04
#define IEEE80211_FC1_RETRY                 0x08
#define IEEE80211_FC1_PWR_MGT               0x10
#define IEEE80211_FC1_MORE_DATA             0x20
#define IEEE80211_FC1_WEP                   0x40
#define IEEE80211_FC1_ORDER                 0x80

#define IEEE80211_SEQ_FRAG_MASK             0x000f
#define IEEE80211_SEQ_FRAG_SHIFT            0
#define IEEE80211_SEQ_SEQ_MASK              0xfff0
#define IEEE80211_SEQ_SEQ_SHIFT             4
#define IEEE80211_SEQ_MAX                   4096

#define IEEE80211_FC0_TYPE_MGT              0x00
#define IEEE80211_FC0_TYPE_CTL              0x04
#define IEEE80211_FC0_TYPE_DATA             0x08

/* for TYPE_MGT */
#define IEEE80211_FC0_SUBTYPE_ASSOC_REQ     0x00
#define IEEE80211_FC0_SUBTYPE_ASSOC_RESP    0x10
#define IEEE80211_FC0_SUBTYPE_REASSOC_REQ   0x20
#define IEEE80211_FC0_SUBTYPE_REASSOC_RESP  0x30
#define IEEE80211_FC0_SUBTYPE_PROBE_REQ     0x40
#define IEEE80211_FC0_SUBTYPE_PROBE_RESP    0x50
#define IEEE80211_FC0_SUBTYPE_BEACON        0x80
#define IEEE80211_FC0_SUBTYPE_ATIM          0x90
#define IEEE80211_FC0_SUBTYPE_DISASSOC      0xa0
#define IEEE80211_FC0_SUBTYPE_AUTH          0xb0
#define IEEE80211_FC0_SUBTYPE_DEAUTH        0xc0
#define IEEE80211_FC0_SUBTYPE_ACTION        0xd0
#define IEEE80211_FCO_SUBTYPE_ACTION_NO_ACK 0xe0

/* for TYPE_DATA (bit combination) */
#define IEEE80211_FC0_SUBTYPE_DATA          0x00
#define IEEE80211_FC0_SUBTYPE_CF_ACK        0x10
#define IEEE80211_FC0_SUBTYPE_CF_POLL       0x20
#define IEEE80211_FC0_SUBTYPE_CF_ACPL       0x30
#define IEEE80211_FC0_SUBTYPE_NODATA        0x40
#define IEEE80211_FC0_SUBTYPE_CFACK         0x50
#define IEEE80211_FC0_SUBTYPE_CFPOLL        0x60
#define IEEE80211_FC0_SUBTYPE_CF_ACK_CF_ACK 0x70
#define IEEE80211_FC0_SUBTYPE_QOS           0x80
#define IEEE80211_FC0_SUBTYPE_QOS_NULL      0xc0

/* for TYPE_CTL */
#define IEEE80211_FC0_SUBTYPE_BACK_REQ		0x80
#define IEEE80211_FC0_SUBTYPE_BACK			0x90
#define	IEEE80211_FC0_SUBTYPE_PS_POLL		0xa0
#define	IEEE80211_FC0_SUBTYPE_RTS		    0xb0
#define	IEEE80211_FC0_SUBTYPE_CTS		    0xc0
#define	IEEE80211_FC0_SUBTYPE_ACK		    0xd0
#define	IEEE80211_FC0_SUBTYPE_CF_END		0xe0
#define	IEEE80211_FC0_SUBTYPE_CF_END_ACK	0xf0

#define IEEE80211_FC_TYPE(_type, _stype) (__cpu_to_le16((_type) | (_stype)))

#define IEEE80211_GET_FC_TYPE(_fc)   ((_fc) & __cpu_to_le16(IEEE80211_FC0_TYPE_MASK))
#define IEEE80211_GET_FC_STYPE(_fc)  ((_fc) & __cpu_to_le16(IEEE80211_FC0_SUBTYPE_MASK))

#define IEEE80211_FC_ORDER       (IEEE80211_FC1_ORDER << 8)
#define IEEE80211_FC_WEP         (IEEE80211_FC1_WEP << 8)
#define IEEE80211_FC_MORE_FRAG   (IEEE80211_FC1_MORE_FRAG << 8)
#define IEEE80211_FC_SUBTYPE_QOS (IEEE80211_FC0_SUBTYPE_QOS)

#pragma pack(1)
struct ieee80211_hdr {
	le16 frame_control;
	le16 duration_id;
	u8 addr1[ETH_ALEN];
	u8 addr2[ETH_ALEN];
	u8 addr3[ETH_ALEN];
	le16 seq_ctrl;
	u8 addr4[ETH_ALEN];
} __packed __aligned(2);
#pragma pack()

/* ieee80211_has_tods - check if IEEE80211_FC1_DIR_TODS is set */
static inline bool ieee80211_has_tods(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_DIR_TODS) != 0;
}

/* ieee80211_has_fromds - check if IEEE80211_FC1_DIR_FROMDS is set */
static inline bool ieee80211_has_fromds(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_DIR_FROMDS) != 0;
}

/* ieee80211_has_a4 - check if IEEE80211_FC1_DIR_TODS and IEEE80211_FC1_DIR_FROMDS are set */
static inline bool ieee80211_has_a4(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_DIR_MASK) == IEEE80211_FC1_DIR_MASK;
}

/* ieee80211_has_morefrags - check if IEEE80211_FC1_MORE_FRAG is set */
static inline bool ieee80211_has_morefrags(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_MORE_FRAG) != 0;
}

#if MAC80211_OWNED
/* ieee80211_has_retry - check if IEEE80211_FC1_RETRY is set */
static inline bool ieee80211_has_retry(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_RETRY) != 0;
}

/*  ieee80211_has_pm - check if IEEE80211_FC1_PWR_MGT is set */
static inline bool ieee80211_has_pm(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_PWR_MGT) != 0;
}

/* ieee80211_has_moredata - check if IEEE80211_FC1_MORE_DATA is set */
static inline bool ieee80211_has_moredata(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_MORE_DATA) != 0;
}
#endif // !MAC80211_OWNED

/* ieee80211_has_protected - check if IEEE80211_FC1_WEP is set */
static inline bool ieee80211_has_protected(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_WEP) != 0;
}

/* ieee80211_has_order - check if IEEE80211_FC1_ORDER is set */
static inline bool ieee80211_has_order(le16 fc)
{
    u8 fc_1 = (u8)(fc>>8);
	return (fc_1 & IEEE80211_FC1_ORDER) != 0;
}

/* ieee80211_is_mgmt - check if type is IEEE80211_FC0_TYPE_MGT */
static inline bool ieee80211_is_mgmt(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_MGT;
}

/* ieee80211_is_ctl - check if type is IEEE80211_FC0_TYPE_CTL */
static inline bool ieee80211_is_ctl(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_CTL;
}

/* ieee80211_is_data - check if type is IEEE80211_FC0_TYPE_DATA */
static inline bool ieee80211_is_data(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_DATA;
}

/* ieee80211_is_data_qos - check if type is IEEE80211_FC0_TYPE_DATA and IEEE80211_FC0_SUBTYPE_QOS is set */
static inline bool ieee80211_is_data_qos(le16 fc)
{
	/*
	 * mask with QOS_DATA rather than IEEE80211_FC0_SUBTYPE_MASK as we just need
	 * to check the one bit
	 */
	u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_QOS)) ==
	       (IEEE80211_FC0_TYPE_DATA | IEEE80211_FC0_SUBTYPE_QOS);
}

/* ieee80211_is_data_present - check if type is IEEE80211_FC0_TYPE_DATA and has data */
static inline bool ieee80211_is_data_present(le16 fc)
{
	/*
	 * mask with 0x40 and test that that bit is clear to only return true
	 * for the data-containing substypes.
	 */
	u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | 0x40)) == IEEE80211_FC0_TYPE_DATA;
}

/* ieee80211_is_assoc_req - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_ASSOC_REQ */
static inline bool ieee80211_is_assoc_req(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_ASSOC_REQ);
}

/* ieee80211_is_assoc_resp - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_ASSOC_RESP */
static inline bool ieee80211_is_assoc_resp(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_ASSOC_RESP);
}

/* ieee80211_is_reassoc_req - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_REASSOC_REQ */
static inline bool ieee80211_is_reassoc_req(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_REASSOC_REQ);
}

/* ieee80211_is_reassoc_resp - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_REASSOC_RESP */
static inline bool ieee80211_is_reassoc_resp(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_REASSOC_RESP);
}

/* ieee80211_is_probe_req - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_PROBE_REQ */
static inline bool ieee80211_is_probe_req(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_PROBE_REQ);
}

/* ieee80211_is_probe_resp - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_PROBE_RESP */
static inline bool ieee80211_is_probe_resp(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_PROBE_RESP);
}

/* ieee80211_is_beacon - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_BEACON */
static inline bool ieee80211_is_beacon(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_BEACON);
}

#if MAC80211_OWNED
/* ieee80211_is_atim - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_ATIM */
static inline bool ieee80211_is_atim(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_ATIM);
}
#endif //!MAC80211_OWNED

/* ieee80211_is_disassoc - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_DISASSOC */
static inline bool ieee80211_is_disassoc(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_DISASSOC);
}

/* ieee80211_is_auth - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_AUTH */
static inline bool ieee80211_is_auth(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_AUTH);
}

/* ieee80211_is_deauth - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_DEAUTH */
static inline bool ieee80211_is_deauth(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_DEAUTH);
}

/* ieee80211_is_action - check if IEEE80211_FC0_TYPE_MGT && IEEE80211_FC0_SUBTYPE_ACTION */
static inline bool ieee80211_is_action(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_ACTION);
}

/* ieee80211_is_back_req - check if IEEE80211_FC0_TYPE_CTL && IEEE80211_FC0_SUBTYPE_BACK_REQ */
static inline bool ieee80211_is_back_req(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_BACK_REQ);
}

/* ieee80211_is_back - check if IEEE80211_FC0_TYPE_CTL && IEEE80211_FC0_SUBTYPE_BACK */
static inline bool ieee80211_is_back(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_BACK);
}

/* ieee80211_is_pspoll - check if IEEE80211_FC0_TYPE_CTL && IEEE80211_FC0_SUBTYPE_PS_POLL */
static inline bool ieee80211_is_pspoll(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_PS_POLL);
}

/* ieee80211_is_rts - check if IEEE80211_FC0_TYPE_CTL && IEEE80211_STYPE_RTS */
static inline bool ieee80211_is_rts(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_RTS);
}

/* ieee80211_is_cts - check if IEEE80211_FC0_TYPE_CTL && IEEE80211_STYPE_CTS */
static inline bool ieee80211_is_cts(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_CTS);
}

/* ieee80211_is_ack - check if IEEE80211_FC0_TYPE_CTL && IEEE80211_STYPE_ACK */
static inline bool ieee80211_is_ack(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_ACK);
}

/* ieee80211_is_cfend - check if IEEE80211_FC0_TYPE_CTL && IEEE80211_FC0_SUBTYPE_CF_END */
static inline bool ieee80211_is_cfend(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_CF_END);
}

/* ieee80211_is_cfendack - check if IEEE80211_FC0_TYPE_CTL && IEEE80211_FC0_SUBTYPE_CF_END_ACK */
static inline bool ieee80211_is_cfendack(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_CF_END_ACK);
}

/* ieee80211_is_nullfunc - check if frame is a regular (non-QoS) nullfunc frame */
static inline bool ieee80211_is_nullfunc(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_DATA | IEEE80211_FC0_SUBTYPE_NODATA);
}

/* ieee80211_is_qos_nullfunc - check if frame is a QoS nullfunc frame */
static inline bool ieee80211_is_qos_nullfunc(le16 fc)
{
    u8 fc_0 = (u8)fc;
	return (fc_0 & (IEEE80211_FC0_TYPE_MASK | IEEE80211_FC0_SUBTYPE_MASK)) ==
	       (IEEE80211_FC0_TYPE_DATA | IEEE80211_FC0_SUBTYPE_QOS_NULL);
}

#if MAC80211_UNUSED
/* ieee80211_is_bufferable_mmpdu - check if frame is bufferable MMPDU */
static inline bool ieee80211_is_bufferable_mmpdu(le16 fc)
{
	/* IEEE 802.11-2012, definition of "bufferable management frame";
	 * note that this ignores the IBSS special case. */
	return ieee80211_is_mgmt(fc) &&
	       (ieee80211_is_action(fc) ||
		ieee80211_is_disassoc(fc) ||
		ieee80211_is_deauth(fc));
}

/* ieee80211_is_first_frag - check if IEEE80211_SEQ_FRAG_MASK is not set */
static inline bool ieee80211_is_first_frag(le16 seq_ctrl)
{
	return (seq_ctrl & cpu_to_le16(IEEE80211_SEQ_FRAG_MASK)) == 0;
}

/* ieee80211_is_frag - check if a frame is a fragment */
static inline bool ieee80211_is_frag(struct ieee80211_hdr *hdr)
{
	return ieee80211_has_morefrags(hdr->frame_control) ||
	       hdr->seq_ctrl & cpu_to_le16(IEEE80211_SEQ_FRAG_MASK);
}
#endif //!MAC80211_UNUSED

/* "Measurement Request/Report information element" */
#pragma pack(1)
struct ieee80211_msrment {
	u8 token;
	u8 mode;
	u8 type;
	u8 request[0];
} __packed;
#pragma pack()

/* "Channel Switch Announcement information element" */
#pragma pack(1)
struct ieee80211_chan_switch {
	u8 mode;
	u8 new_ch_num;
	u8 count;
} __packed;
#pragma pack()

/* "Extended Channel Switch Announcement element" */
#pragma pack(1)
struct ieee80211_extended_chan_switch {
	u8 mode;
	u8 new_operating_class;
	u8 new_ch_num;
	u8 count;
} __packed;
#pragma pack()

/* "Secondary Channel Offset element" */
#pragma pack(1)
struct ieee80211_sec_chan_offset {
	u8 sec_chan_offset;
} __packed;
#pragma pack()

/* "wide bandwidth channel switch elment " */
#pragma pack(1)
struct ieee80211_wide_bw_chansw {
	u8 new_channel_width;
    u8 new_center_freq_seg0;
    u8 new_center_freq_seg1;
};
#pragma pack()

/**
 * struct ieee80211_tim
 *
 * This structure refers to "Traffic Indication Map information element"
 */
#pragma pack(1)
struct ieee80211_tim {
	u8 dtim_count;
	u8 dtim_period;
	u8 bitmap_ctrl;
	/* variable size: 1 - 251 bytes */
	u8 virtual_map[1];
};
#pragma pack()

#define WLAN_SA_QUERY_TR_ID_LEN 2
#define WLAN_MEMBERSHIP_LEN 8
#define WLAN_USER_POSITION_LEN 16

/* "TPC Report element" */
#pragma pack(1)
struct ieee80211_tpc_report {
	u8 tx_power;
	u8 link_margin;
};
#pragma pack()

#define IEEE80211_ADDBA_EXT_FRAG_LEVEL_MASK	GENMASK(2, 1)
#define IEEE80211_ADDBA_EXT_FRAG_LEVEL_SHIFT	1
#define IEEE80211_ADDBA_EXT_NO_FRAG		BIT(0)

#pragma pack(1)
struct ieee80211_addba_extension {
	u8 data;
};
#pragma pack()

#pragma pack(1)
struct ieee80211_mgmt {
	le16 frame_control;
	le16 duration;
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	le16 seq_ctrl;
	union {
		struct {
			le16 auth_algorithm;
			le16 auth_transaction;
			le16 status_code;
			/* possibly followed by Challenge text */
			u8 variable[0];
		} auth;
		struct {
			le16 reason_code;
		} deauth;
		struct {
			le16 capab_info;
			le16 listen_interval;
			/* followed by SSID and Supported rates */
			u8 variable[0];
		} assoc_req;
		struct {
			le16 capab_info;
			le16 status_code;
			le16 aid;
			/* followed by Supported rates */
			u8 variable[0];
		} assoc_resp, reassoc_resp;
		struct {
			le16 capab_info;
			le16 listen_interval;
			u8 current_ap[ETH_ALEN];
			/* followed by SSID and Supported rates */
			u8 variable[0];
		} reassoc_req;
		struct {
			le16 reason_code;
		} disassoc;
		struct {
			le64 timestamp;
			le16 beacon_int;
			le16 capab_info;
			/* followed by some of SSID, Supported rates,
			 * FH Params, DS Params, CF Params, IBSS Params, TIM */
			u8 variable[0];
		} beacon;
		struct {
			/* only variable items: SSID, Supported rates */
			u8 variable[0];
		} probe_req;
		struct {
			le64 timestamp;
			le16 beacon_int;
			le16 capab_info;
			/* followed by some of SSIDs, Supported rates, FH Params, 
			   DS Params, CF Params, IBSS Params */
			u8 variable[0];
		} probe_resp;
		struct {
			u8 category;
			union {
				struct{
					u8 action_code;
					u8 variable[0];
				} chan_switch; /* May need update more chan-switch items*/
				struct{
					u8 action_code;
					struct ieee80211_extended_chan_switch data;
					u8 variable[0];
				} ext_chan_switch;
				struct {
					u8 action_code;
					u8 dialog_token;
					u8 status_code;
					u8 variable[0];
				} wme_action;
				struct{
					u8 action_code;
					u8 dialog_token;
					u8 element_id;
					u8 length;
					struct ieee80211_msrment msr_elem;
				} measurement;
				struct{
					u8 action_code;
					u8 dialog_token;
					le16 capab;
					le16 timeout;
					le16 start_seq_num;
					/* followed by BA Extension */
					u8 variable[0];
				} addba_req;
				struct{
					u8 action_code;
					u8 dialog_token;
					le16 status;
					le16 capab;
					le16 timeout;
				} addba_resp;
				struct{
					u8 action_code;
					le16 params;
					le16 reason_code;
				} delba;
				struct {
					u8 action_code;
					u8 variable[0];
				} self_prot;
				struct{
					u8 action_code;
					u8 variable[0];
				} mesh_action;
				struct {
					u8 action;
					u8 trans_id[WLAN_SA_QUERY_TR_ID_LEN];
				} sa_query;
				struct {
					u8 action;
					u8 smps_control;
				} ht_smps;
				struct {
					u8 action_code;
					u8 chanwidth;
				} ht_notify_cw;
				struct {
					u8 action_code;
					u8 dialog_token;
					le16 capability;
					u8 variable[0];
				} tdls_discover_resp;
				struct {
					u8 action_code;
					u8 operating_mode;
				} vht_opmode_notif;
				struct {
					u8 action_code;
					u8 membership[WLAN_MEMBERSHIP_LEN];
					u8 position[WLAN_USER_POSITION_LEN];
				} vht_group_notif;
				struct {
					u8 action_code;
					u8 dialog_token;
					u8 tpc_elem_id;
					u8 tpc_elem_length;
					struct ieee80211_tpc_report tpc;
				} tpc_report;
				struct {
					u8 action_code;
					u8 dialog_token;
					u8 follow_up;
					u8 tod[6];
					u8 toa[6];
					le16 tod_error;
					le16 toa_error;
					u8 variable[0];
				} ftm;
			} u;
		} action;
	} u;
} __aligned(2);
#pragma pack()

#define IEEE80211_MAX_SSID_LEN		32

#define IEEE80211_MAX_MESH_ID_LEN	32

#define IEEE80211_FIRST_TSPEC_TSID	8
#define IEEE80211_NUM_TIDS		16

/* number of ACs */
#define IEEE80211_NUM_OF_ACS		4

#define IEEE80211_QOS_LEN		2
/* 1d tag mask */
#define IEEE80211_QOS_TAG1D_MASK		0x0007
/* TID mask */
#define IEEE80211_QOS_TID_MASK		0x000f
/* EOSP */
#define IEEE80211_QOS_EOSP			0x0010
/* ACK policy */
#define IEEE80211_QOS_ACK_POLICY_NORMAL	0x0000
#define IEEE80211_QOS_ACK_POLICY_NOACK	0x0020
#define IEEE80211_QOS_ACK_POLICY_NO_EXPL	0x0040
#define IEEE80211_QOS_ACK_POLICY_BLOCKACK	0x0060
#define IEEE80211_QOS_ACK_POLICY_MASK	0x0060
/* A-MSDU 802.11n */
#define IEEE80211_QOS_A_MSDU_PRESENT	0x0080
/* Mesh Control 802.11s */
#define IEEE80211_QOS_MESH_CONTROL_PRESENT  0x0100

/* Mesh Power Save Level */
#define IEEE80211_QOS_MESH_PS_LEVEL		0x0200
/* Mesh Receiver Service Period Initiated */
#define IEEE80211_QOS_RSPI			0x0400

/* U-APSD queue for WMM IEs sent by AP */
#define IEEE80211_WMM_IE_AP_UAPSD	(1<<7)
#define IEEE80211_WMM_IE_AP_UAPSD_PARAM_SET_CNT_MASK	0x0f

/* U-APSD queues for WMM IEs sent by STA */
#define IEEE80211_WMM_IE_STA_UAPSD_VO	(1<<0)
#define IEEE80211_WMM_IE_STA_UAPSD_VI	(1<<1)
#define IEEE80211_WMM_IE_STA_UAPSD_BK	(1<<2)
#define IEEE80211_WMM_IE_STA_UAPSD_BE	(1<<3)
#define IEEE80211_WMM_IE_STA_UAPSD_MASK	0x0f

/* U-APSD max SP length for WMM IEs sent by STA */
#define IEEE80211_WMM_IE_STA_UAPSD_SP_ALL	0x00
#define IEEE80211_WMM_IE_STA_UAPSD_SP_2	0x01
#define IEEE80211_WMM_IE_STA_UAPSD_SP_4	0x02
#define IEEE80211_WMM_IE_STA_UAPSD_SP_6	0x03
#define IEEE80211_WMM_IE_STA_UAPSD_SP_MASK	0x03
#define IEEE80211_WMM_IE_STA_UAPSD_SP_SHIFT	5

#define IEEE80211_HT_CTL_LEN		4

/* Supported rates membership selectors */
#define IEEE80211_BSS_MEMBERSHIP_SELECTOR_HT_PHY	127
#define IEEE80211_BSS_MEMBERSHIP_SELECTOR_VHT_PHY	126

/* mgmt header + 1 byte category code */
#define IEEE80211_ACTION_MIN_SIZE offsetof(struct ieee80211_mgmt, u.action.u)

#define IEEE80211_HTCAP_MAX_MPDU_LEN_3839		3839
#define IEEE80211_HTCAP_MAX_MPDU_LEN_7935		7935

#define IEEE80211_VHTCAP_MAX_MPDU_LEN_3895		3895
#define IEEE80211_VHTCAP_MAX_MPDU_LEN_7991		7991
#define IEEE80211_VHTCAP_MAX_MPDU_LEN_11454		11454

#define IEEE80211_HT_MCS_MASK_LEN		10

/* 802.11n HT capability MSC set */
#define IEEE80211_HTCAP_MCS_RX_HIGHEST_MASK		0x3ff
#define IEEE80211_HTCAP_MCS_TX_DEFINED				0x01
#define IEEE80211_HTCAP_MCS_TX_RX_DIFF				0x02
/* value 0 == 1 stream etc */
#define IEEE80211_HTCAP_MCS_TX_MAX_STREAMS_MASK	0x0C
#define IEEE80211_HTCAP_MCS_TX_MAX_STREAMS_SHIFT	2
#define	IEEE80211_HTCAP_MCS_TX_MAX_STREAMS			4
#define IEEE80211_HTCAP_MCS_TX_UNEQUAL_MODULATION	0x10

/*
 * 802.11n D5.0 20.3.5 / 20.6:
 * - indices 0 to 7 and 32 are single spatial stream
 * - 8 to 31 are multiple spatial streams using equal modulation
 *   [8..15 for two streams, 16..23 for three and 24..31 for four]
 * - remainder are multiple spatial streams using unequal modulation
 */
#define IEEE80211_HTCAP_MCS_UNEQUAL_MODULATION_START 33
#define IEEE80211_HTCAP_MCS_UNEQUAL_MODULATION_START_BYTE \
	(IEEE80211_HTCAP_MCS_UNEQUAL_MODULATION_START / 8)

/* 802.11n HT capabilities masks (for cap_info) */
#define IEEE80211_HTCAP_LDPC_CODING		0x0001
#define IEEE80211_HTCAP_SUP_WIDTH_20_40	0x0002
#define IEEE80211_HTCAP_SM_PS				0x000C
#define	IEEE80211_HTCAP_SM_PS_SHIFT		2
#define IEEE80211_HTCAP_GRN_FLD			0x0010
#define IEEE80211_HTCAP_SGI_20				0x0020
#define IEEE80211_HTCAP_SGI_40				0x0040
#define IEEE80211_HTCAP_TX_STBC			0x0080
#define IEEE80211_HTCAP_RX_STBC			0x0300
#define	IEEE80211_HTCAP_RX_STBC_SHIFT		8
#define IEEE80211_HTCAP_DELAY_BA			0x0400
#define IEEE80211_HTCAP_MAX_AMSDU			0x0800
#define IEEE80211_HTCAP_DSSSCCK40			0x1000
#define IEEE80211_HTCAP_RESERVED			0x2000
#define IEEE80211_HTCAP_40MHZ_INTOLERANT	0x4000
#define IEEE80211_HTCAP_LSIG_TXOP_PROT		0x8000

/* 802.11n HT extended capabilities masks (for extended_ht_cap_info) */
#define IEEE80211_HTCAP_EXT_PCO				0x0001
#define IEEE80211_HTCAP_EXT_PCO_TIME		0x0006
#define	IEEE80211_HTCAP_EXT_PCO_TIME_SHIFT	1
#define IEEE80211_HTCAP_EXT_MCS_FB			0x0300
#define	IEEE80211_HTCAP_EXT_MCS_FB_SHIFT	8
#define IEEE80211_HTCAP_EXT_HTC_SUP			0x0400
#define IEEE80211_HTCAP_EXT_RD_RESPONDER	0x0800

/* 802.11n HT capability AMPDU settings (for ampdu_params_info) */
#define IEEE80211_HTCAP_AMPDU_PARM_FACTOR		0x03
#define IEEE80211_HTCAP_AMPDU_PARM_DENSITY		0x1C
#define	IEEE80211_HTCAP_AMPDU_PARM_DENSITY_SHIFT	2

#define IEEE80211_HT_MAX_AMPDU_8K 	0
#define	IEEE80211_HT_MAX_AMPDU_16K	1
#define	IEEE80211_HT_MAX_AMPDU_32K	2
#define	IEEE80211_HT_MAX_AMPDU_64K	3


enum ieee80211_vht_opmode_bits {
    IEEE80211_OPMODE_CHANWIDTH_MASK = 3,
    IEEE80211_OPMODE_CHANWIDTH_20MHZ = 0,
    IEEE80211_OPMODE_CHANWIDTH_40MHZ = 1,
    IEEE80211_OPMODE_CHANWIDTH_80MHZ = 2,
    IEEE80211_OPMODE_CHANWIDTH_160MHZ = 3,
    IEEE80211_OPMODE_RX_NSS_MASK = 0x70,
    IEEE80211_OPMODE_RX_NSS_SHIFT = 4,
    IEEE80211_OPMODE_RX_NSS_TYPE_BF = 0x80,
};

#define IEEE80211_HT_MAX_AMPDU_FACTOR 13

/* Minimum MPDU start spacing */
enum ieee80211_min_mpdu_spacing {
	IEEE80211_HTCAP_MPDU_DENSITY_NONE = 0,	/* No restriction */
	IEEE80211_HTCAP_MPDU_DENSITY_0_25 = 1,	/* 1/4 usec */
	IEEE80211_HTCAP_MPDU_DENSITY_0_5 = 2,	/* 1/2 usec */
	IEEE80211_HTCAP_MPDU_DENSITY_1 = 3,	/* 1 usec */
	IEEE80211_HTCAP_MPDU_DENSITY_2 = 4,	/* 2 usec */
	IEEE80211_HTCAP_MPDU_DENSITY_4 = 5,	/* 4 usec */
	IEEE80211_HTCAP_MPDU_DENSITY_8 = 6,	/* 8 usec */
	IEEE80211_HTCAP_MPDU_DENSITY_16 = 7	/* 16 usec */
};

/* HT Operation element */
#pragma pack(1)
struct ieee80211_ht_operation {
	u8 primary_chan;
	/* Five octets of HT Operation Information */
	u8 ht_param; /* B0..B7 */
	le16 operation_mode; /* B8..B23 */
	le16 stbc_param; /* B24..B39 */
	u8 basic_set[16];
};
#pragma pack()

/* for ht_param */
#define IEEE80211_HT_PARAM_SEC_CHA_OFFSET	0x03
#define	IEEE80211_HT_PARAM_SEC_CHA_NONE		0x00
#define	IEEE80211_HT_PARAM_SEC_CHA_ABOVE	0x01
#define	IEEE80211_HT_PARAM_SEC_CHA_BELOW	0x03
#define IEEE80211_HT_PARAM_CHAN_WIDTH_ANY	0x04
#define IEEE80211_HT_PARAM_RIFS_MODE		0x08

/* block-ack parameters */
#define IEEE80211_ADDBA_PARAMETER_AMSDU_MASK 	 0x0001
#define IEEE80211_ADDBA_PARAMETER_POLICY_MASK 	 0x0002
#define IEEE80211_ADDBA_PARAMETER_TID_MASK 		 0x003C
#define IEEE80211_ADDBA_PARAMETER_BUF_SIZE_MASK  0xFFC0
#define IEEE80211_DELBA_PARAMETER_TID_MASK 		 0xF000
#define IEEE80211_DELBA_PARAMETER_INITIATOR_MASK 0x0800

/*
 * A-MPDU buffer sizes
 * According to HT size varies from 8 to 64 frames
 * HE adds the ability to have up to 256 frames.
 */
#define IEEE80211_AMPDU_MIN_BUF		0x8
#define IEEE80211_AMPDU_MAX_BUF_HT	0x40
#define IEEE80211_AMPDU_MAX_BUF		0x100

#define IEEE80211_HE_VHT_MAX_AMPDU_FACTOR 20
#define IEEE80211_HE_HT_MAX_AMPDU_FACTOR  16

/* Spatial Multiplexing Power Save Modes */
#define WLAN_HTCAP_SM_PS_STATIC	0
#define WLAN_HTCAP_SM_PS_DYNAMIC	1
#define WLAN_HTCAP_SM_PS_INVALID	2
#define WLAN_HTCAP_SM_PS_DISABLED	3

/* for rx_highest */
#define IEEE80211_VHTCAP_MAX_NSTS_TOTAL_SHIFT	13
#define IEEE80211_VHTCAP_MAX_NSTS_TOTAL_MASK	(7 << IEEE80211_VHTCAP_MAX_NSTS_TOTAL_SHIFT)

/* for tx_highest */
#define IEEE80211_VHTCAP_EXT_NSS_BW_CAPABLE	(1 << 13)

/**
 * enum ieee80211_vht_mcs_support - VHT MCS support definitions
 * @IEEE80211_VHTCAP_MCS_SUPPORT_0_7: MCSes 0-7 are supported for the
 *	number of streams
 * @IEEE80211_VHTCAP_MCS_SUPPORT_0_8: MCSes 0-8 are supported
 * @IEEE80211_VHTCAP_MCS_SUPPORT_0_9: MCSes 0-9 are supported
 * @IEEE80211_VHTCAP_MCS_NOT_SUPPORTED: This number of streams isn't supported
 */
enum ieee80211_vht_mcs_support {
	IEEE80211_VHTCAP_MCS_SUPPORT_0_7	= 0,
	IEEE80211_VHTCAP_MCS_SUPPORT_0_8	= 1,
	IEEE80211_VHTCAP_MCS_SUPPORT_0_9	= 2,
	IEEE80211_VHTCAP_MCS_NOT_SUPPORTED	= 3,
};

/* HE capabilities element */
#pragma pack(1)
struct ieee80211_he_capabilities {
	u8 mac_cap_info[6];
	u8 phy_cap_info[11];
};
#pragma pack()

#define IEEE80211_TX_RX_MCS_NSS_DESC_MAX_LEN	5

/**
 * enum ieee80211_he_mcs_support - HE MCS support definitions:
 * -IEEE80211_HECAP_MCS_SUPPORT_0_7: MCSes 0-7 are supported for the
 *	number of streams
 * -IEEE80211_HECAP_MCS_SUPPORT_0_9: MCSes 0-9 are supported
 * -IEEE80211_HECAP_MCS_SUPPORT_0_11: MCSes 0-11 are supported
 * -IEEE80211_HECAP_MCS_NOT_SUPPORTED: This number of streams isn't supported
 */
enum ieee80211_he_mcs_support {
	IEEE80211_HECAP_MCS_SUPPORT_0_7	= 0,
	IEEE80211_HECAP_MCS_SUPPORT_0_9	= 1,
	IEEE80211_HECAP_MCS_SUPPORT_0_11	= 2,
	IEEE80211_HECAP_MCS_NOT_SUPPORTED	= 3,
};

/**
 * struct ieee80211_he_mcs_nss_supp - HE Tx/Rx HE MCS NSS Support Field (P802.11ax_D2.0 section 9.4.2.237.4):
 * @he_rx_mcs_80: Rx MCS map 2 bits for each stream, total 8 streams, for channel
 *     widths less than 80MHz.
 * @he_tx_mcs_80: Tx MCS map 2 bits for each stream, total 8 streams, for channel
 *     widths less than 80MHz.
 * @he_rx_mcs_160: Rx MCS map 2 bits for each stream, total 8 streams, for channel
 *     width 160MHz.
 * @he_tx_mcs_160: Tx MCS map 2 bits for each stream, total 8 streams, for channel
 *     width 160MHz.
 * @he_rx_mcs_80p80: Rx MCS map 2 bits for each stream, total 8 streams, for
 *     channel width 80p80MHz.
 * @he_tx_mcs_80p80: Tx MCS map 2 bits for each stream, total 8 streams, for
 *     channel width 80p80MHz.
 */
#pragma pack(1)
struct ieee80211_he_mcs_nss_supp {
	le16 he_rx_mcs_80;
	le16 he_tx_mcs_80;
	le16 he_rx_mcs_160;
	le16 he_tx_mcs_160;
	le16 he_rx_mcs_80p80;
	le16 he_tx_mcs_80p80;
};
#pragma pack()

/**
 * struct ieee80211_he_operation - HE capabilities element
 *
 * This structure is the "HE operation element" fields as
 * described in P802.11ax_D4.0 section 9.4.2.243
 */
#pragma pack(1)
struct ieee80211_he_operation {
	le32 he_operation_params;
	le16 he_mcs_nss_set;
	/* Optional 0,1,3,4,5,7 or 8 bytes: depends on @he_oper_params */
	u8* optional;
};

/**
 * ieee80211_he_6ghz_oper - HE 6 GHz operation Information field
 * @primary_chan: primary channel
 * @control: control flags
 * @center_freq_seg0: channel center frequency segment 0
 * @center_freq_seg1: channel center frequency segment 1
 * @min_rate: minimum rate (in 1 Mbps units)
 */
struct ieee80211_he_6ghz_oper {
	u8 primary_chan;
#define 	IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH		0x3
#define		IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH_20MHZ	0
#define		IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH_40MHZ	1
#define		IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH_80MHZ	2
#define		IEEE80211_HE_6GHZ_OP_CTRL_CHANWIDTH_160MHZ	3
#define 	IEEE80211_HE_6GHZ_OP_CTRL_DUP_BEACON		0x4
	u8 control;
	u8 center_freq_seg0;
	u8 center_freq_seg1;
	u8 min_rate;
} __packed;

#pragma pack()

/**
 * struct ieee80211_he_spr - HE spatial reuse element
 *
 * This structure is the "HE spatial reuse element" element as
 * described in P802.11ax_D4.0 section 9.4.2.241
 */
#pragma pack(1)
struct ieee80211_he_spr {
	u8 he_sr_control;
	/* Optional 0 to 19 bytes: depends on @he_sr_control */
	u8 optional[0];
};
#pragma pack()

#pragma pack(1)
struct ieee80211_he_mu_edca_param_ac_record {
	u8 aifsn;
	u8 ecw_min_max;
	u8 mu_edca_timer;
};

struct ieee80211_he_mu_edca_param_set {
	u8 he_qos_info;
	struct ieee80211_he_mu_edca_param_ac_record ac_be;
	struct ieee80211_he_mu_edca_param_ac_record ac_bk;
	struct ieee80211_he_mu_edca_param_ac_record ac_vi;
	struct ieee80211_he_mu_edca_param_ac_record ac_vo;
};
#pragma pack()


/* HE Spatial Reuse defines */
#define IEEE80211_HESPR_PSR_DISALLOWED					BIT(0)
#define IEEE80211_HESPR_NON_SRG_OBSS_PD_SR_DISALLOWED	BIT(1)
#define IEEE80211_HESPR_NON_SRG_OFFSET_PRESENT			BIT(2)
#define IEEE80211_HESPR_SRG_INFORMATION_PRESENT			BIT(3)
#define IEEE80211_HESPR_HESIGA_SR_VAL15_ALLOWED			BIT(4)

/* 802.11ac VHT Capabilities */
#define IEEE80211_VHTCAP_MAX_MPDU_LENGTH_3895			0x00000000
#define IEEE80211_VHTCAP_MAX_MPDU_LENGTH_7991			0x00000001
#define IEEE80211_VHTCAP_MAX_MPDU_LENGTH_11454			0x00000002
#define IEEE80211_VHTCAP_MAX_MPDU_MASK					0x00000003
#define IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ		0x00000004
#define IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ	0x00000008
#define IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK			0x0000000C
#define IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_SHIFT			2
#define IEEE80211_VHTCAP_RXLDPC						0x00000010
#define IEEE80211_VHTCAP_SHORT_GI_80					0x00000020
#define IEEE80211_VHTCAP_SHORT_GI_160					0x00000040
#define IEEE80211_VHTCAP_TXSTBC						0x00000080
#define IEEE80211_VHTCAP_RXSTBC_1						0x00000100
#define IEEE80211_VHTCAP_RXSTBC_2						0x00000200
#define IEEE80211_VHTCAP_RXSTBC_3						0x00000300
#define IEEE80211_VHTCAP_RXSTBC_4						0x00000400
#define IEEE80211_VHTCAP_RXSTBC_MASK					0x00000700
#define IEEE80211_VHTCAP_RXSTBC_SHIFT					8
#define IEEE80211_VHTCAP_SU_BEAMFORMER_CAPABLE			0x00000800
#define IEEE80211_VHTCAP_SU_BEAMFORMEE_CAPABLE			0x00001000
#define IEEE80211_VHTCAP_BEAMFORMEE_STS_SHIFT          13
#define IEEE80211_VHTCAP_BEAMFORMEE_STS_MASK			\
		(7 << IEEE80211_VHTCAP_BEAMFORMEE_STS_SHIFT)
#define IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_SHIFT		16
#define IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_MASK		\
		(7 << IEEE80211_VHTCAP_SOUNDING_DIMENSIONS_SHIFT)
#define IEEE80211_VHTCAP_MU_BEAMFORMER_CAPABLE			0x00080000
#define IEEE80211_VHTCAP_MU_BEAMFORMEE_CAPABLE			0x00100000
#define IEEE80211_VHTCAP_VHT_TXOP_PS					0x00200000
#define IEEE80211_VHTCAP_HTC_VHT						0x00400000
#define IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT	23
#define IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK	\
		(7 << IEEE80211_VHTCAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT)
#define IEEE80211_VHTCAP_VHT_LINK_ADAPTATION_VHT_UNSOL_MFB	0x08000000
#define IEEE80211_VHTCAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB	0x0c000000
#define IEEE80211_VHTCAP_RX_ANTENNA_PATTERN				0x10000000
#define IEEE80211_VHTCAP_TX_ANTENNA_PATTERN				0x20000000
#define IEEE80211_VHTCAP_EXT_NSS_BW_SHIFT					30
#define IEEE80211_VHTCAP_EXT_NSS_BW_MASK					0xc0000000

/* 802.11ax HE MAC capabilities */
#define IEEE80211_HEMAC_CAP0_HTC_HE						0x01
#define IEEE80211_HEMAC_CAP0_TWT_REQ					0x02
#define IEEE80211_HEMAC_CAP0_TWT_RES					0x04
#define IEEE80211_HEMAC_CAP0_DYNAMIC_FRAG_NOT_SUPP		0x00
#define IEEE80211_HEMAC_CAP0_DYNAMIC_FRAG_LEVEL_1		0x08
#define IEEE80211_HEMAC_CAP0_DYNAMIC_FRAG_LEVEL_2		0x10
#define IEEE80211_HEMAC_CAP0_DYNAMIC_FRAG_LEVEL_3		0x18
#define IEEE80211_HEMAC_CAP0_DYNAMIC_FRAG_MASK			0x18
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_1		0x00
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_2		0x20
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_4		0x40
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_8		0x60
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_16		0x80
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_32		0xa0
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_64		0xc0
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_UNLIMITED	0xe0
#define IEEE80211_HEMAC_CAP0_MAX_NUM_FRAG_MSDU_MASK		0xe0

#define IEEE80211_HEMAC_CAP1_MIN_FRAG_SIZE_UNLIMITED	0x00
#define IEEE80211_HEMAC_CAP1_MIN_FRAG_SIZE_128			0x01
#define IEEE80211_HEMAC_CAP1_MIN_FRAG_SIZE_256			0x02
#define IEEE80211_HEMAC_CAP1_MIN_FRAG_SIZE_512			0x03
#define IEEE80211_HEMAC_CAP1_MIN_FRAG_SIZE_MASK			0x03
#define IEEE80211_HEMAC_CAP1_TF_MAC_PAD_DUR_0US			0x00
#define IEEE80211_HEMAC_CAP1_TF_MAC_PAD_DUR_8US			0x04
#define IEEE80211_HEMAC_CAP1_TF_MAC_PAD_DUR_16US		0x08
#define IEEE80211_HEMAC_CAP1_TF_MAC_PAD_DUR_MASK		0x0c
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_1		0x00
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_2		0x10
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_3		0x20
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_4		0x30
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_5		0x40
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_6		0x50
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_7		0x60
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_8		0x70
#define IEEE80211_HEMAC_CAP1_MULTI_TID_AGG_RX_QOS_MASK	0x70

/* Link adaptation is split between byte HE_MAC_CAP1 and HE_MAC_CAP2. 
 * It should be set only if IEEE80211_HE_MAC_CAP0_HTC_HE with:
 * 0 = No feedback.
 * 1 = reserved.
 * 2 = Unsolicited feedback.
 * 3 = both
 */
#define IEEE80211_HEMAC_CAP1_LINK_ADAPTATION	0x80

#define IEEE80211_HEMAC_CAP2_LINK_ADAPTATION	0x01
#define IEEE80211_HEMAC_CAP2_ALL_ACK			0x02
#define IEEE80211_HEMAC_CAP2_TRS				0x04
#define IEEE80211_HEMAC_CAP2_BSR				0x08
#define IEEE80211_HEMAC_CAP2_BCAST_TWT			0x10
#define IEEE80211_HEMAC_CAP2_32BIT_BA_BITMAP	0x20
#define IEEE80211_HEMAC_CAP2_MU_CASCADING		0x40
#define IEEE80211_HEMAC_CAP2_ACK_EN				0x80

#define IEEE80211_HEMAC_CAP3_OMI_CONTROL		0x02
#define IEEE80211_HEMAC_CAP3_OFDMA_RA			0x04

/* The maximum length of an A-MDPU is defined by the combination of the Maximum
 * A-MDPU Length Exponent field in the HT capabilities, VHT capabilities and the
 * same field in the HE capabilities.
 */
#define IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_USE_VHT		0x00
#define IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_VHT_1		0x08
#define IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_VHT_2		0x10
#define IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_RESERVED		0x18
#define IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_MASK			0x18
#define IEEE80211_HEMAC_CAP3_AMSDU_FRAG						0x20
#define IEEE80211_HEMAC_CAP3_FLEX_TWT_SCHED					0x40
#define IEEE80211_HEMAC_CAP3_RX_CTRL_FRAME_TO_MULTIBSS		0x80

#define IEEE80211_HEMAC_CAP3_MAX_AMPDU_LEN_EXP_SHIFT		3

#define IEEE80211_HEMAC_CAP4_BSRP_BQRP_A_MPDU_AGG		0x01
#define IEEE80211_HEMAC_CAP4_QTP				0x02
#define IEEE80211_HEMAC_CAP4_BQR				0x04
#define IEEE80211_HEMAC_CAP4_SRP_RESP			0x08
#define IEEE80211_HEMAC_CAP4_NDP_FB_REP			0x10
#define IEEE80211_HEMAC_CAP4_OPS				0x20
#define IEEE80211_HEMAC_CAP4_AMDSU_IN_AMPDU		0x40
/* Multi TID agg TX is split between byte #4 and #5
 * The value is a combination of B39,B40,B41
 */
#define IEEE80211_HEMAC_CAP4_MULTI_TID_AGG_TX_QOS_B39			0x80

#define IEEE80211_HEMAC_CAP5_MULTI_TID_AGG_TX_QOS_B40			0x01
#define IEEE80211_HEMAC_CAP5_MULTI_TID_AGG_TX_QOS_B41			0x02
#define IEEE80211_HEMAC_CAP5_SUBCHAN_SELECTIVE_TRANSMISSION		0x04
#define IEEE80211_HEMAC_CAP5_UL_2x996_TONE_RU					0x08
#define IEEE80211_HEMAC_CAP5_OM_CTRL_UL_MU_DATA_DIS_RX			0x10
#define IEEE80211_HEMAC_CAP5_HE_DYNAMIC_SM_PS					0x20
#define IEEE80211_HEMAC_CAP5_PUNCTURED_SOUNDING					0x40
#define IEEE80211_HEMAC_CAP5_HT_VHT_TRIG_FRAME_RX				0x80

/* 802.11ax HE PHY capabilities */
#define IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G			0x02
#define IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G	0x04
#define IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G			0x08
#define IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G	0x10
#define IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_RU_MAPPING_IN_2G		0x20
#define IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_RU_MAPPING_IN_5G		0x40
#define IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_MASK					0xfe

#define IEEE80211_HEPHY_CAP1_PREAMBLE_PUNC_RX_80MHZ_ONLY_SECOND_20MHZ	0x01
#define IEEE80211_HEPHY_CAP1_PREAMBLE_PUNC_RX_80MHZ_ONLY_SECOND_40MHZ	0x02
#define IEEE80211_HEPHY_CAP1_PREAMBLE_PUNC_RX_160MHZ_ONLY_SECOND_20MHZ	0x04
#define IEEE80211_HEPHY_CAP1_PREAMBLE_PUNC_RX_160MHZ_ONLY_SECOND_40MHZ	0x08
#define IEEE80211_HEPHY_CAP1_PREAMBLE_PUNC_RX_MASK						0x0f
#define IEEE80211_HEPHY_CAP1_DEVICE_CLASS_A							0x10
#define IEEE80211_HEPHY_CAP1_LDPC_CODING_IN_PAYLOAD					0x20
#define IEEE80211_HEPHY_CAP1_HE_LTF_AND_GI_FOR_HE_PPDUS_0_8US			0x40
/* Midamble RX/TX Max NSTS is split between byte #2 and byte #3 */
#define IEEE80211_HEPHY_CAP1_MIDAMBLE_RX_TX_MAX_NSTS					0x80

#define IEEE80211_HEPHY_CAP2_MIDAMBLE_RX_TX_MAX_NSTS		0x01
#define IEEE80211_HEPHY_CAP2_NDP_4x_LTF_AND_3_2US			0x02
#define IEEE80211_HEPHY_CAP2_STBC_TX_UNDER_80MHZ			0x04
#define IEEE80211_HEPHY_CAP2_STBC_RX_UNDER_80MHZ			0x08
#define IEEE80211_HEPHY_CAP2_DOPPLER_TX					0x10
#define IEEE80211_HEPHY_CAP2_DOPPLER_RX					0x20

/* Note that the meaning of UL MU below is different between an AP and a non-AP
 * sta, where in the AP case it indicates support for Rx and in the non-AP sta
 * case it indicates support for Tx.
 */
#define IEEE80211_HEPHY_CAP2_UL_MU_FULL_MU_MIMO			0x40
#define IEEE80211_HEPHY_CAP2_UL_MU_PARTIAL_MU_MIMO			0x80

#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_TX_NO_DCM		0x00
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_TX_BPSK			0x01
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_TX_QPSK			0x02
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_TX_16_QAM		0x03
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_TX_MASK			0x03
#define IEEE80211_HEPHY_CAP3_DCM_MAX_TX_NSS_1				0x00
#define IEEE80211_HEPHY_CAP3_DCM_MAX_TX_NSS_2				0x04
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_RX_NO_DCM		0x00
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_RX_BPSK			0x08
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_RX_QPSK			0x10
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_RX_16_QAM		0x18
#define IEEE80211_HEPHY_CAP3_DCM_MAX_CONST_RX_MASK			0x18
#define IEEE80211_HEPHY_CAP3_DCM_MAX_RX_NSS_1				0x00
#define IEEE80211_HEPHY_CAP3_DCM_MAX_RX_NSS_2				0x20
#define IEEE80211_HEPHY_CAP3_RX_HE_MU_PPDU_FROM_NON_AP_STA	0x40
#define IEEE80211_HEPHY_CAP3_SU_BEAMFORMER				0x80

#define IEEE80211_HEPHY_CAP4_SU_BEAMFORMEE				0x01
#define IEEE80211_HEPHY_CAP4_MU_BEAMFORMER				0x02

/* Minimal allowed value of Max STS under 80MHz is 3 */
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_4		0x0c
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_5		0x10
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_6		0x14
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_7		0x18
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_8		0x1c
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_MASK	0x1c

/* Minimal allowed value of Max STS above 80MHz is 3 */
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_4		0x60
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_5		0x80
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_6		0xa0
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_7		0xc0
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_8		0xe0
#define IEEE80211_HEPHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_MASK	0xe0

#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_1	0x00
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_2	0x01
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_3	0x02
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_4	0x03
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_5	0x04
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_6	0x05
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_7	0x06
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_8	0x07
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_MASK	0x07

#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_1	0x00
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_2	0x08
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_3	0x10
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_4	0x18
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_5	0x20
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_6	0x28
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_7	0x30
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_8	0x38
#define IEEE80211_HEPHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK	0x38

#define IEEE80211_HEPHY_CAP5_NG16_SU_FEEDBACK				0x40
#define IEEE80211_HEPHY_CAP5_NG16_MU_FEEDBACK				0x80

#define IEEE80211_HEPHY_CAP6_CODEBOOK_SIZE_42_SU			0x01
#define IEEE80211_HEPHY_CAP6_CODEBOOK_SIZE_75_MU			0x02
#define IEEE80211_HEPHY_CAP6_TRIG_SU_BEAMFORMER_FB			0x04
#define IEEE80211_HEPHY_CAP6_TRIG_MU_BEAMFORMER_FB			0x08
#define IEEE80211_HEPHY_CAP6_TRIG_CQI_FB					0x10
#define IEEE80211_HEPHY_CAP6_PARTIAL_BW_EXT_RANGE			0x20
#define IEEE80211_HEPHY_CAP6_PARTIAL_BANDWIDTH_DL_MUMIMO	0x40
#define IEEE80211_HEPHY_CAP6_PPE_THRESHOLD_PRESENT			0x80

#define IEEE80211_HEPHY_CAP7_SRP_BASED_SR					0x01
#define IEEE80211_HEPHY_CAP7_POWER_BOOST_FACTOR_AR			0x02
#define IEEE80211_HEPHY_CAP7_HE_SU_MU_PPDU_4XLTF_AND_08_US_GI		0x04
#define IEEE80211_HEPHY_CAP7_MAX_NC_1					0x08
#define IEEE80211_HEPHY_CAP7_MAX_NC_2					0x10
#define IEEE80211_HEPHY_CAP7_MAX_NC_3					0x18
#define IEEE80211_HEPHY_CAP7_MAX_NC_4					0x20
#define IEEE80211_HEPHY_CAP7_MAX_NC_5					0x28
#define IEEE80211_HEPHY_CAP7_MAX_NC_6					0x30
#define IEEE80211_HEPHY_CAP7_MAX_NC_7					0x38
#define IEEE80211_HEPHY_CAP7_MAX_NC_MASK				0x38
#define IEEE80211_HEPHY_CAP7_STBC_TX_ABOVE_80MHZ			0x40
#define IEEE80211_HEPHY_CAP7_STBC_RX_ABOVE_80MHZ			0x80

#define IEEE80211_HEPHY_CAP8_HE_ER_SU_PPDU_4XLTF_AND_08_US_GI		0x01
#define IEEE80211_HEPHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G		0x02
#define IEEE80211_HEPHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU			0x04
#define IEEE80211_HEPHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU			0x08
#define IEEE80211_HEPHY_CAP8_HE_ER_SU_1XLTF_AND_08_US_GI		0x10
#define IEEE80211_HEPHY_CAP8_MIDAMBLE_RX_TX_2X_AND_1XLTF		0x20
#define IEEE80211_HEPHY_CAP8_DCM_MAX_RU_242				0x00
#define IEEE80211_HEPHY_CAP8_DCM_MAX_RU_484				0x40
#define IEEE80211_HEPHY_CAP8_DCM_MAX_RU_996				0x80
#define IEEE80211_HEPHY_CAP8_DCM_MAX_RU_2x996				0xc0
#define IEEE80211_HEPHY_CAP8_DCM_MAX_RU_MASK				0xc0

#define IEEE80211_HEPHY_CAP9_LONGER_THAN_16_SIGB_OFDM_SYM		0x01
#define IEEE80211_HEPHY_CAP9_NON_TRIGGERED_CQI_FEEDBACK		0x02
#define IEEE80211_HEPHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU		0x04
#define IEEE80211_HEPHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU		0x08
#define IEEE80211_HEPHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_COMP_SIGB	0x10
#define IEEE80211_HEPHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_NON_COMP_SIGB	0x20
#define IEEE80211_HEPHY_CAP9_NOMIMAL_PKT_PADDING_0US			0x00
#define IEEE80211_HEPHY_CAP9_NOMIMAL_PKT_PADDING_8US			0x40
#define IEEE80211_HEPHY_CAP9_NOMIMAL_PKT_PADDING_16US			0x80
#define IEEE80211_HEPHY_CAP9_NOMIMAL_PKT_PADDING_RESERVED		0xc0
#define IEEE80211_HEPHY_CAP9_NOMIMAL_PKT_PADDING_MASK			0xc0

/* 802.11ax HE TX/RX MCS NSS Support  */
#define IEEE80211_TXRX_MCS_NSS_SUPP_HIGHEST_MCS_POS			(3)
#define IEEE80211_TXRX_MCS_NSS_SUPP_TX_BITMAP_POS			(6)
#define IEEE80211_TXRX_MCS_NSS_SUPP_RX_BITMAP_POS			(11)
#define IEEE80211_TXRX_MCS_NSS_SUPP_TX_BITMAP_MASK			0x07c0
#define IEEE80211_TXRX_MCS_NSS_SUPP_RX_BITMAP_MASK			0xf800

enum ieee80211_he_highest_mcs_supported_subfield_enc {
	IEEE80211_HIGHEST_MCS_SUPPORTED_MCS7 = 0,
	IEEE80211_HIGHEST_MCS_SUPPORTED_MCS8,
	IEEE80211_HIGHEST_MCS_SUPPORTED_MCS9,
	IEEE80211_HIGHEST_MCS_SUPPORTED_MCS10,
	IEEE80211_HIGHEST_MCS_SUPPORTED_MCS11,
};

static inline u8
ieee80211_he_mcs_nss_size(const struct ieee80211_he_capabilities *he_cap)
{
	u8 nss_count = 4;

	if (he_cap->phy_cap_info[0] &
	    IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G) {
		nss_count += 4;
	}

	if (he_cap->phy_cap_info[0] &
	    IEEE80211_HEPHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G) {
		nss_count += 4;
	}

	return nss_count;
}

/* ieee802.11ax HE PPE Thresholds */
#define IEEE80211_HE_PPE_THRES_NSS_SUPPORT_2NSS			(1)
#define IEEE80211_HE_PPE_THRES_NSS_POS				(0)
#define IEEE80211_HE_PPE_THRES_NSS_MASK				(7)
#define IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_2x966_AND_966_RU	\
	(BIT(5) | BIT(6))
#define IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_MASK		0x78
#define IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_POS		(3)
#define IEEE80211_HE_PPE_THRES_INFO_PPET_SIZE			(3)

/*
 * Calculate 802.11ax HE capabilities IE PPE field size
 * Input: Header byte of ppe_thres (first byte), and HE capa IE's PHY cap u8*
 */
static inline u8
ieee80211_he_ppe_size(u8 ppe_thres_hdr, const u8 *phy_cap_info)
{
	u8 n;

	if ((phy_cap_info[6] &
	     IEEE80211_HEPHY_CAP6_PPE_THRESHOLD_PRESENT) == 0)
		return 0;

	n = hweight8(ppe_thres_hdr &
		     IEEE80211_HE_PPE_THRES_RU_INDEX_BITMASK_MASK);
	n *= (1 + ((ppe_thres_hdr & IEEE80211_HE_PPE_THRES_NSS_MASK) >>
		   IEEE80211_HE_PPE_THRES_NSS_POS));

	/*
	 * Each pair is 6 bits, and we need to add the 7 "header" bits to the
	 * total size.
	 */
	n = (n * IEEE80211_HE_PPE_THRES_INFO_PPET_SIZE * 2) + 7;
	n = DIV_ROUND_UP(n, 8);

	return n;
}

/* HE Operation defines */
#define IEEE80211_HEOP_DFLT_PE_DURATION_MASK    0x00000003
#define IEEE80211_HEOP_TWT_REQUIRED			    0x00000008
#define IEEE80211_HEOP_RTS_THRESHOLD_MASK		0x00003ff0
#define IEEE80211_HEOP_RTS_THRESHOLD_OFFSET		4
#define IEEE80211_HEOP_VHT_OPER_INFO			0x00004000
#define IEEE80211_HEOP_CO_HOSTED_BSS			0x00008000
#define IEEE80211_HEOP_ER_SU_DISABLE			0x00010000
#define IEEE80211_HEOP_6GHZ_OP_INFO		    	0x00020000
#define IEEE80211_HEOP_BSS_COLOR_MASK			0x3f000000
#define IEEE80211_HEOP_BSS_COLOR_OFFSET		    24
#define IEEE80211_HEOP_PARTIAL_BSS_COLOR		0x40000000
#define IEEE80211_HEOP_BSS_COLOR_DISABLED		0x80000000

/*
 * ieee80211_he_oper_size - calculate 802.11ax HE Operations IE size
 */
static inline u8
ieee80211_he_operation_size(const u8 *he_operation_ie)
{
	struct ieee80211_he_operation *he_operation = (void *)he_operation_ie;
	//u8 he_operation_len = sizeof(struct ieee80211_he_operation);
	u8 he_operation_len = 6; //HE_Operation header size is 6
	u32 he_operation_params;

	/* Make sure the input is not NULL */
	if (!he_operation_ie)
		return 0;

	/* Calc required length */
	he_operation_params = le32_to_cpu(he_operation->he_operation_params);
	if (he_operation_params & IEEE80211_HEOP_VHT_OPER_INFO)
        he_operation_len += 3;
	if (he_operation_params & IEEE80211_HEOP_CO_HOSTED_BSS)
		he_operation_len++;
	if (he_operation_params & IEEE80211_HEOP_6GHZ_OP_INFO)
		he_operation_len += sizeof(struct ieee80211_he_6ghz_oper);

	/* Add the first byte (extension ID) to the total length */
	he_operation_len++;

	return he_operation_len;
}

/**
 * ieee80211_he_6ghz_operation - obtain 6 GHz operation field
 * @he_oper: HE operation element (must be pre-validated for size)
 *	but may be NULL
 *
 * Return: a pointer to the 6 GHz operation field, or NULL
 */
static inline const struct ieee80211_he_6ghz_oper *
ieee80211_he_6ghz_operation(const struct ieee80211_he_operation *he_operation)
{
	const u8 *ret_op = (void *)&he_operation->optional;
	u32 he_oper_params;

	if (!he_operation)
		return NULL;

	he_oper_params = le32_to_cpu(he_operation->he_operation_params);

	if (!(he_oper_params & IEEE80211_HEOP_6GHZ_OP_INFO))
		return NULL;
	if (he_oper_params & IEEE80211_HEOP_VHT_OPER_INFO)
		ret_op += 3;
	if (he_oper_params & IEEE80211_HEOP_CO_HOSTED_BSS)
		ret_op++;

	return (void *)ret_op;
}

/* Algorithms for the Authentication*/
#define WLAN_AUTH_MODE_OPEN 0
#define WLAN_AUTH_MODE_SHARED_KEY 1
#define WLAN_AUTH_MODE_FT 2
#define WLAN_AUTH_MODE_SAE 3
#define WLAN_AUTH_MODE_FILS_SK 4
#define WLAN_AUTH_MODE_FILS_SK_PFS 5
#define WLAN_AUTH_MODE_FILS_PK 6
#define WLAN_AUTH_MODE_LEAP 128

#define WLAN_AUTH_MODE_CHALLENGE_LEN 128

#define WLAN_CAPABILITY_ESS				BIT(0)
#define WLAN_CAPABILITY_IBSS			BIT(1)
#define WLAN_CAPABILITY_CF_POLLABLE		BIT(2)
#define WLAN_CAPABILITY_CF_POLL_REQUEST	BIT(3)
#define WLAN_CAPABILITY_PRIVACY			BIT(4)
#define WLAN_CAPABILITY_SHORT_PREAMBLE	BIT(5)
#define WLAN_CAPABILITY_PBCC			BIT(6)
#define WLAN_CAPABILITY_CHANNEL_AGILITY	BIT(7)

/* 802.11h */
#define WLAN_CAPABILITY_SPECTRUM_MGMT	BIT(8)
#define WLAN_CAPABILITY_QOS				BIT(9)
#define WLAN_CAPABILITY_SHORT_SLOT_TIME	BIT(10)
#define WLAN_CAPABILITY_APSD			BIT(11)
#define WLAN_CAPABILITY_RADIO_MEASURE	BIT(12)
#define WLAN_CAPABILITY_DSSS_OFDM		BIT(13)
#define WLAN_CAPABILITY_DEL_BACK		BIT(14)
#define WLAN_CAPABILITY_IMM_BACK		BIT(15)

/* DMG (60gHz) 802.11ad */
/* type - bits 0..1 */
#define WLAN_CAPABILITY_DMG_TYPE_MASK		0x0003
#define WLAN_CAPABILITY_DMG_TYPE_IBSS		0x0001 /* Tx by: STA */
#define WLAN_CAPABILITY_DMG_TYPE_PBSS		0x0002 /* Tx by: PCP */
#define WLAN_CAPABILITY_DMG_TYPE_AP			0x0003 /* Tx by: AP */

#define WLAN_CAPABILITY_DMG_CBAP_ONLY		BIT(2)
#define WLAN_CAPABILITY_DMG_CBAP_SOURCE		BIT(3)
#define WLAN_CAPABILITY_DMG_PRIVACY			BIT(4)
#define WLAN_CAPABILITY_DMG_ECPAC			BIT(5)

#define WLAN_CAPABILITY_DMG_SPECTRUM_MGMT	BIT(8)
#define WLAN_CAPABILITY_DMG_RADIO_MEASURE	BIT(12)

/* 802.11g ERP information element */
#define WLAN_ERP_NON_ERP_PRESENT BIT(0)
#define WLAN_ERP_USE_PROTECTION  BIT(1)
#define WLAN_ERP_BARKER_PREAMBLE BIT(2)

/* Status codes (IEEE Std 802.11-2016, 9.4.1.9, Table 9-46) */
#define WLAN_STATUS_SUCCESS 0
#define WLAN_STATUS_UNSPECIFIED_FAILURE 1
#define WLAN_STATUS_TDLS_WAKEUP_ALTERNATE 2
#define WLAN_STATUS_TDLS_WAKEUP_REJECT 3
#define WLAN_STATUS_SECURITY_DISABLED 5
#define WLAN_STATUS_UNACCEPTABLE_LIFETIME 6
#define WLAN_STATUS_NOT_IN_SAME_BSS 7
#define WLAN_STATUS_CAPS_UNSUPPORTED 10
#define WLAN_STATUS_REASSOC_NO_ASSOC 11
#define WLAN_STATUS_ASSOC_DENIED_UNSPEC 12
#define WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG 13
#define WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION 14
#define WLAN_STATUS_CHALLENGE_FAIL 15
#define WLAN_STATUS_AUTH_TIMEOUT 16
#define WLAN_STATUS_AP_UNABLE_TO_HANDLE_NEW_STA 17
#define WLAN_STATUS_ASSOC_DENIED_RATES 18
#define WLAN_STATUS_ASSOC_DENIED_NOSHORT 19
#define WLAN_STATUS_SPEC_MGMT_REQUIRED 22
#define WLAN_STATUS_PWR_CAPABILITY_NOT_VALID 23
#define WLAN_STATUS_SUPPORTED_CHANNEL_NOT_VALID 24
#define WLAN_STATUS_ASSOC_DENIED_NO_SHORT_SLOT_TIME 25
#define WLAN_STATUS_ASSOC_DENIED_NO_HT 27
#define WLAN_STATUS_R0KH_UNREACHABLE 28
#define WLAN_STATUS_ASSOC_DENIED_NO_PCO 29
#define WLAN_STATUS_ASSOC_REJECTED_TEMPORARILY 30
#define WLAN_STATUS_ROBUST_MGMT_FRAME_POLICY_VIOLATION 31
#define WLAN_STATUS_UNSPECIFIED_QOS_FAILURE 32
#define WLAN_STATUS_DENIED_INSUFFICIENT_BANDWIDTH 33
#define WLAN_STATUS_DENIED_POOR_CHANNEL_CONDITIONS 34
#define WLAN_STATUS_DENIED_QOS_NOT_SUPPORTED 35
#define WLAN_STATUS_REQUEST_DECLINED 37
#define WLAN_STATUS_INVALID_PARAMETERS 38
#define WLAN_STATUS_REJECTED_WITH_SUGGESTED_CHANGES 39
#define WLAN_STATUS_INVALID_IE 40
#define WLAN_STATUS_GROUP_CIPHER_NOT_VALID 41
#define WLAN_STATUS_PAIRWISE_CIPHER_NOT_VALID 42
#define WLAN_STATUS_AKMP_NOT_VALID 43
#define WLAN_STATUS_UNSUPPORTED_RSN_IE_VERSION 44
#define WLAN_STATUS_INVALID_RSN_IE_CAPAB 45
#define WLAN_STATUS_CIPHER_REJECTED_PER_POLICY 46
#define WLAN_STATUS_TS_NOT_CREATED 47
#define WLAN_STATUS_DIRECT_LINK_NOT_ALLOWED 48
#define WLAN_STATUS_DEST_STA_NOT_PRESENT 49
#define WLAN_STATUS_DEST_STA_NOT_QOS_STA 50
#define WLAN_STATUS_ASSOC_DENIED_LISTEN_INT_TOO_LARGE 51
#define WLAN_STATUS_INVALID_FT_ACTION_FRAME_COUNT 52
#define WLAN_STATUS_INVALID_PMKID 53
#define WLAN_STATUS_INVALID_MDIE 54
#define WLAN_STATUS_INVALID_FTIE 55
#define WLAN_STATUS_REQUESTED_TCLAS_NOT_SUPPORTED 56
#define WLAN_STATUS_INSUFFICIENT_TCLAS_PROCESSING_RESOURCES 57
#define WLAN_STATUS_TRY_ANOTHER_BSS 58
#define WLAN_STATUS_GAS_ADV_PROTO_NOT_SUPPORTED 59
#define WLAN_STATUS_NO_OUTSTANDING_GAS_REQ 60
#define WLAN_STATUS_GAS_RESP_NOT_RECEIVED 61
#define WLAN_STATUS_STA_TIMED_OUT_WAITING_FOR_GAS_RESP 62
#define WLAN_STATUS_GAS_RESP_LARGER_THAN_LIMIT 63
#define WLAN_STATUS_REQ_REFUSED_HOME 64
#define WLAN_STATUS_ADV_SRV_UNREACHABLE 65
#define WLAN_STATUS_REQ_REFUSED_SSPN 67
#define WLAN_STATUS_REQ_REFUSED_UNAUTH_ACCESS 68
#define WLAN_STATUS_INVALID_RSNIE 72
#define WLAN_STATUS_U_APSD_COEX_NOT_SUPPORTED 73
#define WLAN_STATUS_U_APSD_COEX_MODE_NOT_SUPPORTED 74
#define WLAN_STATUS_BAD_INTERVAL_WITH_U_APSD_COEX 75
#define WLAN_STATUS_ANTI_CLOGGING_TOKEN_REQ 76
#define WLAN_STATUS_FINITE_CYCLIC_GROUP_NOT_SUPPORTED 77
#define WLAN_STATUS_CANNOT_FIND_ALT_TBTT 78
#define WLAN_STATUS_TRANSMISSION_FAILURE 79
#define WLAN_STATUS_REQ_TCLAS_NOT_SUPPORTED 80
#define WLAN_STATUS_TCLAS_RESOURCES_EXCHAUSTED 81
#define WLAN_STATUS_REJECTED_WITH_SUGGESTED_BSS_TRANSITION 82
#define WLAN_STATUS_REJECT_WITH_SCHEDULE 83
#define WLAN_STATUS_REJECT_NO_WAKEUP_SPECIFIED 84
#define WLAN_STATUS_SUCCESS_POWER_SAVE_MODE 85
#define WLAN_STATUS_PENDING_ADMITTING_FST_SESSION 86
#define WLAN_STATUS_PERFORMING_FST_NOW 87
#define WLAN_STATUS_PENDING_GAP_IN_BA_WINDOW 88
#define WLAN_STATUS_REJECT_U_PID_SETTING 89
#define WLAN_STATUS_REFUSED_EXTERNAL_REASON 92
#define WLAN_STATUS_REFUSED_AP_OUT_OF_MEMORY 93
#define WLAN_STATUS_REJECTED_EMERGENCY_SERVICE_NOT_SUPPORTED 94
#define WLAN_STATUS_QUERY_RESP_OUTSTANDING 95
#define WLAN_STATUS_REJECT_DSE_BAND 96
#define WLAN_STATUS_TCLAS_PROCESSING_TERMINATED 97
#define WLAN_STATUS_TS_SCHEDULE_CONFLICT 98
#define WLAN_STATUS_DENIED_WITH_SUGGESTED_BAND_AND_CHANNEL 99
#define WLAN_STATUS_MCCAOP_RESERVATION_CONFLICT 100
#define WLAN_STATUS_MAF_LIMIT_EXCEEDED 101
#define WLAN_STATUS_MCCA_TRACK_LIMIT_EXCEEDED 102
#define WLAN_STATUS_DENIED_DUE_TO_SPECTRUM_MANAGEMENT 103
#define WLAN_STATUS_ASSOC_DENIED_NO_VHT 104
#define WLAN_STATUS_ENABLEMENT_DENIED 105
#define WLAN_STATUS_RESTRICTION_FROM_AUTHORIZED_GDB 106
#define WLAN_STATUS_AUTHORIZATION_DEENABLED 107
#define WLAN_STATUS_FILS_AUTHENTICATION_FAILURE 112
#define WLAN_STATUS_UNKNOWN_AUTHENTICATION_SERVER 113
#define WLAN_STATUS_UNKNOWN_PASSWORD_IDENTIFIER 123
#define WLAN_STATUS_DENIED_HE_NOT_SUPPORTED 124
#define WLAN_STATUS_SAE_HASH_TO_ELEMENT 126
#define WLAN_STATUS_SAE_PK 127

/* Reason codes (IEEE Std 802.11-2016, 9.4.1.7, Table 9-45) */
#define WLAN_REASON_UNSPECIFIED 1
#define WLAN_REASON_PREV_AUTH_NOT_VALID 2
#define WLAN_REASON_DEAUTH_LEAVING 3
#define WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY 4
#define WLAN_REASON_DISASSOC_AP_BUSY 5
#define WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA 6
#define WLAN_REASON_CLASS3_FRAME_FROM_NONASSOC_STA 7
#define WLAN_REASON_DISASSOC_STA_HAS_LEFT 8
#define WLAN_REASON_STA_REQ_ASSOC_WITHOUT_AUTH 9
#define WLAN_REASON_PWR_CAPABILITY_NOT_VALID 10
#define WLAN_REASON_SUPPORTED_CHANNEL_NOT_VALID 11
#define WLAN_REASON_BSS_TRANSITION_DISASSOC 12
#define WLAN_REASON_INVALID_IE 13
#define WLAN_REASON_MICHAEL_MIC_FAILURE 14
#define WLAN_REASON_4WAY_HANDSHAKE_TIMEOUT 15
#define WLAN_REASON_GROUP_KEY_UPDATE_TIMEOUT 16
#define WLAN_REASON_IE_IN_4WAY_DIFFERS 17
#define WLAN_REASON_GROUP_CIPHER_NOT_VALID 18
#define WLAN_REASON_PAIRWISE_CIPHER_NOT_VALID 19
#define WLAN_REASON_AKMP_NOT_VALID 20
#define WLAN_REASON_UNSUPPORTED_RSN_IE_VERSION 21
#define WLAN_REASON_INVALID_RSN_IE_CAPAB 22
#define WLAN_REASON_IEEE_802_1X_AUTH_FAILED 23
#define WLAN_REASON_CIPHER_SUITE_REJECTED 24
#define WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE 25
#define WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED 26
#define WLAN_REASON_SSP_REQUESTED_DISASSOC 27
#define WLAN_REASON_NO_SSP_ROAMING_AGREEMENT 28
#define WLAN_REASON_BAD_CIPHER_OR_AKM 29
#define WLAN_REASON_NOT_AUTHORIZED_THIS_LOCATION 30
#define WLAN_REASON_SERVICE_CHANGE_PRECLUDES_TS 31
#define WLAN_REASON_UNSPECIFIED_QOS_REASON 32
#define WLAN_REASON_NOT_ENOUGH_BANDWIDTH 33
#define WLAN_REASON_DISASSOC_LOW_ACK 34
#define WLAN_REASON_EXCEEDED_TXOP 35
#define WLAN_REASON_STA_LEAVING 36
#define WLAN_REASON_END_TS_BA_DLS 37
#define WLAN_REASON_UNKNOWN_TS_BA 38
#define WLAN_REASON_TIMEOUT 39
#define WLAN_REASON_PEERKEY_MISMATCH 45
#define WLAN_REASON_AUTHORIZED_ACCESS_LIMIT_REACHED 46
#define WLAN_REASON_EXTERNAL_SERVICE_REQUIREMENTS 47
#define WLAN_REASON_INVALID_FT_ACTION_FRAME_COUNT 48
#define WLAN_REASON_INVALID_PMKID 49
#define WLAN_REASON_INVALID_MDE 50
#define WLAN_REASON_INVALID_FTE 51
#define WLAN_REASON_MESH_PEERING_CANCELLED 52
#define WLAN_REASON_MESH_MAX_PEERS 53
#define WLAN_REASON_MESH_CONFIG_POLICY_VIOLATION 54
#define WLAN_REASON_MESH_CLOSE_RCVD 55
#define WLAN_REASON_MESH_MAX_RETRIES 56
#define WLAN_REASON_MESH_CONFIRM_TIMEOUT 57
#define WLAN_REASON_MESH_INVALID_GTK 58
#define WLAN_REASON_MESH_INCONSISTENT_PARAMS 59
#define WLAN_REASON_MESH_INVALID_SECURITY_CAP 60
#define WLAN_REASON_MESH_PATH_ERROR_NO_PROXY_INFO 61
#define WLAN_REASON_MESH_PATH_ERROR_NO_FORWARDING_INFO 62
#define WLAN_REASON_MESH_PATH_ERROR_DEST_UNREACHABLE 63
#define WLAN_REASON_MAC_ADDRESS_ALREADY_EXISTS_IN_MBSS 64
#define WLAN_REASON_MESH_CHANNEL_SWITCH_REGULATORY_REQ 65
#define WLAN_REASON_MESH_CHANNEL_SWITCH_UNSPECIFIED 66

/* Information Element IDs (IEEE Std 802.11-2016, 9.4.2.1, Table 9-77) */
#define WLAN_EID_SSID 0
#define WLAN_EID_SUPP_RATES 1
#define WLAN_EID_DS_PARAMS 3
#define WLAN_EID_CF_PARAMS 4
#define WLAN_EID_TIM 5
#define WLAN_EID_IBSS_PARAMS 6
#define WLAN_EID_COUNTRY 7
#define WLAN_EID_REQUEST 10
#define WLAN_EID_BSS_LOAD 11
#define WLAN_EID_EDCA_PARAM_SET 12
#define WLAN_EID_TSPEC 13
#define WLAN_EID_TCLAS 14
#define WLAN_EID_SCHEDULE 15
#define WLAN_EID_CHALLENGE 16
#define WLAN_EID_PWR_CONSTRAINT 32
#define WLAN_EID_PWR_CAPABILITY 33
#define WLAN_EID_TPC_REQUEST 34
#define WLAN_EID_TPC_REPORT 35
#define WLAN_EID_SUPPORTED_CHANNELS 36
#define WLAN_EID_CHANNEL_SWITCH 37
#define WLAN_EID_MEASURE_REQUEST 38
#define WLAN_EID_MEASURE_REPORT 39
#define WLAN_EID_QUIET 40
#define WLAN_EID_IBSS_DFS 41
#define WLAN_EID_ERP_INFO 42
#define WLAN_EID_TS_DELAY 43
#define WLAN_EID_TCLAS_PROCESSING 44
#define WLAN_EID_HT_CAP 45
#define WLAN_EID_QOS 46
#define WLAN_EID_RSN 48
#define WLAN_EID_EXT_SUPP_RATES 50
#define WLAN_EID_AP_CHANNEL_REPORT 51
#define WLAN_EID_NEIGHBOR_REPORT 52
#define WLAN_EID_RCPI 53
#define WLAN_EID_MOBILITY_DOMAIN 54
#define WLAN_EID_FAST_BSS_TRANSITION 55
#define WLAN_EID_TIMEOUT_INTERVAL 56
#define WLAN_EID_RIC_DATA 57
#define WLAN_EID_DSE_REGISTERED_LOCATION 58
#define WLAN_EID_SUPPORTED_OPERATING_CLASSES 59
#define WLAN_EID_EXT_CHANSWITCH_ANN 60
#define WLAN_EID_HT_OPERATION 61
#define WLAN_EID_SECONDARY_CHANNEL_OFFSET 62
#define WLAN_EID_BSS_AVERAGE_ACCESS_DELAY 63
#define WLAN_EID_ANTENNA 64
#define WLAN_EID_RSNI 65
#define WLAN_EID_MEASUREMENT_PILOT_TRANSMISSION 66
#define WLAN_EID_BSS_AVAILABLE_ADM_CAPA 67
#define WLAN_EID_BSS_AC_ACCESS_DELAY 68 /* note: also used by WAPI */
#define WLAN_EID_TIME_ADVERTISEMENT 69
#define WLAN_EID_RRM_ENABLED_CAPABILITIES 70
#define WLAN_EID_MULTIPLE_BSSID 71
#define WLAN_EID_20_40_BSS_COEXISTENCE 72
#define WLAN_EID_20_40_BSS_INTOLERANT 73
#define WLAN_EID_OVERLAPPING_BSS_SCAN_PARAMS 74
#define WLAN_EID_RIC_DESCRIPTOR 75
#define WLAN_EID_MMIE 76
#define WLAN_EID_EVENT_REQUEST 78
#define WLAN_EID_EVENT_REPORT 79
#define WLAN_EID_DIAGNOSTIC_REQUEST 80
#define WLAN_EID_DIAGNOSTIC_REPORT 81
#define WLAN_EID_LOCATION_PARAMETERS 82
#define WLAN_EID_NONTRANSMITTED_BSSID_CAPA 83
#define WLAN_EID_SSID_LIST 84
#define WLAN_EID_MULTIPLE_BSSID_INDEX 85
#define WLAN_EID_FMS_DESCRIPTOR 86
#define WLAN_EID_FMS_REQUEST 87
#define WLAN_EID_FMS_RESPONSE 88
#define WLAN_EID_QOS_TRAFFIC_CAPABILITY 89
#define WLAN_EID_BSS_MAX_IDLE_PERIOD 90
#define WLAN_EID_TFS_REQ 91
#define WLAN_EID_TFS_RESP 92
#define WLAN_EID_WNMSLEEP 93
#define WLAN_EID_TIM_BROADCAST_REQUEST 94
#define WLAN_EID_TIM_BROADCAST_RESPONSE 95
#define WLAN_EID_COLLOCATED_INTERFERENCE_REPORT 96
#define WLAN_EID_CHANNEL_USAGE 97
#define WLAN_EID_TIME_ZONE 98
#define WLAN_EID_DMS_REQUEST 99
#define WLAN_EID_DMS_RESPONSE 100
#define WLAN_EID_LINK_ID 101
#define WLAN_EID_WAKEUP_SCHEDULE 102
#define WLAN_EID_CHANNEL_SWITCH_TIMING 104
#define WLAN_EID_PTI_CONTROL 105
#define WLAN_EID_TPU_BUFFER_STATUS 106
#define WLAN_EID_INTERWORKING 107
#define WLAN_EID_ADV_PROTO 108
#define WLAN_EID_EXPEDITED_BANDWIDTH_REQ 109
#define WLAN_EID_QOS_MAP_SET 110
#define WLAN_EID_ROAMING_CONSORTIUM 111
#define WLAN_EID_EMERGENCY_ALERT_ID 112
#define WLAN_EID_MESH_CONFIG 113
#define WLAN_EID_MESH_ID 114
#define WLAN_EID_MESH_LINK_METRIC_REPORT 115
#define WLAN_EID_CONGESTION_NOTIFICATION 116
#define WLAN_EID_PEER_MGMT 117
#define WLAN_EID_MESH_CHANNEL_SWITCH_PARAMETERS 118
#define WLAN_EID_MESH_AWAKE_WINDOW 119
#define WLAN_EID_BEACON_TIMING 120
#define WLAN_EID_MCCAOP_SETUP_REQUEST 121
#define WLAN_EID_MCCAOP_SETUP_REPLY 122
#define WLAN_EID_MCCAOP_ADVERTISEMENT 123
#define WLAN_EID_MCCAOP_TEARDOWN 124
#define WLAN_EID_GANN 125
#define WLAN_EID_RANN 126
#define WLAN_EID_EXT_CAPAB 127
#define WLAN_EID_PREQ 130
#define WLAN_EID_PREP 131
#define WLAN_EID_PERR 132
#define WLAN_EID_PXU 137
#define WLAN_EID_PXUC 138
#define WLAN_EID_AMPE 139
#define WLAN_EID_MIC 140
#define WLAN_EID_DESTINATION_URI 141
#define WLAN_EID_U_APSD_COEX 142
#define WLAN_EID_DMG_WAKEUP_SCHEDULE 143
#define WLAN_EID_EXTENDED_SCHEDULE 144
#define WLAN_EID_STA_AVAILABILITY 145
#define WLAN_EID_DMG_TSPEC 146
#define WLAN_EID_NEXT_DMG_ATI 147
#define WLAN_EID_DMG_CAPABILITIES 148
#define WLAN_EID_DMG_OPERATION 151
#define WLAN_EID_DMG_BSS_PARAMETER_CHANGE 152
#define WLAN_EID_DMG_BEAM_REFINEMENT 153
#define WLAN_EID_CHANNEL_MEASUREMENT_FEEDBACK 154
#define WLAN_EID_CCKM 156
#define WLAN_EID_AWAKE_WINDOW 157
#define WLAN_EID_MULTI_BAND 158
#define WLAN_EID_ADDBA_EXTENSION 159
#define WLAN_EID_NEXTPCP_LIST 160
#define WLAN_EID_PCP_HANDOVER 161
#define WLAN_EID_DMG_LINK_MARGIN 162
#define WLAN_EID_SWITCHING_STREAM 163
#define WLAN_EID_SESSION_TRANSITION 164
#define WLAN_EID_DYNAMIC_TONE_PAIRING_REPORT 165
#define WLAN_EID_CLUSTER_REPORT 166
#define WLAN_EID_REPLAY_CAPABILITIES 167
#define WLAN_EID_RELAY_TRANSFER_PARAM_SET 168
#define WLAN_EID_BEAMLINK_MAINTENANCE 169
#define WLAN_EID_MULTIPLE_MAC_SUBLAYERS 170
#define WLAN_EID_U_PID 171
#define WLAN_EID_DMG_LINK_ADAPTATION_ACK 172
#define WLAN_EID_MCCAOP_ADVERTISEMENT_OVERVIEW 174
#define WLAN_EID_QUIET_PERIOD_REQUEST 175
#define WLAN_EID_QUIET_PERIOD_RESPONSE 177
#define WLAN_EID_QMF_POLICY 181
#define WLAN_EID_ECAPC_POLICY 182
#define WLAN_EID_CLUSTER_TIME_OFFSET 183
#define WLAN_EID_INTRA_ACCESS_CATEGORY_PRIORITY 184
#define WLAN_EID_SCS_DESCRIPTOR 185
#define WLAN_EID_QLOAD_REPORT 186
#define WLAN_EID_HCCA_TXOP_UPDATE_COUNT 187
#define WLAN_EID_HIGHER_LAYER_STREAM_ID 188
#define WLAN_EID_GCR_GROUP_ADDRESS 189
#define WLAN_EID_ANTENNA_SECTOR_ID_PATTERN 190
#define WLAN_EID_VHT_CAP 191
#define WLAN_EID_VHT_OPERATION 192
#define WLAN_EID_VHT_EXTENDED_BSS_LOAD 193
#define WLAN_EID_VHT_WIDE_BW_CHSWITCH  194
#define WLAN_EID_VHT_TRANSMIT_POWER_ENVELOPE 195
#define WLAN_EID_VHT_CHANNEL_SWITCH_WRAPPER 196
#define WLAN_EID_VHT_AID 197
#define WLAN_EID_VHT_QUIET_CHANNEL 198
#define WLAN_EID_VHT_OPERATING_MODE_NOTIFICATION 199
#define WLAN_EID_UPSIM 200
#define WLAN_EID_REDUCED_NEIGHBOR_REPORT 201
#define WLAN_EID_TVHT_OPERATION 202
#define WLAN_EID_DEVICE_LOCATION 204
#define WLAN_EID_WHITE_SPACE_MAP 205
#define WLAN_EID_FTM_PARAMETERS 206
#define WLAN_EID_VENDOR_SPECIFIC 221
#define WLAN_EID_CAG_NUMBER 237
#define WLAN_EID_AP_CSN 239
#define WLAN_EID_FILS_INDICATION 240
#define WLAN_EID_DILS 241
#define WLAN_EID_FRAGMENT 242
#define WLAN_EID_RSNX 244
#define WLAN_EID_EXTENSION 255

/* Element ID Extension (EID 255) values */
#define WLAN_EID_EXT_ASSOC_DELAY_INFO 1
#define WLAN_EID_EXT_FILS_REQ_PARAMS 2
#define WLAN_EID_EXT_FILS_KEY_CONFIRM 3
#define WLAN_EID_EXT_FILS_SESSION 4
#define WLAN_EID_EXT_FILS_HLP_CONTAINER 5
#define WLAN_EID_EXT_FILS_IP_ADDR_ASSIGN 6
#define WLAN_EID_EXT_KEY_DELIVERY 7
#define WLAN_EID_EXT_WRAPPED_DATA 8
#define WLAN_EID_EXT_FTM_SYNC_INFO 9
#define WLAN_EID_EXT_EXTENDED_REQUEST 10
#define WLAN_EID_EXT_ESTIMATED_SERVICE_PARAMS 11
#define WLAN_EID_EXT_FILS_PUBLIC_KEY 12
#define WLAN_EID_EXT_FILS_NONCE 13
#define WLAN_EID_EXT_FUTURE_CHANNEL_GUIDANCE 14
#define WLAN_EID_EXT_OWE_DH_PARAM 32
#define WLAN_EID_EXT_PASSWORD_IDENTIFIER 33
#define WLAN_EID_EXT_HE_CAPABILITIES 35
#define WLAN_EID_EXT_HE_OPERATION 36
#define WLAN_EID_EXT_UORA         37
#define WLAN_EID_EXT_HE_MU_EDCA_PARAMS 38
#define WLAN_EID_EXT_SPATIAL_REUSE 39
#define WLAN_EID_EXT_MAX_CHANNEL_SWITCH_TIME 52
#define WLAN_EID_EXT_OCV_OCI 54
#define WLAN_EID_EXT_MULTIPLE_BSSID_CONFIGURATION 55
#define WLAN_EID_EXT_SHORT_SSID_LIST 58
#define WLAN_EID_EXT_HE_6GHZ_BAND_CAP 59
#define WLAN_EID_EXT_EDMG_CAPABILITIES 61
#define WLAN_EID_EXT_EDMG_OPERATION 62
#define WLAN_EID_EXT_REJECTED_GROUPS 92
#define WLAN_EID_EXT_ANTI_CLOGGING_TOKEN 93

/* Action frame categories (IEEE Std 802.11-2016, 9.4.1.11, Table 9-76) */
#define WLAN_ACTION_SPECTRUM_MGMT 0
#define WLAN_ACTION_QOS 1
#define WLAN_ACTION_DLS 2
#define WLAN_ACTION_BLOCK_ACK 3
#define WLAN_ACTION_PUBLIC 4
#define WLAN_ACTION_RADIO_MEASUREMENT 5
#define WLAN_ACTION_FT 6
#define WLAN_ACTION_HT 7
#define WLAN_ACTION_SA_QUERY 8
#define WLAN_ACTION_PROTECTED_DUAL 9
#define WLAN_ACTION_WNM 10
#define WLAN_ACTION_UNPROTECTED_WNM 11
#define WLAN_ACTION_TDLS 12
#define WLAN_ACTION_MESH 13
#define WLAN_ACTION_MULTIHOP 14
#define WLAN_ACTION_SELF_PROTECTED 15
#define WLAN_ACTION_DMG 16
#define WLAN_ACTION_WMM 17 /* WMM Specification 1.1 */
#define WLAN_ACTION_FST 18
#define WLAN_ACTION_ROBUST_AV_STREAMING 19
#define WLAN_ACTION_UNPROTECTED_DMG 20
#define WLAN_ACTION_VHT 21
#define WLAN_ACTION_FILS 26
#define WLAN_ACTION_VENDOR_SPECIFIC_PROTECTED 126
#define WLAN_ACTION_VENDOR_SPECIFIC 127
/* Note: 128-255 used to report errors by setting category | 0x80 */


/* SPECTRUM_MGMT action code */
#define WLAN_ACTION_SPCT_MSR_REQ 	0
#define	WLAN_ACTION_SPCT_MSR_RPRT 	1
#define	WLAN_ACTION_SPCT_TPC_REQ 	2
#define	WLAN_ACTION_SPCT_TPC_RPRT 	3
#define	WLAN_ACTION_SPCT_CHL_SWITCH 4

/* HT action codes */
#define WLAN_HT_ACTION_NOTIFY_CHANWIDTH 	0
#define	WLAN_HT_ACTION_SMPS 				1
#define	WLAN_HT_ACTION_PSMP 				2
#define	WLAN_HT_ACTION_PCO_PHASE 			3
#define	WLAN_HT_ACTION_CSI 					4
#define	WLAN_HT_ACTION_NONCOMPRESSED_BF 	5
#define	WLAN_HT_ACTION_COMPRESSED_BF 		6
#define	WLAN_HT_ACTION_ASEL_IDX_FEEDBACK 	7

/* VHT action codes */
#define WLAN_VHT_ACTION_COMPRESSED_BF 	0
#define	WLAN_VHT_ACTION_GROUPID_MGMT 	1
#define	WLAN_VHT_ACTION_OPMODE_NOTIF 	2

/* Self Protected Action codes */
#define WLAN_SP_RESERVED 				0
#define	WLAN_SP_MESH_PEERING_OPEN 		1
#define	WLAN_SP_MESH_PEERING_CONFIRM 	2
#define	WLAN_SP_MESH_PEERING_CLOSE 		3
#define	WLAN_SP_MGK_INFORM 				4
#define	WLAN_SP_MGK_ACK 				5

/* Security key length */
#define WLAN_KEY_LEN_WEP40 			5
#define	WLAN_KEY_LEN_WEP104 		13
#define	WLAN_KEY_LEN_CCMP 			16
#define	WLAN_KEY_LEN_CCMP_256 		32
#define	WLAN_KEY_LEN_TKIP 			32
#define	WLAN_KEY_LEN_AES_CMAC 		16
#define	WLAN_KEY_LEN_SMS4 			32
#define	WLAN_KEY_LEN_GCMP 			16
#define	WLAN_KEY_LEN_GCMP_256 		32
#define	WLAN_KEY_LEN_BIP_CMAC_256 	32
#define	WLAN_KEY_LEN_BIP_GMAC_128 	16
#define	WLAN_KEY_LEN_BIP_GMAC_256 	32

#define IEEE80211_WEP_IV_LENGTH			4
#define IEEE80211_WEP_ICV_LENGTH		4
#define IEEE80211_CCMP_HDR_LENGTH		8
#define IEEE80211_CCMP_MIC_LENGTH		8
#define IEEE80211_CCMP_PN_LENGTH		6
#define IEEE80211_CCMP_256_HDR_LENGTH	8
#define IEEE80211_CCMP_256_MIC_LENGTH	16
#define IEEE80211_CCMP_256_PN_LENGTH	6
#define IEEE80211_TKIP_IV_LENGTH		8
#define IEEE80211_TKIP_ICV_LENGTH		4
#define IEEE80211_CMAC_PN_LENGTH		6
#define IEEE80211_GMAC_PN_LENGTH		6
#define IEEE80211_GCMP_HDR_LENGTH		8
#define IEEE80211_GCMP_MIC_LENGTH		16
#define IEEE80211_GCMP_PN_LENGTH		6

#define FILS_NONCE_LENGTH			16
#define FILS_MAX_KEK_LENGTH		64

#define FILS_ERP_MAX_USERNAME_LENGTH	16
#define FILS_ERP_MAX_REALM_LENGTH		253
#define FILS_ERP_MAX_RRK_LENGTH		64

#define PMK_MAX_LENGTH			64
#define SAE_PASSWORD_MAX_LENGTH		128

/* Public action codes (IEEE Std 802.11-2016, 9.6.8.1, Table 9-307) */
#define WLAN_PUB_ACTION_20_40_BSS_COEX 				0
#define	WLAN_PUB_ACTION_DSE_ENABLEMENT 				1
#define	WLAN_PUB_ACTION_DSE_DEENABLEMENT 			2
#define	WLAN_PUB_ACTION_DSE_REG_LOC_ANN 			3
#define	WLAN_PUB_ACTION_EXT_CHANSW_ANN 				4
#define	WLAN_PUB_ACTION_DSE_MSMT_REQ  				5
#define	WLAN_PUB_ACTION_DSE_MSMT_RESP  				6
#define	WLAN_PUB_ACTION_MSMT_PILOT  				7
#define	WLAN_PUB_ACTION_DSE_PC  					8
#define	WLAN_PUB_ACTION_VENDOR_SPECIFIC  			9
#define	WLAN_PUB_ACTION_GAS_INITIAL_REQ  			10
#define	WLAN_PUB_ACTION_GAS_INITIAL_RESP  			11
#define	WLAN_PUB_ACTION_GAS_COMEBACK_REQ 			12
#define	WLAN_PUB_ACTION_GAS_COMEBACK_RESP 			13
#define	WLAN_PUB_ACTION_TDLS_DISCOVER_RES  			14
#define	WLAN_PUB_ACTION_LOC_TRACK_NOTI  			15
#define	WLAN_PUB_ACTION_QAB_REQUEST_FRAME  			16
#define	WLAN_PUB_ACTION_QAB_RESPONSE_FRAME  		17
#define	WLAN_PUB_ACTION_QMF_POLICY 					18
#define	WLAN_PUB_ACTION_QMF_POLICY_CHANGE  			19
#define	WLAN_PUB_ACTION_QLOAD_REQUEST  				20
#define	WLAN_PUB_ACTION_QLOAD_REPORT 				21
#define	WLAN_PUB_ACTION_HCCA_TXOP_ADVERT 			22
#define	WLAN_PUB_ACTION_HCCA_TXOP_RESPONSE  		23
#define	WLAN_PUB_ACTION_PUBLIC_KEY  				24
#define	WLAN_PUB_ACTION_CHANNEL_AVAIL_QUERY  		25
#define	WLAN_PUB_ACTION_CHANNEL_SCHEDULE_MGMT 		26
#define	WLAN_PUB_ACTION_CONTACT_VERI_SIGNAL  		27
#define	WLAN_PUB_ACTION_GDD_ENABLEMENT_REQ  		28
#define	WLAN_PUB_ACTION_GDD_ENABLEMENT_RESP  		29
#define	WLAN_PUB_ACTION_NETWORK_CHANNEL_CONTROL  	30
#define	WLAN_PUB_ACTION_WHITE_SPACE_MAP_ANN  		31
#define	WLAN_PUB_ACTION_FTM_REQUEST  				32
#define	WLAN_PUB_ACTION_FTM  						33
#define	WLAN_PUB_ACTION_FILS_DISCOVERY  			34

/* TDLS action codes */
#define WLAN_TDLS_SETUP_REQUEST 					0
#define	WLAN_TDLS_SETUP_RESPONSE 					1
#define	WLAN_TDLS_SETUP_CONFIRM  					2
#define	WLAN_TDLS_TEARDOWN 							3
#define	WLAN_TDLS_PEER_TRAFFIC_INDICATION  			4
#define	WLAN_TDLS_CHANNEL_SWITCH_REQUEST  			5
#define	WLAN_TDLS_CHANNEL_SWITCH_RESPONSE 			6
#define	WLAN_TDLS_PEER_PSM_REQUEST  				7
#define	WLAN_TDLS_PEER_PSM_RESPONSE  				8
#define	WLAN_TDLS_PEER_TRAFFIC_RESPONSE  			9
#define	WLAN_TDLS_DISCOVERY_REQUEST  				10

/* Ext-Chan-Switching capability to be set in the 1st byte of the
 * @WLAN_EID_EXT_CAPABILITY information element
 */
#define WLAN_EXT_CAPA1_EXT_CHAN_SWITCHING	BIT(2)

/* Multiple BSSID capability is set in the 6th bit of 3rd byte of the
 * @WLAN_EID_EXT_CAPABILITY information element
 */
#define WLAN_EXT_CAPA3_MULTIPLE_BSSID_SUPPORT	BIT(6)

#define WLAN_EXT_CAPA8_OPMODE_NOTIF	1<<6

/* Defines the maximal number of MSDUs in an A-MSDU. */
#define WLAN_EXT_CAPA8_MAX_MSDU_IN_AMSDU_LSB	1<<7
#define WLAN_EXT_CAPA9_MAX_MSDU_IN_AMSDU_MSB	1<<0

/*
 * Fine Timing Measurement Initiator - bit 71 of @WLAN_EID_EXT_CAPABILITY
 * information element
 */
#define WLAN_EXT_CAPA9_FTM_INITIATOR	1<<7

/* Defines support for TWT Requester and TWT Responder */
#define WLAN_EXT_CAPA10_TWT_REQUESTER_SUPPORT	1<<5
#define WLAN_EXT_CAPA10_TWT_RESPONDER_SUPPORT	1<<6

/*
 * When set, indicates that the AP is able to tolerate 26-tone RU UL
 * OFDMA transmissions using HE TB PPDU from OBSS (not falsely classify the
 * 26-tone RU UL OFDMA transmissions as radar pulses).
 */
#define WLAN_EXT_CAPA10_OBSS_NARROW_BW_RU_TOLERANCE_SUPPORT 1<<7

/* Defines support for enhanced multi-bssid advertisement*/
#define WLAN_EXT_CAPA11_EMA_SUPPORT	1<<1

/* TDLS specific payload type in the LLC/SNAP header */
#define WLAN_TDLS_SNAP_RFTYPE	0x2

/* BSS Coex IE information field bits */
#define WLAN_BSS_COEX_INFORMATION_REQUEST	1<<0


#define WLAN_TIMEOUT_REASSOC_DEADLINE  	1 /* 802.11r */
#define	WLAN_TIMEOUT_KEY_LIFETIME 		2 /* 802.11r */
#define	WLAN_TIMEOUT_ASSOC_COMEBACK 	3 /* 802.11w */

/**
 * struct ieee80211_timeout_interval - Timeout Interval element
 * @type: type, see &enum ieee80211_timeout_interval_type
 * @value: timeout interval value
 */
#pragma pack(1)
struct ieee80211_timeout_interval {
	u8 type;
	le32 value;
};
#pragma pack()

/* Block ack action code */
enum ieee80211_back_action_code {
    WLAN_ACTION_ADDBA_REQUEST = 0,
    WLAN_ACTION_ADDBA_RESPONSE = 1,
    WLAN_ACTION_DELBA = 2,
};

/* SA Query Action codes (IEEE 802.11w/D8.0, 7.4.9) */
enum ieee80211_sa_query_action_code {
    /* request */
    WLAN_ACTION_SA_QUERY_REQUEST = 0,
    /* response */
    WLAN_ACTION_SA_QUERY_RESPONSE = 1,
};

/* "BSS Max idle period element" */
#pragma pack(1)
enum ieee80211_idle_options {
	WLAN_IDLE_OPTIONS_PROTECTED_KEEP_ALIVE = BIT(0),
};

struct ieee80211_bss_max_idle_period {
	le16 max_idle_period;
	u8 idle_options;
};
#pragma pack()

/* Multiple BSSID */
#pragma pack(1)
/* "Multiple BSSID-index element" */
struct ieee80211_bssid_index {
    /* A value between 1 and 2n- 1 that identifies the 
     * nontransmitted BSSID.
     */
	u8 bssid_index;
	u8 dtim_period; /* optional */
	u8 dtim_count;  /* optional */
};

/* "Multiple BSSID Configuration element" */
struct ieee80211_mbssid_configuration {
    /* Carries the total number of active BSSIDs
     * in the multiple BSSID set. 
     */
	u8 bssid_count;

    /* indicates the least number of Beacon frames or 
     * DMG Beacon frames a STA needs to receive in order to 
     * discover all the active nontransmitted BSSIDs in the set. */
	u8 profile_periodicity;
};
#pragma pack()

/**
 * ieee80211_get_qos_ctl - get pointer to qos control bytes
 * @hdr: the frame
 *

 */
static inline u8 *ieee80211_get_qos_ctl(struct ieee80211_hdr *hdr)
{
    /*
     * The qos ctrl bytes come after the frame_control, duration, seq_num
     * and 3 or 4 addresses.
     * 3 address: 2 + 2 + 2 + 3*6 = 24
     * 4 address: 2 + 2 + 2 + 4*6 = 30
     */
    u8 offset = ieee80211_has_a4(hdr->frame_control) ? 30 : 24;

    return (u8 *)hdr + offset;
}

/**
 * get qos TID from a frame
 */
static inline u8 ieee80211_get_tid(struct ieee80211_hdr *hdr)
{
	u8 *qos_ctl = ieee80211_get_qos_ctl(hdr);
	return qos_ctl[0] & IEEE80211_QOS_TID_MASK;
}

/**
 * returns the pointer to the source address (SA)
 */
static inline u8 *ieee80211_get_sa(struct ieee80211_hdr *hdr)
{
    le16 fc = hdr->frame_control;
	if (ieee80211_has_a4(fc))
		return hdr->addr4;
	if (ieee80211_has_fromds(fc))
		return hdr->addr3;
	return hdr->addr2;
}

/* Returns the pointer to the destination address (DA). */
static inline u8 *ieee80211_get_da(struct ieee80211_hdr *hdr)
{
    return ieee80211_has_tods(hdr->frame_control) ? 
        hdr->addr3 : hdr->addr1;
}

/**
 * _ieee80211_is_robust_mgmt_frame - check if frame is a robust management frame
 */
static inline bool _ieee80211_is_robust_mgmt_frame(struct ieee80211_hdr *hdr)
{
	le16 fc = hdr->frame_control;

	if (ieee80211_is_disassoc(fc) ||
		ieee80211_is_deauth(fc))
		return true;

	if (ieee80211_is_action(fc)) {
		u8 category;

		/* Skip the check if it is a protected frame */
		if (ieee80211_has_protected(fc))
			return true;
		category = *(((u8 *) hdr) + 24);
		if (category == WLAN_ACTION_PUBLIC ||
			category == WLAN_ACTION_HT ||
			category == WLAN_ACTION_VHT ||
			category == WLAN_ACTION_UNPROTECTED_WNM ||
			category == WLAN_ACTION_SELF_PROTECTED ||
			category == WLAN_ACTION_UNPROTECTED_DMG ||
			category == WLAN_ACTION_VENDOR_SPECIFIC)
			return false;

		return true;
	}

	return false;
}

/* Check if skb contains a robust mgmt frame */
static inline bool ieee80211_is_robust_mgmt_frame(struct sk_buff *skb)
{
	if (skb->len < IEEE80211_ACTION_MIN_SIZE)
		return false;
	return _ieee80211_is_robust_mgmt_frame((void *)skb->data);
}

/* Check if frame is a public action frame */
static inline bool ieee80211_is_public_action(struct ieee80211_hdr *hdr,
    u32 len)
{
	struct ieee80211_mgmt *mgmt = (void *)hdr;
	if (len < IEEE80211_ACTION_MIN_SIZE)
		return false;
	if (ieee80211_is_action(mgmt->frame_control) && 
        (mgmt->u.action.category == WLAN_ACTION_PUBLIC))
		return true;
    return false;
}

/* Convert time units (TU) to microseconds */
static inline unsigned long ieee80211_tu_to_usec(unsigned long tu)
{
	return 1024 * tu;
}

/* Orginal from wpa_supplicant from ieee802_11_common.h */

#pragma pack(1)
struct element {
	u8 id;
	u8 datalen;
	u8 data[];
};
#pragma pack()

/* element iteration helpers */
#define for_each_element(_elem, _data, _datalen)			      \
	for (_elem = (const struct element *)(_data);			      \
	     (const u8 *)(_data) + (_datalen) - (const u8 *)_elem >=  \
		(int)sizeof(*_elem) &&					                  \
	     (const u8 *)(_data) + (_datalen) - (const u8 *)_elem >=  \
		(int)sizeof(*_elem) + _elem->datalen;			          \
	     _elem = (const struct element *)(_elem->data + _elem->datalen))

#define for_each_element_id(element, _id, data, datalen)		  \
	for_each_element(element, data, datalen)			          \
		if (element->id == (_id))

#define for_each_element_extid(element, extid, _data, _datalen)	 \
	for_each_element(element, _data, _datalen)			         \
		if (element->id == WLAN_EID_EXTENSION &&		         \
		    element->datalen > 0 &&				                 \
		    element->data[0] == (extid))

#define for_each_subelement(sub, element)				         \
	for_each_element(sub, (element)->data, (element)->datalen)

#define for_each_subelement_id(sub, id, element)			     \
	for_each_element_id(sub, id, (element)->data, (element)->datalen)

#define for_each_subelement_extid(sub, extid, element)			\
	for_each_element_extid(sub, extid, (element)->data, (element)->datalen)

/**
 * for_each_element_completed - determine if element parsing consumed all data
 * @element: element pointer after for_each_element() or friends
 * @data: same data pointer as passed to for_each_element() or friends
 * @datalen: same data length as passed to for_each_element() or friends
 */
static inline bool for_each_element_completed(const struct element *element,
					      const void *data, size_t data_len)
{
	return (const u8 *)element == (const u8 *)data + data_len;
}

#define SUITE_SELECTOR(a, b, c, d) \
	((((u32)(d)) << 24) | (((u32)(c)) << 16) | (((u32)(b)) << 8) | \
	 (u32)(a))

/* AKM suite selectors */
#define WLAN_RSN_AKM_SUITE_8021X          SUITE_SELECTOR(0x00, 0x0f, 0xac, 1)
#define WLAN_RSN_AKM_SUITE_PSK            SUITE_SELECTOR(0x00, 0x0f, 0xac, 2)
#define WLAN_RSN_AKM_SUITE_8021X_SHA256   SUITE_SELECTOR(0x00, 0x0f, 0xac, 5)
#define WLAN_RSN_AKM_SUITE_PSK_SHA256     SUITE_SELECTOR(0x00, 0x0f, 0xac, 6)
#define WLAN_RSN_AKM_SUITE_SAE            SUITE_SELECTOR(0x00, 0x0f, 0xac, 8)
#define WLAN_RSN_AKM_SUITE_SUITE_B        SUITE_SELECTOR(0x00, 0x0f, 0xac, 11)
#define WLAN_RSN_AKM_SUITE_SUITE_B_192    SUITE_SELECTOR(0x00, 0x0f, 0xac, 12)

/* Cipher suite selectors */
#define WLAN_RSN_CIPHER_SUITE_WEP40 SUITE_SELECTOR(0x00, 0x0f, 0xac, 1)
#define WLAN_RSN_CIPHER_SUITE_TKIP SUITE_SELECTOR(0x00, 0x0f, 0xac, 2)

#define WLAN_RSN_CIPHER_SUITE_CCMP SUITE_SELECTOR(0x00, 0x0f, 0xac, 4)
#define WLAN_RSN_CIPHER_SUITE_WEP104 SUITE_SELECTOR(0x00, 0x0f, 0xac, 5)
#define WLAN_RSN_CIPHER_SUITE_AES_CMAC SUITE_SELECTOR(0x00, 0x0f, 0xac, 6)

#define WLAN_RSN_CIPHER_SUITE_GCMP SUITE_SELECTOR(0x00, 0x0f, 0xac, 8)
#define WLAN_RSN_CIPHER_SUITE_GCMP_256 SUITE_SELECTOR(0x00, 0x0f, 0xac, 9)
#define WLAN_RSN_CIPHER_SUITE_CCMP_256 SUITE_SELECTOR(0x00, 0x0f, 0xac, 10)
#define WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128 SUITE_SELECTOR(0x00, 0x0f, 0xac, 11)
#define WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256 SUITE_SELECTOR(0x00, 0x0f, 0xac, 12)
#define WLAN_RSN_CIPHER_SUITE_BIP_CMAC_256 SUITE_SELECTOR(0x00, 0x0f, 0xac, 13)

/* OUI */
#define WLAN_OUI_MICROSOFT 0x0050f2 /* Microsoft (also used in Wi-Fi specs) 00:50:F2 */
#define WLAN_OUI_MICROSOFT_WPA 0x0050f201
#define WLAN_OUI_MICROSOFT_WMM 0x0050f202
#define WLAN_OUI_MICROSOFT_WPS 0x0050f204

#define IEEE80211_HT_CHANWIDTH_20MHZ 	0
#define IEEE80211_HT_CHANWIDTH_ANY 		1

/* Management MIC information element (IEEE 802.11w) */
#pragma pack(1)
struct ieee80211_mmie {
	u8 element_id;
	u8 length;
	le16 key_id;
	u8 sequence_number[6];
	u8 mic[8];
};
#pragma pack()

/* Management MIC information element (IEEE 802.11w) for GMAC and CMAC-256 */
#pragma pack(1)
struct ieee80211_mmie_16 {
	u8 element_id;
	u8 length;
	le16 key_id;
	u8 sequence_number[6];
	u8 mic[16];
};
#pragma pack()

/* Channel switch timing */
#pragma pack(1)
struct ieee80211_ch_switch_timing {
	le16 switch_time;
	le16 switch_timeout;
};
#pragma pack()

/*
 * WME/802.11e information element.
 */
#pragma pack(1)
struct ieee80211_wmm_ie {
    u8 element_id;
    u8 length;
    u8 oui[3];     /* 0x00, 0x50, 0xf2 */
    u8 oui_type;
    u8 subtype;    /* OUI subtype */
    u8 version;    /* spec revision */
    u8 qosinfo;    /* QoS info */
};
#pragma pack()

#pragma pack(1)
struct ieee80211_mcs_info {
	u8 rx_mask[IEEE80211_HT_MCS_MASK_LEN];
	u8 tx_params;
	le16 rx_highest;
	u8 reserved[3];
};
#pragma pack()

#pragma pack(1)
struct ieee80211_ht_capabilities {
	le16 ht_capabilities_info;
	u8 ampdu_params_info;

	/* 16 bytes MCS information */
	struct ieee80211_mcs_info mcs;

	le16 ht_extended_capabilities;
	le32 tx_bf_capability_info;
	u8 antenna_selection_info;
};
#pragma pack()

/* for operation_mode */
#define IEEE80211_HT_OP_MODE_CCFS2_SHIFT	5
#define IEEE80211_HT_OP_MODE_CCFS2_MASK		0x1fe0

#pragma pack(1)
struct ieee80211_vht_mcs_info {
	le16 rx_mcs_map;
	le16 rx_highest;
	le16 tx_mcs_map;
	le16 tx_highest;
};

struct ieee80211_vht_capabilities {
	le32 vht_capabilities_info;
	struct ieee80211_vht_mcs_info supported_mcs_set;
};
#pragma pack()

/* VHT operation mode subfields - 802.11ac-2013 Table 8.183x */
#define	IEEE80211_VHT_CHANWIDTH_USE_HT		0	/* Use HT IE for chw */
#define	IEEE80211_VHT_CHANWIDTH_80MHZ		1	/* 80MHz */
#define	IEEE80211_VHT_CHANWIDTH_160MHZ		2	/* 160MHz */
#define	IEEE80211_VHT_CHANWIDTH_80P80MHZ	3	/* 80+80MHz */

/* VHT operation element */
#pragma pack(1)
struct ieee80211_vht_operation {
	u8 chan_width;
	u8 center_freq_seg0_idx;
	u8 center_freq_seg1_idx;
	le16 basic_mcs_set;
};
#pragma pack()

#pragma pack(1)
struct ieee80211_tspec_ie {
	u8 element_id;
	u8 len;
	u8 oui[3];
	u8 oui_type;
	u8 oui_subtype;
	u8 version;
	le16 tsinfo;
	u8 tsinfo_resvd;
	le16 nominal_msdu;
	le16 max_msdu;
	le32 min_service_int;
	le32 max_service_int;
	le32 inactivity_int;
	le32 suspension_int;
	le32 service_start_time;
	le32 min_data_rate;
	le32 mean_data_rate;
	le32 peak_data_rate;
	le32 max_burst_size;
	le32 delay_bound;
	le32 min_phy_rate;
	le16 sba;
	le16 medium_time;
};
#pragma pack()

#pragma pack(1)
struct ieee80211_country_triplet {
    union {
        struct {
            u8 first_chan;
            u8 num_chans;
            s8 max_power;
        } chans;
        struct {
            u8 reg_ext_id;
            u8 reg_class;
            u8 coverage_class;
        } ext;
    } u;
};
#pragma pack()

#define IEEE80211_COUNTRY_EXTENSION_ID 201

#define IEEE80211_HE_6GHZ_MAX_AMPDU_FACTOR       13

#pragma pack(1)
struct ieee80211_he_6ghz_cap {
	/* uses IEEE80211_HE_6GHZ_CAP_* below */
	__le16 cap;
} __packed;
#pragma pack()

/* HE 6 GHz band capabilities */
/* uses enum ieee80211_min_mpdu_spacing values */
#define IEEE80211_HE_6GHZCAP_MIN_MPDU_START	0x0007
/* uses enum ieee80211_vht_max_ampdu_length_exp values */
#define IEEE80211_HE_6GHZCAP_MAX_AMPDU_LEN_EXP	0x0038
/* uses IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_* values */
#define IEEE80211_HE_6GHZCAP_MAX_MPDU_LEN	0x00c0
/* WLAN_HT_CAP_SM_PS_* values */
#define IEEE80211_HE_6GHZCAP_SM_PS		0x0600
#define IEEE80211_HE_6GHZCAP_RD_RESPONDER	0x0800
#define IEEE80211_HE_6GHZCAP_RX_ANTPAT_CONS	0x1000
#define IEEE80211_HE_6GHZCAP_TX_ANTPAT_CONS	0x2000

/* utils */
u32 ieee80211_channel_to_frequency(int chan, enum nl80211_band band);
int ieee80211_frequency_to_channel(u32 freq);
u32 ieee80211_hdrlen(le16 fc);
const struct element *ieee80211_find_element(const u8 *ies, u32 len, u8 eid);
const struct element *ieee80211_find_vendor_element(const u8 *ies, u32 len, u32 oui);
const struct element *ieee80211_find_extension_element(const u8 *ies, u32 len, u8 eeid);

#endif // !__IEEE80211_H

#ifndef __NET_MAC80211_DEFS_H
#define __NET_MAC80211_DEFS_H

/* ieee80211_channel */
enum ieee80211_channel_flags {
    IEEE80211_CHAN_DISABLED = BIT(0),
    IEEE80211_CHAN_NO_IR = BIT(1),
    IEEE80211_CHAN_RADAR = BIT(3),
    IEEE80211_CHAN_NO_HT40PLUS = BIT(4),
    IEEE80211_CHAN_NO_HT40MINUS = BIT(5),
    IEEE80211_CHAN_NO_OFDM = BIT(6),
    IEEE80211_CHAN_NO_80MHZ = BIT(7),
    IEEE80211_CHAN_NO_160MHZ = BIT(8),
    IEEE80211_CHAN_INDOOR_ONLY = BIT(9),
    IEEE80211_CHAN_IR_CONCURRENT = BIT(10),
    IEEE80211_CHAN_NO_20MHZ = BIT(11),
    IEEE80211_CHAN_NO_10MHZ = BIT(12),
    IEEE80211_CHAN_NO_HE = BIT(13),
};

#define IEEE80211_CHAN_NO_HT40 \
	(IEEE80211_CHAN_NO_HT40PLUS | IEEE80211_CHAN_NO_HT40MINUS)

struct ieee80211_channel
{
    enum nl80211_band band;
    u32 center_freq;
	u16 freq_offset;
	u16 hw_value;
    u16 ieee;
    u32 flags;
    int max_antenna_gain;
    int max_power;
    int max_reg_power;
};

enum ieee80211_rate_flags {
    IEEE80211_RATE_SHORT_PREAMBLE = 1 << 0,
    IEEE80211_RATE_MANDATORY_A = 1 << 1,
    IEEE80211_RATE_MANDATORY_B = 1 << 2,
    IEEE80211_RATE_MANDATORY_G = 1 << 3,
    IEEE80211_RATE_ERP_G = 1 << 4,
    IEEE80211_RATE_SUPPORTS_5MHZ = 1 << 5,
    IEEE80211_RATE_SUPPORTS_10MHZ = 1 << 6,
};

struct ieee80211_rate {
    u32 flags;
    u16 bitrate;
    u16 hw_value;
    u16 hw_value_short;
};

#define IEEE80211_MAX_CHAINS	4

enum ieee80211_hw_flags {
    IEEE80211_HW_HAS_RATE_CONTROL,
    IEEE80211_HW_SIGNAL_DBM,
    IEEE80211_HW_SPECTRUM_MGMT,
    IEEE80211_HW_AMPDU_AGGREGATION,
    IEEE80211_HW_SUPPORTS_PS,
    IEEE80211_HW_SUPPORTS_DYNAMIC_PS,
    IEEE80211_HW_MFP_CAPABLE,
    IEEE80211_HW_WANT_MONITOR_VIF,
    IEEE80211_HW_SUPPORT_FAST_XMIT,
    IEEE80211_HW_REPORTS_TX_ACK_STATUS,
    IEEE80211_HW_CONNECTION_MONITOR,
    IEEE80211_HW_QUEUE_CONTROL,
    IEEE80211_HW_SUPPORTS_PER_STA_GTK,
    IEEE80211_HW_AP_LINK_PS,
    IEEE80211_HW_TX_AMPDU_SETUP_IN_HW,
    IEEE80211_HW_CHANCTX_STA_CSA,
	IEEE80211_HW_SINGLE_SCAN_ON_ALL_BANDS,
    IEEE80211_HW_SUPPORTS_AMSDU_IN_AMPDU,
    IEEE80211_HW_NEEDS_UNIQUE_STA_ADDR,
    IEEE80211_HW_SUPPORTS_REORDERING_BUFFER,
    IEEE80211_HW_USES_RSS,
	IEEE80211_HW_TX_AMSDU,
	IEEE80211_HW_TX_FRAG_LIST,
    IEEE80211_HW_REPORTS_LOW_ACK,
    IEEE80211_HW_SUPPORTS_TX_FRAG,
    IEEE80211_HW_SUPPORTS_VHT_EXT_NSS_BW,
    IEEE80211_HW_SUPPORTS_ONLY_HE_MULTI_BSSID,
    IEEE80211_HW_SUPPORTS_TX_ENCAP_OFFLOAD,
	IEEE80211_HW_SUPPORTS_RX_DECAP_OFFLOAD,

    /* keep last, obviously */
    NUM_IEEE80211_HW_FLAGS
};

/* chanctx */
struct ieee80211_chan_def {
    struct ieee80211_channel *chan;
    enum nl80211_chan_width width;
    u32 center_freq1;
    u32 center_freq2;
	//struct ieee80211_edmg edmg;  //TODOTODO: edmg is not supported now.
	u16 freq1_offset;
};

struct ieee80211_chanctx_conf {
	struct ieee80211_chan_def def;
	struct ieee80211_chan_def min_def;

    /* smps */
    u8 rx_chains_static;
    u8 rx_chains_dynamic;
	bool radar_enabled;
};

struct ieee80211_chanctx {
    list_entry_t list;
    list_entry_t assigned_vifs;
    bool driver_present;
    struct ieee80211_chanctx_conf conf;
};

enum ieee80211_chanctx_change {
    IEEE80211_CHANCTX_CHANGE_WIDTH = BIT(0),
    IEEE80211_CHANCTX_CHANGE_RX_CHAINS = BIT(1),
    IEEE80211_CHANCTX_CHANGE_RADAR = BIT(2),
    IEEE80211_CHANCTX_CHANGE_CHANNEL = BIT(3),
    IEEE80211_CHANCTX_CHANGE_MIN_WIDTH = BIT(4),
};

/* chanctx switch */
enum ieee80211_chanctx_switch_mode {
    CHANCTX_SWMODE_REASSIGN_VIF,
    CHANCTX_SWMODE_SWAP_CONTEXTS,
};

struct ieee80211_vif_chanctx_switch {
    struct ieee80211_vif *vif;
    struct ieee80211_chanctx_conf *old_ctx;
    struct ieee80211_chanctx_conf *new_ctx;
};

/* supported band capabiliites */
struct ieee80211_sta_ht_cap {
    bool ht_supported;
    u16 cap; /* use IEEE80211_HT_CAP_ */
    u8 ampdu_factor;
    u8 ampdu_density;
    struct ieee80211_mcs_info mcs;
};

struct ieee80211_sta_vht_cap {
    bool vht_supported;
    u32 cap; /* use IEEE80211_VHT_CAP_ */
    struct ieee80211_vht_mcs_info vht_mcs;
};

#define IEEE80211_HE_PPE_THRES_MAX_LEN		25

struct ieee80211_sta_he_cap {
    bool he_supported;
    struct ieee80211_he_capabilities he_capabilities;
    struct ieee80211_he_mcs_nss_supp he_mcs_nss_supp;
    u8 ppe_thres[IEEE80211_HE_PPE_THRES_MAX_LEN];
};

struct ieee80211_sband_iftype_data {
    u16 types_mask;
    struct ieee80211_sta_he_cap he_cap;
	struct ieee80211_he_6ghz_cap he_6ghz_cap;
};

struct ieee80211_supported_band {
    struct ieee80211_channel *channels;
    struct ieee80211_rate *bitrates;
    enum nl80211_band band;
    u32 n_channels;
    u32 n_bitrates;
    struct ieee80211_sta_ht_cap ht_cap;
    struct ieee80211_sta_vht_cap vht_cap;
    u16 n_iftype_data;
    const struct ieee80211_sband_iftype_data *iftype_data;
};

static inline const struct ieee80211_sband_iftype_data *
ieee80211_get_sband_iftype_data(const struct ieee80211_supported_band *sband,
    u8 iftype)
{
    const struct ieee80211_sband_iftype_data *iftype_data = NULL;
    u16 i;

    if (iftype < NL80211_IFTYPE_MAX) {
        for (i = 0; i < sband->n_iftype_data; i++) {
            if (sband->iftype_data[i].types_mask & BIT(iftype)) {
                iftype_data = &sband->iftype_data[i];
                break;
            }
        }
    }

    return iftype_data;
}

u32 ieee80211_ie_split_ric(const u8* ies, u32 ielen,
	const u8* ids, int n_ids,
	const u8* after_ric, int n_after_ric,
	u32 offset);

static inline u32 ieee80211_ie_split(const u8 *ies, u32 ielen,
	const u8 *ids, int n_ids, u32 offset)
{
	return ieee80211_ie_split_ric(ies, ielen, ids, n_ids, NULL, 0, offset);
}

static inline const struct ieee80211_sta_he_cap *
ieee80211_get_iftype_he_cap(const struct ieee80211_supported_band *sband,
    u8 iftype)
{
    const struct ieee80211_sband_iftype_data *iftype_data =
        ieee80211_get_sband_iftype_data(sband, iftype);

    if (!iftype_data)
        return NULL;
    if (!iftype_data->he_cap.he_supported)
        return NULL;
    return &iftype_data->he_cap;
}

static inline const struct ieee80211_sta_he_cap *
ieee80211_get_sta_he_cap(const struct ieee80211_supported_band *sband)
{
    return ieee80211_get_iftype_he_cap(sband, NL80211_IFTYPE_STATION);
}

static inline __le16
ieee80211_get_he_6ghz_cap(const struct ieee80211_supported_band *sband,
    enum nl80211_iftype iftype)
{
    const struct ieee80211_sband_iftype_data *data =
        ieee80211_get_sband_iftype_data(sband, iftype);

    if (WARN_ON(!data || !data->he_cap.he_supported))
        return 0;

    return data->he_6ghz_cap.cap;
}

struct mac_address {
    u8 addr[ETH_ALEN];
};

enum ieee80211_bss_type {
    IEEE80211_BSS_TYPE_ESS,
    IEEE80211_BSS_TYPE_PBSS,
    IEEE80211_BSS_TYPE_IBSS,
    IEEE80211_BSS_TYPE_MBSS,
    IEEE80211_BSS_TYPE_ANY
};

/* Access Categories */
enum ieee80211_ac_numbers {
    IEEE80211_AC_VO = 0,  /* Voice */
    IEEE80211_AC_VI = 1,  /* Video */
    IEEE80211_AC_BE = 2,  /* Best Effort */
    IEEE80211_AC_BK = 3,  /* Background */
};

struct ieee80211_sta_txpwr {
    s16 power;
    enum nl80211_tx_power_setting type;
};

struct ieee80211_ssid {
	u8 ssid_len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
};

enum ieee80211_filter_flags {
    IEEE80211_FIF_ALLMULTI = 1 << 1,
    IEEE80211_FIF_FCSFAIL = 1 << 2,
    IEEE80211_FIF_PLCPFAIL = 1 << 3,
    IEEE80211_FIF_BCN_PRBRESP_PROMISC = 1 << 4,
    IEEE80211_FIF_CONTROL = 1 << 5,
    IEEE80211_FIF_OTHER_BSS = 1 << 6,
    IEEE80211_FIF_PSPOLL = 1 << 7,
    IEEE80211_FIF_PROBE_REQ = 1 << 8,
};

struct ieee80211_tx_queue_params {
    u16 txop;
    u16 cw_min;
    u16 cw_max;
    u8 aifs;
    bool acm;
    bool uapsd;
    bool mu_edca;
    struct ieee80211_he_mu_edca_param_ac_record mu_edca_param_record;
};

/* Maximal size of an A-MSDU that can be transported in a HT BA session */
#define IEEE80211_MAX_MPDU_LEN_HT_BA		4095

enum ieee80211_smps_mode {
    IEEE80211_SMPS_AUTOMATIC,   /* automatic */
    IEEE80211_SMPS_NONE,        /* none */
    IEEE80211_SMPS_STATIC,      /* static */
    IEEE80211_SMPS_DYNAMIC,     /* dynamic */

	/* keep last */
	IEEE80211_SMPS_NUM_MODES,
};

/* station state */
enum ieee80211_sta_state {
    /* NOTE: these state should be ordered correctly! */
    IEEE80211_STA_NOTEXIST,    /* station doesn't exist at all */
    IEEE80211_STA_NONE,        /* station exists without special state */
    IEEE80211_STA_AUTH,        /* station is authenticated */
    IEEE80211_STA_ASSOC,       /* station is associated */
    IEEE80211_STA_AUTHORIZED,  /* station is authorized (802.1X) */
};

enum ieee80211_rate_control_changed {
    IEEE80211_RC_CHANGED_BW = BIT(0),
    IEEE80211_RC_CHANGED_SMPS = BIT(1),
    IEEE80211_RC_CHANGED_SUPP_RATES = BIT(2),
    IEEE80211_RC_CHANGED_NSS = BIT(3),
};

/* Parsed Information Elements */
struct ieee802_11_elems {
    const u8 *ie_start;
    size_t total_len;
    const struct ieee80211_ch_switch_timing *ch_sw_timing;
	const struct ieee80211_tim *tim;
	const u8 *ssid;
    const u8 *ext_capab;
    const u8 *supp_rates;
    const u8 *ds_params;
    const u8 *challenge;
    const u8 *rsn;
    const u8 *rsnx;
    const u8 *wmm_info;
    const u8 *wmm_param;
	const u8 *erp_info;
    const u8 *ext_supp_rates;
	const struct ieee80211_ht_operation *ht_operation;
    const struct ieee80211_ht_capabilities *ht_capabilities;
	const struct ieee80211_vht_operation *vht_operation;
    const struct ieee80211_vht_capabilities *vht_capabilities;
    const struct ieee80211_he_operation *he_operation;
    const u8 *he_cap;
	const struct ieee80211_he_spr* he_spr;
    const struct ieee80211_he_mu_edca_param_set *mu_edca_param_set;
	const struct ieee80211_he_6ghz_cap *he_6ghz_cap;
	const u8 *peering;
	const u8 *mesh_id;
	const u8 *uora_element;
    const struct ieee80211_chan_switch *chan_switch;
    const struct ieee80211_extended_chan_switch *extended_chan_switch;
    const struct ieee80211_wide_bw_chansw *wide_bw_chansw;
    const u8 *max_channel_switch_time;
    const u8 *country_elem;
    const u8 *power_constraint_elem;
    const struct ieee80211_timeout_interval *timeout_int;
    const u8 *opmode_notif;
    const struct ieee80211_sec_chan_offset *sec_chan_offset;
    const struct ieee80211_bss_max_idle_period *bss_max_idle_period;
    const struct ieee80211_mbssid_configuration *mbssid_config;
    const struct ieee80211_addba_extension *addba_extension;
	const struct ieee80211_bssid_index *bssid_index;
	u8 mesh_id_len;
    u8 peering_len;
    u8 country_elem_len;
    u8 bssid_index_len;
    u8 ext_capab_len;
    u8 ssid_len;
    u8 supp_rates_len;
    u8 tim_len;
    u8 wmm_info_len;
    u8 wmm_param_len;
    u8 he_cap_len;
    u8 he_operation_len;
	u8 challenge_len;
    u8 rsn_len;
    u8 rsnx_len;
    u8 ext_supp_rates_len;

    /* set when elements are not parsed completedly or error is seen */
    bool parse_error;
};

enum ieee80211_privacy {
    IEEE80211_PRIVACY_ON,
    IEEE80211_PRIVACY_OFF,
    IEEE80211_PRIVACY_ANY
};

#define IEEE80211_PRIVACY(x)	\
	((x) ? IEEE80211_PRIVACY_ON : IEEE80211_PRIVACY_OFF)

enum ieee80211_interface_iteration_flags {
    IEEE80211_VIF_ITER_NORMAL = 0,
    IEEE80211_VIF_ITER_ACTIVE = 1,
    IEEE80211_VIF_ITER_INACTIVE = 2,
};

enum ieee80211_bss_change {
    BSS_CHANGED_ASSOC = BIT(0),
    BSS_CHANGED_ERP_CTS_PROT = BIT(1),
    BSS_CHANGED_ERP_PREAMBLE = BIT(2),
    BSS_CHANGED_ERP_SLOT = BIT(3),
    BSS_CHANGED_HT = BIT(4),
    BSS_CHANGED_BASIC_RATES = BIT(5),
    BSS_CHANGED_BEACON_INT = BIT(6),
    BSS_CHANGED_BSSID = BIT(7),
    BSS_CHANGED_BEACON = BIT(8),
    BSS_CHANGED_BEACON_ENABLED = BIT(9),
    BSS_CHANGED_CQM = BIT(10),
    BSS_CHANGED_IBSS = BIT(11),
    BSS_CHANGED_ARP_FILTER = BIT(12),
    BSS_CHANGED_QOS = BIT(13),
    BSS_CHANGED_IDLE = BIT(14),
    BSS_CHANGED_SSID = BIT(15),
    BSS_CHANGED_AP_PROBE_RESP = BIT(16),
    BSS_CHANGED_PS = BIT(17),
    BSS_CHANGED_TXPOWER = BIT(18),
    BSS_CHANGED_P2P_PS = BIT(19),
    BSS_CHANGED_BEACON_INFO = BIT(20),
    BSS_CHANGED_BANDWIDTH = BIT(21),
    BSS_CHANGED_OCB = BIT(22),
    BSS_CHANGED_MU_GROUPS = BIT(23),
    BSS_CHANGED_KEEP_ALIVE = BIT(24),
    BSS_CHANGED_MCAST_RATE = BIT(25),
    BSS_CHANGED_FTM_RESPONDER = BIT(26),
    BSS_CHANGED_TWT = BIT(27),
    BSS_CHANGED_HE_OBSS_PD = BIT(28),
    BSS_CHANGED_HE_BSS_COLOR = BIT(29),
};

enum ieee80211_wpa_type {
    IEEE80211_WPA_TYPE_NONE = 0,
    IEEE80211_WPA_TYPE_RSN = 1,
    IEEE80211_WPA_TYPE_WPA = 2
};

enum ieee80211_priv_cmd_id {
    IEEE80211_PRIV_CMD_NONE = 0,
    IEEE80211_PRIV_CMD_RDDM,
    IEEE80211_PRIV_CMD_CCODE,

    IEEE80211_PRIV_CMD_MAX
};

struct ieee80211_priv_cmd {
    u32 id;
    u32 len;
    u8 data[0];
};

#define IEEE80211_FRAME_HEADER_LEN   24
#define IEEE80211_DEAUTH_FRAME_LEN	(IEEE80211_FRAME_HEADER_LEN /* hdr */ + 2 /* reason */ + 64 /* iv + mic */ + 16 /*reserved*/)

#define IEEE80211_RSN_CAP_PTKSA_REPLAYCOUNTER     0x0c
#define IEEE80211_RSN_CAP_GTKSA_REPLAYCOUNTER     0x30
#define IEEE80211_RSN_CAP_MFP_REQUIRED            0x40
#define IEEE80211_RSN_CAP_MFP_ENABLED             0x80

/* B2-B3: PTKSA Replay Counter */
#define IEEE80211_RSN_CAP_PTKSA_RC0 BIT(2)
#define IEEE80211_RSN_CAP_PTKSA_RC1 BIT(3)
/* B4-B5: GTKSA Replay Counter */
#define IEEE80211_RSN_CAP_GTKSA_RC0 BIT(4)
#define IEEE80211_RSN_CAP_GTKSA_RC1 BIT(5)
/* B6: Mgmt Frame Protect Required */
#define IEEE80211_RSN_CAP_MFPR BIT(6)
/* B7: Mgmt Frame Protect Enabled */
#define IEEE80211_RSN_CAP_MFPC BIT(7)

#define IEEE80211_RSNXE_CAP_SAE_H2E               0x20

/* struct ieee80211_bitrate_mask */
struct ieee80211_bitrate_control {
    enum nl80211_txrate_gi gi;
    u32 legacy;
    u8 ht_mcs[IEEE80211_HT_MCS_MASK_LEN]; /* HT */
    u16 vht_mcs[NL80211_VHT_NSS_MAX];     /* VHT */
};

struct ieee80211_bitrate_mask {
    struct ieee80211_bitrate_control control[NUM_NL80211_BANDS];
};

enum ieee80211_rate_info_bw {
    IEEE80211_RATE_INFO_BW_20 = 0,
    IEEE80211_RATE_INFO_BW_5,
    IEEE80211_RATE_INFO_BW_10,
    IEEE80211_RATE_INFO_BW_40,
    IEEE80211_RATE_INFO_BW_80,
    IEEE80211_RATE_INFO_BW_160,
};

enum ieee80211_rate_info_flags {
    IEEE80211_RATE_INFO_FLAGS_MCS = BIT(0),
    IEEE80211_RATE_INFO_FLAGS_VHT_MCS = BIT(1),
    IEEE80211_RATE_INFO_FLAGS_SHORT_GI = BIT(2),
    IEEE80211_RATE_INFO_FLAGS_HE_MCS = BIT(3),
};

struct ieee80211_rate_info {
    u8 flags;    /* see IEEE80211_RATE_INFO_FLAGS_XXX */
    u8 mcs;
    u16 legacy;  /* rate */
    u8 bw;       /* bandwidth */
    u8 nss;
    struct {
        u8 gi;
        u8 dcm;
        u8 ru_alloc;
    } he;
};

/* TXRX */
enum ieee80211_packet_rx_flags {
    IEEE80211_RX_AMSDU = BIT(3),
    IEEE80211_RX_MALFORMED_ACTION_FRM = BIT(4),
    IEEE80211_RX_DEFERRED_RELEASE = BIT(5),
};

struct ieee80211_rx_status {
	u32 flag;
    u16 freq;
    u64 mactime;
    u64 boottime_ns;
    u32 device_timestamp;
    u32 ampdu_reference;
    u8 enc_flags;
    u8 encoding : 2, bw : 3, he_ru : 3;
    u8 he_gi : 2, he_dcm : 1;
    u8 band;
    u8 antenna;
    s8 signal;
    u8 chains;
	u8 rate_idx;
    u8 nss;
    u8 rx_flags;
    s8 chain_signal[IEEE80211_MAX_CHAINS];
	u8 zero_length_psdu_type;
    u8 ampdu_delimiter_crc;
};

static inline struct ieee80211_rx_status *
IEEE80211_SKB_RXCB(struct sk_buff *skb)
{
    return (struct ieee80211_rx_status *)skb->cb;
}

enum ieee80211_sta_rx_bandwidth {
    IEEE80211_STA_RX_BANDWIDTH_20 = 0,
    IEEE80211_STA_RX_BANDWIDTH_40 = 1,
    IEEE80211_STA_RX_BANDWIDTH_80 = 2,
    IEEE80211_STA_RX_BANDWIDTH_160 = 3,
};

/* TX */
enum ieee80211_tx_info_flags {
	IEEE80211_TX_CTL_REQUEST_TX_STATUS		= BIT(0),
	IEEE80211_TX_CTL_ASSIGN_SN				= BIT(1),
	IEEE80211_TX_CTL_NO_ACK					= BIT(2),
	IEEE80211_TX_CTRL_HW_80211_ENCAP        = BIT(3),
	IEEE80211_TX_STATUS_ACK					= BIT(8),
    IEEE80211_TX_STATUS_NOACK_TRANSMITTED   = BIT(9),
	IEEE80211_TX_INTERNAL_DONT_ENCRYPT		= BIT(16),
	IEEE80211_TX_INTERNAL_MLME_TX			= BIT(17),
};

/* there are 56 bytes to be kept if don't need the rateset */
#define IEEE80211_TX_INFO_DRIVER_DATA_SIZE 56

/* maximum number of rate stages */
#define IEEE80211_TX_MAX_RATES	4

/* maximum number of rate table entries */
#define IEEE80211_TX_RATE_TABLE_SIZE	4

struct ieee80211_tx_rate {
	s8 idx;
	u16 count:5,
	    flags:11;
};

typedef void(*ieee80211_tx_complete_handler)(struct sk_buff *skb, void *arg, bool acked);

struct ieee80211_tx_info {
	/* common information */
	u32 flags;

    /* u32 */
    u32 band : 3;
    u32 ack_frame_id : 13;
    u32 hw_queue : 4;
    u32 tx_time_est : 10;
	/* 2 free bits */

	union {
		struct {
			struct ieee80211_vif *vif;
			struct ieee80211_key_conf *hw_key;
			u32 flags;
			u64 enqueue_time;
		} control;
		struct {
			struct ieee80211_tx_rate rates[IEEE80211_TX_MAX_RATES];
            s32 ack_signal;
			u8 antenna;
			u16 tx_time;
			bool is_valid_ack_signal;
		} status;
		void *driver_data[
			IEEE80211_TX_INFO_DRIVER_DATA_SIZE / sizeof(void *)];
	} u;

    ieee80211_tx_complete_handler tx_complete_handler;
    void *tx_complete_arg;
};

/* TX control data */
struct ieee80211_tx_control {
	struct ieee80211_sta *sta;
};

enum mac80211_rx_flags {
	IEEE80211_RX_FLAG_MMIC_ERROR		= BIT(0),
	IEEE80211_RX_FLAG_DECRYPTED		    = BIT(1),
	IEEE80211_RX_FLAG_MMIC_STRIPPED		= BIT(3),
	IEEE80211_RX_FLAG_IV_STRIPPED		= BIT(4),
	IEEE80211_RX_FLAG_FAILED_FCS_CRC	= BIT(5),
	IEEE80211_RX_FLAG_NO_SIGNAL_VAL		= BIT(8),
	IEEE80211_RX_FLAG_PN_VALIDATED		= BIT(10),
	IEEE80211_RX_FLAG_DUP_VALIDATED		= BIT(11),
	IEEE80211_RX_FLAG_ONLY_MONITOR		= BIT(17),
	IEEE80211_RX_FLAG_SKIP_MONITOR		= BIT(18),
	IEEE80211_RX_FLAG_AMSDU_MORE	    = BIT(19),
	IEEE80211_RX_FLAG_MSDU_ERR_LEN      = BIT(20),
	IEEE80211_RX_FLAG_MIC_STRIPPED		= BIT(21),
	IEEE80211_RX_FLAG_ICV_STRIPPED		= BIT(23),
	IEEE80211_RX_FLAG_80211_MCAST		= BIT(30),
};

/*
 *mac80211_rx_encoding_flags - MCS & bandwidth flags
 */
enum mac80211_rx_encoding_flags {
	RX_ENC_FLAG_SHORTPRE		= BIT(0), 			/* Short preamble used */
	RX_ENC_FLAG_SHORT_GI		= BIT(2), 			/* Short guard interval used */
	RX_ENC_FLAG_HT_GF		    = BIT(3), 			/* Frame was received in a HT-greenfield transmission */
	RX_ENC_FLAG_STBC_MASK		= BIT(4) | BIT(5), 	/* STBC 2 bit bitmask. 1 - Nss=1, 2 - Nss=2, 3 - Nss=3 */
	RX_ENC_FLAG_LDPC		    = BIT(6), 			/* LDPC used */
	RX_ENC_FLAG_BF			    = BIT(7), 			/* packet was beamformed */
};

#define RX_ENC_LEGACY 				0
#define RX_ENC_HT					1
#define RX_ENC_VHT					2
#define RX_ENC_HE					3

enum ieee80211_conf_changed {
	IEEE80211_CONF_CHANGED_SMPS				= BIT(1),
	IEEE80211_CONF_CHANGED_LISTEN_INTERVAL	= BIT(2),
	IEEE80211_CONF_CHANGED_MONITOR			= BIT(3),
	IEEE80211_CONF_CHANGED_PS				= BIT(4),
	IEEE80211_CONF_CHANGED_POWER		    = BIT(5),
	IEEE80211_CONF_CHANGED_CHANNEL			= BIT(6),
	IEEE80211_CONF_CHANGED_RETRY_LIMITS		= BIT(7),
	IEEE80211_CONF_CHANGED_IDLE				= BIT(8),
};

enum ieee80211_ampdu_mlme_action {
	IEEE80211_AMPDU_RX_START, 			/* start RX aggregation */
	IEEE80211_AMPDU_RX_STOP,  			/* stop RX aggregation */
	IEEE80211_AMPDU_TX_START, 			/* start TX aggregation */
	IEEE80211_AMPDU_TX_STOP_CONT,   	/* stop TX aggregation but continue transmitting queued packets, now unaggregated. */
	IEEE80211_AMPDU_TX_STOP_FLUSH,  	/* stop TX aggregation and flush all packets */
	IEEE80211_AMPDU_TX_STOP_FLUSH_CONT,
	IEEE80211_AMPDU_TX_OPERATIONAL,
};

struct ieee80211_ampdu_params {
	enum ieee80211_ampdu_mlme_action action; 	/* the ampdu action */
	struct ieee80211_sta *sta;               	/* peer of this AMPDU session */
	u16 tid;									/* tid of the BA session */
	u16 ssn;									/* start sequence number of the session */
	u16 buf_size;								/* reorder buffer size */
	bool amsdu;									/* indicates the peer's ability to receive A-MSDU within A-MPDU */
	u16 timeout;								/* BA session timeout */
};

#define IEEE80211_MAX_CSA_COUNTERS_NUM 2
struct ieee80211_mutable_offsets {
	u16 tim_offset;
	u16 tim_length;

	u16 csa_counter_offs[IEEE80211_MAX_CSA_COUNTERS_NUM];
};

static inline struct ieee80211_tx_info *IEEE80211_SKB_CB(struct sk_buff *skb)
{
	return (struct ieee80211_tx_info *)skb->cb;
}

/* key */
enum ieee80211_key_cmd {
    IEEE80211_SET_KEY,
    IEEE80211_DISABLE_KEY,
};

struct ieee80211_key_conf {
    u16 flags;     /* see &enum ieee80211_key_flags. */
	u32 cipher;    /* The key's cipher suite selector. */
	u8 icv_len;    /* The ICV length for this key type */
	u8 iv_len;     /* The ICV length for this key type */
	u8 hw_key_idx; /* the key index the driver wants */
	s8 key_idx;     /* key index (0-3) */
	u8 color;       /* key color */
	u8 key_len;     /* key material length */
	u8 key[0];     /* key material */
};

enum ieee80211_key_flags {
	IEEE80211_KEY_FLAG_GENERATE_IV_MGMT	= BIT(0),
	IEEE80211_KEY_FLAG_GENERATE_IV		= BIT(1), 	/* requires IV generation for this particular key */
	IEEE80211_KEY_FLAG_GENERATE_MMIC	= BIT(2), 	/* requires Michael MIC generation in software */
	IEEE80211_KEY_FLAG_PAIRWISE			= BIT(3), 	/* the key is pairwise rather then a shared key */
	IEEE80211_KEY_FLAG_GTK              = BIT(4), 	/* the key is Gtk */
	IEEE80211_KEY_FLAG_PUT_IV_SPACE		= BIT(5),
	IEEE80211_KEY_FLAG_RX_MGMT			= BIT(6), 	/* This key will be used to decrypt received management frames. */
	IEEE80211_KEY_FLAG_RESERVE_TAILROOM	= BIT(7), 	/* sufficient tailroom must always be reserved for ICV or MIC */
	IEEE80211_KEY_FLAG_PUT_MIC_SPACE	= BIT(8), 	/* only requires MIC space */
	IEEE80211_KEY_FLAG_NO_AUTO_TX		= BIT(9), 	/* key needs explicit Tx activation. */
	IEEE80211_KEY_FLAG_GENERATE_MMIE	= BIT(10), 	/* requires sequence number generation only */
};

struct ieee80211_he_obss_pd {
	bool enable;
	u8 sr_ctrl;
	u8 non_srg_max_offset;
	u8 min_offset;
	u8 max_offset;
	u8 bss_color_bitmap[8];
	u8 partial_bssid_bitmap[8];
};

/**
* enum ieee80211_offload_flags - virtual interface offload flags
*
* @IEEE80211_OFFLOAD_ENCAP_ENABLED: tx encapsulation offload is enabled
*    The driver supports sending frames passed as 802.3 frames by mac80211.
*    It must also support sending 802.11 packets for the same interface.
* @IEEE80211_OFFLOAD_ENCAP_4ADDR: support 4-address mode encapsulation offload
* @IEEE80211_OFFLOAD_DECAP_ENABLED: rx encapsulation offload is enabled
*    The driver supports passing received 802.11 frames as 802.3 frames to
*    mac80211.
*/
enum ieee80211_offload_flags {
    IEEE80211_OFFLOAD_ENCAP_ENABLED      = BIT(0),
    IEEE80211_OFFLOAD_ENCAP_4ADDR        = BIT(1),
    IEEE80211_OFFLOAD_DECAP_ENABLED      = BIT(2),
};

#endif // !__NET_MAC80211_DEFS_H
