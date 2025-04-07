/*===========================================================================

  Mailbox IPC test implementation


 Copyright (c) 2022 by QUALCOMM Technologies, Incorporated.  
 All Rights Reserved.
===========================================================================*/

/*
Mailbox test source.
Exercise mailbox IPC APIs for dev-test
*/

#include "mboxipc_common.h" /* For mailbox APIs */
#include "mbox_os_utils.h"
/* Test channel name. This has to be pre-defined and is shared between the mailbox driver code in the two 
subsystems that need to communicate, for e.g. UEFI and PDP0 */
#define TEST_CH_NAME "test12" 
#define TEST_CH_NAME_1 "test22" 
#define NUM_TEST_REMOTES 2

void mbox_test_rx_cb(mbox_ipc_handle_type handle, const void *priv, mbox_message message, UINT16 size);

typedef struct 
{
  mbox_ipc_handle_type test_ipc_handle;
  mbox_message test_send_data;
  mbox_message test_recv_data;
  UINT16 test_send_count;
  UINT16 test_recv_count;
  UINT16 test_recv_size;
}mbox_ipc_test_ctx_type;

static UINT32 test_err_cnt = 0;
static mbox_ipc_test_ctx_type *mbox_ipc_test_ctx = NULL;


INT32 mbox_test_init()
{
  mbox_ipc_err_type err = MBOX_IPC_STATUS_FAILURE;
  int idx = 0, loop_idx = 0;
  mbox_ipc_open_config_type test_open_cfg[NUM_TEST_REMOTES];
  
  MBOX_OS_LOG_DBG("mbox_test_init: Start remotes:%d", NUM_TEST_REMOTES);
  
  mbox_ipc_test_ctx = (mbox_ipc_test_ctx_type*)(mbox_os_calloc(sizeof(mbox_ipc_test_ctx_type) * NUM_TEST_REMOTES));
  if(!mbox_ipc_test_ctx)
  {
  MBOX_OS_LOG_ERR("mbox_test_init: mbox_os_calloc failed %d", NUM_TEST_REMOTES);
  return -1;
  }
  
  
  mbox_ipc_test_ctx[0].test_send_data = 1; /*this can increment on each send to track message integrity along with test_send_count*/
  mbox_ipc_test_ctx[1].test_send_data = 1; /*this can increment on each send to track message integrity along with test_send_count*/
 
/* Initialize channel open configurations */
  MBOX_IPC_OPEN_CONFIG_INIT(test_open_cfg[0]);
  MBOX_IPC_OPEN_CONFIG_INIT(test_open_cfg[1]);
  //test_open_cfg[0].remote_ss = "pdp0";
  test_open_cfg[1].send_address =  0x1A980180; //16TH REG FAIL
  test_open_cfg[1].receive_address = 0x17420108;
  //test_open_cfg[1].remote_ss = "pdp0";
  test_open_cfg[0].name = TEST_CH_NAME;
  test_open_cfg[1].name = TEST_CH_NAME_1;
  test_open_cfg[0].send_address = 0x1B980178; //15TH PASS
  test_open_cfg[0].receive_address = 0x174202F8;//63RD REG PASS
  
  for(loop_idx = 0; loop_idx < 5; loop_idx++)
  {
    for(idx = 0; idx<NUM_TEST_REMOTES; idx++)
    {
      
      test_open_cfg[idx].options = 0;
      test_open_cfg[idx].notify_rx = mbox_test_rx_cb;
      test_open_cfg[idx].send_timeout = 0;
      test_open_cfg[idx].priv = (void*)&(mbox_ipc_test_ctx[idx]);
      
       /* Open the channel */
      err = mbox_ipc_open(&test_open_cfg[idx], &(mbox_ipc_test_ctx[idx].test_ipc_handle));
      if(err != MBOX_IPC_STATUS_SUCCESS)
      {
        MBOX_OS_LOG_ERR("mbox_test_init: mbox_ipc_open failed err = (0x%x)", err);
        return err;
      }
      MBOX_OS_LOG_DBG("mbox_test_init: mbox_ipc_open success for idx %d", idx);
      
      /* Make sure the channel is ready to receive some data. Wait until ready to receive. 
      No handshake due to H/W bug */
      //err = MBOX_IPC_STATUS_CH_NOT_READY_FOR_TX; 
      // while(err == MBOX_IPC_STATUS_CH_NOT_READY_FOR_TX)
      // {
        // err = mbox_ipc_ch_status(mbox_ipc_test_ctx->test_ipc_handle);
        // /* Wait 5 seconds and allow other side to open the channel and be ready to receive data */
       // Wait(5);
      // }
        
      /* send some data */
      err = mbox_ipc_send(mbox_ipc_test_ctx[idx].test_ipc_handle, /* handle obtained from mbox_ipc_open */
                NULL, /*we don't need packet-specific private data */
                mbox_ipc_test_ctx[idx].test_send_data++, 
                0, /* we're sending a control message, no data in any shared memory */ 
                0);
                
      if(err != MBOX_IPC_STATUS_SUCCESS)
      {
      MBOX_OS_LOG_ERR("mbox_test_init: mbox_ipc_send failed for idx %d err = (0x%x)", idx, err);
      return err;
      }
      mbox_ipc_test_ctx[idx].test_send_count++;
      MBOX_OS_LOG_DBG("mbox_test_init: mbox_ipc_send success from test client for idx %d", idx);
    }
  }
  /* Wait for 5 seconds to receive a message */
  //Wait(5);
  
  /* If no message was received, print an error message */
  // if(mbox_ipc_test_ctx->test_recv_count == 0)
  // {
  // //printf("No message received");
  // return -1;
  // }
  // /* Close the channel */
  // err = mbox_ipc_close(mbox_ipc_test_ctx->test_ipc_handle);
  // if(err != MBOX_IPC_STATUS_SUCCESS)
  // {
// // printf("Error closing channel, %d",err);
  // return -1;
  // }
  
  MBOX_OS_LOG_DBG("mbox_test_init: Exiting test client err:%d", err);
  return 0;
}

void mbox_test_rx_cb(mbox_ipc_handle_type handle, const void *priv, mbox_message message, UINT16 size)
{
  
  mbox_ipc_test_ctx_type* ctx = (mbox_ipc_test_ctx_type*)priv;
  if(!ctx)
  return;

  MBOX_OS_LOG_DBG("mbox_test_rx_cb: message:0x%x", message);
  ctx->test_recv_count++;
  ctx->test_recv_data = message;
  ctx->test_recv_size = size;

/* We're done with the message. Call rx_done */
  if(mbox_ipc_rx_done(handle, message) != MBOX_IPC_STATUS_SUCCESS)
    test_err_cnt++;
}
