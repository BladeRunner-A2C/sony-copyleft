/** @file EcI2c.c

  Provides I2C routines for communication with Embedded Controller (EC).

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=====================================================================================
when           who         what, where, why
--------       ---         ------------------------------------------------------------
2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                           and code refactoring
2022/12/08     bkulkarn    Update Hamoa EC FW partition size/I2C core instance, code refactoring
2022/12/06     sumesahu    Add PREDEFINE I2c slave address.
2022/09/22     bkulkarn    Support recovery protocol and power/resource related changes
2022/07/29     sumesahu    Initial version
=======================================================================================*/


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
#include <Guid/FileInfo.h>
#include <Library/ECFwUpdateLib.h>
#include <Library/ECFwUpdateLib/EcRecovery.h>
#include <i2c_common.h>

EC_DEVICE_CONTEXT *deviceContext;

/**
 * Return EFI_STATUS value for i2c_status value
 *
 * @param I2cStatus     i2c_status value
 * @retval EFI_SUCCESS             I2C_SUCCESS
 * @retval EFI_DEVICE_ERROR        any other i2c failures
 *
**/
EFI_STATUS EcI2cStatusToEfiStatus(i2c_status I2cStatus)
{
  EFI_STATUS status = EFI_SUCCESS;

  EC_TRACE();

  // Convert from i2c_status to EFI_STATUS
  switch (I2cStatus)
  {
    case I2C_SUCCESS:
    case I2C_TRANSFER_COMPLETED:
      status = EFI_SUCCESS;
      break;

    case I2C_ERROR_INVALID_PARAMETER:
      status = EFI_INVALID_PARAMETER;
      goto ErrorCase;

    case I2C_ERROR_BUS_NOT_IDLE:
      EC_E(" I2C_ERROR_BUS_NOT_IDLE\n");
      goto ErrorCase;
    case I2C_ERROR_MEM_ALLOC_FAIL:
      EC_E(" I2C_ERROR_MEM_ALLOC_FAIL\n");\
      goto ErrorCase;

    case I2C_ERROR_TRANSFER_TIMEOUT:
      EC_E(" I2C_ERROR_TRANSFER_TIMEOUT\n");
      goto ErrorCase;

    case I2C_ERROR_HANDLE_ALLOCATION:
      EC_E(" I2C_ERROR_HANDLE_ALLOCATION\n");
      goto ErrorCase;

    case I2C_ERROR_ARBITRATION_LOST:
      EC_E(" I2C_ERROR_ARBITRATION_LOST\n");
      goto ErrorCase;

    case I2C_ERROR_START_STOP_UNEXPECTED:
      EC_E(" I2C_ERROR_START_STOP_UNEXPECTED\n");
      goto ErrorCase;

    case I2C_ERROR_DATA_NACK:
      EC_E(" I2C_ERROR_DATA_NACK\n");
      goto ErrorCase;

    case I2C_ERROR_ADDR_NACK:
      EC_E(" I2C_ERROR_ADDR_NACK\n");
      goto ErrorCase;

    default:
      status = EFI_DEVICE_ERROR;
      break;

   ErrorCase:
     status = EFI_DEVICE_ERROR;
  }

  return status;
}

