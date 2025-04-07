/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 21/12/21  zxue     Add a mechanism to check the memory issue 
 19/8/21   zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_SK_BUFF_H
#define __QDF_SK_BUFF_H

#include <qdf/compile_type.h>
#include <qdf/base_type.h>
#include <qdf/errno.h>
#include <qdf/stdio.h>

#if SUPPORT_DEBUG_PRINT
#define SUPPORT_SKB_DEBUG 1
#define skb_debug pr_debug
#else
#define skb_debug(...) sizeof(UINT8)
#endif

struct sock;

/* ip checksum */
enum {
    CHECKSUM_NONE = 0,
    CHECKSUM_UNNECESSARY = 1,
    CHECKSUM_COMPLETE = 2,
    CHECKSUM_PARTIAL = 3,
};

/* socket buffer */
struct sk_buff
{
    struct sk_buff *next;
    struct sk_buff *prev;

    struct sock *sk;
    struct net_device *dev;

    /* memory management */
    void *pci_dev;
    void *pool;

    u8 cb[80]; /* Used for private variables */

    u32 len;

    u8 *head;  /* pointer to buffer head */
    u8 *data;  /* pointer to data head */

    u32 tail;  /* data end position */
    u32 end;   /* buffer end postion */

    u32 priority;      /* TODOTODO: review the usage */
    u16 queue_mapping;

    u8 pre_alloc : 1, /* reference to data but not own the data */
       ip_summed : 2;  /* TODOTODO: Add the support for ipsumed? */

    /* extention */
    void(*free_meta)(struct sk_buff *skb);
    void *meta;
};

#if SUPPORT_SKB_DEBUG

struct sk_buff *__alloc_skb(u32 size, 
    u32 meta_size, void(*free_meta)(struct sk_buff *),
    void *pci_dev, void *pool, 
    const char* func, unsigned long line);
struct sk_buff *__skb_clone(struct sk_buff *skb, const char* func, unsigned long line);
void __kfree_skb(struct sk_buff *skb, const char* func, unsigned long line);
void *__skb_put(struct sk_buff *skb, u32 len, const char* func, unsigned long line);

#define alloc_skb(_s) __alloc_skb(_s, 0, NULL, NULL, NULL, __FUNCTION__, __LINE__)
#define skb_clone(_skb) __skb_clone(_skb, __FUNCTION__, __LINE__)
#define dev_alloc_skb(_d, _s) __alloc_skb(_s, 0, NULL, _d, NULL, __FUNCTION__, __LINE__)
#define kfree_skb(_skb) __kfree_skb(_skb, __FUNCTION__, __LINE__)
#define consume_skb(_skb) __kfree_skb(_skb, __FUNCTION__, __LINE__)
#define skb_put(_skb, _len) __skb_put(_skb, _len, __FUNCTION__, __LINE__) 

#else // !SUPPORT_SKB_DEBUG

struct sk_buff *__alloc_skb(u32 size, 
    u32 meta_size, void(*free_meta)(struct sk_buff *), 
    void *pci_dev, void *pool);
struct sk_buff *__skb_clone(struct sk_buff *skb);
void __kfree_skb(struct sk_buff *skb);
void *__skb_put(struct sk_buff *skb, u32 len);

static inline struct sk_buff *alloc_skb(u32 size)
{
    return __alloc_skb(size, 0, NULL, NULL, NULL);
}

static inline void kfree_skb(struct sk_buff *skb)
{
    __kfree_skb(skb);
}

static inline void consume_skb(struct sk_buff *skb)
{
    /* need reference count support or not? */
    __kfree_skb(skb);
}

static inline struct sk_buff *skb_clone(struct sk_buff *skb)
{
    return __skb_clone(skb);
}

static inline struct sk_buff *dev_alloc_skb(void *dev, u32 size)
{
    return __alloc_skb(size, 0, NULL, dev, NULL);
}

static inline void *skb_put(struct sk_buff *skb, u32 len)
{
    return __skb_put(skb, len);
}

#endif // SUPPORT_SKB_DEBUG

/* bytes of free space at the head. */
static inline u32 skb_headroom(const struct sk_buff *skb)
{
    return (u32)(skb->data - skb->head);
}

