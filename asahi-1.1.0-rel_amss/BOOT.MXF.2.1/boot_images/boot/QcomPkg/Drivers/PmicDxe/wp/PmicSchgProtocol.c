/*! @file PmicSchgProtocol.c 

*  PMIC- SCHG MODULE RELATED DECLARATION
*  This file contains functions and variable declarations to support 
*  the PMIC SCHG (Switch Mode Battery Charger) module.
*
*  Copyright (c) 2017 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Inc Proprietary and Confidential.
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
#include <Library/PmicLib/comm/src/pm_comm.h>

#include "pm_uefi.h"
#include "pm_version.h"
#include "pm_schg_usb.h"
#include "pm_schg_typec.h"
#include "pm_schg_misc.h"
#include "pm_schg_batif.h"
#include "pm_schg_chgr.h"
#include "pm_schg_dcdc.h"
#include "pm_bmd.h"
#include "pm_schg_bob.h"
#include "pm_sdam.h"

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


#define PM_SCHG_200_MS_WAIT                     200000 //200 milli Second wait
#define PMIC_SCHG_MAX_APSD_DONE_CHECK_ITERATION 5

#define SPMI_BUSID_0                    0
#define SPMI_BUSID_1                    1

EFI_PM_SCHG_CFGDATA_TYPE gSchgCfgData = {0}; 

STATIC UINT32  gSchgPmicIndex[MAX_CHARGING_PORT] = { 0 };
STATIC UINT32  gSchgSlaveIndex[MAX_CHARGING_PORT] = { 0 };
STATIC UINT32  gChargerCount = 0;

/*Charger dump */
#define PMIC_SCHG_PERIPHERAL_START_ADDR      0x1000
#define PMIC_SCHG_MISC_PERIPHERAL_START_ADDR 0x1600
#define PMIC_SCHG_PERIPHERAL_NUM        5
#define PM_DC_ZIN_ICL_PT_VOLT_MV         8000
#define PM_DC_ZIN_ICL_PT_HV_VOLT_MV      9000
#define PM_DC_ZIN_ICL_LV_VOLT_MV         5500
#define PM_DC_ZIN_ICL_MID_LV_VOLT_MV     6500
#define PM_DC_ZIN_ICL_MID_HV_VOLT_MV     8000
#define PM_DC_ZIN_ICL_HV_VOLT_MV         11000

#define PMIC_ALL_LAYER_REV_2 2
#define PMIC_METAL_REV_0 0

#define PMIC_SCHG_MAX_APSD_DONE_CHECK_ITERATION 5
#define PM_SCHG_200_MS_WAIT                     200000 //200 milli Second wait
#define PM_SCHG_2_MS_WAIT                       2000 //2 milli Second wait

#define PM_SCHG_OTG_CURRENT_LIMIT_1500_MA           1500
#define PM_SCHG_OTG_CURRENT_LIMIT_250_MA            250
#define PM_SCHG_OTG_WA_FPFET_SS                     0x3
#define PM_FORCE_USBICL_SDP_FLOAT_DEFAULT_IN_MA     500

#define SDAM_MEM_007_ADDR     7
#define SDAM_MEM_010_ADDR    10
#define SDAM_MEM_012_ADDR    12
#define SDAM_MEM_013_ADDR    13
#define SDAM_MEM_014_ADDR    14
#define SDAM_MEM_018_ADDR    18
#define SDAM_MEM_020_ADDR    20
#define SDAM_MEM_022_ADDR    22
#define SDAM_MEM_029_ADDR    29
#define SDAM_MEM_024_ADDR    24
#define SDAM_MEM_028_ADDR    28
#define SDAM_MEM_029_ADDR    29
#define SDAM_MEM_030_ADDR    30
#define SDAM_MEM_036_ADDR    36
#define SDAM_MEM_037_ADDR    37
#define SDAM_MEM_038_ADDR    38
#define SDAM_MEM_039_ADDR    39
#define SDAM_MEM_040_ADDR    40
#define SDAM_MEM_051_ADDR    51
#define SDAM_MEM_052_ADDR    52
#define SDAM_MEM_053_ADDR    53
#define SDAM_MEM_054_ADDR    54
#define SDAM_MEM_055_ADDR    55
#define SDAM_MEM_056_ADDR    56
#define SDAM_MEM_057_ADDR    57
#define SDAM_MEM_058_ADDR    58
#define SDAM_MEM_059_ADDR    59
#define SDAM_MEM_041_ADDR    41
#define SDAM_MEM_049_ADDR    49
#define SDAM_MEM_060_ADDR    60
#define SDAM_MEM_061_ADDR    61
#define SDAM_MEM_062_ADDR    62
#define SDAM_MEM_064_ADDR    64
#define SDAM_MEM_066_ADDR    66
#define SDAM_MEM_068_ADDR    68
#define SDAM_MEM_078_ADDR    78
#define SDAM_MEM_080_ADDR    80

#define TZ_RESET_DONE        0xA5
#define CHG_DXE_LOADED       0x80
#define BTMTHR_COEFF0        1156
#define BTMTHR_COEFF1        75
#define BTMTHR_COEFF2        6

#define USB_INPUT_CURRENT_LIMIT_900MA           900
#define USB_INPUT_CURRENT_LIMIT_500MA           500
#define USB_INPUT_CURRENT_LIMIT_150MA           150
#define USB_INPUT_CURRENT_LIMIT_100MA           100

#define USBIN_ICL_OPTION_HC_MODE                PM_SCHG_USB_ICL_OPTIONS_USBIN_MODE_CHG                                        //0bXX1
#define USBIN_ICL_OPTION_100MA_MODE             0                                                                             //0b000
#define USBIN_ICL_OPTION_150MA_MODE             PM_SCHG_USB_ICL_OPTIONS_CFG_USB3P0_SEL                                        //0b100
#define USBIN_ICL_OPTION_500MA_MODE             PM_SCHG_USB_ICL_OPTIONS_USB51_MODE                                            //0b010
#define USBIN_ICL_OPTION_900MA_MODE             PM_SCHG_USB_ICL_OPTIONS_USB51_MODE | PM_SCHG_USB_ICL_OPTIONS_CFG_USB3P0_SEL   //0b110
#define USB_INPUT_CURRENT_LIMIT_CFG_STEP_SIZE   50
#define SDAM_ACTIVE_PORT_VALID_MASK             0x80

#define BATTAUTH_ENABLE 0x01
#define BATTAUTH_DISABLE 0x02

