/*===============================================================================
  Copyright (c) 2021-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc
  
  FILE: 		SSRNotifier.c
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  10/14/21	 yanw  	    initial version

================================================================================*/

#include <Protocol/EFIQSocketQMI.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "SSRNotifier.h"
#include "subsystem_control_v02.h"

//#define ENABLE_NOTIF_DEBUG_LOGGING

#define QMI_SHUTDOWN_ACK_TIMEOUT	3000

#define RESET_EVT_RESP_MSG(p) \
{ \
	(p)->result = QMI_RESULT_TYPE_MIN_ENUM_VAL_V01; \
	(p)->error = QMI_ERROR_TYPE_MIN_ENUM_VAL_V01; \
}


#define RESP_RECVD(r)	\
	((r)->result!=QMI_RESULT_TYPE_MIN_ENUM_VAL_V01)
	
#define RESP_RECVD_SUCCESS(r) \
	((r)->result==QMI_RESULT_SUCCESS_V01)
	
#define SS_RESP_RECVD(p)	\
	RESP_RECVD(&((qmi_ssctl_subsys_event_resp_msg_v02*)(p))->resp)
	
#define SS_RESP_RECVD_SUCCESS(p) \
	RESP_RECVD_SUCCESS(&((qmi_ssctl_subsys_event_resp_msg_v02*)(p))->resp)
	

typedef struct
{
	Event*					Evt;    // resp event shared by all online subsystems
	UINT32					NumOfDst; // number of subsystems to which send the req
	qmi_ssctl_subsys_event_resp_msg_v02** 	Resp;		// ptr to resp data of specific subsystem
} SSCTL_REQ_CB_DATA_TYPE;

Mutex*	Mtx_SSCTLCbData = NULL;
SSCTL_REQ_CB_DATA_TYPE	SsctlCbData;

extern SSR_SUBSYS_CTX_TYPE**	SSRSubsysCtx;
extern UINT32 MaxSubsysConfigured;
extern UINT32 SubsysRegisteredNum;

BOOLEAN SSRNotifierInitDone = FALSE;

STATIC EFI_QSOCKETQMI_PROTOCOL*  QmiProt;
STATIC qmi_idl_service_object_type  ssctl_svc_obj;
STATIC Event* IndEvt;

STATIC qmi_client_os_params		NotifierOsParam;
STATIC qmi_client_type			NotifierHdl = NULL;

STATIC
VOID IndCb
(
 qmi_client_type                user_handle,
 unsigned int                   msg_id,
 void                           *ind_buf,
 unsigned int                   ind_buf_len,
 void                           *ind_cb_data
)
{
#ifdef ENABLE_NOTIF_DEBUG_LOGGING
	DEBUG((EFI_D_ERROR,"debug: got ind msg_id=0x%x\n", msg_id));
#endif
	switch (msg_id)
	{
		case QMI_SSCTL_SHUTDOWN_READY_IND_V02:
		case QMI_SSCTL_SUBSYS_EVENT_COMP_IND_V02:
			EventSignal(IndEvt, TRUE);
			break;
		default:;
	}
}

VOID ResetQmiInfo(SSR_SUBSYS_CTX_TYPE* Ctx)
{
	SSR_RUNTIME_INFO*	RuntimeInfo = Ctx->RuntimeInfo;
	
	ASSERT(RuntimeInfo!=NULL);
	RuntimeInfo->QmiHdl = NULL;
	if (RuntimeInfo->LastRespMsg) 
	{
		FreePool(RuntimeInfo->LastRespMsg);
		RuntimeInfo->LastRespMsg = NULL;
	}
}

