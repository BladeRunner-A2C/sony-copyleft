/*=============================================================================

                       MAILBOX IPC


 Copyright (c) 2022-2023 QUALCOMM Technologies, Incorporated.
 All rights reserved.
 Qualcomm Confidential and Proprietary

=============================================================================*/

/*=============================================================================
                         EDIT HISTORY FOR FILE

$Header:  $
=============================================================================*/

/* Handshake: Rev 2: */
/*=====================*/
/* Note: No handshake implemented due to H/W bug */

/*Handshake mechanism between Client-proc and Host-proc
For e.g., For AP2PDP mailbox, PDP is Host-proc and AP is Client-proc.
======================================================================
Base address of shared memory for data transfer will have to be hard-coded and shared between PDP and AP.
The 64-bit space available in command register will be used as follows:

<-(Generates intr)--><--No Intr -------->
<-----_1 register---><--_0 register----->

<-32-bit PA offset--><--size--><--ctrl--->
|    |    |    |    |    |    |    |    |


32-bit message allows Client-proc to write offset of data in shared memory. 
( This is upto mailbox user. Mailbox user can use this 32-bit message as just a control message also.)
(But if there is data, then it is recommended that the message be the offset of the data in shared memory.)
16-bit size allows Client-proc to specify size of data available in shared memory.
16-bit control field will be leveraged for IPC handshake.

size: When Client-proc writes to host mailbox, it writes the size of the data in shared memory.
Allowed values for size:
0 to 2^16-1.

When Host-side mailbox_drv reads the Command register, it needs to set the lsb (bit 0) of "ctrl" field to 1, 
to indicate it is ready for next command.
Note: We'll call this "Ready to receive" from Host-side.
Since this will use the _0 register, an interrupt will not be generated to Host-proc ( Or client-proc).

Note for mailbox user:
On the Client-proc, mailbox_user can either block on mbox_send using MBOX_SEND_FLAG_BLOCK,
OR
mailbox_drv on Client-proc return error "mbox_not_ready" to mailbox_user if previous write was not read by Host.
So we allow only one 32-bit message to be in-flight.

*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include "mbox_internal.h"
#include "mbox_cfg.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
typedef struct mbox_ipc_channel
{
  uint8                       remote_id;
  char                        name[MBOX_CH_NAME_LEN];
  uint8                       tx_ch_id;
  uint8                       rx_ch_id;
  const void                 *priv;
  mbox_ipc_rx_notification_cb notify_rx;
  
  MBOX_LINK(struct mbox_ipc_channel, link);
} mbox_ipc_channel_type;

/*=============================================================================
                       LOCAL DATA DECLARATIONS
=============================================================================*/
static MBOX_LIST(mbox_ipc_channel_type, mbox_ipc_channel_tbl)[MBOX_NUM_REMOTES];
static mbox_os_mutex_type mbox_ipc_cmn_mutex;

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/
const char* mbox_ipc_remote_subsystems[MBOX_NUM_REMOTES] = 
{
  "pdp0",
  "pdp1",
  "pdp2",
  "cpucp"
};

/*=============================================================================

                     LOCAL FUNCTION DEFINATION
                     
=============================================================================*/

/*=============================================================================
  FUNCTION  mbox_ipc_remote_id_from_addr
=============================================================================*/
static mbox_status_type mbox_ipc_remote_id_from_addr
(
  UINT64          address,
  mbox_dir_type   dir,  
  uint8           *remote_id
)
{
  uint8 id;
  id = mbox_cfg_get_remote_id_from_addr(address, dir);
  if(id == MBOX_INVALID_REM_ID)
  {
	return MBOX_STATUS_INVALID_PARAM;
  }
  
  *remote_id = id;
  return MBOX_IPC_STATUS_SUCCESS;
}

/*=============================================================================
  FUNCTION  mbox_ipc_remote_id_from_name
=============================================================================*/
static mbox_status_type mbox_ipc_remote_id_from_name
(
  const char *remote_ss,
  uint8      *remote_id
)
{
  uint8 idx;
  
  if (!remote_ss)
  {
    return MBOX_STATUS_INVALID_PARAM;
  }

  for (idx = 0; idx < MBOX_NUM_REMOTES; idx++)
  {
    if (!mbox_os_string_compare(remote_ss, mbox_ipc_remote_subsystems[idx]))
    {
      *remote_id = idx;
      return MBOX_STATUS_SUCCESS;
    }
  }

  return MBOX_STATUS_INVALID_PARAM;
}

