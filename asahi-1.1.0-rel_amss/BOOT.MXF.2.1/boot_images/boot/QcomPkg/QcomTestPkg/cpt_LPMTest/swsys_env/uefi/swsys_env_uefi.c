/*
===========================================================================
*/
/**
  @file swsys_env_uefi.c

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  08/30/17   ih      Added muti-thread support    
  06/14/17   jh      Initial revision.

  ====================================================================
*/

#include <stdarg.h>

#include <Library/QcomLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/TimerLib.h>
#include <swsys_kernel_lib.h>

#include <Uefi.h>
#include "TimetickUEFI.h"

#include "swsys_env_uefi.h"
#include "swsys_env_uefi_flash.h"
#include "swsys_env_uefi_clk_switch.h"
#include "swsys_env_uefi_dispctrl.h"
#include "swsys_env_uefi_tsens.h"
#include "swsys_env_uefi_sysinfo.h"
#include "../swsys_env_common.h"
#include "../swsys_env_common_thread.h"
#include "../../swsys_logger/swsys_logger.h"

void swsys_env_init ()
{
  //swsys_env_init_common();

  swsys_env_i.env       = SWSYS_ENV_UEFI;
  swsys_env_i.env_str   = "uefi";

  swsys_env_i.malloc    = swsys_malloc_uefi;
  swsys_env_i.malloc_uc = swsys_malloc_uc_uefi;
  swsys_env_i.malloc_pages = swsys_malloc_pages_uefi;
  swsys_env_i.free      = swsys_free_uefi;
  swsys_env_i.free_pages= swsys_free_pages_uefi;

  swsys_env_i.fopen     = swsys_fopen_uefi;
  swsys_env_i.fclose    = swsys_fclose_uefi;
  swsys_env_i.fread     = swsys_fread_uefi;
  swsys_env_i.fwrite    = swsys_fwrite_uefi;
  swsys_env_i.fflush    = swsys_fflush_uefi;
  swsys_env_i.stdout_io = swsys_stdout_uefi;

  swsys_env_i.vprintf    = swsys_vprintf_uefi;
  swsys_env_i.vsnprintf  = swsys_vsnprintf_common;

  swsys_env_i.strtoi32  = swsys_strtoi32_common;
  swsys_env_i.strtoi64  = swsys_strtoi64_common;
  swsys_env_i.strtou32  = swsys_strtou32_common;
  swsys_env_i.strtou64  = swsys_strtou64_common;

  swsys_env_i.strtof    = swsys_strtof_uefi;
  swsys_env_i.strtod    = swsys_strtod_uefi;

  swsys_env_i.strncmp   = swsys_strncmp_common;
  swsys_env_i.strcmp    = swsys_strcmp_common;
  swsys_env_i.strstr    = swsys_strstr_common;
  swsys_env_i.strlen    = swsys_strlen_common;

  swsys_env_i.exit = swsys_exit_uefi;

  swsys_env_i.srand = swsys_srand_uefi;
  swsys_env_i.rand  = swsys_rand_uefi;

  swsys_env_i.memcpy = swsys_memcpy_common;
  swsys_env_i.memset = swsys_memset_common;

  swsys_env_i.flash_write = swsys_flash_write_uefi;
  swsys_env_i.flash_read = swsys_flash_read_uefi;

  swsys_env_i.reboot = swsys_reboot_uefi;

  swsys_env_i.init_ddr_clk = swsys_init_ddr_clk_uefi;
  swsys_env_i.deinit_ddr_clk = swsys_deinit_ddr_clk_uefi;
  swsys_env_i.switch_ddr_clk = swsys_switch_ddr_clk_uefi;
  swsys_env_i.read_ddr_clk = swsys_read_ddr_clk_uefi;
  swsys_env_i.get_ddr_freq_table = swsys_get_ddr_freq_table_uefi;

  swsys_env_i.init_shub_clk = swsys_init_shub_clk_uefi;
  swsys_env_i.deinit_shub_clk = swsys_deinit_shub_clk_uefi;
  swsys_env_i.switch_shub_clk = swsys_switch_shub_clk_uefi;
  swsys_env_i.read_shub_clk = swsys_read_shub_clk_uefi;
  swsys_env_i.get_shub_freq_table = swsys_get_shub_freq_table_uefi;

  swsys_env_i.init_cpu_clk = swsys_init_cpu_clk_uefi;
  swsys_env_i.deinit_cpu_clk = swsys_deinit_cpu_clk_uefi;
  swsys_env_i.switch_cpu_clk = swsys_switch_cpu_clk_uefi;
  swsys_env_i.cpu_available_clks = swsys_cpu_available_clks_uefi;
  swsys_env_i.read_cpu_clk = swsys_read_cpu_clk_uefi;

  swsys_env_i.busywait = swsys_busywait_uefi;

  swsys_env_i.init_tsens = swsys_init_tsens_uefi;
  swsys_env_i.read_tsens_sensor = swsys_read_tsens_sensor_uefi;
  swsys_env_i.read_max_tsens_sensor = swsys_read_max_tsens_sensor_uefi;
  swsys_env_i.get_num_of_tsens_sensors = swsys_get_num_of_tsens_sensors_uefi;

  swsys_env_i.set_lmh_runtime_profile = swsys_set_lmh_runtime_profile_uefi;


  swsys_env_i.init_dispctrl = swsys_init_dispctrl_uefi;
  swsys_env_i.dispctrl_off = swsys_dispctrl_off_uefi;
  swsys_env_i.dispctrl_on = swsys_dispctrl_on_uefi;

  swsys_env_i.time = swsys_time_uefi;
  swsys_env_i.difftime = swsys_difftime_uefi;

  swsys_env_i.get_time_us = swsys_get_time_us_uefi;
  swsys_env_i.get_time_sec = swsys_get_time_sec_uefi;

  swsys_env_i.init_sysinfo = swsys_init_sysinfo_uefi;
  swsys_env_i.get_serial_number = swsys_get_serial_number_uefi;
  swsys_env_i.get_chip_id = swsys_get_chip_id_uefi;
  swsys_env_i.get_chip_version = swsys_get_chip_version_uefi;
  swsys_env_i.get_processor_name = swsys_get_processor_name_uefi;
  swsys_env_i.get_device_id = swsys_get_device_id_uefi;

  swsys_env_i.write_buffer_into_file =   swsys_write_buffer_into_file_uefi;
  swsys_env_i.read_file_to_buffer = swsys_read_file_to_buffer_uefi;

#ifdef UEFI_MULTI_THRREAD_SUPPORT
  swsys_env_i.thread_create = swsys_thread_create_uefi;
  swsys_env_i.thread_join = swsys_thread_join_uefi;
  swsys_env_i.get_curr_thread = swsys_get_curr_thread_uefi;
  swsys_env_i.thread_setaffinity = swsys_thread_setaffinity_uefi;
  swsys_env_i.thread_getaffinity = swsys_thread_getaffinity_uefi;
  swsys_env_i.thread_lock = swsys_thread_lock_uefi;
  swsys_env_i.thread_unlock = swsys_thread_unlock_uefi;
  swsys_env_i.thread_lock_init = swsys_thread_lock_init_uefi;
  swsys_env_i.thread_semaphore_wait = swsys_thread_semaphore_wait_uefi;
  swsys_env_i.thread_semaphore_post = swsys_thread_semaphore_post_uefi;
  swsys_env_i.thread_semaphore_init = swsys_thread_semaphore_init_uefi;  
  swsys_env_i.thread_sleep = swsys_thread_sleep_uefi;
  swsys_env_i.system_sleep = swsys_system_sleep_uefi;
#endif
  swsys_env_i.system_lpm_stats = system_lpm_stats_uefi;

  swsys_env_i.is_ap_core = swsys_is_ap_core_uefi;
  swsys_env_i.get_ap_core_num = swsys_get_ap_core_num_uefi;
  swsys_env_i.get_ncpus = swsys_get_ncpus_uefi;
  swsys_env_i.get_available_ncpus = swsys_get_available_ncpus_uefi;
  swsys_env_i.init_deferred_cores = swsys_init_deferred_cores_uefi;
	
#ifdef LOG_TIMESTAMP
  get_qtimer_base();
  log_lock_init();
#endif
}

