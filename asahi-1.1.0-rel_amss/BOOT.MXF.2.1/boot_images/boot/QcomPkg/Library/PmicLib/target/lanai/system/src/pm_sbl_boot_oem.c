/*! \file pm_sbl_boot_oem.c
*  \n
*  \brief This file contains PMIC device initialization function where initial PMIC
*  \n SBL settings are configured through the PDM auto-generated code.
*  \n
*   Copyright (c) 2015,2023, 2024 Qualcomm Technologies, Inc. All rights reserved.
*   Confidential and Proprietary - Qualcomm Technologies, Inc.
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/target/lanai/system/src/pm_sbl_boot_oem.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/31/19   zzx     Added pm_log_pmic_version()
02/01/18   aab     Updated PMI_CLK_DIST_ADDR to be VREG_SP
12/22/17   pxm     Change SRAM access to DMA support
09/28/17   pxm     Remove the code which turning off L24A for EUD check.
09/13/17   aab     Added target specific fn: pm_spmi_tgt_vrm_init()
07/10/17   pxm     Loader to provide OTP Read API for VBAT,IBAT Gain offset
06/13/17   czq     Configure BATT_ID bias delay.
04/06/17   aab     Updated pm_driver_post_init(): Turn off EUD Rail if VBUS is detected 
03/07/17   ds      Removed the call to pm_aop_pre_init()
01/16/17   aab     Updated pm_driver_post_init() to support SDM845
06/01/16   aab     Updated pm_driver_post_init() to add RF_CLK Drive strength configuration if CDP is detected
04/29/15   aab     Updated pm_device_post_init() 
12/04/15   aab     Updated to support MSM8998 target 
12/04/15   aab     Creation
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_sbl_boot_target.h"
#include "pm_pon.h"
#include "pm_app_pon.h"
#include "pm_sbl_boot.h"
#include "pm_device.h"
#include "pm_comm.h"
#include "pm_utils.h"
#include "DDIChipInfo.h"
#include "ChipInfo.h"
#include "pm_sdam_driver.h"
#include <stdio.h>
#include "boot_logger.h"
#include "CoreVerify.h"
#include "pm_ldo.h"
#include "pm_bob.h"
#include "DALDeviceId.h"
#include "DDIPlatformInfo.h"
#include "DDIChipInfo.h"
#include "pm_app_vreg.h"
#include "pm_target_information.h"
#include "pm_clk.h"
#include "pm_clk_calrc.h"
#include "pm_pbs_driver.h"
#include "pm_version.h"
#include "pm_pbs_info.h"
#include "pm_log_utils.h"
#include "DDIPlatformInfo.h"
#include "SpmiCfg.h"
#include "pm_app_rgb.h"
#include "pm_app_chg.h"
#include "pm_adc_config.h"
#include "PlatformInfo.h"
#include "pm_dt_parser.h"
#include "pm_dt.h"
#include "pm_chg.h"
#include "pm_qbg.h"
#include "pm_rtc.h"
#include "railway.h"
#include "cpr.h"
#include "pm_app_rtc.h"
#include "pm_config_sbl_common.h"
#include "ChipInfo.h"
#include "pm_gpio_driver.h"
#include "pm_pbs_driver.h"
#include "pm_pbs_client.h"
#include <Library/ChipInfoLib/ChipInfoImage.h>
#include <Library/ChipInfoLib/ChipInfoLocal.h>
#include "pm_scpq_chgr.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
#define PM_VREG_SP_SID    0x1
#define PM_VREG_SP_ADDR   0x3E00
#define PSTM1_SID         0x0
#define PSTM1_BASE_ADDR   0x2900
#define BCL1_SID          0x1
#define BCL2_SID          0x7
#define BCL_BASE_ADDR     0x4800

#define REVID_SBL_ID_0    0x150
#define REVID_SBL_ID_1    0x151

#define SPMI_MASTER_SPMI_CLK_BUF_CFG  0x0740

#define SPMI_MASTER2_SPMI_CLK_BUF_CFG  0x1240

#define PM_SDCARD_DET_MGPI_INDEX 4
#define PM_VERSION_LOG_LENGTH 128

#define PM_TOKEI_INT_SLAVE_ID     0x0
#define INT_MOD_EN_CTL            0x546
#define INT_ENABLE                0x80

#define OUTPUT_VOLTAGE_STEP_SIZE  25
#define MIN_ELVSS_VOLT -800
#define MAX_ELVSS_VOLT -6600
#define MIN_ELVDD_VOLT 4600
#define MAX_ELVDD_VOLT 5200
#define MIN_OLEDB_VOLT 5000
#define MAX_OLEDB_VOLT 8000
#define OLEDB_BASE_OUTPUT_VOLTAGE 4925
#define AZURA_INDEX   0
#define HAPUNA_INDEX  7
#define SDAM17_MEM_07 7
#define SDAM17_MEM_08 8
#define SDAM17_MEM_09 9
#define LDO_LPM_OCP_RESP_FLAG_REG 51
#define ONE_BYTE      1

#define SDAM_PERIPHERAL_OFFSET 0x100
#define SDAM_PBS_RET 0x43
#define RAIL_TYPES_COUNT 3

#define GPIO1_PERPH_RESET_CTL3  0x88DA
#define IGNORE_ALL_RESET        0

#define S4_SOFT_RESET_CTL_REGISTER  0xA4DB

#define SDAM23_MEM127_ADDR 0x86BF
#define ADC_CMN2_IADC_DIG_PARAM2_ADDR 0x3049
#define ADC_CMN_BG_EXT_SNS_RESISTOR_SEL 0x305E
#define EXT_RSNS_SELECTION 0x01

#define PSI_VARIANT_MAJOR   0x7297
#define PSI_VARIANT_MINOR   0x7299

#define EPM_MODE_CONFIG_SDAM_ADDR  0xA045 //EPM Enable and Mode set address
#define EPM_DEFAULT_DATA           0x80   //Enabling EPM with ACAT Mode
#define EPM_DEFAULT_MODE_SET       0x1

#define SDAM_MEM_041_ADDR          41
#define CLK4_RF_RF_FREQ_DIV_ADDR   0x5770
#define PM_XO_FREQ_DIV2            0x1
#define SDAM03_MEM090_ADDR			0x729A

#define SPMI_MASTER_SLAVE_SPMI_CLK_BUF_CFG 	(0x0640)
/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/


static pm_err_flag_type pm_pon_tgt_uvlo_ovlo_cfg(void);
static pm_err_flag_type pm_rtc_alarm_threshold_check(void);

static pm_err_flag_type
pm_config_ibat_rsns(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  pm_dt_charger_config *charger_dt_config = (pm_dt_charger_config*)pm_dt_get_node(PMIC_DT_NODE_PM_CHARGER);
  CORE_VERIFY_PTR(charger_dt_config);
  uint32 pmic_index = charger_dt_config->charger_pmic_index;

  if(charger_dt_config->ibat_via_ext_sense)
  {
	err_flag |= pm_comm_write_byte_mask(pmic_index, ADC_CMN2_IADC_DIG_PARAM2_ADDR, 0x3, EXT_RSNS_SELECTION);
    // Set SDAM23_MEM_127 for adc scaling
    err_flag |= pm_comm_write_byte(AZURA_INDEX, SDAM23_MEM127_ADDR, charger_dt_config->ext_rsns_adc_scale);
	
	err_flag |= pm_comm_write_byte(pmic_index, ADC_CMN_BG_EXT_SNS_RESISTOR_SEL, charger_dt_config->ext_rsns_adc_scale);
  }

  return err_flag;
}

static pm_err_flag_type 
pm_sbl_boot_oem_psi_variant_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  pm_dt_psi_config *psi_dt_config = (pm_dt_psi_config*)pm_dt_get_node(PMIC_DT_NODE_OPSI_CONFIG);
  CORE_VERIFY_PTR(psi_dt_config);

  err_flag = pm_comm_write_byte_array(PMIC_A, PSI_VARIANT_MAJOR, 0x2, (uint8*)&psi_dt_config->psi_variant_major);
  err_flag |= pm_comm_write_byte(PMIC_A, PSI_VARIANT_MINOR, psi_dt_config->psi_variant_minor);

  return err_flag;
}

static pm_err_flag_type pm_primming_control(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_sw_config  *sw_dt_config = NULL;
  sw_dt_config = pm_dt_get_node( PMIC_DT_NODE_PM_SW_CONFIG );
  CORE_VERIFY_PTR(sw_dt_config);

  err_flag |= pm_comm_write_byte(AZURA_INDEX, SDAM03_MEM090_ADDR, sw_dt_config->primming_enable);		//primming control

  return err_flag;
}

static pm_err_flag_type
pm_device_pre_init_dt_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 pmic_index = 0;
  uint32 periph_id = 0;  
  uint32 value = 0;
  uint32 operation = 0;
  uint32 bus_id = 0;
  int i = 0;
  pm_model_type model = PMIC_IS_INVALID;
  
  pm_dt_sw_config *sw_dt_config = NULL;
  sw_dt_config = pm_dt_get_node( PMIC_DT_NODE_PM_SW_CONFIG );
  if((sw_dt_config != NULL) && sw_dt_config->device_pre_init && (sw_dt_config->device_pre_init_count > 0))
  {
    for(i = 0; i < sw_dt_config->device_pre_init_count; i++)
    {     
      operation = sw_dt_config->device_pre_init[i * PM_DT_DEV_PRE_INIT_ITEM_SIZE];
      bus_id = sw_dt_config->device_pre_init[(i * PM_DT_DEV_PRE_INIT_ITEM_SIZE) + 1];
      pmic_index = sw_dt_config->device_pre_init[(i * PM_DT_DEV_PRE_INIT_ITEM_SIZE) + 2];
      periph_id = sw_dt_config->device_pre_init[(i * PM_DT_DEV_PRE_INIT_ITEM_SIZE) + 3];
      value = sw_dt_config->device_pre_init[(i * PM_DT_DEV_PRE_INIT_ITEM_SIZE) + 4];

      //If the PMIC absent, go to next item.
      model = pm_get_pmic_model(pmic_index);
      if((PMIC_IS_INVALID == model) || (PMIC_IS_UNKNOWN == model))
      {
        continue;
      }

      switch( operation )
      {
        case PM_EPM_EN:
          err_flag |= pm_sbl_epm_en( (uint8)value );
          break;
        case PM_EPM_MODE:
          err_flag |= pm_sbl_epm_mode( (uint8)value );          
          break;
        case PM_EPM_CONFIG:        
          err_flag |= pm_sbl_epm_config((uint8)bus_id, (uint8)pmic_index, (uint8)periph_id, (uint8)value );
          break;
        case PM_EPM_DEFAULT_MODE:
          if (value == EPM_DEFAULT_MODE_SET)
          {
            err_flag |= pm_comm_write_byte(PMIC_A, EPM_MODE_CONFIG_SDAM_ADDR, EPM_DEFAULT_DATA);
          }
          break;
        default:
          err_flag |= PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
          break;
      }
    }
  }
  return err_flag;
}

static pm_err_flag_type 
pm_log_pmic_version(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_device_info_type pmic_info;
  char pm_version[PM_VERSION_LOG_LENGTH] = {0};
  uint32 size = 0, offset = 0, bus_id = 0, pmic_index = 0;

  for(bus_id = 0; bus_id < PM_MAX_BUSES_SUPPORTED; ++bus_id)
  { 
    offset = 0;
    
    size = snprintf(pm_version, PM_VERSION_LOG_LENGTH - 1, "BUS: %d, PMIC", bus_id);
    
    for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
    {
      err_flag = pm_get_pmic_info_ex(bus_id, pmic_index, &pmic_info);
      if (err_flag != PM_ERR_FLAG_SUCCESS)
      {
        return err_flag;
      }

      if ((pmic_info.ePmicModel != PMIC_IS_UNKNOWN) && (pmic_info.ePmicModel != PMIC_IS_INVALID))
      {
        offset += size;
        size = snprintf(pm_version + offset, PM_VERSION_LOG_LENGTH - 1 - offset,
          " %c:%d.%d", 'A' + pmic_index, pmic_info.nPmicAllLayerRevision, pmic_info.nPmicMetalRevision);
      }
    }

    offset += size;
    pm_version[offset] = '\0';

    // Using pm_log_message here will lead to unexpected warning due to snprintf used inside pm_log_message
    LogMsg(pm_version);
  }

  return err_flag;
}


static pm_err_flag_type
pm_post_driver_init_dt_config(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint16 spmi_clk_data_cfg = 0;
  uint32 pmic_index = 0;
  uint32 periph_id = 0;  
  uint32 value = 0;
  uint32 operation = 0;
  //uint32 bus_id = 0;
  int i = 0;
  pm_model_type model = PMIC_IS_INVALID;
  
  pm_dt_sw_config  *sw_dt_config = NULL;
  sw_dt_config = pm_dt_get_node( PMIC_DT_NODE_PM_SW_CONFIG );
  if((sw_dt_config != NULL) && (sw_dt_config->post_driver_init != NULL) && (sw_dt_config->post_driver_init_count > 0))
  {
    for(i = 0; i < sw_dt_config->post_driver_init_count; i++)
    {     
      operation = sw_dt_config->post_driver_init[i*5];
      //bus_id = sw_dt_config->post_driver_init[(i*5)+1];
      pmic_index = sw_dt_config->post_driver_init[(i*5)+2];
      periph_id = sw_dt_config->post_driver_init[(i*5)+3];
      value = sw_dt_config->post_driver_init[(i*5)+4];

      //If the PMIC absent, go to next item.
      model = pm_get_pmic_model(pmic_index);
      if((PMIC_IS_INVALID == model) || (PMIC_IS_UNKNOWN == model))
      {
        continue;
      }
      
      switch( operation )
      {
        case PM_LDO_SET_ENABLE:
          err_flag |= pm_ldo_sw_enable(pmic_index, periph_id, value, TRUE);
          break;
        case PM_LDO_SET_VOLT:
          err_flag |= pm_ldo_volt_level(pmic_index, periph_id, value * 1000, TRUE); // *1000 to change to uv 
          break;
        case PM_LDO_SET_MODE:
          err_flag |= pm_ldo_sw_mode(pmic_index, periph_id, value);
          break;
        case PM_LDO_SET_PD_CTRL:
          err_flag |= pm_ldo_pull_down(pmic_index, periph_id, value);
          break;
        case PM_LDO_SET_PIN_CTRL:
          err_flag |= pm_ldo_pin_ctrled(pmic_index, periph_id, value);
          break;
        case PM_LDO_SET_OCP_BROADCAST:
          err_flag |= pm_ldo_ocp_broadcast(pmic_index, periph_id, value);
          break;
        case PM_LDO_SET_AHC:
          err_flag |= pm_ldo_ahc_enable(pmic_index, periph_id, value);
          break;  
        case PM_SMPS_SET_ENABLE:
          err_flag |= pm_smps_sw_enable(pmic_index, periph_id, value, TRUE);
          break;
        case PM_SMPS_SET_VOLT:
          err_flag |= pm_smps_volt_level(pmic_index, periph_id, value * 1000, TRUE);  // *1000 to change to uv
          break;
        case PM_SMPS_SET_MODE:
          err_flag |= pm_smps_sw_mode(pmic_index, periph_id, value);
          break;
        case PM_SMPS_SET_PD_CTRL:
          err_flag |= pm_smps_pull_down(pmic_index, periph_id, value);
          break;
        case PM_SMPS_SET_PIN_CTRL:
          err_flag |= pm_smps_pin_ctrled(pmic_index, periph_id, value);
          break;
        case PM_SMPS_SET_OCP_BROADCAST:
          err_flag |= pm_smps_ocp_broadcast(pmic_index, periph_id, value);
          break;
        case PM_SMPS_SET_AHC:
          err_flag |= pm_smps_ahc_enable(pmic_index, periph_id, value);
          break;
        case PM_SMPS_SET_AHC_HR:
          err_flag |= pm_smps_ahc_set_headroom(pmic_index, periph_id, value);
          break;
        case PM_BOB_SET_ENABLE:
          //err_flag = ;
          break;
        case PM_BOB_SET_VOLT:
          //err_flag = ;
          break;
        case PM_BOB_SET_MODE:
          //err_flag = ;
          break;
        case PM_GPIO_SET_ENABLE:
          err_flag |= pm_gpio_enable(pmic_index, periph_id, value);
          break;
        case PM_GPIO_SET_CFG_MODE:
          err_flag |= pm_gpio_cfg_mode(pmic_index, periph_id, value);
          break;
        case PM_GPIO_SET_OUTPUT_LVL:
          err_flag |= pm_gpio_set_output_level(pmic_index, periph_id, value);
          break;
        case PM_GPIO_SET_VOLT_SRC:
          err_flag |= pm_gpio_set_voltage_source(pmic_index, periph_id, value);
          break;
        case PM_GPIO_SET_OUT_BUFF_CONFIG:
          err_flag |= pm_gpio_set_out_buf_cfg(pmic_index, periph_id, value);
          break;
        case PM_GPIO_SET_OUT_DRV_STR:
          err_flag |= pm_gpio_set_out_drv_str(pmic_index, periph_id, value);
          break;
        case PM_GPIO_SET_OUT_SRC_CFG:
          err_flag |= pm_gpio_set_out_src_cfg(pmic_index, periph_id, value);
          break;
        case PM_GPIO_SET_PULL_SEL:
          err_flag |= pm_gpio_set_pull_sel(pmic_index, periph_id, value) ;
          break;  
        case PM_CLK_ENABLE:
          err_flag |= pm_clk_sw_enable(PM_SPMI_BUSID_0, pmic_index, periph_id, value);
          break;
        case PM_CLK_DRV_STR:
          err_flag |= pm_clk_drv_strength(PM_SPMI_BUSID_0, pmic_index, periph_id, value) ;
          break;
        case PM_SPMI_CLK_DATA_CFG:
          /*value stores spmi data cfg and periph_id stores spmi clk cfg  here*/
          spmi_clk_data_cfg = (((uint8)value << 8)| ((uint8)periph_id)); 
          err_flag = pm_comm_write_byte_array(pmic_index, SPMI_MASTER_SPMI_CLK_BUF_CFG, 2, (uint8*)&spmi_clk_data_cfg);
          break;
        case PM_SPMI1_CLK_DATA_CFG:
          spmi_clk_data_cfg = (((uint8)value << 8)| ((uint8)periph_id)); 
          err_flag = pm_comm_write_byte_array(pmic_index, SPMI_MASTER2_SPMI_CLK_BUF_CFG, 2, (uint8*)&spmi_clk_data_cfg);
          break;
		case PM_SLV_SPMI_CLK_DATA_CFG:
		  /*value stores spmi_buff_strength_data here*/
		  spmi_clk_data_cfg = (value & 0x3);
		  err_flag = pm_comm_write_byte(pmic_index, SPMI_MASTER_SLAVE_SPMI_CLK_BUF_CFG, (uint8)spmi_clk_data_cfg);
		  break;
        case PM_LDO_LPM_OCP_RESP:
          err_flag |= pm_sdam_mem_write(pmic_index, PM_SDAM_1, LDO_LPM_OCP_RESP_FLAG_REG, ONE_BYTE, (uint8*)&value);
          break;
        case PM_SET_DELAY:
          err_flag |= pm_busy_wait( value );
          break;
        case PM_LDO_OCP_RESP_CFG:
          err_flag |= pm_ldo_ocp_resp_cfg(pmic_index, periph_id, (uint8)value);
          break;
        case PM_SMPS_SET_ULS :
          err_flag |= pm_smps_set_uls( pmic_index, periph_id, value);
          break;
        case PM_LDO_SET_ULS :
          err_flag |= pm_ldo_uls( pmic_index, periph_id, value);
          break;
        default:
          err_flag |= PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
          break;
        }
    }
  }
  
  return err_flag;
}

