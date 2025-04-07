/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2008-2011	Luis R. Rodriguez <mcgrof@qca.qualcomm.com>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright      2017  Intel Deutschland GmbH
 * Copyright (C) 2018 - 2019 Intel Corporation
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
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 1/9/21    zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/qbase.h>
#include <net/regulatory.h>
#include <net/ndebug.h>
#include <net/mac80211.h>

/* Sanity check on a regulatory rule */
static bool is_valid_reg_rule(const struct ieee80211_reg_rule *rule)
{
    const struct ieee80211_freq_range *freq_range = &rule->freq_range;
    u32 freq_diff;

    if (freq_range->start_freq_khz <= 0 || freq_range->end_freq_khz <= 0)
        return false;

    if (freq_range->start_freq_khz > freq_range->end_freq_khz)
        return false;

    freq_diff = freq_range->end_freq_khz - freq_range->start_freq_khz;

    if (freq_range->end_freq_khz <= freq_range->start_freq_khz ||
        freq_range->max_bandwidth_khz > freq_diff)
        return false;

    return true;
}

static bool is_valid_rd(const struct ieee80211_regdomain *rd)
{
    const struct ieee80211_reg_rule *reg_rule = NULL;
    u32 i;

    if (!rd->n_reg_rules)
        return false;

    if (WARN_ON(rd->n_reg_rules > (u32)NL80211_MAX_SUPP_REG_RULES))
        return false;

    for (i = 0; i < rd->n_reg_rules; i++) {
        reg_rule = &rd->reg_rules[i];
        if (!is_valid_reg_rule(reg_rule))
            return false;
    }

    return true;
}

 /**
  * freq_in_rule_band - tells us if a frequency is in a frequency band
  * @freq_range: frequency rule we want to query
  * @freq_khz: frequency we are inquiring about
  *
  * This lets us know if a specific frequency rule is or is not relevant to
  * a specific frequency's band. Bands are device specific and artificial
  * definitions (the "2.4 GHz band", the "5 GHz band" and the "60GHz band"),
  * however it is safe for now to assume that a frequency rule should not be
  * part of a frequency's band if the start freq or end freq are off by more
  * than 2 GHz for the 2.4 and 5 GHz bands, and by more than 20 GHz for the
  * 60 GHz band.
  * This resolution can be lowered and should be considered as we add
  * regulatory rule support for other "bands".
  **/
static bool freq_in_rule_band(const struct ieee80211_freq_range *freq_range,
    u32 freq_khz)
{
#define ONE_GHZ_IN_KHZ	1000000
    /*
     * From 802.11ad: directional multi-gigabit (DMG):
     * Pertaining to operation in a frequency band containing a channel
     * with the Channel starting frequency above 45 GHz.
     */
    u32 limit = freq_khz > 45 * ONE_GHZ_IN_KHZ ?
        20 * ONE_GHZ_IN_KHZ : 2 * ONE_GHZ_IN_KHZ;
    if (abs((s32)freq_khz - (s32)freq_range->start_freq_khz) <= limit)
        return true;
    if (abs((s32)freq_khz - (s32)freq_range->end_freq_khz) <= limit)
        return true;
    return false;
#undef ONE_GHZ_IN_KHZ
}

bool freq_bw_fit_range(const struct ieee80211_freq_range *freq_range,
    u32 center_freq_khz, u32 bw_khz)
{
    u32 start_freq_khz;
    u32 end_freq_khz;

    start_freq_khz = center_freq_khz - (bw_khz / 2);
    if (start_freq_khz < freq_range->start_freq_khz)
        return false;

    end_freq_khz = center_freq_khz + (bw_khz / 2);
    if (end_freq_khz > freq_range->end_freq_khz)
        return false;

    return true;
}


static const struct ieee80211_reg_rule *
freq_reg_info_regd(u32 center_freq,
    const struct ieee80211_regdomain *regd, u32 bw)
{
    u32 i;
    bool band_rule_found = false;
    bool bw_fits = false;

    if (!regd)
        return ERR_PTR(-EINVAL);

    for (i = 0; i < regd->n_reg_rules; i++) {
        const struct ieee80211_reg_rule *rr;
        const struct ieee80211_freq_range *fr = NULL;

        rr = &regd->reg_rules[i];
        fr = &rr->freq_range;

        /*
         * We only need to know if one frequency rule was
         * was in center_freq's band, that's enough, so lets
         * not overwrite it once found
         */
        if (!band_rule_found)
            band_rule_found = freq_in_rule_band(fr, center_freq);

        bw_fits = freq_bw_fit_range(fr, center_freq, bw);

        if (band_rule_found && bw_fits)
            return rr;
    }

    if (!band_rule_found)
        return ERR_PTR(-ERANGE);

    return ERR_PTR(-EINVAL);
}

