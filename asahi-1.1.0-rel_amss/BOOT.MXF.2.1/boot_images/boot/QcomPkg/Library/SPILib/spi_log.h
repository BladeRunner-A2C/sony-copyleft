/** 
    @file  SPI_log.h
    @brief SPI logging interface
 */
/*=============================================================================
            Copyright (c) 2019, 2023 Qualcomm Technologies, Incorporated.
                              All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

#ifndef __SPI_LOG_H__
#define __SPI_LOG_H__

#define LEVEL_INFO    0x00000040
#define LEVEL_ERROR   0x80000000

#define SPI_LOG_LEVEL
//#define ENABLE_SPI_LEVEL_INFO

// to enable logs, set SPI_LOG_FLAGS to an OR of the above bits in scons
#ifdef SPI_LOG_LEVEL
#include<Library/DebugLib.h>
#ifdef ENABLE_SPI_LEVEL_INFO
#define SPI_LOG(level, format_str, args...) \
        {DEBUG((level, format_str"\n", ##args));}
#else
// if ENABLE_SPI_LEVEL_INFO is disabled, print logs only for LEVEL_ERROR
#define SPI_LOG(level, format_str, args...) \
        if(level == LEVEL_ERROR){DEBUG((level, format_str"\n", ##args));}
#endif
#else
#define SPI_LOG(level,args...)
#endif

#endif
