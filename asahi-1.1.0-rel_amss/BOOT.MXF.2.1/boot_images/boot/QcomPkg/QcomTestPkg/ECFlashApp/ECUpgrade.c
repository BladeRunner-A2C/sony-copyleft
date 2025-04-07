/** @file
  EC_Upgrade is used to flash/Erase/ the EC firmware to external Flash

Copyright (c) 2021-2023 Qualcomm Technologies Inc. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who            what, where, why
 --------   ---            ----------------------------------------------------------
 04/26/23   chic           Refine i2c_block_read/write to support multiple type payload transaction
 12/08/22   bkulkarn       Update Hamoa EC FW partition size/I2C core instance, code refactoring
 11/14/22   ananns         Added code documentation and function descriptions
 10/17/21   sumesahu       Initial revision
=============================================================================*/

#include <ECFlashApp.h>

/**
  Send command process EC Data Bufer to internal eFlash SPI ROM

  @param buff                   Pointer to buff
  @param size                   size of the buffer

  @retval EFI_SUCCESS           EC flash to SPI ROM is successfull
  @retval EFI_DEVICE_ERROR      write to EC fails
  @retval EFI_OUT_OF_RESOURCES  size or buff is out of range
**/
static
EFI_STATUS
EC_Flash_To_SPIROM(
  void* buff,
  UINT16 size
  )
{

  EFI_STATUS  Status    = EFI_SUCCESS;
  UINT8       wdBuf[5]  = {0,};
  
  if ((size > EC_MAX_WRITE_SECTOR_TO_FLASH) ||
    (buff == NULL))
  {
    EC_E("- Error in buffer Size criteria:[%d]!!\n", size);
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext!\n");
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  
  EC_TRACE();

  wdBuf[0] = deviceContext->ctrl_path;
  switch (size)
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

  wdBuf[2] = (UINT8)(*((unsigned int*)(buff)) & 0xFF);         //ADDRL
  wdBuf[3] = (UINT8)((*((unsigned int*)(buff)) >> 8) & 0xFF);  //ADDRM
  wdBuf[4] = (UINT8)((*((unsigned int*)(buff)) >> 16) & 0xFF); //ADDRH

  Status = i2c_block_write (
    EC_WRITE_DATABUF_TO_SPI_ROM_CMD_WO,
    &(wdBuf[0]),
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_write() failed with %r\n", Status);
    goto Exit;
  }

Exit:
  return Status;
}

/**
  Parse the EC FW image

  @retval EFI_SUCCESS            Parsing of FW image is successfull
  @retval EFI_OUT_OF_RESOURCES   ec device or FW image is NULL
**/
EFI_STATUS
EC_Parse_FW_Image(void)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if ((deviceContext == NULL) || 
    (deviceContext->fw_img_data == NULL))
  {
    EC_E("- deviceContext or deviceContext->fw_img_data is NULL!!\n");
    Status = EFI_DEVICE_ERROR;
    goto Error;
  }

  EC_TRACE();

  deviceContext->fw_bbk_blk_data = (byte *) ((&(deviceContext->fw_img_data[0])) + ACTV_STARTUP_BLK_BUFFER_SIZE);
  deviceContext->fw_main_blk_data = (byte *) ((&(deviceContext->fw_img_data[0])) + ACTV_STARTUP_BLK_BUFFER_SIZE + ACTV_BOOT_BLK_BUFFER_SIZE);
  
  EC_I("Check: bbk[0x%x], mbk[0x%x], fw[0]:0x%x, fw[0x2000]:0x%x\n",
    deviceContext->fw_bbk_blk_data[0],
    deviceContext->fw_main_blk_data[0],
    deviceContext->fw_img_data[0],
    deviceContext->fw_img_data[0x2000]);

Error:
  return Status;
}


