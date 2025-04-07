/*! @file PmicSchgProtocol.c 

*  PMIC- SCHG MODULE RELATED DECLARATION
*  This file contains functions and variable declarations to support 
*  the PMIC SCHG (Switch Mode Battery Charger) module.
*
*  Copyright (c) 2017,2023 Qualcomm Technologies, Inc. All rights reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     --------------------------------------------------------------------------
08/07/18   dc      Return SDP when BC1.2 detection is disabled in HW
08/01/18   ivy     Set HW AFP/Jeita in the same API
07/27/18   cs      for NON-SMB2351, return unsupported for getActivePort
06/18/18   sb      Set ICL to 500 mA while APSD is not finished for wall chargers
06/21/18   cs      added API to get active charging port.
05/17/18   ivy     Added support for DC IRQ status
05/14/17   ra      Support for Debug Accessory Mode
03/26/18   ra      Support for HW JEITA status
03/15/18   ra      Remove charger default setting
03/05/18   pxm     Update due to pm_schg_usb driver change
02/23/18   cs      remove checking for chip revision before enabling charger watchdog
02/20/18   ra      Adding new protocols
02/09/18   ra      Removing Wipower related protocol
01/24/18   ra      Adding support for icl status
11/27/17   ra      Support for battery missing detection and AFP
11/09/17   ra      Update JEITA code, remove OTG and Legacy cable detection WA.
09/19/17   cs      for SDM855 remvoe unsupported function calls.
06/13/17   ll      Enable/disable HW AFP based on debug board detection
03/21/17   dch     Initialize ICL for all charger as 500mA and increase it to 1500mA in case charger is not SDP/Float charger
02/15/17   va      Add re run APSD 
02/08/17   ll      Added OTG sequence for OTG device with large cap
02/06/17   cs      add config to enable/disable INOV
01/27/17   ai      Fix use of retail
01/27/17   sm      battery missing is true either latched or RT STATUS is TRUE.
                   Add support for PBS triggered AFP
                   Fixed battery missing not detected after battery missing shutdown and reboot
01/23/17   sm      CFG parameter Structure changes
12/19/16   sm      Added API to get SCHG Charger PmicIndex
12/09/16   sm      Added changes to set OTG current limit when enabling/disabling OTG
11/14/16   sm      Added required changes for preventing accidental reverse boosting in EFI_PmicSchgEnableCharger() and EFI_PmicSchgExit()
11/09/16   sm      Added changes to read latched status of PM_SCHG_MISC_IRQ_WDOG_BARK interrupt
11/04/16   sm      Added APSD done status check in EFI_PmicSchgGetChargerPortType()
10/19/16   sm      Added changes to read latched status of BAT_THERM_OR_ID_MISSING interrupt
                   Removed HVDCP configuration settings
10/17/16   sm      Added SetChargeCmdBit() API
                   Added changes to report charger wdog not supported for PMI8998 versions before v2.0
                   Added changes in EFI_PmicSchgGetChgWdogStatus() to check if disabling charging on 
                   wdog bite functionality is enabled and return status accordingly.
10/13/16   cs      add protocol API for setting dcin current limit.
09/20/16   sv      fixing klocwork issues
09/13/16   sm      Removed host mode setting from init()
09/06/16   cs      wipower changes to remove 3.5 sec, not suspend DCIn
08/24/16   sm      Added function call to set FV_MAX during Init()
08/16/16   sm      Added API to enable/disable HW JEITA and made EFI_PmicSchgEnableJeita() obsolete
07/18/16   sm      Added API to configure USB ICL options
07/15/16   cs      added wipower support
06/24/16   sm      Added API to return if charging is enabled or not. 
06/23/16   sm      Added changes to enable/disable HVDCP
06/23/16   va      Adding support for Charger Fg Peripheral dumps
06/09/16   sm      Added check for hostmode support and then resetting port role 
                   Redefined GetOtgStatus API
05/25/16   sm      Added pm_schg_chgr_set_charge_current() in Init()
                   Added  pm_schg_usb_enable_icl_override_after_apsd() in SetUSBMaxCurrent()
05/10/16   sm      Added back SchgExit for placeholder
04/21/16   sm      Added APIs to enable/disable and pet watchdog
04/07/16   sm      Completing API definitions
03/28/16   sm      Few IRQ corrections
03/28/16   va      Adding HW Jeita support, exit API
02/19/16   sm      Initial draft
===========================================================================*/

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/FuseControlLib.h>

#include "pm_uefi.h"
#include "pm_version.h"

#include <Protocol/EFIPmicSchg.h>
#include <Library/DebugLib.h>
#include <api/dal/DALSys.h>
#include "PmicFileLog.h"
/**
  PMIC Lib interfaces
 */
#include "pm_uefi.h"
#include "pm_core_utils.h"
#include "pm_scpq_usb.h"
#include "pm_scpq_chgr.h"
#include "pm_scpq_typec.h"
#include "pm_scpq_dcdc.h"
#include "pm_scpq_misc.h"
#include "pm_scpq_wls.h"
#include "pm_scpq_hs_usb.h"
#include "pm_scpq_hs_chgr.h"
#include "pm_scpq_hs_typec.h"
#include "pm_scpq_hs_dcdc.h"
#include "pm_scpq_hs_misc.h"
#include "pm_sdam.h"

#define MAX_CHARGING_PORT   4
#define PM_SCHG_200_MS_WAIT                     200000 //200 milli Second wait
#define PMIC_SCHG_MAX_APSD_DONE_CHECK_ITERATION 5
#define SDAM_MEM_30_ADDR 30

#define SDAM_MEM_039_ADDR    39

#define SDAM_MEM_051_ADDR    51
#define SDAM_MEM_052_ADDR    52
#define SDAM_MEM_053_ADDR    53
#define SDAM_MEM_054_ADDR    54

#define SDAM15_MEM_21_ADDR 21

EFI_PM_SCHG_CFGDATA_TYPE gSchgCfgData = {0}; 
STATIC UINT32   gSchg_P_PmicIndex[MAX_CHARGING_PORT] = { 0 };
STATIC UINT32   gSchg_P_SlaveIndex[MAX_CHARGING_PORT] = { 0 };
STATIC UINT32   gCharger_P_Count = 0;

