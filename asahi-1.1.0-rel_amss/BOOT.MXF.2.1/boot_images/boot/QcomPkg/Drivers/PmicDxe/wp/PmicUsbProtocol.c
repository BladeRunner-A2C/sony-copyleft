/*! @file PmicUsbProtocol.c 

*  PMIC- USB MODULE RELATED DECLARATION
*  This file contains functions and variable declarations to support 
*  the PMIC USB module.
*
*  Copyright (c) 2015-2021 Qualcomm Technologies, Inc.  All Rights Reserved. 
*  Qualcomm Technologies Inc Proprietary and Confidential.
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
10/24/17   ra      Added new file for TypeC peripheral for PM855B
09/19/17   cs     for SDM855 remvoe unsupported function calls.
12/19/16   sm      Removed PmicIndex from PmicUsbProtocol APIs
06/09/16   sm      Redefined GetOtgStatus API
06/02/16   sm      Added changes to remove support for PMI8998 v1.0
06/01/16   sm      Removed EFI_QCOM_CHARGER_EX_PROTOCOL related changes
05/10/16   sm      Added API to return charger presence
05/09/16   sm      Enabled code inside EFI_PmicUsbEnableOtg()
04/06/16   sm      Completed the API definitions.
04/06/16   sm      Made changes to always assume we have bad PMIv1.0 part 
                   and always run workaround
03/07/16   sm      Added TypeC related APIs (Skeleton)
04/14/15   al      added support for PMI8950 
02/11/15   sv      added support for 8909 and 8916
01/30/15   al      New file.
===========================================================================*/

/*===========================================================================

INCLUDE FILES FOR MODULE

===========================================================================*/

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

#include <Library/DebugLib.h>
#include <Library/QcomBaseLib.h>

#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIPmicSchg.h>
#include <Protocol/EFIPmicUsb.h>

#include "pm_uefi.h"
#include "pm_version.h"
#include "pm_chg.h"

/*===========================================================================

                        GLOBAL DATA DEFINITIONS

===========================================================================*/
STATIC EFI_QCOM_PMIC_SCHG_PROTOCOL  *PmicSchgProtocol = NULL;
STATIC UINT32                       PmicDeviceIndex   = 0xFF;
STATIC UINT64                             gPortRoleSetTimeInmS   = 0;

#define PMIC_ALL_LAYER_REV_1 1
#define PMIC_METAL_REV_0 0
/*===========================================================================
EXTERNAL FUNCTION DECLARATIONS
===========================================================================*/

STATIC BOOLEAN IsSmbSupported(void)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_CHIPINFO_PROTOCOL *ChipInfoProtocol = NULL;
  EFIChipInfoFamilyType ChipSetFamily = EFICHIPINFO_FAMILY_UNKNOWN;
  BOOLEAN SmbSupported = FALSE;

  Status = gBS->LocateProtocol(&gEfiChipInfoProtocolGuid, NULL, (VOID **)&ChipInfoProtocol);
  if ((EFI_SUCCESS == Status) && (ChipInfoProtocol != NULL))
  {
    Status |= ChipInfoProtocol->GetChipFamily(ChipInfoProtocol, &ChipSetFamily);
    if ((EFI_SUCCESS == Status) && (EFICHIPINFO_FAMILY_MAKENA == ChipSetFamily))
    {
      SmbSupported = TRUE;
    }
  }
  return SmbSupported;
}

EFI_STATUS EFIPmicUsbInit( VOID )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  if(NULL == PmicSchgProtocol)
  {
    Status = gBS->LocateProtocol(&gQcomPmicSchgProtocolGuid, NULL, (VOID **)&PmicSchgProtocol);
    if(EFI_SUCCESS == Status && NULL != PmicSchgProtocol)
    {
      UINT8 activePort   = 0;
      Status = PmicSchgProtocol->GetActivePort(&activePort);
      PmicDeviceIndex = activePort;
    }
  }

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicUsbUsbinValid
(
  OUT BOOLEAN *pValid
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type errFlag = PM_ERR_FLAG_SUCCESS;

  if(!pValid)
  {
    return EFI_INVALID_PARAMETER;
  }
  
  *pValid = FALSE;

  if (TRUE == IsSmbSupported())
  {
	if(EFI_SUCCESS != EFIPmicUsbInit())
	{
	  return EFI_UNSUPPORTED;
	}
    Status = PmicSchgProtocol->UsbinValid(PmicDeviceIndex,pValid);
  }
  else
  {
    errFlag = pm_chg_is_vbus_present(pValid);

    Status = (PM_ERR_FLAG_SUCCESS == errFlag) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
  }

  return Status;
}



/**
EFI_PmicChargerPortType ()

@brief
Gets charger port type
*/
EFI_STATUS
EFIAPI
EFI_PmicUsbChargerPortType
(
  OUT EFI_PM_USB_CHGR_PORT_TYPE *PortType
)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  if(!PortType)
  {
    return EFI_INVALID_PARAMETER;
  }

  if(EFI_SUCCESS != EFIPmicUsbInit())
  {
    return EFI_UNSUPPORTED;
  }
     
  Status = PmicSchgProtocol->GetChargerPortType(PmicDeviceIndex,(EFI_PM_SCHG_CHGR_PORT_TYPE*)PortType);

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicUsbSetOtgILimit
(
  IN  UINT32 ImAmp
)
{
  return EFI_UNSUPPORTED;
}


