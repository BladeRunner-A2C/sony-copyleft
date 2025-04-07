/*! \file
*
*  \brief  pm_scpq_hs_usb.c driver implementation.
*  \details charger driver implementation.
*  &copy;
*  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    -------------------------------------------------------------
01/19/23    rs    Initial revision
=============================================================================== */

/*=============================================================================

                        INCLUDE FILES

===============================================================================*/
#include "pm_scpq_hs_driver.h"
#include "pm_scpq_hs_usb.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/
#define ADDRESS(x) (scpq_hs_ptr->base_address + \
                    scpq_hs_ptr->usb_register->peripheral_offset + \
                    scpq_hs_ptr->usb_register->x)

#define SLAVE_ID   (scpq_hs_ptr->comm_ptr->slave_id)

#define PM_SCPQ_HS_USB_USBIN_MAX_CURRENT_LIMIT_CFG_MV      5000
#define PM_SCPQ_HS_USB_USBIN_CURRENT_LIMIT_CFG_STEP_SIZE   50

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
pm_err_flag_type pm_scpq_hs_usb_get_apsd_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_apsd_status_type apsd_status_type, boolean *result)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == result || apsd_status_type >= PM_SCPQ_HS_USB_APSD_STATUS_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type apsd_status = ADDRESS(apsd_status);
    err_flag = pm_comm_read_byte(SLAVE_ID, apsd_status, &data);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      *result = (data & (0x1 << apsd_status_type)) ? TRUE : FALSE;
    }
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_get_apsd_result_status(uint32 bus_id, uint32 pmic_index, pm_chg_charger_port_type *apsd_result)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);
  pm_register_address_type apsd_result_status;
  int8 usb_type = 0x06;

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == apsd_result)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    *apsd_result = PM_CHARGER_PORT_TYPE_INVALID;
    apsd_result_status = ADDRESS(apsd_result_status);

    err_flag = pm_comm_read_byte(SLAVE_ID, apsd_result_status, &data);
    if(PM_ERR_FLAG_SUCCESS == err_flag)
    {
      /*Check for charger port type starting from bit 6 to 0*/
      while(usb_type >= 0)
      {
        if(data & (1 << usb_type))
        {
          *apsd_result = (pm_chg_charger_port_type)usb_type;
          break;
        }
        usb_type--;
      }
    }
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_configure_usb_icl_options(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_icl_options_type icl_options, boolean set_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);
  pm_register_data_type data = (set_value) ? 0xFF : 0x00;
  pm_register_data_type mask = 0x1 << icl_options ;

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(icl_options >= PM_SCPQ_HS_USB_ICL_OPTIONS_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type usbin_icl_options = ADDRESS(usb_icl_options);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usbin_icl_options, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_set_icl_cfg(uint32 bus_id, uint32 pmic_index, uint32 usbin_current_limit)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0x0;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    if(usbin_current_limit > PM_SCPQ_HS_USB_USBIN_MAX_CURRENT_LIMIT_CFG_MV)
    {
      data = 100;
    }
    else
    {
      data = (usbin_current_limit + (PM_SCPQ_HS_USB_USBIN_CURRENT_LIMIT_CFG_STEP_SIZE / 2)) / PM_SCPQ_HS_USB_USBIN_CURRENT_LIMIT_CFG_STEP_SIZE;
    }
    pm_register_address_type usbin_current_limit_cfg = ADDRESS(usb_icl_cfg);

    err_flag = pm_comm_write_byte(SLAVE_ID, usbin_current_limit_cfg, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_set_usbin_suspend(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_usb_suspend_type usb_suspend_cfg, boolean set_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(usb_suspend_cfg >= PM_SCPQ_HS_USB_USB_SUSPEND_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type usb_suspend = ADDRESS(usb_suspend);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usb_suspend, (1 << usb_suspend_cfg), set_value ? 0x01 : 0x00);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_aicl_options_cfg(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_aicl_cfg_type aicl_cfg_type, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(aicl_cfg_type >= PM_SCPQ_HS_USB_AICL_INVALID || aicl_cfg_type < PM_SCPQ_HS_USB_AICL_START_AT_MAX)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type usb_aicl_cfg = ADDRESS(usb_aicl_cfg);
    pm_register_data_type mask = 0x1 << aicl_cfg_type;
    pm_register_data_type data = enable ? 0xFF : 0x00;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usb_aicl_cfg, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_enable_icl_override_after_apsd(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type usb_icl_override = ADDRESS(usb_icl_override);
    pm_register_data_type mask = PM_BIT(4);
    pm_register_data_type data = enable << 4;
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, usb_icl_override, mask, data);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_irq_status(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_usb_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type    err_flag    = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data;
  uint8 mask = 1 << irq;
  pm_register_address_type int_sts;
  pm_scpq_hs_data_type *scpq_hs_ptr  = pm_scpq_hs_get_data(bus_id, pmic_index);

  if (NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if (irq >= PM_SCPQ_HS_USB_IRQ_INVALID || type >= PM_IRQ_STATUS_INVALID || NULL == status)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    switch (type)
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
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    err_flag = pm_comm_read_byte_mask(SLAVE_ID, int_sts, mask, &data);
    *status = data ? TRUE : FALSE;
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_rerun_apsd(uint32 bus_id, uint32 pmic_index, boolean rerun)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 apsd_rerun = 0x0;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type apsd_cfg_reg = ADDRESS(apsd_cmd);
	apsd_rerun = (rerun == TRUE) ? 0x01 : 0x00;
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, apsd_cfg_reg, 0x1, apsd_rerun);
  }

  return err_flag;
}

pm_err_flag_type pm_scpq_hs_usb_apsd_enable(uint32 bus_id, uint32 pmic_index, uint8 apsd_start_detect, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 apsd_enable = 0x0;
  pm_scpq_hs_data_type *scpq_hs_ptr = pm_scpq_hs_get_data(bus_id, pmic_index);

  if(NULL == scpq_hs_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_address_type apsd_cfg_reg = ADDRESS(apsd_en);
	pm_register_data_type mask = 0x1 << apsd_start_detect;
	apsd_enable = (enable == TRUE) ? 0x80 : 0x00;
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, apsd_cfg_reg, mask, apsd_enable);
  }

  return err_flag;
}