#define PMIC_ALL_LAYER_REV_2 2
#define PMIC_METAL_REV_0 0

#define CHARGER_PMIC_IDX    7

#define BATTAUTH_ENABLE 0x01
#define BATTAUTH_DISABLE 0x02

/*===========================================================================
EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/

/**
EFI_PmicSchgDumpPeripheral()

@brief
 Dump SCHG Peripheral
 */
EFI_STATUS
EFIAPI
EFI_PmicSchgDumpPeripheral( VOID )
{
  return EFI_SUCCESS;
}


/**
EFI_PmicSchgInit ()

@brief
Initializes SCHG
*/
EFI_STATUS
EFIAPI
EFI_PmicSchgInit
(
  IN UINT32 PmicDeviceIndex,
  IN EFI_PM_SCHG_CFGDATA_TYPE SchgCfgData,
  IN BOOLEAN bDbgBoard
)
{
  return EFI_SUCCESS;
}

/*
@brief
De-Initializes SCHG
*/
EFI_STATUS
EFIAPI
EFI_PmicSchgExit
(
  IN UINT32 PmicDeviceIndex
)
{
  return EFI_SUCCESS;
}


/**
EFI_PmicSchgEnableCharger ()

@brief
Enable charging
*/
EFI_STATUS
EFIAPI
EFI_PmicSchgEnableCharger
(
  IN UINT32  PmicDeviceIndex,
  IN BOOLEAN ChargerEnable
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgUsbinValid
(
  IN  UINT32 PmicDeviceIndex,
  OUT BOOLEAN *Valid
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type errFlag;
  if(NULL == Valid)
  {
    return EFI_INVALID_PARAMETER;
  }
  
  if((errFlag = pm_scpq_usb_irq_status(PmicDeviceIndex, PM_SCPQ_USB_IRQ_USBIN_PLUGIN, PM_IRQ_STATUS_RT, Valid)) == PM_ERR_FLAG_SUCCESS)
  {
	return EFI_SUCCESS;
  }
  else if((errFlag = pm_scpq_hs_usb_irq_status(0,PmicDeviceIndex, PM_SCPQ_HS_USB_IRQ_USBIN_PLUGIN, PM_IRQ_STATUS_RT, Valid)) == PM_ERR_FLAG_SUCCESS)
  {
	return EFI_SUCCESS;
  }
  else
  {
	errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  Status = (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS: EFI_DEVICE_ERROR;
  return Status;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgGetPowerPath
(
  IN  UINT32                  PmicDeviceIndex,
  OUT PM_SCHG_POWER_PATH_TYPE *PowerPath
)
{
  pm_scpq_chgr_status_type chargerStatus = {0};
  pm_scpq_hs_chgr_status_type chargerStatus_hs = {0};
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  if(NULL == PowerPath)
  {
    return EFI_INVALID_PARAMETER;
  }
  
  if(pm_scpq_chgr_get_chgr_status(PmicDeviceIndex, &chargerStatus) == PM_ERR_FLAG_SUCCESS)
  {
    if(chargerStatus.charger_status.valid_input_power_source)
    {
      //either usb or wireless
      BOOLEAN Valid = FALSE;
      errFlag = pm_scpq_usb_irq_status(PmicDeviceIndex, PM_SCPQ_USB_IRQ_USBIN_PLUGIN, PM_IRQ_STATUS_RT, &Valid);
      if(errFlag == PM_ERR_FLAG_SUCCESS)
      {
        if(Valid) 
        { 
          *PowerPath = PM_SCHG_POWER_PATH__USBIN; 
        }
        else
        {
          *PowerPath = PM_SCHG_POWER_PATH__DCIN; 
        }        
      }
      else
      {
        //todo print out error.
        *PowerPath = PM_SCHG_POWER_PATH__INVALID; 
        return EFI_DEVICE_ERROR;
      }            
    }
    else
    {
      *PowerPath = PM_SCHG_POWER_PATH__BATTERY; 
    }
    return EFI_SUCCESS;
  }
  else if(pm_scpq_hs_chgr_get_chgr_status(0,PmicDeviceIndex, (pm_scpq_hs_chgr_status_type*)&chargerStatus_hs))
  {
	if(chargerStatus_hs.charger_status.valid_input_power_source)
      {
        //either usb or wireless
        BOOLEAN Valid = FALSE;
        errFlag = pm_scpq_hs_usb_irq_status(0,PmicDeviceIndex, PM_SCPQ_HS_USB_IRQ_USBIN_PLUGIN, PM_IRQ_STATUS_RT, &Valid);
        if(errFlag == PM_ERR_FLAG_SUCCESS)
        {
          if(Valid) 
          { 
            *PowerPath = PM_SCHG_POWER_PATH__USBIN; 
          }
          else
          {
            *PowerPath = PM_SCHG_POWER_PATH__DCIN; 
          }        
        }
        else
        {
          //todo print out error.
          *PowerPath = PM_SCHG_POWER_PATH__INVALID; 
          return EFI_DEVICE_ERROR;
        }            
      }
      else
      {
        *PowerPath = PM_SCHG_POWER_PATH__BATTERY; 
      }
      return EFI_SUCCESS;
  }

  return EFI_DEVICE_ERROR;
}


/**
EFI_PmicSchgIsBatteryPresent ()

@brief
Gets battery presence status
*/
EFI_STATUS
EFIAPI
EFI_PmicSchgIsBatteryPresent
(
  IN  UINT32 PmicDeviceIndex,
  OUT BOOLEAN *BatteryPresent
)
{
  return EFI_SUCCESS;
}


/**
EFI_PmicChargerPortType ()

@brief
Gets charger port type
*/
EFI_STATUS
EFIAPI
EFI_PmicSchgGetChargerPortType
(
  IN  UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCHG_CHGR_PORT_TYPE *PortType
)
{
  pm_err_flag_type  errFlag       = PM_ERR_FLAG_SUCCESS;
  BOOLEAN           ApsdDoneStatus = FALSE;
  //BOOLEAN           bc1p2_en = FALSE;
  UINT32            ApsdDoneCheckIteration = 0;

  if(NULL == PortType)
  {
    return EFI_INVALID_PARAMETER;
  }

  *PortType = EFI_PM_SCHG_CHG_PORT_INVALID;

  //errFlag = pm_scpq_usb_configure_usb_icl_options(PmicDeviceIndex, PM_CHG_USB_AUTO_SRC_DETECT, &bc1p2_en);
  //if(PM_ERR_FLAG_SUCCESS != errFlag)
  //{
  //  return EFI_DEVICE_ERROR;
  //}
  //if(!bc1p2_en)
  //{
  //  *PortType = EFI_PM_SCHG_CHG_PORT_SDP_CHARGER;
  //  return EFI_SUCCESS;
  //}
  
  do
  {
    do
	{
		if((errFlag = pm_scpq_usb_get_apsd_status(PmicDeviceIndex, PM_SCPQ_USB_APSD_STATUS_APSD_DTC_STATUS_DONE , &ApsdDoneStatus)) == PM_ERR_FLAG_SUCCESS)
		{
			break;
		}			
		else if((errFlag = pm_scpq_hs_usb_get_apsd_status(0,PmicDeviceIndex, PM_SCPQ_HS_USB_APSD_STATUS_APSD_DTC_STATUS_DONE , &ApsdDoneStatus)) == PM_ERR_FLAG_SUCCESS)
		{
			break;
		}
		else
		{
			errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
			break;
		}
	}while(FALSE);
	
    PMIC_UART_DEBUG(( EFI_D_WARN, "PmicDxe:: %a APSD done status: %d \n\r", __FUNCTION__, ApsdDoneStatus));
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      break;
    }

    if(TRUE == ApsdDoneStatus)
    {
		if((errFlag =  pm_scpq_usb_get_apsd_result_status(PmicDeviceIndex, (pm_chg_charger_port_type*) PortType)) == PM_ERR_FLAG_SUCCESS)
		{
			break;
		}
		else if ((errFlag = pm_scpq_hs_usb_get_apsd_result_status(0,PmicDeviceIndex, (pm_chg_charger_port_type*) PortType)) == PM_ERR_FLAG_SUCCESS)
		{
			break;
		}
		else
		{
			errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
			break;
		}
    }
    else
    {
		/*if APSD result is not available yet, read again after 200 milli second.*/
		PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a APSD not done, stalling for 200mS before re-checking \n\r", __FUNCTION__));
		gBS->Stall(PM_SCHG_200_MS_WAIT);
    }

    ApsdDoneCheckIteration ++;

  }while ((FALSE == ApsdDoneStatus) && (ApsdDoneCheckIteration < PMIC_SCHG_MAX_APSD_DONE_CHECK_ITERATION));

  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    *PortType = EFI_PM_SCHG_CHG_PORT_INVALID;
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgConfigOtg
(
IN  UINT32                    PmicDeviceIndex,
IN  EFI_PM_SCHG_DCDC_OTG_CFG_TYPE  OtgCfgType,
IN  BOOLEAN                   SetValue
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgSetOtgILimit
(
IN  UINT32   PmicDeviceIndex,
IN  UINT32   ImAmp
)
{
  return EFI_SUCCESS;
}


/**
  Sets Maximum USB current

  @param MaxCurrent  Current to be set

  @return
  EFI_SUCCESS:           Function returned successfully.
  EFI_INVALID_PARAMETER: A Parameter was incorrect.
  EFI_DEVICE_ERROR:      The physical device reported an error.
  EFI_NOT_READY:         The physical device is busy or not ready to
                         process this request.
*/

EFI_STATUS
EFIAPI
EFI_PmicSchgSetUsbMaxCurrent
(
  IN UINT32 PmicDeviceIndex,
  IN UINT32 MaxCurrent
)
{
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
EFI_PmicSchgEnableAfpMode
(
  IN  UINT32   PmicDeviceIndex
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgSetInputPriority
(
   IN  UINT32                          PmicDeviceIndex,
   IN  EFI_PM_SCHG_INPUT_PRIORITY_TYPE InputPriority
)
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgEnableChgWdog
(
  IN UINT32  PmicDeviceIndex,
  IN BOOLEAN Enable
)
{
  EFI_STATUS         Status      = EFI_SUCCESS;
  pm_err_flag_type   err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_scpq_chgr_wdog_cfg_type  wdog_cfg = {0};
  pm_scpq_hs_misc_wdog_cfg_type scpq_hs_wdog_cfg = {0};

  if(pm_scpq_chgr_get_config_wdog(PmicDeviceIndex, &wdog_cfg) == PM_ERR_FLAG_SUCCESS)
  {
	  wdog_cfg.wdog_timer_en = Enable;
	  //if enable, charging will disable when charger wdog bite
	  wdog_cfg.bite_wdog_disable_charging_cfg = Enable;

	  err_flag |= pm_scpq_chgr_config_wdog(PmicDeviceIndex, wdog_cfg);
  }
  else if(pm_scpq_hs_misc_get_config_wdog(0, PmicDeviceIndex, &scpq_hs_wdog_cfg) == PM_ERR_FLAG_SUCCESS)
  {
	scpq_hs_wdog_cfg.wdog_timer_en = Enable;
    //if enable, charging will disable when charger wdog bite
    scpq_hs_wdog_cfg.bite_wdog_disable_charging_cfg = Enable;
    err_flag |= pm_scpq_hs_misc_config_wdog(0, PmicDeviceIndex, scpq_hs_wdog_cfg);
	  
  }
  else 
  {
	err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  Status = (PM_ERR_FLAG_SUCCESS == err_flag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgSetFccMaxCurrent
(
  IN UINT32 PmicDeviceIndex,
  IN UINT32 MaxCurrentInmA
)
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgSetFvMaxVoltage
(
  IN UINT32 PmicDeviceIndex,
  IN UINT32 MaxVoltageInMv
)
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgEnableOtg
(
  IN  UINT32   PmicDeviceIndex,
  IN  BOOLEAN  Enable
)
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgGetOtgStatus
(
   IN  UINT32                       PmicDeviceIndex,
   OUT EFI_PM_SCHG_DCDC_OTG_STATUS_TYPE  *pOtgStatus
)
{
    EFI_STATUS         Status      = EFI_SUCCESS;
    pm_err_flag_type   err_flag    = PM_ERR_FLAG_SUCCESS;
    pm_scpq_dcdc_otg_status_type TempOtgStatus = PM_SCPQ_DCDC_OTG_STATUS_INVALID;
	pm_scpq_hs_dcdc_otg_status_type TempOtgStatus_hs = PM_SCPQ_HS_DCDC_OTG_STATUS_INVALID;
	
	if(pm_scpq_dcdc_get_otg_status(PmicDeviceIndex, &TempOtgStatus) == PM_ERR_FLAG_SUCCESS)
	{
		err_flag    = PM_ERR_FLAG_SUCCESS;
		switch (TempOtgStatus)
		{
		  case PM_SCPQ_DCDC_OTG_DISABLED: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_DISABLED;
			break;
		  case PM_SCPQ_DCDC_OTG_EXECUTING_ENABLE_SEQ: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_EXECUTING_ENABLE_SEQ;
			break;
		  case PM_SCPQ_DCDC_OTG_ENABLED: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ENABLED;
			break;
		  case PM_SCPQ_DCDC_OTG_EXECUTING_DISABLE_SEQ: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_EXECUTING_DISABLE_SEQ;
			break;
		  case PM_SCPQ_DCDC_OTG_STATUS_INVALID: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_DISABLED;
			break;
		  case PM_SCPQ_DCDC_OTG_ERROR: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ERROR;
			break;
		  default: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ERROR;
		}		
	}
	else if (pm_scpq_hs_dcdc_get_otg_status(0,PmicDeviceIndex,(pm_scpq_hs_dcdc_otg_status_type*)&TempOtgStatus_hs) == PM_ERR_FLAG_SUCCESS)
	{
		err_flag    = PM_ERR_FLAG_SUCCESS;
		switch (TempOtgStatus_hs)
		{
		  case PM_SCPQ_HS_DCDC_OTG_DISABLED: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_DISABLED;
			break;
		  case PM_SCPQ_HS_DCDC_OTG_EXECUTING_ENABLE_SEQ: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_EXECUTING_ENABLE_SEQ;
			break;
		  case PM_SCPQ_HS_DCDC_OTG_ENABLED: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ENABLED;
			break;
		  case PM_SCPQ_HS_DCDC_OTG_EXECUTING_DISABLE_SEQ: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_EXECUTING_DISABLE_SEQ;
			break;
		  case PM_SCPQ_HS_DCDC_OTG_STATUS_INVALID: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_DISABLED;
			break;
		  case PM_SCPQ_HS_DCDC_OTG_ERROR: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ERROR;
			break;
		  default: 
			*pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ERROR;
		}
	}
	else
	{
		err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
	}
	
    

    Status = (PM_ERR_FLAG_SUCCESS == err_flag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

    return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgUsbSuspend
(
  IN UINT32  PmicDeviceIndex,
  IN BOOLEAN Enable
  )
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgPetChgWdog
(
  IN UINT32 PmicDeviceIndex
)
{
  EFI_STATUS         Status      = EFI_SUCCESS;
  pm_err_flag_type   err_flag    = PM_ERR_FLAG_SUCCESS;

  err_flag |= pm_scpq_chgr_bark_bite_wdog_pet(PmicDeviceIndex);
  if(pm_scpq_chgr_bark_bite_wdog_pet(PmicDeviceIndex) == PM_ERR_FLAG_SUCCESS)
  {
	  err_flag = PM_ERR_FLAG_SUCCESS;
  }
  else if (pm_scpq_hs_misc_bark_bite_wdog_pet(0, PmicDeviceIndex) == PM_ERR_FLAG_SUCCESS)
  {
	  err_flag = PM_ERR_FLAG_SUCCESS;
  }
  else
  {
	  err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  Status = (PM_ERR_FLAG_SUCCESS == err_flag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgPrintAiclSts
(
IN  UINT32   PmicDeviceIndex,
OUT BOOLEAN  *IsAICLComplete
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgChgrSourceReinserted
(
  IN  UINT32   PmicDeviceIndex,
  OUT BOOLEAN  *pReinserted
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgRerunAicl
(
  IN  UINT32                          PmicDeviceIndex,
  IN  EFI_PM_SCHG_AICL_RERUN_TIME_CFG RerunTime
  )
{
  return EFI_SUCCESS;
}



EFI_STATUS EFI_PmicSchgEnableJeita(UINT32 PmicDeviceIndex, EFI_PM_SCHG_JEITA_TYPE JeitaType)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgGetChargingStatus
(
  UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCHG_CHARGING_STATUS *pChargingStatus
)
{
  pm_scpq_chgr_status_type chargerStatus = {0};
    
  if(NULL == pChargingStatus)
  {
    return EFI_INVALID_PARAMETER;
  }
  
  if((pm_scpq_chgr_get_chgr_status(PmicDeviceIndex, &chargerStatus) == PM_ERR_FLAG_SUCCESS)
	  || (pm_scpq_hs_chgr_get_chgr_status(0, PmicDeviceIndex, (pm_scpq_hs_chgr_status_type*)&chargerStatus) == PM_ERR_FLAG_SUCCESS))
  {
    
    if((chargerStatus.charger_status.battery_charger_status == PM_SCPQ_BATT_CHGR_STATUS_TRICKLE) || 
        (chargerStatus.charger_status.battery_charger_status  == PM_SCPQ_BATT_CHGR_STATUS_PRECHARGE) ||
        (chargerStatus.charger_status.battery_charger_status  == PM_SCPQ_BATT_CHGR_STATUS_FULLON) || 
        (chargerStatus.charger_status.battery_charger_status  == PM_SCPQ_BATT_CHGR_STATUS_TAPER))
    {
      *pChargingStatus = EFI_PM_SCHG_CHARGING_ENABLED;
    }
    else
    {
      *pChargingStatus = EFI_PM_SCHG_CHARGING_DISABLED;
    } 
    return EFI_SUCCESS;
  }
  
  return EFI_DEVICE_ERROR;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgDCInValid
(
IN  UINT32 PmicDeviceIndex,
OUT BOOLEAN *Valid
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  if(NULL == Valid)
  {
    return EFI_INVALID_PARAMETER;
  }
  if(pm_scpq_wls_irq_status(PmicDeviceIndex, PM_SCPQ_WLS_IRQ_DCIN_PLUGIN, PM_IRQ_STATUS_RT, Valid) == PM_ERR_FLAG_SUCCESS)
  {
	 errFlag = PM_ERR_FLAG_SUCCESS;
  }
  else if(pm_scpq_hs_wls_irq_status(0,PmicDeviceIndex) == PM_ERR_FLAG_SUCCESS)
  {
	 errFlag = PM_ERR_FLAG_SUCCESS;
  }
  else
  {
	errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;  
  }
  
  Status = (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS: EFI_DEVICE_ERROR;
  return Status;
}




EFI_STATUS
EFIAPI
EFI_PmicSchgDCInSuspend
(
IN  UINT32 PmicDeviceIndex,
IN  BOOLEAN Suspend
)
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgSetDCInPower
(
IN  UINT32  PmicDeviceIndex,
IN  UINT32  PowerInMicroWalts
)
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgSetUsbIclMode
(
  UINT32                            PmicDeviceIndex,
  IN EFI_PM_SCHG_USB_ICL_MODE_TYPE  IclModeType
)
{
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicSchgGetChgWdogStatus
(
  IN UINT32                     PmicDeviceIndex,
  OUT EFI_PM_SCHG_WDOG_STS_TYPE *pWdogSts
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgEnableHWJeita(UINT32 PmicDeviceIndex, BOOLEAN Enable)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgToggleWipowerSDLatch(UINT32 PmicDeviceIndex)
{ 
	return EFI_UNSUPPORTED;
}

EFI_STATUS EFI_PmicSchgSetDcInCurrent(UINT32 PmicDeviceIndex, UINT32 dcInCurrentLimit)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetChargeCmdBit(UINT32 PmicDeviceIndex, BOOLEAN Enable)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  
  if(pm_scpq_chgr_enable_charging(PmicDeviceIndex, Enable) == PM_ERR_FLAG_SUCCESS)
  {
	  errFlag = PM_ERR_FLAG_SUCCESS;
  }
  else if(pm_scpq_hs_chgr_enable_charging(0,PmicDeviceIndex, Enable) == PM_ERR_FLAG_SUCCESS)
  {
	  errFlag = PM_ERR_FLAG_SUCCESS;
  }
  else
  {
	  errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;	  
  }
  
  return (errFlag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

/**
EFI_PmicSchgGetPmicInfo ()

@brief
Provides SCHG charger PMIC Index.
*/
EFI_STATUS
EFIAPI
EFI_PmicSchgGetPmicInfo
(
  OUT EFI_PM_SCHG_PMIC_INFO *SchgPmicInfo
)
{
  SchgPmicInfo->PmicIndex[0] = CHARGER_PMIC_IDX;
  SchgPmicInfo->SlaveIndex[0] = CHARGER_PMIC_IDX;
  return EFI_SUCCESS;
}

EFI_STATUS
EFI_PmicSchgGetChargerPmicIndex
(
    OUT UINT8 *ChargerPmicIndex
)
{
	if(NULL == ChargerPmicIndex)
		return EFI_INVALID_PARAMETER;
	else{
		pm_chg_get_primary_charger_pmic_index((UINT32*)ChargerPmicIndex);
	}
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgConfigApsd
(
  IN  UINT32                      PmicDeviceIndex
)
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgConfigHvdcp
(
  IN UINT32                       PmicDeviceIndex,
  IN EFI_SCHG_HVDCP_CFGDATA_TYPE *pSchgHvdcpDataType
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetIclStatus
(
IN UINT32                       PmicDeviceIndex,
OUT EFI_PM_SCHG_ICL_STATUS *pIclStatus
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_dcdc_icl_status_type iclsts = {0};
  boolean bAiclDone = FALSE;

  if (!pIclStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  if((errFlag = pm_scpq_dcdc_get_icl_status(PmicDeviceIndex, &iclsts)) == PM_ERR_FLAG_SUCCESS)
  {
	errFlag |= pm_scpq_misc_irq_status(PmicDeviceIndex, PM_SCPQ_MISC_IRQ_AICL_DONE, PM_IRQ_STATUS_RT, &bAiclDone);
  }
  else if ((errFlag =  pm_scpq_hs_dcdc_get_icl_status(0, PmicDeviceIndex, (pm_scpq_hs_dcdc_icl_status_type*)&iclsts)) == PM_ERR_FLAG_SUCCESS)
  {
	errFlag |= pm_scpq_hs_misc_irq_status(0,PmicDeviceIndex, PM_SCPQ_HS_MISC_IRQ_AICL_DONE, PM_IRQ_STATUS_RT, &bAiclDone);
  }
  else
  {
	errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }

  pIclStatus->max_icl_status = iclsts.icl_max_status;
  pIclStatus->aicl_icl_status = iclsts.icl_aicl_status;
  pIclStatus->thermal_icl_status = iclsts.icl_thm_status;
  pIclStatus->final_icl_status = iclsts.icl_final_status;
  pIclStatus->aicl_done = bAiclDone;
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetVconn
(
IN UINT32                       PmicDeviceIndex,
IN BOOLEAN                     VconnEn
)
  {
    return EFI_SUCCESS;
  }


EFI_STATUS EFI_PmicSchgGetPortState
(
IN UINT32                       PmicDeviceIndex,
OUT  EFI_PM_SCHG_TYPEC_PORT_STATUS  *TypeCStatus
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  pm_chg_typec_status_type typec_status = { 0 };

  if (!TypeCStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  if(pm_scpq_usb_get_typec_status(PmicDeviceIndex, &typec_status) == PM_ERR_FLAG_SUCCESS)
  {
	errFlag = PM_ERR_FLAG_SUCCESS;
  }
  else if (pm_scpq_hs_usb_get_typec_status(0,PmicDeviceIndex, &typec_status) == PM_ERR_FLAG_SUCCESS)
  {
	errFlag = PM_ERR_FLAG_SUCCESS;
  }
  else
  {
	errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  if (PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  else
  {
    TypeCStatus->cc_out_sts = (EFI_PM_SCHG_TYPEC_CC_OUT_STATUS)typec_status.cc_out_sts;
    TypeCStatus->dfp_curr_adv = (EFI_PM_SCHG_TYPEC_DFP_CURR_ADV)typec_status.dfp_curr_adv;
    TypeCStatus->ufp_conn_type = (EFI_PM_SCHG_TYPEC_UFP_CONNECTOR_TYPE)typec_status.ufp_conn_type;
    TypeCStatus->vbus_sts = typec_status.vbus_sts;
    TypeCStatus->vbus_err_sts = typec_status.vbus_err_sts;
    TypeCStatus->debounce_done_sts = typec_status.debounce_done_sts;
    TypeCStatus->vconn_oc_sts = typec_status.vconn_oc_sts;
    TypeCStatus->ccout_out_hiz_sts = typec_status.ccout_out_hiz_sts;
  }

  return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgGetConnectState
(
IN UINT32                       PmicDeviceIndex,
OUT  EFI_PM_SCHG_TYPEC_CONNECT_MODE_STATUS  *TypeCConnStatus
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  pm_chg_typec_port_role_type port_role = PM_CHG_TYPEC_ROLE_NONE;

  if (!TypeCConnStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  if(pm_scpq_usb_typec_get_port_role(PmicDeviceIndex, &port_role) == PM_ERR_FLAG_SUCCESS)
  {
	  errFlag = PM_ERR_FLAG_SUCCESS;
  }
  else if (pm_scpq_hs_usb_typec_get_port_role(0,PmicDeviceIndex, &port_role) == PM_ERR_FLAG_SUCCESS)
  {
	  errFlag = PM_ERR_FLAG_SUCCESS;
  }
  else
  {
	  errFlag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  if (PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  else
  {
    *TypeCConnStatus = (EFI_PM_SCHG_TYPEC_CONNECT_MODE_STATUS)port_role;
  }

  return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgGetHwJeitaStatus
(
IN UINT32                       PmicDeviceIndex,
OUT EFI_PM_SCHG_BATT_TEMP_STATUS  *pHwJeitaStatus
)
{
  return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgGetDCIrqStatus
(
IN  UINT32 						PmicDeviceIndex,
IN	EFI_PM_SCHG_DC_IRQ_TYPE		irq,
OUT BOOLEAN*					irq_status
)
{
  return EFI_SUCCESS;
}


EFI_STATUS EFI_EnDebugAccessoryMode
(
IN UINT32                       PmicDeviceIndex,
IN  BOOLEAN                EnDbgAccessSnk,
IN  BOOLEAN                EnFmb
)
{
  return EFI_SUCCESS;
}


EFI_STATUS EFI_GetDAMConnectSts
(
IN  UINT32                       PmicDeviceIndex,
OUT  BOOLEAN                *ConnectSts
)
{
  /* Get DAM connect status */
  if(pm_scpq_typec_get_dam_connect_sts(PmicDeviceIndex, ConnectSts) == PM_ERR_FLAG_SUCCESS)
  {
	return EFI_SUCCESS;	  
  }
  else if(pm_scpq_hs_typec_get_dam_connect_sts(0, PmicDeviceIndex, ConnectSts) == PM_ERR_FLAG_SUCCESS)
  {
	return EFI_SUCCESS;	  
  }

  return EFI_DEVICE_ERROR;
}


EFI_STATUS EFI_SetDAMIcl
(
IN  UINT32                       PmicDeviceIndex,
IN  DAM_SEL_ICL                icl_sel
)
{
  return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgGetBattMissingStatus
(
IN  UINT32 						PmicDeviceIndex,
IN	EFI_PM_SCHG_BATT_MISSING_STATUS_TYPE		status_type,
OUT BOOLEAN*					status_val
)
{
  return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgGetActivePort
(
OUT UINT8*					  active_pmic_index
)
{
    EFI_STATUS            Status = EFI_SUCCESS;
    pm_err_flag_type      errFlag = PM_ERR_FLAG_SUCCESS;
    if (NULL == active_pmic_index)
    {
        Status = EFI_INVALID_PARAMETER;
    }
    else
    {
        *active_pmic_index = 0;
        if (gCharger_P_Count == 0)
        {
			errFlag = pm_scpq_chgr_get_scpq_pmic_info(gSchg_P_PmicIndex, gSchg_P_SlaveIndex, &gCharger_P_Count, MAX_CHARGING_PORT);
            if (PM_ERR_FLAG_SUCCESS != errFlag)
            {
                return EFI_DEVICE_ERROR;
            }
        }
		
		if (gCharger_P_Count == 0)
		{
			errFlag = pm_scpq_hs_chgr_get_scpq_hs_pmic_info(0,gSchg_P_PmicIndex, gSchg_P_SlaveIndex, &gCharger_P_Count, MAX_CHARGING_PORT);
			if (PM_ERR_FLAG_SUCCESS != errFlag)
			{
				return EFI_DEVICE_ERROR;
			}
		}
		
        if(gCharger_P_Count == 1)
        {
            *active_pmic_index = gSchg_P_PmicIndex[0];
        }
        else
        {
            return EFI_UNSUPPORTED;
        }
    }
    
    return Status;
}

EFI_STATUS EFI_PmicSetTestModeDischarging
(
IN BOOLEAN discharging
)
{
	return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetOS
(
IN EFI_PM_SCHG_OS_TYPE OS
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    uint8 data = 0;

    if(OS >= EFI_PM_SCHG_OS_INVALID)
    {
        return EFI_INVALID_PARAMETER;
    }

    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_16, SDAM_MEM_30_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }

    //Clear MSB 4bits and update OS type
    data = (data & 0x0E) | OS;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_16, SDAM_MEM_30_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a Set OS type write failed\n\r", __FUNCTION__));

      return EFI_DEVICE_ERROR;
    }

    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_16, SDAM_MEM_30_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }

    PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a SET OS value : %d\n\r", __FUNCTION__, data));
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetLogCategoriesFromSdam
(
  OUT UINT64* LoggingCategories 
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  
  errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM15_MEM_21_ADDR, 8, (UINT8 *)LoggingCategories);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a Get logging Category from SDAM failed\n\r", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetShipMode
(
IN BOOLEAN enable
)
{
  return EFI_SUCCESS; 
}

EFI_STATUS EFI_PmicSchgGetValidPonReasons
(
IN UINT64*					  pon_reason_arr
)
{
  return EFI_SUCCESS; 
}

EFI_STATUS EFI_PmicSchgSetOffModeSrc
(
IN UINT8 OffModeSrcCfg
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetOffModeSrcVbatThresh
(
IN UINT32 voltThHi,
IN UINT32 voltThLo
)
{
  return EFI_SUCCESS;
}
EFI_STATUS EFI_PmicSchgGetDVDDReset
(
OUT BOOLEAN* reset
)
{    
  return EFI_SUCCESS;  
}

EFI_STATUS EFI_PmicSchgSetMaxPwrReq
(
IN UINT8 config,
IN UINT8 negotiatedPwr_w
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetMaxPwrReq_BattSts
(
IN BOOLEAN batt_missing,
IN BOOLEAN batt_dead
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetMaxPwrReq
(
OUT UINT8 *config,
OUT UINT8 *negotiated_pwr

)
{
    return EFI_SUCCESS;
}
EFI_STATUS EFI_PmicSchgSetMaxPwrReq_SkipChgReset
(
IN BOOLEAN b_skip
)
{
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicSchgSetUsbInput
(
  IN UINT32 PmicDeviceIndex,
  IN UINT32 Voltage_mV,
  IN UINT32 Current_mA
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetPortEn
(
IN UINT8 PortIndex,
IN EFI_PM_SCHG_TYPEC_PORT_EN_TYPE PortEnType
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgEnableAICL
(
IN UINT32 PmicDeviceIndex,
IN BOOLEAN enable
)
{
    //return pm_schg_usb_aicl_options_cfg(PmicDeviceIndex, PM_SCHG_USB_AICL_CFG_AICL_EN, enable);
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgEnableAICLPeriodicRerun
(
IN UINT32 PmicDeviceIndex,
IN BOOLEAN enable
)
{
    //return pm_schg_usb_aicl_options_cfg(PmicDeviceIndex, PM_SCHG_USB_AICL_CFG_PERIODIC_RERUN_EN, enable);
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSetChargerCfg
(
UINT32 PmicDeviceIndex,
IN UINT32 fv_mv,
IN UINT32 fcc_ma
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSetChargerInhibit
(
UINT32 PmicDeviceIndex,
BOOLEAN enable
)
{
    //return pm_schg_chgr_set_inhibit(PmicDeviceIndex, enable);
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSetPonSWHardReset
(
UINT32 PmicDeviceIndex
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetChgDxeLoadStatus
(
BOOLEAN b_done)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetChargerConfigEn
(
UINT32 PmicDeviceIndex,
EFI_PM_SCHG_CHG_CONFIG_EN_TYPE config,
BOOLEAN enable
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetTypeCPortRole
(
UINT32 PmicDeviceIndex,
EFI_PM_SCHG_TYPEC_PORT_ROLE_TYPE RoleType
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetPortEn
(
IN UINT8 PortIndex,
IN EFI_PM_SCHG_TYPEC_PORT_EN_TYPE *PortEnType
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetRDOPDContractV
(
IN UINT32 rdo,
IN UINT16 voltage
)
{
    return EFI_SUCCESS;    
}

EFI_STATUS EFI_PmicSchgGetSavedActivePort
(
OUT EFI_PM_SCHG_SDAM_ACTIVE_PORT_INDEX* sdam_active_port_id
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetGoodBattSOC
(
IN UINT8 soc
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetDCINSupported
(
OUT BOOLEAN* supported
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetSWThermalAdjustment
(
IN UINT32   PmicDeviceIndex,
IN UINT32   adj_current_mA
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetChargingLimit
(
BOOLEAN b_enable,
UINT8 TargetSoc,
UINT8 DeltaSoc
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
 
    UINT8 data = 0; // bit 7 enable/disable, bits 6:0 are the targetsoc
    UINT8 mask = 0x80;

    data = (b_enable) ? (TargetSoc | mask) : 0;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_054_ADDR, 1, &data);
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    data = (b_enable) ? (DeltaSoc) : 0;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_053_ADDR, 1, &data);
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgCheckChargingLimit
(
OUT BOOLEAN* b_written
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    UINT8 hlos_written = 0;
    
    if (b_written == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_052_ADDR, 1, &hlos_written);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }
    
    *b_written = (hlos_written == 0xAA) ? TRUE : FALSE;
    return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgSetBatteryAuthentication
(
BOOLEAN enable
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
 
    UINT8 data = 0; 
    data = (enable) ? BATTAUTH_ENABLE : BATTAUTH_DISABLE;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_051_ADDR, 1, &data);
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }


    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetUnauthenticatedBatteryCharging
(
BOOLEAN enable
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
 
    UINT8 data = 0; 
    data = (enable) ? BATTAUTH_ENABLE : BATTAUTH_DISABLE;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_2, SDAM_MEM_039_ADDR, 1, &data);
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }


    return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgSetPowerState
(
IN EFI_PM_SCHG_POWER_STATE_TYPE pwr_state
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetUefiChargingMode
(IN EFI_PM_SCHG_UEFI_STATE_TYPE charging_mode)
{   
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetNumSerialBattery
(
IN UINT32  PmicDeviceIndex,
OUT UINT8* num_serial_battery
)
{
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetFakeBatStatus
(
IN UINT32 PmicDeviceIndex,
OUT BOOLEAN* is_fake_battery
)
{
    return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgGetConvertedRidFromSdam 
(
UINT32* batt_id
)
{
    if(batt_id == NULL) return EFI_INVALID_PARAMETER;
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    UINT32 id_sdam = 0;

    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_23, SDAM_MEM_30_ADDR, 2, (UINT8 *)&id_sdam);
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        PMIC_DEBUG((EFI_D_WARN, "PmicDxe:: %a Get converted RID from SDAM failed\n\r", __FUNCTION__));
        return EFI_DEVICE_ERROR;
    }
    *batt_id = id_sdam * 1000; //ohm

    return EFI_SUCCESS;
}


EFI_STATUS EFI_PmicSchgGetTadSdamInfo
(
OUT EFI_PM_SCHG_TAD_SDAM_INFO_TYPE* tad_sdaminfo
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS EFI_PmicSchgSetTadSdamInfo
(
IN EFI_PM_SCHG_TAD_SDAM_INFO_TYPE* tad_sdaminfo
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS EFI_PmicSchgGetSBLNegotiatedInfo
(
OUT UINT8* info
)
{
    return EFI_SUCCESS;
}


/**
PMIC SCHG UEFI Protocol implementation
*/
EFI_QCOM_PMIC_SCHG_PROTOCOL PmicSchgProtocolImplementation = 
{
  PMIC_SCHG_REVISION_8,
  EFI_PmicSchgInit,
  EFI_PmicSchgEnableCharger,
  EFI_PmicSchgGetPowerPath, 
  EFI_PmicSchgIsBatteryPresent,
  EFI_PmicSchgGetChargerPortType,
  EFI_PmicSchgConfigOtg,
  EFI_PmicSchgSetOtgILimit,
  EFI_PmicSchgEnableAfpMode,
  EFI_PmicSchgSetInputPriority,
  EFI_PmicSchgSetFccMaxCurrent,
  EFI_PmicSchgSetFvMaxVoltage,
  EFI_PmicSchgEnableOtg,
  EFI_PmicSchgUsbSuspend,
  EFI_PmicSchgEnableJeita,
  EFI_PmicSchgGetOtgStatus,
  EFI_PmicSchgUsbinValid,    
  EFI_PmicSchgSetUsbMaxCurrent,
  EFI_PmicSchgChgrSourceReinserted,
  EFI_PmicSchgRerunAicl,
  //EFI_PmicSchgPrintAiclSts,
  EFI_PmicSchgDumpPeripheral,
  EFI_PmicSchgEnableChgWdog,
  EFI_PmicSchgPetChgWdog,
  EFI_PmicSchgGetChargingStatus,
  EFI_PmicSchgDCInValid,
  EFI_PmicSchgDCInSuspend,
  EFI_PmicSchgSetDCInPower,
  EFI_PmicSchgExit,
  EFI_PmicSchgSetUsbIclMode,
  EFI_PmicSchgGetChgWdogStatus,
  EFI_PmicSchgEnableHWJeita,
  EFI_PmicSchgToggleWipowerSDLatch,
  EFI_PmicSchgSetDcInCurrent,
  EFI_PmicSchgSetChargeCmdBit,
  EFI_PmicSchgGetPmicInfo,
  EFI_PmicSchgConfigApsd,
  EFI_PmicSchgConfigHvdcp,
  EFI_PmicSchgGetIclStatus,
  EFI_PmicSchgSetVconn,
  EFI_PmicSchgGetPortState,
  EFI_PmicSchgGetConnectState,
  EFI_PmicSchgGetHwJeitaStatus,
  EFI_PmicSchgGetDCIrqStatus,
  EFI_EnDebugAccessoryMode,
  EFI_GetDAMConnectSts,
  EFI_SetDAMIcl,
  EFI_PmicSchgGetBattMissingStatus,
  EFI_PmicSchgGetActivePort,
  EFI_PmicSetTestModeDischarging,
  EFI_PmicSchgGetLogCategoriesFromSdam,
  EFI_PmicSchgGetChargerPmicIndex,
  EFI_PmicSchgSetShipMode,
  EFI_PmicSchgGetValidPonReasons,
  EFI_PmicSchgSetOffModeSrc,
  EFI_PmicSchgSetOffModeSrcVbatThresh,
  EFI_PmicSchgGetDVDDReset,
  EFI_PmicSchgSetOS,
  EFI_PmicSchgSetMaxPwrReq,
  EFI_PmicSchgGetMaxPwrReq,
  EFI_PmicSchgSetUsbInput,  
  EFI_PmicSchgSetMaxPwrReq_BattSts,
  EFI_PmicSchgSetMaxPwrReq_SkipChgReset,
  EFI_PmicSchgSetPortEn,
  EFI_PmicSchgEnableAICL,
  EFI_PmicSchgEnableAICLPeriodicRerun,
  EFI_PmicSetChargerCfg,
  EFI_PmicSetChargerInhibit, 
  EFI_PmicSetPonSWHardReset,
  EFI_PmicSchgSetChgDxeLoadStatus,
  EFI_PmicSchgSetChargerConfigEn,
  EFI_PmicSchgSetTypeCPortRole,
  EFI_PmicSchgGetPortEn,
  EFI_PmicSchgSetRDOPDContractV,
  EFI_PmicSchgGetSavedActivePort,
  EFI_PmicSchgSetGoodBattSOC,
  EFI_PmicSchgGetDCINSupported,
  EFI_PmicSchgSetSWThermalAdjustment,
  EFI_PmicSchgSetChargingLimit,
  EFI_PmicSchgCheckChargingLimit,
  EFI_PmicSchgSetBatteryAuthentication,
  EFI_PmicSchgSetUnauthenticatedBatteryCharging,
  EFI_PmicSchgSetPowerState,
  EFI_PmicSchgSetUefiChargingMode,
  EFI_PmicSchgGetNumSerialBattery,
  EFI_PmicSchgGetFakeBatStatus,
  EFI_PmicSchgGetConvertedRidFromSdam,
  EFI_PmicSchgGetTadSdamInfo,
  EFI_PmicSchgSetTadSdamInfo,
  EFI_PmicSchgGetSBLNegotiatedInfo,
};

