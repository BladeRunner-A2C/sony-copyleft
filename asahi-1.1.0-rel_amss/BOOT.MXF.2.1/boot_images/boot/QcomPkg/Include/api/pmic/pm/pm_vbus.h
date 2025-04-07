#ifndef __PM_VBUS_H__
#define __PM_VBUS_H__

/*! \file  pm_vbus.h
 *  \n
 *  \brief  PMIC VBUS MODULE RELATED DECLARATION
 *  \details  This file contains functions and variable declarations to support
 *   the PMIC VBUS module.
 *
 *  \n &copy; Copyright (c) 2022 QUALCOMM Technologies Incorporated. All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/08/22   xj      Porting VBUS driver from core.boot.5.1.1
===========================================================================*/

/*===========================================================================
                    INCLUDE FILES FOR MODULE
===========================================================================*/
#include "pm_err_flags.h"
#include "com_dtypes.h"
#include "pm_resources_and_types.h"


/*=============================================================================
                    LOCAL VARIABLE DEFINITIONS
=============================================================================*/
typedef enum
{
  PM_VBUS_IRQ_VBUS_DET = 0,
  PM_VBUS_IRQ_INVALID
}pm_vbus_irq_type;

/*=============================================================================
                    VBUS FUNCTION PROTOTYPES
=============================================================================*/

/**
 * @brief This function enables irq
 *
 * @details
 *  This function enables irq
 *
 * @param[in] pmic_index:  The pmic_index of VBUS module.
 * @param[in] irq:         Refer #pm_vbus_irq_type for details.
 * @param[in] enable:      FALSE: 0, TRUE: 1
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_vbus_irq_enable(uint32 pmic_index, pm_vbus_irq_type irq, boolean enable);

/**
 * @brief This function clears the VBUS irq
 *
 * @param[in] pmic_index: The pmic_index of VBUS module.
 * @param[in] irq:        Refer #pm_vbus_irq_type for details.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_vbus_irq_clear(uint32 pmic_index, pm_vbus_irq_type irq);

/**
 * @brief This function configures the VBUS irq trigger
 *
 * @param[in] pmic_index:  The pmic_index of VBUS module.
 * @param[in] irq:         Refer #pm_vbus_irq_type for details.
 * @param[in] trigger:     Refer #pm_irq_trigger_type for details.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_vbus_irq_set_trigger(uint32 pmic_index, pm_vbus_irq_type irq, pm_irq_trigger_type trigger);

/**
 * @brief This function configures the VBUS for irq
 *
 * @param[in] pmic_index:  The pmic_index of VBUS module.
 * @param[in] irq:         Refer #pm_vbus_irq_type for details.
 * @param[in] type:        Refer #pm_irq_status_type for details.
 * @param[out] status:     IRQ status.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_vbus_irq_status(uint32 pmic_index, pm_vbus_irq_type irq, pm_irq_status_type type, boolean *status);

/**
 * @brief This function get the VBUS detect status
 *
 * @param[in] pmic_index:  The pmic_index of VBUS module.
 * @param[out] status:     VBUS present status
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_vbus_get_vbus_status(uint32 pmic_index, boolean *vbus_status);

#endif //__PM_VBUS_H__

