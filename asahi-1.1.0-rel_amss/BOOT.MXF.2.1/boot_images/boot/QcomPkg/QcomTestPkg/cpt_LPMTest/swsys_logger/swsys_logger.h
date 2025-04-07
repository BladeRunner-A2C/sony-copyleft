/*
===========================================================================
*/
/**
  @file qblizzard_logger.h

*/
/*
  ====================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.
  ====================================================================
  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/14/17   jh      Initial revision.
  ====================================================================
*/

#ifndef SWSYS_LOGGER_H
#define SWSYS_LOGGER_H
#include "swsys_env_uefi.h"

typedef enum {
  SWSYS_LOG_TRACE   = -2,
  SWSYS_LOG_DEBUG   = -1,
  SWSYS_LOG_INFO    = 0,
  SWSYS_LOG_NOTICE  = 1,
  SWSYS_LOG_WARNING = 2,
  SWSYS_LOG_ERROR   = 3,
  SWSYS_LOG_DISABLE = 4,
} swsys_log_level;

extern const char* swsys_log_level_choices[];

typedef enum {
  OK = 0,
  MALLOC_ERR = 1,
  FOPEN_ERR = 2,
  FILE_NOT_REGISTERED = 3,
} swsys_log_error;

swsys_log_level swsys_log_str_to_level(char* str);
void swsys_log_register_console(swsys_log_level level);

// registers a file for logger output. If called twice for the same file, then just
// update the level.
swsys_log_error swsys_log_register_file(swsys_log_level level, const char* path);
swsys_log_error swsys_log_unregister_file(const char* path);
void swsys_log_unregister_all();
void swsys_log(swsys_log_level level, const char* format, ...);
void swsys_va_log(swsys_log_level level, const char* format, va_list va_l);
void swsys_trace(const char* format, ...);
void swsys_debug(const char* format, ...);
void swsys_info(const char* format, ...);
void swsys_notice(const char* format, ...);
void swsys_warning(const char* format, ...);
void swsys_error(const char* format, ...);
void swsys_putc(const char* input);
bool get_qtimer_base(void);
void log_lock_init(void);

#endif // SWSYS_LOGGER_H
