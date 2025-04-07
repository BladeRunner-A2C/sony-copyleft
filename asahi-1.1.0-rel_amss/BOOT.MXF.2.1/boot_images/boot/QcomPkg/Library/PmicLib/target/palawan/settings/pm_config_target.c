/*! \file
 *  
 *  \brief  
 *   pm_config_target.c
 *  \details 
 *   This file contains customizable target specific 
 *   driver settings & PMIC registers. This file is generated from database functional
 *   configuration information that is maintained for each of the targets.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation Resource Setting Information Version: VU.Please Provide Valid Label - Not Approved
 *    PMIC code generation Software Register Information Version: VU.Please Provide Valid Label - Not Approved
 *    PMIC code generation Processor Allocation Information Version: VU.Please Provide Valid Label - Not Approved
 *    This file contains code for Target specific settings and modes.
 *  
 *  Copyright (c) 2010,2023 Qualcomm Technologies, Inc. All rights reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/02/18   pxm     Revise LPG channel for RGB.
07/29/17   sv      Added support for pm_rgb_pmic_index_type config data
05/15/17   aab     Added more config items on sbl_schg_pbs_temp_monitor_config[]
05/01/17   aab     Added support for pm_rgb_specific_data_type config data
04/28/17   aab     Added pm_device_index_type config data
03/14/17   pxm     Enable ICL and set to 1500 mA.
02/13/17    al     Add support to read PBS from REV_ID
01/11/17   pxm     add support for PBS triggered AFP
12/16/16   pxm     Added support for fake battery id range configuration
10/20/16   aab     Added support for Batt_therm Out of bound temperature check
10/13/16   pxm     Updated charger Wdog default configuration
09/17/16   aab     Updated Wipower charger default power level. 
09/17/16   aab     Added WiPower charging wait time as configurable 
08/25/16   pxm     Add skin temperature threshold configuration parameter  
08/12/16   aab     Added debugboard detection support
07/05/16   aab     Cleanup unused data
05/27/16   pxm     Add sbl_schg_wipower_specific_data[1]
04/29/16   aab     Added sbl_pon_specific_data[]
03/24/16   al      Add keypress support
03/29/16   al      Updating for newer target
03/15/16   aab     Driver update (Support for PMI8998)
02/16/16   aab     Creation
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_lpg_driver.h"
#include "pm_vib_driver.h"
#include "pm_resource_manager.h"
#include "pm_pbs_info.h"
#include "pm_pbs_driver.h"
#include "pm_config_target.h"
#include "pm_sbl_boot.h"
#include "pm_pwm.h"
#include "pm_chg.h"
#include "pm_qbg.h"
#include "pm_app_chg.h"
#include "pm_app_pon.h"

#include "rpmh_common.h"
#include "device_info.h"
#include "pm_rgb_driver.h"
#include "pm_app_haptics.h"

#include "pm_adc_config.h"
#include "pm_config_setting.h"
#include "periph_bitmap.h"
#include "pm_config_opsi_wlist.h"
#include "pm_app_rtc.h"

#define PM_ADD_PROP_CONFIG(id, val) { .prop_id = id, .ptr = (void*)(val)}

/************************************************ DRIVER DATA *********************************/
//                             0: PMK8550, 1: PM7550, 2: PM8550VS, 3: PM8550VE, 4: PM735A, 5: empty, 6: empty, 7: PM8550B/7550BA, 8: PMG1110, 9: PMG1110, A: empty, B: empty, C: PM8010, D: PM8010 /*
uint32 num_of_ldo[]        = { 0,          24,        3,           3,           7,           0,        0,           0,          0,           0,        0,         0,        7,         7,       };
uint32 num_of_smps[]       = { 0,          6,         6,           8,           3,           0,        0,           0,          1,           1,        0,         0,        0,         0,       };
uint32 num_of_gpio[]       = { 6,          12,        6,           8,           4,           0,        0,           12,         4,           4,        0,         0,        2,         2,       };  
uint32 num_of_rtc[]        = { 1,          0,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_bob[]        = { 0,          1,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_vs[]         = { 0,          0,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_lpg_chan[]   = { 0,          0,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_pwron[]      = { 1,          1,         1,           1,           1,           0,        0,           1,          1,           1,        0,         0,        0,         0,       }; 
uint32 num_of_misc[]       = { 1,          1,         1,           1,           1,           0,        0,           1,          1,           1,        0,         0,        1,         1,       }; 
uint32 num_of_rgb[]        = { 0,          1,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_wled[]       = { 0,          0,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_charger[]    = { 0,          0,         0,           0,           0,           0,        0,           1,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_bmd[]        = { 0,          0,         0,           0,           0,           0,        0,           2,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_coincell[]   = { 0,          1,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_fg[]         = { 0,          0,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_ibb[]        = { 0,          0,         0,           0,           0,           0,        0,           1,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_lab[]        = { 0,          0,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_ab[]         = { 0,          0,         0,           0,           0,           0,        0,           1,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_oledb[]      = { 0,          0,         0,           0,           0,           0,        0,           1,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_vib[]        = { 0,          0,         0,           0,           0,           0,        0,           1,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_pbs_core[]   = { 3,          0,         0,           0,           0,           0,        0,           1,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_haptics[]    = { 0,          0,         0,           0,           0,           0,        0,           1,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_lcdb[]       = { 0,          0,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_pwm[]        = { 2,          4,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_sdam[]       = {72,          0,         0,           0,           0,           0,        0,           0,          0,           0,        0,         0,        0,         0,       }; 
uint32 num_of_eusb[]      =  { 0,          0,         0,           0,           0,           0,        0,           1,          0,           0,        0,         0,        0,         0,       }; 

pm_swire_data pm_swire_lut[PM_SWIRE_MAP_NUMBER] =
{
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_1}, // MAP_A BOE
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_2}, // MAP_B
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_3}, // MAP_C Visionox
  {PM_ASWIRE_MAP_SEL_1, PM_ESWIRE_MAP_SEL_4}, // MAP_D
  {PM_ASWIRE_MAP_SEL_2, PM_ESWIRE_MAP_SEL_4}, // MAP_E
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_5}, // MAP_F
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_6}, // MAP_G
  {PM_ASWIRE_MAP_SEL_0, PM_ESWIRE_MAP_SEL_7}, // MAP_H
  {PM_ASWIRE_MAP_SEL_3, PM_ESWIRE_MAP_SEL_8}, // MAP_I for LGD
};

pm_lpg_specific_info_type lpg_specific[1] =  
{
  {49}
};

pm_vib_specific_data_type
vib_specific[1] = 
{
  {1200, 3100}
};

pm_sbl_specific_data_type
sbl_specific_data[1] = 
{
  {
    .verbose_uart_logging = FALSE,      // Enable/disable verbose UART logging
    .rfclk2_config_flag   = FALSE,      // FALSE: Default, TRUE: Disable RFCLK2
    .swire_cfg            = {.supported = TRUE,
                             .swire_map = PM_SWIRE_MAP_C, // Swire map index
                             .pmic_sid = 0x7, 
                             .map_reg = 0xF8B4,
                             .oledb_default_volt_cfg= {
                                                       .default_config_supported = FALSE,
                                                       .elvss_default_volt = -4000,
                                                       .elvdd_default_volt = 4600,
                                                       .oledb_default_volt = 6400,
                                                      }
                            },

    .inductor_cfg        = {
                             .supported = TRUE,
                             .cfg_value = 0x02,  // value for inductor config selection
                             .pmic_sid  = 0x0,
                             .reg_addr  = 0x7078, 
                           },                       
  }
};

pm_qbg_ext_rsns_scale_loc_type pm_ext_rsns_scale_location = 
{
  .pmic_index = PMIC_A,
  .sdam_index = PM_SDAM_23,
  .mem_index = 127
};

pm_haptics_app_config pm_haptics_config =
{
  .haptics_pmic = PMIC_H,               // pmic index of haptics peripheral
  .is_external_boost_vdd = FALSE,        // is haptics vdd connected to VPH_PWR or external boost
  .haptics_gpio_pmic = PMIC_H,          // pmic index of GPIO which is used to enable external boost
  .gpio = PM_GPIO_5                     // GPIO number for external boost enable pin
};

pm_rgb_specific_data_type
rgb_specific_data =
{
  .clock                      = PM_PWM_CLK__19_2_MHZ,
  .pre_div                    = 1,
  .exp                        = 3,
  .bit_size                   = PM_PWM_SIZE__9BIT,
  .ramp_step_duration         = 0,
  .hi_multiplier              = 0,
  .low_multiplier             = 0,
  .rgb_sdam_pmic              = PMIC_A,
  .rgb_sdam                   = PM_SDAM_21,
  .sdam_enable_arg            = 1,
  .sdam_disable_arg           = 2,
  .is_rgb_sdam_trig_supported = FALSE,
  .is_lpg_supported           = FALSE, //PWM is supported
  .ramp_direction             = 0,
  .ramp_toggle                = 0,
  .en_pause_hi                = 0,
  .en_pause_lo                = 0,
  .rgb_dim_level_max          = 0x1FF,
  .led_lpg_pwm_ch             = {PM_PWM_RESOURCE_PWM_3, PM_PWM_RESOURCE_PWM_2, PM_PWM_RESOURCE_PWM_1}, //BLUE, GREEN, RED,
  .rgb_pmic                   = PMIC_B,
};

pm_rtc_app_config pm_rtc_config =
{
  .rtc_pmic = PMIC_A,               // rtc PMIC index for FR68618
  .rtc_sdam = PM_SDAM_4,        	// RTC SDAM
  .rtc_sdam_mem = 0x7      // RTC SDAM MEM
};

/* Azura PMIC */
pm_pbs_info_data_type pm_pbs_info_data_a =
{
  .pbs_otp_start_addr    = 0x0,                /* PBS OTP MEMORY Start Address */
  .pbs_otp_mem_size      = 512,                /* PBS OTP MEMORY Size */
  .pbs_ram_start_addr    = 0x1000,              /* PBS RAM MEMORY Start Address */
  .pbs_ram_mem_size      = 0x2000,               /* PBS RAM MEMORY Size */
  .skip_verify_supported = TRUE,               /* Skip Ram Image Word Range Supported */
  .skip_verify_start     = 0x5,                /* Skip Ram Image Word Range Start Word */
  .skip_verify_end       = 0x8,                /* Skip Ram Image Word Range End Word */
  .pbs_info_place_holder = PM_PBS_INFO_IN_PERIPH, /* Place where PBS Info stored */
  .perph_base_addr       = 0x1A00,               /* Periph BASE_ADDRESS */
  .trim_num              = 0x00,               /* trim_num  */
  .tp_rev                = 0x00,               /* tp_rev    */
  .fab_id                = 0x00,               /* fab_id    */
  .wafer_id              = 0x00,               /* wafer_id  */
  .x_co_ordi             = 0x00,               /* x_co_ordi */
  .y_co_ordi             = 0x00,               /* y_co_ordi */
  .lot_id                = 0x00,               /* lot_id_01_00 */
  .mfg_id                = 0x00,               /* mfg_id    */
};

/* Charger PMIC */
pm_pbs_info_data_type pm_pbs_info_data_h =
{
  .pbs_otp_start_addr    = 0x0,                /* PBS OTP MEMORY Start Address */
  .pbs_otp_mem_size      = 512,                /* PBS OTP MEMORY Size */
  .pbs_ram_start_addr    = 0x800,              /* PBS RAM MEMORY Start Address */
  .pbs_ram_mem_size      = 512,                /* PBS RAM MEMORY Size */
  .skip_verify_supported = TRUE,              /* Skip Ram Image Word Range Supported */
  .skip_verify_start     = 0x1F6,                /* Skip Ram Image Word Range Start Word */
  .skip_verify_end       = 0x1FE,                /* Skip Ram Image Word Range End Word */
  .pbs_info_place_holder = PM_PBS_INFO_IN_PERIPH, /* Place where PBS Info stored */
  .perph_base_addr       = 0x1600,               /* Periph BASE_ADDRESS */
  .trim_num              = 0x00,               /* trim_num  */
  .tp_rev                = 0x00,               /* tp_rev    */
  .fab_id                = 0x00,               /* fab_id    */
  .wafer_id              = 0x00,               /* wafer_id  */
  .x_co_ordi             = 0x00,               /* x_co_ordi */
  .y_co_ordi             = 0x00,               /* y_co_ordi */
  .lot_id                = 0x00,               /* lot_id_01_00 */
  .mfg_id                = 0x00,               /* mfg_id    */
};

pm_pbs_info_data_type*
pm_pbs_info_data[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_PMICS] = {
  {
    &pm_pbs_info_data_a,
    NULL, NULL, NULL, NULL, NULL, NULL, 
    &pm_pbs_info_data_h,
    NULL, NULL, NULL, NULL, NULL, NULL,
  }
};


/* max_num_seqs, ram_start_addr, poff_trig_id, poff_otp_addr, warmreset_trig_id, warmreset_otp_addr */
pm_pbs_custom_seq_data_type pbs_custom_seq_data_a = {2, 0x07DC, 3, 0x000C, 2, 0x0008};

/* max_num_seqs, ram_start_addr, poff_trig_id, poff_otp_addr, warmreset_trig_id, warmreset_otp_addr */
pm_pbs_custom_seq_data_type pbs_custom_seq_data_b = {33, 0x0554, 2, 0x0008, 7, 0x001C};
 
pm_pbs_custom_seq_data_type* pbs_custom_seq_data[] = 
{
   NULL,
   NULL,
   NULL,
   NULL,
};


const uint8 pm_periph_bitmap[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_SLAVE_IDS][PM_MAX_BITMAP_ENTRIES] =
{
  /* Primary SPMI Bus PMICs */
  {
    PM_AZURA_PERIPH_BITMAP,
    PM_BONEFISH_PERIPH_BITMAP,
    PM_V6_PERIPH_BITMAP,
    PM_V8_PERIPH_BITMAP,
    PM_SECO_PERIPH_BITMAP,
    PM_EMPTY_PERIPH_BITMAP,
    PM_EMPTY_PERIPH_BITMAP,
    PM_KOHALA_SCULPIN_PERIPH_BITMAP,
    PM_SECOJR_PERIPH_BITMAP,
    PM_SECOJR_PERIPH_BITMAP,
    PM_EMPTY_PERIPH_BITMAP,
    PM_EMPTY_PERIPH_BITMAP,
    PM_LEICA2_PERIPH_BITMAP,
    PM_LEICA2_PERIPH_BITMAP,
  }
};

/*key press in milli seconds for valid boot*/
pm_pwrkey_dbnc_chk_type pm_pon_pwrkey_dbnc_chk[] =
{
   {
      .chk_at = PM_PON_PWRKEY_DBNC_CHK_AT_CORE,  // check key press at
      .dbnc_time_msec = 400,                     // valid debounce time msec
      .sdam_dbnc_supported = TRUE,               // SDAM support for reading dbnc time
      .pmic_index = 0,                           // primary pmic index
      .min_pmic_rev = 1,                         // minimum revision of pmic supporting SDAM RTC VAL
      .sdam_periph_index = PM_SDAM_2,            // SDAM peripheral
      .sdam_key_press_offset = 26,               // MEM_026
      .sdam_key_release_offset = 30,             // MEM_030
   }
};


uint32 rpmh_drv_id [] = {(uint32)RSC_DRV_HLOS};

pm_qbg_tbat_cal_specific_data_type pm_qbg_tbat_cal_val = 
{
   .qbg_tbat_cal_fast_char = PM_ADC_CAL_ABX_CAL,
   .qbg_tbat_cal_xpm = PM_ADC_CAL_RATIO_CAL,
};

const pm_register_address_type
pm_tgt_sdam_base_address[] =
{
  [PMIC_A] = 0x7000,
  [PMIC_B] = 0x0,
  [PMIC_C] = 0x0,
  [PMIC_D] = 0x0,
  [PMIC_E] = 0x0,
  [PMIC_F] = 0x0,
  [PMIC_G] = 0x0,
  [PMIC_H] = 0x0,
  [PMIC_I] = 0x0,
  [PMIC_J] = 0x0,
  [PMIC_K] = 0x0,
  [PMIC_L] = 0x0,
  [PMIC_M] = 0x0,
  [PMIC_N] = 0x0,
  [PMIC_O] = 0x0,
};

uint32 num_of_sdam_pmics[] = {sizeof(pm_tgt_sdam_base_address) / sizeof(pm_tgt_sdam_base_address[0])};

pm_chg_2nd_batt_cfg pm_chg_2nd_batt =
{
  .gpio_id = PM_GPIO_12,
  .gpio_therm = PM_GPIO_6,
};

pm_config_data_kvp pm_common_config_data[] =
{
  PM_ADD_PROP_CONFIG(PM_PROP_LDO_NUM, num_of_ldo),
  PM_ADD_PROP_CONFIG(PM_PROP_SMPS_NUM, num_of_smps),
  PM_ADD_PROP_CONFIG(PM_PROP_GPIO_NUM, num_of_gpio),
  PM_ADD_PROP_CONFIG(PM_PROP_RTC_NUM, num_of_rtc),
  PM_ADD_PROP_CONFIG(PM_PROP_BOB_NUM, num_of_bob),
  PM_ADD_PROP_CONFIG(PM_PROP_VS_NUM, num_of_vs),
  PM_ADD_PROP_CONFIG(PM_PROP_LPG_NUM, num_of_lpg_chan),
  PM_ADD_PROP_CONFIG(PM_PROP_RGB_NUM, num_of_rgb),
  PM_ADD_PROP_CONFIG(PM_PROP_WLED_NUM,  num_of_wled),
  PM_ADD_PROP_CONFIG(PM_PROP_CHARGER_NUM, num_of_charger),
  PM_ADD_PROP_CONFIG(PM_PROP_BMD_NUM, num_of_bmd),
  PM_ADD_PROP_CONFIG(PM_PROP_COINCELL_NUM,  num_of_coincell),
  PM_ADD_PROP_CONFIG(PM_PROP_FG_NUM,  num_of_fg),
  PM_ADD_PROP_CONFIG(PM_PROP_IBB_NUM, num_of_ibb),
  PM_ADD_PROP_CONFIG(PM_PROP_LAB_NUM, num_of_lab),
  PM_ADD_PROP_CONFIG(PM_PROP_AB_NUM,  num_of_ab),
  PM_ADD_PROP_CONFIG(PM_PROP_OLEDB_NUM, num_of_oledb),
  PM_ADD_PROP_CONFIG(PM_PROP_VIB_NUM, num_of_vib),
  PM_ADD_PROP_CONFIG(PM_PROP_PBS_CORE,  num_of_pbs_core),
  PM_ADD_PROP_CONFIG(PM_PROP_HAPTICS_NUM, num_of_haptics),
  PM_ADD_PROP_CONFIG(PM_PROP_LCDB_NUM,  num_of_lcdb),
  PM_ADD_PROP_CONFIG(PM_PROP_PWM_NUM, num_of_pwm),
  PM_ADD_PROP_CONFIG(PM_PROP_SDAM_NUM,  num_of_sdam),
  PM_ADD_PROP_CONFIG(PM_PROP_PBS_INFO,  pm_pbs_info_data),
  PM_ADD_PROP_CONFIG(PM_PROP_VIB_DATA,  vib_specific),
  PM_ADD_PROP_CONFIG(PM_PROP_RPMH_DRV_ID, rpmh_drv_id),
  PM_ADD_PROP_CONFIG(PM_PROP_PERIPH_BITMAP, pm_periph_bitmap),
  PM_ADD_PROP_CONFIG(PM_PROP_OEM_PSI_WLIST_PERIPH_BITMAP, pm_oem_psi_whitelist_bitmap),
  PM_ADD_PROP_CONFIG(PM_PROP_SBL_SPECIFIC_DATA, sbl_specific_data),
  PM_ADD_PROP_CONFIG(PM_PROP_SDAM_ADDR_DATA,  pm_tgt_sdam_base_address),
  PM_ADD_PROP_CONFIG(PM_PROP_SDAM_PMICS_NUM,  num_of_sdam_pmics),
  PM_ADD_PROP_CONFIG(PM_PROP_LPG_SPECIFIC_DATA, lpg_specific),
  PM_ADD_PROP_CONFIG(PM_PROP_SWIRE_LUT, pm_swire_lut),
  PM_ADD_PROP_CONFIG(PM_PROP_RGB_SPECIFIC_DATA, &rgb_specific_data),
  PM_ADD_PROP_CONFIG(PM_PROP_HAPTICS_APP_CONFIG, &pm_haptics_config),
  PM_ADD_PROP_CONFIG(PM_PROP_PBS_CUSTOM_SEQ_DATA, pbs_custom_seq_data),
  PM_ADD_PROP_CONFIG(PM_PROP_LONG_PWRKEY_HOLD_BOOT_TIME,  pm_pon_pwrkey_dbnc_chk),
  PM_ADD_PROP_CONFIG(PM_PROP_QBG_EXT_RSNS_SCALE_LOCATION, &pm_ext_rsns_scale_location),
  PM_ADD_PROP_CONFIG(PM_PROP_QBG_TBAT_CAL_SPECIFIC_DATA, &pm_qbg_tbat_cal_val),
  PM_ADD_PROP_CONFIG(PM_PROP_RTC_APP_CONFIG, &pm_rtc_config),
  PM_ADD_PROP_CONFIG(PM_PROP_CHG_APP_CONFIG, &pm_chg_2nd_batt)
};


pm_err_flag_type
pm_config_common_data(  pm_config_data_kvp **common_config_data, 
                            uint32 *common_config_data_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  if ((common_config_data == NULL) || (common_config_data_size == NULL))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    *common_config_data = pm_common_config_data;
    *common_config_data_size = ((sizeof(pm_common_config_data))/(sizeof(pm_common_config_data[0])));
  }

  return err_flag;
}
