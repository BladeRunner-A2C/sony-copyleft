#ifndef __PM_SCHG_BATIF_H__
#define __PM_SCHG_BATIF_H__

/*! \file
*  \n
*  \brief  pm_schg_batif.h PMIC-SCHG MODULE RELATED DECLARATION
*  \details  This header file contains functions and variable declarations
*  to support Qualcomm PMIC SCHG BAT IF (Switch-Mode Battery Charger) module. The
*  Switched-Mode Battery Charger (SCHG OTG) module includes a buck regulated
*  battery charger with integrated switches. The SCHG OTG module, along with the
*  Over Voltage Proection (OVP) module will majorly be used by charger
*  appliation for charging Li-Ion batteries with high current (up to 2A).
*  \n &copy;
*  Copyright (c) 2016-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who    what, where, why
--------    ---    ----------------------------------------------------------
08/01/18    ivy    Added API to set batt therm pull up to register
06/21/18    cs     added fake battery detection support.
02/28/18    pxm    Remove unused APIs. Refine code
03/01/16    sm     Added pm_schg_batif_cfg_batt_missing_src()
02/16/16    va     Adding required API for enabling charger
01/14/16    al     Initial version.
========================================================================== */
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

/*! \enum pm_schg_irq_bit_field_type
   \brief different types of irq bit fields of by smbch_bat_if irq module
 */
typedef enum
{
  PM_SCHG_BATIF_BAT_TEMP,
  PM_SCHG_BATIF_ALL_CH_CONV_DONE,
  PM_SCHG_BATIF_BAT_OV,
  PM_SCHG_BATIF_BAT_LOW,
  PM_SCHG_BATIF_BAT_THERM_OR_ID_MISSING,
  PM_SCHG_BATIF_BAT_TERMINAL_MISSING,
  PM_SCHG_BATIF_BUCK_OC_OV,
  PM_SCHG_BATIF_VPH_OV,
  PM_SCHG_BATIF_IRQ_INVALID
} pm_schg_batif_irq_type;

typedef enum
{
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P0,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P1,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P2,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P3,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P4,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P5,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P6,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P7,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P8,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_5P9,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_6P0,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_6P1,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_6P2,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_6P3,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_6P4,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_6P5,
  PM_SCHG_BATIF_LOW_BATTERY_THRESH_INVALID
} pm_schg_batif_low_battery_threshold;

typedef enum
{
  PM_SCHG_BAT_MISS_SRC_CFG__PIN_SRC_EN = 0,
  PM_SCHG_BAT_MISS_SRC_CFG__BAT_MISS_ALG_EN = 2, // value is 2 bacause register bit for this config is 2, 1 is RESERVED.
  PM_SCHG_BAT_MISS_SRC_CFG__INVALID
} pm_schg_batif_bat_miss_src_cfg_type;

typedef enum
{
  PM_SCHG_BAT_MISS_THERM_CMP = 0,
  PM_SCHG_BAT_MISS_BAT_ID_BMISS_CMP,
  PM_SCHG_BAT_MISS_FAKE_BAT_DET,
  PM_SCHG_BAT_MISS_INVALID
} pm_schg_batif_bat_miss_status_type;

typedef enum
{
  PM_SCHG_BATIF_PULL_UP_BAT_THM = 0,
  PM_SCHG_BATIF_PULL_UP_MISC_THM = 2,
  PM_SCHG_BATIF_PULL_UP_CONN_THM = 4,
  PM_SCHG_BATIF_PULL_UP_SMB_THM = 6,
  PM_SCHG_BATIF_PULL_UP_INVALID
} pm_schg_batif_adc_pull_up_type;

typedef enum
{
  PM_SCHG_BATIF_PULL_UP_RES_NONE,
  PM_SCHG_BATIF_PULL_UP_RES_30K,
  PM_SCHG_BATIF_PULL_UP_RES_100K,
  PM_SCHG_BATIF_PULL_UP_RES_400K,
  PM_SCHG_BATIF_PULL_UP_RES_INVALID,
} pm_schg_batif_adc_pull_up_res_type;