static pm_err_flag_type
pm_clear_sdam_ret_field(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type* sdam_base_address_list_ptr = NULL;
  pm_register_address_type sdam_base_addr = 0;
  uint32 slave_id = 0;
  uint8 num_of_sdam = 0, i = 0, j = 0;
  uint32 *num_of_sdam_pmics = NULL;

  sdam_base_address_list_ptr =
    (pm_register_address_type *)pm_target_information_get_specific_info(PM_PROP_SDAM_ADDR_DATA);
  CORE_VERIFY_PTR(sdam_base_address_list_ptr);

  num_of_sdam_pmics = (uint32 *)pm_target_information_get_specific_info(PM_PROP_SDAM_PMICS_NUM);
  CORE_VERIFY_PTR(num_of_sdam_pmics);

  //Clear PBS_RET for each sdam
  for(i = 0; i < *num_of_sdam_pmics; i++)
  {
    err_flag = pm_get_slave_id(i, 0, &slave_id);
    if(err_flag != PM_ERR_FLAG_SUCCESS)
    {
      err_flag = PM_ERR_FLAG_SUCCESS;
      continue;
    }

    num_of_sdam = pm_target_information_get_periph_count_info(PM_PROP_SDAM_NUM, i);
    if(num_of_sdam == 0 || sdam_base_address_list_ptr[i] == 0)
    {
      continue;
    }

    for(j = 0; j < num_of_sdam; j++)
    {
      sdam_base_addr = sdam_base_address_list_ptr[i] + (j * SDAM_PERIPHERAL_OFFSET);

      err_flag = pm_comm_write_byte(slave_id, sdam_base_addr + SDAM_PBS_RET, 0x00);

      if(err_flag != PM_ERR_FLAG_SUCCESS)
      {
        return err_flag;
      }
    }
  }

  return err_flag;
}

