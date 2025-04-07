/*
===========================================================================
*/
/**
  @file swsys_logger.c

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

#include "../swsys_linkedlist/swsys_linkedlist.h"
#include "../swsys_env/swsys_env.h"
#include "../swsys_string/swsys_string.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIHWIO.h>
#include "swsys_logger.h"

#ifdef LOG_TIMESTAMP
#define __inpdw(port)       (*((volatile unsigned int *) (port)))
#define in_dword_masked(addr, mask) (__inpdw(addr) & (mask))

//#define QTIMER_FREQ (1000000000 / 19200000) //this will introduce calculation deviation
//#define QTIMER_BASE 0x17C22000
#define HWIO_QTMR_CNTPCT_LO_ADDR(BASE)                          (BASE      + 0x00000008)
#define HWIO_QTMR_CNTPCT_LO_RMSK                          0xffffffff
#define HWIO_QTMR_CNTPCT_LO_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTPCT_LO_ADDR(BASE), HWIO_QTMR_CNTPCT_LO_RMSK)

#define HWIO_QTMR_CNTPCT_HI_ADDR(BASE)                          (BASE      + 0x0000000C)
#define HWIO_QTMR_CNTPCT_HI_RMSK                          0xffffffff
#define HWIO_QTMR_CNTPCT_HI_IN(BASE)          \
        in_dword_masked(HWIO_QTMR_CNTPCT_HI_ADDR(BASE), HWIO_QTMR_CNTPCT_HI_RMSK)

static char * QTIMER = {"+APSS_QTMR0_F0V2_QTMR_V2"};

void *qtimer_base_addr = NULL;
VOID *log_lock; 

bool get_qtimer_base(void)
{
  EFI_STATUS Status;
  bool no_error = true;
	EFI_HWIO_PROTOCOL *HWIOProtocol = NULL;

  //Locate HWIOProtocol
  if(!HWIOProtocol){
     Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&HWIOProtocol);
     if (Status != EFI_SUCCESS) {
       DEBUG (( EFI_D_ERROR,"Failed to locate HWIOProtocol\n"));
       return false; 
     }
  }
  Status = HWIOProtocol->MapRegion(HWIOProtocol, QTIMER, (UINT8**)(&qtimer_base_addr));
  if(Status == EFI_SUCCESS){
     DEBUG (( EFI_D_WARN,"qtimer base is 0x%lX\n", qtimer_base_addr));
     return no_error;
  }
  else{
     DEBUG (( EFI_D_ERROR,"Failed to map qtimer region\n"));
     return false;
  }
}

UINT64 get_timestamp(void)
{
  UINT32  count_low, count_hi1, count_hi2;
	UINT64  tick_count = 0;

  if(!qtimer_base_addr)
    return 0;
		
  do
  {
    count_hi1 = HWIO_QTMR_CNTPCT_HI_IN(qtimer_base_addr);
    count_low = HWIO_QTMR_CNTPCT_LO_IN(qtimer_base_addr);

    /* repeat the above until the same value is read from the   
      high count register successively */
    count_hi2 = HWIO_QTMR_CNTPCT_HI_IN(qtimer_base_addr);
  }while (count_hi1 != count_hi2);

  tick_count = ((UINT64)count_hi1 <<32) | count_low;
	return (tick_count * 10000/192); 
}

void log_lock_init(void)
{
  swsys_thread_lock_init(&log_lock, NULL);
}
#endif

typedef struct {
  swsys_log_level file_level;
  FILE* file;
} swsys_logger_file;

typedef struct {
  swsys_linkedlist* files;
  swsys_log_level console_level;
} swsys_logger_state;

typedef struct {
  swsys_log_level level;
  char* format;
  va_list va_l;
} swsys_logger_filewrite_params;

const char* swsys_log_level_choices[] = {"trace", "debug", "info", "notice", "warning", "error", "disable"};

bool swsys_log_compare_file(void* list_data, void* cust_data);
swsys_log_error swsys_log_unregister_file_node(swsys_linkedlist_node* file);
void swsys_log_cleanup_file(void* data, void* cust_data);
void swsys_log_write_file(void* data, void* cust_data);

#define SWSYS_LOGGER_MAX_FILE_WRITE 300
char swsys_logger_file_buffer[SWSYS_LOGGER_MAX_FILE_WRITE];

