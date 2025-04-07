/**
 * @file dtb_test_framework.c
 * @brief
 * Source file for DTB Tests.
 *
 * Copyright 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc
 *
 */

/*==========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who        what, where, why
--------   ---        ---------------------------------------------------------
09/20/23   tmt        Initial creation of file

===========================================================================*/

/*==========================================================================
                             INCLUDE FILES
===========================================================================*/

#include "boot_config_context.h"

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/

// Flags to enable DTB Tests

// NOTE NOTE NOTE NOTE NOTE NOTE NOTE
// When enabling any of these tests you will usually have to tweak these files:
//   .../QcomPkg/SocPkg/libsizecfg.json
//   .../QcomPkg/SocPkg/<SOC>/include/Soc_cust.h : #define SCL_SBL1_IMAGE_SIZE
//      Increase in chunks of 0x4000

//#define NON_RECURSIVE_PERFORMANCE_ANALYSIS_ENABLED
extern bl_error_boot_type NonRecursivePerformanceAnalysis(boot_handle config_context_handle);

//#define WRITE_DTB_ON_THE_FLY_ENABLED
extern void WriteDTBOnTheFly(boot_handle config_context_handle);

//#define READ_DTB_ON_THE_FLY_ENABLED
extern 	void ReadDTBOnTheFly(boot_handle config_context_handle);

// Test Framework Global Entry-Point
void dtb_test_framework(boot_handle config_context_handle) {
#ifdef NON_RECURSIVE_PERFORMANCE_ANALYSIS_ENABLED
	NonRecursivePerformanceAnalysis(config_context_handle);
#endif
#ifdef WRITE_DTB_ON_THE_FLY_ENABLED
	WriteDTBOnTheFly(config_context_handle);
#endif
#ifdef READ_DTB_ON_THE_FLY_ENABLED
	ReadDTBOnTheFly(config_context_handle);
#endif
}
