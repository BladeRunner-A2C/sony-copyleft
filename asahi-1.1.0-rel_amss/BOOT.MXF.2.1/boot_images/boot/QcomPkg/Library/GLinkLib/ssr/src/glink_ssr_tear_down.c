/*---------------------------------------------------------------------------
   GLINK_SSR_HANDOFF.C  - G-LINK SSR handoff Source File
---------------------------------------------------------------------------*/
/**
  @file glink_ssr_mgr.c

*/
/* This file contains implementation for the G-LINK SSR handoff for SSR master. */

/*--------------------------------------------------------------------------
Copyright (c) 2014, 2022, 2023  QUALCOMM Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary.
---------------------------------------------------------------------------*/

/*===========================================================================

                           EDIT HISTORY FOR FILE


when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/22/15   an      Initial revision
===========================================================================*/


/*===========================================================================

                        INCLUDE FILES

===========================================================================*/

#include <stdio.h>
#include "comdef.h"
#include "glink.h"
#include "glink_rpm.h"
#include "glink_ssr_type.h"
#include "glink_os_utils.h"

extern boolean glink_is_link_down(const char *remote_ss, const char *transport_name);
extern void glink_notify_link_down_to_clients(const char *remote_ss, const char *transport_name);
extern void glink_set_remote_down(const char *remote_ss, const char *transport_name);

extern glink_err_type glink_mask_interrupt
(
  const char*               remote_ss,
  const char*               xport,
  boolean                   mask
  
);
/*===========================================================================

                        MACRO DEFINITIONS

===========================================================================*/

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/


/*===========================================================================

                        LOCAL DATA DEFINITIONS

===========================================================================*/


/*===========================================================================

                        LOCAL FUNCTION DECLARATIONS

===========================================================================*/


/*===========================================================================

                        LOCAL FUNCTION DEFINITIONS

===========================================================================*/


/*===========================================================================

                        PUBLIC FUNCTION DEFINITIONS

===========================================================================*/

/*===========================================================================
  FUNCTION  glink_ssr_td_rxv_cb
  ===========================================================================*/
/**
  This function implements the callback to process RX notifications.
 
  @param[in]  handle       Pointer to the G-LINK channel handle.
  @param[in]  priv         Pointer to the channel's private data.
  @param[in]  pkt_priv     Pointer to the RX packet's private data.
  @param[in]  iovec        Pointer to the RX vector.
  @param[in]  size         RX buffer size.
  @param[in]  intent_used  Size of the intent used for this packet.
  @param[in]  vprovider    Buffer provider for virtual space.
  @param[in]  pprovider    Buffer provider for physical space.
 
  @return
  NA.

*/
/*=========================================================================*/
void glink_ssr_td_rxv_cb
(
  glink_handle_type  handle,
  const void        *priv,
  const void        *pkt_priv,
  void              *iovec,
  size_t             size,
  size_t             intent_used,
  glink_buffer_provider_fn vprovider,
  glink_buffer_provider_fn pprovider
)
{
}

/*===========================================================================
  FUNCTION  glink_ssr_td_tx_cb
  ===========================================================================*/
/**
  This function implements the callback to process TX notifications.
 
  @param[in]  handle       Pointer to the G-LINK channel handle.
  @param[in]  priv         Pointer to the channel's private data.
  @param[in]  pkt_priv     Pointer to the TX packet's private data.
  @param[in]  buffer       Pointer to the TX buffer.
  @param[in]  size         RX buffer size.
 
  @return
  NA.

*/
/*=========================================================================*/
void glink_ssr_td_tx_cb
(
  glink_handle_type  handle,
  const void        *priv,
  const void        *pkt_priv,
  const void        *buffer,
  size_t             size
)
{
}

/*===========================================================================
  FUNCTION  glink_ssr_td_state_cb
  ===========================================================================*/
