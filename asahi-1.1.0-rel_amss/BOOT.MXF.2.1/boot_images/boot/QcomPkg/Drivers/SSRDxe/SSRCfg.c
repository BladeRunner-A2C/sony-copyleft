/*===============================================================================
  Copyright (c) 2020,2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		SSRCfg.c
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/10/20	 yanw  	    initial version

================================================================================*/

#include <Protocol/EFIDtbExtn.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include "SSRCfg.h"

#define SSR_SUBSYS_CONFIG_NODE_NAME                  "/soc/ssr"

#define SSR_SUBSYS_CONFIG_NODE                       "/soc/ssr/ssr_subsys_config_"

#define DT_NODE_BUF_SIZE 100

STATIC SSR_SUBSYS_CFG_TYPE* pSsrSubsysConfig = NULL;
UINT32 MaxSubsysConfigured;

EFI_STATUS LoadSSRSubsystemConfigFromDT(void)
{
	STATIC EFI_DTB_EXTN_PROTOCOL *DtbExtnProtocol = NULL;
	EFI_STATUS Status = EFI_SUCCESS;
	FdtNodeHandle hNode, pNode;
	UINT32 pHandle = 0;
	CHAR8 SSRSubsystemConfigNode[DT_NODE_BUF_SIZE];
	UINT32 WdogIntr[2] = { 0, 0 };
	UINT32 Size = 0;
	UINT32 Idx = 0;
	
		// Initializing dtb protocol
	if (!DtbExtnProtocol)
	{
		Status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL, (VOID **)&DtbExtnProtocol);
		if (EFI_ERROR(Status))
		{
			DtbExtnProtocol = NULL;
			DEBUG((EFI_D_ERROR,"Failed to locate dtb protocol %r\n",Status));
			return Status;
		}
	}
	
	if (DtbExtnProtocol && (EFI_SUCCESS == Status))
	{
		Status = DtbExtnProtocol->FdtGetNodeHandle (&hNode, SSR_SUBSYS_CONFIG_NODE_NAME);
		if (EFI_SUCCESS != Status) {
			DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get SSR_SUBSYS_CONFIG_NODE_NAME node handle\n"));
			return Status;
		}
		
		Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "max_subsys_configured", &MaxSubsysConfigured);
		if (EFI_SUCCESS != Status || MaxSubsysConfigured==0) {
			DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get max_subsys_configured or is 0\n"));
			return Status;
		}
		
		//Need to read configuration from device tree and store it in SSR_SUBSYS_CFG_TYPE array
		pSsrSubsysConfig = AllocateZeroPool(sizeof(SSR_SUBSYS_CFG_TYPE) * MaxSubsysConfigured);
		if (pSsrSubsysConfig == NULL)
			return EFI_OUT_OF_RESOURCES;
		
		for (Idx=0;Idx<MaxSubsysConfigured;Idx++)
		{
			AsciiSPrint(SSRSubsystemConfigNode, DT_NODE_BUF_SIZE, "%a%d", SSR_SUBSYS_CONFIG_NODE, (Idx+1));
			
			Status = DtbExtnProtocol->FdtGetNodeHandle (&hNode, SSRSubsystemConfigNode);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to read SSR cfg DT node %a\n", SSRSubsystemConfigNode));
				return Status;
			}
			
			Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "subsys_name", &Size);
			if (Status == EFI_SUCCESS)
			{
				pSsrSubsysConfig[Idx].Name = AllocateZeroPool(Size);
				if (pSsrSubsysConfig[Idx].Name == NULL)
					return EFI_OUT_OF_RESOURCES;
				
				Status = DtbExtnProtocol->FdtGetStringPropList(&hNode, "subsys_name", pSsrSubsysConfig[Idx].Name, Size);
				if (EFI_SUCCESS != Status) {
					DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get Subsystem Name\n"));
					return Status;
				}
			}
			else {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get Subsystem size\n"));
				return Status;
			}
			
			Size=0;
			Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "subsys_id", &Size);
			if (EFI_ERROR(Status) || Size == 0)
			{
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get size of subsystem Id\n"));
				return Status;
			}
			pSsrSubsysConfig[Idx].NumOfSubsysId = Size / sizeof(UINT32);
			pSsrSubsysConfig[Idx].SubsysId = AllocateZeroPool(Size);
			if (pSsrSubsysConfig[Idx].SubsysId == NULL)
			{
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to alloc buffer for subsystem Id\n"));
				return EFI_OUT_OF_RESOURCES;
			}
			
			Status = DtbExtnProtocol->FdtGetUint32PropList(&hNode, "subsys_id", pSsrSubsysConfig[Idx].SubsysId, Size);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get subsystem Id\n"));
				return Status;
			}
			
			Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "subsys_id", pSsrSubsysConfig[Idx].SubsysId);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get SSR Subsystem Id\n"));
				return Status;
			}
		
			Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "host", &pSsrSubsysConfig[Idx].Host);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get Host details\n"));
				return Status;
			}
		
			Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "sfr_type", &pSsrSubsysConfig[Idx].SFRType);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get SFR type details\n"));
				return Status;
			}
		
			Status = DtbExtnProtocol->FdtGetPropSize(&hNode, "wdog_intr", &Size);
			if (Status == EFI_SUCCESS)
			{
				Status = DtbExtnProtocol->FdtGetUint32PropList(&hNode, "wdog_intr", WdogIntr, Size);
				if (EFI_SUCCESS != Status) {
					DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get Wdog Intr details\n"));
					return Status;
				}
			}
			else {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get Wdog Intr Size\n"));
				return Status;
			}
			pSsrSubsysConfig[Idx].WdogIntr.Vector = WdogIntr[0];
			pSsrSubsysConfig[Idx].WdogIntr.IntrCfg = WdogIntr[1];
			
			// err_fatal Node Properties
			Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "err_fatal", &pHandle);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get err_fatal\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetPhandleNode(&hNode, pHandle, &pNode);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get phandle node err_fatal\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetPropSize(&pNode, "entry_name", &Size);
			if (Status == EFI_SUCCESS)
			{
				pSsrSubsysConfig[Idx].ErrFatal.EntryName = AllocateZeroPool(Size);
				if (pSsrSubsysConfig[Idx].ErrFatal.EntryName == NULL)
					return EFI_OUT_OF_RESOURCES;
				
				Status = DtbExtnProtocol->FdtGetStringPropList(&pNode, "entry_name", pSsrSubsysConfig[Idx].ErrFatal.EntryName, Size);
				if (EFI_SUCCESS != Status) {
					DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get err_fatal entry_name\n"));
					return Status;
				}
			}
			else {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get err_fatal entry_name size\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetUint32Prop(&pNode, "bit", &pSsrSubsysConfig[Idx].ErrFatal.Bit);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get err_fatal bit details\n"));
				return Status;
			}
			
			// proxy_unvote Node Properties
			Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "proxy_unvote", &pHandle);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get proxy_unvote\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetPhandleNode(&hNode, pHandle, &pNode);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get phandle node proxy_unvote\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetPropSize(&pNode, "entry_name", &Size);
			if (Status == EFI_SUCCESS)
			{
				pSsrSubsysConfig[Idx].ProxyUnvote.EntryName = AllocateZeroPool(Size);
				if (pSsrSubsysConfig[Idx].ProxyUnvote.EntryName == NULL)
					return EFI_OUT_OF_RESOURCES;
				
				Status = DtbExtnProtocol->FdtGetStringPropList(&pNode, "entry_name", pSsrSubsysConfig[Idx].ProxyUnvote.EntryName, Size);
				if (EFI_SUCCESS != Status) {
					DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get proxy_unvote entry_name\n"));
					return Status;
				}
			}
			else {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get proxy_unvote entry_name size\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetUint32Prop(&pNode, "bit", &pSsrSubsysConfig[Idx].ProxyUnvote.Bit);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get proxy_unvote bit details\n"));
				return Status;
			}

			// err_ready Node Properties
			Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "err_ready", &pHandle);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get err_ready\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetPhandleNode(&hNode, pHandle, &pNode);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get phandle node err_ready\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetPropSize(&pNode, "entry_name", &Size);
			if (Status == EFI_SUCCESS)
			{
				pSsrSubsysConfig[Idx].ErrReady.EntryName = AllocateZeroPool(Size);
				if (pSsrSubsysConfig[Idx].ErrReady.EntryName == NULL)
					return EFI_OUT_OF_RESOURCES;
				
				Status = DtbExtnProtocol->FdtGetStringPropList(&pNode, "entry_name", pSsrSubsysConfig[Idx].ErrReady.EntryName, Size);
				if (EFI_SUCCESS != Status) {
					DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get err_ready entry_name\n"));
					return Status;
				}
			}
			else {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get err_ready entry_name size\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetUint32Prop(&pNode, "bit", &pSsrSubsysConfig[Idx].ErrReady.Bit);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get err_ready bit details\n"));
				return Status;
			}
			
			// stop_ack_bit Node Properties
			Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "stop_ack_bit", &pHandle);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get stop_ack_bit\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetPhandleNode(&hNode, pHandle, &pNode);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get phandle node stop_ack_bit\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetPropSize(&pNode, "entry_name", &Size);
			if (Status == EFI_SUCCESS)
			{
				pSsrSubsysConfig[Idx].StopAck.EntryName = AllocateZeroPool(Size);
				if (pSsrSubsysConfig[Idx].StopAck.EntryName == NULL)
					return EFI_OUT_OF_RESOURCES;
				
				Status = DtbExtnProtocol->FdtGetStringPropList(&pNode, "entry_name", pSsrSubsysConfig[Idx].StopAck.EntryName, Size);
				if (EFI_SUCCESS != Status) {
					DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get stop_ack_bit entry_name\n"));
					return Status;
				}
			}
			else {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get stop_ack_bit entry_name size\n"));
				return Status;
			}
			Status = DtbExtnProtocol->FdtGetUint32Prop(&pNode, "bit", &pSsrSubsysConfig[Idx].StopAck.Bit);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get stop_ack_bit bit details\n"));
				return Status;
			}
			
			/* read QmiSvcIns */
			Status = DtbExtnProtocol->FdtGetUint32Prop(&hNode, "qmi_svc_ins", (UINT32*)&pSsrSubsysConfig[Idx].QmiSvcIns);
			if (EFI_SUCCESS != Status) {
				DEBUG((EFI_D_ERROR,"[SSR_CONFIG] Unable to get QmiSvcIns value\n"));
				return Status;
			}
		}
	}
	
	return Status;
}

