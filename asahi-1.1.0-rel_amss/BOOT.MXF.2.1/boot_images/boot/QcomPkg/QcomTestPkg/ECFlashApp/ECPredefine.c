/** @file
   Contains routines to erase/update/verify internal e-flash using H/W predefine protocol.

Copyright (c) 2022-2023 Qualcomm Technologies Inc. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who                 what, where, why
 --------   ---                 ----------------------------------------------------------
 04/26/23   chic                 Refine i2c_block_read/write to support multiple type payload transaction
 03/03/23   bkulkarn             Switch to EfiShellProtocol to resolve UEFI panic for long filename
 12/08/22   bkulkarn             Update Hamoa EC FW partition size/I2C core instance, code refactoring
 11/14/22   ananns               Added code documentation and function descriptions
 8/17/22    bkulkarn             Initial revision
=============================================================================*/

#include <ECFlashApp.h>

unsigned char flash_id[3] = {0,};

/**
 * @brief Perform EC H/W reset
 *
 * @param None
 *
 * @retval EFI_SUCCESS         EC predefine reset is successfully.
 * @retval EFI_NOT_READY       I2C transfer is failed
 * @retval EFI_DEVICE_ERROR    Nothing is written to device
 */
EFI_STATUS
EcPredefineReset(void)
{
  EFI_STATUS        status = EFI_SUCCESS;
  i2c_descriptor    buffer_desc[2] = {{0}};
  UINT8             buf0[1] = {EFLASH_CMD_CHIP_SELECT};
  UINT8             buf1[2] = {0x5A, 0xA5};
  i2c_status        i2c_sts = I2C_SUCCESS;
  UINT32            bytes_written = 0;

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext handle!\n");
    status = EFI_DEVICE_ERROR;
    goto Error;
  }

  EC_TRACE();

  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("- i2c_handle NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Error;
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
  if (EFI_ERROR (i2c_sts))
  {
    EC_E("- Failed to transfer I2C. Error = %d\n", i2c_sts);
    status = EFI_NOT_READY;
    goto Error;
  }

  if (!bytes_written)
  {
    EC_E("- Nothing is written to device\n");
    status = EFI_DEVICE_ERROR;
    goto Error;
  }

  EC_D( "Total bytes written: %d\n", bytes_written);

  SleepMs(TIME_10MS);

Error:
  return status;
}

/**
 * @brief Checks EC H/W Predefine status
 *
 * @param cycleMs                Timeout value to support retry mechanism
 * @param maxAttempt             No of retry attempt
 * @param checkBit               check for the predefine status bit
 * @param checkValue             Ethier it can be 0 or 1
 *
 * @retval EFI_SUCCESS           EC predefine status read is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined block read is failed
 */
EFI_STATUS
EcPredefineStatus(
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

    status = i2c_predefine_block_read(
      EFLASH_CMD_READ_STATUS,
      &ec_spi_status,
      1,
      0,
      0);
    if (EFI_ERROR(status))
    {
      EC_E(" i2c_predefine_block_read() failed with %r\n", status);
      goto Exit;
    }

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
    EC_E("\nEC SPI service busy!\n");
    status = EFI_NOT_READY;
    goto Exit;
  }

Exit:
  return status;
}

/**
 * @brief Function to get the EC internal Flash ID
 *
 * @param None
 *
 * @retval EFI_SUCCESS           Reading EC predefine Flash ID is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined block read is failed
 */
EFI_STATUS
EcPredefineGetFlashID(void)
{
  EFI_STATUS status = EFI_SUCCESS;
  UINT16     cycleMs = 50;
  UINT16     maxAttempt = 10;

  // Read the SPI Flash ID
  status = i2c_predefine_block_read(
    EFLASH_CMD_READ_ID,
    flash_id,
    3,
    cycleMs,
    maxAttempt);
  if (EFI_ERROR(status))
  {
    EC_E("i2c_predefine_block_read() failed with %r\n", status);
    goto Exit;
  }

Exit:
  return status;
}

/**
 * @brief EC H/W Predefine Chip erase
 *
 * @param None
 *
 * @retval EFI_SUCCESS           EC flash chip erase is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined write is failed
 */
