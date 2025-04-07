#ifndef __VADCBSP_H__
#define __VADCBSP_H__
/*============================================================================
  @file VAdcBsp.h

  Function and data structure declarations for VADC DAL


                Copyright (c) 2017-2021 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/rel/core.boot/6.1.1/QcomPkg/Settings/ADC/interface/VAdcBsp.h#1 $ */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "AdcScalingBsp.h"
#include "SpmiTypes.h"
#include "pm_version.h"
#include "pm_gpio.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
#define VADC_REVISION(major, minor) (((major) << 8) | (minor))

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef enum
{
   VADC_DECIMATION_RATIO_256 = 0,
   VADC_DECIMATION_RATIO_512,
   VADC_DECIMATION_RATIO_1024
} VAdcDecimationRatioType;

typedef enum
{
   VADC_AVERAGE_1_SAMPLE = 0,
   VADC_AVERAGE_2_SAMPLES,
   VADC_AVERAGE_4_SAMPLES,
   VADC_AVERAGE_8_SAMPLES,
   VADC_AVERAGE_16_SAMPLES
} VAdcAverageModeType;

typedef enum
{
   VADC_SETTLING_DELAY_0_US = 0,
   VADC_SETTLING_DELAY_100_US,
   VADC_SETTLING_DELAY_200_US,
   VADC_SETTLING_DELAY_300_US,
   VADC_SETTLING_DELAY_400_US,
   VADC_SETTLING_DELAY_500_US,
   VADC_SETTLING_DELAY_600_US,
   VADC_SETTLING_DELAY_700_US,
   VADC_SETTLING_DELAY_800_US,
   VADC_SETTLING_DELAY_900_US,
   VADC_SETTLING_DELAY_1_MS,
   VADC_SETTLING_DELAY_2_MS,
   VADC_SETTLING_DELAY_4_MS,
   VADC_SETTLING_DELAY_6_MS,
   VADC_SETTLING_DELAY_8_MS,
   VADC_SETTLING_DELAY_10_MS,
   VADC_SETTLING_DELAY_16_MS,
   VADC_SETTLING_DELAY_32_MS,
   VADC_SETTLING_DELAY_64_MS,
   VADC_SETTLING_DELAY_128_MS
} VAdcSettlingDelay;

typedef enum
{
   VADC_CAL_METHOD_NO_CAL = 0,
   VADC_CAL_METHOD_RATIOMETRIC,
   VADC_CAL_METHOD_ABSOLUTE
} VAdcCalMethodType;

typedef struct
{
   char *pszName;
   uint32 uAdcHardwareChannel;
   VAdcSettlingDelay eSettlingDelay;
   VAdcAverageModeType eAverageMode;
   VAdcDecimationRatioType eDecimationRatio;
   VAdcCalMethodType eCalMethod;
   VAdcChannelScalingFactor scalingFactor;
   int32 nOffset;
   VAdcScalingMethodType eScalingMethod;
   uint32 uPullUp;
   uint32 uSlaveId;
   AdcIntTableType *pIntTable;
} VAdcChannelConfigType;

typedef struct
{
   uint8 *paucChannels;
   uint32 uNumChannels;
   pm_gpio_perph_index eGpio;
   uint32 uPmicId;
} VAdcGpioChannelMappingType;

typedef struct
{
   const char *pszName;
   const char *pszLowName;
   const char *pszMedName;
   const char *pszHighName;
   int32 nMedToLow;
   int32 nLowToMed;
   int32 nHighToMed;
   int32 nMedToHigh;
} VAdcAveragedChannelConfigType;

typedef struct VAdcBspType
{
   const char *pszDTPath;
   VAdcChannelConfigType *paChannels;
   uint32 *puNumChannels;
   VAdcAveragedChannelConfigType *paAveragedChannels;
   uint32 *puNumAveragedChannels;
   VAdcGpioChannelMappingType *paGpioChannelMappings;
   uint32 uNumGpioChannelMappings;
   uint32 uFullScale_code;
   uint32 uFullScale_uV;
   uint32 uFullRatiometric_code;
   uint32 uReadTimeout_us;
   uint32 uLDOSettlingTime_us;
   uint32 uSlaveId;
   uint32 uPeripheralId;
   uint32 uMasterID;
   uint8 uBusId;
   uint8 ucPmicDevice;
   boolean bUsesInterrupts;
} VAdcBspType;

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/

#endif /* #ifndef __VADCBSP_H__ */

