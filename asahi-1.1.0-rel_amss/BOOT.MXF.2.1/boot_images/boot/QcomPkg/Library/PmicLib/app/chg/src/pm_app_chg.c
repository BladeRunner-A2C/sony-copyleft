/*! \file
*  
*  \brief  pm_app_chg.c
*  \details Implementation file for SBL charger float and also internal charger APIs.
*    
*  Copyright (c) 2021,2023, 2024 Qualcomm Technologies, Inc. All rights reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/17/20   zzx     Call Dp toggle api for CDP charger detection
01/06/20   xp      Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_app_chg.h"
#include "pm_chg.h"
#include "pm_qbg.h"
#include "pm_utils.h"
#include "pm_log_utils.h"
#include "pm_bmd.h"
#include "pm_bmd_driver.h"
#include "pm_app_rgb.h"
#include "pm_rgb_driver.h"
#include "pm_scpq_driver.h"
#include "pm_scpq_hs_driver.h"
#include "pm_schg_driver.h"
#include "pm_scpq_chgr.h"
#include "pm_scpq_hs_chgr.h"
#include "pm_scpq_chgr2.h"
#include "pm_schg_chgr.h"
#include "pm_scpq_usb.h"
#include "pm_scpq_hs_usb.h"
#include "pm_schg_usb.h"
#include "pm_scpq_batif.h"
#include "pm_scpq_hs_batif.h"
#include "pm_scpq_misc.h"
#include "pm_scpq_hs_misc.h"
#include "pm_schg_misc.h"
#include "pm_scpq_dcdc.h"
#include "pm_scpq_hs_dcdc.h"
#include "pm_schg_batif.h"
#include "pm_schg_dcdc.h"
#include "pm_scpq_typec.h"
#include "pm_scpq_hs_typec.h"
#include "pm_schg_typec.h"
#include "CoreVerify.h"
#include "pm_target_information.h"
#include "qusb_dci_common.h"
#include "busywait.h"
#include "adc.h"
#include "pm_dt_parser.h"
#include "DDIPlatformInfo.h"
#include "pm_pbs_client.h"
#include "pm_bsi.h"
#include "pm_bsi_driver.h"


#ifdef FEATURE_XBOOT
#include <Library/SetChargerLib.h>
#endif /* FEATURE_XBOOT */

/***************************************************************************
*
*                           Macros and Definitions
*
****************************************************************************/
// sample vbat/ibat and toggle LED every 500ms
#define PM_WEAK_BATTERY_CHARGING_DELAY (500 * 1000)
#define PM_WAIT_FOR_APSD_DONE_DELAY    (50 * 1000) //50 ms

#define BATTERY_UV_OC_VSYSMIN_STEP_DOWN_INTERVAL            (100 * 1000)            // 100 ms
#define VSYSMIN_RECOVER_STEP_MV                             (100)                   // 100 mv
#define BATTERY_UV_OC_I_PRE_CFG_IN_MA                       (250)                   // 250 ma
#define BATTERY_UV_OC_RECOVERY_TIME                         (50 * 1000)             // 50  ms
#define WDOG_PET_INTERVAL_MS                                (500)                   // 500 ms

#define SMB_SID                                             (0xD)
#define SMB_SUBTYPE_ADDR                                    (0x105)
#define SMB_139X_SCHG_PERPH0_BASE                           (0x2600)
#define SMB_139X_SCHG_PERPH1_BASE                           (0x2700)
#define SMB_139X_SCHG_PERPH2_BASE                           (0x2800)
#define SMB_1510_SCHG_PERPH0_BASE                           (0x3000)
#define SMB_1510_SCHG_PERPH1_BASE                           (0x3100)
#define SMB_139X_SCHG_PERPH0_CFG_SDCDC                      (SMB_139X_SCHG_PERPH0_BASE+0x7A)
#define MASK_CFG_EN_WIN_OV                                  (0x1<<5)
#define SMB_139X_SCHG_PERPH0_ENG_SDCDC_3LVL_B_LOOP_ERR_CFG  (SMB_139X_SCHG_PERPH0_BASE+0xC8)
#define MASK_ENG_X2_WIN_OV                                  (0x1<<3)
#define SMB_139X_SCHG_PERPH0_SOVP_CFG0                      (SMB_139X_SCHG_PERPH0_BASE+0x80)
#define MASK_CFG_EN_UV_RISE_DEB                             (0x1<<3)
#define SMB_1510_SCHG_PERPH0_CFG_SDCDC                      (SMB_1510_SCHG_PERPH0_BASE+0x7A)
#define MASK_1510_CFG_EN_WIN_OV                             (0x1<<5)
#define SMB_1510_SCHG_PERPH0_ENG_SDCDC_3LVL_B_LOOP_ERR_CFG  (SMB_1510_SCHG_PERPH0_BASE+0xC8)
#define MASK_1510_ENG_X2_WIN_OV                             (0x1<<3)
#define SMB_1510_SCHG_PERPH0_SOVP_CFG0                      (SMB_1510_SCHG_PERPH0_BASE+0x80)
#define MASK_1510_CFG_EN_UV_RISE_DEB                        (0x1<<3)
#define SMB_1510_SCHG_PERPH0_LOCK_SPARE                     (SMB_1510_SCHG_PERPH0_BASE+0x9E)
#define MASK_1510_CFG_EN_VBAT2_PD                           (0x1<<5)
#define SMB_1510_SCHG_PERPH1_ENG_SSUPPLY1                   (SMB_1510_SCHG_PERPH1_BASE+0xC1)
#define MASK_1510_CFG_VBAT2_UVLO                            (0x03<<3)

#define SMB_COTA                                            (0x39)
#define SMB_SILVERSTONE                                     (0x54)
#define MEM_011                                             (11)
#define MEM_014                                             (14)
#define CMD_WRITE                                           (0x20)
#define CMD_READ                                            (0x10)
#define MAX_WAIT_COUNT                                      (5)
#define SPMI_BRIDGE_DELAY                                   (30)
#define COMPLETE_STATUS_MASK                                (0x40)
#define SDAM_STATUS_IN_PROCESS                              (0x00)
#define SDAM_STATUS_COMPLETED                               (0x40)
#define PID(reg)                                            ((pm_register_data_type)(((reg) & 0xFF00) >> 8))
#define OFFSET(reg)                                         ((pm_register_data_type)((reg) & 0x00FF))
#define VBAT2_UVLO_4_5V                                     (0x00)

#define BMD02_EN_ADDR (0x3E46)
#define BAT2_THERM_CH_CTL_ADDR (0x3042)
#define BAT2_ID_CH_CTL_ADDR (0x3044)
#define QBG_MODE_CTL1_ADDR (0x4F43)
#define CMN_ADC_GP_CH_CTL2_ADDR (0x4F75)

#define PM_THERM_PULL_UP_30K (0)
#define PM_THERM_PULL_UP_100K (1)
#define PM_THERM_PULL_UP_400K (2)

#define PM_THERM_CHANNEL_30K (0x24)
#define PM_THERM_CHANNEL_100K (0x44)
#define PM_THERM_CHANNEL_400K (0x64)

#define PM_SDP_ICL_MA (500)
#define PM_CDP_ICL_MIN_MA (1500)

#define PM_DEFAULT_ACC0_DATA (0x8000)
#define PM_ACC0_POLL_INTERVAL (5 * 1000)  // 5ms each cycle
#define PM_ACC0_POLL_TIMEOUT (500 * 1000)  // Overall 500ms polling timeout

#define QBG_SDAM_AUTH_BATT_ID_0_LSB (0x865E) //SDAM23.MEM_030   
#define QBG_SDAM_AUTH_BATT_ID_0_MSB (0x865F) //SDAM23.MEM_031

#define ADC_INPUT_BATT_THERM_OHMS "BATT_THERM_OHMS"

#define SMART_BATTERY_THRESHOLD_OHM (250 * 1000)
#define PU_RESISTOR_OFF_TIME (100) // Wait 100us for pull up resistor to finish turn off process.

#define PM_WAIT_FOR_APSD_DONE_POLL_TIMEOUT (5 * 1000)
#define PM_WAIT_FOR_APSD_DONE_INTERVAL (500)


/***************************************************************************
*
*                           Function Definitions
*
****************************************************************************/
static pm_err_flag_type pm_app_chg_apply_charger_config(void);
static pm_err_flag_type pm_app_chg_get_batt_id(pm_adc_pull_up_type pu_type, uint32 *batt_id_ohms);
static pm_err_flag_type pm_app_chg_enable_smb_protections(boolean enable);
static pm_err_flag_type pm_app_chg_get_2cell_vbat(uint32* vcell1, uint32* vcell2);
static void pm_app_chg_pet_wdog(void);
static pm_err_flag_type pm_app_chg_no_battery_boot_config(void);
static pm_err_flag_type pm_app_chg_wait_apsd_and_aicl_from_max(void);
static pm_err_flag_type pm_app_chg_is_dam_cable_connected(uint32 bus_id, uint32 charger_index, boolean* connected);
static pm_err_flag_type pm_app_chg_get_icl_final(uint32 bus_id, uint32 charger_index, uint32* icl_final);
static pm_err_flag_type pm_config_jeita();
static pm_err_flag_type pm_scpq_config_jeita(uint32 pmic_index);
static pm_err_flag_type pm_schg_config_jeita(uint32 bus_id, uint32 pmic_index);
static pm_err_flag_type pm_scpq_hs_config_jeita(uint32 bus_id, uint32 pmic_index);
static pm_err_flag_type pm_app_save_batt_id_to_sdam(uint32 batt_id_ohms);
static pm_err_flag_type pm_smb_bridge_write(uint32 sid, pm_register_address_type reg, pm_register_data_type data);
static pm_err_flag_type pm_smb_bridge_read(uint32 sid, pm_register_address_type reg, pm_register_data_type *data);
static pm_err_flag_type pm_smb_bridge_write_mask(uint32 sid, pm_register_address_type reg, pm_register_data_type mask, pm_register_data_type data);
static pm_err_flag_type pm_smb_bridge_read_mask(uint32 sid, pm_register_address_type reg, pm_register_data_type mask, pm_register_data_type *data);
static boolean pm_app_chg_dbc_timeout();
static pm_err_flag_type pm_app_bmd_src_ctl(pm_bmd_src_ctl_sel_type src_type);
static pm_err_flag_type pm_app_is_smartbattery(boolean *is_smartbattery);
static pm_err_flag_type pm_app_chg_dam_cable_config(void);
static pm_err_flag_type pm_app_chg_enable_bpd_cfg(boolean enable);

/***************************************************************************
*
*                           API Implementation
*
****************************************************************************/
pm_dt_charger_config *
pm_get_charger_dt_config(void)
{
  static pm_dt_charger_config *charger_dt_config = NULL;

  if(NULL == charger_dt_config)
  {
    charger_dt_config = (pm_dt_charger_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CHARGER);
    CORE_VERIFY_PTR(charger_dt_config);
  }

  return charger_dt_config;
}

void 
pm_app_chg_get_debug_board_id_min_max(uint32* min, uint32* max)
{
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();

  if((NULL == min) || (NULL == max))
  {
    return;
  }

  *min = charger_dt_config->min_dbg_board_id;
  *max = charger_dt_config->max_dbg_board_id;
}


