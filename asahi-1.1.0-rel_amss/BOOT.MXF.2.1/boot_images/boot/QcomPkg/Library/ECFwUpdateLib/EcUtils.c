/** @file EC_Utils.c

  Provides EC FW update related utility routines.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights
  Reserved. Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/05/05     ananns      Renamed function from EcFirmwareRollback to EcFirmwareSync
  2023/03/29     sumesahu    Add support for Power-off EC during off mode charging &
                             enable check for power level.
  2023/03/22     bkulkarn    Changes to update EC Firmware version in SMBIOS Type-0 table
  2023/02/28     sumesahu    Fix for Boot KPI during empty EC FW
  2023/02/23     bkulkarn    Support to query & update EC device status in NV and code refactoring
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine, code refactoring
  2023/01/17     ananns      Cleaning up reference to global device context structure
  2023/01/10     ananns      Memory check is added in GetOnBinaryEcFwVersions function after memory allocation
  2022/12/01     bkulkarn    Reset hook support for EC device firmware update.
  2022/11/22     sumesahu    Support for power/resource related changes
  2022/09/22     bkulkarn    Support recovery protocol
  2022/07/29     bkulkarn    Initial version
=============================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/FwCommonLib.h>
#include <Library/FwUpdateLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/BootConfig.h>
#include <Library/EdkiiSystemCapsuleLib.h>
#include <Include/Library/MemoryAllocationLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/BlockIo.h>
#include <Library/ECFwUpdateLib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "EcUpgrade.h"
#include "EcUtils.h"

extern EC_DEVICE_CONTEXT *deviceContext;

/* EC Device ID to Firmware Resource GUID Mappings. Append new entries
at the end. */
EC_DEVICE_ID_TO_GUID_MAPPING EcDeviceIdToGUIDMappings[] =
{
  {EC_DEVICE_ID_8380_ITE_8987, EC_DEVICE_FW_8380_ITE_8987_GUID},
};

CORRUPTION_INFO corruptionLookUpTable[] =
{
  /*CorruptionStatus/Index          Valid(V)/Invalid(X) Partitions
  -----------------------------------------------------------------------*/
  {   0x0,                     "P2-MBK[X],P1-MBK[X],P2-BBK[X],P1-BBK[X]"},
  {   0x1,                     "P2-MBK[X],P1-MBK[X],P2-BBK[X],P1-BBK[V]"},
  {   0x2,                     "P2-MBK[X],P1-MBK[X],P2-BBK[V],P1-BBK[X]"},
  {   0x3,                     "P2-MBK[X],P1-MBK[X],P2-BBK[V],P1-BBK[V]"},
  {   0x4,                     "P2-MBK[X],P1-MBK[V],P2-BBK[X],P1-BBK[X]"},
  {   0x5,                     "P2-MBK[X],P1-MBK[V],P2-BBK[X],P1-BBK[V]"},
  {   0x6,                     "P2-MBK[X],P1-MBK[V],P2-BBK[V],P1-BBK[X]"},
  {   0x7,                     "P2-MBK[X],P1-MBK[V],P2-BBK[V],P1-BBK[V]"},
  {   0x8,                     "P2-MBK[V],P1-MBK[X],P2-BBK[X],P1-BBK[X]"},
  {   0x9,                     "P2-MBK[V],P1-MBK[X],P2-BBK[X],P1-BBK[V]"},
  {   0xA,                     "P2-MBK[V],P1-MBK[X],P2-BBK[V],P1-BBK[X]"},
  {   0xB,                     "P2-MBK[V],P1-MBK[X],P2-BBK[V],P1-BBK[V]"},
  {   0xC,                     "P2-MBK[V],P1-MBK[V],P2-BBK[X],P1-BBK[X]"},
  {   0xD,                     "P2-MBK[V],P1-MBK[V],P2-BBK[X],P1-BBK[V]"},
  {   0xE,                     "P2-MBK[V],P1-MBK[V],P2-BBK[V],P1-BBK[X]"},
  {   0xF,                     "P2-MBK[V],P1-MBK[V],P2-BBK[V],P1-BBK[V]"}
};