/**
  This function implements the callback to process state change notifications.
 
  @param[in]  handle       Pointer to the G-LINK channel handle.
  @param[in]  priv         Pointer to the channel's private data.
  @param[in]  event        Channel state change event.
 
  @return
  NA.

*/
/*=========================================================================*/
void glink_ssr_td_state_cb
(
  glink_handle_type         handle,
  const void               *priv,
  glink_channel_event_type event
)
{
  glink_channel_event_type *channel_event = (glink_channel_event_type *)priv;
  
  *channel_event = event;
}



/*===========================================================================
  FUNCTION  glink_ssr_td_rx_sigs_cb
  ===========================================================================*/
/**
  This function implements the callback to process the notification of new
  intent queued.
 
  @param[in]  handle       Pointer to the G-LINK channel handle.
  @param[in]  priv         Pointer to the channel's private data.
  @param[in]  prev         Previous signals.
  @param[in]  curr         Current signals.
 
  @return
  NA.

*/
/*=========================================================================*/
void glink_ssr_td_rx_sigs_cb
(
  glink_handle_type         handle,
  const void               *priv,
  uint32                    prev,
  uint32                    curr
)
{
}

/*===========================================================================
  FUNCTION  glink_ssr_tear_down
  ===========================================================================*/
/**
  This function implements notifying remote_name of tear down so remote can clean up.
 
  @param[in]  remote_name       Name of remote sub-system.
  @param[in]  transport_name    Name of transport. Only "RPM" and "SMEM" are supported
 
  @return
  NA.

*/
/*=========================================================================*/
void glink_ssr_tear_down( const char *remote_name, const char *transport_name )
{
  glink_handle_type channel_handle = NULL;
  volatile glink_channel_event_type channel_event = GLINK_LOCAL_DISCONNECTED;
  const char channel_name[] = "glink_ssr";
  glink_err_type err = GLINK_STATUS_SUCCESS;
  boolean mask_interrupt = TRUE;
  glink_open_config_type channel_config = 
  {
    transport_name,
    remote_name,
    &channel_name[0],
    0,
    (const void*)&channel_event,
    NULL,
    NULL,
    &glink_ssr_td_rxv_cb,
    &glink_ssr_td_tx_cb,
    &glink_ssr_td_state_cb,
    NULL,
    NULL,
    &glink_ssr_td_rx_sigs_cb,
    NULL,
    NULL,
    0,
    NULL,
    NULL
  };
  glink_ssr_command_header_type cleanup_cmd = 
  {
    0,
    GLINK_SSR_COMMAND_CLEANUP,
    0,
    sizeof("apss"),
    "apss"
  };

  /* Deregistering/Masking the interrupt here, before switching to polling mode.
     Polling mode is used even though interrupts are processed in the boot exit path.
     Polling mode is needed to avoid a deadlock on the DxeLock (which is held before calling the GlinkExitBSCallback,
	 and also when glink_os_calloc is called to allocate an intent structure, from the xport ISR.
	 DxeLock is a recursive lock, so it is OK to be called recursively from the same thread.
  */
  err = glink_mask_interrupt(remote_name, transport_name, mask_interrupt);
  if(err != GLINK_STATUS_SUCCESS)
  {
	return;
  }
  
  if (glink_open(&channel_config, &channel_handle) != GLINK_STATUS_SUCCESS)
  {
    return;
  }

  /* Poll until channel is fully connected */
  while (channel_event != GLINK_CONNECTED)
  {
    glink_rx_poll(channel_handle);
  }
  
  //Set remote_down to TRUE
  glink_set_remote_down(remote_name, transport_name);

  /* Send cleanup command */
  err = glink_tx(channel_handle, NULL, &cleanup_cmd, sizeof(cleanup_cmd), GLINK_TX_REQ_INTENT|GLINK_TX_SINGLE_THREADED|GLINK_TX_FORCE_POLL);
  
  if(err != GLINK_STATUS_SUCCESS)
  {
	return;
  }
  
  /* Notify all clients with channel DISCONNECT event */
  glink_notify_link_down_to_clients(remote_name, transport_name);
  
  /* Wait for the link to be reset by remote */
  while (glink_is_link_down(remote_name, transport_name) != TRUE);
 
}
