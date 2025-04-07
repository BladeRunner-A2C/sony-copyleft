
#ifndef SPMIPIC_H
#define SPMIPIC_H
/**
 * @file:  SpmiPic.h
 * @brief:
 *
 * Copyright (c) 2013-2017 by Qualcomm Technologies Incorporated. All Rights Reserved.
 *
 * $DateTime: 2022/06/08 10:24:24 $
 * $Header: //components/rel/core.qdsp6/8.0/pmic/spmi/src/core/hal/SpmiPic.h#1 $
 * $Change: 37721481 $
 *
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 5/01/15  Added API to clear all Interrupts
 * 1/20/15  Multiple bus support
 * 10/1/13  Initial Version
 */


#include "SpmiTypes.h"
#include "SpmiInfo.h"

Spmi_Result SpmiPic_SetInterruptEnabled(SpmiDevInfo *pDev, uint8 owner, uint16 channel, boolean enabled);
Spmi_Result SpmiPic_HandleIrq(SpmiDevInfo *pDev, uint8 owner);

#endif