static pm_err_flag_type
pm_print_psi_version(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 SBL_ID_0 = 0;
  uint8 SBL_ID_1 = 0;

  err_flag |= pm_comm_read_byte(0, REVID_SBL_ID_1, &SBL_ID_1);
  err_flag |= pm_comm_read_byte(0, REVID_SBL_ID_0, &SBL_ID_0);
  if(err_flag == PM_ERR_FLAG_SUCCESS )
  {
    pm_log_message("PSI: b0x%02x_v0x%02x", SBL_ID_1, SBL_ID_0);
  }

  return err_flag;
}

pm_err_flag_type
pm_device_pre_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 data = 0;

  err_flag |= pm_log_pmic_version();

  err_flag |= pm_clear_sdam_ret_field();

  err_flag |= pm_config_ibat_rsns();
  
  err_flag |= pm_sbl_boot_oem_psi_variant_config();

  err_flag |= pm_device_pre_init_dt_config();

  /* Detect platform and set SDAM01_MEM041 before PSI for APQ */
  if(ChipInfo_GetChipId() == CHIPINFO_ID_SMP_LANAI)
  {
    data = 1;
    err_flag |= pm_sdam_mem_write(PMIC_A, PM_SDAM_1, SDAM_MEM_041_ADDR , 1, &data);
  }
  
  err_flag |= pm_primming_control();

  return err_flag; 
}

