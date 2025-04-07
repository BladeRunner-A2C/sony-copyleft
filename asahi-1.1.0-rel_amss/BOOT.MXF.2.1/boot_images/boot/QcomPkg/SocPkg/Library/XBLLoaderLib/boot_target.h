

#ifndef _BOOT_TARGET_H
#define _BOOT_TARGET_H

/*===========================================================================

                                boot_target
                                Header File

GENERAL DESCRIPTION
  This header file contains target specific declarations and definitions

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2014 - 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/SocPkg/Library/XBLLoaderLib/boot_target.h#1 $
  $DateTime: 2024/04/02 23:00:31 $ 
  $Author: cirrusp4svc $

when       who          what, where, why
--------   --------     ----------------------------------------------------------
07/14/22   rhy          Rename Timestamp to AOSS timestamp
12/22/22   rhy          Added ifdefs for AOP region. Code cleanup
12/21/22   krd          added kuno arm flag for shrm region dump
12/19/22   krd          added shrm dmem region seperate for kuno
05/25/22   rama         Changes for dynamic ramdump entries count
03/15/22   ck           Added initial ECPRI_MEMORY_REGION_TABLE
03/18/21   ds           shrm imem dump change
03/03/21   ds           enable DCC regions
02/20/21   ds           add additional dump regions
01/18/21   yps          Comment out some regions which are not in memory map
12/11/20   ds           aop_config image loading changes
11/01/20   ds           Blacklist and flex whitelist feature support
08/17/20   ds           shrm whitelist update
07/28/20   ds           waipio updates for whitelist and mem regions
07/27/20   rakhi        Increased MAX_CRASHDUMP_TABLE_ENTRIES to 300
02/25/20   ck           Moved AARCH64 MMU PT definitions to boot_page_table_armv8.h
11/26/19   sp           Updtaed QHEE_IMG_WHITELIST
08/07/19   yps          Removed PMIC config temp buffer from white list table
01/22/19   yps          Added new definitions accordeing to new ld file
08/29/18   msantos      added SBL crash dump region to table
02/13/18   vk           Update IPA regions
01/19/18   vk           Add FlexSku
08/24/17   yps          Increased crash dump  table entries
05/08/17   kpa          update STI_IMG_WHITELIST
05/09/17   sj           define pmic device index
04/27/17   kpa          enable dumping DCC SRAM region
04/13/17   kpa          Added MAX_CRASHDUMP_TABLE_ENTRIES
04/08/17   kpa          remove SHRM_IMG_WHITELIST
03/03/17   ds           update aop whtlist
02/22/17   ds           fix abl and devcfg whitelist area
01/27/16   digants      Added Defines for whitelist address ranges for each image
07/14/16   kedara       Initial version for SDM845
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#ifndef _ARM_ASM_
#include "boot_comdef.h"
#endif /* _ARM_ASM_ */

/*===========================================================================
              DEFINES FOR TARGET (equivalent to <target>.builds src)
===========================================================================*/
#include "Target_cust.h"
/*===========================================================================
                   DEFINES FOR MEMORY MAP, COMMON FEATURE DEFINES
===========================================================================*/
#include "tzbsp_fuseprov_chipset.h"

/*===========================================================================
                      DEFINES FOR RAMDUMPS / FEATURE ENABLE 
===========================================================================*/
#define FEATURE_BOOT_RAMDUMPS_TO_SD_CARD
#define CONVERT_TO_MB_SHIFT 20
#define SD_PATH "/fs_mnt/"
#define SD_RAM_DUMP_PATH SD_PATH "ram_dump/"

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE: The region name should be 8.3 format beacuase SDCARD is FAT formatted. */
/*       eg. CODERAM.BIN                                                        */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#define MEMORY_REGION1  {SCL_IMEM_BASE,         SCL_IMEM_SIZE,         "OCIMEM",                "OCIMEM.BIN" },
#define MEMORY_REGION2  {SCL_AOP_CODE_RAM_BASE, SCL_AOP_CODE_RAM_SIZE, "AOP Code RAM region",   "CODERAM.BIN"},
#define MEMORY_REGION3  {SCL_AOP_DATA_RAM_BASE, SCL_AOP_DATA_RAM_SIZE, "AOP Data RAM region",   "DATARAM.BIN"},
#ifdef SCL_AOP_MSG_RAM0_BASE    
    #define MEMORY_REGION4 {SCL_AOP_MSG_RAM1_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM0 region", "MSGRAM0.BIN"},     
#else
    #define MEMORY_REGION4
#endif
#ifdef SCL_AOP_MSG_RAM1_BASE    
    #define MEMORY_REGION5 {SCL_AOP_MSG_RAM1_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM1 region", "MSGRAM1.BIN"},     
#else
    #define MEMORY_REGION5
#endif
#ifdef SCL_AOP_MSG_RAM2_BASE    
    #define MEMORY_REGION6 {SCL_AOP_MSG_RAM2_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM2 region", "MSGRAM2.BIN"},     
#else
    #define MEMORY_REGION6
