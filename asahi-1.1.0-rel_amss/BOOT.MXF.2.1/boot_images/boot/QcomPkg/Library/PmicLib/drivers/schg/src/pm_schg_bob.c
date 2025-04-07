/*! \file
*
*  \brief  pm_schg_BOB.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2017-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


when       who     what, where, why
--------   ---    -------------------------------------------------------------
06/20/18    cs      Initial revision
=============================================================================== */

/*=============================================================================

                      INCLUDE FILES

===============================================================================*/
#include "pm_schg_driver.h"
#include "pm_schg_bob.h"
#include "pm_version.h"

/*===========================================================================
                      MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (schg_ptr->schg_register->bob_register->base_address + schg_ptr->schg_register->bob_register->x)
#define SLAVE_ID (schg_ptr->comm_ptr->slave_id)

/*===========================================================================

                      FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type
pm_schg_bob_is_port_active(uint32 bus_id, uint32 pmic_index, boolean *is_active)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 arbitor_mask = 0x02;
  uint8 reg_val = 0;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(bus_id, pmic_index);
  pm_model_type model_type = PMIC_IS_INVALID;

  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(is_active == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    model_type = pm_get_pmic_model_ex(bus_id, pmic_index);
    if (model_type == PMIC_IS_SMB2351 || model_type == PMIC_IS_DONINGTON)
    {
      pm_register_address_type address = ADDRESS(multi_port_arbiter);
      err_flag = pm_comm_read_byte_array_ex(bus_id, SLAVE_ID, address, 1, &reg_val);
      if (err_flag == PM_ERR_FLAG_SUCCESS)
      {
        *is_active = (reg_val & arbitor_mask) ? TRUE : FALSE;
      }
    }
    else
    {
      err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }

  return err_flag;
}

pm_err_flag_type 
pm_schg_bob_get_batt_cfg(uint32 bus_id, uint32 pmic_index, pm_bob_bat_type *bat_type)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;  
  uint8 reg_val = 0;
  pm_schg_data_type *schg_ptr = pm_schg_get_data(bus_id, pmic_index);
  if(NULL == schg_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    return err_flag;
  }
    
  if(bat_type == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
    return err_flag;
  }
  
  *bat_type = PM_BOB_BAT_TYPE_INVALID;

  pm_register_address_type address = ADDRESS(bat_3s_charge_cfg);
  err_flag = pm_comm_read_byte_ex(bus_id, SLAVE_ID, address, &reg_val);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  if (reg_val >= PM_BOB_BAT_TYPE_INVALID)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  *bat_type = (pm_bob_bat_type)reg_val;

  return err_flag;
}

