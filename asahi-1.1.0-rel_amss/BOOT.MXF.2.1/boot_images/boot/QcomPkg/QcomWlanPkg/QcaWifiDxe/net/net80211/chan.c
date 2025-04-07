/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 8/2/22    zxue     fix the kw issue
 6/9/21    zxue     fix parasoft issue
 19/8/21   zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/net80211.h>
#include <net/ndebug.h>
#include "vif.h"
#include "chan.h"
#include "mlme.h"
#include "drvops.h"

/*---------------------------------------------------------------------------*/
/* chandef */

void ieee80211_chandef_create(struct ieee80211_chan_def *chandef,
    struct ieee80211_channel *chan,
    enum nl80211_channel_type chan_type)
{
    static const struct {
        enum nl80211_chan_width width;
        s32 offset;
    } chan_def_map[] = {
        [NL80211_CHAN_NO_HT] = { NL80211_CHAN_WIDTH_20_NOHT, 0 },
        [NL80211_CHAN_HT20] = { NL80211_CHAN_WIDTH_20, 0 },
        [NL80211_CHAN_HT40PLUS] = { NL80211_CHAN_WIDTH_40, 10 },
        [NL80211_CHAN_HT40MINUS] = {NL80211_CHAN_WIDTH_40, -10 }
    };

    if (WARN_ON(!chan))
        return;

    chandef->chan = chan;
    chandef->center_freq2 = 0;

    if (!WARN_ON(chan_type >= ARRAY_LENGTH(chan_def_map))) {
        chandef->width = chan_def_map[chan_type].width;
        chandef->center_freq1 = chan->center_freq + chan_def_map[chan_type].offset;
    }
}

bool ieee80211_chandef_valid(const struct ieee80211_chan_def *chandef)
{
    enum nl80211_chan_width chanwidth;
    u32 cfreq;

    if (!chandef->chan)
        return false;

    chanwidth = chandef->width;
    cfreq = chandef->chan->center_freq;

    if (NL80211_CHAN_WIDTH_5 == chanwidth ||
        NL80211_CHAN_WIDTH_10 == chanwidth ||
        NL80211_CHAN_WIDTH_20 == chanwidth ||
        NL80211_CHAN_WIDTH_20_NOHT == chanwidth) {
        if (chandef->center_freq1 != cfreq)
            return false;
        if (chandef->center_freq2)
            return false;
	}
    else if (NL80211_CHAN_WIDTH_40 == chanwidth) {
        if (chandef->center_freq1 != cfreq + 10 &&
            chandef->center_freq1 != cfreq - 10)
            return false;
        if (chandef->center_freq2)
            return false;
	}
    else if (NL80211_CHAN_WIDTH_80 == chanwidth) {
        if (chandef->center_freq1 != cfreq + 10 &&
            chandef->center_freq1 != cfreq - 10 &&
            chandef->center_freq1 != cfreq + 30 &&
            chandef->center_freq1 != cfreq - 30)
            return false;
        if (chandef->center_freq2)
            return false;
    }
    else if (NL80211_CHAN_WIDTH_80P80 == chanwidth) {
        if (chandef->center_freq1 != cfreq + 10 &&
            chandef->center_freq1 != cfreq - 10 &&
            chandef->center_freq1 != cfreq + 30 &&
            chandef->center_freq1 != cfreq - 30)
            return false;
        if (!chandef->center_freq2)
            return false;
        /* not adjacent */
        if (chandef->center_freq1 - chandef->center_freq2 == 80 ||
            chandef->center_freq2 - chandef->center_freq1 == 80)
            return false;
	} 
    else if (NL80211_CHAN_WIDTH_160 == chanwidth) {
        if (chandef->center_freq1 != cfreq + 10 &&
            chandef->center_freq1 != cfreq - 10 &&
            chandef->center_freq1 != cfreq + 30 &&
            chandef->center_freq1 != cfreq - 30 &&
            chandef->center_freq1 != cfreq + 50 &&
            chandef->center_freq1 != cfreq - 50 &&
            chandef->center_freq1 != cfreq + 70 &&
            chandef->center_freq1 != cfreq - 70)
            return false;
        if (chandef->center_freq2)
            return false;
	} else {
        return false;
	}

    /* channel 14 is only for 802.11b */
    if (chandef->center_freq1 == 2484 &&
        chandef->width != NL80211_CHAN_WIDTH_20_NOHT)
        return false;

    return true;
}

