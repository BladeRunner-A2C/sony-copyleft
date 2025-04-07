/*
===========================================================================
*/
/**
  @file swsys_env_uefi_dispctrl.c

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/14/17   jh      Initial revision.

  ====================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIDisplayPwrCtrl.h>

#include "swsys_env_uefi_dispctrl.h"
#include "../swsys_logger/swsys_logger.h"
#include "../swsys_app_sync/swsys_app_sync.h"

/*=========================================================================
      Variables
==========================================================================*/
EFI_QCOM_DISPLAY_PWR_CTRL_PROTOCOL *DispCtrl = NULL;

void *DisplayClockLock = NULL;

/* =========================================================================
**  Functions
** =========================================================================*/

bool swsys_init_dispctrl_uefi()
{
  EFI_STATUS status = EFI_SUCCESS;
  status = gBS->LocateProtocol(&gQcomDisplayPwrCtrlProtocolGuid,
                               NULL,
                               (VOID **)&DispCtrl);
  if (status != EFI_SUCCESS)
  {
    swsys_error("ERROR: DispPwrCtrl protocol load failed\n");
    return false;
  }

  swsys_debug("DispPwrCtrl protocol loaded\n");

  //Initialize named lock
  swsys_thread_lock_init(&DisplayClockLock, QUESTCLOCK_LOCK_NAME);
  
  return true;
}

bool swsys_dispctrl_off_uefi()
{
  EFI_STATUS status = EFI_SUCCESS;

  if (DispCtrl ==  NULL) {
	  return false;
  }

  swsys_info("\nCall Display API: off\n");

  swsys_thread_lock(DisplayClockLock);
  status = DispCtrl->DisplayPanelPowerControl(EFI_DISPLAY_TYPE_PRIMARY, EFI_DISPLAY_POWER_STATE_OFF);
  swsys_thread_unlock(DisplayClockLock);

  if (status != EFI_SUCCESS)
  {
    if (status == EFI_UNSUPPORTED)
    {
      swsys_error("ERROR: Could not change primary display state\n");
    }
    else
    {
      swsys_error("ERROR: Could not change primary display state\n");
      return false;
    }
  }

  swsys_info("\nDisplay off\n");
  return true;
}

bool swsys_dispctrl_on_uefi()
{
  EFI_STATUS status = EFI_SUCCESS;

  if (DispCtrl ==  NULL) {
	  return false;
  }
  swsys_info("\nCall Display API: on\n");

  swsys_thread_lock(DisplayClockLock);
  status = DispCtrl->DisplayPanelPowerControl(EFI_DISPLAY_TYPE_PRIMARY, EFI_DISPLAY_POWER_STATE_ON);
  swsys_thread_unlock(DisplayClockLock);

  if (status != EFI_SUCCESS)
  {
    if (status == EFI_UNSUPPORTED)
    {
      swsys_error("ERROR: Could not change primary display state\n");
    }
    else
    {
      swsys_error("ERROR: Could not change primary display state\n");
      return false;
    }
  }

  swsys_info("\nDisplay on\n");
  return true;
}

