/** @file EcUpgrade.c

  Provides wrappers for EC Firmware upgrade routines.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/04/28     ananns      Renamed function name from EcFirmwareRollback to EcFirmwareSync
  2023/02/28     sumesahu    Fix for Boot KPI during empty EC FW
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
  2022/11/22     bkulkarn    Changes to support A/B partition update
  2022/07/29     sumesahu    Initial version
=============================================================================*/


#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootConfig.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/SecBootSigLib.h>
#include <Protocol/FirmwareManagement.h>
#include <Library/ECFwUpdateLib.h>

extern EC_DEVICE_CONTEXT *deviceContext;

/**
 * @brief Utility function to check if flash-type corresponds to internal eFlash
 *
 * @param flashType - Variable indicating flash type
 *
 * @retval
 *  TRUE  - If flashType corresponds to an internal flash partition.
 *  FALSE - Otherwise
 */
static BOOLEAN
IsInternalFlashPartition(
  EC_FLASH_PARTITION_INFO flashType
  )
{
  if ((flashType >= INTERNAL_FLASH) ||
      (flashType < EXTERNAL_FLASH_P1))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/**
 * @brief Function to send data buffer to EC's internal eFlash
 *
 * @param cmd                I2C Command for writing into slave
 * @param buff               Pointer Buffer for holding the write data into slave
 * @param size               Size of the write buffer to slave
 *
 * @retval status           A EFI_STATUS indicating result of the operation.
 **/
static EFI_STATUS
EcFlashToSpiRom(
  UINT8 cmd,
  void* buff,
  UINT16 size)
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         wdBuf[5] = {0,};
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("Invalid EC device context!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((size >  EC_MAX_WRITE_SECTOR_TO_FLASH) ||
    (NULL == buff))
  {
    EC_E("Error in buffer size criteria:[%d]!\n", size);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  wdBuf[0] = deviceContext->ctrl_path;
  switch(size)
  {
    case LIMIT_32B:
      wdBuf[1] = 0x01;
      break;
    case LIMIT_64B:
      wdBuf[1] = 0x02;
      break;
    case LIMIT_128B:
      wdBuf[1] = 0x04;
      break;
    case LIMIT_256B:
      wdBuf[1] = 0x08;
      break;
    case LIMIT_512B:
      wdBuf[1] = 0x10;
      break;
    default:
      wdBuf[1] = 0x08;
      EC_I("Falling back to 256byte limit!!\n");
      break;
  }

  wdBuf[2] = (UINT8)(*((unsigned int*)(buff)) & 0xFF);                  //ADDRL
  wdBuf[3] = (UINT8)((*((unsigned int*)(buff)) >> 8) & 0xFF);          //ADDRM
  wdBuf[4] = (UINT8)((*((unsigned int*)(buff)) >> 16) & 0xFF);         //ADDRH
  status = EcI2cBlockWrite(cmd, &(wdBuf[0]), 5);
  EC_ERROR_HANDLER(status, EcI2cBlockWrite, Exit);

Exit:
  return status;
}

/**
 * @brief Function to parse the boot-block & main-block regions from the buffer
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
static EFI_STATUS
EcParseFwImage(void)
{
  EFI_STATUS status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->fw_img_data)
  {
    EC_E("deviceContext->fw_img_data is NULL!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  deviceContext->fw_bbk_blk_data = (byte *) (&(deviceContext->fw_img_data[0]));
  deviceContext->fw_main_blk_data = (byte *) ((&(deviceContext->fw_img_data[0])) + BOOT_BLK_BUFFER_SIZE);

  EC_I("Check: bbk[0x%x], mbk[0x%x], fw[0]:0x%x, fw[0x2000]:0x%x\n",
    deviceContext->fw_bbk_blk_data[0],
    deviceContext->fw_main_blk_data[0],
    deviceContext->fw_img_data[0],
    deviceContext->fw_img_data[BOOT_BLK_BUFFER_SIZE]);

Exit:
  return status;
}

/**
 * @brief Function to select the flash appropriate type
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
static EFI_STATUS
EcSelectSpiFlash(void)
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         buf = 0;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((EXTERNAL_FLASH_P1 == deviceContext->flash_type) ||
      (EXTERNAL_FLASH_P2 == deviceContext->flash_type))
  {
    buf = SEL_EXT_SPI_FLASH_CMD;
    deviceContext->erase_sector_size = EXT_FLASH_ERASE_SECTOR_SIZE;
    EC_I("Select External SPI Flash\n");
  }
  else if (IsInternalFlashPartition(deviceContext->flash_type))
  {
    buf = SEL_INT_SPI_FLASH_CMD;
    deviceContext->erase_sector_size = INT_FLASH_ERASE_SECTOR_SIZE;
    EC_I("Select Internal SPI eFlash\n");
  }
  else
  {
    buf = SEL_INT_SPI_FLASH_CMD;
    deviceContext->erase_sector_size = INT_FLASH_ERASE_SECTOR_SIZE;
    EC_E("Flash type is not supported, falling back to Internal flash type\n");
  }

  status = EcI2cBlockWrite(EC_SPI_QUICK_CMD, &buf, 1);
  EC_ERROR_HANDLER(status, EcI2cBlockWrite, Exit);

Exit:
  return status;
}

/**
 * @brief Function to wait for EC checksum result
 *
 * @param timeout_ms    Total timeout for checksum operation.
 *
 * @retval status       A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
WaitForEcChecksumResult(unsigned int timeout_ms)
{
  EFI_STATUS     status = EFI_SUCCESS;
  UINT8          ec_status[5] = {0,};
  unsigned int   duration = 100;  // 100ms is the minimum delay
  unsigned int   retry = 2;
  unsigned int   default_retry = 20;
  EC_TRACE();

  retry = (timeout_ms <= 0)? default_retry:(timeout_ms/duration);

  EC_I(" Wait for EC Checksum Read\n");

  status = EcI2cBlockRead(
    BULK_READ_CMD,
    ec_status,
    sizeof(ec_status),
    duration,
    retry);
  if (EFI_ERROR(status))
  {
    EC_E("EcI2cBlockRead for checksum failed with %r, result :0x%x 32bit checksum[0,1,2,3]:[0x%x, 0x%x, 0x%x, 0x%x]\n",
          status,ec_status[0], ec_status[1], ec_status[2], ec_status[3], ec_status[4]);
    goto Exit;
  }

  if (PASS_CHECKSUM == ec_status[0])
  {
    EC_W("EC Checksum Passed, 32bit checksum[0,1,2,3]:[0x%x, 0x%x, 0x%x, 0x%x]\n",
        ec_status[1], ec_status[2], ec_status[3], ec_status[4]);
  }
  else
  {
    EC_E("EC Checksum Failed!!, 32bit checksum[0,1,2,3]:[0x%x, 0x%x, 0x%x, 0x%x]\n",
      ec_status[1], ec_status[2], ec_status[3], ec_status[4]);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  return status;
}

/**
 * @brief Function to wait for EC SPI service
 *
 * @param cycle_ms      Sleep time before each i2c transaction
 * @param max_retry     Maximum retry before failure
 *
 * @retval status       A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
WaitForEcSpiService(UINT16 cycle_ms, UINT8 max_retry)
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         ec_status[3] = {0,};
  unsigned int  times = 0;
  EC_TRACE();

  do
  {
    SleepMs(cycle_ms*1000);

    status = EcI2cBlockRead(
      EC_SPI_SERVICE_CMD,
      ec_status,
      sizeof(ec_status),
      0,
      0);
    if (EFI_SUCCESS == status)
    {
      if (EC_FW_IN_BOOT_BLK_IDLE == ec_status[0])
      {
        EC_W("EC BBK SPI service is idle\n");
        goto Exit;
      }
      else if (EC_FW_IN_MAIN_BLK_IDLE == ec_status[0])
      {
        EC_I("EC MBK SPI service is idle\n");
        goto Exit;
      }
      else
      {
        EC_I("EC SPI service is in Unknown State!!\n");
       }
    }

    // If EC is busy, or bus error, do the retry
    times++;
    EC_P(" .");
  }while(times < max_retry);

  EC_P(" \n");
  if (times == max_retry)
  {
    EC_W("EC SPI service is busy and timed out, \
      ec_spi_service_status = 0x%x\n", ec_status[0]);
    status = EFI_DEVICE_ERROR;
  }
Exit:
  return status;
}

/**
 * @brief Function to check the firmware control path
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcCheckControlPath(void)
{
  EFI_STATUS    status = EFI_SUCCESS;
  EFI_STATUS    temp_status = EFI_SUCCESS;
  UINT8         uData[3] = {0,};
  unsigned int  retry=0;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  temp_status = EcEnterBBK();
  EC_WARN_HANDLER(temp_status, EcEnterBBK);

  SleepMs(TIME_100MS);

  temp_status = EcCheckFwStatus();
  EC_WARN_HANDLER(temp_status, EcCheckFwStatus);

  if (deviceContext->fw_status != BOOT_BLK)
  {
    EC_W("fw is not in Boot Block: %d!!\n",
      deviceContext->fw_status);
  }

  for (;retry < 5; retry++)
  {
    ZeroMem(uData, (sizeof(uData)/sizeof(uData[0])));
    status = EcI2cBlockRead(
      EC_SPI_SERVICE_CMD,
      uData,
      sizeof(uData),
      0,
      0);
    EC_ERROR_HANDLER(status, EcI2cBlockRead, Exit);

    EC_W("EC response [%x,%x,%x]\n",
      uData[0],uData[1],uData[2]);

    if (INT_FLASH_CTRL_PATH == uData[1])
    {
      EC_I("Control path is in Internal eFlash!\n");
      deviceContext->ctrl_path = INT_FLASH_CTRL_PATH;
      goto Exit;
    }
    if (INT_FLASH_P1_CTRL_PATH == uData[1])
    {
      EC_I("Control path is in Internal eFlash P1 partition!\n");
      deviceContext->ctrl_path = INT_FLASH_P1_CTRL_PATH;
      goto Exit;
    }
    if (INT_FLASH_P2_CTRL_PATH == uData[1])
    {
      EC_I("Control path is in Internal eFlash P2 partition!\n");
      deviceContext->ctrl_path = INT_FLASH_P2_CTRL_PATH;
      goto Exit;
    }
    else if (EXT_FLASH_CTRL_PATH == uData[1])
    {
      EC_I("Control path is in External Flash!\n");
      deviceContext->ctrl_path = EXT_FLASH_CTRL_PATH;
      goto Exit;
    }
    else
    {
      EC_E("Retrying (%d)\r",retry);
      SleepMs(TIME_10MS);
      continue;
    }
  }

  EC_W("EC is in unknown control path!\n");
  deviceContext->ctrl_path = UNKNOWN_CTRL_PATH;

  if (deviceContext->fw_status != MAIN_BLK)
  {
    temp_status = EcExitBBK();
    EC_WARN_HANDLER(temp_status, EcExitBBK);

    temp_status = EcCheckFwStatus();
    EC_WARN_HANDLER(temp_status, EcCheckFwStatus);
  }

Exit:
  return status;
}

/**
 * @brief Function tp erase the selected region of internal/external SPI FLash
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
static EFI_STATUS
EcEraseSpiFlash(void)
{
  UINT16            cycle_ms = 1000;
  UINT8             retry = 5;
  EFI_STATUS        status = EFI_SUCCESS;
  UINTN             writeProgress = PROGRESS_EC_FW_CAPSULE_ERASE_START;
  UINTN             progressChunk = 10;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (BOOT_BLK == deviceContext->fw_status)
  {
    EC_I("FW is in Boot Block\n");
  }
  else
  {
    EC_I("FW is not in Boot Block\n");
  }

  EcFwUpdateProgress(writeProgress);
  writeProgress += progressChunk;

  if (EXTERNAL_FLASH_P1 == deviceContext->flash_type)
  {
    deviceContext->start_addr = BOOT_BLK_START_ADDR;
    deviceContext->erase_blockCount = 32;
  }
  else if (EXTERNAL_FLASH_P2 == deviceContext->flash_type)
  {
    deviceContext->start_addr = BOOT_BLK2_START_ADDR;
    deviceContext->erase_blockCount = 32;
  }
  else if (INTERNAL_FLASH_P1 == deviceContext->flash_type)
  {
    deviceContext->start_addr = ACTIVE_MBK_START_ADDR;
    deviceContext->end_addr = ACTIVE_MBK_END_ADDR;
    deviceContext->erase_blockCount = 24;
  }
  else if (INTERNAL_FLASH_P2 == deviceContext->flash_type)
  {
    deviceContext->start_addr = BACKUP_MBK_START_ADDR;
    deviceContext->end_addr = BACKUP_MBK_END_ADDR;
    deviceContext->erase_blockCount = 24;
  }
  else
  {
    EC_W("Unknown flash type %d, falling into default P1 MBK\n",
      deviceContext->flash_type);
    // Default to internal active partition
    deviceContext->start_addr = MAIN_BLK_START_ADDR;
    deviceContext->end_addr = MAIN_BLK_END_ADDR;
    deviceContext->erase_blockCount = 24;
  }

  EcFwUpdateProgress(writeProgress);
  writeProgress += progressChunk;

  EC_I("Erasing sector [0x%x] from start[0x%x] --- end[0x%x] with erase_sector_size:%d\n",
    deviceContext->flash_type,
    deviceContext->start_addr,
    (deviceContext->start_addr + (deviceContext->erase_blockCount*deviceContext->erase_sector_size) - 1),
    deviceContext->erase_sector_size);

  UINT8 blockCount = deviceContext->erase_blockCount;

  status = EcCheckControlPath();
  EC_ERROR_HANDLER(status, EcCheckControlPath, Exit);

  if (EXT_FLASH_CTRL_PATH == deviceContext->ctrl_path)
  {
    if (EXTERNAL_FLASH_P1 == deviceContext->flash_type)
    {
      EC_I("ERASE_EXT_ACTIVE_PARTITION_CMD\n");
    }
    else
    {
      EC_I("ERASE_EXT_BACKUP_PARTITION_CMD\n");
    }
  }
  else if (INT_FLASH_CTRL_PATH == deviceContext->ctrl_path)
  {
    EC_I("ERASE_INT_FLASH_MBK_CMD\n");
  }

  status = EcEraseDesignatedFlash(cycle_ms,retry);
  EC_ERROR_HANDLER(status, EcEraseDesignatedFlash, Exit);

  EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_ERASE_END);

  EC_W("blk(%dKB) %d / %d erased\n",
    (deviceContext->erase_sector_size/_SIZE_1KB), blockCount, blockCount);

Exit:
  return status;
}

/**
 * @brief Function to update the selected region of internal/external SPI flash.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
static EFI_STATUS
EcWriteSpiFlash(void)
{
  UINT16        blockNum = 0;
  EFI_STATUS    status = EFI_SUCCESS;
  unsigned int  addr = 0;
  UINT16        blockCount = 0;
  UINTN         writeProgress = PROGRESS_EC_FW_CAPSULE_ERASE_END;
  UINTN         progressChunk = 5;
  byte          *fw_buffer = NULL;
  UINT8         flash_type = UNKNOWN_FLASH_INFO;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("Invalid EC device context!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  blockCount = deviceContext->erase_blockCount*(deviceContext->erase_sector_size/EC_MAX_WRITE_SECTOR_TO_RAM);

  EC_D("Total block count %d, each of %d bytes to be flashed\n",
    blockCount, EC_MAX_WRITE_SECTOR_TO_RAM);

  status = WaitForEcSpiService(100, 5);
  EC_ERROR_HANDLER(status, WaitForEcSpiService, Exit);

  writeProgress += progressChunk;
  EcFwUpdateProgress(writeProgress);

  status = GetNvEcFwFlashTypeStatus(&flash_type);
  if ((EFI_NOT_FOUND == status) ||
     (EFI_BUFFER_TOO_SMALL == status))
  {
    status = SetNvEcFwFlashTypeStatusDonotFlush(0);
    EC_ERROR_HANDLER(status, SetNvEcFwFlashTypeStatusDonotFlush, Exit);
  }
  deviceContext->flash_type = flash_type;
  EC_W("deviceContext->flash_type: %d\n", deviceContext->flash_type);

  if (UNKNOWN_FLASH_INFO == deviceContext->flash_type)
  {
    EC_E("Invalid flash-type (%d) detected!\n", deviceContext->flash_type);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((EXTERNAL_FLASH_P1 == deviceContext->flash_type) ||
      (EXTERNAL_FLASH_P2 == deviceContext->flash_type))
  {
    fw_buffer = deviceContext->fw_img_data;
  }
  else
  {
    fw_buffer = deviceContext->fw_main_blk_data;
  }

  for (blockNum = 0; blockNum < blockCount; blockNum++)
  {
    // Write Sector to RAM: [ADDR][W][_CMD_FLASH_BUF_WRITE][DATA0][DATA1]...[DATAN-1]
    status = EcI2cBlockWriteToRam(
        EC_FLASH_BUF_WRITE_CMD,
        (void*)&(fw_buffer[blockNum * EC_MAX_WRITE_SECTOR_TO_RAM]),
        EC_MAX_WRITE_SECTOR_TO_RAM);
    if (EFI_ERROR(status))
    {
      EC_E("EcI2cBlockWriteToRam() for block: %d, flash: %d failed with %r\n",
        blockNum, deviceContext->flash_type, status);
      goto Exit;
    }

    addr = deviceContext->start_addr + (blockNum * EC_MAX_WRITE_SECTOR_TO_FLASH);
    status = EcFlashToSpiRom(
        EC_WRITE_DATABUF_TO_SPI_ROM_CMD,
        &addr,
        EC_MAX_WRITE_SECTOR_TO_FLASH);
    EC_ERROR_HANDLER(status, EcFlashToSpiRom, Exit);

    if (blockNum % 16 == 0)
    {
      EC_W("\r blk(256B) %d / %d written - Addr 0x%x", blockNum, blockCount, addr);
      if (writeProgress < PROGRESS_EC_FW_CAPSULE_UPDATE_END)
      {
        writeProgress += progressChunk;
        EcFwUpdateProgress(writeProgress);
      }
    }

    // 10ms, supported Ext. flash need 700us response time for each sector write
    SleepMs(10000);
  }

Exit:
  return status;
}

/**
 * @brief Function to trigger EC Checksum operation.
 * [EC_MODE_CMD][BYTECNT1][RUN_MAIN_CHECKSUM_CMD] Entry EC Boot-Block
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRunChecksum(EC_FLASH_PARTITION_INFO flashType)
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         wdBuf = RUN_INT_MBK_CHECKSUM_CMD; //Run checksum
  EC_TRACE();

  if ((flashType <= UNKNOWN_FLASH_INFO) ||
    (flashType >= MAX_LIMIT_FLASH_INFO))
  {
    EC_E("flashType is Invalid: %d\n", flashType);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (EXTERNAL_FLASH_P1 == flashType)
  {
    wdBuf = RUN_EXT_1ST_PARTITION_CHECKSUM_CMD;
  }
  else if (EXTERNAL_FLASH_P2 == flashType)
  {
    wdBuf = RUN_EXT_2ND_PARTITION_CHECKSUM_CMD;
  }
  else if ((INTERNAL_FLASH_P1 == flashType) ||
    (INTERNAL_FLASH_MBK_P1 == flashType))
  {
    wdBuf = RUN_INT_ACTIVE_CHECKSUM_CMD;
  }
  else if ((INTERNAL_FLASH_P2 == flashType) ||
    (INTERNAL_FLASH_MBK_P2 == flashType))
  {
    wdBuf = RUN_INT_BACKUP_CHECKSUM_CMD;
  }

  status = EcI2cBlockWrite(EC_MODE_CMD, &wdBuf, 1);
  EC_ERROR_HANDLER(status, EcI2cBlockWrite, Exit);

Exit:
  return status;
}

/**
 * @brief Function to program the EC firmware
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
static EFI_STATUS
EcProgramFirmware(void)
{
  EFI_STATUS status = EFI_SUCCESS;
  EC_TRACE();

  status = EcSelectSpiFlash();
  EC_ERROR_HANDLER(status, EcSelectSpiFlash, Exit);

  status = EcCheckFwStatus();
  EC_ERROR_HANDLER(status, EcCheckFwStatus, Exit);

  status = EcEraseSpiFlash();
  EC_ERROR_HANDLER(status, EcEraseSpiFlash, Exit);

  status = EcWriteSpiFlash();
  EC_ERROR_HANDLER(status, EcWriteSpiFlash, Exit);

Exit:
  return status;
}

/**
 * @brief Function to finalize the reflashing process.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
static EFI_STATUS
EcFinalizeReflash(EC_FLASH_PARTITION_INFO flashType)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT8      cycle_ms = 100;
  UINT16     max_attempt = 400;
  EC_TRACE();

  if ((flashType <= UNKNOWN_FLASH_INFO) ||
    (flashType >= MAX_LIMIT_FLASH_INFO))
  {
    EC_E("flashType is Invalid: %d\n", flashType);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  EC_W("Partition Type: %d\n", flashType);
   /*
   * TRUE indicates SPI service is IDLE,
   * FALSE indicates SPI service is BUSY
   */
  EC_W("WaitForEcSpiService()...\n");
  status = WaitForEcSpiService(100, 40);
  EC_ERROR_HANDLER(status, WaitForEcSpiService, Exit);

  EC_W("Entering BBK...\n");
  status = EcEnterBBK();
  EC_ERROR_HANDLER(status, EcEnterBBK, Exit);

  status = WaitForEnterIntoBootBlock(cycle_ms, max_attempt);
  EC_ERROR_HANDLER(status, WaitForEnterIntoBootBlock, Exit);

  EC_W("Sleep 10msec...\n");
  SleepMs(TIME_10MS);

  EC_W("EcRunChecksum()...\n");
  status = EcRunChecksum(flashType);
  EC_ERROR_HANDLER(status, EcRunChecksum, Exit);

  /* Safe delay for calculating the checksum */
  SleepMs(TIME_100MS);

  /* Wait till internal checksum result is computed */
  status = ((IsInternalFlashPartition(flashType)) ?
    WaitForEcChecksumResult(TIME_1SEC):WaitForEcChecksumResult(TIME_30MS));
  EC_ERROR_HANDLER(status, WaitForEcChecksumResult, Exit);

  status = EcExitBBK();
  EC_ERROR_HANDLER(status, EcExitBBK, Exit);

  status = WaitForEnterIntoMainBlock(cycle_ms, max_attempt);
  EC_ERROR_HANDLER(status, WaitForEnterIntoMainBlock, Exit);

Exit:
  return status;
}