/**
 * @brief Function to read the EC FW version from firmware binary.
 *
 * @param ver_info         Pointer to structure containing EC FW version
 * @param ver_str          Pointer to string to be searched within FW binary
 *
 * @retval status          A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
GetOnBinaryEcFwVersions (
  const char *ver_str
  )
{
  EFI_STATUS        status = EFI_SUCCESS;
  CHAR8             *temp_str = NULL;
  char              *ver_start_pos = NULL, *ver_end_pos2 = NULL;
  int               i = 0, ec_ver_addr=0;
  VERSION_INFO      *ver_info = NULL;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!strncmp(ver_str,"EC VER:",strlen(ver_str)))
  {
    ver_info = &(deviceContext->on_bin_fv_info);
  }
  else if (!strncmp(ver_str,"LsFv:",strlen(ver_str)))
  {
    ver_info = &(deviceContext->on_bin_lsfv_info);
  }
  else
  {
    EC_E("version string is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  ver_info->main_ver = 0;
  ver_info->sub_ver  = 0;
  ver_info->test_ver = 0;

  if (!deviceContext->fw_img_data)
  {
    EC_E("fw_img_data is invalid!\n");
    status = EFI_ABORTED;
    goto Exit;
  }

  if ((deviceContext->fw_img_data_size <= 0) ||
    (deviceContext->fw_img_data_size > EC_FW_BLOCK_SIZE))
  {
    EC_E("fw_img_data size is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  temp_str = (CHAR8 *)AllocateCopyPool (
    deviceContext->fw_img_data_size,
    deviceContext->fw_img_data
    );
  if (NULL == temp_str)
  {
    status = EFI_OUT_OF_RESOURCES;
    EC_E("AllocateCopyPool failed!\n");
    goto Exit;
  }

  EC_I("Size of bin file=%dKB\n",
    (deviceContext->fw_img_data_size/1024));

  if ('E' == temp_str[EC_VERSION_OFFSET])
  {
    EC_I("FW binary is copied properly\n");
  }
  else
  {
    EC_E("FW binary not copied properly, aborting!\n");
    status = EFI_ABORTED;
    goto Exit;
  }

  /* Eliminate Null characters in the binary file
   just to automatically find the "EC Ver:" string */
  for (i=0;i<BUFFER_SIZE;i++)
  {
    if (temp_str[i]=='\0')
    {
      temp_str[i]='_';
    }
  }

  ver_start_pos = strstr(temp_str, ver_str);
  if ((ver_start_pos != NULL) &&
    (temp_str+BUFFER_SIZE-ver_start_pos) >= EC_FV_VERSION_LEN)
  {
    ec_ver_addr =  ver_start_pos - temp_str + strlen(ver_str);
    ver_end_pos2 = strchr(&(temp_str[ec_ver_addr]),'$');

    EC_D( "Length of EC %a %ld\n", ver_str, ver_end_pos2 - ver_start_pos);
    /* Overall Length of string "EC VER:00:01:00"[15bytes], "Fv:00:01:00"[11bytes], "LsFv:00:01:00"[13 bytes] */
    if ((ver_end_pos2 != NULL) &&
        (((ver_end_pos2 - ver_start_pos) >= 11) ||
        ((ver_end_pos2 - ver_start_pos) <= 18)))
    {
      ver_info->main_ver  =  (temp_str[ec_ver_addr+0] - '0')*10 + (temp_str[ec_ver_addr+1] - '0');
      ver_info->sub_ver   =  (temp_str[ec_ver_addr+3] - '0')*10 + (temp_str[ec_ver_addr+4] - '0');
      ver_info->test_ver  =  (temp_str[ec_ver_addr+6] - '0')*10 + (temp_str[ec_ver_addr+7] - '0');
    }
  }
Exit:
  if (temp_str)
  {
    FreePool(temp_str);
    temp_str = NULL;
  }
  return status;
}