EFI_STATUS PmicSchgDumpPeripheral( VOID );

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
  EFI_STATUS              Status         = EFI_SUCCESS;

  if(!RETAIL)
  {
    Status = PmicSchgDumpPeripheral();
  }
  else
  {
    return EFI_UNSUPPORTED;
  }
  return Status;
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
  EFI_STATUS           Status  = EFI_SUCCESS;
  pm_err_flag_type     errFlag = PM_ERR_FLAG_SUCCESS;
  pm_schg_chgr_status_type    charger_status = {0};
  BOOLEAN              HWChargingEnabled = FALSE;

  PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a ChargerEnable: %d (0: Disable Charging, 1: Enable Charging)\r\n", __FUNCTION__, ChargerEnable ));

  errFlag |= pm_schg_chgr_get_chgr_status(SPMI_BUSID_1, PmicDeviceIndex, &charger_status);
  HWChargingEnabled = charger_status.status_5.charging_enable;

  pm_schg_chgr_enable_src(SPMI_BUSID_1, PmicDeviceIndex, FALSE);
  if(HWChargingEnabled == ChargerEnable)
  {
    PMIC_DEBUG((EFI_D_WARN, "PmicDxe:: %a No action required ChargerEnable = %d HWChargingEnable = %d charging_enable = %d \n\r", __FUNCTION__, 
                ChargerEnable, HWChargingEnabled, charger_status.status_5.charging_enable));
  }
  else
  {
    /* If Charging is disabled, and API is called to enable charging
       or if Charging is enabled and API is called to disable charging
       Perform register write */
    //UEFI does not have access to disable batt_id or therm for batt missing, charging cannot be disabled
    //errFlag |=  pm_schg_batif_cfg_batt_missing_src(PmicDeviceIndex, PM_SCHG_BAT_MISS_SRC_CFG__PIN_SRC_EN, (!ChargerEnable));
    //set to cmd control set it to FALSE always.
    errFlag |= pm_schg_chgr_enable_charging(SPMI_BUSID_1, PmicDeviceIndex, ChargerEnable);
    
  }

  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return (Status);    
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
  EFI_STATUS            Status  = EFI_SUCCESS;
  pm_err_flag_type      errFlag = PM_ERR_FLAG_SUCCESS;
  BOOLEAN               UsbinPlugedIn = FALSE;

  if(NULL == Valid)
  {
    Status = EFI_INVALID_PARAMETER;
  }
  else
  {
    /*Read IRQ real time status*/
    errFlag = pm_schg_usb_irq_status(SPMI_BUSID_1, PmicDeviceIndex, PM_SCHG_USB_IRQ_USBIN_PLUGIN, PM_IRQ_STATUS_RT,(boolean*)&UsbinPlugedIn);
    
    Status = (PM_ERR_FLAG_SUCCESS == errFlag)? EFI_SUCCESS : EFI_DEVICE_ERROR;

    *Valid = (UsbinPlugedIn) ? TRUE : FALSE;
  }

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
  EFI_STATUS                  Status  = EFI_SUCCESS;

  return Status;
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
#define BATTERY_VOLTAGE_MULTIPLIER      300
#define BATTERY_VOLTAGE_DIVISOR         1156
#define NO_VBATCELL_TH_MV               2500
  int16 pon_vbattcell_raw = 0;
  static int32 pon_vbattcell_mv = 0;
  static BOOLEAN sb_pon_vbattcell_mv_read = FALSE;

  if(NULL == BatteryPresent)
  {
    return EFI_INVALID_PARAMETER;
  }

  if(!sb_pon_vbattcell_mv_read)
  {
    pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_010_ADDR, sizeof(pon_vbattcell_raw), (uint8*)&pon_vbattcell_raw);
    pon_vbattcell_mv = (int32) pon_vbattcell_raw;
    pon_vbattcell_mv = pon_vbattcell_mv * BATTERY_VOLTAGE_MULTIPLIER / BATTERY_VOLTAGE_DIVISOR;

    sb_pon_vbattcell_mv_read = TRUE;
  }
  
  // Consider Battery is not present if pon VBAT is close to 0
  if(pon_vbattcell_mv < NO_VBATCELL_TH_MV)
  {
    *BatteryPresent = FALSE;
  }
  else
  {
    *BatteryPresent = TRUE;
  }
  PMIC_UART_DEBUG(( EFI_D_WARN, "PmicDxe:: %a pon_vbattcell_mv=%d,  BatteryPresent=%d\n\r", __FUNCTION__, pon_vbattcell_mv, *BatteryPresent));
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
  BOOLEAN           bc1p2_en = FALSE;
  UINT32            ApsdDoneCheckIteration = 0;

  if(NULL == PortType)
  {
    return EFI_INVALID_PARAMETER;
  }

  *PortType = EFI_PM_SCHG_CHG_PORT_INVALID;

  
  errFlag = pm_schg_usb_get_usbin_option1_cfg(SPMI_BUSID_1, PmicDeviceIndex, PM_SCHG_USB_BC1P2_SRC_DETECT, &bc1p2_en);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  if(!bc1p2_en)
  {
    *PortType = EFI_PM_SCHG_CHG_PORT_SDP_CHARGER;
    return EFI_SUCCESS;
  }
  
  do
  {
    errFlag = pm_schg_usb_get_apsd_status(SPMI_BUSID_1, PmicDeviceIndex, PM_SCHG_USB_APSD_STATUS_APSD_DTC_STATUS_DONE , &ApsdDoneStatus);
    PMIC_UART_DEBUG(( EFI_D_WARN, "PmicDxe:: %a APSD done status: %d \n\r", __FUNCTION__, ApsdDoneStatus));
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      break;
    }

    if(TRUE == ApsdDoneStatus)
    {
      errFlag =  pm_schg_usb_get_apsd_result_status(SPMI_BUSID_1, PmicDeviceIndex, (pm_chg_charger_port_type*) PortType);
      if(PM_ERR_FLAG_SUCCESS != errFlag)
      {
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
  pm_err_flag_type  errFlag       = PM_ERR_FLAG_SUCCESS;
  pm_schg_dcdc_otg_cfg_type cfg   = PM_SCHG_DCDC_OTG_CFG_INVALID;

  switch(OtgCfgType)
  {
  case EFI_PM_SCHG_DCDC_OTG_CFG_OTG_EN_SRC_CFG:
    cfg = PM_SCHG_DCDC_OTG_CFG_OTG_EN_SRC_CFG;
    break;
  case EFI_PM_SCHG_DCDC_OTG_CFG_ENABLE_OTG_IN_DEBUG_MODE:
    cfg = PM_SCHG_DCDC_OTG_CFG_ENABLE_OTG_IN_DEBUG_MODE;
    break;
  default:
    return EFI_UNSUPPORTED;
  }

  errFlag = pm_schg_dcdc_config_otg(SPMI_BUSID_1, PmicDeviceIndex, cfg, SetValue);
  
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
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
EFI_PmicSchgSetUsbInput
(
  IN UINT32 PmicDeviceIndex,
  IN UINT32 Voltage_mV,
  IN UINT32 Current_mA
)
{

  EFI_STATUS status = EFI_SUCCESS;
  /*pm_schg_usb_icl_options_type usbin_mode_chg = PM_SCHG_USB_ICL_OPTIONS_INVALID;
  switch(Current_mA)
  {
    case USB_INPUT_CURRENT_LIMIT_900MA:
      usbin_mode_chg = PM_SCHG_USB_ICL_OPTIONS_INVALID;
      break;
    case USB_INPUT_CURRENT_LIMIT_500MA:
      usbin_mode_chg = USBIN_ICL_OPTION_500MA_MODE;
      break;
    case USB_INPUT_CURRENT_LIMIT_150MA:
      usbin_mode_chg = USBIN_ICL_OPTION_150MA_MODE;
      break;
    case USB_INPUT_CURRENT_LIMIT_100MA:
      usbin_mode_chg = USBIN_ICL_OPTION_100MA_MODE;
      break;
    default:
      usbin_mode_chg = USBIN_ICL_OPTION_HC_MODE;
      break;
  }

  if(usbin_mode_chg == USBIN_ICL_OPTION_HC_MODE)
  {
    //Mitigation for ICL inaccuracy for VIN >=12V, reduce ICL setting by 2step (= 2*50 = 100mA)
    if(Voltage_mV >= 12000)
    {
        Current_mA -= (2 * USB_INPUT_CURRENT_LIMIT_CFG_STEP_SIZE);
    }

    status = pm_schg_usb_set_usbin_current_limit_cfg(PmicDeviceIndex, Current_mA);
    if (status != EFI_SUCCESS){return status;}
  }

  status = pm_schg_usb_configure_usbin_icl_options(PmicDeviceIndex, usbin_mode_chg, TRUE);
  if (status != EFI_SUCCESS){return status;}
    
  //set icl override
  status = pm_schg_usb_cmd_icl_override(PmicDeviceIndex, TRUE);
  status |= (EFI_STATUS)pm_schg_usb_enable_icl_override_after_apsd(PmicDeviceIndex, TRUE);
  if (status != EFI_SUCCESS){return status;}*/

  return status;
}

EFI_STATUS EFI_PmicSchgSetNoDVDDReset
(
OUT BOOLEAN enable
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  UINT8 data = 0;

  /*** Read SDAM AFP Flag ***/
  errFlag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_022_ADDR, 1, &data);//0x40 + 22 = 0x56
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
	PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a fail to read sdam\r\n", __FUNCTION__));
	return EFI_DEVICE_ERROR;
  }

  data |= (enable ? 0x2 : 0); 
  //sdam_set_no_dvdd_rb
  errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_022_ADDR, 1, &data);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
	PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a fail to write sdam\r\n", __FUNCTION__));
    return EFI_DEVICE_ERROR;
  }
     
  return EFI_SUCCESS;  
}

