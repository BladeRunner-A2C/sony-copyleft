#ifndef __PM_SCPQ_HS_MISC_H__
#define __PM_SCPQ_HS_MISC_H__

/*! \file
 *  \n
 *  \brief  pm_scpq_hs_misc.h PMIC-SCPQ MODULE RELATED DECLARATION 
 *  \details  This header file contains functions and variable declarations 
 *  to support Qualcomm PMIC SCPQ OTG (Switch-Mode Battery Charger) module. The 
 *  Switched-Mode Battery Charger (SCPQ OTG) module includes a buck regulated 
 *  battery charger with integrated switches. The SCPQ OTG module, along with the 
 *  Over Voltage Proection (OVP) module will majorly be used by charger 
 *  appliation for charging Li-Ion batteries with high current (up to 2A).
 *  \n &copy;
 *  Copyright (c) 2022,2023 Qualcomm Technologies, Inc. All rights reserved.
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
01/19/23    rs    Initial revision
========================================================================== */
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

typedef enum 
{
  PM_SCPQ_HS_MISC_POWER_PATH__NONE,
  PM_SCPQ_HS_MISC_POWER_PATH__BATTERY,
  PM_SCPQ_HS_MISC_POWER_PATH__USBIN,
  PM_SCPQ_HS_MISC_POWER_PATH__DCIN,
  PM_SCPQ_HS_MISC_POWER_PATH__INVALID
}pm_scpq_hs_misc_pwr_pth_type;


typedef struct {
  boolean thermreg_disabled;         // all 3 temperature monitoring sources (skin, die, junction) are disabled 
  boolean temp_below_range;          // when high, indicates skin, die or junction temperature below temp_1 level
  boolean temp_within_range;         // when high, indicates skin, die or junction temperature between temp_1 level and temp_2 level
  boolean temp_above_range;          // when high, indicates skin, die or junction temperature between temp_2 level and temp_3 level
  boolean alert_level;               // when high, indicates skin, die or junction temperature above temp_3 level
  boolean tlim;                      // when high, indicates junction temp above 140c
  boolean therm_range_active;        // 0 = no thermal regulation, 1 = thermal regulation of icl and/or input voltage (qc)
  boolean therm_range_status_7;      // reserved 
}pm_scpq_hs_misc_temp_range_status; 

typedef struct {
  boolean aicl_done;                 // Aicl Done
  boolean aicl_fail;                 // Aicl Fail
  boolean icl_imin;                  // ICL has collapsed down to ICLmin
  boolean dcin_ch_collapse;          // DC Input Collapse (dg)
  boolean usbin_ch_collapse;         // USB Input Collapse (dg)
  boolean highest_dc;                // Switcher in High Duty Cycle
  boolean soft_limit;                // Switcher Hard/Soft Limiting
  boolean aicl_status_7;             // tbd-reserved 
}pm_scpq_hs_misc_aicl_status;

typedef enum {
  PM_SCPQ_HS_CHGR_BARK,
  PM_SCPQ_HS_CHGR_BITE,
  PM_SCPQ_HS_CHGR_BARK_BITE_INVALID,
}pm_scpq_hs_misc_wdog_status;

typedef struct {
  boolean wdog_timer_en;                  //Watchdog time enable/disable, bit0
  boolean wdog_timer_en_on_plugin;        //All three watchdog timers enable/disable during plugin, bit1
  boolean bark_wdog_int_en;               //BARK watchdog timer expire interrupt enable/disable, bit4
  boolean bite_wdog_int_en;               //BITE watchdog timre expire interrupt enable/disable, bit5
  boolean bite_wdog_disable_charging_cfg; //Controls charging enable/disable after Bite wd timer expires, bit7
}pm_scpq_hs_misc_wdog_cfg_type;

typedef enum {
  PM_SCPQ_HS_MISC_AICL_CFG_TREG_ALLOW_DECREASE,  // allow decrease during thermal regulation even if increase was due to high duty cycle
  PM_SCPQ_HS_MISC_AICL_CFG_AICL_HIGH_DC_INC,     //allow aicl to increment input current limit even during high duty cycle
  PM_SCPQ_HS_MISC_AICL_CFG_INVALID
}pm_scpq_hs_misc_aicl_cfg;

