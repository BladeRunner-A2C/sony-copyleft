#ifndef SYSTEMCACHE_DEFINES_H_
#define SYSTEMCACHE_DEFINES_H_

/*===============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc. All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  FILE:                 systemcache_defines.h

  REVISION HISTORY
  when       who       what, where, why
  --------   ---       ----------------------------------------------------------
  09/07/23   vencha      Created
================================================================================*/

/* System Cache Modes */
#define CACHE_MODE_NORMAL   0x0
#define CACHE_MODE_TCM      0x1
#define CACHE_MODE_NSE      0x2
#define CACHE_MODE_RESERVED 0x3 /* defaults to TCM_MODE */

#define TRUE  1
#define FALSE 0

/*SystemCache USECASE ID List*/
#define RESERVE         0
#define CPUSS           1
#define VIDSC0          2
#define AUDIO           6
#define MODEMHP_GROW    7
#define MODEMHW         9
#define COMPUTE        10
#define GPUHTW         11
#define GPU            12
#define MMUHWT         13
#define DISPLAY        16
#define MODEMHP_FIX    20
#define MODEM_PAGING   21
#define AUDIOHW        22
#define CVP            28
#define MODEM_VPE      29
#define WRITE_CACHE    31
#define CAMERA_EXP0    34
#define CPU_HWT        36
#define CAMERA_EXP1    38
#define COMPUTE_HCP    39
#define LCP_DARE       40
#define AUDIO_ENPU     45
#define ISLAND_1       46
#define ISLAND_2       47
#define ISLAND_3       48
#define ISLAND_4       49
#define CAMERA_EXP2    50
#define CAMERA_EXP3    51
#define CAMERA_EXP4    52
#define DISPLAY_WB     53
#define DISPLAY_1      54
#define VIDSC_VSP      64

#endif /* SYSTEMCACHE_DEFINES_H_ */
