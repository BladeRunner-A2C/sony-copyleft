/*===============================================================================
  Copyright (c) 2020-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc
  
  FILE: 		SSRCore.c
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/15/23   kk         added new APIs to support ssr bringup and shutdown
  08/26/20	 yanw  	    initial version

================================================================================*/

#include <Protocol/EFISmp2p.h>
#include <Protocol/EFIPIL.h>
#include <Protocol/EFISmem.h>
#include <Protocol/EFIGLink.h>
#include <Library/PrintLib.h>
#include <Library/KernelLib.h>
#include <Library/QcomLib.h>
#include <Library/BaseLib.h>
#include <Library/smp2p.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <scm_sip_interface.h>
#include "SSRCore.h"
#include "SSRSmp2p.h"
#include "SSRNotifier.h"

//#define SSR_CORE_DBG_LOG

#define SSR_THREAD_NAME_MAX_LEN		16
#define	SSR_THREAD_STACK_SIZE		(8*1024)

#define SSR_EVT_BITMASK(n)		(1<<(n))

typedef struct {
   VOID                   *Arg;
   UINT32                  VectorNum;
   Event                  *SyncEvent;
} SSR_WDOG_HDL_ARG;

typedef struct
{
	LIST_ENTRY			List;
	CHAR8				DrvName[16];
	SSR_DRIVER_CB_FUNC	Cb;
	VOID*				Arg;
	UINT32				Prio;
} SSR_DRV_CB_ENTRY;

extern EFI_SMP2P_PROTOCOL*  Smp2pProtocol;
STATIC EFI_PIL_PROTOCOL*	PilProtocol = NULL;

UINT32 SubsysRegisteredNum;
SSR_SUBSYS_CTX_TYPE**	SSRSubsysCtx;

extern BOOLEAN SSRNotifierInitDone;

STATIC EFI_STATUS BringupSubsysById(UINT32);

STATIC 
EFI_STATUS InvokeDrvCallbacks(SSR_SUBSYS_CTX_TYPE* SubsysCtx, SSR_EVENT_TYPE Evt)
{
	SSR_DRV_CB_ENTRY* CbEntry;
	LIST_ENTRY*	CbNode;
	EFI_STATUS	Status;
	LIST_ENTRY* CbList = &SubsysCtx->CbList;
	
	for (CbNode = GetFirstNode(CbList); \
				!IsNull(CbList, CbNode); \
				CbNode = GetNextNode(CbList, CbNode))
	{
		CbEntry = BASE_CR(CbNode, SSR_DRV_CB_ENTRY, List);
		ASSERT(CbEntry->DrvName[0]!='\0' && CbEntry->Cb);
		
		Status = CbEntry->Cb(Evt, CbEntry->Arg);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "%a return %r for evt %d\n", \
					CbEntry->DrvName, Status, Evt));
			return Status;
		}
	}
	
	return EFI_SUCCESS;
}


UINT32 FindCurrentSubsysId(SSR_SUBSYS_CTX_TYPE* Ctx)
{
	EFI_STATUS Status;
	SSR_SUBSYS_CFG_TYPE* Cfg=Ctx->SubsysCfg;
	SSR_RUNTIME_INFO* RuntimeInfo=Ctx->RuntimeInfo;
	PIL_SUBSYS_CFG_TYPE PilCfg={0};
	CHAR16	SubsysNameUnicode[NAME_MAX_LENGTH];
	
	if (Cfg==NULL || RuntimeInfo==NULL)
		return 0;
	
	if (Cfg->NumOfSubsysId==1)
		return Cfg->SubsysId[0];
	
	if (RuntimeInfo->CurrentSubsysId!=0)
		return RuntimeInfo->CurrentSubsysId;
	
	if (RuntimeInfo->ImageName[0]!=0)
	{
		if (PilProtocol==NULL)
		{
			Status = gBS->LocateProtocol (&gEfiPilProtocolGuid, NULL, (VOID **) &PilProtocol);
			if (EFI_ERROR(Status))
			{
				DEBUG((EFI_D_ERROR, "Failed to locate PIL protocol\n"));
				return Status;
			}
		}
		
		AsciiStrToUnicodeStrS(RuntimeInfo->ImageName, SubsysNameUnicode, NAME_MAX_LENGTH);
		Status = PilProtocol->PilInitCfgByUnicodeName(SubsysNameUnicode, &PilCfg);
		if (EFI_ERROR(Status))
			return Status;
		
		return PilCfg.SubsysID;
	}
	return 0;
}

STATIC
VOID ResetRuntimeInfo(SSR_SUBSYS_CTX_TYPE* SubsysCtx)
{
	SSR_RUNTIME_INFO*	RuntimeInfo = SubsysCtx->RuntimeInfo;
	
	ASSERT(RuntimeInfo!=NULL);
	
	/*SMP2P_REG_DONE_BIT clear by ResetSmp2pInfo() */
	/*WDOG_REG_DONE_BIT dont need clear once set */
	/*QMI_REG_DONE_BIT dont need clear once set */
	SSR_CLEAR_STATUS_BIT(RuntimeInfo->StatusTrace, ERR_READY_CONFIRMED_BIT);
	/*IN_RESTART_BIT controlled by ssr monitor thread */
	/*WDOG_FIRED_BIT controlled by ssr monitor thread */
	
	/*CurrPhase reset by shutdown func and ssr monitor*/
	/*SSRThread controlled by shutdown func*/
	/*QmiHdl and LastRespMsg controlled by QMI notifier callback */
	
	if (!SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, IN_RESTART_BIT))
	{
		/* image info need reset in shutdown case only */
		RuntimeInfo->CurrentSubsysId = 0;
		ZeroMem(RuntimeInfo->ImageName, sizeof(CHAR8)*NAME_MAX_LENGTH);
	}
}


STATIC
EFI_STATUS RestartSubsystem(SSR_SUBSYS_CTX_TYPE* SubsysCtx)
{
	EFI_STATUS	Status;
	SSR_SUBSYS_CFG_TYPE*	SubsysCfg;
	SSR_RUNTIME_INFO* 		RuntimeInfo;
	
	ASSERT(SubsysCtx!=NULL);
	if ((SubsysCfg = SubsysCtx->SubsysCfg)==NULL)
		ASSERT(0);
	if ((RuntimeInfo=SubsysCtx->RuntimeInfo)==NULL)
		ASSERT(0);
	
	ASSERT(RuntimeInfo->CurrentSubsysId!=0);
	/* todo use shutdown callback defined by clients */
	Status = ShutdownSubsys(RuntimeInfo->CurrentSubsysId, TRUE);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to ssr shutdown subsys_id=%d\n", RuntimeInfo->CurrentSubsysId));
		goto RestartSubsystem_err;
	}
	
	/* todo use bringup callback defined by clients */
	if (RuntimeInfo->ImageName[0]!=0)
		Status = BringupSubsys(RuntimeInfo->ImageName, NULL);
	else
	{
		ASSERT(RuntimeInfo->CurrentSubsysId!=0);
		Status = BringupSubsysById(RuntimeInfo->CurrentSubsysId);
	}
	
RestartSubsystem_err:
	return Status;
}

