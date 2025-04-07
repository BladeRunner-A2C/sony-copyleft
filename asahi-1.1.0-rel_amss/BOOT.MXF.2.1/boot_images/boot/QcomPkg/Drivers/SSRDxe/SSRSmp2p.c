/*===============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc
  
  FILE: 		SSRSmp2p.c
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  04/24/23	 yanw  	    initial version

================================================================================*/

#include <Protocol/EFISmp2p.h>
#include <Library/smp2p.h>
#include <Library/UefiBootServicesTableLib.h>
#include "SSRCore.h"
#include "SSRCfg.h"

//#define SSR_SMP2P_DBG_LOG

EFI_SMP2P_PROTOCOL*  Smp2pProtocol = NULL;

CONST UINT32 MaxSmp2pCtxNum = 30;
STATIC UINT32 Smp2pCtxCreatedNum;

/* 
this is the array used to save smp2p info for subsys. 
once assigned to a subsys, it is fixed and cannot change 
*/
STATIC SSR_SMP2P_INFO   Smp2pInfoArray[MaxSmp2pCtxNum];

EFI_STATUS ResetSmp2pInfo(SSR_SUBSYS_CTX_TYPE* Ctx)
{
	SSR_SMP2P_INFO* Smp2pInfo;
	UINT32 Smp2pRet;
	EFI_STATUS Status;
	UINT32 Data = 0;
	
	ASSERT(Smp2pProtocol!=NULL);
	ASSERT(Ctx->Smp2pCtxNum<=1);
	
	if (Ctx->Smp2pCtxNum==0)
	{
		ASSERT(Ctx->Smp2pInfoPtr!=NULL);
		return EFI_SUCCESS;
	}
	
	/* reset the smp2p info for the subsystem, keep the memory for reuse */
	Smp2pInfo = Ctx->Smp2pInfoPtr;
	
	/* read it last time before unregister */
	Status = Smp2pProtocol->Smp2pRead(Smp2pInfo->Ctx, &Data, &Smp2pRet);
	if (EFI_ERROR(Status))
		DEBUG((EFI_D_ERROR, "warning; failed to read smp2p from %a\n", Ctx->SubsysCfg->Name));
	
	if (Data!=0)
	{
#ifdef SSR_SMP2P_DBG_LOG
		DEBUG((EFI_D_ERROR, "debug: read smp2p value 0x%x from %a\n", Data, Ctx->SubsysCfg->Name));
#endif
		Smp2pInfo->Data = Data;
	}
		
	/* unregister smp2p ctx */
	Status = Smp2pProtocol->Smp2pDeregister(Smp2pInfo->Ctx, &Smp2pRet);
	if (EFI_ERROR(Status)) {
		DEBUG((EFI_D_ERROR, "Err: Failed to deregister smp2p ctx smp2pRet 0x%x\n", \
					Smp2pRet));
		return Status;
	}
	Smp2pInfo->Ctx = NULL;
	
	// todo, ignore verify that it will have same number of entry after restart 
	Ctx->Smp2pCtxNum = 0;
	SSR_CLEAR_STATUS_BIT(Ctx->RuntimeInfo->StatusTrace, SMP2P_REG_DONE_BIT);
	return EFI_SUCCESS;
}

STATIC 
BOOLEAN IsNewSmp2pCtx
(
	smp2p_context_type* New,
	SSR_SMP2P_INFO*     ExistInfo, 
	UINT32 ScanNum
)
{
	UINT32 Idx;
	BOOLEAN IsNew = FALSE;
	SSR_SMP2P_INFO* InfoToScan = ExistInfo;
	
	/* first time boot, InfoToScan==NULL, ScanNum == 0
	   in restart, InfoToScan!=NULL, ScanNum==0
	*/
	if (InfoToScan == NULL || ScanNum==0)
		return TRUE;

	/* first time boot, InfoToScan->Ctx!=NULL
	   in restart, InfoToScan->Ctx could be NULL
	*/
	if (ScanNum!=0) ASSERT(InfoToScan->Ctx != NULL);
	
	for (Idx=0;Idx<ScanNum;Idx++)
	{
		if (New != (InfoToScan++)->Ctx)
		{
			IsNew = TRUE;
			break;
		}
	}
	return IsNew; 
}

