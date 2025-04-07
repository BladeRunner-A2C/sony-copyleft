/*
===========================================================================
*/
/**
  @file swsys_linkedlist.c

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/14/17   jh      Initial revision.

  ====================================================================
*/

#include "../swsys_env/swsys_env.h"
#include "../swsys_logger/swsys_logger.h"
#include "swsys_linkedlist.h"

swsys_linkedlist* swsys_linkedlist_init()
{
  void* ll = swsys_malloc(sizeof(swsys_linkedlist));
  if (!ll) {
	  swsys_error("Fail to allocate memory for linklist\n");
	  return NULL;
  }
  swsys_linkedlist* llt = (swsys_linkedlist*)ll;
  void* h = swsys_malloc(sizeof(swsys_linkedlist_node));
  if (!h) {
	  swsys_error("Fail to allocate memory for linklist head node\n");
	  return NULL;
  }
  swsys_linkedlist_node* ht = (swsys_linkedlist_node*)h;

  llt->head = ht;
  ht->next = ht;
  ht->prev = ht;

  llt->size = 0;
  return llt;
}

uint32_t swsys_linkedlist_deinit(swsys_linkedlist* list)
{
  swsys_linkedlist_node* head = NULL;
  swsys_linkedlist_node* next = NULL;
  swsys_linkedlist_node* temp;
  if (!list) {
    return 1;
  }
  head = list->head;
  if (!head)
  {
  	return 1;
  }
  next = head->next;
  while (next != head) {
    temp = next;
    next = next->next;
    swsys_linkedlist_remove(list, temp);
  }
  swsys_free(head);
  swsys_free(list);
  return 0;
}

swsys_linkedlist_node* swsys_linkedlist_append(swsys_linkedlist* list, void* data)
{
  return swsys_linkedlist_insert(list, list->head->prev, data);
}

swsys_linkedlist_node* swsys_linkedlist_insert(swsys_linkedlist* list,
    swsys_linkedlist_node* node,
    void* data)
{
  void* newnode_void = swsys_malloc(sizeof(swsys_linkedlist_node));
  if (!newnode_void) {
	  swsys_error("Fail to allocate memory for new node\n");
	  return NULL;
  }
  swsys_linkedlist_node* newnode = (swsys_linkedlist_node*)newnode_void;
  newnode->data = data;
  newnode->prev = node;
  newnode->next = node->next;
  node->next->prev = newnode;
  node->next = newnode;
  list->size++;
  return newnode;
}

void swsys_linkedlist_remove(swsys_linkedlist* list, swsys_linkedlist_node* node)
{
  if (list->size == 0) {
    return;
  }
  node->next->prev = node->prev;
  node->prev->next = node->next;
  swsys_trace("linkedlist freeing node\n");
  swsys_free(node);
  list->size--;
}

swsys_linkedlist_node* swsys_linkedlist_find_after(swsys_linkedlist* list,
    swsys_linkedlist_node* node,
    bool (*data_match)(void* list_data, void* cust_data),
    void* cust_data)
{
  swsys_linkedlist_node* head = list->head;
  swsys_linkedlist_node* next = node->next;
  while (next != head) {
    if (data_match(next->data, cust_data)) {
      return next;
    }
    next = next->next;
  }
  return NULL;
}

void swsys_linkedlist_foreach(swsys_linkedlist* list,
    void (*func)(void* data, void* cust_data),
    void* cust_data)
{
  if (list == NULL) {
    return;
  }
  swsys_linkedlist_node* head = list->head;
  swsys_linkedlist_node* next = head->next;
  while (next != head) {
    func(next->data, cust_data);
    next = next->next;
  }
}

swsys_linkedlist_node* swsys_linkedlist_find(swsys_linkedlist* list,
    bool (*data_match)(void* list_data, void* cust_data),
    void* cust_data)
{
  return swsys_linkedlist_find_after(list, list->head, data_match, cust_data);
}

void* swsys_linkedlist_get_nth(swsys_linkedlist* list, uint64_t n)
{
  uint64_t i;
  swsys_trace("in linkedlist_get_nth\n");
  swsys_linkedlist_node* next = list->head->next;
  for ( i = 0; i < n || next == list->head; i++) {
    next = next->next;
  }
  if (next == list->head) {
    swsys_trace("linkedlist_get_nth returning NULL\n");
    return NULL;
  }
  swsys_trace("linkedlist_get_nth returning next->data\n");
  return next->data;
}
