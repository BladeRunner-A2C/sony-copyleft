/*
===========================================================================
*/
/**
  @file swsys_linkedlist.h

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

#ifndef SWSYS_LINKEDLIST_H
#define SWSYS_LINKEDLIST_H

#include <stdint.h>
#include <stdbool.h>

typedef struct swsys_linkedlist_node {
  void* data;
  struct swsys_linkedlist_node* next;
  struct swsys_linkedlist_node* prev;
} swsys_linkedlist_node;

// doubly linked list with dummy node
typedef struct {
  swsys_linkedlist_node* head;
  uint64_t size;
} swsys_linkedlist;

swsys_linkedlist* swsys_linkedlist_init();

// you must free your own data before calling this
uint32_t swsys_linkedlist_deinit(swsys_linkedlist* list);

// new node will be inserted at 'end' of list (the prev of the head).
swsys_linkedlist_node* swsys_linkedlist_append(swsys_linkedlist* list, void* data);

// new node will be inserted after 'node'
swsys_linkedlist_node* swsys_linkedlist_insert(swsys_linkedlist* list,
    swsys_linkedlist_node* node,
    void* data);

void swsys_linkedlist_remove(swsys_linkedlist* list, swsys_linkedlist_node* node);

// returns the first node where data_match returns true. data_match takes list_data which
// is the data from the current iteration of the list, and cust_data which is simply the
// cust_data argument to swsys_linkedlist_find
swsys_linkedlist_node* swsys_linkedlist_find(swsys_linkedlist* list,
    bool (*data_match)(void* list_data, void* cust_data),
    void* cust_data);

// returns the first node where data_match returns true. Starts looking after an
// arbitrary node. data_match is the same as in swsys_linkedlist_find
swsys_linkedlist_node* swsys_linkedlist_find_after(swsys_linkedlist* list,
    swsys_linkedlist_node* node,
    bool (*data_match)(void* list_data, void* cust_data),
    void* cust_data);

// runs func on every data
void swsys_linkedlist_foreach(swsys_linkedlist* list,
    void (*func)(void* data, void* cust_data),
    void* cust_data);

void* swsys_linkedlist_get_nth(swsys_linkedlist* list, uint64_t n);

#endif // SWSYS_LINKEDLIST_H