typedef enum
{
  PM_SCPQ_HS_MISC_AICL_CMD_RERUN_AICL,
  PM_SCPQ_HS_MISC_AICL_CMD_RESTART_AICL,
  PM_SCPQ_HS_MISC_AICL_CMD_RESTART_THERMAL,
  PM_SCPQ_HS_MISC_AICL_CMD_INVALID
}pm_scpq_hs_misc_aicl_cmd_type;

typedef enum {
  PM_SCPQ_HS_MISC_AICL_RERUN_TIME_3S,
  PM_SCPQ_HS_MISC_AICL_RERUN_TIME_12S,
  PM_SCPQ_HS_MISC_AICL_RERUN_TIME_45S,
  PM_SCPQ_HS_MISC_AICL_RERUN_TIME_3M,
  PM_SCPQ_HS_MISC_AICL_RERUN_TIME_CFG_INVALID, //Invalid
}pm_scpq_hs_misc_aicl_rerun_time_cfg;

typedef enum
{
  PM_SCPQ_HS_MISC_BUCKBOOST_REFRESH_PULSE_1_IN_8,
  PM_SCPQ_HS_MISC_BUCKBOOST_REFRESH_PULSE_1_IN_4,
  PM_SCPQ_HS_MISC_BUCKBOOST_REFRESH_PULSE_INVALID,
}pm_scpq_hs_misc_buckboost_refresh_pulse_type;


typedef enum
{
  PM_SCPQ_HS_MISC_SKIN_ADC_CFG,  //1 TO USE AUX THERM PIN FOR BATTERY TEMPERATURE DETECTION (jeita), 0 FOR SKIN TEMP DETECTION
  PM_SCPQ_HS_MISC_SKIN_ADC_SRC_EN,
  PM_SCPQ_HS_MISC_WLS_ADC_SRC_EN = PM_SCPQ_HS_MISC_SKIN_ADC_SRC_EN, 
  PM_SCPQ_HS_MISC_THERMREG_CONNECTOR_ADC_SRC_EN,
  PM_SCPQ_HS_MISC_THERMREG_USB_CONN_ADC_SRC_EN = PM_SCPQ_HS_MISC_THERMREG_CONNECTOR_ADC_SRC_EN,
  PM_SCPQ_HS_MISC_THERMREG_SMB_ADC_SRC_EN,
  PM_SCPQ_HS_MISC_THERM_SRC_CFG_RESERVED,  //Reserved bit 4
  PM_SCPQ_HS_MISC_DIE_ADC_SRC_EN,
  PM_SCPQ_HS_MISC_DIE_CMP_SRC_EN,
  PM_SCPQ_HS_MISC_THERMREG_SW_ICL_ADJUST,  //only software thermal regulation allowed
  PM_SCPQ_HS_MISC_THERM_SRC_CFG_INVALID,
}pm_scpq_hs_misc_therm_src_cfg_type;


typedef enum 
{
  PM_SCPQ_HS_MISC_VIN_DIV16_MUX_SEL_USB_SNS,
  PM_SCPQ_HS_MISC_VIN_DIV16_MUX_SEL_USB_IN,
  PM_SCPQ_HS_MISC_VIN_DIV16_MUX_SEL_WLS_SNS,
  PM_SCPQ_HS_MISC_VIN_DIV16_MUX_SEL_WLS_IN,
  PM_SCPQ_HS_MISC_VIN_DIV16_MUX_SEL_INVALID
} pm_scpq_hs_misc_vin_div16_mux_sel_type;

typedef enum {
  PM_SCPQ_HS_MISC_IRQ_WDOG_SNARL,             //Generated when SNARL watchdog timer expires
  PM_SCP_HS_MISC_IRQ_SMB_EN = PM_SCPQ_HS_MISC_IRQ_WDOG_SNARL,
  PM_SCPQ_HS_MISC_IRQ_WDOG_BARK,              //Generated when BARK watchdog timer expires 
  PM_SCPQ_HS_MISC_IRQ_X2D2_EN = PM_SCPQ_HS_MISC_IRQ_WDOG_BARK,
  PM_SCPQ_HS_MISC_IRQ_AICL_FAIL,              //AICL Fail
  PM_SCPQ_HS_MISC_IRQ_AICL_DONE,              //AICL Done
  PM_SCPQ_HS_MISC_IRQ_IMP_TRIGGER_EN,         //Input Missing Poller trigger
  PM_SCPQ_HS_MISC_IRQ_ALL_CHNL_CONV_DONE,     //All channel down
  PM_SCPQ_HS_MISC_IRQ_TEMPERATURE_CHANGE,     //Change in temperature die or skin
  PM_SCPQ_HS_MISC_IRQ_TEMPERATURE_CHANGE_SMB, //temperature change in SMB
  PM_SCPQ_HS_MISC_IRQ_INVALID,                //Invalid
}pm_scpq_hs_misc_irq_type; 