/**
 * @brief Function to query and save full EC FW version
 * (Fv, LsFv and code-mirror tag) from IC.
 *
 * @param none
 *
 * @retval status    `     A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetOnDeviceFullEcFwVersion (
  void
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  UINT8       rdBuf[EC_FULL_VERSION_DATA_SIZE] = {0};
  UINT8       ecStatus[3] = {0,};
  UINT8       retry = 0, maxRetry = 10;
  UINT16      cycle_ms = 5;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("deviceContext is NULL!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  SetMem(
    rdBuf,
    EC_FULL_VERSION_DATA_SIZE,
    0xff
    );

  // Wait for EC SPI to be idle, before attempting for retry.
  do
  {
    SleepMs(cycle_ms*1000);
    status = EcI2cBlockRead(EC_SPI_SERVICE_CMD, ecStatus, 3, 0, 0);
    EC_ERROR_HANDLER(status, EcI2cBlockRead, Exit);

    if (EC_FW_IN_MAIN_BLK_IDLE == ecStatus[0])
    {
      EC_D(" EC MBK SPI service is in idle (0x%x)\n");
      break;
    }

    retry++;
  } while (retry < maxRetry);

  if (EC_FW_IN_MAIN_BLK_IDLE != ecStatus[0])
  {
    EC_E(" EC MBK SPI service not in idle (0x%x)\n", ecStatus[0]);
    status = EFI_DEVICE_ERROR;
    deviceContext->is_fw_corrupted = 1;
    goto Exit;
  }

  /* Read & Validate Full EC version with block read protocol */
  status = EcI2cBlockRead(
    EC_FULL_VERSION_BLK_READ_CMD,
    rdBuf,
    EC_FULL_VERSION_DATA_SIZE,
    30,
    3);
  EC_ERROR_HANDLER(status, EcI2cBlockRead, Exit);

  if ((0xff == rdBuf[0]) &&
    (0xff == rdBuf[1]) &&
    (0xff == rdBuf[2]))
  {
    EC_E("Invalid EC Firmware Version (Fv)!\n");
    status = EFI_DEVICE_ERROR;
    deviceContext->is_fw_corrupted = 1;
    goto Exit;
  }

  if ((0x00 == rdBuf[0]) &&
    (0x00 == rdBuf[1]) &&
    (0x00 == rdBuf[2]))
  {
    EC_E("EC flash is empty!\n");
    status = EFI_DEVICE_ERROR;
    deviceContext->is_fw_corrupted = 1;
    goto Exit;
  }

  deviceContext->on_ic_fv_info.main_ver =
    (rdBuf[2]& 0x0F) + (((rdBuf[2] >> 4) & 0x0F) * 10);
  deviceContext->on_ic_fv_info.sub_ver  =
    (rdBuf[1]& 0x0F) + (((rdBuf[1] >> 4) & 0x0F) * 10);
  deviceContext->on_ic_fv_info.test_ver =
    (rdBuf[0]& 0x0F) + (((rdBuf[0] >> 4) & 0x0F) * 10);

  if ((0xff == rdBuf[3]) &&
    (0xff == rdBuf[4]) &&
    (0xff == rdBuf[5]))
  {
    EC_E("Invalid EC Lowest Supported Firmware Version (LsFv)!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  deviceContext->on_ic_lsfv_info.main_ver =
    (rdBuf[5]& 0x0F) + (((rdBuf[5] >> 4) & 0x0F) * 10);
  deviceContext->on_ic_lsfv_info.sub_ver  =
    (rdBuf[4]& 0x0F) + (((rdBuf[4] >> 4) & 0x0F) * 10);
  deviceContext->on_ic_lsfv_info.test_ver =
    (rdBuf[3]& 0x0F) + (((rdBuf[3] >> 4) & 0x0F) * 10);

  if (0xff == rdBuf[6])
  {
    EC_E("Invalid EC code mirror tag!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  deviceContext->code_mirror_tag = rdBuf[6];

Exit:
    return status;
}

/**
 * @brief Function to query and save EC FW version from NV area
 *
 * @param none
 *
 * @retval status    `     A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetOnNvEcFwVersion (
  OUT UINT32 *FwVersion
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  UINT32      OnNvEcFwversion = 0;
  EC_TRACE();

  if(!FwVersion)
  {
    EC_E("FwVersion handle is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("deviceContext is NULL!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = GetNvEcFwVersion(&OnNvEcFwversion);
  EC_WARN_HANDLER(status, GetNvEcFwVersion);

  deviceContext->on_nv_fv_info.sub_ver = ((OnNvEcFwversion) & (0x00FF0000)) >> 16;
  deviceContext->on_nv_fv_info.test_ver = ((OnNvEcFwversion) & (0x000000FF));
  EC_I("  NvEc FwVersion            : V%dT%d\n",
    deviceContext->on_nv_fv_info.sub_ver,
    deviceContext->on_nv_fv_info.test_ver);
  *FwVersion = OnNvEcFwversion;

Exit:
    return status;
}

/**
 * @brief Function to query and save EC Lowest Supported (Ls)
 * FW version from NV area
 *
 * @param none
 *
 * @retval status    `     A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetOnNvEcLsFwVersion (
  UINT32 *LsFwVersion
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  UINT32      OnNvEcLsFwVersion = 0;
  EC_TRACE();

  if(!LsFwVersion)
  {
    EC_E("FwVersion handle is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("deviceContext is NULL!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = GetNvEcLsFwVersion(&OnNvEcLsFwVersion);
  EC_WARN_HANDLER(status, GetNvEcLsFwVersion);

  deviceContext->on_nv_lsfv_info.sub_ver = ((OnNvEcLsFwVersion) & (0x00FF0000)) >> 16;
  deviceContext->on_nv_lsfv_info.test_ver = ((OnNvEcLsFwVersion) & (0x000000FF));
  EC_I("  NvEc LsFwVersion          : V%dT%d\n\n",
    deviceContext->on_nv_lsfv_info.sub_ver,
    deviceContext->on_nv_lsfv_info.test_ver);
  *LsFwVersion = OnNvEcLsFwVersion;

Exit:
    return status;
}

/**
 * @brief Function to compare provided EC FW version with on device FW version.
 *
 * @param ver_info         Pointer to structure containing EC FW version
 *
 * @retval retVal          An integer indicating result of the operation.
 *
 **/
int
CompareWithNvEcFwVersion (
  VERSION_INFO  * ver_info
  )
{
  int retVal = 0;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    retVal = -1;
    goto Exit;
  }

  if ((ver_info->main_ver) < (deviceContext->on_nv_lsfv_info.main_ver))
  {
    retVal = 1;
    goto Exit;
  }
  else if ((ver_info->main_ver) == (deviceContext->on_nv_lsfv_info.main_ver))
  {
    if (ver_info->sub_ver < deviceContext->on_nv_lsfv_info.sub_ver)
    {
      retVal = 1;
      goto Exit;
    }
    else if ((ver_info->sub_ver) == (deviceContext->on_nv_lsfv_info.sub_ver))
    {
      if (ver_info->test_ver < deviceContext->on_nv_lsfv_info.test_ver)
      {
        retVal = 1;
        goto Exit;
      }
    }
  }
Exit:
  return retVal;
}

/**
 * @brief Function to compare provided EC FW version with version stored in NV.
 *
 * @param ver_info         Pointer to structure containing EC FW version
 *
 * @retval retVal          An integer indicating result of the operation.
 *
 **/
int
CompareWithOnDeviceEcFwVersion (
  VERSION_INFO  * ver_info
  )
{
  int retVal = 1;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    goto Exit;
  }

  if ((ver_info->main_ver) > (deviceContext->on_ic_fv_info.main_ver))
  {
    retVal = 0;
    goto Exit;
  }
  else if ((ver_info->main_ver) == (deviceContext->on_ic_fv_info.main_ver))
  {
    if (ver_info->sub_ver > deviceContext->on_ic_fv_info.sub_ver)
    {
      retVal = 0;
      goto Exit;
    }
    else if ((ver_info->sub_ver) == (deviceContext->on_ic_fv_info.sub_ver))
    {
      if ((ver_info->test_ver) >= (deviceContext->on_ic_fv_info.test_ver))
      {
        retVal = 0;
        goto Exit;
      }
    }
  }
Exit:
  return retVal;
}

/**
 * @brief Function to read the EC FW FFS file entry from FV
 *
 * @param Image             Pointer to FV image handle
 * @param ImageSize         Size of FV image buffer
 * @param Buffer            Pointer to pointer that contains EC FW FFS contents
 * @param BufferSize        Pointer to buffer that contains EC FW FFS contents
 *
 * @retval status           A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
ReadEcFwFromFV (
  IN VOID                      *Image,
  IN UINTN                      ImageSize,
  IN VOID                       **Buffer,
  IN OUT UINTN                  *BufferSize
  )
{
  EFI_STATUS                          status     = EFI_SUCCESS;
  UINT32                              FileHeaderSize = 0;
  boolean                             ReadResult = FALSE;
  VOID                               *FileBuffer = NULL;
  UINTN                               FileBufferSize = 0;
  FV_BUFFER_HANDLE                    FVBufferHandle = {0};
  EFI_GUID                            EcFwFfsGuid = EC_FW_FFS_FILE_GUID;

  EC_TRACE();

  if ((NULL == Image) ||
    (0 == ImageSize))
  {
    status =  EFI_INVALID_PARAMETER;
    EC_E("Invalid Image handle\n");
    goto Exit;
  }

  FVBufferHandle.Buffer = Image;
  FVBufferHandle.BufferSize = ImageSize;

  ReadResult = GetFfsByName(
    FVBufferHandle.Buffer,
    FVBufferHandle.BufferSize,
    &EcFwFfsGuid,
    EFI_FV_FILETYPE_RAW,
    &FileBuffer,
    &FileBufferSize
    );
  if (FALSE == ReadResult)
  {
    status = EFI_NOT_FOUND;
    EC_E("GetFfsByName failed with status %r!\n", status);
    goto Exit;
  }

  if (IS_FFS_FILE2 (FileBuffer))
  {
    FileHeaderSize = sizeof(EFI_FFS_FILE_HEADER2);
  }
  else
  {
    FileHeaderSize = sizeof(EFI_FFS_FILE_HEADER);
  }

  FileBuffer = (UINT8 *)FileBuffer + FileHeaderSize;
  FileBufferSize = FileBufferSize - FileHeaderSize;

  EC_I("EC FW FileBufferSize is :%d bytes\n", FileBufferSize);

  *Buffer = AllocateCopyPool (FileBufferSize, FileBuffer);
  if (NULL == *Buffer)
  {
    status = EFI_OUT_OF_RESOURCES;
    EC_E("AllocateCopyPool failed!\n");
    goto Exit;
  }

  *BufferSize = FileBufferSize;

Exit:
  if (EFI_ERROR(status))
  {
    if (*Buffer)
    {
      gBS->FreePool(*Buffer);
      *Buffer = NULL;
    }
  }
  return status;
}

/**
 * @brief Function to query the EC device ID from EC hardware.
 *
 * @param none
 *
 * @retval status          A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
GetEcDeviceId (
  void
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  UINT8       max_attempt = 10;
  UINT16      cycle_ms = 5;
  boolean     IsDeviceUp = FALSE;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = GetDeviceStatus(&IsDeviceUp);
  EC_ERROR_HANDLER(status, GetDeviceStatus, Exit);

  if (!IsDeviceUp)
  {
    EC_E("Device is not Initialised/Active with %r\n", status);
    status = EFI_UNSUPPORTED;
    goto Exit;
  }

  /* Wait for EC SPI to be idle, before attempting for retry */
  status = WaitForEnterIntoMainBlock(cycle_ms, max_attempt);
  if(EFI_ERROR(status))
  {
    EC_W(" WaitForEnterIntoMainBlock() failed with %r\n", status);
    status = WaitForEnterIntoBootBlock(cycle_ms, max_attempt);
    if(EFI_ERROR(status))
    {
      EC_W(" WaitForEnterIntoBootBlock() failed with %r \
        Neither in BBK nor in MBK\n", status);
      status = EFI_SUCCESS;
      deviceContext->is_fw_corrupted = 1;
    }
  }

  deviceContext->ec_device_id = deviceContext->register_info.chipID;

Exit:
    return status;
}