pm_err_flag_type
pm_sbl_boot_pon_reset_config( void )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_pon_config  *pon_dt = NULL;  
  
  pon_dt = pm_dt_get_node(PMIC_DT_NODE_PM_PON);

  if(pon_dt != NULL)
  {
    if(pon_dt->pshold_enable)
    {
      err_flag |= pm_app_pon_pshold_cfg(pon_dt->ps_hold_reset_type);
    }
    
    //PON KPDPWR PON Reset configuration
    if(pon_dt->s2_kpdpwr_enable)
    {
      err_flag |= pm_app_pon_reset_cfg(PM_APP_PON_RESET_SOURCE_KPDPWR,
                                       pon_dt->s2_kpdpwr_reset_type, 
                                       pon_dt->s2_kpdpwr_s1_ms, 
                                       pon_dt->s2_kpdpwr_s2_ms);   
    }
    else
    {
      err_flag |= pm_pon_reset_source_ctl(PMIC_A, PM_PON_RESET_SOURCE_KPDPWR, PM_OFF);  
    }
    
    //PON RESIN_AND_KPDPWR PON Reset configuration
    if(pon_dt->s2_kpdpwr_resin_enable)
    {
      err_flag |= pm_app_pon_reset_cfg(PM_APP_PON_RESET_SOURCE_RESIN_AND_KPDPWR,
                                       pon_dt->s2_kpdpwr_resin_reset_type, 
                                       pon_dt->s2_kpdpwr_resin_s1_ms,
                                       pon_dt->s2_kpdpwr_resin_s2_ms); 
    }
    else
    {
      err_flag |= pm_pon_reset_source_ctl(PMIC_A, PM_PON_RESET_SOURCE_RESIN_AND_KPDPWR, PM_OFF);
    } 
    
    //PON RESIN Reset configuration
    if(pon_dt->s2_resin_enable)
    {
      err_flag |= pm_app_pon_reset_cfg(PM_APP_PON_RESET_SOURCE_RESIN,
                                       pon_dt->s2_resin_reset_type, 
                                       pon_dt->s2_resin_s1_ms,
                                       pon_dt->s2_resin_s2_ms); 
    }
    else
    {
      err_flag |= pm_pon_reset_source_ctl(PMIC_A, PM_PON_RESET_SOURCE_RESIN, PM_OFF); 
    }

    //S3 Reset configuration
    if(pon_dt->s3_enable)
    {
      err_flag |= pm_app_pon_s3_reset_timer_cfg( pon_dt->s3_reset_src,  pon_dt->s3_reset_timer_value_ms);
    }
    
  }

  return err_flag;
}