static const struct ieee80211_reg_rule *
__freq_reg_info(struct net80211_pdev *pdev, u32 center_freq, u32 min_bw)
{
    const struct ieee80211_regdomain *regd = net80211_regulatory_get_regdomain(pdev);
    const struct ieee80211_reg_rule *reg_rule = NULL;
    u32 bw;

    for (bw = MHZ_TO_KHZ(20); bw >= min_bw; bw = bw / 2) {
        reg_rule = freq_reg_info_regd(center_freq, regd, bw);
        if (!IS_ERR(reg_rule))
            return reg_rule;
    }

    return reg_rule;
}

const struct ieee80211_reg_rule *freq_reg_info(
    struct net80211_pdev *pdev,
    u32 center_freq)
{
    return __freq_reg_info(pdev, center_freq, MHZ_TO_KHZ(20));
}

static unsigned int
reg_get_max_bandwidth_from_range(const struct ieee80211_regdomain *rd,
    const struct ieee80211_reg_rule *rule)
{
    const struct ieee80211_freq_range *freq_range = &rule->freq_range;
    const struct ieee80211_freq_range *freq_range_tmp;
    const struct ieee80211_reg_rule *tmp;
    u32 start_freq, end_freq, idx, no;

    for (idx = 0; idx < rd->n_reg_rules; idx++)
        if (rule == &rd->reg_rules[idx])
            break;

    if (idx == rd->n_reg_rules)
        return 0;

    /* get start_freq */
    no = idx;

    while (no) {
        tmp = &rd->reg_rules[--no];
        freq_range_tmp = &tmp->freq_range;

        if (freq_range_tmp->end_freq_khz < freq_range->start_freq_khz)
            break;

        freq_range = freq_range_tmp;
    }

    start_freq = freq_range->start_freq_khz;

    /* get end_freq */
    freq_range = &rule->freq_range;
    no = idx;

    while (no < rd->n_reg_rules - 1) {
        tmp = &rd->reg_rules[++no];
        freq_range_tmp = &tmp->freq_range;

        if (freq_range_tmp->start_freq_khz > freq_range->end_freq_khz)
            break;

        freq_range = freq_range_tmp;
    }

    end_freq = freq_range->end_freq_khz;

    return end_freq - start_freq;
}

unsigned int reg_get_max_bandwidth(const struct ieee80211_regdomain *rd,
    const struct ieee80211_reg_rule *rule)
{
    unsigned int bw = reg_get_max_bandwidth_from_range(rd, rule);

    if (rule->flags & NL80211_RRF_NO_160MHZ)
        bw = min_t(unsigned int, bw, MHZ_TO_KHZ(80));
    if (rule->flags & NL80211_RRF_NO_80MHZ)
        bw = min_t(unsigned int, bw, MHZ_TO_KHZ(40));

    /*
     * HT40+/HT40- limits are handled per-channel. Only limit BW if both
     * are not allowed.
     */
    if (rule->flags & NL80211_RRF_NO_HT40MINUS &&
        rule->flags & NL80211_RRF_NO_HT40PLUS)
        bw = min_t(unsigned int, bw, MHZ_TO_KHZ(20));

    return bw;
}

static uint32_t reg_rule_to_chan_bw_flags(const struct ieee80211_regdomain *regd,
    const struct ieee80211_reg_rule *reg_rule,
    const struct ieee80211_channel *chan)
{
    const struct ieee80211_freq_range *freq_range = NULL;
    u32 max_bandwidth_khz, bw_flags = 0;

    freq_range = &reg_rule->freq_range;

    max_bandwidth_khz = freq_range->max_bandwidth_khz;
    /* Check if auto calculation requested */
    if (reg_rule->flags & NL80211_RRF_AUTO_BW)
        max_bandwidth_khz = reg_get_max_bandwidth(regd, reg_rule);

    /* If we get a reg_rule we can assume that at least 5Mhz fit */
    if (!freq_bw_fit_range(freq_range,
        MHZ_TO_KHZ(chan->center_freq),
        MHZ_TO_KHZ(10)))
        bw_flags |= IEEE80211_CHAN_NO_10MHZ;
    if (!freq_bw_fit_range(freq_range,
        MHZ_TO_KHZ(chan->center_freq),
        MHZ_TO_KHZ(20)))
        bw_flags |= IEEE80211_CHAN_NO_20MHZ;

    if (max_bandwidth_khz < MHZ_TO_KHZ(10))
        bw_flags |= IEEE80211_CHAN_NO_10MHZ;
    if (max_bandwidth_khz < MHZ_TO_KHZ(20))
        bw_flags |= IEEE80211_CHAN_NO_20MHZ;
    if (max_bandwidth_khz < MHZ_TO_KHZ(40))
        bw_flags |= IEEE80211_CHAN_NO_HT40;
    if (max_bandwidth_khz < MHZ_TO_KHZ(80))
        bw_flags |= IEEE80211_CHAN_NO_80MHZ;
    if (max_bandwidth_khz < MHZ_TO_KHZ(160))
        bw_flags |= IEEE80211_CHAN_NO_160MHZ;
    return bw_flags;
}

