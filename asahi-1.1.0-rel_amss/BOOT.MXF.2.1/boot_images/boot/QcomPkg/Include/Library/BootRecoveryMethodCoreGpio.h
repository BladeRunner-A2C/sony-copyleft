/**
# @file BootRecoveryMethodCoreGpio.h
#
#  check if Boot recovery GPIO method is enabled and boot set to boot
#
#  Copyright 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
#
#**/

/*==============================================================================
#                              EDIT HISTORY
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 04/13/23   ac      Initial Revision
#
#==============================================================================*/

#ifndef __BOOT_RECOVERY_METHOD_CORE_GPIO_H__
#define __BOOT_RECOVERY_METHOD_CORE_GPIO_H__


/* -------- RecoveryInfoCoreGpio APIs ------------------------- */
EFI_STATUS RecoveryBootIsGpioMethodEnabled (UINT8 *IsGpioMethodEnabled);
EFI_STATUS RecoveryBootGetGpioBootSet (UINT32 *GpioBootSet);

#endif
