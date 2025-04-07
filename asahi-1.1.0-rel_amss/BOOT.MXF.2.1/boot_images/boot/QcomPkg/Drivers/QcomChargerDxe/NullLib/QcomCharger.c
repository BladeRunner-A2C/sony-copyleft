/** @file QcomCharger.c

  Implements the QUALCOMM Charger protocol

  Copyright (c) 2016-2019,  Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


when         who     what, where, why
--------     ---     -----------------------------------------------------------
08/12/22     cs     Initial draft

=============================================================================*/
#include <Uefi.h>

/**
  EFI interfaces
 */
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

/**
  Charger PROTOCOL interface
 */
#include <Protocol/EFIQcomCharger.h>

/**
  EFI interfaces
 */
 #include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include <api/pmic/pm/pm_uefi.h>

/**
  Protocol Dependencies
*/
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIPmicVersion.h>
#include <Library/QcomTargetLib.h>

/**
  ADC Dependencies
 */
#include <Protocol/EFIAdc.h>

/**
  Ext HW Dependencies
*/


#include <api/pmic/charger/ChargerLibCommon.h>

EFI_QCOM_CHARGER_PROTOCOL QcomChargerProtocolImplementation;

/*===========================================================================*/
/*                  FUNCTIONS PROTOTYPES                                     */
/*===========================================================================*/
/**
EFI_QcomChargerInit()

@brief
Initializes charger module
*/
EFI_STATUS QcomChargerInitialize(IN EFI_HANDLE         ImageHandle,
                             IN EFI_SYSTEM_TABLE   *SystemTable)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(EFI_SUCCESS == Status)
  {
    Status = gBS->InstallMultipleProtocolInterfaces( &ImageHandle,
                                                      &gQcomChargerProtocolGuid,
                                                      &QcomChargerProtocolImplementation,
                                                      NULL );
  }

  return Status;
}

/**
EFI_QcomChargerEnableCharging()

@brief
Enables charging
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerEnableCharging
(
  IN BOOLEAN Enable
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}

/**
EFI_QcomChargerSetMaxUsbCurrent()

@brief
Set maximum USB current
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerSetMaxUsbCurrent
(
  IN UINT32 MaxCurrent
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  MaxCurrent = 100;

  return Status;
}

/**
EFI_QcomChargerGetMaxUsbCurrent()

@brief
Gets maximum USB current from config file
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetMaxUsbCurrent
(
  OUT UINT32 *pMaxCurrent
)
{
  return EFI_UNSUPPORTED;
}

/**
EFI_QcomChargerGetChargingStatus()

@brief
Initializes charger module
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetChargingAction
(
  EFI_QCOM_CHARGER_ACTION_TYPE  *pChargingAction,
  EFI_QCOM_CHARGER_ACTION_INFO  *pChargerActionInfo,
  BOOLEAN vbattChecking
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(NULL == pChargingAction)
  {
    return EFI_INVALID_PARAMETER;
  }

  return Status;
}


/**
EFI_QcomChargerTakeAction()

@brief
Initializes charger module
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerTakeAction
(
  EFI_QCOM_CHARGER_ACTION_TYPE ChargingAction,
  CONST EFI_QCOM_CHARGER_ACTION_INFO *pChargerActionInfo
)
{
  EFI_STATUS Status = EFI_SUCCESS;


  return Status;
}

EFI_STATUS
EFIAPI
EFI_QcomChargerDisplayImage
(
  IN EFI_QCOM_CHARGER_DISP_IMAGE_TYPE ImageType,
  IN BOOLEAN ClearScreen
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  /* Display functionality is moved to charger app */
  return Status;
}


EFI_STATUS
EFIAPI
EFI_QcomChargerDeInitialize
(
  EFI_QCOM_CHARGER_ACTION_TYPE ChargingAction
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}



