/*=======================================================================*//**
 * @file        UsbSharedLoader.c
 * @author:     pmahajan
 * @date        03-feb-2017
 *
 * @brief       USB common & shared USB core init implementation.
 *
 * @details     This file contains API's the Init sequence for HS and SS core implementation.
 *
 * @note        
 *              Copyright 2017 QUALCOMM Technologies Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2016-2017,2021-2023 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================
// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 02/03/17     pm 	     Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "UsbSharedLib.h"
#include "qusb_log.h"
#include "qusb_dci_common.h"
#include "DDIChipInfo.h"
#include "UsbRetimer.h"
#include "UsbRedriver.h"
#include "UsbSharedLibTargetConfig.h"

#include "UsbRepeater.h"
#include "pm_eusb.h"


void usb_shared_delay_us(uint32 usecs) {
  qusb_dci_delay_us(usecs);
}

void usb_shared_loop_here(void) {
  static volatile uint32 loop_here = 0x1; 
  while(loop_here);
}

void usb_shared_uart_log_info(char *message) {
  return;
}
void usb_shared_uart_log_info1(char *message, uint32 value) {
  return;
}

void usb_shared_uart_log_warn(char *message, uint32 value) {
  qusb_uart_log(message, value);
}

void usb_shared_uart_log_error(char *message, uint32 value) {
  qusb_uart_log(message, value);
}

void usb_shared_error_log(uint32 id_0, uint8 offset, uint32 param) {
  qusb_error_log((qusb_log_enum)id_0, offset, param);
}

uint32 usb_shared_get_chip_revision(void) {
  return (uint32)DalChipInfo_ChipVersion();
}


//============================================================================

/**
* @function  usb_shared_get_platform
*
* @brief Read platforminfo from DAL API and cache it.
*
* @Note : None.
*
* @param None.
*
* @return None.
*
*/
//============================================================================
usb_platform_ctx usb_get_platform(void)
{
  usb_platform_ctx usb_platform;
    usb_platform.platform = PlatformInfo_Platform();
    usb_platform.subtype  = PlatformInfo_PlatformSubtype();
    //usb_shared_uart_log_error("platform: ", 
  //  ((usb_platform.platform << 16) | usb_platform.subtype));
  return usb_platform;
}


boolean usb_shared_pmic_gpio_enable(uint32 gpio_index, boolean is_enable)
{
  return TRUE;
}


#if 1
boolean usb_shared_tlmm_gpio_in(uint32 gpio_number, uint32 gpio_pull, uint32* value)
{
  return TRUE;
}
boolean usb_shared_tlmm_gpio_out(uint32 gpio_number, uint32 gpio_pull, boolean output_high)
{
  return TRUE;  
}
void usb_shared_tlmm_gpio_high(uint32 gpio_number)
{
  return;
}
void usb_shared_tlmm_gpio_low(uint32 gpio_number)
{
  return;
}


#else
boolean usb_shared_tlmm_gpio_in(uint32 gpio_number, uint32 gpio_pull, uint32* value)
{
  GPIOValueType pin_value = GPIO_LOW;
  GPIOResult gpio_res;
  GPIOClientHandleType gpio_handle;
  gpio_res = GPIO_Attach (GPIO_DEVICE_TLMM, &gpio_handle);
  if (gpio_res == GPIO_SUCCESS)
  {
    GPIOKeyType gpio_key;
    gpio_res = GPIO_RegisterPinExplicit (gpio_handle, gpio_number, GPIO_ACCESS_SHARED, &gpio_key);
    if (gpio_res == GPIO_SUCCESS)
    {
      GPIOConfigType gpio_config;
      gpio_config.func = USB_TLMM_GPIO_FUN_GPIO;
      gpio_config.dir = GPIO_IN;
      gpio_config.pull = gpio_pull;
      gpio_config.drive = USB_TLMM_GPIO_DRV_STR_2MA; /* 0.01mA, rounded up to 2mA by the driver. */
      gpio_res = GPIO_ConfigPin (gpio_handle, gpio_key, gpio_config);
      usb_shared_delay_us(10);
      if (gpio_res == GPIO_SUCCESS)
      {
        gpio_res = GPIO_ReadPin (gpio_handle, gpio_key, &pin_value);
        usb_shared_uart_log_error("tlmm_gpio|in ", gpio_number << 16 | pin_value);
      }
    }
  }
  if (gpio_res != GPIO_SUCCESS)
  {
  return FALSE;
  }
  if (pin_value == GPIO_HIGH)
  {
    *value = 1;
  }
  else
  {
    *value = 0;
  }
  return TRUE;
}


