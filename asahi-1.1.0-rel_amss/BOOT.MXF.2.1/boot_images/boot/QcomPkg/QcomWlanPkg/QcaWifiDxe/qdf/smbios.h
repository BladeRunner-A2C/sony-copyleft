/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
#ifndef __SMBIOS_CFG_H__
#define __SMBIOS_CFG_H__

#define VENDER_BDF_EXT_MAX_LEN  		133

typedef struct SMBIOS_CFG_PARA{
	UINT8 ACAXCfg;   	  // 11AC/11Ax cfg
	UINT8 CCSetFlag;    // 0:disable CC setting from smbios, 1: format is Country Code ANSI, 2: WWR
	union
	{
		struct{
			UINT8 Lowpart;
			UINT8 Highpart;
		}SepCCValue;
		UINT16 CCValue;
	}u;
	UINT8 VenderBdfString[VENDER_BDF_EXT_MAX_LEN];
}SMBIOS_CFG, *P_SMBIOS_CFG;

EFI_STATUS SmbiosGetWlanCfg(P_SMBIOS_CFG SmbiosCfg);

#endif

