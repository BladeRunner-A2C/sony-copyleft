#ifndef __LINUX_NL80211_H
#define __LINUX_NL80211_H

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

/*
 * 802.11 netlink interface public header
 *
 * Copyright 2006-2010 Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2008 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2008 Luis Carlos Cobo <luisca@cozybit.com>
 * Copyright 2008 Michael Buesch <m@bues.ch>
 * Copyright 2008, 2009 Luis R. Rodriguez <lrodriguez@atheros.com>
 * Copyright 2008 Jouni Malinen <jouni.malinen@atheros.com>
 * Copyright 2008 Colin McCabe <colin@cozybit.com>
 * Copyright 2015-2017	Intel Deutschland GmbH
 * Copyright (C) 2018-2019 Intel Corporation
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*
 * This header file defines the userspace API to the wireless stack. Please
 * be careful not to break things - i.e. don't move anything around or so
 * unless you can demonstrate that it breaks neither API nor ABI.
 *
 * Additions to the API should be accompanied by actual implementations in
 * an upstream driver, so that example implementations exist in case there
 * are ever concerns about the precise semantics of the API or changes are
 * needed, and to ensure that code for dead (no longer implemented) API
 * can actually be identified and removed.
 * Nonetheless, semantics should also be documented carefully in this file.
 */

#include <qdf/qbase.h>
#include <net/ether.h>


#define NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY	24

/**
 * enum nl80211_iftype - (virtual) interface types
 *
 * @NL80211_IFTYPE_UNSPECIFIED: unspecified type, driver decides
 * @NL80211_IFTYPE_ADHOC: independent BSS member
 * @NL80211_IFTYPE_STATION: managed BSS member
 * @NL80211_IFTYPE_AP: access point
 * @NL80211_IFTYPE_AP_VLAN: VLAN interface for access points; VLAN interfaces
 *	are a bit special in that they must always be tied to a pre-existing
 *	AP type interface.
 * @NL80211_IFTYPE_WDS: wireless distribution interface
 * @NL80211_IFTYPE_MONITOR: monitor interface receiving all frames
 * @NL80211_IFTYPE_MESH_POINT: mesh point
 * @NL80211_IFTYPE_P2P_CLIENT: P2P client
 * @NL80211_IFTYPE_P2P_GO: P2P group owner
 * @NL80211_IFTYPE_P2P_DEVICE: P2P device interface type, this is not a netdev
 *	and therefore can't be created in the normal ways, use the
 *	%NL80211_CMD_START_P2P_DEVICE and %NL80211_CMD_STOP_P2P_DEVICE
 *	commands to create and destroy one
 * @NL80211_IF_TYPE_OCB: Outside Context of a BSS
 *	This mode corresponds to the MIB variable dot11OCBActivated=true
 * @NL80211_IFTYPE_NAN: NAN device interface type (not a netdev)
 * @NL80211_IFTYPE_MAX: highest interface type number currently defined
 * @NUM_NL80211_IFTYPES: number of defined interface types
 *
 * These values are used with the %NL80211_ATTR_IFTYPE
 * to set the type of an interface.
 *
 */
enum nl80211_iftype {
	NL80211_IFTYPE_UNSPECIFIED,
	NL80211_IFTYPE_ADHOC,
	NL80211_IFTYPE_STATION,
	NL80211_IFTYPE_AP,
	NL80211_IFTYPE_AP_VLAN,
	NL80211_IFTYPE_MONITOR,
	NL80211_IFTYPE_MESH_POINT,
	NL80211_IFTYPE_P2P_CLIENT,
	NL80211_IFTYPE_P2P_GO,
	NL80211_IFTYPE_P2P_DEVICE,
	NL80211_IFTYPE_OCB,
	NL80211_IFTYPE_NAN,

	/* keep last */
	NUM_NL80211_IFTYPES,
	NL80211_IFTYPE_MAX = NUM_NL80211_IFTYPES - 1
};

/**
 * enum nl80211_he_gi - HE guard interval
 * @NL80211_RATE_INFO_HE_GI_0_8: 0.8 usec
 * @NL80211_RATE_INFO_HE_GI_1_6: 1.6 usec
 * @NL80211_RATE_INFO_HE_GI_3_2: 3.2 usec
 */
enum nl80211_he_gi {
	NL80211_RATE_INFO_HE_GI_0_8,
	NL80211_RATE_INFO_HE_GI_1_6,
	NL80211_RATE_INFO_HE_GI_3_2,
};