boolean usb_shared_tlmm_gpio_out(uint32 gpio_number, uint32 gpio_pull, boolean output_high)
{
  GPIOValueType value;
  GPIOResult gpio_res;
  GPIOClientHandleType gpio_handle;

  gpio_res = GPIO_Attach (GPIO_DEVICE_TLMM, &gpio_handle);
  if (gpio_res == GPIO_SUCCESS)
  {
    GPIOKeyType gpio_key;
    gpio_res = GPIO_RegisterPinExplicit (gpio_handle, gpio_number, GPIO_ACCESS_SHARED, &gpio_key);
    if (gpio_res == GPIO_SUCCESS)
    {
      GPIOConfigType gpio_config;
      gpio_config.func = USB_TLMM_GPIO_FUN_GPIO;
      gpio_config.dir = GPIO_OUT;
      gpio_config.pull = gpio_pull;
      gpio_config.drive = USB_TLMM_GPIO_DRV_STR_2MA; /* 0.01mA, rounded up to 2mA by the driver. */
      gpio_res = GPIO_ConfigPin (gpio_handle, gpio_key, gpio_config);
      if (gpio_res == GPIO_SUCCESS)
      {
        value = (output_high == 0) ? GPIO_LOW : GPIO_HIGH;
        usb_shared_uart_log_error("tlmm_gpio|out ", gpio_number << 16 | output_high);
        gpio_res = GPIO_WritePin (gpio_handle, gpio_key, value);
      }
    }
  }
  if (gpio_res != GPIO_SUCCESS)
  {
    return FALSE;
  }
  return TRUE;
}

void usb_shared_tlmm_gpio_high(uint32 gpio_number)
{  
  usb_shared_tlmm_gpio_out(gpio_number, USB_TLMM_GPIO_NO_PULL, TRUE);
  return;
}

void usb_shared_tlmm_gpio_low(uint32 gpio_number)
{  
  usb_shared_tlmm_gpio_out(gpio_number, USB_TLMM_GPIO_NO_PULL, FALSE);
  return;
}

#endif

boolean usb_shared_is_retimer_force_dp4lane_enabled(void)
{
  return FALSE;
}

#if 1
boolean usb_shared_i2c_open(usb_i2c_ctx_type* i2c_ctx, i2c_instance instance, uint32 slave_addr)
{
	return FALSE;
}
boolean usb_shared_i2c_close(usb_i2c_ctx_type* i2c_ctx)
{
	return FALSE;
}

boolean usb_shared_i2c_write(usb_i2c_ctx_type* i2c_ctx, uint16 addr, uint8* buffer, uint16 buffer_len)
{
	return FALSE;
}

boolean usb_shared_i2c_read(usb_i2c_ctx_type* i2c_ctx, uint16 addr, uint8* buffer, uint16 buffer_len)
{
	return FALSE;
}
#else


boolean usb_shared_i2c_open(usb_i2c_ctx_type* i2c_ctx, i2c_instance instance, uint32 slave_addr)
{
  i2c_status istatus = I2C_SUCCESS;
  istatus = i2c_open(instance, &i2c_ctx->handle);
  if (I2C_ERROR(istatus))
  {
    //usb_shared_uart_log_error("Failed to initialize I2C", istatus);    
    DEBUG(( EFI_D_ERROR, "Failed to init i2c: %d\r\n", istatus));
    return FALSE;
  }
  //usb_shared_uart_log_info1("Open initialize I2C", (uint32)(uintptr_t)i2c_ctx->handle);
  DEBUG(( EFI_D_ERROR, "open init i2c: 0x%x\r\n", (uint32)(uintptr_t)i2c_ctx->handle));
  i2c_ctx->config.bus_frequency_khz = 100;
  i2c_ctx->config.slave_address = slave_addr;
  i2c_ctx->config.mode = I2C;
  i2c_ctx->config.slave_max_clock_stretch_us = 500;
  i2c_ctx->config.core_configuration1 = 0;
  i2c_ctx->config.core_configuration2 = 0;
	return TRUE;
}

boolean usb_shared_i2c_close(usb_i2c_ctx_type* i2c_ctx)
{
  i2c_status istatus = I2C_SUCCESS;

  if (i2c_ctx->handle != NULL)
  {
    usb_shared_uart_log_info1("close I2C", (uint32)(uintptr_t)i2c_ctx->handle);    
    istatus = i2c_close(i2c_ctx->handle);
    if (I2C_ERROR(istatus))
    {
      usb_shared_uart_log_error("Failed to Deinitialize I2C", istatus);    
      return FALSE;
    }
  }
  return TRUE;
}