/* bytes at buffer end */
static inline u32 skb_tailroom(const struct sk_buff *skb)
{
    return (skb->end - skb->tail);
}

/* adjust headroom */
static inline void skb_reserve(struct sk_buff *skb, u32 len)
{
    skb->data += len;
    skb->tail += len;
}

static inline u8 *skb_tail_pointer(const struct sk_buff *skb)
{
    return skb->head + skb->tail;
}

static inline void skb_reset_tail_pointer(struct sk_buff *skb)
{
    skb->tail = (u32)(skb->data - skb->head);
}

static inline void skb_set_tail_pointer(struct sk_buff *skb, u32 offset)
{
    skb_reset_tail_pointer(skb);
    skb->tail += offset;
}

static inline unsigned int skb_end_offset(const struct sk_buff *skb)
{
    return skb->end;
}

static inline unsigned char *skb_end_pointer(const struct sk_buff *skb)
{
    return skb->head + skb->end;
}

static inline void *skb_push(struct sk_buff *skb, u32 len)
{
    skb->data -= len;
    skb->len += len;
    return skb->data;
}

static inline void *__skb_pull(struct sk_buff *skb, u32 len)
{
    skb->len -= len;
    return skb->data += len;
}

static inline void *skb_pull(struct sk_buff *skb, u32 len)
{
    return (len > skb->len) ? NULL : __skb_pull(skb, len);
}

static inline void *skb_put_data(struct sk_buff *skb, const void *data,
    u32 len)
{
    void *tmp = skb_put(skb, len);

	if (tmp == NULL)
		return NULL;
	
    memcpy(tmp, data, len);

    return tmp;
}

static inline int __skb_pad_or_free(struct sk_buff *skb, u32 pad)
{
    if (skb_tailroom(skb) >= pad) {
        memset(skb->data + skb->len, 0, pad);
        return 0;
    }

    /* free when fail to pad */
    kfree_skb(skb);
    return -ENOSPC;
}

/* zero pad the tail of an skb */
static inline int skb_put_padto(struct sk_buff *skb, u32 len)
{
    u32 size = skb->len;

    if (unlikely(size < len)) {
        len -= size;
        if (__skb_pad_or_free(skb, len))
            return -ENOMEM;
        skb_put(skb, len);
    }
    return 0;
}

static inline void *skb_put_zero(struct sk_buff *skb, u32 len)
{
    void *tmp = skb_put(skb, len);
	if (tmp == NULL)
		return NULL;

    memset(tmp, 0, len);

    return tmp;
}

static inline int skb_copy_bits(const struct sk_buff *skb, u32 offset, void *to, u32 len)
{
    if (offset > skb->len - len)
        return -EFAULT;

    memcpy(to, skb->data + offset, len);
    return 0;
}

static inline void skb_copy_from_linear_data(const struct sk_buff *skb,
    void *to, u32 len)
{
    memcpy(to, skb->data, len);
}

static inline void __skb_set_length(struct sk_buff *skb, u32 len)
{
    skb->len = len;
    skb_set_tail_pointer(skb, len);
}

static inline void skb_trim(struct sk_buff *skb, u32 len)
{
    __skb_set_length(skb, len);
}

static inline int skb_copy_datagram_msg(const struct sk_buff *skb, u32 offset,
    void *msg_data, u32 msg_len)
{
    if (!msg_data)
        return -EINVAL;
    if (offset >= skb->len)
        return -EOVERFLOW;
    if (msg_len < (skb->len - offset))
        return -EMSGSIZE;

    memcpy(msg_data, skb->data + offset, skb->len - offset);

    return skb->len - offset;
}

static inline int skb_linearize(struct sk_buff *skb)
{
    return 0;
}

static inline void skb_set_queue_mapping(struct sk_buff *skb, u16 queue_mapping)
{
    skb->queue_mapping = queue_mapping;
}

static inline u16 skb_get_queue_mapping(const struct sk_buff *skb)
{
    return skb->queue_mapping;
}

/* not supported yet */
int pskb_expand_head(struct sk_buff *skb, int nhead, int ntail,
    gfp_t gfp_mask);

