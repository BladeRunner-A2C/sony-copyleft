/** @file QcomCharger.c

  Implements the QUALCOMM Charger protocol

  Copyright (c) 2016-2019,  Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


when         who     what, where, why
--------     ---     -----------------------------------------------------------
07/12/17     cs      added images for debug board cases.
06/21/17     dc      Move Platform Check to QcomChargerDxe and support config override
04/24/17     va      Enable Charger App Changes - to be enabled later
03/30/17     ll      Implemented level file-logging
03/07/17     cs      remove duplicate get errors checking emergency shutdown condition.
02/07/17     sm      Added changes to skip installing QcomChargerDXE protocol for CLS platform
02/07/17     sm      Checking return status for ChargerLib_GetBatteryStatus
11/09/16     cs      modified charger present API also to detect DCIn.
09/13/16     sm      Marked EFI_QcomChargerGetMaxUsbCurrent() as Unsupported
06/23/16     va      Adding Action Info for taking Action
06/23/16     va      Adding support for Charger Fg Peripheral dumps
06/14/16     va      Adding File log support to Charger App
06/03/16     va      Update for early sign of life during profile load
06/01/16     sm      Added wrapper APIs for battery presence and battery voltage.
05/24/16     sm      Enabled ChargerPlatform_Init() API call
05/09/16     sm      Added changes to install protocol from QcomChargerInitialize()
04/21/16     sm      Added API call for Watchdog
03/21/16     va      Adding DeInit Api
03/15/16     sm      Added changes for bring up to only enter and exit the DXE
                     no platform initialization performed.
02/10/16     sm      Initial draft

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

#include "QcomChargerPlatform.h"

#include <api/pmic/charger/ChargerLibCommonWP.h>

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
  EFI_PLATFORMINFO_PLATFORM_TYPE PlatformType;

  Status = GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "QcomChargerDxe:: %a Error getting platform type = %r \r\n", __FUNCTION__, Status));
    return EFI_DEVICE_ERROR;
  }

  /* Required Initialization */
  Status = ChargerPlatform_Init();
  //if(EFI_SUCCESS == Status) make sure install gQcomChargerProtocol
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

  Status = ChargerLib_ChargerEnable(Enable);

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

  Status = ChargerLib_SetMaxUsbCurrent(MaxCurrent);

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
  QCOM_CHARGER_PLATFORM_ACTION_INFO chargerActionInfo = {0};

  if(NULL == pChargingAction)
  {
    return EFI_INVALID_PARAMETER;
  }

  chargerActionInfo.bChargerSrcPresent = pChargerActionInfo->bChargerSrcPresent;
  chargerActionInfo.DispSignOfLifeMaxThresholdMv = pChargerActionInfo->DispSignOfLifeMaxThresholdMv;
  chargerActionInfo.ChargerAttached =  (CHARGERLIB_ATTACHED_CHGR_TYPE)pChargerActionInfo->ChargerAttached;
  chargerActionInfo.LedConfigType = (QCOM_CHARGER_PLATFORM_CHARGING_LED_CONFIG_TYPE)pChargerActionInfo->LedConfigType;
  chargerActionInfo.bPowerKeyPressed = pChargerActionInfo->bPowerKeyPressed;
  chargerActionInfo.BattStsInfo.StateOfCharge =  pChargerActionInfo->BatteryStatusInfo.StateOfCharge;
  chargerActionInfo.BattStsInfo.ChargeCurrent =  pChargerActionInfo->BatteryStatusInfo.ChargeCurrent;  
  chargerActionInfo.BattStsInfo.BatteryVoltage = pChargerActionInfo->BatteryStatusInfo.BatteryVoltage;
  chargerActionInfo.BattStsInfo.BatteryTemperature = pChargerActionInfo->BatteryStatusInfo.BatteryTemperature;
  chargerActionInfo.BattStsInfo.Ocv = pChargerActionInfo->BatteryStatusInfo.Ocv;
  chargerActionInfo.BattStsInfo.StateOfChargeCentiPct = pChargerActionInfo->BatteryStatusInfo.StateOfCharge * 100;

  Status = ChargerPlatform_GetChargingAction((EFI_QCOM_CHARGER_ACTION_TYPE *)pChargingAction, &chargerActionInfo, vbattChecking);

  pChargerActionInfo->bChargerSrcPresent = chargerActionInfo.bChargerSrcPresent;
  pChargerActionInfo->DispSignOfLifeMaxThresholdMv = chargerActionInfo.DispSignOfLifeMaxThresholdMv;
  pChargerActionInfo->ChargerAttached = (EFI_QCOM_CHARGER_ATTACHED_TYPE)chargerActionInfo.ChargerAttached;
  pChargerActionInfo->LedConfigType = (EFI_QCOM_CHARGER_CHARGING_LED_CONFIG_TYPE)chargerActionInfo.LedConfigType;
  pChargerActionInfo->BatteryStatusInfo.StateOfCharge = chargerActionInfo.BattStsInfo.StateOfCharge;
  pChargerActionInfo->BatteryStatusInfo.ChargeCurrent = chargerActionInfo.BattStsInfo.ChargeCurrent;  
  pChargerActionInfo->BatteryStatusInfo.BatteryVoltage = chargerActionInfo.BattStsInfo.BatteryVoltage;
  pChargerActionInfo->BatteryStatusInfo.BatteryTemperature = chargerActionInfo.BattStsInfo.BatteryTemperature;
  pChargerActionInfo->BatteryStatusInfo.Ocv = chargerActionInfo.BattStsInfo.Ocv;

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

  Status = ChargerPlatform_TakeAction((EFI_QCOM_CHARGER_ACTION_TYPE)ChargingAction, (QCOM_CHARGER_PLATFORM_ACTION_INFO *)pChargerActionInfo);

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

  Status = ChargerPlatform_Exit();

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

  Status = ChargerLib_GetBatteryPresence(pBatteryPresent);

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
  EFI_PM_FG_BATT_STATUS_INFO BatteryStatus = {0};

  if(NULL == pBatteryVoltage)
  {
    return EFI_INVALID_PARAMETER;
  }
  *pBatteryVoltage = 0;

  Status = ChargerLib_GetBatteryStatus((chargerlib_batt_status_info*)&BatteryStatus);

  if(EFI_SUCCESS == Status)
  {
  *pBatteryVoltage = BatteryStatus.BatteryVoltage;
  }

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
  QCOM_CHARGER_PLATFORM_LOG_INFO Info   = {0};

  if(NULL == pFileLogInfo)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status = ChargerPlatformFile_GetLogInfo(&Info);
  if(Status == EFI_SUCCESS)
  {
    pFileLogInfo->gChargerLogHandle            = Info.gChargerLogHandle;
    pFileLogInfo->bPrintChargerAppDbgMsg       = Info.bPrintChargerAppDbgMsg;
    pFileLogInfo->bPrintChargerAppDbgMsgToFile = Info.bPrintChargerAppDbgMsgToFile;
    pFileLogInfo->fileLogLevelMask             = Info.fileLogLevelMask;
  }
  else
  {
    /* DEBUG */
    CHARGER_FILE_UART_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Error = %r \r\n",__FUNCTION__, Status));
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
  Status = ChargerLib_DumpChargerPeripheral();
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

  Status = ChargeLib_IsDcinValid(pIsDcInValid);

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

  Status = ChargerPlatformFile_GetChargerConfig(ChargerCfgKey, KeyValue);
  if(Status == EFI_SUCCESS)
  {
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a CfgKey = %d Value = %d \r\n",__FUNCTION__, ChargerCfgKey, *KeyValue));
  }
  else
  {
    /* DEBUG */
    CHARGER_DEBUG(( EFI_D_WARN, "QcomChargerDxe:: %a Error = %r \r\n",__FUNCTION__, Status));
  }

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
    Status = ChargerLib_IsChargingSupported(pIsChargingSupported);
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

    Status = ChargerLib_GetDisplayImageType((CHARGERLIB_EVENT_DISP_IMAGE_TYPE *)pDispImage);
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

    Status = ChargerLib_GetPlatformPwrOnReason((CHARGERLIB_PLATFORM_PWRON_REASON_TYPE*)pPwrOnReason);
    if (Status != EFI_SUCCESS){return Status;}
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

    Status = ChargerLib_GetControlAction(pControlAction);
    if (Status != EFI_SUCCESS){return Status;}
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

    Status = ChargerLib_SetControlAction(controlAction);
    if (Status != EFI_SUCCESS){return Status;}
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
  ChgBattType type = CHG_BATT_TYPE_INVALID;

  Status = ChargerLib_GetBatteryType(&type);
  if (Status == EFI_SUCCESS)
  {
    *pBatteryType = (UINT32)type;
  }

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
  chargerlib_batt_status_info BatteryStatus = {0};
  
  if(NULL == pBatterySOC)
  {
    return EFI_INVALID_PARAMETER;
  }
  *pBatterySOC = 0;
    
  Status = ChargerLib_GetBatteryStatus(&BatteryStatus);
    
  if(EFI_SUCCESS == Status)
  {
    *pBatterySOC = BatteryStatus.StateOfCharge;
  }
    
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
  if(!ChargerLib_GetDCINSupported())
  {
    *pConnected = FALSE;
    *pCharger_max_voltage_mv = 0;
    *pCharger_max_current_ma = 0;
    return EFI_SUCCESS;
  }
  return ChargerLib_GetBarrelChargerStatus(pConnected, pCharger_max_voltage_mv, pCharger_max_current_ma);
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

  Status = ChargerPlatform_CpdlogTimer_Exit();

  return Status;
}

/**
EFI_QcomChargerIsOffmode ()

@brief
get if going to lpm offmode or normal offmode or not in offmode
*/

EFI_STATUS
EFIAPI
EFI_QcomChargerIsOffmode
(
  BOOLEAN* lpm_offmode,
  BOOLEAN* offmode
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = ChargerLib_IsLPMOffmode(lpm_offmode, offmode);

  return Status;
}

/**
//EFI_QcomChargerGetMaxNegotiatedPwr()

@brief
get charging path
*/

EFI_STATUS
EFIAPI
EFI_QcomChargerGetMaxNegotiatedPwr
(
UINT8* pConfig, 
UINT8* pNegotiatedPwr
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  CHARGERLIB_PLATFORM_CHGR_MAX_PWR_REQ_CFG_STS_TYPE max_pwr_req;
  max_pwr_req.AsUint8 = 0;

  Status = ChargerLib_GetPlatformMaxPwrReqCfgSts(&max_pwr_req, pNegotiatedPwr);
  *pConfig = max_pwr_req.AsUint8;

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
  EFI_QcomChargerIsOffmode,
  EFI_QcomChargerGetMaxNegotiatedPwr,
};
