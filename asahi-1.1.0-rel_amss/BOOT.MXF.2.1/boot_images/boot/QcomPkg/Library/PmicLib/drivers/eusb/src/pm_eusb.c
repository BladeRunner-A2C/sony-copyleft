/*! \file
*
*  \brief  pm_eusb.c driver implementation.
*  &copy;
*  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/eusb/src/pm_eusb.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who      what, where, why
--------   ---      -------------------------------------------------------------
01/06/22   akm     Implement EUSB driver
=============================================================================== */

/*=============================================================================

          INCLUDE FILES

===============================================================================*/
#include "pm_eusb.h"
#include "pm_eusb_driver.h"

/*===========================================================================
                       MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (eusb_ptr->base_address + eusb_ptr->eusb_reg_table->x)
#define SLAVE_ID   (eusb_ptr->comm_ptr->slave_id)

/*===========================================================================

FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type 
pm_eusb_enable(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_eusb_data_type *eusb_ptr = pm_eusb_get_data(bus_id, pmic_index);

  if(NULL == eusb_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_data_type mask = 0x80;  // <0>
    pm_register_data_type data = enable ? 0x80 : 0;

    err_flag = pm_comm_write_byte_mask_ex(bus_id, SLAVE_ID, ADDRESS(eusb_eusb_en), mask, data);
  }

  return err_flag;
}

pm_err_flag_type
pm_eusb_rptr_status(uint32 bus_id, uint32 pmic_index, uint8 *rptr_sts)
{

  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_eusb_data_type *eusb_ptr = pm_eusb_get_data(bus_id, pmic_index);

  if(NULL == eusb_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(NULL == rptr_sts)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_data_type rptr_data = 0;
    pm_register_data_type mask = 0x80;

    err_flag = pm_comm_read_byte_ex(bus_id, SLAVE_ID, ADDRESS(eusb_rptr_sts), &rptr_data);

    if(err_flag == PM_ERR_FLAG_SUCCESS)
    {
      *rptr_sts = rptr_data & mask;
    }
  }

  return err_flag;
}


