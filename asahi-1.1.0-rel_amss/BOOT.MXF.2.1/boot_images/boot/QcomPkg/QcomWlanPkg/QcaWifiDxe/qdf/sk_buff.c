/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 21/12/21  zxue     Add a mechanism to check the memory issue 
 19/10/21  zxue     refine code
 1/9/21    zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <Library/MemoryAllocationLib.h>
#include <qdf/pr_debug.h>
#include "sk_buff.h"
#include "pci.h"

/* pci dev */
extern EFI_QCWLAN_DEVICE_CONTEXT gWlanDriverContext;

static inline pci_dev_handle __pci_get_dev_handle()
{
    return (void *)&gWlanDriverContext.PciDev;
}

#define SKB_STRUCT_SIZE (sizeof(struct sk_buff))

#if SUPPORT_SKB_DEBUG
struct sk_buff *__alloc_skb(u32 size, 
    u32 meta_size, void(*free_meta)(struct sk_buff *), 
    void *pci_dev, void *pool, 
    const char* func, unsigned long line)
#else
struct sk_buff *__alloc_skb(u32 size, 
    u32 meta_size, void(*free_meta)(struct sk_buff *), 
    void *pci_dev, void *pool)
#endif
{
    struct sk_buff *skb;
    u8 *data, *meta;
    u32 alloc_size;
    
    alloc_size = SKB_STRUCT_SIZE + meta_size + size;

    /* allocate struct sk_buff and data buffer */
    if (pci_dev)
        skb = (struct sk_buff *)pci_mem_alloc(pci_dev, alloc_size);
    else
        skb = (struct sk_buff *)AllocateZeroPool(alloc_size);
    if (!skb)
        return NULL;
    
    /* assign the meta data */
    meta = meta_size ? ((u8 *)skb + SKB_STRUCT_SIZE) : NULL;
    /* assign data buffer */
    data = (u8 *)skb + SKB_STRUCT_SIZE + meta_size;
    /* initalize the fields */
    skb->head = data;
    skb->data = data;
    skb_reset_tail_pointer(skb);
    skb->end = size;
	skb->pci_dev = pci_dev;
    skb->meta = meta;
    skb->free_meta = free_meta;
    skb->pool = pool;

#if SUPPORT_SKB_DEBUG
    pr_raw_dbg("%a(%d): allocated skb 0x%p(%d)(pci_dev 0x%p, pool 0x%p)\n", 
        func, line, skb, size, pci_dev, pool);
#endif

    return skb;
}

#if SUPPORT_SKB_DEBUG
void __kfree_skb(struct sk_buff *skb, const char* func, unsigned long line)
#else
void __kfree_skb(struct sk_buff *skb)
#endif
{
    void *pci_dev = skb->pci_dev;
    void *pool = skb->pool;

    if (pool) {
        sk_buff_pool_free_skb(pool, skb);

#if SUPPORT_SKB_DEBUG
        pr_raw_dbg("%a(%d): queued skb 0x%p to pool 0x%p\n",
            func, line, skb, pool);
#endif
        return;
    }

    /* free meta */
    if (skb->free_meta)
        skb->free_meta(skb);

    if (pci_dev) {
        pci_mem_free(pci_dev, (u32)(skb->head - (u8*)skb) + skb->end, skb);
    }
    else {
        FreePool(skb);
    }

#if SUPPORT_SKB_DEBUG
    pr_raw_dbg("%a(%d): freed skb 0x%p (pci_dev 0x%p, pool 0x%p)\n", 
        func, line, skb, pci_dev, pool);
#endif
}

#if SUPPORT_SKB_DEBUG
struct sk_buff *__skb_clone(struct sk_buff *skb, const char* func, unsigned long line)
#else
struct sk_buff *__skb_clone(struct sk_buff *skb)
#endif
{
    struct sk_buff *cloned;

#if SUPPORT_SKB_DEBUG
    if (skb->pool)
        cloned = __sk_buff_pool_alloc_skb(skb->pool, 0, func, line);
    else
        cloned = __alloc_skb(skb->end, 0, NULL, skb->pci_dev, NULL, func, line);
#else
    if (skb->pool)
        cloned = __sk_buff_pool_alloc_skb(skb->pool, 0);
    else
        cloned = __alloc_skb(skb->end, 0, NULL, skb->pci_dev, NULL);
#endif

    if (cloned == NULL)
		return NULL;
    /* copy data */
    CopyMem(cloned->head, skb->head, skb->end);

    /* copy skb fields */
    CopyMem(cloned->cb, skb->cb, sizeof(skb->cb));
    cloned->data = cloned->head + skb_headroom(skb);
    cloned->len = skb->len;
    cloned->tail = skb->tail;
    cloned->sk = skb->sk;

#if SUPPORT_SKB_DEBUG
    pr_raw_dbg("%a(%d): cloned skb 0x%p\n", func, line, skb);
#endif

    return cloned;
}

#if SUPPORT_SKB_DEBUG
void *__skb_put(struct sk_buff *skb, u32 len, const char* func, unsigned long line)
#else
void *__skb_put(struct sk_buff *skb, u32 len)
#endif
{
    void *tmp = skb_tail_pointer(skb);

    if (skb->tail + len > skb->end) {
#if SUPPORT_SKB_DEBUG
		pr_raw_err("%a(%d): skb put fail skb->tail = %d len = %d skb->end = %d\n", 
			func, line, skb->tail, len, skb->end);
#endif
        return NULL;
    }

    skb->tail += len;
    skb->len += len;
    return tmp;
}

