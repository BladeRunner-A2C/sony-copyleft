/** @file Lanai.h
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc. All rights reserved.
**/

#ifndef __PERIPH_PWR_LANAI_H__
#define __PERIPH_PWR_LANAI_H__

#include "Config.h"

RailsCfgType WlanRailsLanai[] =
{
   {.NodeName = "/pm/ldob15", .MicroVolts =  1800000},
   {.NodeName = "/pm/ldoc3",  .MicroVolts =  1200000},
   {.NodeName = "/pm/smpi4",  .MicroVolts =   940000},
   {.NodeName = "/pm/smpc2",  .MicroVolts =   976000},
   {.NodeName = "/pm/smpc3",  .MicroVolts =   916000},
   {.NodeName = "/pm/smpc6",  .MicroVolts =  1864000},
   {.NodeName = "/pm/smpc1",  .MicroVolts =  1316000},
   {.NodeName = "/pm/ldok6",  .MicroVolts =  1800000},
   {.NodeName = NULL,         .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioLanai[] =
{
   {.GpioNum = 16, .EnableLevel = 1},
   {.GpioNum = 0,  .EnableLevel = 0},
};

ModulePwrupConfigType LanaiWlan =
{
   .ConfigLabel = "Lanai_WLan",
   .PeriphName = PERIPH_MODULE_NAME_WLAN,
   .PCIeRCIndex = 0,
   .RailsCfg = WlanRailsLanai,
   .EnGpio = WlanEnGpioLanai,
};

ModulePwrupConfigType* LanaiModules[] =
{
   &LanaiWlan,
   NULL,
};

PlatModulePwrupConfigType LanaiModulesConfig =
{
   .ChipInfoId = 0,
   .ChipFamilyId = EFICHIPINFO_FAMILY_LANAI,
   .PeriphModuleCfg = LanaiModules,
};

#endif  /* __PERIPH_PWR_LANAI_H__ */

