/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 19/10/21  zxue     refine code and remove the diag log
 9/26/21   zxue     support qcom based wall timer
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __CONFIG_H
#define __CONFIG_H

#include <Library/PcdLib.h>

// Default Security boot is not support on X86
#ifndef SUPPORT_SECURITY_BOOT
#define SUPPORT_SECURITY_BOOT 0
#endif

#ifndef SUPPORT_LOAD_BY_EVT
#define SUPPORT_LOAD_BY_EVT 0
#endif

#ifndef SUPPORT_RECOVERY_FROM_PARTITION
#define SUPPORT_RECOVERY_FROM_PARTITION 0
#endif

//
// Features only available on QCOM platform
//
#ifndef SUPPORT_QCOM_BASE_LIB
#define SUPPORT_QCOM_BASE_LIB 0
#endif

#ifndef SUPPORT_QCOM_DPP
#define SUPPORT_QCOM_DPP 0
#endif

#ifndef SUPPORT_QCOM_PARTITION
#define SUPPORT_QCOM_PARTITION 0
#endif

#if FixedPcdGetBool(PcdAth11kEnabled)
#define SUPPORT_DRIVER_ATH11K 1
#endif

#ifndef SUPPORT_DRIVER_ATH11K
#define SUPPORT_DRIVER_ATH11K 0
#endif

//
// Logging
//
#ifndef SUPPORT_DEBUG_PRINT
#define SUPPORT_DEBUG_PRINT 1
#endif

#if SUPPORT_DEBUG_PRINT
// WMI_DIAG_LOG
#define SUPPORT_WMI_DIAG_LOG 1
#endif

#endif // !__CONFIG_H