/**
 * @brief Function to get the FW partition corruption status from EC hardware.
 *
 * @param corruption_status  Pointer to corruption status variable.
 *
 * @retval status            A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
GetEcFwCorruptionStatus (
  UINT8 *corruption_status
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  UINT8       rdBuf[2] = {0x00,};
  EC_TRACE();

  if (!corruption_status)
  {
    EC_E("Invalid Paramater!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = EcI2cBlockRead(EC_CORRUPTION_STATUS_CMD,
    rdBuf, 2, 30, 2);
  EC_ERROR_HANDLER(status, EcI2cBlockRead, Exit);

  *corruption_status = rdBuf[0];
  EC_I("\n Corruption Value: 0X%X\n", *corruption_status);

  if (rdBuf[0] == ALL_PARTITIONS_OK)
  {
    EC_I("P1 and P2 Partition intact!!\n");
  }
  else
  {
    EC_D("Partitions Corrupted \n Corruption status: %a\n",
      corruptionLookUpTable[(*corruption_status) & 0x0F].name);
  }

Exit:
  return status;
}

/**
 * @brief Function to get the FW partition corruption status from EC hardware.
 *
 * @param none
 *
 * @retval status          A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
SetEcFwCorruptionStatus (
  UINT8 *corruption_status
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (!corruption_status)
  {
    EC_E("Invalid Paramater!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  deviceContext->corruption_status = *corruption_status;
  EC_I("Corruption status Value set with 0X%X\n",
    deviceContext->corruption_status);

Exit:
  return status;
}

/**
 * @brief Find the Firmware Resource GUID for the EC device.
 *
 * @param FwResourceGuid - Pointer to GUID that is modified to correspond to the current
 *                         platform type.
 *
 * @retval status           A EFI_STATUS indicating result of the operation.
 *
 */
