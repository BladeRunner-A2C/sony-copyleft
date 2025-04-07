/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 6/9/21    zxue     fix parasoft issue
 1/9/21    zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/compile_type.h>
#include <qdf/errno.h>
#include <qdf/alloc.h>
#include "radix_list.h"

/******************************/
/* struc radix_block */

struct radix_block *alloc_radix_block(void)
{
    struct radix_block *rdb;

    /* allocate struct radix_block */
    rdb = kzalloc(sizeof(*rdb) +
        RADIX_BLOCK_SIZE * sizeof(void *), GFP_KERNEL);
    return rdb;
}

void free_radix_block(struct radix_block *rdb)
{
    kfree(rdb);
}

/******************************/
/* struct radix_block_head */

static inline struct radix_block *__radix_block_peek(const struct radix_block_head *list)
{
    struct radix_block *rdb = list->next;

    if (rdb == (struct radix_block *)list)
        rdb = NULL;
    return rdb;
}

static inline void __radix_block_unlink(struct radix_block *rdb, struct radix_block_head *list)
{
    struct radix_block *next, *prev;

    list->qlen -= 1;
    next = rdb->next;
    prev = rdb->prev;

    rdb->next = rdb->prev = NULL;

    next->prev = prev;
    prev->next = next;
}

static inline void __radix_block_insert(struct radix_block *newrb,
    struct radix_block *prev, struct radix_block *next,
    struct radix_block_head *list)
{
    newrb->next = next;
    newrb->prev = prev;
    next->prev = newrb;
    prev->next = newrb;

    list->qlen++;
}

static inline void __radix_block_queue_before(struct radix_block_head *list,
    struct radix_block *next, struct radix_block *newrb)
{
    __radix_block_insert(newrb, next->prev, next, list);
}

static inline void __radix_block_queue_tail(struct radix_block_head *list,
    struct radix_block *newrb)
{
    __radix_block_queue_before(list, (struct radix_block *)list, newrb);
}

static inline struct radix_block *__radix_block_dequeue(struct radix_block_head *list)
{
    struct radix_block *rdb = __radix_block_peek(list);
    if (rdb)
        __radix_block_unlink(rdb, list);
    return rdb;
}

static inline void __radix_block_queue_purge(struct radix_block_head *list)
{
    struct radix_block *rdb;
    while ((rdb = __radix_block_dequeue(list)) != NULL)
        free_radix_block(rdb);
}

static inline int radix_block_queue_empty(const struct radix_block_head *list)
{
    return list->next == (const struct radix_block *)list;
}

#define radix_block_queue_walk(_queue, _rdb)                 \
		for ((_rdb) = (_queue)->next;					     \
		     (_rdb) != (struct radix_block *)(_queue);		 \
		     (_rdb) = (_rdb)->next)

#define radix_block_queue_walk_safe(_queue, _rdb, _tmp)      \
		for ((_rdb) = (_queue)->next, (_tmp) = (_rdb)->next; \
		     (_rdb) != (struct radix_block *)(_queue);		 \
		     (_rdb) = (_tmp), (_tmp) = (_rdb)->next)


/******************************/
/* radix_list */
static struct radix_block *
__radix_list_find_block(struct radix_list *list, u64 id)
{
    struct radix_block *rdb;
    radix_block_queue_walk(&list->blocks, rdb) {
        if (rdb->start > id)
            break;
        if (rdb->end > id)
            return rdb;
    }

    return NULL;
}

static struct radix_block *
__radix_list_get_block(struct radix_list *list, u64 id)
{
    struct radix_block *rdb, *rdb_new;
    radix_block_queue_walk(&list->blocks, rdb) {
        if (rdb->start > id)
            break;
        if (rdb->end > id)
            return rdb;
    }

    /* alloc new block */
    rdb_new = alloc_radix_block();
	if (rdb_new == NULL)
		return NULL;

    rdb_new->start = (id / RADIX_BLOCK_SIZE) * RADIX_BLOCK_SIZE;
    rdb_new->end = rdb_new->start + RADIX_BLOCK_SIZE;

    /* tail */
    if (rdb == (struct radix_block *)&list->blocks) {
        __radix_block_queue_tail(&list->blocks, rdb_new);
    }
    else {
        __radix_block_queue_before(&list->blocks, rdb, rdb_new);
    }

    return rdb_new;
}