EFI_STATUS
EFIAPI
EFI_PmicSchgEnableAfpMode
(
  IN  UINT32   PmicDeviceIndex
)
{
  EFI_STATUS           Status  = EFI_SUCCESS;
  pm_err_flag_type     errFlag = PM_ERR_FLAG_SUCCESS;
  UINT8 index = 0;

  PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a \r\n", __FUNCTION__));

  Status |= EFI_PmicSchgSetNoDVDDReset(TRUE);
  if(Status != EFI_SUCCESS)
	return Status;

  errFlag = pm_schg_chgr_get_schg_pmic_info(SPMI_BUSID_1, gSchgPmicIndex, gSchgSlaveIndex, &gChargerCount, MAX_CHARGING_PORT);

  PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a gChargerCount=%d\r\n", __FUNCTION__, gChargerCount));
  PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a enable AFP for PmicDeviceIndex=%d\r\n", __FUNCTION__, gSchgPmicIndex[gChargerCount - 1]));
  errFlag |= pm_schg_misc_en_afp(SPMI_BUSID_1, gSchgPmicIndex[gChargerCount - 1]);//Enable AFP for parallel charger

  PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a enable AFP for PmicDeviceIndex=%d\r\n", __FUNCTION__, PmicDeviceIndex));

  errFlag |= pm_schg_misc_en_afp(SPMI_BUSID_1, PmicDeviceIndex);
  for (index = 0; index < gChargerCount - 1; index++)
  {
	if(PmicDeviceIndex != index)
	{
	  errFlag |= pm_schg_misc_en_afp(SPMI_BUSID_1, gSchgPmicIndex[index]);
      PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a enable AFP for PmicDeviceIndex=%d\r\n", __FUNCTION__, gSchgPmicIndex[index]));
	}
  }

  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return (Status);
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
  EFI_STATUS           Status  = EFI_SUCCESS;
  pm_err_flag_type     errFlag = PM_ERR_FLAG_SUCCESS;
  pm_schg_misc_wdog_cfg_type wdog_cfg = { 0 };

  PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a : %d \r\n", __FUNCTION__, Enable));

  wdog_cfg.wdog_timer_en = Enable;
  errFlag |= pm_schg_misc_config_wdog(SPMI_BUSID_1, PmicDeviceIndex, wdog_cfg);
  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return (Status);
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
  pm_err_flag_type   err_flag    = PM_ERR_FLAG_SUCCESS;
  
  err_flag = pm_schg_dcdc_otg_enable(SPMI_BUSID_1, PmicDeviceIndex, Enable);
  
  if(PM_ERR_FLAG_SUCCESS != err_flag)
  {
    return EFI_DEVICE_ERROR;
  }
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
    pm_schg_dcdc_otg_status_type TempOtgStatus = PM_SCHG_DCDC_OTG_STATUS_INVALID;

    err_flag = pm_schg_dcdc_get_otg_status(SPMI_BUSID_1, PmicDeviceIndex, &TempOtgStatus);

    switch (TempOtgStatus)
    {
      case PM_SCHG_DCDC_OTG_DISABLED: 
        *pOtgStatus = EFI_PM_SCHG_DCDC_OTG_DISABLED;
        break;
      case PM_SCHG_DCDC_OTG_EXECUTING_ENABLE_SEQ: 
        *pOtgStatus = EFI_PM_SCHG_DCDC_OTG_EXECUTING_ENABLE_SEQ;
        break;
      case PM_SCHG_DCDC_OTG_ENABLED: 
        *pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ENABLED;
        break;
      case PM_SCHG_DCDC_OTG_EXECUTING_DISABLE_SEQ: 
        *pOtgStatus = EFI_PM_SCHG_DCDC_OTG_EXECUTING_DISABLE_SEQ;
        break;
      case PM_SCHG_DCDC_OTG_STATUS_INVALID: 
        *pOtgStatus = EFI_PM_SCHG_DCDC_OTG_DISABLED;
        break;
      case PM_SCHG_DCDC_OTG_ERROR: 
        *pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ERROR;
        break;
      default: 
        *pOtgStatus = EFI_PM_SCHG_DCDC_OTG_ERROR;
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
  EFI_STATUS           Status  = EFI_SUCCESS;
  pm_err_flag_type     errFlag = PM_ERR_FLAG_SUCCESS;

  PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a \r\n", __FUNCTION__));

  errFlag |= pm_schg_misc_bark_bite_wdog_pet(SPMI_BUSID_1, PmicDeviceIndex);

  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  return (Status);
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
EFI_STATUS PmicSchgDumpPeripheral( VOID )
{
  EFI_STATUS Status  = EFI_SUCCESS;
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  UINT8 index = 0;

  errFlag = pm_schg_chgr_get_schg_pmic_info(SPMI_BUSID_1, gSchgPmicIndex, gSchgSlaveIndex, &gChargerCount, MAX_CHARGING_PORT);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    PMIC_DEBUG((EFI_D_WARN, "PmicDxe::%a SCHG_PERIPHERAL get_schg_pmic_info Error (%d) \n\r", __FUNCTION__, errFlag));
    return EFI_UNSUPPORTED;
  }
  for (index = 0; index < gChargerCount; index++)
  {
    errFlag = pm_core_utils_dump_peripheral(1, gSchgSlaveIndex[index], PMIC_SCHG_PERIPHERAL_START_ADDR, PMIC_SCHG_PERIPHERAL_NUM);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
   PMIC_DEBUG((EFI_D_WARN, "PmicDxe::%a SCHG_PERIPHERAL pm_core_utils_dump_peripheral Error (%d) \r\n",  __FUNCTION__, errFlag));
  }

  /* Dump separately for Misc peripheral */
    errFlag |= pm_core_utils_dump_peripheral(1, gSchgSlaveIndex[index], PMIC_SCHG_MISC_PERIPHERAL_START_ADDR, 1);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    PMIC_DEBUG((EFI_D_WARN, "PmicDxe::%a SCHG_MISC_PERIPHERAL pm_core_utils_dump_peripheral Error (%d) \n\r", __FUNCTION__, errFlag));
  }

  Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
  }


  return Status;
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
  pm_schg_chgr_status_type chargerStatus = {0};
  pm_err_flag_type errFlag;
  
  if(NULL == pChargingStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pChargingStatus = EFI_PM_SCHG_CHARGING_INVALID;
  errFlag = pm_schg_chgr_get_chgr_status(SPMI_BUSID_1, PmicDeviceIndex, &chargerStatus);

  if(errFlag == PM_ERR_FLAG_SUCCESS)
  {

    switch(chargerStatus.status_1.battery_charger_status)
    {
      case PM_SCHG_BATT_CHGR_STATUS_TRICKLE:
      case PM_SCHG_BATT_CHGR_STATUS_PRECHARGE:
      case PM_SCHG_BATT_CHGR_STATUS_FULLON:
      case PM_SCHG_BATT_CHGR_STATUS_TAPER:
        *pChargingStatus = EFI_PM_SCHG_CHARGING_ENABLED;
        break;
      case PM_SCHG_BATT_CHGR_STATUS_INHIBIT:
        *pChargingStatus = EFI_PM_SCHG_CHARGING_INHIBITED;
        break;
      case PM_SCHG_BATT_CHGR_STATUS_TERMINATION:
        *pChargingStatus = EFI_PM_SCHG_CHARGING_TERMINATED;
        break;   
      case PM_SCHG_BATT_CHGR_STATUS_PAUSE:
        *pChargingStatus = EFI_PM_SCHG_CHARGING_PAUSED;
        break;
      default:
        *pChargingStatus = EFI_PM_SCHG_CHARGING_DISABLED;
        break;
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
  EFI_STATUS            Status = EFI_SUCCESS;

  if (NULL == Valid)
  {
    Status = EFI_INVALID_PARAMETER;
  }

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
  pm_err_flag_type     errFlag = PM_ERR_FLAG_SUCCESS;
  pm_schg_misc_wdog_status wdog_sts = PM_SCHG_MISC_BARK_BITE_INVALID;
  pm_schg_misc_sbb_wd_cfg wd_sbb_cfg = { 0 };

  PMIC_DEBUG(( EFI_D_WARN, "PmicDxe:: %a\r\n", __FUNCTION__));

  errFlag |= pm_schg_misc_get_misc_wdog_status(SPMI_BUSID_1, PmicDeviceIndex, &wdog_sts);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
	return EFI_DEVICE_ERROR;

  if(PM_SCHG_MISC_BARK == wdog_sts)
	*pWdogSts = EFI_PM_SCHG_WDOG_STS_BARK;
  else if(PM_SCHG_MISC_BITE == wdog_sts)
  {
	errFlag |= pm_schg_misc_get_snarl_bark_bite_wd_cfg(SPMI_BUSID_1, PmicDeviceIndex, &wd_sbb_cfg);
	if(PM_ERR_FLAG_SUCCESS != errFlag)
	  return EFI_DEVICE_ERROR;

	if(wd_sbb_cfg.bite_wdog_disable_charging_cfg)
	  *pWdogSts = EFI_PM_SCHG_WDOG_STS_BITE_CHARGING_DISABLED;
	else
	  *pWdogSts = EFI_PM_SCHG_WDOG_STS_BITE_CHARGING_NOT_DISABLED;
  }

  return (EFI_SUCCESS);
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
  return EFI_SUCCESS;
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
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  if(!SchgPmicInfo)
  {
    return EFI_INVALID_PARAMETER;
  }

  errFlag = pm_schg_chgr_get_schg_pmic_info(SPMI_BUSID_1, gSchgPmicIndex, gSchgSlaveIndex, &gChargerCount, MAX_CHARGING_PORT);

  if (PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }

  //to support hana, this API will only return the first charging port.
  memcpy(SchgPmicInfo->PmicIndex, gSchgPmicIndex, sizeof(UINT32)*MAX_CHARGING_PORT);
  memcpy(SchgPmicInfo->SlaveIndex, gSchgSlaveIndex, sizeof(UINT32)*MAX_CHARGING_PORT);
  SchgPmicInfo->ChargerCount = gChargerCount;
  
  return (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
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

	if (!pIclStatus)
	{
		return EFI_INVALID_PARAMETER;
	}

	errFlag = pm_schg_dcdc_get_icl_status(SPMI_BUSID_1, PmicDeviceIndex, (pm_schg_dcdc_icl_status_type*)pIclStatus);
	if (PM_ERR_FLAG_SUCCESS != errFlag)
	{
		return EFI_DEVICE_ERROR;
	}

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
	pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
	pm_chg_typec_status_type typec_status = { 0 };

	if (!TypeCStatus)
	{
		return EFI_INVALID_PARAMETER;
	}

	errFlag = pm_schg_usb_get_typec_status(SPMI_BUSID_1, PmicDeviceIndex, &typec_status);
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

	errFlag = pm_schg_usb_typec_get_port_role(SPMI_BUSID_1, PmicDeviceIndex, &port_role);
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
	pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
	pm_schg_chgr_status_type chgr_status = { { 0 } };

	if (!pHwJeitaStatus)
	{
		return EFI_INVALID_PARAMETER;
	}

	errFlag = pm_schg_chgr_get_chgr_status(SPMI_BUSID_1, PmicDeviceIndex, &chgr_status);
	if (PM_ERR_FLAG_SUCCESS != errFlag)
	{
		return EFI_DEVICE_ERROR;
	}
	else
	{
		pHwJeitaStatus->jeitaHardHot = chgr_status.status_7.bat_temp_status_too_hot;
		pHwJeitaStatus->jeitaSoftHot = chgr_status.status_7.bat_temp_status_hot_soft;
		pHwJeitaStatus->jeitaHardCold = chgr_status.status_7.bat_temp_status_too_cold;
		pHwJeitaStatus->jeitaSoftCold = chgr_status.status_7.bat_temp_status_cold_soft;
	}

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
	pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

	/* Get DAM connect status */
	errFlag = pm_schg_typec_get_dam_connect_sts(SPMI_BUSID_1, PmicDeviceIndex, ConnectSts);
	
	if (PM_ERR_FLAG_SUCCESS != errFlag)
	{
		return EFI_DEVICE_ERROR;
	}

	return EFI_SUCCESS;

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
  EFI_STATUS            Status = EFI_SUCCESS;
  pm_err_flag_type      errFlag = PM_ERR_FLAG_SUCCESS;
  boolean               st;

  if (NULL == status_val)
  {
    Status = EFI_INVALID_PARAMETER;
  }
  else
  {
    /*get batt missing status*/
    errFlag = pm_schg_batt_missing_status(SPMI_BUSID_1, PmicDeviceIndex, (pm_schg_batif_bat_miss_status_type)status_type, &st);
    Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? PM_ERR_FLAG_SUCCESS : EFI_DEVICE_ERROR;

    *status_val = st;
  }

  return Status;
}

EFI_STATUS EFI_PmicSchgGetActivePort
(
OUT UINT8*					  active_pmic_index
)
{
  EFI_STATUS            Status = EFI_SUCCESS;
  pm_err_flag_type      errFlag = PM_ERR_FLAG_SUCCESS;
  UINT8                 port_index = 0;
  BOOLEAN               is_active = FALSE, active_port_found = FALSE;

  if (NULL == active_pmic_index)
  {
    return EFI_INVALID_PARAMETER;
  }
  else
  {
    if (gChargerCount == 0)
    {
      //no charger or have not called pm_schg_chgr_get_schg_pmic_info
      errFlag = pm_schg_chgr_get_schg_pmic_info(SPMI_BUSID_1, gSchgPmicIndex, gSchgSlaveIndex, &gChargerCount, MAX_CHARGING_PORT);

      if (PM_ERR_FLAG_SUCCESS != errFlag)
      {
        return EFI_DEVICE_ERROR;
      }
    }
    //default to the first port if charger is not present
    *active_pmic_index = gSchgPmicIndex[0];
    for (port_index = 0; port_index < gChargerCount; port_index++)
    {
      errFlag = pm_schg_bob_is_port_active(SPMI_BUSID_1, gSchgPmicIndex[port_index], &is_active);
      if (PM_ERR_FLAG_FEATURE_NOT_SUPPORTED == errFlag)
      {
        return EFI_UNSUPPORTED;
      }
      if (is_active)
      {
        //found the first active port
        *active_pmic_index = gSchgPmicIndex[port_index];
        active_port_found = TRUE;
        break;
      }
    }
  }
  // if switcher is off for all ports, pick the port with batfet ctrl on to be active port
  if (!active_port_found)
  {
      /*for (port_index = 0; port_index < gChargerCount; port_index++)
      {
        errFlag = pm_schg_bob_is_batfet_ctrl_on(gSchgPmicIndex[port_index], &is_active);
        if (PM_ERR_FLAG_FEATURE_NOT_SUPPORTED == errFlag)
        {
          return EFI_UNSUPPORTED;
        }
        if (is_active)
        {
          //found the first active port
          *active_pmic_index = gSchgPmicIndex[port_index];
          break;
        }
      }*/
  }

  return Status;
}

EFI_STATUS EFI_PmicSchgSetTestModeDischarging
(
IN  BOOLEAN           testmode_discharging
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  uint8 data = 0;
  /* Set the ICL for DAM */
  errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_2, SDAM_MEM_036_ADDR, 1, &data);
  if (PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  data = (data & 0xFE) | testmode_discharging; //bit 7:1 should not change.
  errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_2, SDAM_MEM_036_ADDR, 1, &data);
  if (PM_ERR_FLAG_SUCCESS != errFlag)
  {
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
EFI_STATUS EFI_PmicSchgGetShipMode
(
IN BOOLEAN *enable
)
{
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetValidPonReasons
(
IN UINT64*					  pon_reason_arr
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  uint8 data = 0;
  uint8 ponhist_start_addr = 0;
  static UINT64 pon_history = 0;
  
  if (NULL == pon_reason_arr)
  {
    return EFI_INVALID_PARAMETER;
  }
  
  if(pon_history)
  {
    *pon_reason_arr = pon_history;
    return EFI_SUCCESS;
  }
  /*** Read SDAM Flag ***/
  errFlag |= pm_sdam_mem_read(0, PM_SDAM_15, SDAM_MEM_055_ADDR, 1, &data);
  
  /**** Check SDAM Flag and Read PON reasons for 1st/2nd latest reset ***/
  ponhist_start_addr = (TZ_RESET_DONE == data)? SDAM_MEM_049_ADDR: SDAM_MEM_041_ADDR;
  errFlag |= pm_sdam_mem_read(0, PM_SDAM_3, ponhist_start_addr, 8, (uint8*)pon_reason_arr);
  if(PM_ERR_FLAG_SUCCESS == errFlag)
  {
    pon_history = *pon_reason_arr;
    data = 0;
    pm_sdam_mem_write(0, PM_SDAM_15, SDAM_MEM_055_ADDR, 1, &data);
  }
  return (PM_ERR_FLAG_SUCCESS != errFlag) ? EFI_DEVICE_ERROR: EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetOffModeSrc
(
IN UINT8 OffModeSrcCfg
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

  errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_056_ADDR, 1, &OffModeSrcCfg);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetOffModeSrcVbatThresh
(
IN UINT32 voltThHi,
IN UINT32 voltThLo
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  uint8 adcThHi = 0;
  uint8 adcThLo = 0;
    
  //convert voltage to adc code
  //since we only have one byte of SDAM register, round it up and write only MSB
  adcThHi = ((voltThHi * BTMTHR_COEFF0) / (BTMTHR_COEFF1 * BTMTHR_COEFF2) + 0x80) >> 8;
  adcThLo = ((voltThLo * BTMTHR_COEFF0) / (BTMTHR_COEFF1 * BTMTHR_COEFF2) + 0x80) >> 8;

  errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_057_ADDR, 1, &adcThHi);
  errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_058_ADDR, 1, &adcThLo);

  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  
  return EFI_SUCCESS;
}
EFI_STATUS EFI_PmicSchgGetDVDDReset
(
OUT BOOLEAN* reset
)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  UINT8 data = 0;

  if(reset == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  
  *reset = FALSE;
  
  errFlag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_059_ADDR, 1, &data);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }

  if (data)
  {
    if (data == 0x80)
    {
        PMIC_DEBUG((EFI_D_WARN, "PmicDxe:: %a dvdd reset happened \r\n", __FUNCTION__));  
        *reset = TRUE;
    }
    //clear the flag
    data = 0;
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_059_ADDR, 1, &data);    
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }
  }
     
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
    
    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_16, SDAM_MEM_030_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }
    data = (data & 0xFE) | OS;
    
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_16, SDAM_MEM_030_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }
    
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetMaxPwrReq
(
IN UINT8 config,
IN UINT8 negotiatedPwr_w
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_061_ADDR, 1, &config);
    errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_066_ADDR, 1, &negotiatedPwr_w);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetMaxPwrReq_BattSts