STATIC
EFI_STATUS HandleRestart(SSR_SUBSYS_CTX_TYPE* SubsysCtx)
{
	SSR_SUBSYS_CFG_TYPE* SubsysCfg;
	EFI_STATUS			 Status;
	
	ASSERT(SubsysCtx!=NULL);
	if ((SubsysCfg=SubsysCtx->SubsysCfg)==NULL)
		ASSERT(0);
	
#if 0
	// debug, check ssr signal before SS boot
	Event*	Evt=NULL;
	SSR_SMP2P_INFO* Smp2pInfo = SubsysCtx->Smp2pInfoPtr;
	Status = Smp2pProtocol->Smp2pGetEvt(Smp2pInfo->Ctx, &Evt);
	if (EFI_ERROR(Status)||Evt==NULL)
		DEBUG((EFI_D_ERROR, "failed to get ssr evt before SS restart\n"));
	else
	{
		if (EventGetSignalState(Evt))
			DEBUG((EFI_D_ERROR, "ssr evt is signaled before SS restart\n"));
		else
			DEBUG((EFI_D_ERROR, "ssr evt is unsignaled before SS restart\n"));
	}
#endif
	if (SubsysCtx->RestartLvl == SYSTEM_RESTART)
	{
		DEBUG((EFI_D_ERROR, "SSR will trigger system reset\n"));
		WatchDogForceBite();
		while(1);
	}
	else if (SubsysCtx->RestartLvl == SUBSYS_RESTART)
	{
		DEBUG((EFI_D_ERROR, "QFWK_SSR: SSR will restart subsystem %a\n", \
				SubsysCfg->Name));
		SubsysCtx->CrashCnt++;
		SSR_SET_STATUS_BIT(SubsysCtx->RuntimeInfo->StatusTrace,IN_RESTART_BIT);
		Status = RestartSubsystem(SubsysCtx);
		SSR_CLEAR_STATUS_BIT(SubsysCtx->RuntimeInfo->StatusTrace,IN_RESTART_BIT);
		DEBUG((EFI_D_ERROR, "QFWK_SSR: SSR %a restart done count=%d\n", \
				SubsysCfg->Name, SubsysCtx->CrashCnt));
	}
	else
		ASSERT(0);
	
#if 0
	// debug, check ssr signal right after SS boot
	Evt=NULL;
	Status = Smp2pProtocol->Smp2pGetEvt(Smp2pInfo->Ctx, &Evt);
	if (EFI_ERROR(Status)||Evt==NULL)
		DEBUG((EFI_D_ERROR, "failed to get ssr evt after SS restart\n"));
	else
	{
		if (EventGetSignalState(Evt))
		{
			UINT32 data=0;
			UINT32 Smp2pRet;
			Smp2pProtocol->Smp2pRead(Smp2pInfo->Ctx, &data, &Smp2pRet);
			DEBUG((EFI_D_ERROR, "ssr evt is signaled after SS restart data=0x%x\n", data));
		}
			
		else
			DEBUG((EFI_D_ERROR, "ssr evt is unsignaled after SS restart\n"));
	}
#endif
	
	/* wait for subsys to fully bootup */
	ThreadSleep(500);
	
	return Status;
}

STATIC
VOID PrintSFR(SSR_SUBSYS_CFG_TYPE* SubsysCfg)
{
	EFI_STATUS Status;
	EFI_SMEM_PROTOCOL*	SmemProtocol = NULL;
	smem_alloc_params_type Params = { 0 };
	
	Status = gBS->LocateProtocol (
			&gEfiSMEMProtocolGuid,
			NULL,
			(VOID **) &SmemProtocol
			);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "Failed to locate smem protocol\n"));
	}
	
	Params.remote_host = SubsysCfg->Host;
	Params.smem_type = SubsysCfg->SFRType;
	
	Status = SmemProtocol->SmemGetAddrEx(&Params);
	if (EFI_ERROR(Status) || Params.buffer==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to locate smem addr\n"));
		return;
	}
	
	DEBUG((EFI_D_ERROR, "QFWK_SSR: SFR: Subsystem Failure Reason : %a\n", (CHAR8*)Params.buffer));
	
}

STATIC
EFI_STATUS HandleProxyUnvote(SSR_SUBSYS_CTX_TYPE* SubsysCtx)
{
	return InvokeDrvCallbacks(SubsysCtx, SSR_PROXY_UNVOTE);
}

