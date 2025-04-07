/*============================================================================
  FILE:         VAdcFwkCoreInf.c

  OVERVIEW:     VADC Device Layer framework Interface file (bare-metal)

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

  $Header: //components/rel/core.boot/6.1/QcomPkg/Library/PmicLib/adc/devices/vadc/src/DalVAdcFwk.c#1 $$DateTime: 2021/10/11 15:28:53 $$Author: pwbldsvc $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
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
extern VAdcDrvCtxt gVAdcDrvCtxt;

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Following functions are extended in AdcDevice Interface.
------------------------------------------------------------------------------*/
static AdcResult
VAdc_AdcDevice_RecalibrateChannel(
   AdcDeviceHandle *h,
   uint32 uChannelIdx,
   AdcDeviceRecalibrateResultType *pAdcDeviceRecalibrateResult
   )
{
   VAdcClientCtxt *pCtxt = h->pClientCtxt;

   return VAdc_RecalibrateChannel(pCtxt,
                                  uChannelIdx,
                                  pAdcDeviceRecalibrateResult);
}

void
VAdc_InitInterface(VAdcClientCtxt *pclientCtxt)
{
   static uint32 devCtxtIndex = 0;
   static const AdcDevice vtbl =
   {
      VAdc_AdcDevice_GetInputProperties,
      VAdc_AdcDevice_GetDeviceProperties,
      VAdc_AdcDevice_ReadChannel,
      VAdc_AdcDevice_ProcessConversionResult,
      VAdc_AdcDevice_ProcessConversionResultInverse,
      VAdc_AdcDevice_RecalibrateChannel,
   };
   /*--------------------------------------------------------------------------
     Depending upon client type setup the vtables (entry points)
     --------------------------------------------------------------------------*/
   CORE_VERIFY(devCtxtIndex < gVAdcDrvCtxt.dwNumDev);
   pclientCtxt->pVAdcDevCtxt = &gVAdcDrvCtxt.VAdcDevCtxt[devCtxtIndex++];
   pclientCtxt->AdcDeviceHandle.pVtbl  = &vtbl;
   pclientCtxt->AdcDeviceHandle.pClientCtxt = pclientCtxt;
}

