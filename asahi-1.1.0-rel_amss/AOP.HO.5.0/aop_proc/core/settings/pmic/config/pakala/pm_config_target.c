/*! \file pm_config_target.c
 *
 *  \brief This file contains customizable target specific driver settings & PMIC registers.
 *         This file info is taken from Target Component Resource Specific Settings from PDM
 *         that is maintained for each of the targets separately.
 *
 *  &copy; Copyright 2013 - 2019 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_pakala_base/aop_proc/core/settings/pmic/config/lanai/pm_config_target.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/17/14   kt      Created.
03/11/19   pv      Rail and clock structures changed as per C99
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"
#include "pm_config_target.h"

/*
PMIC  NAME

A  A_Azura(PMK8650) 
B  B_Humu(PM8550) 
C
D  D_Voodoo8(V8_PM8550VE) 
E
F  F_Voodoo6(V6_PM8550VS) 
G  G_Voodoo8(V6_PM8550VE) 
H
I  I_Voodoo8(V8_PM8550VE) 
J  J_Voodoo6(PM8550VS) 
K  K_NaloJR(PMR735D) 
L
M  M_Leica2(PM8010) 
N  N_Leica2(PM8010) 
*/

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type bob_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3008,  .MaxVoltage = 4000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 750,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // BOB1 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_AUTO_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 2704,  .MaxVoltage = 3008,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 500,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // BOB2 
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD, .Reserved = 0}, // L01B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 272,  .MinVoltage = 3008,  .MaxVoltage = 3048,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD, .Reserved = 0}, // L02B 
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L03B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 8,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L04B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 288,  .MinVoltage = 3100,  .MaxVoltage = 3148,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 30,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L05B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 168,  .MinVoltage = 1800,  .MaxVoltage = 3008,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L06B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 168,  .MinVoltage = 1800,  .MaxVoltage = 3008,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L07B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 1800,  .MaxVoltage = 3008,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L08B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 168,  .MinVoltage = 2960,  .MaxVoltage = 3008,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L09B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 8,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L10B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 1064,  .MaxVoltage = 1292,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L11B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 1200,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L12B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 3000,  .MaxVoltage = 3000,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L13B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 184,  .MinVoltage = 3200,  .MaxVoltage = 3200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L14B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 104,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // L15B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L16B 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 168,  .MinVoltage = 2504,  .MaxVoltage = 2504,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L17B 
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1D 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 880,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD, .Reserved = 0}, // L2D 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 880,  .MaxVoltage = 920,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L3D 
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_f[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 40,  .MinVoltage = 880,  .MaxVoltage = 920,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 17,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1F 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2F 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3F 
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_g[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 40,  .MinVoltage = 912,  .MaxVoltage = 936,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L1G 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 1200,  .MaxVoltage = 1860,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L2G 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 1200,  .MaxVoltage = 1256,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L3G Do we need to remove PC handling Dynamic ACC
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_i[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 8,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1I 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 40,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // L2I 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 40,  .MinVoltage = 880,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L3I Remove PC handling Dynamic ACC
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_j[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 880,  .MaxVoltage = 920,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1J 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 8,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2J 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 300,  .MaxVoltage = 1000,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L3J lpi_mx
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_k[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 400,  .MaxVoltage = 920,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L1K 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 912,  .MaxVoltage = 1000,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L2K 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L3K Need client to vote on bypass mode
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 80,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L4K 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 80,  .MinVoltage = 952,  .MaxVoltage = 976,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L5K 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 1776,  .MaxVoltage = 1860,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L6K 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 800,  .MaxVoltage = 800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L7K 
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_m[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 112,  .MinVoltage = 1104,  .MaxVoltage = 1104,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1M 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 1056,  .MaxVoltage = 1056,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2M 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 248,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3M 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 144,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L4M 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 96,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L5M 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 136,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L6M 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 312,  .MinVoltage = 2960,  .MaxVoltage = 2960,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7M 
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_n[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 1104,  .MaxVoltage = 1104,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1N 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 1104,  .MaxVoltage = 1104,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2N 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 144,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3N 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 144,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L4N 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L5N 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 104,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L6N 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 104,  .MinVoltage = 3304,  .MaxVoltage = 3304,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7N 
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 928,  .MaxVoltage = 1100,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S1D Parent
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S2D vdd gfx mx add alias 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1200,  .MaxVoltage = 1300,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S3D Parent
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 500,  .MaxVoltage = 1036,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S4D WCN_MX, Modem PDC vote for mode
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1100,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S5D vdd gfx add alias
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S6D gfx follower
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S7D gfx follower
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S8D gfx follower
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_f[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S1F apc1_cx
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S2F apc1_cx
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S3F apc1_cx
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S4F** apc1_cx
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 500,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANBB, .Reserved = 0}, // S5F** wcn_cx 
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 400,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S6F** apc0_mx
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S7F** acp1_mx
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 400,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S8F** vdd_mx
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_g[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 700,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S1G VDDQ
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S2G alias for vdda ebi
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1856,  .MaxVoltage = 2000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S3G 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 900,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // S4G 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 900,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S5G alias for vdd_modem
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S6G modem follower
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 480,  .MaxVoltage = 1100,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S7G vdd nsp1 alias for nsp1
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S8G nsp1 follower
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_i[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 400,  .MaxVoltage = 1100,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S1I vdd nsp2 alias for nsp2
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S2I nsp2 follower
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 400,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S3I alias for vdd mm
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S4I mm follower
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S5I alias for lpi cx
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S6I alias for mxc 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1224,  .MaxVoltage = 1340,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S7I parent
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 900,  .MaxVoltage = 972,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S8I vdd2l
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_j[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1100,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S1J alias for vdd cx
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1000,  .MaxVoltage = 1100,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S2J vdd 2h, do we need ret ? 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1000,  .MaxVoltage = 1100,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S3J Do we need to allow this optional rail
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 500,  .MaxVoltage = 1000,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANBB, .Reserved = 0}, // S4J ** apc0cx
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S5J apc0cx
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S6J apc0cx
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_clk_info_type clk_info_a[]=
{
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//CLK_DIST *not supported
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_WLANBB, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK1_RF  wlan
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK2_RF  protostar
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_HLOS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK3_RF  NFC
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK4_RF  Is it needed for Gnss
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 0, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK5_RF  spare
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_ARC, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK6_LN  
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 0, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK7_LN  spare
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_HLOS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK8_LN  UFS
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 0, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK9_LN  spare
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 0, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY  
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 0, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK11_DIV  
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 0, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY  
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 0, .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0, .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // SLEEP_CLK1  
};


/*Name, PmicIndex, PeriphType, PeriphId, AccessAllowed, SlaveId, BaseAddr, RsrcCategory, EnableAddrOff, EnableFixedTime, EnableSeqType, ModeAddrOff, ModeFixedTime, ModeSeqType, 
  VoltAddrOff, VoltFixedTime, VoltSeqType, MaxVoltage, DrvOwnMask, Reserved*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_target_rsrc_info_type target_rsrc_info[] = 
{
  {"vreg.sp", 0, PM_VRM_PERIPH_VREG, 1, {PM_ACCESS_ALLOWED, 0x1, 0x3E00, VRM_RSRC_XO_BUFFER, 0x80, 420, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC, 0}},
  {"gpio.sp", 0, PM_VRM_PERIPH_GPIO, 7, {PM_ACCESS_ALLOWED, 0x1, 0x8E00, VRM_RSRC_XO_BUFFER, 0x46, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC, 0}},
  //{"rclkha1", 0, PM_VRM_PERIPH_CLK,  5, {PM_ACCESS_ALLOWED, 0x0, 0x5400, VRM_RSRC_REGULATOR, 0x45, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_MDMS, 0}},
  {"bclplmb0",    0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x1, 0x4800, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
//Add BCL PLM 2 for Kiholo  
  {"bclplmh0",    0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x7, 0x4800, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"vrm.apc0",   0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x9, 0xA500, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"vrm.apc1",   0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x5, 0x9C00, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"vrm.amx0", 0, PM_VRM_PERIPH_NONE, 0, { PM_ACCESS_ALLOWED, 0x5, 0xAB00, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0 }},
  {"vrm.amx1", 0, PM_VRM_PERIPH_NONE, 0, { PM_ACCESS_ALLOWED, 0x5, 0xAE00, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0 }},
};
                                                  
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type pstm_a[] = 
{
  { .pbs_name = "vrm.aoss", .LowVal = 0x01, .HighVal = 0x02, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AOP, .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED, .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //
  { .pbs_name = "vrm.soc", .LowVal = 0x03, .HighVal = 0x04, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AUD|PM_DRV_DDR|PM_DRV_HLOS|PM_DRV_MDMS|PM_DRV_TZ, .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED, .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //
};

uint32   num_of_target_rsrc[]= {sizeof(target_rsrc_info)/sizeof(target_rsrc_info[0])};

uint32 num_of_ldo[] = {0,sizeof(ldo_rail_b)/sizeof(ldo_rail_b[0]), 0, sizeof(ldo_rail_d)/sizeof(ldo_rail_d[0]), 0, sizeof(ldo_rail_f)/sizeof(ldo_rail_f[0]), sizeof(ldo_rail_g)/sizeof(ldo_rail_g[0]), 0, sizeof(ldo_rail_i)/sizeof(ldo_rail_i[0]),sizeof(ldo_rail_j)/sizeof(ldo_rail_j[0]),sizeof(ldo_rail_k)/sizeof(ldo_rail_k[0]), 0,sizeof(ldo_rail_m)/sizeof(ldo_rail_m[0]),sizeof(ldo_rail_n)/sizeof(ldo_rail_n[0]), 0, 0};
uint32 num_of_smps[] = {0,0,0,sizeof(smps_rail_d)/sizeof(smps_rail_d[0]),0,sizeof(smps_rail_f)/sizeof(smps_rail_f[0]),sizeof(smps_rail_g)/sizeof(smps_rail_g[0]),0,sizeof(smps_rail_i)/sizeof(smps_rail_i[0]),sizeof(smps_rail_j)/sizeof(smps_rail_j[0]),0,0,0,0, 0, 0};
uint32   num_of_bob[]        = {0, sizeof(bob_rail_b)/sizeof(bob_rail_b[0]), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32   num_of_pstm_seq[]   = {sizeof(pstm_a)/sizeof(pstm_a[0]),0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* ldo_rail[]=
{
 NULL, ldo_rail_b, NULL, ldo_rail_d, NULL, ldo_rail_f, ldo_rail_g, NULL, ldo_rail_i, ldo_rail_j, ldo_rail_k, NULL, ldo_rail_m, ldo_rail_n, NULL, NULL};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* smps_rail[]=
{
 NULL, NULL, NULL, smps_rail_d, NULL, smps_rail_f, smps_rail_g, NULL, smps_rail_i, smps_rail_j, NULL, NULL, NULL, NULL, NULL, NULL};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_clk_info_type* clk_info[]=
{
    clk_info_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* bob_rail[]=
{
    NULL, bob_rail_b, NULL , NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type* pstm_info[]=
{
    pstm_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
uint32 rpmh_drv_id[] = {(uint32)RSC_DRV_AOP};




/*
PMIC  NAME

A  A_Azura(PMK8650) 
B  B_Humu(PM8550) 
C
D  D_Voodoo8(V8_PM8550VE) 
E
F  F_Voodoo6(V6_PM8550VS) 
G  G_Voodoo8(V6_PM8550VE) 
H
I  I_Voodoo8(V8_PM8550VE) 
J  J_Voodoo6(PM8550VS) 
K  K_NaloJR(PMR735D) 
L
M  M_Leica2(PM8010) 
N  N_Leica2(PM8010) 
*/

__attribute__((section("pm_dram_reclaim_pool")))
uint8 pm_periph_bitmap[][PM_MAX_BITMAP_ENTRIES] =
{
  /* 0: pmk8650 */
  {
    0xf2, 0xab, 0xee, 0xff, 
    0xff, 0x7b, 0x40, 0x22, 
    0x00, 0x00, 0xf3, 0x5f, 
    0x9f, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x3f, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x03, 0x00, 0x40, 
    
  },
  /* 1: pm8650 */
  {
    0x72, 0xef, 0x38, 0x30,
    0x00, 0x00, 0x40, 0x52,
    0x83, 0x07, 0x02, 0x40,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0xff, 0x0f, 0x03,
    0x00, 0x00, 0x00, 0x00,
    0xfe, 0xff, 0x03, 0x00,
    0xf6, 0xcf, 0x00, 0xc0,
    
  },
  /* 2: Empty */
  {
    0,
  },
  /* 3: pm8550ve */
  {
    0x72, 0xcf, 0x00, 0x30, 
    0x00, 0x00, 0x40, 0x12, 
    0x00, 0x00, 0x02, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0x00, 0xfe, 
    0xff, 0xff, 0x07, 0x00, 
    0x0e, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0xc0, 
    
  },
  /* 4: Luminous */
  {
    0,
  },
  /* 5: pm8550ve */
  {
    0x72, 0xcf, 0x00, 0x30, 
    0x00, 0x00, 0x40, 0x12, 
    0x00, 0x00, 0x02, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0x00, 0xfe, 
    0xff, 0xff, 0x07, 0x00, 
    0x0e, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0xc0, 
    
  },
  /* 6: pm8550ve */
  {
    0x72, 0xcf, 0x00, 0x30, 
    0x00, 0x00, 0x40, 0x12, 
    0x00, 0x00, 0x02, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0x00, 0xfe, 
    0xff, 0xff, 0x07, 0x00, 
    0x0e, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0xc0, 
    
  },
  /* 7: pm8550b */
  {
    0x72, 0xdf, 0xd0, 0x73, 
    0xe0, 0x3f, 0x41, 0x76, 
    0x80, 0xc1, 0x02, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0x0f, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x07, 0x60, 
    
  },
  /* 8: pm8550ve */
  {
    0x72, 0xcf, 0x00, 0x30, 
    0x00, 0x00, 0x40, 0x12, 
    0x00, 0x00, 0x02, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0x00, 0xfe, 
    0xff, 0xff, 0x07, 0x00, 
    0x0e, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0xc0, 
    
  },
  /* 9: pm8550ve */
  {
    0x72, 0xcf, 0x00, 0x30, 
    0x00, 0x00, 0x40, 0x12, 
    0x00, 0x00, 0x02, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0x00, 0xfe, 
    0xff, 0xff, 0x07, 0x00, 
    0x0e, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0xc0, 
    
  },
  /* A: pmr735d */
  {
    0x72, 0x4f, 0x00, 0x30, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x02, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x03, 0x00, 0x02, 
    0x00, 0x00, 0x00, 0x00, 
    0xfe, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0xc0, 
    
  },
  /* B: empty */
  {
    0x0,
  },
  /* C: pm8010 */
  {
    0xf2, 0x02, 0x00, 0x00, 
    0x10, 0x10, 0x00, 0x00, 
    0x7f, 0x00, 0x02, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x03, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0x00, 
    
  },
  /* D: pm8010 */
  {
    0xf2, 0x02, 0x00, 0x00, 
    0x10, 0x10, 0x00, 0x00, 
    0x7f, 0x00, 0x02, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x03, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0x00, 
    
  },

};

/*Min poll time[in us] threshold in vrm for regulators*/
__attribute__((section("pm_dram_reclaim_pool")))
uint32 min_settling_time_thr[] = {(uint32)600};