#endif
#ifdef SCL_AOP_MSG_RAM3_BASE    
    #define MEMORY_REGION7 {SCL_AOP_MSG_RAM3_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM3 region", "MSGRAM3.BIN"},     
#else
    #define MEMORY_REGION7
#endif
#ifdef SCL_AOP_MSG_RAM4_BASE    
    #define MEMORY_REGION8 {SCL_AOP_MSG_RAM4_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM4 region", "MSGRAM4.BIN"},     
#else
    #define MEMORY_REGION8
#endif
#ifdef SCL_AOP_MSG_RAM5_BASE    
    #define MEMORY_REGION9 {SCL_AOP_MSG_RAM5_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM5 region", "MSGRAM5.BIN"},     
#else
    #define MEMORY_REGION9
#endif
#ifdef SCL_AOP_MSG_RAM6_BASE    
    #define MEMORY_REGION10 {SCL_AOP_MSG_RAM6_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM6 region", "MSGRAM6.BIN"},     
#else
    #define MEMORY_REGION10
#endif
#ifdef SCL_AOP_MSG_RAM7_BASE    
    #define MEMORY_REGION11 {SCL_AOP_MSG_RAM7_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM7 region", "MSGRAM7.BIN"},     
#else
    #define MEMORY_REGION11
#endif
#ifdef SCL_AOP_MSG_RAM8_BASE    
    #define MEMORY_REGION12 {SCL_AOP_MSG_RAM8_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM8 region", "MSGRAM8.BIN"},     
#else
    #define MEMORY_REGION12
#endif
#ifdef SCL_AOP_MSG_RAM9_BASE    
    #define MEMORY_REGION13 {SCL_AOP_MSG_RAM9_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM9 region", "MSGRAM9.BIN"},     
#else
    #define MEMORY_REGION13
#endif
#ifdef SCL_AOP_MSG_RAM10_BASE    
    #define MEMORY_REGION14 {SCL_AOP_MSG_RAM10_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM10 region", "MSGRAM10.BIN"},     
#else
    #define MEMORY_REGION14
#endif
#ifdef SCL_AOP_MSG_RAM11_BASE    
    #define MEMORY_REGION15 {SCL_AOP_MSG_RAM11_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM11 region", "MSGRAM11.BIN"},     
#else
    #define MEMORY_REGION15
#endif
#ifdef SCL_AOP_MSG_RAM12_BASE    
    #define MEMORY_REGION16 {SCL_AOP_MSG_RAM12_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM12 region", "MSGRAM12.BIN"},     
#else
    #define MEMORY_REGION16
#endif
#ifdef SCL_AOP_MSG_RAM13_BASE    
    #define MEMORY_REGION17 {SCL_AOP_MSG_RAM13_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM13 region", "MSGRAM13.BIN"},     
#else
    #define MEMORY_REGION17
#endif
#ifdef SCL_AOP_MSG_RAM14_BASE    
    #define MEMORY_REGION18 {SCL_AOP_MSG_RAM14_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM14 region", "MSGRAM14.BIN"},     
#else
    #define MEMORY_REGION18
#endif
#ifdef SCL_AOP_MSG_RAM15_BASE    
    #define MEMORY_REGION19 {SCL_AOP_MSG_RAM15_BASE, SCL_AOP_MSG_RAMX_SIZE, "AOP MSGRAM15 region", "MSGRAM15.BIN"},     
#else
    #define MEMORY_REGION19
#endif

#define MEMORY_REGION20 {SHRM_IMEM_SHRM_IRAM_BASE,          SHRM_TOTAL_DUMP_MEM_SIZE,   "SHRM MEM region",  "SHRM_MEM.BIN"},
#define MEMORY_REGION21 {SCL_DCC_LL_SRAM_BASE,              SCL_DCC_LL_SRAM_SIZE,       "DCC SRAM region",  "DCC_SRAM.BIN"},
#define MEMORY_REGION22 {SCL_DCC_CFG,                       SCL_DCC_CFG_SIZE,           "DCC CFG region",   "DCC_CFG.BIN"},
#define MEMORY_REGION23 {BOOT_CRASH_DUMP_DATA_DUMP_ADDR,    BOOT_CRASH_DUMP_DATA_SIZE,  "CD STRCT region",  "CD_STRCT.BIN"},
#define MEMORY_REGION24 {SCL_SBL1_DDR_DUMP_ADDR,            SCL_SBL1_DDR_SIZE,          "CD BTDDR region",  "CD_BTDDR.BIN"},
#define MEMORY_REGION25 {SCL_BOOT_IMEM_DUMP_ADDR,           SCL_BOOT_IMEM_BASE_SIZE,    "CD BTIMM region",  "CD_BTIMM.BIN"},
#define MEMORY_REGION26 {SHARED_IMEM_DUMP_ADDR,             SHARED_IMEM_SIZE,           "CD SHIMM region",  "CD_SHIMM.BIN"},
#define MEMORY_REGION27 {SCL_CPUCPFW_BASE,                  SCL_CPUCPFW_SIZE,           "CPUCPFW region",   "CPUCPFW.BIN" },
#ifdef ARM32BIT_TARGET
    #define MEMORY_REGION28 {SHRM_DMEM_SHRM_DRAM_BASE,  SHRM_TOTAL_DUMP_MEM_SIZE,       "SHRM DRAM region", "SHRMDMEM.BIN"},
