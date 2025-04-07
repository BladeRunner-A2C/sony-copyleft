/** @file EcRecovery.c

  Provides routines to erase/update/verify internal flash using H/W predefine protocol.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
2023/05/05     ananns        Added function to exit from BBK in EcReFlashUsingRecovery
2023/07/04     ananns        Removed EC Recovery verify function from the predefine sequence
2023/02/04     sumesahu      FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
2022/12/08     bkulkarn      Update Hamoa EC FW partition size/I2C core instance, code refactoring
2022/09/22     bkulkarn      Initial version
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
#include "EcRecovery.h"

extern EC_DEVICE_CONTEXT *deviceContext;

/**
 * Entry function to trigger reset operation using recovery protocol
 *
 * @param None
 *
 * @retval status       A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryReset()
{
  EFI_STATUS        status = EFI_SUCCESS;
  i2c_descriptor    buffer_desc[2] = {{0}};
  UINT8             buf0[1] = {EFLASH_CMD_CHIP_SELECT};
  UINT8             buf1[2] = {EFLASH_RESET_PATTERN1, EFLASH_RESET_PATTERN2};
  i2c_status        i2c_sts = I2C_SUCCESS;
  UINT32            bytes_written = 0;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  /* Reset EC using pre-define command.*/
  buffer_desc[0].buffer = buf0;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  buffer_desc[1].buffer = buf1;
  buffer_desc[1].length = 2;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->recovery_slave_config),
    buffer_desc,
    2,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("- Failed to transfer I2C. Error = %d\n", i2c_sts);
    status = EFI_NOT_READY;
    goto Exit;
  }
  EC_D( "Total bytes written: %d\n", bytes_written);

  SleepMs(TIME_10MS);

Exit:
  return status;
}

/**
 * Entry function to read the command completion status using recovery protocol.
 *
 * @param cycleMs       Value indicating delay in ms per iteration.
 * @param maxAttempt    Value indicating max number of retries to be done.
 * @param checkBit      Mask to be used to evaluate the read status.
 * @param checkValue    Value indicating expectation of the masked evaluation
 *                        0: To evaluate if masked bit to be cleared in the read status.
 *                        1: To evaluate if masked bit to be set in the read status.
 *
 * @retval status       A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryCmdStatus(
  UINT16 cycleMs,
  UINT8 maxAttempt,
  UINT8 checkBit,
  UINT8 checkValue)
{
  EFI_STATUS        status = EFI_SUCCESS;
  unsigned int      attempt = 0;
  UINT8             ec_spi_status = 0;
  UINT8             result = 0;

  do
  {
    SleepMs(cycleMs*1000);

    status = EcI2cPredefineBlockRead(
      EFLASH_CMD_READ_STATUS,
      &ec_spi_status,
      1,
      0,
      0);
    EC_ERROR_HANDLER(status, EcI2cPredefineBlockRead, Exit);

    EC_D("EFLASH_CMD_READ_STATUS: 0x%X\n", ec_spi_status);

    if (checkValue == 0)
    {
      if ((ec_spi_status & checkBit) == 0)
      {
        result = 1;
        break;
      }
    }

    if (checkValue == 1)
    {
      if ((ec_spi_status & checkBit) > 0)
      {
        result = 1;
        break;
      }
    }
    // If EC is busy continue retry
    attempt++;
  } while (attempt < maxAttempt);

  if (!result)
  {
    status = EFI_NOT_READY;
    EC_E("\nEC SPI service busy!\n");
    goto Exit;
  }

Exit:
  return status;
}

/**
 * Entry function to read the EC flash ID registers using recovery protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryGetFlashID()
{
  EFI_STATUS        status = EFI_SUCCESS;
  unsigned char     flash_id[3] = {0,};
  UINT16            timeout_ms = 30;
  UINT8             max_attempt = 3;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  // Read the SPI Flash ID
  status = EcI2cPredefineBlockRead(
    EFLASH_CMD_READ_ID,
    flash_id,
    sizeof(flash_id),
    timeout_ms,
    max_attempt);
  EC_ERROR_HANDLER(status, EcI2cPredefineBlockRead, Exit);

  if ((flash_id[0] != 0xFF) ||
      (flash_id[1] != 0xFF) ||
      (flash_id[2] != 0xFE))
  {
    EC_E("Mismatch in EC Flash ID = %x %x %x\n",
      flash_id[0], flash_id[1], flash_id[2]);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_I("EC Internal Flash ID = %x %x %x\n",
    flash_id[0], flash_id[1], flash_id[2]);

  CopyMem(&deviceContext->register_info.flash_id, flash_id, sizeof(flash_id));

Exit:
  return status;
}

/**
 * Entry function to read the EC Chip ID registers using recovery protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryGetChipID()
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         chipId1 = 0;
  UINT8         chipId2 = 0;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  /* Read EC Chip ID1 register */
  status = EcI2EcReadByte(
    EC_CHIPID1_REG_ADDR,
    &chipId1);
  EC_ERROR_HANDLER(status, EcI2EcReadByte, Exit);

  EC_I("EC CHIPID1: 0x%X\n", chipId1);

  SleepMs(TIME_1MS);

  /* Read EC Chip ID2 register */
  status = EcI2EcReadByte(
    EC_CHIPID2_REG_ADDR,
    &chipId2);
  EC_ERROR_HANDLER(status, EcI2EcReadByte, Exit);

  EC_I("EC CHIPID2: 0x%X\n", chipId2);

  SleepMs(TIME_1MS);

  deviceContext->register_info.chipID = ((uint16) chipId1 << 0x8) | chipId2;

  EC_I("EC CHIPID: 0x%X\n", deviceContext->register_info.chipID);

