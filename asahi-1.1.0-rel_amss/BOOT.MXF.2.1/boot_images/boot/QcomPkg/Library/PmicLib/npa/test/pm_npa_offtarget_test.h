#ifndef PM_NPA_OFFTARGET_TEST_H
#define PM_NPA_OFFTARGET_TEST_H
/*===========================================================================


                  P M    NPA   H E A D E R    F I L E

DESCRIPTION
  This file contains prototype definitions to support interaction
  with the QUALCOMM Power Management ICs.

Copyright (c) 2010 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/npa/test/pm_npa_offtarget_test.h#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/31/10   umr     Created.
===========================================================================*/
/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */


/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/


/*===========================================================================

                        DEFINITIONS

===========================================================================*/
/*===========================================================================

                        GENERIC FUNCTION PROTOTYPES

===========================================================================*/
void
pm_core_npa_offtarget_init (void);

void
pm_core_npa_offtarget_close (void);

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* PM_NPA_OFFTARGET_TEST_H */
