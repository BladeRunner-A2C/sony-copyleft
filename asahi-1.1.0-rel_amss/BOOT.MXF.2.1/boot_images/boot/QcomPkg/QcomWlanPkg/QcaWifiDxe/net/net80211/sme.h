/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 22/9/21   zxue     support beacon filter
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __NET_NET80211_SME_H
#define __NET_NET80211_SME_H

#include <net/net80211.h>
#include <net/net80211/mlme.h>
#include "net80211_i.h"

 /*****************************/
/* public */

void
net80211_sta_sme_init(struct net80211_vif *vif);

void
net80211_sta_sme_exit(struct net80211_vif *vif);

int
net80211_sta_sme_connect(struct net80211_vif *vif,
    struct net80211_connect_params *connect);

int
net80211_sta_sme_disconnect(struct net80211_vif *vif);

void
net80211_sta_sme_stop(struct net80211_vif *vif);

/* mlme */
void
net80211_sta_sme_rx_assoc_resp(struct net80211_vif *vif,
    u16 status_code, bool abort);

void
net80211_sta_sme_rx_mgmt(struct net80211_vif *vif,
    const u8 *buf, u32 len);

void
net80211_sta_sme_tx_mgmt(struct net80211_vif *vif,
    const u8 *buf, u32 len);

/*****************************/
/* internal only */
void
net80211_sta_sme_connect_done(struct net80211_vif *vif,
    struct net80211_connect_result *result);

void
net80211_sta_sme_send_disconnected(struct net80211_vif *vif,
    struct net80211_disconnect_result *result);

void
net80211_sta_sme_external_auth_request(struct net80211_vif* vif,
    struct net80211_auth_request_query* query);

void
net80211_sta_sme_external_auth_response(struct net80211_vif* vif,
    struct net80211_auth_response_query* query);

/* beacon filter */
void
net80211_sta_bcn_filter_init(struct net80211_vif *vif);
int
net80211_sta_recalc_bcn_filter(struct net80211_vif *vif);

#endif // !__NET_NET80211_SME_H



