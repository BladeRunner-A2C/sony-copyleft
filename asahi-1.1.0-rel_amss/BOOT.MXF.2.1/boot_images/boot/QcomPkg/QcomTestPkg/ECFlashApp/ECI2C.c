/** @file
  I2C Application that communicate with the EC (Embedded Controller).

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
EC_DEVICE_CONTEXT *deviceContext = NULL;
CMD_CONTEXT CmdContext[] =
{
  /* CMD                             LenCmd LenDat                BCNT */
  /**********************************ACPI I2C Command (Addr : 0x76)**********************************/
  {EC_VERSION_CMD_RO,                   1,    4,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {EC_FLASH_BUF_WRITE_CMD_WO,           1,    LIMIT_256B,       0,              ACPI_I2C_PROTOCOL}, 
  {READ_BUFF_512_CMD_RO,                1,    5,                0,              ACPI_I2C_PROTOCOL},
  {BULK_READ_CMD_RO,                    1,    DYNAMIC_DAT_LEN,  WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},          
  {CHECKSUM_RESULT_CMD_RO,              1,    6,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {READ_ROM_TO_BUFF_512_CMD_RO,         1,    5,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {EC_REGISTER_WRITE_WO,                1,    4,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {EC_REGISTER_READ_WO,                 1,    4,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {EC_WRITE_DATABUF_TO_SPI_ROM_CMD_WO,  1,    6,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {ERASE_DESIGNATED_CMD_WO,             1,    6,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {SPI_QUICK_CMD_WO,                    1,    2,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {EC_MODE_CMD_WO,                      1,    2,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {CORRUPTION_STATUS_CMD_RO,            1,    2,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  {SPI_SERVICE_CMD_RO,                  1,    3,                WITH_BYTE_CNT,  ACPI_I2C_PROTOCOL},
  /***********************************Pre-define Command (Addr : 0x5B)********************************/
  {I2EC_ADDRESS_WO,                     1,    2,                0,              RECOVERY_I2C_PROTOCOL},
  {I2EC_DATA_WR,                        1,    1,                0,              RECOVERY_I2C_PROTOCOL},
  {PREDEFINE_CHIP_SELECT_TOGGLE_WO,     1,    1,                0,              RECOVERY_I2C_PROTOCOL},
  {LAST_TAG_MUST_STAY_AT_LAST,          0,    0,                0,              0}//PLEASE DO NOT REMOVE THE TAG
};
/**
 * Return EFI_STATUS value for i2c_status value
 *
 * @param  I2cStatus               i2c_status value
 * @retval EFI_SUCCESS             I2C_SUCCESS
 * @retval EFI_DEVICE_ERROR        any other i2c failures
 *
**/
EFI_STATUS
I2cstatusToEfistatus(
  i2c_status I2cstatus
  )
{
  EFI_STATUS status = EFI_SUCCESS;

  // Convert from i2c_status to EFI_STATUS
  switch ( I2cstatus )
  {
    case I2C_SUCCESS:
      status = EFI_SUCCESS;
      break;
    default:
      status = EFI_DEVICE_ERROR;
  }

  return status;
}

/**
 * @brief De-Initialize I2C CORE PROTOCOL
 */
void
I2C_DeInit(void)
{
  i2c_status i2c_sts  = I2C_SUCCESS;

  if (deviceContext == NULL)
  {
    EC_E("Invalid deviceContext\n");
    goto Exit;
  }

  if (deviceContext->i2c_handle != NULL)
  {
    i2c_sts = i2c_close(deviceContext->i2c_handle);

    if (EFI_ERROR (i2c_sts))
    {
      EC_D("\r\nFailed to DeInitialize I2C %d\n", i2c_sts);
    }

    deviceContext->i2c_handle = NULL;
  }
Exit:
  return;
}

/**
 * @brief Initialize I2C CORE PROTOCOL
 * @retval EFI_SUCCESS             I2C_SUCCESS
 * @retval EFI_OUT_OF_RESOURCES    Failed to initialize I2C core
 * @retval EFI_DEVICE_ERROR        deviceContext handle NULL
 */
EFI_STATUS
I2C_Init(void)
{
  EFI_STATUS        status                = EFI_SUCCESS;
  i2c_status        i2c_sts               = I2C_SUCCESS;
  i2c_slave_config  acpi_i2c_cfg          = {0};
  i2c_slave_config  recovery_slave_config = {0};

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->i2c_handle != NULL)
  {
    i2c_sts = i2c_close(deviceContext->i2c_handle);
    if (i2c_sts != I2C_SUCCESS)
    {
      EC_E("i2c_close() failed with %d\n", i2c_sts);
    }
  }

  EC_D("Initializing the I2C Core!!\n");

  i2c_sts = i2c_open(
    (i2c_instance) (I2C_INSTANCE_006),
    &deviceContext->i2c_handle
    );
  if ((EFI_ERROR(i2c_sts)) ||
    (deviceContext->i2c_handle == NULL ))
  {
    EC_E("i2c_open() failed with %d\n", i2c_sts);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_D("Initializing Recovery & ACPI I2C Config!!\n");
  recovery_slave_config.bus_frequency_khz           = I2C_DEFAULT_BUS_FREQ;                   /**< Bus speed in kHz. */
  recovery_slave_config.slave_address               = deviceContext->recovery_slave_addr;       /**< 7-bit I2C slave address.*/
  recovery_slave_config.mode                        = I2C;                                                 /**< Protocol mode. Refer #i2c_mode */
  recovery_slave_config.slave_max_clock_stretch_us  = I2C_MAX_CLK_STRETCH_FREQ;      /**< Maximum time in microseconds that an I2C slave may hold the SCL line low. Not applicable for I3C*/
  recovery_slave_config.core_configuration1         = 0;                                    /**< Core Specific Configuration. Recommended 0. */
  recovery_slave_config.core_configuration2         = 0;                                    /**< Core Specific Configuration. Recommended 0. */
  deviceContext->recovery_slave_config              = recovery_slave_config;

  acpi_i2c_cfg.bus_frequency_khz                    = I2C_DEFAULT_BUS_FREQ;           /**< Bus speed in kHz. */
  acpi_i2c_cfg.slave_address                        = deviceContext->slave_addr;      /**< 7-bit I2C slave address. 7-bit I3C dynamic address */
  acpi_i2c_cfg.mode                                 = I2C;                            /**< Protocol mode. Refer #i2c_mode */
  acpi_i2c_cfg.slave_max_clock_stretch_us           = I2C_MAX_CLK_STRETCH_FREQ;       /**< Maximum time in microseconds that an I2C slave may hold the SCL line low. Not applicable for I3C*/
  acpi_i2c_cfg.core_configuration1                  = 0;                              /**< Core Specific Configuration. Recommended 0. */
  acpi_i2c_cfg.core_configuration2                  = 0;                              /**< Core Specific Configuration. Recommended 0. */
  deviceContext->slave_config                       = acpi_i2c_cfg;

Exit:
  return status;
}

/**
 * @brief I2C CMD WRITE ONLY PROTOCOL [ADDR][CMD]
 *
 * @param  activeI2cChannel        Active I2c Channel
 * @param  cmd                     command value
 *
 * @retval EFI_SUCCESS             The I2C command write is executed successfully.
 * @retval EFI_DEVICE_ERROR        I2C handler or deviceContext handle is NULL.
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_cmd_write_only (
  UINT8 activeI2cChannel,
  UINT8 cmd
  )
{
  i2c_status        i2c_sts               =   I2C_SUCCESS;
  EFI_STATUS        status                =   EFI_SUCCESS;
  UINT32            bytes_written         =   0;
  
  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_TRACE();
  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("- i2c_handle NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  i2c_slave_config *active_slave_config = ((activeI2cChannel == RECOVERY_I2C_PROTOCOL) ?
    &(deviceContext->recovery_slave_config) : &(deviceContext->slave_config));
  deviceContext->activeI2cChannel = activeI2cChannel;

  i2c_sts = i2c_write (
    deviceContext->i2c_handle,
    active_slave_config,
    0,
    SLAVE_TYPE_NORM,
    &cmd,
    1,
    &bytes_written,
    I2C_TIMEOUT_MS);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_write() failed with %d\n", (uint32) i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }
  if (!bytes_written)
  {
    EC_E("- Nothing is written to device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_D( "Total bytes written: %d\n", bytes_written);
Exit:
  return status;
}

/**
 * @brief I2C DATA READ ONLY PROTOCOL [ADDR] [DATA_LOW][DATA_HIGH]
 *
 * @param  activeI2cChannel        Active I2c Channel
 * @param  buff                    Pointer to I2C read buffer
 * @param  buff_size               Size of the read buffer.
 *
 * @retval EFI_SUCCESS             The I2C read is executed successfully.
 * @retval EFI_DEVICE_ERROR        I2C handler is NULL.
 * @retval EFI_OUT_OF_RESOURCES    Unable to allocate the requested memory or buff_size out of range
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_data_read_only (
  UINT8 activeI2cChannel,
  void* buff,
  UINT8 buff_size
  )
{
  i2c_status        i2c_sts               =   I2C_SUCCESS;
  EFI_STATUS        status                =   EFI_SUCCESS;
  UINT32            bytes_read            =   0;
  UINT8             *rdBuf                =   NULL;

  if (!buff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_TRACE();
  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  if ((buff_size == 0) ||
    (buff_size > BLOCK_READ_BYTE_MAX))
  {
    EC_E("Error in buffer size criteria:[%d]!!\n", buff_size);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }
  rdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * buff_size);
  if (rdBuf == NULL)
  {
    EC_E("Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  i2c_slave_config *active_slave_config = ((activeI2cChannel == RECOVERY_I2C_PROTOCOL) ?
    &(deviceContext->recovery_slave_config) : &(deviceContext->slave_config));
  deviceContext->activeI2cChannel = activeI2cChannel;

  i2c_sts = i2c_read (
    deviceContext->i2c_handle,
    active_slave_config,
    0,
    SLAVE_TYPE_NORM,
    rdBuf,
    buff_size,
    &bytes_read,
    I2C_TIMEOUT_MS);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_read() failed with %d\n", (uint32) i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }
  if (!bytes_read)
  {
    EC_E("Nothing is read from the device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_D( "Total bytes read: %d\n", bytes_read);
  /* Cross check the read block for debugging */
  if (deviceContext->debug_mask)
  {
    EC_D( "Dumping read byte buffer[%d]:", bytes_read);
    for (int i = 0 ; i < bytes_read; i++)
    {
      EC_P( " 0x%x, ",rdBuf[i]);
    }
    EC_P( "\n ");
  }
  CopyMem(
    buff,
    &(rdBuf[0]),
    bytes_read);
Exit:
  if (rdBuf)
  {
    FreePool(rdBuf);
    rdBuf = NULL;
  }
  return status;
}

/**
 * @brief I2C WORD READ PROTOCOL [ADDR][CMD] [ADDR] [DATA_LOW][DATA_HIGH]
 *
 * @param  activeI2cChannel        Active I2c Channel
 * @param  cmd                     I2C command value
 * @param  buff                    Pointer to I2C read buffer
 *
 * @retval EFI_SUCCESS             The I2C word read is executed successfully.
 * @retval EFI_DEVICE_ERROR        I2C transferred is failed, deviceContext handle or buff NULL.
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_word_read (
  UINT8 activeI2cChannel,
  UINT8 cmd,
  void* buff
  )
{
  i2c_status        i2c_sts               = I2C_SUCCESS;
  EFI_STATUS        status                = EFI_SUCCESS;
  UINT8             wdBuf[1]              = {0};
  UINT8             rdBuf[2]              = {0,};
  UINT32            bytes_read            = 0;
  i2c_descriptor    buffer_desc[2]        = {{0}};

  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!buff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_TRACE();
  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  i2c_slave_config *active_slave_config = ((activeI2cChannel == RECOVERY_I2C_PROTOCOL) ?
    &(deviceContext->recovery_slave_config) : &(deviceContext->slave_config));
  deviceContext->activeI2cChannel = activeI2cChannel;

  /* Fille the descriptor */
  wdBuf[0] = cmd;
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;
  buffer_desc[1].buffer = rdBuf;
  buffer_desc[1].length = 2;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;
  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    active_slave_config,
    buffer_desc,
    2,
    NULL,
    NULL,
    0,
    &bytes_read);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }
  if (!bytes_read)
  {
    EC_E("- Nothing is read from the device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_D( "Total bytes read: %d\n", bytes_read);
  /* Cross check the read block for debugging */
  if (deviceContext->debug_mask)
  {
    EC_D( "Dumping read word buffer[%d]:", bytes_read);
    for (int i = 0 ; i < bytes_read; i++)
    {
      EC_P( " 0x%x, ",rdBuf[i]);
    }
    EC_P( " \n ");
  }
  CopyMem(
    buff,
    &(rdBuf[0]),
    bytes_read);
Exit:
  return status;
}

/**
 * @brief I2C BYTE READ PROTOCOL [ADDR][CMD] [ADDR] [DATA]
 * 
 * @param  activeI2cChannel        Active I2c Channel
 * @param  cmd                     I2C command value
 * @param  buff                    Pointer to I2C read buffer
 *
 * @retval EFI_SUCCESS             The I2C byte read is executed successfully.
 * @retval EFI_DEVICE_ERROR        I2C transferred is failed.
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_byte_read (
  UINT8 activeI2cChannel,
  UINT8 cmd,
  void* buff
  )
{
  i2c_status        i2c_sts               = I2C_SUCCESS;
  EFI_STATUS        status                = EFI_SUCCESS;
  UINT8             wdBuf[1]              = {0};
  UINT8             rdBuf[1]              = {0};
  UINT32            bytes_read            = 0;
  i2c_descriptor    buffer_desc[2]        = {{0}};
  
  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!buff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_TRACE();
  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  i2c_slave_config *active_slave_config = ((activeI2cChannel == RECOVERY_I2C_PROTOCOL) ?
    &(deviceContext->recovery_slave_config) : &(deviceContext->slave_config));
  deviceContext->activeI2cChannel = activeI2cChannel;
  
  /* Fill the descriptor */
  wdBuf[0] = cmd;
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;
  buffer_desc[1].buffer = rdBuf;
  buffer_desc[1].length = 1;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;
  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    active_slave_config,
    buffer_desc,
    2,
    NULL,
    NULL,
    0,
    &bytes_read);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }
  if (!bytes_read)
  {
    EC_E("- Nothing is read from the device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_D("Total bytes read: %d\n", bytes_read);
  /* Cross check the read block for debugging */
  if (deviceContext->debug_mask)
  {
    EC_D("Dumping read byte buffer[%d]:", bytes_read);
    for (int i = 0 ; i < bytes_read; i++)
    {
      EC_P( " 0x%x, ",rdBuf[i]);
    }
    EC_D( " \n ");
  }
  CopyMem(
    buff,
    &(rdBuf[0]),
    bytes_read);
Exit:
  return status;
}

/**
 * @brief I2C BLOCK READ PROTOCOL [ADDR][CMD(32-bit Max)] [ADDR] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
 * @brief This API can perform BYTE READ / WORD READ PROTOCL as well
 * @param  cmd                     I2C command 
 * @param  rbuff                   Pointer to I2C read buffer
 * @param  dynamic_datalength      Dynamic Data Length
 * @param  cycle_ms                Time yield for the slave device to complete the I/O mentioned in milliseconds
 * @param  max_retry               No of retry
 *
 * @retval EFI_SUCCESS             The I2C block read is executed successfully.
 * @retval EFI_DEVICE_ERROR        I2C transferred is failed.
 * @retval EFI_OUT_OF_RESOURCES    Unable to allocate the required memory or rlength out of range
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_block_read (
  UINT32 cmd,
  void* rbuff,
  UINT8 dynamic_datalength,
  UINT16 cycle_ms,
  UINT8 max_retry
  )
{
  i2c_status        i2c_sts               = I2C_SUCCESS;
  EFI_STATUS        status                = EFI_SUCCESS;
  UINT8             wdBuf[4]              = {0};
  UINT32            bytes_read            = 0;
  i2c_descriptor    buffer_desc[2]        = {{0}};
  UINT8             *rdBuf                = NULL;
  UINT8             retry                 = 0;
  CMD_CONTEXT       *cmd_ctx              = &CmdContext[0];
  i2c_slave_config  *active_slave_config  = NULL;

  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!rbuff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  for (UINT8 i=0; CmdContext[i].cmd != LAST_TAG_MUST_STAY_AT_LAST; i++)
  {
    if (CmdContext[i].cmd == cmd)
    {
      if ((dynamic_datalength == 0) &&
        (CmdContext[i].wrDataSize == DYNAMIC_DAT_LEN))
      {
        continue;
      }
      else
      {
        if (dynamic_datalength)
        {
          CmdContext[i].wrDataSize = dynamic_datalength;
        }
        cmd_ctx = &CmdContext[i];
        break;
      }
    }
  }

  if ((cmd_ctx->wrDataSize == 0) ||
    (cmd_ctx->wrDataSize > BLOCK_READ_BYTE_MAX))
  {
    EC_E("- Error in buffer Size criteria:[%d]!!\n", cmd_ctx->wrDataSize);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  rdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * (cmd_ctx->wrDataSize+1));//TODO: Check not mandatory to add 1
  if (rdBuf == NULL)
  {
    EC_E("- Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }
  deviceContext->activeI2cChannel = cmd_ctx->activeI2cChannel;
  if (deviceContext->activeI2cChannel == RECOVERY_I2C_PROTOCOL)
  {
    active_slave_config = &(deviceContext->recovery_slave_config);
  }
  else if (deviceContext->activeI2cChannel == ACPI_I2C_PROTOCOL)
  {
    active_slave_config = &(deviceContext->slave_config);
  }
  else
  {
    EC_E("- Unknown Active I2C Channel!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  // set up transfer list

  for (UINT8 i = 0;i < sizeof(UINT32);i++)
  {
    wdBuf[i] = (UINT8)(cmd_ctx->cmd >> ((3 - i) * 8));
    EC_D( "wdBuf[%d] = 0x%x\n", i, wdBuf[i]);
  }
  
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = cmd_ctx->wCmdLength;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[1].buffer = rdBuf;
  buffer_desc[1].length = cmd_ctx->wrDataSize;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;

  EC_D("- Sending read block request with CMD 0x%x \r\n", cmd_ctx->cmd);
  EC_D("- wCmdLength = %d, rDatLength = %d \r\n", cmd_ctx->wCmdLength, cmd_ctx->wrDataSize);

  // At most 10sec
  do
  {
    i2c_sts = i2c_transfer(
      deviceContext->i2c_handle,
      active_slave_config,
      buffer_desc,
      2,
      NULL,
      NULL,
      0,
      &bytes_read);
    if (i2c_sts == I2C_SUCCESS)
    {
      break;
    }
    else if ((i2c_sts == I2C_ERROR_ADDR_NACK ) ||
      (i2c_sts == I2C_ERROR_DATA_NACK))
    {
      SleepMs(cycle_ms*1000);
      status = EFI_SUCCESS;
    }
    retry++;
    EC_P(" I2C retry : %d(%dms) \r ",retry,cycle_ms);
    }while (retry < max_retry);

    EC_P(" \r\n ");

    if ((I2C_SUCCESS != i2c_sts) &&
      (i2c_sts != I2C_ERROR_ADDR_NACK) &&
      (i2c_sts != I2C_ERROR_DATA_NACK))
    {
      EC_E("- Failed to transfer I2C. Error = %d\n", i2c_sts);
      status = I2cstatusToEfistatus(i2c_sts);
      goto Exit;
    }

    if (!bytes_read)
    {
      EC_E("- Nothing is read from the device\n");
      status = EFI_DEVICE_ERROR;
      goto Exit;
    }

    EC_D( "Total bytes read: %d\n", bytes_read);

    /* Cross check the read block for debugging */
    if (deviceContext->debug_mask)
    {
      EC_D( "Dumping read block buffer[%d]:", bytes_read);
      for (int i = 0; i < bytes_read; i++)
      {
        EC_P( " 0x%x, ",rdBuf[i]);
      }
      EC_P( " \n ");
    }

  CopyMem(
    rbuff,
    &(rdBuf[cmd_ctx->withByteCnt]),
    (cmd_ctx->wrDataSize - cmd_ctx->withByteCnt));

Exit:
  if (rdBuf)
  {
    FreePool(rdBuf);
    rdBuf = NULL;
  }
  if (dynamic_datalength)
  {
    cmd_ctx->wrDataSize = DYNAMIC_DAT_LEN;
  }
  return status;
}

/**
 * @brief I2C WORD WRITE PROTOCOL [ADDR][CMD] [DATA_LOW] [DATA_HIGH]
 *
 * @param  activeI2cChannel        Active I2c Channel
 * @param  cmd                     I2C command value
 * @param  buff                    Pointer to I2C write buffer
 *
 * @retval EFI_SUCCESS             The I2C word write is executed successfully.
 * @retval EFI_DEVICE_ERROR        I2C transferred is failed.
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_word_write (
  UINT8 activeI2cChannel,
  UINT8 cmd,
  void* buff
  )
{
  i2c_status        i2c_sts               = I2C_SUCCESS;
  EFI_STATUS        status                = EFI_SUCCESS;
  UINT8             wdBuf[2]              = {0,};
  UINT32            bytes_written         = 0;
  i2c_descriptor    buffer_desc[2]        = {{0}};
  
  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!buff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_TRACE();
  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  i2c_slave_config *active_slave_config = ((activeI2cChannel == RECOVERY_I2C_PROTOCOL) ?
    &(deviceContext->recovery_slave_config) : &(deviceContext->slave_config));
  deviceContext->activeI2cChannel = activeI2cChannel;
  
  // set up transfer list
  wdBuf[0] = cmd;
  CopyMem(
    &(wdBuf[1]),
    buff,
    2);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 3; /* cmd and buff[low, high] addition*/
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;
  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    active_slave_config,
    buffer_desc,
    1,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }
  if (!bytes_written)
  {
    EC_E("Nothing is written to device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_D( "Total bytes written is %d\n", bytes_written);
Exit:
  return status;
}

/**
 * @brief I2C BYTE WRITE PROTOCOL [ADDR][CMD][DATA]
 * 
 * @param  activeI2cChannel        Active I2c Channel
 * @param  cmd                     I2C command value
 * @param  buff                    Pointer to I2C write buffer
 *
 * @retval EFI_SUCCESS             The I2C byte write is executed successfully.
 * @retval EFI_DEVICE_ERROR        I2C transferred is failed.
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_byte_write (
  UINT8 activeI2cChannel,
  UINT8 cmd,
  void* buff
  )
{
  i2c_status        i2c_sts               = I2C_SUCCESS;
  EFI_STATUS        status                = EFI_SUCCESS;
  UINT8             wdBuf[2]              = {0,};
  UINT32            bytes_written         = 0;
  i2c_descriptor    buffer_desc[1]        = {{0}};

  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!buff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_TRACE();
  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  i2c_slave_config *active_slave_config = ((activeI2cChannel == RECOVERY_I2C_PROTOCOL) ?
    &(deviceContext->recovery_slave_config) : &(deviceContext->slave_config));
  deviceContext->activeI2cChannel = activeI2cChannel;
  
  // set up transfer list
  wdBuf[0] = cmd;
  CopyMem(
    &(wdBuf[1]),
    buff,
    1);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 2; /* cmd and buff addition*/
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;
  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    active_slave_config,
    buffer_desc,
    1,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }
  if (!bytes_written)
  {
    EC_E("Nothing is written to device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  EC_D( "Total bytes written is %d\n", bytes_written);
Exit:
  return status;
}

/**
 * @brief I2C BLOCK WRITE PROTOCOL [ADDR][CMD(32-bit Max)] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
 * @brief This API can perform BYTE WRITE / WORD WRITE PROTOCL as well
 * @param  cmd                       I2C Command
 * @param  wbuff                     Pointer to I2C write buffer
 *
 * @retval EFI_SUCCESS               The I2C block write is executed successfully.
 * @retval EFI_DEVICE_ERROR          I2C transferred is failed.
 * @retval EFI_OUT_OF_RESOURCES      Unable to allocate the required memory or buff_size out of range
 * @retval EFI_INVALID_PARAMETER     Invalid command value
 */
EFI_STATUS
i2c_block_write (
  UINT32 cmd,
  void* wbuff,
  UINT16 cycle_ms,
  UINT8 max_retry
  )
{
  i2c_status        i2c_sts               = I2C_SUCCESS;
  EFI_STATUS        status                = EFI_SUCCESS;
  UINT8             *wdBuf                = NULL;
  CMD_CONTEXT       *cmd_ctx              = &CmdContext[0];
  UINT32            bytes_written         = 0;
  UINT8             retry                 = 0;
  i2c_descriptor    buffer_desc[1]        = {{0}};
  i2c_slave_config  *active_slave_config  = NULL;

  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!wbuff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  for (UINT8 i=0; CmdContext[i].cmd != LAST_TAG_MUST_STAY_AT_LAST ;i++)
  {
    if (CmdContext[i].cmd == cmd)
    {
      cmd_ctx = &CmdContext[i];
      break;
    }
  }

  if ((cmd_ctx->wrDataSize == 0) ||
    (cmd_ctx->wrDataSize > BLOCK_WRITE_BYTE_MAX) ||
    (cmd_ctx->withByteCnt && (cmd_ctx->wrDataSize > 0xFF)) )
  {
    EC_E("- Error in buffer Size criteria:[%d]!!\n", cmd_ctx->wrDataSize);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

 
  UINT16 bufferLength = cmd_ctx->wCmdLength + cmd_ctx->wrDataSize;
  wdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * bufferLength);
  if (wdBuf == NULL)
  {
    EC_E("- Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  deviceContext->activeI2cChannel = cmd_ctx->activeI2cChannel;
  if (deviceContext->activeI2cChannel == RECOVERY_I2C_PROTOCOL)
  {
    active_slave_config = &(deviceContext->recovery_slave_config);
  }
  else if (deviceContext->activeI2cChannel == ACPI_I2C_PROTOCOL)
  {
    active_slave_config = &(deviceContext->slave_config);
  }
  else
  {
    EC_E("- Unknown Active I2C Channel!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  UINT8 i = 0;
  /* Fill in the Command */
  for (;i < cmd_ctx->wCmdLength;i++)
  {
    wdBuf[i] = (UINT8)(cmd_ctx->cmd >> ((3 - i) * 8));
    EC_D( "wdBuf[%d] = 0x%x\n", i, wdBuf[i]);
  }
  /* Fill in Byte Count if the command format have one */
  if (cmd_ctx->withByteCnt)
  {
    wdBuf[i] = cmd_ctx->wrDataSize - 1;
    i++;
  }
  /* Fill in Data payload */
  CopyMem(
    &(wdBuf[i]),
    wbuff,
    (cmd_ctx->wrDataSize - cmd_ctx->withByteCnt));

  /* Fill the descriptor */
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = bufferLength;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  if (deviceContext->debug_mask)
  {
    EC_D ("Dumping write block buffer[%d]:", bufferLength);
    for (int i = 0 ; i < bufferLength; i++)
    {
      EC_P( " 0x%x, ",wdBuf[i]);
    }
    EC_P( " \n ");
  }

  EC_D("- Sending write block request with CMD 0x%x \r\n", cmd_ctx->cmd);
  EC_D("- wCmdLength = %d, wDatLength = %d \r\n", cmd_ctx->wCmdLength, cmd_ctx->wrDataSize);

  // At most 10sec
  do
  {
    i2c_sts = i2c_transfer(
      deviceContext->i2c_handle,
      active_slave_config,
      buffer_desc,
      1,
      NULL,
      NULL,
      0,
      &bytes_written);
    if (i2c_sts == I2C_SUCCESS)
    {
      break;
    }
    else if ((i2c_sts == I2C_ERROR_ADDR_NACK) ||
      (i2c_sts == I2C_ERROR_DATA_NACK))
    {
      SleepMs(cycle_ms*1000);
      status = EFI_SUCCESS;
    }
    retry++;
    EC_P(" I2C retry : %d(%dms) \r ",retry,cycle_ms);
  }while (retry < max_retry);

  if ((I2C_SUCCESS != i2c_sts) &&
    (i2c_sts != I2C_ERROR_ADDR_NACK) &&
    (i2c_sts != I2C_ERROR_DATA_NACK))
  {
    EC_E("- Failed to transfer I2C. Error = %d\n", i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }

  if (!bytes_written)
  {
    EC_E("- Nothing is written to device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_D( "Total bytes written is %d\n", bytes_written);

Exit:
  if (wdBuf)
  {
    FreePool(wdBuf);
    wdBuf = NULL;
  }
  return status;
}

/**
 * @brief I2EC Address Write -> I2EC Data Write
 * @param  address           I2C address value
 * @param  data              Data value of size of 1 byte
 *
 * @retval EFI_SUCCESS       The I2C write byte is executed successfully
 * @retval EFI_DEVICE_ERROR  I2C transferred is failed.
 */
EFI_STATUS
i2ec_writebyte (
  unsigned int address,
  UINT8 data
)
{
  EFI_STATUS  status      = EFI_SUCCESS;
  UINT8       wdBuf[2]    = {0,};

  wdBuf[0] = (address >> 8) & 0xFF;
  wdBuf[1] = address & 0xFF;

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  status = i2c_block_write (
    I2EC_ADDRESS_WO,
    &(wdBuf[0]),
    0,
    0);
  if (EFI_ERROR(status))
  {
    EC_E("i2c_word_write() failed with %r\n", status);
    goto Exit;
  }

  status = i2c_block_write (
    I2EC_DATA_WR,
    &data,
    0,
    0);
  if (EFI_ERROR(status))
  {
    EC_E("i2c_byte_write() failed with %r\n", status);
    goto Exit;
  }

Exit:
  return status;
}

/**
 * @brief I2EC Address Write -> I2EC Data Read
 * @param  address           I2C address value
 * @param  buff              Poniter to the read buffer
 *
 * @retval EFI_SUCCESS       The I2C read byte is executed successfully
 * @retval EFI_DEVICE_ERROR  I2C transferred is failed.
 */
EFI_STATUS
i2ec_readbyte (
  unsigned int address,
  void* buff
)
{
  EFI_STATUS      status          = EFI_SUCCESS;
  UINT8           wdBuf[2]        = {0,};
  UINT8           rdBuf[1]        = {0};

  if (!buff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  wdBuf[0] = (address >> 8) & 0xFF;
  wdBuf[1] = address & 0xFF;

  status = i2c_block_write (
    I2EC_ADDRESS_WO,
    &(wdBuf[0]),
    0,
    0);
  if (EFI_SUCCESS != status)
  {
      EC_E("- i2c_word_write() failed!!\n");
      goto Exit;
  }

  status = i2c_block_read (
    I2EC_DATA_WR,
    &(rdBuf[0]),
    STATIC_DAT_LEN,
    0,
    0);
  if (EFI_SUCCESS != status)
  {
      EC_E("- i2c_byte_read() failed!!\n");
      goto Exit;
  }
  CopyMem(
    buff,
    &(rdBuf[0]),
    1);

Exit:
  return status;
}

/**
 * @brief Pre-define Command Send protocol:
 *        [S] 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] [P]
 * @param  cmd                     I2C command value
 *
 * @retval EFI_SUCCESS             The I2C predefined write is executed successfully
 * @retval EFI_DEVICE_ERROR        I2C transferred is failed.
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_predefine_send (
  UINT8 cmd
)
{
  i2c_status      i2c_sts         = I2C_SUCCESS;
  EFI_STATUS      status          = EFI_SUCCESS;
  UINT32          bytes_written   = 0;
  i2c_descriptor  buffer_desc[3]  = {{0}};
  UINT8           buf0[1]         = {EFLASH_CMD_CHIP_SELECT};
  UINT8           buf1[2]         = {EFLASH_CMD_BLOCK_WRITE};
  UINT8           retry           = 0;
  UINT8           max_retry       = 5;
  UINT8           cycle_ms        = 1;

  if (cmd == INVALID_CMD)
  {
    EC_E("- Unknown command!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  /* Fill the descriptor */
  buffer_desc[0].buffer = buf0;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buf1[1] = cmd;
  buffer_desc[1].buffer = buf1;
  buffer_desc[1].length = 2;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_WRITE ;

  buffer_desc[2].buffer = buf0;
  buffer_desc[2].length = 1;
  buffer_desc[2].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  do
  {
    i2c_sts = i2c_transfer(
      deviceContext->i2c_handle,
      &(deviceContext->recovery_slave_config),
      buffer_desc,
      3,
      NULL,
      NULL,
      0,
      &bytes_written);
    if (i2c_sts == I2C_SUCCESS)
    {
      break;
    }
    else if ((i2c_sts == I2C_ERROR_ADDR_NACK) ||
      (i2c_sts == I2C_ERROR_DATA_NACK))
    {
      SleepMs(cycle_ms*1000);
      status = EFI_SUCCESS;
    }
    retry++;
    EC_P(" I2C retry : %d(%dms) \r ",retry,cycle_ms);
  } while (retry < max_retry);

  if ((I2C_SUCCESS != i2c_sts) &&
    (i2c_sts != I2C_ERROR_ADDR_NACK) &&
    (i2c_sts != I2C_ERROR_DATA_NACK))
  {
    EC_E("Failed to transfer I2C. Error = %d\n", i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }

  if (!bytes_written)
  {
    EC_E("Nothing is written to device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

Exit:
  return status;
}

/**
 * @brief Pre-define block read protocol:
 *   [ADDR] [0x17] [ADDR] [0x18] [CMD] [ADDR] [DATA_0][DATA_1] ... [DATA_N-1]
 *   [S] 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] S 0x5B [R] payload[0] [A] payload[N] [NA] [P]
 *
 * @param  cmd                     I2C command value
 * @param  buff                    Pointer to the read buffer
 * @param  buff_size               Read buffer size
 * @param cycle_ms                 I2C Timeout value in milliseconds
 * @param max_retry                No of retry if in case of failure in transmission
 *
 * @retval EFI_SUCCESS             The I2C predefined block read is executed successfully
 * @retval EFI_DEVICE_ERROR        I2C transferred is failed.
 * @retval EFI_OUT_OF_RESOURCES    Unable to allocate the required memory or buff_size out of range
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_predefine_block_read(
  UINT8 cmd,
  void* buff,
  UINT8 buff_size,
  UINT16 cycle_ms,
  UINT8 max_retry
  )
{
  i2c_status      i2c_sts         = I2C_SUCCESS;
  EFI_STATUS      status          = EFI_SUCCESS;
  UINT32          bytes_read      = 0;
  i2c_descriptor  buffer_desc[4]  = {{0}};
  UINT8           buf0[1]         = {EFLASH_CMD_CHIP_SELECT};
  UINT8           buf1[2]         = {EFLASH_CMD_BLOCK_WRITE};
  UINT8           *rdBuf          = NULL;
  UINT8           retry           = 0;

  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((buff_size == 0) ||
    (buff_size > BLOCK_READ_BYTE_MAX))
  {
    EC_E("Error in buffer Size criteria:[%d]!!\n", buff_size);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  rdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * (buff_size));
  if (rdBuf == NULL)
  {
    EC_E("- Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  // set up transfer list
  buffer_desc[0].buffer = buf0;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buf1[1] = cmd;
  buffer_desc[1].buffer = buf1;
  buffer_desc[1].length = 2;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[2].buffer = rdBuf;
  buffer_desc[2].length = buff_size;
  buffer_desc[2].flags  = I2C_FLAG_START | I2C_FLAG_READ;

  buffer_desc[3].buffer = buf0;
  buffer_desc[3].length = 1;
  buffer_desc[3].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;

  do
  {
    i2c_sts = i2c_transfer(
      deviceContext->i2c_handle,
      &(deviceContext->recovery_slave_config),
      buffer_desc,
      4,
      NULL,
      NULL,
      0,
      &bytes_read);
    if (i2c_sts == I2C_SUCCESS)
    {
      break;
    }
    else if ((i2c_sts == I2C_ERROR_ADDR_NACK) ||
      (i2c_sts == I2C_ERROR_DATA_NACK))
    {
      SleepMs(cycle_ms*1000);
      status = EFI_SUCCESS;
    }
    retry++;
    EC_I("I2C retry : %d(%dms) \r ",retry,cycle_ms);
  } while (retry < max_retry);

  if ((I2C_SUCCESS != i2c_sts) &&
    (i2c_sts != I2C_ERROR_ADDR_NACK) &&
    (i2c_sts != I2C_ERROR_DATA_NACK))
  {
    EC_E("Failed to transfer I2C. Error = %d\n", i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }

  if (!bytes_read)
  {
    EC_E("- Nothing is read from the device\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  CopyMem(
    buff,
    &(rdBuf[0]),
    buff_size);

Exit:
  if (rdBuf)
  {
    FreePool(rdBuf);
    rdBuf = NULL;
  }
  return status;
}

/**
 * @brief Pre-define block write protocol:
 *  [ADDR] [0x17] [ADDR] [0x18] [CMD] [ADDR] [DATA_0][DATA_1] ... [DATA_N-1]
 *  [S] 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] payload[0] [A] payload[N] [NA] [P]
 *
 * @param  cmd                     I2C command value
 * @param  buff                    Pointer to the read buffer
 * @param  buff_size               Read buffer size
 *
 * @retval EFI_SUCCESS             The I2C predefined block write is executed successfully
 * @retval EFI_DEVICE_ERROR        I2C transferred is failed.
 * @retval EFI_OUT_OF_RESOURCES    Unable to allocate the required memory or buff_size out of range
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_predefine_block_write(
  UINT8 cmd,
  void* buff,
  UINT8 buff_size
  )
{
  i2c_status          i2c_sts         = I2C_SUCCESS;
  EFI_STATUS          status          = EFI_SUCCESS;
  UINT8               *wdBuf          = NULL;;
  UINT32              bytes_written   = 0;
  i2c_descriptor      buffer_desc[3]  = {{0}};
  UINT8               buf0[1]         = {EFLASH_CMD_CHIP_SELECT};

  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid buffer!!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if ((buff_size == 0) ||
    (buff_size > BLOCK_WRITE_BYTE_MAX))
  {
    EC_E("Error in buffer Size criteria:[%d]!!\n", buff_size);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  UINT8 bufferLength = buff_size + 2;
  wdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * bufferLength);
  if (wdBuf == NULL)
  {
    EC_E("Failed to Allocate from Pool!!\n");
    status =  EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  /* Fill the descriptor */
  buffer_desc[0].buffer = buf0;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  wdBuf[0] = EFLASH_CMD_BLOCK_WRITE;
  wdBuf[1] = cmd;
  CopyMem(
    &(wdBuf[2]),
    buff,
    buff_size);

  buffer_desc[1].buffer = wdBuf;
  buffer_desc[1].length = bufferLength;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[2].buffer = buf0;
  buffer_desc[2].length = 1;
  buffer_desc[2].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->recovery_slave_config),
    buffer_desc,
    3,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("- Failed to transfer I2C. Error = %d\n", i2c_sts);
    status = I2cstatusToEfistatus(i2c_sts);
    goto Exit;
  }

  if (!bytes_written)
  {
    EC_E("- Nothing is written to device\n");
    status = EFI_DEVICE_ERROR;
  }

Exit:
  if (wdBuf)
  {
    FreePool(wdBuf);
    wdBuf = NULL;
  }
  return status;
}

/**
 * @brief Pre-define block write protocol:
 * [ADDR] [0x17] [ADDR] [0x18] [CMD] [ADDR] [DATA_0][DATA_1] ... [DATA_N-1]
 * [S] 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] payload[0] [A] payload[N] [NA] [P]
 *
 * @param  cmd                     I2C command value
 * @param  writeBuf                Pointer to the writeBuf
 * @param  writeBufSize            write buffer size
 * @param  readBuf                 Pointer to the readBuf
 * @param  readBufSize             read buffer size
 *
 * @retval EFI_SUCCESS             The I2C predefined fast read is executed successfully
 * @retval EFI_OUT_OF_RESOURCES    Insufficient buffer size or Unable to allocate resources for necessary buff_size.
 * @retval EFI_INVALID_PARAMETER   Invalid command value
 */
EFI_STATUS
i2c_predefine_fast_read(
  UINT8 cmd,
  void* writeBuf,
  UINT8 writeBufSize ,
  void* readBuf,
  UINT8 readBufSize
  )
{
  i2c_status      i2c_sts         = I2C_SUCCESS;
  EFI_STATUS      status          = EFI_SUCCESS;
  UINT8           *wdBuf          = NULL;
  UINT32          bytes_written   = 0;
  i2c_descriptor  buffer_desc[3]  = {{0}};
  UINT8           buf0[1]         = {EFLASH_CMD_CHIP_SELECT};

  if (cmd == INVALID_CMD)
  {
    EC_E("Invalid command %d!\n", cmd);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (writeBuf == NULL)
  {
    EC_E("Invalid writeBuf!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (readBuf == NULL)
  {
    EC_E("Invalid readBuf!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!deviceContext)
  {
    EC_E("Invalid deviceContext!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (deviceContext->i2c_handle == NULL)
  {
    EC_E("i2c_handle is NULL!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_TRACE();

  if ((writeBufSize == 0) ||
    (writeBufSize > BLOCK_WRITE_BYTE_MAX))
  {
    EC_E("Error in buffer Size criteria:[%d]!!\n", writeBufSize);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  UINT8 bufferLength = writeBufSize + 2;
  wdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * bufferLength);
  if (wdBuf == NULL)
  {
    EC_E("Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  /* Fill the descriptor */
  buffer_desc[0].buffer = buf0;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  wdBuf[0] = EFLASH_CMD_BLOCK_WRITE;
  wdBuf[1] = cmd;
  CopyMem(
    &(wdBuf[2]),
    writeBuf,
    writeBufSize);

  buffer_desc[1].buffer = wdBuf;
  buffer_desc[1].length = bufferLength;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[2].buffer = readBuf;
  buffer_desc[2].length = readBufSize;
  buffer_desc[2].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;

  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->recovery_slave_config),
    buffer_desc,
    3,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
     EC_E("i2c_transfer() failed with %d\n", i2c_sts);
     status = I2cstatusToEfistatus(i2c_sts);
     goto Exit;
  }

  if (!bytes_written)
  {
    EC_E("Nothing is written to device\n");
    status = EFI_DEVICE_ERROR;
  }

Exit:
  if (wdBuf)
  {
    FreePool(wdBuf);
    wdBuf = NULL;
  }

  return status;
}