static bool is_ht40_allowed(struct ieee80211_channel *chan)
{
    if (!chan)
        return false;
    if (chan->flags & IEEE80211_CHAN_DISABLED)
        return false;
    /* This would happen when regulatory rules disallow HT40 completely */
    if ((chan->flags & IEEE80211_CHAN_NO_HT40) == IEEE80211_CHAN_NO_HT40)
        return false;
    return true;
}

static void reg_process_ht_flags_channel(struct net80211_pdev *pdev,
    struct ieee80211_channel *channel)
{
    struct ieee80211_supported_band *sband = net80211_get_sband(pdev, channel->band);
    struct ieee80211_channel *channel_before = NULL, *channel_after = NULL;
    const struct ieee80211_regdomain *regd;
    unsigned int i;
    u32 flags;

    if (sband == NULL)
		return;

    if (!is_ht40_allowed(channel)) {
        channel->flags |= IEEE80211_CHAN_NO_HT40;
        return;
    }

    /*
     * We need to ensure the extension channels exist to
     * be able to use HT40- or HT40+, this finds them (or not)
     */
    for (i = 0; i < sband->n_channels; i++) {
        struct ieee80211_channel *c = &sband->channels[i];

        if (c->center_freq == (channel->center_freq - 20))
            channel_before = c;
        if (c->center_freq == (channel->center_freq + 20))
            channel_after = c;
    }

    flags = 0;
    regd = net80211_regulatory_get_regdomain(pdev);
    if (regd) {
        const struct ieee80211_reg_rule *reg_rule =
            freq_reg_info_regd(MHZ_TO_KHZ(channel->center_freq),
                regd, MHZ_TO_KHZ(20));

        if (!IS_ERR(reg_rule))
            flags = reg_rule->flags;
    }

    /*
     * Please note that this assumes target bandwidth is 20 MHz,
     * if that ever changes we also need to change the below logic
     * to include that as well.
     */
    if (!is_ht40_allowed(channel_before) ||
        flags & NL80211_RRF_NO_HT40MINUS)
        channel->flags |= IEEE80211_CHAN_NO_HT40MINUS;
    else
        channel->flags &= ~IEEE80211_CHAN_NO_HT40MINUS;

    if (!is_ht40_allowed(channel_after) ||
        flags & NL80211_RRF_NO_HT40PLUS)
        channel->flags |= IEEE80211_CHAN_NO_HT40PLUS;
    else
        channel->flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
}

static void reg_process_ht_flags_band(
    struct net80211_pdev *pdev,
    struct ieee80211_supported_band *sband)
{
    unsigned int i;

    if (!sband)
        return;

    for (i = 0; i < sband->n_channels; i++)
        reg_process_ht_flags_channel(pdev, &sband->channels[i]);
}

static void reg_process_ht_flags(struct net80211_pdev *pdev)
{
    enum nl80211_band band;

    if (!pdev)
        return;

    for (band = 0; band < NUM_NL80211_BANDS; band++)
        reg_process_ht_flags_band(pdev, net80211_get_sband(pdev, band));
}

/*
 * XXX: add support for the rest of enum nl80211_reg_rule_flags, we may
 * want to just have the channel structure use these
 */
static u32 map_regdom_flags(u32 rd_flags)
{
    u32 channel_flags = 0;
    if (rd_flags & NL80211_RRF_NO_IR_ALL)
        channel_flags |= IEEE80211_CHAN_NO_IR;
    if (rd_flags & NL80211_RRF_DFS)
        channel_flags |= IEEE80211_CHAN_RADAR;
    if (rd_flags & NL80211_RRF_NO_OFDM)
        channel_flags |= IEEE80211_CHAN_NO_OFDM;
    if (rd_flags & NL80211_RRF_NO_OUTDOOR)
        channel_flags |= IEEE80211_CHAN_INDOOR_ONLY;
    if (rd_flags & NL80211_RRF_IR_CONCURRENT)
        channel_flags |= IEEE80211_CHAN_IR_CONCURRENT;
    if (rd_flags & NL80211_RRF_NO_HT40MINUS)
        channel_flags |= IEEE80211_CHAN_NO_HT40MINUS;
    if (rd_flags & NL80211_RRF_NO_HT40PLUS)
        channel_flags |= IEEE80211_CHAN_NO_HT40PLUS;
    if (rd_flags & NL80211_RRF_NO_80MHZ)
        channel_flags |= IEEE80211_CHAN_NO_80MHZ;
    if (rd_flags & NL80211_RRF_NO_160MHZ)
        channel_flags |= IEEE80211_CHAN_NO_160MHZ;
    if (rd_flags & NL80211_RRF_NO_HE)
        channel_flags |= IEEE80211_CHAN_NO_HE;
    return channel_flags;
}

