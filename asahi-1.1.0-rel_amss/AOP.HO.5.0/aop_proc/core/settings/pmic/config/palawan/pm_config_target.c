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

$Header: //components/dev/aop.ho/5.0/avadrav.aop.ho.5.0.palawan_buildinfra_new/aop_proc/core/settings/pmic/config/lanai/pm_config_target.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/17/14   kt      Created.
03/11/19   pv      Rail and clock structures changed as per C99
04/07/23   arua    Palawan Initial Stub
05/29/23   arua    APC,BCL,target resource, L24B Addition
08/18/23   arua    PGA R5_4 L3C Changes, Corrections & RFCLKHOLD Feature
04/10/23   arua    RFCLK name change, RTC_FM owner change 
26/10/23   arua    PGA Min Max Voltage update
03/11/23   arua    PGA Min Max Voltage update to PGA R6_2
05/12/23   arua    PGA Min Max Voltage update to PGA R6_5
18/01/24   arua    PGA Min Max Voltage update to PGA R6_6
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"
#include "pm_config_target.h"


/*
PMIC  Name      SID
A     Azura     0
B     Bonefish  1
C     voodoo6   2
D     voodoo8   3
E     Seco      4
H     Sculpin   7 
H     Kohala    7
I     SecoJr    8
J     SecoJr    9
M     Leica2    C
N     Leica2    D
*/

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type bob_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 0,   .MinVoltage = 3008,  .MaxVoltage = 3960,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 30,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // BOB1 BOB1
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 880,  .MaxVoltage = 958,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L1B QLINK_0p9
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 880,  .MaxVoltage = 950,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC|PM_DRV_HLOS, .Reserved = 0}, // L2B QREF_0p9
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 880,  .MaxVoltage = 920,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L3B USBSSDP_0p9
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 1200, .MaxVoltage = 1200, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC|PM_DRV_HLOS, .Reserved = 0}, // L4B QREF_1p2
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 1200, .MaxVoltage = 1200, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,   .Reserved = 0}, // L5B PX14, PX10
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,   .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,   .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L6B PX11, Azura VDDA
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 104, .MinVoltage = 1800, .MaxVoltage = 1800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,   .Reserved = 0}, // L7B 1.8v AON, Under HV load
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 1800, .MaxVoltage = 1800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L8B AMOLED_VDDIO
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 756,  .MaxVoltage = 816,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L9B SDR753_VDDAL
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 866,  .MaxVoltage = 931,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L10B SDR753/875_VDDA
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1800, .MaxVoltage = 1800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD,   .Reserved = 0}, // L11B TMD_VDD1.8
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 200, .MinVoltage = 2400, .MaxVoltage = 2800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L12B UFS_VCC
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 168, .MinVoltage = 2700, .MaxVoltage = 3300, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS,.VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L13B SDCARD_VDD1,UHS1
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,   .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,   .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L14B Unused
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,   .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,   .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L15B Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 2900, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L16B TMD_VDD3
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 2700, .MaxVoltage = 3300, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L17B eUSB repeater
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 160, .MinVoltage = 2000, .MaxVoltage = 3000, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANRF,.Reserved = 0}, // L18B RTC_FM
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 96,  .MinVoltage = 2600, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L19B AMOLED_VCI
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 232, .MinVoltage = 1620, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS,.VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L20B UIM0
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 232, .MinVoltage = 1620, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS,.VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L21B UIM1
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 184, .MinVoltage = 2700, .MaxVoltage = 3400, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L22B AMOLED_AVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 1650, .MaxVoltage = 3544, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L23B SDC_LS
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 1800, .MaxVoltage = 1800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, //Dummy
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_c[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 904,  .MaxVoltage = 970,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR,   .Reserved = 0}, // L1C LP5_VDD2L
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 504,  .MaxVoltage = 848,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // L2C LPI_MX
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 1200, .MaxVoltage = 1250, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L3C Display
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 866,  .MaxVoltage = 958,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L1D UFS_CORE
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 352,  .MaxVoltage = 848,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // L2D LPI_CX
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 1140, .MaxVoltage = 1260, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L3D UFS_VCCQ
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_e[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 488,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L1E SDR_VDDMX
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 80,  .MinVoltage = 920,  .MaxVoltage = 969,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L2E SDR_VDDALM
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 504,  .MaxVoltage = 868,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L3E SDR753_VDDCX
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 1620, .MaxVoltage = 2000, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L4E SDR_VDDAH
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1100, .MaxVoltage = 1304, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L5E QET
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 96,  .MinVoltage = 1080, .MaxVoltage = 1304, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L6E SDR_VDDAM
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 128, .MinVoltage = 1620, .MaxVoltage = 3300, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // L7E esim
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_m[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 80,  .MinVoltage = 1104, .MaxVoltage = 1104, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L1M OV64B_DVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 1056, .MaxVoltage = 1056, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L2M S5KJN1_DVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 160, .MinVoltage = 2800, .MaxVoltage = 2800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L3M OV64B_AVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 144, .MinVoltage = 2800, .MaxVoltage = 2800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L4M S5KJN1_AVDD
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,   .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,   .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L5M Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 168, .MinVoltage = 2800, .MaxVoltage = 2800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L6M IMX766_AVDD1
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 224, .MinVoltage = 2800, .MaxVoltage = 2800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L7M IMX766, OV64B, S5KJN1_VCM
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_n[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 1104, .MaxVoltage = 1104, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L1N IMX766_DVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 1056, .MaxVoltage = 1056, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L2N IMX688_0_AON_DVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 144, .MinVoltage = 1800, .MaxVoltage = 1800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L3N IMX766_AVDD2
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 96,  .MinVoltage = 1800, .MaxVoltage = 1800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L4N IMX688_0_AON_AVDD2
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 104, .MinVoltage = 1800, .MaxVoltage = 1800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L5N IMX688_0_AON_DOVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 160, .MinVoltage = 2800, .MaxVoltage = 2800, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L6N IMX688_0_AON_AVDD1
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 80,  .MinVoltage = 3304, .MaxVoltage = 3304, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // L7N VCSEL_VCCA33, VCSEL_TX_V33
};
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1856, .MaxVoltage = 2040, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,   .Reserved = 0}, // S1B HV Subreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1256, .MaxVoltage = 1408, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,   .Reserved = 0}, // S2B MV Subreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 968,  .MaxVoltage = 1040, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,   .Reserved = 0}, // S3B LV Subreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 944,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S4B VDD_GFX
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S5B VDD_GFX
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S6B VDD_GFX
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_c[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 1050, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S1C VDD_CX
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 904,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S2C VDD_NSP
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S3C VDD_NSP
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 812,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S4C VDD_MODEM
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S5C VDD_MODEM
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 504,  .MaxVoltage = 884,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S6C VDD_MXC
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S1D APC0
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S2D APC1
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S3D APC1
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S4D APC1
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 1000, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S5D APC1 / A_EBI
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 852,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S6D VDD_MM
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,    .EnableFixedTime = 0,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,  .Reserved = 0}, // S7D VDD_MM
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 504,  .MaxVoltage = 884,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S8D VDD_MXA
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_e[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1010, .MaxVoltage = 1120, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR,   .Reserved = 0}, // S1E LP5_VDD2H
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 570,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR,   .Reserved = 0}, // S2E LP5_VDDQ
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_AUTO_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1600, .MaxVoltage = 2400, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANRF,.Reserved = 0}, // S3E IPA 2P2
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_i[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 1000, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,   .Reserved = 0}, // S1I VDDA_EBI
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_j[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 504,  .MaxVoltage = 868, .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 20, .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,  .Reserved = 0}, // S1J SDR875_VDDCX
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_clk_info_type clk_info_a[]=
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//CLK_DIST *not supported
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF,.ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK1
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_MDMS,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK2
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn = 0,      .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0,            .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK3
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn = 0,      .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0,            .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK4
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn = 0,      .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0,            .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK5
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//BB_CLK1
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//BB_CLK2
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//BB_CLK3
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//BB_CLK4
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  PM_OFF,.EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//DIV_CLK1
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//SLEEP_CLK  
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//Dummy
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//Dummy
};