boolean usb_shared_i2c_write(usb_i2c_ctx_type* i2c_ctx, uint16 addr, uint8* buffer, uint16 buffer_len)
{
  i2c_status status = I2C_SUCCESS;
  uint32 written_count = 0;
 
  if ((NULL == i2c_ctx) || (NULL == buffer) || (buffer_len==0))
  {
    usb_shared_uart_log_error("usb_shared_i2c_write, invalid parameter", buffer_len);    
    return FALSE;
  }
  
  if(NULL == i2c_ctx->handle)
  {
    usb_shared_uart_log_error("usb_shared_i2c_write, not open 0x%x ", 0);
    return FALSE;
  }
  
  status = i2c_write(i2c_ctx->handle, &(i2c_ctx->config), addr, 1, buffer,
                      buffer_len, &written_count, USB_I2C_TIMEOUT_MAX);
  if (I2C_ERROR(status))
  {
    usb_shared_uart_log_error("usb_shared_i2c_write, write failed reg|data ", addr<<16|*buffer);
    return FALSE;
  }
  
  // Only enable for debugging as this prints 10s of lines to UART
  usb_shared_uart_log_error("usb_shared_i2c_write, write reg|data: ", addr<<16|*buffer);
  return TRUE;
}

boolean usb_shared_i2c_read(usb_i2c_ctx_type* i2c_ctx, uint16 addr, uint8* buffer, uint16 buffer_len)
{
  i2c_status status = I2C_SUCCESS;
  uint32 read_count = 0;
  
  if ((NULL == i2c_ctx) || (NULL == buffer) || (buffer_len==0))
  {
    usb_shared_uart_log_error("usb_shared_i2c_read, invalid parameter ", (uint32)(uintptr_t)i2c_ctx);    
    //usb_shared_error_log(I2C_READ_FAIL__BAD_PARAMETER_LOG, 0, buffer);
    return FALSE;
  }

  if(NULL == i2c_ctx->handle)
  {
    usb_shared_uart_log_error("usb_shared_i2c_read, Not Open", (uint32)(uintptr_t)i2c_ctx->handle);    
    return FALSE;
  }

  status = i2c_read(i2c_ctx->handle, &(i2c_ctx->config), addr, 1, buffer,
                      buffer_len, &read_count, USB_I2C_TIMEOUT_MAX);
  
  if (I2C_ERROR(status))
  {
    usb_shared_uart_log_error("usb_shared_i2c_read, read failed reg ", status);
    return FALSE;
  }
  usb_shared_uart_log_error("usb_shared_i2c_read, read reg ", addr<<16|*buffer);
  return TRUE;
}

#endif


#if 1
boolean usb_shared_spmi_write(uint32 core_num, uint16 addr, uint8 data)
{
  return TRUE;
}
boolean usb_shared_spmi_read(uint32 core_num, uint16 addr, uint8* data)
{
  return TRUE;
}
boolean usb_shared_spmi_init(uint32 core_num)
{
  return TRUE;
}

#else
boolean usb_shared_spmi_write(uint32 core_num, uint16 addr, uint8 data)
{
  pm_err_flag_type spmi_ret = PM_ERR_FLAG_SUCCESS;

  //spmi_ret = pm_eusb_write(PMIC_EUSB_RPTR_INDEX, addr, data);
  //usb_shared_uart_log_info1("write reg|data:", addr<<16|data);
  usb_shared_error_log(USB_SHARED_SPMI_WRITE_LOG, 0, addr<<16| data);

  if(PM_ERR_FLAG_SUCCESS != spmi_ret)
  {
    usb_shared_error_log(USB_SHARED_SPMI_WRITE_FAIL_LOG, 0, spmi_ret);
    //DEBUG(( EFI_D_ERROR, "write spmi reg failed: %d\r\n", spmi_ret));
    return FALSE;
  }
  return TRUE;
}


boolean usb_shared_spmi_read(uint32 core_num, uint16 addr, uint8* data)
{
  pm_err_flag_type spmi_ret = PM_ERR_FLAG_SUCCESS;
  //spmi_ret = pm_eusb_read(PMIC_EUSB_RPTR_INDEX, addr, data);
  //usb_shared_uart_log_error("read reg|data:", addr<<16|*data);
  usb_shared_error_log(USB_SHARED_SPMI_READ_LOG, 0, addr<<16|*data);


  if(PM_ERR_FLAG_SUCCESS != spmi_ret)
  {
    usb_shared_error_log(USB_SHARED_SPMI_READ_FAIL_LOG, 0, spmi_ret);
    //DEBUG(( EFI_D_ERROR, "read spmi failed: %d\r\n", spmi_ret));
    return FALSE;
  }
  return TRUE;
}

boolean usb_shared_spmi_init(uint32 core_num)
{
  pm_err_flag_type    spmi_ret;

  spmi_ret = pm_eusb_enable(PMIC_EUSB_RPTR_INDEX, 1);
  //usb_shared_uart_log_error("usb_spmi_enable core", core_num);
  usb_shared_error_log(USB_SHARED_SPMI_ENABLE_LOG, 0, core_num);


  if(PM_ERR_FLAG_SUCCESS != spmi_ret)
  {
    usb_shared_error_log(USB_SHARED_SPMI_ENABLE_FAIL_LOG, 0, spmi_ret);
    //DEBUG(( EFI_D_ERROR, "Init spmi failed: %d\r\n", spmi_ret));
    return FALSE;
  }

  return TRUE;
}

#endif
