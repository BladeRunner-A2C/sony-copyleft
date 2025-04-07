/**************************************************************************
 * FILE: devprg_transport_pcie.c
 *
 * PCIE abstraction layer for TX and RX.
 *
 * Copyright (c) 2018, 2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 *************************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/5.1/QcomPkg/Library/DevPrgLib/devprg_transport_pcie.c#1 $
  $DateTime: 2021/02/25 15:01:58 $
  $Author: pwbldsvc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2023-01-09   gml   Added Pinnacles DevPrg PCIe support
2021-02-21   sa    Ported to Olympic.
2018-11-08   eo   Create.

===========================================================================*/

#include "comdef.h"

#include "devprg_firehose.h"
#include "devprg_log.h"
#include "devprg_transport_pcie.h"
#include "devprg_transport.h"


#include "mhi.h"

/* MHI Channel numbers for RX and TX  */
#define FIREHOSE_RX 34
#define FIREHOSE_TX 35

/* This cannot be bigger as SAHARA packets cannot be bigger than 512 */
#define MHI_MAX_PACKET_SIZE 512

/* MAX Data size. This can be unlimited, for now 1 MB */
#define MHI_MAX_RAW_DATA_SIZE 0x100000

/* Indicates if SAHARA channel is successfully opened */ 
static boolean mhi_up=FALSE;

/* Indicates if a fatal error occurred */
static uint32 fatal_error=0; 

dp_res_t devprg_transport_pcie_set_mode(enum devprg_transport_mode_key key, 
                                                  unsigned int val)
{
  return DEVPRG_SUCCESS;
}

/* Three variables to communicate information from the callback, */
struct devprg_pcie_cb_data
{
  uint32 error;
  uint32 bytes;
  uint8 called;
};


static struct devprg_pcie_cb_data pcie_cb_tx_data, pcie_cb_rx_data;

/** 
 * @brief      mhi_booti_rw_cb
 *
 *             Callback function used to receive channel request completions from MHI Core
 *              
 * 
 * @param[in]  status - Indicates status of operation
 *
 * @dependencies
 *             None
 *              
 * 
 * @return       
 *             None
 * 
 * @sideeffect None 
 */
void devprg_mhi_rw_cb(mhi_return_t status)
{


   switch(status.op)
   {
      case MHI_READ:
      case MHI_READ_NULL:
          /* Check if a fatal error occurred that we couldn't handle. Return the error code as part of the cb */
          if(fatal_error)
              pcie_cb_rx_data.error = DEVPRG_ERROR_ACCESS_DENIED;
          else 
          {
              if(status.status != MHI_SUCCESS)
                  pcie_cb_rx_data.error = DEVPRG_ERROR_RECEIVE;
              else
                  pcie_cb_rx_data.error=DEVPRG_SUCCESS;
          }
          pcie_cb_rx_data.bytes = status.payload.rw.bytesRW;
          pcie_cb_rx_data.called = 1; 
          break;
      case MHI_WRITE:
          if(fatal_error)
              pcie_cb_rx_data.error = DEVPRG_ERROR_ACCESS_DENIED;
          else 
          {
              if(status.status != MHI_SUCCESS)
                  pcie_cb_tx_data.error = DEVPRG_ERROR_TRANSMIT;
              else
                  pcie_cb_tx_data.error=DEVPRG_SUCCESS;
          }
         pcie_cb_tx_data.bytes = status.payload.rw.bytesRW;
         pcie_cb_tx_data.called = 1; 
         break;
      default:
         /* Should not get an unknown operation. Mark the global fatal error flag */
         fatal_error=1; 
   }

   return; 
}

void devprg_mhi_poll()
{
    if (mhi_up != TRUE)
       return; 

    /* Trigger PCIE driver polling */
    mhi_poll(); 

    return;
}