static void handle_channel_custom(struct net80211_pdev *pdev,
    struct ieee80211_channel *chan,
    const struct ieee80211_regdomain *regd,
    u32 min_bw)
{
    u32 bw_flags = 0;
    const struct ieee80211_reg_rule *reg_rule = NULL;
    const struct ieee80211_power_rule *power_rule = NULL;
    u32 bw;

    for (bw = MHZ_TO_KHZ(20); bw >= min_bw; bw = bw / 2) {
        reg_rule = freq_reg_info_regd(MHZ_TO_KHZ(chan->center_freq),
            regd, bw);
        if (!IS_ERR(reg_rule))
            break;
    }

    if (IS_ERR_OR_NULL(reg_rule)) {
        pr_debug("Disabling freq %d MHz as custom regd has no rule that fits it\n",
            chan->center_freq);
        chan->flags |= IEEE80211_CHAN_DISABLED;
        return;
    }

    power_rule = &reg_rule->power_rule;
    bw_flags = reg_rule_to_chan_bw_flags(regd, reg_rule, chan);

    chan->flags = bw_flags | map_regdom_flags(reg_rule->flags);
    chan->max_antenna_gain = (int)MBI_TO_DBI(power_rule->max_antenna_gain);
    chan->max_reg_power = chan->max_power =
        (int)MBM_TO_DBM(power_rule->max_eirp);

    chan->max_power = chan->max_reg_power;
}

static void handle_band_custom(struct net80211_pdev *pdev,
    struct ieee80211_supported_band *sband,
    const struct ieee80211_regdomain *regd)
{
    unsigned int i;

    if (!sband)
        return;

    /*
     * We currently assume that you always want at least 20 MHz,
     * otherwise channel 12 might get enabled if this rule is
     * compatible to US, which permits 2402 - 2472 MHz.
     */
    for (i = 0; i < sband->n_channels; i++)
        handle_channel_custom(pdev, &sband->channels[i], regd,
            MHZ_TO_KHZ(20));
}

static void reg_process_self_managed_hints(
    struct net80211_pdev *pdev, 
    const struct ieee80211_regdomain *regd)
{
    const struct ieee80211_regdomain *tmp;
    enum nl80211_band band;

    tmp = pdev->regd;
    rcu_assign_pointer(pdev->regd, regd);
    kfree((void *)tmp);

    for (band = 0; band < NUM_NL80211_BANDS; band++)
        handle_band_custom(pdev, net80211_get_sband(pdev, band), regd);

    reg_process_ht_flags(pdev);
}

static const struct ieee80211_regdomain *
reg_copy_regd(const struct ieee80211_regdomain *src_regd)
{
    struct ieee80211_regdomain *regd;
    unsigned int i;

    regd = kzalloc(struct_size(regd, reg_rules, src_regd->n_reg_rules),
        GFP_KERNEL);
    if (!regd)
        return ERR_PTR(-ENOMEM);

    memcpy(regd, src_regd, sizeof(struct ieee80211_regdomain));

    for (i = 0; i < src_regd->n_reg_rules; i++)
        memcpy(&regd->reg_rules[i], &src_regd->reg_rules[i],
            sizeof(struct ieee80211_reg_rule));

    return regd;
}

const struct ieee80211_regdomain *
net80211_regulatory_get_regdomain(struct net80211_pdev *pdev)
{
    return pdev->regd;
}

int net80211_regulatory_set_regdomain(struct net80211_pdev *pdev,
    struct ieee80211_regdomain *regd)
{
    const struct ieee80211_regdomain *regd_cloned;

    if (!is_valid_rd(regd)) {
        pr_debug("Invalid regulatory domain detected\n");
        return -EINVAL;
    }

    regd_cloned = reg_copy_regd(regd);
    if (IS_ERR(regd_cloned))
        return PTR_ERR(regd_cloned);

    /* process the request immediately */
    reg_process_self_managed_hints(pdev, regd_cloned);
    return 0;
}

void net80211_regulatory_register(struct net80211_pdev *pdev)
{
    pr_debug("pdev 0x%p\n", pdev);
}

void net80211_regulatory_deregister(struct net80211_pdev *pdev)
{
    pr_debug("pdev 0x%p\n", pdev);
    kfree((void *)pdev->regd);
    rcu_assign_pointer(pdev->regd, NULL);
}