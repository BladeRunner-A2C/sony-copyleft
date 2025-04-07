/*! \file
*
*  \brief  pm_scpq_hs_null.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2022,2023 Qualcomm Technologies, Inc. All rights reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    -------------------------------------------------------------
=============================================================================== */

/*=============================================================================

                    INCLUDE FILES

===============================================================================*/
#include "pm_scpq_hs_driver.h"
#include "pm_scpq_hs_usb.h"
#include "pm_scpq_hs_chgr.h"
#include "pm_scpq_hs_typec.h"
#include "pm_scpq_hs_dcdc.h"
#include "pm_scpq_hs_batif.h"
#include "pm_scpq_hs_misc.h"
/*===========================================================================
                      MACRO DECLARATIONS
===========================================================================*/

pm_err_flag_type pm_scpq_hs_usb_get_typec_vbus_status(uint32 bus_id, uint32 pmic_index, boolean *vbus_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_get_chgr_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_chgr_status_type *chgr_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_enable_charging(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_get_apsd_result_status(uint32 bus_id, uint32 pmic_index, pm_chg_charger_port_type *apsd_result)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_typec_get_port_role(uint32 bus_id, uint32 pmic_index, pm_chg_typec_port_role_type *port_role)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_get_typec_status(uint32 bus_id, uint32 pmic_index, pm_chg_typec_status_type *typec_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_dcdc_get_power_path_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_dcdc_power_path_status *power_path_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_set_float_volt(uint32 bus_id, uint32 pmic_index, uint32 float_volt_mv)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_configure_vsysmin(uint32 bus_id, uint32 pmic_index, uint32 vsysmin_mv)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_set_charge_current(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_chgr_current_type charge_current_type, uint32 current_in_ma)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_set_usbin_suspend(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_usb_suspend_type usb_suspend_cfg, boolean set_value)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_vph_track_threshold_sel(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_chgr_vph_track_sel_type track_sel)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_set_batt_therm_ch_id_cfg(uint32 bus_id, uint32 pmic_index, uint8 channel_id)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_batif_jeita_en_cfg(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_cfg_type jeita_cfg_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_batif_set_jeita_threshold_value(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_threshold_type threshold_type, uint32 jeita_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_batif_get_jeita_threshold_value(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_threshold_type threshold_type, uint16* jeita_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_batif_cfg_batt_missing_src(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_batif_bat_miss_src_cfg_type bat_miss_cfg, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_typec_get_dam_connect_sts(uint32 bus_id, uint32 pmic_index, boolean *ConnectSts)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_dcdc_get_icl_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_dcdc_icl_status_type *icl_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_configure_usb_icl_options(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_icl_options_type icl_options, boolean set_value)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_enable_icl_override_after_apsd(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_set_icl_cfg(uint32 bus_id, uint32 pmic_index, uint32 usbin_current_limit)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_aicl_options_cfg(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_aicl_cfg_type aicl_cfg_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_get_vsysmin_cfg(uint32 bus_id, uint32 pmic_index, uint32* vsysmin_mv)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_get_float_volt_cfg(uint32 bus_id, uint32 pmic_index, uint32 *float_volt_mv)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_get_charge_current_cfg(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_chgr_current_type charge_current_type, uint32* current_in_ma)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_get_bat_2s_chg_cfg(uint32 bus_id, uint32 pmic_index, boolean* is_2s_bat)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr2_get_bat_2s_chg_cfg(uint32 bus_id, uint32 pmic_index, boolean* is_2s_bat)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_get_apsd_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_apsd_status_type apsd_status_type, boolean *result)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_aicl_cmd_enable(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_aicl_cmd_type cmd)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_get_batt_therm_ch_id_cfg(uint32 bus_id, uint32 pmic_index, uint8* channel_id)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_set_input_priority(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_input_priority_type priority)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_typec_set_dam_icl(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_typec_dam_icl_sel icl_sel)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_set_vin_adc_mux_sel(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_vin_div16_mux_sel_type vin_mux_sel)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_bark_bite_wdog_pet(uint32 bus_id, uint32 pmic_index)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_vph_prechg_alg_en(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_set_wd_bark_timeout(uint32 bus_id, uint32 pmic_index, uint32 timeout_ms)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_get_scpq_hs_pmic_info(uint32 bus_id,uint32 *pmic_index, uint32 *slave_id, uint32* charger_count, uint32 max_charger)
{
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_scpq_hs_misc_batt_therm_ch_enable(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_irq_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_irq_type irq, pm_irq_status_type type, boolean *status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_dcdc_get_otg_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_dcdc_otg_status_type* otg_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_chgr_get_scpq_pmic_info(uint32 bus_id, uint32 *pmic_index, uint32 *slave_id, uint32* charger_count, uint32 max_charger)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_set_wd_bark_timeout(uint32 bus_id, uint32 pmic_index, uint32 timeout_ms)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_get_config_wdog(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_wdog_cfg_type *chgr_wd_cfg)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_config_wdog(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_wdog_cfg_type chgr_wd_cfg)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_bark_bite_wdog_pet(uint32 bus_id, uint32 pmic_index)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_misc_irq_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_irq_type irq, pm_irq_status_type type, boolean *status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_wls_irq_status(uint32 bus_id, uint32 pmic_index)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_scpq_hs_usb_rerun_apsd(uint32 bus_id, uint32 pmic_index, boolean rerun)
{
  return PM_ERR_FLAG_SUCCESS;	
}

pm_err_flag_type pm_scpq_hs_usb_apsd_enable(uint32 bus_id, uint32 pmic_index, uint8 apsd_start_detect, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;	
}

