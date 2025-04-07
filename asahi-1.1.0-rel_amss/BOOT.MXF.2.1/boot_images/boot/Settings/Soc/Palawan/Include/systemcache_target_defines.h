#ifndef SYSTEMCACHE_TARGET_DEFINES_H_
#define SYSTEMCACHE_TARGET_DEFINES_H_

/*===============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc. All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  FILE:                 systemcache_defines.h

  REVISION HISTORY
  when       who       what, where, why
  --------   ---       ----------------------------------------------------------
  09/07/23   vencha      Created
================================================================================*/

#define LLCC0_TRP_REG_BASE_OFFSET 0x1000000
#define LLCC1_TRP_REG_BASE_OFFSET 0x1400000
#define LLCC2_TRP_REG_BASE_OFFSET 0x1200000
#define LLCC3_TRP_REG_BASE_OFFSET 0x1600000
#define LLCC_BROADCAST_ANDTRP_REG_BASE_OFFSET 0x1A00000

#define LLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RESRVED_WAYS_SHFT 0
#define LLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RESRVED_WAYS_BMSK 0x3FFF
#define LLCC_TRP_SCT_n_ATTRIBUTE2_CFG_BONUS_WAYS_SHFT 0
#define LLCC_TRP_SCT_n_ATTRIBUTE2_CFG_BONUS_WAYS_BMSK 0x3FFF

#endif // SYSTEMCACHE_TARGET_DEFINES_H_