static void ieee80211_chandef_primary_freqs(const struct ieee80211_chan_def *chandef,
    u32 *freq_p40, u32 *freq_p80)
{
    enum nl80211_chan_width chanwidth = chandef->width;
    int n;

	if (NL80211_CHAN_WIDTH_40 == chanwidth) {
        *freq_p40 = chandef->center_freq1;
        *freq_p80 = 0;
	} 
    else if (NL80211_CHAN_WIDTH_80 == chanwidth ||
        NL80211_CHAN_WIDTH_80P80 == chanwidth) {
        *freq_p80 = chandef->center_freq1;
        /* number of P20 */
        n = (30 + chandef->chan->center_freq - chandef->center_freq1) / 20;
        /* number of P40 */
        n /= 2;
        /* frequency of P40 */
        *freq_p40 = chandef->center_freq1 - 20 + 40 * n;
	}
    else if (NL80211_CHAN_WIDTH_160 == chanwidth) {
        /* number of P20 */
        n = (70 + chandef->chan->center_freq - chandef->center_freq1) / 20;
        /* number of P40 */
        n /= 2;
        /* freqency of P40 */
        *freq_p40 = chandef->center_freq1 - 60 + 40 * n;
        /* number of P80 */
        n /= 2;
        /* frequencye of P80 */
        *freq_p80 = chandef->center_freq1 - 40 + 80 * n;
	}
    else {
        WARN_ON_ONCE(1);
	}
}

const struct ieee80211_chan_def *
ieee80211_chandef_compatible(
    const struct ieee80211_chan_def *chandef1,
    const struct ieee80211_chan_def *chandef2)
{
    u32 chandef1_freq_p40 = 0, chandef1_freq_p80 = 0;
    u32 chandef2_freq_p40 = 0, chandef2_freq_p80 = 0;

    if (ieee80211_chandef_identical(chandef1, chandef2))
        return chandef1;

    /* don't have the same control channel */
    if (chandef1->chan != chandef2->chan)
        return NULL;

    /* same channel width but is not identical */
    if (chandef1->width == chandef2->width)
        return NULL;

    /* one of them is 5 or 10 MHz */
    if (chandef1->width == NL80211_CHAN_WIDTH_5 ||
        chandef1->width == NL80211_CHAN_WIDTH_10 ||
        chandef2->width == NL80211_CHAN_WIDTH_5 ||
        chandef2->width == NL80211_CHAN_WIDTH_10)
        return NULL;

    if (chandef2->width == NL80211_CHAN_WIDTH_20_NOHT ||
        chandef2->width == NL80211_CHAN_WIDTH_20)
        return chandef1;
    if (chandef1->width == NL80211_CHAN_WIDTH_20_NOHT ||
        chandef1->width == NL80211_CHAN_WIDTH_20)
        return chandef2;

    /* get chandef1/chandef2 primary frequency 40 && primary frequency 80*/
    ieee80211_chandef_primary_freqs(chandef1, 
        &chandef1_freq_p40, &chandef1_freq_p80);
    ieee80211_chandef_primary_freqs(chandef2, 
        &chandef2_freq_p40, &chandef2_freq_p80);

    if (chandef1_freq_p40 != chandef2_freq_p40)
        return NULL;

    WARN_ON(!chandef1_freq_p80 && !chandef2_freq_p80);
    if (chandef1_freq_p80 && chandef2_freq_p80 &&
        chandef1_freq_p80 != chandef2_freq_p80)
        return NULL;

    if (chandef1->width > chandef2->width)
    	return chandef1;
    else
        return chandef2;
}

/* chandef helpers */
bool ieee80211_chandef_ht_operation(
    const struct ieee80211_ht_operation *htop,
    struct ieee80211_chan_def *chandef)
{
    enum nl80211_channel_type channel_type = NL80211_CHAN_NO_HT;
    u8 secondary_channel_offset;

    if (!htop)
        return false;

    secondary_channel_offset = 
        (htop->ht_param & IEEE80211_HT_PARAM_SEC_CHA_OFFSET);

    if (IEEE80211_HT_PARAM_SEC_CHA_NONE == secondary_channel_offset)
        channel_type = NL80211_CHAN_HT20;
    else if (IEEE80211_HT_PARAM_SEC_CHA_ABOVE == secondary_channel_offset)
        channel_type = NL80211_CHAN_HT40PLUS;
    else if (IEEE80211_HT_PARAM_SEC_CHA_BELOW == secondary_channel_offset)
        channel_type = NL80211_CHAN_HT40MINUS;
    else
        return false;

    ieee80211_chandef_create(chandef, chandef->chan, channel_type);
    return true;
}


/*---------------------------------------------------------------------------*/
/* helpers */