STATIC
UINT32 FindEmptySmp2pIdx(VOID)
{
	UINT32 Idx;
	for (Idx=0;Idx<MaxSmp2pCtxNum;Idx++)
	{
		/* once smp2p entry associated to subsys, it's one-time assignment,
			cannot change again. so new entry must have data==0*/
		if (Smp2pInfoArray[Idx].SubsysCtx == NULL)
		{
			ASSERT(Smp2pInfoArray[Idx].Data==0);
			return Idx;
		}
	}
	return 0xffff;
}

STATIC
EFI_STATUS	AddSmp2pInfoToSubsys
(
	smp2p_context_type* Smp2pCtx,
	SSR_SUBSYS_CTX_TYPE* SubsysCtx
)
{
	SSR_SMP2P_INFO* Smp2pInfo;
	SSR_RUNTIME_INFO* RuntimeInfo;
	UINT32 Smp2pInfoIdx;
	
	if (Smp2pCtx==NULL || SubsysCtx==NULL || (RuntimeInfo=SubsysCtx->RuntimeInfo)==NULL)
		return EFI_INVALID_PARAMETER;
	
	if (IsNewSmp2pCtx(Smp2pCtx, SubsysCtx->Smp2pInfoPtr, SubsysCtx->Smp2pCtxNum))
	{
		if (SSR_STATUS_BIT_IS_SET(RuntimeInfo->StatusTrace, IN_RESTART_BIT))
		{
			/* SubsysCtx->Smp2pInfoPtr is not NULL, but the content has been
			reset, Smp2pCtxNum also reset.
			so just use the empty slot which was used by last time boot 
			*/
			ASSERT(SubsysCtx->Smp2pInfoPtr!=NULL && SubsysCtx->Smp2pCtxNum==0);
			Smp2pInfo = SubsysCtx->Smp2pInfoPtr + SubsysCtx->Smp2pCtxNum;
			Smp2pInfo->Ctx = Smp2pCtx;
			Smp2pInfo->Data = 0;
		}
		else
		{

			if (SubsysCtx->Smp2pInfoPtr==NULL)
			{
				/* the subsys first time register smp2p */
				if (Smp2pCtxCreatedNum>=MaxSmp2pCtxNum)
					return EFI_OUT_OF_RESOURCES;
				
				if ((Smp2pInfoIdx = FindEmptySmp2pIdx()) >= MaxSmp2pCtxNum)
					ASSERT(0);
				Smp2pInfoArray[Smp2pInfoIdx].Ctx = Smp2pCtx;
				Smp2pInfoArray[Smp2pInfoIdx].Data = 0;
				Smp2pInfoArray[Smp2pInfoIdx].SubsysCtx = SubsysCtx;
				
				if (SubsysCtx->Smp2pInfoPtr==NULL)
					SubsysCtx->Smp2pInfoPtr = &Smp2pInfoArray[Smp2pInfoIdx];
				
				Smp2pCtxCreatedNum++;
			}
			else {
				/* the subsys got shutdown and reload, similar to restart case. Data may not be 0 */
				ASSERT(SubsysCtx->Smp2pInfoPtr!=NULL && SubsysCtx->Smp2pCtxNum==0);
				Smp2pInfo = SubsysCtx->Smp2pInfoPtr + SubsysCtx->Smp2pCtxNum;
				Smp2pInfo->Ctx = Smp2pCtx;
			}
		}
		
		SubsysCtx->Smp2pCtxNum++;
	}

	
	return EFI_SUCCESS;
}

