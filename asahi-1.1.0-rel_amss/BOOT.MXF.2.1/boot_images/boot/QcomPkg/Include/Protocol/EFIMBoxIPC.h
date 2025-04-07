#ifndef __EFIMBOXIPC_H__
#define __EFIMBOXIPC_H__
/** 
  @file  EFIMBoxIPC.h
  @brief Mailbox IPC Interface in UEFI.
*/
/*=============================================================================
  Copyright (c) 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     ----------------------------------------------------------
 06/07/22   mad     Created
=============================================================================*/


/*===========================================================================
  INCLUDE FILES
===========================================================================*/
#include "mboxipc_common.h"

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/

/** @ingroup efi_mboxipc_constants
  Protocol version.
*/
#define EFI_MBOXIPC_PROTOCOL_REVISION 0x0000000000000001

/*  Protocol GUID definition */
#define EFI_MBOXIPC_PROTOCOL_GUID \
  { 0x330ed179, 0x7c94, 0x407c, { 0xaf, 0x99, 0xdd, 0xcc, 0x62, 0x44, 0xa0, 0x31 } }

/* generated online:
{330ed1797c94407caf99ddcc6244a031}
*/

/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/*
  External reference to the Mailbox-IPC Protocol GUID.
 */
extern EFI_GUID gEfiMBoxIPCProtocolGuid;
/** @endcond */

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/

/** 
 *EFI_MBOX_IPC_OPEN
 * Opens a logical, bi-directional Mailbox channel based on the specified config params
 *
 * @param[in]       cfg_ptr  Pointer to the configuration structure. Reference mboxipc_common.h
 * @param[in,out]   handle   Mailbox IPC handle associated with the logical channel
 * @param[in,out]   ret      Return value from Mailbox-IPC API
 *
 * @return       Standard UEFI status codes
 *
 * @sideeffects
 * Implementation notes:
 * Assigns a pre-decided (compile-time) set of command-registers from both Send and Receive H/W mailboxes.
 * The receive register is marked ready to receive.
 *
 * Rev01 notes:
 * Channels are pre-assigned (hard-coded) for the first revision.
 * This call will not result in an interrupt to remote.
 * API user needs to anticipate that this API will use locks.
 */
typedef EFI_STATUS (EFIAPI* EFI_MBOX_IPC_OPEN)
(
  mbox_ipc_open_config_type *cfg_ptr,
  mbox_ipc_handle_type      *handle,
  mbox_ipc_err_type			*ret 
);

/** EFI_MBOX_IPC_CLOSE
 * Closes the Mailbox logical channel specified by the handle.
 *
 * @param[in]       handle   Mailbox IPC handle associated with the logical channel
 * @param[in,out]   ret      Return value from Mailbox-IPC API
 *
 * @return       Standard Mailbox IPC error codes
 *
 * @sideeffects  Frees the corresponding resources and removes from local open list. API uses locks.
 *               Rev01 : Only local clean-up, does not inform remote. API added for completion.
 */
 typedef EFI_STATUS (EFIAPI* EFI_MBOX_IPC_CLOSE)
(
  mbox_ipc_handle_type handle,
  mbox_ipc_err_type			*ret
);


/**
EFI_MBOX_IPC_SEND
Write to remote Host's mailbox.
========================
Mbox_IPC API user can provide 32-bit message to be written.
This message can be the off-set of user's data in shared memory, that is accessible by remote Host.

arguments:
@param[in]      handle  		channel handle returned from mbox_ipc_open
@param[in]      pkt_priv 	    Reserved for Rev01. Can be used as a value that can be returned if we support a callback for send completion.
@param[in]      message 		This is upto mbox_user code on Host and Client sides. Can be the offset of some shared structure in memory.
@param[in]      len 		 	Size of data in shared memory that corresponds to "message". Zero is an acceptable value for len.
@param[in]      options 		Reserved
@param[in,out]  ret             Return value from Mailbox-IPC API

return:
MBOX_IPC_STATUS_SUCCESS        successfully written
MBOX_IPC_CH_NOT_READY_FOR_TX   channel is either not ready or busy
MBOX_IPC_INVALID_CH            Invalid channel was specified
*/
typedef EFI_STATUS (EFIAPI* EFI_MBOX_IPC_SEND)
(
  mbox_ipc_handle_type handle, 
  const void           *pkt_priv, 
  mbox_message         message, 
  UINT16               len, 
  UINT32               options, 
  mbox_ipc_err_type    *ret
);

/**
EFI_MBOX_RX_DONE

API for mailbox API user to indicate that the received message is consumed.
This API will not hold any locks.

@note: This will not raise an interrupt to the remote.
But this will indicate to the remote that this channel is ready to receive data.

arguments:
@param[in]      handle      Mailbox IPC handle associated with the logical channel
@param[in]      message     Message that was received that the API user is done consuming.
@param[in,out]  ret         Return value from Mailbox-IPC API

return:
MBOX_IPC_STATUS_SUCCESS        success
MBOX_IPC_INVALID_CH    		   Invalid channel was specified
MBOX_IPC_INVALID_PARAM		   Message is invalid
*/
typedef EFI_STATUS (EFIAPI* EFI_MBOX_IPC_RX_DONE)
(
  mbox_ipc_handle_type handle, 
  mbox_message         message,
  mbox_ipc_err_type	   *ret
);

/**
EFI_MBOX_STATUS

API for mailbox API user to check state of its channel.
This API will not hold any locks.
This API returns a bit-mask of channel states.

arguments:
@param[in]      handle      Mailbox IPC handle associated with the logical channel
@param[in,out]  state       Bit-mask of channel states that will be returned.
Bit mask of channel states: Refer mboxipc_common.h.
*/

typedef EFI_STATUS (EFIAPI* EFI_MBOX_IPC_CH_STATUS)
(
  mbox_ipc_handle_type handle, 
  UINT32              *state
);


/**
 * This API allows clients to poll the transport for any new data that might
 * have come in. It would *usually* be used when incoming interrupts are
 * disabled.
 *
 * @param[in]   handle      Mailbox-IPC handle associated with the logical channel
 * @param[out]  ret         Return code from the actual Mailbox-IPC API                       
 *
 * @return       Standard EFI error codes
 *
 * @sideeffects  None
 */
 //Note:
/*MSFT is looking at approving scheduler for hamoa. 
I would not remove any existing logic until may be next chip.
But for new code, we can deprioritize poll API.*/

/* typedef EFI_STATUS (EFIAPI* EFI_MBOX_IPC_RX_POLL)
(
  mbox_ipc_handle_type handle,
  mbox_status    *ret  
);*/


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_mailbox_ipc_protocol
  @par Summary
  Mailbox-IPC Protocol interface.
*/
typedef struct _EFI_MBOX_IPC_PROTOCOL {
  UINT64                              Revision;
  EFI_MBOX_IPC_OPEN					  MailBoxIPCOpen;
  EFI_MBOX_IPC_CLOSE				  MailBoxIPCClose;
  EFI_MBOX_IPC_SEND                   MailBoxIPCSend;
  EFI_MBOX_IPC_RX_DONE                MailBoxIPCRxDone;
  EFI_MBOX_IPC_CH_STATUS              MailBoxIPCChStatus;
  //EFI_MBOX_IPC_RX_POLL              MailBoxIPCRxPoll; /* de-prioritized */
}EFI_MBOX_IPC_PROTOCOL;

#endif /* __EFIMBOXIPC_H__ */