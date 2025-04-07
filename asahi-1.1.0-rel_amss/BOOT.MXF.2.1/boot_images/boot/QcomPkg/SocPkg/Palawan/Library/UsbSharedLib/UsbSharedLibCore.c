/*=======================================================================*//**
 * @file        UsbSharedCore.c
 * @author:     Pmahajan
 * @date        03-feb-2017
 *
 * @brief       USB common & shared USB core init implementation.
 *
 * @details     This file contains API's the Init sequence for HS and SS core implementation.
 *
 * @note        
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2016-2018,2022-2023 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
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
// 10/20/21     pohanw   add booster wrapper
// 05/28/21     jaychoi  Update retimer sequence
// 04/30/21     jaychoi  Added support for B1 retimer
// 06/14/17     amitg    Cleanup
// 02/03/17     pm 	     Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include "UsbSharedLib.h"
#include "DDIChipInfo.h"
#include "DDIPlatformInfo.h"
#include "UsbSharedLibTargetConfig.h"
#include "UsbRetimer.h"
#include "UsbRedriver.h"
#include "UsbRepeater.h"
#include <Uefi/UefiBaseType.h>
#include "SpmiTypes.h"
#include <Protocol/EFISPMI.h>
#include <Protocol/EFIPmicVreg.h>
#include <Protocol/EFIPmicVersion.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicClkBuff.h>
#include "HalusbHWIO.h"

#include "DDITlmm.h"
#include "DALSys.h"   // Required for DALSYS_InitMod for TLMM

//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------

void usb_shared_delay_us(uint32 usecs) {
  gBS->Stall (MICRO_STALL_UNITS(usecs));
}

void usb_shared_loop_here(void) { 
  static volatile uint32 loop_here = 0x1; 

  while(loop_here);
}

void usb_shared_uart_log_info(char *message) { 
  //DebugPrint(EFI_D_INFO,"%a\n", message);
}

void usb_shared_uart_log_info1(char *message, uint32 value) {
  DebugPrint(EFI_D_INFO,"%a, 0x%x\n", message, value);
}

void usb_shared_uart_log_warn(char *message, uint32 value) { 
  DebugPrint(EFI_D_ERROR, "%a: 0x%x\n", message, value);
}

void usb_shared_uart_log_error(char *message, uint32 value) { 
  DebugPrint(EFI_D_ERROR, "%a: 0x%x\n", message, value);
}

void usb_shared_error_log(uint32 id_0, uint8 offset, uint32 param) {
  //qusb_error_log((qusb_log_enum)id_0, offset, param);
  DebugPrint(EFI_D_ERROR, "0x%x: 0x%x\n", id_0+offset, param);
  return;
}

uint32 usb_shared_get_chip_revision(void) {
  return (uint32)DalChipInfo_ChipVersion();
}


usb_platform_ctx usb_get_platform(void)
{
  DalDeviceHandle                  *phPlatformInfo   = NULL;
  DALResult                         eResult;
  DalPlatformInfoPlatformInfoType   platformInfo;
  usb_platform_ctx usb_platform= {DALPLATFORMINFO_TYPE_32BITS, 0};  //init value will only get platform once

   /*Initialize DALSYS and attach to the DAL TLMM driver. */
    DALSYS_InitMod(NULL);

  eResult = DAL_DeviceAttach(DALDEVICEID_PLATFORMINFO, &phPlatformInfo);
    if (eResult != DAL_SUCCESS)
  {
    usb_shared_uart_log_error("platform: attach failed", eResult);
  }
  else
  {
    eResult = DalPlatformInfo_GetPlatformInfo(phPlatformInfo, &platformInfo);
    if (eResult != DAL_SUCCESS)
    {
      usb_shared_uart_log_error("platform: get failed", eResult);
        usb_platform.platform = DALPLATFORMINFO_TYPE_UNKNOWN;
        usb_platform.subtype = 0;
      }
      else
      {
        usb_platform.platform = platformInfo.platform;
        usb_platform.subtype = platformInfo.subtype;
    }

    eResult = DAL_DeviceDetach(phPlatformInfo);
    if (eResult != DAL_SUCCESS)
    {
      usb_shared_uart_log_error("platform: detach failed", eResult);
    }
  }
  usb_shared_uart_log_error("platform: ",
    ((usb_platform.platform << 16) | usb_platform.subtype));
  return usb_platform;
}

