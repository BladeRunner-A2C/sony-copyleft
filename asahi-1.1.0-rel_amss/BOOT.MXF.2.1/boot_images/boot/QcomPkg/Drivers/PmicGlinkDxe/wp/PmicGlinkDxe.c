/**
@file  PmicGlinkDxe.c
@brief USB Power Control Module related Declaration
*/
/*=============================================================================
Copyright (c) 2018 Qualcomm Technologies, Incorporated.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
03/29/18   cs      added ucsi support.
11/06/17   cs      Initial Release
=============================================================================*/

/*===========================================================================*/
/*                  INCLUDE FILES                                            */
/*===========================================================================*/
#include <Uefi.h>

/**
  Library Dependencies
*/
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/UefiBootServicesTableLib.h>

/**
  Protocol Dependencies
*/
#include <Protocol/EFIPmicGlink.h>
#include "pmic_glink.h"


/*===========================================================================*/
/*                  LOCAL VARIABLE DECLARATIONS                              */
/*===========================================================================*/
EFI_PMIC_GLINK_PROTOCOL PmicGlinkProtocolImplementation;


/*===========================================================================*/
/*                  FUNCTION DEFINITIONS                                     */
/*===========================================================================*/
/**
  Initialize PmicGlink Module

  @param none

  @return
  EFI_SUCCESS:                  Function returned successfully.
  EFI_INVALID_PARAMETER:        A Parameter was incorrect.
  EFI_DEVICE_ERROR:             The physical device reported an error.
  EFI_UNSUPPORTED:              The physical device does not support this function
*/
EFI_STATUS PmicGlinkInit(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status = EFI_SUCCESS;

//  Status = pmic_glink_Init();

  if(EFI_SUCCESS == Status)
  {
    Status = gBS->InstallMultipleProtocolInterfaces(&ImageHandle,
                                                    &gpmicGlinkProtocolGuid,
                                                    &PmicGlinkProtocolImplementation,
                                                    NULL);
  }
  return Status;
}



/**
EFI_PmicGlink_UCSIReadBuffer()

@brief
read ucsi data buffer from ADSP
*/
EFI_STATUS
EFIAPI
EFI_PmicGlink_UCSIReadBuffer
(
   UINT8** ppReadBuffer,
   UINT8 size
)
{
  if (ppReadBuffer != NULL && *ppReadBuffer != NULL)
  {
    return pmic_glink_ucsi_read_buffer(ppReadBuffer, size);
}
  return EFI_INVALID_PARAMETER;
}


/**
EFI_PmicGlink_UCSIWriteBuffer()

@brief
write data buffer to ADSP
*/
EFI_STATUS
EFIAPI
EFI_PmicGlink_UCSIWriteBuffer
(
  UINT8* pWriteBuffer,
  UINT8 size
)
{

  if (pWriteBuffer != NULL)
{
    return pmic_glink_ucsi_write_buffer(pWriteBuffer, size);
}

  return EFI_INVALID_PARAMETER;
}

/**
EFI_PmicGlink_USBCReadBuffer()

@brief
read usbc data buffer from ADSP
*/
EFI_STATUS
EFIAPI
EFI_PmicGlink_USBCReadBuffer
(
   UINT8** ppReadBuffer,
   UINT8 size
)
{
  if (ppReadBuffer != NULL && *ppReadBuffer != NULL)
  {
    return pmic_glink_usbc_read_buffer(ppReadBuffer, size);
	}
  return EFI_INVALID_PARAMETER;
}


