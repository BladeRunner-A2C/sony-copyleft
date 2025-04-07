#ifndef __PM_BSI_DRIVER_H__
#define __PM_BSI_DRIVER_H__

/*! \file pm_bsi_driver.h
*  \n
*  \brief  This file contains functions prototypes and variable/type/constant
*         declarations for supporting bsi peripheral.
*  &copy;
*  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/dev/core.boot/6.1/suqitian.core.boot.6.1.D0319LanaiIBAT10A/QcomPkg/Library/PmicLib/drivers/bsi/src/pm_bsi_driver.h#1 $

$Author: suqitian $
$DateTime: 2023/03/19 07:20:20 $
when         who      what, where, why
--------   ---        ----------------------------------------------------------
06/07/23   suqitian   Implement BSI driver
========================================================================== */

/*===========================================================================
            INCLUDE FILES
===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                     BSI TYPES AND STRUCTURES

===========================================================================*/
typedef struct
{
  pm_register_address_type bsi_bsi_en;                     // 0x46
  pm_register_address_type bsi_mipi_bif_cfg;               // 0x55
} pm_bsi_register_info_type;


typedef struct
{
  pm_comm_info_type            *comm_ptr;
  pm_bsi_register_info_type    *bsi_reg_table;
  pm_register_address_type     base_address;
}pm_bsi_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void
pm_bsi_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index, uint32 bus_id);

pm_bsi_data_type*
pm_bsi_get_data(uint32 bus_id, uint32 pmic_index);


#endif // __PM_BSI_DRIVER_H__

