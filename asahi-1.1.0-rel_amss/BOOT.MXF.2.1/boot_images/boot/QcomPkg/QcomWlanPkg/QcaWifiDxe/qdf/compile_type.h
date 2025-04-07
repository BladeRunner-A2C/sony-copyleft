/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 23/7/21   zxue     remove unused code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_COMPILE_TYPE_H
#define __QDF_COMPILE_TYPE_H

 /* Compier dependent macros */
#define unlikely(_x)   (_x)
#define likely(_x)     (_x)

#define DEBUG_PARAMETER(_P) (void)(_P)

/*****************************************************************************/
#define __packed
#define __iomem
#define __aligned(x)
#define __force
#define __must_check

/*****************************************************************************/
/* MICROS to disable the code */

#define EXPORT_SYMBOL_GPL(_x)
#define EXPORT_SYMBOL(_x)
#define MODULE_DEVICE_TABLE(_p1, _p2)

#define MHI_COMPILE_TEST 0
#define COMPILE_TEST

/*****************************************************************************/
//:TODO::
#define mod_timer(x, y)  //TODO
#define from_timer(ab, t, retry) NULL

#define IS_ENABLED(_x) (_x)

//:TODO::
struct timer_list{
    void* t;
};

#endif // !__QDF_COMPILE_TYPE_H

