#ifndef PM_RGB_DRIVER__H
#define PM_RGB_DRIVER__H

/*! \file pm_rgb_driver.h
*  \n
*  \brief  This file contains functions prototypes and variable/type/constant
*         declarations for supporting rgb peripheral.
*
*  \n &copy; Copyright 2012-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/rgb/src/pm_rgb_driver.h#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/16/14   akm     Comm change Updates
03/31/14   akm     Updated to the latest PMIC driver architecture
03/04/13   aab     Created
========================================================================== */

/*===========================================================================
            INCLUDE FILES
===========================================================================*/
#include "pm_target_information.h"
#include "pm_sdam.h"

/*===========================================================================

                     RGB TYPES AND STRUCTURES

===========================================================================*/

#define PPG_CH1    0
#define PPG_CH2    1
#define PPG_CH3    2

typedef struct
{
  pm_register_address_type peripheral_offset;
  pm_register_address_type src_sel;             //0x045
  pm_register_address_type en_ctl;              //0x046
  pm_register_address_type chgr_led_config;     //0x058
} pm_rgb_register_info_type;


typedef struct
{
  pm_comm_info_type          *comm_ptr;
  pm_rgb_register_info_type  *rgb_reg_table;
  pm_register_address_type    base_address;
  uint8                       num_of_peripherals;
  uint8                       sub_type;
  uint8                       dig_maj_min_ver;
} pm_rgb_data_type;

typedef struct {
  uint8 ppg1_lut_en;
  uint8 pattern_config;
  uint8 high_index;
  uint8 low_index;
  uint8 high_multiplier;
  uint8 low_multiplier;
  uint8 ppg2_lut_en;    
}pm_ppg_config_type;

typedef struct
{
  uint8              clock;
  uint8              pre_div;
  uint8              exp;
  uint8              bit_size;
  uint8              ramp_step_duration;
  uint8              ramp_step_sdam_offset;
  uint8              ppg_sdam_pmic;
  uint8              ppg1_sdam;
  uint8              ppg2_sdam;
  boolean            is_ppg_sdam_trig_supported;
  uint16             ppg_rgb_dim_level_max;
  pm_ppg_config_type sdam_mem_offsets[3];
  pm_ppg_config_type config_values;
  uint8              ppg_pwm_ch[3];
  uint8              ppg_pmic;
}pm_rgb_specific_data_type;

/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void pm_rgb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index);

pm_rgb_data_type* pm_rgb_get_data(uint32 pmic_index);

uint8 pm_rgb_get_num_peripherals(uint32 pmic_index);

#endif // PM_RGB_DRIVER__H

