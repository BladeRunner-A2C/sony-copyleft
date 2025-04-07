/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 6/9/21    zxue     fix parasoft issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <qdf/pr_debug.h>
#include <qdf/errno.h>
#include "event.h"

static void __timer_event_hanlder(IN EFI_EVENT Event, IN VOID *Context)
{
    struct timer *t = (struct timer*)Context;
    t->handler(t, t->context);
}

int __init_timer(struct timer *t, timer_handler handler, void *context)
{
    EFI_STATUS Status;

    t->handler = handler;
    t->context = context;

    Status = gBS->CreateEvent(
        EVT_TIMER | EVT_NOTIFY_SIGNAL,
        TPL_NOTIFY,
        __timer_event_hanlder,
        t,
        &t->evt);

    if (EFI_ERROR(Status)) {
        pr_err("create timer failed: %r\n", Status);
        return -EINVAL;
    }

    return 0;
}

int __set_timer(struct timer *t, u8 periodic, u32 ms)
{
    EFI_STATUS Status;

    Status = gBS->SetTimer(t->evt, 
        periodic ? TimerPeriodic : TimerRelative, 
        EFI_TIMER_PERIOD_MILLISECONDS(ms));
    
    if (EFI_ERROR(Status)) {
        pr_err("set timer failed: %r\n", Status);
        return -EINVAL;
    }

    return 0;
}

int __cancel_timer(struct timer *t)
{
    EFI_STATUS Status;

    Status = gBS->SetTimer(t->evt, TimerCancel, 0);

    if (EFI_ERROR(Status)) {
        pr_err("cancel timer failed: %r\n", Status);
        return -EACCES;
    }

    return 0;
}

int __close_timer(struct timer *t)
{
    EFI_STATUS Status;

    Status = gBS->CloseEvent(t->evt);

    if (EFI_ERROR(Status)) {
        pr_err("close timer failed: %r\n", Status);
        return -EACCES;
    }

    return 0;
}


void __wait_for_enter_key(void)
{
    UINTN EventIndex;
    BOOLEAN ExitLoop = FALSE;
    EFI_INPUT_KEY Key;

    do {

        gBS->WaitForEvent(1, &gST->ConIn->WaitForKey, &EventIndex);
        gST->ConIn->ReadKeyStroke(gST->ConIn, &Key);

    } while (!(Key.UnicodeChar == CHAR_LINEFEED ||
        Key.UnicodeChar == CHAR_CARRIAGE_RETURN) ||
        !(ExitLoop));
}