/**
 * enum nl80211_he_ru_alloc - HE RU allocation values
 * @NL80211_RATE_INFO_HE_RU_ALLOC_26: 26-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_52: 52-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_106: 106-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_242: 242-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_484: 484-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_996: 996-tone RU allocation
 * @NL80211_RATE_INFO_HE_RU_ALLOC_2x996: 2x996-tone RU allocation
 */
enum nl80211_he_ru_alloc {
	NL80211_RATE_INFO_HE_RU_ALLOC_26,
	NL80211_RATE_INFO_HE_RU_ALLOC_52,
	NL80211_RATE_INFO_HE_RU_ALLOC_106,
	NL80211_RATE_INFO_HE_RU_ALLOC_242,
	NL80211_RATE_INFO_HE_RU_ALLOC_484,
	NL80211_RATE_INFO_HE_RU_ALLOC_996,
	NL80211_RATE_INFO_HE_RU_ALLOC_2x996,
};


/**
 * enum nl80211_initiator - Indicates the initiator of a reg domain request
 * @NL80211_REGDOM_SET_BY_CORE: Core queried CRDA for a dynamic world
 * 	regulatory domain.
 * @NL80211_REGDOM_SET_BY_USER: User asked the wireless core to set the
 * 	regulatory domain.
 * @NL80211_REGDOM_SET_BY_DRIVER: a wireless drivers has hinted to the
 * 	wireless core it thinks its knows the regulatory domain we should be in.
 * @NL80211_REGDOM_SET_BY_COUNTRY_IE: the wireless core has received an
 * 	802.11 country information element with regulatory information it
 * 	thinks we should consider. cfg80211 only processes the country
 *	code from the IE, and relies on the regulatory domain information
 *	structure passed by userspace (CRDA) from our wireless-regdb.
 *	If a channel is enabled but the country code indicates it should
 *	be disabled we disable the channel and re-enable it upon disassociation.
 */
enum nl80211_reg_initiator {
	NL80211_REGDOM_SET_BY_CORE,
	NL80211_REGDOM_SET_BY_USER,
	NL80211_REGDOM_SET_BY_DRIVER,
	NL80211_REGDOM_SET_BY_COUNTRY_IE,
};

/**
 * enum nl80211_reg_rule_flags - regulatory rule flags
 *
 * @NL80211_RRF_NO_OFDM: OFDM modulation not allowed
 * @NL80211_RRF_NO_CCK: CCK modulation not allowed
 * @NL80211_RRF_NO_INDOOR: indoor operation not allowed
 * @NL80211_RRF_NO_OUTDOOR: outdoor operation not allowed
 * @NL80211_RRF_DFS: DFS support is required to be used
 * @NL80211_RRF_PTP_ONLY: this is only for Point To Point links
 * @NL80211_RRF_PTMP_ONLY: this is only for Point To Multi Point links
 * @NL80211_RRF_NO_IR: no mechanisms that initiate radiation are allowed,
 * 	this includes probe requests or modes of operation that require
 * 	beaconing.
 * @NL80211_RRF_AUTO_BW: maximum available bandwidth should be calculated
 *	base on contiguous rules and wider channels will be allowed to cross
 *	multiple contiguous/overlapping frequency ranges.
 * @NL80211_RRF_IR_CONCURRENT: See %NL80211_FREQUENCY_ATTR_IR_CONCURRENT
 * @NL80211_RRF_NO_HT40MINUS: channels can't be used in HT40- operation
 * @NL80211_RRF_NO_HT40PLUS: channels can't be used in HT40+ operation
 * @NL80211_RRF_NO_80MHZ: 80MHz operation not allowed
 * @NL80211_RRF_NO_160MHZ: 160MHz operation not allowed
 */
enum nl80211_reg_rule_flags {
	NL80211_RRF_NO_OFDM		    = 1<<0,
	NL80211_RRF_NO_CCK		    = 1<<1,
	NL80211_RRF_NO_INDOOR		= 1<<2,
	NL80211_RRF_NO_OUTDOOR		= 1<<3,
	NL80211_RRF_DFS			    = 1<<4,
	NL80211_RRF_PTP_ONLY		= 1<<5,
	NL80211_RRF_PTMP_ONLY		= 1<<6,
	NL80211_RRF_NO_IR		    = 1<<7,
	__NL80211_RRF_NO_IBSS		= 1<<8,
	NL80211_RRF_AUTO_BW		    = 1<<11,
	NL80211_RRF_IR_CONCURRENT	= 1<<12,
	NL80211_RRF_NO_HT40MINUS	= 1<<13,
	NL80211_RRF_NO_HT40PLUS		= 1<<14,
	NL80211_RRF_NO_80MHZ		= 1<<15,
	NL80211_RRF_NO_160MHZ		= 1<<16,
    NL80211_RRF_NO_HE           = 1 << 17,
};

