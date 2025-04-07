#ifndef __ADCDEVICETYPES_H__
#define __ADCDEVICETYPES_H__
/*============================================================================
  @file AdcDeviceTypes.h

  ADC Physical Device TypeDefs 

  This header provides a common interface for the ADC typedefs to interface with
  different ADC hardware.

  External clients may not access these interfaces.

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/rel/core.boot/6.1/QcomPkg/Library/PmicLib/adc/devices/common/protected/DDIAdcDevice.h#2 $ 
 * $DateTime: $
 */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "com_dtypes.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef uint32 AdcResult;

enum
{
   ADC_DEVICE_ERROR_OUT_OF_TM_CLIENTS = 1,
   ADC_DEVICE_ERROR_TM_NOT_SUPPORTED,
   ADC_DEVICE_ERROR_TM_THRESHOLD_OUT_OF_RANGE,
   ADC_DEVICE_ERROR_TM_INVALID_MEAS_IDX,
   ADC_DEVICE_ERROR_TM_BUSY,
   ADC_DEVICE_ERROR_FG_NOT_SUPPORTED
};

typedef enum
{
   ADC_DEVICE_CHANNEL_READY,
   ADC_DEVICE_CHANNEL_BUSY,
   ADC_DEVICE_CHANNEL_CALIBRATING,
   ADC_DEVICE_CHANNEL_ERROR,
   _ADC_MAX_DEVICE_CHANNEL_STATUS = 0x7FFFFFFF
} AdcDeviceChannelStatusType;

typedef enum
{
   ADC_DEVICE_RESULT_VALID,
   ADC_DEVICE_RESULT_INVALID,
   ADC_DEVICE_RESULT_INVALID_CHANNEL,
   ADC_DEVICE_RESULT_TIMEOUT,
   ADC_DEVICE_RESULT_STALE,
   _ADC_MAX_DEVICE_RESULT_STATUS = 0x7FFFFFFF
} AdcDeviceResultStatusType;

typedef struct
{
   uint32 uNumChannels;      /* number of ADC channels */
   uint32 uNumMeas;          /* number of TM measurements */
} AdcDeviceDevicePropertiesType;

typedef struct
{
   AdcDeviceResultStatusType eStatus;
   int32 nPhysical1_uV;    /* ref 1 in microvolts */
   int32 nPhysical2_uV;    /* ref 2 in microvolts */
   uint32 uCode1;          /* raw ADC code for ref 1 */
   uint32 uCode2;          /* raw ADC code for ref 2 */
} AdcDeviceRecalibrateResultType;

typedef struct
{
   AdcDeviceResultStatusType eStatus;
   int32 nPhysical;     /* result in physical units. Units depend on BSP */
   uint32 uPercent;     /* result as percentage of reference voltage used
                         * for conversion. 0 = 0%, 65535 = 100% */
   uint32 uMicrovolts;  /* result in microvolts */
   uint32 uCode;        /* raw ADC code */
} AdcDeviceResultType;

typedef struct
{
   int32 nPhysicalMin;   /* Minimum threshold in physical units */
   int32 nPhysicalMax;   /* Maximum threshold in physical units */
} AdcDeviceTMRangeType;

typedef enum
{
   ADC_DEVICE_TM_THRESHOLD_LOWER,    /* Lower threshold */
   ADC_DEVICE_TM_THRESHOLD_HIGHER,   /* Higher threshold */
   ADC_DEVICE_TM_NUM_THRESHOLDS
} AdcDeviceTMThresholdType;


#endif