/**
 * @brief Function to check the EC FW status
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcCheckFwStatus(void)
{

  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         uData[3] = {0,};
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = EcI2cBlockRead(
    EC_SPI_SERVICE_CMD,
    uData,
    sizeof(uData),
    0,
    0);
  if (EFI_ERROR(status))
  {
    EC_E("EcI2cBlockRead(EC_SPI_SERVICE_CMD) failed with %r\n", status);
    deviceContext->fw_status = UNKNOWN_BLK;
    goto Exit;
  }

  if (EC_FW_IN_BOOT_BLK_IDLE == uData[0])
  {
    EC_W("FW is running in Boot Block!\n");
    deviceContext->fw_status =  BOOT_BLK;
  }
  else if (EC_FW_IN_MAIN_BLK_IDLE == uData[0])
  {
    EC_I("FW is running in Main Block!\n");
    deviceContext->fw_status = MAIN_BLK;
  }
  else
  {
    EC_I("FW is running in Unknown Block!\n");
    deviceContext->fw_status = UNKNOWN_BLK;
  }

Exit:
  return status;
}

/**
 * @brief Function to enter into the EC boot block: [EC_MODE_CMD][BYTECNT1[EC_ENTER_BBK_CMD] Entry EC Boot-Block
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcEnterBBK(void)
{
  UINT8         wdBuf = ENTER_BBK_CMD;
  EFI_STATUS    status = EFI_SUCCESS;
  EC_TRACE();

  status = EcI2cBlockWrite(EC_MODE_CMD, &wdBuf, 1);
  EC_ERROR_HANDLER(status, EcI2cBlockWrite, Exit);

Exit:
  return status;
}

/**
 * @brief Function to exit out of the EC Boot Block.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcExitBBK(void)
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         wdBuf = EXIT_BBK_CMD; //Exit BBK mode
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (BOOT_BLK != deviceContext->fw_status)
  {
    EC_I("EC is not running in boot block, skipping the exit request.\n");
    goto Exit;
  }

  status = EcI2cBlockWrite(EC_MODE_CMD, &wdBuf, 1);
  EC_ERROR_HANDLER(status, EcI2cBlockWrite, Exit);

  /* Delay to jump from BBK->MBK */
  SleepMs(TIME_20MS);