pm_err_flag_type
pm_device_post_init ( void )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  err_flag |= pm_print_psi_version();
  err_flag |= pm_sbl_boot_pon_reset_config();

  //PON PMIC UVLO configuration
  err_flag |= pm_pon_tgt_uvlo_ovlo_cfg();
  
  /*check for valid PON keypress */
  err_flag |= pm_app_pwrkey_long_press_check(PM_PON_PWRKEY_DBNC_CHK_AT_LOADER);  

  /*Initialize charger sense resistor calibration */
  err_flag |= pm_ext_rsns_init();

  err_flag |= pm_set_oledb_default_config();

  err_flag |= pm_config_sbl_oem_psi();
  
  /* Lanai APQ platform need RF_CLK4 configured as 38.4MHz to support Neutron card */
  if(ChipInfo_GetChipId() == CHIPINFO_ID_SMP_LANAI)
  {
    err_flag |=  pm_comm_write_byte(PMIC_A, CLK4_RF_RF_FREQ_DIV_ADDR, PM_XO_FREQ_DIV2);
  }

  return err_flag;
}

pm_err_flag_type
pm_set_oledb_default_config()
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_display_config *display_dt = NULL;
  int32  elvss_mvolt = 0;
  uint32 elvdd_mvolt = 0;
  uint32 oledb_mvolt = 0;
  uint8  elvss_data  = 0;
  uint8  elvdd_data  = 0;
  uint8  oledb_data  = 0;   

  display_dt = pm_dt_get_node(PMIC_DT_NODE_PM_DISPLAY);
  if((display_dt != NULL) && display_dt->apply_default_volt)
  {
    elvss_mvolt = display_dt->default_elvss;
    elvdd_mvolt = display_dt->default_elvdd;
    oledb_mvolt = display_dt->default_oledb;
  } 
  else
  {
    return err_flag;
  }


  if(elvss_mvolt > 0 ) //elvss voltage polarity check ; (it should be -ve)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  err_flag |= (ABS(elvss_mvolt) >= ABS(MIN_ELVSS_VOLT) && ABS(elvss_mvolt) <= ABS(MAX_ELVSS_VOLT)) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_INVALID_PARAMETER ;
  err_flag |= (elvdd_mvolt >= MIN_ELVDD_VOLT && elvdd_mvolt <= MAX_ELVDD_VOLT) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_INVALID_PARAMETER ;
  err_flag |= (oledb_mvolt >= MIN_OLEDB_VOLT && oledb_mvolt <= MAX_OLEDB_VOLT) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_INVALID_PARAMETER ;

  if(err_flag != PM_ERR_FLAG_SUCCESS )
  {
    return err_flag;
  }

  elvss_data = (ABS(elvss_mvolt) - ABS(MIN_ELVSS_VOLT)) / OUTPUT_VOLTAGE_STEP_SIZE ;
  elvdd_data = (elvdd_mvolt - MIN_ELVDD_VOLT) / OUTPUT_VOLTAGE_STEP_SIZE ;
  oledb_data = (oledb_mvolt - OLEDB_BASE_OUTPUT_VOLTAGE) / OUTPUT_VOLTAGE_STEP_SIZE ;

  err_flag |= pm_sdam_mem_write(AZURA_INDEX, PM_SDAM_17, SDAM17_MEM_07, ONE_BYTE, &elvss_data);
  err_flag |= pm_sdam_mem_write(AZURA_INDEX, PM_SDAM_17, SDAM17_MEM_08, ONE_BYTE, &elvdd_data);
  err_flag |= pm_sdam_mem_write(AZURA_INDEX, PM_SDAM_17, SDAM17_MEM_09, ONE_BYTE, &oledb_data);

   return err_flag;
}

