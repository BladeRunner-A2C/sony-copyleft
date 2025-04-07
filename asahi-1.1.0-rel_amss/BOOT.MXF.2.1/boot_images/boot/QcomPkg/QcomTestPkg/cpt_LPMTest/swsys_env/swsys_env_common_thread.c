/*
===========================================================================
*/
/**
  @file swsys_env_common_thread.c

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

#include "swsys_env.h"
#include "swsys_env_common_thread.h"

swsys_thread_err swsys_thread_create_common(
    swsys_thread* thread,
    swsys_thread_attr* attr,
    int (*start_routine) (void*),
    void* arg)
{
  // common threading not implemented now
  return SWSYS_THREAD_NOT_IMPLEMENTED;
}

swsys_thread_err swsys_thread_join_common(swsys_thread* thread, void** value_ptr)
{
  return SWSYS_THREAD_NOT_IMPLEMENTED;
}

swsys_thread_err swsys_thread_setaffinity_common(swsys_thread* thread, int32_t cpu)
{
  return SWSYS_THREAD_NOT_IMPLEMENTED;
}

swsys_thread_err  swsys_thread_getaffinity_common(swsys_thread* thread, int32_t *cpu)
{
  return SWSYS_THREAD_NOT_IMPLEMENTED;
}

swsys_thread_err swsys_thread_lock_common(void* p_lock)
{
  // common threading not implemented now
  return SWSYS_THREAD_NOT_IMPLEMENTED;
}

swsys_thread_err swsys_thread_unlock_common(void* p_lock)
{
  // common threading not implemented now
  return SWSYS_THREAD_NOT_IMPLEMENTED;
}

swsys_thread_err swsys_thread_lock_init_common(void** pp_lock)
{
  // common threading not implemented now
  return SWSYS_THREAD_NOT_IMPLEMENTED;
}

