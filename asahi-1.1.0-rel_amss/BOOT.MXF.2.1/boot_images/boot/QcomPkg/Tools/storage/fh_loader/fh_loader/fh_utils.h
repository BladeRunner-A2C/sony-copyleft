/**************************************************************************
 * FILE: fh_utils.h
 *
 * Helper functions.
 *
 * Copyright (c) 2019 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Proprietary
 *
 *************************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Tools/storage/fh_loader/fh_loader/fh_utils.h#1 $
  $DateTime: 2024/04/02 23:00:31 $
  $Author: cirrusp4svc $

when         who   what, where, why
----------   ---   ---------------------------------------------------------
2019-12-18   wek   Create.

===========================================================================*/

#ifndef __FH_UTILS_H__
#define __FH_UTILS_H__

#ifdef _MSC_VER // i.e. if compiling under Windows
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <time.h>

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

double ReturnTimeInSeconds (struct timeval *start_time, struct timeval *end_time);
static double fh_get_delta_seconds(struct timeval *start_time)
{
  struct timeval end_time;
  gettimeofday (&end_time, NULL);
  return ReturnTimeInSeconds (start_time, &end_time);
}

#endif /* __FH_UTILS_H__ */