SSR_SUBSYS_CFG_TYPE* LookupSSRCfgById(UINT32 SubsysId)
{
	UINT32 Idx = 0, Num;

	for (Idx=0; Idx<MaxSubsysConfigured; Idx++)
	{
		for (Num=0;Num<pSsrSubsysConfig[Idx].NumOfSubsysId;Num++)
		{
			if (pSsrSubsysConfig[Idx].SubsysId[Num] == SubsysId)
			{
				return &pSsrSubsysConfig[Idx];
			}
		}
	}

	DEBUG((EFI_D_ERROR,"Failed to find SubsysId %d\n", SubsysId));
	return NULL;
}

SSR_SUBSYS_CFG_TYPE* LookupSSRCfgBySvcInsId(ssctl_qmi_service_instance_enum_type_v02 InstanceId)
{
	UINT32 Idx;
	
	for (Idx=0;Idx<MaxSubsysConfigured;Idx++)
	{
		if (pSsrSubsysConfig[Idx].QmiSvcIns == InstanceId)
		{
			return &pSsrSubsysConfig[Idx];
		}
	}
	
	DEBUG((EFI_D_ERROR,"Failed to find QMI instance id 0x%x\n", InstanceId));
	return NULL;
}

SSR_SUBSYS_CFG_TYPE* LookupSSRCfgByName(CHAR8* SubsysName)
{
	UINT32 Idx = 0;
	
	for (Idx=0; Idx<MaxSubsysConfigured; Idx++)
	{
		if (0 == AsciiStriCmp(pSsrSubsysConfig[Idx].Name, SubsysName))
		{
			return &pSsrSubsysConfig[Idx];
		}
	}

	DEBUG((EFI_D_ERROR,"Failed to find SubsysName %a\n", SubsysName));
	return NULL;
}