/**
EFI_PmicGlink_USBCWriteBuffer()

@brief
write usbcdata buffer to ADSP
*/
EFI_STATUS
EFIAPI
EFI_PmicGlink_USBCWriteBuffer
(
  UINT8* pWriteBuffer,
  UINT8 size
)
{

  if (pWriteBuffer != NULL)
{
    return pmic_glink_usbc_write_buffer(pWriteBuffer, size);
}

  return EFI_INVALID_PARAMETER;
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_GetBatteryCount
(
  OUT UINT32* batteryCount
)
{
  if (batteryCount == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  return pmic_glink_get_battery_count(batteryCount);
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_GetBatteryStatus
(
  IN  UINT32          battery_index,
  OUT EFI_PM_GLINK_BATT_STATUS_INFO *pBattStsInfo
)
{
  if (pBattStsInfo == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  pmic_glink_get_battery_info(battery_index);

  return pmic_glink_get_battery_status(battery_index, pBattStsInfo);
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_GetBatteryStatusExt
(
  OUT UINT32* battery_ocv
)
{
  if(battery_ocv == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }
  return pmic_glink_get_battery_status_ext(battery_ocv);
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_IsBatteryPresent
(
  IN  UINT32          battery_index,
  OUT BOOLEAN         *pBatteryPresent
)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT32 battery_count = 0;
  static BOOLEAN battery_present = TRUE;
  static BOOLEAN battery_present_read = FALSE;

  if(battery_present_read && battery_present == TRUE)
  {
    *pBatteryPresent = battery_present;
	return status;
  }
  if (pBatteryPresent == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  *pBatteryPresent = FALSE;

  status = EFI_PmicGlink_GetBatteryCount(&battery_count);
  if (!EFI_ERROR(status))
  {
    battery_present_read = TRUE;
    if (battery_count > battery_index)
    {
      *pBatteryPresent = TRUE;
      battery_present = TRUE;
      DEBUG((EFI_D_WARN, "EFI_PmicGlink_IsBatteryPresent:: battery index: %d is present. \r\n", battery_index));
    }
    else
    {
      battery_present = FALSE;
      DEBUG((EFI_D_WARN, "EFI_PmicGlink_IsBatteryPresent:: battery index: %d is missing becasue battery_count = %d \r\n", battery_index, battery_count));
    }
  }

  return status;
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_LinkStatus
(
  OUT EFI_PM_GLINK_LINK_STATUS *PmicGLinkStatus
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(NULL == PmicGLinkStatus)
    return EFI_INVALID_PARAMETER;

  Status = pmic_glink_get_link_status(PmicGLinkStatus);

  return Status;
}


EFI_STATUS
EFIAPI
EFI_PmicGlink_CpdLogLinkStatus
(
  OUT EFI_PM_GLINK_LINK_STATUS *PmicGLinkStatus
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if(NULL == PmicGLinkStatus)
    return EFI_INVALID_PARAMETER;

  Status = pmic_glink_cpdlog_get_link_status(PmicGLinkStatus);
  return Status;
}


EFI_STATUS
EFIAPI
EFI_PmicGlink_Connect
(
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = pmic_glink_Init();

  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_Disconnect
(
)
{
  pmic_glink_deinit();
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_CpdLogConnect
(
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = pmic_glink_cpdlog_Init();
  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_CpdLogDisconnect
(
)
{
  pmic_glink_cpdlog_deinit();
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
EFI_PmicGlink_CpdlogSetProperties
(
  IN UINT64 categories,
  IN UINT32 level
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  Status = pmic_glink_cpdlog_set_properties(categories, level);
  
  return Status;
}


EFI_STATUS
EFIAPI
EFI_PmicGlink_CpdlogGetBuffer
(
  IN  UINT32 max_logsize,
  OUT CHAR8  *ReceivedBuffer
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  Status = pmic_glink_cpdlog_get_buffer(max_logsize, ReceivedBuffer);
  
  return Status;
}



EFI_STATUS
EFIAPI
EFI_PmicGlink_CpdlogGetQbgDump
(
  OUT UINT32 *ReceivedQbgDumpSize,  
  OUT UINT32 *ReceivedQbgDump,
  IN  UINT32         battery_cell_id
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  //Status = pmic_glink_cpdlog_get_qbg_dump(ReceivedQbgDumpSize, ReceivedQbgDump);

  return Status;
}


EFI_STATUS
EFIAPI
EFI_PmicGlink_GetChargerPower
(
  OUT EFI_PM_GLINK_CHARGER_POWER *pChargerPower
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  Status = pmic_glink_get_charger_power(pChargerPower);
  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_SendShdnNotification
(
)
{
  EFI_STATUS Status = EFI_SUCCESS;

  //Status = pmic_glink_send_shutdown_notification();
  return Status;
}

EFI_STATUS
EFIAPI
EFI_PmicGlink_CpdlogGetInitBuffer
(
  IN  UINT32 max_logsize,
  OUT CHAR8  *ReceivedBuffer
)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  Status = pmic_glink_cpdlog_get_init_buffer(max_logsize, ReceivedBuffer);
  
  return Status;
}

/**
EFI_PmicGlink_OemReadBuffer()

@brief
read oem data buffer from ADSP
*/
EFI_STATUS
EFIAPI
EFI_PmicGlink_OemReadBuffer
(
   UINT32* pReadBuffer,
   UINT32 property_id,
   UINT8 size
)
{
  if (pReadBuffer != NULL)
  {
    return pmic_glink_oem_read_buffer(pReadBuffer, property_id,size);
  }
  return EFI_INVALID_PARAMETER;
}


/**
EFI_PmicGlink_OemWriteBuffer()

@brief
write oem data buffer to ADSP
*/
EFI_STATUS
EFIAPI
EFI_PmicGlink_OemWriteBuffer
(
  UINT32* pWriteBuffer,
  UINT32 property_id,
  UINT8 size
)
{

  if (pWriteBuffer != NULL)
  {
    return pmic_glink_oem_write_buffer(pWriteBuffer, property_id, size);
  }

  return EFI_INVALID_PARAMETER;
}

/**
EFI_PmicGlink_OemExtention()

@brief
read oem data buffer from ADSP
*/
EFI_STATUS
EFIAPI
EFI_PmicGlink_OemExtention
(
   UINT32* pDataBuffer,
   UINT8 size
)
{
  if (pDataBuffer != NULL)
  {
    return pmic_glink_oem_write_read_buffer(pDataBuffer, size);
  }
  return EFI_INVALID_PARAMETER;
}

/**
  USB Power Control Protocol implementation
 */
EFI_PMIC_GLINK_PROTOCOL PmicGlinkProtocolImplementation =
{
  EFI_PMICGLINK_PROTOCOL_REVISION_9,
  EFI_PmicGlink_UCSIReadBuffer,
  EFI_PmicGlink_UCSIWriteBuffer,
  EFI_PmicGlink_USBCReadBuffer,
  EFI_PmicGlink_USBCWriteBuffer,
  EFI_PmicGlink_GetBatteryCount,
  EFI_PmicGlink_GetBatteryStatus,
  EFI_PmicGlink_IsBatteryPresent,
  EFI_PmicGlink_Connect,
  EFI_PmicGlink_LinkStatus,
  EFI_PmicGlink_CpdLogConnect,  
  EFI_PmicGlink_CpdLogLinkStatus,
  EFI_PmicGlink_CpdlogSetProperties,
  EFI_PmicGlink_CpdlogGetBuffer,
  EFI_PmicGlink_CpdlogGetQbgDump,
  EFI_PmicGlink_GetBatteryStatusExt,
  EFI_PmicGlink_Disconnect,
  EFI_PmicGlink_CpdLogDisconnect,
  EFI_PmicGlink_GetChargerPower,
  EFI_PmicGlink_SendShdnNotification,
  EFI_PmicGlink_CpdlogGetInitBuffer,
  EFI_PmicGlink_OemExtention,
};


