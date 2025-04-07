/*
===========================================================================

FILE:         gpi_cfg.c

DESCRIPTION:  This file implements the GPI Config Data.

===========================================================================

                         Edit History


when           who     what, where, why
----------     ---     -------------------------------------------------------- 
01/24/24       GST     File Created for Milos

===========================================================================
             Copyright (c) 2024 QUALCOMM Technologies, Incorporated.
                    All Rights Reserved
             Confidential and Proprietary - Qualcomm Technologies, Inc
===========================================================================
*/

#include "gpitgtcfgdata.h"
#include "msmhwiobase.h"

#define GSI_0_BASE       (QUPV3_0_QUPV3_ID_1_BASE + 0x00004000)
#define GSI_1_BASE       (QUPV3_1_QUPV3_ID_1_BASE + 0x00004000)
#define GSI_SSC_BASE     (LPASS_BASE              + 0x00B04000)

const tgt_gpi_config_type  tgt_gpi_config[] =
{
   { TRUE, 1, GSI_0_BASE,   0, { 465, 466, 467, 468, 469, 470, 471, 627, 628, 629, 630, 631,   0,   0,   0,   0 } },  /* QUP_0 */
   { TRUE, 2, GSI_1_BASE,   0, { 620, 621, 622, 623, 624, 625, 626, 383, 384, 385, 386, 387,   0,   0,   0,   0 } },  /* QUP_1 */
   { TRUE, 3, GSI_SSC_BASE, 0, { 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426 } }   /* QUP_SSC */
};
