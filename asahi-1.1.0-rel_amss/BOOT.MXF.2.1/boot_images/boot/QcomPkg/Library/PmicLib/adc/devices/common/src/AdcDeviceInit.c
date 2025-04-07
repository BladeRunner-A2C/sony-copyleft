/*============================================================================
  @file AdcDeviceInit.c

  Implementation for ADC Physical Device Driver Interface Init.

  Copyright (c) 2022-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  
  $Header:  $
============================================================================*/
/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "AdcDevice.h"
#include "VAdc.h"
#include "CoreVerify.h"

/*-------------------------------------------------------------------------
 * Global Variables
 * ----------------------------------------------------------------------*/
const struct AdcDeviceInitCtxtType gAdcDeviceInitCtxt[ADC_DEVICE_MAX] = 
{
   [0] = {VAdc_AdcDevice_Attach},  /*VADC Device Init*/
};

/*-------------------------------------------------------------------------
 * Function Definitions
 * ----------------------------------------------------------------------*/
AdcResult AdcDevice_Attach(AdcDeviceId adc_device_id,
                           uint32 adc_device_index,
                           void** hDevice)
{
   if (adc_device_id >= ADC_DEVICE_MAX)
   {
      CORE_VERIFY(0);
   }

   if (gAdcDeviceInitCtxt[adc_device_id].VAdc_Attach)
   {
      return gAdcDeviceInitCtxt[adc_device_id].VAdc_Attach(adc_device_index, hDevice);
   }

   return DAL_SUCCESS;
}

