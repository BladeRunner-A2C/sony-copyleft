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

#include <net/netdevice.h>
#include <net/ndebug.h>

void netdev_setup(struct net_device *dev)
{
    skb_queue_head_init(&dev->txq);
    skb_queue_head_init(&dev->txq_recycle);
    skb_queue_head_init(&dev->rxq);

    net_dbg("txq 0x%p, txq_recycle 0x%p, rxq 0x%p\n",
        &dev->txq, &dev->txq_recycle, &dev->rxq);
}

void netdev_teardown(struct net_device *dev)
{
    struct sk_buff *skb;

    net_dbg("txq 0x%p(len %d), txq_recycle 0x%p(len %d), rxq 0x%p(len %d)\n",
        &dev->txq, skb_queue_len(&dev->txq), 
        &dev->txq_recycle, skb_queue_len(&dev->txq_recycle), 
        &dev->rxq, skb_queue_len(&dev->rxq));

    /* recycle the tx */
    while ((skb = __skb_dequeue(&dev->txq)) != NULL) {
        skb_queue_tail(&dev->txq_recycle, skb);
    }

    /* free pending txq_recycle */
    skb_queue_purge(&dev->txq_recycle);
    /* free pending rx */
    skb_queue_purge(&dev->rxq);
}

u64 net_bytes_history_get_tput(struct net_bytes_history *history)
{
    u64 tput = 0;
    u64 now = getwalltime_us();
    struct net_bytes_record *record0 =
        &history->records[history->next & 0x1];
    struct net_bytes_record *record1 =
        &history->records[(history->next + 1) & 0x1];

    if (now - record1->timestamp <= NETDEV_TPUT_CALCULATE_INTERVAL) {
        if ((record1->timestamp - record0->timestamp) <=
            (NETDEV_TPUT_CALCULATE_INTERVAL + NETDEV_TPUT_CALCULATE_INTERVAL))
            tput = (record1->bytes - record0->bytes) / ((record1->timestamp - record0->timestamp) / 1000) * 1000;
    }

    return tput;
}
