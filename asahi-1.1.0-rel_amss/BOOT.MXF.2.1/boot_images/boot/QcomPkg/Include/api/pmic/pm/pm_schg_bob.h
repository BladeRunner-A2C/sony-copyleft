#ifndef __PM_SCHG_BOB_H__
#define __PM_SCHG_BOB_H__

/*! \file
*  \n
*  \brief  pm_schg_bob.h PMIC-SCHG MODULE RELATED DECLARATION
*  \details  This header file contains functions and variable declarations
*  to support Qualcomm PMIC SCHG (Switch-Mode Battery Charger) module. The
*  Switched-Mode Battery Charger (SCHG) module includes a buck regulated
*  battery charger with integrated switches. The SCHG module, along with the
*  Over Voltage Proection (OVP) module will majorly be used by charger
*  appliation for charging Li-Ion batteries with high current (up to 2A).
*  \n &copy; Copyright 2017-2022 QUALCOMM Technologies Inc, All Rights Reserved
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who    what, where, why
--------    ---    ----------------------------------------------------------
06/20/18    cs     Initial version.
========================================================================== */
#include "com_dtypes.h"
#include "pm_err_flags.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/


typedef enum
{
    PM_BOB_BAT_TYPE_2S,
    PM_BOB_BAT_TYPE_3S,
    PM_BOB_BAT_TYPE_INVALID,
}pm_bob_bat_type;


/*===========================================================================

                 SCHG DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/**
* @brief This function returns if this charging port is active
*
* @param[in] pmic_index:  The pmic_index of charger module.
* @param[out]  isActive:  1 the port is active, 0, port not active.
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_bob_is_port_active(uint32 bus_id, uint32 pmic_index, boolean *is_active);


/**
* @brief This function returns the type of battery
*
* @param[in] pmic_index:  The pmic_index of charger module.
* @param[out]  bat_type:  2S, 3S, etc.
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_bob_get_batt_cfg(uint32 bus_id, uint32 pmic_index, pm_bob_bat_type *bat_type);

#endif /* __PM_SCHG_BOB_H__ */