static pm_err_flag_type 
pm_app_chg_get_batt_id(pm_adc_pull_up_type pu_type, uint32 *batt_id_ohms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  adc_status_type adc_status = ADC_STATUS_SUCCESS;
  adc_result_type adc_result = {0};
  const char *channel = NULL;

  if(NULL == batt_id_ohms || pu_type >= PM_BATT_ID_PU_INVALID)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  switch(pu_type)
  {
  case PM_ADC_PU_30K:
    channel = ADC_INPUT_BATT_ID_OHMS_PU_30K;
    break;
  case PM_ADC_PU_100K:
    channel = ADC_INPUT_BATT_ID_OHMS;
    break;
  case PM_ADC_PU_400K:
    channel = ADC_INPUT_BATT_ID_OHMS_PU_400K;
    break;
  default:
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  adc_status = adc_read(channel, &adc_result);
  if(adc_status != ADC_STATUS_SUCCESS)
  {
    pm_log_message("adc_read error: %d. %s %d", adc_status, __func__, __LINE__);
    return PM_ERR_FLAG_FAILURE;
  }

  *batt_id_ohms = adc_result.physical;

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_is_debug_board_present(boolean* present)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  static boolean debug_board_detected = FALSE;
  static boolean debug_board_present = FALSE;
  uint32 battery_id = 0;
  uint32 battery_id_min = 0, battery_id_max = 0;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;
  pm_bmd_src_ctl_sel_type source = PM_BMD_SRC_INVALID;
  boolean smartbattery = FALSE;
  
  if(NULL == present)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  if(!debug_board_detected)
  {
    err_flag |= pm_app_load_batt_id_from_sdam(&battery_id);
    
    if(0 == battery_id)
    {
      err_flag |= pm_bsi_pu_resistor_enable(bus_id, pmic_index, FALSE); //BSI_BSI_EN --- bit7 0 disable BSI
      pm_busy_wait(PU_RESISTOR_OFF_TIME);
      err_flag |= pm_app_chg_get_batt_id(PM_ADC_PU_100K, &battery_id);
      
      if(battery_id < SMART_BATTERY_THRESHOLD_OHM)
      {
        err_flag |= pm_app_chg_get_batt_id(PM_ADC_PU_100K, &battery_id);
      }
      
      err_flag |= pm_app_save_batt_id_to_sdam(battery_id);
    }
    
    err_flag |= pm_bmd_get_src_type(bus_id, pmic_index, &source);   
    err_flag |= pm_app_is_smartbattery(&smartbattery);
    if(smartbattery)
    {
      if(source != PM_BMD_SRC_BATT_THERM)
      {
        err_flag |= pm_bmd_src_ctl(bus_id, pmic_index, PM_BMD_SRC_BATT_THERM);
      }
    }
    else
    {
      if(source != charger_dt_config->batt_detect_src)
      {
        err_flag |= pm_bmd_src_ctl(bus_id, pmic_index, charger_dt_config->batt_detect_src);
      }
    }  

    //compared with the configured debug board ID range
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    { 
      pm_app_chg_get_debug_board_id_min_max(&battery_id_min, &battery_id_max);
      pm_log_message("Battery ID: %d Ohm", battery_id);

      debug_board_present = (battery_id >= battery_id_min) && (battery_id <= battery_id_max);
    }

    debug_board_detected = TRUE;
  }

  *present = debug_board_present;
  
  if(NULL != pm_bmd_get_data(bus_id, pmic_index))
  {
    err_flag |= pm_bmd_enable(bus_id, pmic_index, TRUE);    
    err_flag |= pm_app_chg_enable_bpd_cfg(TRUE);
  }  
	
  return err_flag;
}

pm_err_flag_type
pm_app_chg_get_batt_therm_ohms(uint32 *ohms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  adc_status_type adc_status;
  adc_result_type adc_result;

  if(NULL == ohms)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  adc_status = adc_read(ADC_INPUT_BATT_THERM_OHMS, &adc_result);
  CORE_VERIFY(adc_status == ADC_STATUS_SUCCESS);

  *ohms = adc_result.physical;

  return err_flag;
}

pm_err_flag_type
pm_app_chg_get_batt_temp_of_adc_code(pm_adc_pull_up_type type, uint32 code, int32 *celsius)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  AdcResult result = ADC_SUCCESS;
  AdcResultType tempResult = {0};
  static boolean inited = FALSE;
  static AdcResult uAdcDevInit = ADC_ERROR;
  static AdcInputPropertiesType adcInputProps;

  if(NULL == celsius)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(!inited)
  {
    /*1. Attach to ADC */
    if (uAdcDevInit != ADC_SUCCESS)
    {
      uAdcDevInit = Adc_DeviceAttach();
      if(uAdcDevInit != ADC_SUCCESS)
      {
        return err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
      }
    }

    char *channel = ADC_INPUT_BATT_THERM;
    uint32 chan_size = sizeof(ADC_INPUT_BATT_THERM);

    switch(type)
    {
    case PM_ADC_PU_30K:
      channel = ADC_INPUT_BATT_THERM_PU_30K;
      chan_size = sizeof(ADC_INPUT_BATT_THERM_PU_30K);
      break;
    case PM_ADC_PU_100K:
      channel = ADC_INPUT_BATT_THERM;
      chan_size = sizeof(ADC_INPUT_BATT_THERM);
      break;
    case PM_ADC_PU_400K:
      channel = ADC_INPUT_BATT_THERM_PU_400K;
      chan_size = sizeof(ADC_INPUT_BATT_THERM_PU_400K);
      break;
    default:
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    /* Get the channel's input properties. The channel here is batt therm */
    result = Adc_GetAdcInputProperties(channel,
                                       chan_size,
                                       &adcInputProps);
    if(result != ADC_SUCCESS)
    {
      return PM_ERR_FLAG_PERIPHERAL_ERR;
    }

    inited = TRUE;
  }

  /* Call the API to get the temp refer to the given channel value*/
  result = Adc_ProcessConversionResult( &adcInputProps, code, &tempResult);
  if(result != ADC_SUCCESS)
  {
    return PM_ERR_FLAG_PERIPHERAL_ERR;
  }

  *celsius = tempResult.nPhysical;

  return err_flag;
}

pm_err_flag_type
pm_app_chg_get_adc_code_of_battery_temp(pm_adc_pull_up_type type, int32 celsius, uint32 *code)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  AdcResult result = ADC_SUCCESS;
  AdcResultType adcResult = {0};
  static boolean inited = FALSE;
  static AdcResult uAdcDevInit = ADC_ERROR;
  static AdcInputPropertiesType adcInputProps;

  if(NULL == code)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(!inited)
  {
    /*1. Attach to ADC */
    if (uAdcDevInit != ADC_SUCCESS)
    {
      uAdcDevInit = Adc_DeviceAttach();
      if(uAdcDevInit != ADC_SUCCESS)
      {
        return err_flag = PM_ERR_FLAG_PERIPHERAL_ERR;
      }
    }

    char *channel = ADC_INPUT_BATT_THERM;
    uint32 chan_size = sizeof(ADC_INPUT_BATT_THERM);

    switch(type)
    {
    case PM_ADC_PU_30K:
      channel = ADC_INPUT_BATT_THERM_PU_30K;
      chan_size = sizeof(ADC_INPUT_BATT_THERM_PU_30K);
      break;
    case PM_ADC_PU_100K:
      channel = ADC_INPUT_BATT_THERM;
      chan_size = sizeof(ADC_INPUT_BATT_THERM);
      break;
    case PM_ADC_PU_400K:
      channel = ADC_INPUT_BATT_THERM_PU_400K;
      chan_size = sizeof(ADC_INPUT_BATT_THERM_PU_400K);
      break;
    default:
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    /* Get the channel's input properties. The channel here is batt therm */
    result = Adc_GetAdcInputProperties(channel,
                        chan_size,
                        &adcInputProps);
    if(result != ADC_SUCCESS)
    {
      return PM_ERR_FLAG_PERIPHERAL_ERR;
    }

    inited = TRUE;
  }

  /* Call the inverse API to get the code refer to the given channel value*/
  result = Adc_ProcessConversionResultInverse( &adcInputProps, celsius, &adcResult);
  if(result != ADC_SUCCESS)
  {
    return PM_ERR_FLAG_PERIPHERAL_ERR;
  }

  *code = adcResult.nCode;

  return err_flag;
}

pm_err_flag_type 
pm_app_chg_dbc_condition_check(boolean* bypass_dbc)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  boolean debug_board_present = FALSE, battery_missing = FALSE;
  uint32 therm = 0;
  boolean is_jig = FALSE;

  if(NULL == bypass_dbc)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  uint32 image_type = pm_get_img_type();

  *bypass_dbc = (PM_IMG_LOADER == image_type) ? 
                    charger_dt_config->skip_loader_dbc : charger_dt_config->skip_core_dbc;

  // To prevent device shutdown by huge power consumption when customer skip dbc,
  // wait until APSD complete and then start AICL from MAX.
  // This should be removed if APSD is complete in PON stage for low battery case.
  if((PM_IMG_LOADER == image_type) && *bypass_dbc)
  {
    err_flag |= pm_app_chg_wait_apsd_and_aicl_from_max();
  }

  err_flag |= pm_app_chg_is_debug_board_present(&debug_board_present);

  if(charger_dt_config->detect_jig_by_therm)
  {
    err_flag |= pm_app_chg_get_batt_therm_ohms(&therm);
    pm_log_message("Therm: %d Ohm", therm);

    if((therm <= charger_dt_config->max_therm) &&
        (therm >= charger_dt_config->min_therm))
    {
      is_jig = TRUE;
      err_flag |= pm_app_chg_configure_usb_icl(charger_dt_config->jig_icl_ma);
    }

    // If JIG is detected, the behavior is expected same with debug board.
    debug_board_present |= is_jig;
  }

  pm_busy_wait(300);
  
  err_flag |= pm_chg_is_battery_present(&battery_missing);

  if((PM_ERR_FLAG_SUCCESS == err_flag) && (debug_board_present || battery_missing))
  {
    if(debug_board_present)
    {
      pm_log_message("debug board connected");
      err_flag |= pm_chg_enable_usb_charging(FALSE);
      err_flag |= pm_chg_enable_wireless_charging(FALSE);
    }

    if(battery_missing)
    {
      pm_log_message("battery missing");
      err_flag |= pm_app_chg_no_battery_boot_config();
    }

    *bypass_dbc = TRUE; // Overwrite due to HW limitation
  }

  return err_flag;
}


