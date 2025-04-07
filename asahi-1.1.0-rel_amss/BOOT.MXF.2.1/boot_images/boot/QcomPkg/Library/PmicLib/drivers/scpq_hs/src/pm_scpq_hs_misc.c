/*! \file
*
*  \brief  pm_scpq_misc.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2022,2023 Qualcomm Technologies, Inc. All rights reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
01/19/23    rs    Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_scpq_hs_misc.h"
#include "pm_scpq_hs_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
#define ADDRESS(x) (scpq_hs_ptr->base_address + \
                    scpq_hs_ptr->misc_register->peripheral_offset + \
                    scpq_hs_ptr->misc_register->x)

#define SLAVE_ID   (scpq_hs_ptr->comm_ptr->slave_id)

/*===========================================================================

FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type pm_scpq_hs_misc_aicl_cmd_enable(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_aicl_cmd_type cmd)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);
  pm_register_data_type data = 0x1 << cmd;
  pm_register_data_type mask = 0x1 << cmd;

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(PM_SCPQ_HS_MISC_AICL_CMD_INVALID <= cmd)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type aicl_cmd_reg = ADDRESS(aicl_cmd);
    err_flag = pm_comm_write_byte_mask(pmic_index, aicl_cmd_reg, data, mask);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_misc_set_batt_therm_ch_id_cfg(uint32 bus_id, uint32 pmic_index, uint8 channel_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type reg_addr = ADDRESS(batt_therm_ch_id);
    err_flag = pm_comm_write_byte(SLAVE_ID, reg_addr, channel_id);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_misc_get_batt_therm_ch_id_cfg(uint32 bus_id, uint32 pmic_index, uint8* channel_id)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type reg_addr = ADDRESS(batt_therm_ch_id);
    err_flag = pm_comm_read_byte(SLAVE_ID, reg_addr, channel_id);
  }

  return err_flag;
}

pm_err_flag_type 
pm_scpq_hs_misc_set_vin_adc_mux_sel(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_vin_div16_mux_sel_type vin_mux_sel)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(vin_mux_sel >= PM_SCPQ_HS_MISC_VIN_DIV16_MUX_SEL_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type vin_div16_mux_sel_reg = ADDRESS(vin_div16_mux_sel);
    err_flag = pm_comm_write_byte(SLAVE_ID, vin_div16_mux_sel_reg, vin_mux_sel);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_misc_batt_therm_ch_enable(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS; 
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);
  uint8 mask = 0x01;

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type batt_therm_chen = ADDRESS(batt_therm_ch_en);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, batt_therm_chen, mask, enable ? 1 : 0);  
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_misc_set_wd_bark_timeout(uint32 bus_id, uint32 pmic_index, uint32 timeout_ms)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 min = 0;
  uint32 step = 0;
  uint32 base = 0;
  uint8 data = 0;
  uint8 mask = 0x1F;

  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if(timeout_ms < 250)
  {
    timeout_ms = 250;
  }
  else if(timeout_ms >= 32 * 1000)
  {
    timeout_ms = 32 * 1000;
  }

  // [0.25s : 0.25s : 2s]; [2.5s : 0.5s : 4s]; [5s : 1s : 16s]; [18s : 2s : 32s]
  // stored in [4:0]
  if(timeout_ms <= 2 * 1000)
  {
    min = 250;
    step = 250;
    base = 0;
  }
  else if(timeout_ms <= 4 * 1000)
  {
    min = 2 * 1000;
    step = 500;
    base = 7;
  }
  else if(timeout_ms <= 16 * 1000)
  {
    min = 4 * 1000;
    step = 1000;
    base = 11;
  }
  else // timeout <= 32000
  {
    min = 16 * 1000;
    step = 2 * 1000;
    base = 23;
  }

  data = (timeout_ms - min) / step + base;

  err_flag = pm_comm_write_byte_mask(SLAVE_ID, ADDRESS(wd_bb_time_sel), mask, data);

  return err_flag;
}

/*This API configures the charger watchdog */
pm_err_flag_type pm_scpq_hs_misc_get_config_wdog(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_wdog_cfg_type *chgr_wd_cfg)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == chgr_wd_cfg)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type wd_cfg_reg = ADDRESS(wd_cfg);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, wd_cfg_reg, 0xB3, &data);
    chgr_wd_cfg->bite_wdog_disable_charging_cfg = (data & 0x80) >> 7;
    chgr_wd_cfg->bite_wdog_int_en               = (data & 0x20) >> 5;
    chgr_wd_cfg->bark_wdog_int_en               = (data & 0x10) >> 4;
    chgr_wd_cfg->wdog_timer_en_on_plugin        = (data & 0x02) >> 1;
    chgr_wd_cfg->wdog_timer_en                  = data & 0x01;
  }

  return err_flag;
}

/*This API configures the charger watchdog */
pm_err_flag_type pm_scpq_hs_misc_config_wdog(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_wdog_cfg_type chgr_wd_cfg)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data  = 0;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else   
  {
    pm_register_address_type wd_cfg_reg = ADDRESS(wd_cfg);
    data |= ((chgr_wd_cfg.bite_wdog_disable_charging_cfg << 0x7) | (chgr_wd_cfg.bite_wdog_int_en << 0x5) |
            (chgr_wd_cfg.bark_wdog_int_en << 0x4) | (chgr_wd_cfg.wdog_timer_en_on_plugin << 0x1) |
            (chgr_wd_cfg.wdog_timer_en << 0x0));
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, wd_cfg_reg, 0xB3, data);
  }

  return err_flag;
}

/* Writing to this register will pet (reset) BARK and BITE watchdog timers */
pm_err_flag_type pm_scpq_hs_misc_bark_bite_wdog_pet(uint32 bus_id, uint32 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type wdog_pet = ADDRESS(bark_bite_wdog_pet);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, wdog_pet, 0x01, 0x01);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_misc_irq_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_misc_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  uint8 mask = 1 << irq;
  pm_register_address_type int_sts = 0;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(0,pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == status || irq >= PM_SCPQ_HS_MISC_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch(type)
    {
    case PM_IRQ_STATUS_RT:
      int_sts = ADDRESS(int_rt_sts);
      break;
    case PM_IRQ_STATUS_LATCHED:
      int_sts = ADDRESS(int_latched_sts);
      break;
    case PM_IRQ_STATUS_PENDING:
      int_sts = ADDRESS(int_pending_sts);
      break;
    default:
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    err_flag = pm_comm_read_byte_mask(SLAVE_ID, int_sts, mask, &data);
    *status = data ? TRUE : FALSE;
  }

  return err_flag;
}