// todo need protection
STATIC
VOID NotifierCb(
	qmi_client_type                user_handle,
	qmi_idl_service_object_type    service_obj,
	qmi_client_notify_event_type   service_event,
	void                           *notify_cb_data
 )
 {
	 EFI_STATUS Status;
	 qmi_service_info* InfoList;
	 UINT32 EntryNum = MaxSubsysConfigured,NewServiceNum =0, idx;
	 STATIC UINT32 PreServiceNum=0;
	 qmi_client_error_type QmiErr=0;
	 qmi_service_instance	InstanceId;
	 VOID* 		LastRespMsg;
	 SSR_SUBSYS_CTX_TYPE* Ctx = NULL;
	 SSR_SUBSYS_CFG_TYPE* Cfg=NULL;
	 SSR_RUNTIME_INFO*	RuntimeInfo;
#ifdef ENABLE_NOTIF_DEBUG_LOGGING	 
	 DEBUG((EFI_D_ERROR,"debug: NotifierCb invoked. evt=%d\n", service_event));
#endif	 
	 ASSERT(MaxSubsysConfigured != 0);
	 
	 if (service_event == QMI_CLIENT_SERVICE_COUNT_INC)
	 {
		 InfoList = AllocateZeroPool(sizeof(qmi_service_info) * MaxSubsysConfigured);
		 if (InfoList == NULL)
		 {
			 DEBUG((EFI_D_ERROR,"error: failed to alloc memory in NotifierCb\n"));
			 return;
		 }
		 
		 Status = QmiProt->QmiClientGetServiceList(ssctl_svc_obj, InfoList, &EntryNum, &NewServiceNum, QmiErr);
		 if (EFI_ERROR(Status))
		 {
			DEBUG((EFI_D_ERROR,"err: failed to get service list. \n"));
			return;
		 }
		 
#ifdef ENABLE_NOTIF_DEBUG_LOGGING
	 DEBUG((EFI_D_ERROR,"debug: NotifierCb SERVICE_COUNT_INC, EntryNum=%d NewServiceNum=%d PreServiceNum=%d.\n", EntryNum, NewServiceNum,PreServiceNum));
#endif		 

		 if (EntryNum!=NewServiceNum)
		 {
			 DEBUG((EFI_D_ERROR,"error: service list unmatching. EntryNum=%d ServiceNum=%d. %r\n", \
					EntryNum, NewServiceNum,Status));
			 return;	 
		 }
		 
		 if (NewServiceNum<=PreServiceNum)
		 {
			 DEBUG((EFI_D_ERROR,"error: new service num unmatching. NewServiceNum=%d PreServiceNum=%d. %r\n", \
					NewServiceNum, PreServiceNum));
			 return;
		 }
		 
		 /* find out new instance */
		 for (idx=0;idx<EntryNum;idx++)
		 {
			 Status = QmiProt->QmiClientGetInstanceId(&InfoList[idx], &InstanceId, QmiErr);
			 if (EFI_ERROR(Status))
			 {
				 DEBUG((EFI_D_ERROR,"error: failed to get service instance_id %r\n",Status));
				 return;
			 }
			
			 Cfg = LookupSSRCfgBySvcInsId(InstanceId);
			 if (Cfg==NULL)
			 {
				DEBUG((EFI_D_ERROR,"error: failed to find subsystem with instance_id=0x%x\n",InstanceId));
				continue;		
			 }
			 
			 if (Cfg->SubsysCtx==NULL)
			 {
				 /* it does not matter if there is multiple subsysId and the actual loaded image is the other one,
				 just use one of the subsysid to create the ctx as long as they have same QMI instance id */
				 Status = InitSubsysCtx(Cfg->SubsysId[0], &Ctx);
				 ASSERT(Status == EFI_SUCCESS && Ctx!=NULL);
			 }
			 else
				 Ctx = Cfg->SubsysCtx;
			 
			 /* if ctx found, go init the QMI client */
			 if ((RuntimeInfo=Ctx->RuntimeInfo)==NULL)
				 ASSERT(0);
			 if (RuntimeInfo->QmiHdl!=0)
				 continue;
			 
			 Status = QmiProt->QmiClientInit(	&InfoList[idx],
												ssctl_svc_obj,
												IndCb,
												NULL,
												NULL,
												&RuntimeInfo->QmiHdl,
												QmiErr);
			if (EFI_ERROR(Status)) 
			{
				DEBUG((EFI_D_ERROR,"error: Failed to init QMI client to %a. %r\n",Ctx->SubsysCfg->Name, Status));
				return;
			}
#ifdef ENABLE_NOTIF_DEBUG_LOGGING			
			DEBUG((EFI_D_ERROR,"QMI client initialized to %a. hdl=0x%x\n",Ctx->SubsysCfg->Name, RuntimeInfo->QmiHdl));
#endif
			
			ASSERT(RuntimeInfo->LastRespMsg == NULL);
			LastRespMsg = AllocateZeroPool(sizeof(qmi_ssctl_subsys_event_resp_msg_v02));
			if (LastRespMsg==NULL)
			{
				DEBUG((EFI_D_ERROR,"error: failed to locate buffer for evt_resp msg for %a.\n", Ctx->SubsysCfg->Name));
				return;
			}
			else {
				RuntimeInfo->LastRespMsg = LastRespMsg;
			}
		 }
		 
		 PreServiceNum = NewServiceNum;
		 
	 }
	 
	 else if (service_event == QMI_CLIENT_SERVICE_COUNT_DEC)
	 {
		 UINT32 Num=0,Num1=0;
		 SSR_SUBSYS_CTX_TYPE*	SubSysWithQmi=NULL;
		 SSR_SUBSYS_CTX_TYPE** ArrCtx;
		 
		 Status = LookForSubsysWithQmiHdl(&Num, &SubSysWithQmi, 1);
		 if (Status==EFI_NOT_FOUND || Num==0)
		 {
			 DEBUG((EFI_D_ERROR,"error: failed to subsys with QMI initialized\n"));
			 return;
		 }
		 
		 if (Num==1)
		 {	/* there is only one subsys online, directly release it */
			 
			 if (PreServiceNum!=1)
			 {
				DEBUG((EFI_D_ERROR,"error: found conflict num of online subsys PreServiceNum=%d\n", PreServiceNum));
				ASSERT(0);
			 }
			
			 if (SubSysWithQmi==NULL || (RuntimeInfo = SubSysWithQmi->RuntimeInfo)==NULL)
				 ASSERT(0);
			 
			 Status = QmiProt->QmiClientRelease(RuntimeInfo->QmiHdl, QmiErr);
			 if (EFI_ERROR(Status))
			 {
				 DEBUG((EFI_D_ERROR,"error: failed to release QMI for %a\n", SubSysWithQmi->SubsysCfg->Name));
				 return;
			 }
			 ResetQmiInfo(SubSysWithQmi);
			 PreServiceNum=0;
			 DEBUG((EFI_D_ERROR,"QMI client released for %a.\n", SubSysWithQmi->SubsysCfg->Name));
		 }
		 else
		 {	/* found multiple subsys with QMI */
			 ArrCtx = AllocateZeroPool(sizeof(SSR_SUBSYS_CTX_TYPE*) * Num);		 
			 InfoList = AllocateZeroPool(sizeof(qmi_service_info) * Num);
			 if (InfoList == NULL || ArrCtx==NULL)
			 {
				 DEBUG((EFI_D_ERROR,"error: failed to alloc memory in NotifierCb\n"));
				 return;
			 }
			 
			 ASSERT(Num<=SubsysRegisteredNum);
			 Status = LookForSubsysWithQmiHdl(&Num1, ArrCtx, Num);
			 if (EFI_ERROR(Status) || Num!=Num1)
			 {
				 DEBUG((EFI_D_ERROR,"error: failed to find subsys with QMI %d %d %r\n", Num, Num1, Status));
				 return;
			 }
			 
			 EntryNum = Num;
			 Status = QmiProt->QmiClientGetServiceList(ssctl_svc_obj, InfoList, &EntryNum, &NewServiceNum, QmiErr);
#ifdef ENABLE_NOTIF_DEBUG_LOGGING
			DEBUG((EFI_D_ERROR,"DEBUG: NotifierCb SERVICE_COUNT_DEC, EntryNum=%d NewServiceNum=%d PreServiceNum=%d.\n", EntryNum, NewServiceNum,PreServiceNum));
#endif	
			 if (EFI_ERROR(Status) || NewServiceNum>=PreServiceNum || NewServiceNum>=Num)
			 {
				 DEBUG((EFI_D_ERROR,"error: QmiClientGetServiceList return info unexplained EntryNum=%d NewServiceNum=%d SubsysWithQmi=%d %a\n", \
						EntryNum, NewServiceNum, Num, Status));
				return;
			 }
			 
			 /* find which subsys offline and release it */
			for (idx=0;idx<Num;idx++)
			{
				if ((Ctx=ArrCtx[idx])==NULL || (RuntimeInfo=Ctx->RuntimeInfo)==NULL || RuntimeInfo->QmiHdl==NULL)
					 ASSERT(0);
				 
				Status = QmiProt->QmiClientGetServiceInstance(	ssctl_svc_obj, \
																Ctx->SubsysCfg->QmiSvcIns, \
																&InfoList[idx], \
																QmiErr);
#ifdef ENABLE_NOTIF_DEBUG_LOGGING																	
				DEBUG((EFI_D_ERROR,"debug: QmiClientGetServiceInstance return %r. %a\n", Status, Ctx->SubsysCfg->Name));
#endif				
				if (EFI_ERROR(Status))
				{
					 /* the service instance is gone */
					Status = QmiProt->QmiClientRelease(RuntimeInfo->QmiHdl, QmiErr);
					if (EFI_ERROR(Status))
						DEBUG((EFI_D_ERROR,"Failed to release qmi client for %a.\n", Ctx->SubsysCfg->Name));
					else
					{
						ResetQmiInfo(Ctx);
						DEBUG((EFI_D_ERROR,"QMI client released for %a.\n", Ctx->SubsysCfg->Name));
					}
				}
			}
			
			FreePool(InfoList);
			FreePool(ArrCtx);
			PreServiceNum = NewServiceNum;
		 }
	 }
 }