(
IN BOOLEAN batt_missing,
IN BOOLEAN batt_dead
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    uint8 data = 0;
    
    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_061_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }

    data = (data & 0x3F ) | (batt_missing << 7) | (batt_dead << 6);
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_061_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetMaxPwrReq
(
OUT UINT8 *config,
OUT UINT8 *negotiated_pwr

)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

    if(config == NULL || negotiated_pwr == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_061_ADDR, 1, config);    
    errFlag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_066_ADDR, 1, negotiated_pwr);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}
EFI_STATUS EFI_PmicSchgSetMaxPwrReq_SkipChgReset
(
IN BOOLEAN b_skip
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    uint8 data = 0;
    
    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_061_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }

    data = (data & 0xEF ) | (b_skip << 4);
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_061_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;

}

EFI_STATUS EFI_PmicSchgSetPortEn
(
IN UINT8 PortIndex,
IN EFI_PM_SCHG_TYPEC_PORT_EN_TYPE PortEnType
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS EFI_PmicSchgEnableAICL
(
IN UINT32 PmicDeviceIndex,
IN BOOLEAN enable
)
{
    return pm_schg_usb_aicl_options_cfg(SPMI_BUSID_1, PmicDeviceIndex, PM_SCHG_USB_AICL_CFG_AICL_EN, enable);
}

EFI_STATUS EFI_PmicSchgEnableAICLPeriodicRerun
(
IN UINT32 PmicDeviceIndex,
IN BOOLEAN enable
)
{
    return pm_schg_usb_aicl_options_cfg(SPMI_BUSID_1, PmicDeviceIndex, PM_SCHG_USB_AICL_CFG_PERIODIC_RERUN_EN, enable);
}

EFI_STATUS EFI_PmicSetChargerCfg
(
UINT32 PmicDeviceIndex,
IN UINT32 fv_mv,
IN UINT32 fcc_ma
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

    errFlag = pm_schg_chgr_set_float_volt(SPMI_BUSID_1, PmicDeviceIndex, fv_mv);
    //errFlag |= pm_schg_chgr_set_charge_current(PmicDeviceIndex, PM_SCHG_CHGR_FAST_CHARGE_CURRENT, fcc_ma);
    //Note: Pass FCC directly to pre-charge/trickle current API.
    //      Expect the API will cap the setting based on HW Limit
    //errFlag |= pm_schg_chgr_set_charge_current(PmicDeviceIndex, PM_SCHG_CHGR_PRE_CHARGE_CURRENT, fcc_ma);
    //errFlag |= pm_schg_chgr_set_charge_current(PmicDeviceIndex, PM_SCHG_CHGR_TRICKLE_CHARGE_CURRENT, fcc_ma);
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }
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
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    uint16 reg_pon_sw_hard_reset_ctl = 0xA60;
    uint16 reg_pon_sw_hard_reset_go  = 0xA61;
    uint8 mask = 0x80;
    uint8 data = 0xFF;
    
    errFlag  = pm_comm_write_byte_mask_ex(SPMI_BUSID_1, PmicDeviceIndex, reg_pon_sw_hard_reset_ctl, mask, data);
    errFlag |= pm_comm_write_byte_mask_ex(SPMI_BUSID_1, PmicDeviceIndex, reg_pon_sw_hard_reset_go, mask, data);

    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetChgDxeLoadStatus
(
BOOLEAN b_done)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    uint8 data = 0;

    data = (b_done) ? 0x80 : 0;
    
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_080_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetChargerConfigEn
(
UINT32 PmicDeviceIndex,
EFI_PM_SCHG_CHG_CONFIG_EN_TYPE config,
BOOLEAN enable
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

    switch (config)
    {
    case EFI_PM_SCHG_CHG_CONFIG_EN_ITERM:
        //errFlag = pm_schg_chgr_set_iterm_en(PmicDeviceIndex, enable);
        break;
    case EFI_PM_SCHG_CHG_CONFIG_EN_VPH_OV_HW:
        //errFlag = pm_schg_chgr_set_vph_ov_hw_en(PmicDeviceIndex, enable);
        break;
    default:
        return EFI_INVALID_PARAMETER;
    }

    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetTypeCPortRole
(
UINT32 PmicDeviceIndex,
EFI_PM_SCHG_TYPEC_PORT_ROLE_TYPE RoleType
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    pm_chg_typec_port_role_type port_role = PM_CHG_TYPEC_ROLE_INVALID;

    switch (RoleType)
    {
    case EFI_PM_SCHG_TYPEC_PORT_ROLE_DRP:
      port_role = PM_CHG_TYPEC_ROLE_DRP;
      break;
    case EFI_PM_SCHG_TYPEC_PORT_ROLE_SNK:
      port_role = PM_CHG_TYPEC_ROLE_UFP;
      break;
    case EFI_PM_SCHG_TYPEC_PORT_ROLE_SRC:
      port_role = PM_CHG_TYPEC_ROLE_DFP;
      break;
    default:
        return EFI_INVALID_PARAMETER;
    }

    errFlag = pm_schg_usb_typec_set_port_role(SPMI_BUSID_1, PmicDeviceIndex, port_role);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetPortEn
(
IN UINT8 PortIndex,
IN EFI_PM_SCHG_TYPEC_PORT_EN_TYPE *PortEnType
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS EFI_PmicSchgSetRDOPDContractV
(
IN UINT32 rdo,
IN UINT16 voltage
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    
    errFlag  = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_038_ADDR, 4, (uint8*)&rdo);
    errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_062_ADDR, 2, (uint8*)&voltage);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;    
}

EFI_STATUS EFI_PmicSchgGetSavedActivePort
(
OUT EFI_PM_SCHG_SDAM_ACTIVE_PORT_INDEX* sdam_active_port_id
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    uint8 data = 0;
    boolean valid_port = FALSE;
    
    if(sdam_active_port_id == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }
    
    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_2, SDAM_MEM_037_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }

    valid_port = (data & SDAM_ACTIVE_PORT_VALID_MASK) ? TRUE : FALSE;

    if(valid_port)
    {
        *sdam_active_port_id = ((data & 0xF0) >> 4) & EFI_PM_SCHG_SDAM_PORT_MAX;
        if (*sdam_active_port_id >= MAX_CHARGING_PORT)
        {
            return EFI_DEVICE_ERROR;
        }        
    }
    else
    {
        *sdam_active_port_id = EFI_PM_SCHG_SDAM_PORT_NONE;
    }    
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetGoodBattSOC
(
IN UINT8 soc
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_068_ADDR, 1, &soc);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetDCINSupported
(
OUT BOOLEAN* supported
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    UINT8 reg_val = 0;
    
    if (supported == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_1, SDAM_MEM_078_ADDR, 1, &reg_val);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }
    
    // SDAM 1, MEM078, bit 1
    *supported = (reg_val & 0x2) ? TRUE : FALSE;
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetSWThermalAdjustment
(
IN UINT32   PmicDeviceIndex,
IN UINT32   adj_current_mA
)
{
    /*pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

    errFlag = pm_schg_misc_set_sw_thermal_adjustment(PmicDeviceIndex, adj_current_mA);
    
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }*/
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetLogCategoriesFromSdam(OUT UINT64* LoggingCategories)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS EFI_PMIcSchgGetChargerPmicIndex(OUT UINT8 *ChargerPmicIndex)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS EFI_PmicSchgSetChargingLimit
(
BOOLEAN b_enable,
UINT8 TargetSoc,
UINT8 DeltaSoc
)
{
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
 
    UINT8 data = 0; 

    data = (b_enable) ? (b_enable) : 0;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_051_ADDR, 1, &data);
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    data = (b_enable) ? (TargetSoc) : 0;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_053_ADDR, 1, &data);
    if (PM_ERR_FLAG_SUCCESS != errFlag)
    {
        return EFI_DEVICE_ERROR;
    }

    data = (b_enable) ? (DeltaSoc) : 0;

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, SDAM_MEM_054_ADDR, 1, &data);
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

    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_2, SDAM_MEM_038_ADDR, 1, &data);
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
    pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
    uint8 data = 0;

    if(pwr_state >= EFI_PM_SCHG_OS_INVALID)
    {
        return EFI_INVALID_PARAMETER;
    }
    
    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_16, SDAM_MEM_030_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }
    data = (data & 0xF1) | (pwr_state << 0x1); // Bit 1:3
    
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_16, SDAM_MEM_030_ADDR, 1, &data);
    if(PM_ERR_FLAG_SUCCESS != errFlag)
    {
      return EFI_DEVICE_ERROR;
    }
    
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetUefiChargingMode
(IN EFI_PM_SCHG_UEFI_STATE_TYPE charging_mode)
{
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;
  uint8 data = 0;

  if(charging_mode > EFI_PM_SCHG_OFFMODE_CXPC)
  {
      return EFI_INVALID_PARAMETER;
  }
    
  errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_2, SDAM_MEM_040_ADDR, 1, &data);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
  data = (data & 0xFC) | charging_mode; // Bit 0:1
    
  errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_2, SDAM_MEM_040_ADDR, 1, &data);
  if(PM_ERR_FLAG_SUCCESS != errFlag)
  {
    return EFI_DEVICE_ERROR;
  }
    
  return EFI_SUCCESS;

}