#define NL80211_RRF_PASSIVE_SCAN	NL80211_RRF_NO_IR
#define NL80211_RRF_NO_IBSS		NL80211_RRF_NO_IR
#define NL80211_RRF_NO_IR		NL80211_RRF_NO_IR
#define NL80211_RRF_NO_HT40		(NL80211_RRF_NO_HT40MINUS |\
					 NL80211_RRF_NO_HT40PLUS)
#define NL80211_RRF_GO_CONCURRENT	NL80211_RRF_IR_CONCURRENT

/* For backport compatibility with older userspace */
#define NL80211_RRF_NO_IR_ALL		(NL80211_RRF_NO_IR | __NL80211_RRF_NO_IBSS)

/**
 * enum nl80211_dfs_regions - regulatory DFS regions
 *
 * @NL80211_DFS_UNSET: Country has no DFS master region specified
 * @NL80211_DFS_FCC: Country follows DFS master rules from FCC
 * @NL80211_DFS_ETSI: Country follows DFS master rules from ETSI
 * @NL80211_DFS_JP: Country follows DFS master rules from JP/MKK/Telec
 */
enum nl80211_dfs_regions {
	NL80211_DFS_UNSET	= 0,
	NL80211_DFS_FCC		= 1,
	NL80211_DFS_ETSI	= 2,
	NL80211_DFS_JP		= 3,
};

/**
 * enum nl80211_user_reg_hint_type - type of user regulatory hint
 *
 * @NL80211_USER_REG_HINT_USER: a user sent the hint. This is always
 *	assumed if the attribute is not set.
 * @NL80211_USER_REG_HINT_CELL_BASE: the hint comes from a cellular
 *	base station. Device drivers that have been tested to work
 *	properly to support this type of hint can enable these hints
 *	by setting the NL80211_FEATURE_CELL_BASE_REG_HINTS feature
 *	capability on the struct wiphy. The wireless core will
 *	ignore all cell base station hints until at least one device
 *	present has been registered with the wireless core that
 *	has listed NL80211_FEATURE_CELL_BASE_REG_HINTS as a
 *	supported feature.
 * @NL80211_USER_REG_HINT_INDOOR: a user sent an hint indicating that the
 *	platform is operating in an indoor environment.
 */
enum nl80211_user_reg_hint_type {
	NL80211_USER_REG_HINT_USER	= 0,
	NL80211_USER_REG_HINT_CELL_BASE = 1,
	NL80211_USER_REG_HINT_INDOOR    = 2,
};


/**
 * enum nl80211_channel_type - channel type
 * @NL80211_CHAN_NO_HT: 20 MHz, non-HT channel
 * @NL80211_CHAN_HT20: 20 MHz HT channel
 * @NL80211_CHAN_HT40MINUS: HT40 channel, secondary channel
 *	below the control channel
 * @NL80211_CHAN_HT40PLUS: HT40 channel, secondary channel
 *	above the control channel
 */
enum nl80211_channel_type {
	NL80211_CHAN_NO_HT,
	NL80211_CHAN_HT20,
	NL80211_CHAN_HT40MINUS,
	NL80211_CHAN_HT40PLUS
};

/**
 * enum nl80211_key_mode - Key mode
 *
 * @NL80211_KEY_RX_TX: (Default)
 *	Key can be used for Rx and Tx immediately
 *
 * The following modes can only be selected for unicast keys and when the
 * driver supports @NL80211_EXT_FEATURE_EXT_KEY_ID:
 *
 * @NL80211_KEY_NO_TX: Only allowed in combination with @NL80211_CMD_NEW_KEY:
 *	Unicast key can only be used for Rx, Tx not allowed, yet
 * @NL80211_KEY_SET_TX: Only allowed in combination with @NL80211_CMD_SET_KEY:
 *	The unicast key identified by idx and mac is cleared for Tx and becomes
 *	the preferred Tx key for the station.
 */
