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

#ifndef __NET_NET80211_REG_H
#define __NET_NET80211_REG_H

#include <net/mac80211.h>

void net80211_regulatory_register(struct net80211_pdev *pdev);
void net80211_regulatory_deregister(struct net80211_pdev *pdev);

#endif /* !__NET_NET80211_REG_H */