STATIC
INT32 SSRMonitorEntry(VOID* Arg)
{
	EFI_STATUS			 Status = EFI_UNSUPPORTED;
	UINT32 				 Smp2pRet = SMP2P_STATUS_FAILURE;
	SSR_SUBSYS_CFG_TYPE* SubsysCfg;
	SSR_SMP2P_INFO* 	 Smp2pInfoPtr;
	smp2p_context_type*  Smp2pCtx;
	SSR_RUNTIME_INFO*	 RuntimeInfo;
	UINT32				 Smp2pCtxNum;
	UINT32				 NewData;
	UINT32			 	 XorDiff;
	UINT32 				CurrentSubsysId;
	SSR_SUBSYS_CTX_TYPE* SubsysCtx = (SSR_SUBSYS_CTX_TYPE*)Arg;
	
	ASSERT(SubsysCtx!=NULL);
	if ((SubsysCfg=SubsysCtx->SubsysCfg)==NULL)
		ASSERT(0);
	if ((Smp2pInfoPtr=SubsysCtx->Smp2pInfoPtr)==NULL)
		ASSERT(0);
	if ((RuntimeInfo=SubsysCtx->RuntimeInfo)==NULL)
		ASSERT(0);
	ASSERT(Smp2pProtocol!=NULL);
	
	while (1)
	{
		if ((Smp2pCtx=Smp2pInfoPtr->Ctx)==NULL)
			ASSERT(0);
		if ((Smp2pCtxNum=SubsysCtx->Smp2pCtxNum)==0)
			ASSERT(0);
		
		if (Smp2pCtxNum == 1) 
		{
			/* wait for both smp2p and wdog */
			Status = Smp2pProtocol->Smp2pWait(Smp2pCtx, &Smp2pRet);
		}
		else {
			/* wait for multiple smp2p */
		}
		
		if (EFI_ERROR(Status) || Smp2pRet!=SMP2P_STATUS_SUCCESS)
		{
			DEBUG((EFI_D_ERROR, "Failed to wait smp2p evt %r Smp2pRet=0x%x\n", \
					Status, Smp2pRet));
			continue;
		}
		
		if (RuntimeInfo->CurrPhase == SSR_PHASE_SHUTDOWN)
		{
			/* only exit in shutdown usecase */
			RuntimeInfo->SSRThread = NULL;
			break;
		}
		
		NewData = 0;
		Status = Smp2pProtocol->Smp2pRead(Smp2pCtx, &NewData, &Smp2pRet);
		if (EFI_ERROR(Status)|| Smp2pRet!=SMP2P_STATUS_SUCCESS)
		{
			DEBUG((EFI_D_ERROR, "Failed to read smp2p entry %r Smp2pRet=0x%x\n", \
					Status, Smp2pRet));
			continue;
		}
		
		DEBUG((EFI_D_ERROR, "QFWK_SSR: %a smp2p update 0x%x -> 0x%x\n", \
			                SubsysCfg->Name, Smp2pInfoPtr->Data, NewData));
		
		/* analyze and handle smp2p evt */
		XorDiff = NewData ^ Smp2pInfoPtr->Data;
		
		/* assume there is only bit set, notify if getting bit reset */
		// todo filter out bit reset
		if (NewData - XorDiff != Smp2pInfoPtr->Data)
		{
			DEBUG((EFI_D_ERROR, "warning: detected bit reset\n", \
		          Smp2pInfoPtr->Data, NewData));
			Smp2pInfoPtr->Data = NewData;
			continue;
		}
		
		Smp2pInfoPtr->Data = NewData;
		
		if (SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, WDOG_FIRED_BIT))
		{
			SSR_CLEAR_STATUS_BIT(RuntimeInfo->StatusTrace, WDOG_FIRED_BIT);
			DEBUG((EFI_D_ERROR, "QFWK_SSR: SSR detected wdog bite on %a\n", \
						SubsysCfg->Name));
						
			if (XorDiff&SSR_EVT_BITMASK((SubsysCfg->ErrFatal).Bit))
				DEBUG((EFI_D_ERROR, "SSR detects err fatal on %a\n", \
						SubsysCfg->Name));
						
			if (NewData&SSR_EVT_BITMASK(SSR_SFR_BIT))
				PrintSFR(SubsysCfg);
			
			HandleRestart(SubsysCtx);
			continue;
		}
		
		if (XorDiff!=0)
		{
							   
			if (XorDiff&SSR_EVT_BITMASK((SubsysCfg->ProxyUnvote).Bit))
			{
				DEBUG((EFI_D_ERROR, "QFWK_SSR: Bit 2 is set: Proxy Unvote is set on %a\n", SubsysCfg->Name));
				
				/* handle ProxyUnvote Evt*/
				Status = HandleProxyUnvote(SubsysCtx);
				if (EFI_ERROR(Status))
					DEBUG((EFI_D_ERROR, "Failed to do proxy unvote by ssr %a\n", SubsysCfg->Name));
				
				/* invoke post_unvote handler */
				InvokeDrvCallbacks(SubsysCtx, SSR_POST_UNVOTE);
			}
			
			if (XorDiff&SSR_EVT_BITMASK((SubsysCfg->ErrReady).Bit))
			{
				/* handle ErrReady Evt*/
				DEBUG((EFI_D_ERROR, "QFWK_SSR: Bit 1 is set: SSR subsystem err handling service is UP on %a\n", \
						SubsysCfg->Name));
				SSR_SET_STATUS_BIT(RuntimeInfo->StatusTrace,ERR_READY_CONFIRMED_BIT);
				if (SubsysCtx->SubsysStatus != SSR_SUBSYS_STATUS_UP)
					SubsysCtx->SubsysStatus = SSR_SUBSYS_STATUS_UP;
				
				CurrentSubsysId = FindCurrentSubsysId(SubsysCtx);
				if (CurrentSubsysId!=0)
					SSR_SET_CURRENT_SUBSYS_ID(SubsysCtx, CurrentSubsysId);
			}
			
			if (XorDiff&SSR_EVT_BITMASK((SubsysCfg->StopAck).Bit))
			{
				/* handle StopAck Evt*/
				DEBUG((EFI_D_ERROR, "QFWK_SSR: Bit 3 is set: SSR recv stop ack INQ from %a\n", \
						SubsysCfg->Name));
			}
			
			if (XorDiff&SSR_EVT_BITMASK((SubsysCfg->ErrFatal).Bit))
			{			
				DEBUG((EFI_D_ERROR, "QFWK_SSR: Bit 0 is set: SSR detects err fatal on %a\n", \
						SubsysCfg->Name));
						
				/* reset wdog flag, leave the event signaled, this will cause this thread 
				run another loop but nothing will happen */ 
				if (SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace,WDOG_FIRED_BIT))
				{				
					DEBUG((EFI_D_ERROR, "QFWK_SSR: SSR detected wdog bite on %a\n", SubsysCfg->Name));
				}
						
				if (NewData&SSR_EVT_BITMASK(SSR_SFR_BIT))
				{
					PrintSFR(SubsysCfg);
				}
						
				HandleRestart(SubsysCtx);
				continue;
			}
		}
		
	};
	DEBUG((EFI_D_ERROR, "ssr monitor thread exiting...\n"));
	ThreadExit(0);
	return 0;	
}

STATIC
SSR_SUBSYS_CTX_TYPE* LookForSubsysCtxById(UINT32 SubsysId)
{
	UINT32 Idx, Num;
	SSR_SUBSYS_CTX_TYPE* Ctx=NULL;
	SSR_SUBSYS_CFG_TYPE* Cfg;
	for (Idx=0;Idx<SubsysRegisteredNum;Idx++)
	{
		if ((Cfg = SSRSubsysCtx[Idx]->SubsysCfg)==NULL)
			ASSERT(0);
		for (Num=0;Num<Cfg->NumOfSubsysId;Num++)
		{
			if (Cfg->SubsysId[Num] == SubsysId)
			{
				Ctx = SSRSubsysCtx[Idx];
				return Ctx;
			}
		}
	}
	return NULL;
}

EFI_STATUS LookForSubsysWithQmiHdl(
	UINT32* NumFound, 
	SSR_SUBSYS_CTX_TYPE** CtxArr,
	UINT32 ArrLen)
{
	UINT32 Idx;
	SSR_RUNTIME_INFO* RuntimeInfo;
	UINT32 Found=0;
	
	for (Idx=0;Idx<SubsysRegisteredNum;Idx++)
	{
		if ((RuntimeInfo=SSRSubsysCtx[Idx]->RuntimeInfo)==NULL)
			ASSERT(0);
		if (RuntimeInfo->QmiHdl != NULL)
		{
			if (CtxArr && ArrLen > Found)
				CtxArr[Found] = SSRSubsysCtx[Idx];
			Found++;
		}
	}
	*NumFound = Found;
	if (Found==0)
		return EFI_NOT_FOUND;
	else if (Found>ArrLen)
		return EFI_BUFFER_TOO_SMALL;
	else
		return EFI_SUCCESS;
}


EFI_STATUS InitSubsysCtx(UINT32 SubsysId, SSR_SUBSYS_CTX_TYPE** CtxPtr)
{
	SSR_SUBSYS_CTX_TYPE* Ctx;
	SSR_SUBSYS_CFG_TYPE* Cfg;
	SSR_RUNTIME_INFO* RuntimeInfo;

	if ((Ctx = LookForSubsysCtxById(SubsysId)) == NULL)
	{
		Cfg = LookupSSRCfgById(SubsysId);
		if (Cfg==NULL)
			return EFI_UNSUPPORTED;
		
		
		Ctx = AllocateZeroPool(sizeof(SSR_SUBSYS_CTX_TYPE));
		if (Ctx == NULL)
			return EFI_OUT_OF_RESOURCES;
		
		Ctx->SubsysCfg = Cfg;
		Cfg->SubsysCtx = Ctx;
		SSRSubsysCtx[SubsysRegisteredNum++] = Ctx;
		
		InitializeListHead(&Ctx->CbList);
	}
	
	if (Ctx->RuntimeInfo == NULL)
	{
		RuntimeInfo = AllocateZeroPool(sizeof(SSR_RUNTIME_INFO));
		if (Ctx == NULL)
			return EFI_OUT_OF_RESOURCES;
		Ctx->RuntimeInfo = RuntimeInfo;
	}
	*CtxPtr = Ctx;
	return EFI_SUCCESS;
}


STATIC
enum HandlerStatus SSRWdogIntrHandler (VOID *Arg)
{
  SSR_WDOG_HDL_ARG* IsrCtxt = (SSR_WDOG_HDL_ARG*)Arg;
  Event* ISRHandleEvt = IsrCtxt->SyncEvent;
  SSR_SUBSYS_CTX_TYPE* SubsysCtx = (SSR_SUBSYS_CTX_TYPE*)IsrCtxt->Arg;
  