EFI_STATUS EFI_PmicSchgGetNumSerialBattery
(
IN UINT32  PmicDeviceIndex,
OUT UINT8* num_serial_battery
)
{
    pm_err_flag_type      errFlag = PM_ERR_FLAG_SUCCESS;
    pm_bob_bat_type       bat_type = PM_BOB_BAT_TYPE_INVALID;
    
    if (NULL == num_serial_battery)
    {
      return EFI_INVALID_PARAMETER;
    }
    
    errFlag = pm_schg_bob_get_batt_cfg(SPMI_BUSID_1, PmicDeviceIndex, &bat_type);
    if (errFlag != PM_ERR_FLAG_SUCCESS)
    {
      return EFI_DEVICE_ERROR;
    }

    switch(bat_type)
    {
    case PM_BOB_BAT_TYPE_2S:
        *num_serial_battery = 2;
    break;
    case PM_BOB_BAT_TYPE_3S:
        *num_serial_battery = 3;
    break;
    default:
        // should never reach here
    break;
    }
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetFakeBatStatus
(
IN UINT32 PmicDeviceIndex,
OUT BOOLEAN* is_fake_battery
)
{
    pm_err_flag_type      errFlag = PM_ERR_FLAG_SUCCESS;
    UINT16                battid_adc = 0;
    UINT16                fake_batid_up_th = 0;
    UINT16                fake_batid_lo_th = 0;
    
    if (NULL == is_fake_battery)
    {
        return EFI_INVALID_PARAMETER;
    }

    *is_fake_battery = FALSE;

    //read battery ID from SDAM written by PBS
    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_012_ADDR, 2, (uint8*)&battid_adc);

    //read fake battery ID range
    errFlag |= pm_schg_batif_get_fake_bat_id_th(SPMI_BUSID_1, PmicDeviceIndex, &fake_batid_up_th, &fake_batid_lo_th);

    if (errFlag != PM_ERR_FLAG_SUCCESS)
    {
        return errFlag;
    }

    //check if battery ID falls into fake ID range
    if ((battid_adc >= fake_batid_lo_th) && (battid_adc <= fake_batid_up_th))
    {
        *is_fake_battery = TRUE;
    }

    return errFlag;
}