pm_err_flag_type
pm_driver_pre_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  return err_flag;
}

pm_err_flag_type
pm_driver_post_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_dt_pon_config  *pon_dt = NULL;
  
  pon_dt = pm_dt_get_node(PMIC_DT_NODE_PM_PON);  

  if(pon_dt != NULL)
  {
    err_flag |= pm_clk_calrc_smpl_enable(PM_SPMI_BUSID_0, PMIC_A, pon_dt->enable_smpl);
    err_flag |= pm_clk_calrc_set_smpl_delay(PM_SPMI_BUSID_0, PMIC_A, pon_dt->smpl_delay);
  }
  
  err_flag |= pm_post_driver_init_dt_config();

  err_flag |= pm_app_vreg_clear_ocp_status();
  
  /*WA for EUD usb*/
  err_flag |= pm_comm_write_byte(PMIC_H, 0x945, 1);
  err_flag |= pm_comm_write_byte(PMIC_H, 0xFD46, 0x80);
  
  err_flag |= pm_app_rtc_update_status();

  return err_flag;
}

pm_err_flag_type
pm_sbl_chg_pre_init (void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 charger_pmic_index = PMIC_H;

  //This is a Workaround for Puhi/PM8350B reverse boost OCP issue
  err_flag |= pm_app_chg_trim_otg_offset_and_gain();

  err_flag |= pm_rtc_alarm_threshold_check();

  err_flag |= pm_chg_get_primary_charger_pmic_index(&charger_pmic_index);
  // Disable vph pre-charge algorithm to avoid charging current for SDP is too low in some cases.
  err_flag |= pm_scpq_chgr_vph_prechg_alg_en(charger_pmic_index, FALSE);

  return err_flag;
}


pm_err_flag_type
pm_sbl_chg_post_init ( void )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  return err_flag;
}