swsys_logger_state swsys_logger_state_i;

swsys_log_level swsys_log_str_to_level(char* str)
{
  if (!str) {
	swsys_error("not a valid log level\n");
    return SWSYS_LOG_DISABLE;
  }
  if (swsys_strcicmp(str, "trace") == 0) {
    return SWSYS_LOG_TRACE;
  }
  else if (swsys_strcicmp(str, "debug") == 0) {
    return SWSYS_LOG_DEBUG;
  }
  else if (swsys_strcicmp(str, "info") == 0) {
    return SWSYS_LOG_INFO;
  }
  else if (swsys_strcicmp(str, "notice") == 0) {
    return SWSYS_LOG_NOTICE;
  }
  else if (swsys_strcicmp(str, "warning") == 0) {
    return SWSYS_LOG_WARNING;
  }
  else if (swsys_strcicmp(str, "error") == 0) {
    return SWSYS_LOG_ERROR;
  }
  else if (swsys_strcicmp(str, "disable") == 0) {
    return SWSYS_LOG_DISABLE;
  }
  else {
    swsys_error("%s is not a valid log level\n", str);
    return SWSYS_LOG_DISABLE;
  }
}

void swsys_log_register_console(swsys_log_level level)
{
  swsys_logger_state_i.console_level = level;
}

swsys_log_error swsys_log_register_file(swsys_log_level level, const char* path)
{
  swsys_logger_file* file;
  swsys_linkedlist_node* node;
  if (swsys_logger_state_i.files == NULL) {
    swsys_logger_state_i.files = swsys_linkedlist_init();
	if (!swsys_logger_state_i.files){
		return MALLOC_ERR;
	}
  }

  // check if path already exists
  node = swsys_linkedlist_find(swsys_logger_state_i.files, swsys_log_compare_file, (void*)path);
  if (node) {
    // File already exists, just update the level
    file = (swsys_logger_file*)node->data;
    file->file_level = level;
  }
  else {
    file = (swsys_logger_file*)swsys_malloc(sizeof(swsys_logger_file));
    if (file == NULL) {
      return MALLOC_ERR;
    }

    file->file_level = level;
    file->file = swsys_fopen(path, "w");
    if (file->file == NULL) {
      swsys_free(file);
      return FOPEN_ERR;
    }

    swsys_linkedlist_append(swsys_logger_state_i.files, (void*)file);
  }

  return OK;
}

swsys_log_error swsys_log_unregister_file(const char* path)
{
  //swsys_logger_file* file;
  swsys_linkedlist_node* node;
  node = swsys_linkedlist_find(swsys_logger_state_i.files, swsys_log_compare_file, (void*)path);

  if (node == NULL) {
    return FILE_NOT_REGISTERED;
  }
  return swsys_log_unregister_file_node(node);
}

swsys_log_error swsys_log_unregister_file_node(swsys_linkedlist_node* node)
{
  swsys_logger_file* file = (swsys_logger_file*)node->data;
  swsys_fclose(file->file);
  swsys_free(file);
  swsys_linkedlist_remove(swsys_logger_state_i.files, node);
  return OK;
}

void swsys_log_unregister_all()
{
  swsys_linkedlist_foreach(swsys_logger_state_i.files, swsys_log_cleanup_file, NULL);
  swsys_linkedlist_deinit(swsys_logger_state_i.files);
}

void swsys_va_log(swsys_log_level level, const char* format, va_list va_l)
{
  if (level >= swsys_logger_state_i.console_level) {
    swsys_vprintf(format, va_l);
    swsys_fflush(swsys_stdout());
  }
  swsys_linkedlist_foreach(swsys_logger_state_i.files, swsys_log_write_file, (void*)&level);
}

void swsys_log_ts(swsys_log_level level, const char* format, ...)
{
  va_list va_l;
  va_start(va_l, format);
  swsys_va_log(level, format, va_l);
  va_end(va_l);
}

void swsys_log(swsys_log_level level, const char* format, ...)
{
  va_list va_l;
#ifdef LOG_TIMESTAMP
  swsys_thread_lock(log_lock);
  swsys_log_ts(level, "%lld - ", get_timestamp());
#endif
  va_start(va_l, format);
  swsys_va_log(level, format, va_l);
  va_end(va_l);
#ifdef LOG_TIMESTAMP
  swsys_thread_unlock(log_lock);
#endif
}

