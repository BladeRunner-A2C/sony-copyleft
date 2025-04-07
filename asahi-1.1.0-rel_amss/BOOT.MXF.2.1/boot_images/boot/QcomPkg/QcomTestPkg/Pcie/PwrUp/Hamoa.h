/** @file Hamoa.h
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
**/

#ifndef __PERIPH_PWR_HAMOA_H__
#define __PERIPH_PWR_HAMOA_H__

#include "Config.h"

RailsCfgType WlanRailsHamoa[] = 
{
   {.NodeName = "/pm/smpj5",  .MicroVolts =   1200000},
   {.NodeName = "/pm/smpf1",  .MicroVolts =    880000},
   {.NodeName = "/pm/smpc4",  .MicroVolts =   1800000},
   {.NodeName = "/pm/ldoe3", .MicroVolts =    1200000},
   {.NodeName = "/pm/ldoi3", .MicroVolts =     880000},
   {.NodeName = "/pm/ldoi1", .MicroVolts =    1800000},
   {.NodeName = "/pm/ldob15", .MicroVolts =   1800000},
   {.NodeName = NULL,         .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioHamoa[] = 
{
   {.GpioNum = 80, .EnableLevel = 1},
   {.GpioNum = 0,  .EnableLevel = 0},
};

ModulePwrupConfigType HamoaWlan = 
{
   .ConfigLabel = "Hamoa_WLan",
   .PeriphName = PERIPH_MODULE_NAME_WLAN,
   .PCIeRCIndex = 0,
   .RailsCfg = WlanRailsHamoa,
   .EnGpio = WlanEnGpioHamoa,
};

ModulePwrupConfigType* HamoaModules[] =
{
   &HamoaWlan,
   NULL,
};

PlatModulePwrupConfigType HamoaModulesConfig =
{
   .ChipInfoId = 0,
   .ChipFamilyId = EFICHIPINFO_FAMILY_HAMOA,
   .PeriphModuleCfg = HamoaModules,
};

#endif  /* __PERIPH_PWR_HAMOA_H__ */