/* reallocate header of sk_buff */
int pskb_expand_head(struct sk_buff *skb, int nhead, int ntail,
		     gfp_t gfp_mask)
{
	return -ENOMEM;
}

/*****************************/
/* helpers */
static void __sk_buff_pool_free_skb_meta(struct sk_buff *skb)
{
    struct sk_buff_data_inits *init = skb->meta;
    if (!init)
        return;

    dma_unmap_single(skb->pci_dev, init->paddr,
        init->paddr_mapping_addr,
        (u32)(skb->head - (u8*)skb) + skb->end,
        DMA_BIDIRECTIONAL);
}

#if SUPPORT_SKB_DEBUG
void __sk_buff_pool_init(struct sk_buff_pool *pool, u32 capacity, u32 skb_size, void *dev,
    const char* func, unsigned long line)
#else
void __sk_buff_pool_init(struct sk_buff_pool *pool, u32 capacity, u32 skb_size, void *dev)
#endif
{
    pool->dev = dev;
    pool->capacity = capacity;
    pool->count = 0;
    pool->skb_size = skb_size;

    skb_queue_head_init(&pool->free_list);

#if SUPPORT_SKB_DEBUG
    pr_raw_dbg("%a(%d): init sk_buff_pool 0x%p: capacity %d, skb_size %d\n",
        func, line, pool, pool->capacity, pool->skb_size);
#endif
}

#if SUPPORT_SKB_DEBUG
struct sk_buff *__sk_buff_pool_alloc_skb(struct sk_buff_pool *pool, u32 align,
    const char* func, unsigned long line)
#else
struct sk_buff *__sk_buff_pool_alloc_skb(struct sk_buff_pool *pool, u32 align)
#endif
{
    struct sk_buff *skb;
    struct sk_buff_pool *target_pool;
    struct sk_buff_data_inits *inits;
    dma_addr_t paddr;
    void *paddr_mapping_addr;
    int ret;

    /* allocate from pool free_list */
    if (!skb_queue_empty(&pool->free_list)) {
        skb = skb_dequeue(&pool->free_list);
		if (skb == NULL)
			return NULL;

#if SUPPORT_SKB_DEBUG
        pr_raw_dbg("%a(%d): dequeued skb 0x%p(%d) from pool 0x%p\n", 
            func, line, skb, skb->end, pool);
#endif
        return skb;
    }

    /* allocate new skb */
    target_pool = (pool->count < pool->capacity) ? pool : NULL;

#if SUPPORT_SKB_DEBUG
    skb = __alloc_skb(pool->skb_size, 
        sizeof(*inits), __sk_buff_pool_free_skb_meta, 
        pool->dev, target_pool, func, line);
#else
    skb = __alloc_skb(pool->skb_size, 
        sizeof(*inits), __sk_buff_pool_free_skb_meta,
        pool->dev, target_pool);
#endif

    if (skb == NULL)
		return NULL;

    /* NOTE: 
     * Only single buffer is allocated for skb include structure and data
     * Bidirectional DMA map requires mapping on the full memory. 
     */
    ret = dma_map_single(pool->dev, skb,
        (u32)(skb->head - (u8*)skb) + skb->end,
        DMA_BIDIRECTIONAL, &paddr, &paddr_mapping_addr);
    if (ret)
        goto err_free;

    /* alignment */
    if (!IS_ALIGNED((u64)skb->data, align)) {
        skb_reserve(skb,
            (u32)(PTR_ALIGN(skb->data, align) - skb->data));
    }

    /* update the inits data */
    inits = skb->meta;
    inits->offset = (u32)(skb->data - skb->head);
    inits->paddr = paddr;
    inits->paddr_mapping_addr = paddr_mapping_addr;

    if (skb && (target_pool == pool)) {
        pool->count++;
    }

err_free:
    if (ret) {
        skb->pool = NULL;
#if SUPPORT_SKB_DEBUG
        __kfree_skb(skb, func, line);
#else
        __kfree_skb(skb);
#endif
        skb = NULL;
    }

    return skb;
}

#if SUPPORT_SKB_DEBUG
void __sk_buff_pool_free_skb(struct sk_buff_pool *pool, struct sk_buff *skb,
    const char* func, unsigned long line)
#else
void __sk_buff_pool_free_skb(struct sk_buff_pool *pool, struct sk_buff *skb)
#endif
{
    struct sk_buff_data_inits *inits = skb->meta;

    /* reset the variables */
    skb->data = skb->head + inits->offset;
    skb->len = 0;
    skb_reset_tail_pointer(skb);

    skb->sk = NULL;
    skb->dev = NULL;
    skb->ip_summed = 0;

    ZeroMem(skb->data, skb->len + skb_tailroom(skb));
    ZeroMem(skb->cb, sizeof(skb->cb));

    /* reset inits meta */
    inits->meta = NULL;
    skb->pre_alloc = 0;

    skb_queue_tail(&pool->free_list, skb);
}

#if SUPPORT_SKB_DEBUG
void __sk_buff_pool_purge(struct sk_buff_pool *pool, const char* func, unsigned long line)
#else
void __sk_buff_pool_purge(struct sk_buff_pool *pool)
#endif
{
    struct sk_buff *skb;

    pool->count -= skb_queue_len(&pool->free_list);

    while ((skb = __skb_dequeue(&pool->free_list)) != NULL) {
        skb->pool = NULL;
        kfree_skb(skb);
    }

    WARN_ON(pool->count != 0);
}