  /* disregard if in restart process */
  if (SSR_STATUS_BIT_IS_SET(SubsysCtx->RuntimeInfo->StatusTrace,IN_RESTART_BIT))
	  return HANDLER_RESCHEDULE;

  // required to transition into active state
  UINT32 Vect = IsrCtxt->VectorNum;
  
  SSR_SET_STATUS_BIT(SubsysCtx->RuntimeInfo->StatusTrace,WDOG_FIRED_BIT);

  // After handling the callback need to re-enable
  MaskInterrupt (Vect);

  // Signal the smp2p evt, Reschedule param has to be false in ISR
  EventSignal (ISRHandleEvt, FALSE); 

  return HANDLER_RESCHEDULE;
}

STATIC
EFI_STATUS RegIntrHdlWithEvt(
	SSR_SUBSYS_CTX_TYPE* SubsysCtx,
	Event* Evt
	)
{
	SSR_WDOG_HDL_ARG *IsrCtxt;
	SSR_SUBSYS_CFG_TYPE* SubsysCfg;
	UINT32 Vector;
	enum IntrConfig IntrCfg;
	
	ASSERT(SubsysCtx && SubsysCtx->SubsysCfg);
	SubsysCfg = SubsysCtx->SubsysCfg;
	Vector = (SubsysCfg->WdogIntr).Vector;
	IntrCfg = (SubsysCfg->WdogIntr).IntrCfg;
	
	IsrCtxt = AllocatePool (sizeof(SSR_WDOG_HDL_ARG));
    if (IsrCtxt == NULL)
    return EFI_OUT_OF_RESOURCES;

	IsrCtxt->Arg = SubsysCtx;
	IsrCtxt->VectorNum = Vector;
	if (Evt != NULL)
		IsrCtxt->SyncEvent = Evt;
	else {
		IsrCtxt->SyncEvent = EventInit (0, SCHED_EVENT_STATE_UNSIGNALED, \
										SCHED_EVENT_FLAG_AUTOUNSIGNAL);
	}
	
	RegisterIntrHandler(Vector, &SSRWdogIntrHandler, (VOID*)IsrCtxt);
	
	ConfigureInterrupt (Vector, IntrCfg, 0);
	UnmaskInterrupt (Vector);
	return EFI_SUCCESS;
}

EFI_STATUS RegisterSubsys(UINT32 SubsysId)
{
	EFI_STATUS Status;
	SSR_SUBSYS_CFG_TYPE* SubsysCfg=NULL;
	SSR_SUBSYS_CTX_TYPE* SubsysCtx=NULL;
	Thread*				MonThread=NULL;
	SSR_SMP2P_INFO*		Smp2pInfo;
	SSR_RUNTIME_INFO*	RuntimeInfo;
	CHAR8	ThreadName[SSR_THREAD_NAME_MAX_LEN] = { 0 };
	
	if (SubsysId == 0 || SubsysId >= TZ_PIL_AUTH_UNSUPPORTED_PROC)
		return EFI_INVALID_PARAMETER;

	SSRNotifInit();
	
	if (Smp2pProtocol==NULL)
	{
		Status = gBS->LocateProtocol (
				&gEfiSMP2PProtocolGuid,
				NULL,
				(VOID **) &Smp2pProtocol
				);
		if (EFI_ERROR(Status)) {
			DEBUG((EFI_D_ERROR, "Failed to locate smp2p protocol\n"));
			return Status;
		}
	}
	
	Status = InitSubsysCtx(SubsysId, &SubsysCtx);
	if (EFI_ERROR(Status)||SubsysCtx==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to init subsys ctx\n"));
		return Status;
	}
	if ((RuntimeInfo=SubsysCtx->RuntimeInfo)==NULL || \
		(SubsysCfg=SubsysCtx->SubsysCfg)==NULL)
		ASSERT(0);
#ifdef SSR_CORE_DBG_LOG		
	if (SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, SMP2P_REG_DONE_BIT))
		DEBUG((EFI_D_ERROR, "debug: smp2p entry created previously\n"));
#endif
	if (!SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, SMP2P_REG_DONE_BIT))
	{
		/* register smp2p entry */
		if (SubsysCtx->Smp2pInfoPtr==NULL || SubsysCtx->Smp2pCtxNum==0)
		{
			if (SubsysCtx->Smp2pInfoPtr)
				ASSERT(SubsysCtx->Smp2pInfoPtr->Ctx==NULL);
			ASSERT(SubsysCtx->Smp2pCtxNum==0);
			
			Status = RegisterSubsysSmp2pEntry(
						(CHAR8*)((SubsysCfg->ErrFatal).EntryName),
						SubsysCfg->Host,
						SubsysCtx);
			if (EFI_ERROR(Status))
			{
				DEBUG((EFI_D_ERROR, "Failed to register ErrFatal entry\n"));
				return Status;
			}
			
			Status = RegisterSubsysSmp2pEntry(
						(CHAR8*)((SubsysCfg->ProxyUnvote).EntryName),
						SubsysCfg->Host,
						SubsysCtx);
			if (EFI_ERROR(Status))
			{
				DEBUG((EFI_D_ERROR, "Failed to register ProxyUnvote entry\n"));
				return Status;
			}
			
			Status = RegisterSubsysSmp2pEntry(
						(CHAR8*)((SubsysCfg->ErrReady).EntryName),
						SubsysCfg->Host,
						SubsysCtx);
			if (EFI_ERROR(Status))
			{
				DEBUG((EFI_D_ERROR, "Failed to register ErrReady entry\n"));
				return Status;
			}
			
			Status = RegisterSubsysSmp2pEntry(
						(CHAR8*)((SubsysCfg->StopAck).EntryName),
						SubsysCfg->Host,
						SubsysCtx);
			if (EFI_ERROR(Status))
			{
				DEBUG((EFI_D_ERROR, "Failed to register StopAck entry\n"));
				return Status;
			}
			
			SSR_SET_STATUS_BIT(RuntimeInfo->StatusTrace, SMP2P_REG_DONE_BIT);
		}
	}
#ifdef SSR_CORE_DBG_LOG			
	if (SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, WDOG_REG_DONE_BIT))
		DEBUG((EFI_D_ERROR, "debug: wdog interrupt registered previously\n"));
#endif
	if (!SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, WDOG_REG_DONE_BIT))
	{
	/* register wdog interrupt, assuming 0 is not valid wdog int vector */
		if ((SubsysCfg->WdogIntr).Vector != 0)
		{
			Smp2pInfo = SubsysCtx->Smp2pInfoPtr;
			if (Smp2pInfo->Ctx != NULL)
			{
				/* register/override wdog intr with existing smp2p evt so they can be 
				watched by same thread */
				Event*	Evt = NULL;
				Status = Smp2pProtocol->Smp2pGetEvt(Smp2pInfo->Ctx, &Evt);
				if (EFI_ERROR(Status) || Evt == NULL)
					ASSERT(0);
				
				Status = RegIntrHdlWithEvt(SubsysCtx, Evt);
				if (EFI_ERROR(Status))
					DEBUG((EFI_D_ERROR, "Failed to register wdog interrupt %d\n", \
							(SubsysCfg->WdogIntr).Vector));
			}
			
			SSR_SET_STATUS_BIT(RuntimeInfo->StatusTrace, WDOG_REG_DONE_BIT);
		}
	}
