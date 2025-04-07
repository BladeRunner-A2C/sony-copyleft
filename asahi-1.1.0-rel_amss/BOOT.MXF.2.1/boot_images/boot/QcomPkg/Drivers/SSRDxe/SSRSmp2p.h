/*===============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		SSRSmp2p.h
  DESCRIPTION:	
  
  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  04/24/23	 yanw  	    initial version

================================================================================*/

#ifndef __SSR_SMP2P_H__
#define __SSR_SMP2P_H__

#include "SSRCore.h"

EFI_STATUS ResetSmp2pInfo(SSR_SUBSYS_CTX_TYPE*);
EFI_STATUS RegisterSubsysSmp2pEntry(CHAR8*,	smem_host_type,	SSR_SUBSYS_CTX_TYPE*);
EFI_STATUS CheckSubsysStatusBySmp2p(UINT32, SSR_SUBSYS_STATUS*, UINT32*);
#endif