/**
 * The entry Point for De-Initialize I2C CORE PROTOCOL
 *
 * @param Void
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cDeInit(void)
{
  EFI_STATUS    status = EFI_SUCCESS;
  i2c_status    i2c_sts  = I2C_SUCCESS;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (deviceContext->i2c_handle)
  {
    i2c_sts = i2c_close(deviceContext->i2c_handle);
    if (I2C_SUCCESS != i2c_sts)
    {
      EC_E("i2c_close() failed with %d!\n", i2c_sts);
      deviceContext->i2c_handle = NULL;
      status = EcI2cStatusToEfiStatus(i2c_sts);
      goto Exit;
    }
    deviceContext->i2c_handle = NULL;
  }

Exit:
  return status;
}

/**
 * The entry Point for Initialize I2C CORE PROTOCOL
 *
 * @param Void
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cInit(void)
{
  EFI_STATUS            status = EFI_SUCCESS;
  i2c_status            i2c_sts = I2C_SUCCESS;
  i2c_slave_config      acpi_i2c_cfg = {0};
  i2c_slave_config      recovery_slave_config = {0};

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (deviceContext->i2c_handle)
  {
    i2c_sts = i2c_close(deviceContext->i2c_handle);
    if (I2C_SUCCESS != i2c_sts)
    {
       EC_E("- Failed to DeInitialize I2C handle %d\n", i2c_sts);
    }
  }

  EC_D("Initializing the I2C Core!!\n");
  i2c_sts = i2c_open(
    (i2c_instance) (I2C_INSTANCE_006),
    &deviceContext->i2c_handle);
  if ((I2C_SUCCESS != i2c_sts) ||
    (NULL == deviceContext->i2c_handle))
  {
    EC_E("i2c_open() failed with :%d\n", i2c_sts);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  EC_D("Initializing Recovery & ACPI I2C Config.\n");

  recovery_slave_config.bus_frequency_khz = I2C_DEFAULT_BUS_FREQ;                   /**< Bus speed in kHz. */
  recovery_slave_config.slave_address   = deviceContext->recovery_slave_addr;       /**< 7-bit I2C slave address.*/
  recovery_slave_config.mode = I2C;                                                 /**< Protocol mode. Refer #i2c_mode */
  recovery_slave_config.slave_max_clock_stretch_us = I2C_MAX_CLK_STRETCH_FREQ;      /**< Maximum time in microseconds that an I2C slave may hold the SCL line low. Not applicable for I3C*/
  recovery_slave_config.core_configuration1 = 0;                                    /**< Core Specific Configuration. Recommended 0. */
  recovery_slave_config.core_configuration2 = 0;                                    /**< Core Specific Configuration. Recommended 0. */
  deviceContext->recovery_slave_config = recovery_slave_config;

  acpi_i2c_cfg.bus_frequency_khz = I2C_DEFAULT_BUS_FREQ;                            /**< Bus speed in kHz. */
  acpi_i2c_cfg.slave_address   = deviceContext->slave_addr;                         /**< 7-bit I2C slave address.*/
  acpi_i2c_cfg.mode = I2C;                                                          /**< Protocol mode. Refer #i2c_mode */
  acpi_i2c_cfg.slave_max_clock_stretch_us = I2C_MAX_CLK_STRETCH_FREQ;               /**< Maximum time in microseconds that an I2C slave may hold the SCL line low. Not applicable for I3C*/
  acpi_i2c_cfg.core_configuration1 = 0;                                             /**< Core Specific Configuration. Recommended 0. */
  acpi_i2c_cfg.core_configuration2 = 0;                                             /**< Core Specific Configuration. Recommended 0. */
  deviceContext->slave_config = acpi_i2c_cfg;

Exit:
  return status;
}

/**
 * The entry Point for EC Initialize Device Data Structure
 *
 * @param Void
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcInitializeDevice(void)
{
  EFI_STATUS status = EFI_SUCCESS;

  EC_TRACE();

  if (!deviceContext)
  {
    deviceContext = AllocateZeroPool(sizeof(EC_DEVICE_CONTEXT));
    if (deviceContext == NULL)
    {
      EC_E("Failed during memory allocation!!\n");
      status = EFI_OUT_OF_RESOURCES;
      goto Exit;
    }
  }

  ZeroMem(deviceContext, sizeof(deviceContext));
  deviceContext->slave_addr = I2C_EC_SLAVE_ADDRESS;
  deviceContext->recovery_slave_addr = I2C_PREDEFINE_EC_SLAVE_ADDRESS;

  /* I2C Core Initialization */
  status = EcI2cInit();
  if (EFI_SUCCESS != status)
  {
    EC_E("EcI2cInit with %r\n", status);
    goto Exit;
  }
  deviceContext->is_device_init_done = 1;

Exit:
  return status;
}

