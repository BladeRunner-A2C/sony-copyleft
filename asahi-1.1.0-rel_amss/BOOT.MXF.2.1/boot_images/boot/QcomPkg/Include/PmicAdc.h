#ifndef __PMICADC_H__
#define __PMICADC_H__

/*============================================================================
  @file PmicAdc.h

  PMIC Voltage ADC Device Driver Interface header

  Clients may include this header and use these interfaces to read analog
  inputs.

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/dev/core.boot/6.1/hadigal.core.boot.6.1.lan_pmic_adc_boot_03/QcomPkg/Include/DDIAdc.h#1 $ */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "PmicAdcTypes.h"

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
/**
   @brief Attaches to the ADC driver

   This function attaches the client to the ADC driver. This function is used
   to obtain the device handle which is required to use the ADC driver APIs.

   @param  DevId [in] The device ID to attach to (e.g., AdcDEVICEID_ADC)
   @param  phDalDevice [out] Pointer to Adc device handle pointer which will receive
                             a pointer to the ADC device handle

   @return Adc_SUCCESS if the attach was successful. Other return values
           indicate that an error occurred.

*/
AdcResult
Adc_DeviceAttach(void);

/**
   @brief Detaches from the ADC driver

   This function detaches from the ADC driver.

   

   @return Adc_SUCCESS if the detach was successful. Other return values
           indicate that an error occurred.

*/
static __inline AdcResult
Adc_AdcDeviceDetach(DalDeviceHandle *_h)
{
   return ADC_SUCCESS;
}

/**
   @brief Gets the properties for an analog input from the ADC Adc properties

   This function looks up the properties for an analog input.

   @param  pInputName [in] The name of the analog input to look up
   @param  nInputNameSize [in] The size of the analog input name in bytes
   @param  pAdcInputProps [out] The buffer to write the property values to

   @return Adc_SUCCESS if the input was found. DAL_SUCCESS if the input was
      found in the properties file.

      ADC_ERROR_INVALID_PROPERTY_LENGTH is returned if the
      property was incorrectly defined.

      All other values correspond to Adc error codes, and should
      generally be interpreted to mean that the analog input is
      not present on the target hardware.

*/
AdcResult
Adc_GetAdcInputProperties(const char *pInputName,  uint32 nInputNameSize,  AdcInputPropertiesType *pAdcInputProps);

/**
   @brief Reads an analog input

   This function performs a blocking ADC read for the device and channel specified by the
   client in pAdcInputProps.

   @param  pAdcInputProps [in] Pointer to input properties for the channel
   @param  pAdcResult [out] ADC conversion result

   @see    Adc_AdcDeviceAttach

   @return Adc_SUCCESS if the request was successfully queued.

           Other return values indicate an error and include:
           ADC_ERROR_INVALID_DEVICE_IDX - the client specified an invalid device index
           ADC_ERROR_INVALID_CHANNEL_IDX - the client specified an invalid channel index
           ADC_ERROR_NULL_POINTER - pAdcInputProps or pAdcResult was NULL

*/
AdcResult
Adc_Read(  const AdcInputPropertiesType *pAdcInputProps,  AdcResultType *pAdcResult);

/**
   @brief Recalibrates an analog input

   This function requests the ADC driver to recalibrate the specified
   channel. If other channels share the physical device configuration
   (as defined in the ADC device BSP), then those channels may also be
   updated by the recalibration.

   @param  pAdcInputProps [in] Pointer to input properties for the channel
   @param  pAdcRecalResult [out] ADC recalibration result

   @see    Adc_AdcDeviceAttach

   @return Adc_SUCCESS if the request was successfully queued.

           Other return values indicate an error and include:
           ADC_ERROR_INVALID_DEVICE_IDX - the client specified an invalid device index
           ADC_ERROR_INVALID_CHANNEL_IDX - the client specified an invalid channel index
           ADC_ERROR_NULL_POINTER - pAdcParams was NULL
           ADC_ERROR_DEVICE_QUEUE_FULL - the device request queue was full

*/
AdcResult
Adc_Recalibrate(  const AdcInputPropertiesType *pAdcInputProps,  AdcRecalibrationResultType *pAdcRecalResult);

/**
   @brief Scales ADC code to usable values

   This function scales ADC code to usable values, including microvolts and physical values.
   Physical units for the different ADC channels are given in AdcInputs.h.

   
   @param  pAdcInputProps [in] Pointer to input properties for the channel
   @param  uAdcCode [in] The ADC code
   @param  pAdcResult [out] ADC conversion result

   @see    Adc_AdcDeviceAttach

   @return Adc_SUCCESS if the request was successfully queued.

           Other return values indicate an error and include:
           ADC_ERROR_INVALID_DEVICE_IDX - the client specified an invalid device index
           ADC_ERROR_INVALID_CHANNEL_IDX - the client specified an invalid channel index
           ADC_ERROR_NULL_POINTER - pAdcInputProps or pAdcResult was NULL

*/
AdcResult
Adc_ProcessConversionResult( const AdcInputPropertiesType *pAdcInputProps, uint32 uAdcCode, AdcResultType *pAdcResult);

/**
   @brief Scales a physical value to ADC code

   This function scales physical values to ADC code and other intermediate values, e.g. microvolts.
   Physical units for the different ADC channels are given in AdcInputs.h.

   
   @param  pAdcInputProps [in] Pointer to input properties for the channel
   @param  nPhysical [in] Physical value
   @param  pAdcResult [out] ADC conversion result

   @see    Adc_AdcDeviceAttach

   @return Adc_SUCCESS if the request was successfully queued.

           Other return values indicate an error and include:
           ADC_ERROR_INVALID_DEVICE_IDX - the client specified an invalid device index
           ADC_ERROR_INVALID_CHANNEL_IDX - the client specified an invalid channel index
           ADC_ERROR_NULL_POINTER - pAdcInputProps or pAdcResult was NULL

*/
AdcResult
Adc_ProcessConversionResultInverse( const AdcInputPropertiesType *pAdcInputProps, int32 nPhysical, AdcResultType *pAdcResult);

#endif

