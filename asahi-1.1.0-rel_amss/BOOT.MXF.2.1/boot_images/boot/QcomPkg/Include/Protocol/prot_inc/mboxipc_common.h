#ifndef __MBOX_IPC_COMMON_H__
#define __MBOX_IPC_COMMON_H__

/*
 * @file mboxipc_common.h
 *
 * Public API and data structures needed to use H/W Mailbox IPC.
 */

/*==============================================================================
     Copyright (c) 2022 Qualcomm Technologies, Inc.
     All rights reserved.
     Qualcomm Confidential and Proprietary
==============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/23/22   mad      Initial revision
===========================================================================*/

/** Overview
================
Mailbox IPC provides a logical IPC layer over Mailbox H/W.
Mbox IPC users can open a logical channel (implemented as pre-assigned channels for S/W ver 1) 
for sending and receiving 32-bit messages from/to remote subsystems.
These channels can have only one message in-flight.

List of possible subsystems:
  "pdp0"   PDP in NCC0
  "pdp1"   PDP in NCC1
  "pdp2"   PDP in NCC2
  "cpucp"  CPU-CP processor
  "tz"     TZ
  "apss"   HLOS or UEFI
*/

/** Max allowed channel name length */
#define MBOX_IPC_CH_NAME_LEN 			16

/**---- Mailbox IPC options------- */
#define MBOX_IPC_SEND_BLOCK				0x1  /* Not implemented. */
/* 
For future: 
On Write, block until remote has read. */
/* If this flag is specified, the send_timeout is not used. We just busy wait for remote to read message.*/


#define MBOX_IPC_NO_SEND_LOCKS			0x2  /* Use exclusive resources and don't hold any locks */
/* Rev01 will not hold any locks at all in send path(since we don't support any packet Q-ing etc). So this is superfluous, but good to keep for future.*/
/**---- Mailbox options end------- */

/** API users must call this macro to initialize the open config structure
 * before setting its individual members. This will ensure that the 
 * default optional values in the structure are appropriately initialized. */
#define MBOX_IPC_OPEN_CONFIG_INIT(cfg) \
  memset(&(cfg), 0, sizeof(cfg))

/** Mailbox IPC status/return codes */
typedef enum {
  MBOX_IPC_STATUS_SUCCESS                = 0,
  MBOX_IPC_STATUS_CH_NOT_READY_FOR_TX    = -1,
  MBOX_IPC_STATUS_INVALID_CH			 = -2,
  MBOX_IPC_STATUS_FAILURE                = -3,
  MBOX_IPC_STATUS_INVALID_PARAM			 = -4,
  MBOX_IPC_STATUS_MEM_FAILURE			 = -5,
  MBOX_IPC_STATUS_DRV_FAILURE			 = -6
}mbox_ipc_err_type;

/** Mailbox IPC channel state bit-mask */
/* Not implemented in Hamoa H/W v1 due to H/W issue.*/
#define MBOX_IPC_INVALID_CH				0 /** Invalid channel was specified */
#define MBOX_IPC_CH_READY_TO_SEND		2 /** Channel is available to send a message (i.e. Remote is ready to receive a message) */
#define MBOX_IPC_CH_READY_TO_RECEIVE	4 /** Channel is ready to receive a message */

/** 
 * Opaque handle returned by mbox_ipc_open. API user uses this handle to call into
 * Mailbox IPC API for any further activity related to the channel.
 *
 * API user must not modify or try to interpret this value 
 */
typedef void *mbox_ipc_handle_type;

/* Mailbox message is a 32-bit value */
typedef UINT32 mbox_message;


/*
Type definition of receive callback to register with mailbox-IPC to receive message from remote.
This is part of mbox_ipc_open_config_type and needs to be provided while opening the logical channel using mbox_ipc_open() API.

This callback will be called in ISR context, in UEFI.
This callback will be called while holding a lock.

arguments:
@param[in]  handle      Mailbox IPC handle associated with the logical channel
@param[out] priv        Private data provided by API user in mbox_ipc_open_config_type
@param[out] message     message received from remote (32-bit message for Rev01)
@param[out] size        size of data in shared memory. 
                        (Can be 0 if message is just a control message with no associated shared memory data.)
*/
typedef void (*mbox_ipc_rx_notification_cb)(mbox_ipc_handle_type handle, const void *priv, mbox_message message, UINT16 size);


/**
 * Data Structure for Mailbox-IPC logical channel open configuration
 *
 * This structure is used by the API users to open a Mailbox logical channel
 * when calling mbox_ipc_open()
 *
 * API users must ensure to zero this structure before setting the members
 * to ensure forwards binary compatibility.
 */
