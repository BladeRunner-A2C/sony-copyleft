#ifndef __VADC_H__
#define __VADC_H__
/*============================================================================
  @file VAdc.h

  Function and data structure declarations for VADC device layer.


                Copyright (c) 2008-2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/dev/core.boot/6.1/hadigal.core.boot.6.1.kai_pmic_adc_boot_08/QcomPkg/Library/PmicLib/adc/devices/vadc/src/DalVAdc.h#1 $ */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "AdcDevice.h"
#include "VAdcBsp.h"
#include "VAdcLog.h"
#include "VAdcCommon.h"
#include "AdcScalingUtil.h"
#include "pm_gpio.h"
#include "pm_vadc.h"
#ifndef ADC_BOOT_DRIVER
#include "timer.h"
#include "pm_version_p.h"		/* Modem image */
#else
#include "pm_version.h"
#endif

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef enum
{
   VADC_AVERAGED_CHANNEL_STATE_UNKNOWN = 0,
   VADC_AVERAGED_CHANNEL_STATE_LOW,
   VADC_AVERAGED_CHANNEL_STATE_LOW_MED,
   VADC_AVERAGED_CHANNEL_STATE_MED,
   VADC_AVERAGED_CHANNEL_STATE_MED_HIGH,
   VADC_AVERAGED_CHANNEL_STATE_HIGH
} VAdcAveragedChannelStateType;

typedef struct
{
   uint32 uLowChannel;
   uint32 uMedChannel;
   uint32 uHighChannel;
   VAdcAveragedChannelStateType eState;
} VAdcAveragedChannelType;

/*
 * Declaring a "VAdc" Driver, device and client context
 */
typedef struct VAdcDrvCtxt VAdcDrvCtxt;
typedef struct VAdcDevCtxt VAdcDevCtxt;
typedef struct VAdcClientCtxt VAdcClientCtxt;


struct VAdcDevCtxt
{
   // VAdc Dev state can be added by developers here
   pm_device_info_type pmicDeviceInfo;              /* PMIC device info */
   VAdcDebugInfoType debug;                         /* debug structure */
   struct pm_vadc_device *pmicVAdcDev;              /* PMIC VADC device */
   const VAdcBspType *pBsp;                         /* pointer to the BSP */
   uint32 DevId;
   //VAdcAveragedChannelType *paAveragedChannels;     /* config for averaged channels. Comment out for bootloader */ 
   uint32 uDeviceIndex;                             /* device index */
   uint32 uTotalNumChannels;                        /* total number of channels */
   boolean bHardwareSupported;                      /* flag to indicate if the hardware is supported */
};

struct VAdcDrvCtxt
{
   // Base Members
   VAdcDevCtxt VAdcDevCtxt[VADC_MAX_NUM_DEVICES];
   uint32 dwNumDev;
   uint32 bInit;
};

/*
 * Declaring a "VAdc" Client Context
 */
struct VAdcClientCtxt
{
   // Base Members
   VAdcDevCtxt *pVAdcDevCtxt;
   AdcDeviceHandle AdcDeviceHandle;
};

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/

/* Functions specific to VADC - AdcDevice interface */
AdcResult VAdc_AdcDevice_Attach(uint32, void **);
void VAdc_InitInterface(VAdcClientCtxt *pclientCtxt);
AdcResult VAdc_AdcDevice_GetInputProperties(AdcDeviceHandle *h, const char *pChannelName, uint32 *puChannelIdx);
AdcResult VAdc_AdcDevice_GetDeviceProperties(AdcDeviceHandle *h, AdcDeviceDevicePropertiesType *pAdcDeviceProp);
AdcResult VAdc_AdcDevice_ReadChannel (AdcDeviceHandle *h, uint32 uChannelIdx, AdcDeviceResultType *pAdcDeviceReadResult);
AdcResult VAdc_AdcDevice_ProcessConversionResult(AdcDeviceHandle *h, uint32 uChannelIdx, uint32 uAdcCode, AdcDeviceResultType *pAdcDeviceResult);
AdcResult VAdc_AdcDevice_ProcessConversionResultInverse(AdcDeviceHandle *h, uint32 uChannelIdx, int32 nPhysical, AdcDeviceResultType *pAdcDeviceResult);


/* Internal Functions specific to VADC Device interface */
AdcResult VAdc_DeviceInit(VAdcClientCtxt *pCtxt);
AdcResult VAdc_SetDeviceIndex(VAdcClientCtxt *, uint32);
AdcResult VAdc_GetDeviceProperties(VAdcClientCtxt *, AdcDeviceDevicePropertiesType *);
AdcResult VAdc_GetChannel(VAdcClientCtxt *, const char *, uint32 *);
AdcResult VAdc_ReadChannel(VAdcClientCtxt *, uint32, AdcDeviceResultType *);
AdcResult VAdc_RecalibrateChannel(VAdcClientCtxt *, uint32, AdcDeviceRecalibrateResultType *);
AdcResult VAdc_ProcessConversionResult(VAdcClientCtxt *, uint32, uint32, AdcDeviceResultType *);
AdcResult VAdc_ProcessConversionResultInverse(VAdcClientCtxt *, uint32, int32, AdcDeviceResultType *);

#endif /* #ifndef __VADC_H__ */