static struct radix_block *
__radix_list_get_free_block(struct radix_list *list, u64 *nextid, u64 max)
{
    struct radix_block *rdb, *rdb_new;
    u64 id = *nextid;

    radix_block_queue_walk(&list->blocks, rdb) {
        if (rdb->start > id)
            break;
        if (rdb->end > id) {
            /* block is full */
            if (rdb->valid == (rdb->end - rdb->start)) {
                id = rdb->end;
                if (id >= max)
                    return NULL;
                continue;
            }
            else {
                while (rdb->values[id - rdb->start]) {
                    id++;
                    if (id >= max)
                        return NULL;
                }

                *nextid = id;
                return rdb;
            }
        }
    }

    /* alloc new block */
    rdb_new = alloc_radix_block();
	if (rdb_new == NULL)
		return NULL;

    rdb_new->start = (id / RADIX_BLOCK_SIZE) * RADIX_BLOCK_SIZE;
    rdb_new->end = rdb_new->start + RADIX_BLOCK_SIZE;

    /* tail */
    if (rdb == (struct radix_block *)&list->blocks) {
        __radix_block_queue_tail(&list->blocks, rdb_new);
    }
    else {
        __radix_block_queue_before(&list->blocks, rdb, rdb_new);
    }

    *nextid = id;

    return rdb_new;
}

void *radix_list_lookup(struct radix_list *list, u64 id)
{
    struct radix_block *rdb = __radix_list_find_block(list, id);
    if (!rdb)
        return NULL;
    return rdb->values[id - rdb->start];
}

s64 radix_list_insert(struct radix_list *list, u64 id, void *ptr)
{
    struct radix_block *rdb;

    if (!ptr)
        return -EINVAL;

    rdb = __radix_list_get_block(list, id);
    if (rdb == NULL)
        return -EINVAL;

    if (rdb->values[id - rdb->start])
        return -EINVAL;
    
    rdb->values[id - rdb->start] = ptr;
    rdb->valid++;

    return id;
}

s64 radix_list_alloc(struct radix_list *list, void *ptr, u64 id, u64 max)
{
    struct radix_block *rdb;

    if (!ptr)
        return -EINVAL;

    rdb = __radix_list_get_free_block(list, &id, max);
    if (rdb == NULL)
        return -EINVAL;

    rdb->values[id - rdb->start] = ptr;
    rdb->valid++;

    return id;
}

void *radix_list_delete(struct radix_list *list, u64 id)
{
    struct radix_block *rdb;
    void *ptr;

    rdb = __radix_list_find_block(list, id);
    if (!rdb)
        return NULL;

    ptr = rdb->values[id - rdb->start];
    if (ptr) {
        rdb->values[id - rdb->start] = NULL;
        rdb->valid--;
    }

    if (!rdb->valid) {
        __radix_block_unlink(rdb, &list->blocks);
        free_radix_block(rdb);
    }

    return ptr;
}

void radix_list_destory(struct radix_list *list)
{
    __radix_block_queue_purge(&list->blocks);
}

void *radix_list_get_next(struct radix_list_iter *iter, u64 *nextid)
{
    struct radix_block *rdb = iter->block;
    u64 id = iter->id;
    void *ptr;

    /* reenumarate when radix list changed */
    if (!rdb || iter->qlen != iter->block_queue->qlen) {
        radix_block_queue_walk(iter->block_queue, rdb) {
            if (rdb->start > id)
                break;

            if (rdb->end > id)
                break;
        }
    }

    do {
        if (rdb == (struct radix_block *)iter->block_queue)
            break;

        if (rdb->start > id)
            id = rdb->start;

        for (; id < rdb->end; id++) {
            ptr = rdb->values[id - rdb->start];
            if (!ptr)
                continue;

            *nextid = id;
            iter->block = rdb;
            iter->qlen = iter->block_queue->qlen;
            iter->id = id;
            return ptr;
        }

        rdb = rdb->next;
    } while (1);

    iter->block = rdb;
    iter->qlen = iter->block_queue->qlen;
    return NULL;
}