/*
===========================================================================
*/
/**
  @file swsys_env.h

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

#ifndef SWSYS_ENV_H
#define SWSYS_ENV_H

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

// This should be before including <timer.h> 
// since timer_t defined in <KernIntfLib.h> is being used in <time.h>
//#include <KernIntfLib.h>

//#include <time.h>

#define KEEP_DISPLAY_OFF    0   //Keep display off during and after the end of sleep test
#define KEEP_DISPLAY_ON     1   //Keep display on during sleep test
#define DISPLAY_TOGGLE      2   //Turn off display at beginning of sleep test an turn it back on when sleep test is done
#define DISPLAY_ITERATION   3	//Toggle display per sleep iteration

#define NUM_OF_CPU_CLUSTERS 4

//Time for testapps to do thread sleep when pausing 
#define TESTAPP_IDLE_TIME_DURING_PAUSE 500

typedef long int __time_t;

typedef enum {
  SWSYS_ENV_NONE = 0x0,
  SWSYS_ENV_UEFI = 0x1,
  SWSYS_ENV_LNX  = 0x2,
  SWSYS_ENV_AND  = 0x4,
  SWSYS_ENV_ALL  = 0xFFFFFFFF,
} swsys_env_type;

typedef enum {
  SWSYS_THREAD_SUCCESS = 0x0,
  SWSYS_THREAD_NOT_IMPLEMENTED = 0x1,
  SWSYS_THREAD_ENV_ERROR = 0x2,
} swsys_thread_err;

typedef struct swsys_thread {
  void* env_thread;
} swsys_thread;

typedef struct swsys_thread_attr {
  //nothing here for now, we can add things as needed
  int32_t   priority;
  uint64_t  stack_size;
  char      thread_name[16];
} swsys_thread_attr;

typedef struct swsys_env_s {
  swsys_env_type env;
  char*          env_str;

  // dynamic memory
  void* (*malloc)    (uint64_t size);
  void* (*malloc_uc) (uint64_t size); // uncached allocation, uefi only
  void* (*malloc_pages) (uint64_t pages);
  void  (*free)      (void* buf);
  void (*free_pages) (void* buf, uint64_t pages);

  // file operations
  FILE*    (*fopen)  (const char* filename, const char* mode);
  int64_t  (*fclose) (FILE* f);
  uint64_t (*fread)  (void* buf, uint64_t size, uint64_t count, FILE* f);
  uint64_t (*fwrite) (const void* buf, uint64_t size, uint64_t count, FILE* f);
  int32_t  (*fflush) (FILE* stream);
  FILE*    (*stdout_io) ();

  // printing
  //int32_t (*printf)   (const char* format, ...);
  int32_t (*vprintf)   (const char* format, va_list arg);
  //int32_t (*snprintf) (char* s, uint64_t n, const char* format, ...);
  int32_t (*vsnprintf) (char* s, uint64_t n, const char* format, va_list arg);

  // string conversions
  int32_t  (*strtoi32) (const char* str, char** endptr, int32_t base);
  int64_t  (*strtoi64) (const char* str, char** endptr, int32_t base);
  uint32_t (*strtou32) (const char* str, char** endptr, int32_t base);
  uint64_t (*strtou64) (const char* str, char** endptr, int32_t base);
  float    (*strtof)   (const char* str, char** endptr);
  double   (*strtod)   (const char* str, char** endptr);

  // string compare
  int32_t (*strncmp) (const char* str1, const char* str2, uint64_t num);
  int32_t (*strcmp) (const char* str1, const char* str2);
  char*   (*strstr) (const char* str1, const char* str2);
  uint64_t (*strlen) (const char* str);

  void (*exit) (int32_t status);

  void    (*srand) (uint32_t seed);
  int32_t (*rand)  ();

  void (*memcpy) (void* dest, const void* src, uint64_t len);
  void (*memset) (void* ptr, int32_t value, uint64_t num);

  uint64_t (*flash_write) (void* buf, uint64_t size, uint64_t count, char* partition);
  uint64_t (*flash_read) (void* buf, uint64_t size, uint64_t count, char* partition, uint64_t* bytes_read);

  void (*reboot) ();

  void (*init_ddr_clk) (uint32_t init_freq_khz, uint32_t display_mode);
  void (*deinit_ddr_clk) ();
  uint32_t (*switch_ddr_clk) (uint32_t freq_khz);
  bool (*read_ddr_clk) (uint32_t* freq_khz);
  uint8_t (*get_ddr_freq_table) (uint32_t *freq_list);
  void (*init_shub_clk) (uint32_t init_freq_khz, uint32_t display_mode);
  void (*deinit_shub_clk) ();
  uint32_t (*switch_shub_clk) (uint32_t freq_khz);
  bool (*read_shub_clk) (uint32_t* freq_khz);
  uint8_t (*get_shub_freq_table) (uint32_t *freq_list);
  void (*init_cpu_clk) ();
  void (*deinit_cpu_clk) ();
  uint32_t (*switch_cpu_clk) (uint32_t cluster, uint32_t freq_khz);
  uint32_t (*cpu_available_clks) (uint32_t cluster, uint32_t* freq_vol_tbl);
  bool (*read_cpu_clk) (uint32_t cluster, uint32_t* freq_khz);

  bool (*init_tsens) ();
  bool (*read_tsens_sensor) (uint32_t sensor_id, int32_t* ret_val);
  bool (*read_max_tsens_sensor) (int32_t* ret_val);
  bool (*get_num_of_tsens_sensors) (uint32_t* ret_val);
  bool (*set_lmh_runtime_profile)();

  bool (*init_dispctrl) ();
  bool (*dispctrl_off) ();
  bool (*dispctrl_on) ();

  void (*busywait) (uint32_t wait_us);

  time_t (*time) (time_t* time);
  double (*difftime) (time_t end, time_t beginning);

  uint64_t (*get_time_us)();
  uint64_t (*get_time_sec)();

  bool (*get_device_id)(uint8_t *device_id, uint32_t size);

  bool (*init_sysinfo)(void);
  bool (*get_serial_number)(uint64_t *serial_number);
  bool (*get_chip_id)(char* chip_id, uint32_t size);
  bool (*get_chip_version)(uint32_t *chip_version);
  bool (*get_processor_name)(char *processor_name, uint32_t size);
    
  bool (*write_buffer_into_file)(uint8_t *buffer, uint32_t buffer_len, void *filename);
  bool (*read_file_to_buffer)(void *filename, uint8_t *buffer, uint32_t read_len);

  swsys_thread_err (*thread_create) (swsys_thread* thread,
                                     swsys_thread_attr* attr,
                                     int (*start_routine) (void*),
                                     void* arg);
  swsys_thread_err (*thread_join) (swsys_thread* thread,
                          void** value_ptr);


  swsys_thread_err (*get_curr_thread)(swsys_thread* thread);

  swsys_thread_err (*thread_setaffinity) (swsys_thread* thread, int32_t cpu);
  swsys_thread_err (*thread_getaffinity) (swsys_thread* thread, int32_t *cpu);
  
  swsys_thread_err (*thread_lock) (void* p_lock);
  swsys_thread_err (*thread_unlock) (void* p_lock);
  swsys_thread_err (*thread_lock_init) (void** pp_lock, char* lock_name);
  
  swsys_thread_err (*thread_semaphore_wait) (void* p_sem);
  swsys_thread_err (*thread_semaphore_post) (void* p_sem, bool resched);
  swsys_thread_err (*thread_semaphore_init) (void** pp_sem, uint32_t cnt);
    
  swsys_thread_err (*thread_sleep) (uint32_t time_duration);
  swsys_thread_err (*system_sleep) (uint64_t time_duration);
  void* (*system_lpm_stats) (uint32_t lpm_type);
  
  bool (*is_ap_core) ();
  uint32_t (*get_ap_core_num) ();
  uint32_t (*get_ncpus)(); // to get supported number of CPUs
  uint32_t (*get_available_ncpus)(); // to get available number of CPUs
  uint32_t (*init_deferred_cores)(uint32_t coreMask); // to init deferred cores
} swsys_env;

void swsys_enable_uc_malloc ();
void* swsys_malloc    (uint64_t size);
void* swsys_malloc_uc (uint64_t size); // uncached allocation, uefi only
void* swsys_malloc_pages (uint64_t size);
void  swsys_free      (void* buf);
void  swsys_free_pages     (void* buf, uint64_t pages);

FILE*    swsys_fopen  (const char* filename, const char* mode);
int64_t  swsys_fclose (FILE* f);
uint64_t swsys_fread  (void* buf, uint64_t size, uint64_t count, FILE* f);
uint64_t swsys_fwrite (const void* buf, uint64_t size, uint64_t count, FILE* f);
int32_t  swsys_fflush (FILE* stream);
FILE*    swsys_stdout ();

int32_t swsys_printf    (const char* format, ...);
int32_t swsys_vprintf   (const char* format, va_list arg);
int32_t swsys_snprintf  (char* s, uint64_t n, const char* format, ...);
int32_t swsys_vsnprintf (char* s, uint64_t n, const char* format, va_list arg);

int32_t  swsys_strtoi32 (const char* str, char** endptr, int32_t base);
int64_t  swsys_strtoi64 (const char* str, char** endptr, int32_t base);
uint32_t swsys_strtou32 (const char* str, char** endptr, int32_t base);
uint64_t swsys_strtou64 (const char* str, char** endptr, int32_t base);
float    swsys_strtof   (const char* str, char** endptr);
double   swsys_strtod   (const char* str, char** endptr);

int32_t  swsys_strncmp (const char* str1, const char* str2, int64_t num);
int32_t  swsys_strcmp  (const char* str1, const char* str2);
char*    swsys_strstr  (const char* str1, const char* str2);
uint64_t swsys_strlen  (const char* str);

void swsys_exit (int32_t status);

void    swsys_srand (uint32_t seed);
int32_t swsys_rand  ();

void swsys_memcpy(void* dest, const void* src, uint64_t len);
void swsys_memset(void* ptr, int32_t value, uint64_t num);

uint64_t swsys_flash_write (void* buf, uint64_t size, uint64_t count, char* partition);
uint64_t swsys_flash_read (void* buf, uint64_t size, uint64_t count, char* partition, uint64_t* bytes_read);

void swsys_init_ddr_clk(uint32_t init_freq_khz, uint32_t display_mode);
void swsys_deinit_ddr_clk();
uint32_t swsys_switch_ddr_clk(uint32_t freq_khz);
bool swsys_read_ddr_clk(uint32_t* freq_khz);
uint8_t swsys_get_ddr_freq_table(uint32_t *freq_list);
uint8_t swsys_get_shub_freq_table(uint32_t *freq_list);
void swsys_init_shub_clk(uint32_t init_freq_khz,  uint32_t display_mode);
void swsys_deinit_shub_clk();
uint32_t swsys_switch_shub_clk(uint32_t freq_khz);
bool swsys_read_shub_clk(uint32_t* freq_khz);
void swsys_init_cpu_clk();
void swsys_deinit_cpu_clk();
uint32_t swsys_switch_cpu_clk(uint32_t cpu_num, uint32_t freq_khz);
uint32_t swsys_cpu_available_clks(uint32_t cpu_num, uint32_t* freq_tbl);
bool swsys_read_cpu_clk(uint32_t cpu_num, uint32_t* freq_khz);

void swsys_busywait(uint32_t wait_us);

bool swsys_init_tsens();
bool swsys_read_tsens_sensor(uint32_t sensor_id, int32_t* ret_val);
bool swsys_read_max_tsens_sensor(int32_t* ret_val);
bool swsys_get_num_of_tsens_sensors(uint32_t* ret_val);
bool swsys_set_lmh_runtime_profile();


bool swsys_init_dispctrl();
bool swsys_dispctrl_off();
bool swsys_dispctrl_on();

time_t swsys_time(time_t* time);
double swsys_difftime(time_t end, time_t beginning);

uint64_t swsys_get_time_us();
uint64_t swsys_get_time_sec();

bool swsys_init_sysinfo();
bool swsys_get_serial_number(uint64_t *serial_number);
bool swsys_get_chip_id(char* chip_id, uint32_t size);
bool swsys_get_chip_version(uint32_t *chip_version);
bool swsys_get_processor_name(char *processor_name, uint32_t size);
bool swsys_get_device_id(uint8_t *buf, uint32_t len);

bool swsys_write_buffer_into_file(uint8_t *buffer, uint32_t buffer_len, void *filename);
bool swsys_read_file_to_buffer(void *filename, uint8_t *buffer, uint32_t read_len);

void swsys_reboot ();

extern swsys_env swsys_env_i;

// Sets up the swsys_env_i. Defined in each environment.
void swsys_env_init();

swsys_env_type swsys_get_env();
char*          swsys_get_env_str();

swsys_thread_err swsys_thread_create(
    swsys_thread* thread,
    swsys_thread_attr* attr,
    int (*start_routine) (void*),
    void* arg);
swsys_thread_err swsys_thread_join(swsys_thread* thread, void** value_ptr);
swsys_thread_err swsys_get_curr_thread(swsys_thread* thread);
swsys_thread_err swsys_thread_setaffinity(swsys_thread* thread, int32_t cpu);
swsys_thread_err swsys_thread_getaffinity(swsys_thread* thread, int32_t *cpu);
swsys_thread_err swsys_thread_lock(void* p_lock);
swsys_thread_err swsys_thread_unlock(void* p_lock);
swsys_thread_err swsys_thread_lock_init(void** pp_lock, char* lock_name);
swsys_thread_err swsys_thread_semaphore_wait(void* p_sem);
swsys_thread_err swsys_thread_semaphore_post(void* p_sem, bool resched);
swsys_thread_err swsys_thread_semaphore_init(void** pp_sem, uint32_t cnt);
swsys_thread_err swsys_thread_sleep(uint32_t time_duration);
swsys_thread_err swsys_system_sleep(uint64_t time_duration);
void *swsys_system_lpm_stats(uint32_t lpm_type);

bool swsys_is_ap_core();
uint32_t swsys_get_ap_core_num();
uint32_t swsys_get_ncpus();
uint32_t swsys_get_available_ncpus();
uint32_t swsys_init_deferred_cores(uint32_t coreMask);

void swsys_check_cpu_clk(void);
void swsys_check_system_clk(void);

#endif // SWSYS_ENV_H
