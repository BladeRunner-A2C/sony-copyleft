/**
 * @file:  SpmiBlock.c
 * 
 * Copyright (c) 2013-2016 by Qualcomm Technologies 
 * Incorporated. All Rights Reserved. 
 * 
 * $DateTime: 2022/05/20 00:19:17 $
 * $Header: //components/dev/aop.ho/5.0/parasv.aop.ho.5.0.lanai_pmic_stubs_verification/aop_proc/core/pmic/spmi/src/platform/config/hoya7/kailua/SpmiBlock.c#1 $
 * $Change: 37313055 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 10/1/13  Initial Version
 */

#include "SpmiInfo.h"
#include "SpmiTypes.h"
#include "SpmiHal.h"
#include "SpmiGenericConsts.h"
#include "SpmiUtils.h"
#include "SpmiOsTarget.h"

#define SPMI_PMIC_ARB_PHYS_ADDRESS 0x0000000
#define SPMI_BARE_OWNER_NUMBER     4

#define SPMI_MAX_BUSES_SUPPORTED      (1)

static uint16 periphMap[SPMI_MAX_PERIPH_ID + 1];
static ChannelMapEntry channelMap[SPMI_MAX_CHANNELS_SUPPORTED];
static SpmiDeviceGenerics generics=INIT_SPMI_DEV_GENERICS;

static SpmiTargetConfig spmiTgt =
{
    .hwioAddrStr    = "AOSS",
    .interruptVec   = 96,
};

SpmiDevInfo spmiDevices[] = {
   {
      .baseAddrs          = (uint8*)SPMI_PMIC_ARB_PHYS_ADDRESS,
      .uDevIdx            = 0,
      .reservedChan       = SPMI_MAX_CHANNELS_SUPPORTED - 1,
      .nextChanIdx        = 0,
      .reservedChanEn     = TRUE,   
      .dynamicChannelMode = FALSE,   
      .periphMap          = periphMap,
      .channelMap         = channelMap,
      .pGenerics          = &generics,
      .target             = (void*) &spmiTgt,    
      .numPmicArbChan     = 0,
      .busChanStart       = 0,
      .interruptVec       = 96,
      .interruptSupported = FALSE,

   },
};

SpmiInfo spmiInfo = {
  .owner              = SPMI_BARE_OWNER_NUMBER,
  .uNumDevices        = SPMI_MAX_BUSES_SUPPORTED,
  .devices            = spmiDevices,
};

SpmiInfo * pSpmiBlockInfo = &spmiInfo;

