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

#ifndef __QDF_RADIX_LIST_H
#define __QDF_RADIX_LIST_H

#include <qdf/base_type.h>

/******************************/
#define RADIX_BLOCK_SIZE 64

struct radix_block
{
    struct radix_block *next;
    struct radix_block *prev;

    u64 start;
    u64 end;
    u32 valid;
    void *values[0];
};

/******************************/
struct radix_block_head
{
    struct radix_block *next;
    struct radix_block *prev;
    u32 qlen;
};

static inline void __radix_block_head_init(struct radix_block_head *list)
{
    list->prev = list->next = (struct radix_block *)list;
    list->qlen = 0;
}

/******************************/
struct radix_list
{
    struct radix_block_head blocks;
};

struct radix_list_iter
{
    const struct radix_block_head *block_queue;
    struct radix_block *block;
    u32 qlen;
    u64 id;
};

static inline void radix_list_init(struct radix_list *list)
{
    __radix_block_head_init(&list->blocks);
}

s64 radix_list_alloc(struct radix_list *list, void *ptr, u64 id, u64 max);
void *radix_list_lookup(struct radix_list *list, u64 id);
s64 radix_list_insert(struct radix_list *list, u64 id, void *ptr);
void *radix_list_delete(struct radix_list *list, u64 id);
void radix_list_destory(struct radix_list *list);

static inline u64 radix_list_iterator_init(
    struct radix_list_iter *iter,
    const struct radix_list *list)
{
    iter->block_queue = &list->blocks;
    iter->block = iter->block_queue->next;
    iter->qlen = iter->block_queue->qlen;
    iter->id = 0;

    return 0;
}

static inline u64 radix_list_iterator_move(
    struct radix_list_iter *iter)
{
    iter->id++;
    return iter->id;
}

void *radix_list_get_next(struct radix_list_iter *iter, u64 *nextid);

#define radix_list_for_each_entry(_list, _iter, _id, _entry)         \
	for ((_id) = radix_list_iterator_init(&(_iter), _list);          \
         ((_entry) = radix_list_get_next(&(_iter), &(_id))) != NULL; \
         (_id) = radix_list_iterator_move(&(_iter)))


/* Use RADIX_LIST as RADIX_TREE */

typedef struct radix_list radix_tree_t;
#define RADIX_TREE(_name)	struct radix_list _name;
#define INIT_RADIX_TREE(_idr) radix_list_init(_idr)

typedef struct radix_list_iter radix_tree_iter_t;

#define radix_tree_init radix_list_init
#define radix_tree_lookup radix_list_lookup
#define radix_tree_insert radix_list_insert
#define radix_tree_delete radix_list_delete
#define radix_tree_for_each_entry radix_list_for_each_entry


#endif // !__QDF_RADIX_LIST_H

