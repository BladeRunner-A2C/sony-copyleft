#ifndef __HSUART_CONFIG_H__
#define __HSUART_CONFIG_H__


/*=============================================================================   
    @file  HSUART_config.h
    @brief interface to device configuration
   
    Copyright 2023 Qualcomm Technologies, Inc. All rights reserved

===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
01/05/23    RK      created
=============================================================================*/

#include "comdef.h"

typedef enum 
{
	UART_2W_PROTOCOL  = 2, //QUPv3 protocols as in FW register
	UART_4W_PROTOCOL = 18,
}uart_cfg_protocol;

typedef struct hsuart_plat_device_config
{
   volatile uint32      uart_base;
   volatile uint32      qup_common_base;
   uint8                core_index;
   uint8                se_index;
   uart_cfg_protocol    qupv3_protocol;
   uint32               gpio_tx_config;
   uint32               gpio_rx_config;
   uint32               gpio_cts_config;
   uint32               gpio_rfr_config;
   uint32               clock_id_index;
   uint8**              common_clock_id;
   uint8**              core_clock_id;
   uint32               base_freq;
   uint32               irq_num;
   uint32               tcsr_base;
   uint32               tcsr_offset;
   uint32               tcsr_value;
}hsuart_plat_device_config;

#endif