bool ieee80211_chandef_vht_operation(
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_vht_operation *vhtop,
    const struct ieee80211_ht_operation *htop,
    bool supports_vht_ext_nss_bw,
    struct ieee80211_chan_def *chandef)
{
    struct ieee80211_chan_def chandef_new = *chandef;
    int cf0, cf1;
    int ccfs0, ccfs1, ccfs2;
    int ccf0, ccf1;
    u32 vht_cap;
    bool support_80P80;
    bool support_160;

    if (!vhtop || !htop)
        return false;

    vht_cap = sband->vht_cap.cap;
    support_160 = ((vht_cap & (IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK |
        IEEE80211_VHTCAP_EXT_NSS_BW_MASK)) != 0);
    support_80P80 = ((vht_cap &
        IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ) ||
        (vht_cap & IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ &&
            vht_cap & IEEE80211_VHTCAP_EXT_NSS_BW_MASK) ||
            ((vht_cap & IEEE80211_VHTCAP_EXT_NSS_BW_MASK) >>
                IEEE80211_VHTCAP_EXT_NSS_BW_SHIFT > 1));
    ccfs0 = vhtop->center_freq_seg0_idx;
    ccfs1 = vhtop->center_freq_seg1_idx;
    ccfs2 = (le16_to_cpu(htop->operation_mode) &
        IEEE80211_HT_OP_MODE_CCFS2_MASK)
        >> IEEE80211_HT_OP_MODE_CCFS2_SHIFT;

    /* when parsing, CCFS1 and CCFS2 are equivalent */
    ccf0 = ccfs0;
    ccf1 = ccfs1;
    if (!ccfs1 && supports_vht_ext_nss_bw)
        ccf1 = ccfs2;

    cf0 = ieee80211_channel_to_frequency(ccf0, chandef->chan->band);
    cf1 = ieee80211_channel_to_frequency(ccf1, chandef->chan->band);

    switch (vhtop->chan_width) {
    case IEEE80211_VHT_CHANWIDTH_USE_HT:
        /* just use HT information directly */
        break;
    case IEEE80211_VHT_CHANWIDTH_80MHZ:
        chandef_new.width = NL80211_CHAN_WIDTH_80;
        chandef_new.center_freq1 = cf0;
        /* If needed, adjust based on the newer interop workaround. */
        if (ccf1) {
            unsigned int diff;

            diff = abs(ccf1 - ccf0);
            if ((diff == 8) && support_160) {
                chandef_new.width = NL80211_CHAN_WIDTH_160;
                chandef_new.center_freq1 = cf1;
            }
            else if ((diff > 8) && support_80P80) {
                chandef_new.width = NL80211_CHAN_WIDTH_80P80;
                chandef_new.center_freq2 = cf1;
            }
        }
        break;
    case IEEE80211_VHT_CHANWIDTH_160MHZ:
        /* deprecated encoding */
        chandef_new.width = NL80211_CHAN_WIDTH_160;
        chandef_new.center_freq1 = cf0;
        break;
    case IEEE80211_VHT_CHANWIDTH_80P80MHZ:
        /* deprecated encoding */
        chandef_new.width = NL80211_CHAN_WIDTH_80P80;
        chandef_new.center_freq1 = cf0;
        chandef_new.center_freq2 = cf1;
        break;
    default:
        return false;
    }

    if (!ieee80211_chandef_valid(&chandef_new))
        return false;

    *chandef = chandef_new;
    return true;
}