// As a Workaround for Puhi/PM8350B reverse boost OCP issue
// This change is to limit IBAT to <4A and IOTG to <3A.
// This W/A only applicable for Puhi and use BIT[0] of SDAM16_MEM032 as flag to indicate if the w/a has been applied
pm_err_flag_type 
pm_app_chg_trim_otg_offset_and_gain(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type trim_flag_address = 0x7F60;  // Address of Tokei.SDAM16_MEM032
  pm_register_address_type otg_offset_addr = 0x2CF5;
  pm_register_address_type otg_gain_addr = 0x2CF6;
  pm_register_data_type offset_data = 0, gain_data = 0;
  const pm_register_data_type trim_flag_mask = 0x1; // BIT[0] of SDAM16_MEM032
  pm_register_data_type data = 0;
  uint32 pmic_index_charger = PMIC_INDEX_MAX;

  err_flag = pm_chg_get_primary_charger_pmic_index(&pmic_index_charger);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(NULL != pm_scpq_get_data(pmic_index_charger))
  {
    err_flag = pm_comm_read_byte(PMIC_A, trim_flag_address, &data);
    // Check if the BIT[0] of Tokei.SDAM16_MEM032 is 1.
    // 1: OTG has been trimed
    // 0: OTG trim has been reset
    if(trim_flag_mask & data)
    {
      return PM_ERR_FLAG_SUCCESS; // return as we only apply this sw W/A at 1st boot(after dvdd/xvdd reset)
    }

    /* W/A for otg offset trim */
    err_flag |= pm_comm_read_byte(pmic_index_charger, otg_offset_addr, &offset_data);
    //Adjust the offset_data
    if(offset_data <= 0x4)
    {
      offset_data = 0x24 - offset_data;
    }
    else if((0x5 <= offset_data) && (offset_data <= 0x1F))
    {
      offset_data -= 5;
    }
    else if((0x20 <= offset_data) && (offset_data <= 0x3A))
    {
      offset_data += 5;
    }
    else if((0x3B <= offset_data) && (offset_data <= 0x3F))
    {
      offset_data = 0x3F;
    }
    // Write back the offset_data
    err_flag |= pm_comm_write_byte(pmic_index_charger, otg_offset_addr, offset_data);

    /* W/A for otg gain trim */
    err_flag |= pm_comm_read_byte(pmic_index_charger, otg_gain_addr, &gain_data);
    //Adjust the gain_data
    if(gain_data <= 0x5)
    {
      gain_data = 0x26 - gain_data;
    }
    else if((0x6 <= gain_data) && (gain_data <= 0x1F))
    {
      gain_data -= 6;
    }
    else if((0x20 <= gain_data) && (gain_data <= 0x39))
    {
      gain_data += 6;
    }
    else if((0x3A <= gain_data) && (gain_data <= 0x3F))
    {
      gain_data = 0x3F;
    }
    // Write back the gain_data
    err_flag |= pm_comm_write_byte(pmic_index_charger, otg_gain_addr, gain_data);

    // Set flag to indicate dvdd/xvdd happened and we have applied this sw W/A
    err_flag |= pm_comm_write_byte_mask(PMIC_A, trim_flag_address, trim_flag_mask, trim_flag_mask);
  }

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  err_flag |= pm_app_chg_apply_charger_config();
  
  return err_flag;
}


