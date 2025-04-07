#include "pm_schg_batif.h"
#include "pm_schg_chgr.h"
#include "pm_schg_dcdc.h"
#include "pm_schg_misc.h"
#include "pm_schg_typec.h"
#include "pm_schg_usb.h"

pm_err_flag_type pm_schg_batif_enable_shipmode(uint32 bus_id, uint32 pmic_index)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_irq_enable(uint32 bus_id, uint32 pmic_index, pm_schg_batif_irq_type irq, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_irq_clear(uint32 bus_id, uint32 pmic_index, pm_schg_batif_irq_type irq)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_irq_set_trigger(uint32 bus_id, uint32 pmic_index, pm_schg_batif_irq_type irq, pm_irq_trigger_type trigger)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_irq_status(uint32 bus_id, uint32 pmic_index, pm_schg_batif_irq_type irq, pm_irq_status_type type, boolean *status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_set_low_batt_detect_threshold(uint32 bus_id, uint32 pmic_index, pm_schg_batif_low_battery_threshold lbt_cfg)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_cfg_batt_missing_src(uint32 bus_id, uint32 pmic_index, pm_schg_batif_bat_miss_src_cfg_type bat_miss_cfg, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batt_missing_status(uint32 bus_id, uint32 pmic_index, pm_schg_batif_bat_miss_status_type status_type, boolean *st)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_batif_enable_fake_bat_detect(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_enable_src(uint32 bus_id, uint32 pmic_index, boolean chg_en_src)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_chg_polarity_low(uint32 bus_id, uint32 pmic_index, boolean chg_pol_low)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_charge_current(uint32 bus_id, uint32 pmic_index, pm_schg_chgr_current_type charge_current_type, uint32 current)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_enable_charging(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_get_chgr_status(uint32 bus_id, uint32 pmic_index, pm_schg_chgr_status_type *charger_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_float_volt(uint32 bus_id, uint32 pmic_index, uint32 float_volt_mv)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_jeita_fvcomp_cfg(uint32 bus_id, uint32 pmic_index, uint32 fv_comp_hot, uint32 fv_comp_cold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_jeita_ccomp(uint32 bus_id, uint32 pmic_index, uint32 ccomp_hot, uint32 ccomp_cold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_set_jeita_threshold_value(uint32 bus_id, uint32 pmic_index, pm_schg_chgr_jeita_threshold_type threshold_type, uint32 jeita_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_get_jeita_threshold_value(uint32 bus_id, uint32 pmic_index, pm_schg_chgr_jeita_threshold_type threshold_type, uint16* jeita_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_jeita_en_cfg(uint32 bus_id, uint32 pmic_index, pm_schg_chgr_jeita_cfg_type jeita_cfg_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_chgr_get_schg_pmic_info(uint8 bus_id, uint32 *pmic_index, uint32 *slave_id, uint32 *charger_count, uint32 max_charger)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_otg_enable(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_config_otg(uint32 bus_id, uint32 pmic_index, pm_schg_dcdc_otg_cfg_type otg_cfg_type, boolean set_value)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_set_otg_current_limit(uint32 bus_id, uint32 pmic_index, uint32 otg_limit_ma)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_get_otg_status(uint32 bus_id, uint32 pmic_index, pm_schg_dcdc_otg_status_type *otg_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_get_icl_status(uint32 bus_id, uint32 pmic_index, pm_schg_dcdc_icl_status_type *icl_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_configure_vsysmin(uint32 bus_id, uint32 pmic_index, uint32 vsysmin_mv)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_set_ref_max_psns(uint32 bus_id, uint32 pmic_index, uint32 current_mA)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_dcdc_get_power_path_status(uint32 bus_id, uint32 pmic_index, pm_schg_dcdc_power_path_status *power_path_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_irq_enable(uint32 bus_id, uint32 pmic_index, pm_schg_misc_irq_type irq, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_irq_clear(uint32 bus_id, uint32 pmic_index, pm_schg_misc_irq_type irq)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_irq_set_trigger(uint32 bus_id, uint32 pmic_index, pm_schg_misc_irq_type irq, pm_irq_trigger_type trigger)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_irq_status(uint32 bus_id, uint32 pmic_index, pm_schg_misc_irq_type irq, pm_irq_status_type type, boolean *status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_get_sysok_reason(uint32 bus_id, uint32 device_index, pm_schg_misc_sysok_reason_type *sysok_reason)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_get_misc_wdog_status(uint32 bus_id, uint32 device_index, pm_schg_misc_wdog_status *misc_wdog_sts)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_en_afp(uint32 bus_id, uint32 pmic_index)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_bark_bite_wdog_pet(uint32 bus_id, uint32 pmic_index)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_config_wdog(uint32 bus_id, uint32 pmic_index, pm_schg_misc_wdog_cfg_type misc_wd_cfg)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_get_config_wdog(uint32 bus_id, uint32 pmic_index, pm_schg_misc_wdog_cfg_type *misc_wd_cfg)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_set_snarl_bark_bite_wd_cfg(uint32 bus_id, uint32 pmic_index, pm_schg_misc_sbb_wd_cfg misc_wd_sbb_cfg)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_get_snarl_bark_bite_wd_cfg(uint32 bus_id, uint32 pmic_index, pm_schg_misc_sbb_wd_cfg *misc_wd_sbb_cfg)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_set_aicl_rerun_time_cfg(uint32 bus_id, uint32 pmic_index, pm_schg_misc_aicl_rerun_time_cfg aicl_rerun_time)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_set_thermreg_src_cfg(uint32 bus_id, uint32 device_index, pm_schg_misc_therm_src_cfg_type src_cfg_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_set_die_temp_thresholds(uint32 bus_id, uint32 device_index, int32 hot_threshold, int32 too_hot_threshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_misc_aicl_cmd(uint32 bus_id, uint32 device_index, pm_schg_misc_aicl_cmd_type cmd)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_typec_status(uint32 bus_id, uint32 pmic_index, pm_chg_typec_status_type *typec_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_typec_vbus_status(uint32 bus_id, uint32 pmic_index, boolean *vbus_status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_typec_vconn_enable(uint32 bus_id, uint32 pmic_index, pm_schg_usb_typec_vconn_enable_type enable_type)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_typec_get_port_role(uint32 bus_id, uint32 pmic_index, pm_chg_typec_port_role_type *port_role)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_typec_set_port_role(uint32 bus_id, uint32 pmic_index, pm_chg_typec_port_role_type port_role)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_typec_disable(uint32 bus_id, uint32 pmic_index, boolean disable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_typec_enable_try_sink_mode(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_typec_en_dbg_access_snk(uint32 bus_id, uint32 pmic_index, boolean EnDbgAccessSnk)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_typec_en_fmb(uint32 bus_id, uint32 pmic_index, boolean EnFmb)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_typec_get_dam_connect_sts(uint32 bus_id, uint32 pmic_index, boolean *ConnectSts)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_typec_set_dam_icl(uint32 bus_id, uint32 pmic_index, pm_schg_usb_typec_dam_icl_sel icl_sel)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_irq_enable(uint32 bus_id, uint32 pmic_index, pm_schg_usb_irq_type irq, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_irq_clear(uint32 bus_id, uint32 pmic_index, pm_schg_usb_irq_type irq)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_irq_set_trigger(uint32 bus_id, uint32 pmic_index, pm_schg_usb_irq_type irq, pm_irq_trigger_type trigger)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_irq_status(uint32 bus_id, uint32 pmic_index, pm_schg_usb_irq_type irq, pm_irq_status_type type, boolean *status)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_set_usbin_adptr_allowance(uint32 bus_id, uint32 pmic_index, pm_schg_usb_usbin_adapter_allowance_type adptr_allowance)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_usbin_adptr_allowance(uint32 bus_id, uint32 pmic_index, pm_schg_usb_usbin_adapter_allowance_type *adptr_allowance)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_apsd_status(uint32 bus_id, uint32 pmic_index, pm_schg_usb_apsd_status_type apsd_status, boolean *result)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_apsd_result_status(uint32 bus_id, uint32 pmic_index, pm_chg_charger_port_type *apsd_result)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_configure_usbin_icl_options(uint32 bus_id, uint32 pmic_index, pm_schg_usb_icl_options_type icl_options, boolean set_value)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_set_usbin_current_limit_cfg(uint32 bus_id, uint32 pmic_index, uint32 usbin_current_limit)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_rerun_apsd(uint32 bus_id, uint32 pmic_index)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_set_usbin_option1_cfg(uint32 bus_id, uint32 pmic_device, pm_schg_usb_usbin_options_1_cfg usbin_cfg, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_set_usbin_suspend(uint32 bus_id, uint32 pmic_index, boolean set_value)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_aicl_options_cfg(uint32 bus_id, uint32 pmic_index, pm_schg_usb_aicl_cfg_type aicl_cfg_type, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_enable_icl_override_after_apsd(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_schg_usb_get_usbin_option1_cfg(uint32 bus_id, uint32 pmic_device, pm_schg_usb_usbin_options_1_cfg usbin_cfg, boolean *enable)
{
  return PM_ERR_FLAG_SUCCESS;
}