void swsys_enable_uc_malloc ()
{
  swsys_env_i.malloc    = swsys_malloc_uc_uefi;
  swsys_env_i.free      = swsys_free_uc_uefi;
}

void* swsys_malloc_uefi (uint64_t size)
{
  return (void*) AllocatePool(size);
}

void* swsys_malloc_uc_uefi (uint64_t size)
{
  return (void*) UncachedAllocatePool(size);
}

void* swsys_malloc_pages_uefi (UINTN Pages)
{
  return (void*) AllocatePages(Pages);
}

void swsys_free_uefi (void* buf)
{
  FreePool(buf);
}

void swsys_free_uc_uefi (void* buf)
{
  return UncachedFreePool(buf);
}

void swsys_free_pages_uefi (void* buf, uint64_t pages)
{
  return FreePages(buf, pages);
}

FILE* swsys_fopen_uefi (const char* filename, const char* mode)
{
  return NULL;
}

int64_t swsys_fclose_uefi (FILE* stream)
{
  return 0;
}

uint64_t swsys_fread_uefi (void* buf, uint64_t size, uint64_t count, FILE* f)
{
  return 0;
}

uint64_t swsys_fwrite_uefi (const void* buf, uint64_t size, uint64_t count, FILE* f)
{
  return 0;
}