Exit:
  return status;
}

/**
 * @brief Function to Recover/Copy/Rollback th FW content from one partition
 * to another partition.
 * COPY_INT_P1MBK_TO_P2 implies copy FW content from P1MBK to P2MBK
 * COPY_INT_P2MBK_TO_P1 implies copy FW content from P2MBK to P1MBK
 *
 * @param wdBuf      Direction to copy FW content from one partition to another.
 * @param flash_type Implies partition flash Type in internal eFlash of EC
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcFirmwareSync(
  UINT8 wdBuf,
  EC_FLASH_PARTITION_INFO flash_type
  )
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         wBuf   = 0;
  EC_TRACE();

  if (!wdBuf)
  {
    EC_E("Buffer Value not valid!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((flash_type <= UNKNOWN_FLASH_INFO) ||
    (flash_type >= MAX_LIMIT_FLASH_INFO))
  {
    EC_E("flashType is Invalid: %d\n", flash_type);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (COPY_INT_P1MBK_TO_P2 == wdBuf)
  {
    /*
     * TRUE indicates SPI service is IDLE,
     * FALSE indicates SPI service is BUSY
     */
    status = WaitForEcSpiService(100, 40);
    EC_ERROR_HANDLER(status, WaitForEcSpiService, Exit);

    EC_W("Syncing the BBK...\n");
    wBuf = (wdBuf == COPY_INT_P1MBK_TO_P2) ?
      COPY_INT_P1BBK_TO_P2 : COPY_INT_P2BBK_TO_P1;

    status = EcI2cBlockWrite(EC_MODE_CMD, &wBuf, 1);
    EC_ERROR_HANDLER(status, EcI2cBlockWrite, Exit);

    SleepMs(TIME_500MS); //Need to fine tune
  }


  /*
   * TRUE indicates SPI service is IDLE,
   * FALSE indicates SPI service is BUSY
   */
  status = WaitForEcSpiService(100, 40);
  EC_ERROR_HANDLER(status, WaitForEcSpiService, Exit);

  EC_W("Syncing the MBK...\n");
  status = EcI2cBlockWrite(EC_MODE_CMD, &wdBuf, 1);
  EC_ERROR_HANDLER(status, EcI2cBlockWrite, Exit);

  SleepMs(TIME_1SEC); //Need to fine tune

  status = EcFinalizeReflash(flash_type);
  EC_ERROR_HANDLER(status, EcFinalizeReflash, Exit);