/*===========================================================================

                 SCPQ HS MISC DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/**
 * @brief This function enables selected misc aicl cmd
 * 
 * @details
 *  This function enables selected misc aicl cmd
 *  AICL_CMD register is write only and only affect when setting each command bit to 1, so default to enable
 * 
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[in] aicl_cmd:      Refer #pm_scpq_hs_misc_aicl_cmd_type for details.
 *                                
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_hs_misc_aicl_cmd_enable(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_aicl_cmd_type cmd);


/**
 * @brief This API sets ADC Channel ID for Battery Thermistor
 *
 * @details
 *  This API sets ADC Channel ID for Battery Thermistor
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] channel_id:         Channel id.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_hs_misc_set_batt_therm_ch_id_cfg(uint32 bus_id, uint32 pmic_index, uint8 channel_id);

/**
 * @brief This API gets ADC Channel ID for Battery Thermistor
 *
 * @details
 *  This API gets ADC Channel ID for Battery Thermistor
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] channel_id:         Channel id.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_hs_misc_get_batt_therm_ch_id_cfg(uint32 bus_id, uint32 pmic_index, uint8* channel_id);

/**
 * @brief This API sets MUX for VIN ADC Channel
 *
 * @details
 *  This API sets MUX value for VIN ADC Channel. 
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] vin_mux_sel:        The Mux value to select the VIN SRC type before reading the ADC Channel.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_hs_misc_set_vin_adc_mux_sel(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_vin_div16_mux_sel_type vin_mux_sel);


/**
 * @brief Enable or disable therm channel 
 *
 * @details
 *  Enable or disable therm channel.
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] enable:             TRUE --- Enable therm channel. FALSE --- Disable therm channel.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_hs_misc_batt_therm_ch_enable(uint32 bus_id, uint32 pmic_index, boolean enable);

/**
 * @brief This function configures the timeout selection of bark for charger watchdog
 * 
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index: The pmic_index of charger module.
 * @param[in] timeout_ms: Timeout value in the unit of ms.
 *                                
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_scpq_hs_misc_set_wd_bark_timeout(uint32 bus_id, uint32 pmic_index, uint32 timeout_ms);

/**
 * @brief This function returns the charger watchdog config
 * 
 * @details
 *  This function returns the charger watchdog config
 * 
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[in] chgr_wd_cfg:  Refer #pm_scpq_hs_misc_wdog_cfg_type for details.
 *                                
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_hs_misc_get_config_wdog(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_wdog_cfg_type *chgr_wd_cfg);

/**
 * @brief This function configures the charger watchdog
 * 
 * @details
 *  This function configures the charger watchdog
 * 
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[in] chgr_wd_cfg:  Refer #pm_scpq_hs_misc_wdog_cfg_type for details.
 *                                
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_hs_misc_config_wdog(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_wdog_cfg_type chgr_wd_cfg);

/**
 * @brief Writing to this register will pet (reset) BARK and BITE watchdog timers
 *
 * @details
 *  Writing to this register will pet (reset) BARK and BITE watchdog timers
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:  The pmic_index of charger module.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_hs_misc_bark_bite_wdog_pet(uint32 bus_id, uint32 pmic_index);


/**
 * @brief API to get the MISC IRQ Status 
 *
 * @details
 *  this function gives the IRQ status 
 *
 * @param[in] bus_id:   SPMI Bus id 
 * @param[in] pmic_index:  The pmic_index of charger module.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_hs_misc_irq_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_irq_type irq, pm_irq_status_type type, boolean *status);

#endif /* __PM_SCPQ_HS_MISC_H__*/
