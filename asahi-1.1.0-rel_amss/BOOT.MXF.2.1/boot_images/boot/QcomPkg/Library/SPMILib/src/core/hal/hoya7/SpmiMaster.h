/**
 * @file:  SpmiMaster.h
 * @brief: Configures the Spmi Master Controller
 * 
 * Copyright (c) 2013-2015 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2024/04/02 23:00:31 $
 * $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/SPMILib/src/core/hal/hoya7/SpmiMaster.h#1 $
 * $Change: 53083464 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 10/1/13  Initial Version
 */
#ifndef SPMIMASTER_H
#define	SPMIMASTER_H

#include "SpmiBusCfg.h"
#include "SpmiUtils.h"
#include "SpmiInfo.h"

Spmi_Result SpmiMaster_ConfigHW(SpmiDevInfo *pDev, uint8 masterId, SpmiBusCfg_ConfigType cfgType);
void SpmiMaster_LoadRadixTree(SpmiDevInfo *pDev, SpmiBusCfg_ChannelCfg* entries, uint32 numEntries);

#endif