int32_t swsys_fflush_uefi (FILE* f)
{
  return 0;
}

FILE* swsys_stdout_uefi ()
{
  return NULL;
}

// We need to call AsciiPrint with only a single string argument
// since there is no exposed UEFI print function which accepts a
// va_list. Therefore we use vsnprintf to create a string, and
// pass it to AsciiPrint.
int32_t swsys_vprintf_uefi (const char* format, va_list va_l)
{
  char* fakebuf = NULL;
  // make a dummy call to find out what the length will be
  int32_t len = swsys_vsnprintf_common(fakebuf, 0, format, va_l);
  if (len < 0) {
    return len;
  }
  // allocate a buffer now that we know the length
  char* buf = (char*)swsys_malloc_uefi(len*sizeof(char)+1);
  // create the real string
  len = swsys_vsnprintf_common(buf, len+1, format, va_l);
  if (len < 0) {
    return len;
  }
  //  Logging to Display Framebuffer and scrolling will make the
  //  test slower, so instead use DEBUG macro which outputs only to
  //  SerialConsole
//  AsciiPrint(buf);
  DEBUG ((EFI_D_ERROR, buf));
  swsys_free_uefi((void*)buf);
  return len;
}

void swsys_exit_uefi (int32_t status)
{
  return;
}

float swsys_strtof_uefi (const char* str, char** endptr)
{
  return 0.0f;
}

double swsys_strtod_uefi (const char* str, char** endptr)
{
  return 0.0;
}

uint32_t swsys_mul_wid = 0xFCA01979;
uint32_t swsys_mul_zid = 0xBA031903;

void swsys_srand_uefi (uint32_t seed)
{
  if (seed != 0 && seed != 0x464FFFFF) {
    swsys_mul_wid = seed;
  }
  else {
    swsys_mul_wid = 0xFCA01979;
  }
  swsys_mul_zid = 0xBA031903;
}

int32_t swsys_rand_uefi ()
{
    swsys_mul_zid = 36969 * (swsys_mul_zid & 65535) + (swsys_mul_zid >> 16);
    swsys_mul_wid = 18000 * (swsys_mul_wid & 65535) + (swsys_mul_wid >> 16);
    return ((swsys_mul_zid << 16) + swsys_mul_wid);
}

void swsys_reboot_uefi ()
{
  /*if (gRT) {
    swsys_trace("gRT is valid\n");
  }
  else {
    swsys_trace("gRT is not valid\n");
    return;
  }
  if (gRT->ResetSystem) {
    swsys_trace("reset is valid\n");
  }
  else {
    swsys_trace("reset is not valid\n");
  }*/
  gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
}

void swsys_busywait_uefi (uint32_t wait_us)
{
  MicroSecondDelay(wait_us);
}

time_t swsys_time_uefi(time_t* time)
{
  uint64_t tick = GetPerformanceCounter();
  return tick;
}
#if 0
/*bool swsys_timer_initialized = false;
static Timetick_timer_Type swsys_timer;*/
uint64_t last_tick = 0;
uint64_t overflow_counter = 0;
time_t swsys_time_uefi(time_t* time)
{
  /*uint64_t tick;
  if (!swsys_timer_initialized) {
    if(PcdGet32(PcdQTimerEnabled))
    {
      swsys_timer = TIMETICK_QTIMER;
    }
    else
    {
      swsys_timer = TIMETICK_TIMER_ADGT;
    }
    Timetick_Init();
    swsys_timer_initialized = true;
  }
  Timetick_GetCount(swsys_timer,&tick);
  if (time) {
    *time = tick;
  }
  return tick;*/
  uint64_t tick = GetPerformanceCounter();
  if (tick < last_tick) {
    // we have overflow
    // FIXME: This is a hack. If swsys_time_uefi is not called every 223 seconds,
    // we will overflow without knowing. A better way would be to increment some
    // variable using a 223 second timer event. Math: 223.69 = (2^32-1)/19200000
    overflow_counter++;
  }
  last_tick = tick;
  uint64_t t = (overflow_counter << 32) + tick;
  if (time) {
    *time = t;
  }
  return t;
}
#endif
double swsys_difftime_uefi(time_t end, time_t beginning)
{
  /*uint32_t timetick_freq;
  uint64_t useconds;
  double seconds;
  swsys_printf("entering swsys_difftime_uefi\n");
  Timetick_GetFreq(swsys_timer, &timetick_freq);
  useconds = end - beginning;
  useconds = useconds * 1000000;
  useconds = useconds / timetick_freq;
  seconds = ((double)useconds) / 1000000.0;
  swsys_printf("exiting swsys_difftime_uefi\n");
  return seconds;*/
  return ((double)(end - beginning)) / 19200000.0;
}

