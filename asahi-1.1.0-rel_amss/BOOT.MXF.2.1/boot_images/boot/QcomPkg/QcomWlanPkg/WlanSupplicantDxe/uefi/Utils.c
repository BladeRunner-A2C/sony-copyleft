/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "Utils.h"
#include "Debug.h"
#include <Library/UefiLib.h>

#define WALL_TIMER_STEP_INTERVAL 10 /* Millisecond */

struct WallTimer {
    UINT32 Flags;
    EFI_EVENT Timer;
    MILLISECOND_TYPE Wall;
} __GlobalWallTimer;

enum WallTimerFlags
{
    WALL_TIMER_FLAG_OPENED = 1,
    WALL_TIMER_FLAG_STARTED = 2
};

STATIC VOID WallTimerHandler(
    IN EFI_EVENT Event,
    IN VOID *Context)
{
    struct WallTimer *Timer = Context;

    Timer->Wall += WALL_TIMER_STEP_INTERVAL;
}

STATIC EFI_STATUS __WallTimerOpen(VOID)
{
    EFI_STATUS Status;

    Status = gBS->CreateEvent(
        EVT_TIMER | EVT_NOTIFY_SIGNAL,
        TPL_NOTIFY,
        WallTimerHandler,
        &__GlobalWallTimer,
        &__GlobalWallTimer.Timer);

    return Status;
}

STATIC EFI_STATUS __WallTimerClose(VOID)
{
    EFI_STATUS Status;

    Status = gBS->CloseEvent(&__GlobalWallTimer.Timer);
    
    return Status;
}

STATIC EFI_STATUS __WallTimerStart(VOID)
{
    EFI_STATUS Status;

    Status = gBS->SetTimer(
        __GlobalWallTimer.Timer,
        TimerPeriodic,
        EFI_TIMER_PERIOD_MILLISECONDS(WALL_TIMER_STEP_INTERVAL));

    return Status;
}

STATIC EFI_STATUS __WallTimerStop(VOID)
{
    EFI_STATUS Status;

    Status = gBS->SetTimer(
        __GlobalWallTimer.Timer,
        TimerCancel, 0);

    return Status;
}

VOID WallTimerAttach(VOID)
{
    EFI_STATUS Status;

    if (!(__GlobalWallTimer.Flags & WALL_TIMER_FLAG_OPENED)) {
        Status = __WallTimerOpen();
        if (EFI_ERROR(Status)) {
            return;
        }
        __GlobalWallTimer.Flags |= WALL_TIMER_FLAG_OPENED;
    }

    if (!(__GlobalWallTimer.Flags & WALL_TIMER_FLAG_STARTED)) {
        Status = __WallTimerStart();
        if (EFI_ERROR(Status)) {
            return;
        }
        __GlobalWallTimer.Flags |= WALL_TIMER_FLAG_STARTED;
    }
}

VOID WallTimerDetach(VOID)
{
    EFI_STATUS Status;

    if (__GlobalWallTimer.Flags & WALL_TIMER_FLAG_STARTED) {
        Status = __WallTimerStop();
        if (EFI_ERROR(Status)) {
            return;
        }

        __GlobalWallTimer.Flags &= ~WALL_TIMER_FLAG_STARTED;
    }

    if (__GlobalWallTimer.Flags & WALL_TIMER_FLAG_OPENED) {
        Status = __WallTimerClose();
        if (EFI_ERROR(Status)) {
            return;
        }

        __GlobalWallTimer.Flags &= ~WALL_TIMER_FLAG_OPENED;
    }
}

MILLISECOND_TYPE GetTimeInMillisecond(VOID)
{
    return __GlobalWallTimer.Wall;
}