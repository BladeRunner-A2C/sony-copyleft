/**
 * @file MailboxDxe.c
 *
 * DXE driver for Mailbox device in UEFI
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
06/29/2022 mad     Created
===========================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIMBoxIPC.h>

extern mbox_ipc_err_type mbox_ipc_init();
static EFI_STATUS efi_status_from_mbox_ipc_status(mbox_ipc_err_type err);

/*===========================================================================
                        INTERNAL FUNCTION DEFINITIONS
===========================================================================*/
 /** 
 * EFI_mbox_ipc_open
 * Opens a logical, bi-directional Mailbox channel based on the specified config params
 *
 * @param[in]       cfg_ptr  Pointer to the configuration structure. Reference mboxipc_common.h
 * @param[in,out]   handle   Mailbox IPC handle associated with the logical channel
 * @param[in,out]   ret      Return value from Mailbox-IPC API
 *
 * @return       Standard UEFI status codes
 *
 * @sideeffects
 * Assigns a pre-decided (compile-time) set of command-registers from both Send and Receive H/W mailboxes.
 * The receive register is marked ready to receive.
 *
 * Rev01 notes:
 * Channels are pre-assigned (hard-coded) for the first mailbox-ipc s/w revision.
 * This call will not result in an interrupt to remote.
 * API user needs to anticipate that this API will use locks.
 */
static EFI_STATUS EFI_mbox_ipc_open
(
  mbox_ipc_open_config_type *cfg_ptr,
  mbox_ipc_handle_type      *handle,
  mbox_ipc_err_type			*ret 
)
{
  if(!ret)
	return EFI_INVALID_PARAMETER;
  
  *ret = mbox_ipc_open(cfg_ptr, handle);
  
  return (efi_status_from_mbox_ipc_status(*ret));
}


/** EFI_mbox_ipc_close
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
 static EFI_STATUS EFI_mbox_ipc_close
(
  mbox_ipc_handle_type handle,
  mbox_ipc_err_type			*ret
)
{
  if(!ret)
    return EFI_INVALID_PARAMETER;

  *ret = mbox_ipc_close(handle);
  
  return (efi_status_from_mbox_ipc_status(*ret));
}

/**
EFI_mbox_ipc_send
Write to remote Host's mailbox.
========================
Mbox_IPC API user can provide 32-bit message to be written.
Recommendation: This message *can* be the off-set of user's data in shared memory, that is accessible by remote Host.

arguments:
@param[in]      handle  		channel handle returned from mbox_ipc_open
@param[in]      pkt_priv 	    Reserved and not used for s/w Rev-01. Future: Can be used as a value that can be returned if we support a callback for send completion.
@param[in]      message 		This is upto mbox_user code on Host and Client sides. Can be the offset of some shared structure in memory. Can also be a control message.
@param[in]      len 		 	Size of data in shared memory that corresponds to "message". Zero is an acceptable value for len.
@param[in]      options 		Reserved
@param[in,out]  ret             Return value from Mailbox-IPC API

return:
MBOX_IPC_STATUS_SUCCESS        			successfully written
MBOX_IPC_STATUS_CH_NOT_READY_FOR_TX   	channel is either not ready or busy
MBOX_IPC_STATUS_INVALID_CH            	Invalid channel was specified

@sideeffects
Raises an interrupt to remote mailbox host.
*/
static EFI_STATUS EFI_mbox_ipc_send
(
  mbox_ipc_handle_type handle, 
  const void           *pkt_priv, 
  mbox_message         message, 
  UINT16               len, 
  UINT32               options, 
  mbox_ipc_err_type    *ret
)
{
  if(!ret)
    return EFI_INVALID_PARAMETER;

  *ret = mbox_ipc_send(handle, pkt_priv, message,len,options);
  return (efi_status_from_mbox_ipc_status(*ret));
}

