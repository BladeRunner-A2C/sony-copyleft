#ifndef __ADCDEVICE_H__
#define __ADCDEVICE_H__
/*============================================================================
  @file AdcDevice.h

  ADC Physical Device Driver Interface header

  This header is to be included solely by the ADC and implementations of
  this DDI. It provides a common interface for the ADC DAL to interface with
  different ADC hardware.

  External clients may not access these interfaces.

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
  $Header: $ 
============================================================================*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "AdcDeviceTypes.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
#define ADC_DEVICEID_MASK     0xFFFF0000
#define ADC_DEVICEID_BSHFT    16
#define ADC_DEVICE_INDEX_MASK 0x0000FFFF

#define ADC_DEVICE_ID(dev_id)    ((dev_id & ADC_DEVICEID_MASK) >> ADC_DEVICEID_BSHFT)
#define ADC_DEVICE_INDEX(dev_id) (dev_id & ADC_DEVICE_INDEX_MASK)
/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
struct AdcDevice;
typedef struct AdcDevice AdcDevice;

typedef struct AdcDeviceHandle AdcDeviceHandle;
struct AdcDeviceHandle
{
   const AdcDevice *pVtbl;
   void *pClientCtxt;
};

struct AdcDevice
{
   AdcResult (*GetInputProperties)(AdcDeviceHandle * _h, const char * pChannelName, uint32 *);
   AdcResult (*GetDeviceProperties)(AdcDeviceHandle * _h, AdcDeviceDevicePropertiesType *pAdcDeviceProp);
   AdcResult (*ReadChannel)(AdcDeviceHandle * _h, uint32 uChannelIdx, AdcDeviceResultType *);
   AdcResult (*ProcessConversionResult)(AdcDeviceHandle *_h, uint32 uChannelIdx, uint32 uAdcCode, AdcDeviceResultType *pAdcDeviceResult);
   AdcResult (*ProcessConversionResultInverse)(AdcDeviceHandle *_h, uint32 uChannelIdx, int32 nPhysical, AdcDeviceResultType *pAdcDeviceResult);
   AdcResult (*RecalibrateChannel)(AdcDeviceHandle * _h, uint32  uChannelIdx, AdcDeviceRecalibrateResultType *);
};

struct AdcDeviceInitCtxtType {
  AdcResult (*VAdc_Attach)(uint32, void **);
};

typedef enum {
  ADC_DEVICE_VADC,
  //ADC_DEVICE_VADCTM, /* commented for bootloader */
  ADC_DEVICE_MAX,
}AdcDeviceId;
/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/

/**
   @brief Attaches to the ADC physical device driver

   This function attaches the client to the physical ADC device driver.
   This function is used to obtain the device handle which is required to
   use the driver APIs.

   @param  pszDevName [in] The device ID string to attach to
   @param  hAdcDevice [out] Pointer to DAL device handle pointer which will receive a pointer to the ADC device handle

   @return DAL_SUCCESS if the attach was successful. Other return values
           indicate that an error occurred.

*/
#define AdcDevice_DeviceAttach(uDeviceId, hAdcDevice)\
        AdcDevice_Attach((ADC_DEVICE_ID(uDeviceId)), ADC_DEVICE_INDEX(uDeviceId), hAdcDevice)

AdcResult AdcDevice_Attach(AdcDeviceId DeviceId, uint32 device_index, void **phAdcDevice);

/**
   @brief Gets the number of channels defined for this device

   @param  _h [in] Device handle obtained from AdcDevice_DeviceAttach
   @param  pAdcDeviceProp [out] Pointer to result data

   @see    AdcDevice_DeviceAttach

   @return DAL_SUCCESS if successful.

*/
static __inline AdcResult
AdcDevice_GetDeviceProperties(AdcDeviceHandle * _h, AdcDeviceDevicePropertiesType *pAdcDeviceProp)
{
   return (_h)->pVtbl->GetDeviceProperties( _h, pAdcDeviceProp);
}

