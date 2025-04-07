#ifndef _EFI_I2C_TP_H_
#define _EFI_I2C_TP_H_

/*
===========================================================================
*/
/**
  @file  Trackpad.h
  @brief Header file to enable I2C Trackpad  resources
*/
/* 
  ====================================================================
  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  ==================================================================== 
  
  ====================================================================
*/

/*=============================================================================
                              EDIT HISTORY


 when         who      what, where, why
 --------     ---      ----------------------------------------------------------
 10/15/22    rgotur   I2C Trackpad Inbox support and Device tree integration
 08/23/22    rgotur   Initial revision for UEFI I2C Trackpad Driver
=============================================================================*/

/*=========================================================================
      Include Files
==========================================================================*/
#include <Uefi.h>
#include <Protocol/EFIPmicGpio.h>
#include <api/pmic/pm/pm_version.h>

#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include "i2c_api.h"
#include "npa.h"
#include "pmapp_npa.h"

/*=========================================================================
      Macro Definitions
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/

/**
  Get power status.

  @param  none

  @retval EFI_SUCCESS             Unable to locate charger protocol or power status OK
  @retval EFI_OUT_OF_RESOURCES    Charger power status is not ok or at off mode charging
**/
EFI_STATUS 
I2CTpGetChargerPowerStatus(void);

#endif