/*Name, PmicIndex, PeriphType, PeriphId, AccessAllowed, SlaveId, BaseAddr, RsrcCategory, EnableAddrOff, EnableFixedTime, EnableSeqType, ModeAddrOff, ModeFixedTime, ModeSeqType, 
  VoltAddrOff, VoltFixedTime, VoltSeqType, MaxVoltage, DrvOwnMask, Reserved*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_target_rsrc_info_type target_rsrc_info[] = 
{
  //{"vreg.sp",  0, PM_VRM_PERIPH_VREG, 1, {PM_ACCESS_ALLOWED, 0x1, 0x3E00, VRM_RSRC_XO_BUFFER, 0x80, 420, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC,  0}},
  //{"gpio.sp",  0, PM_VRM_PERIPH_GPIO, 7, {PM_ACCESS_ALLOWED, 0x1, 0x8E00, VRM_RSRC_XO_BUFFER, 0x46, 20,  VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC,  0}},
  {"clkha2",     0, PM_VRM_PERIPH_CLK,  5, {PM_ACCESS_ALLOWED, 0x0, 0x5500, VRM_RSRC_REGULATOR, 0x45, 20,  VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_MDMS, 0}},
  {"bclplmb0",   0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x1, 0x4800, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"bclplmh0",   0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x7, 0x4800, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"vrm.apc0",   0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x3, 0x9C00, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"vrm.apc1",   0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x3, 0x9F00, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  //{"vrm.apc2", 0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x4, 0xA500, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type pstm_a[] = 
{
  {.pbs_name = "vrm.aoss", .LowVal = 0x01, .HighVal = 0x02, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AOP ,                                  .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-AOSS_Sleep 1-AOSS_Wake
  {.pbs_name = "vrm.soc",  .LowVal = 0x03, .HighVal = 0x04, .SettlingTime = 900, .DrvOwnMask = PM_DRV_DDR|PM_DRV_TZ|PM_DRV_AUD|PM_DRV_MDMS , .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-SOC_Sleep 1-SOC_Wake
  {.pbs_name = "vrm.wlan", .LowVal = 0x06, .HighVal = 0x05, .SettlingTime = 900, .DrvOwnMask = PM_DRV_WLANRF,                                .DefaultVal = 0, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-WLAN_WA_DISENGAGE 1- WLAN_ENGAGE
};

uint32   num_of_target_rsrc[]= {sizeof(target_rsrc_info)/sizeof(target_rsrc_info[0])};

uint32   num_of_ldo[]        = {0, sizeof(ldo_rail_b)/sizeof(ldo_rail_b[0]), sizeof(ldo_rail_c)/sizeof(ldo_rail_c[0]), sizeof(ldo_rail_d)/sizeof(ldo_rail_d[0]), sizeof(ldo_rail_e)/sizeof(ldo_rail_e[0]), 0, 0, 0, 0, 0, 0, 0, sizeof(ldo_rail_m)/sizeof(ldo_rail_m[0]), sizeof(ldo_rail_n)/sizeof(ldo_rail_n[0])};
uint32   num_of_smps[]       = {0, sizeof(smps_rail_b)/sizeof(smps_rail_b[0]), sizeof(smps_rail_c)/sizeof(smps_rail_c[0]), sizeof(smps_rail_d)/sizeof(smps_rail_d[0]),  sizeof(smps_rail_e)/sizeof(smps_rail_e[0]), 0, 0, 0, sizeof(smps_rail_i)/sizeof(smps_rail_i[0]), sizeof(smps_rail_j)/sizeof(smps_rail_j[0])};
uint32   num_of_bob[]        = {0, sizeof(bob_rail_b)/sizeof(bob_rail_b[0]), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32   num_of_pstm_seq[]   = {sizeof(pstm_a)/sizeof(pstm_a[0]),0,0,0,0,0,0,0,0,0,0,0,0,0};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* ldo_rail[]=
{
    NULL, ldo_rail_b, ldo_rail_c, ldo_rail_d, ldo_rail_e, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ldo_rail_m, ldo_rail_n
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* smps_rail[]=
{
    NULL, smps_rail_b, smps_rail_c, smps_rail_d, smps_rail_e, NULL, NULL, NULL, smps_rail_i, smps_rail_j, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_clk_info_type* clk_info[]=
{
    clk_info_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* bob_rail[]=
{
    NULL, bob_rail_b, NULL , NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type* pstm_info[]=
{
    pstm_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
uint32 rpmh_drv_id[] = {(uint32)RSC_DRV_AOP};

__attribute__((section("pm_dram_reclaim_pool")))
uint8 pm_periph_bitmap[][PM_MAX_BITMAP_ENTRIES] =
{
  /* SID 0x0: pmk7550: Azura */
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
  /* SID 0x1: pm7550: Bonefish */
  {
    0x72, 0xef, 0x38, 0x30,
    0x00, 0x00, 0x40, 0x52,
    0x83, 0x07, 0x02, 0x40,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0xff, 0x0f, 0xff,
    0xff, 0x1f, 0x00, 0x00,
    0xfe, 0xff, 0xff, 0x01,
    0x36, 0xcf, 0x00, 0xc0
    
  },
  /* SID 0x2: pm8550vs: V6 */
  {
    0x72, 0xcf, 0x00, 0x30, 
    0x00, 0x00, 0x40, 0x12, 
    0x00, 0x00, 0x02, 0x40, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x3f, 0x00, 0xfe, 
    0xff, 0x1f, 0x00, 0x00, 
    0x0e, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x00, 0xc0, 
    
  },
  /* SID 0x3: pm8550ve: V8 */
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
  /* SID 0x4: pmr735A: Seco */
  {
    0x72, 0xcf, 0x00, 0x30,
    0x00, 0x00, 0x40, 0x02,
    0x00, 0x00, 0x02, 0x40,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0x00, 0x6e,
    0x0f, 0x00, 0x00, 0x00,
    0xfe, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0xc0
  },
  /* 5: empty */
  {
    0x0,
  },
  /* 6: empty */
  {
    0x0,
  },
  /* 7: empty */
  {
    0x0,
  },
  /* SID 0x8: PMG1110 - SecoJr */
  {
    0x72, 0x4f, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x40,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0x00, 0x3e,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0,
  },
  /* SID 0x9: PMG1110: SecoJr */
  {
    0x72, 0x4f, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x40,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0x00, 0x3e,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0,
  },
  /* A: empty */
  {
    0x0,
  },
  /* B: empty */
  {
    0x0,
  },
  /*SID 0xC: pm8010: Leica2 */
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
  /*SID 0xD: pm8010: Leica2 */
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