/**
 * The entry Point for EC De Initialize Device Data Structure
 *
 * @param Void
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcDeInitializeDevice(void)
{
  EFI_STATUS status = EFI_SUCCESS;

  EC_TRACE();

  status = EcI2cDeInit();
  EC_WARN_HANDLER(status, EcI2cDeInit);

  if (deviceContext)
  {
    if (deviceContext->fw_img_data)
    {
      FreePool(deviceContext->fw_img_data);
      deviceContext->fw_img_data = NULL;
    }

    FreePool(deviceContext);
    deviceContext = NULL;
  }

  return status;
}

/**
 * The entry Point for I2C CMD WRITE ONLY PROTOCOL [ADDR][CMD]
 *
 * @param cmd                I2c Command write transaction
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cCmdWriteOnly(UINT8 cmd)
{
  i2c_status  i2c_sts         = I2C_SUCCESS;
  EFI_STATUS  status          = EFI_SUCCESS;
  UINT32      bytes_written   = 0;
  UINT32      timeout_ms      = 2500;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  i2c_sts = i2c_write (
    deviceContext->i2c_handle,
    &deviceContext->slave_config,
    0,
    SLAVE_TYPE_NORM,
    &cmd,
    1,
    &bytes_written,
    timeout_ms);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("- I2C write command error :  %d\n", (uint32) i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }
  EC_D( "Total bytes written: %d\n", bytes_written);

Exit:
  return status;
}

/**
 * The entry Point for I2C DATA READ ONLY PROTOCOL [ADDR] [DATA_LOW][DATA_HIGH]
 *
 * @param buff               Pointer Buffer for holding the read data from slave
 * @param buff_size          Size of the read buffer from slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cDataReadOnly(
  void* buff,
  UINT8 buff_size)
{

  i2c_status    i2c_sts = I2C_SUCCESS;
  EFI_STATUS    status = EFI_SUCCESS;
  UINT32        bytes_read = 0;
  UINT8         *rdBuf = NULL;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((0 == buff_size) ||
      (buff_size > BLOCK_READ_BYTE_MAX))
  {
    EC_E("Invalid buffer size :[%d]!\n", buff_size);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  rdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * buff_size);
  if (rdBuf == NULL)
  {
    EC_E("- Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  i2c_sts = i2c_read(
    deviceContext->i2c_handle,
    &deviceContext->slave_config,
    0,
    SLAVE_TYPE_NORM,
    rdBuf,
    buff_size,
    &bytes_read,
    2500);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_read() failed with %d\n", (uint32) i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }
  EC_D( "Total bytes read: %d\n", bytes_read);

  /* Cross check the read block for debugging */
  EC_D( "Dumping read byte buffer[%d]:", bytes_read);
  for (int i = 0 ; i < bytes_read; i++)
  {
    EC_P ( " 0x%x, ",rdBuf[i]);
  }
  EC_P ( "\n ");

  CopyMem(buff, &(rdBuf[0]), bytes_read);

Exit:
  if (rdBuf)
  {
    FreePool(rdBuf);
    rdBuf = NULL;
  }
  return status;
}

/**
 * The entry Point for I2C WORD READ PROTOCOL [ADDR][CMD] [ADDR] [DATA_LOW][DATA_HIGH]
 *
 * @param cmd               I2C command for reading from slave
 * @param buff              Pointer Buffer for holding the read data from slave
 *
 * @retval EFI_SUCCESS      The entry point is executed successfully.
 * @retval other            Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cWordRead(
  UINT8 cmd,
  void* buff)
{

  i2c_status    i2c_sts = I2C_SUCCESS;
  EFI_STATUS    status = EFI_SUCCESS;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  UINT8 wdBuf[1] = {0};
  UINT8 rdBuf[2] = {0,};
  UINT32 bytes_read = 0;
  i2c_descriptor buffer_desc[2] = {{0}};
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
    &(deviceContext->slave_config),
    buffer_desc,
    2,
    NULL,
    NULL,
    0,
    &bytes_read);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  if (!bytes_read)
  {
    EC_E("Invalid number of bytes read!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_D( "Total bytes read: %d\n", bytes_read);

  /* Cross check the read block for debugging */
  EC_D( "Dumping read word buffer[%d]:", bytes_read);
  for (int i = 0 ; i < bytes_read; i++)
  {
    EC_P( " 0x%x, ",rdBuf[i]);
  }
  EC_P( " \n ");

  CopyMem(
    buff,
    &(rdBuf[0]),
    bytes_read);

Exit:
  return status;
}

