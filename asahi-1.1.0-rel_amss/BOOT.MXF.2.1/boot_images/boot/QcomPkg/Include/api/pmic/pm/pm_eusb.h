#ifndef __PM_EUSB_H__
#define __PM_EUSB_H__

/*! \file  pm_eusb.h
 *  \n
 *  \brief  PMIC-EUSB MODULE RELATED DECLARATION
 *  \details  This file contains functions and variable declarations to support
 *   the PMIC EUSB module.
 *
 *  \n &copy; Copyright (c) 2022 QUALCOMM Technologies Incorporated. All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/api/pmic/pm/pm_eusb.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/06/22   akm     Implement EUSB driver
===========================================================================*/

/*===========================================================================
                INCLUDE FILES FOR MODULE
===========================================================================*/
#include "pm_err_flags.h"
#include "com_dtypes.h"

/*=============================================================================
                    LOCAL VARIABLE DEFINITIONS
=============================================================================*/



/*===========================================================================
                          FUNCTION DEFINITIONS
===========================================================================*/


/**
 * @brief This function enable/disable EUSB functionality
 *
 * @param[in]  bus_id:
 *               0 for primary spmi bus
 *               1 for secondary spmi bus
 * @param[in]  pmic_index:
 *               0 for primary pmic
 *               1 for secondary pmic
 * @param[in] enable:
 *               enable or disable
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 * DEPENDENCY: pm_driver_init() must be called in advance
 */
pm_err_flag_type 
pm_eusb_enable(uint32 bus_id, uint32 pmic_index, boolean enable);

/**
 * @brief This function gives EUSB logic enable status
 *
 * @param[in]  bus_id:
 *               0 for primary spmi bus
 *               1 for secondary spmi bus
 * @param[in]  pmic_index:
 *               0 for primary pmic
 *               1 for secondary pmic
 * @param[out] rptr_sts:
 *               EUSB Repeater status enabled or disabled
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_INVALID_PARAMETER = There is inavalid input parameter
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 * DEPENDENCY: pm_driver_init() must be called in advance
 */
pm_err_flag_type 
pm_eusb_rptr_status(uint32 bus_id, uint32 pmic_index, uint8 *rptr_sts);

#endif

