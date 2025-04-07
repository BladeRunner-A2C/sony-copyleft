#ifndef HSUART_DEFS_H
#define HSUART_DEFS_H
/*==================================================================================================

FILE: HSUartDefs.h

DESCRIPTION: This module provides the driver software for the HS-UART.

Copyright (c) 2023 Qualcomm Technologies, Inc.
        All Rights Reserved.

==================================================================================================*/
/*==================================================================================================
Edit History


when       who     what, where, why
--------   ---     --------------------------------------------------------
01/05/23   RK      Initial revision

==================================================================================================*/
/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "HSUartApi.h"
#include "HSUART_config.h"

typedef struct hsuart_context
{
   uint32               port_id;
   boolean              is_port_open;
   hsuart_plat_device_config* properties;
   hsuart_open_config     open_config;

   char*                tx_buf;
   uint32               bytes_to_tx;
   uint32               bytes_txed;
   void*                tx_cb_data;
   volatile void*       tx_signal;


   char*                rx_buf;
   uint32               rx_write_offset;
   uint32               rx_buf_size;
   void*                rx_cb_data;

   void*                clock_handle;
   void*                tlmm_handle;
   void*                interrupt_context;
}hsuart_context;

#endif