// This function should be called if charging taking place. internal use only
static pm_err_flag_type 
pm_app_chg_output_charging_status(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean power_by_usbin = FALSE;
  pm_chg_power_path_type power_path = PM_CHG_POWER_PATH_INVALID;
  pm_chg_charger_port_type charger_port = PM_CHARGER_PORT_TYPE_INVALID;
  static boolean float_icl_configured = FALSE;
  adc_status_type adc_status = ADC_STATUS_SUCCESS;
  adc_result_type vadc_result = {0, 0, 0};
  adc_result_type iadc_result = {0, 0, 0};
  pm_scpq_chgr_status_type chgr_sts = {0};
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 charger_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;
  char* charger_type = NULL;
  char* chg_path = "USB";
  char* adc_ch = "VWLS";
  char* chg_sts_str[PM_SCPQ_BATT_CHGR_STATUS_COUNT] =
              {"INHIBIT", "TRICKLE", "PRECHG", "FULLON", "TAPER", "TERMINATION", "PAUSE", "DISABLED", "INVALID"};

  static boolean sdp_detected_first_time = TRUE;
  pm_scpq_misc_vin_div16_mux_sel_type scpq_mux_sel = PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_INVALID;
  pm_scpq_hs_misc_vin_div16_mux_sel_type scpq_hs_mux_sel = PM_SCPQ_HS_MISC_VIN_DIV16_MUX_SEL_INVALID;

  err_flag |= pm_chg_get_power_path(&power_path);

  if(power_path == PM_CHG_POWER_PATH_USBIN)
  {
    power_by_usbin = TRUE;
    if(NULL != pm_scpq_get_data(charger_index))
    {        
        scpq_mux_sel = PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_USB_IN;
    } 
    else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
    {
        scpq_hs_mux_sel = PM_SCPQ_HS_MISC_VIN_DIV16_MUX_SEL_USB_IN;   
    }        

    err_flag |= pm_chg_get_charger_port_type(&charger_port);

    switch(charger_port)
    {
    case PM_CHARGER_PORT_SDP_CHARGER:
      charger_type = "SDP";
      break;
    case PM_CHARGER_PORT_OCP_CHARGER:
      charger_type = "OCP";
      break;
    case PM_CHARGER_PORT_CDP_CHARGER:
      charger_type = "CDP";
      break;
    case PM_CHARGER_PORT_DCP_CHARGER:
      charger_type = "DCP";
      break;
    case PM_CHARGER_PORT_FLOAT_CHARGER:
      charger_type = "Float";
      if(charger_dt_config->apply_float_charger_icl && !float_icl_configured)
      {
        err_flag |= pm_app_chg_configure_usb_icl(charger_dt_config->float_charger_icl_ma);
        float_icl_configured = TRUE;
      }
      break;
    case PM_CHARGER_PORT_QC_2P0_CHARGER:
      charger_type = "QC2";
      break;
    case PM_CHARGER_PORT_QC_3P0_CHARGER:
      charger_type = "QC3";
      break;
    default:
      charger_type = "Unknown";
      break;
    }
	if(((charger_port == PM_CHARGER_PORT_SDP_CHARGER) || (charger_port == PM_CHARGER_PORT_CDP_CHARGER)) && sdp_detected_first_time)
    {
      sdp_detected_first_time = FALSE;
      if(NULL != pm_scpq_get_data(charger_index))
      {
        err_flag |= pm_scpq_typec_set_dam_icl(charger_index, PM_TYPEC_DAM_ICL_FMB);
      }
      else if(NULL != pm_scpq_hs_get_data(bus_id, charger_index))
      {
        /* Will be enabled later*/
        err_flag |= pm_scpq_hs_typec_set_dam_icl(bus_id, charger_index, PM_SCPQ_HS_TYPEC_DAM_ICL_FMB);
      }        
      else if(NULL != pm_schg_get_data(bus_id, charger_index))
      {
        err_flag |= pm_schg_typec_set_dam_icl(bus_id, charger_index, PM_SCHG_USB_TYPEC_DAM_ICL_FMB);
      }
    }
  }
  else if(power_path == PM_CHG_POWER_PATH_WIRELESS)
  {
    chg_path = "WLS";
    scpq_mux_sel = PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_WLS_IN;
  }
  else
  {
    return err_flag;
  }

  if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_chgr_get_chgr_status(charger_index, &chgr_sts);
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
  {
    err_flag |= pm_scpq_hs_chgr_get_chgr_status(bus_id, charger_index, (pm_scpq_hs_chgr_status_type*)&chgr_sts);
  }        
  else if(NULL != pm_schg_get_data(bus_id, charger_index))
  {
    err_flag |= pm_schg_chgr_get_chgr_status(bus_id, charger_index, (pm_schg_chgr_status_type*)&chgr_sts);
  }

  /*Configuring the mux for USB/WLS voltage reading. Applicable for scpq only*/
  if(NULL != pm_scpq_get_data(charger_index))
  {
    pm_scpq_misc_set_vin_adc_mux_sel(charger_index, scpq_mux_sel);
    pm_busy_wait(10);
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
  {
    pm_scpq_hs_misc_set_vin_adc_mux_sel(bus_id, charger_index, scpq_hs_mux_sel);
    pm_busy_wait(10); 
  }        
  
  adc_status = adc_read(adc_ch, &vadc_result);
  if(adc_status != ADC_STATUS_SUCCESS)
  {
    pm_log_message("adc_read error: %d. %s %d", adc_status, __func__, __LINE__);
    return PM_ERR_FLAG_FAILURE;
  }

  // WLS_IN_I is the same ADC channel as USB_IN_I
  adc_status = adc_read(ADC_INPUT_USB_IN_I, &iadc_result);
  if(adc_status != ADC_STATUS_SUCCESS)
  {
    pm_log_message("ADC %s sts:%d", ADC_INPUT_USB_IN_I, adc_status, __func__, __LINE__);
    return PM_ERR_FLAG_FAILURE;
  }

  pm_log_message("Charger:%s V%s:%dmV I%s:%dmA CHG_STS:%s",
                  power_by_usbin ? charger_type : "Wireless",
                  chg_path,
                  vadc_result.physical,
                  chg_path,
                  iadc_result.physical,
                  chg_sts_str[chgr_sts.charger_status.battery_charger_status]);

  return err_flag;
}


static pm_err_flag_type
pm_app_chg_enable_bpd_cfg(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;

  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_batif_cfg_batt_missing_src(pmic_index, PM_SCPQ_BAT_MISS_SRC_CFG_PIN_SRC_EN, enable);
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
  {
     err_flag = pm_scpq_hs_batif_cfg_batt_missing_src(bus_id, pmic_index, PM_SCPQ_HS_BAT_MISS_SRC_CFG_PIN_SRC_EN, enable);  
  }        
  else if(NULL != pm_schg_get_data(bus_id, pmic_index))
  {
    err_flag = pm_schg_batif_cfg_batt_missing_src(bus_id, pmic_index, PM_SCHG_BAT_MISS_SRC_CFG__PIN_SRC_EN, enable);
  }

  return err_flag;
}


static pm_err_flag_type 
pm_app_chg_apply_charger_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;

  if((NULL != pm_scpq_get_data(pmic_index)) || (NULL != pm_scpq_hs_get_data(bus_id, pmic_index)))
  {
    uint8 channel_id = PM_THERM_CHANNEL_100K; // default 100K
    uint8 channel_id_from_register = PM_THERM_CHANNEL_100K; 
    uint8 pull_up = 0x2;  // default 100K, 0 - open, 0x1 - 30k pull-up, 0x2 - 100k pull-up, 0x3 - 400k pull-up
    uint8 default_pu = PM_THERM_PULL_UP_100K;

    if(NULL != pm_scpq_get_data(pmic_index))
    {       
      err_flag |= pm_scpq_misc_get_batt_therm_ch_id_cfg(pmic_index, &channel_id_from_register);
    } 
    else if(NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
    {
      err_flag |= pm_scpq_hs_misc_get_batt_therm_ch_id_cfg(bus_id, pmic_index, &channel_id_from_register);
    }        
   
    if(channel_id_from_register == PM_THERM_CHANNEL_100K)
    {
      default_pu = PM_THERM_PULL_UP_100K;
    }
    else if(channel_id_from_register == PM_THERM_CHANNEL_30K)
    {
      default_pu = PM_THERM_PULL_UP_30K;
    }
    else if(channel_id_from_register == PM_THERM_CHANNEL_400K)
    {
      default_pu = PM_THERM_PULL_UP_400K;
    }
    
    if((err_flag == PM_ERR_FLAG_SUCCESS) && (default_pu != charger_dt_config->batt_therm_pull_up))
    {
      if(charger_dt_config->batt_therm_pull_up == PM_THERM_PULL_UP_30K)
      {
        channel_id = PM_THERM_CHANNEL_30K;
        pull_up = 0x1;
      }
      else if(charger_dt_config->batt_therm_pull_up == PM_THERM_PULL_UP_400K)
      {
        channel_id = PM_THERM_CHANNEL_400K;
        pull_up = 0x3;
      }
      
      if(NULL != pm_scpq_get_data(pmic_index))
      {     
        err_flag |= pm_scpq_misc_batt_therm_ch_enable(pmic_index, FALSE);
      }    
      else if(NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
      {    
        err_flag |= pm_scpq_hs_misc_batt_therm_ch_enable(bus_id, pmic_index, FALSE);       
      }

      err_flag |= pm_busy_wait(100 * 1000);
      // We have no plan to write drive for periph ADC_CMN_BG. 
      // So we use pm_comm_write_byte to write value direct into this register.
      err_flag |= pm_comm_write_byte(pmic_index, 0x3061, pull_up);
        
      if(NULL != pm_scpq_get_data(pmic_index))
      {     
        err_flag |= pm_scpq_misc_set_batt_therm_ch_id_cfg(pmic_index, channel_id);
        err_flag |= pm_scpq_misc_batt_therm_ch_enable(pmic_index, TRUE);
      }    
      else if(NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
      {    
        err_flag |= pm_scpq_hs_misc_set_batt_therm_ch_id_cfg(bus_id, pmic_index, channel_id);
        err_flag |= pm_scpq_hs_misc_batt_therm_ch_enable(bus_id, pmic_index, TRUE);
      }
     }     

    // configure QBG mode_ctl2 for ichg_fs_option
    if(charger_dt_config->apply_ichg_fs)
    {
      err_flag |= pm_qbg_set_qbg_mode_ctl2_ichg_fs_opt(pmic_index, (charger_dt_config->ichg_fs == PM_CHG_FS_24A) ? TRUE : FALSE);
    }

    uint8 batt2_data = 0;
    pm_chg_2nd_batt_cfg* chg_app_config = pm_target_information_get_specific_info(PM_PROP_CHG_APP_CONFIG);  
    if(charger_dt_config->enable_1s2p_id2)
    {
      err_flag |= pm_comm_write_byte(pmic_index, BMD02_EN_ADDR, 0x80); // Enable BMD02 peripheral
      err_flag |= pm_comm_write_byte(pmic_index, BAT2_ID_CH_CTL_ADDR, 0x0D); // CH = 0x0D for ID2

      if(NULL != chg_app_config)
      {
        err_flag |= pm_gpio_enable(pmic_index, chg_app_config->gpio_id, FALSE); // Disable PMIC GPIO12
      }

      err_flag |= pm_comm_write_byte(pmic_index, QBG_MODE_CTL1_ADDR, 0x80); // Configure to 2P battery type.
      batt2_data |= 1 << 0; // BIT[0] for 1S2P ID2 enable
    }
    else
    {
      err_flag |= pm_comm_write_byte(pmic_index, BMD02_EN_ADDR, 0); // Disable BMD02
    }

    if(charger_dt_config->enable_1s2p_therm2)
    {
      err_flag |= pm_comm_write_byte(pmic_index, BAT2_THERM_CH_CTL_ADDR, 0x0C); // CH = 0x0C for Therm2
      err_flag |= pm_comm_write_byte(pmic_index, CMN_ADC_GP_CH_CTL2_ADDR, 0xE6);

      if(NULL != chg_app_config)
      {
        err_flag |= pm_gpio_enable(pmic_index, chg_app_config->gpio_therm, FALSE); // Disable PMIC GPIO6
      }

      batt2_data |= 1 << 1; // BIT[1] for 1S2P therm2 enable
    }

    if(charger_dt_config->enable_1s2p_id2 || charger_dt_config->enable_1s2p_therm2)
    {
      // SDAM23.MEM126: [0] ID2, [1] Therm2
      err_flag |= pm_sdam_mem_write(0, PM_SDAM_23, 126, 1, &batt2_data);
    }

    if(charger_dt_config->ignore_temp_in_dbc)
    {
      if(NULL != pm_scpq_get_data(pmic_index))
      {     
        err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_AFP_COLD, FALSE);
        err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_AFP_HOT, FALSE);
        err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_HARD_LIMIT, FALSE);
      }    
      else if(NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
      {    
        err_flag |= pm_scpq_hs_batif_jeita_en_cfg(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_AFP_COLD, FALSE);
        err_flag |= pm_scpq_hs_batif_jeita_en_cfg(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_AFP_HOT, FALSE);
        err_flag |= pm_scpq_hs_batif_jeita_en_cfg(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_HARD_LIMIT, FALSE);
      }
    }
    else if(pm_get_img_type() == PM_IMG_LOADER)
    {
      err_flag |= pm_config_jeita();
    }
  }

  // configure float voltage threshold
  if(charger_dt_config->apply_float_voltage)
  {
    if(NULL != pm_schg_get_data(bus_id, pmic_index))
    {
      err_flag |= pm_schg_chgr_set_float_volt(bus_id, pmic_index, charger_dt_config->float_voltage_mv);
    }
    else
    {
      if(NULL != pm_scpq_get_data(pmic_index))
      {     
        err_flag |= pm_scpq_chgr_set_float_volt(pmic_index, charger_dt_config->float_voltage_mv);
      }    
      else if(NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
      {    
        err_flag |= pm_scpq_hs_chgr_set_float_volt(bus_id, pmic_index, charger_dt_config->float_voltage_mv);
      }
    }
  }

  if(charger_dt_config->apply_vsysmin)
  {
    if(NULL != pm_schg_get_data(bus_id, pmic_index))
    {
      err_flag |= pm_schg_dcdc_configure_vsysmin(bus_id, pmic_index, charger_dt_config->vsysmin);
    }
    else
    {
      if (NULL != pm_scpq_get_data(pmic_index))
      {     
        err_flag |= pm_scpq_chgr_configure_vsysmin(pmic_index, charger_dt_config->vsysmin);
      }    
      else if (NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
      {    
        err_flag |= pm_scpq_hs_chgr_configure_vsysmin(bus_id, pmic_index, charger_dt_config->vsysmin);
      }
    }
  }

  // configure pre_charging current limit
  if(charger_dt_config->apply_pre_charge_current)
  {
    if(NULL != pm_schg_get_data(bus_id, pmic_index))
    {
      err_flag |= pm_schg_chgr_set_charge_current(bus_id, pmic_index, PM_SCHG_CHGR_PRE_CHARGE_CURRENT, charger_dt_config->pre_charge_ma);
    }
    else
    {
      if(NULL != pm_scpq_get_data(pmic_index))
      {     
        err_flag |= pm_scpq_chgr_set_charge_current(pmic_index, PM_SCPQ_CHGR_PRE_CHARGE_CURRENT, charger_dt_config->pre_charge_ma);
      }    
      else if(NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
      {    
        err_flag |= pm_scpq_hs_chgr_set_charge_current(bus_id, pmic_index, PM_SCPQ_HS_CHGR_PRE_CHARGE_CURRENT, charger_dt_config->pre_charge_ma);
      }
    }
  }

  // configure fast charging current limit
  if(charger_dt_config->apply_fast_charge_current)
  {
    if(NULL != pm_schg_get_data(bus_id, pmic_index))
    {
      err_flag |= pm_schg_chgr_set_charge_current(bus_id, pmic_index, PM_SCHG_CHGR_FAST_CHARGE_CURRENT, charger_dt_config->fast_charge_ma);
    }
    else
    {
      if(NULL != pm_scpq_get_data(pmic_index))
      {     
        err_flag |= pm_scpq_chgr_set_charge_current(pmic_index, PM_SCPQ_CHGR_FAST_CHARGE_CURRENT, charger_dt_config->fast_charge_ma);
      }    
      else if(NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
      {    
        err_flag |= pm_scpq_hs_chgr_set_charge_current(bus_id, pmic_index, PM_SCPQ_HS_CHGR_FAST_CHARGE_CURRENT, charger_dt_config->fast_charge_ma);
      }
    }
  }

  // configure usbin input current limit
  if(charger_dt_config->apply_icl)
  {
    err_flag |= pm_app_chg_configure_usb_icl(charger_dt_config->icl_ma);
  }

  if(charger_dt_config->usb_suspend)
  {
    if(NULL != pm_schg_get_data(bus_id, pmic_index))
    {
      err_flag |= pm_schg_usb_set_usbin_suspend(bus_id, pmic_index, TRUE);
    }
    else
    {
      if (NULL != pm_scpq_get_data(pmic_index))
      {     
             err_flag |= pm_scpq_usb_set_usbin_suspend(pmic_index, PM_SCPQ_USB_USBIN_SUSPEND, TRUE);
      }    
      else if (NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
      {    
             err_flag |= pm_scpq_hs_usb_set_usbin_suspend(bus_id, pmic_index, PM_SCPQ_HS_USB_USBIN_SUSPEND, TRUE);
      }
    }
  }

  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag |= pm_scpq_usb_set_input_priority(pmic_index,
                  (pm_scpq_usb_input_priority_type)charger_dt_config->wls_usb_prior_swap);
  }

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_check_weak_battery_status(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_chg_charger_port_type charger_type = PM_CHARGER_PORT_TYPE_INVALID;
  uint32 battery_voltage = 0;
  int32 battery_current = 0;
#ifndef FEATURE_XBOOT
  uint32 cell_threshold = 0;
#endif /* !FEATURE_XBOOT */
  boolean charging_ongoing = FALSE;
  boolean light_on = FALSE;
  static boolean first_loop = TRUE;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 bus_id = charger_dt_config->charger_bus_index;
#ifndef FEATURE_XBOOT
  boolean battery_is_2s = FALSE;
#endif /* !FEATURE_XBOOT */
  uint32 pmic_index_charger = charger_dt_config->charger_pmic_index;
  
  err_flag |= pm_chg_get_charger_port_type(&charger_type);
  
#ifndef FEATURE_XBOOT
  if(charger_type == PM_CHARGER_PORT_SDP_CHARGER)
  {
    cell_threshold = (PM_IMG_LOADER == pm_get_img_type()) ? 
                      charger_dt_config->loader_dbc_threshold + charger_dt_config->dbc_sdp_thd_inc : charger_dt_config->core_dbc_threshold;
  }
  else
  {
    cell_threshold = (PM_IMG_LOADER == pm_get_img_type()) ? 
                      charger_dt_config->loader_dbc_threshold : charger_dt_config->core_dbc_threshold;
  }

  err_flag |= pm_chg_is_2s_batt(&battery_is_2s);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(battery_is_2s)
  {
    cell_threshold *= 2;
  }
#endif /* !FEATURE_XBOOT */

  while(!pm_app_chg_dbc_timeout())
  {
    err_flag = pm_chg_get_vbatt(&battery_voltage);
    err_flag |= pm_chg_get_ibatt(&battery_current);

    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      return err_flag;
    }

    pm_log_message("VBAT: %dmV IBAT: %dmA", battery_voltage, battery_current);

#ifndef FEATURE_XBOOT
    if(battery_voltage > cell_threshold)
    {
      break; // continue booting up since the voltage has crossed the threshold
    }
#endif /* !FEATURE_XBOOT */

    if(TRUE == first_loop)
    {   
      err_flag |= pm_app_chg_dam_cable_config();
    }
    
    err_flag = pm_chg_is_charging_ongoing(&charging_ongoing);
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      return err_flag;
    }

    // Since USB charging is by default disabled in some charger PMIC,
    // we need some delay to double check if charging is really not happen.
    if(TRUE == first_loop)
    {
      first_loop = FALSE;

      if(NULL != pm_scpq_get_data(pmic_index_charger))
      {
        //Configure VPH_TRACK_SEL = 7% once if sw go to SBL charging loop (VBAT <= 3.3V)
        //This is to guarantee that the pre-charger has sufficient headroom. 
        err_flag |= pm_scpq_chgr_vph_track_threshold_sel(pmic_index_charger, PM_SCPQ_VPH_TRACK_SEL_7_PCT);
      }
      else if (NULL != pm_scpq_hs_get_data(bus_id, pmic_index_charger))
      {
        //Configure VPH_TRACK_SEL = 7% once if sw go to SBL charging loop (VBAT <= 3.3V)
        //This is to guarantee that the pre-charger has sufficient headroom. 
        err_flag |= pm_scpq_hs_chgr_vph_track_threshold_sel(bus_id, pmic_index_charger, PM_SCPQ_HS_VPH_TRACK_SEL_7_PCT); 
      }        

      if(FALSE == charging_ongoing)
      {
        err_flag |= pm_busy_wait(PM_WEAK_BATTERY_CHARGING_DELAY);
        continue;
      }
    }

    if(FALSE == charging_ongoing)
    {
#ifdef FEATURE_XBOOT
      if (battery_voltage > charger_dt_config->core_dbc_threshold)
      {
         break; // continue booting up since the voltage has crossed the threshold
      }
      pm_log_message("Not charging. Shutdown");
#endif /* FEATURE_XBOOT */
      pm_log_message("charger is not charging and device will shut down");
      err_flag |= pm_busy_wait(100 * 1000);
      // Not charging and vbat lower than dead battery charging, shutdown 
      err_flag |= pm_device_shutdown();
    }
    else
    {
#ifdef FEATURE_XBOOT
      err_flag |= pm_app_chg_configure_usb_icl_somc();
#endif /* FEATURE_XBOOT */
      // In charging, output charger information. Is it charged by USB or wireless
      // For USB charger, which charger type is connected.
      err_flag |= pm_app_chg_output_charging_status();
      // Delay a certain duration and toggle LED
      err_flag |= pm_busy_wait(PM_WEAK_BATTERY_CHARGING_DELAY);
      err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, light_on);
      light_on = !light_on;

      if(PM_ERR_FLAG_SUCCESS != err_flag)
      {
        return err_flag;
      }
      pm_app_chg_pet_wdog();
#ifdef FEATURE_XBOOT
      pm_log_message("Primary Charging loop exit");
      break;
#endif /* FEATURE_XBOOT */
    }
  }

  // Turn off LED after exiting charging
  err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, FALSE);

#ifdef FEATURE_XBOOT
   err_flag |= pm_sbl_config_chg_parameters_somc(pmic_index_charger);
   err_flag |= pm_schg_usb_set_usbin_adptr_allowance_somc(pmic_index_charger);
#endif /* FEATURE_XBOOT */

  return err_flag;
}


static pm_err_flag_type 
pm_app_chg_is_dam_cable_connected(uint32 bus_id, uint32 charger_index, boolean* connected)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if((NULL == connected) || (charger_index > PMIC_INDEX_MAX))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(NULL != pm_schg_get_data(bus_id, charger_index))
  {
    err_flag |= pm_schg_typec_get_dam_connect_sts(bus_id, charger_index, connected);
  }
  else if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_typec_get_dam_connect_sts(charger_index, connected);
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
  {
    err_flag |= pm_scpq_hs_typec_get_dam_connect_sts(bus_id, charger_index, connected); 
  }      
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


static pm_err_flag_type 
pm_app_chg_get_icl_final(uint32 bus_id, uint32 charger_index, uint32* icl_final)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_schg_dcdc_icl_status_type icl_schg = {0};
  pm_scpq_dcdc_icl_status_type icl_scpq = {0};
  pm_scpq_hs_dcdc_icl_status_type icl_scpq_hs = {0};

  if((NULL == icl_final) || (charger_index > PMIC_INDEX_MAX))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  if(NULL != pm_schg_get_data(bus_id, charger_index))
  {
    err_flag |= pm_schg_dcdc_get_icl_status(bus_id, charger_index, &icl_schg);
    *icl_final = icl_schg.final_icl_status;
  }
  else if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_dcdc_get_icl_status(charger_index, &icl_scpq);
    *icl_final = icl_scpq.icl_final_status;
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
  {
    err_flag |= pm_scpq_hs_dcdc_get_icl_status(bus_id, charger_index, &icl_scpq_hs);
    *icl_final = icl_scpq_hs.icl_final_status; 
  }        
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


/*
 * Config ICL except :
 *     1. Charger type is SDP
 *     2. DAM cable connected without battery
 */
pm_err_flag_type 
pm_app_chg_configure_usb_icl(uint32 icl_ma)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_chg_charger_port_type charger_type = PM_CHARGER_PORT_TYPE_INVALID;
  uint32 final_icl = 0;
  boolean is_dam_cable = FALSE;
  boolean battery_missing   = FALSE;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 charger_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;
  
  do
  {
	err_flag |= pm_chg_get_charger_port_type(&charger_type);
    err_flag |= pm_app_chg_is_dam_cable_connected(bus_id, charger_index, &is_dam_cable);
    err_flag |= pm_chg_is_battery_present(&battery_missing);
    if((err_flag != PM_ERR_FLAG_SUCCESS) || ((PM_CHARGER_PORT_SDP_CHARGER == charger_type) && (FALSE == is_dam_cable))
        || ((TRUE == is_dam_cable) && (TRUE == battery_missing)))
    {
	  break;
    }
    if(PM_CHARGER_PORT_SDP_CHARGER == charger_type)
    {
      // for SDP and DAM concurrency, we need to override as 500ma instead of USB500 mode.
      icl_ma = PM_SDP_ICL_MA;
    }
    else if(PM_CHARGER_PORT_CDP_CHARGER == charger_type)
    {
      icl_ma = PM_CDP_ICL_MIN_MA;
    }
	
    // Check and use the available charger driver
    if(NULL != pm_schg_get_data(bus_id, charger_index))
    {
      //Set USBIN_MODE_CHG to USB_HIGH_CURRENT_MODE
      err_flag |= pm_schg_usb_configure_usbin_icl_options(bus_id, charger_index, PM_SCHG_USB_ICL_OPTIONS_USBIN_MODE_CHG, TRUE);
      //Set ICL_OVERRIDE_AFTER_APSD
      err_flag |= pm_schg_usb_enable_icl_override_after_apsd(bus_id, charger_index, TRUE);
      //Set ICL config
      err_flag |= pm_schg_usb_set_usbin_current_limit_cfg(bus_id, charger_index, icl_ma);
      //Disable AICL to update ICL status
      err_flag |= pm_schg_usb_aicl_options_cfg(bus_id, charger_index, PM_SCHG_USB_AICL_CFG_AICL_EN, FALSE);
      //Delay 10ms
      pm_busy_wait(10 * 1000);
      //Enable AICL
      err_flag |= pm_schg_usb_aicl_options_cfg(bus_id, charger_index, PM_SCHG_USB_AICL_CFG_AICL_EN, TRUE);
    }
    else if(NULL != pm_scpq_get_data(charger_index))
    {
#ifdef FEATURE_XBOOT
      //Set USB51_MODE to 500mA mode
      err_flag |= pm_scpq_usb_configure_usb_icl_options(charger_index, PM_SCPQ_USB_ICL_OPTIONS_USB51_MODE, TRUE);
#endif /* FEATURE_XBOOT */
      //Set USBIN_MODE_CHG to USB_HIGH_CURRENT_MODE
      err_flag |= pm_scpq_usb_configure_usb_icl_options(charger_index, PM_SCPQ_USB_ICL_OPTIONS_USBIN_MODE_CHG, TRUE);
      //Set ICL_OVERRIDE_AFTER_APSD
      err_flag |= pm_scpq_usb_enable_icl_override_after_apsd(charger_index, TRUE);
      //Set ICL config
      err_flag |= pm_scpq_usb_set_icl_cfg(charger_index, icl_ma);
      //Disable AICL, then SCPQ_P_DCDC_ICL_STATUS | 0x2709 could be changed to icl_ma
      err_flag |= pm_scpq_usb_aicl_options_cfg(charger_index, PM_SCPQ_USB_AICL_EN, FALSE, USBIN_COLLAPSE_GF_5MS, USBIN_AICL_STEP_10MS);
      //Delay 10ms
      pm_busy_wait(10 * 1000);
      //Enable AICL
      err_flag |= pm_scpq_usb_aicl_options_cfg(charger_index, PM_SCPQ_USB_AICL_EN, TRUE, USBIN_COLLAPSE_GF_5MS, USBIN_AICL_STEP_10MS);
    }
    else if(NULL != pm_scpq_hs_get_data(bus_id, charger_index))
    {
      //Set USBIN_MODE_CHG to USB_HIGH_CURRENT_MODE
      err_flag |= pm_scpq_hs_usb_configure_usb_icl_options(bus_id, charger_index, PM_SCPQ_HS_USB_ICL_OPTIONS_USBIN_MODE_CHG, TRUE);
      //Set ICL_OVERRIDE_AFTER_APSD
      err_flag |= pm_scpq_hs_usb_enable_icl_override_after_apsd(bus_id, charger_index, TRUE);
      //Set ICL config
      err_flag |= pm_scpq_hs_usb_set_icl_cfg(bus_id, charger_index, icl_ma);
      //Disable AICL, then SCPQ_HS_DCDC_ICL_STATUS | 0x2709 could be changed to icl_ma
      err_flag |= pm_scpq_hs_usb_aicl_options_cfg(bus_id, charger_index, PM_SCPQ_HS_USB_AICL_EN, FALSE);
      //Delay 10ms
      pm_busy_wait(10 * 1000);
      //Enable AICL
      err_flag |= pm_scpq_hs_usb_aicl_options_cfg(bus_id, charger_index, PM_SCPQ_HS_USB_AICL_EN, TRUE);
    }
    else
    {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  } while (FALSE);

  err_flag |= pm_app_chg_get_icl_final(bus_id, charger_index, &final_icl);
  pm_log_message("%sICL final: %dmA", is_dam_cable ? "DAM Cable, " : "", final_icl);

  return err_flag;
}


/* Get the two cell vbat for 2S battery */
static pm_err_flag_type 
pm_app_chg_get_2cell_vbat(uint32* vcell1, uint32* vcell2)
{
  pm_err_flag_type err_flag  = PM_ERR_FLAG_SUCCESS;
  adc_status_type adc_status = ADC_STATUS_SUCCESS;
  adc_result_type adc_vbat = {0}, adc_vbat_mid = {0};
  boolean battery_is_2s = FALSE;

  if((NULL == vcell1) || (NULL == vcell2))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag = pm_chg_is_2s_batt(&battery_is_2s);    
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if(battery_is_2s)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  // Get 2s battery S+ volt, sum of two cells voltage
  adc_status |= adc_read(ADC_INPUT_VBATT_2S, &adc_vbat);
  // Get 2s battery mid volt, one cell voltage
  adc_status |= adc_read(ADC_INPUT_VBATT_2S_MID, &adc_vbat_mid);

  if(adc_status != ADC_STATUS_SUCCESS)
  {
    pm_log_message("adc_read error: %d. %s %d", adc_status, __func__, __LINE__);
    return PM_ERR_FLAG_FAILURE;
  }

  *vcell2 = adc_vbat_mid.microvolts / 1000;
  *vcell1 = adc_vbat.microvolts / 1000 - *vcell2;

  return err_flag;
}


pm_err_flag_type 
pm_app_chg_battery_uv_oc_detection()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 vcell              = 0;
  boolean recovered         = TRUE;
  boolean charging          = FALSE;
  boolean light_on          = TRUE;
  uint32 v_sys_min_backup = 3000; // default vsys_min is 3000mv.
  int32 v_sys_min_step = 0;
  uint32 v_float_backup = 0;
  uint32 i_pre_chg_backup = 0;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 charger_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;
  boolean battery_is_2s = FALSE;

  err_flag = pm_chg_is_2s_batt(&battery_is_2s);    
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  
  uint32 vcell_thld = battery_is_2s ? charger_dt_config->uv_oc_2s_threshold : charger_dt_config->uv_oc_1s_threshold;

  if(NULL != pm_scpq_get_data(charger_index))
  {
    //Configure VPH_TRACK_SEL = 7% once if sw go to SBL charging loop (VBAT <= 3.3V)
    //This is to guarantee that the pre-charger has sufficient headroom. 
    err_flag |= pm_scpq_chgr_vph_track_threshold_sel(charger_index, PM_SCPQ_VPH_TRACK_SEL_7_PCT);
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
  {
    //Configure VPH_TRACK_SEL = 7% once if sw go to SBL charging loop (VBAT <= 3.3V)
    //This is to guarantee that the pre-charger has sufficient headroom.
    err_flag |= pm_scpq_hs_chgr_vph_track_threshold_sel(bus_id, charger_index, PM_SCPQ_HS_VPH_TRACK_SEL_7_PCT);
    err_flag |= pm_scpq_hs_chgr_vph_prechg_alg_en(bus_id, charger_index, TRUE); 
  }        

  err_flag |= pm_chg_get_vbatt(&vcell);
  if(vcell < vcell_thld)
  {
    if (NULL != pm_scpq_get_data(charger_index))
    {        
       //Get current V_sys_min, V_float, I_pre_chg settings, restore them after battery recovered
       err_flag |= pm_scpq_chgr_get_vsysmin_cfg(charger_index, &v_sys_min_backup);
       err_flag |= pm_scpq_chgr_get_float_volt_cfg(charger_index, &v_float_backup);
       err_flag |= pm_scpq_chgr_get_charge_current_cfg(charger_index, PM_SCPQ_CHGR_PRE_CHARGE_CURRENT, &i_pre_chg_backup);

       //Set V_sys_min = 4.6v, V_float = 4.5v(1S) / 9.0v(2S), IPRE_CFG = 250mA(1S) / 125mA(2S) 
       //This is to ensure battery can only charge in pre/trickle state with low charging current at the beginning
       err_flag |= pm_scpq_chgr_configure_vsysmin(charger_index, charger_dt_config->vsys_min_recover_mv);
       err_flag |= pm_scpq_chgr_set_float_volt(charger_index, charger_dt_config->vflt_recover_mv);
       err_flag |= pm_scpq_chgr_set_charge_current(charger_index, PM_SCPQ_CHGR_PRE_CHARGE_CURRENT, BATTERY_UV_OC_I_PRE_CFG_IN_MA);
    }
    else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
    {
        //Disable algorithm to regulate pre-charge current
        err_flag |= pm_scpq_hs_chgr_vph_prechg_alg_en(bus_id, charger_index, FALSE);

        //Get current V_sys_min, V_float, I_pre_chg settings, restore them after battery recovered
        err_flag |= pm_scpq_hs_chgr_get_vsysmin_cfg(bus_id, charger_index, &v_sys_min_backup);
        err_flag |= pm_scpq_hs_chgr_get_float_volt_cfg(bus_id, charger_index, &v_float_backup);
        err_flag |= pm_scpq_hs_chgr_get_charge_current_cfg(bus_id, charger_index, PM_SCPQ_HS_CHGR_PRE_CHARGE_CURRENT, &i_pre_chg_backup);

        //Set V_sys_min = 4.6v, V_float = 4.5v(1S) / 9.0v(2S), IPRE_CFG = 250mA(1S) / 125mA(2S) 
        //This is to ensure battery can only charge in pre/trickle state with low charging current at the beginning
        err_flag |= pm_scpq_hs_chgr_configure_vsysmin(bus_id, charger_index, charger_dt_config->vsys_min_recover_mv);
        err_flag |= pm_scpq_hs_chgr_set_float_volt(bus_id, charger_index, charger_dt_config->vflt_recover_mv);
        err_flag |= pm_scpq_hs_chgr_set_charge_current(bus_id, charger_index, PM_SCPQ_HS_CHGR_PRE_CHARGE_CURRENT, BATTERY_UV_OC_I_PRE_CFG_IN_MA); 
    }         

    //Disable SMB1399 protections for 2s battery
    err_flag |= pm_app_chg_enable_smb_protections(FALSE);

    err_flag |= pm_app_chg_dam_cable_config();

    //Enable charging and charger wdog
    err_flag |= pm_chg_enable_usb_charging(TRUE);
    err_flag |= pm_chg_enable_wireless_charging(TRUE);
    err_flag |= pm_app_chg_enable_charger_wdog(TRUE);

    //Waiting for charging status update at 1st time charging enable
    err_flag |= pm_busy_wait(PM_WEAK_BATTERY_CHARGING_DELAY);

    //waiting for battery recovered
    while(!pm_app_chg_dbc_timeout() && (vcell < vcell_thld))
    {
      pm_log_message("Vbat:%dmV", vcell);
      pm_busy_wait(BATTERY_UV_OC_RECOVERY_TIME);

      err_flag |= pm_chg_is_charging_ongoing(&charging);
      if(FALSE == charging)
      {
        recovered = FALSE;
        break;
      }

      err_flag |= pm_app_chg_output_charging_status();
      err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, light_on);
      light_on = (light_on == TRUE) ? FALSE : TRUE;

      err_flag |= pm_chg_get_vbatt(&vcell);
      if((vcell >= vcell_thld) && (TRUE == battery_is_2s))
      {
        // The required delay is different between protection IC. VBAT is close to VFloat before protect FET is closed.
        for(uint32 time = 0; time < charger_dt_config->uvp_recover_delay; time += WDOG_PET_INTERVAL_MS)
        {
          pm_app_chg_pet_wdog();
          uint32 uvp_recover_delay_remain = charger_dt_config->uvp_recover_delay - time;            
          if(uvp_recover_delay_remain > WDOG_PET_INTERVAL_MS) 
          {     
            uvp_recover_delay_remain = WDOG_PET_INTERVAL_MS;                
          }
          
          pm_busy_wait(uvp_recover_delay_remain * 1000);
      
          err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, light_on);
          light_on = (light_on == TRUE) ? FALSE : TRUE;
        }
        
        err_flag |= pm_chg_get_vbatt(&vcell);
      }

      // Pet the watch dog so it does not bark during recovery
      pm_app_chg_pet_wdog();
    }

    //Step down V_sys_min setting by 100ms/step whenever battery is recovered or not
    for(v_sys_min_step = charger_dt_config->vsys_min_recover_mv - v_sys_min_backup; v_sys_min_step >= 0; v_sys_min_step -= VSYSMIN_RECOVER_STEP_MV)
    {
      
      if (NULL != pm_scpq_get_data(charger_index))
      {
         err_flag |= pm_scpq_chgr_configure_vsysmin(charger_index, v_sys_min_backup + v_sys_min_step);
      }
      else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
      {
         err_flag |= pm_scpq_hs_chgr_configure_vsysmin(bus_id, charger_index, v_sys_min_backup + v_sys_min_step); 
      }        

      pm_busy_wait(BATTERY_UV_OC_VSYSMIN_STEP_DOWN_INTERVAL);
    }

    if (NULL != pm_scpq_get_data(charger_index))
    {
       //Restore V_float, I_pre_chg settings whenever battery is recovered or not
       err_flag |= pm_scpq_chgr_set_float_volt(charger_index, v_float_backup);
       err_flag |= pm_scpq_chgr_set_charge_current(charger_index, PM_SCPQ_CHGR_PRE_CHARGE_CURRENT, i_pre_chg_backup);
    }
    else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
    {
       //Restore V_float, I_pre_chg settings whenever battery is recovered or not
       err_flag |= pm_scpq_hs_chgr_set_float_volt(bus_id, charger_index, v_float_backup);
       err_flag |= pm_scpq_hs_chgr_set_charge_current(bus_id, charger_index, PM_SCPQ_HS_CHGR_PRE_CHARGE_CURRENT, i_pre_chg_backup);
       err_flag |= pm_scpq_hs_chgr_vph_prechg_alg_en(bus_id, charger_index, TRUE);
    }        

    //Enable SMB1399 protections for 2s battery
    err_flag |= pm_app_chg_enable_smb_protections(TRUE);

    if(FALSE == recovered)
    {
      pm_log_message("battery recover failed");
      //Wait 1s to flush out the uart log
      pm_busy_wait(1 * 1000 * 1000);
      err_flag |= pm_device_shutdown();
    }

    pm_log_message("Battery recovered");
  }

  // Turn off LED after exiting recovery
  err_flag |= pm_rgb_led_config(PM_RGB_SEGMENT_R, PM_RGB_DIM_LEVEL_MID, FALSE);

  return err_flag;
}