Exit:
  return status;
}

/**
 * Entry function to read the EC firmware using recovery protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryVerify()
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT16        blockNum = 0;
  UINT16        blockCount = 0;
  unsigned int  addr = 0;
  UINT8         rdBuff[EC_READ_MAX_BYTES_FROM_EFLASH] = {0,};
  UINT8         fwData[EC_READ_MAX_BYTES_FROM_EFLASH] = {0,};
  UINT8         wdBuf[4] = {0,};
  int           result = 0;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->fw_img_data)
  {
    EC_E("fw_img_data is invalid!");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  blockCount = (deviceContext->end_addr / EC_WRITE_MAX_BYTES_TO_EFLASH);

  EC_I("Total block count %d, each of %d bytes to be read\n",
    blockCount, EC_WRITE_MAX_BYTES_TO_EFLASH);

  for (blockNum = 0; blockNum < blockCount; blockNum++)
  {
    status = EcI2cPredefineSend(EFLASH_CMD_WRITE_DISABLE);
    EC_ERROR_HANDLER(status, EcI2cPredefineSend, Exit);

    addr = deviceContext->start_addr + (blockNum * EC_READ_MAX_BYTES_FROM_EFLASH);

    wdBuf[0] = (UINT8)((*((unsigned int*)(&addr)) >> 16) & 0xFF);
    wdBuf[1] = (UINT8)((*((unsigned int*)(&addr)) >> 8) & 0xFF);
    wdBuf[2] = (UINT8)(*((unsigned int*)(&addr)) & 0xFF);
    wdBuf[3] = 0x0;

    status = EcI2cPredefineFastRead(
      EFLASH_CMD_FAST_READ,
      wdBuf,
      4,
      rdBuff,
      EC_READ_MAX_BYTES_FROM_EFLASH);
    EC_ERROR_HANDLER(status, EcI2cPredefineFastRead, Exit);

    CopyMem(
      fwData,
      (UINT8*)&(deviceContext->fw_img_data[blockNum*EC_READ_MAX_BYTES_FROM_EFLASH]),
      EC_READ_MAX_BYTES_FROM_EFLASH);

    result = CompareMem(
      rdBuff,
      fwData,
      EC_READ_MAX_BYTES_FROM_EFLASH);
    if (result)
    {
      EC_E("Firmware content mismatch between data flashed & read from EC for blockNum: %d\n",
        blockNum);
      status = EFI_DEVICE_ERROR;
      goto Exit;
    }
  }

  EC_I("Successfully validated the firmware contents\n");

Exit:
  return status;
}

/**
 * Entry function to erase the EC firmware on hardware using recovery protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryErase()
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         wdBuf[3] = {0,};
  int           addr = 0;
  UINT16        cycleMs = 1;
  UINT8         maxAttempt = 5;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  for (addr = 0; addr < deviceContext->end_addr; addr += INT_FLASH_ERASE_SECTOR_SIZE)
  {
    status = EcI2cPredefineSend(EFLASH_CMD_WRITE_ENABLE);
    EC_ERROR_HANDLER(status, EcI2cPredefineSend, Exit);

    status = EcRecoveryCmdStatus(cycleMs, maxAttempt, SPIROM_WRITE_ENABLE_BIT, 1);
    EC_ERROR_HANDLER(status, EcRecoveryCmdStatus, Exit);

    wdBuf[0] = (UINT8)((*((unsigned int*)(&addr)) >> 16) & 0xFF);
    wdBuf[1] = (UINT8)((*((unsigned int*)(&addr)) >> 8) & 0xFF);
    wdBuf[2] = (UINT8)(*((unsigned int*)(&addr)) & 0xFF);

    status = EcI2cPredefineBlockWrite(EFLASH_CMD_SECTOR_ERASE, wdBuf, 3);
    EC_ERROR_HANDLER(status, EcI2cPredefineBlockWrite, Exit);

    // Check if the EC SPI bus is IDLE
    status = EcRecoveryCmdStatus(cycleMs, maxAttempt, SPIROM_BUSY_BIT, 0);
    EC_ERROR_HANDLER(status, EcRecoveryCmdStatus, Exit);

    status = EcI2cPredefineSend(EFLASH_CMD_WRITE_DISABLE);
    EC_ERROR_HANDLER(status, EcI2cPredefineSend, Exit);

    EC_W("Erased - %d / 32K\r", addr/1024);
  }

  EC_W("Erasing of flash (%d) completed successfully\n", deviceContext->flash_type);

Exit:
    return status;
}

/**
 * Entry function to program the EC firmware to hardware.
 * to enable recovery/pre-define protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryProgram()
{
  EFI_STATUS        status = EFI_SUCCESS;
  UINT16            blockNum = 0;
  UINT16            blockCount = 0;
  unsigned int      addr = 0;
  UINT8             data[EC_WRITE_MAX_BYTES_TO_EFLASH] = {0,};
  UINT8             wdBuf[5] = {0,};
  UINT8             wdBuf1[2] = {0,};
  UINT16            dataBufIndex = 0;
  UINT16            cycleMs = 1;
  UINT8             maxAttempt = 5;

  EC_TRACE();

  EC_W("EC FW Prepare Program Start. Time (ms): %lld\n", GetTimerCountms());

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->fw_img_data)
  {
    EC_E("fw_img_data is invalid!");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  blockCount = (deviceContext->end_addr / EC_WRITE_MAX_BYTES_TO_EFLASH);

  EC_I("Total block count %d, each of %d bytes to be flashed\n",
    blockCount, EC_WRITE_MAX_BYTES_TO_EFLASH);

  EC_I("Start Addr: 0x%X, Block Count: %d\n", deviceContext->start_addr, blockCount);

  for (blockNum = 0; blockNum < blockCount; blockNum++)
  {
    status = EcI2cPredefineSend(EFLASH_CMD_WRITE_ENABLE);
    EC_ERROR_HANDLER(status, EcI2cPredefineSend, Exit);

    status = EcRecoveryCmdStatus(cycleMs, maxAttempt, SPIROM_WRITE_ENABLE_BIT, 1);
    EC_ERROR_HANDLER(status, EcRecoveryCmdStatus, Exit);

    dataBufIndex = 0;
    addr = deviceContext->start_addr + (blockNum * EC_WRITE_MAX_BYTES_TO_EFLASH);

    CopyMem(
      data,
      (UINT8*)&(deviceContext->fw_img_data[blockNum*EC_WRITE_MAX_BYTES_TO_EFLASH]),
      EC_WRITE_MAX_BYTES_TO_EFLASH);

    wdBuf[0] = (UINT8)((*((unsigned int*)(&addr)) >> 16) & 0xFF);
    wdBuf[1] = (UINT8)((*((unsigned int*)(&addr)) >> 8) & 0xFF);
    wdBuf[2] = (UINT8)(*((unsigned int*)(&addr)) & 0xFF);
    wdBuf[3] = data[dataBufIndex];
    dataBufIndex++;
    wdBuf[4] = data[dataBufIndex];
    dataBufIndex++;

    status = EcI2cPredefineBlockWrite(EFLASH_CMD_AAI_WORD_PROGRAM, wdBuf, 5);
    EC_ERROR_HANDLER(status, EcI2cPredefineBlockWrite, Exit);

    // Check if EC SPI is idle
    status = EcRecoveryCmdStatus(cycleMs, maxAttempt, SPIROM_BUSY_BIT, 0);
    EC_ERROR_HANDLER(status, EcRecoveryCmdStatus, Exit);

    while (dataBufIndex < EC_WRITE_MAX_BYTES_TO_EFLASH)
    {
      wdBuf1[0] = data[dataBufIndex];
      dataBufIndex++;
      wdBuf1[1] = data[dataBufIndex];
      dataBufIndex++;

      status = EcI2cPredefineBlockWrite(EFLASH_CMD_AAI_WORD_PROGRAM, wdBuf1, 2);
      EC_ERROR_HANDLER(status, EcI2cPredefineBlockWrite, Exit);

      // Check if EC SPI is idle
      status = EcRecoveryCmdStatus(cycleMs, maxAttempt, SPIROM_BUSY_BIT, 0);
      EC_ERROR_HANDLER(status, EcRecoveryCmdStatus, Exit);
    }

    status = EcI2cPredefineSend(EFLASH_CMD_WRITE_DISABLE);
    EC_ERROR_HANDLER(status, EcI2cPredefineSend, Exit);
    
    if (blockNum % 64 == 0)
    {
      EC_W("Block %d (256Bytes) of %d written; Addr: 0x%x\r", blockNum, blockCount, addr);
    }
  }

  EC_W("EC FW Prepare Program End. Time (ms): %lld\n", GetTimerCountms());

Exit:
  return status;
}

/**
 * Entry function to perform the required initialization of H/W,
 * to enable recovery/pre-define protocol.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcRecoveryInit()
{
  EFI_STATUS    status = EFI_SUCCESS;

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  // Turns-Off the LPC Bus.
  status = EcI2EcWriteByte(RESET_STS_REG_ADDR, 0x40);
  EC_ERROR_HANDLER(status, EcI2EcWriteByte, Exit);

  SleepMs(TIME_5MS);

  // Switch to internal eFlash operation (1059h)
  status = EcI2EcWriteByte(SLAVE_FIFO_CTRL_REG_ADDR, 0x30);
  EC_ERROR_HANDLER(status, EcI2EcWriteByte, Exit);

  SleepMs(TIME_5MS);

  deviceContext->is_recovery_active = 1;
Exit:
    return status;
}

/**
 * Entry function to handle H/W predefine based FW update:
 *  - Erase the e-flash.
 *  - Program the e-flash.
 *  - Verify the update.
 *  - Perform EC reset.
 *
 * Note: The caller of this function should either perform the predefine H/W init
 * or ensure its not required.
 *
 * @param None
 *
 * @retval status  A EFI_STATUS indicating result of the operation.
 *
 **/
