/*===============================================================================
  Copyright (c) 2020,2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc
  
  FILE: 		SSRCfg.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/10/20	 yanw  	    initial version

================================================================================*/
#ifndef __SSR_CFG_H__
#define __SSR_CFG_H__

#include <smem_type.h>
#include <Library/KernelLib.h>
#include "subsystem_control_v02.h"

/* todo, use struct of smp2p entry, instead of bit */
typedef struct 
{
	CHAR8* EntryName;
	UINT32 Bit;
} SMP2P_CFG_TYPE;

typedef struct
{
	UINT32 				Vector;
	enum IntrConfig		IntrCfg;
} INTR_CFG_TYPE;


typedef struct
{
	CHAR8*					Name;	// glink name
	UINT32					NumOfSubsysId;
	UINT32*					SubsysId;
	smem_host_type			Host;
	smem_mem_type			SFRType;
	INTR_CFG_TYPE		WdogIntr;
	SMP2P_CFG_TYPE 	ErrFatal;
	SMP2P_CFG_TYPE 	ProxyUnvote;
	SMP2P_CFG_TYPE 	ErrReady;
	SMP2P_CFG_TYPE 	StopAck;
	ssctl_qmi_service_instance_enum_type_v02 QmiSvcIns;
	VOID*			SubsysCtx;
} SSR_SUBSYS_CFG_TYPE;

extern UINT32 MaxSubsysConfigured;

/* ssr failure reason bit is not watched, just to print out reason 
when err_fatal detected */
#define SSR_SFR_BIT			0x8

EFI_STATUS LoadSSRSubsystemConfigFromDT(void);
SSR_SUBSYS_CFG_TYPE* LookupSSRCfgById(UINT32);
SSR_SUBSYS_CFG_TYPE* LookupSSRCfgByName(CHAR8*);
SSR_SUBSYS_CFG_TYPE* LookupSSRCfgBySvcInsId(ssctl_qmi_service_instance_enum_type_v02);
EFI_STATUS SpreadEntryInitVal(smem_host_type, UINT32);

#endif // __SSR_CFG_H__