/**
   Determine whether the channel is supported by the device.

   @param  _h [in] Device handle obtained from AdcDevice_DeviceAttach
   @param  pChannelName [in] NULL-terminated channel name
   @param  puChannelIdx [out] Channel index

   @see    AdcDevice_DeviceAttach

   @return DAL_SUCCESS if successful.

*/
static __inline AdcResult
AdcDevice_GetInputProperties(AdcDeviceHandle * _h, const char *pChannelName, uint32 *puChannelIdx)
{
   return (_h)->pVtbl->GetInputProperties( _h, pChannelName, puChannelIdx);
}

#ifndef ADC_LOADER_DRIVER
/**
   @brief Recalibrates a specific channel

   This function is used to calibrate a specific channel. If multiple channels
   use the same configuration, then those channels will also be recalibrated.

   @param  _h [in] Device handle obtained from AdcDevice_DeviceAttach
   @param  uChannelIdx [in] The index of the channel to recalibrate
   @param  pAdcDeviceRecalibrateResult [out] Recalibration result

   @see    AdcDevice_DeviceAttach

   @return DAL_SUCCESS if successful.

*/
static __inline AdcResult
AdcDevice_RecalibrateChannel(AdcDeviceHandle *_h, uint32 uChannelIdx, AdcDeviceRecalibrateResultType *pAdcDeviceRecalibrateResult)
{
   return (_h)->pVtbl->RecalibrateChannel( _h, uChannelIdx, pAdcDeviceRecalibrateResult);
}
#endif

/**
   @brief Reads an ADC channel

   This function is used to read an ADC channel.

   @param  _h [in] Device handle obtained from AdcDevice_DeviceAttach
   @param  uChannelIdx [in] The index of the channel to recalibrate
   @param  pAdcDeviceReadResult [out] Read result

   @see    AdcDevice_DeviceAttach

   @return DAL_SUCCESS if successful.

*/
static __inline AdcResult
AdcDevice_ReadChannel(AdcDeviceHandle *_h, uint32 uChannelIdx, AdcDeviceResultType *pAdcDeviceReadResult)
{
   return (_h)->pVtbl->ReadChannel( _h, uChannelIdx, pAdcDeviceReadResult);
}

/**
   @brief Scales ADC code to usable values

   This function scales ADC code to usable values, including microvolts and physical values.
   Physical units for the different ADC channels are given in AdcInputs.h.

   @param  _h [in] Handle to the ADC driver instance instantiated by AdcDevice_DeviceAttach
   @param  uChannelIdx [in] Which channel
   @param  uAdcCode [in] The ADC code
   @param  pAdcDeviceResult [out] ADC conversion result

   @see    AdcDevice_DeviceAttach

   @return DAL_SUCCESS if the request was successfully queued.

*/
static __inline AdcResult
AdcDevice_ProcessConversionResult(AdcDeviceHandle *_h, uint32 uChannelIdx, uint32 uAdcCode, AdcDeviceResultType *pAdcDeviceResult)
{
   return (_h)->pVtbl->ProcessConversionResult( _h, uChannelIdx, uAdcCode, pAdcDeviceResult);
}

/**
   @brief Scales a physical value to ADC code

   This function scales physical values to ADC code and other intermediate values, e.g. microvolts.
   Physical units for the different ADC channels are given in AdcInputs.h.

   @param  _h [in] Handle to the ADC driver instance instantiated by AdcDevice_DeviceAttach
   @param  uChannelIdx [in] Which channel
   @param  nPhysical [in] Physical value
   @param  pAdcDeviceResult [out] ADC conversion result

   @see    AdcDevice_DeviceAttach

   @return DAL_SUCCESS if the request was successfully queued.

*/
static __inline AdcResult
AdcDevice_ProcessConversionResultInverse(AdcDeviceHandle *_h, uint32 uChannelIdx, int32 nPhysical, AdcDeviceResultType *pAdcDeviceResult)
{
   return (_h)->pVtbl->ProcessConversionResultInverse( _h, uChannelIdx, nPhysical, pAdcDeviceResult);
}

#endif