/* dev apis for skb */
#define dev_kfree_skb(skb) consume_skb(skb)
#define dev_kfree_skb_any(skb) do {   \
       if (skb)                       \
           kfree_skb(skb);            \
   } while (0)

/************************************/

struct sk_buff_head 
{
    struct sk_buff *next;
    struct sk_buff *prev;

    u32 qlen; /* the length of the queue */
};

static inline void __skb_queue_head_init(struct sk_buff_head *list)
{
    list->prev = list->next = (struct sk_buff *)list;
    list->qlen = 0;
}

static inline void skb_queue_head_init(struct sk_buff_head *list)
{
    __skb_queue_head_init(list);
}

static inline __u32 skb_queue_len(const struct sk_buff_head *list)
{
    return list->qlen;
}

static inline struct sk_buff *__skb_peek(const struct sk_buff_head *list)
{
    struct sk_buff *skb = list->next;

    /* list is empty */
    if (skb == (struct sk_buff *)list)
        skb = NULL;

    return skb;
}

static inline struct sk_buff *skb_peek(const struct sk_buff_head *list)
{
    return __skb_peek(list);
}

/* unlink the skb from a a list */
static inline void __skb_unlink(struct sk_buff *skb, struct sk_buff_head *list)
{
    struct sk_buff *next, *prev;

    list->qlen -= 1;
    next = skb->next;
    prev = skb->prev;

    skb->next = skb->prev = NULL;

    next->prev = prev;
    prev->next = next;
}

static inline void __skb_insert(struct sk_buff *newsk,
    struct sk_buff *prevsk, struct sk_buff *nextsk,
    struct sk_buff_head *list)
{
    newsk->next = nextsk;
    newsk->prev = prevsk;
    nextsk->prev = newsk;
    prevsk->next = newsk;

    list->qlen++;
}

static inline void __skb_queue_before(struct sk_buff_head *list,
    struct sk_buff *nextsk, struct sk_buff *newsk)
{
    /* insert at specified position */
    __skb_insert(newsk, nextsk->prev, nextsk, list);
}

static inline void __skb_queue_tail(struct sk_buff_head *list,
    struct sk_buff *newsk)
{
    /* queue at the end */
    __skb_queue_before(list, (struct sk_buff *)list, newsk);
}

static inline void skb_queue_tail(struct sk_buff_head *list,
    struct sk_buff *skb_new)
{
    /* queue at the end */
    __skb_queue_before(list, (struct sk_buff *)list, skb_new);
}

static inline struct sk_buff *__skb_dequeue(struct sk_buff_head *list)
{
    struct sk_buff *skb = skb_peek(list);
    if (skb)
        __skb_unlink(skb, list);
    return skb;
}

static inline struct sk_buff *skb_dequeue(struct sk_buff_head *list)
{
    return __skb_dequeue(list);
}

static inline void __skb_queue_purge(struct sk_buff_head *list)
{
    struct sk_buff *skb;
    while ((skb = __skb_dequeue(list)) != NULL)
        kfree_skb(skb);
}

static inline void skb_queue_purge(struct sk_buff_head *list)
{
    __skb_queue_purge(list);
}

static inline int skb_queue_empty(const struct sk_buff_head *list)
{
    return (list->next == (const struct sk_buff *)list);
}

static inline void __skb_queue_splice(const struct sk_buff_head *list,
				      struct sk_buff *prevsk,
				      struct sk_buff *nextsk)
{
	struct sk_buff *firstsk = list->next;
	struct sk_buff *lastsk = list->prev;

	firstsk->prev = prevsk;
	prevsk->next = firstsk;

	lastsk->next = nextsk;
	nextsk->prev = lastsk;
}

/* join two skb lists */
static inline void skb_queue_splice_tail(const struct sk_buff_head *list,
					 struct sk_buff_head *head)
{
	if (!skb_queue_empty(list)) {
		__skb_queue_splice(list, head->prev, (struct sk_buff *)head);
		head->qlen += list->qlen;
	}
}

/* walk the skb queue */
#define skb_queue_walk(_queue, _skb)                         \
		for ((_skb) = (_queue)->next;				         \
		     (_skb) != (struct sk_buff *)(_queue);	         \
		     (_skb) = (_skb)->next)