u32 ieee80211_chandef_downgrade(struct ieee80211_chan_def *chandef)
{
    u32 flags;
    int n;

    switch (chandef->width) {
    case NL80211_CHAN_WIDTH_20:
        chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
        flags = NET80211_MLME_DISABLE_HT | NET80211_MLME_DISABLE_VHT;
        break;
    case NL80211_CHAN_WIDTH_40:
        chandef->width = NL80211_CHAN_WIDTH_20;
        chandef->center_freq1 = chandef->chan->center_freq;
        flags = NET80211_MLME_DISABLE_40MHZ |
            NET80211_MLME_DISABLE_VHT;
        break;
    case NL80211_CHAN_WIDTH_80:
        n = (30 + chandef->chan->center_freq - chandef->center_freq1) / 20;
        /* n_P40 */
        n /= 2;
        /* freq_P40 */
        chandef->center_freq1 = chandef->center_freq1 - 20 + 40 * n;
        chandef->width = NL80211_CHAN_WIDTH_40;
        flags = NET80211_MLME_DISABLE_VHT;
        break;
    case NL80211_CHAN_WIDTH_80P80:
        chandef->center_freq2 = 0;
        chandef->width = NL80211_CHAN_WIDTH_80;
        flags = NET80211_MLME_DISABLE_80P80MHZ |
            NET80211_MLME_DISABLE_160MHZ;
        break;
    case NL80211_CHAN_WIDTH_160:
        /* n_P20 */
        n = (70 + chandef->chan->center_freq - chandef->center_freq1) / 20;
        /* n_P80 */
        n /= 4;
        chandef->center_freq1 = chandef->center_freq1 - 40 + 80 * n;
        chandef->width = NL80211_CHAN_WIDTH_80;
        flags = NET80211_MLME_DISABLE_80P80MHZ |
            NET80211_MLME_DISABLE_160MHZ;
        break;
    default:
    case NL80211_CHAN_WIDTH_20_NOHT:
        WARN_ON_ONCE(1);
        chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
        flags = NET80211_MLME_DISABLE_HT | NET80211_MLME_DISABLE_VHT;
        break;
    case NL80211_CHAN_WIDTH_5:
    case NL80211_CHAN_WIDTH_10:
        WARN_ON_ONCE(1);
        /* keep chandef->width */
        flags = NET80211_MLME_DISABLE_HT | NET80211_MLME_DISABLE_VHT;
        break;
    }

    WARN_ON_ONCE(!ieee80211_chandef_valid(chandef));

    return flags;
}

static bool net80211_secondary_channel_ok(struct net80211_pdev *pdev,
    u32 center_freq, enum nl80211_chan_width chan_width,
    u32 prohibited_flags)
{
    static const u32 chan_width_to_bandwidth[] = {
        [NL80211_CHAN_WIDTH_20] = 20,
        [NL80211_CHAN_WIDTH_20_NOHT] = 20,
        [NL80211_CHAN_WIDTH_40] = 40,
        [NL80211_CHAN_WIDTH_80] = 80,
        [NL80211_CHAN_WIDTH_80P80] = 80,
        [NL80211_CHAN_WIDTH_160] = 160,
        [NL80211_CHAN_WIDTH_5] = 20,
        [NL80211_CHAN_WIDTH_10] = 20,
    };
    static const u32 chan_width_prohibited_flags[] = {
        [NL80211_CHAN_WIDTH_20] = IEEE80211_CHAN_NO_20MHZ,
        [NL80211_CHAN_WIDTH_20_NOHT] = IEEE80211_CHAN_NO_20MHZ,
        [NL80211_CHAN_WIDTH_40] = IEEE80211_CHAN_NO_OFDM,
        [NL80211_CHAN_WIDTH_80] = IEEE80211_CHAN_NO_OFDM | IEEE80211_CHAN_NO_80MHZ,
        [NL80211_CHAN_WIDTH_80P80] = IEEE80211_CHAN_NO_OFDM | IEEE80211_CHAN_NO_80MHZ,
        [NL80211_CHAN_WIDTH_160] = IEEE80211_CHAN_NO_OFDM | IEEE80211_CHAN_NO_160MHZ,
        [NL80211_CHAN_WIDTH_5] = IEEE80211_CHAN_NO_OFDM,
        [NL80211_CHAN_WIDTH_10] = IEEE80211_CHAN_NO_OFDM | IEEE80211_CHAN_NO_10MHZ,
    };

    struct ieee80211_channel *chan;
    u32 freq, start_freq, end_freq;
    u32 bandwidth;

    if (chan_width >= ARRAY_LENGTH(chan_width_to_bandwidth))
        return false;

    bandwidth = chan_width_to_bandwidth[chan_width];
    prohibited_flags |= chan_width_prohibited_flags[chan_width];

    start_freq = (center_freq - (bandwidth / 2) + 10);
    end_freq = (center_freq + (bandwidth / 2) - 10);

    for (freq = start_freq; freq <= end_freq; freq += 20) {
        chan = net80211_get_channel(pdev, freq);
        if (!chan || chan->flags & prohibited_flags)
            return false;
    }

    return true;
}

