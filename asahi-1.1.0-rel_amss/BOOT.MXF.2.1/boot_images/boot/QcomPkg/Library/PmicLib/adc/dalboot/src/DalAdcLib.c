/*============================================================================
  FILE:         AdcLib.c

  OVERVIEW:     Implementation to support Legacy DAL ADC device wrapper layer.

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
#include "DDIAdc.h"
#include "PmicAdc.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define ADC_MAGIC_NUM ((DalDeviceHandle *)0x43444156)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
DALResult DalAdc_GetAdcInputProperties(DalDeviceHandle *_h, const char *pszChannelName, uint32 nInputNameSize, AdcInputPropertiesType *pChannel)
{
   if (_h != ADC_MAGIC_NUM)
   {
      return DAL_ERROR;
   }

   return Adc_GetAdcInputProperties(pszChannelName, nInputNameSize, pChannel);
}

DALResult DalAdc_Read(DalDeviceHandle *_h, const AdcInputPropertiesType *pChannel, AdcResultType *pAdcResult)
{
   if (_h != ADC_MAGIC_NUM)
   {
      return DAL_ERROR;
   }

   return Adc_Read(pChannel, pAdcResult);
}

#ifndef ADC_LOADER_DRIVER
DALResult DalAdc_Recalibrate(DalDeviceHandle *_h, const AdcInputPropertiesType *pChannel, AdcRecalibrationResultType *pAdcRecalResult)
{
   if (_h != ADC_MAGIC_NUM)
   {
      return DAL_ERROR;
   }

   return Adc_Recalibrate(pChannel, pAdcRecalResult);
}
#endif

DALResult DalAdc_ProcessConversionResult(DalDeviceHandle *_h, const AdcInputPropertiesType *pChannel, uint32 uAdcCode, AdcResultType *pAdcResult)
{
   if (_h != ADC_MAGIC_NUM)
   {
      return DAL_ERROR;
   }

   return Adc_ProcessConversionResult(pChannel, uAdcCode, pAdcResult);
}

DALResult DalAdc_ProcessConversionResultInverse(DalDeviceHandle *_h, const AdcInputPropertiesType *pChannel, int32 nPhysical, AdcResultType *pAdcResult)
{
   if (_h != ADC_MAGIC_NUM)
   {
      return DAL_ERROR;
   }

   return Adc_ProcessConversionResultInverse(pChannel, nPhysical, pAdcResult);
}

DALResult DAL_AdcDeviceAttach(DALDEVICEID DevId, DalDeviceHandle **phAdcDev)
{
   DALResult result;

   if (DevId != DALDEVICEID_ADC)
   {
      return DAL_ERROR;
   }

   result = Adc_DeviceAttach();

   if (result != DAL_SUCCESS)
   {
      return result;
   }

   *phAdcDev = ADC_MAGIC_NUM;

   return DAL_SUCCESS;
}