/* SMB1399 protections for 2s battery UV/OC recovery */
static pm_err_flag_type 
pm_app_chg_enable_smb_protections(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean battery_is_2s = FALSE;
  pm_register_data_type subtype = 0;

  err_flag = pm_chg_is_2s_batt(&battery_is_2s);    
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }  

  // TODO: Do we need to check if SMB1399 is present? Is it still SMB1399 on Lanai?
  if(battery_is_2s)
  {
    err_flag |= pm_smb_bridge_read(SMB_SID, SMB_SUBTYPE_ADDR, &subtype);
    switch (subtype)
    {
      case SMB_COTA:
      {
        // D2 WIN_OV (0x267A[5])
        err_flag |= pm_smb_bridge_write_mask(SMB_SID, SMB_139X_SCHG_PERPH0_CFG_SDCDC, MASK_CFG_EN_WIN_OV, enable ? MASK_CFG_EN_WIN_OV : 0);
        // X2 WIN_OV (0x26C8[3])
        err_flag |= pm_smb_bridge_write_mask(SMB_SID, SMB_139X_SCHG_PERPH0_ENG_SDCDC_3LVL_B_LOOP_ERR_CFG, MASK_ENG_X2_WIN_OV, enable ? MASK_ENG_X2_WIN_OV : 0);
        // VBAT2_UV (0X2680[3])
        err_flag |= pm_smb_bridge_write_mask(SMB_SID, SMB_139X_SCHG_PERPH0_SOVP_CFG0, MASK_CFG_EN_UV_RISE_DEB, enable ? MASK_CFG_EN_UV_RISE_DEB : 0);
        break;
      }
      case SMB_SILVERSTONE:
      {
        //D2 WIN_OV (0x307A[5])
        err_flag |= pm_smb_bridge_write_mask(SMB_SID, SMB_1510_SCHG_PERPH0_CFG_SDCDC, MASK_1510_CFG_EN_WIN_OV, enable ? MASK_1510_CFG_EN_WIN_OV : 0);
        //X2 WIN_OV (0x30C8[3])
        err_flag |= pm_smb_bridge_write_mask(SMB_SID, SMB_1510_SCHG_PERPH0_ENG_SDCDC_3LVL_B_LOOP_ERR_CFG, MASK_1510_ENG_X2_WIN_OV, enable ? MASK_1510_ENG_X2_WIN_OV : 0);
        //VBAT2_PD (0x309E[5])
        err_flag |= pm_smb_bridge_write_mask(SMB_SID, SMB_1510_SCHG_PERPH0_LOCK_SPARE, MASK_1510_CFG_EN_VBAT2_PD, 0);
        //VBAT2_UV (0x3080[3])
        err_flag |= pm_smb_bridge_write_mask(SMB_SID, SMB_1510_SCHG_PERPH0_SOVP_CFG0, MASK_1510_CFG_EN_UV_RISE_DEB, enable ? MASK_1510_CFG_EN_UV_RISE_DEB : 0);
        //VBAT2_UVLO (0x31C1[4:3]) set to 4.5V
        err_flag |= pm_smb_bridge_write_mask(SMB_SID, SMB_1510_SCHG_PERPH1_ENG_SSUPPLY1, MASK_1510_CFG_VBAT2_UVLO, (VBAT2_UVLO_4_5V << 3));
        break;
      }
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_app_chg_enable_charger_wdog(boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_chgr_wdog_cfg_type wdog_cfg = {0};
  pm_scpq_hs_misc_wdog_cfg_type scpq_hs_wdog_cfg = {0};
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 charger_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;

  if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_chgr_set_wd_bark_timeout(charger_index, 32 * 1000);
    err_flag |= pm_scpq_chgr_get_config_wdog(charger_index, &wdog_cfg);

    wdog_cfg.wdog_timer_en = enable;
    //if enable, charging will disable when charger wdog bite
    wdog_cfg.bite_wdog_disable_charging_cfg = enable;

    err_flag |= pm_scpq_chgr_config_wdog(charger_index, wdog_cfg);
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
  {
    err_flag |= pm_scpq_hs_misc_set_wd_bark_timeout(bus_id, charger_index, 32 * 1000);
    err_flag |= pm_scpq_hs_misc_get_config_wdog(bus_id, charger_index, &scpq_hs_wdog_cfg);

    scpq_hs_wdog_cfg.wdog_timer_en = enable;
    //if enable, charging will disable when charger wdog bite
    scpq_hs_wdog_cfg.bite_wdog_disable_charging_cfg = enable;

    err_flag |= pm_scpq_hs_misc_config_wdog(bus_id, charger_index, scpq_hs_wdog_cfg); 
  }

  return err_flag;
}


static void
pm_app_chg_pet_wdog(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 charger_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;
 
  if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag |= pm_scpq_chgr_bark_bite_wdog_pet(charger_index);
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      pm_log_message("Pet Charger wdog failed");
    }
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
  {
    err_flag |= pm_scpq_hs_misc_bark_bite_wdog_pet(bus_id, charger_index);
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      pm_log_message("Pet Charger wdog failed");
    }
  
  }        

  // Pet TME introduced watch dog enabling during boot, not charger wdog
  pm_msm_watch_dog_pet();

  return;
}