#else
    #define MEMORY_REGION28
#endif
#define MEMORY_REGION29 {SCL_IPA_IU_BASE,   SCL_IPA_IU_SIZE,   "IPA IRAM region", "IPA_IU.BIN"  },
#define MEMORY_REGION30 {SCL_IPA_SRAM_BASE, SCL_IPA_SRAM_SIZE, "IPA SRAM region", "IPA_SRAM.BIN"},
#define MEMORY_REGION31 {SCL_IPA_HRAM_BASE, SCL_IPA_HRAM_SIZE, "IPA HRAM region", "IPA_HRAM.BIN"},
#define MEMORY_REGION32 {SCL_IPA_MBOX_BASE, SCL_IPA_MBOX_SIZE, "IPA MBOX region", "IPA_MBOX.BIN"},
#define MEMORY_REGION33 {SCL_IPA_GSI_BASE,  SCL_IPA_GSI_SIZE,  "IPA GSI  region", "IPA_GSI.BIN" },
#define MEMORY_REGION34 {SCL_IPA_SEQ_BASE,  SCL_IPA_SEQ_SIZE,  "IPA SEQ region",  "IPA_SEQ.BIN" },

// Note: No Comma (',') after Last Memory region
#define MEMORY_REGION_LAST {0, 0, NULL, NULL}

// Note: Memory region separated by spaces. Make sure to include Comma (,) at the end of individual Memory region
#define MEMORY_REGION_TABLE MEMORY_REGION1 MEMORY_REGION2 MEMORY_REGION3 MEMORY_REGION4 MEMORY_REGION5 MEMORY_REGION6 MEMORY_REGION7 MEMORY_REGION8 MEMORY_REGION9 MEMORY_REGION10 MEMORY_REGION11 MEMORY_REGION12 MEMORY_REGION13 MEMORY_REGION14 MEMORY_REGION15 MEMORY_REGION16 MEMORY_REGION17 MEMORY_REGION18 MEMORY_REGION19 MEMORY_REGION20 MEMORY_REGION21 MEMORY_REGION22 MEMORY_REGION23 MEMORY_REGION24 MEMORY_REGION25 MEMORY_REGION26 MEMORY_REGION27 MEMORY_REGION28 MEMORY_REGION_LAST
#define ECPRI_MEMORY_REGION_TABLE MEMORY_REGION_LAST

//pmic device index
#define PMIC_DEVICE_INDEX 1
#define DLOAD_PMIC_WDG_S1_VALUE      110
#define DLOAD_PMIC_WDG_S2_VALUE      120

#define FEATURE_TPM_HASH_POPULATE

/*===========================================================================
  Definitions of address range where IMEM exists on the MSM.
===========================================================================*/
#define IMEM_RANGE_START_ADDR SCL_IMEM_BASE
#define IMEM_RANGE_END_ADDR   (SCL_IMEM_BASE+SCL_IMEM_SIZE)


/*===========================================================================
  Definition for the end address of SDRAM on the MSM.
  MAX value for 48 bits (2^48) -1
===========================================================================*/
#define RANGE_END_ADDR        0xFFFFFFFFFFFFUL


/*===========================================================================
                      BOOT LOGGER DEFINES
===========================================================================*/

/*=========================================================================== 
  The clock that is used to track time passing.
===========================================================================*/
#define TIMETICK_CLK  MPM_SLEEP_TIMETICK_COUNT_VAL 

/*=========================================================================== 
  Clock frequency is 32.768 KHz
  The number of microseconds per cycle is:
  1 / (32.768 KHz) = 30.52ms
  The int part is 30
===========================================================================*/
#define TIMETICK_CLK_SPEED_INT       30

/*=========================================================================== 
  MPM Sleep Clock frequency is 32.768 KHz
  The number of microseconds per cycle is:
  1 / (32.768 KHz) = 30.52us
  we round 0.52 to 1/2.
  Timestamp is calculated as : count*int + count/2
  Floating point arithmetic should not be used to avoid error and speed penalty
===========================================================================*/
#define CALCULATE_AOSS_SLEEP_CNTR_US(COUNT) \
  ((COUNT)*TIMETICK_CLK_SPEED_INT + (COUNT)/2)

/*=========================================================================== 
  Qtimer Clock frequency is CXO 19.2MHz
  The number of microseconds per cycle 1/19.2
===========================================================================*/
#define CALCULATE_QTIMER_TIMESTAMP(COUNT) \
  ((COUNT)/19.2)
  
/*
  we are using 32 bits timestamp, the max counter value is:
  0xFFFFFFFF/31 = 138547732
  after this value the timestamp will overflow
*/
#define LOG_MAX_COUNT_VAL  138547732

/* Define the SD Ram Dump Indicator LED */
#define RAM_DUMP_LED  PM_RGB_SEGMENT_B

/* Define the DDR training Indicator LED */
#define DDR_TRAINING_LED PM_RGB_SEGMENT_G


#endif  /* _BOOT_TARGET_H */