EFI_STATUS
EFIAPI 
EFI_PmicUsbEnableOtg
(
  IN BOOLEAN  Enable
)
{
  return EFI_UNSUPPORTED;
}


EFI_STATUS
EFIAPI
EFI_PmicUsbGetOtgStatus
(
  OUT EFI_PM_USB_OTG_STATUS_TYPE  *pOtgStatus
)
{
  EFI_STATUS  Status = EFI_SUCCESS;
  
  if(!pOtgStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pOtgStatus = EFI_PM_USB_OTG_STATUS_INVALID;

  if(EFI_SUCCESS != EFIPmicUsbInit())
  {
    return EFI_UNSUPPORTED;
  }

  Status = PmicSchgProtocol->GetOtgStatus(PmicDeviceIndex, (EFI_PM_SCHG_DCDC_OTG_STATUS_TYPE *)pOtgStatus);

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicUsbCGetPortState
(
  OUT  EFI_PM_USB_TYPEC_PORT_STATUS  *TypeCStatus
)
{
  EFI_STATUS       Status = EFI_SUCCESS;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if (!TypeCStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  SetMem(TypeCStatus, sizeof(EFI_PM_USB_TYPEC_PORT_STATUS), 0x00);

  if(EFI_SUCCESS != EFIPmicUsbInit())
  {
    return EFI_UNSUPPORTED;
  }

  err_flag = pm_chg_get_typec_status((pm_chg_typec_status_type *)TypeCStatus);

  return (Status | err_flag);
}

EFI_STATUS
EFIAPI
EFI_PmicUsbCGetConnectState
(
  OUT  EFI_PM_USB_TYPEC_CONNECT_MODE_STATUS  *pTypeCConnStatus
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if (NULL == pTypeCConnStatus)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pTypeCConnStatus = EFI_PM_USB_TYPEC_CONNECT_MODE_INVALID;

  if(EFI_SUCCESS != EFIPmicUsbInit())
  {
    return EFI_UNSUPPORTED;
  }

  err_flag = pm_chg_typec_get_port_role((pm_chg_typec_port_role_type*)pTypeCConnStatus);

  return (Status | err_flag);
}

EFI_STATUS
EFIAPI
EFI_PmicUsbCSetVConn
(
   IN  EFI_PM_USB_TYPEC_VCONN_CONFIG  *pVconnConfig
)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EFI_PmicUsbCSetPortRole
(
  IN  EFI_PM_USB_TYPEC_PORT_ROLE  PortRole
)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EFI_PmicUsbCEnable
(
  IN  BOOLEAN  Enable
)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EFI_PmicUsbGetChargerPresence
(
  OUT BOOLEAN  *pChargerPresent
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_PM_USB_TYPEC_CONNECT_MODE_STATUS TypeCConnStatus;

  if(NULL == pChargerPresent)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pChargerPresent = FALSE;

  Status = EFI_PmicUsbCGetConnectState(&TypeCConnStatus);
  if((EFI_PM_USB_TYPEC_CONNECT_MODE_UFP == TypeCConnStatus) && (EFI_SUCCESS == Status))
  {
    *pChargerPresent = TRUE;
  }

  return Status;
}


EFI_STATUS
EFIAPI
EFI_PmicUsbGetPortRoleSetTime
(
  OUT UINT64  *pPortRoleSetTime
)
{
  if(!pPortRoleSetTime)
    return EFI_INVALID_PARAMETER;

  if(gPortRoleSetTimeInmS)
  {
    *pPortRoleSetTime = gPortRoleSetTimeInmS;
  }
  else 
  {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
PMIC USB UEFI Protocol implementation
*/
EFI_QCOM_PMIC_USB_PROTOCOL PmicUsbProtocolImplementation = 
{
  .Revision               = PMIC_USB_REVISION,
  .UsbinValid             = EFI_PmicUsbUsbinValid,  
  .ChargerPort            = EFI_PmicUsbChargerPortType, 
  .SetOtgILimit           = EFI_PmicUsbSetOtgILimit,
  .EnableOtg              = EFI_PmicUsbEnableOtg,
  .GetOtgStatus           = EFI_PmicUsbGetOtgStatus,
  .UsbCGetPortState       = EFI_PmicUsbCGetPortState,
  .UsbCGetConnectState    = EFI_PmicUsbCGetConnectState,
  .UsbCSetVConn           = EFI_PmicUsbCSetVConn,
  .UsbCSetPortRole        = EFI_PmicUsbCSetPortRole,
  .UsbCEnable             = EFI_PmicUsbCEnable,
  .GetChargerPresence     = EFI_PmicUsbGetChargerPresence,
  .GetPortRoleSetTime     = EFI_PmicUsbGetPortRoleSetTime,
};

