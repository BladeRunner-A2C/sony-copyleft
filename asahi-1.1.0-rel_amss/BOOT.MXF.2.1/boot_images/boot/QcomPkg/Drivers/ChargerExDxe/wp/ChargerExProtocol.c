/*! @file ChargerExProtocol.c

*  CHARGER EXTENDED MODULE RELATED DECLARATION
*  This file contains functions and variable declarations to support 
*  the Charger Extended module.
*
*  Copyright (c) 2017 -2019, 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Inc Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     --------------------------------------------------------------------------
02/22/23   dm      Added platform types supported for Hamoa
05/27/19   sg      Boot to HLOS directly if POFF is due to Pmic FAULT
01/09/19   vr      Change Non-Error log level from Warning to Info
01/09/19   vr      Updated IsOffModeCharging API for mtp to not return offmodecharging true when mtp does not support charging
09/05/18   cs      Updated for presil RUmi
06/18/18   sb      Updated IsOffModeCharging API for CLS
06/05/18   sb      added cable pon detection for off-mode charging
03/15/18   ra      Add missing field for IsPowerOk
02/09/18   ra      Hardcoding values for bring up
03/03/16   va      Adding offmode, flash APIs to contained for ABL, making open source and local header copies
12/16/16   sm      Added changes to return EFI_UNSUPPORTED Status for CDP and RUMI Platforms
11/09/16   cs      modified charger present API also to detect DCIn. 
09/09/16   sm      Added Status success check after locating protocol. 
05/31/16   sm      New File
===========================================================================*/

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include <Library/UefiLib.h>
/**
  PMIC Lib interfaces
 */
#include <Include/Protocol/EFIQcomCharger.h>
#include <Include/Protocol/EFIPmicUsb.h>
#include <Protocol/EFIChargerEx.h>
#include <Include/Protocol/EFIPmicPwrOn.h>
#include <Include/Protocol/EFIPmicSchg.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Library/QcomLib.h>

#include "smem.h"

#include <api/pmic/pm/pm_chg.h>
#include <api/pmic/charger/ChargerLibCommonWP.h>


/*===========================================================================
                        MACRO AND TYPE DEFINITIONS
===========================================================================*/
#define PM_DEVICE_0     0       /* Primary PMIC index */

#define PM_FAULT_SEQ        0x40
#define PM_WARMRESET_SEQ    0x40


/*===========================================================================
                        GLOBAL DATA DEFINITION
===========================================================================*/
extern EFI_GUID gQcomPmicUsbProtocolGuid;
EFI_CHARGER_EX_PROTOCOL ChargerExProtocolImplementation;


STATIC EFI_QCOM_CHARGER_PROTOCOL    *pQcomChargerProtocol = NULL;
STATIC EFI_QCOM_PMIC_SCHG_PROTOCOL  *pPmicSchgProtocol = NULL;

STATIC BOOLEAN                      InPowerTestingMode    = FALSE;
//STATIC UINT8                        gShipModeExit         = FALSE;

/*===========================================================================
                        INTERNAL FUNCTION DECLARATIONS
===========================================================================*/
EFI_STATUS ChargerExSaveChargeInfoToSmem(pm_chg_info_type *pChargerSharedInfo);
EFI_STATUS ChargerExGetChargeInfoFromSmem(pm_chg_info_type *pChargerSharedInfo);
EFI_STATUS ChargerExGetBatterySOC(UINT32  *pBatterySOC);


/*===========================================================================
                        EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/
/**
ChargerExInitialize()

@brief
Initializes charger Extended module
*/
EFI_STATUS ChargerExInitialize( IN EFI_HANDLE         ImageHandle,
                                IN EFI_SYSTEM_TABLE   *SystemTable )
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = gBS->InstallMultipleProtocolInterfaces(
    &ImageHandle,
    &gChargerExProtocolGuid,
    &ChargerExProtocolImplementation,
    NULL
    );
  if(EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  Install Protocol failed, Error[%r] \r\n", __FUNCTION__, Status));
  }

  return Status;
}

