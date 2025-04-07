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

#ifndef __NET_NET80211_CHAN_H
#define __NET_NET80211_CHAN_H

#include <net/ieee80211.h>
#include <net/mac80211.h>
#include "net80211_i.h"

/*---------------------------------------------------------------------------*/
/* chandef */

void
ieee80211_chandef_create(struct ieee80211_chan_def *chandef,
    struct ieee80211_channel *channel,
    enum nl80211_channel_type chantype);

static inline bool
ieee80211_chandef_identical(const struct ieee80211_chan_def *chandef1,
    const struct ieee80211_chan_def *chandef2)
{
    return (chandef1->chan == chandef2->chan &&
        chandef1->width == chandef2->width &&
        chandef1->center_freq1 == chandef2->center_freq1 &&
        chandef1->center_freq2 == chandef2->center_freq2);
}

const struct ieee80211_chan_def *
ieee80211_chandef_compatible(const struct ieee80211_chan_def *chandef1,
    const struct ieee80211_chan_def *chandef2);

bool ieee80211_chandef_valid(const struct ieee80211_chan_def *chandef);

static inline enum ieee80211_rate_flags
ieee80211_chandef_rate_flags(struct ieee80211_chan_def *chandef)
{
    if (NL80211_CHAN_WIDTH_5 == chandef->width)
        return IEEE80211_RATE_SUPPORTS_5MHZ;
    if (NL80211_CHAN_WIDTH_10 == chandef->width)
        return IEEE80211_RATE_SUPPORTS_10MHZ;
    return 0;
}

static inline int
ieee80211_chandef_max_power(struct ieee80211_chan_def *chandef)
{
    if (NL80211_CHAN_WIDTH_5 == chandef->width)
        return min(chandef->chan->max_reg_power - 6,
            chandef->chan->max_power);
    if (NL80211_CHAN_WIDTH_10 == chandef->width)
        return min(chandef->chan->max_reg_power - 3,
            chandef->chan->max_power);

    return chandef->chan->max_power;
}

/*---------------------------------------------------------------------------*/
/* helpers */
bool ieee80211_chandef_ht_operation(const struct ieee80211_ht_operation *htop,
    struct ieee80211_chan_def *chandef);

bool ieee80211_chandef_vht_operation(
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_vht_operation *vhtop,
    const struct ieee80211_ht_operation *htop,
    bool supports_vht_ext_nss_bw,
    struct ieee80211_chan_def *chandef);

u32 ieee80211_chandef_downgrade(struct ieee80211_chan_def *c);


/*---------------------------------------------------------------------------*/
bool
net80211_chandef_usable(struct net80211_pdev *pdev,
    const struct ieee80211_chan_def *chandef,
    u32 prohibited_flags);

int
net80211_vif_use_channel(struct net80211_vif *vif,
    const struct ieee80211_chan_def *chandef);

void
net80211_vif_release_channel(struct net80211_vif *vif);

int
net80211_vif_get_channel_shift(struct net80211_vif *vif);

void
net80211_recalc_min_chandef(struct net80211_vif *vif);

void
net80211_recalc_smps_chanctx(struct net80211_pdev *pdev,
    struct ieee80211_chanctx *chanctx);

void 
net80211_recalc_txpower(struct net80211_vif *vif, bool update_bss);

#endif // !__NET_NET80211_CHAN_H