#ifdef SSR_CORE_DBG_LOG		
	if (RuntimeInfo->SSRThread!=NULL)
		DEBUG((EFI_D_ERROR, "debug: ssr monitor thread created previously\n"));
#endif
	if ((RuntimeInfo->SSRThread==NULL) && !SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, IN_RESTART_BIT))
	{
		/* create monitor thread at the first time call*/
		AsciiSPrint(ThreadName, SSR_THREAD_NAME_MAX_LEN, "ssr_%a", SubsysCfg->Name);
		MonThread = ThreadCreate(ThreadName, SSRMonitorEntry, (VOID*)SubsysCtx, \
							HIGHEST_PRIORITY - 4, SSR_THREAD_STACK_SIZE);
		if (MonThread==NULL)
		{
			DEBUG((EFI_D_ERROR, "Failed to create ssr monitor thread\n"));
			return EFI_UNSUPPORTED;
		}
		RuntimeInfo->SSRThread = MonThread;
		
#if 0		
		ThreadSetPinnedCpu (MonThread, 0);
		ThreadDetach (MonThread);
#endif
		ThreadResume(MonThread);
	}
	
	return EFI_SUCCESS;
}


EFI_STATUS ModifyRestartLvl(UINT32 SubsysId, RESTART_LEVEL Lvl)
{
	SSR_SUBSYS_CTX_TYPE* SubsysCtx=NULL;
	EFI_STATUS			 Status;
	
	Status = InitSubsysCtx(SubsysId, &SubsysCtx);
	if (EFI_ERROR(Status) || SubsysCtx==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to init ssr ctx with id=%d\n", SubsysId));
		return EFI_UNSUPPORTED;
	}

	SubsysCtx->RestartLvl = Lvl;
	DEBUG((EFI_D_ERROR, "Set restart level to %d for %a\n", \
						Lvl, SubsysCtx->SubsysCfg->Name));
	return EFI_SUCCESS;
}

STATIC
BOOLEAN IsDrvRegistered(UINT32 SubsysId, CHAR8* DrvName)
{
	SSR_SUBSYS_CTX_TYPE* SubsysCtx;
	LIST_ENTRY* CbList;
	LIST_ENTRY*	CbNode;
	SSR_DRV_CB_ENTRY* CbEntry;
	BOOLEAN Found = FALSE;
	
	if (DrvName == NULL)
		return FALSE;
	
	if ((SubsysCtx = LookForSubsysCtxById(SubsysId)) == NULL)
		return FALSE;
	
	CbList = &SubsysCtx->CbList;

	for (CbNode = GetFirstNode(CbList); \
				!IsNull(CbList, CbNode); \
				CbNode = GetNextNode(CbList, CbNode))
	{
		CbEntry = BASE_CR(CbNode, SSR_DRV_CB_ENTRY, List);
		if (0 == AsciiStrnCmp(CbEntry->DrvName, DrvName, 16))
		{
			Found = TRUE;
			break;
		}
	}
	
	return Found;
}

VOID AddCallbackByPrio(LIST_ENTRY* Head, LIST_ENTRY* Entry)

{
	LIST_ENTRY* 		Node;
	SSR_DRV_CB_ENTRY*	CbEntry;
	SSR_DRV_CB_ENTRY* 	NewCbEntry = BASE_CR(Entry, SSR_DRV_CB_ENTRY, List);
	
	
	for (Node = GetFirstNode(Head); !IsNull(Head, Node); Node = GetNextNode(Head, Node))
	{
		CbEntry = BASE_CR(Node, SSR_DRV_CB_ENTRY, List);
		
		if (NewCbEntry->Prio <= CbEntry->Prio )
		{
			/* insert new entry prior to CbEntry */
			LIST_ENTRY* PrevNode = GetPreviousNode(Head, &CbEntry->List);
			LIST_ENTRY* NextNode = &CbEntry->List;
			NewCbEntry->List.ForwardLink = NextNode;
			NewCbEntry->List.BackLink = PrevNode;
			NextNode->BackLink = &NewCbEntry->List;
			PrevNode->ForwardLink = &NewCbEntry->List;
			break;
		}
	}
	
	/* if the new entry is not inserted in list, insert to tail */
	if (!IsNodeInList(Head, &NewCbEntry->List))
		InsertTailList(Head, &NewCbEntry->List);
}

EFI_STATUS RegisterCbForSubsys(
	CHAR8* DrvName, 
	UINT32 SubsysId,
	SSR_DRIVER_CB_TYPE* Cb,
	UINT32 Prio)
{
	SSR_DRV_CB_ENTRY*	CbEntry;
	EFI_STATUS			Status;
	SSR_SUBSYS_CTX_TYPE* SubsysCtx=NULL;
	
	if (DrvName == NULL || Cb == NULL || Cb->Cb==NULL || \
	    SubsysId == 0 || SubsysId >= TZ_PIL_AUTH_UNSUPPORTED_PROC)
		return EFI_INVALID_PARAMETER;
	
	if (IsDrvRegistered(SubsysId, DrvName))
		return EFI_ALREADY_STARTED;
	
	if (PilProtocol==NULL)
	{
		Status = gBS->LocateProtocol (
				&gEfiPilProtocolGuid,
				NULL,
				(VOID **) &PilProtocol
				);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to locate PIL protocol\n"));
			return Status;
		}
	}
	
	if (Smp2pProtocol==NULL)
	{
		Status = gBS->LocateProtocol (
				&gEfiSMP2PProtocolGuid,
				NULL,
				(VOID **) &Smp2pProtocol
				);
		if (EFI_ERROR(Status)) {
			DEBUG((EFI_D_ERROR, "Failed to locate smp2p protocol\n"));
			return Status;
		}
	}
	
	Status = InitSubsysCtx(SubsysId, &SubsysCtx);
	if (EFI_ERROR(Status) || SubsysCtx==NULL)
		return EFI_UNSUPPORTED;
	
	CbEntry = AllocateZeroPool(sizeof(SSR_DRV_CB_ENTRY));
	if (CbEntry==NULL)
		return EFI_OUT_OF_RESOURCES;
		
	AsciiStrCpyS(CbEntry->DrvName, 16, DrvName);
	CbEntry->Cb = Cb->Cb;
	CbEntry->Arg = Cb->Arg;
	CbEntry->Prio = Prio;
	
	/* insert to linklist by ascending prio */
	AddCallbackByPrio(&SubsysCtx->CbList, &CbEntry->List);
	
	return EFI_SUCCESS;
}

EFI_STATUS UnRegisterCbForSubsys(CHAR8* DrvName, UINT32 SubsysId)
{
	SSR_SUBSYS_CTX_TYPE* SubsysCtx;
	LIST_ENTRY* CbList;
	LIST_ENTRY*	CbNode;
	SSR_DRV_CB_ENTRY* CbEntry;
	
	if (DrvName == NULL || (SubsysCtx = LookForSubsysCtxById(SubsysId)) == NULL)
		return EFI_INVALID_PARAMETER;
	
	CbList = &SubsysCtx->CbList;
	
	if (IsDrvRegistered(SubsysId, DrvName))
	{
		for (CbNode = GetFirstNode(CbList); !IsNull(CbList, CbNode); CbNode = GetNextNode(CbList, CbNode))
		{
			CbEntry = BASE_CR(CbNode, SSR_DRV_CB_ENTRY, List);
			if (0 == AsciiStrnCmp(CbEntry->DrvName, DrvName, 16))
				RemoveEntryList(&CbEntry->List);
		}
	}
	else
	{
		DEBUG((EFI_D_ERROR, "%a is not registered Subsys ID: %d\n",DrvName, SubsysId));
		return EFI_NOT_FOUND;
	}
	
	/*Check after removing the CbEntry*/
	if (!IsDrvRegistered(SubsysId, DrvName)) 
	{
		return EFI_SUCCESS;
	}
	else
	{
		DEBUG((EFI_D_ERROR, "Failed to Unregistered %a Subsys ID: %d\n",DrvName, SubsysId));
		return EFI_UNSUPPORTED;
	}
}

