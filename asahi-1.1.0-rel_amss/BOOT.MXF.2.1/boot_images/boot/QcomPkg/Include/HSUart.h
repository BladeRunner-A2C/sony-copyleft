#ifndef __HSUART_H__
#define __HSUART_H__
/*==================================================================================================

FILE: HSUart.h

DESCRIPTION: UEFI driver for HS-UARTDM/UARTBAM

  Copyright 2023 Qualcomm Technologies, Inc. All rights reserved

==================================================================================================*/
#include "hsuart_common.h"
/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

RETURN_STATUS EFIAPI hsuart_deinitialize(void);
RETURN_STATUS EFIAPI hsuart_initialize(void);
BOOLEAN       EFIAPI hsuart_poll(void);
UINTN         EFIAPI hsuart_read(OUT UINT8 *user_buffer, IN UINTN bytes_requested);
UINTN         EFIAPI hsuart_write(IN UINT8 *user_buffer, IN UINTN bytes_to_send);
BOOLEAN       EFIAPI hsuart_is_cable_connected(void);
BOOLEAN       EFIAPI hsuart_power_off(void);
BOOLEAN       EFIAPI hsuart_power_on(void);
RETURN_STATUS EFIAPI hsuart_set_baudrate(IN UINTN baud_rate);
/* New set of APIs to support hsuart_handle for AU */
RETURN_STATUS EFIAPI hsuart_deinitialize_ex(void *hsuart_handle);
RETURN_STATUS EFIAPI hsuart_initialize_ex(hsuart_instance instance, hsuart_open_config *config, void **hsuart_handle);
BOOLEAN       EFIAPI hsuart_poll_ex(void *hsuart_handle);
UINTN         EFIAPI hsuart_read_ex(void *hsuart_handle, OUT UINT8 *user_buffer, IN UINTN bytes_requested);
UINTN         EFIAPI hsuart_write_ex(void *hsuart_handle, IN UINT8 *user_buffer, IN UINTN bytes_to_send);
BOOLEAN       EFIAPI hsuart_is_cable_connected_ex(void *hsuart_handle);
BOOLEAN       EFIAPI hsuart_power_off_ex(void *hsuart_handle);
BOOLEAN       EFIAPI hsuart_power_on_ex(void *hsuart_handle);
RETURN_STATUS EFIAPI hsuart_set_baudrate_ex(void *hsuart_handle, IN UINTN baud_rate);
#endif  // __HSUART_H__

