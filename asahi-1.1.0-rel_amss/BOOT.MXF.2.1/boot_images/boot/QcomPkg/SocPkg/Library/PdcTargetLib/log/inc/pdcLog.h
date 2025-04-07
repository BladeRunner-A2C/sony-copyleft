#ifndef _PDCINT_LOG_H_
#define _PDCINT_LOG_H_
/*============================================================================
  FILE:         pdcInt_log.h

  OVERVIEW:     This file declares the interface to the drivers logging system

  DEPENDENCIES: None

                Copyright (c) 2016 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary.
                Export of this technology or software is regulated by the U.S. Government.
                Diversion contrary to U.S. law prohibited.
==============================================================================
$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/SocPkg/Library/PdcTargetLib/log/inc/pdcLog.h#1 $
$DateTime: 2024/04/02 23:00:31 $
============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
                           GLOBAL FUNCTION DECLARATIONS
 =============================================================================*/

/**
 * pdcLog_printf
 *
 * @brief Logs a debug message using the standard C printf function format
 * 
 * @param arg_count:  Number of parameters that are being logged.
 * @param format:     The format string for printing log.
 */
void pdcLog_printf(int arg_count, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* _PDCINT_LOG_H_ */

