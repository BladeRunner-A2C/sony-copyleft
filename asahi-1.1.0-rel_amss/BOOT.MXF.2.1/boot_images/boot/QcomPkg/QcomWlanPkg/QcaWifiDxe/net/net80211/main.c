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
#include <net/net80211/net80211_i.h>
#include <net/net80211/reg.h>

/* Implmentation exposed to lower layer */
struct ieee80211_ops;

struct net80211_pdev *
net80211_pdev_alloc(size_t priv_data_len,
    const struct ieee80211_ops *ops)
{
    struct net80211_pdev *pdev;
    size_t alloc_size;

    alloc_size = sizeof(*pdev) + priv_data_len;

    pdev = kzalloc(alloc_size, GFP_KERNEL);
    if (!pdev)
        return NULL;

    /* intialize the pdev->conf */
    pdev->conf.rts_threshold = (u32)-1;
    pdev->conf.dynamic_ps_timeout = 0;
    pdev->conf.max_tx_aggregation_subframes = IEEE80211_AMPDU_MAX_BUF_HT;

    pdev->ops = ops;

    /* interfaces */
    net80211_interfaces_init(pdev);

    /* scan */
    net80211_scan_init(pdev);

    /* chanctx */
    net80211_chanctx_init(pdev);

    /* stations */
	net80211_stations_init(pdev);
	
    return pdev;
}

void
net80211_pdev_free(struct net80211_pdev *pdev)
{
    net80211_stations_remove(pdev);

    kfree(pdev);
}

int
net80211_pdev_register(struct net80211_pdev *pdev)
{
    if (pdev->conf.max_listen_interval == 0)
        pdev->conf.max_listen_interval = 5;

    net80211_regulatory_register(pdev);
    net80211_notify_dev_registered(pdev);

    return 0;
}

void
net80211_pdev_unregister(struct net80211_pdev *pdev)
{
    net80211_chanctx_remove(pdev);
    net80211_scan_remove(pdev);
    net80211_interfaces_remove(pdev);

    net80211_regulatory_deregister(pdev);
    net80211_notify_dev_unregistered(pdev);
}

/* helpers */
void net80211_queue_work(struct net80211_pdev *pdev, struct work_struct *work)
{
    schedule_work(work);
}

u32
net80211_get_band_supp_rates(struct net80211_pdev *pdev,
    enum nl80211_band band)
{
    const static u32 mandatories[] = {
        [NL80211_BAND_2GHZ] = (IEEE80211_RATE_MANDATORY_B | IEEE80211_RATE_MANDATORY_G),
        [NL80211_BAND_5GHZ] = IEEE80211_RATE_MANDATORY_A,
        /* TODO6G: */
    };

    const struct ieee80211_supported_band *sband;
    u32 supp_rates = 0;
    u32 mandatory;
    u32 i;

    sband = net80211_get_sband(pdev, band);
    if (!sband)
        return 0;

    mandatory = (band < ARRAY_LENGTH(mandatories)) ? mandatories[band] : 0;

    for (i = 0; i < sband->n_bitrates; i++) {
        struct ieee80211_rate *rate = &sband->bitrates[i];
        if (!(rate->flags & mandatory))
            continue;
        supp_rates |= BIT(i);
    }

    return supp_rates;
}


