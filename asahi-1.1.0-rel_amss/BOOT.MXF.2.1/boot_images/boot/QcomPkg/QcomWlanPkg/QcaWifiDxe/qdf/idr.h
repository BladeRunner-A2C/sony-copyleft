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

#ifndef __QDF_IDR_H
#define __QDF_IDR_H

#include <qdf/radix_list.h>

struct idr
{
    struct radix_list rdl;
};

typedef struct radix_list_iter idr_iter_t;

#define DEFINE_IDR(_name)	struct idr _name;
#define INIT_IDR(_idr) idr_init(_idr)

static inline void idr_init(struct idr *idr)
{
    radix_list_init(&idr->rdl);
}

static inline void idr_destroy(struct idr *idr)
{
    radix_list_destory(&idr->rdl);
}

static inline void *idr_find(struct idr *idr, u64 id)
{
    return radix_list_lookup(&idr->rdl, id);
}

static inline void *idr_remove(struct idr *idr, u64 id)
{
    return radix_list_delete(&idr->rdl, id);
}

static inline int idr_alloc(struct idr *idr, void *ptr, int start, int end)
{
    return (int)radix_list_alloc(&idr->rdl, ptr, start, end);
}

static inline void idr_for_each(const struct idr *idr,
    int(*fn)(int id, void *p, void *data), void *data)
{
    struct radix_list_iter iter;
    void *ptr;
    u64 id;
    
    radix_list_for_each_entry(&idr->rdl, iter, id, ptr) {
        fn((int)id, ptr, data);
    }
}

static inline int idr_alloc_cyclic(struct idr *idr, void *ptr, int start, int end)
{
    // NOTE: use idr_alloc directly
    return idr_alloc(idr, ptr, start, end);
}

#define idr_for_each_entry(_idr, _iter, _id, _entry)                  \
	for ((_id) = radix_list_iterator_init(&(_iter), &(_idr)->rdl);    \
         ((_entry) = radix_list_get_next(&(_iter), &(_id))) != NULL;  \
         (_id) = radix_list_iterator_move(&(_iter)))

#endif // !__QDF_IDR_H