pm_err_flag_type
pm_pon_tgt_uvlo_ovlo_cfg(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_model_type pmic_model  = PMIC_IS_INVALID;
  uint32 pmic_index = 0, thresh_mv = 0, hyst_mv = 0, enable = 0;

  pm_dt_pon_config  *pon_dt = NULL;

  pon_dt = pm_dt_get_node(PMIC_DT_NODE_PM_PON);  
  
  if(pon_dt != NULL)
  {
    for(uint8 i=0; i < pon_dt->uvlo_config_count; i++)
    {
     
      pmic_index = pon_dt -> uvlo_cfg[(i*4)+0];
      thresh_mv  = pon_dt -> uvlo_cfg[(i*4)+1];
      hyst_mv    = pon_dt -> uvlo_cfg[(i*4)+2];
      enable     = pon_dt -> uvlo_cfg[(i*4)+3];
      

      pmic_model = pm_get_pmic_model(pmic_index);

      if ((pmic_model != PMIC_IS_INVALID) && (pmic_model != PMIC_IS_UNKNOWN) && 
          (pmic_model != PMIC_IS_AZURA) && (pmic_model != PMIC_IS_PM8008) &&
          (pmic_model != PMIC_IS_PM8010))
      {
        
     
        err_flag |= pm_pon_config_uvlo(pmic_index, 
                                       thresh_mv, 
                                       hyst_mv, 
                                       enable);
      }
    }

    for(uint8 i=0; i < pon_dt->ovlo_config_count; i++)
    {
     
      pmic_index = pon_dt -> ovlo_cfg[(i*4)+0];
      thresh_mv  = pon_dt -> ovlo_cfg[(i*4)+1];
      hyst_mv    = pon_dt -> ovlo_cfg[(i*4)+2];
      enable     = pon_dt -> ovlo_cfg[(i*4)+3];
      

      pmic_model = pm_get_pmic_model(pmic_index);

      if ((pmic_model != PMIC_IS_INVALID) && (pmic_model != PMIC_IS_UNKNOWN) && 
          (pmic_model != PMIC_IS_AZURA) && (pmic_model != PMIC_IS_PM8008) &&
          (pmic_model != PMIC_IS_PM8010))
      {
        

        err_flag |= pm_pon_config_ovlo(pmic_index,
                                       thresh_mv,
                                       hyst_mv,
                                       enable);
      }
    }
  }

  return err_flag;
}


pm_err_flag_type
pm_spmi_tgt_vrm_init ( SpmiBusCfg_Ppid *pm_vrm_rsrc_arr,
                       uint32 *vrm_cfg_index,
                       uint8 vrm_rsrc_arr_size )
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_pbs_data_type* pbs_client_ptr = NULL;
  pm_gpio_data_type* gpio_ptr = NULL;

  uint32 pmic_index = 0, periph_index = 0;
  uint8 no_of_pbs_core = 0, pbs_core_index = 0;

  if (*vrm_cfg_index >= vrm_rsrc_arr_size)
  {
    return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }

  //GPIOs
  for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
     gpio_ptr = pm_gpio_get_data(pmic_index);
     if (gpio_ptr != NULL)
     {
        for (periph_index = 0; periph_index < gpio_ptr->num_of_peripherals; periph_index++)
        {
           if (*vrm_cfg_index >= PM_VRM_RSRC_ARR_SIZE)
           {
             return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
           }
           pm_vrm_rsrc_arr[*vrm_cfg_index].slaveId = gpio_ptr->comm_ptr->slave_id;
           pm_vrm_rsrc_arr[*vrm_cfg_index].address = gpio_ptr->base_address + (gpio_ptr->gpio_register->peripheral_offset * periph_index) ;
           (*vrm_cfg_index)++;
        }
     }
  }
   
    //PBS Clients
  for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
     pbs_client_ptr = pm_pbs_get_data(PM_SPMI_BUSID_0, pmic_index);
     no_of_pbs_core =  pm_target_information_get_periph_count_info(PM_PROP_PBS_CORE, pmic_index);
     if (pbs_client_ptr != NULL)
     {
       for (pbs_core_index = 0; pbs_core_index < no_of_pbs_core; pbs_core_index++)
       { 
         for (periph_index = 0; periph_index < pbs_client_ptr->pbs_client_count[pbs_core_index]; periph_index++)
         {
           if (*vrm_cfg_index >= PM_VRM_RSRC_ARR_SIZE)
           {
             return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
           }
           pm_vrm_rsrc_arr[*vrm_cfg_index].slaveId = pbs_client_ptr->comm_ptr->slave_id;
           pm_vrm_rsrc_arr[*vrm_cfg_index].address = pbs_client_ptr->base_address[pbs_core_index] + (pbs_client_ptr->pbs_client_reg_table->peripheral_offset * periph_index);
           (*vrm_cfg_index)++;
	  
           if ((pmic_index == 0) && (periph_index == PM_PBS_CLIENT_1))
           {
             if (*vrm_cfg_index >= PM_VRM_RSRC_ARR_SIZE)
             {
               return err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
             }
             pm_vrm_rsrc_arr[*vrm_cfg_index].slaveId = PM_GLOBAL_PRIMARY_SID;
             pm_vrm_rsrc_arr[*vrm_cfg_index].address = pm_vrm_rsrc_arr[*vrm_cfg_index-1].address;
             (*vrm_cfg_index)++;
           }
         }
       }
    }
  }
   
  pm_vrm_rsrc_arr[*vrm_cfg_index].slaveId = PM_VREG_SP_SID;
  pm_vrm_rsrc_arr[*vrm_cfg_index].address = PM_VREG_SP_ADDR;
  (*vrm_cfg_index)++;

  pm_vrm_rsrc_arr[*vrm_cfg_index].slaveId = PSTM1_SID;
  pm_vrm_rsrc_arr[*vrm_cfg_index].address = PSTM1_BASE_ADDR;
  (*vrm_cfg_index)++;

/*  if (*vrm_cfg_index >= 200)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
*/

 /*Hard Code BCL Peripherals to RPID-200 onwards*/