/**
  EC to select the External partition P1 or P2

  @retval EFI_SUCCESS        Selection of Flash is successfull
  @retval EFI_DEVICE_ERROR     Block write to EC fails
  @retval EFI_OUT_OF_RESOURCES  deviceContext is NULL
**/
static
EFI_STATUS
EC_Select_SPI_Flash(void)
{
  EFI_STATUS  Status  = EFI_SUCCESS;
  UINT8       buf     = 0;

  if (deviceContext == NULL)
  {
    EC_E("deviceContext is NULL\n");
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if ((deviceContext->flash_type == EXTERNAL_FLASH_P1) ||
    (deviceContext->flash_type == EXTERNAL_FLASH_P2))
  {
    buf = SEL_EXT_SPI_FLASH_CMD;
    deviceContext->erase_sector_size = EXT_FLASH_ERASE_SECTOR_SIZE;
    EC_I("Select External SPI Flash\n");
  }
  else if (deviceContext->flash_type == INTERNAL_FLASH)
  {
    buf = SEL_INT_SPI_FLASH_CMD;
    deviceContext->erase_sector_size = INT_FLASH_ERASE_SECTOR_SIZE;
    EC_I("Select Internal SPI eFlash\n");
  }
  else
  {
    buf = SEL_INT_SPI_FLASH_CMD;
    deviceContext->erase_sector_size = INT_FLASH_ERASE_SECTOR_SIZE;
    EC_E("- Flash Type is not supported, falling back to Internal Flash type\n");
  }

  Status = i2c_block_write (
    SPI_QUICK_CMD_WO,
    &buf,
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_write() failed with %r\n", Status);
    goto Exit;
  }

Exit:
  return Status;
}

/**
  Get EC Checksum Result

  @param timeout_ms             timeout value is used for retry mechanism

  @retval EFI_SUCCESS           checksum is matched successfull
  @retval EFI_DEVICE_ERROR      checksum is mismatched
**/
EFI_STATUS
Wait_For_EC_Checksum_Result(
  unsigned int timeout_ms
  )
{
  EFI_STATUS        Status        = EFI_SUCCESS;
  UINT8             ec_status[5]  = {0,};
  unsigned int      duration      = 100;  // 100ms is the minimum delay
  unsigned int      retry         = 0;

  retry = (timeout_ms <= 0) ?
    20 : (timeout_ms / duration); //default retry is 20 times

  if (deviceContext == NULL)
  {
    EC_E("deviceContext is NULL\n");
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  EC_I(" - Wait for EC Checksum Read\n");
  Status = i2c_block_read (
    CHECKSUM_RESULT_CMD_RO,
    ec_status,
    STATIC_DAT_LEN,
    duration,
    retry);
  if (EFI_SUCCESS == Status)
  {
   if (ec_status[0] == PASS_CHECKSUM)
   {
     EC_I("- EC Checksum Passed, 32bit checksum[0,1,2,3]:[0x%x, 0x%x, 0x%x, 0x%x]\n",
       ec_status[1], ec_status[2], ec_status[3], ec_status[4]);
     Status = EFI_SUCCESS;
     goto Exit;
   }
   else if (ec_status[0] == FAIL_CHECKSUM)
   {
     EC_E("- EC Checksum Failed!!, 32bit checksum[0,1,2,3]:[0x%x, 0x%x, 0x%x, 0x%x]\n",
       ec_status[1], ec_status[2], ec_status[3], ec_status[4]);
     Status = EFI_DEVICE_ERROR;
     goto Exit;
   }
  }
  else
  {
    EC_I("- EC Checksum Error and Timed out, checksum_result:0x%x 32bit checksum[0,1,2,3]:[0x%x, 0x%x, 0x%x, 0x%x]\n",
      ec_status[0], ec_status[1], ec_status[2], ec_status[3], ec_status[4]);
    Status = EFI_DEVICE_ERROR;
  }

Exit:
  return Status;
}

/**
  Get EC SPI Service Busy
    [0xAC]->Read->[XX]
    [XX]: AA - EC is in idle.
    Others: BUSY

  @param cycle_ms             Timeout value is used for retry mechanism
  @param max_retry            No of retry if incase of failure

  @retval EFI_SUCCESS        EC BBK/MBK SPI service is idle
  @retval EFI_DEVICE_ERROR   EC SPI service is busy and Timed out
**/
static
EFI_STATUS
Wait_For_EC_SPI_Service(
  UINT16 cycle_ms,
  UINT8 max_retry
  )
{
  EFI_STATUS    Status        = EFI_SUCCESS;
  UINT8         ec_status[3]  = {0,};
  unsigned int  times         = 0;

  if (deviceContext == NULL)
  {
    EC_E("deviceContext is NULL\n");
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  EC_I("Wait for EC SPI Service\r\n");

  do 
  {
    SleepMs(cycle_ms*1000);

    Status = i2c_block_read (
      SPI_SERVICE_CMD_RO,
      ec_status,
      STATIC_DAT_LEN,
      0,
      0);
    if (EFI_SUCCESS == Status)
    {
      if (ec_status[0] == EC_FW_IN_BOOT_BLK_IDLE)
      {
          EC_I("- EC BBK SPI service is idle\n");
          Status = EFI_SUCCESS;
          goto Exit;
      }
      else if (ec_status[0] == EC_FW_IN_MAIN_BLK_IDLE)
      {
          EC_I("- EC MBK SPI service is idle\n");
          Status = EFI_SUCCESS;
          goto Exit;
      }
    }

    // If EC is busy, or bus error, do the retry
    times++;
    EC_P(" .");
  }while(times < max_retry);

  EC_P(" \n");
  if (times == max_retry)
  {
    EC_I("- EC SPI service is busy and Timed out, ec_spi_service_status = 0x%x\n", ec_status[0]);
    Status = EFI_DEVICE_ERROR;
  }

Exit:
  return Status;
}

/**
    EC Check for Control Path for internal or external flash

  @retval EFI_SUCCESS        Successfully read the Internal/External flash control path
  @retval EFI_DEVICE_ERROR   I2C byte read is failed
**/
static
EFI_STATUS
EC_Check_Control_Path(void)
{
  EFI_STATUS    Status    = EFI_SUCCESS;
  UINT8         uData[3]  = {0,};
  unsigned int  retry     = 0;

  if (deviceContext == NULL)
  {
    EC_E("deviceContext is NULL\n");
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  for(; retry < 5; retry++)
  {
    Status = i2c_block_read (
      SPI_SERVICE_CMD_RO,
      uData,
      STATIC_DAT_LEN,
      0 ,
      0);
      if (EFI_ERROR(Status))
      {
        EC_E("i2c_block_read() failed with %r\n", Status);
        goto Exit;
      }
      else
      {
        EC_D("EC response [%x,%x,%x]\n",uData[0],uData[1],uData[2]);
        if (uData[1] == INT_FLASH_CTRL_PATH)
        {
          EC_D("- CTRL path is in INT eFlash!!\n");
          deviceContext->ctrl_path = INT_FLASH_CTRL_PATH;
          Status = EFI_SUCCESS;
          goto Exit;
        }
        else if (uData[1] == EXT_FLASH_CTRL_PATH)
        {
          EC_D("- CTRL path is in EXT Flash!!\n");
          deviceContext->ctrl_path = EXT_FLASH_CTRL_PATH;
          Status = EFI_SUCCESS;
          goto Exit;
        }
        else
        {
          EC_E("- Reading CTRL path retry %d\r",retry);
          SleepMs(TIME_10MS);
          continue;
        }
      }
  }

  EC_E("- Unknown CTRL path Error!!\n");
  deviceContext->ctrl_path = UNKNOWN_CTRL_PATH;

Exit:
  return Status;
}

/**
    EC erase the internal or external flash

  @retval EFI_SUCCESS       Erase the Internal/External flash is successfull
  @retval EFI_DEVICE_ERROR  Wait For EC SPI Service failed
**/
static
EFI_STATUS
EC_Erase_SPI_Flash(void)
{
  UINT16        cycle_ms  = 0;
  UINT8         retry     = 0;
  EFI_STATUS    Status    = EFI_SUCCESS;

  if (deviceContext == NULL)
  {
    EC_E("deviceContext is NULL\n");
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->fw_status == BOOT_BLK)
  {
    EC_I("- FW is in BOOT BLK\n");
  }
  else
  {
    EC_I("- FW is not in BOOT BLK\n");
  }

  //TODO : Replace with the new define command to hide the belowing flash information
  if (deviceContext->flash_type == EXTERNAL_FLASH_P1)
  {
    deviceContext->start_addr = BOOT_BLK_START_ADDR;
    deviceContext->erase_blockCount = 32;//External Flash erase sector is 4K base
  }
  else if (deviceContext->flash_type == EXTERNAL_FLASH_P2)
  {
    deviceContext->start_addr = BOOT_BLK2_START_ADDR;
    deviceContext->erase_blockCount = 32;//External Flash erase sector is 4K base
  }
  else if (deviceContext->flash_type == INTERNAL_FLASH_P1B)
  {
    deviceContext->erase_blockCount = 6;//6k
    deviceContext->start_addr = ACTV_BBK_START_ADDR;
  }
  else if (deviceContext->flash_type == INTERNAL_FLASH_P2B)
  {
    deviceContext->erase_blockCount = 8;//8k
    deviceContext->start_addr = BKUP_STARTUP_BBK_START_ADDR;
  }
  else if (deviceContext->flash_type == INTERNAL_FLASH_P1M)
  {
    deviceContext->erase_blockCount = 24;//24k
    deviceContext->start_addr = ACTV_MBK_START_ADDR;
  }
  else if (deviceContext->flash_type == INTERNAL_FLASH_P2M)
  {
    deviceContext->erase_blockCount = 24;//24k
    deviceContext->start_addr = BKUP_MBK_START_ADDR;
  }
  else if (deviceContext->flash_type == INTERNAL_FLASH_P2BM)
  {
    deviceContext->erase_blockCount = 32;//32k
    deviceContext->start_addr = BKUP_STARTUP_BBK_START_ADDR;
  }
  else
  {
    deviceContext->start_addr = MAIN_BLK_START_ADDR;
    deviceContext->end_addr = MAIN_BLK_END_ADDR;
    deviceContext->erase_blockCount = NO_OF_MAIN_BLK;//Internal Flash erase sector is 1K base
  }

  EC_I("- Erasing sector from start[0x%x] --- end[0x%x] with erase_sector_size:%d\n",
    deviceContext->start_addr,
    (deviceContext->start_addr + (deviceContext->erase_blockCount*deviceContext->erase_sector_size) - 1),
    deviceContext->erase_sector_size);
  
  UINT8 blockCount = deviceContext->erase_blockCount;
  Status = EC_Check_Control_Path();
  if (EFI_ERROR(Status))
  {
    EC_E("- EC_Check_Control_Path failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (deviceContext->ctrl_path == UNKNOWN_CTRL_PATH)
  {
    deviceContext->ctrl_path  = ((deviceContext->flash_type <= INTERNAL_FLASH_P2NV) ?
      INT_FLASH_CTRL_PATH : EXT_FLASH_CTRL_PATH);
  }

  if (deviceContext->ctrl_path == EXT_FLASH_CTRL_PATH)
  {
    if (deviceContext->flash_type == EXTERNAL_FLASH_P1)
    {
      EC_I("- ERASE_EXT_ACTIVE_PARTITION_CMD\n");
    }
    else
    {
      EC_I("- ERASE_EXT_BACKUP_PARTITION_CMD\n");
    }
    //retry every 1SEC, Set 5SEC time out
    cycle_ms = 1000;
    retry = 5;
  }
  else if (deviceContext->ctrl_path == INT_FLASH_CTRL_PATH)
  {
    if (deviceContext->flash_type == INTERNAL_FLASH_P1M)
    {
        EC_I("- ERASE_INT_ACTIVE_MBK_CMD\n");
    }
    else if (deviceContext->flash_type == INTERNAL_FLASH_P2M)
    {
        EC_I("- ERASE_INT_BACKUP_MBK_CMD\n");
    }
    else if (deviceContext->flash_type == INTERNAL_FLASH_P1B)
    {
        EC_I("- ERASE_INT_ACTIVE_BBK_CMD\n");
    }
    else if (deviceContext->flash_type == INTERNAL_FLASH_P2B)
    {
        EC_I("- ERASE_INT_BACKUP_MBK_CMD\n");
    }
    //retry every 1SEC, Set 5SEC time out
    cycle_ms = 1000;
    retry = 5;
  }
  
  Status = Erase_Designated_Flash(cycle_ms,retry);
  if (EFI_ERROR(Status))
  {
    EC_E("- Erase_Designated_Flash failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  
  //Check EC is finish ERASING FLASH process or not, will end earlier when detect SPI service is IDLE
  if (EFI_ERROR(Status))
  {
    EC_E("- Wait_For_EC_SPI_Service failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  
  EC_I("- blk %d / %d erased\n", blockCount, blockCount);

Exit:
  return Status;
}

/**
    EC write the internal or external flash

  @retval EFI_SUCCESS        Write to the Internal/External flash is successfull
  @retval EFI_OUT_OF_RESOURCES  Wait For EC SPI Service failed
  @retval EFI_DEVICE_ERROR  I2C block write is failed
**/
EFI_STATUS
EC_Write_SPI_Flash(void)
{
  EFI_STATUS    Status      = EFI_SUCCESS;
  UINT16        blockNum    = 0;
  UINT16        blockCount  = 0;
  unsigned int  addr        = 0;
  byte          *buff       = NULL;

  if (deviceContext == NULL)
  {
    EC_E("deviceContext is NULL\n");
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  blockCount = deviceContext->erase_blockCount*(deviceContext->erase_sector_size/EC_MAX_WRITE_SECTOR_TO_RAM);

  EC_I("Total block count %d, each of %d bytes to be flashed\n", blockCount, EC_MAX_WRITE_SECTOR_TO_RAM);

  deviceContext->debug_mask = DISABLE_LOGS;

  Status = Wait_For_EC_SPI_Service(100, 5);
  if (EFI_ERROR(Status))
  {
    EC_E("- Wait_For_EC_SPI_Service failed with %r\n", Status);
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  if (buff == NULL)
  {
    if ((deviceContext->flash_type == EXTERNAL_FLASH_P1) ||
      (deviceContext->flash_type == EXTERNAL_FLASH_P2) ||
      (deviceContext->flash_type == INTERNAL_FLASH_P2B) ||
      (deviceContext->flash_type == INTERNAL_FLASH_P2BM))
    {
      buff = &deviceContext->fw_img_data[0];
    }
    else if (deviceContext->flash_type == INTERNAL_FLASH_P1B)
    {
      buff = &deviceContext->fw_bbk_blk_data[0];
    }
    else if ((deviceContext->flash_type == INTERNAL_FLASH) ||
      (deviceContext->flash_type == INTERNAL_FLASH_P1M) ||
      (deviceContext->flash_type == INTERNAL_FLASH_P2M))
    {
      buff = &deviceContext->fw_main_blk_data[0];
    }
  }
  for(; blockNum < blockCount; blockNum++)
  {
    /* Load Binary to EC Data Buffer.*/

    Status = i2c_block_write (
      EC_FLASH_BUF_WRITE_CMD_WO,
      (void*)(buff + (blockNum * EC_MAX_WRITE_SECTOR_TO_RAM)),
      1,
      5); //Write Sector to RAM: [ADDR][W][EC_FLASH_BUF_WRITE_CMD_WO][DATA0][DATA1]...[DATAN-1]
    if (EFI_ERROR(Status))
    {
      EC_E("- i2c_block_write failed with %r\n", Status);
      Status = EFI_DEVICE_ERROR;
      goto Exit;
    }

    SleepMs(5000); //5ms

    addr = deviceContext->start_addr + (blockNum * EC_MAX_WRITE_SECTOR_TO_FLASH);
    Status = EC_Flash_To_SPIROM(
      &addr,
      EC_MAX_WRITE_SECTOR_TO_FLASH);
    if (EFI_ERROR(Status))
    {
      EC_E("- EC_Flash_To_SPIROM failed with %r\n", Status);
      Status = EFI_DEVICE_ERROR;
      goto Exit;
    }

    if (blockNum % 16 == 0)
    {
      EC_I("- blk %d / %d written\r", blockNum, blockCount);
    }

    SleepMs(10000); //10ms, supported Ext. flash need 700us response time for each sector write
  }

  deviceContext->debug_mask = ENABLE_LOGS;

  EC_I("- blk %d / %d written - Addr 0x%x\n", blockNum, blockCount, addr);

Exit:
  buff = NULL;
  return Status;
}

/**
    [EC_MODE_CMD][BYTECNT1][RUN_CHECKSUM_CMD] Entry EC Boot-Block

  @retval EFI_SUCCESS        Successfully queried checksum command for the Internal/External flash
  @retval EFI_DEVICE_ERROR   I2C block write is failed
**/
static
EFI_STATUS
EC_Run_Checksum(void)
{
  EFI_STATUS  Status  = EFI_SUCCESS;
  UINT8       wdBuf   = RUN_CHECKSUM_INT_P1_32K; //Run checksum
  
  if (deviceContext == NULL)
  {
    EC_E("- deviceContext is NULL!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->flash_type == EXTERNAL_FLASH_P1)
  {
    wdBuf = RUN_CHECKSUM_EXT_P1_128K;
  }
  else if (deviceContext->flash_type == EXTERNAL_FLASH_P2)
  {
    wdBuf = RUN_CHECKSUM_EXT_P2_128K; // Run for second partition for now to ensure recovery is intact.
  }
  else if ((deviceContext->flash_type == INTERNAL_FLASH_P1B) ||
    (deviceContext->flash_type == INTERNAL_FLASH_P1M))
  {
    wdBuf = RUN_CHECKSUM_INT_P1_32K;
  }
  else if ((deviceContext->flash_type == INTERNAL_FLASH_P2B) ||
    (deviceContext->flash_type == INTERNAL_FLASH_P2M))
  {
    wdBuf = RUN_CHECKSUM_INT_P2_32K;
  }
  else
  {
    wdBuf = RUN_CHECKSUM_INT_P1_32K;
    //TODO : to make it more generic, we should query the EC to know the supported flash partition layout
  }
  
  Status = i2c_block_write (
    EC_MODE_CMD_WO,
    &wdBuf,
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_write() failed with %r\n", Status);
    goto Exit;
  }

Exit:
    return Status;
}

/**
    Programming the EC firmware

  @retval EFI_SUCCESS        EC FW is programmed Successfully
  @retval EFI_DEVICE_ERROR   EC Select/Erase/Write to SPI Flash is Failed
**/
static
EFI_STATUS
EC_Program_Firmware(void)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (deviceContext == NULL)
  {
    EC_E("- deviceContext is NULL!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  EC_TRACE();

  Status = EC_Select_SPI_Flash();
  if (EFI_ERROR(Status))
  {
    EC_E("EC_Select_SPI_Flash() failed with %r\n", Status);
    goto Exit;
  }

  EC_Check_FW_Status();

  Status = EC_Erase_SPI_Flash();
  if (EFI_ERROR(Status))
  {
    EC_E("EC_Erase_SPI_Flash() failed with %r\n", Status);
    goto Exit;
  }

  Status = EC_Write_SPI_Flash();
  if (EFI_ERROR(Status))
  {
    EC_E("EC_Write_SPI_Flash() failed with %r\n", Status);
    goto Exit;
  }
  
Exit:
  return Status;
}

/**
    Programming the EC firmware to internal flash (code mirror)

    @retval EFI_SUCCESS        EC FW is programmed from external flash to internal flash Successfully
    @retval EFI_DEVICE_ERROR   EC Run Checksum cmd execution failed
**/
static
EFI_STATUS
EC_Finalize_Reflash(void)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  if (deviceContext == NULL)
  {
    EC_E("- deviceContext is NULL!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  EC_TRACE();

  EC_E("Sending checksum cmd for flash_type: %d\n", deviceContext->flash_type);

  Status = EC_Run_Checksum();
  if (EFI_ERROR(Status))
  {
    EC_E("EC_Run_Checksum() failed with %r\n", Status);
    goto Exit;
  }
  
  SleepMs(TIME_500MS); //Delay for calculating the checksum
  
  /* Wait till internal Cheksum result is passed */
  Status = ((deviceContext->flash_type == INTERNAL_FLASH)?
    Wait_For_EC_Checksum_Result(100):Wait_For_EC_Checksum_Result(20000)); //at most 8sec, will end earlier if we get I2C_SUCCESS
  if (EFI_ERROR(Status))
  {
    EC_E("Wait_For_EC_Checksum_Result() failed with %r\n", Status);
    goto Exit;
  }

Exit:
  return Status;
}

/**
  Check the EC FW running mode either Boot block or main block or unknown block mode

  @retval None
**/
void EC_Check_FW_Status(void)
{
  EFI_STATUS  Status    = EFI_SUCCESS;
  UINT8       uData[3]  = {0,};
  
  if (deviceContext == NULL)
  {
    EC_E("- deviceContext is NULL!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  EC_TRACE();

  Status = i2c_block_read (
    SPI_SERVICE_CMD_RO,
    uData,
    STATIC_DAT_LEN,
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_read() failed with %r\n", Status);
    deviceContext->fw_status = 0;
    goto Exit;
  }

  if (uData[0] == EC_FW_IN_BOOT_BLK_IDLE)
  {
    EC_I("- FW is running in BOOT BLK mode!!\n");
    deviceContext->fw_status =  BOOT_BLK;
  }
  else if (uData[0] == EC_FW_IN_MAIN_BLK_IDLE)
  {
    EC_I("- FW is running in MAIN BLK mode!!\n");
    deviceContext->fw_status = MAIN_BLK;
  }
  else
  {
    EC_I("- FW is running in UNKNOWN BLK mode, setting to BBK forcefully!!\n");
    deviceContext->fw_status = BOOT_BLK;
  }

Exit:
  EC_I("EC_Check_FW_Status() completed with %r\n", Status);
}

/**
    EC Boot Block Entry [EC_MODE_CMD][BYTECNT1[EC_ENTER_BBK_CMD]

  @retval EFI_SUCCESS           EC entered into Boot Block Mode
  @retval EFI_DEVICE_ERROR      I2C block write is failed
**/
EFI_STATUS
EC_Enter_BBK(void)
{
  EFI_STATUS  Status  = EFI_SUCCESS;
  UINT8       wdBuf   = ENTER_BBK_CMD; //Enter BBK mode

  Status = i2c_block_write (
    EC_MODE_CMD_WO,
    &wdBuf,
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_write() failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_I("- Entered BBK Area\n");

Exit:
  return Status;
}

/**
    EC Boot Block Exit
    [0xBB][0x00] Exit EC Boot-Block (Normal service loop)

    @retval EFI_SUCCESS        EC exited from Boot Block Mode
    @retval EFI_DEVICE_ERROR   I2C block write is failed
**/
EFI_STATUS
EC_Exit_BBK(void)
{
  EFI_STATUS  Status  = EFI_SUCCESS;
  UINT8       wdBuf   = EXIT_BBK_CMD; //Exit BBK mode

  Status = i2c_block_write (
    EC_MODE_CMD_WO,
    &wdBuf,
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_write() failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_I("- Exited BBK Area\n");

Exit:
  return Status;
}

/**
    EC_Enable_Flashing kicks off the reflash process

    @retval EFI_SUCCESS             EC enable the refalshing process successfully
    @retval EFI_OUT_OF_RESOURCES    Error in EC FW status ( Unknown block mode or status is zero)
    @retval EFI_DEVICE_ERROR        failed to enter BBK mode
**/
EFI_STATUS
EC_Enable_Flashing(void)
{
  EFI_STATUS Status = EFI_SUCCESS;

  if (deviceContext == NULL)
  {
    EC_E("- deviceContext is NULL!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }
  
  EC_TRACE();

  /* Check if the FW is in UNKNOWN_BLK */
  if ((deviceContext->fw_status == 0) ||
    (deviceContext->fw_status == UNKNOWN_BLK))
  {
    EC_E("- Error in EC FW status = %d, setting to BBK!!\n", deviceContext->fw_status);
    deviceContext->fw_status = BOOT_BLK;
    goto Exit;
  }

  /**
      1: MAIN BLK
      2: BOOT BLK
  */
  if ((deviceContext->fw_status == MAIN_BLK) &&
    (deviceContext->flash_type == INTERNAL_FLASH))
  {
    EC_I(" - Trying to enter boot blk mode....\n");
    /* Switch to BBK Area */
    Status =  EC_Enter_BBK();
    if (EFI_ERROR(Status))
    {
      EC_E("EC_Enter_BBK() failed with %r\n", Status);
      goto Exit;
    }
  }

  /* Reconfirm if the FW is in MAIN or BOOT BLK */
  EC_Check_FW_Status();
  if ((deviceContext->fw_status == 0) ||
    (deviceContext->fw_status == UNKNOWN_BLK))
  {
    EC_E("- Error in Reconfirming EC FW status = %d, setting to BBK!\n", deviceContext->fw_status);
	deviceContext->fw_status = BOOT_BLK;
    goto Exit;
  }
  else if (deviceContext->fw_status == MAIN_BLK)
  {
    EC_E("- FW is still in MAIN BLK mode!!\n");
  }
  else if (deviceContext->fw_status == BOOT_BLK)
  {
    EC_I("- FW successfully entered to BOOT BLK mode!!\n");
  }
  else
  {
    EC_E("- FW is in Unknown FW Status!!\n");
    Status =  EFI_DEVICE_ERROR;
    goto Exit;
  }
  
  Status =  Wait_For_EC_SPI_Service(100, 5); // TRUE: IDLE, FALSE: BUSY
  if (EFI_ERROR(Status))
  {
    EC_E("Wait_For_EC_SPI_Service() failed with %r\n", Status);
    goto Exit;
  }

Exit:
  return Status;
}


/**
    ECReflash reflashes the entire MAIN_FW Block image.

    @retval EFI_SUCCESS             EC refalshing the main firmware block image is successfully
    @retval EFI_OUT_OF_RESOURCES    EC Parse/Flashing to Flash is failed
    @retval EFI_DEVICE_ERROR        Program/Finilize FW Image Failed
**/
EFI_STATUS EC_Reflash(void)
{
  EFI_STATUS Status = EFI_SUCCESS;
  
  if (deviceContext == NULL)
  {
    EC_E("- deviceContext is NULL!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  EC_TRACE();

  Status = EC_Parse_FW_Image();
  if (EFI_ERROR(Status))
  {
    EC_E("EC_Parse_FW_Image() failed with %r\n", Status);
    goto Exit;
  }
  
  Status = EC_Enable_Flashing();
  if (EFI_ERROR(Status))
  {
    EC_E("EC_Enable_Flashing() failed with %r\n", Status);
    goto Exit;
  }
  
  Status = EC_Program_Firmware();
  if (EFI_ERROR(Status))
  {
    EC_E("EC_Program_Firmware() failed with %r\n", Status);
    goto Exit;
  }
  
  Status = EC_Finalize_Reflash();
  if (EFI_ERROR(Status))
  {
    EC_E("EC_Finalize_Reflash() failed with %r\n", Status);
    goto Exit;
  }

  if (deviceContext->flash_type == INTERNAL_FLASH)
  {
    Status = EC_Exit_BBK();
    if (EFI_ERROR(Status))
    {
      EC_E("EC_Exit_BBK() failed with %r\n", Status);
      goto Exit;
    }
  }

Exit:
  return Status;
}

/**
    Erase the designated Flash

    @param cycle_ms             Timeout value to support the retry mechanism
    @param retry                no of retry

    @retval EFI_SUCCESS         Erase the designated flash is successfully
    @retval EFI_DEVICE_ERROR    I2C block write is Failed
**/
EFI_STATUS
Erase_Designated_Flash(
  UINT16 cycle_ms,
  UINT8 retry
  )
{
  UINT8       wdBuf[5]  = {0,};
  EFI_STATUS  Status    = EFI_SUCCESS;
  
  if (deviceContext == NULL)
  {
    EC_E("- deviceContext is NULL!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  EC_TRACE();

  wdBuf[0] = deviceContext->ctrl_path;
  wdBuf[1] = deviceContext->erase_blockCount;
  wdBuf[2] = (UINT8)(*((unsigned int*)(&deviceContext->start_addr)) & 0xFF);         //ADDRL
  wdBuf[3] = (UINT8)((*((unsigned int*)(&deviceContext->start_addr)) >> 8) & 0xFF);  //ADDRM
  wdBuf[4] = (UINT8)((*((unsigned int*)(&deviceContext->start_addr)) >> 16) & 0xFF); //ADDRH
  
  Status = i2c_block_write (
    ERASE_DESIGNATED_CMD_WO,
    &(wdBuf[0]),
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_write() failed with %r\n", Status);
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  
  Status = Wait_For_EC_SPI_Service(cycle_ms,retry);

Exit:
  return Status;
}

/**
    read the designated Flash area

    @param addr              Address of flash from where we have to read
    @param cycle_ms          Timeout value to support the retry mechanism
    @param retry             no of retry

    @retval EFI_SUCCESS       Reading the designated flash is successfully
    @retval EFI_DEVICE_ERROR  I2C block read is Failed
**/
EFI_STATUS
Read_Designated_Area(
  unsigned int addr,
  UINT16 cycle_ms,
  UINT8 retry
  )
{
  EFI_STATUS  Status    = EFI_SUCCESS;
  UINT8       wdBuf[4]  = {0,};
  UINT8       rdBuf[16] = {0,};

  if (deviceContext == NULL)
  {
    EC_E("- deviceContext is NULL!!\n");
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  EC_TRACE();

  wdBuf[0] = 0x0F;
  wdBuf[1] = (UINT8)(*((unsigned int*)(&addr)) & 0xFF);           //ADDRL
  wdBuf[2] = (UINT8)((*((unsigned int*)(&addr)) >> 8) & 0xFF);    //ADDRM
  wdBuf[3] = (UINT8)((*((unsigned int*)(&addr)) >> 16) & 0xFF);   //ADDRH
  
  Status = i2c_block_write (
    READ_ROM_TO_BUFF_512_CMD_RO,
    &(wdBuf[0]),
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_write() failed with %r\n", Status);
    goto Exit;
  }

  SleepMs(20*1000);
  
  Status = i2c_block_read (
    READ_BUFF_512_CMD_RO,
    rdBuf,
    STATIC_DAT_LEN,
    30,
    3);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_read() failed with %r\n", Status);
    goto Exit;
  }

  EC_E( "Dumping read block buffer\n");
  for (UINT8 i=0; i<16 ;i++)
  {
     EC_P( " 0x%X,",rdBuf[i]);
  }
  EC_P( " \n ");

Exit:
  return Status;
}

/**
 * @brief Read Corruption status, support in Startup BBK/ BBK /MBK

 * @retval EFI_SUCCESS       Reading Corruption status successfully 
 * @retval EFI_DEVICE_ERROR  I2C block read is Failed
**/
EFI_STATUS
EC_Check_Corruption_Status(
  void
  )
{
  EFI_STATUS Status   = EFI_SUCCESS;
  UINT8     rdBuf[2]  = {0};

  Status = i2c_block_read (
    CORRUPTION_STATUS_CMD_RO,
    rdBuf,
    STATIC_DAT_LEN,
    0,
    0);
  if (EFI_ERROR(Status))
  {
    EC_E("i2c_block_read() failed with %r\n", Status);
    goto Exit;
  }

  EC_I("- Corruption Status : 0x%x\n",rdBuf[0]);

Exit:
  return Status;
}