EFI_STATUS RegisterSubsysSmp2pEntry
(
	CHAR8* 			EntryName,
	smem_host_type	Host,
	SSR_SUBSYS_CTX_TYPE* SubsysCtx
)
{
	EFI_STATUS Status;
	UINT32				Smp2pRet;
	smp2p_context_type*	Smp2pCtx=NULL;
	
	if (EntryName==NULL || SubsysCtx==NULL)
		return EFI_INVALID_PARAMETER;
	
	ASSERT(Smp2pProtocol!=NULL);
	
	Status = Smp2pProtocol->Smp2pRegister(&Smp2pCtx, Host, \
					EntryName, &Smp2pRet);
				
	if (EFI_ERROR(Status) && \
		Smp2pRet!=SMP2P_STATUS_DUPLICATE && \
		Smp2pRet!=SMP2P_STATUS_NOT_FOUND)
	{
		DEBUG((EFI_D_ERROR, "Failed to register smp2p entry, st=0x%x smp2p=0x%x\n",\
		       Status, Smp2pRet));
		return Status;
	}
#ifdef SSR_SMP2P_DBG_LOG
	DEBUG((EFI_D_ERROR, "Smp2pRegister, st=0x%x Smp2pCtx=0x%x smp2pret=0x%x\n",\
		       Status, Smp2pCtx, Smp2pRet));
#endif	
	if (Smp2pRet!=SMP2P_STATUS_DUPLICATE)
	{
		ASSERT(Smp2pCtx!=NULL);
		Status = AddSmp2pInfoToSubsys(Smp2pCtx, SubsysCtx);
		if (EFI_ERROR(Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to add smp2p ctx to subsys\n"));
			return Status;
		}
	}
	
	return EFI_SUCCESS;
}

EFI_STATUS CheckSubsysStatusBySmp2p(UINT32 SubsysId, SSR_SUBSYS_STATUS* SubsysStatus, UINT32* Smp2pVal)
{
	EFI_STATUS Status;
	UINT32 EntryVal=0, Smp2pEntryVal = 0xffff;
	UINT32				Smp2pRet;
	SSR_SUBSYS_CTX_TYPE* CtxPtr;
	SSR_SUBSYS_CFG_TYPE*	SubsysCfg;
	smp2p_context_type*	Smp2pCtx=NULL;
	
	Status = InitSubsysCtx(SubsysId, &CtxPtr);
	if (EFI_ERROR(Status)||CtxPtr==NULL)
	{
		DEBUG((EFI_D_ERROR, "Failed to init subsys ctx sub_id %d\n", SubsysId));
		return Status;
	}
	ASSERT(CtxPtr->SubsysCfg);
	SubsysCfg = CtxPtr->SubsysCfg;
	
	if (CtxPtr->SubsysStatus != SSR_SUBSYS_STATUS_UNKOWN)
	{
		/* the subsys is registered previously and in track */ 
		*SubsysStatus = CtxPtr->SubsysStatus;
		Smp2pEntryVal = CtxPtr->Smp2pInfoPtr->Data;
		return EFI_SUCCESS;
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
	
	Status = Smp2pProtocol->Smp2pRegister(&Smp2pCtx, SubsysCfg->Host, \
					(CHAR8*)((SubsysCfg->ErrReady).EntryName), &Smp2pRet);
	if (Status == EFI_SUCCESS)
	{
		/* entry is cresated, go ahead read it */
		*SubsysStatus = SSR_SUBSYS_STATUS_UP;
	}
	else if (Smp2pRet==SMP2P_STATUS_NOT_FOUND)
	{
		/* entry is not created by TX side */
		*SubsysStatus = SSR_SUBSYS_STATUS_DOWN;
	}
	else if (Smp2pRet==SMP2P_STATUS_DUPLICATE)
	{
		/* the subsys is regsitered ssr previously */
		*SubsysStatus = SSR_SUBSYS_STATUS_UP;
	}
	else {
		DEBUG((EFI_D_ERROR, "Failed to register smp2p sub_id %d\n", SubsysId));
		return Status;
	}
	
	if (Smp2pCtx != NULL)
	{
		if (*SubsysStatus == SSR_SUBSYS_STATUS_UP)
		{
			/* read smp2p entry */
			Status = Smp2pProtocol->Smp2pRead(Smp2pCtx, &EntryVal, &Smp2pRet);
			if (EFI_ERROR(Status))
			{
				DEBUG((EFI_D_ERROR, "Failed to read smp2p value sub_id %d smp2p_err\n", SubsysId, Smp2pRet));
				return Status;
			}
			Smp2pEntryVal = EntryVal;
		}
		
		Status = Smp2pProtocol->Smp2pDeregister(Smp2pCtx, &Smp2pRet);
		if (EFI_ERROR(Status)) {
			DEBUG((EFI_D_ERROR, "Failed to deregister smp2p sub_id %d smp2p_err 0x%x\n", SubsysId, Smp2pRet));
			return Status;
		}
	}
	
	if (Smp2pVal && Smp2pEntryVal!=0xffff) *Smp2pVal = Smp2pEntryVal;
#ifdef SSR_SMP2P_DBG_LOG
	DEBUG((EFI_D_ERROR, "debug: subsys_id %d  SubsysStatus %d Smp2pVal 0x%x\n", SubsysId, *SubsysStatus, Smp2pEntryVal));
#endif
	return EFI_SUCCESS;
}