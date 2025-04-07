#ifndef UART_DEFS_H
#define UART_DEFS_H
/*==================================================================================================

FILE: UartDefs.h

DESCRIPTION: This module provides the driver software for the UART.

Copyright (c) 2016, 2022 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
Edit History

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/UartDefs.h#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
10/21/22   MP       Adde baud rate in Uart_Properties
11/7/16    VV       Initial revision

==================================================================================================*/
/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "UartApi.h"

typedef struct
{
   volatile uint32 uart_base;
   volatile uint32 qup_common_base;
   uint32 gpio_tx_config;
   uint32 gpio_rx_config;
   uint32 gpio_cts_config;
   uint32 gpio_rfr_config;
   uint32 clock_id_index;
   void*  bus_clock_id;
   void*  core_clock_id;
   char*  core_clock_str;
   uint32 base_freq;
   uint32 irq_num;
   uint32 tcsr_base;
   uint32 tcsr_offset;
   uint32 tcsr_value;
   uint32 baud_rate;
}UART_PROPERTIES;

typedef struct uart_context
{
   uint32               port_id;
   boolean              is_port_open;
   UART_PROPERTIES*     properties;
   uart_open_config     open_config;

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
}uart_context;

#endif
