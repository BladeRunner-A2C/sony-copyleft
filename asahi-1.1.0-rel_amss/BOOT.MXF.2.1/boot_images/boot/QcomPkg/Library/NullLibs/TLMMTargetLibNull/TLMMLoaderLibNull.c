/** @file TlmmLib.c
  
  Stub Functions for TlmmLib

  Copyright (c) 2016, 2020,  2023 Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/24/23   as      Added GPIO functions      
 03/02/20   ck      Added TLMM_ConfigGpioGroup
 09/22/16   kpa     Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"
#include <DALStdDef.h>
#include <DALStdErr.h>
#include <DALFramework.h>
#include <DALSys.h>
#include <DALDeviceId.h>
#include <DDITlmm.h>
#include <GPIO.h>

/*===========================================================================
                      DATA DECLARATIONS
===========================================================================*/
typedef struct
{
} TLMMClientCtxt;


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 
/*===========================================================================

  FUNCTION TLMM_GPIO_INIT

  DESCRIPTION
        This function provides a stub to initialize the GPIOs for 
        the TLMM configuration specified at boot time.

  PARAMETERS
    None.

  DEPENDENCIES
    None.

  RETURN VALUE
    None.

  SIDE EFFECTS
    None

===========================================================================*/
boolean tlmm_gpio_init(void)
{
  return(TRUE);
}


/*==========================================================================

  FUNCTION      TLMM_ConfigGpioGroup

  DESCRIPTION   See DALTLMM.h

==========================================================================*/

DALResult TLMM_ConfigGpioGroup(TLMMClientCtxt*     pCtxt,
                               DALGpioEnableType   eEnable,
                               DALGpioSignalType*  eGpioGroup,
                               uint32              nSize)
{
  return DAL_SUCCESS;
}


DALResult Tlmm_ConfigGpioGroup(DALGpioEnableType  eEnable,
                               DALGpioSignalType* eGpioGroup, 
                               uint32             nSize)
{
  return DAL_SUCCESS;
}

/*==========================================================================
  FUNCTION      GPIO_Attach
  DESCRIPTION   See GPIO.h
==========================================================================*/

GPIOResult GPIO_Attach
(
  GPIODeviceIdType      eDevice,
  GPIOClientHandleType *pHandle
)
{
   return GPIO_SUCCESS;
}

/*==========================================================================
  FUNCTION      GPIO_RegisterPinExplicit
  DESCRIPTION   See GPIO.h
==========================================================================*/

GPIOResult GPIO_RegisterPinExplicit
(
  GPIOClientHandleType  Handle,
  uint32                nPinNumber,
  GPIOAccessType        AccessType,
  GPIOKeyType          *GPIOKey
)
{
  return GPIO_SUCCESS;
}

/*==========================================================================
  FUNCTION      GPIO_ReadPin
  DESCRIPTION   See GPIO.h
==========================================================================*/

GPIOResult GPIO_ReadPin
(
  GPIOClientHandleType Handle,
  GPIOKeyType          GPIOKey,
  GPIOValueType       *pValue
)
{
  return GPIO_SUCCESS;
}