void swsys_trace(const char* format, ...)
{
  va_list va_l;
#ifdef LOG_TIMESTAMP
  swsys_thread_lock(log_lock);
  swsys_log_ts(SWSYS_LOG_TRACE, "%lld - ", get_timestamp());
#endif
  va_start(va_l, format);
  swsys_va_log(SWSYS_LOG_TRACE, format, va_l);
  va_end(va_l);
#ifdef LOG_TIMESTAMP
  swsys_thread_unlock(log_lock);
#endif
}

void swsys_debug(const char* format, ...)
{
  va_list va_l;
#ifdef LOG_TIMESTAMP
  swsys_thread_lock(log_lock);
  swsys_log_ts(SWSYS_LOG_DEBUG, "%lld - ", get_timestamp());
#endif
  va_start(va_l, format);
  swsys_va_log(SWSYS_LOG_DEBUG, format, va_l);
  va_end(va_l);
#ifdef LOG_TIMESTAMP
  swsys_thread_unlock(log_lock);
#endif
}

void swsys_info(const char* format, ...)
{
  va_list va_l;
#ifdef LOG_TIMESTAMP
  swsys_thread_lock(log_lock);
  swsys_log_ts(SWSYS_LOG_INFO, "%lld - ", get_timestamp());
#endif
  va_start(va_l, format);
  swsys_va_log(SWSYS_LOG_INFO, format, va_l);
  va_end(va_l);
#ifdef LOG_TIMESTAMP
  swsys_thread_unlock(log_lock);
#endif
}

void swsys_notice(const char* format, ...)
{
  va_list va_l;
#ifdef LOG_TIMESTAMP
  swsys_thread_lock(log_lock);
  swsys_log_ts(SWSYS_LOG_NOTICE, "%lld - ", get_timestamp());
#endif
  va_start(va_l, format);
  swsys_va_log(SWSYS_LOG_NOTICE, format, va_l);
  va_end(va_l);
#ifdef LOG_TIMESTAMP
  swsys_thread_unlock(log_lock);
#endif
}

void swsys_warning(const char* format, ...)
{
  va_list va_l;
#ifdef LOG_TIMESTAMP
  swsys_thread_lock(log_lock);
  swsys_log_ts(SWSYS_LOG_WARNING, "%lld - ", get_timestamp());
#endif
  va_start(va_l, format);
  swsys_va_log(SWSYS_LOG_WARNING, format, va_l);
  va_end(va_l);
#ifdef LOG_TIMESTAMP
  swsys_thread_unlock(log_lock);
#endif
}

void swsys_error(const char* format, ...)
{
  va_list va_l;
#ifdef LOG_TIMESTAMP
  swsys_thread_lock(log_lock);
  swsys_log_ts(SWSYS_LOG_ERROR, "%lld - ", get_timestamp());
#endif
  va_start(va_l, format);
  swsys_va_log(SWSYS_LOG_ERROR, format, va_l);
  va_end(va_l);
#ifdef LOG_TIMESTAMP
  swsys_thread_unlock(log_lock);
#endif
}

void swsys_putc(const char* input)
{
    DEBUG ((EFI_D_ERROR, input));
}

bool swsys_log_compare_file(void* list_data, void* cust_data)
{
  char* filename = (char*)cust_data;
  if (!swsys_strcmp((char*)list_data, filename)) {
    return true;
  }
  else {
    return false;
  }
}

void swsys_log_cleanup_file(void* data, void* cust_data)
{
  swsys_logger_file* file = (swsys_logger_file*)data;
  swsys_fclose(file->file);
  swsys_free(file);
}

void swsys_log_write_file(void* data, void* cust_data)
{
  swsys_logger_file* file = (swsys_logger_file*)data;
  swsys_logger_filewrite_params* params = (swsys_logger_filewrite_params*)cust_data;
  if (params->level >= file->file_level) {
    swsys_vsnprintf(swsys_logger_file_buffer,
        SWSYS_LOGGER_MAX_FILE_WRITE,
        params->format,
        params->va_l);
    swsys_fwrite(swsys_logger_file_buffer,
        sizeof(char),
        swsys_strlen(swsys_logger_file_buffer),
        file->file);
  }
}
