/*
===========================================================================
*/
/**
  @file swsys_env_linux.h

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

#ifndef SWSYS_ENV_LINUX_H
#define SWSYS_ENV_LINUX_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../swsys_env.h"

#define SWSYS_ENV_LINUX_FLAG

void* swsys_malloc_uc_linux (uint64_t size); // uncached allocation, uefi only
//void  swsys_free_linux      (void* buf);

void swsys_reboot_linux();

uint64_t swsys_flash_read_linux (void* buf, uint64_t size, uint64_t count, char* partition, uint64_t* bytes_read);

uint64_t swsys_flash_write_linux (void* buf, uint64_t size, uint64_t count, char* partition);

swsys_thread_err swsys_thread_create_linux(
    swsys_thread* thread,
    swsys_thread_attr* attr,
    void* (*start_routine) (void*),
    void* arg);

swsys_thread_err swsys_thread_join_linux(swsys_thread* thread, void** value_ptr);
#endif // SWSYS_ENV_LINUX_H