enum nl80211_key_mode {
	NL80211_KEY_RX_TX,
	NL80211_KEY_NO_TX,
	NL80211_KEY_SET_TX
};

/**
 * enum nl80211_chan_width - channel width definitions
 *
 * These values are used with the %NL80211_ATTR_CHANNEL_WIDTH
 * attribute.
 *
 * @NL80211_CHAN_WIDTH_20_NOHT: 20 MHz, non-HT channel
 * @NL80211_CHAN_WIDTH_20: 20 MHz HT channel
 * @NL80211_CHAN_WIDTH_40: 40 MHz channel, the %NL80211_ATTR_CENTER_FREQ1
 *	attribute must be provided as well
 * @NL80211_CHAN_WIDTH_80: 80 MHz channel, the %NL80211_ATTR_CENTER_FREQ1
 *	attribute must be provided as well
 * @NL80211_CHAN_WIDTH_80P80: 80+80 MHz channel, the %NL80211_ATTR_CENTER_FREQ1
 *	and %NL80211_ATTR_CENTER_FREQ2 attributes must be provided as well
 * @NL80211_CHAN_WIDTH_160: 160 MHz channel, the %NL80211_ATTR_CENTER_FREQ1
 *	attribute must be provided as well
 * @NL80211_CHAN_WIDTH_5: 5 MHz OFDM channel
 * @NL80211_CHAN_WIDTH_10: 10 MHz OFDM channel
 */
enum nl80211_chan_width {
	NL80211_CHAN_WIDTH_20_NOHT,
	NL80211_CHAN_WIDTH_20,
	NL80211_CHAN_WIDTH_40,
	NL80211_CHAN_WIDTH_80,
	NL80211_CHAN_WIDTH_80P80,
	NL80211_CHAN_WIDTH_160,
	NL80211_CHAN_WIDTH_5,
	NL80211_CHAN_WIDTH_10,
};

/**
 * enum nl80211_auth_type - AuthenticationType
 *
 * @NL80211_AUTHTYPE_OPEN_SYSTEM: Open System authentication
 * @NL80211_AUTHTYPE_SHARED_KEY: Shared Key authentication (WEP only)
 * @NL80211_AUTHTYPE_FT: Fast BSS Transition (IEEE 802.11r)
 * @NL80211_AUTHTYPE_NETWORK_EAP: Network EAP (some Cisco APs and mainly LEAP)
 * @NL80211_AUTHTYPE_SAE: Simultaneous authentication of equals
 * @NL80211_AUTHTYPE_FILS_SK: Fast Initial Link Setup shared key
 * @NL80211_AUTHTYPE_FILS_SK_PFS: Fast Initial Link Setup shared key with PFS
 * @NL80211_AUTHTYPE_FILS_PK: Fast Initial Link Setup public key
 * @__NL80211_AUTHTYPE_NUM: internal
 * @NL80211_AUTHTYPE_MAX: maximum valid auth algorithm
 * @NL80211_AUTHTYPE_AUTOMATIC: determine automatically (if necessary by
 *	trying multiple times); this is invalid in netlink -- leave out
 *	the attribute for this on CONNECT commands.
 */
enum nl80211_auth_type {
	NL80211_AUTHTYPE_OPEN_SYSTEM,
	NL80211_AUTHTYPE_SHARED_KEY,
	NL80211_AUTHTYPE_FT,
	NL80211_AUTHTYPE_NETWORK_EAP,
	NL80211_AUTHTYPE_SAE,
	NL80211_AUTHTYPE_FILS_SK,
	NL80211_AUTHTYPE_FILS_SK_PFS,
	NL80211_AUTHTYPE_FILS_PK,

	/* keep last */
	__NL80211_AUTHTYPE_NUM,
	NL80211_AUTHTYPE_MAX = __NL80211_AUTHTYPE_NUM - 1,
	NL80211_AUTHTYPE_AUTOMATIC
};

#if NL80211_OWNED

/**
 * enum nl80211_mfp - Management frame protection state
 * @NL80211_MFP_NO: Management frame protection not used
 * @NL80211_MFP_REQUIRED: Management frame protection required
 * @NL80211_MFP_OPTIONAL: Management frame protection is optional
 */
enum nl80211_mfp {
	NL80211_MFP_NO,
	NL80211_MFP_REQUIRED,
	NL80211_MFP_OPTIONAL,
};
#endif //!NL80211_OWNED