/**
EFI_ChargerExGetChargerPresence()

@brief
 Returns charger presence status
 */
EFI_STATUS
EFIAPI
EFI_ChargerExGetChargerPresence
(
  OUT BOOLEAN  *pChargerPresent
)
{
  EFI_STATUS                           Status = EFI_SUCCESS;
  STATIC EFI_QCOM_PMIC_USB_PROTOCOL   *PmicUsbProtocol   = NULL;
  BOOLEAN                              DcInValid = FALSE;
  EFI_PLATFORMINFO_PLATFORM_TYPE       PlatformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;

  if (!pChargerPresent)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }
  if(InPowerTestingMode && EFI_PLATFORMINFO_TYPE_CDP == PlatformType)
  {
    *pChargerPresent = TRUE;
    return Status;
  }

  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType))
  {
    DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a CDP/RUMI (%d) Platform detected. No Battery information available. \r\n", __FUNCTION__, PlatformType));
    return EFI_UNSUPPORTED;
  }

  if (!PmicUsbProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomPmicUsbProtocolGuid,
                                  NULL,
                                 (VOID **)&PmicUsbProtocol );

    if((EFI_SUCCESS != Status) || (NULL == PmicUsbProtocol))
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = PmicUsbProtocol->GetChargerPresence(pChargerPresent);

  if (EFI_SUCCESS != Status)
  {
    return Status;
  }

  if (!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol(&gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol);

    if ((EFI_SUCCESS != Status) || (NULL == pQcomChargerProtocol))
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = pQcomChargerProtocol->IsDcInValid(&DcInValid);

  if (EFI_SUCCESS == Status)
  {
    (*pChargerPresent) |= DcInValid;
  } 

  return Status;
}


/**
EFI_ChargerExGetBatteryPresence ()

@brief
Get battery presence status SCHG
*/
EFI_STATUS
EFIAPI
EFI_ChargerExGetBatteryPresence
(
  OUT BOOLEAN  *pBatteryPresent
)
{
  EFI_STATUS                      Status = EFI_SUCCESS;

  EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;
  
  if (!pBatteryPresent)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  if(InPowerTestingMode && EFI_PLATFORMINFO_TYPE_CDP == PlatformType)
  {
    *pBatteryPresent = TRUE;
    return Status;
  }

  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType))
  {
    DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a CDP/RUMI (%d) Platform detected. No Battery information available. \r\n", __FUNCTION__, PlatformType));
    return EFI_UNSUPPORTED;
  }

  if(!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );

    if((EFI_SUCCESS != Status) || (NULL == pQcomChargerProtocol))
    {
      return EFI_DEVICE_ERROR;
    }
  }
  
  Status = pQcomChargerProtocol->GetBatteryPresence(pBatteryPresent);
  
  return Status;
}

/**
EFI_ChargerExGetBatteryVoltage ()

@brief
Returns battery voltage
*/
EFI_STATUS
EFIAPI
EFI_ChargerExGetBatteryVoltage
(
  OUT UINT32  *pBatteryVoltage
)
{
  EFI_STATUS                      Status = EFI_SUCCESS;

  EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;

  if (!pBatteryVoltage)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType && (!InPowerTestingMode)) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType))
  {
    DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a CDP/RUMI (%d) Platform detected. No Battery information available. \r\n", __FUNCTION__, PlatformType));
    return EFI_UNSUPPORTED;
  }

  if(!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );

    if(EFI_SUCCESS != Status || NULL == pQcomChargerProtocol)
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = pQcomChargerProtocol->GetBatteryVoltage(pBatteryVoltage);

  return Status;
}

