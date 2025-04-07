/*! \file
*
*  \brief  pm_scpq_hs_bat_if.c driver implementation.
*  \details charger driver implementation.
*  &copy; Copyright 2022-2023 QUALCOMM Technologies, Inc All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
01/19/23    rs     Initial revision 

========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_scpq_hs_batif.h"
#include "pm_scpq_hs_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
#define ADDRESS(x) (scpq_hs_ptr->base_address + \
                    scpq_hs_ptr->batif_register->peripheral_offset + \
                    scpq_hs_ptr->batif_register->x)

#define SLAVE_ID   (scpq_hs_ptr->comm_ptr->slave_id)

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/


pm_err_flag_type pm_scpq_hs_batif_cfg_batt_missing_src(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_batif_bat_miss_src_cfg_type bat_miss_cfg, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(bat_miss_cfg >= PM_SCPQ_HS_BAT_MISS_SRC_CFG_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_data_type mask = 1 << bat_miss_cfg;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, ADDRESS(bpd_cfg), mask, enable ? 0xFF : 0x00);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_batif_jeita_en_cfg(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_cfg_type jeita_cfg_type, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id,device_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(jeita_cfg_type >= PM_SCPQ_HS_BATIF_JEITA_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type jeita_en_cfg = ADDRESS(jeita_en_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, jeita_en_cfg, (uint8)(1 << jeita_cfg_type), (enable ? 0xFF : 0x00));
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_batif_set_jeita_threshold_value(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_threshold_type threshold_type, uint32 jeita_threshold)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, device_index);
  uint8 jeita_threshold_lsb = (jeita_threshold & 0xFF);
  uint8 jeita_threshold_msb = jeita_threshold >> 8;
  pm_register_address_type addr_msb = 0, addr_lsb = 0;


  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(threshold_type >= PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch(threshold_type)
    {
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_WARM:
      addr_msb = ADDRESS(jeita_warm_thd_msb);
      addr_lsb = ADDRESS(jeita_warm_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_COOL:
      addr_msb = ADDRESS(jeita_cool_thd_msb);
      addr_lsb = ADDRESS(jeita_cool_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT:
      addr_msb = ADDRESS(jeita_thot_thd_msb);
      addr_lsb = ADDRESS(jeita_thot_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD:
      addr_msb = ADDRESS(jeita_tcold_thd_msb);
      addr_lsb = ADDRESS(jeita_tcold_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT_AFP:
      addr_msb = ADDRESS(jeita_thot_afp_thd_msb);
      addr_lsb = ADDRESS(jeita_thot_afp_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD_AFP:
      addr_msb = ADDRESS(jeita_tcold_afp_thd_msb);
      addr_lsb = ADDRESS(jeita_tcold_afp_thd_lsb);
      break;
    default:
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    err_flag = pm_comm_write_byte(SLAVE_ID, addr_msb, jeita_threshold_msb);
    err_flag |= pm_comm_write_byte(SLAVE_ID, addr_lsb, jeita_threshold_lsb);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_batif_get_jeita_threshold_value(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_threshold_type threshold_type, uint16* jeita_threshold)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, device_index);
  pm_register_address_type addr_msb = 0, addr_lsb = 0;

  uint8 jeita_threshold_msb = 0, jeita_threshold_lsb = 0;

  if (NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(threshold_type >= PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch (threshold_type)
    {
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_WARM:
      addr_msb = ADDRESS(jeita_warm_thd_msb);
      addr_lsb = ADDRESS(jeita_warm_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_COOL:
      addr_msb = ADDRESS(jeita_cool_thd_msb);
      addr_lsb = ADDRESS(jeita_cool_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT:
      addr_msb = ADDRESS(jeita_thot_thd_msb);
      addr_lsb = ADDRESS(jeita_thot_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD:
      addr_msb = ADDRESS(jeita_tcold_thd_msb);
      addr_lsb = ADDRESS(jeita_tcold_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT_AFP:
      addr_msb = ADDRESS(jeita_thot_afp_thd_msb);
      addr_lsb = ADDRESS(jeita_thot_afp_thd_lsb);
      break;
    case PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD_AFP:
      addr_msb = ADDRESS(jeita_tcold_afp_thd_msb);
      addr_lsb = ADDRESS(jeita_tcold_afp_thd_lsb);
      break;
    default:
      return err_flag;
    }
    err_flag |= pm_comm_read_byte(SLAVE_ID, addr_msb, &jeita_threshold_msb);
    err_flag |= pm_comm_read_byte(SLAVE_ID, addr_lsb, &jeita_threshold_lsb);
    *jeita_threshold = (jeita_threshold_msb << 8) | jeita_threshold_lsb;
  }
  return err_flag;
}