EFI_STATUS
EcReFlashUsingRecovery()
{
  EFI_STATUS    status = EFI_SUCCESS;
  EFI_STATUS    recoveryStatus = EFI_SUCCESS;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_W("######################################################################################\n");
  EC_W("#                                !!! WARNING !!!                                     #\n");
  EC_W("#   EC Firmware Update is in progress. Please do not power-off/shutdown the device   #\n");
  EC_W("#                                                                                    #\n");
  EC_W("######################################################################################\n");

  // Update attributes corresponding to Active/P1 partition of the internal eFlash.
  deviceContext->ctrl_path = INT_FLASH_P1_CTRL_PATH;
  deviceContext->flash_type = INTERNAL_FLASH_P1;
  deviceContext->start_addr = ACTIVE_BBK_START_ADDR;
  deviceContext->end_addr = ACTIVE_MBK_END_ADDR;
  deviceContext->erase_blockCount = 32;

  status = EcRecoveryInit();
  EC_ERROR_HANDLER(status, EcRecoveryInit, Exit);

  status = EcRecoveryErase();
  EC_ERROR_HANDLER(status, EcRecoveryErase, Exit);

  SleepMs(TIME_5MS);

  status = EcRecoveryProgram();
  EC_ERROR_HANDLER(status, EcRecoveryProgram, Exit);

  SleepMs(TIME_5MS);

  status = EcRecoveryReset();
  EC_ERROR_HANDLER(status, EcRecoveryReset, Exit);

  SleepMs(TIME_2SEC);

  /* Till this point FW programming is complete, so bypass. */
  recoveryStatus = EcCheckControlPath();
  EC_WARN_HANDLER(recoveryStatus, EcCheckControlPath);

  if (deviceContext->fw_status == UNKNOWN_BLK)
  {
    EC_E("Error due to unknown partition type %d\n", deviceContext->fw_status);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  if ((deviceContext) &&
    (deviceContext->fw_status == BOOT_BLK))
  {
    recoveryStatus  = EcExitBBK();
    EC_WARN_HANDLER(recoveryStatus , EcExitBBK);

    recoveryStatus  = EcCheckFwStatus();
    EC_WARN_HANDLER(recoveryStatus , EcCheckFwStatus);
  }

  return status;
}