#define PMIC_INDEX_FOR_GPIO (2)
EFI_QCOM_PMIC_GPIO_PROTOCOL *PmicGpioProtocol_shared = NULL;
boolean usb_shared_pmic_gpio_enable(uint32 gpio_index, boolean is_enable)
{
  EFI_STATUS Status = EFI_SUCCESS;
  if (!PmicGpioProtocol_shared)
  {
    Status = gBS->LocateProtocol(&gQcomPmicGpioProtocolGuid, NULL, (void **)&PmicGpioProtocol_shared);
    if (EFI_ERROR(Status))
    {
      PmicGpioProtocol_shared = NULL;
      usb_shared_uart_log_error("Failed to open PMIC GPIO protocol Status", gpio_index);
      return FALSE;
    }
  }
  Status = PmicGpioProtocol_shared->Enable(PMIC_INDEX_FOR_GPIO, gpio_index, is_enable);
  if (EFI_SUCCESS != Status)
  {
    usb_shared_uart_log_error("Failed to enable GPIO status ", Status);
    return FALSE;
  }
  return TRUE;
}


#if 0
void usb_shared_tlmm_gpio_high(uint32 gpio_number)
{
  return;
}

void usb_shared_tlmm_gpio_low(uint32 gpio_number)
{
  return;
}
boolean usb_shared_tlmm_gpio_in(uint32 gpio_number, uint32 gpio_pull, uint32* value)
{
  return TRUE;
}
boolean usb_shared_tlmm_gpio_out(uint32 gpio_number, uint32 gpio_pull, boolean output_high)
{
  return TRUE;
}

#else

//============================================================================
/**
* @function  usb_shared_tlmm_gpio_high
*
* @brief For device mode: Configure GPIO high and enabled
*
* @Note : None
*
* @param  GPIO number 
*
* @return None
*
*/
//============================================================================

boolean usb_shared_tlmm_gpio_in(uint32 gpio_number, uint32 gpio_pull, uint32* value)
{
  /*Handle to the DAL TLMM Device context.*/
  DalDeviceHandle   *tlmm_handle  = NULL;
  DALResult         result        = DAL_ERROR;

  /* Create a DAL-formatted GPIO configuration for */
  DALGpioSignalType config =
     (DALGpioSignalType)DAL_GPIO_CFG(
     gpio_number, 0, DAL_GPIO_INPUT, gpio_pull, DAL_GPIO_2MA);
  
  /* Initialize DALSYS and attach to the DAL TLMM driver. */
  DALSYS_InitMod(NULL);
  result = DAL_DeviceAttach(DALDEVICEID_TLMM, &tlmm_handle);

  if((DAL_ERROR == result) || (tlmm_handle == NULL))
  {
    usb_shared_uart_log_error("tlmm: attach fail", result);
    return FALSE;
  }
  else
  {
    /* Configure the GPIO. */
    result = DalTlmm_ConfigGpio(tlmm_handle, config, DAL_TLMM_GPIO_ENABLE);
    if(DAL_SUCCESS != result)
    {
      usb_shared_uart_log_error("tlmm: config fail", result);
      return FALSE;
    }
    else
    {
      DALGpioValueType read_value;
      result = DalTlmm_GpioIn(tlmm_handle, config, &read_value);
      if(DAL_SUCCESS != result)
      {
        usb_shared_uart_log_error("tlmm: IN fail", result);
        return FALSE;
    }
      else
      {

        if (DAL_GPIO_LOW_VALUE == read_value)
        {
          *value = 0;
  }
        else
        {
          *value = 1;
        }
      }
    }
    result = DAL_DeviceDetach(tlmm_handle);
    if(DAL_SUCCESS != result)
    {
      usb_shared_uart_log_error("tlmm: detach fail", result);
      return FALSE;
    }
  }
  return TRUE;
}