EFI_STATUS SSRNotifInit(VOID)
{
	EFI_STATUS	Status;
	qmi_client_error_type QmiErr =0;
	
	if (SSRNotifierInitDone)
		return EFI_SUCCESS;
	
	ssctl_svc_obj = ssctl_get_service_object_v02();
	SSCTL_QCCI_OS_SIGNAL_INIT(&NotifierOsParam);
	
	if (QmiProt==NULL)
	{
		Status = gBS->LocateProtocol(&gEfiQSocketQMIProtocolGuid, 
									NULL,(VOID**)&QmiProt);
										
		if(EFI_ERROR(Status) || QmiProt == NULL) {
			DEBUG((EFI_D_ERROR,"warning: failed to locate QMI protocol\n"));
			return EFI_UNSUPPORTED;
		}
	}
	
	do {
		Status = QmiProt->QmiClientNotifierInit(ssctl_svc_obj, &NotifierOsParam, &NotifierHdl, QmiErr);
		if (EFI_ERROR(Status) || NotifierHdl==NULL)
		{
			DEBUG((EFI_D_ERROR,"Failed to init QMI client notifier, %r\n", Status));
			break;
		}
		
		Status = QmiProt->QmiClientRegisterNotifyCb(NotifierHdl, NotifierCb, NULL, QmiErr);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR,"Failed to init register notifier callback, %r\n", Status));
			break;
		}
		
		IndEvt = EventInit(0, SCHED_EVENT_STATE_UNSIGNALED, SCHED_EVENT_FLAG_AUTOUNSIGNAL);
		if (IndEvt == NULL)
		{
			DEBUG((EFI_D_ERROR,"Failed to init ind event.\n"));
			Status = EFI_UNSUPPORTED;
			break;;
		}
	
	} while(0);
		
	if (Status == EFI_SUCCESS) SSRNotifierInitDone = TRUE;
	return Status;
}


