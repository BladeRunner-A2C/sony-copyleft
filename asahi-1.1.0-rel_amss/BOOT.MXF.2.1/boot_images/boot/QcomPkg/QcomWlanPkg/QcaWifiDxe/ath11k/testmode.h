/* SPDX-License-Identifier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#include "core.h"

#define MAX_WMI_UTF_LEN 252
#define WMI_TLV_HDR_SIZE 4
#define WMITLV_TAG_BYTE 17
#define FTM_MODE_RESET_TIMEOUT_HZ (10 * HZ)
#define WMITLV_SET_HDR(tlv_buf, tag, len) ({ \
		(((u32 *)(tlv_buf))[0]) = (((tag) << 16) | ((len) & 0x0000FFFF)); \
	})

struct seg_hdr_info {
	u32 len;
	u32 msgref;
	u32 segmentinfo;
	u32 pad;
};

#ifdef CONFIG_NL80211_TESTMODE

bool ath11k_tm_event_wmi(struct ath11k_base *ab, u32 cmd_id, struct sk_buff *skb);
int ath11k_tm_cmd(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		  void *data, int len);

#else

static inline bool ath11k_tm_event_wmi(struct ath11k_base *ab, u32 cmd_id,
				       struct sk_buff *skb)
{
	return false;
}

/*
static inline int ath11k_tm_cmd(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif,
				void *data, int len)
{
	return 0;
}
*/
#endif