boolean usb_shared_tlmm_gpio_out(uint32 gpio_number, uint32 gpio_pull, boolean output_high)
{
  /*Handle to the DAL TLMM Device context.*/
  DalDeviceHandle   *tlmm_handle  = NULL;
  DALResult         result        = DAL_ERROR;

  /* Create a DAL-formatted GPIO configuration for */
  DALGpioSignalType config =
     (DALGpioSignalType)DAL_GPIO_CFG(
     gpio_number, 0, DAL_GPIO_OUTPUT, gpio_pull, DAL_GPIO_2MA);
  
  /* Initialize DALSYS and attach to the DAL TLMM driver. */
    DALSYS_InitMod(NULL);
  result = DAL_DeviceAttach(DALDEVICEID_TLMM, &tlmm_handle);

  if((DAL_ERROR == result) || (tlmm_handle == NULL))
    {
    usb_shared_uart_log_error("tlmm: attach fail", result);
    return FALSE;
    }
    else
    {
    /* Configure the GPIO. */
    result = DalTlmm_ConfigGpio(tlmm_handle, config, DAL_TLMM_GPIO_ENABLE);
    if(DAL_SUCCESS != result)
      {
      usb_shared_uart_log_error("tlmm: config fail", result);
      return FALSE;
      }
      else
      {

      if (output_high)
      {
        /* Drive the GPIO HIGH. */
        result = DalTlmm_GpioOut(tlmm_handle, config, DAL_GPIO_HIGH_VALUE);
      }
      else
      {
        /* Drive the GPIO HIGH. */
        result = DalTlmm_GpioOut(tlmm_handle, config, DAL_GPIO_LOW_VALUE);
      }
      if(DAL_SUCCESS != result)
      {
        usb_shared_uart_log_error("tlmm: out fail", result);
        return FALSE;
      }

    }
    result = DAL_DeviceDetach(tlmm_handle);
    if(DAL_SUCCESS != result)
      {
      usb_shared_uart_log_error("tlmm: detach fail", result);
      return FALSE;
      }
    }
  return TRUE;
}

void usb_shared_tlmm_gpio_high(uint32 gpio_number)
{  
  usb_shared_tlmm_gpio_out(gpio_number, DAL_GPIO_NO_PULL, TRUE);
}

void usb_shared_tlmm_gpio_low(uint32 gpio_number)
{  
  usb_shared_tlmm_gpio_out(gpio_number, DAL_GPIO_NO_PULL, FALSE);
}
#endif



boolean usb_shared_is_retimer_force_dp4lane_enabled(void)
{
  static boolean usb_shared_force_dp4lane = FALSE;
  #if 0
  static boolean usb_shared_force_dp4lane_uefi_var_read = FALSE;
  EFI_STATUS                    Status      = EFI_SUCCESS;
  INT8                          UefiVar     = 0;
  UINTN                         UefiVarSize;
  

  if (FALSE == usb_shared_force_dp4lane_uefi_var_read)
  {
    usb_shared_force_dp4lane_uefi_var_read = TRUE;

    UefiVarSize = sizeof(UefiVar);
    Status = gRT->GetVariable(L"ForceUsb4RetimerDP4LANE", &gQcomTokenSpaceGuid, NULL, &UefiVarSize, &UefiVar);
    if(!EFI_ERROR(Status) && UefiVar) 
    {
      usb_shared_uart_log_error("USB Force USB4 Retimer DP4LANE Mode Enabled", UefiVar);
      usb_shared_force_dp4lane = TRUE;
  }
  }
  #endif
  return usb_shared_force_dp4lane;
}




#if 0

