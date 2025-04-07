/*! \file pm_app_vrm_init.c
 *  \n
 *  \brief Implementation file for VRM resource related application level APIs. 
 *  \n  
 *  \n &copy; Copyright 2016 - 2017 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/core/pmic/pm/app/vrm/src/init/pm_app_vrm_init.c#1 $
 
when        who     what, where, why
--------    ---     ----------------------------------------------------------
11/23/16    kt       Created
03/06/23	bde		Configurable min_settling_time_poll_thr
========================================================================== */
/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_app_vrm_init.h"
#include "pm_debug.h"
#include "pm_rpmh_target.h"
#include "pm_app_pwr.h"
#include "pm_config_target.h"
#include "aop_settings.h"


//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

//Default value, if value not provided through prop id interface

#define PM_MIN_SETTLING_TIME_POLL_THR     600 //uS

//******************************************************************************
// Global Data
//******************************************************************************

extern pm_app_vrm_info_type pm_app_vrm_info;


/* The minimum settling time resource needs to be given to settle
   while polling for vreg READY/OK status */
   
extern uint32 min_settling_time_poll_thr; //us

/*===========================================================================

                     API IMPLEMENTATION 

===========================================================================*/
__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_app_vrm_init()
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
         
    pm_debug_info_type *pmic_debug = pm_get_debug_info();
    CORE_VERIFY_PTR(pmic_debug);
    pmic_debug->pm_app_vrm_info = &pm_app_vrm_info;

    if (pm_app_vrm_info.initialized == FALSE)
    {
        // initialize the pmic app vrm lock
        pm_app_vrm_info.lock_count = 0;
        pm_lock_init(&pm_app_vrm_info.lock);

        pm_app_vrm_info.initialized = TRUE;
    }

	aop_settings_handle dev_id = get_settings_handle("pmic");
	if(dev_id == NULL)
	{
		CORE_VERIFY(0);
	}	
	uint32 *min_settling_time_poll_thr_ptr = (uint32*)get_aop_settings_prop_val(dev_id, "PM_PROP_MIN_SETTLING_TIME_THR");
	
	min_settling_time_poll_thr = ((min_settling_time_poll_thr_ptr!= NULL )&&(*min_settling_time_poll_thr_ptr > PM_MIN_SETTLING_TIME_POLL_THR))? *min_settling_time_poll_thr_ptr : PM_MIN_SETTLING_TIME_POLL_THR;
    return err_flag;
}