static pm_err_flag_type 
pm_app_chg_no_battery_boot_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();

  if(charger_dt_config->apply_boot_wo_batt)
  {
    if(charger_dt_config->boot_wo_batt)
    {
      //Enable charging for booting up without battery
      err_flag |= pm_chg_enable_usb_charging(TRUE);
      err_flag |= pm_chg_enable_wireless_charging(TRUE);
      //Config usb ICL
      err_flag |= pm_app_chg_configure_usb_icl(charger_dt_config->icl_boot_wo_batt);
    }
    else
    {
      pm_log_message("No battery, Shutdown!");
      pm_device_shutdown();
    }
  }

  return err_flag;
}

#if 0
pm_err_flag_type
pm_app_chg_is_apsd_done(boolean* done)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 charger_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;

  if(NULL != pm_scpq_get_data(charger_index))
  {
    err_flag = pm_scpq_usb_get_apsd_status(charger_index, PM_SCPQ_USB_APSD_STATUS_APSD_DTC_STATUS_DONE , done);
  }
    else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
    {
      err_flag = pm_scpq_hs_usb_get_apsd_status(bus_id, charger_index, PM_SCPQ_HS_USB_APSD_STATUS_APSD_DTC_STATUS_DONE , done); 
    }        
  else if(NULL != pm_schg_get_data(bus_id, charger_index))
  {
    err_flag = pm_schg_usb_get_apsd_status(bus_id, charger_index, PM_SCHG_USB_APSD_STATUS_APSD_DTC_STATUS_DONE, done);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}