/**
EFI_ChargerExGetChargingStatus ()

@brief
Returns Charging status
*/
EFI_STATUS
EFIAPI
EFI_ChargerExGetChargingStatus
(
    OUT UINT32  *pBatterySOC,
    OUT BOOLEAN  *IsChargerAttached
)
{
    EFI_STATUS    Status = EFI_SUCCESS;
    EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;

    if (!pBatterySOC && !IsChargerAttached) //this && is here on purpose, one of the pointer could be NULL.
    {
        return EFI_INVALID_PARAMETER;
    }

    Status = GetPlatformType(&PlatformType);
    if(EFI_ERROR(Status))
    {
        DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a GetPlatformType failed, Error[%r] \r\n", __FUNCTION__, Status));
        return Status;
    }
    if(InPowerTestingMode && EFI_PLATFORMINFO_TYPE_CDP == PlatformType)
    {
      if(pBatterySOC)
        *pBatterySOC = 50;
      if(IsChargerAttached)
        *IsChargerAttached = TRUE;
      return Status;
    }
    if(!((EFI_PLATFORMINFO_TYPE_CLS == PlatformType) || 
         (EFI_PLATFORMINFO_TYPE_MTP == PlatformType) || 
         (EFI_PLATFORMINFO_TYPE_QRD == PlatformType) || 
         (EFI_PLATFORMINFO_TYPE_IDP == PlatformType) || 
         (EFI_PLATFORMINFO_TYPE_CRD == PlatformType)))
    {
        Status = EFI_UNSUPPORTED;
        DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a  Non-CLS/MTP/QRD/IDP/CRD (%d) Platform detected, Error[%r] \r\n", __FUNCTION__, PlatformType, Status));
        return Status;
    }

    if (pBatterySOC)
    {

          ChgBattType BatteryType = CHG_BATT_TYPE_INVALID;

          if(!pQcomChargerProtocol)
          {
              Status  = gBS->LocateProtocol(&gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol);
              if(EFI_ERROR(Status) || !pQcomChargerProtocol)
              {
                  DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  QcomChargerProtocol locate failed, Error[%r] \r\n", __FUNCTION__, Status));
                  return Status;
              }
          }
          Status = pQcomChargerProtocol->GetBatteryType(&BatteryType);
          if(EFI_ERROR(Status))
          {
              DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  _GetBatteryType failed, Error[%r] \r\n", __FUNCTION__, Status));
              return Status;
          }

          if(BatteryType == CHG_BATT_TYPE_DEBUG_BOARD)
          {
              *pBatterySOC = 30;
          }
          else
          {
              Status = pQcomChargerProtocol->GetBatterySOC(pBatterySOC);
              if(EFI_ERROR(Status))
              {
                  DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  GetBatterySOC failed, Error[%r] \r\n", __FUNCTION__, Status));
                  return Status;
              }  
          }
        
    }

    if (IsChargerAttached)
    {
        Status = EFI_ChargerExGetChargerPresence(IsChargerAttached);
    }

    return Status;
}

