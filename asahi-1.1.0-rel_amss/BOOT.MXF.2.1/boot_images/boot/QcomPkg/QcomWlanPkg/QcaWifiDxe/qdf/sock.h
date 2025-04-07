/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 1/9/21    zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_SOCK_H
#define __QDF_SOCK_H

#include <qdf/base_type.h>
#include <qdf/sk_buff.h>

struct socket;
struct sock;

/******** sock ********/

struct sockaddr {
    u16	sa_family;
};

struct sock
{
    void(*sk_data_ready)(struct sock *sk);
    void(*sk_error_report)(struct sock *sk);

    u32 sk_err;
    u32 sk_flags;

    struct sk_buff_head	sk_receive_queue;

   //struct kref sk_refcnt;

    void *sk_user_data;

    void *sk_dev;
};

/* Sock flags */
enum sock_flags {
    SOCK_ZAPPED = 0x00000001
};

static inline void sock_set_flag(struct sock *sk, enum sock_flags flag)
{
    sk->sk_flags |= flag;
}

static inline void sock_reset_flag(struct sock *sk, enum sock_flags flag)
{
    sk->sk_flags &= ~flag;
}

static inline bool sock_flag(const struct sock *sk, enum sock_flags flag)
{
    return ((sk->sk_flags & (u32)flag) == (u32)flag);
}

static inline void lock_sock(struct sock *sk)
{
    // TODOTODO:
}

static inline void release_sock(struct sock *sk)
{
    // TODOTODO:
}

static inline void sock_put(struct sock *sk)
{
    // TODOTODO:
    //if (refcount_dec_and_test(&sk->sk_refcnt))
    //    sk_free(sk);
}

static inline void sock_hold(struct sock *sk)
{
    // TODOTODO:
    //refcount_inc(&sk->sk_refcnt);
}


static inline struct sk_buff *sock_alloc_send_skb(struct sock *sk, u32 size)
{
    struct sk_buff *skb = dev_alloc_skb(sk->sk_dev, size);
	if (skb)
    	skb->sk = sk;
    return skb;
}

static inline void skb_set_owner_w(struct sk_buff *skb, struct sock *sk)
{
    skb->sk = sk;
}

struct sk_buff *__skb_recv_datagram(struct sock *sk,
    struct sk_buff_head *sk_queue, int *err);

static inline void skb_free_datagram(struct sock *sk, struct sk_buff *skb)
{
    consume_skb(skb);
}

static inline struct sk_buff *skb_recv_datagram(struct sock *sk, int *err)
{
    return __skb_recv_datagram(sk, &sk->sk_receive_queue, err);
}

int sock_queue_rcv_skb(struct sock *sk, struct sk_buff *skb);


/******** socket ********/
struct socket {
    struct sock *sk;
    //const struct proto_ops *ops;
};

static inline void sock_init_data(struct socket *sock, struct sock *sk)
{
    sock->sk = sk;
}

#endif // !__QDF_SOCK_H