#endif
static pm_err_flag_type
pm_app_chg_restart_aicl_at_max(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint8 charger_index = charger_dt_config->charger_pmic_index;
  uint8 bus_id = charger_dt_config->charger_bus_index;

  if(NULL != pm_scpq_get_data(charger_index))
  {
    //USBIN_AICL_START_AT_MAX = 1;
    err_flag |= pm_scpq_usb_aicl_options_cfg(charger_index, PM_SCPQ_USB_AICL_START_AT_MAX, TRUE, USBIN_COLLAPSE_GF_5MS, USBIN_AICL_STEP_10MS);
    //Restart_AICL = 1;
    err_flag |= pm_scpq_misc_aicl_cmd_enable(charger_index, PM_SCPQ_MISC_AICL_CMD_RESTART_AICL);
  }
    else if (NULL != pm_scpq_hs_get_data(bus_id, charger_index))
    {
      //USBIN_AICL_START_AT_MAX = 1;
      err_flag |= pm_scpq_hs_usb_aicl_options_cfg(bus_id, charger_index, PM_SCPQ_HS_USB_AICL_START_AT_MAX, TRUE);
      //Restart_AICL = 1;
      err_flag |= pm_scpq_hs_misc_aicl_cmd_enable(bus_id, charger_index, PM_SCPQ_HS_MISC_AICL_CMD_RESTART_AICL);
    }        
  else if(NULL != pm_schg_get_data(bus_id, charger_index))
  {
    err_flag |= pm_schg_usb_aicl_options_cfg(bus_id, charger_index, PM_SCHG_USB_AICL_CFG_AICL_START_AT_MAX, TRUE);
    err_flag |= pm_schg_misc_aicl_cmd(bus_id, charger_index, PM_SCHG_MISC_AICL_CMD_RESTART_AICL);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}


/*
  For AICL from max ->It means the input current is adjust from the max.(default it starts from 500ma)
  For example, ICL is set to max (e.g. 3A) and then reduce step by step till the proper ICL value is applied.
  OEMs often perfer start from the max. They observed issues that the power consumption is higher than 500ma and battery is absent.
  So if we skip DBC, then need to call this funtion to prevent device brown out by higher power consumption
*/
static pm_err_flag_type
pm_app_chg_wait_apsd_and_aicl_from_max(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 charger_index = PMIC_INDEX_MAX;
  boolean apsd_done = FALSE;
  boolean vbus_present = TRUE;

  err_flag = pm_chg_get_primary_charger_pmic_index(&charger_index);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  // SBL waiting for APSD done
  int loop_count = PM_WAIT_FOR_APSD_DONE_POLL_TIMEOUT / PM_WAIT_FOR_APSD_DONE_INTERVAL;
  while((loop_count-- > 0)&&(vbus_present) && (!apsd_done))
  {
    err_flag |= pm_chg_is_vbus_present(&vbus_present);
    err_flag |= pm_app_chg_is_apsd_done(&apsd_done);
    pm_app_chg_pet_wdog();
    pm_busy_wait(PM_WAIT_FOR_APSD_DONE_INTERVAL);
  }
  
  if(apsd_done)
  {
    err_flag |= pm_app_chg_restart_aicl_at_max();
  }

  return err_flag;
}


pm_err_flag_type
pm_app_chg_dead_battery_charging(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean bypass_dbc = FALSE;
  uint32 battery_voltage = 0;

  err_flag |= pm_app_chg_dbc_condition_check(&bypass_dbc);
  if(TRUE == bypass_dbc)
  {
    pm_chg_get_vbatt(&battery_voltage);
    pm_log_message("Loader dbc skipped. VBAT: %dmV", battery_voltage);
    return err_flag;
  }

  err_flag |= pm_app_chg_battery_uv_oc_detection();

  err_flag |= pm_chg_enable_usb_charging(TRUE);
  err_flag |= pm_chg_enable_wireless_charging(TRUE);

  err_flag |= pm_app_chg_enable_charger_wdog(TRUE);
  err_flag |= pm_app_chg_check_weak_battery_status();

  return err_flag;
}


pm_err_flag_type pm_config_jeita()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;

  if(NULL != pm_scpq_get_data(pmic_index))
  {
    err_flag = pm_scpq_config_jeita(pmic_index);
  }
  else if (NULL != pm_scpq_hs_get_data(bus_id, pmic_index))
  {
    err_flag = pm_scpq_hs_config_jeita(bus_id, pmic_index); 
  }        
  else if(NULL != pm_schg_get_data(bus_id, pmic_index))
  {
    err_flag = pm_schg_config_jeita(bus_id, pmic_index);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  return err_flag;
}


pm_err_flag_type pm_scpq_config_jeita(uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 code = 0;
  int32 temp = 0;
  uint16 adc_code = 0;
  
  // configure too cold AFP
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_cold_afp_threshold, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD_AFP, code);
  err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_AFP_COLD, charger_dt_config->apply_too_cold_afp);
  
  // configure too hot AFP
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_hot_afp_threshold, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT_AFP, code);
  err_flag |= pm_scpq_batif_jeita_en_cfg(pmic_index, PM_SCPQ_BATIF_JEITA_AFP_HOT, charger_dt_config->apply_too_hot_afp);

  //configure too cold
  err_flag |= pm_scpq_batif_get_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_COLD, code);

  //configure too hot
  err_flag |= pm_scpq_batif_get_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_TOO_HOT, code);
  
  //configure warm
  err_flag |= pm_scpq_batif_get_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_WARM, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_WARM, code);

  //configure cool  
  err_flag |= pm_scpq_batif_get_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_COOL, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_batif_set_jeita_threshold_value(pmic_index, PM_SCPQ_BATIF_JEITA_THRESHOLD_COOL, code);

  return err_flag;
}


pm_err_flag_type pm_schg_config_jeita(uint32 bus_id, uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();  
  uint32 code = 0;  
  int32 temp = 0;  
  uint16 adc_code = 0;
  
  // configure too cold AFP
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_cold_afp_threshold, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_COLD_AFP, code);
  err_flag |= pm_schg_chgr_jeita_en_cfg(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_AFP_COLD, charger_dt_config->apply_too_cold_afp);
  
  // configure too hot AFP
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_hot_afp_threshold, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_HOT_AFP, code);
  err_flag |= pm_schg_chgr_jeita_en_cfg(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_AFP_HOT, charger_dt_config->apply_too_hot_afp);

  //configure too cold
  err_flag |= pm_schg_chgr_get_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_COLD, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, (int32)temp, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_COLD, code);

  //configure too hot
  err_flag |= pm_schg_chgr_get_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_HOT, &adc_code);  
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_TOO_HOT, code);
  
  //configure hot
  err_flag |= pm_schg_chgr_get_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_HOT, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_HOT, code);

  //configure cold
  err_flag |= pm_schg_chgr_get_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_COLD, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_schg_chgr_set_jeita_threshold_value(bus_id, pmic_index, PM_SCHG_CHGR_JEITA_THRESHOLD_COLD, code);

  return err_flag;
}


