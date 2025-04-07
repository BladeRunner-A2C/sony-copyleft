#ifndef __PMICADCTYPES_H__
#define __PMICADCTYPES_H__

/*============================================================================
  @file PmicAdcTypes.h

  ADC Device Driver Interface header

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
#include "AdcInputs.h"
#include "DALSys.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
enum
{
   ADC_ERROR_INVALID_DEVICE_IDX = 1,
   ADC_ERROR_INVALID_CHANNEL_IDX,
   ADC_ERROR_NULL_POINTER,
   ADC_ERROR_DEVICE_QUEUE_FULL,
   ADC_ERROR_INVALID_PROPERTY_LENGTH,
   ADC_ERROR_OUT_OF_MEMORY,
   ADC_ERROR_API_UNSUPPORTED_IN_THIS_CONTEXT,
   ADC_ERROR_DEVICE_NOT_READY,
   ADC_ERROR_INVALID_PARAMETER,
   ADC_ERROR_OUT_OF_TM_CLIENTS,
   ADC_ERROR_TM_NOT_SUPPORTED,
   ADC_ERROR_TM_THRESHOLD_OUT_OF_RANGE,
   ADC_ERROR_TM_BUSY,
   _ADC_MAX_ERROR = 0x7FFFFFFF
};

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef uint32 AdcResult; 

enum {
   ADC_SUCCESS,
   ADC_ERROR = -1,
   ADC_DEVICE_NOT_SUPPORTED = -2,
};

typedef enum
{
   ADC_RESULT_INVALID,
   ADC_RESULT_VALID,
   ADC_RESULT_TIMEOUT,
   ADC_RESULT_STALE,
   _ADC_MAX_RESULT_STATUS = 0x7FFFFFFF
} AdcResultStatusType;

typedef struct
{
   enum
   {
      ADC_REQUEST_STATUS_PENDING,   /* the request is being immediately performed */
      ADC_REQUEST_STATUS_QUEUED,    /* the request was queued */
      ADC_REQUEST_STATUS_ERROR,     /* the request was not started due to an error */
      ADC_REQUEST_STATUS_UNKNOWN,   /* the request status is unknown */
      _ADC_MAX_REQUEST_STATUS = 0x7FFFFFFF
   } eStatus;
} AdcRequestStatusType;

typedef struct
{
   uint32 nDeviceIdx;
   uint32 nChannelIdx;
} AdcInputPropertiesType;

typedef struct
{
   uint32 nDeviceIdx;
   uint32 nChannelIdx;
   DALSYSEventHandle hEvent;
} AdcRequestParametersType;

typedef struct
{
   AdcResultStatusType eStatus;  /* status of the conversion */
   uint32 nDeviceIdx;   /* the device index for this conversion */
   uint32 nChannelIdx;  /* the channel index for this conversion */
   int32 nPhysical;     /* result in physical units. Units depend on BSP */
   uint32 nPercent;     /* result as percentage of reference voltage used
                         * for conversion. 0 = 0%, 65535 = 100% */
   uint32 nMicrovolts;  /* result in microvolts */
   uint32 nCode;        /* raw ADC code from hardware */
} AdcResultType;

typedef struct
{
   AdcResultStatusType eStatus;  /* status of the conversion */
   uint32 uToken;       /* token which identifies this conversion */
   uint32 uDeviceIdx;   /* the device index for this conversion */
   uint32 uChannelIdx;  /* the channel index for this conversion */
   int32 nPhysical1_uV; /* ref 1 in physical units of uV*/
   int32 nPhysical2_uV; /* ref 2 in physical units of uV */
   uint32 uCode1;       /* raw ADC code for ref 1 */
   uint32 uCode2;       /* raw ADC code for ref 2 */
} AdcRecalibrationResultType;

typedef struct
{
   uint32 uDeviceIdx;
   uint32 uChannelIdx;
} AdcTMInputPropertiesType;

typedef struct
{
   AdcTMInputPropertiesType adcTMInputProps;
   DALSYSEventHandle hEvent;
} AdcTMRequestParametersType;

typedef enum
{
   ADC_TM_THRESHOLD_LOWER,    /* Lower threshold */
   ADC_TM_THRESHOLD_HIGHER,   /* Higher threshold */
   _ADC_TM_NUM_THRESHOLDS,
   _ADC_TM_MAX_THRESHOLD = 0x7FFFFFFF
} AdcTMThresholdType;

typedef struct
{
   int32 nPhysicalMin;   /* Minimum threshold in physical units */
   int32 nPhysicalMax;   /* Maximum threshold in physical units */
} AdcTMRangeType;

typedef struct
{
   AdcTMInputPropertiesType adcTMInputProps;   /* TM device and channel indexes */
   AdcTMThresholdType eThresholdTriggered;     /* Type of threshold that triggered */
   int32 nPhysicalTriggered;                   /* Physical value that triggered */
} AdcTMCallbackPayloadType;

typedef enum
{
   ADC_FG_THRESH_SKIN_HOT,        /* Skin temperature hot threshold */
   ADC_FG_THRESH_SKIN_TOO_HOT,    /* Skin temperature too hot threshold */
   ADC_FG_THRESH_CHARGER_HOT,     /* Charger temperature hot threshold */
   ADC_FG_THRESH_CHARGER_TOO_HOT, /* Charger temperature too hot threshold */
   _ADC_FG_MAX_THRESH = 0x7FFFFFFF
} AdcFGThresholdType;

#endif

