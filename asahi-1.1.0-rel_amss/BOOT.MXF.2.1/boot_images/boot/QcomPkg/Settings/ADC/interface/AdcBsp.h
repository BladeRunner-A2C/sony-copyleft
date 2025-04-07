#ifndef __ADC_BSP_H__
#define __ADC_BSP_H__
/*============================================================================
  @file AdcBsp.h

  Function and data structure declarations for ADC's BSP


               Copyright (c) 2013, 2014, 2019-2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Qualcomm Technologies Confidential and Proprietary.
============================================================================*/
/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "com_dtypes.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
#define VADC_DEVICE_ID  0
#define DEVICE_ID_BSHFT 16

#define ADC_DEVICE_ID_SET(val) ((VADC_DEVICE_ID << DEVICE_ID_BSHFT) | val)

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef union
{
   const char *pszDevName;
   uint32 eDeviceId;
} AdcPhysicalDeviceType;

typedef struct
{
   const AdcPhysicalDeviceType *paAdcPhysicalDevices;
   uint32 uNumDevices;
} AdcBspType;

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/

#endif /* #ifndef __ADC_BSP_H__ */

