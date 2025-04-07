/*! \file
*
*  \brief  pm_vbus.c driver implementation.
*  &copy;
*  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


when       who      what, where, why
--------   ---      -------------------------------------------------------------
09/08/22   xj       Porting VBUS driver from core.boot.5.1.1
=============================================================================== */

/*=============================================================================

          INCLUDE FILES

===============================================================================*/

#include "pm_vbus.h"
#include "pm_vbus_driver.h"
#include "pm_resource_manager.h"

/*===========================================================================
                       MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (vbus_ptr->base_address + vbus_ptr->vbus_register->x)
#define SLAVE_ID   (vbus_ptr->comm_ptr->slave_id)

/*===========================================================================

                      FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type pm_vbus_irq_enable(uint32 pmic_index, pm_vbus_irq_type irq, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_address_type irq_reg = 0;
  pm_register_data_type data = 1 << irq;
  pm_vbus_data_type *vbus_ptr = pm_vbus_get_data(pmic_index);

  if(NULL == vbus_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_VBUS_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    if(enable)
    {
      irq_reg = ADDRESS(int_en_set);
    }
    else
    {
      irq_reg = ADDRESS(int_en_clr);
    }

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, irq_reg, data, data);
  }

  return err_flag;
}


pm_err_flag_type pm_vbus_irq_clear(uint32 pmic_index, pm_vbus_irq_type irq)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 1 << irq;
  pm_vbus_data_type *vbus_ptr = pm_vbus_get_data(pmic_index);

  if(NULL == vbus_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(irq >= PM_VBUS_IRQ_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type int_latched_clr = ADDRESS(int_latched_clr);
    err_flag = pm_comm_write_byte_mask(SLAVE_ID, int_latched_clr, data, data);
  }

  return err_flag;
}


pm_err_flag_type pm_vbus_irq_set_trigger(uint32 pmic_index, pm_vbus_irq_type irq, pm_irq_trigger_type trigger)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 mask = 1 << irq;
  pm_register_data_type set_type = 0, polarity_high = 0, polarity_low = 0;
  pm_vbus_data_type *vbus_ptr = pm_vbus_get_data(pmic_index);

  if(NULL == vbus_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if((irq >= PM_VBUS_IRQ_INVALID) || (trigger >= PM_IRQ_TRIGGER_INVALID))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type int_set_type = ADDRESS(int_set_type);
    pm_register_address_type int_polarity_high = ADDRESS(int_polarity_high);
    pm_register_address_type int_polarity_low = ADDRESS(int_polarity_low);

    switch(trigger)
    {
    case PM_IRQ_TRIGGER_ACTIVE_LOW:
      set_type = 0x00;
      polarity_high = 0x00;
      polarity_low = 0xFF;
      break;

    case PM_IRQ_TRIGGER_ACTIVE_HIGH:
      set_type = 0x00;
      polarity_high = 0xFF;
      polarity_low = 0x00;
      break;

    case PM_IRQ_TRIGGER_RISING_EDGE:
      set_type = 0xFF;
      polarity_high = 0xFF;
      polarity_low = 0x00;
      break;

    case PM_IRQ_TRIGGER_FALLING_EDGE:
      set_type = 0xFF;
      polarity_high = 0x00;
      polarity_low = 0xFF;
      break;

    case PM_IRQ_TRIGGER_DUAL_EDGE:
      set_type = 0xFF;
      polarity_high = 0xFF;
      polarity_low = 0xFF;
      break;

    default:
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    err_flag = pm_comm_write_byte_mask(SLAVE_ID, int_set_type, mask, set_type);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, int_polarity_high, mask, polarity_high);
    err_flag |= pm_comm_write_byte_mask(SLAVE_ID, int_polarity_low, mask, polarity_low);
  }

  return err_flag;
}


pm_err_flag_type pm_vbus_irq_status(uint32 pmic_index, pm_vbus_irq_type irq, pm_irq_status_type type, boolean *status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  uint8 mask = 1 << irq;
  pm_register_address_type int_sts = 0;
  pm_vbus_data_type *vbus_ptr = pm_vbus_get_data(pmic_index);

  if(NULL == vbus_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if((irq >= PM_VBUS_IRQ_INVALID) || (type >= PM_IRQ_STATUS_INVALID) || NULL == status)
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
      return PM_ERR_FLAG_INVALID_PARAMETER;
    }

    err_flag = pm_comm_read_byte_mask(SLAVE_ID, int_sts, mask, &data);
    *status = data ? TRUE : FALSE;
  }

  return err_flag;
}


pm_err_flag_type pm_vbus_get_vbus_status(uint32 pmic_index, boolean *vbus_status)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type data = 0;
  pm_register_data_type vbus_status_mask = 0x80;

  pm_vbus_data_type *vbus_ptr = pm_vbus_get_data(pmic_index);
  if(NULL == vbus_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(vbus_status == NULL)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_address_type address = ADDRESS(vbus_det_status1);
    err_flag = pm_comm_read_byte(SLAVE_ID, address, &data);

    *vbus_status = (data & vbus_status_mask) ? TRUE : FALSE;
  }

  return err_flag;
}

