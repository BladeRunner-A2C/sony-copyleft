#ifndef __I2C_DEFINES_H__
#define __I2C_DEFINES_H__


/*=============================================================================   
    @file  i2c_config.h
    @brief interface to device configuration
   
    Copyright (c) 2022-2023 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/10/23   STR     Updated Strongpull config as per HPG
 07/25/23   STR     Updated for Palawan
 06/01/22   gkr     Added Strongpull Support
 09/20/22   ag      Added file for Lanai
=============================================================================*/

// NOTE: QUPs are numbered starting from 0 as per the IO sheet
#define ENABLE_QUP_00
#define ENABLE_QUP_09


// QUPV3_0 [se0 - se7] [0:7]
#define QUPV3_0_CORE_BASE_ADDRESS        0x00A00000
#define QUPV3_0_CORE_COMMON_BASE_ADDRESS 0x00AC0000

// QUPV3_1 [se0 - se7] [8:15]
#define QUPV3_1_CORE_BASE_ADDRESS        0x00800000
#define QUPV3_1_CORE_COMMON_BASE_ADDRESS 0x008C0000

#define TLMM_GPIO_CFG_EX(gpio, func, dir, pull, drive, strongpull) \
                                      (((gpio) & 0x3FF) << 4  | \
                                       ((func) & 0xF  ) << 0  | \
                                       ((dir)  & 0x1  ) << 14 | \
                                       ((pull) & 0x3  ) << 15 | \
                                       ((drive)& 0xF  ) << 17 | \
                                       ((strongpull)& 0x1) << 30)

#define TLMM_GPIO_INPUT             0x0
#define TLMM_GPIO_PULL_UP           0x3
#define TLMM_GPIO_2MA               0x0
#define TLMM_GPIO_STRONG_PULL       0x1
#define TLMM_GPIO_NO_STRONG_PULL    0x0

#define QUP_0   0
#define QUP_1   1

//
// CONFIGURATION START ============================================
//
#define TOP_QUP_00_SDA TLMM_GPIO_CFG_EX(52 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_00_SCL TLMM_GPIO_CFG_EX(53 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_01_SDA TLMM_GPIO_CFG_EX(4  , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
#define TOP_QUP_01_SCL TLMM_GPIO_CFG_EX(5  , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
                                    
#define TOP_QUP_02_SDA TLMM_GPIO_CFG_EX(8  , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_02_SCL TLMM_GPIO_CFG_EX(9  , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_03_SDA TLMM_GPIO_CFG_EX(12 , 2, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_03_SCL TLMM_GPIO_CFG_EX(13 , 2, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_04_SDA TLMM_GPIO_CFG_EX(16 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
#define TOP_QUP_04_SCL TLMM_GPIO_CFG_EX(17 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
                                    
#define TOP_QUP_05_SDA TLMM_GPIO_CFG_EX(20 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_05_SCL TLMM_GPIO_CFG_EX(21 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_06_SDA TLMM_GPIO_CFG_EX(24 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
#define TOP_QUP_06_SCL TLMM_GPIO_CFG_EX(25 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
                                    
#define TOP_QUP_07_SDA TLMM_GPIO_CFG_EX(28 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_07_SCL TLMM_GPIO_CFG_EX(29 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_08_SDA TLMM_GPIO_CFG_EX(0  , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
#define TOP_QUP_08_SCL TLMM_GPIO_CFG_EX(1  , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
                                    
#define TOP_QUP_09_SDA TLMM_GPIO_CFG_EX(36 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
#define TOP_QUP_09_SCL TLMM_GPIO_CFG_EX(37 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_NO_STRONG_PULL)
                                    
#define TOP_QUP_10_SDA TLMM_GPIO_CFG_EX(40 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_10_SCL TLMM_GPIO_CFG_EX(41 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_11_SDA TLMM_GPIO_CFG_EX(44 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_11_SCL TLMM_GPIO_CFG_EX(45 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_12_SDA TLMM_GPIO_CFG_EX(176, 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_12_SCL TLMM_GPIO_CFG_EX(177, 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_13_SDA TLMM_GPIO_CFG_EX(32 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_13_SCL TLMM_GPIO_CFG_EX(33 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_14_SDA TLMM_GPIO_CFG_EX(56 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_14_SCL TLMM_GPIO_CFG_EX(57 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
                                    
#define TOP_QUP_15_SDA TLMM_GPIO_CFG_EX(60 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)
#define TOP_QUP_15_SCL TLMM_GPIO_CFG_EX(61 , 1, TLMM_GPIO_INPUT, TLMM_GPIO_PULL_UP, TLMM_GPIO_2MA, TLMM_GPIO_STRONG_PULL)

#endif
