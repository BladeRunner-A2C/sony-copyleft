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
#ifndef __CHARGERLIB_FG_VIRTUAL_H__
#define __CHARGERLIB_FG_VIRTUAL_H__

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
typedef enum
{
  VFG_CHARGER_TYPE_NOT_USED,
  VFG_CHARGER_TYPE_SDP,
  VFG_CHARGER_TYPE_DCP,
  VFG_CHARGER_TYPE_CDP,
  VFG_CHARGER_TYPE_INVALID,
  VFG_CHARGER_TYPE_TYPEC_15,
  VFG_CHARGER_TYPE_TYPEC_30,
  VFG_CHARGER_TYPE_PD,
  VFG_CHARGER_TYPE_MAX
}VFG_CHARGER_TYPE;

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
EFI_STATUS FGVirtual_GetRelativeStateOfCharge(UINT32 *pCapacity);

/**
  Get Battery current from FG Module

  @param[OUT]   pCurrent        Return the battery current

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGVirtual_GetCurrent(INT16 *pCurrent);

/**
  Get Battery voltage from FG Module

  @param[OUT]  pVolage          Return the battery voltage

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGVirtual_GetVoltage(UINT16 *pVoltage);

/**
  Get Battery temperature from FG Module

  @param[OUT]   pTemperature   Return the battery temperature

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/

EFI_STATUS FGVirtual_GetTemperature(INT16 *pTemperature);

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
EFI_STATUS FGVirtual_GetChargingCurrent(UINT16* charging_current);

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
EFI_STATUS FGVirtual_GetChargingVoltage(UINT16* charging_voltage);

/**
  Get SFL connected status and battery detected from FG Module

  @param[OUT]   
  sfl_connected                 Return the suggested charging voltage
  battery_detected              Return the suggested charging current

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGVirtual_GetStatus(BOOLEAN* sfl_connected, BOOLEAN* battery_detected);

/**
  Get SFL voltage from FG Module

  @param[OUT]   
  voltage_mv                    Return SFL voltage in mv

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGVirtual_GetSFLVoltage(UINT16* voltage_mv);

/**
  Get SFL current from FG Module

  @param[OUT]   
  current_ma                    Return SFL current in mA

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS FGVirtual_GetSFLCurrent(UINT16* current_ma);
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
EFI_STATUS FGVirtual_GetBatteryPresent(BOOLEAN *present);

/**
  Get battery permanent failure active status from FG Module

  @param[OUT]   
  pActive                      Return permanent failure active status
  
  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/

EFI_STATUS FGVirtual_GetPFActive (BOOLEAN* pActive);

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

EFI_STATUS FGVirtual_GetBatteryChargeStatus (PFG_BATT_STATUS_DATA pFGBattSt);

EFI_STATUS FGVirtual_SetChargingStatus(UINT16 power_flag);

EFI_STATUS FGVirtual_SetInputParameters(UINT16 input_voltage_adc, UINT16 input_current_adc, UINT16 icl_final);

EFI_STATUS FGVirtual_SetActualFCCVFloat(UINT16 actual_fcc, UINT16 vfloat);

EFI_STATUS FGVirtual_SetTypeCPortPower(UINT8 port_number, UINT16 vbus_mv, UINT16 current_ma);

EFI_STATUS FGVirtual_SetTypeCPortStatus(UINT8 port_number, BOOLEAN connected, BOOLEAN pd_capable, UINT8 charger_type);

EFI_STATUS FGVirtual_GetTypeCPortPower(UINT8 port_number, UINT16 *vbus_mv, UINT16 *current_ma);

EFI_STATUS FGVirtual_GetTypeCPortStatus(UINT8 port_number, BOOLEAN *connected, BOOLEAN *pd_capable, UINT8 *charger_type);

EFI_STATUS FGVirtual_SetInterruptStatus(UINT8 PortUpdatedStatus);


#endif  /* __CHARGERLIB_FG_H__ */