EFI_STATUS
EcPredefineChipErase(void)
{
  EFI_STATUS status = EFI_SUCCESS;

  status = i2c_predefine_send (EFLASH_CMD_CHIP_ERASE);
  if (EFI_ERROR(status))
  {
    EC_E(" i2c_predefine_send (EFLASH_CMD_WRITE_ENABLE) failed with %r\n", status);
    goto Exit;
  }

  SleepMs(TIME_4SEC);

Exit:
  return status;
}

/**
 * @brief EC H/W Predefine sector erase
 *
 * @param None
 *
 * @retval EFI_SUCCESS           EC flash sector erase is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined write is failed
 */
EFI_STATUS
EcPredefineErase(void)
{
  EFI_STATUS        status = EFI_SUCCESS;
  UINT8             wdBuf[3] = {0,};
  int               addr = 0;
  UINT16            cycleMs = 1;
  UINT8             maxAttempt = 5;

  for (addr = 0;
    addr < EFLASH_ADDR_END;
    addr+=INT_FLASH_ERASE_SECTOR_SIZE)
  {
    status = i2c_predefine_send (EFLASH_CMD_WRITE_ENABLE);
    if (EFI_ERROR (status))
    {
      EC_E(" i2c_predefine_send (EFLASH_CMD_WRITE_ENABLE) failed with %r\n", status);
      goto Exit;
    }

    status = EcPredefineStatus(
      cycleMs,
      maxAttempt,
      SPIROM_WRITE_ENABLE_BIT,
      1);
    if (EFI_ERROR(status))
    {
      EC_E("EcPredefineStatus(WRITE_ENABLE) failed with %r\n", status);
      goto Exit;
    }

    wdBuf[0] = (UINT8)((*((unsigned int*)(&addr)) >> 16) & 0xFF);
    wdBuf[1] = (UINT8)((*((unsigned int*)(&addr)) >> 8) & 0xFF);
    wdBuf[2] = (UINT8)(*((unsigned int*)(&addr)) & 0xFF);

    status = i2c_predefine_block_write(
      EFLASH_CMD_SECTOR_ERASE,
      wdBuf,
      3);
    if (EFI_ERROR (status))
    {
      EC_E("i2c_predefine_block_write(EFLASH_CMD_SECTOR_ERASE) failed with %r\n", status);
      goto Exit;
    }

    // Check if EC SPI is IDLE
    status = EcPredefineStatus(
      cycleMs,
      maxAttempt,
      SPIROM_BUSY_BIT,
      0);
    if (EFI_ERROR(status))
    {
      EC_E("EcPredefineStatus(SPIROM_BUSY) failed with %r\n", status);
      goto Exit;
    }

    status = i2c_predefine_send (EFLASH_CMD_WRITE_DISABLE);
    if (EFI_ERROR(status))
    {
      EC_E(" i2c_predefine_send (EFLASH_CMD_WRITE_DISABLE) failed with %r\n", status);
      goto Exit;
    }
    EC_I("Erased - %d / 32K\r", addr/1024);
  }

  EC_I("\nErasing of eFlash (%d / 32K) completed successfully\n", addr/1024);

Exit:
  return status;
}

/**
 * @brief EC H/W Predefine program the flash
 *
 * @param None
 *
 * @retval EFI_SUCCESS           Programming the EC flash is successfully.
 * @retval EFI_DEVICE_ERROR      I2C predefined write is failed
 * @retval EFI_INVALID_PARAMETER Invalid EC FW image
 */