/* send event to subsystem and get response */
EFI_STATUS ssr_notify_single_ss
( 
	SSR_SUBSYS_CTX_TYPE* DstCtx, 
	SSR_SUBSYS_CTX_TYPE* SrcCtx,
	ssctl_ssr_event_enum_type_v02 Evt,
	UINT32				Timeout,
	qmi_response_type_v01* Resp
)
{
	qmi_ssctl_subsys_event_req_msg_v02 Req;
	EFI_STATUS  Status;
	SSR_RUNTIME_INFO* DstRuntimeInfo;
	qmi_client_error_type QmiErr =0;
	
	if (DstCtx==NULL || (DstRuntimeInfo=DstCtx->RuntimeInfo)==NULL || DstRuntimeInfo->QmiHdl == NULL || \
		QmiProt==NULL)
				ASSERT(0);
	ASSERT(SrcCtx && SrcCtx->SubsysCfg);
	
	if (DstCtx == SrcCtx)
		return EFI_SUCCESS;
	
	Req.subsys_name_len = AsciiStrnLenS(SrcCtx->SubsysCfg->Name, QMI_SSCTL_SUB_SYS_NAME_LENGTH_V02);
	AsciiStrCpyS(Req.subsys_name, QMI_SSCTL_SUB_SYS_NAME_LENGTH_V02, SrcCtx->SubsysCfg->Name);
	Req.event = Evt;
	Req.evt_driven_valid = 1;
	Req.evt_driven = SSCTL_SSR_EVENT_FORCED_V02;
	
	RESET_EVT_RESP_MSG(&((qmi_ssctl_subsys_event_resp_msg_v02*)(DstRuntimeInfo->LastRespMsg))->resp);
#ifdef ENABLE_NOTIF_DEBUG_LOGGING
	DEBUG((EFI_D_ERROR,"DEBUG: %a before resp result=%d err=%d\n", DstCtx->SubsysCfg->Name,\
				((qmi_ssctl_subsys_event_resp_msg_v02*)(DstRuntimeInfo->LastRespMsg))->resp.result,\
				((qmi_ssctl_subsys_event_resp_msg_v02*)(DstRuntimeInfo->LastRespMsg))->resp.error));
#endif				
	Status = QmiProt->QmiClientSendMsgSync(	DstRuntimeInfo->QmiHdl, 
											QMI_SSCTL_SUBSYS_EVENT_REQ_V02,
											&Req,
											sizeof(qmi_ssctl_subsys_event_req_msg_v02),
											DstRuntimeInfo->LastRespMsg,
											sizeof(qmi_ssctl_subsys_event_resp_msg_v02),
											Timeout,
											QmiErr);
	if (!EFI_ERROR(Status) && Resp)
	{
		CopyMem(Resp, &((qmi_ssctl_subsys_event_resp_msg_v02*)(DstRuntimeInfo->LastRespMsg))->resp, \
				sizeof(qmi_ssctl_subsys_event_resp_msg_v02));
#ifdef ENABLE_NOTIF_DEBUG_LOGGING				
		DEBUG((EFI_D_ERROR,"DEBUG: successfully sent evt msg to %a, evt %d\n", DstCtx->SubsysCfg->Name, Evt));
		DEBUG((EFI_D_ERROR,"DEBUG: %a after resp result=%d err=%d\n", DstCtx->SubsysCfg->Name,\
				((qmi_ssctl_subsys_event_resp_msg_v02*)(DstRuntimeInfo->LastRespMsg))->resp.result,\
				((qmi_ssctl_subsys_event_resp_msg_v02*)(DstRuntimeInfo->LastRespMsg))->resp.error));
#endif
	}
		
	return Status;
}