// possible faster implementation:
//static uint64_t seed;
//
//void srand(unsigned s)
//{
//  seed = s-1;
//}
//
//int rand(void)
//{
//  seed = 6364136223846793005ULL*seed + 1;
//  return seed>>33;
//}

uint64_t swsys_get_time_us_uefi()
{
  return GetTimerCountus();
}

uint64_t swsys_get_time_sec_uefi()
{
  uint64_t Tick_us, Tick_sec;
  Tick_us = GetTimerCountus();
  Tick_sec  = Tick_us/1000000;
  return Tick_sec;
}

bool swsys_write_buffer_into_file_uefi(uint8_t *buffer, uint32_t buffer_len, void *filename)
{
  //EFI_STATUS Status;
  UINTN Length = (UINTN)buffer_len;
  bool result = true;

  /* Delete the result file if it already exists */
  DeleteFile ((CHAR16*)filename,
                      NULL,
                      NULL,
                      L"logfs",
                      TRUE,
                      NULL);

  /* Write Logs to Partition */
  WriteFile ((CHAR16*)filename,
                      NULL,
                      NULL,
                      L"logfs",
                      TRUE,
                      NULL,
                      &Length,
                      0,
                      buffer,
                      buffer_len);

  //swsys_info("swsys_write_buffer_into_file_uefi - Status:%d \n", Status);
  //swsys_info("Length:%d, buffer_len:%l\n", Length, buffer_len);
    
  if (Length != buffer_len)
  {
    result = false;
  }
  return result;
}

bool swsys_read_file_to_buffer_uefi(void *filename, uint8_t *buffer, uint32_t read_len) 
{
  EFI_STATUS Status;
  UINTN BytesToRead = (UINTN)read_len;
  
  Status = ReadFile((CHAR16*)filename,
                    NULL,
                    NULL,
                    L"logfs",
                    TRUE,
                    NULL,
                    &BytesToRead,
                    0,
                    buffer,
                    read_len);

  if (Status == EFI_SUCCESS && BytesToRead > 0 )
  {
    //for (int i =0; i < number_of_line_buffers; i++) {
    //  swsys_info("%s", (char *)(buffer+i*line_buffer_len));
    //}
    return true;
  }
  return false;
}


#ifdef UEFI_MULTI_THRREAD_SUPPORT
swsys_thread_err swsys_thread_create_uefi(
    swsys_thread* thread,
    swsys_thread_attr* attr,
    int (*start_routine) (void*),
    void* arg)
{
  swsys_thread_err err = SWSYS_THREAD_SUCCESS;
  
  if (!thread) {
    err = SWSYS_THREAD_ENV_ERROR;
  } else {
    if (!attr) {
      thread->env_thread = (void *)ThreadCreate("NoNameThread", start_routine, arg, DEFAULT_PRIORITY, 4*DEFAULT_STACK_SIZE);
    } else {
      thread->env_thread = (void *)ThreadCreate(attr->thread_name, start_routine, arg, DEFAULT_PRIORITY, 4*DEFAULT_STACK_SIZE);
    }
    if (thread->env_thread) {
		  ThreadResume(thread->env_thread);
	  } else {
      err = SWSYS_THREAD_ENV_ERROR;
    }
  }
  if(err != SWSYS_THREAD_SUCCESS) {
    swsys_printf("Thread Creation Fail!!\r\n");
  }
  return err;
}

swsys_thread_err swsys_thread_join_uefi(swsys_thread* thread, void** value_ptr)
{
  swsys_thread_err err = SWSYS_THREAD_SUCCESS;
  Thread *t;

  if (!thread) {
      err = SWSYS_THREAD_ENV_ERROR;
  } else {
    t = (Thread *)thread->env_thread;
    if(t) {
	    ThreadJoin(thread->env_thread, (int32_t *) NULL, UINT32_MAX /*INFINITE_TIME*/);
	  } else {
      err = SWSYS_THREAD_ENV_ERROR;
    }
  }
  return err;
}