/**
EFI_ChargerExIsOffModeCharging ()

@brief
Returns if device needs to go for off mode charging
*/
EFI_STATUS
EFIAPI
EFI_ChargerExIsOffModeCharging
(
  OUT BOOLEAN *bOffModeCharging
)
{
  EFI_STATUS Status         = EFI_SUCCESS;
  BOOLEAN is_off_mode = FALSE;
  BOOLEAN is_lpm_off_mode= FALSE;

  if (!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol(&gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol);

    if ((EFI_SUCCESS != Status) || (NULL == pQcomChargerProtocol))
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = pQcomChargerProtocol->IsOffmode(&is_lpm_off_mode, &is_off_mode);
  if (Status != EFI_SUCCESS)
  {
    *bOffModeCharging = FALSE;
  }
  else
  {
    *bOffModeCharging = is_lpm_off_mode;
  }
  
  DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a  Offmode Charging = %a \r\n", __FUNCTION__, (*bOffModeCharging) ? "TRUE" : "FALSE"));
  return Status;
}

/**
EFI_ChargerExIsPowerOk ()

@brief
Returns if battery voltage is good to process with SW flash
*/
EFI_STATUS
EFIAPI
EFI_ChargerExIsPowerOk
(
  IN  EFI_CHARGER_EX_POWER_TYPE   PowerType,
  OUT VOID                       *pPowerTypeInfo
)
{
  EFI_STATUS Status                = EFI_SUCCESS;
  EFI_CHARGER_EX_FLASH_INFO *pFlashInfo = NULL;
  BOOLEAN    BatteryPresent        = FALSE;
  EFI_PLATFORMINFO_PLATFORM_TYPE       PlatformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;
  ChgBattType BatteryType          = CHG_BATT_TYPE_INVALID;
  UINT32      BatteryCurrentSOC    = 0;
  UINT32      SwFlashBattMinSOC    = 0;
  BOOLEAN     BarrelChgConnected   = FALSE;
  UINT16      BarrelChgVoltage     = 0;  
  UINT16      BarrelChgCurrent     = 0;
  UINT32      NoBattBootMinChgPwr  = 0;
  UINT8       negotiated_pwr       = 0;

  if(!pPowerTypeInfo)
    return EFI_INVALID_PARAMETER;

  pFlashInfo = (EFI_CHARGER_EX_FLASH_INFO *)pPowerTypeInfo;

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }
  
  if(InPowerTestingMode && EFI_PLATFORMINFO_TYPE_CDP == PlatformType)
  {
    pFlashInfo->bCanFlash = TRUE;
    return Status;
  }

  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType))
  {
    DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a CDP/RUMI (%d) Platform detected. No Battery information available. \r\n", __FUNCTION__, PlatformType));
    return EFI_UNSUPPORTED;
  }
  
  if(!pQcomChargerProtocol)
  {
    Status |= gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );
    if(EFI_SUCCESS != Status || NULL == pQcomChargerProtocol)
    {
      return EFI_DEVICE_ERROR;
    }
  }

  switch(PowerType)
  {
    case EFI_CHARGER_EX_POWER_FLASH_BATTERY_VOLTAGE_TYPE:
      Status  = EFI_ChargerExGetBatteryPresence(&BatteryPresent);
      Status |= pQcomChargerProtocol->GetBatteryType((UINT32*)&BatteryType);
      Status |= pQcomChargerProtocol->GetChargerConfig(EFI_QCOM_CHARGER_CONFIG_KEY_BATT_MISSING_BOOT_MIN_CHG_POWER, &NoBattBootMinChgPwr);
	  if (EFI_SUCCESS != Status) { return Status; }
      
      // no battery
      if (BatteryPresent == FALSE)
      {
        BOOLEAN DcInValid = FALSE;
		UINT8  max_pwr_req = 0;
		
		Status = pQcomChargerProtocol->IsDcInValid(&DcInValid);
		Status |= pQcomChargerProtocol->GetMaxNegotiatedPwr(&max_pwr_req, &negotiated_pwr);
		if (negotiated_pwr >= NoBattBootMinChgPwr)
		{
		  pFlashInfo->bCanFlash = TRUE;
		  DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a Battery missing, ok to flash with strong input = %d W\r\n", __FUNCTION__, negotiated_pwr));
		}
		
		Status  = pQcomChargerProtocol->GetBarrelChargerStatus(&BarrelChgConnected, &BarrelChgVoltage, &BarrelChgCurrent);
        if ((BarrelChgConnected && ((BarrelChgVoltage * BarrelChgCurrent / 1000 / 1000) > NoBattBootMinChgPwr)) || (negotiated_pwr >= NoBattBootMinChgPwr))
        {
          pFlashInfo->bCanFlash = TRUE;
          DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a Battery missing, but strong input power. BarrelChg Voltage & Current = %d mV, %d mA, USB PD input power = %d W\r\n", __FUNCTION__,BarrelChgVoltage, BarrelChgCurrent, negotiated_pwr));
        }
        else
        {
          pFlashInfo->bCanFlash = FALSE;
          DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a Battery missing, and weak input power. BarrelChg Voltage & Current = %d mV, %d mA, USB PD input power = %d W\r\n", __FUNCTION__,BarrelChgVoltage, BarrelChgCurrent, negotiated_pwr));
        }
		
      }
      // fake battery
      else if (BatteryType == CHG_BATT_TYPE_DEBUG_BOARD)
      {
        pFlashInfo->bCanFlash = TRUE;
        DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a Fake battery, ok to flash \r\n", __FUNCTION__));
      }
      // real battery
      else
      {
        Status  = ChargerExGetBatterySOC(&BatteryCurrentSOC);          
        Status |= pQcomChargerProtocol->GetChargerConfig(EFI_QCOM_CHARGER_CONFIG_KEY_SW_FLASH_SOC, &SwFlashBattMinSOC);
        if (EFI_SUCCESS != Status) { return Status; }
        //Temporarily lower threshold to 0 so we always return PowerOk
        SwFlashBattMinSOC = 0;
        if(BatteryCurrentSOC >= SwFlashBattMinSOC)
        {
          pFlashInfo->bCanFlash = TRUE;
          DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a Real battery, ok to flash with BatteryCurrentSOC = %d above threshold %d\r\n", __FUNCTION__,BatteryCurrentSOC, SwFlashBattMinSOC));
        }
        else
        {
          pFlashInfo->bCanFlash = FALSE;
          DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a Real battery, flash not allowed with BatteryCurrentSOC = %d below threshold %d\r\n", __FUNCTION__,BatteryCurrentSOC, SwFlashBattMinSOC));
        }    
      }
    break;
    default:
    break;
  }

  return Status;
}