/**
 * The entry Point for I2C BYTE READ PROTOCOL [ADDR][CMD] [ADDR] [DATA]
 *
 * @param cmd               I2C Command read from slave
 * @param buff              Pointer Buffer for holding the read data from slave
 *
 * @retval EFI_SUCCESS      The entry point is executed successfully.
 * @retval other            Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cByteRead(
  UINT8 cmd,
  void* buff)
{

  i2c_status    i2c_sts = I2C_SUCCESS;
  EFI_STATUS    status = EFI_SUCCESS;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  UINT8 wdBuf[1] = {0};
  UINT8 rdBuf[1] = {0};
  UINT32 bytes_read = 0;
  i2c_descriptor buffer_desc[2] = {{0}};

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
    &(deviceContext->slave_config),
    buffer_desc,
    2,
    NULL,
    NULL,
    0,
    &bytes_read);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  if (!bytes_read)
  {
    EC_E("Invalid number of bytes read!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  EC_D( "Total bytes read: %d\n", bytes_read);

  /* Cross check the read block for debugging */
  EC_D( "Dumping read byte buffer[%d]:", bytes_read);
  for (int i = 0 ; i < bytes_read; i++)
  {
    EC_P( " 0x%x, ",rdBuf[i]);
  }
  EC_D( " \n ");

  CopyMem(
    buff,
    &(rdBuf[0]),
    bytes_read);

Exit:
  return status;
}

/**
 * The entry Point for I2C BLOCK READ PROTOCOL [ADDR][CMD] [ADDR] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
 *
 * @param cmd                I2C Command read from slave
 * @param buff               Pointer Buffer for holding the read data from slave
 * @param buff_size          Size of the read buffer from slave
 * @param cycle_ms           Timeout for retry
 * @param max_retry          Maximum retry count
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2cBlockRead(UINT8 cmd, void* buff, UINT8 buff_size, UINT16 cycle_ms, UINT8 max_retry)
{

  i2c_status        i2c_sts = I2C_SUCCESS;
  EFI_STATUS        status = EFI_SUCCESS;
  UINT8             wdBuf[1] = {0};
  UINT32            bytes_read = 0;
  i2c_descriptor    buffer_desc[2] = {{0}};
  UINT8             *rdBuf = NULL;
  UINT8             retry = 0;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((0 == buff_size) ||
      (buff_size > BLOCK_READ_BYTE_MAX))
  {
    EC_E("Invalid buffer size :[%d]!\n", buff_size);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  rdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * (buff_size+1));
  if (rdBuf == NULL)
  {
    EC_E("- Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  // set up transfer list
  wdBuf[0] = cmd;
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[1].buffer = rdBuf;
  buffer_desc[1].length = buff_size;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;

  EC_D("- Sending read block request with CMD 0x%x rDatLength = %d\r\n",
    cmd, buff_size);

  //At most 10sec
  do
  {
    i2c_sts = i2c_transfer(
        deviceContext->i2c_handle,
        &(deviceContext->slave_config),
        buffer_desc,
        2,
        NULL,
        NULL,
        0,
        &bytes_read);
    if (I2C_SUCCESS == i2c_sts)
    {
      break;
    }
    else if ((I2C_ERROR_ADDR_NACK == i2c_sts) ||
        (I2C_ERROR_DATA_NACK == i2c_sts))
    {
      gBS->Stall(cycle_ms*1000);
      status = EFI_SUCCESS;
    }
    retry++;
    EC_P(" I2C retry : %d(%dms) \r ",retry,cycle_ms);
  } while(retry < max_retry);

  EC_P( " \r\n ");
  if ((I2C_SUCCESS != i2c_sts) &&
    (I2C_ERROR_ADDR_NACK != i2c_sts) &&
    (I2C_ERROR_DATA_NACK != i2c_sts))
  {
    EC_E("- Failed to transfer I2C. Error = %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }
  EC_D( "Total bytes read: %d\n", bytes_read);

  CopyMem(&buff_size,&(rdBuf[0]),1);
  EC_D( "Read Block buff_size is %d\n", buff_size);

  /* Cross check the read block for debugging */
  EC_D( "Dumping read block buffer[%d]:", bytes_read);
  for (int i = 0 ; i < bytes_read; i++)
  {
    EC_P( " 0x%x, ",rdBuf[i]);
  }
  EC_D( " \n ");

  CopyMem(buff, &(rdBuf[1]), (bytes_read-1));

Exit:
  if (rdBuf)
  {
    FreePool(rdBuf);
    rdBuf = NULL;
  }
  return status;
}