/*===========================================================================

                 SCHG BAT_IF DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/*Enable Pmic Ship Mode */
/**
 * @brief This function Enables Pmic Ship Mode.
 *
 * @details
 *  This function Enables Pmic Ship Mode.
 *
 * @param[in]  bus_id:
 *               0 for primary spmi bus
 *               1 for secondary spmi bus
 * 
 * @param[in] pmic_index:         The pmic_index of charger module.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *                                              version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_schg_batif_enable_shipmode(uint32 bus_id, uint32 pmic_index);

/**
* @brief This function enables IRQ
*
* @details
*  This function enables IRQ
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[in] irq                 pm_schg_batif_irq_type
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_batif_irq_enable(uint32 bus_id, uint32 pmic_index, pm_schg_batif_irq_type irq, boolean enable);

/**
* @brief This function clears the SCHG irq
*
* @details
*  This function clears the SCHG irq
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[in] irq                 pm_schg_batif_irq_type
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_batif_irq_clear(uint32 bus_id, uint32 pmic_index, pm_schg_batif_irq_type irq);

/**
* @brief This function configures the SCHG irq trigger
*
* @details
*  This function configures the SCHG irq trigger
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[in] irq                 pm_schg_batif_irq_type
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_batif_irq_set_trigger(uint32 bus_id, uint32 pmic_index, pm_schg_batif_irq_type irq, pm_irq_trigger_type trigger);

/**
* @brief This function configures the SCHG for irq
*
* @details
*  This function configures the SCHG for irq
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[in] irq                 pm_schg_batif_irq_type
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_batif_irq_status(uint32 bus_id, uint32 pmic_index, pm_schg_batif_irq_type irq, pm_irq_status_type type, boolean *status);

/**
* @brief This function set low battery detect cfg
*
* @details
*  This function sets low battery detect cfg
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[in] lbt_cfg             low batt detect cfg
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_batif_set_low_batt_detect_threshold(uint32 bus_id, uint32 pmic_index, pm_schg_batif_low_battery_threshold lbt_cfg);

/**
* @brief This function configures battery missing source
*
* @details
*  This function configures battery missing source
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[in] bat_miss_cfg        battery missing config type
*                                See pm_schg_batif_bat_miss_src_cfg_type for details
* @param[in] enable.             FALSE: 0 TRUE: 1
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_batif_cfg_batt_missing_src(uint32 bus_id, uint32 pmic_index, pm_schg_batif_bat_miss_src_cfg_type bat_miss_cfg, boolean enable);

/**
* @brief This function gets battery missing and fake battery status
*
* @details
*  This function gets battery missing and fake battery status
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[in] status_type         battery missing status type
*                                See pm_schg_batif_bat_miss_status_type for details
* @param[out] enable.             FALSE: 0 TRUE: 1
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_batt_missing_status(uint32 bus_id, uint32 pmic_index, pm_schg_batif_bat_miss_status_type status_type, boolean *st);

/**
* @brief This function disables fake battery detection for a given pmic
*
* @details
*  This function disables fake battery detection
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[in] enable: TRUE: enable, FALSE: disable
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_batif_enable_fake_bat_detect(uint32 bus_id, uint32 pmic_index, boolean enable);

/**
* @brief This function gets fake battery ID range for a given pmic
*
* @details
*  This function disables fake battery detection
*
* @param[in]  bus_id:
*               0 for primary spmi bus
*               1 for secondary spmi bus
* 
* @param[in] pmic_index:         The pmic_index of charger module.
* @param[out] fake_batid_up_th: upper threshold in adc code
* @param[out] fake_batid_lo_th: lower threshold in adc code
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                              version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/

pm_err_flag_type pm_schg_batif_get_fake_bat_id_th(uint32 bus_id, uint32 pmic_index, uint16* fake_batid_up_th, uint16* fake_batid_lo_th);

#endif /* __PM_SCHG_BATIF_H__*/