bool net80211_chandef_usable(struct net80211_pdev *pdev,
    const struct ieee80211_chan_def *chandef,
    u32 prohibited_flags)
{  
    if (WARN_ON(!ieee80211_chandef_valid(chandef)))
        return false;

    if (chandef->width == NL80211_CHAN_WIDTH_20 ||
        chandef->width == NL80211_CHAN_WIDTH_40) {
        const struct ieee80211_sta_ht_cap *sta_ht_cap;
		struct ieee80211_supported_band *sbands = net80211_get_sband(pdev, chandef->chan->band);
		if (sbands == NULL)
			return false;

        if (chandef->chan->band == NL80211_BAND_6GHZ)
			goto check_sec_chan;

		sta_ht_cap = &sbands->ht_cap;
        if (sta_ht_cap == NULL || !sta_ht_cap->ht_supported)
            return false;

        if (chandef->width == NL80211_CHAN_WIDTH_40) {
            u32 cfreq = chandef->chan->center_freq;
            if (!(sta_ht_cap->cap & IEEE80211_HTCAP_SUP_WIDTH_20_40) ||
                (sta_ht_cap->cap & IEEE80211_HTCAP_40MHZ_INTOLERANT))
                return false;
            if (chandef->center_freq1 < cfreq &&
                chandef->chan->flags & IEEE80211_CHAN_NO_HT40MINUS)
                return false;
            if (chandef->center_freq1 > cfreq &&
                chandef->chan->flags & IEEE80211_CHAN_NO_HT40PLUS)
                return false;
        }
    }
    else if (chandef->width == NL80211_CHAN_WIDTH_80 ||
        chandef->width == NL80211_CHAN_WIDTH_80P80 ||
        chandef->width == NL80211_CHAN_WIDTH_160) {
        const struct ieee80211_sta_vht_cap *sta_vht_cap;
		struct ieee80211_supported_band *sbands = net80211_get_sband(pdev, chandef->chan->band);
		if (sbands == NULL)
			return false;

        if (chandef->chan->band == NL80211_BAND_6GHZ)
			goto check_sec_chan;

		sta_vht_cap = &sbands->vht_cap;
        if (sta_vht_cap == NULL || !sta_vht_cap->vht_supported)
            return false;

        if (chandef->width == NL80211_CHAN_WIDTH_80P80) {
            u32 cap = sta_vht_cap->cap & IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK;
            if (cap != IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ)
                return false;
        }
        else if (chandef->width == NL80211_CHAN_WIDTH_160) {
            u32 cap = sta_vht_cap->cap & IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK;
            if (cap != IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160MHZ &&
                cap != IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ)
                return false;
        }
    }

check_sec_chan:
    if (!net80211_secondary_channel_ok(pdev, chandef->center_freq1,
        chandef->width, prohibited_flags))
        return false;

    if (!chandef->center_freq2)
        return true;
    return net80211_secondary_channel_ok(pdev, chandef->center_freq2,
        chandef->width, prohibited_flags);
}

enum nl80211_chan_width net80211_get_sta_bw(struct net80211_sta *sta)
{
    enum nl80211_chan_width chanwidth;
	
    switch (net80211_sta_get_bandwidth(sta)) {
    case IEEE80211_STA_RX_BANDWIDTH_20:
        chanwidth = sta->ht_cap.ht_supported ?
            NL80211_CHAN_WIDTH_20 : NL80211_CHAN_WIDTH_20_NOHT;
        break;
    case IEEE80211_STA_RX_BANDWIDTH_40:
        chanwidth = NL80211_CHAN_WIDTH_40;
        break;
    case IEEE80211_STA_RX_BANDWIDTH_80:
        chanwidth = NL80211_CHAN_WIDTH_80;
        break;
    case IEEE80211_STA_RX_BANDWIDTH_160:
        chanwidth = NL80211_CHAN_WIDTH_160;
        break;
    default:
        WARN_ON(1);
        chanwidth = NL80211_CHAN_WIDTH_20;
    }

    return chanwidth;
}

static enum nl80211_chan_width
net80211_get_max_required_bw(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    enum nl80211_chan_width max_bw = NL80211_CHAN_WIDTH_20_NOHT;
    struct net80211_sta *sta;

	list_for_each_entry(sta, &pdev->sta_list, struct net80211_sta, node) {
        if (vif != sta->vif)
            continue;
        max_bw = max(max_bw, net80211_get_sta_bw(sta));
    }

    return max_bw;
}

static enum nl80211_chan_width
net80211_get_chanctx_max_required_bw(struct net80211_pdev *pdev,
    struct ieee80211_chanctx_conf *conf)
{
	struct net80211_vif *vif;
    enum nl80211_chan_width max_bw = NL80211_CHAN_WIDTH_20_NOHT;

    list_for_each_entry(vif, &pdev->interfaces, 
        struct net80211_vif, node) {
        enum nl80211_chan_width width = NL80211_CHAN_WIDTH_20_NOHT;

        if (!vif->is_running)
            continue;

        if (vif->chanctx_conf != conf)
            continue;

