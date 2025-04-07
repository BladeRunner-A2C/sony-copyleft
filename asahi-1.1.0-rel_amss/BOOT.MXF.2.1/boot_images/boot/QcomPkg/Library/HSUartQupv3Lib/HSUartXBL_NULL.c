/*==================================================================================================

FILE: HSUartXBL_NULL.c

DESCRIPTION: This module provides the driver Software for the UART.

Copyright (c) 2022-2023 Qualcomm Technologies, Inc.
        All Rights Reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                            DESCRIPTION
====================================================================================================

GLOBAL FUNCTIONS:
   hsuart_close
   hsuart_deinitialize
   hsuart_initialize
   hsuart_open
   hsuart_poll
   hsuart_receive
   hsuart_read
   hsuart_transmit
   hsuart_write

==================================================================================================*/
/*==================================================================================================
Edit History


when       who     what, where, why
--------   ---     --------------------------------------------------------
05/10/23   MG     Created


==================================================================================================*/

/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "HSUart.h"
#include "HSUartApi.h"
#include "HSUartDefs.h"
#include "HSUartOs.h"
#include "HSUartHal.h"
//#include "HSUartHwio.h"
#include "HSUartLog.h"
#include "HSUartFWLoad.h"
#include <Uefi.h>

/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                          LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                               MACROS
==================================================================================================*/


/*==================================================================================================
                                     LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================

FUNCTION: hsuart_close

DESCRIPTION:

==================================================================================================*/
hsuart_result hsuart_close(hsuart_handle h)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_open

DESCRIPTION:

==================================================================================================*/
hsuart_result hsuart_open(hsuart_handle* h, hsuart_instance id, hsuart_open_config* config)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}


/*==================================================================================================

FUNCTION: hsuart_isr

DESCRIPTION:

==================================================================================================*/

/*==================================================================================================

FUNCTION: hsuart_receive

DESCRIPTION:

==================================================================================================*/
hsuart_result hsuart_receive(hsuart_handle h, char* buf, uint32 buf_size, void* cb_data)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}


/*==================================================================================================

FUNCTION: hsuart_transmit

DESCRIPTION:

==================================================================================================*/
hsuart_result hsuart_transmit(hsuart_handle h, char* buf, uint32 bytes_to_tx, void* cb_data)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_deinitialize

DESCRIPTION:

==================================================================================================*/
RETURN_STATUS EFIAPI
hsuart_deinitialize(void)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_deinitialize_ex

DESCRIPTION:

==================================================================================================*/
RETURN_STATUS EFIAPI
hsuart_deinitialize_ex(void *hsuart_handle)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_initialize

DESCRIPTION:

==================================================================================================*/
RETURN_STATUS EFIAPI
hsuart_initialize(void)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_initialize_ex

DESCRIPTION:

==================================================================================================*/
RETURN_STATUS EFIAPI
hsuart_initialize_ex(hsuart_instance instance, hsuart_open_config *config, void **hsuart_handle)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================
FUNCTION: hsuart_poll

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
hsuart_poll(void)
{
   return FALSE;
}

/*==================================================================================================

FUNCTION: hsuart_poll_ex

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
hsuart_poll_ex(void *hsuart_handle)
{
   return FALSE;
}

/*==================================================================================================

FUNCTION: hsuart_read

DESCRIPTION:

==================================================================================================*/
UINTN EFIAPI
hsuart_read(OUT UINT8 *user_buffer, IN UINTN bytes_requested)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_read_ex

DESCRIPTION:

==================================================================================================*/
UINTN EFIAPI
hsuart_read_ex(void *hsuart_handle, OUT UINT8 *user_buffer, IN UINTN bytes_requested)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_write

DESCRIPTION:

==================================================================================================*/
UINTN EFIAPI
hsuart_write(IN UINT8 *user_buffer, IN UINTN bytes_to_send)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_write_ex

DESCRIPTION:

==================================================================================================*/
UINTN EFIAPI
hsuart_write_ex(void *hsuart_handle, IN UINT8 *user_buffer, IN UINTN bytes_to_send)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_is_cable_connected

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
hsuart_is_cable_connected(void)
{
   return FALSE;
}

/*==================================================================================================

FUNCTION: hsuart_is_cable_connected_ex

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
hsuart_is_cable_connected_ex(void *hsuart_handle)
{
   return FALSE;
}

/*==================================================================================================

FUNCTION: hsuart_power_off

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
hsuart_power_off(void)
{
   return FALSE;
}

/*==================================================================================================
FUNCTION: hsuart_power_off_ex

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
hsuart_power_off_ex(void *hsuart_handle)
{
   return FALSE;
}

/*==================================================================================================

FUNCTION: hsuart_power_oon

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
hsuart_power_on(void)
{
   return FALSE;
}

/*==================================================================================================

FUNCTION: hsuart_power_on_ex

DESCRIPTION:

==================================================================================================*/
BOOLEAN EFIAPI
hsuart_power_on_ex(void *hsuart_handle)
{
   return FALSE;
}

/*==================================================================================================

FUNCTION: hsuart_get_clock_param

DESCRIPTION:

==================================================================================================*/

RETURN_STATUS EFIAPI
hsuart_set_baudrate(IN UINTN baud_rate)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

RETURN_STATUS EFIAPI
hsuart_set_baudrate_ex(void *hsuart_handle, IN UINTN baud_rate)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

/*==================================================================================================

FUNCTION: hsuart_set_baud_rate

DESCRIPTION:

==================================================================================================*/
hsuart_result hsuart_set_baud_rate(hsuart_handle h, uint32 baud_rate)
{
   return (hsuart_result) EFI_UNSUPPORTED;
}

