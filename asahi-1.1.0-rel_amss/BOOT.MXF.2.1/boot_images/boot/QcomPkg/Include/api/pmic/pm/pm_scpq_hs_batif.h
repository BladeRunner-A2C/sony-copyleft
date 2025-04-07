#ifndef __PM_SCPQ_HS_HS_BATIF_H__
#define __PM_SCPQ_HS_HS_BATIF_H__

/*! \file
 *  \n
 *  \brief  pm_scpq_hs_batif.h PMIC-SCPQ MODULE RELATED DECLARATION
 *  \details  This header file contains functions and variable declarations
 *  to support Qualcomm PMIC SCPQ BAT IF (Switch-Mode Battery Charger) module. The
 *  Switched-Mode Battery Charger (SCPQ OTG) module includes a buck regulated
 *  battery charger with integrated switches. The SCPQ OTG module, along with the
 *  Over Voltage Proection (OVP) module will majorly be used by charger
 *  appliation for charging Li-Ion batteries with high current (up to 2A).
 *  \n &copy;
 *  Copyright (c) 2022-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
01/19/23    rs    Initial revision
========================================================================== */
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/


/*! \enum pm_scpq_hs_irq_bit_field_type
   \brief different types of irq bit fields of by smbch_bat_if irq module
*/
typedef enum {
  PM_SCPQ_HS_BATIF_BAT_TEMP,
  PM_SCPQ_HS_BATIF_BAT_THERM_OR_ID_MISSING,
  PM_SCPQ_HS_BATIF_BAT_LOW,
  PM_SCPQ_HS_BATIF_BAT_OV,
  PM_SCPQ_HS_BATIF_BSM_ACTIVE,
  PM_SCPQ_HS_BATIF_IRQ_INVALID
}pm_scpq_hs_batif_irq_type;

typedef enum {
  PM_SCPQ_HS_BAT_MISS_SRC_CFG_PIN_SRC_EN,
  PM_SCPQ_HS_BAT_MISS_SRC_CFG_INVALID
}pm_scpq_hs_batif_bat_miss_src_cfg_type;

typedef enum
{
  PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT,            /** <Too Hot Jeita Threshold               >*/
  PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_WARM,            /** <Warm Jeita Threshold                  >*/
  PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_COOL,            /** <Hard Hot Jeita Threshold              >*/
  PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD,        /** <Hard COld Jeita Threshold             >*/
  PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_HOT_AFP,     /** <AFP Hot Jeita Threshold               >*/
  PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_TOO_COLD_AFP,    /** <AFP Cold Jeita Threshold              >*/
  PM_SCPQ_HS_BATIF_JEITA_THRESHOLD_INVALID          /** < Invalid                              >*/
}pm_scpq_hs_batif_jeita_threshold_type;

typedef enum
{
  PM_SCPQ_HS_BATIF_JEITA_COOL_CCC,        /** <Cool Charge Current Compensation                        >*/
  PM_SCPQ_HS_BATIF_JEITA_WARM_CCC,        /** <Warm Charge Current Compensation                        >*/
  PM_SCPQ_HS_BATIF_JEITA_COOL_FVC,        /** <COOL Float Voltage Compensation                         >*/
  PM_SCPQ_HS_BATIF_JEITA_WARM_FVC,        /** <WARM Float Voltage Compensation                         >*/
  PM_SCPQ_HS_BATIF_JEITA_FVCOMP_IN_CV,    /** <WARM/COOL VFLT Compensation during CV mode              >*/
  PM_SCPQ_HS_BATIF_JEITA_HARD_LIMIT,      /** <JEITA Temperature HOT/COLD Hard Limit Pauses Charging   >*/
  PM_SCPQ_HS_BATIF_JEITA_AFP_COLD,        /** <Jeita cold condition triggers AFP mode                  >*/
  PM_SCPQ_HS_BATIF_JEITA_AFP_HOT,         /** <Jeita hot condition triggers AFP mode                   >*/
  PM_SCPQ_HS_BATIF_JEITA_INVALID          /** < Invalid                                                >*/
}pm_scpq_hs_batif_jeita_cfg_type;

/*===========================================================================

                 SCPQ_HS BAT_IF DRIVER FUNCTION PROTOTYPES

===========================================================================*/


/**
 * @brief This function configures battery missing source
 *
 * @details
 *  This function configures battery missing source
 *
 * @param[in] bus_id: SPMI Bus id
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[in] bat_miss_cfg:  Battery missing config type, Refer #pm_scpq_hs_batif_bat_miss_src_cfg_type for details
 * @param[in] enable:        FALSE: 0, TRUE: 1
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_hs_batif_cfg_batt_missing_src(uint32 bus_id, uint32 pmic_index, pm_scpq_hs_batif_bat_miss_src_cfg_type bat_miss_cfg, boolean enable);

/**
* @brief This function sets the JEITA temperature thresholds
*
* @details
*  This API configures the JEITA temperature thresholds for soft and hard limits.
*
* @param[in] bus_id: SPMI Bus id
* @param[in] device_index.  Primary: 0 Secondary: 1, etc.
* @param[in] pm_scpq_hs_batif_jeita_threshold_type       Jeita zone to be configured
* @param[in] jeita_threshold      Temperature value for the JEITA zone
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*          version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type
pm_scpq_hs_batif_set_jeita_threshold_value(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_threshold_type threshold_type, uint32 jeita_threshold);


/**
* @brief This function gets the JEITA adc code
*
* @details
*  This API gets the JEITA adc code.
*
* @param[in] bus_id: SPMI Bus id
* @param[in] device_index.  Primary: 0 Secondary: 1, etc.
* @param[in] pm_scpq_hs_batif_jeita_threshold_type       Jeita zone
* @param[out] jeita_threshold      adc value for the JEITA zone
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*          version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type
pm_scpq_hs_batif_get_jeita_threshold_value(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_threshold_type threshold_type, uint16* jeita_threshold);


/**
* @brief This function helps enable HW JEITA related parameters. 
* 
* @details
*  This function helps enable HW JEITA related parameters. 
* 
* @param[in] bus_id: SPMI Bus id
* @param[in] device_index.  Primary: 0 Secondary: 1
* @param[in] jeita_cfg_type      JEITA config type see pm_scpq_hs_batif_jeita_cfg_type for details
* @param[in] enable              Enables the config; 0: FALSE, 1: TRUE 
*
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*          version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type
pm_scpq_hs_batif_jeita_en_cfg(uint32 bus_id, uint32 device_index, pm_scpq_hs_batif_jeita_cfg_type jeita_cfg_type, boolean enable);

#endif /* __PM_SCPQ_HS_BATIF_H__*/