        switch (vif->type) {
        case NL80211_IFTYPE_STATION:
            width = max(vif->bss_conf.chandef.width,
                net80211_get_max_required_bw(vif));
            break;
        default:
            WARN_ON_ONCE(1);
        }
        max_bw = max(max_bw, width);
    }

    return max_bw;
}

void net80211_recalc_chanctx_min_def(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx)
{
    enum nl80211_chan_width max_bw;
    struct ieee80211_chan_def min_def;

	/* will NOT optimize the confs for 5M/10M/radar enable */
    if (ctx->conf.def.width == NL80211_CHAN_WIDTH_5 ||
        ctx->conf.def.width == NL80211_CHAN_WIDTH_10 ||
        ctx->conf.radar_enabled) {
        ctx->conf.min_def = ctx->conf.def;
        return;
    }

    max_bw = net80211_get_chanctx_max_required_bw(pdev, &ctx->conf);

	/* downgrade chandef up to max_bw */
    min_def = ctx->conf.def;
    while (min_def.width > max_bw)
        ieee80211_chandef_downgrade(&min_def);

    /* if the min_def is the same, no need to update */
    if (ieee80211_chandef_identical(&ctx->conf.min_def, &min_def))
        return;

    ctx->conf.min_def = min_def;
    if (!ctx->driver_present)
        return;

    drv_update_chanctx(pdev, ctx, IEEE80211_CHANCTX_CHANGE_MIN_WIDTH);
}

void net80211_recalc_min_chandef(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct ieee80211_chanctx *chanctx;

	chanctx_conf = vif->chanctx_conf;

	if (WARN_ON_ONCE(!chanctx_conf))
		return;

    // get the addr of chanctx
	chanctx = container_of(chanctx_conf, struct ieee80211_chanctx, conf);
	
	net80211_recalc_chanctx_min_def(pdev, chanctx);
}

int net80211_chanctx_refcount(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx)
{
    struct net80211_vif *vif;
    int num = 0;

    list_for_each_entry(vif, &ctx->assigned_vifs,
        struct net80211_vif, assigned_chanctx_list) {
        num++;
    }

    return num;
}

static void net80211_free_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx)
{
    WARN_ON_ONCE(net80211_chanctx_refcount(pdev, ctx) != 0);

    list_del(&ctx->list);
	drv_remove_chanctx(pdev, ctx);
    net_dbg("chanctx=0x%p\n", ctx);
    kfree(ctx);
}

static struct ieee80211_chanctx *
net80211_alloc_chanctx(struct net80211_pdev *pdev,
    const struct ieee80211_chan_def *chandef)
{
    struct ieee80211_chanctx *ctx;

    ctx = kzalloc(sizeof(*ctx) + pdev->conf.chanctx_data_size, GFP_KERNEL); //TODOTODO chanctx_data_size is 0???
    if (!ctx)
        return NULL;

    list_init_head(&ctx->assigned_vifs);
    ctx->conf.def = *chandef;
    ctx->conf.rx_chains_static = 1;
    ctx->conf.rx_chains_dynamic = 1;
    ctx->conf.radar_enabled = false;
    net80211_recalc_chanctx_min_def(pdev, ctx);

    return ctx;
}

static struct ieee80211_chanctx *
net80211_new_chanctx(struct net80211_pdev *pdev,
    const struct ieee80211_chan_def *chandef)
{
    struct ieee80211_chanctx *ctx;
    int err;
	
    ctx = net80211_alloc_chanctx(pdev, chandef);
    net_dbg("chanctx=0x%p\n", ctx);
    if (!ctx)
        return ERR_PTR(-ENOMEM);

    err = drv_add_chanctx(pdev, ctx);
    if (err) {
        kfree(ctx);
        return ERR_PTR(err);
    }

	list_add_tail(&ctx->list, &pdev->chanctx_list);

    net_dbg("chanctx=0x%p\n", ctx);

    return ctx;
}

static void net80211_change_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx,
    const struct ieee80211_chan_def *chandef)
{
    if (ieee80211_chandef_identical(&ctx->conf.def, chandef)) {
        net80211_recalc_chanctx_min_def(pdev, ctx);
        return;
    }

    WARN_ON(!ieee80211_chandef_compatible(&ctx->conf.def, chandef));

    ctx->conf.def = *chandef;
    drv_update_chanctx(pdev, ctx, IEEE80211_CHANCTX_CHANGE_WIDTH);
    net80211_recalc_chanctx_min_def(pdev, ctx);
}

