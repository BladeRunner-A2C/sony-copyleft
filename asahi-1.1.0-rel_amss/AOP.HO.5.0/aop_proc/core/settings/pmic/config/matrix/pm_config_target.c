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

$Header: //components/dev/aop.ho/5.0/nvelugu.aop.ho.5.0.Matrix_PMIC_STUB/aop_proc/core/settings/pmic/config/lanai/pm_config_target.c#1 $

when         who            what, where, why
--------     ---            ----------------------------------------------------------
07/14/2023   nvelugu        Created.
07/25/2023   shassinh       Two dummy clock resource added.
12/18/2023   shassinh       Matrix intial version updated based on PG R5p2.
01/04/2024   shassinh       GPIO3A for controlling IMU Sensor external clock.
01/19/2024   shassinh       GPIO_SP feature addeed.
02/12/2024   shassinh       L1C and L1F min/max voltage changed 
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"
#include "pm_config_target.h"

/*
PMIC  NAME                    SID

A     PMK_AZURA_A              0
B     PM_BONEFISH_B            1
C     PM_V6_C                  2
D     PM_V8_D                  3
E                              4
F     PM_V8_F                  5
G                              6
H     PM_KOHALA_H              7
I                              8
J     PM_KOHALA_J              9
K                              A
L                              B
M     PM_LEICA2_M              C
N     PM_LEICA2_N              D
*/

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type bob_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3008,  .MaxVoltage = 3960,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 30,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // BOB1 BOB 1
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,   .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1B PCIE_2_CORE 0p88 
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 8,    .MinVoltage = 1170,  .MaxVoltage = 1370,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // L2B PX11, Azura VDDA
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 32,   .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // L3B 1.2V VDDIO PX14, PX7xx
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 80,   .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L4B Cam_DVDD_LR, 1p8 camera loads.
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,    .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L5B SDEx_Card_VDD2_1p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 80,   .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD,  .Reserved = 0}, // L6B Sensor VDD 1p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 72,   .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP,  .Reserved = 0}, // L7B 1p8 IO rail,VDD_QFPROM
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 16,   .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L8B eUSB HS core 0.9V
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 40,   .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L9B USBSS_DP1 core 0.9V
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 56,   .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L10B PCIE_1_CORE 0p88 
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,   .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L11B nRF52832_VDD, MEMS_DMIC_VDD_ALT
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 184,  .MinVoltage = 2700,  .MaxVoltage = 3304,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L12B SDExCARD_VDD_3P3, SDCARD_VDD1_alt
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 184,  .MinVoltage = 2504,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L13B UFS_VCC
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 56,   .MinVoltage = 2504,  .MaxVoltage = 3304,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD,  .Reserved = 0}, // L14B PGG Sensor VDD, 3p304v
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 152,  .MinVoltage = 2700,  .MaxVoltage = 3304,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L15B VDD_PDPHY, eUSB 3V
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 320,  .MinVoltage = 3304 ,  .MaxVoltage = 3304,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L16B VDD_A 3p3 rail.
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,    .MinVoltage = 1504,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L17B Unused
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,    .MinVoltage = 1504,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L18B Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 96,   .MinVoltage = 1800,  .MaxVoltage = 3304,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L19B SDCard Level shifter, 3V/ 1.8V config
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,    .MinVoltage = 1504,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L20B Unused
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,    .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L21B Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 288,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L22B CAM_OG_AVDD, 2p8v
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 288,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L23B QCT_CAM5_AVDD, 2p8v
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,    .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN,  .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // proxy rail
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_c[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 1140,  .MaxVoltage = 1280,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1C UFS_VCCQ, 1p2v
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 80,  .MinVoltage = 904,   .MaxVoltage = 904,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR,  .Reserved = 0}, // L2C LPDDR5X_VDD2L_ALT
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3C VDD_A_UFS_0_CORE, 0p912
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 40,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // L1D PHY VDDA 1p2V
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2D VDD_A_PCIE_0_CORE, 0p88v
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 880,   .MaxVoltage = 912,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3D VDD_A_USBSSDP_0p9
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_f[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 880,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0,  .VoltStepperExtraDownTime = 0,  .VoltDischargeTime = 0,  .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L1F 0.9V PHY, QREF_0p88
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 540,  .MaxVoltage = 848,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L2F VDD_LPI_MX, 0p752
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 352,  .MaxVoltage = 848,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L3F VDD_LPI_CX, 0p728
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_m[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 48,   .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1M CAM DVDD RFC2, 1p2v 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 104,  .MinVoltage = 1104,  .MaxVoltage = 1104,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2M Cam 1.05V DVDD1 RFC3/1,
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 256,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3M Cam AVDD3 RFC3,  2p8v
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 120,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L4M Cam AVDD1 RFC1,  2p8v
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 152,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L5M Cam AVDD2 RFC2, 2p8v
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 96,   .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L6M Cam AVDD0 RFC2, 2p8v
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 88,   .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7M Cam VCM,  2p8v
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_n[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 80,   .MinVoltage = 1140,  .MaxVoltage = 1260,  .EnableFixedTime = 300,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1N CAM3, DOVDD, 1p2v
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,    .MinVoltage = 1104,   .MaxVoltage = 1104,  .EnableFixedTime = 300,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2N OV64B_DVDD_R 1p104v.
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 256,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300,   .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3N Camera AVDD, 2p8 v
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 256,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L4N OG01A1B_AVDD, 2p8v
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 72,   .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L5N CAM AVDD1 FFC2, 2p8v
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 96,   .MinVoltage = 2960,  .MaxVoltage = 2960,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L6N OC0TA1B_AVDD, 2p96
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 88,   .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7N Cam_AVDD, 2p8v
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1856,  .MaxVoltage = 2040,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S1B HV SUBreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1216,  .MaxVoltage = 1408,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S2B MV SUBreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,   .MaxVoltage = 852,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S3B VDD_MM
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,     .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S4B VDD_MM Ganged
 {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,     .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S5B VDD_MM Ganged 
 {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,   .MaxVoltage = 852,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S6B VDD_DISP_CX
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_c[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 1052,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // S1C VDD_NSP1_Ganged_with_S6C, 0p856v
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 640,  .MaxVoltage = 1000,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // S2C VDD_EBI, parent_of_VDD_LPI_CX, 0p892v
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 570,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR,  .Reserved = 0}, // S3C LPDDR5X_VDDQ, VDD_IO_EBI, 0p504v
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 904,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // S4C VDD_NSP2
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 904,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S5C VDD_NSP2_Ganged_with_S4C
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 1052,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC,  .Reserved = 0}, // S6C VDD_NSP1
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 904,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S1D VDD_GFX_Ganged_with_S7D
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 904,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S2D VDD_GFX_GANGED_with_S7D
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 540,  .MaxVoltage = 884,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S3D VDD_GFX_MX_C
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 540,  .MaxVoltage = 884,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S4D VDD_MX_C
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 920,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANRF, .Reserved = 0}, // S5D WCN785x_WLCX_0p9
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 880,  .MaxVoltage = 1040,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S6D LV_SUBreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 904,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S7D VDD_GFX
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 904,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S8D VDD_GFX_Ganged_with_S7D
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_f[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,   .MaxVoltage = 1052,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S1F VDD_APC0, 0p728
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,   .MaxVoltage = 1050,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S2F Ganged_with_S1F, VDD_APC0
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 504,   .MaxVoltage = 884,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S3F VDD_MX_A
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1080,  .MaxVoltage = 1100,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S4F VDD_PX1, LPDDR5X_VDD2H,1p1
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,   .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 904,   .MaxVoltage = 904,   .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S5F LPDDR5X_VDD2L, 0p904v
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,   .MaxVoltage = 1050,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S6DrvF VDD_CX, VDD_D_EBI_x
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,     .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S7F VDD_APC1
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,     .MaxVoltage = 0,     .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_8X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S8F VDD_APC1_Ganged
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_clk_info_type clock_info_a[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = 0,                  .AlwaysOn =  0,      .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,   .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//CLK_DIST *not supported
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = 0,                  .AlwaysOn =  0,      .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,   .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = 0,                  .AlwaysOn =  0,      .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,   .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK1_RF  WCN clock
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK2_RF  Unused
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK3_RF  Unused
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK4_RF  Unused
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK5_RF  Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC,    .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK6_LN  vrm.xob
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK7_LN  Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,     .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS,   .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK8_LN  UFS Clock 
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK9_LN  Unused
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY  
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // CLK11_DIV  
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // EMPTY  
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF,  .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_WLANRF, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0}, // SLEEP_CLK1 
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = 0,                  .AlwaysOn =  0,      .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//Dummy
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = 0,                  .AlwaysOn =  0,      .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          ,  .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//Dummy 
};

/*Name, PmicIndex, PeriphType, PeriphId, AccessAllowed, SlaveId, BaseAddr, RsrcCategory, EnableAddrOff, EnableFixedTime, EnableSeqType, ModeAddrOff, ModeFixedTime, ModeSeqType,
  VoltAddrOff, VoltFixedTime, VoltSeqType, MaxVoltage, DrvOwnMask, Reserved*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_target_rsrc_info_type target_rsrc_info[] =
{
 {"vrm.apc0", 0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x5, 0x9C00, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
 {"vrm.apc1", 0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x5, 0xAE00, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
 { "vreg.sp", 0, PM_VRM_PERIPH_VREG, 1, {PM_ACCESS_ALLOWED, 0x1, 0x3E00, VRM_RSRC_XO_BUFFER, 0x80, 420, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC,  0}},
 {"gpio.sp", 0, PM_VRM_PERIPH_GPIO, 7, { PM_ACCESS_ALLOWED, 0x1, 0x8E00, VRM_RSRC_XO_BUFFER, 0x46, 20,  VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC, 0 }},
 {"bclplmb0", 0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x1, 0x4800, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
 {"bclplmh0", 0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x7, 0x4800, VRM_RSRC_LOCAL,     0x00, 0,   VRM_NO_PMIC_SEQ,    0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
 {"gpioa3",  0, PM_VRM_PERIPH_GPIO, 3, {PM_ACCESS_ALLOWED, 0x0, 0xBA00, VRM_RSRC_XO_BUFFER, 0x46, 300, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_AUD, 0}},
 //{"rclkha1", 0, PM_VRM_PERIPH_CLK,  5, {PM_ACCESS_ALLOWED, 0x0, 0x5400, VRM_RSRC_REGULATOR, 0x45, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_MDMS, 0}},
 
};

pm_vrm_pstm_rsrc_info_type pstm_a[] =
{
  {.pbs_name = "vrm.aoss", .LowVal = 0x01, .HighVal = 0x02, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AOP ,                     .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-AOSS_Sleep 1-AOSS_Wake
  {.pbs_name = "vrm.soc",  .LowVal = 0x03, .HighVal = 0x04, .SettlingTime = 900, .DrvOwnMask = PM_DRV_DDR|PM_DRV_TZ|PM_DRV_AUD, .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-SOC_Sleep 1-SOC_Wake
//{.pbs_name = "vrm.wlan", .LowVal = 0x06, .HighVal = 0x05, .SettlingTime = 900, .DrvOwnMask = PM_DRV_WLANRF,                   .DefaultVal = 0, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-WLAN_WA_DISENGAGE 1- WLAN_ENGAGE
};

uint32 num_of_target_rsrc[]= {sizeof(target_rsrc_info)/sizeof(target_rsrc_info[0])};

uint32 num_of_ldo[] = {0,sizeof(ldo_rail_b)/sizeof(ldo_rail_b[0]),sizeof(ldo_rail_c)/sizeof(ldo_rail_c[0]),sizeof(ldo_rail_d)/sizeof(ldo_rail_d[0]),0,sizeof(ldo_rail_f)/sizeof(ldo_rail_f[0]),0,0,0,0,0,0,sizeof(ldo_rail_m)/sizeof(ldo_rail_m[0]),sizeof(ldo_rail_n)/sizeof(ldo_rail_n[0])};
uint32 num_of_smps[] = {0,sizeof(smps_rail_b)/sizeof(smps_rail_b[0]),sizeof(smps_rail_c)/sizeof(smps_rail_c[0]),sizeof(smps_rail_d)/sizeof(smps_rail_d[0]),0,sizeof(smps_rail_f)/sizeof(smps_rail_f[0]),0,0,0,0,0,0,0,0};
uint32 num_of_bob[] = {0,sizeof(bob_rail_b)/sizeof(bob_rail_b[0]),0,0,0,0,0,0,0,0,0,0,0,0};
uint32 num_of_pstm_seq[] = {sizeof(pstm_a)/sizeof(pstm_a[0]),0,0,0,0,0,0,0,0,0,0,0,0,0};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* ldo_rail[] =
{
 NULL, ldo_rail_b, ldo_rail_c, ldo_rail_d, NULL, ldo_rail_f, NULL, NULL, NULL, NULL, NULL, NULL, ldo_rail_m, ldo_rail_n
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* smps_rail[] =
{
 NULL, smps_rail_b, smps_rail_c, smps_rail_d, NULL, smps_rail_f, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_clk_info_type* clk_info[] =
{
  clock_info_a,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* bob_rail[] =
{
 NULL, bob_rail_b, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type* pstm_info[] =
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
  
  /*SID 0x3: pm8550ve: V8  */
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
  
  /*SID 0x4: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  
  /*SID 0x5: pm8550ve: V8  */
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
  
  /*SID 0x6: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  
  /*SID 0x7: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  
  /*SID 0x8: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  
  /*SID 0x9: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  
  /*SID 0xA: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  
  /*SID 0xB: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  
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
  