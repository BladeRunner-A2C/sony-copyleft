/*============================================================================
  FILE:         AdcLib.c

  OVERVIEW:     Implementation of the ADC device wrapper layer

  DEPENDENCIES: None

                Copyright (c) 2012-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2022-10-26  ha   DALSys independent ADC fwk for bootloader
  2016-05-16  jjo  Status check.
  2015-01-23  jjo  Use DDIAdc.h.
  2014-04-02  jjo  Platform subtype check for 8994.
  2013-06-19  jjo  Platform subtype check for 8974.
  2012-12-03  jjo  Added IADC.
  2012-07-01  jjo  Initial version.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "PmicAdc.h"
#include "AdcBsp.h"
#include "AdcDevice.h"
#include "pm_version.h"
#include "DDIChipInfo.h"
#include "pm_vadc_target_config.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef struct
{
   uint32 eDeviceId;
   AdcDeviceHandle *phDevice;
} AdcDeviceType;

typedef struct
{
   AdcBspType *pAdcBsp;
   AdcDeviceType aAdcDevice[ADC_MAX_NUM_DEVICES];
} AdcBootContextType;

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/
static boolean gbAdcInitialized = FALSE;
static AdcBootContextType gAdcCtxt;

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
static AdcResultStatusType Adc_ConvertStatus(AdcDeviceResultStatusType eDeviceStatus)
{
   switch (eDeviceStatus)
   {
      case ADC_DEVICE_RESULT_VALID:
         return ADC_RESULT_VALID;
      case ADC_DEVICE_RESULT_TIMEOUT:
         return ADC_RESULT_TIMEOUT;
      case ADC_DEVICE_RESULT_STALE:
         return ADC_RESULT_STALE;
      default:
         return ADC_RESULT_INVALID;
   }
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
AdcResult Adc_GetAdcInputProperties( const char *pszChannelName, uint32 nInputNameSize, AdcInputPropertiesType *pChannel)
{
   AdcResult result;
   uint32 uDevice;
   uint32 uChannel;
   AdcDeviceHandle *phDevice;

   if ((!gbAdcInitialized) || pszChannelName == NULL || pChannel == NULL)
   {
      return ADC_ERROR;
   }

   for (uDevice = 0; uDevice < gAdcCtxt.pAdcBsp->uNumDevices; uDevice++)
   {
      phDevice = gAdcCtxt.aAdcDevice[uDevice].phDevice;

      result = AdcDevice_GetInputProperties(phDevice, pszChannelName, &uChannel);
      if (result == ADC_SUCCESS)
      {
         pChannel->nDeviceIdx = uDevice;
         pChannel->nChannelIdx = uChannel;

         return ADC_SUCCESS;
      }
   }

   return ADC_ERROR;
}

AdcResult Adc_Read( const AdcInputPropertiesType *pChannel, AdcResultType *pAdcResult)
{
   AdcResult result;
   uint32 uDevice;
   uint32 uChannel;
   AdcDeviceHandle *phDevice;
   AdcDeviceResultType adcDeviceResult;

   if ((!gbAdcInitialized) || pChannel == NULL || pAdcResult == NULL)
   {
      return ADC_ERROR;
   }

   uDevice = pChannel->nDeviceIdx;

   if (uDevice >= gAdcCtxt.pAdcBsp->uNumDevices || uDevice >= ADC_MAX_NUM_DEVICES)
   {
      return ADC_ERROR;
   }

   uChannel = pChannel->nChannelIdx;
   phDevice = gAdcCtxt.aAdcDevice[uDevice].phDevice;

   adcDeviceResult.eStatus = ADC_DEVICE_RESULT_INVALID;
   adcDeviceResult.nPhysical = 0;
   adcDeviceResult.uPercent = 0;
   adcDeviceResult.uMicrovolts = 0;
   adcDeviceResult.uCode = 0;

   result = AdcDevice_ReadChannel(phDevice, uChannel, &adcDeviceResult);
   if (result != ADC_SUCCESS)
   {
      return ADC_ERROR;
   }

   pAdcResult->eStatus = Adc_ConvertStatus(adcDeviceResult.eStatus);
   pAdcResult->nDeviceIdx = uDevice;
   pAdcResult->nChannelIdx = uChannel;
   pAdcResult->nPhysical = adcDeviceResult.nPhysical;
   pAdcResult->nPercent = adcDeviceResult.uPercent;
   pAdcResult->nMicrovolts = adcDeviceResult.uMicrovolts;
   pAdcResult->nCode = adcDeviceResult.uCode;

   return ADC_SUCCESS;
}

#ifndef ADC_LOADER_DRIVER
AdcResult Adc_Recalibrate( const AdcInputPropertiesType *pChannel, AdcRecalibrationResultType *pAdcRecalResult)
{
   AdcResult result;
   uint32 uDevice;
   uint32 uChannel;
   AdcDeviceHandle *phDevice;
   AdcDeviceRecalibrateResultType adcDeviceRecalibrateResult;

   if ((!gbAdcInitialized) || pChannel == NULL || pAdcRecalResult == NULL)
   {
      return ADC_ERROR;
   }

   uDevice = pChannel->nDeviceIdx;

   if (uDevice >= gAdcCtxt.pAdcBsp->uNumDevices || uDevice >= ADC_MAX_NUM_DEVICES)
   {
      return ADC_ERROR;
   }

   uChannel = pChannel->nChannelIdx;
   phDevice = gAdcCtxt.aAdcDevice[uDevice].phDevice;

   adcDeviceRecalibrateResult.eStatus = ADC_DEVICE_RESULT_INVALID;
   adcDeviceRecalibrateResult.nPhysical1_uV = 0;
   adcDeviceRecalibrateResult.nPhysical2_uV = 0;
   adcDeviceRecalibrateResult.uCode1 = 0;
   adcDeviceRecalibrateResult.uCode2 = 0;

   result = AdcDevice_RecalibrateChannel(phDevice, uChannel, &adcDeviceRecalibrateResult);
   if (result != ADC_SUCCESS)
   {
      return ADC_ERROR;
   }

   pAdcRecalResult->eStatus = Adc_ConvertStatus(adcDeviceRecalibrateResult.eStatus);
   pAdcRecalResult->uDeviceIdx = uDevice;
   pAdcRecalResult->uChannelIdx = uChannel;
   pAdcRecalResult->nPhysical1_uV = adcDeviceRecalibrateResult.nPhysical1_uV;
   pAdcRecalResult->nPhysical2_uV = adcDeviceRecalibrateResult.nPhysical2_uV;
   pAdcRecalResult->uCode1 = adcDeviceRecalibrateResult.uCode1;
   pAdcRecalResult->uCode2 = adcDeviceRecalibrateResult.uCode2;

   return ADC_SUCCESS;
}
#endif

AdcResult Adc_ProcessConversionResult( const AdcInputPropertiesType *pChannel, uint32 uAdcCode, AdcResultType *pAdcResult)
{
   AdcResult result;
   uint32 uDevice;
   uint32 uChannel;
   AdcDeviceHandle *phDevice;
   AdcDeviceResultType adcDeviceResult;

   if ((!gbAdcInitialized) || pChannel == NULL || pAdcResult == NULL)
   {
      return ADC_ERROR;
   }

   uDevice = pChannel->nDeviceIdx;

   if (uDevice >= gAdcCtxt.pAdcBsp->uNumDevices || uDevice >= ADC_MAX_NUM_DEVICES)
   {
      return ADC_ERROR;
   }

   uChannel = pChannel->nChannelIdx;
   phDevice = gAdcCtxt.aAdcDevice[uDevice].phDevice;

   adcDeviceResult.eStatus = ADC_DEVICE_RESULT_INVALID;
   adcDeviceResult.nPhysical = 0;
   adcDeviceResult.uPercent = 0;
   adcDeviceResult.uMicrovolts = 0;
   adcDeviceResult.uCode = 0;

   result = AdcDevice_ProcessConversionResult(phDevice, uChannel, uAdcCode, &adcDeviceResult);
   if (result != ADC_SUCCESS)
   {
      return ADC_ERROR;
   }

   pAdcResult->eStatus = Adc_ConvertStatus(adcDeviceResult.eStatus);
   pAdcResult->nDeviceIdx = uDevice;
   pAdcResult->nChannelIdx = uChannel;
   pAdcResult->nPhysical = adcDeviceResult.nPhysical;
   pAdcResult->nPercent = adcDeviceResult.uPercent;
   pAdcResult->nMicrovolts = adcDeviceResult.uMicrovolts;
   pAdcResult->nCode = adcDeviceResult.uCode;

   return ADC_SUCCESS;
}

AdcResult Adc_ProcessConversionResultInverse( const AdcInputPropertiesType *pChannel, int32 nPhysical, AdcResultType *pAdcResult)
{
   AdcResult result;
   uint32 uDevice;
   uint32 uChannel;
   AdcDeviceHandle *phDevice;
   AdcDeviceResultType adcDeviceResult;

   if ((!gbAdcInitialized) || pChannel == NULL || pAdcResult == NULL)
   {
      return ADC_ERROR;
   }

   uDevice = pChannel->nDeviceIdx;

   if (uDevice >= gAdcCtxt.pAdcBsp->uNumDevices || uDevice >= ADC_MAX_NUM_DEVICES)
   {
      return ADC_ERROR;
   }

   uChannel = pChannel->nChannelIdx;
   phDevice = gAdcCtxt.aAdcDevice[uDevice].phDevice;

   adcDeviceResult.eStatus = ADC_DEVICE_RESULT_INVALID;
   adcDeviceResult.nPhysical = 0;
   adcDeviceResult.uPercent = 0;
   adcDeviceResult.uMicrovolts = 0;
   adcDeviceResult.uCode = 0;

   result = AdcDevice_ProcessConversionResultInverse(phDevice, uChannel, nPhysical, &adcDeviceResult);
   if (result != ADC_SUCCESS)
   {
      return ADC_ERROR;
   }

   pAdcResult->eStatus = Adc_ConvertStatus(adcDeviceResult.eStatus);
   pAdcResult->nDeviceIdx = uDevice;
   pAdcResult->nChannelIdx = uChannel;
   pAdcResult->nPhysical = adcDeviceResult.nPhysical;
   pAdcResult->nPercent = adcDeviceResult.uPercent;
   pAdcResult->nMicrovolts = adcDeviceResult.uMicrovolts;
   pAdcResult->nCode = adcDeviceResult.uCode;

   return ADC_SUCCESS;
}

AdcResult Adc_DeviceAttach(void)
{
   AdcBspType *pBsp;
   AdcDeviceType *pAdcDevice;
   AdcResult result;
   uint32 uDevice;

   if (gbAdcInitialized)
   {
      return ADC_SUCCESS;
   }

   /* Use deviceId instead of string */
   uint32 bspId = pm_vadc_target_get_adc_bsp_id ();
   /* Get ADS_BSP config using the target specific deviceId */
   gAdcCtxt.pAdcBsp = pm_vadc_target_get_adc_bsp(bspId);

   if (!gAdcCtxt.pAdcBsp)
   {
      return ADC_ERROR;
   }

   pBsp = gAdcCtxt.pAdcBsp;

   if (pBsp->uNumDevices > ADC_MAX_NUM_DEVICES)
   {
      return ADC_ERROR;
   }

   for (uDevice = 0; uDevice < pBsp->uNumDevices; uDevice++)
   {
      pAdcDevice = &gAdcCtxt.aAdcDevice[uDevice];
      pAdcDevice->eDeviceId = pBsp->paAdcPhysicalDevices[uDevice].eDeviceId;

      /* Iterate over total BSP supported devices and fetch the non-Adc
       * device handle*/
      result = AdcDevice_DeviceAttach(pAdcDevice->eDeviceId,
                                      (void **)&pAdcDevice->phDevice);
      if (result != ADC_SUCCESS)
      {
         return ADC_ERROR;
      }
   }

   gbAdcInitialized = TRUE;

   return ADC_SUCCESS;
}

