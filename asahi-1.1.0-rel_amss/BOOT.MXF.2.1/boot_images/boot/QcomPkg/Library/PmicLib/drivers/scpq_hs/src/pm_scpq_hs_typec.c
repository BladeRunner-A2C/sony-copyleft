/*! \file
*
*  \brief  pm_scpq_hs_typec.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2022,2023 Qualcomm Technologies, Inc. All rights reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    -------------------------------------------------------------
07/09/22    xj     Initial revision
=============================================================================== */

/*=============================================================================

                        INCLUDE FILES

===============================================================================*/
#include "pm_scpq_hs_driver.h"
#include "pm_scpq_hs_typec.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
#define ADDRESS(x) (scpq_hs_ptr->base_address + \
                    scpq_hs_ptr->typec_register->peripheral_offset + \
                    scpq_hs_ptr->typec_register->x)

#define SLAVE_ID   (scpq_hs_ptr->comm_ptr->slave_id)
/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type pm_scpq_hs_usb_get_typec_status(uint32 bus_id, uint32 pmic_index, pm_chg_typec_status_type *typec_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 typec_port_status[6] = {0};
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(typec_status == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(typec_snk_status);
    err_flag = pm_comm_read_byte_array(SLAVE_ID, address, 6, (uint8 *)&typec_port_status);

    if(typec_port_status[0] & 0x02)
    {
      typec_status->dfp_curr_adv = PM_TYPEC_CURR_ADV_3A;
    }
    else if(typec_port_status[0] & 0x04)
    {
      typec_status->dfp_curr_adv = PM_TYPEC_CURR_ADV_1P5A;
    }
    else if(typec_port_status[0] & 0x08)
    {
      typec_status->dfp_curr_adv = PM_TYPEC_CURR_ADV_STD;
    }
    else
    {
      typec_status->dfp_curr_adv = PM_TYPEC_CURR_ADV_INVALID;
    }

    if(typec_port_status[2] & 0x08)
    {//DFP mode - RD/Open on CC1/CC2
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_ATTACHED;
    }
    else if(typec_port_status[2] & 0x04)
    {//DFP mode - RD/RA on CC1/CC2
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_ATTACHED_POWER_CABLE;
    }
    else if(typec_port_status[2] & 0x10)
    {//DFP mode - RD/RD on CC1/CC2
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_DEBUG_ACCESSORY;
    }
    else if(typec_port_status[2] & 0x01)
    {//DFP mode - RA/RA on CC1/CC2
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_AUDIO_ADAPTER;
    }
    else
    {
      typec_status->ufp_conn_type = PM_CHG_TYPEC_UFP_INVALID;
    }

    typec_status->vbus_sts          = (typec_port_status[5] & 0x20) ? TRUE : FALSE;
    typec_status->vbus_err_sts      = (typec_port_status[5] & 0x10) ? TRUE : FALSE;
    typec_status->debounce_done_sts = (typec_port_status[5] & 0x08) ? TRUE : FALSE;
    typec_status->vconn_oc_sts      = (typec_port_status[5] & 0x04) ? TRUE : FALSE;
    typec_status->ccout_out_hiz_sts = (typec_port_status[5] & 0x01) ? TRUE : FALSE;
    typec_status->cc_out_sts        = (typec_port_status[5] & 0x02) ? PM_CHG_TYPEC_ORIENTATION_PLUG_FLIP : PM_CHG_TYPEC_ORIENTATION_PLUG_UNFLIP;
  }

  return err_flag;
}


pm_err_flag_type pm_scpq_hs_usb_get_typec_vbus_status(uint32 bus_id, uint32 pmic_index, boolean *vbus_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0x00;
  pm_register_data_type vbus_status_mask = 0x20;

  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);
  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(vbus_status == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(typec_misc_status);
    err_flag = pm_comm_read_byte(SLAVE_ID, address, &data);

    *vbus_status = (data & vbus_status_mask) ? TRUE : FALSE;
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_typec_set_dam_icl(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_typec_dam_icl_sel icl_sel)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);
  pm_register_data_type data  = icl_sel << 2;
  pm_register_data_type mask  = 0x04;

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_snk_cfg = ADDRESS(typec_debug_access_snk_cfg);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, type_c_snk_cfg, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_typec_get_dam_connect_sts(uint32 bus_id, uint32 pmic_index, boolean *ConnectSts)
{
  pm_err_flag_type err_flag   = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);
  pm_register_data_type data  = 0;
  uint8 mask = 0x3F;

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type type_c_access_status = ADDRESS(typec_debug_access_status);
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, type_c_access_status, mask, &data);
    if(ConnectSts != NULL)
    {
      *ConnectSts = data ? TRUE : FALSE;
    }
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_typec_get_port_role(uint32 bus_id, uint32 pmic_index, pm_chg_typec_port_role_type *port_role)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 typec_port_status[4] = {0};
  uint8 current_adv_mask = 0x0E;
  uint8 dfp_mask = 0x0D;
  uint8 dam_sink_mask = 0x70;
  uint8 dam_typec_state_machine = 0x2C;

  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == port_role)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *port_role = PM_CHG_TYPEC_ROLE_INVALID;

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type address = ADDRESS(typec_snk_status);

    err_flag = pm_comm_read_byte_array(SLAVE_ID, address, sizeof(typec_port_status), typec_port_status);
    if(PM_ERR_FLAG_SUCCESS != err_flag)
    {
      return err_flag;
    }

    if(current_adv_mask & typec_port_status[0])
    {
      *port_role = PM_CHG_TYPEC_ROLE_UFP;
    }
    else if(dfp_mask & typec_port_status[2])
    {
      *port_role = PM_CHG_TYPEC_ROLE_DFP;
    }
    else if ((dam_sink_mask & typec_port_status[0]) || (dam_typec_state_machine & typec_port_status[3]))
    {
      *port_role = PM_CHG_TYPEC_ROLE_UFP;
    }
    else
    {
      *port_role = PM_CHG_TYPEC_ROLE_NONE;
    }
  }

  return err_flag;
}