//STATIC 
EFI_STATUS CheckRespFromEachSS(SSCTL_REQ_CB_DATA_TYPE* Data, UINT32 Timeout, BOOLEAN* AllRecvd, BOOLEAN* AllRecvdSuccess)
{
	BOOLEAN AllRecvd1, AllRecvdSuccess1;
	INT32	KernelRet;
	EFI_STATUS Status = EFI_SUCCESS;
	UINT32		idx;
	SSR_SUBSYS_CTX_TYPE* SvcCtx;
	SSR_RUNTIME_INFO*	RuntimeInfo;
	qmi_ssctl_subsys_event_resp_msg_v02** Resp=Data->Resp;
	
	
	KernelRet = EventWaitTimeout(Data->Evt, Timeout);
	if (KernelRet != NO_ERROR)
	{
		DEBUG((EFI_D_ERROR,"failed to have all subsystems respond. go ahead check resp. %d\n", KernelRet));
	}
	
	AllRecvd1 = TRUE;
	AllRecvdSuccess1 = TRUE;
	for (idx=0;idx<Data->NumOfDst;idx++)
	{
		if (Resp[idx]==NULL || !SS_RESP_RECVD(Resp[idx]))
		{
			AllRecvd1 = FALSE;
			break;
		}
		else
		{
			if (!SS_RESP_RECVD_SUCCESS(Resp[idx]))
				AllRecvdSuccess1 = AllRecvdSuccess1 && FALSE;
		}
	}
	
	if (EFI_ERROR(Status))
	{
		*AllRecvd = AllRecvd1;
		*AllRecvdSuccess = AllRecvdSuccess1;
	}
	
	/* logging */
	for (idx=0;idx<MaxSubsysConfigured;idx++)
	{
		if ( (SvcCtx=SSRSubsysCtx[idx])==NULL || \
					(RuntimeInfo=SvcCtx->RuntimeInfo)==NULL || \
					RuntimeInfo->QmiHdl==NULL || \
					RuntimeInfo->LastRespMsg == NULL ||\
					SvcCtx->SubsysCfg == NULL ||\
					SvcCtx->SubsysCfg->Name == NULL)
			continue;
#ifdef ENABLE_NOTIF_DEBUG_LOGGING					
		DEBUG((EFI_D_ERROR,"DEBUG: %a after resp result=%d err=%d\n", SvcCtx->SubsysCfg->Name,\
				((qmi_ssctl_subsys_event_resp_msg_v02*)(RuntimeInfo->LastRespMsg))->resp.result,\
				((qmi_ssctl_subsys_event_resp_msg_v02*)(RuntimeInfo->LastRespMsg))->resp.error));
#endif
	}
	
	return Status;
}

//STATIC
VOID SsctlReqCb
(
	 qmi_client_type                user_handle,
	 unsigned int                   msg_id,
	 void                           *resp_c_struct,
	 unsigned int                   resp_c_struct_len,
	 void                           *resp_cb_data,
	 qmi_client_error_type          transp_err
)
{
	STATIC UINT32 NumOfResp;
	qmi_ssctl_subsys_event_resp_msg_v02* RespMsg =  resp_c_struct;
	SSCTL_REQ_CB_DATA_TYPE*		Data = (SSCTL_REQ_CB_DATA_TYPE*)resp_cb_data;
	Event* Evt;
	
	ASSERT(msg_id == QMI_SSCTL_SUBSYS_EVENT_RESP_V02);
	if (Data == NULL || (Evt=Data->Evt) == NULL)
		ASSERT(0);
	
	/* need protection since this cb is triggered by diff ipcrtr threads */
	MutexAcquire(Mtx_SSCTLCbData);
	
	Data->Resp[NumOfResp] = RespMsg;
	
	if (++NumOfResp == Data->NumOfDst)
	{
		NumOfResp = 0;
		EventSignal(Data->Evt, FALSE);
	}

	MutexRelease(Mtx_SSCTLCbData);
}

