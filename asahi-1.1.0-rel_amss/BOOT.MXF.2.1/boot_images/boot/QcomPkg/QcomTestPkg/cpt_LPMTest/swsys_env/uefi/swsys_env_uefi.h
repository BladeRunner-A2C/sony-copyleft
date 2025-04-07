/*
===========================================================================
*/
/**
  @file swsys_env_uefi.h

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

#ifndef SWSYS_ENV_UEFI_H
#define SWSYS_ENV_UEFI_H

#include <stdint.h>
#include <stdbool.h>

#include "../swsys_env.h"

//#define LOG_TIMESTAMP

#define SWSYS_ENV_UEFI_FLAG

#define UEFI_MULTI_THRREAD_SUPPORT

void* swsys_malloc_uefi (uint64_t size);
void* swsys_malloc_uc_uefi (uint64_t size); // uncached allocation, uefi only
void* swsys_malloc_pages_uefi (uint64_t size);
void  swsys_free_uefi      (void* buf);
void  swsys_free_uc_uefi   (void* buf);
void swsys_free_pages_uefi (void* buf, uint64_t pages);

FILE*    swsys_fopen_uefi   (const char* filename, const char* mode);
int64_t  swsys_fclose_uefi  (FILE* f);
uint64_t swsys_fread_uefi   (void* buf, uint64_t size, uint64_t count, FILE* f);
uint64_t swsys_fwrite_uefi  (const void* buf, uint64_t size, uint64_t count, FILE* f);
int32_t  swsys_fflush_uefi  (FILE* stream);
FILE*    swsys_stdout_uefi  ();

int32_t  swsys_vprintf_uefi (const char* format, va_list va_l);

void swsys_exit_uefi (int32_t status);

float  swsys_strtof_uefi (const char* str, char** endptr);
double swsys_strtod_uefi (const char* str, char** endptr);

void    swsys_srand_uefi (uint32_t seed);
int32_t swsys_rand_uefi  ();

void swsys_reboot_uefi();

void swsys_busywait_uefi(uint32_t wait_us);

time_t swsys_time_uefi(time_t* time);
double swsys_difftime_uefi(time_t end, time_t beginning);

uint64_t swsys_get_time_us_uefi();
uint64_t swsys_get_time_sec_uefi();
bool swsys_write_buffer_into_file_uefi(uint8_t *buffer, uint32_t buffer_len, void *filename);
bool swsys_read_file_to_buffer_uefi(void *filename, uint8_t *buffer, uint32_t read_len);


bool swsys_is_ap_core_uefi ();
uint32_t swsys_get_ap_core_num_uefi ();

uint32_t swsys_get_ncpus_uefi ();
uint32_t swsys_get_available_ncpus_uefi ();
uint32_t swsys_init_deferred_cores_uefi (uint32_t cpuMask);

#ifdef UEFI_MULTI_THRREAD_SUPPORT
swsys_thread_err swsys_thread_create_uefi(swsys_thread* thread, swsys_thread_attr* attr,
    int (*start_routine) (void*), void* arg);

swsys_thread_err swsys_thread_join_uefi(swsys_thread* thread, void** value_ptr);

swsys_thread_err swsys_get_curr_thread_uefi(swsys_thread* thread);

swsys_thread_err swsys_thread_setaffinity_uefi(swsys_thread *thread, int32_t cpu);

swsys_thread_err swsys_thread_getaffinity_uefi(swsys_thread *thread, int32_t *cpu);

swsys_thread_err swsys_thread_lock_uefi(void* p_lock);

swsys_thread_err swsys_thread_unlock_uefi(void* p_lock);

swsys_thread_err swsys_thread_lock_init_uefi(void** pp_lock, char* lock_name);

swsys_thread_err swsys_thread_semaphore_wait_uefi(void* p_sem);

swsys_thread_err swsys_thread_semaphore_post_uefi(void* p_sem, bool resched);

swsys_thread_err swsys_thread_semaphore_init_uefi(void** pp_sem, uint32_t cnt);

swsys_thread_err swsys_thread_sleep_uefi(uint32_t time_duration);

swsys_thread_err swsys_system_sleep_uefi(uint64_t time_duration);
#endif
void *system_lpm_stats_uefi(uint32_t lpm_type);


#endif // SWSYS_ENV_UEFI_H