boolean usb_shared_spmi_write(uint32 core_num, uint16 addr, uint8 data)
{
  pm_err_flag_type spmi_ret = PM_ERR_FLAG_SUCCESS;

  spmi_ret = pm_eusb_write(PMIC_EUSB_RPTR_INDEX, addr, data);
  //usb_shared_uart_log_info1("write reg|data:", addr<<16|data);
  usb_shared_error_log(USB_SHARED_SPMI_WRITE_LOG, 0, addr<<16|*data);

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
  spmi_ret = pm_eusb_read(PMIC_EUSB_RPTR_INDEX, addr, data);
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



#else

EFI_QCOM_SPMI_PROTOCOL *pSpmiProtocol = NULL;
// ===========================================================================
/**
 * @function    usb_shared_process_cfg_reg_array
 * 
 * @brief   This function reads from array which define list of hwio writes for
 *          USB PHY
 * 
 * @param   cfg_array   - array holding address and value of HW register
 *          start_index     - starting index for array processing
 *          array_entry_cnt - number of entries in the array
 *          core_num  -  core number to which repeater is connected
 * 
 * @return  boolean  - if writes are successful
 * 
 */
// ===========================================================================

boolean usb_shared_spmi_write(uint32 core_num, uint16 addr, uint8 data)
{
  Spmi_Result spmi_ret = SPMI_SUCCESS;
  UINT32 len = 1;
  UINT32 rptr_index;
  if ( (NULL == pSpmiProtocol) )
  {
    DEBUG(( EFI_D_ERROR, "pSpmiProtocol: no found tr\n"));
    //usb_shared_error_log(USB_SHARED_SPMI_WRITE_FAIL__BAD_PARAMETER_LOG, 0, (uint32)(uintptr_t)pSpmiProtocol);
    return FALSE;
  }

  addr = EUSB2_BASE + addr;
  
  rptr_index = usb_repeater_get_index_for_core(core_num);
  spmi_ret |= pSpmiProtocol->WriteLong(pSpmiProtocol, PMIC_EUSB_RPTR_SPMI_BUSID, rptr_index,
                                        SPMI_BUS_ACCESS_PRIORITY_LOW, addr, &data, len);  

  DEBUG(( EFI_D_INFO, "WRITING: rptr_index: 0x%x, reg: 0x%x, data: 0x%x, res = %d\r\n", rptr_index, addr, data, spmi_ret)); 

  if(SPMI_SUCCESS != spmi_ret)
  {
    DEBUG(( EFI_D_ERROR, "write spmi reg failed: %d\r\n", spmi_ret));
    //usb_shared_error_log(USB_SHARED_SPMI_WRITE_FAIL__BAD_PARAMETER_LOG, 0, ((addr <<16)| data));
    return FALSE;
  }
  //usb_shared_error_log(USB_SHARED_SPMI_WRITE_LOG, 0, ((addr <<16)| data));
  return TRUE;
}


boolean usb_shared_spmi_read(uint32 core_num, uint16 addr, uint8* data)
{
  Spmi_Result spmi_ret = SPMI_SUCCESS;
  UINT32 len = 1;
  UINT32 bytesRead =0;
  UINT32 rptr_index;

  if ( (NULL == pSpmiProtocol) )
  {
    DEBUG(( EFI_D_ERROR, "pSpmiProtocol: no found tr\n"));    
    //usb_shared_error_log(USB_SHARED_SPMI_READ_FAIL__BAD_PARAMETER_LOG, 0, (uint32)(uintptr_t)pSpmiProtocol);
    return FALSE;
  }

  addr = EUSB2_BASE + addr;
  rptr_index = usb_repeater_get_index_for_core(core_num);
  spmi_ret |= pSpmiProtocol->ReadLong(pSpmiProtocol, PMIC_EUSB_RPTR_SPMI_BUSID, rptr_index,
									  SPMI_BUS_ACCESS_PRIORITY_LOW, addr, data, len, &bytesRead);
  DEBUG(( EFI_D_ERROR, "READING: rptr_index: 0x%x, reg: 0x%x, data: 0x%x, res = %d\r\n", rptr_index, addr, *data, spmi_ret)); 

  if(SPMI_SUCCESS != spmi_ret)
  {
    DEBUG(( EFI_D_ERROR, "read spmi reg failed: %d\r\n", spmi_ret));
    //usb_shared_error_log(USB_SHARED_SPMI_READ_FAIL_LOG, 0, ((addr <<16)| *data));
    return FALSE;
  }
  //usb_shared_error_log(USB_SHARED_SPMI_READ_LOG, 0, ((addr <<16)| *data));
  return TRUE;
}

boolean usb_shared_spmi_init(uint32 core_num)
{
  EFI_STATUS    Status;

  /* Get SPMI Protocol */
  Status = gBS->LocateProtocol(&gQcomSPMIProtocolGuid, NULL, (VOID **) &pSpmiProtocol);
  if ( EFI_ERROR (Status) )
  {
    DEBUG(( EFI_D_ERROR, "failed to locate SPMIProtocol, Status = (0x%x)\r\n", Status));
    //usb_shared_error_log(USB_SHARED_SPMI_ENABLE_FAIL_LOG, 0, (uint32)(uintptr_t)pSpmiProtocol);
    return FALSE;
  }
  return TRUE;
}

#endif


#if 0
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
  //DEBUG(( EFI_D_ERROR, "open init i2c: 0x%x\r\n", (uint32)(uintptr_t)i2c_ctx->handle));
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
  //usb_shared_uart_log_info1("usb_shared_i2c_write, write reg|data: ", addr<<16|*buffer);
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
  usb_shared_uart_log_warn("usb_shared_i2c_read, read reg ", addr<<16|*buffer);
  return TRUE;
}


#endif