Exit:
  return status;
}

/**
 * @brief Function to enable EC flashing process.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 **/
EFI_STATUS
EcEnableFlashing()
{
  EFI_STATUS    status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (UNKNOWN_BLK == deviceContext->fw_status)
  {
    EC_E("EC Firmware status is invalid (%d)\n", deviceContext->fw_status);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((UNKNOWN_BLK == deviceContext->fw_status) &&
      (IsInternalFlashPartition(deviceContext->flash_type)))
  {
    EC_I("Trying to enter boot block mode.\n");

    status = EcEnterBBK();
    EC_ERROR_HANDLER(status, EcEnterBBK, Exit);
  }

  status = EcCheckFwStatus();
  EC_ERROR_HANDLER(status, EcCheckFwStatus, Exit);

  /* Reconfirm if the FW is in MAIN or BOOT block */
  if (UNKNOWN_BLK == deviceContext->fw_status)
  {
    EC_E("Error in reconfirming EC FW status (%d)!\n", deviceContext->fw_status);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  else if (MAIN_BLK == deviceContext->fw_status)
  {
    EC_E("FW is still in MAIN BLK mode!\n");
  }
  else if (BOOT_BLK == deviceContext->fw_status)
  {
    EC_I("FW successfully entered to BOOT BLK mode!\n");
  }

  /*
   * TRUE indicates SPI service is IDLE,
   * FALSE indicates SPI service is BUSY
   */
  status = WaitForEcSpiService(100, 5);
  EC_ERROR_HANDLER(status, WaitForEcSpiService, Exit);

  EC_W("status = %r\n", status);

Exit:
  return status;
}

/**
 * @brief Entry point to parse and flash the EC firmware image using selected protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcReflashFirmware(void)
{
  EFI_STATUS status = 0;
  UINT8      actv_protocol_status = 0;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = GetNvEcFwActiveProtocolStatus(&actv_protocol_status);
  if ((EFI_NOT_FOUND == status) ||
     (EFI_BUFFER_TOO_SMALL == status))
  {
    status = SetNvEcFwActiveProtocolStatusDonotFlush(0);
    EC_ERROR_HANDLER(status, SetNvEcFwActiveProtocolStatusDonotFlush, Exit);
  }
  deviceContext->active_protocol = actv_protocol_status;
  EC_W("Active Protocol Status: %d \n", deviceContext->active_protocol);

  switch (deviceContext->active_protocol)
  {
    case ACPI_I2C_PROTOCOL:
      status = EcReflashUsingACPII2C();
      EC_ERROR_HANDLER(status, EcReflashUsingACPII2C, Exit);
      break;

     case RECOVERY_I2C_PROTOCOL:
       status = EcReFlashUsingRecovery();
       EC_ERROR_HANDLER(status, EcReFlashUsingRecovery, Exit);
       break;

     default:
       EC_E("Invalid active_protocol %d\n", deviceContext->active_protocol);
       status = EFI_DEVICE_ERROR;
       goto Exit;
  }

  EC_W("status = %r\n", status);

Exit:
  return status;
}

/**
 * @brief Entry point to parse and flash the EC firmware image,
 * using ACPI over I2C protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcReflashUsingACPII2C()
{
  EFI_STATUS status = 0;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = EcParseFwImage();
  EC_ERROR_HANDLER(status, EcParseFwImage, Exit);

  EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_PREPARE_END);

  status = EcEnableFlashing();
  EC_ERROR_HANDLER(status, EcEnableFlashing, Exit);

  EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_UPDATE_START);

  status = EcProgramFirmware();
  EC_ERROR_HANDLER(status, EcProgramFirmware, Exit);

  status = EcFinalizeReflash(deviceContext->flash_type);
  EC_ERROR_HANDLER(status, EcFinalizeReflash, Exit);

  SleepMs(500000);
  EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_UPDATE_END);

Exit:
  return status;

}

/**
 * @brief Function to copy firmware from internal flash to selected external flash partition.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcInt2ExtSPICopy(void)
{
  EFI_STATUS status = EFI_SUCCESS;
  EC_TRACE();

  status = EcI2cCmdWriteOnly(EC_ACPI_Int2Ext_SPI_COPY_CMD);
  EC_ERROR_HANDLER(status, EcI2cCmdWriteOnly, Exit);

  /* Wait for atleast 100 seconds to copy the
     internal FW to Ext SPINOR Active Partition
  */
  for(int i =0; i<10; i++)
  {
    SleepMs(TIME_10SEC);
  }

Exit:
  return status;
}

/**
 * @brief Function to request issuing H/W based force code mirror operation.
 *
 * @param forceMirrorCommand  Command to issue H/W force-code mirror operation
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcForceMirror(UINT8 forceMirrorCommand)
{
  UINT8         wdBuf = forceMirrorCommand;
  EFI_STATUS    status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((0 > deviceContext->fw_status) ||
      (UNKNOWN_BLK == deviceContext->fw_status))
  {
    EC_E("Error in EC FW status = %d!!\n", deviceContext->fw_status);
    status = EFI_NOT_READY;
    goto Exit;
  }

  if (MAIN_BLK == deviceContext->fw_status)
  {
    EC_W("Trying to enter boot blk mode.\n");
    status = EcEnterBBK();
    EC_ERROR_HANDLER(status, EcEnterBBK, Exit);
  }

  status = EcCheckFwStatus();
  EC_ERROR_HANDLER(status, EcCheckFwStatus, Exit);

  if ((0 > deviceContext->fw_status) ||
      (UNKNOWN_BLK == deviceContext->fw_status))
  {
    EC_E("Error in re-confirming EC FW status (%d)!\n", deviceContext->fw_status);
    status =  EFI_DEVICE_ERROR;
    goto Exit;
  }
  else if (MAIN_BLK == deviceContext->fw_status)
  {
    EC_I("FW is still in MAIN BLK mode, proceeding!!\n");
  }
  else if (BOOT_BLK == deviceContext->fw_status)
  {
    EC_I("FW successfully entered to Boot Block!\n");
  }
  else
  {
    EC_E("FW is in Unknown FW status!!\n");
    status = EFI_NOT_READY;
    goto Exit;
  }

  status = EcI2cBlockWrite(EC_MODE_CMD, &wdBuf, 1);
  EC_ERROR_HANDLER(status, EcI2cBlockWrite, Exit);

  // Wait for H/W Code-Mirror operation to complete.
  SleepMs(TIME_5SEC);

Exit:
  return status;
}

/**
 * @brief Function to erase designated region within internal/external flash
 *
 * @param cycle_ms  Sleep time for EC SPI service
 * @param retry     Max retry for EC SPI service
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcEraseDesignatedFlash(UINT16 cycle_ms, UINT8 retry)
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         wdBuf[5] = {0,};
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  wdBuf[0] = deviceContext->ctrl_path;
  wdBuf[1] = deviceContext->erase_blockCount;
  wdBuf[2] = (UINT8)(*((unsigned int*)(&deviceContext->start_addr)) & 0xFF);         //ADDRL
  wdBuf[3] = (UINT8)((*((unsigned int*)(&deviceContext->start_addr)) >> 8) & 0xFF);  //ADDRM
  wdBuf[4] = (UINT8)((*((unsigned int*)(&deviceContext->start_addr)) >> 16) & 0xFF); //ADDRH

  status = EcI2cBlockWrite(EC_ERASE_DESIGNATED_FLASH_AREA_CMD, &(wdBuf[0]), 5);
  EC_I("EcI2cBlockWrite() for EC_ERASE_DESIGNATED_FLASH_AREA_CMD returned %r\n", status);

  status = WaitForEcSpiService(cycle_ms,retry);
  EC_ERROR_HANDLER(status, WaitForEcSpiService, Exit);

Exit:
  return status;
}

/**
 * @brief Function to handle operations to be done post the firmware update.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcPostFwUpdate()
{
  EFI_STATUS                status = EFI_SUCCESS;
  UINT16                    cycle_ms = 50;
  UINT8                     max_attempt = 5;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = EcCheckFwStatus();
  EC_ERROR_HANDLER(status, EcCheckFwStatus, Exit);

  if (MAIN_BLK == deviceContext->fw_status)
  {
    EC_W("Trying to enter Boot block mode.\n");
    status = EcEnterBBK();
    EC_ERROR_HANDLER(status, EcEnterBBK, Exit);

    status = WaitForEnterIntoBootBlock(cycle_ms, max_attempt);
    if (EFI_ERROR(status))
    {
      EC_E("EC is not running in Boot block, fw_status : %d\n",
        deviceContext->fw_status);
      status = EFI_NOT_READY;
      goto Exit;
    }
    deviceContext->fw_status = BOOT_BLK;
  }

  /*
   * Trigger checksum calculation for newly copied
   * partition to ensure the firmware content is valid.
   */
  status = EcFinalizeReflash(deviceContext->flash_type);
  EC_ERROR_HANDLER(status, EcFinalizeReflash, Exit);

  deviceContext->is_fw_corrupted = 0;

  EC_I("Trying to exit from Boot block mode.\n");
  status = EcExitBBK();
  EC_ERROR_HANDLER(status, EcExitBBK, Exit);

  status = WaitForEnterIntoMainBlock(cycle_ms, max_attempt);
  if (EFI_ERROR(status))
  {
    EC_E("EC is not running in Main block, fw_status : %d\n",
      deviceContext->fw_status);
    status = EFI_NOT_READY;
    goto Exit;
  }
  deviceContext->fw_status = MAIN_BLK;

  status = EcFirmwareSync(COPY_INT_P1MBK_TO_P2, INTERNAL_FLASH_P2);
  EC_ERROR_HANDLER(status, EcFirmwareSync, Exit);

  EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_UPDATE_END);

