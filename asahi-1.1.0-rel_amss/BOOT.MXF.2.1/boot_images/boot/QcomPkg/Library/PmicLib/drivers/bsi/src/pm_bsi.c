/*! \file
*
*  \brief  pm_bsi.c driver implementation.
*  &copy;
*  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE


$Header: //components/dev/core.boot/6.1/suqitian.core.boot.6.1.D0319LanaiIBAT10A/QcomPkg/Library/PmicLib/drivers/bsi/src/pm_bsi.c#1 $
$Author: suqitian $
$DateTime: 2023/03/19 07:20:20 $
when       who      what, where, why
--------   ---      -------------------------------------------------------------
06/07/23   suqitian  Implement BSI module driver
=============================================================================== */

/*=============================================================================

          INCLUDE FILES

===============================================================================*/
#include "pm_bsi.h"
#include "pm_bsi_driver.h"

/*===========================================================================
                       MACRO DECLARATIONS
===========================================================================*/

#define ADDRESS(x) (bsi_ptr->base_address + bsi_ptr->bsi_reg_table->x)
#define SLAVE_ID   (bsi_ptr->comm_ptr->slave_id)

/*===========================================================================

FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type
pm_bsi_pu_resistor_enable(uint32 bus_id, uint32 pmic_index, boolean enable)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_bsi_data_type *bsi_ptr = pm_bsi_get_data(bus_id, pmic_index);

  if(NULL == bsi_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else
  {
    pm_register_data_type mask = 0x80;  // <bit7>
    pm_register_data_type data = enable ? 0x80 : 0;

    err_flag |= pm_comm_write_byte_mask_ex(bus_id, SLAVE_ID, ADDRESS(bsi_mipi_bif_cfg), mask, data);
  }

  return err_flag;
}

pm_err_flag_type
pm_bsi_pu_resistor_cfg(uint32 bus_id, uint32 pmic_index, pm_bsi_bif_pu_cfg_type pu_resistor_value)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_bsi_data_type *bsi_ptr = pm_bsi_get_data(bus_id, pmic_index);

  if(NULL == bsi_ptr)
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  else if(pu_resistor_value >= PM_BSI_BIF_PU_INVALID)
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    pm_register_data_type mask = 0x40;  // <bit6>
    uint8 lshif_cnt = 6; // <bit6>
    pm_register_data_type data = (uint8)pu_resistor_value << lshif_cnt;
    
    err_flag |= pm_comm_write_byte_mask_ex(bus_id, SLAVE_ID, ADDRESS(bsi_mipi_bif_cfg), mask, data);
  }

  return err_flag;
}