/*=============================================================================
  FUNCTION  mbox_ipc_ch_id_from_addr
=============================================================================*/
static mbox_status_type mbox_ipc_ch_id_from_addr
(
  UINT64          address,
  uint8           remote_id,
  mbox_dir_type   dir,
  uint8           *ch_id
)
{
  uint8 id;
  id = mbox_cfg_get_ch_id_from_addr(address, dir, remote_id);
  if(id == MBOX_INVALID_CH_ID)
  {
	return MBOX_IPC_STATUS_INVALID_CH;
  }
  
  *ch_id = id;

  return MBOX_STATUS_SUCCESS;
}

/*=============================================================================
  FUNCTION  mbox_ipc_ch_id_from_name
=============================================================================*/
static mbox_status_type mbox_ipc_ch_id_from_name
(
  uint8      remote_id,
  const char *ch_name,
  uint8      *tx_ch_id,
  uint8      *rx_ch_id
)
{
  uint8 idx;
  
  if ((!ch_name) || (remote_id >= MBOX_NUM_REMOTES))
  {
    return MBOX_STATUS_INVALID_PARAM;
  }
  
  for (idx = 0; idx < MBOX_IPC_NUM_CHS; idx++)
  {
    if (mbox_ipc_channels[remote_id][idx].ch_name == NULL)
    {
      continue;
    }
    
    if (!mbox_os_string_compare(ch_name, (mbox_ipc_channels[remote_id][idx]).ch_name))
    {
      *tx_ch_id = (mbox_ipc_channels[remote_id][idx]).tx_ch_id;
	  *rx_ch_id = (mbox_ipc_channels[remote_id][idx]).rx_ch_id;
      return MBOX_STATUS_SUCCESS;
    }
  }

  return MBOX_STATUS_INVALID_CH;
}

/*=============================================================================

                     GLOBAL FUNCTION DEFINATION
                     
=============================================================================*/

INT32 mbox_test_init();

/*=============================================================================
  FUNCTION  mbox_ipc_init
=============================================================================*/
mbox_status_type mbox_ipc_init(void)
{
  mbox_status_type status = MBOX_STATUS_SUCCESS;
  
  MBOX_OS_LOG_DBG("mbox_ipc_init: started status:%d", status);
  
  mbox_os_init();
  mbox_os_mutex_init(&mbox_ipc_cmn_mutex);
  
  status = mbox_drv_init();
  if (status != MBOX_STATUS_SUCCESS)
  {
    return status;
  }

  MBOX_OS_LOG_DBG("mbox_ipc_init: completed status:%d", status);
  //mbox_test_init();
  
  return MBOX_STATUS_SUCCESS;
}