EFI_STATUS RemoveAllCbForSubsys(UINT32 SubsysId)
{
	SSR_SUBSYS_CTX_TYPE* SubsysCtx;
	LIST_ENTRY* CbList;
	LIST_ENTRY*	CbNode;
	SSR_DRV_CB_ENTRY* CbEntry;
	
	if ((SubsysCtx = LookForSubsysCtxById(SubsysId)) == NULL)
		return EFI_INVALID_PARAMETER;
	CbList = &SubsysCtx->CbList;
	
	for (CbNode = GetFirstNode(CbList); !IsNull(CbList, CbNode); CbNode = GetNextNode(CbList, CbNode))
	{
		CbEntry = BASE_CR(CbNode, SSR_DRV_CB_ENTRY, List);
		RemoveEntryList(&CbEntry->List);
	}
		
	return EFI_SUCCESS;
}


EFI_STATUS CheckSubsysStatusByPil(UINT32 SubsysId, SSR_SUBSYS_STATUS* SubsysStatus)
{
	EFI_STATUS Status;
	PIL_SUBSYS_CFG_TYPE PilCfgPtr;
	SSR_SUBSYS_CTX_TYPE* CtxPtr=NULL;
	SSR_RUNTIME_INFO* RuntimeInfo=NULL;
	
	Status = InitSubsysCtx(SubsysId, &CtxPtr);
	if (EFI_ERROR(Status)||CtxPtr==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to init subsys ctx sub_id %d\n", SubsysId));
		return Status;
	}
	
	if (CtxPtr->SubsysStatus != SSR_SUBSYS_STATUS_UNKOWN)
	{
		/* the subsys is registered previously and in track */ 
		*SubsysStatus = CtxPtr->SubsysStatus;
		return EFI_SUCCESS;
	}
	
	if (PilProtocol==NULL)
	{
		Status = gBS->LocateProtocol (&gEfiPilProtocolGuid, NULL, (VOID **) &PilProtocol);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to locate PIL protocol\n"));
			return Status;
		}
	}
	
	Status = PilProtocol->GetLoadedImageCfgCpyById(SubsysId, &PilCfgPtr);
	if (Status==EFI_SUCCESS)
	{
		/* confirmed the subsys is loaded by PIL and in running state */
		RuntimeInfo = CtxPtr->RuntimeInfo;
		ASSERT(RuntimeInfo!=NULL);
		
		// todo, we are assuming the subsys is in up once it's loaded by pil, but it could be shutdown already
		// need add new API in PIL to check the status ?
		
		/* update info from PIL */
		CtxPtr->SubsysStatus = SSR_SUBSYS_STATUS_UP;
		*SubsysStatus = SSR_SUBSYS_STATUS_UP;
		SSR_SET_CURRENT_SUBSYS_ID(CtxPtr, PilCfgPtr.SubsysID);
		CopyMem(RuntimeInfo->ImageName, &PilCfgPtr.FwName, sizeof(CHAR16)*NAME_MAX_LENGTH);
		return EFI_SUCCESS;
	}
	
	/* status is unkown from PIL, could be loaded by other drivers */
	return EFI_UNSUPPORTED;
}


EFI_STATUS ForceShutdownSubsys(SSR_SUBSYS_CTX_TYPE* SubsysCtx)
{
	EFI_STATUS Status;
	SSR_SUBSYS_CFG_TYPE* SubsysCfg=NULL;
	UINT32 SubsysId;
	
	SubsysCfg = SubsysCtx->SubsysCfg;
	
	if (PilProtocol==NULL)
	{
		Status = gBS->LocateProtocol (&gEfiPilProtocolGuid, NULL, (VOID **) &PilProtocol);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to locate PIL protocol\n"));
			return Status;
		}
	}
	
	SubsysId = FindCurrentSubsysId(SubsysCtx);
	if (SubsysId==0)
	{
		DEBUG((EFI_D_ERROR, "error: Failed to find current subsysId\n"));
		return EFI_UNSUPPORTED;
	}
	
	Status = PilProtocol->ProcessPilShutdown(SubsysId);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "Failed to shutdown %a\n", SubsysCfg->Name));
		return Status;
	}
	
	/* clean up status */
	SubsysCtx->SubsysStatus = SSR_SUBSYS_STATUS_DOWN;
	
	return EFI_SUCCESS;
}


EFI_STATUS QMIShutdownSubsys(SSR_SUBSYS_CTX_TYPE* SubsysCtx, UINT32 Timeout)
{
	EFI_STATUS Status;
	SSR_SUBSYS_CFG_TYPE* SubsysCfg=NULL;
	SSR_RUNTIME_INFO* RuntimeInfo=NULL;
	
	
	/* register the subsystem if not done previously */
	RuntimeInfo = SubsysCtx->RuntimeInfo;
	SubsysCfg = SubsysCtx->SubsysCfg;
	ASSERT(RuntimeInfo!=NULL&&SubsysCfg!=NULL);

	Status = ssr_notify_shutdown(SubsysCtx, Timeout);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to send QMI shutdown %a\n",SubsysCfg->Name));
		return Status;
	}
	
	return EFI_SUCCESS;
}


EFI_STATUS CleanXport(SSR_SUBSYS_CTX_TYPE* SubsysCtx)
{
	STATIC EFI_GLINK_PROTOCOL*		GlinkProt; 
	EFI_STATUS Status = EFI_SUCCESS;
	
	if (GlinkProt == NULL) {
		Status = gBS->LocateProtocol(&gEfiGLINKProtocolGuid, 
									NULL,(VOID**)&GlinkProt);
									
		if(EFI_ERROR(Status) || GlinkProt == NULL) {
			DEBUG((EFI_D_ERROR, "Failed to locate glink protocol\n"));
			return Status;
		}
	}
	
	Status = GlinkProt->GlinkSsr(SubsysCtx->SubsysCfg->Name);
	if (EFI_ERROR(Status))
		DEBUG((EFI_D_ERROR, "Failed to clean xport %a\n", SubsysCtx->SubsysCfg->Name));
	return Status;
}


