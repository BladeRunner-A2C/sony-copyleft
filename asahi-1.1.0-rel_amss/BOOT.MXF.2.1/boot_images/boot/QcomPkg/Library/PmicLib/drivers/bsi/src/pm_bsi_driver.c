/*! \file pm_bsi_driver.c
*  \n
*  \brief This file contains bsi peripheral driver initialization during which the driver data is stored.
*  &copy;
*  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/dev/core.boot/6.1/suqitian.core.boot.6.1.D0319LanaiIBAT10A/QcomPkg/Library/PmicLib/drivers/bsi/src/pm_bsi_driver.c#1 $

$Author: suqitian $
$DateTime: 2023/03/19 07:20:20 $
when       who         what, where, why
--------   ---         ----------------------------------------------------------
06/07/23   suqitian    Implement bsi driver
========================================================================== */

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_bsi_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/


/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the BSI data */
static pm_bsi_data_type *pm_bsi_data_arr[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_PMICS];

static pm_bsi_register_info_type bsi_reg =
{
  .bsi_bsi_en        = 0x46,
  .bsi_mipi_bif_cfg  = 0x55
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void
pm_bsi_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index, uint32 bus_id)
{
  pm_bsi_data_type *bsi_ptr = pm_bsi_data_arr[bus_id][pmic_index];

  if(NULL == bsi_ptr)
  {
    pm_malloc(sizeof(pm_bsi_data_type), (void**)&bsi_ptr);
    CORE_VERIFY_PTR(bsi_ptr);

    /* Assign Comm ptr */
    bsi_ptr->comm_ptr = comm_ptr;

    bsi_ptr->bsi_reg_table = &bsi_reg;

    bsi_ptr->base_address = peripheral_info->base_address;

    pm_bsi_data_arr[bus_id][pmic_index] = bsi_ptr;
  }
}

pm_bsi_data_type*
pm_bsi_get_data(uint32 bus_id, uint32 pmic_index)
{
  return ((pmic_index < PM_MAX_NUM_PMICS) && (bus_id < PM_MAX_BUSES_SUPPORTED)) ? pm_bsi_data_arr[bus_id][pmic_index] : NULL;
}