Exit:
  return status;
}

/**
 * @brief Function to wait for Firmware to Enter into Main Block (MBK)
 *
 * @param   cycle_ms         Each cycle sleep time.
 * @param   max_retry        Num of maximum retries.
 *
 * @retval status            A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
WaitForEnterIntoMainBlock(UINT16 cycle_ms, UINT8 max_retry)
{
  UINT8         times = 0;
  EFI_STATUS    status = EFI_SUCCESS;
  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_I("Wait for EC Firmwaer To Enter into Main Block\n");

  do
  {
    SleepMs(cycle_ms*1000);

    status = EcCheckFwStatus();
    if (EFI_ERROR(status))
    {
      EC_E("EcCheckFwStatus() failed %r, ignore and continue\n", status);
      status = EFI_SUCCESS;
      goto Exit;
    }

    if (MAIN_BLK == deviceContext->fw_status)
    {
      EC_I("EC Firmware is in Main Block\n");
      goto Exit;
    }

    times++;
    EC_P(" .");

  } while(times < max_retry);

  EC_P(" \n");

  if (times == max_retry)
  {
    EC_E("EC Firmware is not in Main Block and operation timed out!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  return status;
}

/**
 * @brief Function to wait for Firmware to Enter into Boot Block (BBK)
 *
 * @param   cycle_ms         Each cycle sleep time.
 * @param   max_retry        Num of maximum retries.
 *
 * @retval status            A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
WaitForEnterIntoBootBlock(UINT16 cycle_ms, UINT8 max_retry)
{
  UINT8         times = 0;
  EFI_STATUS    status = EFI_SUCCESS;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_I("Wait for EC Firmware To Enter into Boot Block\n");

  do
  {
    SleepMs(cycle_ms*1000);

    status = EcCheckFwStatus();
    if (EFI_ERROR(status))
    {
      EC_E("EcCheckFwStatus() failed %r, ignore and continue\n", status);
      status = EFI_SUCCESS;
      goto Exit;
    }

    if (BOOT_BLK == deviceContext->fw_status)
    {
      EC_I("EC Firmware is in Boot Block\n");
      goto Exit;
    }

    times++;
    EC_P(" .");

  } while(times < max_retry);

  EC_P(" \n");

  if (times == max_retry)
  {
    EC_E("EC Firmware is not in Boot Block and operation timed out!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  return status;
}
