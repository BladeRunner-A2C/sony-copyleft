/**
@file  ChargerLibFG.h
@brief ChargerLib API definitions for FG module
*/
/*=============================================================================
Copyright (c) 2018 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
10/12/20   ivy     Initial Release
=============================================================================*/
#ifndef __CHARGERLIB_FG_BQ_H__
#define __CHARGERLIB_FG_BQ_H__

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/
#include <Uefi.h>
/**
  Library Dependencies
*/
#include <Library/UefiBootServicesTableLib.h>

/*===========================================================================*/
/*                  TYPEDEF AND MACRO DEFINITIONS                            */
/*===========================================================================*/


/*===========================================================================*/
/*                  FUNCTION PROTOTYPES                                      */
/*===========================================================================*/
/**
  Get Battery SOC from FG Module

  @param[OUT]   pCapacity       Return the battery SOC

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGBQ_GetRelativeStateOfCharge(UINT32 *pCapacity);

/**
  Get Battery current from FG Module

  @param[OUT]   pCurrent        Return the battery current

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGBQ_GetCurrent(INT16 *pCurrent);

/**
  Get Battery voltage from FG Module

  @param[OUT]  pVolage          Return the battery voltage

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGBQ_GetVoltage(UINT16 *pVoltage);

/**
  Get Battery temperature from FG Module

  @param[OUT]   pTemperature   Return the battery temperature

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/

EFI_STATUS FGBQ_GetTemperature(INT16 *pTemperature);

/**
  Get suggested charging current from FG Module

  @param[OUT]   
  pChargingCurrent              Return the suggested charging current

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGBQ_GetChargingCurrent(UINT16* charging_current);

/**
  Get suggested charging voltage from FG Module

  @param[OUT]   
  pChargingVoltage              Return the suggested charging voltage


  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGBQ_GetChargingVoltage(UINT16* charging_voltage);


/**
  Get manufacturer name from FG Module

  @param[OUT] manufacturer_name     Return the suggested charging voltage
  @param[IN] size                   size of the manufacturer_name
    

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGBQ_GetManufacturerName(UINT8 *manufacture_name, size_t size);

/**
  Set ship mode to FG Module    

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/EFI_STATUS FGBQ_SetShipMode();

/**
  Get battery PF Active

  @param[OUT]   bPFActive        Return the battery Permanent Failure Active status

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGBQ_GetPFActive(BOOLEAN *bPFActive);

/**
  Get battery pack permanent failure status

  @param[OUT]   PfStatus        Return the battery permanent failure status

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/

EFI_STATUS FGBQ_GetPFStatus(UINT32 *pPFStatus);

/**
  Get battery present from FG Module

  @param[OUT]   
  present                       Return battery present status
  
  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGBQ_GetBatteryPresent(BOOLEAN *present);

/**
  Get battery charge status from FG Module

  @param[OUT]   
  pFGBattSt                     Return battery charge status
  
  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/

EFI_STATUS FGBQ_GetBatteryChargeStatus (PFG_BATT_STATUS_DATA pFGBattSt);

#endif  /* __CHARGERLIB_FG_H__ */
