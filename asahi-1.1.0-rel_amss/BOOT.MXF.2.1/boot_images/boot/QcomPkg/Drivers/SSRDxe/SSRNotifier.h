/*===============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		SSRNotifier.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  10/14/21	 yanw  	    initial version

================================================================================*/

#ifndef __SSR_NOTIFIER_H__
#define __SSR_NOTIFIER_H__

#include "SSRCore.h"

#define QMI_WAIT_SIG                     0x00010000

#define SSCTL_QCCI_OS_SIGNAL_INIT(ptr) \
	  do { \
	    (ptr)->ext_signal = EventInit(0,SCHED_EVENT_STATE_UNSIGNALED, SCHED_EVENT_FLAG_AUTOUNSIGNAL);\
		(ptr)->sig = QMI_WAIT_SIG;\
		(ptr)->timer_sig = 0;\
	  } while(0)

#define SSCTL_QMI_CCI_OS_SIGNAL_WAIT(e, t) EventWaitTimeout((e)->ext_signal, (t))

#define QMI_NOTIFY_SYNC_TIMEOUT		200 // 200ms
#define QMI_NOTIFY_ASYNC_TIMEOUT	500 // 500ms

EFI_STATUS SSRNotifInit(VOID);
EFI_STATUS ssr_broadcast_ssctl_evt_async(SSR_SUBSYS_CTX_TYPE*, ssctl_ssr_event_enum_type_v02 Evt,UINT32);
EFI_STATUS ssr_broadcast_ssctl_evt_sync(SSR_SUBSYS_CTX_TYPE*, ssctl_ssr_event_enum_type_v02 Evt,UINT32);
EFI_STATUS ssr_notify_subsys_status_sync(SSR_SUBSYS_CTX_TYPE*, ssctl_ssr_event_enum_type_v02, UINT32);
EFI_STATUS ssr_notify_shutdown(SSR_SUBSYS_CTX_TYPE*, UINT32);

#endif