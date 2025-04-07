/*
===========================================================================
*/
/**
  @file swsys_env_uefi_tsens.h

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

#ifndef SWSYS_ENV_UEFI_TSENS_H
#define SWSYS_ENV_UEFI_TSENS_H

#include "../swsys_env.h"
#include <stdbool.h>

bool swsys_init_tsens_uefi();
bool swsys_read_tsens_sensor_uefi(uint32_t sensor_id, int32_t* ret_val);
bool swsys_read_max_tsens_sensor_uefi(int32_t* ret_val);
bool swsys_get_num_of_tsens_sensors_uefi(uint32_t* ret_val);
bool swsys_set_lmh_runtime_profile_uefi();

void swsys_clear_tsens_pause_time(void);
void swsys_set_tsens_pause_time(uint64_t pause_time);
uint64_t swsys_get_tsens_pause_time(void);

#endif // SWSYS_ENV_UEFI_TSNENS_H
