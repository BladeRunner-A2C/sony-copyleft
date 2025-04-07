/*===============================================================================
  Copyright (c) 2020-2021,2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc
  
  FILE: 		SSRCore.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/10/20	 yanw  	    initial version

================================================================================*/
#ifndef __SSR_CORE_H__
#define __SSR_CORE_H__

#include <Protocol/EFISmp2p.h>
#include <Protocol/EFISSR.h>
#include <Protocol/EFIQSocketQMI.h>
#include <Protocol/EFIPIL.h>
#include "SSRCfg.h"

typedef struct
{
	smp2p_context_type* Ctx;
	UINT32				Data;
	VOID* 				SubsysCtx;
} SSR_SMP2P_INFO;

typedef enum
{
	SSR_SUBSYS_STATUS_UNKOWN = 0,
	SSR_SUBSYS_STATUS_DOWN,
	SSR_SUBSYS_STATUS_UP
} SSR_SUBSYS_STATUS;

typedef enum
{
	SSR_PHASE_UNKOWN = 0,
	SSR_PHASE_SHUTDOWN,
	SSR_PHASE_BRINGUP,
	SSR_PHASE_RESTART,
} SSR_PHASE_TYPE;

#define SMP2P_REG_DONE_BIT	0
#define WDOG_REG_DONE_BIT	1
//#define QMI_REG_DONE_BIT	2 not in use
#define ERR_READY_CONFIRMED_BIT	3
#define IN_RESTART_BIT		4
#define WDOG_FIRED_BIT		5

#define SSR_SET_STATUS_BIT(x,b)		((x)=(x)|1<<(b))
#define SSR_CLEAR_STATUS_BIT(x,b)	((x)=(x)&(~(1<<(b))))
#define SSR_STATUS_BIT_IS_SET(x,b)  (((x)&(1<<(b)))!=0)

#define SSR_SET_CURRENT_SUBSYS_ID(c,s)	\
		({if ((c)&&((c)->RuntimeInfo)&&((c)->RuntimeInfo->CurrentSubsysId==0)) (c)->RuntimeInfo->CurrentSubsysId=(s);})

typedef struct
{
	SSR_PHASE_TYPE CurrPhase;
	Thread* 	SSRThread;
	UINT32		StatusTrace;
	UINT32 		CurrentSubsysId;
	CHAR8		ImageName[NAME_MAX_LENGTH];	
	qmi_client_type			QmiHdl;
	VOID*					LastRespMsg;
} SSR_RUNTIME_INFO;

typedef struct
{
	SSR_SUBSYS_CFG_TYPE* 	SubsysCfg;
	SSR_SMP2P_INFO*			Smp2pInfoPtr;	/* currently only support 1 smp2p entry per subsystem */
	UINT32					Smp2pCtxNum;
	SSR_RUNTIME_INFO*		RuntimeInfo;
	SSR_SUBSYS_STATUS		SubsysStatus;
	RESTART_LEVEL			RestartLvl;
	UINT32					CrashCnt;
	LIST_ENTRY				CbList;
} SSR_SUBSYS_CTX_TYPE;

EFI_STATUS InitSubsysCtx(UINT32, SSR_SUBSYS_CTX_TYPE**);
EFI_STATUS RegisterSubsys(UINT32);
EFI_STATUS RegisterCbForSubsys(CHAR8*, UINT32, SSR_DRIVER_CB_TYPE*, UINT32);
EFI_STATUS ModifyRestartLvl(UINT32, RESTART_LEVEL);
EFI_STATUS UnRegisterCbForSubsys(CHAR8* DrvName, UINT32 SubsysId);
EFI_STATUS LookForSubsysWithQmiHdl(UINT32* NumFound, SSR_SUBSYS_CTX_TYPE** CtxArr, UINT32 ArrLen);
EFI_STATUS CheckSubsysStatus(UINT32, SSR_SUBSYS_STATUS*);
EFI_STATUS ShutdownSubsys(UINT32, BOOLEAN);
EFI_STATUS BringupSubsys(CHAR8*, PIL_SUBSYS_CFG_TYPE*);

#endif // __SSR_CORE_H__