static struct ieee80211_chanctx *
net80211_find_chanctx(struct net80211_pdev *pdev,
    const struct ieee80211_chan_def *chandef)
{
    struct ieee80211_chanctx *ctx;

    list_for_each_entry(ctx, &pdev->chanctx_list, struct ieee80211_chanctx, list) {
        if (ieee80211_chandef_identical(&ctx->conf.def, chandef)) {
            return ctx;
        }
    }

    return NULL;
}

void net80211_recalc_chanctx_chantype(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *ctx)
{
    struct ieee80211_chanctx_conf *conf = &ctx->conf;
    struct net80211_vif *vif;
    const struct ieee80211_chan_def *compat = NULL;

    list_for_each_entry(vif, &pdev->interfaces, 
        struct net80211_vif, node) {

        if (!vif->is_running)
            continue;
        if (rcu_access_pointer(vif->chanctx_conf) != conf)
            continue;
        if (vif->type == NL80211_IFTYPE_AP_VLAN)
            continue;

        if (!compat)
            compat = &vif->bss_conf.chandef;

        compat = ieee80211_chandef_compatible(
            &vif->bss_conf.chandef, compat);
        if (WARN_ON_ONCE(!compat))
            break;
    }

    if (!compat)
        return;

    net80211_change_chanctx(pdev, ctx, compat);
}

void net80211_recalc_smps_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *chanctx)
{
    struct net80211_vif *vif;
    u8 rx_chains_static, rx_chains_dynamic;

    rx_chains_static = 1;
    rx_chains_dynamic = 1;

    list_for_each_entry(vif, &pdev->interfaces, 
        struct net80211_vif, node) {
        u8 needed_static, needed_dynamic;

        if (!vif->is_running)
            continue;

        if (rcu_access_pointer(vif->chanctx_conf) !=
            &chanctx->conf)
            continue;

        switch (vif->type) {
        case NL80211_IFTYPE_STATION:
            if (!net80211_vif_get_associated(vif))
                continue;
            break;
        default:
            WARN_ON_ONCE(1);
        }

        switch (vif->smps_mode) {
        default:
            WARN(1, "Invalid SMPS mode %d\n",
                vif->smps_mode);
            /* fall through */
        case IEEE80211_SMPS_NONE:
            needed_static = vif->needed_rx_chains;
            needed_dynamic = vif->needed_rx_chains;
            break;
        case IEEE80211_SMPS_DYNAMIC:
            needed_static = 1;
            needed_dynamic = vif->needed_rx_chains;
            break;
        case IEEE80211_SMPS_STATIC:
			/*static mode and set needed_static = 1 && needed_dynamic = 1*/
            needed_static = 1;
            needed_dynamic = 1;
            break;
        }

        rx_chains_static = max(rx_chains_static, needed_static);
        rx_chains_dynamic = max(rx_chains_dynamic, needed_dynamic);
    }

    /* no need to re-calculate for the values are the same */
    if (rx_chains_static == chanctx->conf.rx_chains_static &&
        rx_chains_dynamic == chanctx->conf.rx_chains_dynamic)
        return;

    /* Use the new calcaculated values*/
    chanctx->conf.rx_chains_static = rx_chains_static;
    chanctx->conf.rx_chains_dynamic = rx_chains_dynamic;
    drv_update_chanctx(pdev, chanctx, IEEE80211_CHANCTX_CHANGE_RX_CHAINS);
}

int net80211_hw_config(struct net80211_pdev *pdev, u32 changed)
{
    int ret = 0;

    changed &= ~(IEEE80211_CONF_CHANGED_CHANNEL |
        IEEE80211_CONF_CHANGED_POWER);

    if (changed && pdev->drv_started) {
        ret = drv_config(pdev, changed);
    }

    return ret;
}

bool __net80211_recalc_txpower(struct net80211_vif *vif)
{
    struct ieee80211_chanctx_conf *chanctx_conf;
    int power;

    chanctx_conf = rcu_dereference(vif->chanctx_conf);
    if (!chanctx_conf) {
        return false;
    }

    power = ieee80211_chandef_max_power(&chanctx_conf->def);
	if (vif->ap_power_level != NET80211_UNSET_POWER_LEVEL)
		power = min(power, vif->ap_power_level);
	
	if (net80211_vif_bss_conf_set_txpower(vif, power)) {
		net80211_hw_config(vif->pdev, 0);
        return true;
	}

    return false;
}

void net80211_recalc_txpower(struct net80211_vif *vif,
    bool update_bss)
{
    if (__net80211_recalc_txpower(vif) ||
        (update_bss && vif->is_running))
        net80211_vif_bss_conf_change_notify(vif);
}

