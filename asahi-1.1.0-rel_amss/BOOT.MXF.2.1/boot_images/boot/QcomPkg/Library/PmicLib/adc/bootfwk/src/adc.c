/*============================================================================
  FILE:         adc.c

  OVERVIEW:     Wrapper for DAL ADC.

  DEPENDENCIES: None

                Copyright (c) 2016-2023 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/adc/bootfwk/src/adc.c#1 $$DateTime: 2024/04/02 23:00:31 $$Author: cirrusp4svc $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2017-02-08  jjo  Ported to boot.
  2016-04-27  jjo  Initial revision.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "adc.h"
#include "PmicAdc.h"
#include "string.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/
static boolean gbAdcDriverInit = FALSE;

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
adc_status_type adc_read(const char *input, adc_result_type *adc_result)
{
   AdcResultType adcResult;
   AdcInputPropertiesType adcInputProps;
   AdcResult result;
   adc_status_type status;

   if (input == NULL || adc_result == NULL)
   {
      return ADC_STATUS_INVALID_PARAM;
   }

   if (!gbAdcDriverInit)
   {
      gbAdcDriverInit = (ADC_SUCCESS == (result = Adc_DeviceAttach()));
      if (!gbAdcDriverInit)
      {
         return ADC_STATUS_ERROR;
      }
   }

   result = Adc_GetAdcInputProperties(input,
                                      (uint32)(strlen(input) + 1),
                                      &adcInputProps);
   if (result != ADC_SUCCESS)
   {
      return ADC_STATUS_CHANNEL_NOT_SUPPORTED;
   }

   result = Adc_Read(&adcInputProps,
                     &adcResult);
   if (result != ADC_SUCCESS)
   {
      return ADC_STATUS_ERROR;
   }

   switch (adcResult.eStatus)
   {
      case ADC_RESULT_VALID:
         status = ADC_STATUS_SUCCESS;
         break;
      case ADC_RESULT_STALE:
         status = ADC_STATUS_STALE;
         break;
      case ADC_RESULT_TIMEOUT:
         status = ADC_STATUS_TIMEOUT;
         break;
      default:
         return ADC_STATUS_ERROR;
   }

   adc_result->physical = adcResult.nPhysical;
   adc_result->microvolts = adcResult.nMicrovolts;
   adc_result->code = adcResult.nCode;

   return status;
}

