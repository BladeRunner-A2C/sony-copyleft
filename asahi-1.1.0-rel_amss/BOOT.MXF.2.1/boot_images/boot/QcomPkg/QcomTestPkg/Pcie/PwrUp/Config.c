/** @file Config.c
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2020 - 2024 Qualcomm Technologies, Inc.
#  All rights reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
**/

#include "Kona.h"
#include "Lahaina.h"
#include "Waipio.h"
#include "Kailua.h"
#include "Lanai.h"
#include "Hamoa.h"
#include "Palawan.h"

PlatModulePwrupConfigType* PeripheralDevices[] = 
{
   &LanaiModulesConfig,
   
   &KailuaModulesConfig,

   &WaipioModulesConfig,

   &LahainaModulesConfig,

   &KonaModulesConfig,

   &HamoaModulesConfig,

   &PalawanModulesConfig,

   NULL,
};