//STATIC
EFI_STATUS ResetSsctlReqCbData(UINT32 Num, SSCTL_REQ_CB_DATA_TYPE* CbData)
{
	Event* Evt;
	UINT32 idx;
	SSR_SUBSYS_CTX_TYPE* Ctx;
	
	ASSERT(CbData!=NULL);
	CbData->NumOfDst = Num;
	
	if (CbData->Evt == NULL)
	{
		Evt = EventInit(0, SCHED_EVENT_STATE_UNSIGNALED, SCHED_EVENT_FLAG_AUTOUNSIGNAL);
		if (Evt==NULL)
			return EFI_UNSUPPORTED;
		CbData->Evt = Evt;
	}
	else
		EventUnsignal(CbData->Evt);
	
	if (Mtx_SSCTLCbData == NULL)
	{
		Mtx_SSCTLCbData = MutexInit(0);
		if (Mtx_SSCTLCbData==NULL)
			return EFI_UNSUPPORTED;
	}

	if (CbData->Resp == NULL)
		CbData->Resp = AllocateZeroPool(sizeof(qmi_response_type_v01) * MaxSubsysConfigured);
	else
	    ZeroMem(CbData->Resp, sizeof(qmi_response_type_v01*) * MaxSubsysConfigured);
	
	for (idx=0;idx<MaxSubsysConfigured;idx++)
	{
		if ( (Ctx=SSRSubsysCtx[idx])==NULL || Ctx->RuntimeInfo==NULL || \
			Ctx->RuntimeInfo->QmiHdl==NULL || Ctx->RuntimeInfo->LastRespMsg==NULL)
			continue;
		
		RESET_EVT_RESP_MSG(&((qmi_ssctl_subsys_event_resp_msg_v02*)(Ctx->RuntimeInfo->LastRespMsg))->resp);
	}		
	return EFI_SUCCESS;
}

EFI_STATUS ssr_broadcast_ssctl_evt_async
(
	SSR_SUBSYS_CTX_TYPE* SrcCtx,
	ssctl_ssr_event_enum_type_v02 Evt,
	UINT32				Timeout
)
{
	qmi_ssctl_subsys_event_req_msg_v02 Req;
	qmi_txn_handle			TxnHdl;
	qmi_client_error_type	QmiErr=0;
	UINT32 					idx;
	SSR_SUBSYS_CTX_TYPE* 	DstCtx;
	SSR_RUNTIME_INFO*		RuntimeInfo;
	UINT32					NumOfOnline=0;
	EFI_STATUS				Status;
	CHAR8*					SrcName;
	BOOLEAN					AllRecvd=FALSE, AllRecvdSuccess=FALSE;
	
	ASSERT(QmiProt!=NULL && SrcCtx!=NULL && SrcCtx->SubsysCfg!=NULL);
	if ((SrcName=SrcCtx->SubsysCfg->Name)==NULL)
		ASSERT(0);
	
	for (idx=0;idx<MaxSubsysConfigured;idx++)
	{
		if ( (DstCtx=SSRSubsysCtx[idx])==NULL || (RuntimeInfo=DstCtx->RuntimeInfo)==NULL || RuntimeInfo->QmiHdl==NULL )
			continue;
		
		if (SrcCtx == DstCtx)
			continue;
		
		NumOfOnline++;
	}
	
	if (NumOfOnline==0)
		return EFI_SUCCESS;
	
	Req.subsys_name_len = AsciiStrnLenS(SrcName, QMI_SSCTL_SUB_SYS_NAME_LENGTH_V02);
	AsciiStrCpyS(Req.subsys_name, QMI_SSCTL_SUB_SYS_NAME_LENGTH_V02, SrcName);
	Req.event = Evt;
	Req.evt_driven_valid = 1;
	Req.evt_driven = SSCTL_SSR_EVENT_FORCED_V02;
	
	Status = ResetSsctlReqCbData(NumOfOnline, &SsctlCbData);
	if (EFI_ERROR(Status))
		goto  ssr_broadcast_ssctl_evt_async_err;
	
	for (idx=0;idx<MaxSubsysConfigured;idx++)
	{
		if ( (DstCtx=SSRSubsysCtx[idx])==NULL || (RuntimeInfo=DstCtx->RuntimeInfo)==NULL || \
			RuntimeInfo->QmiHdl==NULL )
			continue;
		
		if (SrcCtx == DstCtx)
			continue;
		
		ASSERT(RuntimeInfo->LastRespMsg && DstCtx->SubsysCfg);
#ifdef ENABLE_NOTIF_DEBUG_LOGGING		
		DEBUG((EFI_D_ERROR,"DEBUG: %a before resp result=%d err=%d\n", DstCtx->SubsysCfg->Name,\
				((qmi_ssctl_subsys_event_resp_msg_v02*)(RuntimeInfo->LastRespMsg))->resp.result,\
				((qmi_ssctl_subsys_event_resp_msg_v02*)(RuntimeInfo->LastRespMsg))->resp.error));
#endif		
		Status = QmiProt->QmiClientSendMsgAsync(	RuntimeInfo->QmiHdl,
													QMI_SSCTL_SUBSYS_EVENT_REQ_V02,
													&Req,
													sizeof(qmi_ssctl_subsys_event_req_msg_v02),
													RuntimeInfo->LastRespMsg,
													sizeof(qmi_ssctl_subsys_event_resp_msg_v02),
													SsctlReqCb,
													&SsctlCbData,
													&TxnHdl,
													QmiErr
												);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR,"Failed to send evt msg to %a, %r\n", DstCtx->SubsysCfg->Name, Status));
			goto ssr_broadcast_ssctl_evt_async_err;
		}