/*=============================================================================
  FUNCTION  mbox_ipc_open
=============================================================================*/
mbox_status_type mbox_ipc_open
(
  mbox_ipc_open_config_type *open_cfg,
  mbox_ipc_handle_type      *handle
)
{
  mbox_ipc_channel_type *ch_ctx = NULL;
  mbox_status_type      status = MBOX_STATUS_SUCCESS;
  uint8                 remote_id;
  uint8                 tx_ch_id;
  uint8                 rx_ch_id;
  
  if ((open_cfg == NULL) ||
      (handle   == NULL))
  {
    MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! invalid args open_cfg:0x%X, handle:0x%X", open_cfg, handle);
    return MBOX_STATUS_INVALID_PARAM;
  }
 
  // get remote ss from send_address
  if(open_cfg->send_address)
  {
    status = mbox_ipc_remote_id_from_addr(open_cfg->send_address, MBOX_DIR_TX, &remote_id);
	if(status != MBOX_STATUS_SUCCESS)
	{
	  MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! No remote_id found for send_address :0x%X.", open_cfg->send_address);
	  return status;
	}
  }
  else if(open_cfg->receive_address)
  {
    status = mbox_ipc_remote_id_from_addr(open_cfg->receive_address, MBOX_DIR_RX, &remote_id);
	if(status != MBOX_STATUS_SUCCESS)
	{
	  MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! No remote_id found for recv_address :0x%X.", open_cfg->receive_address);
	  return status;
	}
  }
  else
  {
    status = mbox_ipc_remote_id_from_name(open_cfg->remote_ss, &remote_id);
    if (status != MBOX_STATUS_SUCCESS)
    {
      MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! invalid remote_ss:%s.", open_cfg->remote_ss);
      return status;
    }
  }
  
  mbox_os_mutex_acquire(&mbox_ipc_cmn_mutex);

  MBOX_LIST_FIND(mbox_ipc_channel_tbl[remote_id], ch_ctx, link, !mbox_os_string_compare(open_cfg->name, ch_ctx->name));
  if (ch_ctx)
  {
    MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! channel already opened remote_ss:%s, ch_name:%s", 
            open_cfg->remote_ss, open_cfg->name);
    mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
    return MBOX_STATUS_INVALID_CH;
  }
  
  ch_ctx = mbox_os_calloc(sizeof(mbox_ipc_channel_type));
  if (ch_ctx == NULL)
  {
    mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
    return MBOX_STATUS_MEM_FAILURE;
  }
  
  // get channel id from send_address/recv_address
  if((open_cfg->send_address != 0) || (open_cfg->receive_address != 0))
  {
    if(open_cfg->send_address)
    {
      status = mbox_ipc_ch_id_from_addr(open_cfg->send_address, remote_id, MBOX_DIR_TX, &tx_ch_id);
      if (status != MBOX_STATUS_SUCCESS)
      {
        MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! No tx_ch_id found for send_address :0x%X.", open_cfg->send_address);
        mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
    	return status;
      }
	}
	else
	{
	  tx_ch_id = MBOX_INVALID_CH_ID;
	}
	
	if(open_cfg->receive_address)
	{
      status = mbox_ipc_ch_id_from_addr(open_cfg->receive_address, remote_id, MBOX_DIR_RX, &rx_ch_id);
      if (status != MBOX_STATUS_SUCCESS)
      {
        MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! No rx_ch_id found for receive_address :0x%X.", open_cfg->receive_address);
        mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
    	return status;
      }
	}
	else
	{
	  rx_ch_id = MBOX_INVALID_CH_ID;
	}
  }
  else
  {
    status = mbox_ipc_ch_id_from_name(remote_id, open_cfg->name, &tx_ch_id, &rx_ch_id);
    if (status != MBOX_STATUS_SUCCESS)
    {
      MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! invalid ch_name:%s.", open_cfg->name);
      mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
  	  return status;
    }
  }
  
  MBOX_LINK_INIT(ch_ctx->link);
  ch_ctx->remote_id = remote_id;
  ch_ctx->tx_ch_id  = tx_ch_id;
  ch_ctx->rx_ch_id  = rx_ch_id;
  ch_ctx->notify_rx = open_cfg->notify_rx;
  ch_ctx->priv      = open_cfg->priv;
  mbox_os_string_copy(ch_ctx->name, open_cfg->name, sizeof(ch_ctx->name));
  
  *handle = (mbox_ipc_handle_type)ch_ctx;
  
  MBOX_LIST_ADD(mbox_ipc_channel_tbl[remote_id], ch_ctx, link);
  
  if(rx_ch_id != MBOX_INVALID_CH_ID)
  {
    status = mbox_drv_ch_enable(remote_id, rx_ch_id);
    if (status != MBOX_STATUS_SUCCESS)
    {
      MBOX_OS_LOG_ERR("mbox_ipc_open: Channel open failed! channel enable failed remote_ss:%s, ch_name:%s", 
              open_cfg->remote_ss, open_cfg->name);
      *handle = (mbox_ipc_handle_type)0;
      MBOX_LIST_REMOVE(mbox_ipc_channel_tbl[remote_id], ch_ctx, link);
      mbox_os_free(ch_ctx);
    }
  }
  mbox_os_mutex_release(&mbox_ipc_cmn_mutex);

  MBOX_OS_LOG_DBG("mbox_ipc_open: Complete Remote_id:%d, tx_ch_id:%d, rx_ch_id:%d, status:%d", remote_id, tx_ch_id, rx_ch_id, status);
  
  return status;
}

/*=============================================================================
  FUNCTION  mbox_ipc_close
=============================================================================*/
mbox_status_type mbox_ipc_close
(
  mbox_ipc_handle_type handle
)
{
  mbox_ipc_channel_type *ch_ctx = (mbox_ipc_channel_type*)handle;
  mbox_ipc_channel_type *temp_ch_ctx = NULL;
  
  if ((ch_ctx == NULL) || 
      (ch_ctx->remote_id >= MBOX_NUM_REMOTES))
  {
    return MBOX_STATUS_INVALID_PARAM;
  }
  
  MBOX_OS_LOG_DBG("mbox_ipc_close: Remote_id:%d tx_ch_id:%d rx_ch_id:%d.", 
                ch_ctx->remote_id, ch_ctx->tx_ch_id, ch_ctx->rx_ch_id);

  mbox_os_mutex_acquire(&mbox_ipc_cmn_mutex);
  
  MBOX_LIST_FIND(mbox_ipc_channel_tbl[ch_ctx->remote_id], temp_ch_ctx, link, \
			!mbox_os_string_compare(temp_ch_ctx->name, ch_ctx->name));

  if (temp_ch_ctx == NULL)
  {
    mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
    return MBOX_STATUS_INVALID_CH;
  }
  
  mbox_drv_ch_disable(ch_ctx->remote_id, ch_ctx->rx_ch_id);
  MBOX_LIST_REMOVE(mbox_ipc_channel_tbl[ch_ctx->remote_id], ch_ctx, link);
  mbox_os_free(ch_ctx);
  
  mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
  
  return MBOX_STATUS_SUCCESS;
}

