#ifndef XBL_TRIAL_BOOT_H
#define XBL_TRIAL_BOOT_H

/*=============================================================================

                            XBL TRIALBOOT Module Sources

GENERAL DESCRIPTION
  This file defines XBL Trial Boot api's.

Copyright 2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
09/16/22     sp      Initial version
===========================================================================*/

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/

/*===========================================================================
**  Function :  boot_handle_trial_boot
** ==========================================================================
*/
/*!
* 
* @brief
*   This function handles trial boot. Checks for feature enable bit & number of failed attempts 
*   and switches to set B once max attempts reached. And keeps storage partition and tcsr values in sync
*
* @param[in] boot_handle
*
* @par Dependencies
*   None
*
*/
bl_error_boot_type boot_handle_trial_boot(boot_handle config_context_handle);

#endif /* XBL_TRIAL_BOOT_H */