EFI_STATUS
GetEcFwResourceGuid (
  OUT EFI_GUID *FwResourceGuid
  )
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT32        numOfMappings = 0;
  boolean       isFound = FALSE;
  UINT32        mappingIdx = 0;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!FwResourceGuid)
  {
     status = EFI_INVALID_PARAMETER;
     goto Exit;
  }

  status = GetEcDeviceId();
  if (EFI_ERROR(status))
  {
    EC_E("GetEcDeviceId failed with %r\n",status);
    goto Exit;
  }

  numOfMappings = (sizeof(EcDeviceIdToGUIDMappings)/sizeof(EC_DEVICE_ID_TO_GUID_MAPPING));
  for (mappingIdx= 0; mappingIdx < numOfMappings; mappingIdx++)
  {
    if (deviceContext->ec_device_id == EcDeviceIdToGUIDMappings[mappingIdx].EcDeviceId)
    {
      isFound = TRUE;
      break;
    }
  }

  if (FALSE == isFound)
  {
    EC_E("EC FwResource GUID not found for EC Device ID: %d!\n",
      deviceContext->ec_device_id);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  CopyMem(
    FwResourceGuid,
    &EcDeviceIdToGUIDMappings[mappingIdx].EcFwResourceGUID,
    sizeof(EFI_GUID));

Exit:
  return status;
}