dp_res_t devprg_transport_pcie_rx_queue(void *data, size_t size)
{
    uint32 bytesRead=0; 
    mhi_cb_t cb; 
    mhi_status_t status;  

    /* Check that MHI is enumerated  */
    if (mhi_up != TRUE)
    {
       return DEVPRG_ERROR_NOT_INIT;
    }

    /* Check if a fatal error occured if so return error so it can get caught */
    if(fatal_error)
    {
       return DEVPRG_ERROR_NOT_READY;
    }

    /* Prepare the cb data if we are doing an async request */
    pcie_cb_rx_data.error = DEVPRG_SUCCESS;
    pcie_cb_rx_data.bytes = 0;
    pcie_cb_rx_data.called = 0;

    cb.cbFunc=devprg_mhi_rw_cb; 
    cb.userData=(void*)&pcie_cb_rx_data; 

    status = mhi_channel_read(FIREHOSE_RX, data, size, &bytesRead, &cb);
    
    if ((MHI_SUCCESS != status && MHI_PENDING != status))
    {
        return DEVPRG_ERROR_RECEIVE;
    }
    return DEVPRG_SUCCESS;
}

dp_res_t devprg_transport_pcie_rx_queue_check(size_t *rx_num_bytes)
{
  *rx_num_bytes = 0;
  if(pcie_cb_rx_data.called == 0)
    devprg_mhi_poll();

  if(pcie_cb_rx_data.called == 0)
    return DEVPRG_ERROR_NOT_READY;

  if(pcie_cb_rx_data.error != DEVPRG_SUCCESS)
  {
    DP_LOGE("PCIE RX failed on callback %d", pcie_cb_rx_data.error);
    return DEVPRG_ERROR_RECEIVE;
  }

  *rx_num_bytes = pcie_cb_rx_data.bytes;
  return DEVPRG_SUCCESS;
}

dp_res_t devprg_transport_pcie_tx_queue(void *data, size_t size)
{
  mhi_cb_t cb;
  uint32 bytesWritten=0;
  mhi_status_t status; 

  if (mhi_up != TRUE)
  {
      return DEVPRG_ERROR_NOT_INIT;
  }

  /* Check if a fatal error occurred if so return error so it can get caught */
  if(fatal_error)
  {
      return DEVPRG_ERROR_ACCESS_DENIED;
  }

  pcie_cb_tx_data.error = DEVPRG_SUCCESS;
  pcie_cb_tx_data.bytes = 0;
  pcie_cb_tx_data.called = 0;

  cb.cbFunc=devprg_mhi_rw_cb; 
  cb.userData=(void*)&pcie_cb_tx_data;

  status = mhi_channel_write(FIREHOSE_TX, (void*)data, size, &bytesWritten, &cb);
  if (MHI_SUCCESS != status && MHI_PENDING != status )
  {
     return DEVPRG_ERROR_TRANSMIT;
  }

  return DEVPRG_SUCCESS; 
}

dp_res_t devprg_transport_pcie_tx_queue_check(size_t size)
{
  if (pcie_cb_tx_data.called == 0)
    devprg_mhi_poll();

  if (pcie_cb_tx_data.called == 0)
    return DEVPRG_ERROR_NOT_READY;

  if (pcie_cb_tx_data.error != DEVPRG_SUCCESS || pcie_cb_tx_data.bytes != size)
    return DEVPRG_ERROR_TRANSMIT;

  return DEVPRG_SUCCESS;
}

int devprg_transport_pcie_async_support(void)
{
  return 1;
}

static devprg_transport_ops devprg_transport_pcie_ops =
{
  devprg_transport_pcie_set_mode,
  devprg_transport_pcie_rx_queue,
  devprg_transport_pcie_rx_queue_check,
  devprg_transport_pcie_tx_queue,
  devprg_transport_pcie_tx_queue_check,
  devprg_transport_pcie_async_support,
};

static struct devprg_transport devprg_transport_pcie =
{
  DEVPRG_TRANSPORT_PCIE,
  &devprg_transport_pcie_ops
};

mhi_status_t status_open;

struct devprg_transport *devprg_transport_pcie_init(void)
{
   /* Call MHI Init */
  status_open = mhi_init();
  if (MHI_SUCCESS != status_open)
     return NULL;

   /* Open the channels. This could block if host did not enumerate MHI yet */
   if( MHI_SUCCESS != mhi_channel_open(FIREHOSE_RX, NULL))
   {
      return NULL;
   }

   if( MHI_SUCCESS != mhi_channel_open(FIREHOSE_TX, NULL))
   {
      return NULL; 
   }

   mhi_up=TRUE; 

  return &devprg_transport_pcie;
}