static int net80211_assign_vif_chanctx(struct net80211_vif *vif,
    struct ieee80211_chanctx *new_ctx)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct ieee80211_chanctx_conf *conf;
    struct ieee80211_chanctx *curr_ctx = NULL;
    int ret = 0;

    net_dbg("vif=0x%p, new_ctx=0x%p\n", vif, new_ctx);

    conf = vif->chanctx_conf;
    if (conf) {
        curr_ctx = container_of(conf, struct ieee80211_chanctx, conf);

        drv_unassign_vif_chanctx(pdev, vif, curr_ctx);
        conf = NULL;
        list_del(&vif->assigned_chanctx_list);
    }

    if (new_ctx) {
        ret = drv_assign_vif_chanctx(pdev, vif, new_ctx);
        if (ret)
            goto out;

        conf = &new_ctx->conf;
		list_add_tail(&vif->assigned_chanctx_list, &new_ctx->assigned_vifs);
    }

out:
    rcu_assign_pointer(vif->chanctx_conf, conf);

    if (vif->chanctx_conf) {
        net_warn("chanctx band=%u, center_freq=%u\n",
            vif->chanctx_conf->def.chan->band,
            vif->chanctx_conf->def.chan->center_freq);
    }

    vif->bss_conf.idle = !conf;

    if (curr_ctx && net80211_chanctx_refcount(pdev, curr_ctx) > 0) {
        net80211_recalc_chanctx_chantype(pdev, curr_ctx);
        net80211_recalc_smps_chanctx(pdev, curr_ctx);
        net80211_recalc_chanctx_min_def(pdev, curr_ctx);
    }

    if (new_ctx && net80211_chanctx_refcount(pdev, new_ctx) > 0) {
        net80211_recalc_txpower(vif, false);
        net80211_recalc_chanctx_min_def(pdev, new_ctx);
    }

    if (vif->type != NL80211_IFTYPE_P2P_DEVICE &&
        vif->type != NL80211_IFTYPE_MONITOR)
        net80211_vif_bss_conf_change_notify(vif);

    return ret;
}

static inline void
net80211_vif_update_chandef(struct net80211_vif *vif,
    const struct ieee80211_chan_def *chandef)
{
    vif->bss_conf.chandef = *chandef;
}

void net80211_vif_release_channel(struct net80211_vif *vif)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct ieee80211_chanctx_conf *conf;
    struct ieee80211_chanctx *ctx;

    net_dbg("vif->chanctx_conf=0x%p\n", vif->chanctx_conf);

    conf = vif->chanctx_conf;
    if (!conf)
        return;

    /* get the chanctx from conf */
    ctx = container_of(conf, struct ieee80211_chanctx, conf);
    /* free the chanctx */
    net80211_assign_vif_chanctx(vif, NULL);
    if (net80211_chanctx_refcount(pdev, ctx) == 0) {
		// When there is NO assigned_chanctx_list, free the ctx
        net80211_free_chanctx(pdev, ctx);
    }
}

int net80211_vif_use_channel(struct net80211_vif *vif,
    const struct ieee80211_chan_def *chandef)
{
	struct net80211_pdev *pdev = vif->pdev;
	struct ieee80211_chanctx *ctx;
	int ret;

	net80211_vif_release_channel(vif);

	ctx = net80211_find_chanctx(pdev, chandef);
	net_dbg("net80211_find_chanctx -> ctx=0x%p\n", ctx);
	
	if (!ctx) {
		ctx = net80211_new_chanctx(pdev, chandef);
	}
	if (IS_ERR(ctx)) {
		ret = PTR_ERR(ctx);
		goto out;
	}

    net80211_vif_update_chandef(vif, chandef);

	ret = net80211_assign_vif_chanctx(vif, ctx);
	if (ret) {
		/* free the chanctx when refcnt is 0 */
		if (net80211_chanctx_refcount(pdev, ctx) == 0)
			net80211_free_chanctx(pdev, ctx);
		goto out;
	}

out:
	return ret;
}

int net80211_vif_get_channel_shift(struct net80211_vif *vif)
{
    struct ieee80211_chanctx_conf *chanctx_conf;
    int shift = 0;

    chanctx_conf = net80211_vif_get_chanctx_conf(vif);
    if (chanctx_conf)
        shift = ieee80211_chandef_get_shift(&chanctx_conf->def);

    return shift;
}

void net80211_chanctx_init(struct net80211_pdev *pdev)
{
    list_init_head(&pdev->chanctx_list);
}

void net80211_chanctx_remove(struct net80211_pdev *pdev)
{

}