/**
EFI_ChargerExSetFirmwareUpdateMode ()

@brief
Process FW Update action
*/
EFI_STATUS
EFIAPI
EFI_ChargerExSetFirmwareUpdateMode
(
  IN EFI_CHARGER_EX_FW_UPDATE_MODE_TYPE  FwUpdateMode
)
{
    EFI_STATUS    Status = EFI_SUCCESS;
    UINT32 FwUpdateEnable = 0;
    EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;

    Status = GetPlatformType(&PlatformType);
    if (EFI_ERROR(Status))
    {
        DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a GetPlatformType failed, Error[%r] \r\n", __FUNCTION__, Status));
        return Status;
    }

    if (!(EFI_PLATFORMINFO_TYPE_CLS == PlatformType || EFI_PLATFORMINFO_TYPE_MTP == PlatformType || EFI_PLATFORMINFO_TYPE_QRD == PlatformType || EFI_PLATFORMINFO_TYPE_CRD == PlatformType))
    {
        Status = EFI_UNSUPPORTED;
        DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a  Non-(CLS/MTP/QRD/CRD = %d) Platform detected, Error[%r] \r\n", __FUNCTION__, PlatformType, Status));
        return Status;
    }

    if (!pQcomChargerProtocol)
    {
        Status  = gBS->LocateProtocol(&gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol);
        if(EFI_ERROR(Status) || !pQcomChargerProtocol)
        {
            DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  QcomChargerProtocol locate failed, Error[%r] \r\n", __FUNCTION__, Status));
            return Status;
        }
    }

    Status = pQcomChargerProtocol->GetChargerConfig(EFI_QCOM_CHARGER_CONFIG_KEY_FW_UPDATE_SUPPORT, &FwUpdateEnable);
    if (EFI_ERROR(Status))
    {
        DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  GetChargerConfig failed, Error[%r] \r\n", __FUNCTION__, Status));
        return Status;
    }

    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a  FwUpdateEnable = %d, FwUpdateMode = %d\r\n", __FUNCTION__, FwUpdateEnable, FwUpdateMode));

    /* Check for Firmware Update Support props from ChargerConfig. */
    if (FALSE == FwUpdateEnable)
    {
        Status = EFI_UNSUPPORTED;
        DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  FwUpdateEnable = %d, Error[%r] \r\n", __FUNCTION__, FwUpdateEnable, Status));
        return Status;
    }

    switch (FwUpdateMode)
    {
      case EFI_CHARGER_EX_FW_UPDATE_MODE_ENTER:
      {
        /* Based on the CapsuleUdate flag/NV item, ADSP FW loading in Test-mode happens in QcomChargerDxe, 
        so no need to do anything here. */
      }
      break;
      case EFI_CHARGER_EX_FW_UPDATE_MODE_EXIT:
      {
        if (!pPmicSchgProtocol)
        {
          Status = gBS->LocateProtocol(&gQcomPmicSchgProtocolGuid, NULL, (VOID **)&pPmicSchgProtocol);
          if (EFI_ERROR(Status) || !pPmicSchgProtocol)
          {
            DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  PmicSchgProtocol locate failed, Error[%r] \r\n", __FUNCTION__, Status));
            return Status;
          }
        }

        Status = pPmicSchgProtocol->SetTestModeDischarging(FALSE);
        if (EFI_ERROR(Status))
        {
          DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  SetTestModeDischarging failed, Error[%r] \r\n", __FUNCTION__, Status));
          return Status;
        }
      }
      break;
      default:
      {
        Status = EFI_UNSUPPORTED;
        DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  Invalid FwUpdateMode [%d], Error[%r] \r\n", __FUNCTION__, FwUpdateMode, Status));
      }
    }

    return Status;
}


