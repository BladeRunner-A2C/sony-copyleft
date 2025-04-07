/*
===========================================================================
*/
/**
  @file swsys_env_common_thread.h

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

#ifndef SWSYS_ENV_COMMON_THREAD_H
#define SWSYS_ENV_COMMON_THREAD_H

#include "swsys_env.h"

swsys_thread_err swsys_thread_create_common(
    swsys_thread* thread,
    swsys_thread_attr* attr,
    int (*start_routine) (void*),
    void* arg);
swsys_thread_err swsys_thread_join_common(swsys_thread* thread, void** value_ptr);

swsys_thread_err swsys_thread_mutex_lock(void* mutex_ptr);

swsys_thread_err swsys_thread_mutex_unlock(void* mutex_ptr);

swsys_thread_err swsys_thread_mutex_init(void* mutex_ptr);

#endif // SWSYS_ENV_COMMON_THREAD_H
