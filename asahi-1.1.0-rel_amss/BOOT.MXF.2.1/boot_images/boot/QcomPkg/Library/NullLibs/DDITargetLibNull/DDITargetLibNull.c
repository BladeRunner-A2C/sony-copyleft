/**
 * @file DDITargetLibNull.c
 */
/*=============================================================================

                                DDI Null
                                Source File

  Copyright (c) 2021, 2023 QUALCOMM Technologies Incorporated.
  All rights reserved.
===============================================================================

===============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

===============================================================================
when       who     what, where, why
--------   ---     ------------------------------------------------------------
03/22/23   ck      Added ddi_int_out, ddi_out, last_data
08/12/21   ck      Initial version
==============================================================================*/

#include "ddi_drivers.h"


uint8 ddi_int_out[4];
uint8 ddi_out[4];
boolean last_data = FALSE;


ddi_mode_code ddi_get_mode(void)
{
  return DDI_NOOP_MODE;
}


void ddi_pre_entry(void)
{
}


ddi_exit_code ddi_entry(ddi_result_code *ddi_test_result_code )
{
  return DDI_EXIT_HLOS;
}


void ddi_set_param(void)
{
}

