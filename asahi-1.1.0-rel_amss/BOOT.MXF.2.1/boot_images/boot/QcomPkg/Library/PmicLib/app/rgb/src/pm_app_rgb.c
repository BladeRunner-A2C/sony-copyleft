/*! \file
*  
*  \brief  pm_app_rgb.c
*  \details Implementation file for rgb led resourece type.
*
*  &copy; Copyright 2013-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/app/rgb/src/pm_app_rgb.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
0/15/20    xp      Refine parameter of RGB app APIs
05/01/18   pxm     Fixed rgb_led_state array out of bound issue
02/29/17   sv      Added pm_rgb_get_pmic_index API
05/01/17   aab     Updated pm_rgb_led_config() to use max/min dim level config data
05/17/15   aab     Updated LPG Channel assignment to support 8998 target
03/31/15   aab     Added a call to select PWM source: pm_lpg_pwm_src_select()
06/24/14   aab     Cleaned up and added support for PMI8994
03/13/13   aab     Creation
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "pm_app_rgb.h"
#include "pm_rgb_driver.h"
#include "pm_target_information.h"
#include "pm_pwm.h"

#define LED_ENABLE  1
#define LED_DISABLE 0
#define CH_DIS_BIT  0

#define PBS_TRIG_SET_ADDR   0x84E5
#define PBS_TRIG_CLR_ADDR   0x84E6
#define PBS_TRIG_ARG        0x1

#define PBS_ARG_MEM_002     0x2

#define ONE_BYTE        0x1

#define MAX_NUM_LED     0x3

static boolean rgb_led_state[MAX_NUM_LED] =
{
  [PPG_CH1] = LED_DISABLE, 
  [PPG_CH2] = LED_DISABLE, 
  [PPG_CH3] = LED_DISABLE
};

static pm_err_flag_type pm_rgb_config_pwm(pm_app_rgb_config_type *rgb_config);
static pm_err_flag_type pm_rgb_blink_config(uint8 led_ch, pm_rgb_specific_data_type *cfg);

pm_err_flag_type pm_rgb_led_blink(uint32 rgb_mask, uint32 dim_level)
{
  pm_app_rgb_config_type rgb_config =
                                    {
                                      .rgb_state  = PM_RGB_STATE_BLINK,
                                      .rgb_mask   = rgb_mask,
                                      .dim_level  = dim_level
                                    };
  return pm_rgb_config_pwm(&rgb_config);
}

pm_err_flag_type pm_rgb_led_config(uint32 rgb_mask, uint32 dim_level, boolean enable_rgb) 
{
  pm_rgb_state_type rgb_state = (enable_rgb) ? PM_RGB_STATE_GLOW : PM_RGB_STATE_OFF;
  pm_app_rgb_config_type rgb_config =
                                    {
                                      .rgb_state  = rgb_state,
                                      .rgb_mask   = rgb_mask,
                                      .dim_level  = dim_level
                                    };
  return pm_rgb_config_pwm(&rgb_config);
}

static pm_err_flag_type pm_rgb_config_pwm(pm_app_rgb_config_type *rgb_config)
{
  pm_err_flag_type err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_pwm_resource_type led_channel = PM_PWM_RESOURCE_PWM_1;
  uint32 led = 0, dim_level = 0, rgb_mask = 0;
  uint8 ch_dis_bit = CH_DIS_BIT;
  pm_rgb_state_type rgb_state = 0;
  uint8 pos_i = 0;
  static pm_rgb_specific_data_type *cfg_ptr = NULL;

  if(cfg_ptr == NULL)
  {
    cfg_ptr = (pm_rgb_specific_data_type *)pm_target_information_get_specific_info(PM_PROP_RGB_SPECIFIC_DATA);
  }

  if (cfg_ptr == NULL || rgb_config == NULL)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  //continue bootup with real battery if RGB peripheral is not present
  pm_rgb_data_type *rgb_data_ptr = pm_rgb_get_data(cfg_ptr->ppg_pmic);
  if(NULL == rgb_data_ptr)
  {
    return PM_ERR_FLAG_SUCCESS;
  }

  dim_level = rgb_config->dim_level;
  rgb_mask = rgb_config->rgb_mask;
  rgb_state = rgb_config->rgb_state;

  while (rgb_mask & PM_RGB_SEGMENT_ALL)
  {
    led = (1 << pos_i);

    if (rgb_mask & led)
    {
      led_channel = cfg_ptr->ppg_pwm_ch[pos_i];

      switch (rgb_state)
      {
        case PM_RGB_STATE_OFF:
        {
          rgb_led_state[pos_i] = FALSE;

          err_flag |= pm_pwm_enable_pwm(cfg_ptr->ppg_pmic, led_channel, FALSE);

          err_flag |= pm_rgb_enable(cfg_ptr->ppg_pmic, led, LED_DISABLE);

          err_flag |= pm_sdam_mem_write(cfg_ptr->ppg_sdam_pmic, cfg_ptr->ppg1_sdam, cfg_ptr->sdam_mem_offsets[pos_i].ppg1_lut_en, ONE_BYTE, &ch_dis_bit);

          if (cfg_ptr->is_ppg_sdam_trig_supported)
          {
            if (rgb_led_state[PPG_CH1] == FALSE && rgb_led_state[PPG_CH2] == FALSE && rgb_led_state[PPG_CH3] == FALSE)
            {
              err_flag |= pm_comm_write_byte(cfg_ptr->ppg_sdam_pmic, PBS_TRIG_CLR_ADDR, 0x1);
            }
          }
        }
        break;

        case PM_RGB_STATE_BLINK:
        case PM_RGB_STATE_GLOW:
        {
          err_flag |= pm_rgb_enable(cfg_ptr->ppg_pmic, led, LED_ENABLE);

          if (rgb_state == PM_RGB_STATE_BLINK)
          {
            err_flag |= pm_rgb_blink_config(led_channel, cfg_ptr);
          }

          //config clock, pwm_freq_pre_div, pwm_lsb_msb, enable, pwm_sync     
          err_flag |= pm_pwm_clock_config(cfg_ptr->ppg_pmic, led_channel, cfg_ptr->bit_size, cfg_ptr->clock, cfg_ptr->pre_div, cfg_ptr->exp);

          err_flag |= pm_pwm_set_pwm_value(cfg_ptr->ppg_pmic, led_channel, dim_level);

          err_flag |= pm_pwm_enable_pwm(cfg_ptr->ppg_pmic, led_channel, TRUE);

          rgb_led_state[pos_i] = TRUE;
        }
        break;

        default:
          return PM_ERR_FLAG_INVALID_PARAMETER;
      }

      if (cfg_ptr->is_ppg_sdam_trig_supported)
      {
        err_flag |= pm_comm_write_byte(cfg_ptr->ppg_sdam_pmic, PBS_TRIG_SET_ADDR, 0x1);
      }
    }

    rgb_mask = rgb_mask & (~led);
    pos_i++;
  }

  return err_flag;
}

static pm_err_flag_type
pm_rgb_blink_config(uint8 led_ch, pm_rgb_specific_data_type *cfg)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 pbs_arg = PBS_TRIG_ARG;

  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg1_sdam, PBS_ARG_MEM_002, ONE_BYTE, &pbs_arg);

  /* Ramp Step Duration = 7.8ms * cfg->ramp_step_duration */
  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg1_sdam, cfg->ramp_step_sdam_offset, ONE_BYTE, &cfg->ramp_step_duration);

  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg1_sdam, cfg->sdam_mem_offsets[led_ch].ppg1_lut_en, ONE_BYTE, &cfg->config_values.ppg1_lut_en);

  /* Pattern Config; Bit 3:Enable Looping, Bit 1: Enable pause hi, Bit 0: Enable pause low */
  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg1_sdam, cfg->sdam_mem_offsets[led_ch].pattern_config, ONE_BYTE, &cfg->config_values.pattern_config);
  
  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg1_sdam, cfg->sdam_mem_offsets[led_ch].high_index, ONE_BYTE, &cfg->config_values.high_index);

  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg1_sdam, cfg->sdam_mem_offsets[led_ch].low_index, ONE_BYTE, &cfg->config_values.low_index);

  /* Pause_hi_multiplier = 5, If EN_PAUSE_HI = 1, pattern will remain at PWM value located START_INDEX for STEP_DURATION time * (1+PAUSE_HI) Maximum 254*/
  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg1_sdam, cfg->sdam_mem_offsets[led_ch].high_multiplier, ONE_BYTE, &cfg->config_values.high_multiplier);
  
  /* Pause_lo_multiplier = 5, If EN_PAUSE_LO = 1, pattern will remain at PWM value located END_INDEX for STEP_DURATION time * (1+PAUSE_LO) Maximum 254 */
  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg1_sdam, cfg->sdam_mem_offsets[led_ch].low_multiplier, ONE_BYTE, &cfg->config_values.low_multiplier);
  
  err_flag |= pm_sdam_mem_write(cfg->ppg_sdam_pmic, cfg->ppg2_sdam, cfg->sdam_mem_offsets[led_ch].ppg2_lut_en, ONE_BYTE, &cfg->config_values.ppg2_lut_en);
          
  return err_flag;
}