pm_err_flag_type pm_scpq_hs_config_jeita(uint32 bus_id, uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
#if 0  //uncomment this after testing
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 code = 0;
  int32 temp = 0;
  uint16 adc_code = 0;
  
  // configure too cold AFP
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_cold_afp_threshold, &code);
  err_flag |= pm_scpq_hs_batif_set_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD_AFP, code);
  err_flag |= pm_scpq_hs_batif_jeita_en_cfg(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_AFP_COLD, charger_dt_config->apply_too_cold_afp);
  
  // configure too hot AFP
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, charger_dt_config->too_hot_afp_threshold, &code);
  err_flag |= pm_scpq_hs_batif_set_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT_AFP, code);
  err_flag |= pm_scpq_hs_batif_jeita_en_cfg(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_AFP_HOT, charger_dt_config->apply_too_hot_afp);

  //configure too cold
  err_flag |= pm_scpq_hs_batif_get_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_hs_batif_set_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD, code);

  //configure too hot
  err_flag |= pm_scpq_hs_batif_get_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_hs_batif_set_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT, code);
  
  //configure warm
  err_flag |= pm_scpq_hs_batif_get_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_WARM, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_hs_batif_set_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_WARM, code);

  //configure cool  
  err_flag |= pm_scpq_hs_batif_get_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_COOL, &adc_code);
  err_flag |= pm_app_chg_get_batt_temp_of_adc_code(PM_ADC_PU_100K, (uint32)adc_code, &temp);
  err_flag |= pm_app_chg_get_adc_code_of_battery_temp((pm_adc_pull_up_type)charger_dt_config->batt_therm_pull_up, temp, &code);
  err_flag |= pm_scpq_hs_batif_set_jeita_threshold_value(bus_id, pmic_index, PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_COOL, code);
#endif
  return err_flag;
}


pm_err_flag_type 
pm_app_load_batt_id_from_sdam(uint32 *batt_id_ohms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type batt_id_lsb = 0;
  pm_register_data_type batt_id_msb = 0;
  
  if(NULL == batt_id_ohms)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  err_flag |= pm_comm_read_byte(PMIC_A, QBG_SDAM_AUTH_BATT_ID_0_LSB, &batt_id_lsb);
  err_flag |= pm_comm_read_byte(PMIC_A, QBG_SDAM_AUTH_BATT_ID_0_MSB, &batt_id_msb);
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  *batt_id_ohms = (batt_id_msb << 8 | batt_id_lsb) * 1000;

  return err_flag;
}


static pm_err_flag_type 
pm_app_save_batt_id_to_sdam(uint32 batt_id_ohms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type batt_id_lsb = 0;
  pm_register_data_type batt_id_msb = 0;
  uint32 battery_id_sdram = 0;

  //Save battery ID value saved to SDRAM is one-thousandth of battery id value due to SDRAM size limit.(8bit)
  battery_id_sdram = batt_id_ohms / 1000; 
  batt_id_lsb = (pm_register_data_type)battery_id_sdram;
  batt_id_msb = (pm_register_data_type)(battery_id_sdram >> 8);
  
  err_flag |= pm_comm_write_byte(PMIC_A, QBG_SDAM_AUTH_BATT_ID_0_LSB, batt_id_lsb);
  err_flag |= pm_comm_write_byte(PMIC_A, QBG_SDAM_AUTH_BATT_ID_0_MSB, batt_id_msb);

  return err_flag;
}


static pm_err_flag_type pm_smb_bridge_write(uint32 sid, pm_register_address_type reg, pm_register_data_type data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type read_data = 0;
  pm_register_data_type config_value[] = {0, 0, 0, 0};
  uint8 cnt = 0, cmd_status = 0, bus_id = 0;
  uint8 *trigger_argument = NULL, *trigger_return_value = NULL;

  config_value[0] = sid | CMD_WRITE;
  config_value[1] = PID(reg);
  config_value[2] = OFFSET(reg);
  config_value[3] = data;

  //Set register SID/PID/Offset and data
  err_flag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, MEM_011, (sizeof(config_value) / sizeof(config_value[0])), config_value);

  //Trigger PBS
  err_flag |= pm_pbs_client_sw_trigger(bus_id, PMIC_A, PM_PBS_CORE_3, PM_PBS_CLIENT_2, PM_PBS_CLIENT_HW_TRIGGER_4, trigger_argument, trigger_return_value);

  //Wait for write cmd completion
  while(cnt++ < MAX_WAIT_COUNT)
  {
    err_flag |= pm_busy_wait(SPMI_BRIDGE_DELAY);
    err_flag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_15, MEM_011, 1, &read_data);
    cmd_status = read_data & COMPLETE_STATUS_MASK;
    if(cmd_status == SDAM_STATUS_COMPLETED)
    {
      break;
    }
  }

  if(cmd_status != SDAM_STATUS_COMPLETED)
  {
    pm_log_message("bridge write not completed, cmd_status = 0x%02X, count = %d", cmd_status, cnt);
    return PM_ERR_FLAG_FAILURE;
  }

  return err_flag;
}


static pm_err_flag_type pm_smb_bridge_read(uint32 sid, pm_register_address_type reg, pm_register_data_type *data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type read_data = 0;
  pm_register_data_type config_value[] = {0, 0, 0};
  uint8 cnt = 0, cmd_status = 0, bus_id = 0;
  uint8 *trigger_argument = NULL, *trigger_return_value = NULL;

  config_value[0] = sid | CMD_READ;
  config_value[1] = PID(reg);
  config_value[2] = OFFSET(reg);

  //Set register SID/PID/Offset and data
  err_flag = pm_sdam_mem_write(PMIC_A, PM_SDAM_15, MEM_011, (sizeof(config_value) / sizeof(config_value[0])), config_value);

  //Trigger PBS
  err_flag |= pm_pbs_client_sw_trigger(bus_id, PMIC_A, PM_PBS_CORE_3, PM_PBS_CLIENT_2, PM_PBS_CLIENT_HW_TRIGGER_4, trigger_argument, trigger_return_value);

  //Wait for read cmd completion
  while(cnt++ < MAX_WAIT_COUNT)
  {
    err_flag |= pm_busy_wait(SPMI_BRIDGE_DELAY);
    err_flag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_15, MEM_011, 1, &read_data);
    cmd_status = read_data & COMPLETE_STATUS_MASK;
    if(cmd_status == SDAM_STATUS_COMPLETED)
    {
      break;
    }
  }

  if(cmd_status != SDAM_STATUS_COMPLETED)
  {
    pm_log_message("bridge read not completed, cmd_status = 0x%02X, count = %d", cmd_status, cnt);
    return PM_ERR_FLAG_FAILURE;
  }

  //Fetch the data
  err_flag |= pm_sdam_mem_read(PMIC_A, PM_SDAM_15, MEM_014, 1, data);

  return err_flag;
}


static pm_err_flag_type pm_smb_bridge_write_mask(uint32 sid, pm_register_address_type reg, pm_register_data_type mask, pm_register_data_type data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type byte_written = 0;

  err_flag = pm_smb_bridge_read(sid, reg, &byte_written);

  byte_written &= ~mask;
  data &= mask;
  byte_written |= data;

  err_flag |= pm_smb_bridge_write(sid, reg, byte_written);

  return err_flag;
}


static pm_err_flag_type pm_smb_bridge_read_mask(uint32 sid, pm_register_address_type reg, pm_register_data_type mask, pm_register_data_type *data)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  err_flag = pm_smb_bridge_read(sid, reg, data);
  *data = *data & mask;

  return err_flag;
}


static boolean
pm_app_chg_dbc_timeout()
{
  static uint64 dest_timestamp = 0;
  
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  if(0 == dest_timestamp)
  {
    pm_utils_get_timestamp(PM_TIME_IN_MSEC, &dest_timestamp);
  
    dest_timestamp += charger_dt_config->dbc_max_timer_sec * CONVERSION_SEC_TO_MSEC;
  }

  uint64 curr_timestamp = 0;
  pm_utils_get_timestamp(PM_TIME_IN_MSEC, &curr_timestamp);

  return (charger_dt_config->dbc_max_timer_sec != 0) && (curr_timestamp >= dest_timestamp);
}


static pm_err_flag_type 
pm_app_bmd_src_ctl(pm_bmd_src_ctl_sel_type src_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;

  err_flag |= pm_app_chg_enable_bpd_cfg(FALSE);
  
  err_flag |= pm_bmd_enable(bus_id, pmic_index, FALSE);
  err_flag |= pm_bmd_src_ctl(bus_id, pmic_index, src_type);
  err_flag |= pm_bmd_enable(bus_id, pmic_index, TRUE);        
  
  err_flag |= pm_app_chg_enable_bpd_cfg(TRUE);

  return err_flag;
}


pm_err_flag_type
pm_app_bsi_strong_pullup(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 battery_id = 0;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;
  
  err_flag |= pm_app_load_batt_id_from_sdam(&battery_id);

  if(0 == battery_id)
  {
    if(NULL != pm_bmd_get_data(bus_id, pmic_index))
    {
      err_flag |= pm_app_chg_enable_bpd_cfg(FALSE);
      err_flag |= pm_bmd_enable(bus_id, pmic_index, FALSE);
    }

    if(NULL != pm_bsi_get_data(bus_id, pmic_index))
    {
      err_flag |= pm_bsi_pu_resistor_enable(bus_id, pmic_index, FALSE); //BSI_BSI_EN --- bit7 0 disable BSI
      err_flag |= pm_bsi_pu_resistor_cfg(bus_id, pmic_index, PM_BSI_BIF_PU_680); //BSI_MIPI_BIF_CFG --- bit7 0x1: Enable chip internal pull-up resistor. bit6 0x1: PULLUP_680.
      err_flag |= pm_bsi_pu_resistor_enable(bus_id, pmic_index, TRUE); //BSI_BSI_EN --- bit7 1 enable BSI
    }  
  }

  return err_flag;
}


static pm_err_flag_type 
pm_app_is_smartbattery(boolean *is_smartbattery)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 battery_id = 0;
  
  err_flag |= pm_app_load_batt_id_from_sdam(&battery_id);
  *is_smartbattery = (battery_id > SMART_BATTERY_THRESHOLD_OHM) ? TRUE : FALSE;

  return err_flag;
}


static pm_err_flag_type 
pm_app_chg_dam_cable_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_charger_config *charger_dt_config = pm_get_charger_dt_config();
  uint32 pmic_index = charger_dt_config->charger_pmic_index;
  uint32 bus_id = charger_dt_config->charger_bus_index;
  boolean is_dam_cable = FALSE;
  boolean apsd_done = FALSE;
  boolean vbus_present = TRUE;
  pm_chg_charger_port_type charger_type = PM_CHARGER_PORT_TYPE_INVALID;
  
  err_flag |= pm_app_chg_is_dam_cable_connected(bus_id, pmic_index, &is_dam_cable);  

  if(is_dam_cable)
  {
    // SBL waiting for APSD done
    int loop_count = PM_WAIT_FOR_APSD_DONE_POLL_TIMEOUT / PM_WAIT_FOR_APSD_DONE_INTERVAL;
    while((loop_count-- > 0)&&(vbus_present) && (!apsd_done))
    {
      err_flag |= pm_chg_is_vbus_present(&vbus_present);
      err_flag |= pm_app_chg_is_apsd_done(&apsd_done);
      pm_app_chg_pet_wdog();
      pm_busy_wait(PM_WAIT_FOR_APSD_DONE_INTERVAL);
    }
    
    err_flag |= pm_chg_get_charger_port_type(&charger_type);
    
    if(apsd_done)
    {
      if(PM_CHARGER_PORT_SDP_CHARGER == charger_type) 
      {
        err_flag |= pm_app_chg_configure_usb_icl(PM_SDP_ICL_MA);
      }
      else if(PM_CHARGER_PORT_CDP_CHARGER == charger_type) 
      {
        err_flag |= pm_app_chg_configure_usb_icl(PM_CDP_ICL_MIN_MA);
      }   
    }
    else if(loop_count == 0)
    {
      err_flag |= pm_app_chg_configure_usb_icl(PM_SDP_ICL_MA);
    } 
  }

  return err_flag;
}