#ifdef ENABLE_NOTIF_DEBUG_LOGGING
		DEBUG((EFI_D_ERROR,"DEBUG: successfully sent evt msg to %a, evt %d\n", DstCtx->SubsysCfg->Name, Evt));
#endif
	}
	
	Status = CheckRespFromEachSS(&SsctlCbData, Timeout, &AllRecvd, &AllRecvdSuccess);
	if (EFI_ERROR(Status) || !AllRecvd || !AllRecvdSuccess)
	{
		DEBUG((EFI_D_ERROR,"Failed to recv success resp from all subsystems %r\n", Status));
		goto ssr_broadcast_ssctl_evt_async_err;
	}

ssr_broadcast_ssctl_evt_async_err:
	
	Status = (EFI_ERROR(Status))?Status: \
			(AllRecvd && AllRecvdSuccess)?EFI_SUCCESS:EFI_COMPROMISED_DATA;
	return Status;
}


EFI_STATUS ssr_broadcast_ssctl_evt_sync
(
	SSR_SUBSYS_CTX_TYPE* SrcCtx,
	ssctl_ssr_event_enum_type_v02 Evt,
	UINT32				Timeout
)
{
	UINT32 					idx;
	SSR_SUBSYS_CTX_TYPE* 	DstCtx;
	SSR_RUNTIME_INFO*		RuntimeInfo;
	EFI_STATUS				Status = EFI_SUCCESS;
	CHAR8*					SrcName;
	qmi_response_type_v01	SingleSsResp;
	BOOLEAN AllRecvd = TRUE;
	BOOLEAN AllRecvdSuccess = TRUE;
	
	ASSERT(QmiProt!=NULL && SrcCtx!=NULL && SrcCtx->SubsysCfg!=NULL);
	if ((SrcName=SrcCtx->SubsysCfg->Name)==NULL)
		ASSERT(0);
	
	for (idx=0;idx<MaxSubsysConfigured;idx++)
	{
		if ( (DstCtx=SSRSubsysCtx[idx])==NULL || (RuntimeInfo=DstCtx->RuntimeInfo)==NULL || \
			RuntimeInfo->QmiHdl==NULL )
			continue;
		
		if (SrcCtx == DstCtx)
			continue;
		
		RESET_EVT_RESP_MSG(&SingleSsResp);
		Status = ssr_notify_single_ss(DstCtx, SrcCtx, Evt, \
									Timeout, &SingleSsResp);

		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR,"Failed to notify evt %d src %a dst %a\n", Evt, \
							SrcName, DstCtx->SubsysCfg->Name));
			goto ssr_broadcast_ssctl_evt_sync_err;
		}
		
		if (!RESP_RECVD(&SingleSsResp))
		{
			AllRecvd = AllRecvd && FALSE;
		}
		else if (!RESP_RECVD_SUCCESS(&SingleSsResp))
		{
				AllRecvdSuccess = AllRecvdSuccess && FALSE;
		}
	}

ssr_broadcast_ssctl_evt_sync_err:
	
	Status = (EFI_ERROR(Status))?Status: \
			(AllRecvd && AllRecvdSuccess)?EFI_SUCCESS:EFI_COMPROMISED_DATA;
	return Status;
}