EFI_STATUS
EcPredefineProgram(void)
{
  EFI_STATUS        status = EFI_SUCCESS;
  UINT16            blockNum = 0;
  UINT16            blockCount = EFLASH_ADDR_END / EC_WRITE_MAX_BYTES_TO_EFLASH;
  unsigned int      addr = 0;
  UINT16            dataBufIndex = 0;
  UINT16            cycleMs = 1;
  UINT8             data[EC_WRITE_MAX_BYTES_TO_EFLASH] = {0,};
  UINT8             wdBuf[5] = {0,};
  UINT8             wdBuf1[2] = {0,};
  UINT8             maxAttempt = 5;
  UINT8             wordProgramSize = 5;

  EC_I("EC FW Prepare Program Start. Time (ms): %lld\n", GetTimerCountms());

  EC_I("Total block count %d, each of %d bytes to be flashed\n", blockCount, EC_WRITE_MAX_BYTES_TO_EFLASH);

  if (!deviceContext)
  {
    EC_E("Invalid device context!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (!deviceContext->fw_img_data)
  {
    EC_E("Invalid EC FW image!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  EC_I("Start Addr: 0x%X, Block Count: %d\n", deviceContext->start_addr, blockCount);

  for (blockNum = 0; blockNum < blockCount; blockNum++)
  {
    status = i2c_predefine_send (EFLASH_CMD_WRITE_ENABLE);
    if (EFI_ERROR(status))
    {
      EC_E("i2c_predefine_send (EFLASH_CMD_WRITE_ENABLE) failed with %r\n", status);
      goto Exit;
    }

    status = EcPredefineStatus(
      cycleMs,
      maxAttempt,
      SPIROM_WRITE_ENABLE_BIT,
      1);
    if (EFI_ERROR(status))
    {
      EC_E("EcPredefineStatus(WRITE_ENABLE) failed with %r\n", status);
      goto Exit;
    }

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

    status = i2c_predefine_block_write(
      EFLASH_CMD_AAI_WORD_PROGRAM,
      wdBuf,
      wordProgramSize);
    if (EFI_ERROR(status))
    {
      EC_E("i2c_predefine_block_write(EFLASH_CMD_AAI_WORD_PROGRAM) failed with %r\n", status);
      goto Exit;
    }

    // Check if EC SPI is idle
    status = EcPredefineStatus(
      cycleMs,
      maxAttempt,
      SPIROM_BUSY_BIT,
      0);
    if (EFI_ERROR(status))
    {
      EC_E("i2c_predefine_block_write(SPIROM_BUSY) failed with %r\n", status);
      goto Exit;
    }

    while (dataBufIndex < EC_WRITE_MAX_BYTES_TO_EFLASH)
    {
      wdBuf1[0] = data[dataBufIndex];
      dataBufIndex++;
      wdBuf1[1] = data[dataBufIndex];
      dataBufIndex++;

      status = i2c_predefine_block_write(
        EFLASH_CMD_AAI_WORD_PROGRAM,
        wdBuf1,
        2);
      if (EFI_ERROR(status))
      {
        EC_E("i2c_predefine_block_write(EFLASH_CMD_AAI_WORD_PROGRAM) failed with %r\n", status);
        goto Exit;
      }

      // Check if EC SPI is idle
      status = EcPredefineStatus(
        cycleMs,
        maxAttempt,
        SPIROM_BUSY_BIT,
        0);
      if (EFI_ERROR(status))
      {
        EC_E("i2c_predefine_block_write(SPIROM_BUSY) failed with %r\n", status);
        goto Exit;
      }
    }

    status = i2c_predefine_send (EFLASH_CMD_WRITE_DISABLE);
    if (EFI_ERROR(status))
    {
      EC_E(" i2c_predefine_send (EFLASH_CMD_WRITE_DISABLE) failed with %r\n", status);
      goto Exit;
    }

    if (0 == blockNum%32)
    {
      EC_I("Block %d (256Bytes) of %d written; Addr: 0x%x\r", blockNum, blockCount, addr);
    }
  }

  EC_I("Block %d (256Bytes) of %d written, addr: 0x%x\n", blockNum, blockCount, addr);

  EC_I("\nEC FW Prepare Program End. Time (ms): %lld\n", GetTimerCountms());

Exit:
  return status;
}

/**
 * @brief EC H/W Predefine prepare the flash
 *
 * @param None
 *
 * @retval EFI_SUCCESS           Programming the EC flash is successfully.
 * @retval EFI_DEVICE_ERROR      I2C init/ write byte/mismatch flash ID is failed
 */
EFI_STATUS
EcPredefinePrepare(void)
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT8         chipID1 = 0, chipID2 = 0;

  if (!deviceContext)
  {
    EC_E("- deviceContext NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  /*
   * Prepare for pre-define FW update.
   */
  deviceContext->start_addr = EFLASH_ADDR_START;
  deviceContext->end_addr   = EFLASH_ADDR_END;


  // Turns-Off LPC Bus.
  status = i2ec_writebyte (
    RESET_STS_REG_ADDR,
    0x40);
  if (EFI_ERROR(status))
  {
    EC_E("i2ec_writebyte (RESET_STS_REG_ADDR) failed with %r\n", status);
    goto Exit;
  }

  SleepMs(TIME_5MS);

  // Read EC Chip ID1 register
  status = i2ec_readbyte (
    EC_CHIPID1_REG_ADDR,
    &chipID1);
  if (EFI_ERROR(status))
  {
    EC_E("i2ec_writebyte (EC_CHIPID1_REG_ADDR) failed with %r\n", status);
    goto Exit;
  }

  SleepMs(TIME_5MS);

  EC_D("EC_CHIPID1: 0x%X\n", chipID1);

  // Read EC Chip ID2 register
  status = i2ec_readbyte (
    EC_CHIPID2_REG_ADDR,
    &chipID2);
  if (EFI_ERROR(status))
  {
    EC_E("i2ec_writebyte (EC_CHIPID2_REG_ADDR) failed with %r\n", status);
    goto Exit;
  }

  SleepMs(TIME_5MS);

  EC_D("EC_CHIPID2: 0x%X\n", chipID2);

  deviceContext->ecChipID = (((uint16) chipID1 << 0x8) | chipID2);

  EC_I("EC_CHIPID: 0x%X\n", deviceContext->ecChipID);

  // Switch to internal eFlash operation (1059h)
  status = i2ec_writebyte (
    SLAVE_FIFO_CTRL_REG_ADDR,
    0x30);
  if (EFI_ERROR(status))
  {
    EC_E("i2ec_writebyte (SLAVE_FIFO_CTRL_REG_ADDR) failed with %r\n", status);
    goto Exit;
  }

  SleepMs(TIME_5MS);

  status = EcPredefineGetFlashID();
  if (EFI_ERROR(status))
  {
    EC_E("Get_Flash_ID failed with %r\n", status);
    status = EFI_DEVICE_ERROR;
  }

  if ((flash_id[0] != 0xFF) ||
    (flash_id[1] != 0xFF) ||
    (flash_id[2] != 0xFE))
  {
    EC_E("Mismatch in FLASH ID = %x %x %x,  ignoring..\n", flash_id[0], flash_id[1], flash_id[2]);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_I("EC Internal FLASH ID = %x %x %x\n", flash_id[0], flash_id[1], flash_id[2]);

Exit:
  return status;
}

/**
 * @brief Entry function to handle H/W predefine based FW update:
 *  1. Prepare for pre-define update.
 *  2. Erase the e-flash.
 *  3. Program the e-flash.
 *  4. Verify the update.
 *  5. Perform EC reset.
 *
 * @retval EFI_STATUS   A EFI_STATUS value indicating result of the operation.
 */
EFI_STATUS
EcPredefineUpdateMain()
{
  EFI_STATUS    status = EFI_SUCCESS;

  EC_I("Pre-define FW Update Start. Time (ms): %lld\n", GetTimerCountms());
  
  deviceContext->activeI2cChannel = RECOVERY_I2C_PROTOCOL;

  status = EcPredefinePrepare();
  if (EFI_ERROR(status))
  {
    EC_E("EcPredefinePrepare() failed with %r\n", status);
    goto Exit;
  }

  status = EcPredefineErase();
  if (EFI_ERROR(status))
  {
    EC_E("EcPredefineErase() failed with %r\n", status);
    goto Exit;
  }

  SleepMs(TIME_50MS);

  status = EcPredefineProgram();
  if (EFI_ERROR(status))
  {
    EC_E("EcPredefineProgram() failed with %r\n", status);
    goto Exit;
  }

  SleepMs(TIME_50MS);

  status = EcPredefineReset();
  if (EFI_ERROR(status))
  {
    EC_E("EcPredefineReset() failed with %r\n", status);
    goto Exit;
  }

  EC_I("Pre-define FW Update End. Time (ms): %lld\n", GetTimerCountms());

Exit:
  return status;
}
