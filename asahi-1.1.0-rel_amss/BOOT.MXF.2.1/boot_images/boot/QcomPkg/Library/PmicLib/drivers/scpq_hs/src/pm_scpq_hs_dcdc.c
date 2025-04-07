/*! \file
*
*  \brief  pm_scpq_hs_otg.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
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
#include "pm_scpq_hs_dcdc.h"
#include "pm_scpq_hs_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (scpq_hs_ptr->base_address + \
                    scpq_hs_ptr->dcdc_register->peripheral_offset + \
                    scpq_hs_ptr->dcdc_register->x)

#define SLAVE_ID   (scpq_hs_ptr->comm_ptr->slave_id)

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type pm_scpq_hs_dcdc_get_icl_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_dcdc_icl_status_type *icl_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data[4] = {0};
  const uint32 icl_step_size = 50;

  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == icl_status)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type otg_icl_status = ADDRESS(icl_max_status);
    err_flag |= pm_comm_read_byte_array(SLAVE_ID, otg_icl_status, 4, data);

    icl_status->icl_max_status   = data[0] * icl_step_size;
    icl_status->icl_aicl_status  = data[1] * icl_step_size;
    icl_status->icl_thm_status   = data[2] * icl_step_size;
    icl_status->icl_final_status = data[3] * icl_step_size;
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_dcdc_get_power_path_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_dcdc_power_path_status *power_path_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == power_path_status)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(power_path_status);
    pm_register_data_type data = 0;

    err_flag = pm_comm_read_byte(SLAVE_ID, address, &data);

    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      power_path_status->valid_input_source = (data & 0x80) ? TRUE : FALSE;
      power_path_status->input_ss_done = (data & 0x40) ? TRUE : FALSE;
      power_path_status->use_usbin = (data & 0x20) ? TRUE : FALSE;
      power_path_status->use_wls = (data & 0x10) ? TRUE : FALSE;
      power_path_status->usbin_suspend = (data & 0x08) ? TRUE : FALSE;
      power_path_status->wls_suspend = (data & 0x04) ? TRUE : FALSE;
      power_path_status->power_path = data & 0x03;
    }
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_dcdc_get_otg_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_dcdc_otg_status_type* otg_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == otg_status)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type otg_status_addr = ADDRESS(bst_status);
    pm_register_data_type data = 0;
    uint8 read_mask = 0x07;
    err_flag = pm_comm_read_byte_mask(SLAVE_ID, otg_status_addr, read_mask, &data);

    *otg_status = (pm_scpq_hs_dcdc_otg_status_type)data;
  }

  return err_flag;
}
