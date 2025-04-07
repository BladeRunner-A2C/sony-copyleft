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

#include <qdf/pr_debug.h>
#include <qdf/compile_type.h>
#include "sock.h"

struct sk_buff *__skb_recv_datagram(struct sock *sk,
    struct sk_buff_head *sk_queue, int *err)
{
    struct sk_buff *skb = sk_queue->next;
    u32 old_qlen = sk_queue->qlen;

    DEBUG_PARAMETER(old_qlen);

    if (skb == (struct sk_buff *)sk_queue) {
        *err = -EAGAIN;
        return NULL;
    }

    *err = 0;
    __skb_unlink(skb, sk_queue);

    pr_debug("sock 0x%p: qlen %u -> %u\n", sk, old_qlen, sk_queue->qlen);
    return skb;
}

int sock_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
    u32 old_qlen = sk->sk_receive_queue.qlen;

    DEBUG_PARAMETER(old_qlen);

    __skb_queue_tail(&sk->sk_receive_queue, skb);

    pr_debug("sock 0x%p: qlen %u -> %u\n", 
        sk, old_qlen, sk->sk_receive_queue.qlen);

    sk->sk_data_ready(sk);

    return 0;
}