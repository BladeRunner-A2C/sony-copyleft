#ifndef MBOX_INTERNAL_H
#define MBOX_INTERNAL_H
/*=============================================================================

                       MAILBOX INTERNAL


 Copyright (c) 2023 QUALCOMM Technologies, Incorporated.
 All rights reserved.
 Qualcomm Confidential and Proprietary

=============================================================================*/

/*=============================================================================
                         EDIT HISTORY FOR FILE
$Header:  $
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include "mboxipc_common.h"
#include "mbox_os_utils.h"
#include "mbox_cfg.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/
#define MBOX_REMOTE_ID_PDP0		0  /* "pdp0" */
#define MBOX_REMOTE_ID_PDP1 	1  /* "pdp1" */
#define MBOX_REMOTE_ID_PDP2		2  /* "pdp2" */
#define MBOX_REMOTE_ID_CPUCP	3  /* "cpucp" */

#define MBOX_CH_NAME_LEN 32

#define MBOX_LIST(type, name) \
  struct { \
    type *head; \
    type *tail; \
    unsigned int count; \
  } name

#define MBOX_LINK(type, link) \
  struct { \
    type *prev; \
    type *next; \
  } link

#define MBOX_LIST_INIT(list) do {  \
  (list).head = (list).tail = NULL; \
  (list).count = 0; \
} while(0)

#define MBOX_LINK_INIT(link) (link).next = (link).prev = NULL
#define MBOX_LINK_NXT(link) ((link).next)

#define MBOX_LIST_HEAD(list) ((list.count) ? (list.head) : NULL)
#define MBOX_LIST_TAIL(list) ((list.count) ? (list.tail) : NULL)
#define MBOX_LIST_CNT(list) (list.count)
#define MBOX_LIST_REMOVE(list, node, link) \
  do { \
    if((node)->link.prev) \
      (node)->link.prev->link.next = (node)->link.next; \
    else /* node at the front of the list */ \
      list.head = (node)->link.next; \
    if((node)->link.next) \
      (node)->link.next->link.prev = (node)->link.prev; \
    else /* node at the end of the list */ \
      list.tail = (node)->link.prev; \
    list.count--; \
  } while(0)

#define MBOX_LIST_ADD(list, node, link) \
  do { \
    if(!list.tail) \
    { \
      /* first node on the list */ \
      list.tail = list.head = node; \
    } \
    else \
    { \
      (node)->link.prev = list.tail; \
      list.tail->link.next = node; \
      list.tail = node; \
    } \
    list.count++; \
  } while(0)

#define MBOX_LIST_FIND(list, iter, link, test) do {  \
  iter = (list).head; \
  while(iter) { \
    if(test) {  \
      break;  \
    } \
    iter = (iter)->link.next;  \
  } \
} while(0)

#define MBOX_LIST_QUEUE(list, node, link) \
    do { \
      MBOX_LINK_INIT((node)->link); \
      MBOX_LIST_ADD(list, node, link); \
    } while(0)

#define MBOX_LIST_QUEUE_SAFE(list, mutex, node, link) \
  do { \
    mbox_os_mutex_lock(mutex);\
    MBOX_LIST_QUEUE(list, node, link);\
    mbox_os_mutex_unlock(mutex);\
  } while(0)

#define MBOX_LIST_DEQUEUE(list, node, link) \
  do { \
    (node) = MBOX_LIST_HEAD(list); \
    if ((node) != NULL) \
    { \
      MBOX_LIST_REMOVE(list, node, link); \
    } \
  } while(0)

#define MBOX_LIST_DEQUEUE_SAFE(list, mutex, node, link) \
    do { \
      mbox_os_mutex_lock(mutex);\
      MBOX_LIST_DEQUEUE(list, node, link); \
      mbox_os_mutex_unlock(mutex);\
    } while(0)

#define MBOX_LIST_MOVE(dst_list, src_list, node, link) \
    do { \
      MBOX_LIST_REMOVE(src_list, node, link); \
      MBOX_LINK_INIT((node)->link); \
      MBOX_LIST_ADD(dst_list, node, link); \
    } while(0)

#define MBOX_LIST_MOVE_SAFE(dst_list, src_list, mutex, node, link) \
  do { \
    mbox_os_mutex_lock(mutex);\
    MBOX_LIST_MOVE(dst_list, src_list, node, link); \
    mbox_os_mutex_unlock(mutex);\
  } while(0)

#define MBOX_LIST_REMOVE_SAFE(list, mutex, node, link) \
  do { \
    mbox_os_mutex_lock(mutex);\
    MBOX_LIST_REMOVE(list, node, link); \
    mbox_os_mutex_unlock(mutex);\
  } while(0)


#define MBOX_STATUS_SUCCESS               MBOX_IPC_STATUS_SUCCESS 
#define MBOX_STATUS_CH_NOT_READY_FOR_TX   MBOX_IPC_STATUS_CH_NOT_READY_FOR_TX
#define MBOX_STATUS_INVALID_CH            MBOX_IPC_STATUS_INVALID_CH
#define MBOX_STATUS_FAILURE               MBOX_IPC_STATUS_FAILURE
#define MBOX_STATUS_INVALID_PARAM         MBOX_IPC_STATUS_INVALID_PARAM
#define MBOX_STATUS_MEM_FAILURE           MBOX_IPC_STATUS_MEM_FAILURE
#define MBOX_STATUS_DRV_FAILURE           MBOX_IPC_STATUS_DRV_FAILURE

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
typedef mbox_ipc_err_type mbox_status_type;

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/


/*=============================================================================

                     PUBLIC FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
  FUNCTION  mbox_drv_init
=============================================================================*/
mbox_status_type mbox_drv_init(void);

/*=============================================================================
  FUNCTION  mbox_drv_ch_enable
=============================================================================*/
mbox_status_type mbox_drv_ch_enable(uint8 remote_id, uint8 ch_id);

/*=============================================================================
  FUNCTION  mbox_drv_ch_disable
=============================================================================*/
mbox_status_type mbox_drv_ch_disable(uint8 remote_id, uint8 ch_id);

/*=============================================================================
  FUNCTION  mbox_drv_ch_tx
=============================================================================*/
mbox_status_type mbox_drv_ch_tx(uint8 remote_id, uint8 ch_id, uint32 message);

/*=============================================================================
  FUNCTION  mbox_ipc_ch_rx_cb
=============================================================================*/
void mbox_ipc_ch_rx_cb(uint8 remote_id, uint8 ch_id, uint32 message);

#endif /* MBOX_INTERNAL_H */
