/****************************************************************************

                 Embedded USB Debugger Library Routines
                 --------------------------------------

DESCRIPTION
-----------
This file contains private APIs and data structures for use within EUD Library.

Copyright (c) 2020, 2023 QUALCOMM Technologies Incorporated.
All Rights Reserved. Qualcomm Proprietary

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/NullLibs/EudTargetLibNull/eud_config.c#1 $

when       who      what, where, why
--------   ---      ----------------------------------------------------------
02/22/23   ck       Removed unnecessary header and info
07/21/20   amcheriy Created.
******************************************************************************/

#include "com_dtypes.h"
#include "eud_config.h"

static const eud_config_type eud_config_data = {
  .bGPIO           = 1,
  .nGPIOIdx        = 55,
  .bBootConfig     = 0,
  .nBootConfigMask = (1 << 11),
  .eud_en_val      = 0,
  .eud_en_csr      = (uint32_t *)0,
  .bStallOnEnable  = 1,
  /* Duration for which boot needs to be stalled (seconds) */
  .nStallDelay     = 12,
};


const eud_config_type *get_target_config(void)
{
  return &eud_config_data;
}