/**
 * @brief Function to query the device status
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved Device status successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsDeviceInitDone is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetDeviceStatus (
  OUT boolean *IsDeviceUp
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (IsDeviceUp == NULL)
  {
    EC_E("IsDeviceInitDone buffer is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (deviceContext->is_device_init_done &&
    deviceContext->is_device_active)
  {
    *IsDeviceUp = TRUE;
  }
  else
  {
    *IsDeviceUp = FALSE;
  }

Exit:
  return status;
}

/**
 * @brief Function to compare the different in Lowest Supportted version against
 * On IC with On NV variable
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved LsFwVersion comparsion status successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsLsFwVersionSame is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CompareOnIcLsFwVersions (
  OUT boolean *IsLsFwVersionSame
  )
{
  EFI_STATUS  status = EFI_SUCCESS;

  if (IsLsFwVersionSame == NULL)
  {
    EC_E("IsLsFwVersionSame buffer is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((deviceContext->on_ic_lsfv_info.main_ver != deviceContext->on_nv_lsfv_info.main_ver) ||
   (deviceContext->on_ic_lsfv_info.sub_ver != deviceContext->on_nv_lsfv_info.sub_ver) ||
   (deviceContext->on_ic_lsfv_info.test_ver != deviceContext->on_nv_lsfv_info.test_ver))
  {
    *IsLsFwVersionSame = FALSE;
  }
  else
  {
    *IsLsFwVersionSame = TRUE;
  }

Exit:
  return status;
}

/**
 * @brief Function to compare the different in FW version against On IC with On NV variable
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved FwVersion comparsion status successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsOnIcFwVersionSame is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CompareOnIcFwVersion (
  OUT boolean *IsOnIcFwVersionSame
  )
{
  EFI_STATUS  status = EFI_SUCCESS;

  if (IsOnIcFwVersionSame == NULL)
  {
    EC_E("IsOnIcVersionSame buffer is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((deviceContext->on_ic_fv_info.main_ver != deviceContext->on_nv_fv_info.main_ver) ||
    (deviceContext->on_ic_fv_info.sub_ver != deviceContext->on_nv_fv_info.sub_ver) ||
    (deviceContext->on_ic_fv_info.test_ver != deviceContext->on_nv_fv_info.test_ver))
  {
    *IsOnIcFwVersionSame = FALSE;
  }
  else
  {
    *IsOnIcFwVersionSame = TRUE;
  }

Exit:
  return status;
}

/**
 * @brief Function to create and query the On IC LsFv
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On IC Lowest supported Fw Version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the LsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CreateAndGetOnIcLsFwVersion (
  OUT UINT32 *LsFwVersion
  )
{
  EFI_STATUS  status = EFI_SUCCESS;

  if (LsFwVersion == NULL)
  {
    EC_E("LsFwVersion buffer is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  *LsFwVersion = (UINT32) (deviceContext->on_ic_lsfv_info.sub_ver << 16);
  *LsFwVersion |= (UINT32) (deviceContext->on_ic_lsfv_info.test_ver);

  deviceContext->on_ic_lowest_supported_fw_version = *LsFwVersion;

Exit:
  return status;
}

/**
 * @brief Function to create and query the On IC FW version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On IC Fw Version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the FwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CreateAndGetOnIcFwVersion (
  OUT UINT32 *FwVersion
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (FwVersion == NULL)
  {
    EC_E("FwVersion buffer is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  *FwVersion = (UINT32) (deviceContext->on_ic_fv_info.sub_ver << 16);
  *FwVersion |= (UINT32) (deviceContext->on_ic_fv_info.test_ver);
  deviceContext->on_ic_fw_version = *FwVersion;

Exit:
  return status;
}

/**
 * @brief Function to query the On IC Lowest Supported FW version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On IC Lowest Supported Firmware Version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the OnIcLsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetOnIcLsFwVersion (
  OUT UINT32 *OnIcLsFwVersion
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (OnIcLsFwVersion == NULL)
  {
    EC_E("OnIcLsFwVersion is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  *OnIcLsFwVersion = deviceContext->on_ic_lowest_supported_fw_version;

Exit:
  return status;
}

/**
 * @brief Function to set the Firmware Update Done status
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Successfully set the Fw Update status
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
SetFwUpdateStatus (
  IN UINT8 FwUpdateStatus
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  deviceContext->is_fw_update_done = FwUpdateStatus;

Exit:
  return status;
}

/**
 * @brief Function to query the Firmware Update Done status
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved Fw update status successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsFwUpdateDone is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetFwUpdateStatus (
  OUT boolean *IsFwUpdateDone
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (IsFwUpdateDone == NULL)
  {
    EC_E("IsFwUpdateDone is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (deviceContext->is_fw_update_done)
  {
    *IsFwUpdateDone = TRUE;
  }
  else
  {
    *IsFwUpdateDone = FALSE;
  }

Exit:
  return status;
}

/**
 * @brief Function to query the Code Mirror Tag value
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved CodeMirrorTag Value successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the CodeMirrorTag is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetCodeMirrorTag (
  OUT UINT8 *CodeMirrorTag
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (CodeMirrorTag == NULL)
  {
    EC_E("CodeMirrorTag is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  *CodeMirrorTag = deviceContext->code_mirror_tag;

Exit:
  return status;
}

/**
 * @brief Function to query a byte from the EC FW version offset
 *
 * @param FwImageData                    Pointer to the FwImageData
 *
 * @retval EFI_SUCCESS                   Retrieved EC FW version starting byte successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the FwImageData is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetECVersionOffset (
  IN byte *FwImageData,
  IN UINTN Size,
  OUT byte *Data
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (FwImageData == NULL)
  {
    EC_E("FwImageData is NULL!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (Data == NULL)
  {
    EC_E("Data is NULL!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  deviceContext->fw_img_data = FwImageData;
  deviceContext->fw_img_data_size = Size;
  *Data = deviceContext->fw_img_data[EC_VERSION_OFFSET];

Exit:
  return status;
}

/**
 * @brief Function to set the valid raw buffer exist status
 *
 * @param RawBuffStatus                  Set the Raw buffer status value
 *
 * @retval EFI_SUCCESS                   Successfully set the valid buffer status
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
SetRawBuffExistStatus (
  IN UINT8 RawBuffStatus
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  deviceContext->valid_rawbuff_exist = RawBuffStatus;

Exit:
  return status;
}

/**
 * @brief Function to query the Valid raw buffer exist status
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Successfully read raw buffer status
 * @retval EFI_INVALID_PARAMETER         Pointer to the IsValidRawBuffExist is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetRawBuffExistStatus (
  OUT boolean *IsValidRawBuffExist
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (IsValidRawBuffExist == NULL)
  {
    EC_E("IsValidRawBuffExist is invalid!.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((deviceContext->fw_img_data) &&
    (deviceContext->valid_rawbuff_exist))
  {
    *IsValidRawBuffExist = TRUE;
  }
  else
  {
    *IsValidRawBuffExist = FALSE;
  }

Exit:
  return status;
}

/**
 * @brief Function to create and assign On binary Firmware version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   On binary fw version is assigned successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the FwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CreateAndSetOnBinFwVersion (
  OUT UINT32 *FwVersion
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (FwVersion == NULL)
  {
    EC_E("LsFwVersion is invalid!.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  *FwVersion = (UINT32) (deviceContext->on_bin_fv_info.sub_ver << 16);
  *FwVersion |= (UINT32) (deviceContext->on_bin_fv_info.test_ver);

  deviceContext->on_bin_fw_version = *FwVersion;

Exit:
  return status;
}

/**
 * @brief Function to create and query the On binary Lowest Supported Firmware version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On binary lowest supported fw version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the LsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CreateAndGetOnBinLsFwVersion (
  OUT UINT32  *LsFwVersion
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (LsFwVersion == NULL)
  {
    EC_E("LsFwVersion is invalid!.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  *LsFwVersion = (UINT32) (deviceContext->on_bin_lsfv_info.sub_ver << 16);;
  *LsFwVersion |= (UINT32) (deviceContext->on_bin_lsfv_info.test_ver);

  deviceContext->on_bin_lowest_supported_fw_version = *LsFwVersion;
Exit:
  return status;
}

/**
 * @brief Function to compare the FwVersion with NV Fw Version and On IC Fw Version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On binary lowest supported fw version successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the LsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
CompareFwVersion (
  OUT boolean *IsFwVersionLesser
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (IsFwVersionLesser == NULL)
  {
    EC_E("LsFwVersion is invalid!.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (deviceContext->valid_rawbuff_exist &&
     !CompareWithNvEcFwVersion(&(deviceContext->on_bin_fv_info)) &&
     !CompareWithOnDeviceEcFwVersion(&(deviceContext->on_bin_fv_info)))
  {
    *IsFwVersionLesser = FALSE;
  }
  else
  {
    *IsFwVersionLesser = TRUE;
  }

Exit:
  return status;
}

/**
 * @brief Function to print On IC and On Binary main,sub and test version
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Version details are printed successfully
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
DisplayVersionMismatchDetails (
  void
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_W("======== EC FW Version Mismatch, need FW update =======\n");

  EC_W("FW MainVersion [ICFv=%d,  BINFv=%d, BinLsFv=%d, NVLsFv=%d] \n",
    deviceContext->on_ic_fv_info.main_ver, deviceContext->on_bin_fv_info.main_ver,
    deviceContext->on_bin_lsfv_info.main_ver, deviceContext->on_nv_lsfv_info.main_ver);

  EC_W("FW SubVersion  [ICFv=%d,  BINFv=%d, BinLsFv=%d, NVLsFv=%d]\n" ,
    deviceContext->on_ic_fv_info.sub_ver, deviceContext->on_bin_fv_info.sub_ver,
    deviceContext->on_bin_lsfv_info.sub_ver, deviceContext->on_nv_lsfv_info.sub_ver);

  EC_W("FW TestVersion [ICFv=%d,  BINFv=%d, BinLsFv=%d, NVLsFv=%d]\n",
    deviceContext->on_ic_fv_info.test_ver, deviceContext->on_bin_fv_info.test_ver,
    deviceContext->on_bin_lsfv_info.test_ver, deviceContext->on_nv_lsfv_info.test_ver);

  EC_W("=======================================================\n");

Exit:
  return status;
}

/**
 * @brief Function to print EC Fw version details
 * (Chip ID, device ID, On IC Fw version and LsFw version)
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   EC Fw Version details are printed successfully
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
DisplayEcFwVersionDetails (
  void
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_W(" ======  EC FW Version Details =======\n");
  EC_W("  Detected EC Chip ID       : 0x%X\n",
    deviceContext->register_info.chipID);
  EC_W("  FwVersion                 : 0x%X\n",
    deviceContext->on_ic_fw_version);
  EC_W("  LowestSupportedFwVersion  : 0x%X\n",
    deviceContext->on_ic_lowest_supported_fw_version);
  EC_W(" ======================================\n");

Exit:
  return status;
}

/**
 * @brief Function to print EC Fw Partition details
 * (P1BBK, P1MBK, P2BBK, P2MBK)
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   EC Fw Version details are printed successfully
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
DisplayEcFwPartitionDetails (
  void
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  UINT8       corruption_status = 0;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = GetEcFwCorruptionStatus(&corruption_status);
  EC_ERROR_HANDLER(status, GetEcFwCorruptionStatus, Exit);

  deviceContext->corruption_status = corruption_status;
  EC_W("\n  ======  EC FW Partition Details =======\n");
  EC_W("  Corruption status         : [0X%X]->%a\n",
    corruption_status,
    corruptionLookUpTable[corruption_status & 0x0F].name);
  EC_W(" =======================================\n\n");

Exit:
  return status;
}

/**
 * @brief Function to wait for EC Fw getting stable and running in MBK
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   EC Fw Version details are printed successfully
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
WaitForEcFwToStable (
  void
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  UINT8       corruption_status = 0;
  UINT8       maxRetry = 10;
  UINT16      cycle_ms = 5;
  boolean     IsDeviceUp = FALSE;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("deviceContext is invalid!.\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = GetDeviceStatus(&IsDeviceUp);
  EC_ERROR_HANDLER(status, GetDeviceStatus, Exit);

  if (!IsDeviceUp)
  {
    EC_E("Device is not Initialised/Active with %r\n",
      status);
    status = EFI_NOT_READY;
    goto Exit;
  }

  status = GetEcFwCorruptionStatus(&corruption_status);
  EC_ERROR_HANDLER(status, GetEcFwCorruptionStatus, Exit);

  if (corruption_status == 0)
  {
    EC_I("Either older FW or P1, P2 Partition may be corrupted!!\n");
    status = SetEcFwCorruptionStatus(&corruption_status);
    EC_WARN_HANDLER(status, SetEcFwCorruptionStatus);
  }
  else
  {
    if ((corruption_status & SYNC_BIT) && (corruption_status & P1_MBK))
    {
      EC_I(" P1MBK is valid!!\n");
    }
    else if(corruption_status & P2_MBK)
    {
      /* Time required to copy from P2MBK to P1MBK =
       * maxRetry X cycle_ms = 10 X 300 = 3000msec
       * [ At Max 1200 ~ 1500msec needed to erase + sync + verify operations]
       */
      maxRetry = RETRY_250;
      cycle_ms = CYCLE_5MS;
      EC_W(" P1MBK is not valid!! , Auto-Sync in process....\n");
      status = EcFirmwareSync(COPY_INT_P2MBK_TO_P1, INTERNAL_FLASH_P1);
      EC_ERROR_HANDLER(status, EcFirmwareRollback, Exit);

      status = WaitForEnterIntoMainBlock(cycle_ms, maxRetry);
      if (EFI_ERROR(status))
      {
        EC_E("EC is not running in Main block, fw_status : %d, \
          P1MBK might be corrupted\n", deviceContext->fw_status);
        status = EFI_NOT_READY;
        goto Exit;
      }

      status = GetEcFwCorruptionStatus(&corruption_status);
      EC_ERROR_HANDLER(status, GetEcFwCorruptionStatus, Exit);

      status = SetEcFwCorruptionStatus(&corruption_status);
      EC_ERROR_HANDLER(status, SetEcFwCorruptionStatus, Exit);

      EC_W(" \n  Sync Bit         : %a\n",
        (corruption_status & SYNC_BIT) ? "P1MBK Valid" : "P1MBK is not valid");
    }
    else
    {
      EC_W(" P2MBK is not valid!!\n");
    }
  }

