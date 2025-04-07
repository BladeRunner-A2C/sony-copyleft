/* @file Pmic.c

  Implements the Pmic protocol
  
  Copyright (c) 2011-2023 Qualcomm Technologies, Inc.  All Rights Reserved. 
  Qualcomm Technologies Proprietary and Confidential.
  
*/


/*=============================================================================
                              EDIT HISTORY


 when         who     what, where, why
 --------     ---     -----------------------------------------------------------
 04/18/17     va      Moving target specific call to target file
 04/18/17     va      Added API call to set USB typeC port role in PmicInitialize based on HostModeSupported PCD
 08/19/16     pb      Enabled Test protocol (added QcomTargetLib.h for PRODMODE)
 03/24/16     al      Add keypress support
 03/13/16     ck      Enable PMIC NPA client support
 03/09/16     va      Moved common protocol install to pmic.c
 03/08/16     al      Checking for NpaDxe before initializing PAM   
 07/23/15     al      Refactoring code
 11/12/14     al      Adding core specific DAL initialization
 10/07/13     al      Moving platform config to target
 05/06/13     al      Storing pmic info and FabId
 04/01/13     sm      Added check for BattChgApp UEFI Variable
 03/07/13     dy      Add shutdown path for Liquid if pon trigger is charger
 11/06/12     dy      Add SMB350 Workaround
 10/25/12     al      Moved protocol installation to targets
=============================================================================*/


#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/QcomLib.h>
#include <Library/DebugLib.h>
#include <Library/SerialPortShLib.h>
#include "DALSys.h"
#include "CoreVerify.h"

#include "pm_uefi.h"
#include "pm_pon.h"
#include "pm_appsbl_proc_npa.h"
#include "pm_app_pon.h"
#include "pm_core_utils.h"

/**
  PMIC PROTOCOL interface
 */

#include "Protocol/EFIPmicClkBuff.h"
#include "Protocol/EFIPmicChg.h"
#include "Protocol/EFIPmicVib.h"
#include "Protocol/EFIPmicGpio.h"
#include "Protocol/EFIPmicVreg.h"
#include "Protocol/EFIPmicRTC.h"
#include "Protocol/EFIPmicPwrOn.h"
#include "Protocol/EFIPmicRgbLed.h"
#include "Protocol/EFIPmicVersion.h"
#include "Protocol/EFIPmicHaptics.h"
#include "Protocol/EFIPmicIbb.h"
#include "Protocol/EFIPmicAb.h"
#include "Protocol/EFIPmicUsb.h"
#include "Protocol/EFIPmicPwm.h"
#include "Protocol/EFIPmicTest.h"
#include "Protocol/EFIPmicSdam.h"
#include "Protocol/EFIPmicNpaTest.h"

/*===========================================================================

                VARIABLES DEFINITIONS

===========================================================================*/
extern EFI_QCOM_PMIC_CLKBUFF_PROTOCOL   PmicClkBuffProtocolImplementation;
extern EFI_QCOM_PMIC_CHG_PROTOCOL       PmicChgProtocolImplementation;
extern EFI_QCOM_PMIC_HAPTICS_PROTOCOL   PmicHapticsProtocolImplementation;
extern EFI_QCOM_PMIC_GPIO_PROTOCOL      PmicGpioProtocolImplementation;
extern EFI_QCOM_PMIC_VREG_PROTOCOL      PmicVregProtocolImplementation;
extern EFI_QCOM_PMIC_RTC_PROTOCOL       PmicRtcProtocolImplementation;
extern EFI_QCOM_PMIC_PWRON_PROTOCOL     PmicPwronProtocolImplementation;
extern EFI_QCOM_PMIC_RGB_LED_PROTOCOL   PmicRgbLedProtocolImplementation;
extern EFI_QCOM_PMIC_VERSION_PROTOCOL   PmicVersionProtocolImplementation;
extern EFI_QCOM_PMIC_IBB_PROTOCOL       PmicIbbProtocolImplementation;
extern EFI_QCOM_PMIC_AB_PROTOCOL        PmicAbProtocolImplementation;
extern EFI_QCOM_PMIC_USB_PROTOCOL       PmicUsbProtocolImplementation;
extern EFI_QCOM_PMIC_GENERIC_PROTOCOL   PmicGenericProtocolImplementation;
extern EFI_QCOM_PMIC_PWM_PROTOCOL       PmicPwmProtocolImplementation;
extern EFI_QCOM_PMIC_TEST_PROTOCOL      PmicTestProtocolImplementation;
extern EFI_QCOM_PMIC_SDAM_PROTOCOL      PmicSdamProtocolImplementation;
extern EFI_QCOM_PMIC_NPATEST_PROTOCOL   PmicNpaTestProtocolImplementation;

/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/

EFI_EVENT  ExitBootServicesEvent;
EFI_EVENT  ReadyToBootEvent;

#define ARRAY_LENGTH(x)  (sizeof(x) / sizeof(x[0]))

/* ADCDxe entry point */
EFI_STATUS
EFIAPI
AdcEntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);


/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Local Functions
 * -------------------------------------------------------------------------*/

VOID PmicExitBootServicesCallback(IN EFI_EVENT Event, IN VOID *Context)
{
  pm_exit_cleanup();
}

pm_err_flag_type pm_uefi_exit_init(void)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  /*register for both exitbootservices and readytoboot event*/
  Status = gBS->CreateEventEx (EVT_NOTIFY_SIGNAL,
                               TPL_CALLBACK,
                               PmicExitBootServicesCallback,
                               NULL,
                               &gEfiEventReadyToBootGuid,
                               &ReadyToBootEvent
                              );


  Status = gBS->CreateEventEx(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              PmicExitBootServicesCallback,
                              NULL,
                              &gEfiEventExitBootServicesGuid,
                              &ExitBootServicesEvent
                              );

  CORE_VERIFY(Status == EFI_SUCCESS);

  return PM_ERR_FLAG_SUCCESS;
}


