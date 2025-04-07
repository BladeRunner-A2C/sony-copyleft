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

#ifndef __NET_NETDEVICE_H
#define __NET_NETDEVICE_H

#include <qdf/qbase.h>
#include <qdf/sk_buff.h>
#include <net/ether.h>

#define NETDEV_TPUT_CALCULATE_INTERVAL  1000 * 1000 /* us */

struct net_device;

 /* netdevice.h */
enum netdev_tx {
    NETDEV_TX_OK = 0x00,	/* driver took care of packet */
    NETDEV_TX_BUSY = 0x10,	/* driver tx path was busy*/
};

typedef enum netdev_tx netdev_tx_t;

struct net_bytes_record
{
    u64 timestamp;
    u64 bytes;
};

struct net_bytes_history {
    u32 next;
    struct net_bytes_record records[2];
};

struct net_device_stats
{
    u64 rx_bytes;
    u64 tx_bytes;

    struct net_bytes_history tx_bytes_history;
    struct net_bytes_history rx_bytes_history;
};

struct net_device
{
    void *net80211_ptr;

    /* Interface address */
    unsigned char perm_addr[ETH_ALEN];

    void(*priv_destructor)(struct net_device *dev);

    /* tx */
    struct sk_buff_head txq;
	struct sk_buff_head txq_recycle;

    /* rx */
    struct sk_buff_head rxq;

    struct net_device_stats stats;
};

/* helpers */
void netdev_setup(struct net_device *dev);
void netdev_teardown(struct net_device *dev);

u64 net_bytes_history_get_tput(struct net_bytes_history *history);

/* tput */
static inline u64 netdev_get_tx_tput(struct net_device *dev)
{
    return net_bytes_history_get_tput(&dev->stats.tx_bytes_history);
}

static inline u64 netdev_get_rx_tput(struct net_device *dev)
{
    return net_bytes_history_get_tput(&dev->stats.rx_bytes_history);
}

#endif //!__NET_NETDEVICE_H

