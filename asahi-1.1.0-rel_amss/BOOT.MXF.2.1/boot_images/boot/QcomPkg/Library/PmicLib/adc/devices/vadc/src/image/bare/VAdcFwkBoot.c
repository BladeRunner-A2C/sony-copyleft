/*============================================================================
  FILE:         VAdcFwkBoot.c

  OVERVIEW:     VADC Device Layer framework file (bare-metal)

  DEPENDENCIES: None

                Copyright (c) 2022 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header:  $$DateTime: 2021/10/11 15:28:53 $$Author: pwbldsvc $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "DALSys.h"
#include "AdcDevice.h"
#include "VAdc.h"
#include "CoreVerify.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
VAdcDrvCtxt gVAdcDrvCtxt;

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
static AdcResult
VAdc_AdcDevice_Init(AdcDeviceHandle *h)
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;
   return VAdc_DeviceInit(pCtxt);
}

/*------------------------------------------------------------------------------
Following functions are extended in AdcDevice Interface.
------------------------------------------------------------------------------*/
AdcResult
VAdc_AdcDevice_GetInputProperties(
   AdcDeviceHandle *h,
   const char *pChannelName,
   uint32 *puChannelIdx
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_GetChannel(pCtxt,
                          pChannelName,
                          puChannelIdx);
}

AdcResult
VAdc_AdcDevice_GetDeviceProperties(
   AdcDeviceHandle *h,
   AdcDeviceDevicePropertiesType *pAdcDeviceProp
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_GetDeviceProperties(pCtxt, pAdcDeviceProp);
}

AdcResult
VAdc_AdcDevice_ReadChannel(
   AdcDeviceHandle *h,
   uint32 uChannelIdx,
   AdcDeviceResultType *pAdcDeviceReadResult
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_ReadChannel(pCtxt,
                           uChannelIdx,
                           pAdcDeviceReadResult);
}

AdcResult
VAdc_AdcDevice_ProcessConversionResult(
   AdcDeviceHandle *h,
   uint32 uChannelIdx,
   uint32 uAdcCode,
   AdcDeviceResultType *pAdcDeviceResult
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_ProcessConversionResult(pCtxt,
                                       uChannelIdx,
                                       uAdcCode,
                                       pAdcDeviceResult);
}

AdcResult
VAdc_AdcDevice_ProcessConversionResultInverse(
   AdcDeviceHandle *h,
   uint32 uChannelIdx,
   int32 nPhysical,
   AdcDeviceResultType *pAdcDeviceResult
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_ProcessConversionResultInverse(pCtxt,
                                              uChannelIdx,
                                              nPhysical,
                                              pAdcDeviceResult);
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
AdcResult
VAdc_AdcDevice_Attach(
   uint32 DeviceId,
   void **phDevice
   )
{
   AdcResult nErr;
   VAdcClientCtxt *pClientCtxt = NULL;
   AdcDeviceHandle **phAdcDevice = (AdcDeviceHandle **)phDevice;

   /* Allocate memory for the client context */
   nErr = DALSYS_Malloc(sizeof(VAdcClientCtxt), (void **)&pClientCtxt);
   if (DAL_SUCCESS != nErr || NULL == pClientCtxt)
   {
      return DAL_ERROR;
   }

   /* Device and client context reset */
   DALSYS_memset(pClientCtxt, 0, sizeof(VAdcClientCtxt));
   gVAdcDrvCtxt.dwNumDev = VADC_MAX_NUM_DEVICES;
   
   /* Initialize the Device Layer Interface and Client context */
   VAdc_InitInterface(pClientCtxt);
   pClientCtxt->pVAdcDevCtxt->DevId = DeviceId;
   *phAdcDevice = (AdcDeviceHandle *)&(pClientCtxt->AdcDeviceHandle);
   
   /* Call device_init now */
   VAdc_AdcDevice_Init((AdcDeviceHandle *)&(pClientCtxt->AdcDeviceHandle));

   return nErr;
}