/**
 * enum nl80211_tx_rate_attributes - TX rate set attributes
 * @__NL80211_TXRATE_INVALID: invalid
 * @NL80211_TXRATE_LEGACY: Legacy (non-MCS) rates allowed for TX rate selection
 *	in an array of rates as defined in IEEE 802.11 7.3.2.2 (u8 values with
 *	1 = 500 kbps) but without the IE length restriction (at most
 *	%NL80211_MAX_SUPP_RATES in a single array).
 * @NL80211_TXRATE_HT: HT (MCS) rates allowed for TX rate selection
 *	in an array of MCS numbers.
 * @NL80211_TXRATE_VHT: VHT rates allowed for TX rate selection,
 *	see &struct nl80211_txrate_vht
 * @NL80211_TXRATE_GI: configure GI, see &enum nl80211_txrate_gi
 * @__NL80211_TXRATE_AFTER_LAST: internal
 * @NL80211_TXRATE_MAX: highest TX rate attribute
 */
enum nl80211_tx_rate_attributes {
	__NL80211_TXRATE_INVALID,
	NL80211_TXRATE_LEGACY,
	NL80211_TXRATE_HT,
	NL80211_TXRATE_VHT,
	NL80211_TXRATE_GI,

	/* keep last */
	__NL80211_TXRATE_AFTER_LAST,
	NL80211_TXRATE_MAX = __NL80211_TXRATE_AFTER_LAST - 1
};

#define NL80211_TXRATE_MCS NL80211_TXRATE_HT
#define NL80211_VHT_NSS_MAX		8

/**
 * struct nl80211_txrate_vht - VHT MCS/NSS txrate bitmap
 * @mcs: MCS bitmap table for each NSS (array index 0 for 1 stream, etc.)
 */
struct nl80211_txrate_vht {
	__u16 mcs[NL80211_VHT_NSS_MAX];
};

enum nl80211_txrate_gi {
	NL80211_TXRATE_DEFAULT_GI,
	NL80211_TXRATE_FORCE_SGI,
	NL80211_TXRATE_FORCE_LGI,
};

/**
 * enum nl80211_band - Frequency band
 * @NL80211_BAND_2GHZ: 2.4 GHz ISM band
 * @NL80211_BAND_5GHZ: around 5 GHz band (4.9 - 5.7 GHz)
 * @NL80211_BAND_60GHZ: around 60 GHz band (58.32 - 69.12 GHz)
 * @NL80211_BAND_6GHZ: around 6 GHz band (5.9 - 7.2 GHz)
 * @NUM_NL80211_BANDS: number of bands, avoid using this in userspace
 *	since newer kernel versions may support more bands
 */
enum nl80211_band {
	NL80211_BAND_2GHZ,
	NL80211_BAND_5GHZ,
	NL80211_BAND_60GHZ,
	NL80211_BAND_6GHZ,

	NUM_NL80211_BANDS,
};

/**
 * enum nl80211_tx_power_setting - TX power adjustment
 * @NL80211_TX_POWER_AUTOMATIC: automatically determine transmit power
 * @NL80211_TX_POWER_LIMITED: limit TX power by the mBm parameter
 * @NL80211_TX_POWER_FIXED: fix TX power to the mBm parameter
 */
enum nl80211_tx_power_setting {
	NL80211_TX_POWER_AUTOMATIC,
	NL80211_TX_POWER_LIMITED,
	NL80211_TX_POWER_FIXED,
};

#define NL80211_KCK_LEN			16
#define NL80211_KEK_LEN			16
#define NL80211_REPLAY_CTR_LEN		8


/**
 * enum nl80211_dfs_state - DFS states for channels
 *
 * Channel states used by the DFS code.
 *
 * @NL80211_DFS_USABLE: The channel can be used, but channel availability
 *	check (CAC) must be performed before using it for AP or IBSS.
 * @NL80211_DFS_UNAVAILABLE: A radar has been detected on this channel, it
 *	is therefore marked as not available.
 * @NL80211_DFS_AVAILABLE: The channel has been CAC checked and is available.
 */
enum nl80211_dfs_state {
	NL80211_DFS_USABLE,
	NL80211_DFS_UNAVAILABLE,
	NL80211_DFS_AVAILABLE,
};

#define NL80211_MAX_NR_CIPHER_SUITES	5
#define NL80211_MAX_NR_AKM_SUITES		2

#define NL80211_MAX_SUPP_REG_RULES		128
#endif /* __LINUX_NL80211_H */