static pm_err_flag_type pm_install_common_protocols(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status         = EFI_SUCCESS;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  Status  = gBS->InstallMultipleProtocolInterfaces(
    &ImageHandle,
    &gQcomPmicGpioProtocolGuid,    &PmicGpioProtocolImplementation,
    &gQcomPmicVregProtocolGuid,    &PmicVregProtocolImplementation,
    &gQcomPmicChgProtocolGuid,     &PmicChgProtocolImplementation,
    &gQcomPmicClkBuffProtocolGuid, &PmicClkBuffProtocolImplementation,
    &gQcomPmicRtcProtocolGuid,     &PmicRtcProtocolImplementation,
    &gQcomPmicPwrOnProtocolGuid,   &PmicPwronProtocolImplementation,
    &gQcomPmicVersionProtocolGuid, &PmicVersionProtocolImplementation,
    &gQcomPmicIbbProtocolGuid,     &PmicIbbProtocolImplementation,
    &gQcomPmicAbProtocolGuid,      &PmicAbProtocolImplementation,
    &gQcomPmicRgbLedProtocolGuid,  &PmicRgbLedProtocolImplementation,
    &gQcomPmicUsbProtocolGuid,     &PmicUsbProtocolImplementation,
    &gQcomPmicHapticsProtocolGuid, &PmicHapticsProtocolImplementation,
    &gQcomPmicGenericProtocolGuid, &PmicGenericProtocolImplementation,
    &gQcomPmicPwmProtocolGuid,     &PmicPwmProtocolImplementation,
    &gQcomPmicDriverTestProtocolGuid, &PmicTestProtocolImplementation,
    &gQcomPmicSdamProtocolGuid,    &PmicSdamProtocolImplementation,
    &gQcomPmicNpaTestProtocolGuid, &PmicNpaTestProtocolImplementation,   
    NULL
    );

  err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_FAILURE;

  return err_flag;
}


static pm_err_flag_type pm_pmicdxe_init(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status         = EFI_SUCCESS;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  Status |= pm_install_common_protocols(ImageHandle, SystemTable);
  /* NOTE: Do not add any API calls that can fail between protocol installation apis */
  Status |= pm_install_target_protocols(ImageHandle, SystemTable);
  /* NOTE: If common_protocols are installed successfully, but later
   * target_protocols fails to install, then all the common_protocols
   * must be _uninstalled_ before returning to the caller*/
  if (EFI_SUCCESS == Status)
  {
    /*check for valid PON keypress if PMIC is present*/
    err_flag |= pm_app_pwrkey_long_press_check(PM_PON_PWRKEY_DBNC_CHK_AT_CORE);

    err_flag |= pm_uefi_exit_init();

    err_flag |= pm_post_pmic_initialization(ImageHandle, SystemTable);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FAILURE;
  }

  return err_flag;
}


static pm_err_flag_type pm_pmicdxe_init_stubs(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status         = EFI_SUCCESS;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  EFI_PLATFORMINFO_PLATFORM_TYPE PlatformType;

  DEBUG((EFI_D_ERROR, "PmicDxe: PMIC was not detected \n\r"));

  GetPlatformType(&PlatformType);

  //if platform is not rumi then return failure
  if (PlatformType == EFI_PLATFORMINFO_TYPE_RUMI)
  {
    /*install protocols if RUMI with no PMIC*/
    Status |= pm_install_common_protocols(ImageHandle, SystemTable);
    Status |= pm_install_target_protocols(ImageHandle, SystemTable);
  }
  else
  {
    Status = EFI_DEVICE_ERROR;
  }

  err_flag = (Status == EFI_SUCCESS) ? PM_ERR_FLAG_SUCCESS : PM_ERR_FLAG_FAILURE;

  return err_flag;
}


/*----------------------------------------------------------------------------
 * Global Functions
 * -------------------------------------------------------------------------*/


/**
  PmicInitialize ()

  @brief
  Init implementation of EFI_QCOM_PMIC_CLIENT_DEVICE_PROTOCOL
 */
EFI_STATUS
PmicInitialize(
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_STATUS AdcStatus = EFI_SUCCESS;

  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  /* initialize DAL to use DALSYS services like Malloc etc. */
  DALSYS_InitMod(NULL);

  pm_utils_start_timer();
  /* Initialize the PMIC Library */
  err_flag = pm_init();

  if (err_flag == PM_ERR_FLAG_SUCCESS)
  {
    err_flag = pm_pmicdxe_init(ImageHandle, SystemTable);
    pm_utils_get_time("pm_pmicdxe_init");
  }
  else if (err_flag == PM_ERR_FLAG_FAILURE)
  {
    /*PMIC not detected*/
    err_flag = pm_pmicdxe_init_stubs(ImageHandle, SystemTable);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FAILURE;
  }

#ifdef FEATURE_XBOOT
  err_flag |= pm_app_pon_pshold_cfg(PM_APP_PON_CFG_NORMAL_SHUTDOWN);
#endif /* FEATURE_XBOOT */

  Status = (err_flag == PM_ERR_FLAG_SUCCESS) ? EFI_SUCCESS : EFI_DEVICE_ERROR;

  AdcStatus = AdcEntryPoint(ImageHandle, SystemTable);
  pm_utils_get_time("AdcEntryPoint");
  if (AdcStatus != EFI_SUCCESS) 
  {
    DEBUG((EFI_D_ERROR, "PmicDxe: Unable to install ADC protocol handler \n\r"));
  }

  return Status;
}