/**
EFI_MBOX_RX_DONE

API for mailbox API user to indicate that the received message is consumed.
This API will not hold any locks.

@note: This will not raise an interrupt to the remote.
But this will indicate to the remote that this channel is ready to receive data,
so the remote can send another message.

arguments:
@param[in]      handle      Mailbox IPC handle associated with the logical channel
@param[in]      message     Message that was received that the API user is done consuming.
@param[in,out]  ret         Return value from Mailbox-IPC API

possible values for *ret:
MBOX_IPC_STATUS_SUCCESS        success
MBOX_IPC_INVALID_CH    		   Invalid channel was specified
MBOX_IPC_INVALID_PARAM		   Message is invalid

@sideeffects
The channel is marked ready for receiving a new message.
*/
static EFI_STATUS EFI_mbox_ipc_rx_done
(
  mbox_ipc_handle_type handle, 
  mbox_message         message,
  mbox_ipc_err_type	   *ret
)
{
  if(!ret)
    return EFI_INVALID_PARAMETER;

  *ret = mbox_ipc_rx_done(handle, message);
  return(efi_status_from_mbox_ipc_status(*ret));
}

/**
EFI_mbox_ipc_ch_status
API for mailbox API user to check state of its channel.
This API will not hold any locks.
This API returns a bit-mask of channel states.

arguments:
@param[in]  	handle      Mailbox IPC handle associated with the logical channel
@param[in,out]  state       Bit-mask of channel states as defined in mboxipc_common.h

return:
EFI_SUCCESS
*/
static EFI_STATUS EFI_mbox_ipc_ch_status
(
  mbox_ipc_handle_type handle, 
  UINT32              *state
)
{
	if(!state)
		return EFI_INVALID_PARAMETER;
	
	*state = mbox_ipc_ch_status(handle);
	
	return EFI_SUCCESS;
}

/**
Internal helper function:
Return appropriate EFI_STATUS values, given the mailbox ipc error codes.
*/
static EFI_STATUS efi_status_from_mbox_ipc_status(mbox_ipc_err_type err)
{
	switch (err)
	{
		case MBOX_IPC_STATUS_SUCCESS:
		  return EFI_SUCCESS;
		case MBOX_IPC_STATUS_CH_NOT_READY_FOR_TX:
		  return EFI_NOT_READY;
		case MBOX_IPC_STATUS_INVALID_CH:
		case MBOX_IPC_STATUS_INVALID_PARAM:
		  return EFI_INVALID_PARAMETER;
		case MBOX_IPC_STATUS_FAILURE:
		  return EFI_PROTOCOL_ERROR;
		default:
		  return EFI_PROTOCOL_ERROR;
	}
}
/*===========================================================================
                           INTERNAL DATA STRUCTURES
===========================================================================*/

static EFI_MBOX_IPC_PROTOCOL MBoxIPCProtocol =
{
  EFI_MBOXIPC_PROTOCOL_REVISION, /* Revision */
  EFI_mbox_ipc_open, /* MailBoxIPCOpen */
  EFI_mbox_ipc_close, /* MailBoxIPCClose */
  EFI_mbox_ipc_send, /* MailBoxIPCSend */
  EFI_mbox_ipc_rx_done, /* MailBoxIPCRxDone */
  EFI_mbox_ipc_ch_status /*,  MailBoxIPCChStatus */
  //MailBoxIPCRxPoll /*  MailBoxIPCRxPoll , de-prioritized */
};

/*===========================================================================
                        EXTERNAL FUNCTION DEFINITIONS
===========================================================================*/
/**
 * Entry point for the MailboxDxe driver.
 */
EFI_STATUS EFIAPI MailboxEntryPoint
(
  EFI_HANDLE            ImageHandle,
  EFI_SYSTEM_TABLE     *SystemTable
)
{
  EFI_HANDLE handle = NULL;
  EFI_STATUS status;
  mbox_ipc_err_type err;

  status = gBS->InstallMultipleProtocolInterfaces(&handle,
      &gEfiMBoxIPCProtocolGuid, (void **)&MBoxIPCProtocol, NULL, NULL, NULL );
  
  err = mbox_ipc_init();
  status = efi_status_from_mbox_ipc_status(err);
  return status;
}