/**
 * The entry Point for I2C WORD WRITE PROTOCOL [ADDR][CMD] [DATA_LOW] [DATA_HIGH]
 *
 * @param cmd               I2C Command for writing into slave
 * @param buff              Pointer Buffer for holding the write data into slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cWordWrite(
  UINT8 cmd,
  void* buff)
{
  i2c_status    i2c_sts = I2C_SUCCESS;
  EFI_STATUS    status = EFI_SUCCESS;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  UINT8 wdBuf[2] = {0,};
  UINT32 bytes_written = 0;
  i2c_descriptor buffer_desc[1] = {{0}};

  // set up transfer list
  wdBuf[0] = cmd;
  CopyMem(&(wdBuf[1]), buff, 2);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 3; /* cmd and buff[low, high] addition*/
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->slave_config),
    buffer_desc,
    1,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  EC_D( "Total bytes written is %d\n", bytes_written);

Exit:
  return status;
}

/**
 * The entry Point for I2C BYTE WRITE PROTOCOL [ADDR][CMD] [DATA]
 *
 * @param cmd               I2C Command for writing into slave
 * @param buff              Pointer Buffer for holding the write data into slave
 *
 * @retval EFI_SUCCESS      The entry point is executed successfully.
 * @retval other            Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cByteWrite(
  UINT8 cmd,
  void* buff)
{
  i2c_status i2c_sts = I2C_SUCCESS;
  EFI_STATUS status = EFI_SUCCESS;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  UINT8 wdBuf[2] = {0,};
  UINT32 bytes_written = 0;
  i2c_descriptor buffer_desc[1] = {{0}};

  // set up transfer list
  wdBuf[0] = cmd;
  CopyMem(&(wdBuf[1]), buff, 1);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 2; /* cmd and buff addition*/
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->slave_config),
    buffer_desc,
    1,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  EC_D( "Total bytes written is %d\n", bytes_written);

Exit:
  return status;
}