Exit:
  return status;
}

/**
 * @brief Function to check if P1BBK is intact or not
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   P1BBK is proper
 * @retval others                        P1BBK is corrupted
 *
 **/
EFI_STATUS
EcFwCheckP1BBKCorruption (
  VOID
  )
{
  EFI_STATUS   status = EFI_SUCCESS;
  UINT8        corruption_status = 0;
  UINT8        cycle_ms  = 10;
  UINT8        max_retry = 5;
  EC_TRACE();

  status = EcEnterBBK();
  EC_ERROR_HANDLER(status, EcEnterBBK, Exit);

  status = WaitForEnterIntoBootBlock(cycle_ms, max_retry);
  EC_ERROR_HANDLER(status, WaitForEnterIntoBootBlock, Exit);

  status = GetEcFwCorruptionStatus(&corruption_status);
  EC_ERROR_HANDLER(status, GetEcFwCorruptionStatus, Exit);

  EC_W(" \n Corruption Status: 0X%X\n", corruption_status);
  EC_W("==============================\n");

  status = SetEcFwCorruptionStatus(&corruption_status);
  EC_WARN_HANDLER(status, SetEcFwCorruptionStatus);

  /* Corruption status is supported on V0.12.0 onwards
   * And from V0.12.0 onwards FMP commands are supported
   */
  status = (!corruption_status) ? EFI_DEVICE_ERROR : EFI_SUCCESS;

Exit:
  return status;
}