/**
Charger External UEFI Protocol implementation
*/
EFI_CHARGER_EX_PROTOCOL ChargerExProtocolImplementation = 
{
    CHARGER_EX_REVISION,
    EFI_ChargerExGetChargerPresence,
    EFI_ChargerExGetBatteryPresence,
    EFI_ChargerExGetBatteryVoltage,
    EFI_ChargerExIsOffModeCharging,
    EFI_ChargerExIsPowerOk,
    EFI_ChargerExGetChargingStatus,
    EFI_ChargerExSetFirmwareUpdateMode
};


/*===========================================================================
                        INTERNAL FUNCTION DEFINITIONS
===========================================================================*/
EFI_STATUS ChargerExSaveChargeInfoToSmem(pm_chg_info_type *pChargerSharedInfo)
{
    EFI_STATUS    Status = EFI_SUCCESS;
    UINT32     buf_size = sizeof(pm_chg_info_type);
    UINT32     buf_size_ret = 0;
    pm_chg_info_type *pSmemChargerInfo = NULL;

    pSmemChargerInfo = (pm_chg_info_type *) smem_get_addr(SMEM_CHARGER_BATTERY_INFO, &buf_size_ret);
    if(!pSmemChargerInfo)
    {
        DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a  SMEM Retrieve Error.. XBL Core allocating SMEM now \r\n",__FUNCTION__));

        pSmemChargerInfo = (pm_chg_info_type *)smem_alloc(SMEM_CHARGER_BATTERY_INFO, buf_size);
        if(!pSmemChargerInfo)
        {
            Status = EFI_DEVICE_ERROR;
            DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  PmicSchgProtocol locate failed, Error[%r] \r\n", __FUNCTION__, Status));
            return Status;
        }

        DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a  SMEM CHARGER_BATTERY_INFO allocated\r\n", __FUNCTION__));

        /* Initialized to -1 since SBL did not allocate smem yet */
        pSmemChargerInfo->version       = 1;
        pSmemChargerInfo->sbl_entry_mV  = -1;
        pSmemChargerInfo->sbl_entry_soc = -1;
    }

    /* Assign required values to smem memory */
    pSmemChargerInfo->uefi_entry_mV  = pChargerSharedInfo->uefi_entry_mV;
    pSmemChargerInfo->uefi_exit_mV   = pChargerSharedInfo->uefi_exit_mV;
    pSmemChargerInfo->uefi_entry_soc = pChargerSharedInfo->uefi_entry_soc;
    pSmemChargerInfo->uefi_exit_soc  = pChargerSharedInfo->uefi_exit_soc;
    pSmemChargerInfo->uefi_charger_fw_mode = pChargerSharedInfo->uefi_charger_fw_mode;

    return Status;
}