swsys_thread_err swsys_get_curr_thread_uefi(swsys_thread* thread)
{
  swsys_thread_err err = SWSYS_THREAD_SUCCESS;

  if (!thread) {
    err = SWSYS_THREAD_ENV_ERROR;
  } else {
    thread->env_thread= (void *)GetCurrentThread();
  }
  return err;
}

swsys_thread_err swsys_thread_setaffinity_uefi(swsys_thread *thread, int32_t cpu)
{
  swsys_thread_err err = SWSYS_THREAD_SUCCESS;
  Thread *t;

  if (!thread) {
      err = SWSYS_THREAD_ENV_ERROR;
  } else {
    t = (Thread *)thread->env_thread;
    ThreadSetPinnedCpu(t, cpu);
  }
  return err;
}

swsys_thread_err swsys_thread_getaffinity_uefi(swsys_thread *thread, int32_t *cpu)
{
  swsys_thread_err err = SWSYS_THREAD_SUCCESS;

  Thread *t;

  if (!thread || !cpu) {
        err = SWSYS_THREAD_ENV_ERROR;
  } else {
    t = (Thread *)thread->env_thread;
    *cpu = ThreadGetCurrCpu(t);
  }
  return err;
}

swsys_thread_err swsys_thread_lock_uefi(void* p_lock)
{
  if(!p_lock) {
    return SWSYS_THREAD_ENV_ERROR;
  }
  AcquireLock(p_lock);
  return SWSYS_THREAD_SUCCESS;
}

swsys_thread_err swsys_thread_unlock_uefi(void* p_lock)
{
  if(!p_lock) {
    return SWSYS_THREAD_ENV_ERROR;
  }
  ReleaseLock(p_lock);

  return SWSYS_THREAD_SUCCESS;
}

swsys_thread_err swsys_thread_lock_init_uefi(void** pp_lock, char* lock_name )
{
  swsys_thread_err err = SWSYS_THREAD_SUCCESS;

  if(*pp_lock)
    return err;

  InitLock (lock_name, (LockHandle**)pp_lock);

  if (!(*pp_lock)) {
    err = SWSYS_THREAD_ENV_ERROR;
  }
  return err;
}

swsys_thread_err swsys_thread_semaphore_wait_uefi(void* p_sem)
{
  Semaphore* p_semaphore = (Semaphore *)p_sem;
  
  SemWait(p_semaphore);
  return SWSYS_THREAD_SUCCESS;
}

swsys_thread_err swsys_thread_semaphore_post_uefi(void* p_sem, bool resched)
{
  Semaphore* p_semaphore = (Semaphore *)p_sem;

  SemPost(p_semaphore, resched);
  return SWSYS_THREAD_SUCCESS;
}

swsys_thread_err swsys_thread_semaphore_init_uefi(void** pp_sem, uint32_t cnt)
{
  swsys_thread_err err = SWSYS_THREAD_SUCCESS;

  *pp_sem = (void *)SemInit (0, cnt);
  if (!(*pp_sem)) {
    err = SWSYS_THREAD_ENV_ERROR;
  }
  return err;
}

swsys_thread_err swsys_thread_sleep_uefi(uint32_t time_duration)
{
  ThreadSleep(time_duration);
  
  return SWSYS_THREAD_SUCCESS;
}

swsys_thread_err swsys_system_sleep_uefi(uint64_t time_duration)
{

#if (0)
  UINT64 SleepDurMs = 3000;
  
  MpCoreSystemSleep(SleepDurMs);
#endif  
  return SWSYS_THREAD_SUCCESS;
}
#endif

void *system_lpm_stats_uefi(uint32_t lpm_type)
{
#if (0)	
  power_sleep_stats_enum_t sleep_mode = 1;

  return power_sleep_get_lpm_counts(sleep_mode);
#else
  return NULL;
#endif
}

// Get max number of CPUs supported
uint32_t swsys_get_ncpus_uefi ()
{
  return MpcoreGetMaxCpuCount();
}

// Get available(online) number of CPUs supported
uint32_t swsys_get_available_ncpus_uefi ()
{
  return MpcoreGetAvailCpuCount();
}

// Enable all cores (deferred cores) - 0
// For individaul core enablement, use corresponding mask for the core
uint32_t swsys_init_deferred_cores_uefi (uint32_t cpuMask)
{
  uint32_t active_core_num;

  active_core_num = MpcoreInitDeferredCores(cpuMask);

  swsys_thread_sleep(200);

  return active_core_num;
}