EFI_STATUS ssr_notify_subsys_status_sync
(
	SSR_SUBSYS_CTX_TYPE* DstCtx, 
	ssctl_ssr_event_enum_type_v02 Evt, 
	UINT32 Timeout
)
{
	SSR_SUBSYS_CTX_TYPE* SrcCtx;
	SSR_RUNTIME_INFO*	RuntimeInfo;
	UINT32 idx, SrcNum=0;
	EFI_STATUS Status = EFI_UNSUPPORTED;
	qmi_response_type_v01	SingleSsResp;
	BOOLEAN AllRecvd = TRUE;
	BOOLEAN AllRecvdSuccess = TRUE;
	
	ASSERT(DstCtx != NULL);
	
	for (idx=0;idx<MaxSubsysConfigured;idx++)
	{
		if ( (SrcCtx=SSRSubsysCtx[idx])==NULL || (RuntimeInfo=SrcCtx->RuntimeInfo)==NULL || RuntimeInfo->QmiHdl==NULL )
			continue;
		
		if (SrcCtx==DstCtx)
			continue;
		
		SrcNum++;
		RESET_EVT_RESP_MSG(&SingleSsResp);
		Status = ssr_notify_single_ss(DstCtx, SrcCtx, Evt, \
									Timeout, &SingleSsResp);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR,"Failed to notify %a state of %a\n", DstCtx->SubsysCfg->Name,\
					SrcCtx->SubsysCfg->Name));
			goto ssr_notify_subsys_status_sync_err;
		}
		
		if (!RESP_RECVD(&SingleSsResp))
		{
			AllRecvd = AllRecvd && FALSE;
		}
		else if (!RESP_RECVD_SUCCESS(&SingleSsResp))
		{
				AllRecvdSuccess = AllRecvdSuccess && FALSE;
		}
	}
	
ssr_notify_subsys_status_sync_err:
	Status = (EFI_ERROR(Status)&&SrcNum>0)?Status: \
			(AllRecvd && AllRecvdSuccess)?EFI_SUCCESS:EFI_COMPROMISED_DATA;
	return Status;
	
}


EFI_STATUS ssr_notify_shutdown(SSR_SUBSYS_CTX_TYPE* DstCtx, UINT32 Timeout)
{
	qmi_ssctl_shutdown_req_msg_v02	Req = { 0 };
	qmi_ssctl_shutdown_resp_msg_v02 Resp;
	EFI_STATUS	Status = EFI_SUCCESS;
	SSR_RUNTIME_INFO*	RuntimeInfo;
	qmi_client_error_type	QmiErr=0;
	INT32 KernelRet;
	
	ASSERT(QmiProt!=NULL && DstCtx!=NULL && DstCtx->SubsysCfg!=NULL && DstCtx->SubsysCfg->Name);
	if ((RuntimeInfo=DstCtx->RuntimeInfo)==NULL)
		ASSERT(0);
	
	if (RuntimeInfo->QmiHdl==NULL)
	{
		DEBUG((EFI_D_ERROR,"warning: no QMI connection to %a\n", DstCtx->SubsysCfg->Name));
		return EFI_UNSUPPORTED;
	}
	
	KernelRet = EventUnsignal(IndEvt);
	if (KernelRet != NO_ERROR)
	{
		DEBUG((EFI_D_ERROR,"Failed to unsignal IndEvt 0x%x\n", KernelRet));
		Status = EFI_COMPROMISED_DATA;
		goto ssr_notify_shutdown_err;
	}
	
	Status = QmiProt->QmiClientSendMsgSync(	RuntimeInfo->QmiHdl, 
											QMI_SSCTL_SHUTDOWN_REQ_V02,
											&Req,
											sizeof(qmi_ssctl_shutdown_req_msg_v02),
											RuntimeInfo->LastRespMsg,
											sizeof(qmi_ssctl_shutdown_resp_msg_v02),
											Timeout,
											QmiErr);
	if (EFI_ERROR(Status))
	{
		DEBUG((EFI_D_ERROR,"Failed to send shutdown req to %a\n", DstCtx->SubsysCfg->Name));
		goto ssr_notify_shutdown_err;
	}
	
	CopyMem(&Resp, &((qmi_ssctl_shutdown_resp_msg_v02*)(RuntimeInfo->LastRespMsg))->resp, \
				sizeof(qmi_ssctl_shutdown_resp_msg_v02));
	if (!RESP_RECVD(&(Resp.resp)) || !RESP_RECVD_SUCCESS(&(Resp.resp)))
	{
		DEBUG((EFI_D_ERROR,"Failed to get success shutdown resp from %a, ret %d err %d\n", \
				DstCtx->SubsysCfg->Name, Resp.resp.result, Resp.resp.error));
		Status = EFI_COMPROMISED_DATA;
		goto ssr_notify_shutdown_err;
	}		
	
	KernelRet = EventWaitTimeout(IndEvt, Timeout);
	{
		DEBUG((EFI_D_ERROR,"Failed to wait IndEvt 0x%x\n", KernelRet));
		Status = EFI_COMPROMISED_DATA;
		goto ssr_notify_shutdown_err;
	}

ssr_notify_shutdown_err:
	return Status;
}


