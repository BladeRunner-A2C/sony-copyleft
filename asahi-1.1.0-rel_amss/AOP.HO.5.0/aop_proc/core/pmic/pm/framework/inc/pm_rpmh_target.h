#ifndef PM_RPMH_TARGET_H
#define PM_RPMH_TARGET_H

/*! \file pm_rpmh_target.h
*  \n
*  \brief This file contains PMIC function prototypes for sleep related functions.
*  \n
*  &copy; Copyright 2013-2015 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/core/pmic/pm/framework/inc/pm_rpmh_target.h#1 $  

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/24/14   kt      Updated comments header and added doxygen comments.
08/16/13   hs      Initial version. 
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_app_pwr.h"

/*===========================================================================

                        MACRO DEFINITIONS 

===========================================================================*/


/*===========================================================================

                        GENERIC FUNCTION PROTOTYPES

===========================================================================*/

/** 
 * @name pm_rpmh_sleep_init 
 *  
 * @brief This function initializes the sleep settings LUT.
 * 
 * @param None
 *
 * @return pm_err_flag_type 
 *  
 * @dependencies Sleep settings should be available in config.
 *
 */
pm_err_flag_type pm_rpmh_sleep_init(void);

/** 
 * @name pm_rpmh_platform_init 
 *  
 * @brief This function initialize the platform specific 
 *        settings.
 * 
 * @param None
 *
 * @return pm_err_flag_type 
 *  
 * @sideeffects None
 *
 */
pm_err_flag_type pm_rpmh_platform_init(void);

/** 
 * @name pm_rpmh_platform_post_init 
 *  
 * @brief This function initalizes the platform settings post 
 *        pmic_init
 * 
 * @param None
 *
 * @return pm_err_flag_type 
 *  
 * @sideeffects None
 *
 */
pm_err_flag_type pm_rpmh_platform_post_init(void);

/**
* @brief This function initialize the platform specific settings
*        prior to drivers initialization
* 
* @param none
*
* @return pm_err_flag_type
*
*/
pm_err_flag_type pm_rpmh_platform_pre_init (void);

/**
* @brief This function is used to stubbed pmic driver for particular target
*        
* 
* @param none
*
* @return pm_err_flag_type
*
*/
boolean pm_is_target_specific_stub_enable(void);

/**
* @brief This function updates the PMIC resource config based on
*        platform specific settings before
*        registering/configuring the resource in RPMh VRM.
* 
* @param PMIC resource data
*
* @return pm_err_flag_type
*
*/
pm_err_flag_type pm_rpmh_update_rsrc_config(vrm_pmic_rsrc_data* data, uint8* access_allowed);

pm_err_flag_type pm_rpmh_pmic_detect_err_init(void);

pm_err_flag_type pm_rpmh_target_core_rail_set_voltage( pm_core_rail_name rail ,uint64 voltage_uV, pm_request_type active_ret);

/**
 * @brief This function detect the ext TCXO attach based on SDAM value
 *
 * @param ext_tcxo: pointer to bool variable to store SDAM read data
 *
 * @return 
 *     PM_ERR_FLAG_SUCCESS if the read is success
 *     PM_ERR_FLAG_FAILURE if the read fails
 */
pm_err_flag_type pm_rpmh_ext_tcxo_present(bool *ext_tcxo);

#endif /* PM_RPMH_TARGET_H */
