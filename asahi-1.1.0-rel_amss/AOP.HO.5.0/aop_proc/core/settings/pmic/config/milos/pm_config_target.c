/*! \file pm_config_target.c
 *
 *  \brief This file contains customizable target specific driver settings & PMIC registers.
 *         This file info is taken from Target Component Resource Specific Settings from PDM
 *         that is maintained for each of the targets separately.
 *
 *  &copy; Copyright 2013 - 2023 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/dev/aop.ho/5.0/kuam.aop.ho.5.0.milos_bsp1/aop_proc/core/settings/pmic/config/lanai/pm_config_target.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/17/14   kt      Created.
09/07/23   bde     PGA R3_0 code drop
11/24/23   bde     PGA R5_2 Code drop
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"
#include "pm_config_target.h"

/*
PMIC  Name     SID                
A     Azura     0                 
B     Bonefish  1                 
C     voodoo6   2                 
D     SecoJr    3 [EBI_Backup]     
E     Seco      4                 
F     Nalo      5                  
G     SecoJr    6 [VDD2/VDD2H_ALT] 
H               7                 
I               8                 
J               9                 
K     SecoJr    A [Ganges/IoT]      
L     SecoJr    B [Ganges/IoT]      
M               C                 
N               D                 
*/

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANRF, .Reserved = 0}, // L1B FMD 1p8 IO_LDO
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,    .Reserved = 0}, // L2B 0p9 Refgen
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L3B USBSSDP 0p9
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,    .Reserved = 0}, // L4B 1p2 Refgen
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,    .Reserved = 0}, // L5B 1p2 IO, PX10, PX14
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,     .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L6B Azura VDDA
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,    .Reserved = 0}, // L7B 1p8 IO
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L8B Tambora_VDD_CP check LPM requirement
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L9B Touch/AMOLED 1p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD,    .Reserved = 0}, // L10B Sensor 1p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L11B VDD_UIM1_ESIM
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 2400,  .MaxVoltage = 3300,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L12B UFS_VCC, 2.504V for UFS3.1 & 2.952V for UFS 2.2
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 2700,  .MaxVoltage = 3300,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L13B SDCARD_VDD1
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3300,  .MaxVoltage = 3304,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WPSS,   .Reserved = 0}, // L14B Evros PA_2G_3p3
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3300,  .MaxVoltage = 3304,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WPSS,   .Reserved = 0}, // L15B Evros PA_5G_3p3
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3008,  .MaxVoltage = 3008,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD,    .Reserved = 0}, // L16B TMD2755_VDD3
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3104,  .MaxVoltage = 3104,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L17B EUSB_VDD_3P0/EUSB_REPEATER
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANRF, .Reserved = 0}, // L18B AV91C_VDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3000,  .MaxVoltage = 3000,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L19B AMOLED_VTDR6130_VCI
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1620,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L20B UIM_0_VDD/UIM0_LS
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1620,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L21B UIM_1_VDD/UIM1_LS
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3200,  .MaxVoltage = 3200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L22B TOUCH_GT9916_AVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1650,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L23B SDC_LS
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1650,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L24B Dummy
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_c[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 320,  .MaxVoltage = 1004,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L1C A_EBI
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 320,  .MaxVoltage = 650,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // L2C LPDDR4X/5_VDDQ
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 320,  .MaxVoltage = 912,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L3C LPI_CX
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_e[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,      .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1E Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 800,  .MaxVoltage = 800,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L2E SMR546_VDDAL
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 588,  .MaxVoltage = 800,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L3E SMR546_VDD_CX
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1776, .MaxVoltage = 1776,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L4E SMR546_VDDAH
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1200, .MaxVoltage = 1200,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L5E SMR546_VDDAM
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 880,  .MaxVoltage = 912,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L6E SMR546_VDD_MX
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,      .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7E Unused
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_f[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 852,  .MaxVoltage = 950,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L1F SDR_VDD_MX
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 751,  .MaxVoltage = 824,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L2F SDR_VDDAL
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 650, .MaxVoltage = 880,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANRF, .Reserved = 0}, // L3F WCN645x_WLAN_CXMX_0P8
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1700, .MaxVoltage = 1950,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L4F UFS_VCCQ2_1p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1140, .MaxVoltage = 1260,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L5F UFS_VCCQ_1p2
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1200, .MaxVoltage = 1200,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS,   .Reserved = 0}, // L6F AMOLED_VTDR6130_DDIC_VDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1080, .MaxVoltage = 1350,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L7F SDR_VDDAM
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1100, .MaxVoltage = 1320,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L8F QET7100_1/0_VDD_1P2, RBSC BYP??
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 870,  .MaxVoltage = 970,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR,    .Reserved = 0}, // L9F LPDDR5_VDD2L
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1500, .MaxVoltage = 1800,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L10F SDR435_VDDAH
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 320,  .MaxVoltage = 864,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS,   .Reserved = 0}, // L11F SDR_VDD_CX
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 480,  .MaxVoltage = 884,    .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,    .Reserved = 0}, // L12F LPI_MX
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1800,  .MaxVoltage = 2080,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // S1B HV Buck
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1256,  .MaxVoltage = 1408,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // S2B MV Buck
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 880,   .MaxVoltage = 1040,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // S3B LV Buck
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,   .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // S4B VDD_CX
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,     .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S5B VDD_CX_Ganged
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF, .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,     .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S6B APC0
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_c[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S1C APC1
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S2C APC1_Ganged
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1010, .MaxVoltage = 1170,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR,  .Reserved = 0}, // S3C LPDDR4X_VDD2/LPDDR5_VDD2H, APC1_Ganged for AD SKU
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // S4C VDD_MODEM
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // S5C MX
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // S6C VDD_GFX
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1010,  .MaxVoltage = 1170,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S1D A_EBI_Backup
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_e[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 936,  .MaxVoltage = 1306,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // S1E RF MV Parent
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 382,  .MaxVoltage = 1352,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // S2E RF LV parent
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,    .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S3E Unused
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_g[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1010, .MaxVoltage = 1170,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S1G LPDDR4X_VDD2_ALT/LPDDR5_VDD2H_ALT
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_k[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANBB, .Reserved = 0}, // S1K WCN788X_BT_CXMX_0p9
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_l[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANBB, .Reserved = 0}, // S1L WCN788X_VDDD_WLMX_0P9
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type bob_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3008,  .MaxVoltage = 3960,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 30,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // BOB1 BOB1A
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_clk_info_type clk_info_a[]=
{
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//CLK_DIST *not supported
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK1_RF  Wlan Clock
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_MDMS  , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK2_RF  mmW
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_MDMS  , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK3_RF  Sub6
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_MDMS  , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK4_RF  Unused
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS  , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK5_RF  Unused
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC   , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK6_LN  vrm.xob
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS  , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK7_LN  NFC
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS  , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK8_LN  OPT UFS CLK
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK9_LN  OPT Wingmate
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// EMPTY  
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS  , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// CLK11_DIV  
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// EMPTY  
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},// SLEEP_CLK1
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//Dummy
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0            , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//Dummy    
};


/*Name, PmicIndex, PeriphType, PeriphId, AccessAllowed, SlaveId, BaseAddr, RsrcCategory, EnableAddrOff, EnableFixedTime, EnableSeqType, ModeAddrOff, ModeFixedTime, ModeSeqType, 
  VoltAddrOff, VoltFixedTime, VoltSeqType, MaxVoltage, DrvOwnMask, Reserved*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_target_rsrc_info_type target_rsrc_info[] = 
{
//  {"rclkha2", 0, PM_VRM_PERIPH_CLK,  5, {PM_ACCESS_ALLOWED, 0x0, 0x5500, VRM_RSRC_REGULATOR, 0x45, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_MDMS, 0}},
  {"bclplmb0",    0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x1, 0x4800, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},           //BCLPLM B
  {"bclplmh0",    0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x7, 0x4800, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},           //BCLPLM H
  {"vrm.apc0",    0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x1, 0xAB00, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},           //APC0 CLX base
  {"vrm.apc1",    0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x2, 0x9C00, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},           //APC1 CLX base
  {"gpiof1",      0, PM_VRM_PERIPH_GPIO, 1, {PM_ACCESS_ALLOWED, 0x5, 0x8800, VRM_RSRC_XO_BUFFER, 0x44, 200, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_WLANRF, 0}}, //iPA 2p2 Halo Buck enable control
  {"gpiof2",      0, PM_VRM_PERIPH_GPIO, 2, {PM_ACCESS_ALLOWED, 0x5, 0x8900, VRM_RSRC_XO_BUFFER, 0x44, 200, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_WLANRF, 0}}, //iPA 2p2 Halo Buck mode control
  
};
                                                  
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type pstm_a[] = 
{
  {.pbs_name = "vrm.aoss", .LowVal = 0x01, .HighVal = 0x02, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AOP ,                                  .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-AOSS_Sleep 1-AOSS_Wake
  {.pbs_name = "vrm.soc",  .LowVal = 0x03, .HighVal = 0x04, .SettlingTime = 900, .DrvOwnMask = PM_DRV_DDR|PM_DRV_TZ|PM_DRV_AUD|PM_DRV_MDMS , .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-SOC_Sleep 1-SOC_Wake
  //{.pbs_name = "vrm.wlan", .LowVal = 0x06, .HighVal = 0x05, .SettlingTime = 900, .DrvOwnMask = PM_DRV_WLANBB,                              .DefaultVal = 0, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-WLAN_WA_DISENGAGE 1- WLAN_ENGAGE
};

uint32   num_of_target_rsrc[]= {sizeof(target_rsrc_info)/sizeof(target_rsrc_info[0])};

uint32   num_of_ldo[]        = {0, sizeof(ldo_rail_b)/sizeof(ldo_rail_b[0]), sizeof(ldo_rail_c)/sizeof(ldo_rail_c[0]), 0, sizeof(ldo_rail_e)/sizeof(ldo_rail_e[0]), sizeof(ldo_rail_f)/sizeof(ldo_rail_f[0]), 0, 0, 0, 0, 0, 0, 0, 0};
uint32   num_of_smps[]       = {0, sizeof(smps_rail_b)/sizeof(smps_rail_b[0]), sizeof(smps_rail_c)/sizeof(smps_rail_c[0]), sizeof(smps_rail_d)/sizeof(smps_rail_d[0]),  sizeof(smps_rail_e)/sizeof(smps_rail_e[0]), 0, sizeof(smps_rail_g)/sizeof(smps_rail_g[0]), 0, 0, 0, sizeof(smps_rail_k)/sizeof(smps_rail_k[0]), sizeof(smps_rail_l)/sizeof(smps_rail_l[0])};
uint32   num_of_bob[]        = {0, sizeof(bob_rail_b)/sizeof(bob_rail_b[0]), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint32   num_of_pstm_seq[]   = {sizeof(pstm_a)/sizeof(pstm_a[0]),0,0,0,0,0,0,0,0,0,0,0,0,0};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* ldo_rail[]=
{
    NULL, ldo_rail_b, ldo_rail_c, NULL, ldo_rail_e, ldo_rail_f, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* smps_rail[]=
{
    NULL, smps_rail_b, smps_rail_c, smps_rail_d, smps_rail_e, NULL, smps_rail_g, NULL, NULL, NULL, smps_rail_k, smps_rail_l, NULL, NULL
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
  /* SID 0x3: SecoJr EBI Backup */
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
  /* SID 0x4: pmr735a: Seco */
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
  /*  SID 0x5: Nalo */
  {
	0x72, 0x4f, 0x00, 0x30, 
	0x00, 0x00, 0x40, 0x02, 
	0x00, 0x00, 0x02, 0x40, 
	0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 
	0xfe, 0x1f, 0x00, 0x00, 
	0x02, 0x00, 0x00, 0xc0
  },
  /* SID 0x6: SecoJr VDD2/VDD2H backup */
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
  /* 7: EMPTY */
  PM_DEFAULT_PERIPH_BITMAP,
  /* 8: EMPTY*/
  PM_DEFAULT_PERIPH_BITMAP,
  /* 9: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  /* SID 0xA: SecoJr Ganges/IOT */
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
  /* SID 0xB: SecoJr Ganges/IOT */
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
  /* SID 0xC: EMPTY */
  PM_DEFAULT_PERIPH_BITMAP,
  /* SID 0xD: EMPTY */
  PM_DEFAULT_PERIPH_BITMAP,

};

/*Min poll time[in us] threshold in vrm for regulators*/
__attribute__((section("pm_dram_reclaim_pool")))
uint32 min_settling_time_thr[] = {(uint32)600};