/* walk the skb queue safely */
#define skb_queue_walk_safe(_queue, _skb, _tmp)              \
		for ((_skb) = (_queue)->next, (_tmp) = (_skb)->next; \
		     (_skb) != (struct sk_buff *)(_queue);		     \
		     (_skb) = (_tmp), (_tmp) = (_skb)->next)

static inline struct sk_buff *skb_peek_tail(const struct sk_buff_head *list)
{
	struct sk_buff *skb = list->prev;

    /* the list is empty */
	if (skb == (struct sk_buff *)list)
		skb = NULL;
	return skb;
}


/************************************/
struct sk_buff_pool
{
    void *dev;
    u32 capacity;
    u32 count;

    struct sk_buff_head free_list;
    u32 skb_size;
};

struct sk_buff_data_inits
{
    u32 offset;
    dma_addr_t paddr;
    void *paddr_mapping_addr;

    void *meta;
};

static inline dma_addr_t skb_data_map_paddr(struct sk_buff *skb)
{
    struct sk_buff_data_inits *inits = skb->meta;
    if (!inits)
        return 0;
    return inits->paddr + (u32)(skb->data - (u8*)skb);
}


/* extension for tx support */
/* TODO: Find a better location */

static inline void *skb_get_data_meta(struct sk_buff *skb)
{
    struct sk_buff_data_inits *inits = skb->meta;
    if (!inits)
        return NULL;
    return inits->meta;
}

static inline int skb_set_data_meta(struct sk_buff *skb, void *meta)
{
    struct sk_buff_data_inits *inits = skb->meta;
    if (!inits)
        return -EINVAL;
    inits->meta = meta;
    skb->pre_alloc = meta ? 1 : 0;
    return 0;
}

#if SUPPORT_SKB_DEBUG

void __sk_buff_pool_init(struct sk_buff_pool *pool, u32 capacity, u32 skb_size, void *dev,
    const char* func, unsigned long line);
void __sk_buff_pool_purge(struct sk_buff_pool *pool, 
    const char* func, unsigned long line);
struct sk_buff *__sk_buff_pool_alloc_skb(struct sk_buff_pool *pool, u32 align,
    const char* func, unsigned long line);
void __sk_buff_pool_free_skb(struct sk_buff_pool *pool, struct sk_buff *skb,
    const char* func, unsigned long line);

#define sk_buff_pool_init(_p, _c, _s, _d) __sk_buff_pool_init(_p, _c, _s, _d, __FUNCTION__, __LINE__)
#define sk_buff_pool_alloc_skb(_p, _al) __sk_buff_pool_alloc_skb(_p, _al, __FUNCTION__, __LINE__)
#define sk_buff_pool_free_skb(_p, _skb) __sk_buff_pool_free_skb(_p, _skb, __FUNCTION__, __LINE__)
#define sk_buff_pool_purge(_p) __sk_buff_pool_purge(_p, __FUNCTION__, __LINE__)

#else // !SUPPORT_SKB_DEBUG

void __sk_buff_pool_init(struct sk_buff_pool *pool, u32 capacity, u32 skb_size, void *dev);
void __sk_buff_pool_purge(struct sk_buff_pool *pool);
struct sk_buff *__sk_buff_pool_alloc_skb(struct sk_buff_pool *pool, u32 align);
void __sk_buff_pool_free_skb(struct sk_buff_pool *pool, struct sk_buff *skb);

static inline void sk_buff_pool_init(struct sk_buff_pool *pool, u32 capacity, u32 skb_size, void *dev)
{
    __sk_buff_pool_init(pool, capacity, skb_size, dev);
}

static inline void sk_buff_pool_purge(struct sk_buff_pool *pool)
{
    __sk_buff_pool_purge(pool);
}

static inline struct sk_buff *sk_buff_pool_alloc_skb(struct sk_buff_pool *pool, u32 align)
{
    return __sk_buff_pool_alloc_skb(pool, align);
}

static inline void sk_buff_pool_free_skb(struct sk_buff_pool *pool, struct sk_buff *skb)
{
    __sk_buff_pool_free_skb(pool, skb);
}

#endif // !SUPPORT_SKB_DEBUG

#endif // !__QDF_SK_BUFF_H

