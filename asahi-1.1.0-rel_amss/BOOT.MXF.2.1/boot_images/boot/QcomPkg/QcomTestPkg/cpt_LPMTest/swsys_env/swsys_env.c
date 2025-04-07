/*
===========================================================================
*/
/**
  @file swsys_env.c

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

#include <stdarg.h>
#include "swsys_env.h"
#include "uefi/target/target.h"

void* swsys_malloc (uint64_t size)
{
  if (!swsys_env_i.malloc) {
    swsys_printf("swsys_malloc not implemented\n");
	return NULL;
  }
  else{
	return swsys_env_i.malloc(size);
  }
}

void* swsys_malloc_pages (uint64_t pages)
{
  if (!swsys_env_i.malloc_pages) {
    swsys_printf("swsys_malloc_pages not implemented\n");
	return NULL;
  }
  else{
	return swsys_env_i.malloc_pages(pages);
  }
}

void* swsys_malloc_uc (uint64_t size)
{
  if (!swsys_env_i.malloc_uc) {
    swsys_printf("swsys_malloc_uc not implemented\n");
	return NULL;
  }
  else{
	return swsys_env_i.malloc_uc(size);
  }
}

void swsys_free (void* buf)
{
  if (!swsys_env_i.free) {
    swsys_printf("swsys_free not implemented\n");
	return;
  }
  else{
	return swsys_env_i.free(buf);
  }
}

void swsys_free_pages (void* buf, uint64_t pages)
{
  if (!swsys_env_i.free_pages) {
    swsys_printf("swsys_free_pages not implemented\n");
	return;
  }
  else{
	return swsys_env_i.free_pages(buf, pages);
  }
}

FILE* swsys_fopen (const char* filename, const char* mode)
{
  if (!swsys_env_i.fopen) {
    swsys_printf("swsys_fopen not implemented\n");
	return NULL;
  }
  else{
	return swsys_env_i.fopen(filename, mode);
  }
}

int64_t swsys_fclose (FILE* f)
{
  if (!swsys_env_i.fclose) {
    swsys_printf("swsys_fclose not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.fclose(f);
  }
}

uint64_t swsys_fread (void* buf, uint64_t size, uint64_t count, FILE* f)
{
  if (!swsys_env_i.fread) {
    swsys_printf("swsys_fread not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.fread(buf, size, count, f);
  }
}

uint64_t swsys_fwrite (const void* buf, uint64_t size, uint64_t count, FILE* f)
{
  #ifdef SWSYS_DEBUG
  if (!swsys_env_i.fwrite) {
    swsys_printf("swsys_fwrite not implemented\n");
  }
  #endif // SWSYS_DEBUG
  return swsys_env_i.fwrite(buf, size, count, f);
}

int32_t swsys_fflush(FILE* stream)
{
  if (!swsys_env_i.fflush) {
    swsys_printf("swsys_fflush not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.fflush(stream);
  }
}

FILE* swsys_stdout ()
{
  if (!swsys_env_i.stdout_io) {
    swsys_printf("swsys_stdout not implemented\n");
	return NULL;
  }
  else{
	return swsys_env_i.stdout_io();
  }
}

// can't pass variable arguments to function table, so need to use vprintf
int32_t swsys_printf (const char* format, ...)
{
  va_list va_l;
  int32_t ret;
  va_start(va_l, format);
  ret = swsys_vprintf(format, va_l);
  va_end(va_l);
  return ret;
}

int32_t swsys_vprintf (const char* format, va_list arg)
{
  int32_t ret = swsys_env_i.vprintf(format, arg);
  return ret;
}

// can't pass variable arguments to function table, so need to use vsnprintf
int32_t swsys_snprintf (char* s, uint64_t n, const char* format, ...)
{
  va_list va_l;
  int64_t ret;
  va_start(va_l, format);
  ret = swsys_vsnprintf(s, n, format, va_l);
  va_end(va_l);
  return ret;
}

int32_t swsys_vsnprintf (char* s, uint64_t n, const char* format, va_list arg)
{
  return swsys_env_i.vsnprintf(s, n, format, arg);
}

int32_t  swsys_strtoi32 (const char* str, char** endptr, int32_t base)
{
  if (!swsys_env_i.strtoi32) {
    swsys_printf("swsys_strtoi32 not implemented\n");
	return 0;
  }
  else
  {
	return swsys_env_i.strtoi32(str, endptr, base);
  }
}

int64_t  swsys_strtoi64 (const char* str, char** endptr, int32_t base)
{
  if (!swsys_env_i.strtoi64) {
    swsys_printf("swsys_strtoi64 not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.strtoi64(str, endptr, base);
  }
}

uint32_t swsys_strtou32 (const char* str, char** endptr, int32_t base)
{
  if (!swsys_env_i.strtou32) {
    swsys_printf("swsys_strtou32 not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.strtou32(str, endptr, base);
  }
}

uint64_t swsys_strtou64 (const char* str, char** endptr, int32_t base)
{
  if (!swsys_env_i.strtou64) {
    swsys_printf("swsys_strtou64 not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.strtou64(str, endptr, base);
  }
}

float    swsys_strtof   (const char* str, char** endptr)
{
  if (!swsys_env_i.strtof) {
    swsys_printf("swsys_strtof not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.strtof(str, endptr);
  }
}

double   swsys_strtod   (const char* str, char** endptr)
{
  if (!swsys_env_i.strtod) {
    swsys_printf("swsys_strtod not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.strtod(str, endptr);
  }
}

int32_t swsys_strncmp (const char* str1, const char* str2, int64_t num)
{
  if (!swsys_env_i.strncmp) {
    swsys_printf("swsys_strncmp not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.strncmp(str1, str2, num);
  }
}

int32_t swsys_strcmp (const char* str1, const char* str2)
{
  if (!swsys_env_i.strcmp) {
    swsys_printf("swsys_strcmp not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.strcmp(str1, str2);
  }
}

char* swsys_strstr (const char* str1, const char* str2)
{
  if (!swsys_env_i.strstr) {
    swsys_printf("swsys_strstr not implemented\n");
	return NULL;
  }
  else{
	return swsys_env_i.strstr(str1, str2);
  }
}

uint64_t swsys_strlen (const char* str)
{
  if (!swsys_env_i.strlen) {
    swsys_printf("swsys_strlen not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.strlen(str);
  }
}

void swsys_exit (int32_t status)
{
  if (!swsys_env_i.exit) {
    swsys_printf("swsys_exit not implemented\n");
	return;
  }
  else{
	return swsys_env_i.exit(status);
  }
}

void swsys_srand (uint32_t seed)
{
  if (!swsys_env_i.srand) {
    swsys_printf("swsys_srand not implemented\n");
	return;
  }
  else{
	return swsys_env_i.srand(seed);
  }
}

int32_t swsys_rand ()
{
  if (!swsys_env_i.rand) {
    swsys_printf("swsys_rand not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.rand();
  }
}

void swsys_memcpy(void* dest, const void* src, uint64_t len)
{
  if (!swsys_env_i.memcpy) {
    swsys_printf("swsys_memcpy not implemented\n");
	return;
  }
  else{
	swsys_env_i.memcpy(dest, src, len);
  }
}

void swsys_memset(void* ptr, int32_t value, uint64_t num)
{
  if (!swsys_env_i.memset) {
    swsys_printf("swsys_memset not implemented\n");
	return;
  }
  else{
	swsys_env_i.memset(ptr, value, num);
  }
}

uint64_t swsys_flash_write (void* buf, uint64_t size, uint64_t count, char* partition)
{
  if (!swsys_env_i.flash_write) {
    swsys_printf("swsys_flash_write not implemented\n");
	return 0;
  }
  else {
	return swsys_env_i.flash_write(buf, size, count, partition);
  }
}

uint64_t swsys_flash_read (void* buf, uint64_t size, uint64_t count, char* partition, uint64_t* bytes_read)
{
  if (!swsys_env_i.flash_read) {
    swsys_printf("swsys_flash_read not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.flash_read(buf, size, count, partition, bytes_read);
  }
}

void swsys_reboot ()
{
  if (!swsys_env_i.reboot) {
    swsys_printf("swsys_reboot not implemented\n");
	return;
  }
  else{
	return swsys_env_i.reboot();
  }
}

void swsys_init_ddr_clk(uint32_t init_freq_khz, uint32_t display_mode)
{
  if (!swsys_env_i.init_ddr_clk) {
    swsys_printf("swsys_init_ddr_clk not implemented\n");
	return;
  }
  else{
	return swsys_env_i.init_ddr_clk(init_freq_khz,display_mode);
  }
}

void swsys_deinit_ddr_clk()
{
  if (!swsys_env_i.deinit_ddr_clk) {
    swsys_printf("swsys_deinit_ddr_clk not implemented\n");
	return;
  }
  else{
	return swsys_env_i.deinit_ddr_clk();
  }
}

uint32_t swsys_switch_ddr_clk(uint32_t freq_khz)
{
  if (!swsys_env_i.switch_ddr_clk) {
    swsys_printf("swsys_switch_ddr_clk not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.switch_ddr_clk(freq_khz);
  }
}

void swsys_init_shub_clk(uint32_t init_freq_khz, uint32_t display_mode)
{
  if (!swsys_env_i.init_shub_clk) {
    swsys_printf("swsys_init_shub_clk not implemented\n");
	return;
  }
  else{
	return swsys_env_i.init_shub_clk(init_freq_khz, display_mode);
  }
}

void swsys_deinit_shub_clk()
{
  if (!swsys_env_i.deinit_shub_clk) {
    swsys_printf("swsys_deinit_shub_clk not implemented\n");
	return;
  }
  else{
	return swsys_env_i.deinit_shub_clk();
  }
}

uint32_t swsys_switch_shub_clk(uint32_t freq_khz)
{
  if (!swsys_env_i.switch_shub_clk) {
    swsys_printf("swsys_switch_shub_clk not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.switch_shub_clk(freq_khz);
  }
}

bool swsys_read_ddr_clk(uint32_t* freq_khz)
{
  if (!swsys_env_i.read_ddr_clk) {
    swsys_printf("swsys_read_ddr_clk not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.read_ddr_clk(freq_khz);
  }
}

uint8_t swsys_get_ddr_freq_table(uint32_t *freq_list)
{
  if (!swsys_env_i.get_ddr_freq_table) {
    swsys_printf("swsys_get_ddr_freq_table not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.get_ddr_freq_table(freq_list);
  }
}

uint8_t swsys_get_shub_freq_table(uint32_t *freq_list)
{
  if (!swsys_env_i.get_shub_freq_table) {
    swsys_printf("swsys_get_shub_freq_table not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.get_shub_freq_table(freq_list);
  }
}

bool swsys_read_shub_clk(uint32_t* freq_khz)
{
  if (!swsys_env_i.read_shub_clk) {
    swsys_printf("swsys_read_shub_clk not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.read_shub_clk(freq_khz);
  }
}

void swsys_init_cpu_clk()
{
  if (!swsys_env_i.init_cpu_clk) {
    swsys_printf("swsys_init_cpu_clk not implemented\n");
	return;
  }
  else{
	return swsys_env_i.init_cpu_clk();
  }
}

void swsys_deinit_cpu_clk()
{
  if (!swsys_env_i.deinit_cpu_clk) {
    swsys_printf("swsys_deinit_cpu_clk not implemented\n");
	return;
  }
  else{
	return swsys_env_i.deinit_cpu_clk();
  }
}

uint32_t swsys_switch_cpu_clk(uint32_t cluster, uint32_t freq_khz)
{
  if (!swsys_env_i.switch_cpu_clk) {
    swsys_printf("swsys_switch_cpu_clk not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.switch_cpu_clk(cluster, freq_khz);
  }
}

uint32_t swsys_cpu_available_clks(uint32_t cluster, uint32_t* freq_tbl)
{
  if (!swsys_env_i.cpu_available_clks) {
    swsys_printf("swsys_cpu_available_clks not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.cpu_available_clks(cluster, freq_tbl);
  }
}

bool swsys_read_cpu_clk(uint32_t cluster, uint32_t* freq_khz)
{

  if (!swsys_env_i.read_cpu_clk) {
    swsys_printf("swsys_read_cpu_clk not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.read_cpu_clk(cluster, freq_khz);
  }
}

void swsys_busywait(uint32_t wait_us)
{
  if (!swsys_env_i.busywait) {
    swsys_printf("swsys_busywait not implemented\n");
	return;
  }
  else{
	return swsys_env_i.busywait(wait_us);
  }
}

time_t swsys_time(time_t* t)
{
  if (!swsys_env_i.time) {
    swsys_printf("swsys_time not implemented\n");
	return (time_t)0;
  }
  else{
	return swsys_env_i.time(t);
  }
}

double swsys_difftime(time_t end, time_t beginning)
{
  if (!swsys_env_i.difftime) {
    swsys_printf("swsys_difftime not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.difftime(end, beginning);
  }
}

uint64_t swsys_get_time_us()
{
  if (!swsys_env_i.get_time_us) {
    swsys_printf("get_time_us not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.get_time_us();
  }
}

uint64_t swsys_get_time_sec()
{
  if (!swsys_env_i.get_time_sec) {
    swsys_printf("swsys_get_time_sec not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.get_time_sec();
  }
}

bool swsys_init_sysinfo()
{
  if (!swsys_env_i.init_sysinfo) {
    swsys_printf("swsys_init_sysinfo not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.init_sysinfo();
  }
}

bool swsys_get_serial_number(uint64_t *serial_number)
{
  if (!swsys_env_i.get_serial_number) {
    swsys_printf("swsys_get_serial_number not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.get_serial_number(serial_number);
  }
}

bool swsys_get_chip_id(char* chip_id, uint32_t size)
{
  if (!swsys_env_i.get_chip_id) {
    swsys_printf("swsys_get_chip_id not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.get_chip_id(chip_id, size);
  }
}

bool swsys_get_chip_version(uint32_t *chip_version)
{
  if (!swsys_env_i.get_chip_version) {
    swsys_printf("swsys_get_chip_version not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.get_chip_version(chip_version);
  }
}

bool swsys_get_processor_name(char *processor_name, uint32_t size)
{
  if (!swsys_env_i.get_processor_name) {
    swsys_printf("swsys_get_processor_name not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.get_processor_name(processor_name, size );
  }
}

bool swsys_get_device_id(uint8_t* buf, uint32_t size)
{
  if (!swsys_env_i.get_device_id) {
    swsys_printf("swsys_get_device_id not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.get_device_id(buf, size );
  }
}

bool swsys_write_buffer_into_file(uint8_t *buffer, uint32_t buffer_len, void *filename)
{
  if (!swsys_env_i.write_buffer_into_file) {
    swsys_printf("swsys_write_buffer_into_file not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.write_buffer_into_file(buffer, buffer_len, filename);
  }
}

bool swsys_read_file_to_buffer(void *filename, uint8_t *buffer, uint32_t read_len)
{
  if (!swsys_env_i.read_file_to_buffer) {
    swsys_printf("swsys_read_file_to_buffer not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.read_file_to_buffer(filename, buffer, read_len);
  }
}

bool swsys_init_tsens()
{
  if (!swsys_env_i.init_tsens) {
    swsys_printf("swsys_init_tsens not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.init_tsens();
  }
}

bool swsys_read_tsens_sensor(uint32_t sensor_id, int32_t* ret_val)
{
  if (!swsys_env_i.read_tsens_sensor) {
    swsys_printf("swsys_read_tsens_sensor not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.read_tsens_sensor(sensor_id, ret_val);
  }
}

bool swsys_read_max_tsens_sensor(int32_t* ret_val)
{
  if (!swsys_env_i.read_max_tsens_sensor) {
    swsys_printf("swsys_read_max_tsens_sensor not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.read_max_tsens_sensor(ret_val);
  }
}

bool swsys_get_num_of_tsens_sensors(uint32_t* ret_val)
{
  if (!swsys_env_i.read_max_tsens_sensor) {
    swsys_printf("swsys_get_num_of_tsens_sensors not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.get_num_of_tsens_sensors(ret_val);
  }
}

bool swsys_set_lmh_runtime_profile()
{
  if (!swsys_env_i.set_lmh_runtime_profile) {
    swsys_printf("swsys_set_lmh_runtime_profile not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.set_lmh_runtime_profile();
  }
}

bool swsys_init_dispctrl()
{
  if (!swsys_env_i.init_dispctrl) {
    swsys_printf("swsys_init_dispctrl not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.init_dispctrl();
  }
}

bool swsys_dispctrl_off()
{
  if (!swsys_env_i.dispctrl_off) {
    swsys_printf("swsys_dispctrl_off not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.dispctrl_off();
  }
}

bool swsys_dispctrl_on()
{
  if (!swsys_env_i.dispctrl_on) {
    swsys_printf("swsys_dispctrl_on not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.dispctrl_on();
  }
}

swsys_thread_err swsys_thread_create(
    swsys_thread* thread,
    swsys_thread_attr* attr,
    int (*start_routine) (void*),
    void* arg)
{
  if (!swsys_env_i.thread_create) {
    swsys_printf("swsys_thread_create not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_create(thread, attr, start_routine, arg);
  }
}

swsys_thread_err swsys_thread_join(swsys_thread* thread, void** value_ptr)
{
  if (!swsys_env_i.thread_join) {
    swsys_printf("swsys_thread_join not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_join(thread, value_ptr);
  }
}

swsys_thread_err swsys_get_curr_thread(swsys_thread* thread)
{
  if (!swsys_env_i.get_curr_thread) {
    swsys_printf("get_curr_thread not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;  
  }
  else{
	return swsys_env_i.get_curr_thread(thread);
  }
}

swsys_thread_err swsys_thread_setaffinity(swsys_thread* thread, int32_t cpu)
{
  if (!swsys_env_i.thread_setaffinity) {
    swsys_printf("swsys_thread_setaffinity not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;  
  }
  else{
	return swsys_env_i.thread_setaffinity(thread, cpu);
  }
}

swsys_thread_err swsys_thread_getaffinity(swsys_thread* thread, int32_t *cpu)
{
  if (!swsys_env_i.thread_getaffinity) {
    swsys_printf("swsys_thread_getaffinity not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_getaffinity(thread, cpu);
  }
}

swsys_thread_err swsys_thread_lock(void* p_lock)
{
  if (!swsys_env_i.thread_lock) {
    swsys_printf("swsys_thread_lock not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_lock(p_lock);
  }
}

swsys_thread_err swsys_thread_unlock(void* p_lock)
{
  if (!swsys_env_i.thread_unlock) {
    swsys_printf("swsys_thread_unlock not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_unlock(p_lock);
  }
}

swsys_thread_err swsys_thread_lock_init(void** pp_lock, char* lock_name)
{
  if (!swsys_env_i.thread_lock_init) {
    swsys_printf("swsys_thread_lock_init not implemented\n");
    return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
    return swsys_env_i.thread_lock_init(pp_lock, lock_name);
  }
}

swsys_thread_err swsys_thread_semaphore_wait(void* p_sem)
{
  if (!swsys_env_i.thread_semaphore_wait) {
    swsys_printf("thread_semaphore_wait not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_semaphore_wait(p_sem);
  }
}

swsys_thread_err swsys_thread_semaphore_post(void* p_sem, bool resched)
{
  if (!swsys_env_i.thread_semaphore_post) {
    swsys_printf("thread_semaphore_post not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_semaphore_post(p_sem, resched);
  }
}

swsys_thread_err swsys_thread_semaphore_init(void** pp_sem, uint32_t cnt)
{
  if (!swsys_env_i.thread_semaphore_init) {
    swsys_printf("thread_semaphore_init not implemented\n");
    return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_semaphore_init(pp_sem, cnt);
  }
}

swsys_thread_err swsys_thread_sleep(uint32_t time_duration)
{
  if (!swsys_env_i.thread_sleep) {
    swsys_printf("swsys_thread_sleep not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	return swsys_env_i.thread_sleep(time_duration);
  }
}

swsys_thread_err swsys_system_sleep(uint64_t time_duration)
{
  swsys_thread_err result;

  if (!swsys_env_i.system_sleep) {
    swsys_printf("swsys_system_sleep not implemented\n");
	return SWSYS_THREAD_NOT_IMPLEMENTED;
  }
  else{
	swsys_printf("\nGoing into power collapse for %u ms\n", time_duration);
    result = swsys_env_i.system_sleep(time_duration);
    return result;
  }
}

void* swsys_system_lpm_stats(uint32_t lpm_type)
{
  if (!swsys_env_i.system_lpm_stats) {
    swsys_printf("swsys_system_lpm_stats not implemented\n");
    return NULL;
  }
  else{
	return swsys_env_i.system_lpm_stats(lpm_type);
  }
}

bool swsys_is_ap_core()
{
  if (!swsys_env_i.is_ap_core) {
    swsys_printf("swsys_is_ap_core not implemented\n");
	return false;
  }
  else{
	return swsys_env_i.is_ap_core();
  }
}

uint32_t swsys_get_ap_core_num()
{
  if (!swsys_env_i.get_ap_core_num) {
    swsys_printf("swsys_get_ap_core_num not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.get_ap_core_num();
  }
}

uint32_t swsys_get_ncpus()
{
  if (!swsys_env_i.get_ncpus) {
    swsys_printf("swsys_get_ncpus not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.get_ncpus();
  }
}

uint32_t swsys_get_available_ncpus()
{
  if (!swsys_env_i.get_available_ncpus) {
    swsys_printf("swsys_get_available_ncpus not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.get_available_ncpus();
  }
}

uint32_t swsys_init_deferred_cores(uint32_t coreMask)
{
  if (!swsys_env_i.init_deferred_cores) {
    swsys_printf("swsys_init_deferred_cores not implemented\n");
	return 0;
  }
  else{
	return swsys_env_i.init_deferred_cores(coreMask);
  }
}

void swsys_check_cpu_clk(void){

    uint32_t i, ret_freq;

    for (i = 0; i < NUM_OF_CPU_CLUSTERS; i++) {
       swsys_read_cpu_clk(i,&ret_freq);
       DEBUG((EFI_D_WARN, "[CPU_INFO]Cluster[%d] freq is %d\n",i,ret_freq));
    }
}

void swsys_check_system_clk(void){

    uint32_t i, ret_freq;

    for (i = 0; i < NUM_OF_CPU_CLUSTERS; i++) {
       swsys_read_cpu_clk(i,&ret_freq);
       DEBUG((EFI_D_WARN, "[CPU_INFO] Cluster[%d] freq is %d\n",i,ret_freq));
    }
	swsys_read_ddr_clk(&ret_freq);
	DEBUG((EFI_D_WARN, "[DDR_INFO] DDR freq is %d\n",ret_freq));
}

