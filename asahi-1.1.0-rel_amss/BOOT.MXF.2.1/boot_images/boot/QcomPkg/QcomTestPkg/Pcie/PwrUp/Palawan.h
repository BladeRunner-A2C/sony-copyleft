/** @file Palawan.h
#
#  Config module for Pwrup Application.
#
#  Copyright (c) 2024 Qualcomm Technologies, Inc. All rights reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
**/

#ifndef __PERIPH_PWR_PALAWAN_H__
#define __PERIPH_PWR_PALAWAN_H__

#include "Config.h"


RailsCfgType MslWlanRailsPalawan[] =
{
   {.NodeName = "/pm/ldob2",  .MicroVolts =   880000},
   {.NodeName = "/pm/ldob4",  .MicroVolts =  1200000},
  /*{.NodeName = "/pm/ldob7",  .MicroVolts =  1800000},*/     //already turned on during boot up//
   {.NodeName = "/pm/smpb1",  .MicroVolts =  1856000},
   {.NodeName = "/pm/smpb2",  .MicroVolts =  1304000},
   {.NodeName = "/pm/smpb3",  .MicroVolts =   984000},
   {.NodeName = "/pm/smpe3",  .MicroVolts =  2200000},
   {.NodeName = NULL,         .MicroVolts = 0},
};

RailsCfgType HmtWlanRailsPalawan[] =
{
   {.NodeName = "/pm/ldob2",  .MicroVolts =   880000},
   {.NodeName = "/pm/ldob4",  .MicroVolts =  1200000},
  /*{.NodeName = "/pm/ldob7",  .MicroVolts =  1800000},*/     //already turned on during boot up//
   {.NodeName = "/pm/smpb1",  .MicroVolts =  1856000},
   {.NodeName = "/pm/smpb2",  .MicroVolts =  1304000},
   {.NodeName = "/pm/smpb3",  .MicroVolts =   984000},
   {.NodeName = "/pm/smpe3",  .MicroVolts =   830000},
   {.NodeName = NULL,         .MicroVolts = 0},
};

EnGpioCfgType WlanEnGpioPalawan[] =
{
   {.GpioNum = 35, .EnableLevel = 1},
   {.GpioNum = 0,  .EnableLevel = 0},
};

ModulePwrupConfigType PalawanMslWlan =
{
   .ConfigLabel = "Palawan_WLan",
   .PeriphName = PERIPH_MODULE_NAME_WLAN_MSL,
   .PCIeRCIndex = 0,
   .RailsCfg = MslWlanRailsPalawan,
   .EnGpio = WlanEnGpioPalawan,
};

ModulePwrupConfigType PalawanHmtWlan =
{
   .ConfigLabel = "Palawan_WLan",
   .PeriphName = PERIPH_MODULE_NAME_WLAN_HMT,
   .PCIeRCIndex = 0,
   .RailsCfg = HmtWlanRailsPalawan,
   .EnGpio = WlanEnGpioPalawan,
};

ModulePwrupConfigType* PalawanModules[] =
{
   &PalawanMslWlan,
   &PalawanHmtWlan,
   NULL,
};

PlatModulePwrupConfigType PalawanModulesConfig =
{
   .ChipInfoId = 0,
   .ChipFamilyId = EFICHIPINFO_FAMILY_PALAWAN,
   .PeriphModuleCfg = PalawanModules,
};

#endif  /* __PERIPH_PWR_PALAWAN_H__ */