EFI_STATUS ShutdownSubsys(UINT32 SubsysId, BOOLEAN ss_crash)
{
	EFI_STATUS Status;
	KStatus KernelStatus;
	SSR_RUNTIME_INFO* RuntimeInfo=NULL;
	SSR_SUBSYS_CTX_TYPE* SubsysCtx=NULL;
	SSR_SMP2P_INFO* Smp2pInfo;
	Event*	Evt=NULL;
	BOOLEAN InRestart;
	
	Status = InitSubsysCtx(SubsysId, &SubsysCtx);
	if (EFI_ERROR(Status) || SubsysCtx==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to find ssr ctx of subsysId=%d\n",SubsysId));
		return EFI_NOT_FOUND;
	}
	
	if (SubsysId != FindCurrentSubsysId(SubsysCtx))
		SSR_SET_CURRENT_SUBSYS_ID(SubsysCtx,SubsysId);
	
	if ((RuntimeInfo = SubsysCtx->RuntimeInfo)==NULL)
		ASSERT(0);
	
	/* if the subsys does not have smp2p and QMI registered yet, do that before shutdown */
	if (!SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace,SMP2P_REG_DONE_BIT) || \
		!SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace,WDOG_REG_DONE_BIT) || \
		!SSRNotifierInitDone)
	{
#ifdef SSR_CORE_DBG_LOG	
		DEBUG((EFI_D_ERROR, "debug: try to register smp2p and qmi for %a\n",SubsysCtx->SubsysCfg->Name));
#endif
		Status = RegisterSubsys(SubsysId);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to register subsys %a\n",SubsysCtx->SubsysCfg->Name));
			return Status;
		}
		ThreadSleep(5000); // give 5000ms for smp2p and qmi
	}
#ifdef SSR_CORE_DBG_LOG	
	else
		DEBUG((EFI_D_ERROR, "debug: found smp2p registered for %a\n",SubsysCtx->SubsysCfg->Name));
#endif	
	RuntimeInfo->CurrPhase = SSR_PHASE_SHUTDOWN;
	
	Status = InvokeDrvCallbacks(SubsysCtx, SSR_PRE_SHUTDOWN);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to execute SSR_PRE_SHUTDOWN callback\n"));
		return Status;
	}
	
	if (SSRNotifierInitDone)
	{
		/* qmi notify pre_shutdown */
		Status = ssr_broadcast_ssctl_evt_sync(SubsysCtx, SSCTL_SSR_EVENT_BEFORE_SHUTDOWN_V02, QMI_NOTIFY_SYNC_TIMEOUT);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to syncup EVENT_BEFORE_SHUTDOWN %r\n", Status));
			//return Status;
		}
	}
	
	if (!ss_crash)
	{
		// todo, comment out because adsp_lite has repeat timer for comm
		/* try QMI shutdown */
		Status = QMIShutdownSubsys(SubsysCtx, 5000);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to QMI shutdown subsysId=%d\n",SubsysId));
			//return Status;
		}
	}

	/* terminate ssr thread */
	if (RuntimeInfo && RuntimeInfo->SSRThread!=NULL)
	{
		ASSERT(Smp2pProtocol!=NULL);
		Smp2pInfo = SubsysCtx->Smp2pInfoPtr;
		Status = Smp2pProtocol->Smp2pGetEvt(Smp2pInfo->Ctx, &Evt);
		if (EFI_ERROR(Status) || Evt == NULL)
			ASSERT(0);
		
		if (RuntimeInfo->SSRThread != GetCurrentThread())
		{
			/* only terminate sst thread in shutdown usecase. for restart usecase, 
			it's currently in ssr thread so no need to exit */
			EventSignal(Evt, FALSE);
			KernelStatus = ThreadJoin(RuntimeInfo->SSRThread, NULL, 3000);
			if (KernelStatus!=NO_ERROR)
			{
				DEBUG((EFI_D_ERROR, "Failed to join ssr thread %a, 0x%x\n",\
					SubsysCtx->SubsysCfg->Name, KernelStatus));
				//return Status;
			}
#ifdef SSR_CORE_DBG_LOG	
			DEBUG((EFI_D_ERROR, "debug: joined ssr thread %d\n", KernelStatus));
#endif			
		}
	}
	
	Status = ResetSmp2pInfo(SubsysCtx);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to cleanup smp2p subsysId=%d\n",SubsysId));
		return Status;
	}
	
	/* clean up xport before shutdown */
	CleanXport(SubsysCtx);
	
	/* try direct shutdown */
	Status = ForceShutdownSubsys(SubsysCtx);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to direct shutdown subsysId=%d\n",SubsysId));
		return Status;
	}
	
	Status = InvokeDrvCallbacks(SubsysCtx, SSR_POST_SHUTDOWN);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to execute SSR_POST_SHUTDOWN callback\n"));
		return Status;
	}
	
	if (SSRNotifierInitDone)
	{
		/* qmi notify after_shutdown */
		Status = ssr_broadcast_ssctl_evt_sync(SubsysCtx, SSCTL_SSR_EVENT_AFTER_SHUTDOWN_V02, QMI_NOTIFY_SYNC_TIMEOUT);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to syncup EVENT_AFTER_SHUTDOWN %r\n", Status));
			//return Status;
		}
	}
	
	RuntimeInfo->CurrPhase = SSR_PHASE_UNKOWN;
	InRestart = SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, IN_RESTART_BIT);
	ResetRuntimeInfo(SubsysCtx);
	if (!InRestart)
		RemoveAllCbForSubsys(SubsysId);

	return EFI_SUCCESS;
}

EFI_STATUS BringupSubsys(CHAR8* PilSubsysName, PIL_SUBSYS_CFG_TYPE* PilCfgIn)
{
	EFI_STATUS Status;
	SSR_SUBSYS_CTX_TYPE* SubsysCtx=NULL;
	PIL_SUBSYS_CFG_TYPE PilCfg;
	SSR_RUNTIME_INFO* RuntimeInfo;
	UINT16	SubsysNameUnicode[NAME_MAX_LENGTH];
	BOOLEAN UsePilSubsysName=FALSE;
	
	if (PilProtocol==NULL)
	{
		Status = gBS->LocateProtocol (&gEfiPilProtocolGuid, NULL, (VOID **) &PilProtocol);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to locate PIL protocol\n"));
			return Status;
		}
	}
	
	if (PilSubsysName!=NULL)
	{
		AsciiStrToUnicodeStrS(PilSubsysName, SubsysNameUnicode, NAME_MAX_LENGTH);
		Status = PilProtocol->PilInitCfgByUnicodeName(SubsysNameUnicode, &PilCfg);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to get PIL cfg of %a\n",PilSubsysName));
			return Status;
		}
		UsePilSubsysName = TRUE;
	}
	else if (PilCfgIn!=NULL)
		CopyMem(&PilCfg, PilCfgIn, sizeof(PIL_SUBSYS_CFG_TYPE));
	else
		return EFI_INVALID_PARAMETER;
	
	Status = InitSubsysCtx(PilCfg.SubsysID, &SubsysCtx);
	if (EFI_ERROR(Status) || SubsysCtx==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to find ssr ctx of %a\n",PilSubsysName));
		return EFI_NOT_FOUND;
	}
	
	Status = RegisterSubsys(PilCfg.SubsysID);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to register %a\n",PilSubsysName));
		return Status;
	}
	
	// todo, change to SSR_PRE_BRINGUP
	Status = InvokeDrvCallbacks(SubsysCtx, SSR_PRE_RESTART);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to execute SSR_PRE_BRINGUP callback\n"));
		return Status;
	}
	
	if (SSRNotifierInitDone)
	{
		/* qmi notify before_poweron */
		Status = ssr_broadcast_ssctl_evt_sync(SubsysCtx, SSCTL_SSR_EVENT_BEFORE_POWERUP_V02, QMI_NOTIFY_SYNC_TIMEOUT);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to syncup EVENT_BEFORE_POWERUP %r\n", Status));
			//return Status;
		}
	}
	
	if (UsePilSubsysName)
	{
		Status = PilProtocol->ProcessPilImage(SubsysNameUnicode);
		if (EFI_ERROR(Status)) {
			DEBUG((EFI_D_ERROR, "Failed to bringup %a\n", PilSubsysName));
			return Status;
		}
	}
	else
	{
		Status = PilProtocol->ProcessPilImageExt(&PilCfg);
		if (EFI_ERROR(Status)) {
			DEBUG((EFI_D_ERROR, "Failed to bringup subsys_id=%d\n", PilCfg.SubsysID));
			return Status;
		}
	}
	
	if (SSRNotifierInitDone)
	{
		/* qmi notify after_poweron */
		Status = ssr_broadcast_ssctl_evt_sync(SubsysCtx, SSCTL_SSR_EVENT_AFTER_POWERUP_V02, QMI_NOTIFY_SYNC_TIMEOUT);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to syncup EVENT_AFTER_POWERUP %r\n", Status));
			//return Status;
		}
	}
	
	// todo, change to SSR_POST_BRINGUP
	Status = InvokeDrvCallbacks(SubsysCtx, SSR_POST_RESTART);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to execute SSR_POST_BRINGUP callback\n"));
		return Status;
	}
	
	if ((RuntimeInfo=SubsysCtx->RuntimeInfo)==NULL)
		ASSERT(0);
	if (UsePilSubsysName)
		AsciiStrCpyS(RuntimeInfo->ImageName, NAME_MAX_LENGTH, PilSubsysName);
	SSR_SET_CURRENT_SUBSYS_ID(SubsysCtx,PilCfg.SubsysID);
	SubsysCtx->SubsysStatus = SSR_SUBSYS_STATUS_UP;
	
	return EFI_SUCCESS;
}