typedef struct {
  /** string name for the remote subsystem to which the user wants to 
      connect */
	  
  const char                          *remote_ss; /** "pdp0" , "pdp1", "pdp2", "cpucp" */
  
  /** Channel name. Pre-assigned for first revision and not used except for debugging. check mbox_ipc_channels.c for existing pre-assigned channels.
	There can be multiple channels between same subsystems , used by different mailbox API use-cases.  */
  const char						  *name; 

  /** Reserved. Set to 0.  */
  UINT32                            options;

  /** Private data for API user to maintain context. This data is passed back
      to API user in the notification callbacks */
  const void                          *priv;

  /** Data receive notification callback. Optional. (Needed only if API user needs to receive a message.) */
  mbox_ipc_rx_notification_cb            notify_rx;

  /** Set to 0. Reserved. */
  UINT32                              send_timeout;
  
  /** Optional. If non-zero, send_address will be used to assign channel send/receive register instead of using channel name "name" */
  UINT64 							  send_address;
  
  /** Reserved. Set to zero.*/
  UINT64							  receive_address;

}mbox_ipc_open_config_type;

/**
Update:
Not implemented in Hamoa v1 due to H/W bug. API will do nothing.
API for mailbox API user to indicate that the received message is consumed.
This API will not hold any locks.

Note: This will not raise an interrupt to the remote.
But this will indicate to the remote that this channel is ready to receive data.

arguments:
@param[in]  handle      Mailbox IPC handle associated with the logical channel
@param[in]  message     Message that was received that the API user is done consuming.

return:
MBOX_IPC_STATUS_SUCCESS        success
MBOX_IPC_STATUS_INVALID_CH     Invalid channel was specified
MBOX_IPC_STATUS_INVALID_PARAM  Message is invalid
*/
mbox_ipc_err_type mbox_ipc_rx_done(mbox_ipc_handle_type handle, mbox_message message);

/** 
 * Opens a logical, bi-directional Mailbox channel based on the specified config params
 *
 * @param[in]    cfg_ptr  Pointer to the configuration structure
 *
 * @param[out]   handle   Mailbox IPC handle associated with the logical channel
 *
 * @return       Standard Mailbox IPC error codes
 *
 * @sideeffects  
 * Rev01 notes:
 * Channels are pre-assigned (hard-coded) for the first revision.
 * This call will not result in an interrupt to remote.
 * API user needs to anticipate that this API will use locks.
 */
mbox_ipc_err_type mbox_ipc_open
(
  mbox_ipc_open_config_type *cfg_ptr,
  mbox_ipc_handle_type      *handle
);

/** 
 * Closes the Mailbox logical channel specified by the handle.
 *
 * @param[in]    handle   Mailbox IPC handle associated with the logical channel
 *
 * @return       Standard Mailbox IPC error codes
 *
 * @sideeffects  Frees the corresponding resources and removes from local open list. API uses locks.
 *               Rev01 : Only local clean-up, does not inform remote. API added for completion.
 */
mbox_ipc_err_type mbox_ipc_close
(
  mbox_ipc_handle_type handle
);

/**
Write to remote Host's mailbox.
========================
Mbox_IPC API user can provide 32-bit message to be written.
This message can be the off-set of user's data in shared memory, that is accessible by remote Host.

arguments:
@param[in] handle  		channel handle returned from mbox_ipc_open
@param[in] pkt_priv 	Reserved for Rev01. Can be used as a value that can be returned if we support a callback for send completion.
@param[in] message 		This is upto mbox_user code on Host and Client sides. Can be the offset of some shared structure in memory.
@param[in] len 		 	Not supported due to H/W bug. Set to 0. //For future: Size of data in shared memory that corresponds to "message". Zero is an acceptable value for len.
@param[in] options 		Reserved

return:
MBOX_IPC_STATUS_SUCCESS        			successfully written
MBOX_IPC_STATUS_CH_NOT_READY_FOR_TX   	Will not return this status due to H/W bug. For future: channel is either not ready or busy  
MBOX_IPC_STATUS_INVALID_CH            	Invalid channel was specified
*/
mbox_ipc_err_type mbox_ipc_send(mbox_ipc_handle_type handle, const void *pkt_priv, mbox_message message, UINT16 len, UINT32 options);

/**
Will not return status due to H/W bug. Do not use API.

For future:
API for mailbox API user to check state of its channel.
This API will not hold any locks.
This API returns a bit-mask of channel states.

arguments:
@param[in]  handle      Mailbox IPC handle associated with the logical channel

return:
Bit mask of channel states:
Mailbox IPC channel state bit-mask
#define MBOX_IPC_INVALID_CH					0
#define MBOX_IPC_CH_READY_TO_SEND			2
#define MBOX_IPC_CH_READY_TO_RECEIVE		4
*/
UINT32 mbox_ipc_ch_status(mbox_ipc_handle_type handle);
#endif /* __MBOX_IPC_COMMON_H__ */