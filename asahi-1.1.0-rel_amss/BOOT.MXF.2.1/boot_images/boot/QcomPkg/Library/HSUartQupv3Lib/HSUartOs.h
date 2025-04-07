#ifndef HSUART_OS_H
#define HSUART_OS_H
/*==================================================================================================

FILE: HSUartOs.h

DESCRIPTION: This module provides the OS specific APIs to the UART driver software.

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
#include "HSUartDefs.h"


hsuart_result hsuart_clock_close(hsuart_context* h);
hsuart_result hsuart_clock_open(hsuart_context* h,uint32 input_freq);
hsuart_result hsuart_get_driver_properties(void);
hsuart_plat_device_config *hsuart_plat_get_device_config (uint8 core_index);
hsuart_result hsuart_interrupt_close(hsuart_context* h);
hsuart_result hsuart_interrupt_done(hsuart_context* h);
hsuart_result hsuart_interrupt_open(hsuart_context* h, void* isr);
hsuart_result hsuart_tlmm_open(hsuart_context* h);
hsuart_result hsuart_tlmm_close(hsuart_context* h);

#endif