EFI_STATUS ChargerExGetChargeInfoFromSmem(pm_chg_info_type *pChargerSharedInfo)
{
    EFI_STATUS    Status = EFI_SUCCESS;
    UINT32     buf_size = sizeof(pm_chg_info_type);
    UINT32     buf_size_ret = 0;
    pm_chg_info_type *pSmemChargerInfo = NULL;

    pSmemChargerInfo = (pm_chg_info_type *) smem_get_addr(SMEM_CHARGER_BATTERY_INFO, &buf_size_ret);
    if(!pSmemChargerInfo)
    {
        DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a  SMEM Retrieve Error.. XBL Core allocating SMEM now \r\n",__FUNCTION__));

        pSmemChargerInfo = (pm_chg_info_type *)smem_alloc(SMEM_CHARGER_BATTERY_INFO, buf_size);
        if(!pSmemChargerInfo)
        {
            Status = EFI_DEVICE_ERROR;
            DEBUG((EFI_D_ERROR, "ChargerExProtocol:: %a  PmicSchgProtocol locate failed, Error[%r] \r\n", __FUNCTION__, Status));
            return Status;
        }

        DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a  SMEM CHARGER_BATTERY_INFO allocated\r\n", __FUNCTION__));

        /* Initialized to -1 since SBL did not allocate smem yet */
        pSmemChargerInfo->version       = 1;
        pSmemChargerInfo->sbl_entry_mV  = -1;
        pSmemChargerInfo->sbl_entry_soc = -1;
    }

    pChargerSharedInfo->uefi_entry_mV = pSmemChargerInfo->uefi_entry_mV;
    pChargerSharedInfo->uefi_exit_mV = pSmemChargerInfo->uefi_exit_mV;
    pChargerSharedInfo->uefi_entry_soc = pSmemChargerInfo->uefi_entry_soc;
    pChargerSharedInfo->uefi_exit_soc = pSmemChargerInfo->uefi_exit_soc;
    pChargerSharedInfo->uefi_charger_fw_mode = pChargerSharedInfo->uefi_charger_fw_mode;

    return Status;
}

EFI_STATUS ChargerExGetBatterySOC
(
  UINT32  *pBatterySOC
)
{
  EFI_STATUS                      Status = EFI_SUCCESS;

  EFI_PLATFORMINFO_PLATFORM_TYPE  PlatformType = EFI_PLATFORMINFO_TYPE_UNKNOWN;

  if (!pBatterySOC)
  {
    return EFI_INVALID_PARAMETER;
  }

  Status |= GetPlatformType(&PlatformType);
  if(EFI_SUCCESS != Status)
  {
    DEBUG((EFI_D_WARN, "ChargerExProtocol:: %a Error getting platform type  \r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }

  if(InPowerTestingMode && EFI_PLATFORMINFO_TYPE_CDP == PlatformType)
  {
    *pBatterySOC = 50;
    return Status;
  }
  
  if((EFI_PLATFORMINFO_TYPE_CDP == PlatformType) || (EFI_PLATFORMINFO_TYPE_RUMI == PlatformType))
  {
    DEBUG(( EFI_D_WARN, "ChargerExProtocol:: %a CDP/RUMI (%d) Platform detected. No Battery information available. \r\n", __FUNCTION__, PlatformType));
    return EFI_UNSUPPORTED;
  }

  if(!pQcomChargerProtocol)
  {
    Status = gBS->LocateProtocol( &gQcomChargerProtocolGuid, NULL, (VOID **)&pQcomChargerProtocol );

    if(EFI_SUCCESS != Status || NULL == pQcomChargerProtocol)
    {
      return EFI_DEVICE_ERROR;
    }
  }

  Status = pQcomChargerProtocol->GetBatterySOC(pBatterySOC);

  return Status;
}