/**
EFI_QcomChargerGetBatteryPresence ()

@brief
Get battery presence status
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetBatteryPresence
(
  OUT BOOLEAN  *pBatteryPresent
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(NULL == pBatteryPresent)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pBatteryPresent = TRUE;

  return Status;
}

/**
EFI_QcomChargerGetBatteryVoltage ()

@brief
Returns battery voltage
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetBatteryVoltage
(
  OUT UINT32  *pBatteryVoltage
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(NULL == pBatteryVoltage)
  {
    return EFI_INVALID_PARAMETER;
  }
  *pBatteryVoltage = 8000;

  return Status;
}

/**
EFI_QcomChargerGetFileLogInfo ()

@brief
Returns Charger Log File handle information
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetFileLogInfo
(
  OUT EFI_QCOM_CHARGER_LOG_INFO *pFileLogInfo
)
{
  EFI_STATUS                     Status = EFI_SUCCESS;

  if(NULL == pFileLogInfo)
  {
    return EFI_INVALID_PARAMETER;
  }

  return Status;
}

/**
EFI_QcomChargerDumpPeripheral ()

@brief
Debug Prints Charger Fg Peripheral
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerDumpPeripheral( )
{
  EFI_STATUS Status = EFI_SUCCESS;
  return Status;
}

/**
EFI_QcomChargerIsDcInValid ()

@brief
get if dcin is valid or not
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerIsDcInValid(BOOLEAN* pIsDcInValid)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (!pIsDcInValid)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pIsDcInValid = FALSE;

  return Status;
}



/**
EFI_QcomChargerGetChargerConfig ()

@brief
Returns Charger Log File handle information
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetChargerConfig
(
  IN EFI_QCOM_CHARGER_CONFIG_KEY  ChargerCfgKey,
  OUT  UINT32 *KeyValue
)
{
  EFI_STATUS                     Status = EFI_SUCCESS;
  if(NULL == KeyValue)
  {
    return EFI_INVALID_PARAMETER;
  }

  *KeyValue = 0;

  return Status;
}

/**
EFI_QcomChargerIsChargingSupported ()

@brief
Returns If Charger is supported based on platform, configuration and run-time detection
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerIsChargingSupported
(
  OUT  BOOLEAN *pIsChargingSupported
)
{
    //Calling Library API to check if this platform support charging or not
    EFI_STATUS                     Status = EFI_SUCCESS;
    *pIsChargingSupported = FALSE;
    return Status;
}


/**
EFI_QcomChargerGetDisplayImageType ()

@brief
  Returns the image to be diplayed
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetDisplayImageType
(
  OUT  EFI_QCOM_CHARGER_DISP_IMAGE_TYPE *pDispImage
)
{
    //Calling Library API to get the image to be displayed
    EFI_STATUS  Status = EFI_SUCCESS;
    return Status;
}

/**
EFI_QcomChargerGetPonReason ()

@brief
  Returns the PON reason
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetPonReason
(
  OUT EFI_QCOM_CHARGER_PWRON_REASON_TYPE *pPwrOnReason
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    if(pPwrOnReason == NULL) { return EFI_INVALID_PARAMETER; }

    return Status;
}

/**
EFI_QcomChargerGetControlAction ()

@brief
  Returns the boot flow control action
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetControlAction
(
  OUT EFI_CHARGER_CONTROL_ACTION_TYPE *pControlAction
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    if(pControlAction == NULL) { return EFI_INVALID_PARAMETER; }

    return Status;
}

/**
EFI_QcomChargerGetControlAction ()

@brief
  Returns the boot flow control action
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerSetControlAction
(
  IN EFI_CHARGER_CONTROL_ACTION_TYPE controlAction
)
{
    EFI_STATUS Status = EFI_SUCCESS;

    return Status;
}

/**
EFI_QcomChargerGetBatteryType ()

@brief
Returns battery type
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetBatteryType
(
  OUT UINT32  *pBatteryType
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(NULL == pBatteryType)
  {
    return EFI_INVALID_PARAMETER;
  }
  *pBatteryType = (UINT32)CHG_BATT_TYPE_DEBUG_BOARD;

  return Status;
}

/**
EFI_QcomChargerGetBatterySOC ()

@brief
Returns battery SOC
*/
EFI_STATUS
EFIAPI
EFI_QcomChargerGetBatterySOC
(
  OUT UINT32* pBatterySOC
)
{
  EFI_STATUS Status = EFI_SUCCESS;
    
  if(NULL == pBatterySOC)
  {
    return EFI_INVALID_PARAMETER;
  }
  *pBatterySOC = 100;
    
  return Status;
}

/**
EFI_QcomChargerGetBarrelChargerStatus ()

@brief
Returns barrel charger connection, voltage, and current
*/

EFI_STATUS 
EFIAPI
EFI_QcomChargerGetBarrelChargerStatus
(
  OUT BOOLEAN* pConnected, 
  OUT UINT16*  pCharger_max_voltage_mv, 
  OUT UINT16*  pCharger_max_current_ma
)
{
  if (NULL == pConnected || NULL == pCharger_max_voltage_mv || NULL == pCharger_max_current_ma)
  {
    return EFI_INVALID_PARAMETER;
  }

   *pConnected = FALSE;
   *pCharger_max_voltage_mv = 0;
   *pCharger_max_current_ma = 0;
   return EFI_SUCCESS;

  return EFI_SUCCESS;
}

/**
EFI_QcomChargerLoggingTimerExit ()

@brief
Closes chargerPD logging timer event, if enabled
*/

EFI_STATUS
EFIAPI
EFI_QcomChargerLoggingTimerExit
(
  EFI_QCOM_CHARGER_ACTION_TYPE ChargingAction
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  return Status;
}

/**
  PMIC FG UEFI Protocol implementation
 */
EFI_QCOM_CHARGER_PROTOCOL QcomChargerProtocolImplementation =
{
  QCOM_CHARGER_REVISION,
  EFI_QcomChargerEnableCharging,
  EFI_QcomChargerGetMaxUsbCurrent,
  EFI_QcomChargerSetMaxUsbCurrent,
  EFI_QcomChargerGetChargingAction,
  EFI_QcomChargerTakeAction,
  EFI_QcomChargerDisplayImage,
  EFI_QcomChargerGetBatteryPresence,
  EFI_QcomChargerGetBatteryVoltage,
  EFI_QcomChargerDeInitialize,
  EFI_QcomChargerGetFileLogInfo,
  EFI_QcomChargerDumpPeripheral,
  EFI_QcomChargerIsDcInValid,
  EFI_QcomChargerGetChargerConfig,
  EFI_QcomChargerIsChargingSupported,
  EFI_QcomChargerGetDisplayImageType,
  EFI_QcomChargerGetPonReason,
  EFI_QcomChargerGetControlAction,
  EFI_QcomChargerSetControlAction,
  EFI_QcomChargerGetBatteryType,
  EFI_QcomChargerGetBatterySOC,
  EFI_QcomChargerGetBarrelChargerStatus,
  EFI_QcomChargerLoggingTimerExit,
};
