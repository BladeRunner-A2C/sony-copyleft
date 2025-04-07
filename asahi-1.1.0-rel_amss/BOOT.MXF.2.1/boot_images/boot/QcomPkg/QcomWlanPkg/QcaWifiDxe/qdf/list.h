/*
 * Copyright (c) 2020-2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_LIST_H
#define __QDF_LIST_H

#include <Uefi.h>
#include <Base.h>
#include <Library/BaseLib.h>

 /*****************************************************************************/
 /* list api */
typedef LIST_ENTRY list_entry_t;

static inline list_entry_t *list_init_head(list_entry_t *list_head)
{
    return InitializeListHead(list_head);
}

static inline list_entry_t *list_add_tail(list_entry_t *entry, list_entry_t *list_head)
{
    return InsertTailList(list_head, entry);
}

static inline list_entry_t *list_insert_head(list_entry_t *list_head, list_entry_t *entry)
{
    return InsertHeadList(list_head, entry);
}

static inline void __list_insert(list_entry_t *newe,
    list_entry_t *prev, list_entry_t *next,
    list_entry_t *list_head)
{
    newe->ForwardLink = next;
    newe->BackLink = prev;
    next->BackLink = newe;
    prev->ForwardLink = newe;
}

static inline list_entry_t *list_insert_before(list_entry_t *list_head,
    list_entry_t *next, list_entry_t *newe)
{
    __list_insert(newe, GetPreviousNode(list_head, next), next, list_head);
    return list_head;
}

static inline list_entry_t *list_del(list_entry_t *entry)
{
    return RemoveEntryList(entry);
}

static inline u8 list_is_empty(const list_entry_t *list_head)
{
    return IsListEmpty(list_head);
}

static inline u8 list_is_last(const list_entry_t *list_head,
    const list_entry_t *entry)
{
    return IsNodeAtEnd(list_head, entry);
}

static inline list_entry_t *list_first_entry(list_entry_t *list_head)
{
    return GetFirstNode(list_head);
}

static inline void list_move_tail(list_entry_t *list, list_entry_t *head)
{
    list_del(list);
	list_add_tail(list, head);
}

static inline u8 list_contains_entry(
    list_entry_t *list_head, const list_entry_t *entry)
{
    return IsNodeInList(list_head, entry);
}

#define list_first_entry_or_null(_ptr, _type, _member)                   \
    (list_is_empty(_ptr) ? NULL : BASE_CR(list_first_entry(_ptr), _type, _member))

#define list_for_each_entry(_item, _list_head, _type, _member)	          \
    for ((_item) = BASE_CR((_list_head)->ForwardLink, _type, _member);    \
	     &(_item)->_member != (_list_head);					              \
	     (_item) = BASE_CR((_item)->_member.ForwardLink, _type, _member))


#define list_for_each_entry_safe(_item, _tmp, _list_head, _type, _member)  \
    for ((_item) = BASE_CR((_list_head)->ForwardLink, _type, _member),	   \
	 (_tmp) = BASE_CR((_item)->_member.ForwardLink, _type, _member);	   \
	 &(_item)->_member != (_list_head);					                   \
	 (_item) = (_tmp), (_tmp) = BASE_CR((_item)->_member.ForwardLink, _type, _member))


#endif // !__QDF_LIST_H