EFI_STATUS EFI_PmicSchgGetConvertedRidFromSdam 
(
UINT32* batt_id
)
{
    if(batt_id == NULL) return EFI_INVALID_PARAMETER;
    *batt_id = 0; //ohm
    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetTadSdamInfo
(
OUT EFI_PM_SCHG_TAD_SDAM_INFO_TYPE* tad_sdaminfo
)
{
    pm_err_flag_type      errFlag = PM_ERR_FLAG_SUCCESS;
    
    if (NULL == tad_sdaminfo)
    {
        return EFI_INVALID_PARAMETER;
    }

    //Get DC info
    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_66, SDAM_MEM_010_ADDR, 4, (uint8*)&(tad_sdaminfo->DC_ALARM_EXP_TIME));
    errFlag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_66, SDAM_MEM_014_ADDR, 4, (uint8*)&(tad_sdaminfo->DC_POLICY_TIME));
    errFlag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_66, SDAM_MEM_018_ADDR, 1, &(tad_sdaminfo->DC_TIMER_INFO));
    if (errFlag != PM_ERR_FLAG_SUCCESS)
    {
        return EFI_DEVICE_ERROR;
    }
    // Get AC info
    errFlag = pm_sdam_mem_read(PMIC_A, PM_SDAM_66, SDAM_MEM_020_ADDR, 4, (uint8*)&(tad_sdaminfo->AC_ALARM_EXP_TIME));
    errFlag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_66, SDAM_MEM_024_ADDR, 4, (uint8*)&(tad_sdaminfo->AC_POLICY_TIME));
    errFlag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_66, SDAM_MEM_028_ADDR, 1, &(tad_sdaminfo->AC_TIMER_INFO));
    if (errFlag != PM_ERR_FLAG_SUCCESS)
    {
        return EFI_DEVICE_ERROR;
    }
    // Get rtc alarm state
    errFlag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_66, SDAM_MEM_029_ADDR, 1, &(tad_sdaminfo->RTC_ALARM_STATE));
    if (errFlag != PM_ERR_FLAG_SUCCESS)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgSetTadSdamInfo
