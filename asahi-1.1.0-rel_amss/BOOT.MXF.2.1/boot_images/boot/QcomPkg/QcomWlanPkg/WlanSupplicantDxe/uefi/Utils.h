/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __EFI_UTILS_H
#define __EFI_UTILS_H

#include <Uefi.h>

// Wall Timer
typedef UINT64 MILLISECOND_TYPE;
typedef UINT64 MICROSECOND_TYPE;

VOID WallTimerAttach(VOID);
VOID WallTimerDetach(VOID);

MILLISECOND_TYPE GetTimeInMillisecond(VOID);

STATIC inline MICROSECOND_TYPE GetTimeInMicrosecond(VOID)
{
    return GetTimeInMillisecond() * 1000;
}

#define getwalltime_us GetTimeInMillisecond
#define getwalltime_ms GetTimeInMillisecond

// NetLib API
#define ntohs(_x)   SwapBytes16(_x)
#define htons(_x)   ntohs(_x)

#endif // !__EFI_UTILS_H