/**
 * @brief Function to query the On IC and On Binary version details
 *
 * @param none
 *
 * @retval EFI_SUCCESS                   Retrieved On IC and On binary version info successfully
 * @retval EFI_INVALID_PARAMETER         Pointer to the OnIcFwVersion/OnIcLsFwVersion/
 *                                       OnBinFwVersion/OnBinLsFwVersion is NULL
 * @retval EFI_DEVICE_ERROR              Pointer to the deviceContext is NULL
 *
 **/
EFI_STATUS
GetOnIcAndOnBinVersion (
  OUT UINT32 *OnIcFwVersion,
  OUT UINT32 *OnIcLsFwVersion,
  OUT UINT32 *OnBinFwVersion,
  OUT UINT32 *OnBinLsFwVersion
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (OnIcFwVersion == NULL)
  {
    EC_E("OnIcFwVersion is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (OnIcLsFwVersion == NULL)
  {
    EC_E("OnIcLsFwVersion is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (OnBinFwVersion == NULL)
  {
    EC_E("OnBinFwVersion is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (OnBinLsFwVersion == NULL)
  {
    EC_E("OnBinLsFwVersion is NULL!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  *OnIcFwVersion    = deviceContext->on_ic_fw_version;
  *OnIcLsFwVersion  = deviceContext->on_ic_lowest_supported_fw_version;
  *OnBinFwVersion   = deviceContext->on_bin_fw_version;
  *OnBinLsFwVersion = deviceContext->on_bin_lowest_supported_fw_version;

Exit:
  return status;
}

/**
 * @brief Function to query and update the EC device status in NV.
 *
 * @param none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
QueryAndUpdateDeviceStatus(void)
{
  EFI_STATUS    status = EFI_SUCCESS;
  EFI_STATUS    nvStatus = EFI_SUCCESS;
  UINT8         rdBuf[EC_VERSION_DATA_SIZE] = {0xff, 0xff, 0xff, 0xff};
  UINT16        cycleMs = 5;
  UINT8         maxAttempt = 10;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  // Reset the device active status, to update after a successful version query.
  deviceContext->is_device_active = 0;

  status = WaitForEcSpiService(cycleMs, maxAttempt);
  if (EFI_ERROR(status))
  {
    EC_E("WaitForEcSpiService() failed with %r\n", status);
    goto UpdateStatus;
  }

  /* Verify EC version with block read protocol */
  status = EcI2cBlockRead(
    EC_VERSION_BLK_READ_CMD,
    rdBuf,
    EC_VERSION_DATA_SIZE,
    0,
    3);
  if (EFI_ERROR(status))
  {
    EC_E(" EcI2cBlockRead(EC_VERSION_BLK_READ_CMD) failed with %r!\n", status);
    goto UpdateStatus;
  }

  if ((0xff == rdBuf[0]) &&
    (0xff == rdBuf[1]) &&
    (0xff == rdBuf[2]))
  {
    EC_E("Invalid EC Firmware version!\n");
    status = EFI_DEVICE_ERROR;
    goto UpdateStatus;
  }

  if ((0x00 == rdBuf[0]) &&
    (0x00 == rdBuf[1]) &&
    (0x00 == rdBuf[2]))
  {
    EC_E("EC hardware is empty!\n");
    status = EFI_DEVICE_ERROR;
    goto UpdateStatus;
  }

  deviceContext->is_device_active = 1;

UpdateStatus:
  nvStatus = SetNvEcDeviceStatus(deviceContext->is_device_active);
  if (EFI_ERROR(nvStatus))
  {
    EC_E("SetNvEcDeviceStatus() failed with %r\n", nvStatus);
    goto Exit;
  }

Exit:
  return status;
}

/**
 * @brief Standalone routine to query the EC Firmware version from other modules.
 * - This function inits the I2C connection with I2C core.
 * - Queries the EC to read the version.
 * - Releases the resources.
 *
 * @param pEcFwVersion An out parameter containing EC firmware version in
 *                     case of success.
 * @retval status      A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
GetEcFwVersion(
  OUT VERSION_INFO *pEcFwVersion
)
{
  EFI_STATUS status = EFI_SUCCESS;

  EC_TRACE();

  if (!pEcFwVersion)
  {
    EC_E("pEcFwVersion is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = EcInitializeDevice();
  EC_ERROR_HANDLER(status, EcInitializeDevice, Exit);

  status = GetOnDeviceFullEcFwVersion();
  EC_ERROR_HANDLER(status, GetOnDeviceFullEcFwVersion, Exit);

  CopyMem(
    pEcFwVersion,
    &deviceContext->on_ic_fv_info,
    sizeof(VERSION_INFO)
    );

Exit:
  status = EcDeInitializeDevice();
  EC_I("EcDeInitializeDevice() returned %r\n", status);

  return status;
}