/* generally the subsys_id is not unique. so this function is only used for subsystem restart scenario, 
 assume it's unique in subsystem restart scenario since the id is just loaded and saved by PIL */
EFI_STATUS BringupSubsysById(UINT32 SubsysId)
{
	EFI_STATUS Status;
	PIL_SUBSYS_CFG_TYPE		PilSubsysCfg;
	SSR_SUBSYS_CTX_TYPE* SubsysCtx=NULL;
	
	Status = RegisterSubsys(SubsysId);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to register subsys id=%d\n",SubsysId));
		return Status;
	}
	
	Status = InitSubsysCtx(SubsysId, &SubsysCtx);
	if (EFI_ERROR(Status) || SubsysCtx==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to find ssr ctx id=%d\n",SubsysId));
		return EFI_NOT_FOUND;
	}
	
	// todo, change to SSR_PRE_BRINGUP
	Status = InvokeDrvCallbacks(SubsysCtx, SSR_PRE_RESTART);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to execute SSR_PRE_BRINGUP callback\n"));
		return Status;
	}
	
	if (SSRNotifierInitDone)
	{
		/* qmi notify before_poweron */
		Status = ssr_broadcast_ssctl_evt_sync(SubsysCtx, SSCTL_SSR_EVENT_BEFORE_POWERUP_V02, QMI_NOTIFY_SYNC_TIMEOUT);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to syncup EVENT_BEFORE_POWERUP %r\n", Status));
			//return Status;
		}
	}
	
	ASSERT(PilProtocol!=NULL);
	Status = PilProtocol->GetLoadedImageCfgCpyById(SubsysId, &PilSubsysCfg);
	if (EFI_ERROR(Status))
		DEBUG((EFI_D_ERROR, "Failed to get pil cfg subsys_id=%d\n", SubsysId));
	else 
	{
		Status = PilProtocol->ProcessPilImageExt(&PilSubsysCfg);
		if (EFI_ERROR(Status))
			DEBUG((EFI_D_ERROR, "Failed to PIL subsys_id=%d\n", SubsysId));
	}
	
	if (SSRNotifierInitDone)
	{
		/* qmi notify after_poweron */
		Status = ssr_broadcast_ssctl_evt_sync(SubsysCtx, SSCTL_SSR_EVENT_AFTER_POWERUP_V02, QMI_NOTIFY_SYNC_TIMEOUT);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to syncup EVENT_AFTER_POWERUP %r\n", Status));
			//return Status;
		}
	}
	
	// todo, change to SSR_POST_BRINGUP
	Status = InvokeDrvCallbacks(SubsysCtx, SSR_POST_RESTART);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to execute SSR_POST_BRINGUP callback\n"));
		return Status;
	}
	
	SSR_SET_CURRENT_SUBSYS_ID(SubsysCtx,SubsysId);
	SubsysCtx->SubsysStatus = SSR_SUBSYS_STATUS_UP;
	
	return EFI_SUCCESS;
}

EFI_STATUS CheckSubsysStatus(UINT32 SubsysId, SSR_SUBSYS_STATUS* St)
{
	EFI_STATUS Status, RetStatus=EFI_UNSUPPORTED;
	SSR_SUBSYS_CTX_TYPE* SubsysCtx=NULL;
	SSR_RUNTIME_INFO* RuntimeInfo;
	UINT32	SubsysId1;
	SSR_SUBSYS_STATUS St1, SubsysStatus;
	
	/* first check internal status */
	Status = InitSubsysCtx(SubsysId, &SubsysCtx);
	if (EFI_ERROR(Status) || SubsysCtx==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to init subsys ctx, subsus_id=%d\n", SubsysId));
		return Status;
	}
	
	if ((RuntimeInfo=SubsysCtx->RuntimeInfo)==NULL)
		ASSERT(0);
	
	switch (SubsysCtx->SubsysStatus)
	{
		case SSR_SUBSYS_STATUS_UP:
			if ((SubsysId1 = FindCurrentSubsysId(SubsysCtx))!=0) 
			{
				/* clearly know which image is up */
				if (SubsysId1 == SubsysId)
					*St = SSR_SUBSYS_STATUS_UP;
				else
					*St = SSR_SUBSYS_STATUS_DOWN;
				RetStatus = EFI_SUCCESS;
				goto CheckSubsysStatusRet;
			}
			else {
				DEBUG((EFI_D_ERROR, "err: Failed to find out which image is loaded, subsus_id=%d\n", SubsysId));
				RetStatus = EFI_UNSUPPORTED;
				goto CheckSubsysStatusRet;
			}
			break;
			
		case SSR_SUBSYS_STATUS_DOWN:
			*St = SSR_SUBSYS_STATUS_DOWN;
			RetStatus = EFI_SUCCESS;
			goto CheckSubsysStatusRet;

		case SSR_SUBSYS_STATUS_UNKOWN:
			/* need further investigation */
			break;
		default:
			ASSERT(0);
	}
	
	/* saved status is unkown, check smp2p to find more */
	Status =  CheckSubsysStatusBySmp2p(SubsysId, &SubsysStatus, NULL);
	if (Status == EFI_SUCCESS)
	{
		if (SubsysStatus == SSR_SUBSYS_STATUS_DOWN)
		{
			*St = SSR_SUBSYS_STATUS_DOWN;
			RetStatus = EFI_SUCCESS;
		}
		
		else if (SubsysStatus == SSR_SUBSYS_STATUS_UP) 
		{
			if (FindCurrentSubsysId(SubsysCtx) == SubsysId)
			{
				*St = SSR_SUBSYS_STATUS_DOWN;
				RetStatus = EFI_SUCCESS;
			}
			else 
			{
				/* subsys is up, but not sure which image is loaded */
				Status = CheckSubsysStatusByPil(SubsysId, &St1);
				if (Status == EFI_SUCCESS)
				{
					*St = St1;
					RetStatus = EFI_SUCCESS;
				}
			}
		}
	}
CheckSubsysStatusRet:
	return RetStatus;
}


