#ifndef __PM_APP_USBPD_H__
#define __PM_APP_USBPD_H__

/*! \file
*  \n
*  \brief  pm_app_usbpd.h PMIC USBPD app RELATED DECLARATION 
*  \details  This header file contains functions and variable declarations 
*  to support Qualcomm charger module.
*  \n &copy; Copyright 2020-2023 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "pm_pdphy.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

/**
* @brief This function checks for the driver entrance condition / SDAM clearing condition
*
*/
void pm_app_usbpd_start();

#endif /*__PM_APP_USBPD_H__*/