/*  (*vrm_cfg_index)=200;
  pm_vrm_rsrc_arr[200].slaveId = 0x2;
  pm_vrm_rsrc_arr[200].address = 0x4800;
  (*vrm_cfg_index)++;

  pm_vrm_rsrc_arr[*vrm_cfg_index].slaveId = 0x3;
  pm_vrm_rsrc_arr[*vrm_cfg_index].address = 0x4800;
  (*vrm_cfg_index)++;*/

  //BCL1 config
  pm_vrm_rsrc_arr[*vrm_cfg_index].slaveId = BCL1_SID;
  pm_vrm_rsrc_arr[*vrm_cfg_index].address = BCL_BASE_ADDR;
  (*vrm_cfg_index)++;

  //BCL2 config
  pm_vrm_rsrc_arr[*vrm_cfg_index].slaveId = BCL2_SID;
  pm_vrm_rsrc_arr[*vrm_cfg_index].address = BCL_BASE_ADDR;
  (*vrm_cfg_index)++;

  return err_flag;
}

/*
 * SM8350: Uncomment below funtion will disable SD card VDD when multi-tray is removed
 */
pm_err_flag_type
pm_tgt_mgpi_cfg ( SpmiBusCfg_MgpiPortCfg **mgpi_port_cfg_ptr )
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  
/*
  //Comment these changes since QRD Lahaina doesn't use multi-tray. Customers can uncomment if necessary.
  //They need to check if they want to enable for posEdge or negEdge.
  if(NULL == mgpi_port_cfg_ptr)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  DalPlatformInfoPlatformType platform_type = DalPlatformInfo_Platform();
  if(DALPLATFORMINFO_TYPE_QRD == platform_type)
  {
    if(NULL == mgpi_port_cfg_ptr[PM_SDCARD_DET_MGPI_INDEX])
    {
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    SpmiBusCfg_MgpiPortCfg sd_config = *mgpi_port_cfg_ptr[PM_SDCARD_DET_MGPI_INDEX];
    sd_config.posEdgeEn = TRUE;
    sd_config.muxSelEn = TRUE;

    if ( SpmiCfg_ConfigureMgpiPort(&sd_config) != SPMI_SUCCESS )
    {
      return PM_ERR_FLAG_BUS_ERR;
    }
  }
*/
  return err_flag;
}


pm_err_flag_type pm_tgt_aop_pre_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  if(TRUE == DalPlatformInfo_IsFusion())
  {
    //Enable L10C in LPM mode if the target is fusion
    err_flag |= pm_ldo_sw_mode(PMIC_C, PM_LDO_10, PM_SW_MODE_LPM);
    err_flag |= pm_ldo_volt_level(PMIC_C, PM_LDO_10, 1200, TRUE);
    err_flag |= pm_ldo_sw_enable(PMIC_C, PM_LDO_10, PM_ON, TRUE);

    err_flag |= pm_comm_write_byte(HAPUNA_INDEX, GPIO1_PERPH_RESET_CTL3, IGNORE_ALL_RESET);
    
    //Enable soft reset on S4 peripheral
    err_flag |= pm_comm_write_byte(PMIC_C, S4_SOFT_RESET_CTL_REGISTER, 0x1);
  }

  if(pm_get_img_type() == PM_IMG_LOADER)
  {
    //err_flag |= pm_config_cpucp_uls();
    pm_pon_output_log_buffer();
  }
  return err_flag;
}

pm_err_flag_type pm_rtc_alarm_threshold_check(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_pon_on_state_reason_type on_reason;
  pm_pon_reason_type pon_reason;
  boolean battery_is_2s = FALSE;

  err_flag = pm_pon_get_on_reason(AZURA_INDEX, &on_reason);
  if((err_flag == PM_ERR_FLAG_SUCCESS)  && on_reason.pon_seq)
  {
    err_flag = pm_pon_get_pon_reason(AZURA_INDEX, &pon_reason);
    if(pon_reason.rtc && (PM_ERR_FLAG_SUCCESS == err_flag))
    {
      boolean vbus_present = FALSE;
      err_flag = pm_chg_is_vbus_present(&vbus_present);
      if((err_flag == PM_ERR_FLAG_SUCCESS) && !vbus_present)
      {
        uint32 vbat_mv = 0;
        err_flag = pm_chg_get_vbatt(&vbat_mv);
        if(err_flag != PM_ERR_FLAG_SUCCESS)
        {
          return err_flag;
        }

        pm_dt_charger_config *charger_dt_config = pm_dt_get_node(PMIC_DT_NODE_PM_CHARGER);
        CORE_VERIFY_PTR(charger_dt_config);

        // Get 1S or 2S info. If 2S, the threshold should be multiply with 2
        err_flag = pm_chg_is_2s_batt(&battery_is_2s);    
        if(err_flag != PM_ERR_FLAG_SUCCESS)
        {
          return err_flag;
        }

        if(battery_is_2s)
        {
          charger_dt_config->vbat_thd_rtc_pon *= 2;
        }
        
        if(vbat_mv < charger_dt_config->vbat_thd_rtc_pon)
        {
          // Disable RTC alarm
          pm_log_message("Disable RTC alarm");
          err_flag |= pm_rtc_alarm_enable(AZURA_INDEX, FALSE);
        }
      }
    }
  }

  return err_flag;
}

