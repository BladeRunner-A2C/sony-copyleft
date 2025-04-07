/*=============================================================================   
    @file  qntm_tz_memmap_defines.h
    @brief interface to device configuration
   
    Copyright (c) Qualcomm Technologies, Inc. All Rights Reserved.
    Confidential and Proprietary - Qualcomm Technologies, Inc
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 09/05/23   kk      Added new include file.
=============================================================================*/

// IMEM Configuration
#define SHARED_IMEM_OFFSET_ADDR     0x0
#define IMEM_HYP_OFFSET_ADDR        0x00000B20
#define IMEM_TZ_DIAG_OFFSET_ADDR    0x00000720
#define SYSTEM_IMEM_TZ_OFFSET_ADDR  0x13000
#define SYSTEM_IMEM_TZ_SIZE_ADDR    0x19000
#define NUM_OF_CLUSTERS             2
#define NUM_OF_CPUS_PER_CLUSTER     4

// App Region Configuration
#define SCL_TZ_DDR_OFFSET_ADDR      0x68F80000
#define SCL_TZ_DDR_SIZE_ADDR        0x500000
#define TZ_APPS_REGION_SIZE_ADDR    0x1200000