(
IN EFI_PM_SCHG_TAD_SDAM_INFO_TYPE* tad_sdaminfo
)
{
    if(tad_sdaminfo == NULL) return EFI_INVALID_PARAMETER;
    pm_err_flag_type      errFlag = PM_ERR_FLAG_SUCCESS;

    //Get DC info
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_66, SDAM_MEM_010_ADDR, 4, (uint8*)&(tad_sdaminfo->DC_ALARM_EXP_TIME));
    errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_66, SDAM_MEM_014_ADDR, 4, (uint8*)&(tad_sdaminfo->DC_POLICY_TIME));
    errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_66, SDAM_MEM_018_ADDR, 1, &(tad_sdaminfo->DC_TIMER_INFO));
    if (errFlag != PM_ERR_FLAG_SUCCESS)
    {
        return EFI_DEVICE_ERROR;
    }
    // Get AC info
    errFlag = pm_sdam_mem_write(PMIC_A, PM_SDAM_66, SDAM_MEM_020_ADDR, 4, (uint8*)&(tad_sdaminfo->AC_ALARM_EXP_TIME));
    errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_66, SDAM_MEM_024_ADDR, 4, (uint8*)&(tad_sdaminfo->AC_POLICY_TIME));
    errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_66, SDAM_MEM_028_ADDR, 1, &(tad_sdaminfo->AC_TIMER_INFO));
    if (errFlag != PM_ERR_FLAG_SUCCESS)
    {
        return EFI_DEVICE_ERROR;
    }
    // Get rtc alarm state
    errFlag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_66, SDAM_MEM_029_ADDR, 1, &(tad_sdaminfo->RTC_ALARM_STATE));
    if (errFlag != PM_ERR_FLAG_SUCCESS)
    {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}

EFI_STATUS EFI_PmicSchgGetSBLNegotiatedInfo
(
OUT UINT8* info
)
{
    if (NULL == info)
    {
        return EFI_INVALID_PARAMETER;
    }

    return pm_sdam_mem_read(PMIC_A, PM_SDAM_15, SDAM_MEM_060_ADDR, 1, (uint8*)info);
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
    EFI_PmicSchgSetTestModeDischarging,
    EFI_PmicSchgGetLogCategoriesFromSdam,
    EFI_PMIcSchgGetChargerPmicIndex,
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