/*=============================================================================
  FUNCTION  mbox_ipc_send
=============================================================================*/
mbox_status_type mbox_ipc_send
(
  mbox_ipc_handle_type handle, 
  const void           *pkt_priv, 
  uint32               message, 
  uint16               len, 
  uint32               options
)
{
  mbox_ipc_channel_type *ch_ctx = (mbox_ipc_channel_type*)handle;

  if ((ch_ctx == NULL) || 
      (ch_ctx->remote_id >= MBOX_NUM_REMOTES) ||
	  (ch_ctx->tx_ch_id == MBOX_INVALID_CH_ID) ||
	  (ch_ctx->tx_ch_id >= MBOX_IPC_NUM_TX_CHS))
  {
    MBOX_OS_LOG_ERR("mbox_ipc_send failed.",0);
    return MBOX_STATUS_INVALID_PARAM;
  }

  MBOX_OS_LOG_DBG("mbox_ipc_send: Remote_id:%d tx_ch_id:%d, message:0x%X", 
                ch_ctx->remote_id, ch_ctx->tx_ch_id, message);

  /* Due to H/W bug, write only 32-bit message */
  return mbox_drv_ch_tx(ch_ctx->remote_id, ch_ctx->tx_ch_id, message);
}

/*=============================================================================
  FUNCTION  mbox_ipc_ch_rx_cb
=============================================================================*/
void mbox_ipc_ch_rx_cb(uint8 remote_id, uint8 rx_ch_id, uint32 message)
{
  mbox_ipc_channel_type       *ch_ctx = NULL;
  mbox_ipc_rx_notification_cb notify_rx = NULL;
  const void                  *priv = NULL;
  
  if ((remote_id >= MBOX_NUM_REMOTES) || (rx_ch_id >= MBOX_IPC_NUM_RX_CHS))
  {
    MBOX_OS_LOG_ERR("mbox_ipc_ch_rx_cb: Remote_id:%d rx_ch_id:%d", remote_id, rx_ch_id);	  
	return;
  }
  
  MBOX_OS_LOG_DBG("mbox_ipc_ch_rx_cb: Remote_id:%d rx_ch_id:%d, message:0x%X", remote_id, rx_ch_id, message);

  mbox_os_mutex_acquire(&mbox_ipc_cmn_mutex);
  
  if(rx_ch_id == MBOX_INVALID_CH_ID)
  {
	mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
	return;
  }
  
  MBOX_LIST_FIND(mbox_ipc_channel_tbl[remote_id], ch_ctx, link, ch_ctx->rx_ch_id == rx_ch_id);
  
  if (ch_ctx)
  {
    notify_rx = ch_ctx->notify_rx;
    priv = ch_ctx->priv;
  }

  mbox_os_mutex_release(&mbox_ipc_cmn_mutex);
  
  if (ch_ctx && notify_rx)
  {
    notify_rx((mbox_ipc_handle_type)ch_ctx, priv, message, sizeof(message));
  }
}

/*=============================================================================
  FUNCTION  mbox_ipc_ch_status
=============================================================================*/
UINT32 mbox_ipc_ch_status(mbox_ipc_handle_type handle)
{
  /* Not implemented due to H/W bug */
  return MBOX_IPC_STATUS_SUCCESS;
}

/*=============================================================================
  FUNCTION  mbox_ipc_rx_done
=============================================================================*/
mbox_ipc_err_type mbox_ipc_rx_done(mbox_ipc_handle_type handle, mbox_message message)
{
  /* Check validity of handle , if not return invalid handle.

  In handle, check the message in corresponding command-register.

  If it matches message, set the ready to receive bit to 1 and return success.

  If no match, return error invalid param. */

  return MBOX_IPC_STATUS_SUCCESS;

}
