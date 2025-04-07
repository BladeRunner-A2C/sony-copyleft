#
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

$Header: $
 Version : 1.0
 
 when       who     what, where, why
--------   	---     ----------------------------------------------------------
01/23/23	bde		Camano initial version based on PG R3P0
04/05/23	bde		BCL peripheral alias added, Bitmaps updated, WLAN INRUSH removed
05/06/23	bde		Dummy clk peripherals added to avoid out of bound access in stub
07/06/23	bde		PG R6: vregWDT changed to 4X, HV buck Vmin lowered, LVN1200 vmin 320mv as applicable
20/07/23	bde		All 8mv LDO HR is updated to 16mv, recommendation from PMIC SYS
21/07/23	bde		HV,MV, LV Buck, L10B Minmode updated.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_config_interface.h"
#include "pm_config_target.h"

/*
PMIC  Name      		SID
A     Azura     		0
B     Bonefish  		1
C     voodoo6   		2
D     voodoo6   		3
E     Seco      		4
F     NaloJr    		5 
G               		6
H     Sculpin|Kohala    7
I               		8
J               		9
K               		A
L               		B
M     Leica2    		C
N     Leica2    		D
*/


__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 880,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L1B QLINK_0p9
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 880,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS|PM_DRV_ARC, .Reserved = 0}, // L2B QREF_0p9
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 880,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3B USBSSDP_0p9
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS|PM_DRV_ARC, .Reserved = 0}, // L4B QREF_1p2
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // L5B PX14, PX10
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1170,  .MaxVoltage = 1370,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // L6B PX11, Azura VDDA
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 120,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // L7B 1.8v AON, Under HV load
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L8B VDD_UIM1_ESIM
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L9B AMOLED_VDDIO, TOUCH_DVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD, .Reserved = 0}, // L10B Sensor only loads
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L11B DMIC
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 168,  .MinVoltage = 2400,  .MaxVoltage = 3300,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L12B UFS_VCC, EMMC_VCC
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 184,  .MinVoltage = 2700,  .MaxVoltage = 3300,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L13B SDCARD_VDD1,_UHS1
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 2650,  .MaxVoltage = 2940,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L14B SPXT_VDD, 2.7v RF Switch
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1504,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L15B Unused, ALT for Evros check enablement plan.
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 3008,  .MaxVoltage = 3008,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AUD, .Reserved = 0}, // L16B 3008mv touch sensor load
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 200,  .MinVoltage = 3104,  .MaxVoltage = 3104,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L17B eUSB repeater
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 16,  .MinVoltage = 2800,  .MaxVoltage = 2800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANRF, .Reserved = 0}, // L18B AV91C_VDD, RTC_VDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 96,  .MinVoltage = 3000,  .MaxVoltage = 3000,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L19B AMOLED_VCI
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 232,  .MinVoltage = 1620,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L20B UIM0_VDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 350,  .MinVoltage = 1620,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_DIS, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L21B UIM1_VDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 200,  .MinVoltage = 3200,  .MaxVoltage = 3200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L22B Touch AVDD
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 1650,  .MaxVoltage = 3544,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L23B SDC LS, Card Side IO 1.8/3.0V scalable
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 1800,  .MaxVoltage = 1800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L24B VREG 1P8 PX0, Dummy
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_c[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 96,  .MinVoltage = 320,  .MaxVoltage = 650,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // L1C LP4/5 VDDQ, IO_EBI
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 320,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L2C LPI_CX
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 480,  .MaxVoltage = 884,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // L3C LPI_MX
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 870,  .MaxVoltage = 970,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // L1D LP5_VDD2L, Lp5 only load
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 1140,  .MaxVoltage = 1950,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2D UFS_VCCQ for  UFS3.1 1p2, UFS_VCCq2 UFS2.2 1p8, EMMC VCCQ 1p8 only compute
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3D AMOLED_DDIC_VDD
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_e[] =
{
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1E Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 32,  .MinVoltage = 800,  .MaxVoltage = 800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L2E SMR_VDDAL
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 144,  .MinVoltage = 588,  .MaxVoltage = 800,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L3E SMR_CX
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 24,  .MinVoltage = 1776,  .MaxVoltage = 1776,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L4E SMR_VDDAH
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 1200,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L5E SMR_VDDAM
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 880,  .MaxVoltage = 912,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L6E SMR_MX, PHY
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7E Unused
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_f[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 48,  .MinVoltage = 852,  .MaxVoltage = 950, 	.EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L1F SDR_MX, SDR_PHY
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 320,  .MaxVoltage = 864, 	.EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L2F SDR_CX
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 96,  .MinVoltage = 1080,  .MaxVoltage = 1350,	.EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L3F SDR_VDDAM
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 16,   .MinVoltage = 1100,  .MaxVoltage = 1320,	.EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L4F QET 1p2 load
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 72,  .MinVoltage = 751,  .MaxVoltage = 824, 	.EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L5F SDR_VDDAL
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 56,  .MinVoltage = 1500,  .MaxVoltage = 1800,	.EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_MDMS, .Reserved = 0}, // L6F SDR_VDDAH
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  		.EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7F Unused, Power Cycle for MMWR (Compute)
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_m[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 80,  .MinVoltage = 1050,  .MaxVoltage = 1180,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1M RFC UW DVDD 1p104
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 40,  .MinVoltage = 950,  .MaxVoltage = 1150,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2M RFC TELE DVDD 1p056
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 160,  .MinVoltage = 2700,  .MaxVoltage = 2900,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3M RFC UW AVDD 2p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 128,  .MinVoltage = 2700,  .MaxVoltage = 2900,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L4M RFC TELE AVDD 2p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 1700,  .MaxVoltage = 1900,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L5M RFC Wide AVDD2 1p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 168,  .MinVoltage = 2700,  .MaxVoltage = 2900,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L6M RFC Wide AVDD1 2p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 224,  .MinVoltage = 2700,  .MaxVoltage = 3000,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7M RFC TELE, RFC UW VCM, RFC Wide VCM_VDD 2p96
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type ldo_rail_n[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 1050,  .MaxVoltage = 1200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L1N RFC Wide DVDD 1p104
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 64,  .MinVoltage = 950,  .MaxVoltage = 1150,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L2N FFC RGB DVDD1p056
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 168,  .MinVoltage = 1792,  .MaxVoltage = 1980,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L3N RFC UW, TELE, Wide, FFC RGB, Laser AF DOVDD, Flicker Det VDD 1p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 88,  .MinVoltage = 1792,  .MaxVoltage = 1900,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L4N FFC RGB AVDD2 1p8
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 112,  .MinVoltage = 2700,  .MaxVoltage = 2900,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L5N FFC RGB AVDD1 2p8 
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1792,  .MaxVoltage = 3312,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L6N Unused
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 96,  .MinVoltage = 2500,  .MaxVoltage = 3300,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // L7N Laser AF AVDD 2p8
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_b[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1800,  .MaxVoltage = 2040,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S1B HV Subreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1256,  .MaxVoltage = 1408,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S2B MV Subreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 880,  .MaxVoltage = 1040,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S3B LV Subreg
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 2200,  .MaxVoltage = 2200,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_WLANRF, .Reserved = 0}, // S4B WCN_IPA_2p2 load 
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S5B MX_A
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 352,  .MaxVoltage = 904,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S6B APC0
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_c[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S1C VDD_CX
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S2C VDD_CX_Ganged
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S3C VDD_CX_Ganged
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S4C VDD_MODEM
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S5C VDD_MODEM Ganged
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S6C MX_C
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_d[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_NPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S1D VDD_GFX
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S2D VDD_GFX_Ganged
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 300,  .MaxVoltage = 1004,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_ARC, .Reserved = 0}, // S3D VDD_A_EBI
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S4D APC1
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S5D APC1_Ganged
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 1010,  .MaxVoltage = 1170,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_DDR, .Reserved = 0}, // S6D LP4x_VDD2, 5_VDD2H, PX1
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type smps_rail_e[] =
{
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 936,  .MaxVoltage = 1306,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S1E SMR 1p2, 0p9 load parent
 {.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_RET_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 382,  .MaxVoltage = 1352,  .EnableFixedTime = 300, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 20, .VoltStepperExtraDownTime = 20, .VoltDischargeTime = 50, .ModeFixedTime = 20,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // S2E SMR 0p8 load parent
 {.AccessAllowed = PM_ACCESS_DISALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_OFF,  .MinMode = PM_LPM_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 0,  .MaxVoltage = 0,  .EnableFixedTime = 0, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 0,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_HLOS, .Reserved = 0}, // S3E Unused
};


__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_vreg_rail_info_type bob_rail_b[] =
{
{.AccessAllowed = PM_ACCESS_ALLOWED,  .RsrcCategory = VRM_RSRC_REGULATOR, .AlwaysOn = PM_ON,  .MinMode = PM_BYP_MODE_VAL, .SafetyHR = 0,  .MinVoltage = 3008,  .MaxVoltage = 3960,  .EnableFixedTime = 500, .EnableStepperWarmUpTime = 0, .VoltFixedUpTime = 0, .VoltFixedDownTime = 0, .VoltStepperExtraUpTime = 0, .VoltStepperExtraDownTime = 0, .VoltDischargeTime = 0, .ModeFixedTime = 30,  .VregReadyEn = PM_SETTLING_EN, .VregReadyErrEn = PM_SETTLING_ERR_EN, .VregWdogTimer = VRM_4X_SETTLING_TIMER, .AopHandling = 0, .VoltSeqType = VRM_GENERIC_SEQ, .EnableSeqType = VRM_GENERIC_SEQ, .ModeSeqType = VRM_GENERIC_SEQ, .DrvOwnMask = PM_DRV_AOP, .Reserved = 0}, // BOB1 BOB1
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_clk_info_type clk_info_a[]=
{
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//CLK_DIST *not supported
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK1, WCN clock
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK2, MMW clock
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK3, Sub6 clock
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_MDMS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK4
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//RF_CLK5
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_ARC , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//BB_CLK1, vrm.xob 
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//BB_CLK2, NFC Clock
  {.AccessAllowed = PM_ACCESS_ALLOWED,    .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn = PM_OFF, .EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//BB_CLK3, Optional UFS clock. Todo: Check the final PORed
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//BB_CLK4
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = VRM_RSRC_XO_BUFFER, .AlwaysOn =  PM_OFF,.EnableFixedTime = 300,  .EnableSeqType = VRM_GENERIC_SEQ, .Reserved = 0,  .DrvOwnMask = PM_DRV_HLOS, .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//DIV_CLK1
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//EMPTY
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//SLEEP_CLK  
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//Dummy
  {.AccessAllowed = PM_ACCESS_DISALLOWED, .RsrcCategory = 0,                  .AlwaysOn =  0,     .EnableFixedTime = 300,  .EnableSeqType = 0,               .Reserved = 0,  .DrvOwnMask = 0          , .ClkReadyEn = PM_SETTLING_EN, .ClkReadyErrEn = PM_SETTLING_ERR_EN, .ClkWdogTimer = VRM_4X_SETTLING_TIMER, .Reserved1 = 0},//Dummy
};



/*Name, PmicIndex, PeriphType, PeriphId, AccessAllowed, SlaveId, BaseAddr, RsrcCategory, EnableAddrOff, EnableFixedTime, EnableSeqType, ModeAddrOff, ModeFixedTime, ModeSeqType,
  VoltAddrOff, VoltFixedTime, VoltSeqType, MaxVoltage, DrvOwnMask, Reserved*/
__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_target_rsrc_info_type target_rsrc_info[] =
{
//  {"vreg.sp", 0, PM_VRM_PERIPH_VREG, 1, {PM_ACCESS_ALLOWED, 0x1, 0x3E00, VRM_RSRC_XO_BUFFER, 0x80, 420, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC, 0}},
//  {"gpio.sp", 0, PM_VRM_PERIPH_GPIO, 7, {PM_ACCESS_ALLOWED, 0x1, 0x8E00, VRM_RSRC_XO_BUFFER, 0x46, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_SEC, 0}},
  {"rclkha1", 0, PM_VRM_PERIPH_CLK,  5, {PM_ACCESS_ALLOWED, 0x0, 0x5400, VRM_RSRC_REGULATOR, 0x45, 20, VRM_PMIC_WRITE_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_MDMS, 0}},
  {"bclplmb0",    0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x1, 0x4800, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"bclplmh0",    0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x7, 0x4800, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"vrm.apc0",   0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x1, 0xAB00, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
  {"vrm.apc1",   0, PM_VRM_PERIPH_NONE, 0, {PM_ACCESS_ALLOWED, 0x3, 0xA500, VRM_RSRC_LOCAL, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0x00, 0, VRM_NO_PMIC_SEQ, 0, PM_DRV_NONE, 0}},
};

__attribute__((section("pm_ddr_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type pstm_a[] = 
{
  {.pbs_name = "vrm.aoss", .LowVal = 0x01, .HighVal = 0x02, .SettlingTime = 900, .DrvOwnMask = PM_DRV_AOP ,                                  .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-AOSS_Sleep 1-AOSS_Wake
  {.pbs_name = "vrm.soc",  .LowVal = 0x03, .HighVal = 0x04, .SettlingTime = 900, .DrvOwnMask = PM_DRV_DDR|PM_DRV_TZ|PM_DRV_AUD|PM_DRV_MDMS , .DefaultVal = 1, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-SOC_Sleep 1-SOC_Wake
//  {.pbs_name = "vrm.wlan", .LowVal = 0x06, .HighVal = 0x05, .SettlingTime = 900, .DrvOwnMask = PM_DRV_WLANRF,                                .DefaultVal = 0, .AccessAllowed = PM_ACCESS_ALLOWED , .RsrcCategory = VRM_RSRC_PSTM, .EnableSeqType = VRM_GENERIC_SEQ }, //0-WLAN_WA_DISENGAGE 1- WLAN_ENGAGE
};

uint32 num_of_target_rsrc[]= {sizeof(target_rsrc_info)/sizeof(target_rsrc_info[0])} ;

uint32 num_of_ldo[] = {0,sizeof(ldo_rail_b)/sizeof(ldo_rail_b[0]),sizeof(ldo_rail_c)/sizeof(ldo_rail_c[0]),sizeof(ldo_rail_d)/sizeof(ldo_rail_d[0]),sizeof(ldo_rail_e)/sizeof(ldo_rail_e[0]),sizeof(ldo_rail_f)/sizeof(ldo_rail_f[0]),0,0,0,0,0,0,sizeof(ldo_rail_m)/sizeof(ldo_rail_m[0]),sizeof(ldo_rail_n)/sizeof(ldo_rail_n[0])};

uint32 num_of_smps[] = {0,sizeof(smps_rail_b)/sizeof(smps_rail_b[0]),sizeof(smps_rail_c)/sizeof(smps_rail_c[0]),sizeof(smps_rail_d)/sizeof(smps_rail_d[0]),sizeof(smps_rail_e)/sizeof(smps_rail_e[0]),0,0,0,0,0,0,0,0,0};

uint32 num_of_bob[] = {0,sizeof(bob_rail_b)/sizeof(bob_rail_b[0]),0,0,0,0,0,0,0,0,0,0,0,0};

uint32   num_of_pstm_seq[]   = {sizeof(pstm_a)/sizeof(pstm_a[0]),0,0,0,0,0,0,0,0,0,0,0,0,0};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* ldo_rail[] =
{
 NULL, ldo_rail_b, ldo_rail_c, ldo_rail_d, ldo_rail_e, ldo_rail_f, NULL, NULL, NULL, NULL, NULL, NULL, ldo_rail_m, ldo_rail_n
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* smps_rail[] =
{
 NULL, smps_rail_b, smps_rail_c, smps_rail_d, smps_rail_e, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_vreg_rail_info_type* bob_rail[] =
{
 NULL, bob_rail_b, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_clk_info_type* clk_info[]=
{
    clk_info_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};



__attribute__((section("pm_dram_reclaim_pool")))
pm_vrm_pstm_rsrc_info_type* pstm_info[] =
{
    pstm_a, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
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
  /* SID 0x3: pm8550vs: V6 */
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

  /* SID 0x5: pmr735d: NaloJr */
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
  /*SID 0x6: empty */
  PM_DEFAULT_PERIPH_BITMAP,
  /*SID 0x7: pm8550b | pm7550b */
  {
    
	0x72, 0xdf, 0xd0, 0xf3,
	0xe2, 0x7f, 0x41, 0x76,
	0x80, 0xc1, 0x02, 0x40,
	0x00, 0x01, 0x0f, 0x00,
	0x00, 0xff, 0x0f, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x07, 0x67,

  },
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