/**
 * The entry Point for I2C BLOCK WRITE PROTOCOL [ADDR][CMD] [BYTECNT][DATA_0][DATA_1] ... [DATA_N-1]
 *
 * @param cmd                I2C Command for writing into slave
 * @param buff               Pointer Buffer for holding the write data into slave
 * @param buff_size          Size of the read buffer from slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cBlockWrite(
  UINT8 cmd,
  void* buff,
  UINT8 buff_size)
{
  i2c_status        i2c_sts = I2C_SUCCESS;
  EFI_STATUS        status = EFI_SUCCESS;
  UINT8             *wdBuf = NULL;
  UINT32            bytes_written = 0;
  i2c_descriptor    buffer_desc[1] = {{0}};

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((0 == buff_size) ||
      (buff_size > BLOCK_WRITE_BYTE_MAX))
  {
    EC_E("Error in buffer Size criteria:[%d]!!\n", buff_size);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  /*Append 2 bytes for cmd and buffer size*/
  UINT8 bufferLength = buff_size + 2;
  wdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * bufferLength);
  if (wdBuf == NULL)
  {
    EC_E("- Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  /* Fill the descriptor */
  wdBuf[0] = cmd;
  wdBuf[1] = buff_size;
  CopyMem(&(wdBuf[2]), buff, buff_size);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = bufferLength;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  EC_D( "Dumping write block buffer[%d]:", bufferLength);
  for (int i = 0 ; i < bufferLength; i++)
  {
    EC_P( " 0x%x, ",wdBuf[i]);
  }
  EC_P( " \n ");

  EC_D("- Sending write block request with CMD 0x%x \r\n", cmd);
  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->slave_config),
    buffer_desc,
    1,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
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
 * The entry Point for I2C BLOCK WRITE PROTOCOL FOR RAM [ADDR][CMD] [DATA_0][DATA_1] ... [DATA_N-1]
 *
 * @param cmd                I2C Command for writing into slave
 * @param buff               Pointer Buffer for holding the write data into slave
 * @param buff_size          Size of the read buffer from slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS EcI2cBlockWriteToRam(
  UINT8 cmd,
  void* buff,
  UINT16 buff_size)
{
  i2c_status        i2c_sts = I2C_SUCCESS;
  EFI_STATUS        status = EFI_SUCCESS;
  UINT8             *wdBuf = NULL;;
  UINT32            bytes_written = 0;
  i2c_descriptor    buffer_desc[1] = {{0}};

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((0 == buff_size) ||
      (buff_size > BLOCK_WRITE_BYTE_MAX))
  {
    EC_E("Error in buffer Size criteria:[%d]!!\n", buff_size);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  /* Append 1 bytes for cmd size */
  UINT16 bufferLength = buff_size + 1;
  wdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * bufferLength);
  if (wdBuf == NULL)
  {
    EC_E("Failed to Allocate from Pool!!\n");
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  /* Fill the descriptor */
  wdBuf[0] = cmd;
  CopyMem(&(wdBuf[1]), buff, buff_size);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = bufferLength;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  EC_D( "Dumping write block buffer[%d]:", bufferLength);
  for (int i = 0 ; i < bufferLength; i++)
  {
    EC_P( " 0x%x, ",wdBuf[i]);
  }
  EC_P( " \n ");

  EC_D("Sending write block request with CMD 0x%x \r\n", cmd);
  for(int i = 0; i < 5; i++)
  {
    i2c_sts = i2c_transfer(
      deviceContext->i2c_handle,
      &(deviceContext->slave_config),
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
      gBS->Stall(1000);//1ms
    }
  }

  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
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
 * The entry Point for I2EC WRITE BYTE PROTOCOL [ADDR][CMD][I2EC_ADDRESS_WRITE][ADDR_MSB][ADDR_LSB][I2EC_DATA_WRITE][DATA]
 *
 * @param cmd                I2C command for writing into slave
 * @param address            Address for writing the data payload
 * @param data               Data to be written at a given address.
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2EcWriteByte(
  unsigned int address,
  UINT8 data
)
{
  EFI_STATUS        status = EFI_SUCCESS;
  i2c_status        i2c_sts = I2C_SUCCESS;
  UINT8             buff[2] = {0,};
  UINT8             wdBuf[2] = {0,};
  UINT32            bytes_written = 0;
  i2c_descriptor    buffer_desc[1] = {{0}};

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  buff[0] = (address >> 8) & 0xFF;
  buff[1] = address & 0xFF;

  // set up transfer list
  wdBuf[0] = I2EC_ADDRESS_WRITE;
  CopyMem(&(wdBuf[1]), buff, 2);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 3; /* cmd and buff[low, high] addition*/
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->recovery_slave_config),
    buffer_desc,
    1,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer(I2EC_ADDRESS_WRITE) failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  EC_D( "Total bytes written(I2EC_ADDRESS_WRITE) is %d\n", bytes_written);

  // set up transfer list
  wdBuf[0] = I2EC_DATA_READ_OR_WRITE;
  wdBuf[1] = data;
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 2; /* cmd and buff addition*/
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->recovery_slave_config),
    buffer_desc,
    1,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer(I2EC_DATA_READ_OR_WRITE) failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  EC_D( "Total bytes written(I2EC_DATA_READ_OR_WRITE) is %d\n", bytes_written);

Exit:
  return status;
}

/**
 * The entry Point for I2EC READ BYTE PROTOCOL [ADDR][CMD][I2EC_ADDRESS_WRITE][ADDR_MSB][ADDR_LSB][I2EC_DATA_READ][DATA]
 *
 * @param cmd                I2C command for writing into slave
 * @param address            Address for reading the data payload
 * @param data               Data to be written at a given address.
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2EcReadByte(
  unsigned int address,
  void* buff
)
{
  EFI_STATUS        status = EFI_SUCCESS;
  i2c_status        i2c_sts = I2C_SUCCESS;
  i2c_descriptor    buffer_desc[2] = {{0}};
  UINT32            bytes_written = 0;
  UINT8             buf[2] = {0,};
  UINT8             wdBuf[2] = {0,};
  UINT8             buf1[1] = {I2EC_DATA_READ_OR_WRITE};
  UINT8             rdBuf[1] = {0};

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  buf[0] = (address >> 8) & 0xFF;
  buf[1] = address & 0xFF;

  // set up transfer list
  wdBuf[0] = I2EC_ADDRESS_WRITE;
  CopyMem(&(wdBuf[1]), buf, 2);
  buffer_desc[0].buffer = wdBuf;
  buffer_desc[0].length = 3; /* cmd and buff[low, high] addition*/
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE | I2C_FLAG_STOP;

  i2c_sts = i2c_transfer(
    deviceContext->i2c_handle,
    &(deviceContext->recovery_slave_config),
    buffer_desc,
    1,
    NULL,
    NULL,
    0,
    &bytes_written);
  if (I2C_SUCCESS != i2c_sts)
  {
    EC_E("i2c_transfer(I2EC_ADDRESS_WRITE) failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  EC_D( "Total bytes written(I2EC_ADDRESS_WRITE) is %d\n", bytes_written);

  // set up transfer list
  buffer_desc[0].buffer = buf1;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[1].buffer = rdBuf;
  buffer_desc[1].length = 1;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP;

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
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  CopyMem(buff, &(rdBuf[0]), 1);

Exit:
  return status;
}

/**
 * The entry Point for I2EC PREDEFINE SEND PROTOCOL [ADDR] [CS] [ADDR] [BLOCK_WRITE_CMD] [A] [SUB_CMD]
 *
 * @param cmd                I2C command for writing into slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2cPredefineSend(
    UINT8 cmd
)
{
  i2c_status      i2c_sts = I2C_SUCCESS;
  EFI_STATUS      status = EFI_SUCCESS;
  UINT32          bytes_written = 0;
  i2c_descriptor  buffer_desc[3] = {{0}};
  UINT8           buf0[1]={EFLASH_CMD_CHIP_SELECT};
  UINT8           buf1[2]={EFLASH_CMD_BLOCK_WRITE};
  UINT8           retry = 0;
  UINT8           max_retry = 5;
  UINT8           cycle_ms = 1;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
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
      gBS->Stall(cycle_ms*1000);
      status = EFI_SUCCESS;
    }
    retry++;
    EC_P(" I2C retry : %d(%dms) \r ",retry,cycle_ms);
  } while(retry < max_retry);

  if ((I2C_SUCCESS != i2c_sts) &&
      (i2c_sts != I2C_ERROR_ADDR_NACK) &&
      (i2c_sts != I2C_ERROR_DATA_NACK))
  {
    EC_E("i2c_transfer() failed with error = %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

Exit:
  return status;
}

/**
 * The entry Point for I2EC PREDEFINE BLOCK READ PROTOCOL [ADDR] [CS] [ADDR] [BLOCK_WRITE_CMD] [CMD] [ADDR] [DATA_0]..[DATA_N-1]
 *
 * @param cmd                I2C command for writing into slave
 * @param buff               Pointer Buffer for holding the write data into slave
 * @param buff_size          Size of the read buffer from slave
 * @param cycle_ms           Timeout for retry
 * @param max_retry          Maximum retry count
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2cPredefineBlockRead(
  UINT8 cmd,
  void* buff,
  UINT8 buff_size,
  UINT16 cycle_ms,
  UINT8 max_retry
  )
{
  i2c_status      i2c_sts = I2C_SUCCESS;
  EFI_STATUS      status = EFI_SUCCESS;
  UINT32          bytes_read = 0;
  i2c_descriptor  buffer_desc[4] = {{0}};
  UINT8           buf0[1]={EFLASH_CMD_CHIP_SELECT};
  UINT8           buf1[2]={EFLASH_CMD_BLOCK_WRITE};
  UINT8           *rdBuf = NULL;
  UINT8           retry = 0;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((0 == buff_size) ||
      (buff_size > EC_READ_MAX_BYTES_FROM_EFLASH))
  {
    EC_E("Invalid buffer size :[%d]!\n", buff_size);
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  rdBuf = (UINT8 *)AllocateZeroPool(sizeof(UINT8) * (buff_size));
  if (rdBuf == NULL)
  {
    EC_E("Failed to Allocate from Pool!!\n");
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
      gBS->Stall(cycle_ms*1000);
      status = EFI_SUCCESS;
    }
    retry++;
    EC_I("I2C retry : %d(%dms) \r ",retry,cycle_ms);
  } while(retry < max_retry);

  if ((I2C_SUCCESS != i2c_sts) &&
      (i2c_sts != I2C_ERROR_ADDR_NACK) &&
      (i2c_sts != I2C_ERROR_DATA_NACK))
  {
    EC_E("i2c_transfer() failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

  CopyMem(buff, &(rdBuf[0]), buff_size);

Exit:
  if (rdBuf)
  {
    FreePool(rdBuf);
    rdBuf = NULL;
  }
  return status;
}

/**
 * ITE Pre-define block write protocol:
 * [ADDR] [0x17] [ADDR] [0x18] [CMD] [ADDR] [DATA_0][DATA_1] ... [DATA_N-1]
 * S 0x5B [W] [A] 0x17 [A] S 0x5B [W] [A] 0x18 [A] cmd1 [A] payload[0] [A] payload[N] [NA] [P]
 */
EFI_STATUS
EcI2cPredefineBlockWrite(
  UINT8 cmd,
  void* buff,
  UINT8 buff_size
  )
{
  i2c_status          i2c_sts = I2C_SUCCESS;
  EFI_STATUS          status = EFI_SUCCESS;
  UINT8               *wdBuf = NULL;;
  UINT32              bytes_written = 0;
  i2c_descriptor      buffer_desc[3] = {{0}};
  UINT8               buf0[1]={EFLASH_CMD_CHIP_SELECT};

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!buff)
  {
    EC_E("Invalid input buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((buff_size == 0) ||
      (buff_size > EC_WRITE_MAX_BYTES_TO_EFLASH))
  {
    EC_E("Invalid buffer size :[%d]!\n", buff_size);
    status = EFI_INVALID_PARAMETER;
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
  CopyMem(&(wdBuf[2]), buff, buff_size);

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
    EC_E("i2c_transfer(EFLASH_CMD_BLOCK_WRITE) failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
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
 * The entry Point for I2EC PREDEFINE FAST READ PROTOCOL [ADDR] [CS] [ADDR] [BLOCK_WRITE_CMD] [CMD] [ADDR] [DATA_0]..[DATA_N-1]
 *
 * @param cmd                I2C command for writing into slave
 * @param writeBuf           Pointer Buffer for holding the write data into slave
 * @param writeBufSize       Size of the write buffer to slave
 * @param readBuf            Pointer to buffer for holding the read data from the slave
 * @param readBufSize        Size of the read buffer from slave
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcI2cPredefineFastRead(
  UINT8 cmd,
  void* writeBuf,
  UINT8 writeBufSize,
  void* readBuf,
  UINT16 readBufSize
  )
{
  i2c_status      i2c_sts = I2C_SUCCESS;
  EFI_STATUS      status = EFI_SUCCESS;
  UINT8           *wdBuf = NULL;;
  UINT32          bytes_written = 0;
  i2c_descriptor  buffer_desc[4] = {{0}};
  UINT8           buf0[1] = {EFLASH_CMD_CHIP_SELECT};

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->i2c_handle)
  {
    EC_E("i2c_handle is invalid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!writeBuf)
  {
    EC_E("Invalid write buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((0 == writeBufSize) ||
      (writeBufSize > EC_WRITE_MAX_BYTES_TO_EFLASH))
  {
    EC_E("Invalid write buffer size :[%d]!\n", writeBufSize);
    status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  if (!readBuf)
  {
    EC_E("Invalid read buffer!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if ((0 == readBufSize) ||
      (readBufSize > EC_READ_MAX_BYTES_FROM_EFLASH))
  {
    EC_E("Invalid read buffer size :[%d]!\n", readBufSize);
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

  /* Fill the descriptors */
  buffer_desc[0].buffer = buf0;
  buffer_desc[0].length = 1;
  buffer_desc[0].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  wdBuf[0] = EFLASH_CMD_BLOCK_WRITE;
  wdBuf[1] = cmd;
  CopyMem(&(wdBuf[2]), writeBuf, writeBufSize);

  buffer_desc[1].buffer = wdBuf;
  buffer_desc[1].length = bufferLength;
  buffer_desc[1].flags  = I2C_FLAG_START | I2C_FLAG_WRITE;

  buffer_desc[2].buffer = readBuf;
  buffer_desc[2].length = readBufSize;
  buffer_desc[2].flags  = I2C_FLAG_START | I2C_FLAG_READ;

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
    EC_E("i2c_transfer(EFLASH_CMD_BLOCK_WRITE) failed with %d\n", i2c_sts);
    status = EcI2cStatusToEfiStatus(i2c_sts);
    goto Exit;
  }

Exit:
  if (wdBuf)
  {
    FreePool(wdBuf);
    wdBuf = NULL;
  }
  return status;
}
