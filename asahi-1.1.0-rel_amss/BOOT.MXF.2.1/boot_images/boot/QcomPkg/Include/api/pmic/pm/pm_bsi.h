#ifndef __PM_BSI_H__
#define __PM_BSI_H__

/*! \file  pm_bsi.h
 *  \n
 *  \brief  PMIC-BSI MODULE RELATED DECLARATION
 *  \details  This file contains functions and variable declarations to support
 *   the PMIC BSI module.
 *  &copy;
 *  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/dev/core.boot/6.1/suqitian.core.boot.6.1.D0319LanaiIBAT10A/QcomPkg/Include/api/pmic/pm/pm_bsi.h#1 $

when       who       what, where, why
--------   ---       ----------------------------------------------------------
06/07/23   suqitian  Implement BSI module driver
===========================================================================*/

/*===========================================================================
                INCLUDE FILES FOR MODULE
===========================================================================*/
#include "pm_err_flags.h"
#include "com_dtypes.h"

/*=============================================================================
                    LOCAL VARIABLE DEFINITIONS
=============================================================================*/
typedef enum
{
  PM_BSI_BIF_PU_80K,
  PM_BSI_BIF_PU_680,
  PM_BSI_BIF_PU_INVALID
} pm_bsi_bif_pu_cfg_type;

/*===========================================================================
                          FUNCTION DEFINITIONS
===========================================================================*/

/**
 * @brief This function enables pull up resistor
 *
 * @param[in]  bus_id:
 *               0 for primary spmi bus
 *               1 for secondary spmi bus
 * 
 * @param[in]  pmic_index:
 *               pmic index value
 *
 * @param[in] enable:
 *               enable or disable
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 * DEPENDENCY: pm_driver_init() must be called in advance
 */

pm_err_flag_type
pm_bsi_pu_resistor_enable
(
  uint32 bus_id,
  uint32 pmic_index,
  boolean enable
);


/**
 * @brief This function retrieves the source of BSI
 *
 * @param[in]  bus_id:
 *               0 for primary spmi bus
 *               1 for secondary spmi bus
 * 
 * @param[in]  pmic_index:
 *               pmic index value
 *
 * @param[out] pu_resistor_value: 
 *                      Pull up resistor value
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 * DEPENDENCY: pm_driver_init() must be called in advance
 */
pm_err_flag_type
pm_bsi_pu_resistor_cfg
(
  uint32 bus_id,
  uint32 pmic_index,
  pm_bsi_bif_pu_cfg_type pu_resistor_value
);


#endif // __PM_BSI_H__

